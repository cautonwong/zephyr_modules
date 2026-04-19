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
  * @brief  Enables RTC alarm interrupt
  * @param  Param 
  * @retval None
  */
static void NVIC_EnableRTCALarmIRQ(void)
{
  NVIC_ClearPendingIRQ(RTC_ALM_IRQn);
  /* Set Interrupt Priority */
  NVIC_SetPriority(RTC_ALM_IRQn, 0);
  /* Enable Interrupt in NVIC */
  NVIC_EnableIRQ(RTC_ALM_IRQn);
}



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

  SYSCFGLP_PeriphClockCmd(SYSCFGLP_PeriphClock_RTC_ALARM, ENABLE);

  RTCEx_LPWKUSecondsConfig(5);
  RTCEx_AlarmCmd(ENABLE);
  RTCEx_AlarmLPWKUINTConfig(RTC_ALM_INT_WKUSEC, ENABLE);
  
  NVIC_EnableRTCALarmIRQ();

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
