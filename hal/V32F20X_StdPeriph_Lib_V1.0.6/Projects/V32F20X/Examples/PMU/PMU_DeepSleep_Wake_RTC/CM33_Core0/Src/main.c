/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-05
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RTC_TimeType RTC_sTimeStruct;
RTC_ALM_AlarmType RTC_ALM_AlarmStruct;
uint8_t Wakeup_Src = 0;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* V32F20xxx CM33 core0 STD library initialization:
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Set NVIC Group Priority to 3
       - Low Level Initialization
     */
  STD_Init(CLK_GetHCLK0Freq());
  
  /* Configure the System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();

  Wakeup_Src = PMU_GetDSleepWKUSource(SLEEP_CORE_CM33);
  if (PMU_DSLPWKU_RTC == Wakeup_Src)
  {
    printf("RTC Deep Sleep Wakeup Wakeup_Src =0x%x.\r\n", Wakeup_Src);
  }

  STD_Delay(5000);
  
  SYSCFGLP_PeriphClockCmd(SYSCFGLP_PeriphClock_RTC_ALARM, ENABLE);
  
  /* Set Current Time 2022-03-07 23:00:00 0*/
  RTC_sTimeStruct.Year    = 0x22;
  RTC_sTimeStruct.Month   = 0x03;
  RTC_sTimeStruct.Date    = 0x07;
  RTC_sTimeStruct.Hours   = 0x23;
  RTC_sTimeStruct.Minutes = 0x00;
  RTC_sTimeStruct.Seconds = 0x00;
  RTC_sTimeStruct.WeekDay = 0x00;
  RTC_sTimeStruct.SubSeconds = 0x00;
  RTC_SetTime(&RTC_sTimeStruct, RTC_INACCURATE);

  RTC_ALM_AlarmStruct.AlarmYear    = 0x22;
  RTC_ALM_AlarmStruct.AlarmMonth   = 0x03;
  RTC_ALM_AlarmStruct.AlarmDate    = 0x07;
  RTC_ALM_AlarmStruct.AlarmHours   = 0x23;
  RTC_ALM_AlarmStruct.AlarmMinutes = 0x00;
  RTC_ALM_AlarmStruct.AlarmSeconds = 0x05;
  RTC_ALM_AlarmStruct.AlarmMask    = RTC_ALM_ALARM_MASK_SEC;
  
  RTCEx_SetAlarm(&RTC_ALM_AlarmStruct);
  
  RTCEx_AlarmCmd(ENABLE);
  
  RTCEx_DSleepWKUSRCConfig(RTCEVT_ALARM);
  PMU_WKUSRCConfig(SLEEP_CORE_CM33, PMU_WKUSRC_RTC_ALM, ENABLE);
  PMU_WKUSRCConfig(SLEEP_CORE_CM0, PMU_WKUSRC_RTC_ALM, ENABLE);
  
  printf("Enter DeepSleep mode.\r\n");
  STD_DeInitTick();
  
  /*Close all unused periphral*/
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_ENCENG, DISABLE);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_WDT1\
    |SYSCFG0_Periph1Clock_WDT0\
    |SYSCFG0_Periph1Clock_SCR\
    |SYSCFG0_Periph1Clock_FC7, DISABLE);
  SYSCFG1_Periph0ClockCmd(SYSCFG1_Periph0Clock_CRYPTO, DISABLE);
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_WDT2, DISABLE);
  
  /*Switch APBLP PMU clock to RCL*/
  SYSCFGLP_APBLPClockConfig(SYSCFGLP_APBLP_CLKSRC_RCL, 1);
  SYSCFGLP_PMUClockConfig(SYSCFGLP_PMU_CLKSRC_RCL, 1);
  
  /*Power down BGP1, RCH1, PLLL and PLLH automatically*/
  PMU_CLKAUTO_Config(SLEEP_CORE_CM33, ENABLE);
  PMU_CLKAUTO_Config(SLEEP_CORE_CM0, ENABLE);
  
  PMU_EnterDSleepMode(SLEEP_CORE_CM0);
  PMU_EnterDSleepMode(SLEEP_CORE_CM33);
  printf("failed.\r\n");

  /* Infinite loop */
  while (1)
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
  CLK_InitType CLK_InitStruct = {0};
    
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
