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
volatile int16_t bsrc[256][4];

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
  ADC_InitType ADC_InitStruct;
  DMA_InitType DMA_InitStruct;
  GPIO_InitType InitStruct;
  TMR_InitType TMR_InitStruct;
  uint32_t i, nCount;
  
  test_success = 0;
                
  Clock_Init();
  Stdio_Init();
  
  InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
  GPIOA_Init(GPIOA, &InitStruct);
  
    /* Timer0 initialization:
       - Clock source: internal clock(APB clock) 
       - Overflow interval: 1ms                             */
  TMR_DeInit(TMR0);
  TMR_InitStruct.ClockSource = TMR_CLKSRC_INTERNAL;
  TMR_InitStruct.EXTGT = TMR_EXTGT_DISABLE;
  TMR_InitStruct.Period = CLK_GetPCLKFreq()/(128*50) - 1;
  TMR_Init(TMR0, &TMR_InitStruct);
   /* Enable Timer0 */
  TMR_Cmd(TMR0, ENABLE);
  
  /* Ensure AVCC is higher than 2.5V */
  nCount = 0;
  while(1)
  {
    if(!PMU_GetAVCCLVStatus())
    {
      nCount++;
    }
    else
    {
      nCount = 0;
    }
    if(nCount>=10)
    {
      break;
    }
    /* delay 1ms */
    CORTEX_Delay_nSysClock(DELAY_MS(1));
  }
  
  /* ADC DeInit */
  ADC_DeInit();
  
  /* ADC Calibration */
  while(1)
  {
    if(ADC_Calibration()==0)
    {
      break;
    }
  }
  
  /* ADC Init */
  ADC_StructInit(&ADC_InitStruct);
  ADC_InitStruct.Mode = ADC_MODE_AC;
  ADC_InitStruct.ClockSource = ADC_CLKSRC_RCH;
  ADC_InitStruct.SkipSample = ADC_SKIP_0;
  ADC_InitStruct.AverageSample = ADC_AVERAGE_2;
  ADC_InitStruct.TriggerSource = ADC_TRIGSOURCE_TMR0;
  ADC_InitStruct.Channel = ADC_CHANNEL_CH3 \
                         | ADC_CHANNEL_CH4 \
                         | ADC_CHANNEL_CH5 \
                         | ADC_CHANNEL_CH6;
  ADC_InitStruct.AverageEnable = ADC_CHANNEL_CH3 \
                               | ADC_CHANNEL_CH4 \
                               | ADC_CHANNEL_CH5 \
                               | ADC_CHANNEL_CH6;

  ADC_Init(&ADC_InitStruct);
  
  DMA_DeInit(DMA_CHANNEL_0);
  DMA_InitStruct.SrcAddr = (uint32_t)&ANA->ADCDATADMA;
  DMA_InitStruct.DestAddr = (uint32_t)&bsrc[0];
  DMA_InitStruct.FrameLen = 256 - 1;
  DMA_InitStruct.PackLen = 4 - 1;
  DMA_InitStruct.ContMode = DMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = DMA_TRANSMODE_SINGLE;
  DMA_InitStruct.ReqSrc = DMA_REQSRC_ADC;
  DMA_InitStruct.DestAddrMode = DMA_DESTADDRMODE_FEND;
  DMA_InitStruct.SrcAddrMode = DMA_SRCADDRMODE_FIX;
  DMA_InitStruct.TransSize = DMA_TRANSSIZE_HWORD;
  DMA_Init(&DMA_InitStruct, DMA_CHANNEL_0);
  
  DMA_Cmd(DMA_CHANNEL_0, ENABLE);
  
  ADC_Cmd(ENABLE);
  
  while(1)
  {
    if(DMA_GetINTStatus(DMA_INTSTS_C0FE))
    {
      DMA_ClearINTStatus(DMA_INTSTS_C0FE);
      break;
    }
  }
  
  DMA_Cmd(DMA_CHANNEL_0, DISABLE);
  ADC_Cmd(DISABLE);

  printf("CH3\tCH4\tCH5\tCH6\t\r\n");
  for (i=0; i<256; i++)
  {
    printf("%d\t", bsrc[i][0]);
    printf("%d\t", bsrc[i][1]);
    printf("%d\t", bsrc[i][2]);
    printf("%d\r\n", bsrc[i][3]);
  }

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
