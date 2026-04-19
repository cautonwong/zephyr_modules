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
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  GPIO_InitType GPIO_InitStruct;
  CMP_TypeDef InitStruct;
  CMP_CountTypeDef CountInitStruct;
  CMP_INTTypeDef INTInitStruct;
  CMP_OutputTypeDef OutputInitStruct;

  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  /* Forbidden Comparator2 N input pin, IOA5 */
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
  GPIOA_Init(GPIOA, &GPIO_InitStruct); 

  CMP_DeInit(CMP_2);
  CMP_StructInit(&InitStruct);
  InitStruct.DebSel = CMP_DEB_RTCCLK_2; /* 2 32KHz de-bounce */
  InitStruct.SignalSourceSel = CMP_SIGNALSRC_NPIN_TO_BGPREF; /* Compare N to BGP refence(1.2V) */
  CMP_Init(CMP_2, &InitStruct);
  
  CMP_CountStructInit(&CountInitStruct);
  CountInitStruct.ModeSel = CMP_MODE_RISING; /* Rising edge */
  CountInitStruct.CheckPeriod = CMP_PERIOD_7_8125MS; /* Checked every 7.8125ms */ 
  CountInitStruct.CheckNum = CMP_CHKNUM_4; /* Checked data 4 times */
  CMP_CountInit(CMP_2, &CountInitStruct);

 /* Comparator interrupt enable control. */
  CMP_INTStructInit(&INTInitStruct);
  INTInitStruct.INTNumSel = CMP_INTNUM_1;
  INTInitStruct.SubSel = CMP_COUNT_SUB;
  INTInitStruct.THRNum = 10;
  CMP_INTInit(CMP_2, &INTInitStruct);
  
  CMP_INTConfig(CMP_2, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(ANA_IRQn, 0);
  
  CMP_OutputStructInit(&OutputInitStruct);
  OutputInitStruct.DebSel = CMP_OUTPUT_DEB;
  OutputInitStruct.OutputSel = ENABLE; /* Enable Comparator2(output on IOA6) */
  CMP_OutputInit(CMP_2, &OutputInitStruct);

  PMU_BGPCmd(ENABLE);
  CMP_Cmd(CMP_2, ENABLE);

  test_success = 1;
  
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
