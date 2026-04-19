#include <UserB_LIB.h>

uint8 code_buffer[CODE_BUF_LEN];
uint16 newfile_crc16;

struct image_transfer_state_t boot_info;

const uint16 CODE CrcTab16[256]=
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

uint16 GetCRC16( uint8 *ucPtr, uint16 uiLen, uint16 uiCrc)
{
    uint16 i, index;
  
    index = 0;
    for ( i = 0; i < uiLen; ++i,++ucPtr )
    {
        index= ( (uiCrc & 0x00ff) ^ ((*ucPtr)  & 0x00ff) );
        uiCrc= ( ( uiCrc>>8 ) & 0x00ff ) ^ ( CrcTab16[index] );
    }
    return ( uiCrc );
}

void sysclk_at_3dot6864(void)
{
    SYSCTL->SYS_PS = 0x82;
    SysModeChg(Clock_PLL_7M4,   Clock_Div_2);
    SYSCTL->SYS_PS = 0x00;
}

void io_config(void)
{
     /* ‰∏äÊãâÁîµÈòªÈÖçÁΩÆ */
     GPIO->PUA = 0x00300000;
     GPIO->PUB = 0x00000000;
     GPIO->PUC = 0x00000000;
     /* ËæìÂá∫Ê®°ÂºèÈÖçÁΩÆ */  
     GPIO->PIMA = 0x00000000;
     GPIO->PIMB = 0x00000000;
     GPIO->PIMC = 0x00000000;

     GPIO->PMA = PM30_IN  | PM31_IN | PM32_IN | PM33_IN  | PM34_IN | PM35_IN | PM36_IN | PM37_IN |
                 PM20_IN | PM21_IN  | PM22_IN | PM23_IN  | PM24_IN  | PM25_IN  | PM26_IN | PM27_IN |
                 PM10_IN | PM11_IN | PM12_IN| PM13_IN | PM14_IN  | PM15_IN  | PM16_IN | PM17_IN |
                 PM00_IN  | PM01_IN | PM02_IN | PM03_IN  | PM04_IN ;
     GPIO->PMB = PM70_IN | PM71_IN | PM72_IN  | PM73_IN  | PM74_IN | PM75_IN | PM76_IN | PM77_IN |
                 PM60_IN | PM61_IN | PM62_IN| PM63_IN | PM64_IN | PM65_IN | PM66_IN | PM67_IN |
                 PM50_IN | PM51_IN  | PM52_IN | PM53_IN | PM54_IN | PM55_IN | PM56_IN  | PM57_IN |
                 PM40_IN  | PM41_IN  | PM42_IN  | PM43_IN  | PM44_IN  | PM45_IN  | PM46_IN  | PM47_IN;
     GPIO->PMC = PM110_IN | PM111_IN | PM112_IN | PM113_IN | PM114_IN | PM115_IN | PM116_IN | PM117_IN |
                 PM100_IN | PM101_IN | PM102_IN | PM103_IN | PM104_OUT | PM105_IN | PM106_OUT | PM107_OUT |
                 PM90_IN | PM91_IN | PM92_IN | PM93_IN | PM94_IN | PM95_IN |PM96_IN | PM97_IN |
                 PM80_IN | PM81_IN | PM82_IN | PM83_IN | PM84_IN | PM85_IN |PM86_IN | PM87_IN;

     GPIO->PIEA = BIT2 + BIT4 + BIT10 + BIT12 + BIT13 + BIT14 + BIT15+ BIT16 + 
                  BIT17 + BIT20 + BIT21 + BIT22 + BIT23 + BIT24 + BIT25 + BIT26 + BIT27 + 
                  BIT30+ BIT31;
     GPIO->PIEB = BIT0 + BIT1 + BIT2 + BIT3+ BIT6 + BIT7 + 
                  BIT8 + BIT9 + BIT15 + BIT26;
     GPIO->PIEC = BIT16 + BIT17/* + BIT21*/ + BIT22 + BIT23 + 
                  BIT24 + BIT25 + BIT26 + BIT27 + BIT28 + BIT31;
     
     GPIO->PASET |= PM13_IN;
     GPIO->PBCLR |= PM52_IN | PM52_IN | PM54_IN| PM55_IN;
     GPIO->PBCLR |= PM115_IN | PM116_IN;
}
void _lowpower(uint8 process)
{
    uint32 lowpower_cnt = 0;
    
    io_config();
    
    sys_clock_sleep();

    flash_init(&ext_flash , POWER_OFF_MODE);

    while(1)
    {
        if (process != true) /*∑¿÷π≥Ã–Ú≈‹∑…ŒÛ»Î*/
        {
            return;
        }
        if (false != power_on_check())
        {
            break;
        }
        if (lowpower_cnt < LOWPOWER_RST_TIMER)
        {
            lowpower_cnt++;

            plugin_machine.clear_watchdog();
            
            plugin_machine.mcu_delay_us(50000);
        }
    }
    
    sysclk_at_3dot6864();

    flash_init(&ext_flash , POWER_ON_MODE);
}
extern uint8 flash_write(uint32 addr, uint8 *buf, uint16 len, const struct hfp_device_t CODE *device);
extern int iap_patch(uint8_t *old, uint32_t oldsize, const uint8_t *patch, uint32_t patchsize, uint32_t newfile);
//-1 »°œ˚…˝º∂£¨ 0, ß∞‹÷ÿ ‘   1 ≥…π¶ 
int code_update(enum boot_process_step_t *boot_process)
{
    uint8 i, light = 0xff;
    uint16 len = MCU_FLASH_PAGE;
    uint32 writebytes = 0,cnt = 0;
    uint32 dest_addr, src_addr, newfile_addr;
    uint16 check_sum, crc16 = 0xFFFF;
    uint8 *old;
    
    flash_init(&ext_flash , POWER_ON_MODE);

    writebytes = ((uint32)boot_info.block_num[0] << 24) + ((uint32)boot_info.block_num[1] << 16) + ((uint32)boot_info.block_num[2] << 8) + boot_info.block_num[3] - 1;

    writebytes *= boot_info.block_size;

    writebytes += boot_info.last_blocksize;

    if (writebytes < 66)
    {
        return -1;
    }

    check_sum = (((uint16)boot_info.code_crc[1]) << 8) | boot_info.code_crc[0];
 
    if (boot_info.transfer_mode & 0x80)
    {
        pin_relay_led.out(pin_relay_led.direct , pin_relay_led.pin_bit);
        
        newfile_crc16 = 0xFFFF;
        old = (uint8*) AllIint_Vector_Offset;
        newfile_addr = (APP_ADDR + 1024);
        iap_patch(old, APP_MAX_SIZE, __NULL, writebytes - 64 - 2, newfile_addr);
        //check_sum = (((uint16)boot_info.code_crc[2]) << 8) | boot_info.code_crc[1];
        if(true == flash_read(APP_ADDR_NEWFILE_CRC, code_buffer, 2, &ext_flash))
        {
            check_sum = (uint16)(code_buffer[1]<<8) + code_buffer[0];
        }

        if(newfile_crc16 != check_sum) //  Œƒº˛–£—È¥ÌŒÛ ÕÀ≥ˆ 
        {
            return -1;
        }
        writebytes = APP_MAX_SIZE;
    }
    else  
    {
        newfile_addr = (APP_ADDR_DIFF + 1024);
        if(writebytes < APP_MAX_SIZE/2) 
        {
            return -1;
        }
    }

    while(writebytes > 0)
    {
        if(false == power_on_check())
        {
            _lowpower(true);
        }
        
        plugin_machine.clear_watchdog();

        if (!(cnt % FLASH_FREQ))
        {
            pin_relay_led.out(pin_relay_led.direct , pin_relay_led.pin_bit);
            
            if (light)
            {
                pin_relay_led.active_out(pin_relay_led.lat_out , pin_relay_led.pin_bit);
            }
            else
            {
                pin_relay_led.non_active_out(pin_relay_led.lat_out , pin_relay_led.pin_bit);
            }
            light ^= 0xff;
        }

        if(writebytes >= MCU_FLASH_PAGE)
        {
            len = MCU_FLASH_PAGE;
        }
        else
        {
            len = writebytes;
        }

        src_addr = 	newfile_addr;
		
        src_addr +=  MCU_FLASH_PAGE * cnt;
        
        for(i = 0; i < FLASH_WRITE_REPEAT; i++)
        {   
            if(true == flash_read(src_addr, code_buffer, len, &ext_flash))
            {
                break;
            }
        }
        if(i == FLASH_WRITE_REPEAT)
        {
            return false;
        }

        crc16 = GetCRC16(code_buffer, len, crc16);

        dest_addr = AllIint_Vector_Offset + src_addr - newfile_addr;

        for (i = 0; i < FLASH_WRITE_REPEAT; i++)
        {
            /*∑¿÷π≥Ã–Ú≈‹∑…ŒÛ»Î*/
            if (*boot_process != Boot_Exe_Updateflag_Check_Successful)
            {
                return true;
            }
            if (true == fnFlash_Write(dest_addr, code_buffer , len , 5))
            {
                break;
            }
        }
        if (i == FLASH_WRITE_REPEAT)
        {
            return false;
        }
            
        writebytes -= len;
        
        cnt++;
    }

    return (check_sum == crc16);
}

