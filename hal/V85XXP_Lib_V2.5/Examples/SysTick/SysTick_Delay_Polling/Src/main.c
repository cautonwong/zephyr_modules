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
  * @brief  Delay N system-clock cycle.
  * @param  nClock < 0x1000000
  * @retval None
  */
void Delay_nSysClock(__IO uint32_t nClock)
{
  uint32_t tmp;
  
  SysTick->LOAD = nClock - 1;
  SysTick->VAL  = 0; 
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk \
                 |SysTick_CTRL_ENABLE_Msk;
  
  do
  {
    tmp = SysTick->CTRL;
  }
  while (!(tmp & SysTick_CTRL_COUNTFLAG_Msk));
  
  SysTick->CTRL = 0;
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
  
  /* IOB7 CMOS-Output mode */
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUTPUT_CMOS;
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7;
  GPIOBToF_Init(GPIOB, &GPIO_InitStruct);

  test_success = 1;
  
  while (1)
  {
    /* Toggle IOB7, 10ms */
    Delay_nSysClock(26214400/100);
    GPIO_WriteBit(GPIO_B, 7, 1);
    Delay_nSysClock(26214400/100);
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
