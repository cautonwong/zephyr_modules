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
  * @brief  Enables or disables output of RTC second pulse
  * @param  NewState: new state of output of RTC second pulse
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void RTC_SecondPulseOutputCmd(FunctionalState NewState)
{
  GPIO_InitType GPIO_InitStruct;
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  
  if(NewState != DISABLE)
  {
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource14, GPIO_AF0_RTC_SP_O);
  }
  else
  {
    /* disable second pulse output by setting PC14 mode to default analog mode */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
  }
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
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
  
  RTC_SecondPulseOutputCmd(ENABLE);
  STD_Delay(10000);
  RTC_SecondPulseOutputCmd(DISABLE);

  printf("RTC second pulse test.\r\n");

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
