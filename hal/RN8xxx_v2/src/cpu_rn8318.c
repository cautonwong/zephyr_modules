/**
 * @ingroup    RN8318
 * @brief      RN8318 cpu定义
 *
 * @{
 * @file
 *
 */
#include "rn831x_rn861x_mcu.h"
#include "rn8xxx_v2_lib.h"
#include "system_rn831x_rn861x_mcu.h"
#include "core_cm0.h"
#include "hfp_system.h"





//29M
/*全速运行29M */
static void sys_clock_normal_boot(uint16 flag) 
{
    uint8 result = 0;
    if (0x5aa5 == flag)
    {
        SYSCTL->SYS_PS = 0x82;
        result = SysModeChg( Clock_PLL_58M9_DIV2, Clock_Div_2);
        if(result)
        {
            SysModeChg(Clock_RC_29M5,   Clock_Div_4);  //切换至内部RC，2分频，14.75M    
        }    
        SYSCTL->SYS_PS = 0x00;
    }
}

void  rn8318_clear_watchdog(void)
{
    if((WDT->EN & BIT(8)) == 0)
    {
        WDT->EN = 0xbb;
    }
}
/* 实测试10us到50ms误差在5%以内。@ 147435*/
/* 复位运行 3685875*/
/* 上电全速运行 14743500*/
/* 唤醒运行7371750*/
/* 休眠运行327687*/
/* 实测试10us到50ms误差在5%以内。@ 147435*/
uint8 rn8318_delay_us(volatile uint16 count)
{
    uint32 timeout = 1000000;
    
    if(count == 0)
    {
        return true;
    }
    
    SYSCTL->SYS_PS = 0x82;
    SYSCTL->MOD0_EN |= (0x00000001 << 5);
    SYSCTL->SYS_PS = 0x00;
    TC1->STA = 0x0f;
    
    TC1->CCFG = 0x00;
    
    TC1->PS = 13;
    
    TC1->DN = count;
    TC1->CTRL = 0x01;
    while(0 == (TC1->STA & 0x00000001))
    {
        timeout--;
        if(timeout < 1)
        {
            return false;
        }
    } 
   
    TC1->CTRL = 0x00;
    return true;
}



const uint32 CODE freq[6] = {7372800,3686400,1843200,32768,14745600,29491200,};
#if 0
static uint32 get_system_clk(void)
{
    uint32 temp;
    
    
    temp = (SYSCTL->OSC_CTRL1 >> 8) & 0x7;
    if(temp<6)
    {
        temp = freq[temp];
    }
    else
    {
        temp = 3686400;
    }
    
    if(SYSCTL->OSC_CTRL1 & 0x00000020)	
    {
        temp = 1843200-224704;
    }
    
    return temp;
}
#endif

/*全速运行14M */
void sys_clock_normal(void)  
{
    SYSCTL->SYS_PS = 0x82;
    SysModeChg( Clock_PLL_14M7, Clock_Div_1);
    SYSCTL->SYS_PS = 0x00;
}


/* 低功耗休眠 32768 */
void sys_clock_sleep(void)  
{
    SYSCTL->SYS_PS = 0x82;
    SysModeChg( Clock_Losc, Clock_Div_1);
    SYSCTL->SYS_PS = 0x00;
}





static void cacheOnOff(uint32_t c)
{  
    *(uint32_t *)(0x50014060) =  c ? 0xfeed0001 : 0xfeed0000; 
}


