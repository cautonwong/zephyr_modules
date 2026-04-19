/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lib_hfm.h"
#include "lib_ccp.h"
#include "CIC_data.h"
#include <string.h>
#include <math.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void SYSCON_Configuration(void);
void GPIO_Configuration(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
  

unsigned int addr2[1024]; 
extern unsigned char DMA_COUNT;
extern unsigned int DSP_Done_Flag;

/* 0:not start  1:integrate  2:comb  */
unsigned char g_CIC_process_flag = 0;
unsigned char g_CIC_Init_flag = 0;

unsigned int * CIC_BaseAddr               = (unsigned int*)0x200F0000;
unsigned int * CIC_Integrate_Tmpdata_addr = (unsigned int*)0x200F2000;
unsigned int * CIC_Comb_Tmpdata_addr      = (unsigned int*)0x200F2400;
unsigned int * CIC_result_addr            = (unsigned int*)0x200F2800;
unsigned int * CIC_Data_addr              = (unsigned int*)0x200F4800;



int Vaule_Waver[1024] __attribute__((section(".ARM.__at_0x2100B000")));
unsigned char FFTexchange[1024]__attribute__((section(".ARM.__at_0x2100C000")));
unsigned int DSP_exchange[1024] __attribute__((section(".ARM.__at_0x2100D000")));

unsigned int TEST_CMDBUF[2048] __attribute__((section(".ARM.__at_0x21008000")));


unsigned char waver_data_01[2314];
unsigned char waver_data_02[2314];

#define Accel_SetSRAMBaseAddr(addr) CASPER_Wr32b((uint32_t)addr,CASPER_CP_SRAMBADDR);
#define Accel_SetABCD_Addr(ab, cd) CASPER_Wr32b((uint32_t)ab | ((uint32_t)cd << 16), CASPER_CP_CFG);
#define Accel_crypto_mul(ctrl)    CASPER_Wr32b((uint32_t)ctrl, CASPER_CP_CTRL);
#define Accel_CIC_mul(ctrl)      CASPER_Wr32b((uint32_t)ctrl, CASPER_CP_CIC_CFG);


extern unsigned int CMDBUF[1380];

#define Accel_done()                                       \
    {                                                      \
        register uint32_t status;                          \
        do                                                 \
        {                                                  \
            status = CASPER_Rd32b(CASPER_CP_STATUS);       \
        } while (0 == (status & CASPER_STATUS_DONE_MASK)); \
    }

    
    
void CIC_Integrate_Start(void)
{
  g_CIC_process_flag = 1;
  Accel_SetABCD_Addr(CA_MK_OFF((void *)CIC_Integrate_Tmpdata_addr), CA_MK_OFF((void *)CIC_Data_addr));  
  Accel_crypto_mul(Accel_IterOpcodeResaddr(0,(uint32_t)kCASPER_CIC_Integrate,CA_MK_OFF(CIC_BaseAddr)));
  return;
}

void CIC_Comb_Start(void)
{
  g_CIC_process_flag = 2;
  Accel_SetABCD_Addr(CA_MK_OFF((void *)CIC_Comb_Tmpdata_addr), CA_MK_OFF((void *)CIC_BaseAddr));
  Accel_crypto_mul(Accel_IterOpcodeResaddr(0,(uint32_t)kCASPER_CIC_Comb,CA_MK_OFF(CIC_result_addr)));
  return;
}

unsigned char check_CIC_Done_status(void)
{
  register uint32_t status;
  
  status = CASPER_Rd32b(CASPER_CP_STATUS);
  if(0 == (status & CASPER_STATUS_DONE_MASK))
  {
    return 0;
  }
  
  return 1;
}
  
int main(void)
{
  unsigned int i;
  DMA_InitType DMA_InitStructure;
  DMA_LinkListType DMA_LLP[2];
  DMA_LinkListInfoType DMA_LinkListInfo;
  HFM_InitType  HFM_InitStruct;
  CIC_InitType  CIC_InitStruct = {0};
  EGY_InitType EGY_InitStruct;
  CF_InitType  CF_InitStruct;
  uint64_t* addr1;
  GPIO_InitType GPIO_InitStructure;
  
  STD_Init(CLK_GetHCLK0Freq());
  
  /* Configure the CM33/CM0 System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  SYSCON_Configuration();
  
  /* systick */
  SysTick_Config(128000);
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();
  printf("hello word\r\n");  
  
  /* CIC init */
  CASPER_Init(0x200F0000);
  g_CIC_Init_flag = 1;
  
  
  /* CIC config */
  CIC_InitStruct.ChannelNum       = 0;
  CIC_InitStruct.ResultLenth      = 1023; //1024-1
  CIC_InitStruct.IntegrateType    = CIC_Integrate_1bit;
  CIC_InitStruct.DecimationOffset = 0;
  CIC_InitStruct.DecimationRate   = 7; //2^7 = 128
  CIC_InitStruct.Order            = CIC_Order_3;   
  Accel_CIC_mul(Accel_CIC_Config(&CIC_InitStruct));
  
  
  memcpy((void *)CIC_Data_addr, CIC_Data, sizeof(CIC_Data));
  
  CIC_Integrate_Start();
  
  while(g_CIC_process_flag != 3)
  {
  }
  
  addr1 = (uint64_t*)CIC_result_addr;
  for (i = 0; i < 1024; i++)
  {
    addr2[i] = (uint32_t)(addr1[i] & 0x00000000FFFFFFFF);
    printf("%d \r\n",addr2[i]);
  }  

  /* HFM cofig*/
  
  memcpy(TEST_CMDBUF, CMDBUF, 2048*4);
  
  HFM_InitStruct.Mode = 1;
  HFM_InitStruct.ExchAddr = (uint32_t)FFTexchange;
  HFM_InitStruct.WaveBaseAddr = (uint32_t)&Vaule_Waver[0];
  HFM_InitStruct.DSPInstrAddr = (uint32_t)TEST_CMDBUF;
  HFM_InitStruct.DSPExchAddr = (uint32_t)&DSP_exchange[0];
  HFM_Init(&HFM_InitStruct);
  
  HFM_ClearINTStatus(HFM_INT_T2FDONE|HFM_INT_DSPDONE);
  HFM_INTConfig(HFM_INT_T2FDONE|HFM_INT_DSPDONE,ENABLE);
  NVIC_EnableIRQ(HFM_COP_IRQn);
  
  /* create value in waver addr*/
  for(i = 0; i < 128; i++)
  {
    Vaule_Waver[i*3+0] = 1000*cos(2*3.1415926*i/128) + 2000*cos(2*3.1415926*2*i/128);
    Vaule_Waver[i*3+1] = 2000*cos(2*3.1415926*i/128 + 2*3.1415926/4)+4000*cos(2*3.1415926*i*2/128 + 2*3.1415926/4);
    Vaule_Waver[i*3+2] = 3000*cos(2*3.1415926*i/128 + 2*3.1415926/2)+6000*cos(2*3.1415926*i*2/128 + 2*3.1415926/2);
  }
  
  HFM_T2F_StartManual();

  while(DSP_Done_Flag == 0)
  {
  }

  /***************************************************************************************
  EGY 
  ***************************************************************************************/
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF14_ENGY_CF0);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  /* config EGY */
  EGY_InitStruct.Channel = 7;//open ABC channel
  EGY_InitStruct.HARMNum = 0;//use Fundamental wave
  EGY_InitStruct.AddSource = EGY_ACCSOURCE_POWER;
  EGY_InitStruct.AddEGYMode = EGY_ACCEGYMODE_ORIGINAL;
  EGY_InitStruct.AddTypeSel = EGY_ACCTYPE_ACTIVEPOWER;
  EGY_InitStruct.AddPWRMode = EGY_ACCPOWERTYPE_ORGINAL;
  EGY_InitStruct.PowerThresholdSEL = 1;//use HFM_EGYPWRTH1
  EGY_Init(EGY0, &EGY_InitStruct);

  /* conig CF */
  CF_InitStruct.CF_Source = CF_SOURCE_EGY0;
  CF_InitStruct.CF_Polarity = CF_ORGINAL;
  CF_InitStruct.CF_PulsePeriod = CF_PERIOD_80MS;
  CF_InitStruct.CF_Fast = CF_FAST_X1;
  CF_InitStruct.CF_Division = 127;//curent 48000000/128 = 375000
  CF_InitStruct.ConstValue = 0;
  CF_Init(CF0, &CF_InitStruct);
  
  /* open CF out */
  CF_Cmd(CF0, ENABLE);

  /* EGY0 SPILL 1s */
  EGY_PWR1ThresholdConfig(137329);

  /* write value to Power Value */
  for(i = 0;i < 27;i++)
  {
      HFM->POWERVALUE[i] = 1000 + 1000*i;
  }
 
 /* EGY0 USE ABC channel P
     so PWRVALUE[0]+PWRVALUE[1]+PWRVALUE[2] 1000+2000+3000=6000
     CF 137329*16384/(48000000/128)/6000 = 1s */

  /* Open HFM INT */
  HFM_INTConfig(HFM_INT_EGY0SPILL,ENABLE);
  NVIC_EnableIRQ(HFM_COP_IRQn);
  EGY_Cmd(EGY0, ENABLE);

  SYSCFG1->EGYCFEN = 7;//Open EGY and CF 0,1,2

  printf("WAVER CIC HFM test success.\r\n");
  while(1)
  {
  }
  

}

