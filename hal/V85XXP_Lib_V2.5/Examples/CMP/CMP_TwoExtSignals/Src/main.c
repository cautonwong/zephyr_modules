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
  
  /* Forbidden Comparator1 input pins:
         - P input, IOE8
         - N input, IOE9              */
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIOBToF_Init(GPIOE, &GPIO_InitStruct);

  CMP_DeInit(CMP_1);
  CMP_StructInit(&InitStruct);
  InitStruct.DebSel = CMP_DEB_RTCCLK_2; /* 2 32KHz de-bounce */
  InitStruct.SignalSourceSel = CMP_SIGNALSRC_PPIN_TO_NPIN; /* Compare P to N */
  CMP_Init(CMP_1,&InitStruct);

  PMU_BGPCmd(ENABLE);

  CMP_CountStructInit(&CountInitStruct);
  CountInitStruct.ModeSel = CMP_MODE_RISING; /* Rising edge */
  CountInitStruct.CheckPeriod = CMP_PERIOD_7_8125MS; /* Checked every 7.8125ms */ 
  CountInitStruct.CheckNum = CMP_CHKNUM_4; /* Checked data 4 times */
  CMP_CountInit(CMP_1, &CountInitStruct);
  
  /* Comparator interrupt enable control. */
  CMP_INTStructInit(&INTInitStruct);
  INTInitStruct.INTNumSel = CMP_INTNUM_1;
  INTInitStruct.SubSel = CMP_COUNT_NOSUB;
  INTInitStruct.THRNum = 9;
  CMP_INTInit(CMP_1, &INTInitStruct);
  
  CMP_INTConfig(CMP_1, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(ANA_IRQn, 0);

  /* CMP2 output, IOE7 */
  CMP_OutputStructInit(&OutputInitStruct);
  OutputInitStruct.DebSel = CMP_OUTPUT_DEB;
  OutputInitStruct.OutputSel = ENABLE;
  CMP_OutputInit(CMP_1, &OutputInitStruct);

  /* Enable Comparator1 */
  CMP_Cmd(CMP_1, ENABLE);
  CMP_ClearCNTValue(CMP_1);
  
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
