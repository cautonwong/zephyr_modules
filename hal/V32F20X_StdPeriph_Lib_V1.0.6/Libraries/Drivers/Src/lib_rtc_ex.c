/**
  ******************************************************************************
  * @file    lib_rtc_ex.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-03-05
  * @brief   This file provides firmware functions to manage 
  *          RTC analog controller, RTC wakeup and RTC alarm.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 #include "lib_rtc.h"
 #include "lib_rtc_ex.h"
 #include "lib_gpio.h"
 #include "lib_gpio_ex.h"
 #include "lib_clk.h"
 
 /** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup RTC_EX
  * @brief RTC_EX driver modules
  * @{
  */

/** @defgroup RTC_EX_Private_Macros
  * @{
  */ 

#define RTC_ANA_CTRL_COREPW_PSWD           ((uint32_t)0xAA5555AA)
#define RTC_ANA_CTRL_PASSWORD              ((uint32_t)0xBEEFBEEF)
#define RTCONLY_EN                         ((uint32_t)0x00000020)

#define RTC_ALM_CFG_BUSY                   ((uint32_t)0x00000001)
#define RTC_ALM_ALARMCTL_ALARMINACCURATE   ((uint32_t)0x00000002)
#define RTC_ALM_ALARMCTL_ALARMEN           ((uint32_t)0x00000001)

#define RTC_TIMER_EN                       ((uint32_t)0x00000001)
#define RTC_TIMER_WKU_EN                   ((uint32_t)0x00000010)

#define RTC_ANA_RTC_WKU_ENABLE             ((uint32_t)0x00000001)
/**
  * @}
  */ 

 /** @defgroup RTC_EX_Private_Functions
  * @{
  */

/**
  * @brief  Resets the specified RTC analog controller by software.
  * @param  Source: the specified RTC analog controller to be reset.
  *          This parameter can be one of the following values:
  *            @arg RTC_ANA_SW_RST_ADC
  *            @arg RTC_ANA_SW_RST_RTC
  *            @arg RTC_ANA_SW_RST_COMP
  *            @arg RTC_ANA_SW_RST_IO
  *            @arg RTC_ANA_SW_RST_RTC_TIMER
  * @retval None
  */
void RTCEx_RTCANASWReset(uint32_t Source)
{
  /* Check parameters */
  assert_parameters(IS_RTC_ANA_SW_RST_SRC(Source));
  
  RTCANA->SWRSTPSWD = RTC_ANA_CTRL_PASSWORD;
  RTCANA->SWRST = Source;
  __NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();
  
  RTCANA->SWRSTPSWD = RTC_ANA_CTRL_PASSWORD;
  RTCANA->SWRST=0;
  while(RTCANA->SWRST & Source)
  {}
}

/**
  * @brief  Deinitializes the RTC external interrupt registers to
            their default reset values.
  * @param  None
  * @retval None
  */
void RTCEx_GPIOEXTIDeInit(void)
{
  RTCANA->EXTIMODE = 0;
  RTCANA->EXTIPOLA = 0;
  RTCANA->EXTIEMRIMR = 0;
  RTCEx_RTCANASWReset(RTC_ANA_SW_RST_IO);
}

/**
  * @brief  Initializes GPIO pins for RTC only wakeup.
  * @param  Pin: 
  *           RTC_ANA_PI8 
  *           RTC_ANA_PC13
  *           RTC_ANA_PC14
  *           RTC_ANA_PC15
  * @param  Event:
  *           GPIO_EVENT_DISABLE
  *           GPIO_EVENT_RISING_EDGE
  *           GPIO_EVENT_FALLING_EDGE
  *           GPIO_EVENT_DUAL_EDGE
  *           GPIO_EVENT_HIGH_LEVEL
  *           GPIO_EVENT_LOW_LEVEL
  * @retval None
  */
