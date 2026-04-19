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
volatile int g_nCount;
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
  TADCInitType TADC_InitStruct;
  GPIO_InitType GPIO_InitStruct;
  uint32_t i;

  test_success = 0;

  g_nCount = 0;
  
  Clock_Init();
  Stdio_Init();
  printf("ADCTiny test. \r\n");
  
  TADC_INTConfig(DISABLE);
  
  /* Forbidden Tiny ADC input pin, IOE6 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIOBToF_Init(GPIOE, &GPIO_InitStruct);
  
  /* Tiny ADC initialization */
  TADC_DeInit();
  TADC_InitStruct.SignalSel = ADCTINY_SIGNALSEL_IOE6;
  TADC_InitStruct.ADTREF1 = ADCTINY_REF1_0_9;
  TADC_InitStruct.ADTREF2 = ADCTINY_REF2_1_8;
  TADC_InitStruct.ADTREF3 = ADCTINY_REF3_2_7;
  TADC_Init(&TADC_InitStruct);


  /* Enable Tiny ADC */
  TADC_Cmd(ENABLE);
  for(i=0; i<800; i++)
  {
    __NOP();
  }
  
  TADC_IntTHConfig(ADCTINY_THSEL_1);
  for(i=0; i<800; i++)
  {
    __NOP();
  }
  TADC_ClearINTStatus();
  TADC_INTConfig(ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(ANA_IRQn, 3);

  test_success = 1;
  
  while(1)
  {
    WDT_Disable();
    Stdio_Init();
    printf("Tiny ADC interrupt, nCount: %d\r\n", g_nCount);
    printf("CMPOUT: %d. \r\n", TADC_GetOutput());
    if (PMU_EnterSleepMode())
    {
      printf("Current mode is debug mode, failed\r\n");
    }
    else
    {
      printf("Quit sleep mode\r\n");
    }
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