uint8 code_check(enum boot_process_step_t *boot_process)
{
    uint8 buff[512];
    uint16 i, len, check_sum, crc16 = 0xFFFF;
    uint32 writebytes = 0, code_addr;

     /*∑¿÷π≥Ã–Ú≈‹∑…ŒÛ»Î*/
    if (*boot_process != Boot_Exe_Updateflag_Check_Successful)
    {
        return true;
    }

    code_addr = AllIint_Vector_Offset;

    writebytes = ((uint32)boot_info.block_num[0] << 24) + ((uint32)boot_info.block_num[1] << 16) + ((uint32)boot_info.block_num[2] << 8) + boot_info.block_num[3] - 1;
    writebytes *= boot_info.block_size;
    writebytes += boot_info.last_blocksize;

    check_sum = (((uint16)boot_info.code_crc[1]) << 8) | boot_info.code_crc[0];
    
    if (boot_info.transfer_mode & 0x80)
    {
        check_sum = newfile_crc16;
        writebytes = APP_MAX_SIZE;
    }

    do
    {
        plugin_machine.clear_watchdog();
        
        if(writebytes >= MCU_FLASH_PAGE)
        {
            len = MCU_FLASH_PAGE;
        }
        else
        {
            len = writebytes;
        }
        
        writebytes -= len;

        for (i = 0; i < len; i++)
        {
            buff[i] = *((const uint8*)(code_addr));
            code_addr++;
        }

        crc16 = GetCRC16(buff, len, crc16);
        
    }while(writebytes);

    return (check_sum == crc16);
}