void RTCEx_GPIOWKUInit(uint8_t Pin, uint8_t Event)
{
  uint8_t tmp = 0;
  
  /* Check parameters */
  assert_parameters(IS_RTC_ANA_GPIO_PIN(Pin));
  assert_parameters(IS_GPIO_EVENT(Event));

  tmp = RTCANA->EXTIMODE;
  tmp &= ~(3<<(Pin*2));
  tmp |= ((Event & 0x3) << (Pin*2));
  RTCANA->EXTIMODE = tmp;

  tmp = RTCANA->EXTIPOLA;
  tmp &= ~(1<<Pin);
  tmp |= (((Event & 0x4)>>2) << Pin);
  RTCANA->EXTIPOLA |= tmp;

  RTCANA->EXTIEMRIMR |= (1<<Pin);
}

/**
  * @brief  Gets all EXTI interrupt status.
  * @param  None
  * @retval RTC Only EXTI interrrupt status
  */
uint32_t RTCEx_GetAllEXTIINTStatus(void)
{
  return (RTCANA->EXTICFG&RTC_EXTI_CFG_INT_MASK);
}

/**
  * @brief  Clears EXTI interrupt status.
  * @param  INTMask:
  *           RTC_EXTI_CFG_INT3_STS
  *           RTC_EXTI_CFG_INT2_STS
  *           RTC_EXTI_CFG_INT1_STS
  *           RTC_EXTI_CFG_INT0_STS
  * @retval None
  */
void RTCEx_ClearEXTIINTStatus(uint32_t INTMask)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IO_RTC_EXTI_INT(INTMask));
  tmp = RTCANA->EXTICFG;
  tmp &= (~RTC_EXTI_CFG_INT_MASK);
  tmp |= INTMask;
  RTCANA->EXTICFG = tmp;
}


/**
  * @brief  Deinitializes the RTC timer registers to
            their default reset values.
  * @param  None
  * @retval None
  */
void RTCEx_RTCTimerDeInit(void)
{
  RTCANA->TMRCFG = 0;
  RTCANA->TMRCNT = 0;
  
  RTCEx_RTCANASWReset(RTC_ANA_SW_RST_RTC_TIMER);
}

/**
  * @brief  Enables or disables the specified clock of RTC wakeup module.
  * @param  Src: the specified RTC wakeup module's clock
  *            RTC_ANA_CLK_RTC_TIMER
  *            RTC_ANA_CLK_RTC_IO   
  *            RTC_ANA_CLK_RTC_CMP  
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void RTCEx_RTCWKUModuleClkCmd(uint32_t Src, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_RTC_ANA_CLK_SRC(Src));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if(NewState != DISABLE)
  {
    RTCANA->CLKEN |= Src;
  }
  else
  {
    RTCANA->CLKEN &= ~Src;
  }
}

/**
  * @brief  Enables or disables RTC timer.
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void RTCEx_RTCTimerCmd(FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if(NewState != DISABLE)
  {
    RTCANA->TMRCFG |= RTC_TIMER_EN;
  }
  else
  {
    RTCANA->TMRCFG &= ~RTC_TIMER_EN;
  }
}

/**
  * @brief  Enables or disables RTC timer for RTC only wakeup. 
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void RTCEx_RTCOnlyTimerWKUCmd(FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if(NewState != DISABLE)
  {
    RTCANA->TMRCFG |= RTC_TIMER_WKU_EN;
  }
  else
  {
    RTCANA->TMRCFG &= ~RTC_TIMER_WKU_EN;
  }
}

/**
  * @brief  Sets RTC timer count value.
  * @param  val: 0~0x7fffffff.
  * @retval None
  */
void RTCEx_SetRTCTimerCount(uint32_t val)
{
  /* Check parameters */
  assert_parameters(IS_RTC_ANA_TIMER_COUNT_VAL(val));
  
  RTCANA->TMRCNT = val;
}

/**
  * @brief  Enters RTC only mode.
  * @param  None
  * @retval None
  */
void RTCEx_EnterRTCOnlyMode(void)
{
  uint32_t tmp;
  tmp = RTCANA->RTCCTRL;
  tmp &= ~RTCONLY_EN;
  RTCANA->RTCCTRLPSWD = RTC_ANA_CTRL_COREPW_PSWD;
  RTCANA->RTCCTRL = tmp;
  RTCANA->RTCCTRLPSWD = RTC_ANA_CTRL_COREPW_PSWD;
  RTCANA->RTCCTRL = tmp | RTCONLY_EN;
}


