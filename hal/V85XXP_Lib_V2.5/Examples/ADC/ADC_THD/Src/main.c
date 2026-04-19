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
  ADC_InitType ADC_InitStruct;
  ADCTHD_InitType ADC_THDStruct;
  GPIO_InitType InitStruct;
  int16_t nResult;
  uint32_t nCount;
  int16_t ADCData[4] = { 0 };
  
  test_success = 0;
                
  Clock_Init();
  Stdio_Init();
  
  InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIOA_Init(GPIOA, &InitStruct);
  
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
  ADC_InitStruct.Channel = ADC_CHANNEL_BAT1 \
                         | ADC_CHANNEL_BATRTC \
                         | ADC_CHANNEL_CH3 \
                         | ADC_CHANNEL_CH4;
  ADC_InitStruct.AverageEnable = ADC_CHANNEL_BAT1 \
                               | ADC_CHANNEL_BATRTC \
                               | ADC_CHANNEL_CH3 \
                               | ADC_CHANNEL_CH4;
  ADC_InitStruct.ResDivEnable = ADC_CHANNEL_BAT1|ADC_CHANNEL_BATRTC;
  ADC_Init(&ADC_InitStruct);
  
  ADC_Cmd(ENABLE);
  
  /* Manual mode */
  ADC_StartManual();
  if(ADC_WaitForManual(DELAY_MS(100)))
  {
    /*Reset ADC*/
    while(ADC_SoftReset(&ADC_InitStruct)!=0);
  }
  else
  {
    ADCData[0] = ADC_GetADCConversionValue(ADC_CHANNEL_BAT1);
    if(ADC_CalculateValue(ADC_5V_BAT1_RESDIV, ADCData[0], &nResult))
    {
      printf("NVR checksum error.\r\n");
    }
    else
    {
      printf("BAT1 is 0x%X %.3fV.\r\n", ADCData[0], (float)nResult/1000.0);
    }
    ADCData[1] = ADC_GetADCConversionValue(ADC_CHANNEL_BATRTC);
    if(ADC_CalculateValue(ADC_5V_BATRTC_RESDIV, ADCData[1], &nResult))
    {
      printf("NVR checksum error.\r\n");
    }
    else
    {
      printf("BATRTC is 0x%X %.3fV.\r\n", ADCData[1], (float)nResult/1000.0);
    }
    ADCData[2] = ADC_GetADCConversionValue(ADC_CHANNEL_CH4);
    if(ADC_CalculateValue(ADC_5V_ADCCHx_NODIV, ADCData[2], &nResult))
    {
      printf("NVR checksum error.\r\n");
    }
    else
    {
      printf("CH4 is 0x%X %.3fC.\r\n", ADCData[2], (float)nResult/1000.0);
    }
    ADCData[3] = ADC_GetADCConversionValue(ADC_CHANNEL_CH3);
    if(ADC_CalculateValue(ADC_5V_ADCCHx_NODIV, ADCData[3], &nResult))
    {
      printf("NVR checksum error.\r\n");
    }
    else
    {
      printf("CH3 is 0x%X %.3fV.\r\n", ADCData[3], (float)nResult/1000.0);
    }
  }  
  
  ADC_Cmd(DISABLE);
  
  ADC_THDStructInit(&ADC_THDStruct);
  ADC_THDStruct.THDChannel = ADC_THDCHANNEL0;
  ADC_THDStruct.THDSource = ADC_CHANNEL_BAT1;
  ADC_THDStruct.TriggerSel = ADC_THDSEL_RISING;
  ADC_THDStruct.LowerTHD = (ADCData[0]>>8)-0x10;
  ADC_THDStruct.UpperTHD = (ADCData[0]>>8)+0x10;
  if(ADC_THDStruct.UpperTHD&0x80)
  {
    ADC_THDStruct.UpperTHD = 0x7F;
  }
  ADC_THDInit(&ADC_THDStruct);
  
  ADC_THDStruct.THDChannel = ADC_THDCHANNEL1;
  ADC_THDStruct.THDSource = ADC_CHANNEL_BATRTC;
  ADC_THDStruct.TriggerSel = ADC_THDSEL_RISING;
  ADC_THDStruct.LowerTHD = (ADCData[1]>>8)-0x10;
  ADC_THDStruct.UpperTHD = (ADCData[1]>>8)+0x10;
  if(ADC_THDStruct.UpperTHD&0x80)
  {
    ADC_THDStruct.UpperTHD = 0x7F;
  }
  ADC_THDInit(&ADC_THDStruct);
  
  ADC_THDStruct.THDChannel = ADC_THDCHANNEL2;
  ADC_THDStruct.THDSource = ADC_CHANNEL_CH4;
  ADC_THDStruct.TriggerSel = ADC_THDSEL_RISING;
  ADC_THDStruct.LowerTHD = (ADCData[2]>>8)-0x10;
  ADC_THDStruct.UpperTHD = (ADCData[2]>>8)+0x10;
  if(ADC_THDStruct.UpperTHD&0x80)
  {
    ADC_THDStruct.UpperTHD = 0x7F;
  }
  ADC_THDInit(&ADC_THDStruct);

  ADC_THDStruct.THDChannel = ADC_THDCHANNEL3;
  ADC_THDStruct.THDSource = ADC_CHANNEL_CH3;
  ADC_THDStruct.TriggerSel = ADC_THDSEL_RISING;
  ADC_THDStruct.LowerTHD = (ADCData[3]>>8)-0x10;
  ADC_THDStruct.UpperTHD = (ADCData[3]>>8)+0x10;
  if(ADC_THDStruct.UpperTHD&0x80)
  {
    ADC_THDStruct.UpperTHD = 0x7F;
  }
  ADC_THDInit(&ADC_THDStruct);
  
  /* Auto mode */
  ADC_InitStruct.TriggerSource = ADC_TRIGSOURCE_ITVSITV;
  ADC_Init(&ADC_InitStruct);
  
  RTC_WAKE_SITV(1);
  
  ADC_ClearINTStatus(ADC_INTSTS_UPPER_TH3 | ADC_INTSTS_LOWER_TH3 \
                   | ADC_INTSTS_UPPER_TH2 | ADC_INTSTS_LOWER_TH2 \
                   | ADC_INTSTS_UPPER_TH1 | ADC_INTSTS_LOWER_TH1 \
                   | ADC_INTSTS_UPPER_TH0 | ADC_INTSTS_LOWER_TH0);  
  ADC_INTConfig(ADC_INT_UPPER_TH3 | ADC_INT_LOWER_TH3 \
              | ADC_INT_UPPER_TH2 | ADC_INT_LOWER_TH2 \
              | ADC_INT_UPPER_TH1 | ADC_INT_LOWER_TH1 \
              | ADC_INT_UPPER_TH0 | ADC_INT_LOWER_TH0, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(ANA_IRQn, 0);
  
  ADC_LowerTHDCmd(ADC_THDCHANNEL0, ENABLE);
  ADC_UpperTHDCmd(ADC_THDCHANNEL0, ENABLE);
  ADC_LowerTHDCmd(ADC_THDCHANNEL1, ENABLE);
  ADC_UpperTHDCmd(ADC_THDCHANNEL1, ENABLE);
  ADC_LowerTHDCmd(ADC_THDCHANNEL2, ENABLE);
  ADC_UpperTHDCmd(ADC_THDCHANNEL2, ENABLE);
  ADC_LowerTHDCmd(ADC_THDCHANNEL3, ENABLE);
  ADC_UpperTHDCmd(ADC_THDCHANNEL3, ENABLE);
  ADC_Cmd(ENABLE); 

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
