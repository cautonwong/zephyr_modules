/**
  ******************************************************************************
  * @file    lib_rtc.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   RTC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_rtc.h"


/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup RTC 
  * @brief RTC driver modules
  * @{
  */

/** @defgroup RTC_Private_Macros
  * @{
  */ 

/* Private define ------------------------------------------------------------*/
#define RTCPWD_KEY                  (0x5AA55AA5UL)
#define RTCCE_SETKEY                (0xA55AA55BUL)
#define RTCCE_CLRKEY                (0xA55AA55AUL)
/* RTC_CE */
#define RTC_CE_BSY                  (0x2UL)
/* RTC_CTRL */
#define RTC_CTRL_SUBCNTEN           (0x2UL)
/* RTC_ACCTRL */
#define RTC_ACCTRL_ADCSEL           (1UL << 3)
#define RTC_ACCTRL_ADCLK_MASK       (3UL << 4)
#define RTC_ACCTRL_PERIOD_POS       (8UL)
#define RTC_ACCTRL_PERIOD_MASK      (0x3FUL << RTC_ACCTRL_PERIOD_POS)
#define RTC_ACCTRL_ADCJUDGE         (1UL << 14)
#define RTC_ACCTRL_ACEN             (1UL >> 0)
#define RTC_ACCTRL_MANU             (1UL << 1)
/* RTC_INTSTS */
#define RTC_INTSTS_ACBUSY           (1UL << 3)


#define RTC_ADC_ANA_REQ             ((uint32_t)0x00000001)
#define RTC_ADC_FLAG_EOC            ((uint32_t)0x00000002)

/**
  * @}
  */ 


/** @defgroup RTC_Private_Functions
  * @{
  */


/**
  * @brief  Enables or disables RTC registers write protection.
  * @param  NewState: new state of the write protection.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WriteProtection(FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  /* Enable RTC Write-Protection */
  if (NewState != DISABLE)
  {
    WRITE_REG(RTC->PWD, RTCPWD_KEY);
    WRITE_REG(RTC->CE, RTCCE_CLRKEY);
  }
  /* Disable RTC Write-Protection */
  else
  {
    WRITE_REG(RTC->PWD, RTCPWD_KEY);
    WRITE_REG(RTC->CE, RTCCE_SETKEY);
  }
}

/**
  * @brief  Waits until the RTC registers (be W/R protected) are synchronized
  *         with RTC APB clock.
  * @param  None
  * @note   The RTC Resynchronization mode is write protected, use the 
  *         RTC_WriteProtection(DISABLE) before calling this function.
  *           Write-Operation process as follows: 
  *             1. RTC_WriteProtection(DISABLE);  
  *             2. RTC Registers write operation(only first write-operation be 
  *                valid on the same register).
  *             3. RTC_WriteProtection(ENABLE); 
  *             4. RTC_WaitForSynchro();  Wait until the RTC registers be 
  *                synchronized by calling this function.
  * @retval None
  */
void RTC_WaitForSynchro(void)
{
  while (IS_BIT_SET(RTC->CE, RTC_CE_BSY))
  {
  }
}

/**
  * @brief      Writes RTC registers(continuous/be write-protected). 
  * @param[in]  StartAddr   the start address of registers be written
  * @param[in]  wBuffer     pointer to write
  * @param[in]  Len         number of registers be written
  * @retval     None
  */
