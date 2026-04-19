/**
  ******************************************************************************
  * @file    lib_pmu.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-06-30
  * @brief   PMU library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_PMU_H
#define __LIB_PMU_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup PMU
  * @{
  */

/** @defgroup PMU SLEEP CORE
  * @{
  */

#define SLEEP_CORE_CM33     ((uint8_t)0x33)
#define SLEEP_CORE_CM0      ((uint8_t)0x10)
#define IS_CHIP_CORE_SEL(__CORE__) (((__CORE__) == SLEEP_CORE_CM33)||((__CORE__) == SLEEP_CORE_CM0))

/**
  * @}
  */

/** @defgroup PMU Wakeup source
  * @{
  */

#define PMU_WKUSRC_XTAL         ((uint32_t)0x00000001)
#define PMU_WKUSRC_U32K1        ((uint32_t)0x00000002)
#define PMU_WKUSRC_U32K0        ((uint32_t)0x00000004)
#define PMU_WKUSRC_TIMER        ((uint32_t)0x00000008)
#define PMU_WKUSRC_IO           ((uint32_t)0x00000010)
#define PMU_WKUSRC_COMP         ((uint32_t)0x00000020)
#define PMU_WKUSRC_RTC_ALM      ((uint32_t)0x00000040)
#define PMU_WKUSRC_MSK          ((uint32_t)0x0000007F)
#define IS_PMU_WKU_SRC(__SRC__)  (((__SRC__)&PMU_WKUSRC_MSK) != 0 )

/**
  * @}
  */

/** @defgroup PMU interrupt status
  * @{
  */

#define PMU_STS_WDT0            ((uint32_t)0x00000800)  /* the last reset is coming from watch dog timer */
#define PMU_STS_WDT1            ((uint32_t)0x00000400)  /* the last reset is coming from watch dog timer */
#define PMU_STS_CM33RSTPMU      ((uint32_t)0x00000200)  /* the last interrupt is cause by PMU after CM33 wakes up from deep sleep/sleep */
#define PMU_STS_CM0RSTPMU       ((uint32_t)0x00000100)  /* the last interrupt is cause by PMU after CM0 wakes up from deep sleep/sleep */
#define PMU_STS_WDT2            ((uint32_t)0x00000080)  /* the last reset is coming from watch dog timer */
#define PMU_STS_DPORRST         ((uint32_t)0x00000040)
#define PMU_STS_PORRST          ((uint32_t)0x00000020)  /* the last reset is coming from internal power on reset */
#define PMU_STS_EXTRST          ((uint32_t)0x00000010)  /* the last reset is coming from external reset pin */
#define PMU_STS_RSTMASK         ((uint32_t)0x00000FF0)
#define IS_PMU_STS_RST(__STS__) ((__STS__&PMU_STS_RSTMASK)&& \
                                ((__STS__&(~PMU_STS_RSTMASK)) == 0))

/**
  * @}
  */

/** @defgroup PMU XTAL status
  * @{
  */

#define PMU_STS_XOH              ((uint32_t)0x00000008)
#define PMU_STS_XOL              ((uint32_t)0x00000004)
#define IS_PMU_STS_XTAL(__STS__) (((__STS__)==PMU_STS_XOH       ) || \
                                  ((__STS__)==PMU_STS_XOL       ))

/**
  * @}
  */

/** @defgroup PMU STS STATE
  * @{
  */
  
#define PMU_STS_STATE             ((uint32_t)0x0000F0000)

/**
  * @}
  */

/** @defgroup PMU wake up source
  * @{
  */
  
#define PMU_SLPWKU_RTC            ((uint32_t)0x00004000)  /* the previous wake up source from sleep mode is from RTC module */
#define PMU_SLPWKU_COMP           ((uint32_t)0x00002000)  /* the previous wake up source from sleep mode is from Analog module be compare */
#define PMU_SLPWKU_IO             ((uint32_t)0x00001000)  /* the previous wake up source from sleep mode is from IO wake-up */
#define PMU_SLPWKU_TIMER          ((uint32_t)0x00000800)  /* the previous wake up source from sleep mode is from timer */
#define PMU_SLPWKU_U32K0          ((uint32_t)0x00000400)  /* the previous wake up source from sleep mode is from LPUART32k 0 */
#define PMU_SLPWKU_U32K1          ((uint32_t)0x00000200)  /* the previous wake up source from deep sleep mode is from LPUART32k 1 */
#define PMU_SLPWKU_XTAL           ((uint32_t)0x00000100)  /* the previous wake up source from CM0 sleep mode is from crystal absent detection module */
#define PMU_SLPWKU_MASK           ((uint32_t)0x00007F00)

