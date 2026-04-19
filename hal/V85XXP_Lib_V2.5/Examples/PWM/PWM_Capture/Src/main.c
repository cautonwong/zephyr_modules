/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

volatile unsigned char test_success;

__IO uint16_t CapData[10] = { 0 };
__IO uint8_t count;


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Clock_Init:
              - PLLL input clock    : External 32K crystal
              - PLLL frequency      : 26M
              - AHB Clock source    : PLLL
              - AHB Clock frequency : 26M (PLLL divided by 1)
              - APB Clock frequency : 13M (AHB Clock divided by 2)
  * @param  None
  * @retval None
  */
void Clock_Init(void)
{
  CLK_InitTypeDef CLK_Struct;

  CLK_Struct.ClockType = CLK_TYPE_AHBSRC \
                        |CLK_TYPE_PLLL   \
                        |CLK_TYPE_HCLK   \
                        |CLK_TYPE_PCLK;
  CLK_Struct.AHBSource      = CLK_AHBSEL_LSPLL;
  CLK_Struct.PLLL.Frequency = CLK_PLLL_26_2144MHz;
  CLK_Struct.PLLL.Source    = CLK_PLLLSRC_XTALL;
  CLK_Struct.PLLL.State     = CLK_PLLL_ON;
  CLK_Struct.HCLK.Divider   = 1;
  CLK_Struct.PCLK.Divider   = 2;
  CLK_ClockConfig(&CLK_Struct);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  PWM_BaseInitType PWM_BaseInitStruct;
  PWM_ICInitType PWM_ICInitStruct;
  GPIO_InitType GPIO_InitStruct;
  uint8_t i; 

  test_success = 0;

  Clock_Init();
  Stdio_Init();

  /* PWM3 base initialization */
  PWM_BaseStructInit(&PWM_BaseInitStruct);
  PWM_BaseInitStruct.ClockDivision = PWM_CLKDIV_2;
  PWM_BaseInitStruct.ClockSource = PWM_CLKSRC_APB;
  PWM_BaseInitStruct.Mode = PWM_MODE_CONTINUOUS;
  PWM_BaseInit(PWM3, &PWM_BaseInitStruct);

  /* PWM3 Channel 0 capture(falling) configuration */
  PWM_ICStructInit(&PWM_ICInitStruct);
  PWM_ICInitStruct.Channel = PWM_CHANNEL_0;
  PWM_ICInitStruct.CaptureMode = PWM_CM_FALLING;
  PWM_ICInit(PWM3, &PWM_ICInitStruct);
  
  /* IOB0 input mode */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_INPUT;
  GPIOBToF_Init(GPIOB, &GPIO_InitStruct);
  /* Configure PWM3 capture input line: PWM0(IOB0) */
  PWM_ILineConfig(PWM3_IN0, PWM_ILINE_0);

  PWM_ClearCounter(PWM3);

  count = 0;

  MISC_IRQLATConfig(15);

  /* Enable PWM3 Channel capture interrupt, PWM3 NVIC interrupt */
  PWM_ClearChannelINTStatus(PWM3, PWM_CHANNEL_0, PWM_INT_CCIFG);
  PWM_ChannelINTConfig(PWM3, PWM_CHANNEL_0, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(PWM3_IRQn, 3);

  test_success = 1;

  while (count < 10)
  {
    WDT_Clear();
  }

  /* Disable PWM3 timer */
  PWM_BaseStructInit(&PWM_BaseInitStruct);
  PWM_BaseInitStruct.Mode = PWM_MODE_STOP;
  PWM_BaseInit(PWM3, &PWM_BaseInitStruct);
  PWM_ChannelINTConfig(PWM3, PWM_CHANNEL_0, DISABLE);
  CORTEX_NVIC_DisableIRQ(PWM3_IRQn);

  for (i=0; i<10; i++)
    printf("CapData[%d]\t%d\r\n", i, CapData[i]);

  while (1)
  {
    WDT_Clear();
  }
}

#ifndef  ASSERT_NDEBUG
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
