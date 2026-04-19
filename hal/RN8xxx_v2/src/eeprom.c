/**
 * @ingroup    drivers_eepromdev
 * @brief      eeprom 驱动
 *
 * @{
 * @file
 *
 */
#include "hfp_system.h"

#define EEPROM_PASSWORD         0xA0
#define EEPROM_ERR_JUDGE        5
#define EEPROM_OPERATE_CNTS     300

static uint8    eeprom_err_cnts = 0;
static uint8    eeprom_err_flag = 0;
static uint16    eeprom_operate_cnts = 0;

uint8 init_i2c_mem(const struct hfp_device_t CODE *device , uint8 power_mode)
{  
    return true;
}

static uint8 send_device_addr(uint32 device_addr, const struct iic_bus_resource_t CODE *iic_bus , const struct iic_bus_ops_t CODE *bus_driver)
{
    uint32 cnt = 0;

    if ((eeprom_operate_cnts++) > EEPROM_OPERATE_CNTS)
    {
        eeprom_operate_cnts = 0;
        eeprom_err_flag &= ~ERR_EEPROM;
    }

    if (eeprom_err_flag & ERR_EEPROM)
    {
        return false;
    }
    
    while (bus_driver->tx_byte((uint8)(device_addr) ,  iic_bus) == false)
    {
        cnt++;

        plugin_machine.clear_watchdog();
        
        if (cnt >= 80)
        {
            bus_driver->iic_stop(iic_bus);
            if (eeprom_err_cnts < EEPROM_ERR_JUDGE)
            {
                eeprom_err_cnts++;
                if (EEPROM_ERR_JUDGE == eeprom_err_cnts)
                {
                    eeprom_err_cnts = 0;
                    eeprom_err_flag |= ERR_EEPROM;
                }
            }
            return false;
        }
        
        bus_driver->iic_stop(iic_bus);
        plugin_machine.mcu_delay_us(100);
        bus_driver->iic_start(iic_bus);
    }
    
    eeprom_err_flag &= ~ERR_EEPROM;
    eeprom_err_cnts = 0;
    
    return true;
}

