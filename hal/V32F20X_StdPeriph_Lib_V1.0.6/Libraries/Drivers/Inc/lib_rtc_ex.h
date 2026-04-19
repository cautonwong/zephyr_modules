/**
  ******************************************************************************
  * @file    lib_rtc_ex.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-03-05
  * @brief   This file contains all the functions prototypes for the RTC analog
  *          controller and RTC wakeup alarm firmware library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_RTC_EX_H
#define __LIB_RTC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"


/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC_EX
  * @{
  */


#define RTC_ANA_SW_RST_ADC        ((uint32_t)0x00000001)
#define RTC_ANA_SW_RST_RTC        ((uint32_t)0x00000002)
#define RTC_ANA_SW_RST_COMP       ((uint32_t)0x00000004)
#define RTC_ANA_SW_RST_IO         ((uint32_t)0x00000008)
#define RTC_ANA_SW_RST_RTC_TIMER  ((uint32_t)0x00000010)
#define IS_RTC_ANA_SW_RST_SRC(__SRC__)  (((__SRC__) == RTC_ANA_SW_RST_ADC      )  || \
                                         ((__SRC__) == RTC_ANA_SW_RST_RTC      )  || \
                                         ((__SRC__) == RTC_ANA_SW_RST_COMP      )  || \
                                         ((__SRC__) == RTC_ANA_SW_RST_IO       )  || \
                                         ((__SRC__) == RTC_ANA_SW_RST_RTC_TIMER))



#define IS_RTC_ANA_TIMER_COUNT_VAL(__VAL__) (((__VAL__) & (uint32_t)0x80000000) == 0)



#define RTC_ANA_PI8     ((uint32_t)0x00000003)
#define RTC_ANA_PC15    ((uint32_t)0x00000002)
#define RTC_ANA_PC14    ((uint32_t)0x00000001)
#define RTC_ANA_PC13    ((uint32_t)0x00000000)
#define IS_RTC_ANA_GPIO_PIN(__PIN__)  ((__PIN__) <= (uint32_t)0x00000003)


#define RTC_ANA_CLK_RTC_TIMER            ((uint32_t)0x00000004)
#define RTC_ANA_CLK_RTC_IO               ((uint32_t)0x00000002)
#define RTC_ANA_CLK_RTC_CMP              ((uint32_t)0x00000001)
#define IS_RTC_ANA_CLK_SRC(__SRC__)      (((__SRC__) == RTC_ANA_CLK_RTC_TIMER) || \
                                          ((__SRC__) == RTC_ANA_CLK_RTC_IO   ) || \
                                          ((__SRC__) == RTC_ANA_CLK_RTC_CMP  ))




#define IS_RTC_ALM_WKUSEC_PERIOD(__PERIOD__)  (((__PERIOD__) <= (uint32_t)64) && ((__PERIOD__) > 0))
#define IS_RTC_ALM_WKUMIN_PERIOD(__PERIOD__)  (((__PERIOD__) <= (uint32_t)64) && ((__PERIOD__) > 0))
#define IS_RTC_ALM_WKUHOUR_PERIOD(__PERIOD__)  (((__PERIOD__) <= (uint32_t)32) && ((__PERIOD__) > 0))
#define IS_RTC_ALM_WKUCNT_PERIOD(__PERIOD__)  (((__PERIOD__) < (uint32_t)0x01000001) && ((__PERIOD__) > 0))

//CNTCLK
#define RTC_ALM_WKUCNT_32768               ((uint32_t)0x00000000)
#define RTC_ALM_WKUCNT_2048                ((uint32_t)0x01000000)
#define RTC_ALM_WKUCNT_512                 ((uint32_t)0x02000000)
#define RTC_ALM_WKUCNT_128                 ((uint32_t)0x03000000)
#define IS_RTC_ALM_WKUCNT_CNTSEL(__CNTSEL__)  (((__CNTSEL__) == RTC_ALM_WKUCNT_32768) ||\
                                             ((__CNTSEL__) == RTC_ALM_WKUCNT_2048)   ||\
                                             ((__CNTSEL__) == RTC_ALM_WKUCNT_512)    ||\
                                             ((__CNTSEL__) == RTC_ALM_WKUCNT_128))