/**
  * @brief  Configures RTC clock source. 
  * @param  RTCClkSel: the specified RTC clock source.
  *          This parameter can be one of the following values:
  *            @arg RTC_CLKSRC_32KXTAL
  *            @arg RTC_CLKSRC_32KRC
  * @retval None
  */
void RTCEx_ClkSRCConfig(uint32_t RTCClkSrc)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_RTC_ANA_RTCCLKSRC(RTCClkSrc));
  
  RTCANA->RTCCTRLPSWD = RTC_ANA_CTRL_COREPW_PSWD;
  tmp = RTCANA->RTCCTRL;
  
  /* If current RTC clock source is same as RTCClkSrc, return.
   * Otherwise, configure new RTC clock source.
   */
  if((tmp&RTC_CLKSRC_MASK) != RTCClkSrc)
  {
    RTCANA->RTCCTRLPSWD = RTC_ANA_CTRL_COREPW_PSWD;
    if(RTCClkSrc == RTC_CLKSRC_32KXTAL)
    {
      RTCANA->RTCCTRL = tmp|RTC_CLKSRC_32KXTAL;
    }
    else
    {
      tmp &= ~RTC_CLKSRC_MASK;
      RTCANA->RTCCTRL = tmp;
    }
  }
}


/**
  * @brief  waits for completion of RTC alarm configuration.
  * @param  None.
  * @retval None
  */
void RTCEx_WaitForAlarmSync(void)
{
  while(RTCALM->STS & RTC_ALM_CFG_BUSY)
  {}
  RTCALM->CFGVALID = 1;
  while(RTCALM->STS & RTC_ALM_CFG_BUSY)
  {}
}

/**
  * @brief  Configures Multi-second for low-power wakeup function.
  * @param  nPeriod: N seconds interval.
  * @note   For the first interrupt generated by calling this function, it may
  *         have < 1 sec error if the new WKUSEC number(parameter) is not equal
  *         to current WKUSEC number.  If the new WKUSEC is equal to current WKUSEC,
  *         the first interrupt time may have 0~(WKUSEC +1) variation.
  *         To avoid this problem, set an alternative parameter (like 1) by calling
  *         this function, then set the correct parameter to it.
  * @retval None
  */
void RTCEx_LPWKUSecondsConfig(uint8_t nPeriod)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_WKUSEC_PERIOD(nPeriod));

  RTCALM->WKUSEC = nPeriod - 1;
  /* Sync */
  RTCEx_WaitForAlarmSync();
}

/**
  * @brief  Configures Multi-minute for low-power wakeup function.
  * @param  nPeriod: N minute interval.
  * @note   For the first interrupt generated by calling this function, it may
  *         have < 1 min error if the new WKUMIN number(parameter) is not equal
  *         to current WKUMIN number.  If the new WKUMIN is equal to current WKUMIN,
  *         the first interrupt time may have 0~(WKUMIN +1) variation.
  *         To avoid this problem, set an alternative parameter (like 1) by calling
  *         this function, then set the correct parameter to it.
  * @retval None
  */
void RTCEx_LPWKUMinutesConfig(uint8_t nPeriod)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_WKUMIN_PERIOD(nPeriod));

  RTCALM->WKUMIN = nPeriod - 1;
  /* Sync */
  RTCEx_WaitForAlarmSync();
}

/**
  * @brief  Configures Multi-hour for low-power wakeup function.
  * @param  nPeriod: N hour interval.
  * @note   For the first interrupt generated by calling this function, it may
  *         have < 1 hour error if the new WKUHOUR number(parameter) is not equal
  *         to current WKUHOUR number.  If the new WKUHOUR is equal to current WKUHOUR,
  *         the first interrupt time may have 0~(WKUHOUR +1) variation.
  *         To avoid this problem, set an alternative parameter (like 1) by calling
  *         this function, then set the correct parameter to it.
  * @retval None
  */
void RTCEx_LPWKUHoursConfig(uint8_t nPeriod)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_WKUHOUR_PERIOD(nPeriod));

  RTCALM->WKUHOUR = nPeriod - 1;
  /* Sync */
  RTCEx_WaitForAlarmSync();
}