void gpio_config(void)
{
     GPIO->PCA0 = SWD_SEL | PC267_IO | PC245_IO | PC223_IO | PC201_IO | PC10_IO | PC11_IO | PC12_IO |
                  PC13_IO | PC14_IO | PC15_IO | PC16_IO | PC17_IO | PC03_AIN;

     GPIO->PCA1 = PC37_IO | PC36_IO | PC35_IO | PC34_IO | PC33_IO | PC32_IO | PC31_IO | PC30_IO;
     
     GPIO->PCB2 = PC45_2_KEY7 | PC44_2_KEY6;
     
     GPIO->PCE = 0x0000000F;
     
     /* 涓婃媺鐢甸樆閰嶇疆 */
     GPIO->PUA = 0x00300000;
     GPIO->PUB = 0x00000004;
     GPIO->PUC = 0x00000000;
     /* 杈撳嚭妯″紡閰嶇疆 */  
     GPIO->PIMA = 0x00000000;
     GPIO->PIMB = 0x00000000;
     GPIO->PIMC = 0x00000000;
     
     GPIO->PMA = PM30_IN | PM31_OUT | PM32_IN | PM33_OUT | PM34_IN | PM35_OUT | PM36_IN | PM37_IN |
                 PM20_OUT | PM21_OUT | PM22_IN | PM23_OUT | PM24_IN | PM25_IN | PM26_IN | PM27_IN |
                 PM10_OUT | PM11_OUT | PM12_IN| PM13_OUT | PM14_OUT| PM15_OUT |PM16_OUT| PM17_IN|
                 PM00_IN  | PM01_OUT | PM02_IN | PM03_IN  | PM04_IN ;
     
     GPIO->PMB = PM70_OUT | PM71_OUT | PM72_IN | PM73_IN | PM74_OUT | PM75_OUT | PM76_OUT | PM77_OUT |
                 PM60_OUT | PM61_OUT | PM62_OUT | PM63_OUT | PM64_OUT | PM65_OUT | PM66_OUT | PM67_OUT |
                 PM50_OUT | PM51_OUT | PM52_OUT| PM53_IN | PM54_OUT| PM55_OUT |PM56_IN| PM57_OUT|
                 PM40_IN  | PM41_IN  | PM42_OUT | PM43_IN  | PM44_IN | PM45_IN |PM46_IN| PM47_OUT;

     GPIO->PMC = PM110_OUT | PM111_OUT | PM112_IN | PM113_OUT | PM114_OUT | PM115_OUT | PM116_OUT | PM117_IN |
                 PM100_IN | PM101_IN | PM102_OUT | PM103_OUT | PM104_OUT | PM105_IN | PM106_OUT | PM107_OUT |
                 PM90_OUT | PM91_OUT | PM92_OUT| PM93_OUT | PM94_OUT| PM95_OUT |PM96_OUT| PM97_OUT|
                 PM80_OUT | PM81_OUT | PM82_OUT| PM83_OUT | PM84_OUT| PM85_OUT |PM86_OUT| PM87_OUT;

     /*杈撳叆浣胯兘閰嶇疆*/
     GPIO->PIEA = BIT31 + BIT30 + BIT27 + BIT17 + BIT19 + BIT22 + BIT23 + BIT12 + BIT13 + BIT14;
     GPIO->PIEB = 0;
     GPIO->PIEC = 0;     
     
     
     GPIO->PB &= ~BIT17;
     GPIO->PC &= ~BIT30;
       
    
    //GPIO->PMA &= ~BIT28;
    GPIO->PIEA |= BIT28;    //SDA_OUTPUT();
    GPIO->PA |= BIT28;      //SDA_DOUT_1();
    __NOP();
    
    GPIO->PA |= BIT29;      //SCL_DOUT_1();
    //GPIO->PMA &= ~BIT29;
    GPIO->PIEA |= BIT29;    //SCL_OUTPUT();    
    __NOP();

}

/***********************************************************
 * @function_name: rn8318_init
 * @function_file: cpu.c
 * @描述:mcu初始化函数
 *
 * @参数:
 * @返回:
 * @作者:shuyuankang 
 **********************************************************/
void rn8318_init(void)
{
    uint16 flag = 0x5aa5;
    uint32 val = 0;
    
    cacheOnOff(1);
    
    __disable_irq();

    SYSCTL->SYS_PS = 0x82;
    /**
    复位之后首先设置CMPLVD_EN 、WDT_EN 、 GPIO_EN
    */
    SYSCTL->MOD1_EN = (0x00000001 << 11) |  (0x00000001 << 10) |  (0x00000001 << 9) | (0x00000001 << 6) | (0x00000001 << 5);
    
    //SYSCTL->SYS_PD = (0x00000001 << 11) + (0x00000001 << 9) + (0x00000001 << 4) + (0x00000001 << 1);
    SYSCTL->SYS_PD = (0x00000001 << 9) + (0x00000001 << 4) + (0x00000001 << 3);
    /**
    MCU第一次上电时，需要等待约0.5S的起震时间，才可以使用PLL
    */
    if(SYSCTL->SYS_RST & 0x00000020)
    {
        for(val=0;val<20000;val++)
        {
            rn8318_clear_watchdog();
          __NOP();
        }
        //SYSCTL->SYS_RST |= 0x00000020;
    }
    
    sys_clock_normal_boot(flag);
    
    val = (0x00000001 << 7) |  (0x00000001 << 2);
    if(SYSCTL->SYS_RST & val)
    {
        /**
        系统发生看门狗、复位时的HOOK
        */
        
    }
    
    //SYSCTL->SYS_RST = (0x00000001 << 8) | (0x00000001 << 7) | (0x00000001 << 6) | (0x00000001 << 5) | (0x00000001 << 2);
    SYSCTL->SYS_PS = 0x00;
    
    //MADC->LVD_STAT |= 0x00000070;
    MADC->LVD_CTRL = (0x00000001 << 7);
    
    gpio_config();
    
}


