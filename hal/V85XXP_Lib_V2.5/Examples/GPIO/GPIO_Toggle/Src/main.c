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

/* Private functions ---------------------------------------------------------*/

__IO uint32_t delay_cycles;

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
  GPIO_InitType GPIO_InitStruct;

  test_success = 0;

  Clock_Init();
  
  /* De-initialization UART, UART5 transmit pin(IOB7) as GPIO */
  UART_DeInit(UART5);
  
  /* Configure IOB7, output CMOS mode */
  GPIO_WriteBit(GPIO_B, 7, 0);
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUTPUT_CMOS;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIOBToF_Init(GPIOB, &GPIO_InitStruct);

  test_success = 1;
  
  while (1)
  {
    /* Uncertain delay, set IOB7 */
    for (delay_cycles=0; delay_cycles<10000; delay_cycles++);
    GPIO_WriteBit(GPIO_B, 7, 1);
    
    /* Uncertain delay, reset IOB7 */
    for (delay_cycles=0; delay_cycles<10000; delay_cycles++);
    GPIO_WriteBit(GPIO_B, 7, 0);
    
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
