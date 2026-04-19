/**
  ******************************************************************************
  * @file    lib_rtc.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   RTC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_RTC_H
#define __LIB_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */


/*RTC ADC internal use*/
#define RTC_ADC_CHANNELMASK              ((uint32_t)0x000000F0)
#define RTC_ADC_CLKDIVMASK               ((uint32_t)0xFF000000)
#define RTC_ADC_AVERAGESAMPLEMASK        ((uint32_t)0x00700000)
#define RTC_ADC_AVERAGEENMASK            ((uint32_t)0x00000400)


/** @defgroup AccurateSel
  * @{
  */
#define RTC_ACCURATE            ((uint32_t)0x00000000)
#define RTC_INACCURATE          ((uint32_t)0x00000001)

/** @defgroup AutoTrigUnit
  * @{
  */
#define RTC_ACAutoTrigUnit_None   (0UL << 4)
#define RTC_ACAutoTrigUnit_Sec    (1UL << 4)
#define RTC_ACAutoTrigUnit_Min    (2UL << 4)
#define RTC_ACAutoTrigUnit_Hour   (3UL << 4)

/** @defgroup DataSource
  * @{
  */
#define RTC_ACDataSource_Hardware (0)
#define RTC_ACDataSource_Software (1UL << 3)

/** @defgroup IntMask
  * @{
  */
#define RTC_INT_TIMEILLE          (1UL << 0)
#define RTC_INT_CEILLE            (1UL << 1)
#define RTC_INT_ACDONE            (1UL << 2)

/* Private macros ------------------------------------------------------------*/
#define IS_RTC_REGOP_STARTADDR(__STARTADDR__) (((__STARTADDR__) & 0x3U) == 0U)
/* Year      0 ~ 99 */  
#define IS_RTC_TIME_YEAR(__YEAR__) ((__YEAR__) < 0x9AU)
/* Month     1 ~ 12 */ 
#define IS_RTC_TIME_MONTH(__MONTH__) (((__MONTH__) > 0x0U) && ((__MONTH__) < 0x13U))
/* Date      1 ~ 31 */ 
#define IS_RTC_TIME_DATE(__DATE__) (((__DATE__) > 0x0U) && ((__DATE__) < 0x32U))
/* Weekday   0 ~ 6 */
#define IS_RTC_TIME_WEEKDAY(__WEEKDAY__) ((__WEEKDAY__) < 0x7U)
/* Hours     0 ~ 23 */
#define IS_RTC_TIME_HOURS(__HOURS__) ((__HOURS__) < 0x24U)
/* Minutes   0 ~ 59 */
#define IS_RTC_TIME_MINS(__MINS__) ((__MINS__) < 0x5AU)
/* Seconds   0 ~ 59 */
#define IS_RTC_TIME_SECS(__SECS__) ((__SECS__) < 0x5AU)
/* SubSeconds   0 ~ 0x999 */
#define IS_RTC_TIME_SubSECS(__SubSECS__) ((__SubSECS__) < 0x1000U)
/* AccurateSel */
#define IS_RTC_ACCURATESEL(__ACCURATESEL__) (((__ACCURATESEL__) == RTC_ACCURATE) ||\
                                             ((__ACCURATESEL__) == RTC_INACCURATE))
/* AutoTrigUnit */
#define IS_RTC_AUTOCAL_ATCS(__ATCS__)  (((__ATCS__) == RTC_ACAutoTrigUnit_None) ||\
                                        ((__ATCS__) == RTC_ACAutoTrigUnit_Sec)  ||\
                                        ((__ATCS__) == RTC_ACAutoTrigUnit_Min)  ||\
                                        ((__ATCS__) == RTC_ACAutoTrigUnit_Hour))
/* DataSource */
#define IS_RTC_AUTOCAL_ADCSRC(__ADCSRC__)  (((__ADCSRC__) == RTC_ACDataSource_Hardware) ||\
                                            ((__ADCSRC__) == RTC_ACDataSource_Software))
/* AutoTrigPeriod */
#define IS_RTC_AUTOCAL_PERIOD(__PERIOD__) ((__PERIOD__) < 64U)
/* IntMask */
#define RTC_INT_MASK              (RTC_INT_TIMEILLE |\
                                   RTC_INT_CEILLE   |\
                                   RTC_INT_ACDONE)
#define IS_RTC_INTC(__INT__) ((((__INT__) & RTC_INT_MASK) != 0U) &&\
                              (((__INT__) & ~RTC_INT_MASK) == 0U))
#define IS_RTC_INTR(__INT__) (((__INT__) == RTC_INT_TIMEILLE) ||\
                              ((__INT__) == RTC_INT_CEILLE)   ||\
                              ((__INT__) == RTC_INT_ACDONE))





#define RTC_ADC_CHANNEL_TEMP             ((uint32_t)0x0000000A)

#define IS_RTC_ADC_CHANNEL(CHN)         ((CHN) == RTC_ADC_CHANNEL_TEMP)

