/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

__IO uint32_t mb_flag = 0UL; /* be set to 1 in Mailbox interrupt */
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* V32F20xxx CM0 core STD library initialization:
       - HCLK 48 MHz, be configured be CM33 core0
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Low Level Initialization
     */
  STD_Init(48000000UL);
  BSP_Printf_Init();
  
  /* Clear global flag */
  mb_flag = 0UL;
  
  /* NVIC configuration, interrupt from CM0 Core */
  NVIC_DisableIRQ(MAILBOX_IRQn);
  NVIC_SetPriority(MAILBOX_IRQn, 0UL);
  NVIC_EnableIRQ(MAILBOX_IRQn);
  
  printf("Wait for flag.\r\n");
  /* Wait until global flag be set */
  while (mb_flag == 0UL)
  {
  }
  
  STD_Delay(1000UL); /* Delay 1s */
  
  while(1)
  {
    BSP_LED_Off(LED3);
    STD_Delay(200UL);
    BSP_LED_On(LED3);
    STD_Delay(200UL);
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
