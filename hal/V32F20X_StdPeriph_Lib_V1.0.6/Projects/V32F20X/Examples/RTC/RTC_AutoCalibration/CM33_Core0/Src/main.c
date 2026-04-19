/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-05
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

volatile uint32_t RTC_AutoCalDoneFlag;

/* Private typedef -----------------------------------------------------------*/
typedef struct {
  int16_t RTC_ACP0;  /*auto-calibration parameter 0*/
  int16_t RTC_ACP1;  /*auto-calibration parameter 1*/
  int32_t RTC_ACP2;  /*auto-calibration parameter 2*/
  int16_t RTC_ACP3;  /*auto-calibration parameter 3*/
  int16_t RTC_ACP4;  /*auto-calibration parameter 4*/
  int16_t RTC_ACP5;  /*auto-calibration parameter 5*/
  int16_t RTC_ACP6;  /*auto-calibration parameter 6*/
  int16_t RTC_ACP7;  /*auto-calibration parameter 7*/
  
  int16_t RTC_K1;    /* Auto-calibration K1 */
  int16_t RTC_K2;    /* Auto-calibration K2 */
  int16_t RTC_K3;    /* Auto-calibration K3 */
  int16_t RTC_K4;    /* Auto-calibration K4 */
  int16_t RTC_K5;    /* Auto-calibration K5 */
  
  uint16_t RTC_TI;    /*Auto-calibration center temperature*/
  uint32_t RTC_KTEMP; /*Auto-calibration temperature section*/
}RTCINFOParaType;

/* Private define ------------------------------------------------------------*/
#define RTC_AutoCalibrationDone        1
#define RTC_AutoCalibrationNotDone     0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void NVIC_EnableRTCIRQ(void);
static void NVIC_DisableRTCIRQ(void);
static void RTC_FlashINFOParaLoad(RTCINFOParaType *Param);
static void RTC_ACPParamInit(RTCINFOParaType *ACPParam);
static void RTC_AutoCaliParamConfig(RTCINFOParaType* Param, uint32_t RTC_pclk);
static void RTCALM_HighFreqSPOutputCmd(FunctionalState NewState);


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  RTCINFOParaType ACPParam;
  RTC_ADC_InitType  RTC_AdcStruct;
  RTC_AutoCalType RTC_AutoCaliStruct;
  uint32_t AutoCalibrationCnt = 0;

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
  
  SystemClock_Config();
  /* select XOL 32768Hz */
  RTCEx_ClkSRCConfig(RTC_CLKSRC_32KXTAL);
  SYSCFGLP_PeriphClockCmd(SYSCFGLP_PeriphClock_RTC_ALARM, ENABLE);

  BSP_Printf_Init();

  RTC_ACPParamInit(&ACPParam);
  RTC_FlashINFOParaLoad(&ACPParam);
  
  printf("Auto-calibration starts, please prepare for caputuring second pulse on PI0!\r\n");

  /* disable auto-calbration */
  RTC_AutoCalCmd(DISABLE);
  RTC_AutoCalDoneFlag = RTC_AutoCalibrationNotDone;

  /* Initialize RTC ADC */
  RTC_ADC_StructInit(&RTC_AdcStruct);
  RTC_AdcStruct.Channel = RTC_ADC_CHANNEL_TEMP;
  RTC_AdcStruct.ClockDivider  = RTC_ADC_CLKDIV_2;
  RTC_AdcStruct.AverageEnable = RTC_ADC_AVERAGE_ENABLE;
  RTC_AdcStruct.AverageSample = RTC_ADC_AVERAGE_64;
  RTC_ADC_Init(&RTC_AdcStruct);

  /* configure parameters for auto-calibration */
  RTC_AutoCaliParamConfig(&ACPParam, 61440000); /* PLL1 frequency is 61.44MHz */
  RTC_AutoCalStructInit(&RTC_AutoCaliStruct);
  RTC_AutoCaliStruct.ADCJudgeCmd =  DISABLE;
  RTC_AutoCaliStruct.AutoTrigUnit = RTC_ACAutoTrigUnit_Sec;  /* time unit is second */
  RTC_AutoCaliStruct.AutoTrigPeriod = 1;  /* period is 2 seconds, 30s is a recommended period */
  RTC_AutoCaliStruct.DataSource = RTC_ACDataSource_Hardware;
  
  RTC_AutoCalInit(&RTC_AutoCaliStruct);
  RTC_ClearINTStatus(RTC_INT_ACDONE);
  RTC_INTConfig(RTC_INT_ACDONE, ENABLE);
  NVIC_EnableRTCIRQ();
  RTC_AutoCalCmd(ENABLE);

  /* do 5 rounds */
  while(AutoCalibrationCnt < 5)
  {
    /* Auto-calibration is finished */
    while(RTC_AutoCalDoneFlag == RTC_AutoCalibrationNotDone);
    RTC_AutoCalDoneFlag = RTC_AutoCalibrationNotDone;
    AutoCalibrationCnt++;
    if(AutoCalibrationCnt == 1)
    {
      /* enable ouput of 1Hz periodic pulse */
      RTCALM_HighFreqSPOutputCmd(ENABLE);
    }

    printf("round %d auto-calibration is done\r\n", AutoCalibrationCnt);
    printf("PLLDIV      = %d\r\n", RTC->PLL_DIV_AC);
    printf("Temperature = %.2f degrees\r\n", (float)(RTC->ACTEMP)/256.0);
  }
  
  /* stop auto-calibration and output of second pulse */
  RTC_AutoCalCmd(DISABLE);
  NVIC_DisableRTCIRQ();
  
  RTCALM_HighFreqSPOutputCmd(DISABLE);

  printf("auto-calibration test stops\r\n");
  /* Infinite loop */
  while (1)
  {

  }
}