#define RTC_ADC_AVERAGE_2              ((uint32_t)0x00000000)
#define RTC_ADC_AVERAGE_4              ((uint32_t)0x00100000)
#define RTC_ADC_AVERAGE_8              ((uint32_t)0x00200000)
#define RTC_ADC_AVERAGE_16             ((uint32_t)0x00300000)
#define RTC_ADC_AVERAGE_32             ((uint32_t)0x00400000)
#define RTC_ADC_AVERAGE_64             ((uint32_t)0x00500000)

#define IS_RTC_ADC_AVERAG(AVERAG)     (((AVERAG) == RTC_ADC_AVERAGE_2) || \
                                       ((AVERAG) == RTC_ADC_AVERAGE_4) || \
                                       ((AVERAG) == RTC_ADC_AVERAGE_8) || \
                                       ((AVERAG) == RTC_ADC_AVERAGE_16) || \
                                       ((AVERAG) == RTC_ADC_AVERAGE_32) || \
                                       ((AVERAG) == RTC_ADC_AVERAGE_64))

#define RTC_ADC_AVERAGE_ENABLE          (1UL<<10)
#define RTC_ADC_AVERAGE_DISABLE         (0UL<<10)
#define IS_RTC_ADC_AVERAGEEN(AVERAGEEN) (((AVERAGEEN) == RTC_ADC_AVERAGE_ENABLE) || \
                                         ((AVERAGEEN) == RTC_ADC_AVERAGE_DISABLE))

#define RTC_ADC_CLKDIV_1                ((uint32_t)0x00000000)
#define RTC_ADC_CLKDIV_2                ((uint32_t)0x01000000)
#define RTC_ADC_CLKDIV_3                ((uint32_t)0x02000000)
#define RTC_ADC_CLKDIV_4                ((uint32_t)0x03000000)

#define IS_RTC_ADC_CLKDIV(CLKDIV)      (((CLKDIV) == RTC_ADC_CLKDIV_1) || \
                                        ((CLKDIV) == RTC_ADC_CLKDIV_2) || \
                                        ((CLKDIV) == RTC_ADC_CLKDIV_3) || \
                                        ((CLKDIV) == RTC_ADC_CLKDIV_4))

/** @defgroup RTC_Exported_Types
  * @{
  */

/* RTC Time struct */
typedef struct
{
  uint32_t Year;
  uint32_t Month;
  uint32_t Date;
  uint32_t WeekDay;
  uint32_t Hours;
  uint32_t Minutes;
  uint32_t Seconds;
  uint32_t SubSeconds;
} RTC_TimeType;

/* RTC AutoCal struct */
typedef struct
{
  FunctionalState ADCJudgeCmd;
  uint32_t AutoTrigPeriod;
  uint32_t AutoTrigUnit;
  uint32_t DataSource;
} RTC_AutoCalType;

typedef struct
{
  uint32_t Channel;                     /*!< Select the RTC ADC channel to operate */
  uint32_t ClockDivider;                /*!< Config the RTC ADC clock divider */
  uint32_t AverageEnable;               /*!< Config the RTC ADC average enable */
  uint32_t AverageSample;               /*!< Config the RTC ADC average sample */
} RTC_ADC_InitType;


/* Exported Functions ------------------------------------------------------- */
/* RTC Exported Functions Group1: 
                                  Time functions -----------------------------*/
void RTC_SetTime(RTC_TimeType *sTime, uint32_t AccurateSel);
void RTC_GetTime(RTC_TimeType *gTime, uint32_t AccurateSel);
void RTC_SubSecondCmd(FunctionalState NewState);
/* RTC Exported Functions Group2: 
                                  Registers operation functions --------------*/
void RTC_WriteProtection(FunctionalState NewState);
void RTC_WaitForSynchro(void);
void RTC_WriteRegisters(uint32_t StartAddr, const uint32_t *wBuffer, uint8_t Len);
void RTC_ReadRegisters(uint32_t StartAddr, uint32_t *rBuffer, uint8_t Len);
/* RTC Exported Functions Group3: 
                                  AutoCal functions --------------------------*/
void RTC_AutoCalStructInit(RTC_AutoCalType *RTC_ACInitStruct);
void RTC_AutoCalInit(RTC_AutoCalType *RTC_ACInitStruct);
void RTC_AutoCalCmd(FunctionalState NewState);
void RTC_StartAutoCalManual(void);
void RTC_WaitForAutoCalManual(void);
FlagStatus RTC_GetACBusyFlag(void);

void RTC_ADC_StructInit(RTC_ADC_InitType *RTC_ADC_InitStruct);
void RTC_ADC_Init(RTC_ADC_InitType *RTC_ADC_InitStruct);
void RTC_ADC_StartManual(void);
FlagStatus RTC_ADC_GetConvValidFlagStatus(void);
void RTC_ADC_ClearConvValidFlag(void);
int16_t RTC_ADC_GetConvValue(void);

/* RTC Exported Functions Group4: 
                                  Interrupt functions ------------------------*/
void RTC_INTConfig(uint32_t IntMask, FunctionalState NewState);
ITStatus RTC_GetINTStatus(uint32_t IntMask);
void RTC_ClearINTStatus(uint32_t IntMask);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_RTC_H */

/*********************************** END OF FILE ******************************/
