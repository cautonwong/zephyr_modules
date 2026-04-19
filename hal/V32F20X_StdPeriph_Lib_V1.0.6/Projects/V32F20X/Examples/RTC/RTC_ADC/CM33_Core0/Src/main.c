/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-05
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {
  int16_t RTC_ACP0;  /*auto-calibration parameter 0*/
  int16_t RTC_ACP1;  /*auto-calibration parameter 1*/
  int32_t RTC_ACP2;  /*auto-calibration parameter 2*/
}RTCINFOParaType;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief Calculates checksum
  * @param Data: data used for checksum calculation
  * @param DataLen: data length
  * @retval checksum
  */
static uint32_t CheckSumCalc(uint32_t *Data, uint32_t DataLen)
{
  uint32_t i;
  uint32_t Sum = 0;

  for(i = 0; i < DataLen; i++)
  {
    Sum += Data[i];
  }

  return (~Sum);
}


/**
  * @brief  Loads parameters related with teperature calculation from FLASH0 INFO0 memory
  * @param  Param: pointer to a RTCINFOParaType structure
  * @retval None
  */
static void RTC_FlashINFOParaLoad(RTCINFOParaType *Param)
{
  uint32_t ACPParamAndChecksum[5];
  uint32_t TrTmAndCheckSum[3];
  uint32_t Checksum1, CheckSum2;
  /*
   * Address 0             
   *        offset 0        P1 P0,RTC data 1/0  set 1     p0+(p1<<16) 
   *        offset 4        P2, RTC data 2  set 1         p2
   *        offset 8        P5 P4, RTC data 5/4  set 1    p4+(p5<<16)
   *        offset 0x0C     P7 P6,RTC data 7/6  set 1    (P6 + P7<<16)
   *        offset 0x10     Check Sum                    INV(SUM(0x00, 0x0C))
   */
  /* read 20 bytes*/
  FLASH_INFO0ReadWord(FLASH0, 0, ACPParamAndChecksum, 5);
  Checksum1 = CheckSumCalc(ACPParamAndChecksum, 4);

  /*
   * Address 0             
   *        offset 0x4C     Real Temperature 1            Tr
   *        offset 0x50     Measured Temperature 1        Tm
   *        offset 0x54     Checksum                      INV(SUM(0x4C, 0x50))
   */
  FLASH_INFO0ReadWord(FLASH0, 0x4C, TrTmAndCheckSum, 3);
  CheckSum2 = CheckSumCalc(TrTmAndCheckSum, 2);

  if(Checksum1 == ACPParamAndChecksum[4]
     && CheckSum2 == TrTmAndCheckSum[2])
  {
    Param->RTC_ACP0  = (int16_t)ACPParamAndChecksum[0]; 
    Param->RTC_ACP1  = (int16_t)(ACPParamAndChecksum[0]>>16);
    Param->RTC_ACP2  = (int32_t)ACPParamAndChecksum[1] 
                       + ((int32_t)TrTmAndCheckSum[0] - (int32_t)TrTmAndCheckSum[1])*256;
    return;
  }

  /*
   * Address 0x1000             
   *        offset 0        P1 P0,RTC data 1/0  set 2     p0+(p1<<16) 
   *        offset 4        P2, RTC data 2  set 2         p2
   *        offset 8        P5 P4, RTC data 5/4  set 2    p4+(p5<<16)
   *        offset 0x0C     P7 P6,RTC data 7/6  set 2    (P6 + P7<<16)
   *        offset 0x10     Check Sum                    INV(SUM(0x00, 0x0C))
   */
  /* read 20 bytes*/
  FLASH_INFO0ReadWord(FLASH0, 0x1000, ACPParamAndChecksum, 5);
  Checksum1 = CheckSumCalc(ACPParamAndChecksum, 4);

  /*
   * Address 0x1000             
   *        offset 0x4C     Real Temperature 2            Tr
   *        offset 0x50     Measured Temperature 2        Tm
   *        offset 0x54     Checksum                      INV(SUM(0x4C, 0x50))
   */
  FLASH_INFO0ReadWord(FLASH0, 0x104C, TrTmAndCheckSum, 3);
  CheckSum2 = CheckSumCalc(TrTmAndCheckSum, 2);

  if(Checksum1 == ACPParamAndChecksum[4]
     && CheckSum2 == TrTmAndCheckSum[2])
  {
    Param->RTC_ACP0  = (int16_t)ACPParamAndChecksum[0]; 
    Param->RTC_ACP1  = (int16_t)(ACPParamAndChecksum[0]>>16);
    Param->RTC_ACP2  = (int32_t)ACPParamAndChecksum[1] 
                       + ((int32_t)TrTmAndCheckSum[0] - (int32_t)TrTmAndCheckSum[1])*256;
  }
}