uint8 update_flag_erase(void)
{
    uint8 i;
    uint8 updata_flag[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xa5,0xa5};
    
    for (i = 0; i < 0x03; i++)
    {
        if (write_i2c_mem(BOOT_INFO_ADDR, updata_flag, sizeof(updata_flag), &eeprom))
        {
            return true;
        }
    }

    return false;
}

void deep_sleep(void)
{
    io_config();

    flash_init(&ext_flash , POWER_OFF_MODE);

    plugin_machine.mcu_enter_sleep();
    
    while(1)
    {
        plugin_machine.clear_watchdog();
    }
}

uint8 update_flag_get(enum boot_process_step_t *boot_process)
{
    if (*boot_process != Boot_Exe_Init)
    {
        return false;
    }
    if(read_i2c_mem(BOOT_INFO_ADDR, code_buffer, sizeof(struct image_transfer_state_t) + 2, &eeprom))
    {
        uint8 i,offset; 
        uint16 checksum = 0xa5a5, rchecksum = 0x00;
        uint32 flag=0;

        for (i = 0; i < sizeof(struct image_transfer_state_t); i++)
        {
            checksum += code_buffer[i];
        }
        offset = sizeof(struct image_transfer_state_t);
        rchecksum = (uint16)(code_buffer[offset] << 8) + code_buffer[offset + 1];

        if (checksum != rchecksum)
        {
            return false;
        }
        
        memcpy((uint8 *)&boot_info, code_buffer, sizeof(struct image_transfer_state_t));
        memcpy((uint8 *)&flag, boot_info.image_enable, 0x04);

        if ((IMAGE_ENABLE_FLAG != flag)/*||(activation_initiated != boot_info.transfer_enable)*/)
        {
            return false;
        }
        
        *boot_process = Boot_Exe_Updateflag_Check_Successful;
        
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{

    //SysConfCheck();
    FlashVoltageTrim();
    
    int res = 0;
    uint8 err = 0;
    uint32 sp;
    void (*Int_Entry) (void);
    enum boot_process_step_t boot_process_step = Boot_Exe_Init;
    
    rn8318_init();
    heap_init();
    if(true != update_flag_get(&boot_process_step))
    {
        goto Rst_Handler;
    }

    if (boot_process_step != Boot_Exe_Updateflag_Check_Successful)
    {
        goto Rst_Handler;
    }

    while(1)
    {
        res = code_update(&boot_process_step);
        if(res < 0)
        {                      
            goto Rst_Handler;
        }
        else if(res == 1)
        {
            if (code_check(&boot_process_step))
            {
                break;
            }
        }

        if (++err >= FLASH_WRITE_REPEAT)
        {
            update_flag_erase();
            
            deep_sleep();
        }
    }

    update_flag_erase();

Rst_Handler:

    sp = *(uint32_t *)(Read_Flash + AllIint_Vector_Offset);
    __set_MSP(sp);
          		
    Int_Entry = (void(*)())(*(uint32_t *)(Read_Flash + AllIint_Vector_Offset + Rst_Handler_Offset  ));
    (*Int_Entry)();
}