//RTC_ALM_ITV
#define RTC_ALM_ITV_SEC                    ((uint32_t)0x00000000)
#define RTC_ALM_ITV_MIN                    ((uint32_t)0x00000001)
#define RTC_ALM_ITV_HOUR                   ((uint32_t)0x00000002)
#define RTC_ALM_ITV_DATE                   ((uint32_t)0x00000003)
#define RTC_ALM_ITV_500MS                  ((uint32_t)0x00000004)
#define RTC_ALM_ITV_250MS                  ((uint32_t)0x00000005)
#define RTC_ALM_ITV_125MS                  ((uint32_t)0x00000006)
#define RTC_ALM_ITV_62_5MS                 ((uint32_t)0x00000007)
//RTC_ALM_SITV
#define RTC_ALM_ITV_SITVSEC                ((uint32_t)0x00000007)
#define RTC_ALM_SITV_EN                    ((uint32_t)0x00000040)
#define IS_RTC_ALM_ITV(__ITV__)            (((__ITV__) == RTC_ALM_ITV_SEC)     ||\
                                          ((__ITV__) == RTC_ALM_ITV_MIN)     ||\
                                          ((__ITV__) == RTC_ALM_ITV_HOUR)    ||\
                                          ((__ITV__) == RTC_ALM_ITV_DATE)     ||\
                                          ((__ITV__) == RTC_ALM_ITV_500MS)   ||\
                                          ((__ITV__) == RTC_ALM_ITV_250MS)   ||\
                                          ((__ITV__) == RTC_ALM_ITV_125MS)   ||\
                                          ((__ITV__) == RTC_ALM_ITV_62_5MS))
#define IS_RTC_ALM_SITV(__SITV__)          (((__SITV__) <= 64) && ((__SITV__) > 0))

//ALARM MASK
#define RTC_ALM_ALARM_MASK_YEAR      ((uint32_t)0x00000040)
#define RTC_ALM_ALARM_MASK_MONTH     ((uint32_t)0x00000020)
#define RTC_ALM_ALARM_MASK_DATE      ((uint32_t)0x00000010)
#define RTC_ALM_ALARM_MASK_HOUR      ((uint32_t)0x00000008)
#define RTC_ALM_ALARM_MASK_MIN       ((uint32_t)0x00000004)
#define RTC_ALM_ALARM_MASK_SEC       ((uint32_t)0x00000002)
#define RTC_ALM_ALARM_MASK           ((uint32_t)0x0000007E)
#define IS_RTC_ALM_ALARMTIME_MASK(__MASK__)  (((__MASK__) != 0)&&(((__MASK__) & ~RTC_ALM_ALARM_MASK) == 0))

/* Year      0 ~ 99 */  
#define IS_RTC_ALM_ALARMTIME_YEAR(__YEAR__)        (((__YEAR__) < (uint32_t)0x0000009A) && (((__YEAR__)&0xf) < (uint32_t)0x0000000A))
/* Month     1 ~ 12 */ 
#define IS_RTC_ALM_ALARMTIME_MONTH(__MONTH__)      (((__MONTH__) > 0x0) && ((__MONTH__) < (uint32_t)0x00000013) && (((__MONTH__)&0x0000000f) < (uint32_t)0x0000000A))
/* Date      1 ~ 31 */ 
#define IS_RTC_ALM_ALARMTIME_DATE(__DATE__)        (((__DATE__) > 0x0) && ((__DATE__) < (uint32_t)0x00000032) && (((__DATE__)&0x0000000f) < (uint32_t)0x0000000A))
/* Hours     0 ~ 23 */
#define IS_RTC_ALM_ALARMTIME_HOURS(__HOURS__)      ((__HOURS__) < (uint32_t)0x24UL && (((__HOURS__)&0x0000000f) < (uint32_t)0x0000000A))
/* Minutes   0 ~ 59 */                 
#define IS_RTC_ALM_ALARMTIME_MINS(__MINS__)        ((__MINS__) < (uint32_t)0x5AUL && (((__MINS__)&0x0000000f) < (uint32_t)0x0000000A))
/* Seconds   0 ~ 59 */                 
#define IS_RTC_ALM_ALARMTIME_SECS(__SECS__)        ((__SECS__) < (uint32_t)0x5AUL && (((__SECS__)&0x0000000f) < (uint32_t)0x0000000A))