/********************************************************************************
* Function Name  : E2Rom_Write_Page
* Description    : Write one page Data To E2Rom
* Arguments      : E2RomAddr - 地址范围 EEP_Size
*                  Len       - 数据长度
*                  DataAddr  - 数据首地址
*                  Index : start from 0,第一块E方为0,第二块E方为1
* Return         : true / false
********************************************************************************/
uint8 i2c_mem_page_write(uint32 physics_addr, uint8 *DataAddr, uint16 Len, const struct hfp_device_t CODE *device)
{
    const struct iic_bus_ops_t CODE *bus_driver;
    const struct iic_bus_resource_t CODE *iic_bus;
    
    bus_driver = (const struct iic_bus_ops_t CODE *)device->bus_driver;
    iic_bus = (const struct iic_bus_resource_t CODE *)device->resource;
    
    bus_driver->iic_start(iic_bus);
    
    if (send_device_addr((physics_addr >> 16) , iic_bus , bus_driver) == false)
    {
        bus_driver->iic_stop(iic_bus);
        return false;
    }

    if (bus_driver->tx_byte((uint8)(physics_addr >> 8) ,  iic_bus) == false)
    {
        return false;
    }
    
    if (bus_driver->tx_byte((uint8)physics_addr ,  iic_bus) == false)
    {
        return false;
    }
      
    while (Len-- != 0)
    {
        if (bus_driver->tx_byte(*DataAddr , iic_bus) == false)
        {
            bus_driver->iic_stop(iic_bus);
            return false;
        }
        
        DataAddr++;
    }

    bus_driver->iic_stop(iic_bus);
    
    return true;
}
/********************************************************************************
* Function Name  : E2Rom_Write
* Description    : Write Data To E2Rom, 可跨页写
* Arguments      : E2RomAddr - 地址范围 EEP_Size
*                  Len       - 数据长度
*                  DataAddr  - 数据首地址
*                  Index : start from 0,第一块E方为0,第二块E方为1
* Return         : true / false
********************************************************************************/
uint8 eeprom_write(uint32 physics_addr, INT8U *DataAddr, uint16 Len, const struct hfp_device_t CODE *device)
{
    uint16 length, tmp;
    uint16 data_addr;
    struct eeprom_hal_cfg_t *eeprom_hal_cfg;
    
    eeprom_hal_cfg = (struct eeprom_hal_cfg_t *)device->hal_cfg;
    
    
    while (Len > 0)
    {
        data_addr = physics_addr & 0x0000FFFF;
      
        tmp = data_addr & (eeprom_hal_cfg->page_size - 1);
        
        if (tmp != 0)
        {
            length = eeprom_hal_cfg->page_size - tmp;
        }
        else
        {
            length = eeprom_hal_cfg->page_size;
        }
        
        if (Len < length)
        {
            length = Len;
        }
        
        if (i2c_mem_page_write(physics_addr, DataAddr, length, device) == false)
        {
            return false;
        }
        
        physics_addr += length;
        DataAddr += length;
        Len -= length;
    }
    
    return true;
}
/********************************************************************************
* Function Name  : E2Rom_Read
* Description    : Read Data From E2Rom
* Arguments      : E2RomAddr - 地址范围 EEP_Size
*                  Len       - 数据长度
*                  DataAddr  - 数据存放首地址
*                  Index : start from 0,第一块E方为0,第二块E方为1
* Return         : true / false
********************************************************************************/
uint8 eeprom_read(uint32 physics_addr,  uint8 *data_addr, uint16 Len, const struct hfp_device_t CODE *device)
{
    uint8 recv_ack;
    const struct iic_bus_ops_t CODE *bus_driver;
    const struct iic_bus_resource_t CODE *iic_bus;
    
    
    bus_driver = (const struct iic_bus_ops_t CODE *)device->bus_driver;
    iic_bus = (const struct iic_bus_resource_t CODE *)device->resource;
    
    bus_driver->iic_start(iic_bus);

    if (send_device_addr((physics_addr >> 16) , iic_bus , bus_driver) == false)
    {
        bus_driver->iic_stop(iic_bus);
        return false;
    }

    if (bus_driver->tx_byte((uint8)(physics_addr >> 8) ,  iic_bus) == false)
    {
        return false;
    }
    
    if (bus_driver->tx_byte((uint8)physics_addr ,  iic_bus) == false)
    {
        return false;
    }

    
    bus_driver->iic_start(iic_bus);
    
    if (bus_driver->tx_byte((uint8)(physics_addr >> 16) | 0x01 ,  iic_bus) == false)
    {
        bus_driver->iic_stop(iic_bus);
        return false;
    }
    
    while (Len-- != 0)
    {
        recv_ack = (Len != 0 ? true : false);
        *data_addr = bus_driver->rx_byte(recv_ack , iic_bus);
        data_addr++;
    }
    
    bus_driver->iic_stop(iic_bus);
    
    return true;
}


uint8 eeprom_data_check(uint32 physics_addr, volatile uint8 *pData, uint16 Len, const struct hfp_device_t CODE *device)
{
    uint8 RecvACK;
    const struct iic_bus_ops_t CODE *bus_driver;
    const struct iic_bus_resource_t CODE *iic_bus;
    uint8 readData;
    
    bus_driver = (const struct iic_bus_ops_t CODE *)device->bus_driver;
    iic_bus = (const struct iic_bus_resource_t CODE *)device->resource;
    
    bus_driver->iic_start(iic_bus);
    
    if (send_device_addr((physics_addr >> 16) , iic_bus , bus_driver) == false)
    {
        bus_driver->iic_stop(iic_bus);
        return false;
    }

    if (bus_driver->tx_byte((uint8)(physics_addr >> 8) ,  iic_bus) == false)
    {
        bus_driver->iic_stop(iic_bus);
        return false;
    }
    
    if (bus_driver->tx_byte((uint8)physics_addr ,  iic_bus) == false)
    {
        bus_driver->iic_stop(iic_bus);
        return false;
    }
    
    bus_driver->iic_start(iic_bus);
    
    if (bus_driver->tx_byte((uint8)(physics_addr >> 16) | 0x01 ,  iic_bus) == false)
    {
        bus_driver->iic_stop(iic_bus);
        return false;
    }
    
    while (Len-- != 0)
    {
        RecvACK = (Len != 0 ? true : false);
        readData = bus_driver->rx_byte(RecvACK , iic_bus); /* 注意,此处如果不是最后一个字节,要求设备响应 */
        
        if (readData != *pData)
        {
            if (Len != 0)
            {
                bus_driver->rx_byte(false , iic_bus);
            }
            
            bus_driver->iic_stop(iic_bus);
            return false;
        }
        
        pData++;
    }
    
    bus_driver->iic_stop(iic_bus);
    
    return true;
}