/**
  * @brief  Configures RTC counter for lower-power wakeup function.
  * @param  nClock:
  *             1~0x1000000
  * @param   CNTCLK:
  *             RTC_ALM_WKUCNT_32768
  *             RTC_ALM_WKUCNT_2048
  *             RTC_ALM_WKUCNT_512
  *             RTC_ALM_WKUCNT_128
  * @retval None
  */
void RTCEx_LPWKUCounterConfig(uint32_t nClock, uint32_t CNTCLK)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_WKUCNT_PERIOD(nClock));
  assert_parameters(IS_RTC_ALM_WKUCNT_CNTSEL(CNTCLK));

  RTCALM->WKUCNT = CNTCLK | (nClock - 1);
  /* Sync */
  RTCEx_WaitForAlarmSync();
}

/**
  * @brief  Configures RTC ITV for low-power wakeup function.
  * @param  nType:specifies wakeup and interrupt interval
  *         This parameter can be any combination of the following values:
  *           @arg RTC_ALM_ITV_SEC: every a second
  *           @arg RTC_ALM_ITV_MIN: every a minute
  *           @arg RTC_ALM_ITV_HOUR: every an hour
  *           @arg RTC_ALM_ITV_DAY: every other day(at 00:00)
  *           @arg RTC_ALM_ITV_500MS: every 500 microseconds
  *           @arg RTC_ALM_ITV_250MS: every 250 microseconds
  *           @arg RTC_ALM_ITV_125MS: every 125 microseconds
  *           @arg RTC_ALM_ITV_62_5MS: every 62.5 microseconds
  * @retval None
  */
void RTCEx_LPWKUITVConfig(uint8_t nType)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_ITV(nType));

  RTCALM->ITV = nType;
  RTCALM->SITV  = 0;
  /* Sync */
  RTCEx_WaitForAlarmSync();
}

/**
  * @brief  Configures RTC SITV interval for low-power wakeup.
  * @param  nPeriod:specifies wakeup interval, value ranges from 1 to 64
  * @retval None
  */
void RTCEx_LPWKUSITVConfig(uint8_t nPeriod)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_SITV(nPeriod));

  RTCALM->ITV = RTC_ALM_ITV_SITVSEC;
  RTCALM->SITV  = RTC_ALM_SITV_EN | (nPeriod - 1);
  /* Sync */
  RTCEx_WaitForAlarmSync();
}

/**
  * @brief  Gets RTC wakeup counter value for low-power wakeup.
  * @param  None
  * @retval RTC wakeup counter value
  */
uint32_t RTCEx_GetLPWKUCounterValue(void)
{
  return RTCALM->WKUCNTR;
}


/**
  * @brief  Sets the specified RTC Alarm.
  * @param  RTC_ALM_AlarmStruct: pointer to a RTC_ALM_AlarmType structure that
  *         contains the alarm configuration parameters.
  * @retval None
  */
void RTCEx_SetAlarm(RTC_ALM_AlarmType *RTC_ALM_AlarmStruct)
{
  uint32_t  alarmctl;

  /* Parameter check */
  assert_parameters(IS_RTC_ALM_ALARMTIME_YEAR(RTC_ALM_AlarmStruct->AlarmYear));
  assert_parameters(IS_RTC_ALM_ALARMTIME_MONTH(RTC_ALM_AlarmStruct->AlarmMonth));
  assert_parameters(IS_RTC_ALM_ALARMTIME_DATE(RTC_ALM_AlarmStruct->AlarmDate));
  assert_parameters(IS_RTC_ALM_ALARMTIME_HOURS(RTC_ALM_AlarmStruct->AlarmHours));
  assert_parameters(IS_RTC_ALM_ALARMTIME_MINS(RTC_ALM_AlarmStruct->AlarmMinutes));
  assert_parameters(IS_RTC_ALM_ALARMTIME_SECS(RTC_ALM_AlarmStruct->AlarmSeconds));
  assert_parameters(IS_RTC_ALM_ALARMTIME_MASK(RTC_ALM_AlarmStruct->AlarmMask));

  alarmctl = RTCALM->ALARMCTL & RTC_ALM_ALARMCTL_ALARMEN;
  alarmctl |= RTC_ALM_AlarmStruct->AlarmMask;  

  RTCALM->ALARMYEAR  = RTC_ALM_AlarmStruct->AlarmYear;
  RTCALM->ALARMMONTH = RTC_ALM_AlarmStruct->AlarmMonth;
  RTCALM->ALARMDAY   = RTC_ALM_AlarmStruct->AlarmDate;
  RTCALM->ALARMHOUR  = RTC_ALM_AlarmStruct->AlarmHours;
  RTCALM->ALARMMIN   = RTC_ALM_AlarmStruct->AlarmMinutes;
  RTCALM->ALARMSEC   = RTC_ALM_AlarmStruct->AlarmSeconds;
  RTCALM->ALARMTIME  = 0;
  RTCALM->ALARMCTL   = alarmctl;

  /* Sync */
  RTCEx_WaitForAlarmSync();
}