/***********************************************************
 * @function_name: power_off_check
 * @function_file: cpu.c
 * @描述:掉电检测函数
 * @作者:shuyuankang 
 **********************************************************/
uint8 power_off_check(void)
{
    if(0==(MADC->LVD_STAT & 0x00000004))
    {
        
        return true;
    }
    return false;
}
/***********************************************************
 * @function_name: power_off_check
 * @function_file: cpu.c
 * @描述:上电检测函数
 * @作者:shuyuankang 
 **********************************************************/
uint8 power_on_check(void)
{
    uint16 i;
    
    for(i=0;i<1000;i++)
    {
        if(0 == (MADC->LVD_STAT & 0x00000004))
        {
            return false;
        }
    }
    return true;
}


/***********************************************************
 * @function_name: mcu_enter_sleep
 * @function_file: cpu.c
 * @描述:芯片进去休眠
 * @作者:shuyuankang 
 **********************************************************/
void  rn8318_enter_sleep(void)
{
    sys_clock_sleep();

    SYSCTL->SYS_PS = 0x82;
    
    SYSCTL->MOD0_EN = 0;
    
    SYSCTL->SYS_PS = 0x00;
    
    __WFI();
}


/***********************************************************
 * @function_name: mcu_exit_sleep
 * @function_file: cpu.c
 * @描述:芯片从休眠中唤醒后的操作
 * @作者:shuyuankang 
 **********************************************************/
void  rn8318_exit_sleep(void)
{

}


#if 0


UART_TypeDef *UART_list[]=
{
    UART0,
    UART1,
    UART2,
    UART3,
    UART4,
    UART5,
};

const IRQn_Type CODE UART_IRQ[]=
{
    UART0_IRQn,
    UART1_IRQn,
    UART2_IRQn,
    UART3_IRQn,
    UART4_IRQn,
    UART5_IRQn,
};

const uint32 CODE clock_en[] =
{
    UART0_EN,
    UART1_EN,
    UART2_EN,
    UART3_EN,
    UART4_EN,
    UART5_EN,
};

uint8 rn8318_uart_init(struct uart_config_t *uart_config , const struct uart_resource_t CODE *uart_resource)
{
    uint32	ClkDiv;
    UART_TypeDef   *UARTx;
    uint32 ctrl = 0;

    if(uart_resource->mcu_uart_index < 6)
    {
        SYSCTL->SYS_PS = 0x82;
        SYSCTL->MOD0_EN |= clock_en[uart_resource->mcu_uart_index];
        SYSCTL->SYS_PS = 0x00;
        
        __NOP();
        __NOP();
        
        UARTx = UART_list[uart_resource->mcu_uart_index];
        
    }
    else
    {
        return false;
    }
    
    if(uart_config->data_bits == 7)
    {
        ctrl |= (2<<5);
    }
    if(uart_config->data_bits == 8)
    {
        ctrl |= (3<<5);
    }
    if(uart_config->parity == UART_PARITY_NO)
    {
        ctrl |= (0<<7);
    }
    if(uart_config->parity == UART_PARITY_ODD)
    {
        ctrl |= (1<<7);
    }
    if(uart_config->parity == UART_PARITY_EVEN)
    {
        ctrl |= (2<<7);
    }
    if(uart_config->mode == UART_MODE_IR)
    {
        ctrl |= (1<<10);
        ctrl |= (1<<12);
        SYSCTL->SYS_PS = 0x82;
        SYSCTL->MOD0_EN |= UART38K_EN;
        
        SYSCTL->IRFR_CTRL = 0x18;
            
        SYSCTL->SYS_PS = 0x00;
        GPIO->PCA0 |= (UART2_SEL | PC01_TX2 | PC00_RX2);

    }
    if(uart_config->stop_bits == 1)
    {
        ctrl |= (0<<4);
    }
    if(uart_config->stop_bits == 2)
    {
        ctrl |= (1<<4);
    }
    UARTx->CTRL = 1;
    UARTx->CTRL |= ctrl;
    
    ClkDiv = get_system_clk();
    ClkDiv=ClkDiv/(uart_config->baud_rate * 10 * 16)-1;
    UARTx->BAUD = ClkDiv;
    
    
    if(uart_resource->rx_pin)
    {
        uart_resource->rx_pin->in(uart_resource->rx_pin->direct , uart_resource->rx_pin->pin_bit);
    }
    if(uart_resource->tx_pin)
    {
        uart_resource->tx_pin->out(uart_resource->tx_pin->direct , uart_resource->tx_pin->pin_bit);
        *(uart_resource->tx_pin->lat_out) = 1;
    }
    NVIC_EnableIRQ( UART_IRQ[uart_resource->mcu_uart_index] );
	return true;
}

