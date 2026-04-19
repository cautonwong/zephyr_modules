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
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  RTC_TimeType RTC_sTimeStruct;
  RTC_WKUTimeType RTC_WKUTimeStruct;

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

  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();

  if(SET == RTCEx_GetRTCOnlyWKUStatus(RTC_ANA_RTC_WKU_STS))
  {
    printf("RTC Only Wakeup source = RTC time.\r\n");
    RTCEx_ClearRTCOnlyWKUStatus(RTC_ANA_RTC_WKU_STS);
  }

  printf("you have 10 seconds to upgrade your test case, hurry up! \r\n");
  STD_Delay(10000);

  printf("how time flies \r\n");
  /* Set Current Time 2022-03-07 23:00:00 0*/
  RTC_sTimeStruct.Year    = 0x22;
  RTC_sTimeStruct.Month   = 0x03;
  RTC_sTimeStruct.Date    = 0x07;
  RTC_sTimeStruct.Hours   = 0x23;
  RTC_sTimeStruct.Minutes = 0x00;
  RTC_sTimeStruct.Seconds = 0x00;
  RTC_sTimeStruct.WeekDay = 0x00;
  RTC_sTimeStruct.SubSeconds = 0x00;
  RTC_SetTime(&RTC_sTimeStruct, RTC_ACCURATE);

  RTC_WKUTimeStruct.Year    = 0x22;
  RTC_WKUTimeStruct.Month   = 0x03;
  RTC_WKUTimeStruct.Date    = 0x07;
  RTC_WKUTimeStruct.Hours   = 0x23;
  RTC_WKUTimeStruct.Minutes = 0x00;
  RTC_WKUTimeStruct.Seconds = 0x04;
  RTC_WKUTimeStruct.WKUMask = RTC_WKU_YEAR_MASK |
                              RTC_WKU_MONTH_MASK |
                              RTC_WKU_DAY_MASK | 
                              RTC_WKU_HOUR_MASK |
                              RTC_WKU_MIN_MASK;

  RTCEx_SetRTCOnlyWKUTime(&RTC_WKUTimeStruct);
  RTCEx_RTCOnlyWKUCmd(ENABLE);

  RTCEx_EnterRTCOnlyMode();
  printf("Enter RTC_Only mode.\r\n");

  PMU_EnterDSleepMode(SLEEP_CORE_CM0);
  PMU_EnterDSleepMode(SLEEP_CORE_CM33);
  
  while(1)
  {

  }
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