//INT
#define RTC_ALM_INT_ALARM              ((uint32_t)0x00000040)
#define RTC_ALM_INT_WKUCNT             ((uint32_t)0x00000020)
#define RTC_ALM_INT_WKUMIDNIGHT        ((uint32_t)0x00000010)
#define RTC_ALM_INT_WKUHOUR            ((uint32_t)0x00000008)
#define RTC_ALM_INT_WKUMIN             ((uint32_t)0x00000004)
#define RTC_ALM_INT_WKUSEC             ((uint32_t)0x00000002)
#define RTC_ALM_INT_ITVSITV            ((uint32_t)0x00000001)
#define RTC_ALM_INT_MASK               ((uint32_t)0x0000007F)
#define IS_RTC_ALM_INTC(__INT__)       ((((__INT__) & RTC_ALM_INT_MASK) != 0) &&\
                                        (((__INT__) & ~RTC_ALM_INT_MASK) == 0))
#define IS_RTC_ALM_INTR(__INT__)       (((__INT__) == RTC_ALM_INT_ALARM)    ||\
                                        ((__INT__) == RTC_ALM_INT_WKUCNT)   ||\
                                        ((__INT__) == RTC_ALM_INT_WKUMIDNIGHT)  ||\
                                        ((__INT__) == RTC_ALM_INT_WKUHOUR)  ||\
                                        ((__INT__) == RTC_ALM_INT_WKUMIN)   ||\
                                        ((__INT__) == RTC_ALM_INT_WKUSEC)   ||\
                                        ((__INT__) == RTC_ALM_INT_ITVSITV))

//RTCEVT
#define RTCEVT_ALARM             RTC_ALM_INT_ALARM
#define RTCEVT_WKUCNT            RTC_ALM_INT_WKUCNT
#define RTCEVT_MIDNIGHT          RTC_ALM_INT_WKUMIDNIGHT
#define RTCEVT_WKUHOUR           RTC_ALM_INT_WKUHOUR
#define RTCEVT_WKUMIN            RTC_ALM_INT_WKUMIN
#define RTCEVT_WKUSEC            RTC_ALM_INT_WKUSEC
#define RTCEVT_ITVSITV           RTC_ALM_INT_ITVSITV
#define RTCEVT_MSK               RTC_ALM_INT_MASK
#define IS_RTCEVT(__EVT__)       ((((__EVT__) & RTCEVT_MSK) != 0) &&\
                                  (((__EVT__) & ~RTCEVT_MSK) == 0))

#define RTC_WKU_YEAR_MASK               ((uint32_t)0x00000040)
#define RTC_WKU_MONTH_MASK              ((uint32_t)0x00000020)
#define RTC_WKU_DAY_MASK                ((uint32_t)0x00000010)
#define RTC_WKU_HOUR_MASK               ((uint32_t)0x00000008)
#define RTC_WKU_MIN_MASK                ((uint32_t)0x00000004)
#define RTC_WKU_SEC_MASK                ((uint32_t)0x00000002)
#define IS_RTC_WKU_TIME_MASK(__MASK__)  (((__MASK__) & ~((uint32_t)0x7E)) == 0)

