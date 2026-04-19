/**
  ******************************************************************************
  * @file    lib_wdt.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   WDT library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_WDT_H
#define __LIB_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

#if defined (V32F20XXX_CM33_CORE0)
#define IS_WDT_ALL_PERIPH(PERIPH) (((PERIPH) == WDT0) || \
                                   ((PERIPH) == WDT1) || \
                                   ((PERIPH) == WDT2))
#endif /* V32F20XXX_CM33_CORE0 */
#if defined (V32F20XXX_CM33_CORE1)
#define IS_WDT_ALL_PERIPH(PERIPH) ((PERIPH) == WDT1)
#endif /* V32F20XXX_CM33_CORE1 */
#if defined (V32F20XXX_CM0_CORE)
#define IS_WDT_ALL_PERIPH(PERIPH) ((PERIPH) == WDT2)
#endif /* V32F20XXX_CM0_CORE */

/** @defgroup WDT_Period WDT Period
  * @{
  */
#define WDT_PERIOD_2S                          (0UL << 2)
#define WDT_PERIOD_4S                          (1UL << 2)
#define WDT_PERIOD_8S                          (2UL << 2)
#define WDT_PERIOD_16S                         (3UL << 2)
#define WDT_PERIOD_MASK                        (3UL << 2)
#define IS_WDT_PERIOD(PERIOD) (((PERIOD) == WDT_PERIOD_2S) ||\
                               ((PERIOD) == WDT_PERIOD_4S) ||\
                               ((PERIOD) == WDT_PERIOD_8S) ||\
                               ((PERIOD) == WDT_PERIOD_16S))


/* Exported functions --------------------------------------------------------*/ 

void      WDT_Cmd(WDT_Type *WDTx, FunctionalState NewState);
void      WDT_PeriodConfig(WDT_Type *WDTx, uint32_t WDT_Period);
void      WDT_WinValueConfig(WDT_Type *WDTx, uint16_t WDT_WinValue);
void      WDT_Clear(WDT_Type *WDTx);
uint16_t  WDT_GetCounterValue(WDT_Type *WDTx);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_WDT_H */

/*********************************** END OF FILE ******************************/