void RTC_WriteRegisters(uint32_t StartAddr, const uint32_t *wBuffer, uint8_t Len)
{
  uint32_t cnt;
  
  /* Parameter check */
  assert_parameters(IS_RTC_REGOP_STARTADDR(StartAddr));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  
  /* Write registers */
  for (cnt=0UL; cnt<Len; cnt++)
  {
    WRITE_MEM32(StartAddr, *(wBuffer++));
    StartAddr += 4UL;
  }
  
  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief      Reads RTC registers(continuous/be read-protected). 
  * @param[in]  StartAddr   the start address of registers be read
  * @param[out] rBuffer     pointer to read
  * @param[in]  Len         number of registers be read
  * @retval     None
  */
void RTC_ReadRegisters(uint32_t StartAddr, uint32_t *rBuffer, uint8_t Len)
{
  __IO uint32_t tmp = 0UL, cnt=0UL;
  
  UNUSED(tmp);
  
  /* Parameter check */
  assert_parameters(IS_RTC_REGOP_STARTADDR(StartAddr));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Dummy read-operation to RTC->LOAD */
  tmp = READ_REG(RTC->LOAD);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Read registers */
  for (cnt=0UL; cnt<Len; cnt++)
  {
    *(rBuffer++) = READ_MEM32(StartAddr);
    StartAddr += 4UL;
  }
}

/**
  * @brief  Sets RTC current time.
  * @param  sTime: Pointer to Time structure
  *         AccurateSel:
  *             @arg RTC_ACCURATE
  *             @arg RTC_INACCURATE
  * @retval None
  */
void RTC_SetTime(RTC_TimeType *sTime, uint32_t AccurateSel)
{
  uint32_t subsec, sec, tmp;

  /* Parameter check */
  assert_parameters(IS_RTC_TIME_YEAR(sTime->Year));
  assert_parameters(IS_RTC_TIME_MONTH(sTime->Month));
  assert_parameters(IS_RTC_TIME_DATE(sTime->Date)); 
  assert_parameters(IS_RTC_TIME_WEEKDAY(sTime->WeekDay)); 
  assert_parameters(IS_RTC_TIME_HOURS(sTime->Hours)); 
  assert_parameters(IS_RTC_TIME_MINS(sTime->Minutes)); 
  assert_parameters(IS_RTC_TIME_SECS(sTime->Seconds));
  if (AccurateSel == RTC_ACCURATE)
    assert_parameters(IS_RTC_TIME_SubSECS(sTime->SubSeconds));
  assert_parameters(IS_RTC_ACCURATESEL(AccurateSel));

  subsec = sTime->SubSeconds;
  subsec = subsec - ((subsec>>8UL)*156UL) - (((subsec&0xFFUL)>>4UL)*6UL);
  sec = sTime->Seconds;
  sec = sec - ((sec>>4UL)*6UL);
  subsec = (sec*32768UL) + (subsec*32768UL/1000UL);

  tmp = READ_REG(RTC->CTRL);
  if (AccurateSel == RTC_ACCURATE)
  { /* Enable subsecond counter */
    tmp |= RTC_CTRL_SUBCNTEN;
  }
  else
  { /* Disable subsecond counter */
    tmp &= ~RTC_CTRL_SUBCNTEN;
  }
  
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  
  WRITE_REG(RTC->CTRL, tmp);
  
  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Write RTC time registers */
  WRITE_REG(RTC->TIME, subsec);
  WRITE_REG(RTC->SEC, sTime->Seconds);
  WRITE_REG(RTC->MIN, sTime->Minutes);
  WRITE_REG(RTC->HOUR,sTime->Hours);
  WRITE_REG(RTC->DAY, sTime->Date);
  WRITE_REG(RTC->WEEK, sTime->WeekDay);
  WRITE_REG(RTC->MON, sTime->Month);
  WRITE_REG(RTC->YEAR, sTime->Year);

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Gets RTC current time.
  * @param[out]  gTime: Pointer to Time structure
  * @param[in]  AccurateSel:
  *               @arg RTC_ACCURATE
  *               @arg RTC_INACCURATE
  * @retval None
*/
void RTC_GetTime(RTC_TimeType *gTime, uint32_t AccurateSel)
{
  __IO uint32_t dummy_data = 0UL;
  uint32_t subsec, sec;
  
  /* Data for dummy reading.
     To avoid gcc/g++ warnings */
  UNUSED(dummy_data);

  /* Parameter check */
  assert_parameters(IS_RTC_ACCURATESEL(AccurateSel));
  
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Dummy read-operation to RTC->LOAD register */
  dummy_data = READ_REG(RTC->LOAD);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Read RTC time registers */
  gTime->Seconds  = READ_REG(RTC->SEC);
  gTime->Minutes  = READ_REG(RTC->MIN);
  gTime->Hours    = READ_REG(RTC->HOUR);
  gTime->Date     = READ_REG(RTC->DAY);
  gTime->WeekDay  = READ_REG(RTC->WEEK);
  gTime->Month    = READ_REG(RTC->MON);
  gTime->Year     = READ_REG(RTC->YEAR);
  subsec          = READ_REG(RTC->TIME);

  if (AccurateSel == RTC_ACCURATE)
  {
    sec = subsec/32768UL;
    sec = sec + ((sec/10UL)*6UL);
    gTime->Seconds = sec;
    subsec = (subsec%32768UL)*1000UL/32768UL;
    subsec = subsec + (((subsec%100UL)/10UL)*6UL) + ((subsec/100UL)*156UL);
    gTime->SubSeconds = subsec;
  }
  else
  {
    gTime->SubSeconds = 0UL;
  }
}

/**
  * @brief  Enables or disables the RTC subseconds counter.
  * @param  NewState: new state of the RTC subseconds counter.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_SubSecondCmd(FunctionalState NewState)
{
  uint32_t tmp;

  /* Parameter check */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmp = READ_REG(RTC->CTRL);
  if (NewState == ENABLE)
  {
    SET_BIT(tmp, RTC_CTRL_SUBCNTEN);
  }
  else
  {
    CLEAR_BIT(tmp, RTC_CTRL_SUBCNTEN);
  }

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  WRITE_REG(RTC->CTRL, tmp);

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Fills each RTC_ACInitStruct member with its default value.
  * @param  RTC_ACInitStruct: pointer to an RTC_AutoCalType structure which will be initialized.
  * @retval None
  */
void RTC_AutoCalStructInit(RTC_AutoCalType *RTC_ACInitStruct)
{
  /*------------ Reset RTC AutCal init structure parameters values -----------*/
  /* Initialize the ADCJudgeCmd member */
  RTC_ACInitStruct->ADCJudgeCmd = DISABLE;
  /* Initialize the AutoTrigPeriod member */
  RTC_ACInitStruct->AutoTrigPeriod = 0UL;
  /* Initialize the AutoTrigUnit member */
  RTC_ACInitStruct->AutoTrigUnit = RTC_ACAutoTrigUnit_None;
  /* Initialize the DataSource member */
  RTC_ACInitStruct->DataSource = RTC_ACDataSource_Hardware;
}

/**
  * @brief  Initializes the RTC calibration function according to the specified parameters 
  *         in the RTC_ACInitStruct.
  * @param  RTC_ACInitStruct:  pointer to an RTC_AutoCalType structure that
  *         contains the configuration information for the RTC calibration function.
  * @retval None
  */
void RTC_AutoCalInit(RTC_AutoCalType *RTC_ACInitStruct)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(RTC_ACInitStruct->ADCJudgeCmd));
  assert_parameters(IS_RTC_AUTOCAL_ATCS(RTC_ACInitStruct->AutoTrigUnit));
  assert_parameters(IS_RTC_AUTOCAL_ADCSRC(RTC_ACInitStruct->DataSource));
  assert_parameters(IS_RTC_AUTOCAL_PERIOD(RTC_ACInitStruct->AutoTrigPeriod));
  
  tmp = READ_REG(RTC->ACCTRL);
  tmp &= ~(RTC_ACCTRL_ADCSEL \
          |RTC_ACCTRL_ADCLK_MASK \
          |RTC_ACCTRL_PERIOD_MASK \
          |RTC_ACCTRL_ADCJUDGE);
  if (RTC_ACInitStruct->ADCJudgeCmd == ENABLE)
  {
    tmp |= RTC_ACCTRL_ADCJUDGE;
  }
  tmp |= ((RTC_ACInitStruct->AutoTrigUnit) \
         |(RTC_ACInitStruct->AutoTrigPeriod << RTC_ACCTRL_PERIOD_POS) \
         |(RTC_ACInitStruct->DataSource));
  
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  WRITE_REG(RTC->ACCTRL, tmp);
  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Enables or disables RTC Auto-calibration function.
  * @param  NewState: new state of the RTC Auto-calibration function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
 */
void RTC_AutoCalCmd(FunctionalState NewState)
{
  uint32_t tmp;
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = READ_REG(RTC->ACCTRL);
  if (NewState != DISABLE)
  {
    tmp |= RTC_ACCTRL_ACEN;
  }
  else
  {
    tmp &= ~RTC_ACCTRL_ACEN;
  }

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  
  WRITE_REG(RTC->ACCTRL, tmp);
  
  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Starts RTC Auto-calibration manually.
  * @param  None
  * @retval None
  */
void RTC_StartAutoCalManual(void)
{
  uint32_t tmp;
  
  tmp = READ_REG(RTC->ACCTRL);
  tmp |= RTC_ACCTRL_MANU;
  
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  
  /* manual trigger Auto-calibration */
  WRITE_REG(RTC->ACCTRL, tmp); 
  
  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();  
}

/**
  * @brief  Waits until Auto-calibration manual is done.
  * @param  None
  * @retval None
  */
void RTC_WaitForAutoCalManual(void)
{
  while (IS_BIT_SET(RTC->ACCTRL, RTC_ACCTRL_MANU))
  {
  }
}

/**
  * @brief  Fills each RTC ADC_InitStruct member with its default value.
  * @param  RTC_ADC_InitStruct: pointer to an RTC_ADC_InitType structure which will be initialized.
  * @retval None
  */
void RTC_ADC_StructInit(RTC_ADC_InitType *RTC_ADC_InitStruct)
{
  RTC_ADC_InitStruct->Channel       = RTC_ADC_CHANNEL_TEMP;
  RTC_ADC_InitStruct->ClockDivider  = RTC_ADC_CLKDIV_1;
  RTC_ADC_InitStruct->AverageEnable = RTC_ADC_AVERAGE_DISABLE;
  RTC_ADC_InitStruct->AverageSample = RTC_ADC_AVERAGE_2;
}

/**
  * @brief  Initializes the RTC_ADC according to the specified
  *         parameters in the RTC_ADC_InitStruct.
  * @param  RTC_ADC_InitStruct: pointer to a RTC_ADC_InitType structure that
  *         contains the configuration information for the specified RTC_ADC Config.
  * @retval None
  */
void RTC_ADC_Init(RTC_ADC_InitType *RTC_ADC_InitStruct)
{
  /* Check the parameters */
  assert_parameters(IS_RTC_ADC_CHANNEL(RTC_ADC_InitStruct->Channel));  
  assert_parameters(IS_RTC_ADC_CLKDIV(RTC_ADC_InitStruct->ClockDivider));  
  assert_parameters(IS_RTC_ADC_AVERAGEEN(RTC_ADC_InitStruct->AverageEnable));
  assert_parameters(IS_RTC_ADC_AVERAG(RTC_ADC_InitStruct->AverageSample));
  
  CLEAR_BIT(RTCANA->ADCCTRL, RTC_ADC_CHANNELMASK); 
  SET_BIT(RTCANA->ADCCTRL, (RTC_ADC_InitStruct->Channel << 4));
  CLEAR_BIT(RTCANA->ADCCTRLCFG, RTC_ADC_CLKDIVMASK);
  SET_BIT(RTCANA->ADCCTRLCFG, RTC_ADC_InitStruct->ClockDivider);

  CLEAR_BIT(RTCANA->ADCCTRLCFG2, (RTC_ADC_AVERAGESAMPLEMASK | RTC_ADC_AVERAGEENMASK));
  SET_BIT(RTCANA->ADCCTRLCFG2, ((RTC_ADC_InitStruct->AverageSample) | (RTC_ADC_InitStruct->AverageEnable)));
}




/**
  * @brief  Start RTC ADC manual-trigger.
  * @param  None
  * @retval None
  */
void RTC_ADC_StartManual(void)
{
  SET_BIT(RTCANA->ADCCTRL, RTC_ADC_ANA_REQ);
}

/**
  * @brief  Checks whether RTC ADC conversion valid flag is set or not.
  * @param  None.
  * @retval The new state of RTC ADC conversion valid flag (SET or RESET).
  */
FlagStatus RTC_ADC_GetConvValidFlagStatus(void)
{
  FlagStatus bitstatus = RESET;
 
  /* Check the status of conversion bit */
  if ((RTCANA->ADCCTRL & RTC_ADC_FLAG_EOC) != (uint32_t)RESET)
  {
    /* EOC bit is set */
    bitstatus = SET;
  }
  else
  {
    /* EOC bit is reset */
    bitstatus = RESET;
  }
  /* Return the EOC bit status */
  return  bitstatus;
}

/**
  * @brief  Clears RTC ADC conversion valid flag.
  * @param  None.
  * @retval None
  */
void RTC_ADC_ClearConvValidFlag(void)
{
  RTCANA->ADCCTRL |= (RTC_ADC_FLAG_EOC);
}

/**
  * @brief  Gets RTC ADC conversion value.
  * @param  None
  * @retval ADC conversion value.
  */
int16_t RTC_ADC_GetConvValue(void)
{
  return (uint16_t)(RTCANA->ADCCTRL >> 16);
}

/**
  * @brief  Checks whether auto-calibration busy flag is set or not
  * @param  None
  * @retval Busy status.
  */
FlagStatus RTC_GetACBusyFlag(void)
{
  if (IS_BIT_SET(RTC->INTSTS, RTC_INTSTS_ACBUSY))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Enables or disables RTC specified interrupt.
  * @param  INTMask: specifies the RTC interrupt source to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_INT_TIMEILLE
  *            @arg RTC_INT_CEILLE
  *            @arg RTC_INT_ACDONE
  * @param  NewState: new state of the RTC UART specified interrupt
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_INTConfig(uint32_t IntMask, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  assert_parameters(IS_RTC_INTC(IntMask));
  
  if (NewState != DISABLE)
  {
    SET_BIT(RTC->INTEN, IntMask);
  }
  else
  {
    CLEAR_BIT(RTC->INTEN, IntMask);
  }
}

/**
  * @brief  Gets RTC specified interrupt status.
  * @param  INTMask: specifies the RTC interrupt status to get.
  *         This parameter can one of the following values:
  *            @arg RTC_INT_TIMEILLE
  *            @arg RTC_INT_CEILLE
  *            @arg RTC_INT_ACDONE
  * @retval Interrupt status.
  */
ITStatus RTC_GetINTStatus(uint32_t IntMask)
{
  /* Check parameters */
  assert_parameters(IS_RTC_INTR(IntMask));
  
  if (IS_BIT_SET(RTC->INTSTS, IntMask))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears RTC specified interrupt status.
  * @param  INTMask: specifies the RTC interrupt status to clear.
  *         This parameter can any combination of the following values:
  *            @arg RTC_INT_TIMEILLE
  *            @arg RTC_INT_CEILLE
  *            @arg RTC_INT_ACDONE
  * @retval Interrupt status.
  */
void RTC_ClearINTStatus(uint32_t IntMask)
{
  /* Check parameters */
  assert_parameters(IS_RTC_INTC(IntMask));
  
  WRITE_REG(RTC->INTSTS, IntMask);
}

/**
  * @}
  */ 


/**
  * @}
  */ 

/**
  * @}
  */ 


/*********************************** END OF FILE ******************************/
