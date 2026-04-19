#define  _UserB_SystemInit_GLOBALS
#include <UserB_LIB.h>
extern	sIAPComPack_TypeDef	IAPComPack[UART_PORT_MAX];
extern	u16		IAPSysStamp;
extern	u32		FlashBuf[32];
/*****************************************************************************
** Function name:	SystemDelay(u16 t)
**
** Description:		系统延时函数，延时时间
**
** Parameters:		t--取数源地址
**
** Returned value:	NONE
**
******************************************************************************/
void SystemDelay(u16 t)
{
	u16 i;
	while(t--)
	{
		for (i = 0;i < 400;i++);
	}
}


u16 fnUserB_StampThrough(u16 Ago)
{
	extern u16	IAPSysStamp;
	if (IAPSysStamp >= Ago)
		{return (IAPSysStamp - Ago);}
	else
		{return ( (0xffff - Ago) + IAPSysStamp);}
}
/*****************************************************************************
** Function name:	fnRTCDrive_Delay(void)
**
** Description:		RTC延时函数，200Us延时
**
** Parameters:		NONE
**
** Returned value:	NONE
**
******************************************************************************/
void fnRTCDrive_Delay(void)
{
	u8 i;
	for(i=200;i>0;i--)
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

void fnUserB_ClockConfiguration(void)	
{
    SYSCTL->SYS_PS = 0x82;
   	SysModeChg(2,1);
    SYSCTL->SYS_PD = 0x0018;
    SYSCTL->MOD0_EN = 0x3b64;
    SYSCTL->MOD1_EN = 0x0fe0;
    SYSCTL->INTC_EN = 0x01ff;
    SYSCTL->KBI_EN = 0x0000;
    SYSCTL->SYS_RST = 0x0000;   	
	SystemDelay(100);
	SYSCTL->SYS_PS = 0x00;
  	return;
}

void fnUserB_GPIOConfiguration(void)
{
	GPIO->PUA = 0x00000000;
	GPIO->PIMA = 0;				    // 
	GPIO->PCA0 = 0x26000020;	    // P2.0 RXD0 P2.1 TXD0 P2.2 RXD1 P2.3 TXD1
	GPIO->PCA1 = 0x00000000;	    //
	GPIO->PIEA = 0xffffffff;
	
	
	GPIO->PMB = 0xffffffff;		    
	GPIO->PUB = 0x00000000;			 
	GPIO->PCB = 0x00000000;	        
		   					   		
	GPIO->PIEB = 0xffffffff;
	
	GPIO->PMC = 0xffffffff;		    	
	GPIO->PUC = 0xffffff00;				
	GPIO->PCC = 0x000000ff;	        	
		   					   			
	GPIO->PIEC = 0xffffffff;	
	GPIO->PCE = 0x00000000;
}

//定时器tc1初始化 用做5MS中断
void fnUserB_INTC1Init( void )
{
    TC1->CCFG = 0;
    TC1->PS = 4;
    TC1->DN = 3686;
    TC1->CTRL = 0x03;		// star TC0
}

void fnUserB_LVDInit(void)
{
	MADC->LVD_CTRL = 0x0000032e;			 // enable LVD
	MADC->LVD_STAT = 0x01ff;
}

void fnUserB_RTCInit( void )
{
	RTC->CTRL |= 0x00000100;		//RTC Write enable
	fnRTCDrive_Delay();
	RTC->CTRL &= 0xffffff7f;
	fnRTCDrive_Delay();
	RTC->CTRL |= 0x40;
	fnRTCDrive_Delay();
	RTC->CNT1 = 0x00;
	fnRTCDrive_Delay();
	RTC->IE = 0x02;
	fnRTCDrive_Delay();
}


void SystemInit(void)
{
  ;
}

//---------------------------------------------------------
//函数功能：硬件系统初始化
//入口参数：无
//出口参数：无
void fnUserB_SystemInit(void)
{
	fnUserB_ClockConfiguration();
	fnUserB_GPIOConfiguration();
	fnUserB_INTC1Init();
}

void fnUserB_TC1(void)    //系统主节拍.5ms
{
	if(TC1->STA&0x01)
	{
		IAPSysStamp+=5;		//1MS
		TC1->STA = 0x0f;
	}
}
