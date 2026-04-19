/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private functions ---------------------------------------------------------*/

volatile unsigned char test_success;

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
  test_success = 0;
                
  Clock_Init();
  Stdio_Init();

  /* AVCC Lower Power Detector ENABLE */
  PMU_AVCCCmd(ENABLE);
  PMU_AVCCLVDetectorCmd(ENABLE);

  /* Clear AVCCLV interrupt flag */
  ANA_ClearINTStatus(ANA_INT_AVCCLV);
  /* Enable AVCCLV interrupt, ANA NVIC interrupt */
  ANA_INTConfig(ANA_INT_AVCCLV, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(ANA_IRQn, 0);

  test_success = 1; 

  /* Disable WDT, enter sleep mode */
  printf("Enter sleep mode\r\n");
  WDT_Disable();
  if (PMU_EnterSleepMode())
  {
    printf("Enter sleep fail\r\n"); 
    while (1);    
  }

  /* Quit sleep mode, Clock initialization */
  Clock_Init();
  Stdio_Init();
  printf("Exit sleep mode\r\n");

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
