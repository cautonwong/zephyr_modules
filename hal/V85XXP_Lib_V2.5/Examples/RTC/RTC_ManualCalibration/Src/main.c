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
  * @brief  Get_Temperature:
  * @param  [out]T:  The pointer of temperature value got by this function
  * @retval 1  Function error.
            0  Function successed.
 
  */
uint32_t Get_Temperature(int16_t *T)
{
  ADC_InitType ADC_InitStruct;
  int16_t adc_data;
  
  /* ADC interface initialization */
  ADC_StructInit(&ADC_InitStruct);
  ADC_InitStruct.Mode = ADC_MODE_TEMP;
  ADC_InitStruct.ClockSource = ADC_CLKSRC_RCH;
  ADC_InitStruct.SkipSample = ADC_SKIP_4;
  ADC_InitStruct.AverageSample = ADC_AVERAGE_64;
  ADC_InitStruct.TriggerSource = ADC_TRIGSOURCE_OFF;
  ADC_InitStruct.Channel = ADC_CHANNEL_TEMP;
  ADC_InitStruct.AverageEnable = ADC_CHANNEL_TEMP;
  ADC_InitStruct.ResDivEnable = ADC_CHANNEL_NONE;
  ADC_Init(&ADC_InitStruct);

  /* Enable ADC */
  ADC_Cmd(ENABLE);
 

  /* Start Manual ADC conversion */
  ADC_StartManual();
  /* Waiting Manual ADC conversion done */
  if(ADC_WaitForManual(DELAY_MS(100)))
  {
    /*Reset ADC*/
    while(ADC_SoftReset(&ADC_InitStruct)!=0);
  }
  else
  {
    /* Get ADC data */
    adc_data = ADC_GetADCConversionValue(ADC_CHANNEL_TEMP);

  /*-------------------------- Manual calibration  -----------------------------*/
    /* Get temperature original data */
    if (ADC_CalculateValue(ADC_TEMP, adc_data, T))
    {
      return 1;
    }
  }
  
  /* Disable ADC */
  ADC_Cmd(DISABLE);
    
  return 0;
}

void CalRTC(uint32_t rtcplldivsrc, int16_t T)
{
  uint32_t cal_value, div_value;
  int16_t ack_used, PPMx10;
  int16_t ktemp0, ktemp1, ktemp2, ktemp3;
  int16_t Ti;
  
  /* Get section x temperature */
  ktemp0 = (int16_t)(RTC->ACKTEMP<<8 & 0xFF00);
  ktemp1 = (int16_t)((RTC->ACKTEMP ) & 0xFF00);
  ktemp2 = (int16_t)((RTC->ACKTEMP >> 8) & 0xFF00);
  ktemp3 = (int16_t)((RTC->ACKTEMP >> 16) & 0xFF00);

  /* Calculate temperature(float) */
  Ti = RTC->ACTI;

  /* Get ACK(K parameter) */
  if (T < ktemp0)
    ack_used = RTC->ACK[0];
  else if ((T >= ktemp0) && (T < ktemp1))
    ack_used = RTC->ACK[1];
  else if ((T >= ktemp1) && (T < ktemp2))
    ack_used = RTC->ACK[2];
  else if ((T >= ktemp2) && (T < ktemp3))
    ack_used = RTC->ACK[3];
  else  
    ack_used = RTC->ACK[4];
  
  /* Calculate 10*PPM */
  PPMx10 = (int16_t)((((ack_used)*(((T-Ti)*(T-Ti))>>16))>>16) + (int16_t)(RTC->ACP4));
  /* Calculate the value of RTC_CAL, RTC_DIV */
  cal_value = (uint32_t)((((PPMx10*(int16_t)(RTC->ACP5))>>16)) + 1);
  div_value = (uint32_t)((rtcplldivsrc>>1) - ((PPMx10*(int16_t)(RTC->ACP6))>>12) - 1);    

  /* Write RTC_CAL/RTC_DIV register */
  RTC_WriteRegisters((uint32_t)&RTC->CAL, &cal_value, 1);
  RTC->DIV = div_value;
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  NVR_RTCINFO RTCData;
  TMR_InitType TMR_InitStruct;
  uint32_t retval;
  int16_t T;
  uint32_t nCount;
  uint32_t rtcplldivsrc = 26214400UL;

  test_success = 0;
                
  Clock_Init();
  Stdio_Init();

/*------------------------- RTC PLL divider output ---------------------------*/
  /* Enable RTC PLL divider output, IOA3 IOA7 */
  GPIOA_AFConfig(PMUIO7_AF_PLLDIV | PMUIO3_AF_PLLDIV, ENABLE);
  RTC_PLLDIVConfig(RTC_PLLDIVSOURCE_PLLL, 1);
  RTC_PLLDIVOutputCmd(ENABLE);

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
  
  
  /* Get/load RTC NVR information */
  retval = NVR_GetInfo_LoadRTCData(&RTCData, rtcplldivsrc);
  if (retval)
  {
#ifdef __GNUC__
    printf("Get/load RTC NVR information error, return value 0x%lx\r\n", retval);
#else
    printf("Get/load RTC NVR information error, return value 0x%x\r\n", retval);
#endif
  }
  else
  {  
    printf("Get/load RTC NVR information OK!\r\n");
  }  

  /* Timer0 initialization:
       - Clock source: internal clock(APB clock 13107200Hz) 
       - Overflow interval: 5s */
  TMR_DeInit(TMR0);
  TMR_InitStruct.ClockSource = TMR_CLKSRC_INTERNAL;
  TMR_InitStruct.EXTGT = TMR_EXTGT_DISABLE;
  TMR_InitStruct.Period = 13107200*5 - 1;
  TMR_Init(TMR0, &TMR_InitStruct);
  /* Enable Timer0 */
  TMR_Cmd(TMR0, ENABLE);

  while (1)
  {
/*-------------------------- Manual calibration  -----------------------------*/
  /* Get temperature */
    if (Get_Temperature(&T))
    {
      printf("Calculate temperature, checksum error\r\n");
    }
    /* Calibrate RTC_CAL RTC_DIV */
    CalRTC(rtcplldivsrc, T);

    printf("Temperature is %2.3f\r\n", (float)T/256.0);
#ifdef __GNUC__
    printf("DIV 0x%lx\r\n", RTC->DIV);
    printf("CAL 0x%lx\r\n", RTC->CAL);
#else    
    printf("DIV 0x%x\r\n", RTC->DIV);
    printf("CAL 0x%x\r\n", RTC->CAL);
#endif
    printf("\r\n");    

    test_success = 1; 
    
    /* Delay 5s */
    while (TMR_GetINTStatus(TMR0) == 0)
    {
      WDT_Clear();
    }
    TMR_ClearINTStatus(TMR0);
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