/**
  * @brief  Initializes ACP parameters with default value
  * @param  ACPParam: pointer to a RTCINFOParaType structure
  * @retval None
  */
static void RTC_ACPParamInit(RTCINFOParaType *ACPParam)
{
  ACPParam->RTC_ACP0  = 58; 
  ACPParam->RTC_ACP1  = 874;
  ACPParam->RTC_ACP2  = -17611857;
}


/**
  * @brief  Gets one-shot RTC ADC conversion value
  * @param  None
  * @retval conversion value
  */
static int16_t RTC_ADC_GetOneShotConversionValue(void)
{
  int16_t ConvValue;
  RTC_ADC_InitType  RTC_AdcStruct;
  
  RTC_ADC_StructInit(&RTC_AdcStruct);
  RTC_AdcStruct.Channel = RTC_ADC_CHANNEL_TEMP;
  RTC_AdcStruct.ClockDivider  = RTC_ADC_CLKDIV_2;
  RTC_AdcStruct.AverageEnable = RTC_ADC_AVERAGE_ENABLE;
  RTC_AdcStruct.AverageSample = RTC_ADC_AVERAGE_64;
  RTC_ADC_Init(&RTC_AdcStruct);
  
  RTC_ADC_StartManual();
  /* wait for conversion done*/
  while(RTC_ADC_GetConvValidFlagStatus() == RESET);
  RTC_ADC_ClearConvValidFlag();
  ConvValue = RTC_ADC_GetConvValue();

  return ConvValue;
}

/**
  * @brief Calculates temperature.
  * @param ACPParam: pointer to a RTCINFOParaType structure
  * @param ConvValue: RTC ADC conversion value
  * @retval Temperature
  */
static int16_t RTC_TemperatureCalc(RTCINFOParaType *ACPParam, int16_t ConvValue)
{
  float temp0, temp1, temp2;
  int16_t Temperature;

  temp0 = ACPParam->RTC_ACP0;
  temp1 = ACPParam->RTC_ACP1;
  temp2 = ACPParam->RTC_ACP2;

  /* Temperature =((P0*((X*X)>>16) + P1*X + P2)>>8 */
  temp0 = temp0*ConvValue*ConvValue/65536.0;
  temp1 = temp1*ConvValue;

  temp0 = temp0 + temp1 + temp2;
  Temperature = (int16_t)(temp0/256.0);

  return Temperature;
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  RTCINFOParaType ACPParam;
  int16_t ConvValue;
  int16_t Temperature;

  /* V32F20xxx CM33 core0 STD library initialization:
       - Systick timer is configured by default as source of time base, but user()
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Set NVIC Group Priority to 3
       - Low Level Initialization
     */
  STD_Init(CLK_GetHCLK0Freq());

  /* RCH(48M) enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOLState = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_NONE;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_NONE;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  BSP_Printf_Init();

  RTC_ACPParamInit(&ACPParam);

  RTC_FlashINFOParaLoad(&ACPParam);

  ConvValue = RTC_ADC_GetOneShotConversionValue();

  Temperature = RTC_TemperatureCalc(&ACPParam, ConvValue);

  printf("current temperature: %.2f degrees\r\n", (float)Temperature/256.0);

  /* Infinite loop */
  while (1)
  {

  }
}


/**
  * @brief  Initialize the Low level.
  * @retval None
  */
void STD_lowInit(void)
{
  /* nothing to do */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the STD error return state */
  while(1)
  {
  }
}

#ifdef  ASSERT_ENABLED
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
