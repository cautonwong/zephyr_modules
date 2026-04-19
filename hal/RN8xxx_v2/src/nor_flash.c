/**
 * @ingroup    drivers_flashdev
 * @brief      nor flash 驱动
 *
 * @{
 * @file
 *
 */
#include "hfp_system.h"



/******************************************************************************
**定义Flash操作命令字  MX25L3206E
******************************************************************************/

/**
- 2.7 to 3.6 volt for read, erase, and program operations
- 1024 Equal Sectors with 4K byte each
- Page base (256 bytes)
- Fast program time: 0.6ms(typ.) and 3ms(max.)/page
- Byte program time: 9us (typical)
- Fast erase time: 40ms(typ.) /sector ; 0.4s(typ.) /block

- Low active read current: 25mA(max.) at 86MHz
- Low active programming current: 15mA (typ.)
- Low active sector erase current: 9mA (typ.)
- Standby current: 15uA (max.)
- Deep power-down mode 2uA (typical)

*/

struct spi_io_t
{
    uint8  command[8];
    uint8  *buffer;
    uint16 length;
    uint16 cmdnum;
};

#define  MX_CMD_WRSR     0x01        /** write status register */
#define  MX_CMD_WRDI     0x04        /** write disable         */
#define  MX_CMD_RDSR     0x05        /** read status register  */
#define  MX_CMD_WREN     0x06        /** write enable          */
#define  MX_CMD_READ     0x03        /** Read data byte        */
#define  MX_CMD_SE       0x20        /** Sector Erase          */
#define  MX_CMD_BE       0xD8        /** Block Erase           */
#define  MX_CMD_CE       0x60        /** Chip Erase            */
#define  MX_CMD_PP       0x02        /** page program          */
#define  MX_CMD_DP       0xB9        /** Deep power down       */
#define  MX_CMD_RDP      0xAB        /** Realese from Deep power down */
#define  MX_CMD_RDID     0x9F        /** Read Identification  */

#ifdef  BIT_BAND_EN
#define  DO_CS_HIGH()      {*(flash_hal->cs->lat_out) = 1;}
#define  DO_CS_LOW()       {*(flash_hal->cs->lat_out) = 0;}
#else
#define  DO_CS_HIGH()      {*(flash_hal->cs->lat_out) |= flash_hal->cs->pin_bit ;}
#define  DO_CS_LOW()       {*(flash_hal->cs->lat_out) &= ~flash_hal->cs->pin_bit ;}
#endif

uint8 flash_read_and_compare(struct spi_io_t *read_data, const struct spi_bus_ops_t CODE *spi_bus_ops , const struct spi_bus_resource_t CODE *spi_bus_resource , const struct flash_hal_cfg_t CODE *flash_hal)
{
    uint16 ui_i;                         /* 循环变量 */
    
    if (read_data->cmdnum > 8)
    {
        return false;
    }
    
    spi_bus_ops->start(spi_bus_resource);
    
    DO_CS_LOW();
    
    for (ui_i = 0; ui_i < read_data->cmdnum; ui_i ++)
    {
        /* 发送指令和地址 */
        spi_bus_ops->tx_byte(read_data->command[ui_i] , spi_bus_resource);
    }
    
    for (ui_i = 0; ui_i < read_data->length; ui_i ++)
    {
        /* 逐个接收字节 */
        if (read_data->buffer[ui_i] != spi_bus_ops->rx_byte( 0 ,spi_bus_resource))
        {
            DO_CS_HIGH();  /* 将CS线拉高 */
            return false;
        }
    }
    
    DO_CS_HIGH();  /* 将CS线拉高 */

    spi_bus_ops->stop(spi_bus_resource);
    
    return true;
}

uint8 flash_write_data(struct spi_io_t *write_data ,  const struct spi_bus_ops_t CODE *spi_bus_ops , const struct spi_bus_resource_t CODE *spi_bus_resource , const struct flash_hal_cfg_t CODE *flash_hal)
{
    uint16 ui_i;                         /* 循环变量 */
    
    if (write_data->cmdnum > 8)
    {
        return false;
    }
    
    spi_bus_ops->start(spi_bus_resource);    
    
    DO_CS_LOW();
    

    for (ui_i = 0; ui_i < write_data->cmdnum; ui_i ++)
    {
        /* 发送指令和地址 */
        spi_bus_ops->tx_byte(write_data->command[ui_i] , spi_bus_resource);
    }
    
    /* 循环逐个接收字节 */
    for (ui_i = 0; ui_i < write_data->length; ui_i ++)
    { 
        spi_bus_ops->tx_byte(write_data->buffer[ui_i] ,  spi_bus_resource);  /* 逐个接收字节 */
    }
    
    DO_CS_HIGH();  /* 将CS线拉高 */
    
    spi_bus_ops->stop(spi_bus_resource);
    
    return true;
}