#define RTC_ANA_RTC_WKU_STS                   ((uint32_t)0x00000001)
#define RTC_ANA_RTC_CMP_WKU_STS               ((uint32_t)0x00000002)
#define RTC_ANA_PC13_WKU_STS                  ((uint32_t)0x00000004)
#define RTC_ANA_PC14_WKU_STS                  ((uint32_t)0x00000008)
#define RTC_ANA_PC15_WKU_STS                  ((uint32_t)0x00000010)
#define RTC_ANA_PI8_WKU_STS                   ((uint32_t)0x00000020)
#define RTC_ANA_TIMER_WKU_STS                 ((uint32_t)0x00000040)
#define RTC_ANA_WKU_STS_MAKS                  ((uint32_t)0x0000007F)
#define IS_RTC_ANA_WKU_STS(__STS__)           (((__STS__) == RTC_ANA_RTC_WKU_STS)      || \
                                               ((__STS__) == RTC_ANA_RTC_CMP_WKU_STS ) || \
                                               ((__STS__) == RTC_ANA_PC13_WKU_STS )    || \
                                               ((__STS__) == RTC_ANA_PC14_WKU_STS )    || \
                                               ((__STS__) == RTC_ANA_PC15_WKU_STS )    || \
                                               ((__STS__) == RTC_ANA_PI8_WKU_STS )     || \
                                               ((__STS__) == RTC_ANA_TIMER_WKU_STS ))
//RTC Only EXTI interrrupt status
#define RTC_EXTI_CFG_INT3_STS                 (1 << 19)
#define RTC_EXTI_CFG_INT2_STS                 (1 << 18)
#define RTC_EXTI_CFG_INT1_STS                 (1 << 17)
#define RTC_EXTI_CFG_INT0_STS                 (1 << 16)
#define RTC_EXTI_CFG_INT_MASK                 ((uint32_t)0xF << 16)
#define IO_RTC_EXTI_INT(__INT__)              (((__INT__&RTC_EXTI_CFG_INT_MASK) != 0)\
                                              && ((__INT__&(~RTC_EXTI_CFG_INT_MASK)) == 0))
                                              
#define  RTC_CLKSRC_32KXTAL                   ((uint32_t)0x00000008)
#define  RTC_CLKSRC_32KRC                     ((uint32_t)0x00000000)
#define  RTC_CLKSRC_MASK                      ((uint32_t)0x00000008)

#define IS_RTC_ANA_RTCCLKSRC(__SRC__)  (((__SRC__) == RTC_CLKSRC_32KXTAL)  || \
                                        ((__SRC__) == RTC_CLKSRC_32KRC))

//RTCALM_DIVCAPCTRL
#define  RTC_ALM_PLLDIVCLK_PCLK               ((uint32_t)0x00000000)
#define  RTC_ALM_PLLDIVCLK_PLL1               ((uint32_t)0x00000008)
#define  RTC_ALM_PLLDIVCLK_MASK               ((uint32_t)0x00000008)

#define IS_RTC_ALM_PLLDIVCLK(CLK)             (((CLK) == RTC_ALM_PLLDIVCLK_PCLK)  || \
                                               ((CLK) == RTC_ALM_PLLDIVCLK_PLL1))

#define RTC_ALM_DIVCAPMODE_DIVIDE               ((uint32_t)0x00000000)
#define RTC_ALM_DIVCAPMODE_WAIT                 ((uint32_t)0x00000001)
#define RTC_ALM_DIVCAPMODE_CAPTURE              ((uint32_t)0x00000002)
#define RTC_ALM_DIVCAPMODE_IDLE                 ((uint32_t)0x00000003)
#define RTC_ALM_DIVCAPMODE_MASK                 ((uint32_t)0x00000003)

#define IS_RTC_ALM_DIVCAPMODE(MODE)            (((MODE) == RTC_ALM_DIVCAPMODE_DIVIDE) || \
                                               ((MODE) == RTC_ALM_DIVCAPMODE_WAIT) || \
                                               ((MODE) == RTC_ALM_DIVCAPMODE_CAPTURE) || \
                                               ((MODE) == RTC_ALM_DIVCAPMODE_IDLE))