uint32 get_physics_addr(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device)
{
    struct eeprom_hal_cfg_t *eeprom_hal_cfg;
    
    addr &= 0x0000FFFF;
    eeprom_hal_cfg = (struct eeprom_hal_cfg_t *)device->hal_cfg;
    
    if (addr + len > eeprom_hal_cfg->size || buf == NULL)
    {
        return 0;
    }
    
    addr |= (uint32)(EEPROM_PASSWORD | (eeprom_hal_cfg->hard_addr & 0x0E)) << 16;
    return addr;
}



uint8 write_i2c_mem(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device)
{
    uint8  errcnt;
    uint32 physics_addr = 0;
    
    physics_addr = get_physics_addr(addr,  buf,  len, device);
    
    if(physics_addr == 0)
    {
        return false;
    }

#if 0
    hfp_system_state.error_word &= ~ERR_EEPROM;
#endif  
    for (errcnt = 0; errcnt < 8; errcnt++)
    {
        if(errcnt != 0)
        {
            if (eeprom_write(physics_addr, buf, len, device) == false)
            {
                plugin_machine.mcu_delay_us(20);
                continue;
            }
        }
        if (eeprom_data_check(physics_addr, buf, len, device) == true)
        {
            break;
        }
    }
    
    if (errcnt == 8)
    {
    #if 0
        hfp_system_state.error_word |= ERR_EEPROM;
    #endif
        return false;
    }
    
    return true;
}



uint8 read_i2c_mem(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device)
{
    uint32 physics_addr = 0;
    uint8  errcnt;
    
    
    physics_addr = get_physics_addr(addr,  buf,  len, device);
    if(physics_addr == 0)
    {
        return false;
    }

#if 0
    hfp_system_state.error_word &= ~ERR_EEPROM;
#endif  
    
    for (errcnt = 0; errcnt < 8; errcnt++)
    {
        if(eeprom_read(physics_addr, buf,  len, device) == false)
        {
            plugin_machine.mcu_delay_us(20);
            continue;
        }
        else
        {
            break;
        }
        /*
        //所有数据均有校验，因此不必再为总线传输错误做双次比对。
        if (eeprom_data_check(physics_addr, buf, len, device) == true)
        {
            break;
        }*/
    }    
    
    if (errcnt == 8)
    {
    #if 0
    hfp_system_state.error_word &= ~ERR_EEPROM;
    #endif  
        return false;
    }

    return true;
}



uint8 eeprom_io_ctrl(uint8 cmd, const struct hfp_device_t CODE *device , void *ctrl_parameter)
{
    #if 0
  
    uint16 i;
    uint32 addr;
    uint32 len = 1;
    struct eeprom_hal_cfg_t *eeprom_hal_cfg;
    uint8 test_wr[300] , test_rd[300];
    
    eeprom_hal_cfg = (struct eeprom_hal_cfg_t *)device->hal_cfg;
    addr = 0;
    if(cmd == CTRL_TEST)
    {
        while(addr < eeprom_hal_cfg->size)
        {
            for(i=0;i<len;i++)
            {
               test_wr[i] = i;
            }
            
            plugin_machine.clear_watchdog();
            
            if(true == write_i2c_mem(addr, test_wr, len, device))
            {
                hfp_memset(test_rd , 0x00 , len);
                read_i2c_mem(addr, test_rd, len, device);
                if(hfp_data_compare(test_wr , test_rd , len)!=0)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
            addr += len;
            
            len++;
            if(len > 300)
            {
                len = 300;
            }
            
            if((addr+len) > eeprom_hal_cfg->size)
            {
                len = eeprom_hal_cfg->size - addr;
            }
        }
        return true;
    }
    #endif
    return false;
}



const struct driver_t  CODE iic_mem_driver =
{
    init_i2c_mem,
    read_i2c_mem,
    write_i2c_mem,
    eeprom_io_ctrl,
};
/** @} */