uint8 flash_read_data(struct spi_io_t *read_data, const struct spi_bus_ops_t CODE *spi_bus_ops , const struct spi_bus_resource_t CODE *spi_bus_resource , const struct flash_hal_cfg_t CODE *flash_hal)
{
    uint16 ui_i;                         /* 循环变量 */
    
    if (read_data->cmdnum > 8)
    {
        return false;
    }
    
    spi_bus_ops->start(spi_bus_resource);
    
    DO_CS_LOW();
    
    for (ui_i = 0; ui_i < read_data->cmdnum; ui_i ++)
    {
        /* 发送指令和地址 */
        spi_bus_ops->tx_byte(read_data->command[ui_i] , spi_bus_resource);
    }
    plugin_machine.mcu_delay_us(50);
    /* 循环逐个接收字节 */
    for (ui_i = 0; ui_i < read_data->length; ui_i ++)
    {
        /* 逐个接收字节 */
        read_data->buffer[ui_i] = spi_bus_ops->rx_byte( 0 , spi_bus_resource);
    }
    
    DO_CS_HIGH();  /* 将CS线拉高 */
    return flash_read_and_compare(read_data , spi_bus_ops , spi_bus_resource , flash_hal);     /**< 返回读出比较的结果 */
} 



uint8 get_flash_status(const struct spi_bus_ops_t CODE *spi_bus_ops ,  const struct spi_bus_resource_t CODE *spi_bus_resource , const struct flash_hal_cfg_t CODE *flash_hal)
{
    struct spi_io_t spi_io;
    uint8 flash_statue = 0;
    
    spi_io.command[0] = MX_CMD_RDSR;
    spi_io.buffer = &flash_statue;
    spi_io.length = 1;
    spi_io.cmdnum = 1;
    
    flash_read_data(&spi_io , spi_bus_ops , spi_bus_resource , flash_hal);
    if ((flash_statue & 0x01) == 0)
    {
        spi_io.buffer = &flash_statue;
        flash_read_data(&spi_io , spi_bus_ops , spi_bus_resource , flash_hal);
        
        if ((flash_statue & 0x01) == 0)
        {
            return true;
        }
    }
    
    return false;
}

void flash_write_enable(const struct spi_bus_ops_t CODE *spi_bus_ops ,  const struct spi_bus_resource_t CODE *spi_bus_resource , const struct flash_hal_cfg_t CODE *flash_hal)
{
    struct spi_io_t spi_io;
    
    spi_io.command[0] = MX_CMD_WREN;
    spi_io.buffer = NULL;
    spi_io.length = 0;
    spi_io.cmdnum = 1;
    
    flash_write_data(&spi_io , spi_bus_ops , spi_bus_resource , flash_hal);
    
}

uint8 flash_erase(uint32 address, const struct hfp_device_t CODE *device , uint8 erase_mode)
{
    struct spi_io_t spi_io;
    uint8 err;
    uint16 cnt = 50000;
    
    
    const struct spi_bus_ops_t CODE *spi_bus_ops = (const struct spi_bus_ops_t CODE *)device->bus_driver;
    const struct spi_bus_resource_t CODE *spi_bus_resource = (const struct spi_bus_resource_t CODE *)device->resource;
    const struct flash_hal_cfg_t CODE *flash_hal_cfg = (const struct flash_hal_cfg_t CODE *)device->hal_cfg;
 
    if (address > flash_hal_cfg->size)
    {
        return false;
    }    
    
    address &= ~0xFFFU;
    flash_write_enable(spi_bus_ops , spi_bus_resource , flash_hal_cfg);
    plugin_machine.mcu_delay_us(10);
    if (erase_mode == CTRL_FLS_SECTOR_ERASE)
    {
        spi_io.command[0] = MX_CMD_SE;
    }
    else
    {
        spi_io.command[0] = MX_CMD_BE;
    }
    
    spi_io.command[1] = (uint8)(address >> 16);
    spi_io.command[2] = (uint8)(address >> 8);
    spi_io.command[3] = (uint8)address;
    spi_io.buffer = NULL;
    spi_io.cmdnum = 4;
    spi_io.length = 0;
    
    err = flash_write_data(&spi_io , spi_bus_ops , spi_bus_resource , flash_hal_cfg);
    
    while (false == get_flash_status(spi_bus_ops , spi_bus_resource , flash_hal_cfg))
    {
        cnt--;
        if(cnt == 0)
        {
            break;
        }
    }
    
    return err;
}