#define PMU_DSLPWKU_RTC           ((uint32_t)0x00000040)  /* the previous wake up source from deep sleep mode is from RTC module */
#define PMU_DSLPWKU_COMP          ((uint32_t)0x00000020)  /* the previous wake up source from deep sleep mode is from Analog module be compare */
#define PMU_DSLPWKU_IO            ((uint32_t)0x00000010)  /* the previous wake up source from deep sleep mode is from IO wakeup */
#define PMU_DSLPWKU_TIMER         ((uint32_t)0x00000008)  /* the previous wake up source from deep sleep mode is from timer */
#define PMU_DSLPWKU_U32K0         ((uint32_t)0x00000004)  /* the previous wake up source from deep sleep mode is from LPUART32k 0 */
#define PMU_DSLPWKU_U32K1         ((uint32_t)0x00000002)  /* the previous wake up source from deep sleep mode is from LPUART32k 1 */
#define PMU_DSLPWKU_XTAL          ((uint32_t)0x00000001)  /* the previous wake up source from CM33 deep sleep mode is from crystal absent detection module */
#define PMU_DSLPWKU_MASK          ((uint32_t)0x0000007F)

/**
  * @}
  */

/** @defgroup PUM Retention RAM mode switch
  * @{
  */

#define PMU_RAM_MODE_NORMAL            ((uint32_t)0x00000000)  /* normal RAM mode */
#define PMU_RAM_MODE_U32K              ((uint32_t)0x00000001)  /* UART32K buffer mode */
#define IS_PMU_RAM_MODE(__MOD__)       (((__MOD__)==PMU_RAM_MODE_NORMAL ) || \
                                        ((__MOD__)==PMU_RAM_MODE_U32K))
/**
  * @}
  */

/** @defgroup PUM Retention RAM mode switch
  * @{
  */

#define PMU_SRC_U32K0                 ((uint32_t)0x00000000)  /* UART32K0  */
#define PMU_SRC_U32K1                 ((uint32_t)0x00000001)  /* UART32K1  */
#define IS_PMU_SRC_U32K(__SRC__)      (((__SRC__)==PMU_SRC_U32K0 ) || \
                                       ((__SRC__)==PMU_SRC_U32K1))
/**
  * @}
  */


/** @defgroup PMU cycle count
  * @{
  */
  
#define PMU_CYCLE_PWG             ((uint32_t)0x00000010)
#define PMU_CYCLE_CKG             ((uint32_t)0x0000000C)
#define PMU_CYCLE_PWUP            ((uint32_t)0x00000008)
#define PMU_CYCLE_RST             ((uint32_t)0x00000004)
#define PMU_CYCLE_ISO             ((uint32_t)0x00000000)
#define IS_PMU_CYCLE_MODULE(__M__) (((__M__)==PMU_CYCLE_PWG ) || \
                                    ((__M__)==PMU_CYCLE_CKG ) || \
                                    ((__M__)==PMU_CYCLE_PWUP) || \
                                    ((__M__)==PMU_CYCLE_RST ) || \
                                    ((__M__)==PMU_CYCLE_ISO ))
#define IS_PMU_CYCLE_COUNT(__CNT__) (((__CNT__)>=0 ) &&((__CNT__)<=15 ))

/*
* SYSCON_LP_XTAL_EXIST_CTRL
*/
#define XTAL32K_EXIST_WKU               (1UL << 1)
#define XOH_EXIST_WKU                   (1UL << 3)
#define IS_XTAL_EXIST_WKU_EN(E)   (((E) == XTAL32K_EXIST_WKU) ||\
                                   ((E) == XOH_EXIST_WKU))
/**
  * @}
  */
  
/* Exported Functions ------------------------------------------------------- */

/** @defgroup GPIO_Exported_Functions
  * @{
  */

void PMU_EnterSleepMode(uint8_t CoreX);
void PMU_EnterDSleepMode(uint8_t CoreX);
void PMU_WKUINTConfig(uint8_t CoreX, FunctionalState NewState);
void PMU_WKUSRCConfig(uint8_t CoreX, uint32_t Src, FunctionalState NewState);
void PMU_WKUGPIOConfig(uint8_t CoreX, uint32_t PinX, FunctionalState NewState);
void PMU_CLKAUTO_Config(uint8_t CoreX, FunctionalState NewState);
void PMU_RETRAMConfig(uint32_t RamMode);
uint8_t PMU_GetResetSource(uint32_t Status);
uint8_t PMU_GetU32kReceive(uint32_t U32kSrc);
uint32_t PMU_GetAllResetSource();
void PMU_ClearResetSource(uint32_t rstsrc);
uint32_t PMU_GetXTALStatus(uint32_t Status);
uint32_t PMU_GetSleepWKUSource(uint8_t CoreX);
uint32_t PMU_GetDSleepWKUSource(uint8_t CoreX);
uint32_t PMU_GetPMUState(uint8_t CoreX);
uint8_t PMU_GetWKUInterruptStatus(uint8_t CoreX);
void PMU_ClearWKUInterruptStatus(uint8_t CoreX);
void PMU_WaitCycleConfig(uint32_t module, uint8_t cycle);
uint32_t PMU_GetXTALWKUStatus(void);
void PMU_ClearXTALWKUStatus(uint32_t WakeupSrc);
void PMU_XTALWKUSRCConfig(uint32_t WakeupSrc, FunctionalState NewState);

#ifdef __cplusplus
}
#endif
     
#endif /* __LIB_PMU_H */

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
