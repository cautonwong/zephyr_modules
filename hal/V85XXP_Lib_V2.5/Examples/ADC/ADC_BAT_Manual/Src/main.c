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
#include "target.h"                     // Device header

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
  uint32_t i, nCount;
  int16_t ADCData;
  int16_t nResult;
  
  test_success = 0;
                
  Clock_Init();
  
  Stdio_Init();
  printf("Start test.\r\n");
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
  ADC_InitStruct.Mode = ADC_MODE_DC;
  ADC_InitStruct.ClockSource = ADC_CLKSRC_RCH;
  ADC_InitStruct.SkipSample = ADC_SKIP_4;
  ADC_InitStruct.AverageSample = ADC_AVERAGE_4;
  ADC_InitStruct.TriggerSource = ADC_TRIGSOURCE_OFF;
  ADC_InitStruct.Channel = ADC_CHANNEL_BAT1|ADC_CHANNEL_BATRTC;
  ADC_InitStruct.AverageEnable = ADC_CHANNEL_BAT1|ADC_CHANNEL_BATRTC;
  ADC_InitStruct.ResDivEnable = ADC_CHANNEL_BAT1|ADC_CHANNEL_BATRTC;
  ADC_Init(&ADC_InitStruct);
  
  ADC_Cmd(ENABLE);
  
  /* Get ADC Value */
  for(i=0; i<32; i++)
  {
    ADC_StartManual();
    if(ADC_WaitForManual(DELAY_MS(100)))
    {
      /*Reset ADC*/
      while(ADC_SoftReset(&ADC_InitStruct)!=0);
    }
    else
    {     
      ADCData = ADC_GetADCConversionValue(ADC_CHANNEL_BAT1);
      if(ADC_CalculateValue(ADC_5V_BAT1_RESDIV, ADCData, &nResult))
      {
        printf("NVR checksum error.\r\n");
      }
      else
      {
        printf("BAT1 is %.3fV.\t", (float)nResult/1000.0);
      }
      ADCData = ADC_GetADCConversionValue(ADC_CHANNEL_BATRTC);
      if(ADC_CalculateValue(ADC_5V_BATRTC_RESDIV, ADCData, &nResult))
      {
        printf("NVR checksum error.\r\n");
      }
      else
      {
        printf("BATRTC is %.3fV.\r\n", (float)nResult/1000.0);
      } 
    }
  }
  
  ADC_Cmd(DISABLE);
  
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