uint8 flash_read(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device)
{
    struct spi_io_t spi_io;

    
    const struct spi_bus_ops_t CODE *spi_bus_ops = (const struct spi_bus_ops_t CODE *)device->bus_driver;
    const struct spi_bus_resource_t CODE *spi_bus_resource = (const struct spi_bus_resource_t CODE *)device->resource;
    const struct flash_hal_cfg_t CODE *flash_hal_cfg = (const struct flash_hal_cfg_t CODE *)device->hal_cfg;
    
    if ((addr + len) > flash_hal_cfg->size)
    {
        return false;
    }
    
    spi_io.command[0] = MX_CMD_READ;
    spi_io.command[1] = (uint8)(addr >> 16);
    spi_io.command[2] = (uint8)(addr >> 8);
    spi_io.command[3] = (uint8)addr;
    spi_io.buffer = buf;
    spi_io.length = len;
    spi_io.cmdnum = 4;
    
    
    if(false == flash_read_data(&spi_io , spi_bus_ops , spi_bus_resource , flash_hal_cfg))
    {
        return false;
    }
    return true;
}

uint8 flash_write(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device)
{
    struct spi_io_t spi_io;
    uint8 ret;
    uint8 tmp;
    uint16 cnt;
    uint16 timeout = 50000;
    const struct spi_bus_ops_t CODE *spi_bus_ops = (const struct spi_bus_ops_t CODE *)device->bus_driver;
    const struct spi_bus_resource_t CODE *spi_bus_resource = (const struct spi_bus_resource_t CODE *)device->resource;
    const struct flash_hal_cfg_t CODE *flash_hal_cfg = (const struct flash_hal_cfg_t CODE *)device->hal_cfg;
    
    if ((addr + len) > flash_hal_cfg->size)
    {
        return false;
    }
    
    ret = true;
    
    
    while (len)
    {
        flash_write_enable(spi_bus_ops ,  spi_bus_resource , flash_hal_cfg);
        tmp = addr & (256 - 1);  /* 查找一页开始的地方 */
        
        if (tmp != 0)
        {
            cnt = 256 - tmp;       /* 非一页开始的地方最多一次能写的字节数 */
        }
        else
        { 
            cnt = 256;             /* 页开始的地方最多一次能写 EEP_PAGE_SIZE */
        }
        
        if (len < cnt)
        {
            cnt = len;
        }
        
        /* page program */
        spi_io.command[0] = MX_CMD_PP;
        /* 地址高字节 */
        spi_io.command[1] = (uint8)(addr >> 16);
        /* 地址中字节 */
        spi_io.command[2] = (uint8)(addr >> 8);
        spi_io.command[3] = (uint8)addr;          /* 地址低字节 */
        
        spi_io.buffer = buf;           /* 缓存数据 */
        spi_io.cmdnum = 4;             /* 命令长度 */
        spi_io.length = cnt;           /* 数据长度 */
        plugin_machine.mcu_delay_us(10);
        ret = flash_write_data(&spi_io , spi_bus_ops , spi_bus_resource , flash_hal_cfg);       /* 执行命令 */
        plugin_machine.mcu_delay_us(10);
        while (false == get_flash_status(spi_bus_ops , spi_bus_resource , flash_hal_cfg))   /* 等待它的空闲 */
        {
            timeout--;
            if(timeout == 0)
            {
                break;
            }
        }
        
        spi_io.command[0] = MX_CMD_READ;
        
        spi_io.cmdnum = 4;
        
        ret = flash_read_and_compare(&spi_io, spi_bus_ops , spi_bus_resource , flash_hal_cfg);
        
        if (ret == false)
        {
            break;
        }
        
        addr += cnt;
        buf += cnt;
        len -= cnt;
    }
    
    return ret;
}


void flash_power_ctrl(const struct hfp_device_t CODE *device , uint8 power_mode)
{
    const struct flash_hal_cfg_t CODE *flash_hal = (const struct flash_hal_cfg_t CODE *)device->hal_cfg;
    const struct gpio_pin_t CODE *power_ctrl = flash_hal->power_ctrl;
    const struct spi_bus_ops_t CODE *spi_ops = (const struct spi_bus_ops_t CODE*)device->bus_driver;
    
    
    if(power_mode == POWER_ON_MODE)
    {
        if(power_ctrl)
        {
            power_ctrl->active_out(power_ctrl->lat_out , power_ctrl->pin_bit);
            plugin_machine.mcu_delay_us(1000);
        }
        spi_ops->init((const struct spi_bus_resource_t CODE*)device->resource);
        DO_CS_HIGH();
        flash_hal->cs->out(flash_hal->cs->direct , flash_hal->cs->pin_bit);
        
    }
    if(power_mode == POWER_OFF_MODE)
    {
        power_ctrl->non_active_out(power_ctrl->lat_out , power_ctrl->pin_bit);
        spi_ops->stop((const struct spi_bus_resource_t CODE*)device->resource);
        flash_hal->cs->in(flash_hal->cs->direct , flash_hal->cs->pin_bit);
    }
}






uint8 flash_init(const struct hfp_device_t CODE *device , uint8 power_mode)
{
    flash_power_ctrl(device , power_mode);
    return true;
}



/** @} */