#define IS_RTC_ALM_PLLDIV(PLLDIV)             ((PLLDIV) <= 0x3FFFFFF) 


/** @defgroup RTC_EX_Exported_Types
  * @{
  */

/* RTC Alarm Time struct */
typedef struct
{
  uint32_t AlarmMask;
  uint32_t AlarmYear;
  uint32_t AlarmMonth;
  uint32_t AlarmDate;
  uint32_t AlarmHours;
  uint32_t AlarmMinutes;
  uint32_t AlarmSeconds;
}RTC_ALM_AlarmType;

/**
  * @}
  */

/* RTC WKUTime struct */
typedef struct
{
  uint32_t Year;
  uint32_t Month;
  uint32_t Date;
  uint32_t Hours;
  uint32_t Minutes;
  uint32_t Seconds;
  uint32_t WKUMask;
} RTC_WKUTimeType;


/** @defgroup RTC_EX_Functions
  * @{
  */

/* Exported Functions ------------------------------------------------------- */
void RTCEx_WaitForAlarmSync(void);

void RTCEx_RTCANASWReset(uint32_t Source);

void RTCEx_GPIOEXTIDeInit(void);
void RTCEx_GPIOWKUInit(uint8_t Pin, uint8_t Event);
uint32_t RTCEx_GetAllEXTIINTStatus(void);
void RTCEx_ClearEXTIINTStatus(uint32_t INTMask);

void RTCEx_RTCTimerDeInit(void);
void RTCEx_RTCTimerCmd(FunctionalState NewState);
void RTCEx_RTCOnlyTimerWKUCmd(FunctionalState NewState);
void RTCEx_SetRTCTimerCount(uint32_t val);
void RTCEx_RTCWKUModuleClkCmd(uint32_t Src, FunctionalState NewState);
void RTCEx_EnterRTCOnlyMode(void);

void RTCEx_ClkSRCConfig(uint32_t RTCClkSrc);

void RTCEx_LPWKUSecondsConfig(uint8_t nPeriod);
void RTCEx_LPWKUMinutesConfig(uint8_t nPeriod);
void RTCEx_LPWKUHoursConfig(uint8_t nPeriod);
void RTCEx_LPWKUCounterConfig(uint32_t nClock, uint32_t CNTCLK);
void RTCEx_LPWKUITVConfig(uint8_t nType);
void RTCEx_LPWKUSITVConfig(uint8_t nPeriod);
uint32_t RTCEx_GetLPWKUCounterValue(void);

void RTCEx_SetAlarm(RTC_ALM_AlarmType *RTC_ALM_AlarmStruct);
void RTCEx_GetAlarm(RTC_ALM_AlarmType *RTC_ALM_AlarmStruct);
void RTCEx_AlarmCmd(FunctionalState NewState);

void RTCEx_AlarmLPWKUINTConfig(uint32_t INTMask, FunctionalState NewState);
ITStatus RTCEx_GetAlarmLPWKUINTStatus(uint32_t INTMask);
void RTCEx_ClearAlarmLPWKUINTStatus(uint32_t INTMask);
void RTCEx_SleepWKUSRCConfig(uint32_t Wakeup_Event);
void RTCEx_DSleepWKUSRCConfig(uint32_t Wakeup_Event);

void RTCEx_RTCOnlyWKUCmd(FunctionalState NewState);
void RTCEx_SetRTCOnlyWKUTime(RTC_WKUTimeType *RTC_WKUTimeStruct);
FlagStatus RTCEx_GetRTCOnlyWKUStatus(uint32_t WKU_FLAG);
uint32_t RTCEx_GetAllRTCOnlyWKUStatus(void);
void RTCEx_ClearRTCOnlyWKUStatus(uint32_t WKU_FLAG);

void RTC_ALM_HighFreqDivideConfig(uint32_t ClkSrc, uint32_t PLLDIV);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


 #endif /*  #ifndef __LIB_RTC_EX_H */