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
  CLK_OscInitType CLK_OscInitStruct = {0};
  RTC_TimeType RTC_sTimeStruct;
  RTC_TimeType RTC_gTimeStruct;

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
  
  /* XOL enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOLState = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_NONE;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_NONE;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  RTCEx_ClkSRCConfig(RTC_CLKSRC_32KXTAL);

  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();

  /* Set Current Time 2020-12-31 23:59:59 4*/
  RTC_sTimeStruct.Year    = 0x20;
  RTC_sTimeStruct.Month   = 0x12;
  RTC_sTimeStruct.Date    = 0x31;
  RTC_sTimeStruct.Hours   = 0x23;
  RTC_sTimeStruct.Minutes = 0x59;
  RTC_sTimeStruct.Seconds = 0x59;
  RTC_sTimeStruct.WeekDay = 0x04;
  RTC_sTimeStruct.SubSeconds = 0x100;
  RTC_SetTime(&RTC_sTimeStruct,0);
 
  STD_Delay(2000);

  RTC_GetTime(&RTC_gTimeStruct,0);
  printf("The time of RTC is %x:%x:%x %x:%x:%x %x\r\n", \
    RTC_gTimeStruct.Year, \
    RTC_gTimeStruct.Month, \
    RTC_gTimeStruct.Date, \
    RTC_gTimeStruct.Hours, \
    RTC_gTimeStruct.Minutes, \
    RTC_gTimeStruct.Seconds, \
    RTC_gTimeStruct.WeekDay);

  /* Infinite loop */
  while (1)
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