/**
  * @brief  processes RTC IRQ
  * @param  None 
  * @retval None
  */
void RTC_IRQProc(void)
{
  /* check if auto-calibration is done */
  if(RTC->INTSTS&RTC_INT_ACDONE)
  {
    RTC_AutoCalDoneFlag = RTC_AutoCalibrationDone;
    RTC->INTSTS |= RTC_INT_ACDONE; /* clear interrupt flag */
    RTC_ALM_HighFreqDivideConfig(RTC_ALM_PLLDIVCLK_PLL1, RTC->PLL_DIV_AC);
  }
}

/**
  * @brief  AHB and APB Clock Configuration
  *         The Bus Clock is configured as follows :
  *            HCLK0    = PLL0   128 MHz
  *            PCLK0    = PLL0/2 64 MHz
  *            HCLK1    = PLL0/2 64 MHz
  *            PCLK1    = PLL0/2 64 MHz
  *            PLL1     = 61.44MHz
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  
  /* Select RCH as AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0 | CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_RCH;
  CLK_InitStruct.AHBCLKDivider = 1U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_RCH;
  CLK_InitStruct.APBCLKDivider = 2U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Update 1ms tick */
  if (STD_InitTick(CLK_GetHCLK0Freq(), TICK_INT_PRIORITY) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* PLL enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_XOH | CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOHState = CLK_XOH_ON;
  CLK_OscInitStruct.XOLState = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_XOH;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKN0;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKN1;
  CLK_OscInitStruct.PLL0.PLL0_M      = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKM;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_ON;
  CLK_OscInitStruct.PLL1.PLL1_Source = CLK_PLL1SOURCE_XOL_32768;
  CLK_OscInitStruct.PLL1.PLL1_Frequency = CLK_PLL1_IN_32768_OUT_61_44M;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL0 as  AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 1U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 2U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  CLK_InitStruct.BusClock = CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 2U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 2U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Update 1ms tick */
  if (STD_InitTick(CLK_GetHCLK0Freq(), TICK_INT_PRIORITY) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**
  * @brief  Enables RTC interrupt
  * @param  Param 
  * @retval None
  */
static void NVIC_EnableRTCIRQ(void)
{
  NVIC_ClearPendingIRQ(RTC_IRQn);
  /* Set Interrupt Priority */
  NVIC_SetPriority(RTC_IRQn, 0);
  /* Enable Interrupt in NVIC */
  NVIC_EnableIRQ(RTC_IRQn);
}


/**
  * @brief  Disables RTC interrupt
  * @param  None 
  * @retval None
  */
static void NVIC_DisableRTCIRQ(void)
{
  NVIC_ClearPendingIRQ(RTC_IRQn);
  /* Set Interrupt Priority */
  NVIC_SetPriority(RTC_IRQn, 0);
  /* Enable Interrupt in NVIC */
  NVIC_DisableIRQ(RTC_IRQn);
}


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
  uint32_t ACPParamAndChecksum[6];
  uint32_t TrTmAndCheckSum[3];
  uint32_t Checksum1, CheckSum2;
  /*
   * Address 0             
   *        offset 0        P1 P0,RTC data 1/0  set 1     p0+(p1<<16) 
   *        offset 4        P2, RTC data 2  set 1         p2
   *        offset 8        P5 P4, RTC data 5/4  set 1    p4+(p5<<16)
   *        offset 0x0C     P7 P6,RTC data 7/6  set 1     P6 + (P7<<16)
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
    Param->RTC_ACP0  = (int16_t)(ACPParamAndChecksum[0]&0xffff); 
    Param->RTC_ACP1  = (int16_t)(ACPParamAndChecksum[0]>>16);
    Param->RTC_ACP2  = (int32_t)ACPParamAndChecksum[1] 
                       + ((int32_t)TrTmAndCheckSum[0] - (int32_t)TrTmAndCheckSum[1])*256;
    
    Param->RTC_ACP5  = (int16_t)(ACPParamAndChecksum[2]>>16);
    Param->RTC_ACP6  = (int16_t)(ACPParamAndChecksum[3]&0xffff);
    Param->RTC_ACP7  = (int16_t)(ACPParamAndChecksum[3]>>16);
  }
  else
  {
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
      Param->RTC_ACP0  = (int16_t)(ACPParamAndChecksum[0]&0xffff); 
      Param->RTC_ACP1  = (int16_t)(ACPParamAndChecksum[0]>>16);
      Param->RTC_ACP2  = (int32_t)ACPParamAndChecksum[1] 
                         + ((int32_t)TrTmAndCheckSum[0] - (int32_t)TrTmAndCheckSum[1])*256;
      
      Param->RTC_ACP5  = (int16_t)(ACPParamAndChecksum[2]>>16);
      Param->RTC_ACP6  = (int16_t)(ACPParamAndChecksum[3]&0xffff);
      Param->RTC_ACP7  = (int16_t)(ACPParamAndChecksum[3]>>16);
    }
  }

  /*ACP4*/
  FLASH_INFO0ReadWord(FLASH0, 0x2000, ACPParamAndChecksum, 2);
  Checksum1 = CheckSumCalc(ACPParamAndChecksum, 1);
  if(Checksum1 == ACPParamAndChecksum[1])
  {
    Param->RTC_ACP4 = (int16_t)(ACPParamAndChecksum[0]&0xffff);
  }
  else
  {
    FLASH_INFO0ReadWord(FLASH0, 0x2008, ACPParamAndChecksum, 2);
    Checksum1 = CheckSumCalc(ACPParamAndChecksum, 1);
    if(Checksum1 == ACPParamAndChecksum[1])
    {
      Param->RTC_ACP4 = (int16_t)(ACPParamAndChecksum[0]&0xffff);
    }
  }
  
  /* K1, K2, K3, K4, K5*/
  FLASH_INFO0ReadWord(FLASH0, 0x2010, ACPParamAndChecksum, 6);
  Checksum1 = CheckSumCalc(ACPParamAndChecksum, 5);
  if(Checksum1 == ACPParamAndChecksum[5])
  {
    Param->RTC_K1 = (int16_t)(ACPParamAndChecksum[0]&0xffff);
    Param->RTC_K2 = (int16_t)(ACPParamAndChecksum[1]&0xffff);
    Param->RTC_K3 = (int16_t)(ACPParamAndChecksum[2]&0xffff);
    Param->RTC_K4 = (int16_t)(ACPParamAndChecksum[3]&0xffff);
    Param->RTC_K5 = (int16_t)(ACPParamAndChecksum[4]&0xffff);
  }
  else
  {
    FLASH_INFO0ReadWord(FLASH0, 0x2028, ACPParamAndChecksum, 6);
    Checksum1 = CheckSumCalc(ACPParamAndChecksum, 5);
    if(Checksum1 == ACPParamAndChecksum[5])
    {
      Param->RTC_K1 = (int16_t)(ACPParamAndChecksum[0]&0xffff);
      Param->RTC_K2 = (int16_t)(ACPParamAndChecksum[1]&0xffff);
      Param->RTC_K3 = (int16_t)(ACPParamAndChecksum[2]&0xffff);
      Param->RTC_K4 = (int16_t)(ACPParamAndChecksum[3]&0xffff);
      Param->RTC_K5 = (int16_t)(ACPParamAndChecksum[4]&0xffff);
    }
  }

  /* ACTI */
  FLASH_INFO0ReadWord(FLASH0, 0x2040, ACPParamAndChecksum, 2);
  Checksum1 = CheckSumCalc(ACPParamAndChecksum, 1);
  if(Checksum1 == ACPParamAndChecksum[1])
  {
    Param->RTC_TI = (int16_t)(ACPParamAndChecksum[0]&0xffff);
  }
  else
  {
    FLASH_INFO0ReadWord(FLASH0, 0x2048, ACPParamAndChecksum, 2);
    Checksum1 = CheckSumCalc(ACPParamAndChecksum, 1);
    if(Checksum1 == ACPParamAndChecksum[1])
    {
      Param->RTC_TI = (int16_t)(ACPParamAndChecksum[0]&0xffff);
    }
  }
  
  /*ACTEMP*/
  FLASH_INFO0ReadWord(FLASH0, 0x2050, ACPParamAndChecksum, 2);
  Checksum1 = CheckSumCalc(ACPParamAndChecksum, 1);
  if(Checksum1 == ACPParamAndChecksum[1])
  {
    Param->RTC_KTEMP = ACPParamAndChecksum[0];
  }
  else
  {
    FLASH_INFO0ReadWord(FLASH0, 0x2058, ACPParamAndChecksum, 2);
    Checksum1 = CheckSumCalc(ACPParamAndChecksum, 1);
    if(Checksum1 == ACPParamAndChecksum[1])
    {
      Param->RTC_KTEMP = ACPParamAndChecksum[0];
    }
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
  ACPParam->RTC_ACP4  = 0;
  ACPParam->RTC_ACP5  = 6444;
  ACPParam->RTC_ACP6  = 1342;
  ACPParam->RTC_ACP7  = 0;

  ACPParam->RTC_K1    = 21020;
  ACPParam->RTC_K2    = 22021;
  ACPParam->RTC_K3    = 23022;
  ACPParam->RTC_K4    = 24023;
  ACPParam->RTC_K5    = 25024;
  
  ACPParam->RTC_TI = 24*256; /* 24 degrees */
  ACPParam->RTC_KTEMP = 0x3C2800EC;  /*60 degrees,  40 degrees, 0 degree,-20 degrees */
}


/**
  * @brief  Configures Parameters for RTC automative temperature calibration
  * @param  Param: pointer to a RTCINFOParaType structure
  * @param  RTC_pclk: Specifies RTC pclk frequency
  * @retval None
  */
static void RTC_AutoCaliParamConfig(RTCINFOParaType* Param, uint32_t RTC_pclk)
{
  uint32_t temp;
  
  temp = (uint32_t)Param->RTC_ACP0;
  RTC_WriteRegisters((uint32_t)&RTC->ACP0, &temp, 1);
  
  temp = (uint32_t)Param->RTC_ACP1;
  RTC_WriteRegisters((uint32_t)&RTC->ACP1, &temp, 1);
  
  temp = (uint32_t)Param->RTC_ACP2;
  RTC_WriteRegisters((uint32_t)&RTC->ACP2, &temp, 1);
  
  temp = (uint32_t)Param->RTC_ACP3;
  RTC_WriteRegisters((uint32_t)&RTC->ACP3, &temp, 1);
  
  temp = (uint32_t)Param->RTC_ACP4;
  RTC_WriteRegisters((uint32_t)&RTC->ACP4, &temp, 1);
  
  temp = (uint32_t)Param->RTC_ACP5;
  RTC_WriteRegisters((uint32_t)&RTC->ACP5, &temp, 1);
  
  temp = (uint32_t)Param->RTC_ACP6;
  temp = (uint32_t)(temp*(RTC_pclk/6553600.0))&0x0000ffff;
  RTC_WriteRegisters((uint32_t)&RTC->ACP6, &temp, 1);
  
  temp = (uint32_t)Param->RTC_K1;
  RTC_WriteRegisters((uint32_t)&RTC->ACK1, &temp, 1);
  
  temp = (uint32_t)Param->RTC_K2;
  RTC_WriteRegisters((uint32_t)&RTC->ACK2, &temp, 1);
  
  temp = (uint32_t)Param->RTC_K3;
  RTC_WriteRegisters((uint32_t)&RTC->ACK3, &temp, 1);
  
  temp = (uint32_t)Param->RTC_K4;
  RTC_WriteRegisters((uint32_t)&RTC->ACK4, &temp, 1);
  
  temp = (uint32_t)Param->RTC_K5;
  RTC_WriteRegisters((uint32_t)&RTC->ACK5, &temp, 1);
  
  temp = (uint32_t)Param->RTC_TI;
  RTC_WriteRegisters((uint32_t)&RTC->ACTI, &temp, 1);
  
  temp = RTC_pclk/2;
  RTC_WriteRegisters((uint32_t)&RTC->ACF200, &temp, 1);

  temp = (uint32_t)Param->RTC_KTEMP;
  RTC_WriteRegisters((uint32_t)&RTC->ACKTEMP, &temp, 1);
}


/**
  * @brief  Enables or disables output of second pulse from high-frequency clock dividing.
  * @param  NewState: new state of output of second pulse
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void RTCALM_HighFreqSPOutputCmd(FunctionalState NewState)
{
  GPIO_InitType GPIO_InitStruct;

  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  
  if(NewState != DISABLE)
  {
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOI, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOI,GPIO_PinSource0, GPIO_AF0_RTC_PLLDIV0);
  }
  else
  {
    /* disable second pulse output by setting PI0 mode to default analog mode */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_Init(GPIOI, &GPIO_InitStruct);
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