/**
  * @brief  Gets the RTC Alarm values and masks.
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmType structure that will 
  *         contains the output alarm configuration values and masks.
  * @retval None
  */
void RTCEx_GetAlarm(RTC_ALM_AlarmType *RTC_ALM_AlarmStruct)
{
  /* Read RTC time registers */
  RTC_ALM_AlarmStruct->AlarmMask       = RTCALM->ALARMCTL;
  RTC_ALM_AlarmStruct->AlarmYear       = RTCALM->ALARMYEAR;
  RTC_ALM_AlarmStruct->AlarmMonth      = RTCALM->ALARMMONTH;
  RTC_ALM_AlarmStruct->AlarmDate       = RTCALM->ALARMDAY;
  RTC_ALM_AlarmStruct->AlarmHours      = RTCALM->ALARMHOUR;
  RTC_ALM_AlarmStruct->AlarmMinutes    = RTCALM->ALARMMIN;
  RTC_ALM_AlarmStruct->AlarmSeconds    = RTCALM->ALARMSEC;
}

/**
  * @brief  Enables or disables the RTC Alarm.
  * @param  NewState: new state of the RTC Alarm function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTCEx_AlarmCmd(FunctionalState NewState)
{
  uint32_t tmp;

  /* Parameter check */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmp = RTCALM->ALARMCTL;
  if(NewState == ENABLE)
  {
    tmp |= RTC_ALM_ALARMCTL_ALARMEN;
  }
  else
  {
    tmp &= ~RTC_ALM_ALARMCTL_ALARMEN;
  }
  RTCALM->ALARMCTL = tmp;
  /* Sync */
  RTCEx_WaitForAlarmSync();
}


/**
  * @brief  Enables or disables RTC alarm or low-power wakeup interrupt.
  * @param  INTMask: specifies the RTC alarm or low-power interrupt to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *           @arg RTC_ALM_INT_ALARM
  *           @arg RTC_ALM_INT_WKUCNT
  *           @arg RTC_ALM_INT_WKUMIDNIGHT
  *           @arg RTC_ALM_INT_WKUHOUR
  *           @arg RTC_ALM_INT_WKUMIN
  *           @arg RTC_ALM_INT_WKUSEC
  *           @arg RTC_ALM_INT_ITVSITV
  * @param   NewState: new state of the RTC alarm or low-power interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTCEx_AlarmLPWKUINTConfig(uint32_t INTMask, FunctionalState NewState)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_INTC(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if(NewState == ENABLE)
  {
    RTCALM->INTEN |= INTMask;
  }
  else
  {
    RTCALM->INTEN &= ~INTMask;
  }
}

/**
  * @brief  Gets RTC alarm or low-power wakeup interrupt status.
  * @param  INTMask: specifies the RTC alarm or low-power interrupts to check.
  *         This parameter can be one of the following values:
  *           @arg RTC_ALM_INT_ALARM
  *           @arg RTC_ALM_INT_WKUCNT
  *           @arg RTC_ALM_INT_WKUHOUR
  *           @arg RTC_ALM_INT_WKUMIN
  *           @arg RTC_ALM_INT_WKUSEC
  *           @arg RTC_ALM_INT_ITVSITV
  * @retval The new state of RTC low-power interrupt. (SET or RESET).
  */
