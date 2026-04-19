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

  if(SET == RTCEx_GetRTCOnlyWKUStatus(RTC_ANA_TIMER_WKU_STS))
  {
    printf("RTC Only Wakeup source = TIMER.\r\n");
    RTCEx_ClearRTCOnlyWKUStatus(RTC_ANA_TIMER_WKU_STS);
  }
  
  RTCEx_RTCWKUModuleClkCmd(RTC_ANA_CLK_RTC_TIMER, ENABLE);
  
  printf("you have 10 seconds to upgrade the test case, hurry up!\r\n");
  STD_Delay(10000);
  printf("how time flies\r\n");

  RTCEx_RTCTimerDeInit();

  RTCEx_RTCTimerCmd(ENABLE);
  RTCEx_RTCOnlyTimerWKUCmd(ENABLE);
  RTCEx_SetRTCTimerCount(2);

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