uint8 rn8318_uart_close(const struct uart_resource_t CODE *uart_resource)
{
    UART_TypeDef   *UARTx;
    

    
    if(uart_resource->mcu_uart_index < 6)
    {
        UARTx = UART_list[uart_resource->mcu_uart_index];
    }
    else
    {
        return false;
    }    

    UARTx->CTRL &= ~0x00000001;
    NVIC_DisableIRQ( UART_IRQ[uart_resource->mcu_uart_index] );
    return true;
}

void rn8318_uart_recive_enable(uint8 enable , const struct uart_resource_t CODE *uart_resource)
{
    UART_TypeDef   *UARTx;
    
    if(uart_resource->mcu_uart_index < 6)
    {
        UARTx = UART_list[uart_resource->mcu_uart_index];
        if(enable)
        {
            UARTx->CTRL |= 0x0C;
            
        }
        else
        {
            UARTx->CTRL &= 0xfff3;
        }
        UARTx->STA = 0x3F;
    }
}

void rn8318_send_byte(uint8 send_data , const struct uart_resource_t CODE *uart_resource)
{
    UART_TypeDef   *UARTx;
    
    if(uart_resource->mcu_uart_index < 6)
    {
        UARTx = UART_list[uart_resource->mcu_uart_index];
        
        UARTx->TXD = send_data;
    }
}

uint8 rn8318_recive_byte(const struct uart_resource_t CODE *uart_resource , uint8 *byte)
{
    UART_TypeDef   *UARTx;
    

    if(uart_resource->mcu_uart_index < 6)
    {
        UARTx = UART_list[uart_resource->mcu_uart_index];
        *byte = UARTx->RXD;
        if(UARTx->STA & 0x00000004)
        {
            UARTx->STA |= 0x00000004;
            return false;
        }
        if(UARTx->STA & 0x00000008)
        {
            UARTx->STA |= 0x00000008;
            return false;
        }
        if(UARTx->STA & 0x00000010)
        {
            UARTx->STA |= 0x00000010;
            return false;
        }
        return true;
    }
    return false;
}
void rn8318_uart_send_enable(uint8 enable , const struct uart_resource_t CODE *uart_resource)
{
    UART_TypeDef   *UARTx;
    
    if(uart_resource->mcu_uart_index < 6)
    {
        UARTx = UART_list[uart_resource->mcu_uart_index];
        if(enable)
        {
            UARTx->CTRL |= 0x0002;
            
        }
        else
        {
            UARTx->CTRL &= 0xfffd;
        }
        UARTx->STA = 0x02;
    }
}

uint8 rn8318_set_baud(uint16 baud , const struct uart_resource_t CODE *uart_resource)
{
    uint32	ClkDiv;
    UART_TypeDef   *UARTx;

    if(uart_resource->mcu_uart_index < 6)
    {     
        UARTx = UART_list[uart_resource->mcu_uart_index];
    }
    else
    {
        return false;
    }
    UARTx->CTRL &= 0xFFFFFE;
    ClkDiv = get_system_clk();
    ClkDiv=ClkDiv/(baud*10 * 16)-1;
    UARTx->BAUD = ClkDiv;
    UARTx->CTRL |= 0x00000001;
	return true;
}

#endif


const struct machine_interface_t CODE plugin_machine =
{
    rn8318_init,
    __NULL,
    __NULL,
    __NULL,
    rn8318_clear_watchdog,
    rn8318_enter_sleep,
    rn8318_exit_sleep,
    rn8318_delay_us,
    power_off_check,
    power_on_check,
    __NULL,
    __NULL,
    __NULL,
    __NULL,
    __NULL,
    __NULL,
};




/** @} */