ITStatus RTCEx_GetAlarmLPWKUINTStatus(uint32_t INTMask)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_INTR(INTMask));

  if(RTCALM->INTSTS & INTMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears RTC alram or low-power wakeup interrupt status.
  * @param  INTMask: specifies the RTC alarm or low-power interrupts status to clear.
  *         This parameter can be any combination of the following values:
  *           @arg RTC_ALM_INT_ALARM
  *           @arg RTC_ALM_INT_WKUCNT
  *           @arg RTC_ALM_INT_WKUHOUR
  *           @arg RTC_ALM_INT_WKUMIN
  *           @arg RTC_ALM_INT_WKUSEC
  *           @arg RTC_ALM_INT_ITVSITV
  * @retval  None
  */
void RTCEx_ClearAlarmLPWKUINTStatus(uint32_t INTMask)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ALM_INTC(INTMask));

  RTCALM->INTSTS = INTMask;
}

/**
  * @brief  Configures RTC wakeup source for sleep mode.
  * @param  Wakeup_Event:
            This parameter can be any combination of the following values
              @arg RTCEVT_ALARM
              @arg RTCEVT_WKUCNT
              @arg RTCEVT_MIDNIGHT
              @arg RTCEVT_WKUHOUR
              @arg RTCEVT_WKUMIN
              @arg RTCEVT_WKUSEC
              @arg RTCEVT_ITVSITV
  * @retval None
  */
void RTCEx_SleepWKUSRCConfig(uint32_t Wakeup_Event)
{
  /* Check parameters */
  assert_parameters(IS_RTCEVT(Wakeup_Event));

  RTCALM->INTSTS = Wakeup_Event;
  /* Enable RTC interrupt */
  RTCALM->INTEN |= Wakeup_Event;

}

/**
  * @brief  Configures RTC wakeup source for deep sleep mode.
  * @param  Wakeup_Event:
            This parameter can be any combination of the following values
              @arg RTCEVT_ALARM
              @arg RTCEVT_WKUCNT
              @arg RTCEVT_MIDNIGHT
              @arg RTCEVT_WKUHOUR
              @arg RTCEVT_WKUMIN
              @arg RTCEVT_WKUSEC
              @arg RTCEVT_ITVSITV
  * @retval None
  */
void RTCEx_DSleepWKUSRCConfig(uint32_t Wakeup_Event)
{
  /* Check parameters */
  assert_parameters(IS_RTCEVT(Wakeup_Event));

  /* Clear interrupt flag */
  RTCALM->INTSTS = Wakeup_Event;
  /* Enable RTC interrupt */
  RTCALM->INTEN |= Wakeup_Event;
}


/**
  * @brief  Configures RTC only wakeup time.
  * @param  RTC_WKUTimeStruct: pointer to a RTC_WKUTimeType structure that contains 
  *                        the time configuration information for the RTC wakeup.
  * @retval None 
  */