/**
  * @brief  AHB and APB Clock Configuration
  *         The Bus Clock is configured as follows :
  *            HCLK0    = RCH 48 MHz
  *            PCLK0    = RCH
  *            HCLK1     = RCH
  *            PCLK1     = RCH
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  
  /* RCH(48M) enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_RCH;
  CLK_OscInitStruct.RCHState = CLK_RCH_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_RCH_DIV4;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = CLK_PLL0_1stN_2;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = 24;
  CLK_OscInitStruct.PLL0.PLL0_M      = 2;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_NONE;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select RCH as AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0 |\
                            CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_RCH;
  CLK_InitStruct.AHBCLKDivider = 1U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_RCH;
  CLK_InitStruct.APBCLKDivider = 1U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Update 1ms tick */
  if (STD_InitTick(CLK_GetHCLK0Freq(), TICK_INT_PRIORITY) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void SYSCON_Configuration(void)
{
  /* Enable DMA clocks */
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_DMA0);
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
  
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_HFM_COP);
  SYSCFG1_Periph0ClockCmd(SYSCFG1_Periph0Clock_HFM_COP, ENABLE);
  
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_WAVER33);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_WAVER33, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{

}


/**
  * @brief  Initialize the Low level.
  * @retval None
  */
void STD_lowInit(void)
{
  /* nothing to do */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the STD error return state */
  while(1)
  {
  }
}

#ifdef  ASSERT_ENABLED
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_errhandler error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_errhandler error line source number
  * @retval None
  */
void assert_errhandler(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************** END OF FILE ******************************/