void RTCEx_SetRTCOnlyWKUTime(RTC_WKUTimeType *RTC_WKUTimeStruct)
{
  /* Parameter check */
  assert_parameters(IS_RTC_TIME_YEAR(RTC_WKUTimeStruct->Year));
  assert_parameters(IS_RTC_TIME_MONTH(RTC_WKUTimeStruct->Month));
  assert_parameters(IS_RTC_TIME_DATE(RTC_WKUTimeStruct->Date)); 
  assert_parameters(IS_RTC_TIME_HOURS(RTC_WKUTimeStruct->Hours)); 
  assert_parameters(IS_RTC_TIME_MINS(RTC_WKUTimeStruct->Minutes)); 
  assert_parameters(IS_RTC_TIME_SECS(RTC_WKUTimeStruct->Seconds));
  assert_parameters(IS_RTC_WKU_TIME_MASK(RTC_WKUTimeStruct->WKUMask));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  RTC->WKUYEAR  = RTC_WKUTimeStruct->Year;
  RTC->WKUMONTH = RTC_WKUTimeStruct->Month;
  RTC->WKUDAY   = RTC_WKUTimeStruct->Date;
  RTC->WKUHOUR  = RTC_WKUTimeStruct->Hours;
  RTC->WKUMIN   = RTC_WKUTimeStruct->Minutes;
  RTC->WKUSEC   = RTC_WKUTimeStruct->Seconds;
  RTC->WKUCTRL  = RTC_WKUTimeStruct->WKUMask;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Enables or disables RTC only wakeup function.
  * @param  NewState: new state of the Wakeup function
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None 
  */
void RTCEx_RTCOnlyWKUCmd(FunctionalState NewState)
{
  uint32_t tmp;
  
  /* Parameter check */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = RTC->WKUCTRL;
  if (NewState != DISABLE)
  {
    tmp |= RTC_ANA_RTC_WKU_ENABLE;
  }
  else
  {
    tmp &= ~RTC_ANA_RTC_WKU_ENABLE;
  }

  RTC_WaitForSynchro();
  RTC_WriteProtection(DISABLE);
  
  RTC->WKUCTRL = tmp;
  
  RTC_WriteProtection(ENABLE);
  RTC_WaitForSynchro();
}

/**
  * @brief  Checks whether the specified RTC only wakeup flag is set or not .
  * @param  WKU_FLAG: specifies the flag to check. 
  *   This parameter can be one of the following values:
  *     @arg RTC_ANA_RTC_WKU_STS: RTC time wake up flag
  *     @arg RTC_ANA_RTC_CMP_WKU_STS: RTC comparator wake up flag
  *     @arg RTC_ANA_PC13_WKU_STS: GPIO PC13 wake up flag
  *     @arg RTC_ANA_PC14_WKU_STS: GPIO PC14 wake up flag
  *     @arg RTC_ANA_PC15_WKU_STS: GPIO PC15 wake up flag
  *     @arg RTC_ANA_PI8_WKU_STS: GPIO PI8 wake up flag
  *     @arg RTC_ANA_TIMER_WKU_STS: timer wake up flag
  * @retval The new state of WKU_FLAG (SET or RESET).
  */
FlagStatus RTCEx_GetRTCOnlyWKUStatus(uint32_t WKU_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_parameters(IS_RTC_ANA_WKU_STS(WKU_FLAG));
  
  if ((RTCANA->WKUSTS & WKU_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Gets all wakeup flags set in RTC only.
  * @param  None
  * @retval The RTC only wakeup flags.
  */
uint32_t RTCEx_GetAllRTCOnlyWKUStatus(void)
{
  return (RTCANA->WKUSTS&RTC_ANA_WKU_STS_MAKS);
}

/**
  * @brief  Clears RTC only wakeup source.
  * @param  WKU_FLAG: specifies the flag to check. 
  *   This parameter can be one of the following values:
  *     @arg RTC_ANA_RTC_WKU_STS: RTC wake up flag
  *     @arg RTC_ANA_RTC_CMP_WKU_STS: RTC comparator wake up flag
  *     @arg RTC_ANA_PC13_WKU_STS: GPIO PC13 wake up flag
  *     @arg RTC_ANA_PC14_WKU_STS: GPIO PC14 wake up flag
  *     @arg RTC_ANA_PC15_WKU_STS: GPIO PC15 wake up flag
  *     @arg RTC_ANA_PI8_WKU_STS: GPIO PI8 wake up flag
  *     @arg RTC_ANA_TIMER_WKU_STS: Low power timer wake up flag
  * @retval None
  */
void RTCEx_ClearRTCOnlyWKUStatus(uint32_t WKU_FLAG)
{
  /* Check the parameters */
  assert_parameters(IS_RTC_ANA_WKU_STS(WKU_FLAG));
  
  RTCANA->WKUSTS &= (~WKU_FLAG);
}


/**
  * @brief  Configures high-frequency PLL clock divide function.
  * @param  ClkSrc: source of PLL clock
  *          This parameter can be one of the following values:
  *           @arg RTC_ALM_PLLDIVCLK_PCLK
  *           @arg RTC_ALM_PLLDIVCLK_PLL1
  * @param  PLLDIV: 26-bit PLL divider, the actual clock divider is 2*(PLLDIV+1)
  * @retval None
  */
void RTC_ALM_HighFreqDivideConfig(uint32_t ClkSrc, uint32_t PLLDIV)
{
  /* Check parameters */
  assert_parameters(IS_RTC_ALM_PLLDIVCLK(ClkSrc));
  assert_parameters(IS_RTC_ALM_PLLDIV(PLLDIV));

  RTCALM->PLLDIV = PLLDIV;
  RTCALM->DIVCAPCTRL = ClkSrc | RTC_ALM_DIVCAPMODE_DIVIDE;
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
