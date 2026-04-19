/**
  ******************************************************************************
  * @file    lib_syscfg.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   SYSCON library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_SYSCON_H
#define __LIB_SYSCON_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/* Private types --------------------------------------------------------------*/
typedef struct
{
  uint32_t SYSCFG0_CfgPos;
  uint32_t SYSCFG0_CfgMask;
} SYSCFG0_CfgType;

/* Private constants ---------------------------------------------------------*/
#define SYSCFG0_KEY                                        (0xBEEFBEEFUL)

/* Flash 1us cycle configuration */
#define SYSCON_FLASH_1US_CYCLE_POS                          (4UL)
#define SYSCON_FLASH_1US_CYCLE_MASK                         (0x7FFFUL << SYSCON_FLASH_1US_CYCLE_POS)
/* FLASH ECC disable */
#define SYSCON_FLASH_ECC_DIS                                (1UL << 1)
/* FLASH Cache ECC disable */
#define SYSCON_FLASH_CACHE_ECC_DIS                          (1UL << 0)
/* SYSCFG0_CLK_DIV_MASK */
#define SYSCON_CLK_DIV_MASK                                 (0xFFUL)
#define IS_SYSCON_CLK_DIV(CLK_DIV) (((CLK_DIV) > 0UL) && ((CLK_DIV) < 256UL))

/* Private macro -------------------------------------------------------------*/
/* .max System clock value 200M */
#define IS_SYSCLK_VALUE(VALUE)                              ((VALUE) < 200000001UL)


#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

/* Private macro -------------------------------------------------------------*/
/* SYSCFG0_CM0_NONSEC_CFG */
#define SYSCFG0_CM0_NONSEC_CFG_SEC                         (1UL << 0)
#define SYSCFG0_CM0_NONSEC_CFG_PRIV                        (1UL << 1)
#define SYSCFG0_CM0_NONSEC_CFG_NONSEC                      (1UL << 16)
#define SYSCFG0_CM0_NONSEC_CFG_UNPRIV                      (1UL << 17)

/* Exported constants --------------------------------------------------------*/

/** @defgroup  SYSCFG0_CM0_SECPRIV Config
  * @{
  */
#define SYSCFG0_CM0_SEC_PRIV                               (SYSCFG0_CM0_NONSEC_CFG_SEC    |\
                                                             SYSCFG0_CM0_NONSEC_CFG_PRIV)
#define SYSCFG0_CM0_SEC_UNPRIV                             (SYSCFG0_CM0_NONSEC_CFG_SEC    |\
                                                             SYSCFG0_CM0_NONSEC_CFG_UNPRIV)
#define SYSCFG0_CM0_NONSEC_PRIV                            (SYSCFG0_CM0_NONSEC_CFG_NONSEC |\
                                                             SYSCFG0_CM0_NONSEC_CFG_PRIV)
#define SYSCFG0_CM0_NONSEC_UNPRIV                          (SYSCFG0_CM0_NONSEC_CFG_NONSEC |\
                                                             SYSCFG0_CM0_NONSEC_CFG_UNPRIV)
#define IS_SYSCFG0_CM0_SECPRIV(SECPRIV) (((SECPRIV) == SYSCFG0_CM0_SEC_PRIV)     ||\
                                          ((SECPRIV) == SYSCFG0_CM0_SEC_UNPRIV)   ||\
                                          ((SECPRIV) == SYSCFG0_CM0_NONSEC_PRIV)  ||\
                                          ((SECPRIV) == SYSCFG0_CM0_NONSEC_UNPRIV))

/** @defgroup  SYSCFG0_Periph reset
  * @{
  */
#define SYSCFG0_Periph0Reset_DCMI          ((uint32_t)0x80000000)
#define SYSCFG0_Periph0Reset_EADC          ((uint32_t)0x40000000)
#define SYSCFG0_Periph0Reset_SDIO1         ((uint32_t)0x20000000)
#define SYSCFG0_Periph0Reset_SDIO0         ((uint32_t)0x10000000)
#define SYSCFG0_Periph0Reset_I2S1          ((uint32_t)0x08000000)
#define SYSCFG0_Periph0Reset_WDT1          ((uint32_t)0x04000000)
#define SYSCFG0_Periph0Reset_WDT0          ((uint32_t)0x02000000)
#define SYSCFG0_Periph0Reset_DAC           ((uint32_t)0x01000000)
#define SYSCFG0_Periph0Reset_ISO78161      ((uint32_t)0x00800000)
#define SYSCFG0_Periph0Reset_ISO78160      ((uint32_t)0x00400000)
#define SYSCFG0_Periph0Reset_CAN1          ((uint32_t)0x00200000)
#define SYSCFG0_Periph0Reset_CAN0          ((uint32_t)0x00100000)
#define SYSCFG0_Periph0Reset_SCR           ((uint32_t)0x00080000)
#define SYSCFG0_Periph0Reset_WAVER33       ((uint32_t)0x00040000)
#define SYSCFG0_Periph0Reset_MAC1          ((uint32_t)0x00020000)
#define SYSCFG0_Periph0Reset_MAC0          ((uint32_t)0x00010000)
#define SYSCFG0_Periph0Reset_I2S0          ((uint32_t)0x00008000)
#define SYSCFG0_Periph0Reset_OSPI1         ((uint32_t)0x00004000)
#define SYSCFG0_Periph0Reset_OSPI0         ((uint32_t)0x00002000)
#define SYSCFG0_Periph0Reset_CRC           ((uint32_t)0x00001000)
#define SYSCFG0_Periph0Reset_ENCENG        ((uint32_t)0x00000800)
#define SYSCFG0_Periph0Reset_USBFS         ((uint32_t)0x00000400)
#define SYSCFG0_Periph0Reset_USBHS         ((uint32_t)0x00000100)
#define SYSCFG0_Periph0Reset_CRYPTCOP      ((uint32_t)0x00000040)
#define IS_SYSCFG0_PERIPH0RST(PERIPH) ((((PERIPH) & (~0xFFFFFD40)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFG0_Periph1 reset
  * @{
  */
#define SYSCFG0_Periph1Reset_DMA1          ((uint32_t)0x02000000)
#define SYSCFG0_Periph1Reset_DMA0          ((uint32_t)0x01000000)
#define SYSCFG0_Periph1Reset_RNG           ((uint32_t)0x00800000)
#define SYSCFG0_Periph1Reset_CMDA_ADC      ((uint32_t)0x00400000)
#define SYSCFG0_Periph1Reset_ADC           ((uint32_t)0x00200000)
#define SYSCFG0_Periph1Reset_GTMR3         ((uint32_t)0x00100000)
#define SYSCFG0_Periph1Reset_GTMR2         ((uint32_t)0x00080000)
#define SYSCFG0_Periph1Reset_GTMR1         ((uint32_t)0x00040000)
#define SYSCFG0_Periph1Reset_GTMR0         ((uint32_t)0x00020000)
#define SYSCFG0_Periph1Reset_ETMR1         ((uint32_t)0x00010000)
#define SYSCFG0_Periph1Reset_ETMR0         ((uint32_t)0x00008000)
#define SYSCFG0_Periph1Reset_BTMR0_3       ((uint32_t)0x00004000)
#define SYSCFG0_Periph1Reset_FC13          ((uint32_t)0x00002000)
#define SYSCFG0_Periph1Reset_FC12          ((uint32_t)0x00001000)
#define SYSCFG0_Periph1Reset_FC11          ((uint32_t)0x00000800)
#define SYSCFG0_Periph1Reset_FC10          ((uint32_t)0x00000400)
#define SYSCFG0_Periph1Reset_FC9           ((uint32_t)0x00000200)
#define SYSCFG0_Periph1Reset_FC8           ((uint32_t)0x00000100)
#define SYSCFG0_Periph1Reset_FC7           ((uint32_t)0x00000080)
#define SYSCFG0_Periph1Reset_FC6           ((uint32_t)0x00000040)
#define SYSCFG0_Periph1Reset_FC5           ((uint32_t)0x00000020)
#define SYSCFG0_Periph1Reset_FC4           ((uint32_t)0x00000010)
#define SYSCFG0_Periph1Reset_FC3           ((uint32_t)0x00000008)
#define SYSCFG0_Periph1Reset_FC2           ((uint32_t)0x00000004)
#define SYSCFG0_Periph1Reset_FC1           ((uint32_t)0x00000002)
#define SYSCFG0_Periph1Reset_FC0           ((uint32_t)0x00000001)
#define IS_SYSCFG0_PERIPH1RST(PERIPH) ((((PERIPH) & (~0x03FFFFFF)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFG0_Periph clock
  * @{
  */
#define SYSCFG0_Periph0Clock_DMA1           ((uint32_t) 0x00400000)
#define SYSCFG0_Periph0Clock_DMA0           ((uint32_t) 0x00200000)
#define SYSCFG0_Periph0Clock_DCMI           ((uint32_t) 0x00100000)
#define SYSCFG0_Periph0Clock_OSPI1          ((uint32_t) 0x00040000)
#define SYSCFG0_Periph0Clock_OSPI0          ((uint32_t) 0x00020000)
#define SYSCFG0_Periph0Clock_CRC            ((uint32_t) 0x00010000)
#define SYSCFG0_Periph0Clock_SDIO1          ((uint32_t) 0x00008000)
#define SYSCFG0_Periph0Clock_SDIO0          ((uint32_t) 0x00004000)
#define SYSCFG0_Periph0Clock_CRYPTCOP       ((uint32_t) 0x00002000)
#define SYSCFG0_Periph0Clock_USBFS          ((uint32_t) 0x00001000)
#define SYSCFG0_Periph0Clock_USBHS          ((uint32_t) 0x00000800)
#define SYSCFG0_Periph0Clock_ENCENG         ((uint32_t) 0x00000400)
#define SYSCFG0_Periph0Clock_MAC1           ((uint32_t) 0x00000200)
#define SYSCFG0_Periph0Clock_MAC0           ((uint32_t) 0x00000100)
#define SYSCFG0_Periph0Clock_CORE1          ((uint32_t) 0x00000002)
#define IS_SYSCFG0_PERIPH0CLK(PERIPH) ((((PERIPH) & (~0x0077FF02)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFG0_Periph clock
  * @{
  */
#define SYSCFG0_Periph1Clock_CDMA_ADC       ((uint32_t) 0x20000000)
#define SYSCFG0_Periph1Clock_WDT1           ((uint32_t) 0x10000000)
#define SYSCFG0_Periph1Clock_WDT0           ((uint32_t) 0x08000000)
#define SYSCFG0_Periph1Clock_WAVER33        ((uint32_t) 0x04000000)
#define SYSCFG0_Periph1Clock_SCR            ((uint32_t) 0x02000000)
#define SYSCFG0_Periph1Clock_EADC           ((uint32_t) 0x00800000)
#define SYSCFG0_Periph1Clock_DAC            ((uint32_t) 0x00400000)
#define SYSCFG0_Periph1Clock_RNG            ((uint32_t) 0x00200000)
#define SYSCFG0_Periph1Clock_ISO78161       ((uint32_t) 0x00100000)
#define SYSCFG0_Periph1Clock_ISO78160       ((uint32_t) 0x00080000)
#define SYSCFG0_Periph1Clock_ADC            ((uint32_t) 0x00040000)
#define SYSCFG0_Periph1Clock_I2S1           ((uint32_t) 0x00020000)
#define SYSCFG0_Periph1Clock_I2S0           ((uint32_t) 0x00010000)
#define SYSCFG0_Periph1Clock_CAN1           ((uint32_t) 0x00008000)
#define SYSCFG0_Periph1Clock_CAN0           ((uint32_t) 0x00004000)
#define SYSCFG0_Periph1Clock_FC13           ((uint32_t) 0x00002000)
#define SYSCFG0_Periph1Clock_FC12           ((uint32_t) 0x00001000)
#define SYSCFG0_Periph1Clock_FC11           ((uint32_t) 0x00000800)
#define SYSCFG0_Periph1Clock_FC10           ((uint32_t) 0x00000400)
#define SYSCFG0_Periph1Clock_FC9            ((uint32_t) 0x00000200)
#define SYSCFG0_Periph1Clock_FC8            ((uint32_t) 0x00000100)
#define SYSCFG0_Periph1Clock_FC7            ((uint32_t) 0x00000080)
#define SYSCFG0_Periph1Clock_FC6            ((uint32_t) 0x00000040)
#define SYSCFG0_Periph1Clock_FC5            ((uint32_t) 0x00000020)
#define SYSCFG0_Periph1Clock_FC4            ((uint32_t) 0x00000010)
#define SYSCFG0_Periph1Clock_FC3            ((uint32_t) 0x00000008)
#define SYSCFG0_Periph1Clock_FC2            ((uint32_t) 0x00000004)
#define SYSCFG0_Periph1Clock_FC1            ((uint32_t) 0x00000002)
#define SYSCFG0_Periph1Clock_FC0            ((uint32_t) 0x00000001)
#define IS_SYSCFG0_PERIPH1CLK(PERIPH) ((((PERIPH) & (~0x3EFFFFFF)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFG0_TMRClock config
  * @{
  */
#define SYSCFG0_TMRCLK_BPWM3                ((uint32_t) 0x00004000)
#define SYSCFG0_TMRCLK_BPWM2                ((uint32_t) 0x00002000)
#define SYSCFG0_TMRCLK_BPWM1                ((uint32_t) 0x00001000)
#define SYSCFG0_TMRCLK_BPWM0                ((uint32_t) 0x00000800)
#define SYSCFG0_TMRCLK_BTMR3                ((uint32_t) 0x00000400)
#define SYSCFG0_TMRCLK_BTMR2                ((uint32_t) 0x00000200)
#define SYSCFG0_TMRCLK_BTMR1                ((uint32_t) 0x00000100)
#define SYSCFG0_TMRCLK_BTMR0                ((uint32_t) 0x00000080)
#define SYSCFG0_TMRCLK_GTMR3                ((uint32_t) 0x00000040)
#define SYSCFG0_TMRCLK_GTMR2                ((uint32_t) 0x00000020)
#define SYSCFG0_TMRCLK_GTMR1                ((uint32_t) 0x00000010)
#define SYSCFG0_TMRCLK_GTMR0                ((uint32_t) 0x00000008)
#define SYSCFG0_TMRCLK_ETMR1                ((uint32_t) 0x00000004)
#define SYSCFG0_TMRCLK_ETMR0                ((uint32_t) 0x00000002)
#define SYSCFG0_TMRCLK_BTMR_BPWM_GLOBAL     ((uint32_t) 0x00000001)
#define IS_SYSCFG0_TMRCLK(TMRCLK) ((((TMRCLK) & (~0x00007FFF)) == 0x00) && ((TMRCLK) != 0x00))

/** @defgroup  SYSCFG0_BasicTMR config
  * @{
  */
#define SYSCFG0_BTMR0                                     (0UL)
#define SYSCFG0_BTMR1                                     (1UL)
#define SYSCFG0_BTMR2                                     (2UL)
#define SYSCFG0_BTMR3                                     (3UL)
#define SYSCFG0_BPWM0                                     (4UL)
#define SYSCFG0_BPWM1                                     (5UL)
#define SYSCFG0_BPWM2                                     (6UL)
#define SYSCFG0_BPWM3                                     (7UL)
#define IS_SYSCFG0_BTMR(BTMR) ((BTMR) < 8UL)

/** @defgroup  SYSCFG0_BasicTMR_ClkSel config
  * @{
  */
#define SYSCFG0_BTMR_CLKSRC_RCH                           (0UL)
#define SYSCFG0_BTMR_CLKSRC_PLL0                          (1UL)
#define SYSCFG0_BTMR_CLKSRC_PLL1                          (2UL)
#define SYSCFG0_BTMR_CLKSRC_XOH                           (3UL)
#define SYSCFG0_BTMR_CLKSRC_RCHD4                         (4UL)
#define SYSCFG0_BTMR_CLKSRC_RCHD48                        (5UL)
#define SYSCFG0_BTMR_CLKSRC_RCL                           (6UL)
#define SYSCFG0_BTMR_CLKSRC_XOL                           (7UL)
#define SYSCFG0_BTMR_CLKSRC_MASK                          (7UL)
#define SYSCFG0_BTMR_CLKSRC(CLKSRC) ((CLKSRC) < 8UL)

/** @defgroup  SYSCFG0_OSPI_ClkSel config
  * @{
  */
#define SYSCFG0_OSPI_CLKSRC_RCH                             (0UL)
#define SYSCFG0_OSPI_CLKSRC_PLL0                            (1UL)
#define SYSCFG0_OSPI_CLKSRC_PLL1                            (2UL)
#define SYSCFG0_OSPI_CLKSRC_XOH                             (3UL)
#define SYSCFG0_OSPI_CLKSRC_RCHD4                           (4UL)
#define SYSCFG0_OSPI_CLKSRC_RCHD48                          (5UL)
#define SYSCFG0_OSPI_CLKSRC_RCL                             (6UL)
#define SYSCFG0_OSPI_CLKSRC_XOL                             (7UL)
#define SYSCFG0_OSPI_CLKSRC_MASK                            (7UL)
#define IS_SYSCFG0_OSPI_CLKSRC(CLKSRC) ((CLKSRC) < 8UL)

/** @defgroup  SYSCFG0_OSPI_RDS_DLY config
  * @{
  */
#define SYSCFG0_OSPI_RDS_DLY_MASK                           (7UL)
#define IS_SYSCFG0_OSPI_RDS_DLY(DLY) ((DLY) < 8UL)

/** @defgroup  SYSCFG0_I2S_ClkSel config
  * @{
  */
#define SYSCFG0_I2S_CLKSRC_RCH                             (0UL)
#define SYSCFG0_I2S_CLKSRC_PLL0                            (1UL)
#define SYSCFG0_I2S_CLKSRC_PLL1                            (2UL)
#define SYSCFG0_I2S_CLKSRC_XOH                             (3UL)
#define SYSCFG0_I2S_CLKSRC_RCHD4                           (4UL)
#define SYSCFG0_I2S_CLKSRC_RCHD48                          (5UL)
#define SYSCFG0_I2S_CLKSRC_RCL                             (6UL)
#define SYSCFG0_I2S_CLKSRC_XOL                             (7UL)
#define IS_SYSCFG0_I2S_CLKSRC(CLKSRC) ((CLKSRC) < 8UL)

/** @defgroup  SYSCFG0_FCx config
  * @{
  */
#define SYSCFG0_FC_None                                    (0UL)
#define SYSCFG0_FC_UART                                    (1UL)
#define SYSCFG0_FC_SPI                                     (2UL)
#define SYSCFG0_FC_SPI_Slave                               (4UL)
#define SYSCFG0_FC_I2C                                     (8UL)
#define SYSCFG0_FC_SEL_MASK                                (0xFUL)
#define IS_SYSCFG0_FCSEL(FCSEL) (((FCSEL) == SYSCFG0_FC_None)      ||\
                                  ((FCSEL) == SYSCFG0_FC_UART)      ||\
                                  ((FCSEL) == SYSCFG0_FC_SPI)       ||\
                                  ((FCSEL) == SYSCFG0_FC_SPI_Slave) ||\
                                  ((FCSEL) == SYSCFG0_FC_I2C))

/** @defgroup  SYSCFG0_FC_ClkSel config
  * @{
  */
#define SYSCFG0_FC_CLKSRC_RCH                              (0UL)
#define SYSCFG0_FC_CLKSRC_PLL0                             (1UL)
#define SYSCFG0_FC_CLKSRC_PLL1                             (2UL)
#define SYSCFG0_FC_CLKSRC_XOH                              (3UL)
#define SYSCFG0_FC_CLKSRC_RCHD4                            (4UL)
#define SYSCFG0_FC_CLKSRC_RCHD48                           (5UL)
#define SYSCFG0_FC_CLKSRC_RCL                              (6UL)
#define SYSCFG0_FC_CLKSRC_XOL                              (7UL)
#define SYSCFG0_FC_CLKSRC_MASK                             (7UL)
#define IS_SYSCFG0_FC_CLKSRC(CLKSRC) ((CLKSRC) < 8UL)

/** @defgroup  SYSCFG0_ADC_ClkSel config
  * @{
  */
#define SYSCFG0_ADC_CLKSRC_RCHD48                          (0UL)
#define SYSCFG0_ADC_CLKSRC_PLL0                            (1UL)
#define SYSCFG0_ADC_CLKSRC_PLL1                            (2UL)
#define SYSCFG0_ADC_CLKSRC_RCH                             (3UL)
#define SYSCFG0_ADC_CLKSRC_RCHD4                           (4UL)
#define IS_SYSCFG0_ADC_CLKSRC(CLKSRC) ((CLKSRC) < 5UL)

/** @defgroup  SYSCFG0_ADC_RegularExtTrig config
  * @{
  */
#define SYSCFG0_ADCRegularExtTrig_EXTI11                   (0UL)
#define SYSCFG0_ADCRegularExtTrig_TMR2                     (1UL << 1)
#define IS_SYSCFG0_ADCRegularExtTrig(TRIG) (((TRIG) == SYSCFG0_ADCRegularExtTrig_EXTI11) ||\
                                             ((TRIG) == SYSCFG0_ADCRegularExtTrig_TMR2))

/** @defgroup  SYSCFG0_ADC_InjectedExtTrig config
  * @{
  */
#define SYSCFG0_ADC_InjectedExtTrig_EXTI15                 (0UL)
#define SYSCFG0_ADC_InjectedExtTrig_TMR2                   (1UL << 0)
#define IS_SYSCFG0_ADCInjectedExtTrig(TRIG) (((TRIG) == SYSCFG0_ADC_InjectedExtTrig_EXTI15) ||\
                                              ((TRIG) == SYSCFG0_ADC_InjectedExtTrig_TMR2))
                                              
                                              
/** @defgroup  SYSCFG0_ADC_Verf config
  * @{
  */
#define SYSCFG0_ADC_VERF_EXTI                              (0UL)
#define SYSCFG0_ADC_VERF_Internal                          (1UL << 0)
#define IS_SYSCFG0_ADC_VERF(VERF)           (((VERF) == SYSCFG0_ADC_VERF_EXTI) ||\
                                              ((VERF) == SYSCFG0_ADC_VERF_Internal))
                                              
                                              
/** @defgroup  SYSCFG0_ADC_Verf config
  * @{
  */
#define SYSCFG0_ADC_VERF_3_2V                              (0UL)
#define SYSCFG0_ADC_VERF_2_8V                              (1UL << 1)
#define SYSCFG0_ADC_VERF_2_4V                              (2UL << 1)
#define SYSCFG0_ADC_VERF_2_0V                              (3UL << 1)
#define SYSCFG0_ADC_VERF_1_6V                              (4UL << 1)
#define IS_SYSCFG0_ADC_VERF_VAL(VAL)        (((VAL) == SYSCFG0_ADC_VERF_3_2V) ||\
                                              ((VAL) == SYSCFG0_ADC_VERF_2_8V) ||\
                                              ((VAL) == SYSCFG0_ADC_VERF_2_4V) ||\
                                              ((VAL) == SYSCFG0_ADC_VERF_2_0V) ||\
                                              ((VAL) == SYSCFG0_ADC_VERF_1_6V))
                                              
                                              
                                              
/** @defgroup  SYSCFG0_DAC_Verf config
  * @{
  */
#define SYSCFG0_DAC_VERF_EXTI                              (0UL)
#define SYSCFG0_DAC_VERF_Internal                          (1UL << 16)
#define IS_SYSCFG0_DAC_VERF(VERF)           (((VERF) == SYSCFG0_DAC_VERF_EXTI) ||\
                                              ((VERF) == SYSCFG0_DAC_VERF_Internal))
                                              
                                              
/** @defgroup  SYSCFG0_ADC_Verf config
  * @{
  */
#define SYSCFG0_DAC_VERF_3_2V                              (0UL)
#define SYSCFG0_DAC_VERF_2_8V                              (1UL << 17)
#define SYSCFG0_DAC_VERF_2_4V                              (2UL << 17)
#define SYSCFG0_DAC_VERF_2_0V                              (3UL << 17)
#define SYSCFG0_DAC_VERF_1_6V                              (4UL << 17)
#define IS_SYSCFG0_DAC_VERF_VAL(VAL)        (((VAL) == SYSCFG0_DAC_VERF_3_2V) ||\
                                              ((VAL) == SYSCFG0_DAC_VERF_2_8V) ||\
                                              ((VAL) == SYSCFG0_DAC_VERF_2_4V) ||\
                                              ((VAL) == SYSCFG0_DAC_VERF_2_0V) ||\
                                              ((VAL) == SYSCFG0_DAC_VERF_1_6V))

/** @defgroup  SYSCFG0_CDMA_ADC_ClkSel config
  * @{
  */
#define SYSCFG0_CDMA_ADC_CLKSRC_RCH                        (0UL)
#define SYSCFG0_CDMA_ADC_CLKSRC_PLL0                       (1UL)
#define SYSCFG0_CDMA_ADC_CLKSRC_PLL1                       (2UL)
#define SYSCFG0_CDMA_ADC_CLKSRC_XOH                        (3UL)
#define SYSCFG0_CDMA_ADC_CLKSRC_RCHD4                      (4UL)
#define SYSCFG0_CDMA_ADC_CLKSRC_RCHD48                     (5UL)
#define SYSCFG0_CDMA_ADC_CLKSRC_RCL                        (6UL)
#define SYSCFG0_CDMA_ADC_CLKSRC_XOL                        (7UL)
#define IS_SYSCFG0_CDMAADC_CLKSRC(CLKSRC) ((CLKSRC) < 8UL)

/**
  * @}
  */

/** @defgroup  SYSCFG0_SDIO_ClkSel config
  * @{
  */
#define SYSCFG0_SDIO_CLKSRC_RCH                    ((uint32_t)0x00000000)
#define SYSCFG0_SDIO_CLKSRC_PLL0                   ((uint32_t)0x00000001)
#define SYSCFG0_SDIO_CLKSRC_PLL1                   ((uint32_t)0x00000002)
#define SYSCFG0_SDIO_CLKSRC_XOH                    ((uint32_t)0x00000003)
#define SYSCFG0_SDIO_CLKSRC_RCHD4                  ((uint32_t)0x00000004)
#define SYSCFG0_SDIO_CLKSRC_PLL0D                  ((uint32_t)0x00000005)
#define SYSCFG0_SDIO_CLKSRC_RCL                    ((uint32_t)0x00000006)
#define SYSCFG0_SDIO_CLKSRC_XOL                    ((uint32_t)0x00000007)
#define IS_SYSCFG0_SDIO_CLKSRC(CLKSRC)             ((CLKSRC) < 8UL)
/**
  * @}
  */
  
/** @defgroup  SYSCFG0_DAC_ClkSel config
  * @{
  */
#define SYSCFG0_DAC_CLKSRC_RCH                             (0UL)
#define SYSCFG0_DAC_CLKSRC_PLL0                            (1UL)
#define SYSCFG0_DAC_CLKSRC_PLL1                            (2UL)
#define SYSCFG0_DAC_CLKSRC_XOH                             (3UL)
#define SYSCFG0_DAC_CLKSRC_RCHD4                           (4UL)
#define SYSCFG0_DAC_CLKSRC_RCHD48                          (5UL)
#define IS_SYSCFG0_DAC_CLKSRC(CLKSRC) ((CLKSRC) < 6UL)

/** @defgroup  SYSCFG0_EADC_ClkSel config
  * @{
  */
#define SYSCFG0_EADC_CLKSRC_RCHD48                         (0UL)
#define SYSCFG0_EADC_CLKSRC_PLL0                           (1UL)
#define SYSCFG0_EADC_CLKSRC_PLL1                           (2UL)
#define SYSCFG0_EADC_CLKSRC_XOH                            (3UL)
#define SYSCFG0_EADC_CLKSRC_RCHD4                          (4UL)
#define SYSCFG0_EADC_CLKSRC_RCH                            (5UL)
#define IS_SYSCFG0_EADC_CLKSRC(CLKSRC) ((CLKSRC) < 6UL)

/** @defgroup  SYSCFG0_USBHS_ClkSel config
  * @{
  */
#define SYSCFG0_USBHS_CLKSRC_PLL0                          (0UL)
#define SYSCFG0_USBHS_CLKSRC_RCHD4                         (1UL)
#define SYSCFG0_USBHS_CLKSRC_PLL1                          (2UL)
#define SYSCFG0_USBHS_CLKSRC_XOH                           (3UL)
#define SYSCFG0_USBHS_CLKSRC_RCH                           (4UL)
#define IS_SYSCFG0_USBHS_CLKSRC(CLKSRC) ((CLKSRC) < 5UL)

/** @defgroup  SYSCFG0_USBFS_ClkSel config
  * @{
  */
#define SYSCFG0_USBFS_CLKSRC_RCH                           (0UL)
#define SYSCFG0_USBFS_CLKSRC_PLL0                          (1UL)
#define SYSCFG0_USBFS_CLKSRC_PLL1                          (2UL)
#define SYSCFG0_USBFS_CLKSRC_XOH                           (3UL)
#define IS_SYSCFG0_USBFS_CLKSRC(CLKSRC) ((CLKSRC) < 4UL)

/** @defgroup  SYSCFG0_DMAx_REQy config
  * @{
  */
#define SYSCFG0_DMA0_REQ0                       (0UL)
#define SYSCFG0_DMA0_REQ1                       (1UL)
#define SYSCFG0_DMA0_REQ2                       (2UL)
#define SYSCFG0_DMA0_REQ3                       (3UL)
#define SYSCFG0_DMA0_REQ4                       (4UL)
#define SYSCFG0_DMA0_REQ5                       (5UL)
#define SYSCFG0_DMA0_REQ6                       (6UL)
#define SYSCFG0_DMA0_REQ7                       (7UL)
#define SYSCFG0_DMA0_REQ8                       (8UL)
#define SYSCFG0_DMA0_REQ9                       (9UL)
#define SYSCFG0_DMA0_REQ10                      (10UL)
#define SYSCFG0_DMA0_REQ11                      (11UL)
#define SYSCFG0_DMA0_REQ12                      (12UL)
#define SYSCFG0_DMA0_REQ13                      (13UL)
#define SYSCFG0_DMA0_REQ14                      (14UL)
#define SYSCFG0_DMA0_REQ15                      (15UL)
#define SYSCFG0_DMA1_REQ0                       (16UL)
#define SYSCFG0_DMA1_REQ1                       (17UL)
#define SYSCFG0_DMA1_REQ2                       (18UL)
#define SYSCFG0_DMA1_REQ3                       (19UL)
#define SYSCFG0_DMA1_REQ4                       (20UL)
#define SYSCFG0_DMA1_REQ5                       (21UL)
#define SYSCFG0_DMA1_REQ6                       (22UL)
#define SYSCFG0_DMA1_REQ7                       (23UL)
#define SYSCFG0_DMA1_REQ8                       (24UL)
#define SYSCFG0_DMA1_REQ9                       (25UL)
#define SYSCFG0_DMA1_REQ10                      (26UL)
#define SYSCFG0_DMA1_REQ11                      (27UL)
#define SYSCFG0_DMA1_REQ12                      (28UL)
#define SYSCFG0_DMA1_REQ13                      (29UL)
#define SYSCFG0_DMA1_REQ14                      (30UL)
#define SYSCFG0_DMA1_REQ15                      (31UL)
#define IS_SYSCFG0_DMA_REQINDEX(REQINDEX) ((REQINDEX) < 32UL)

/** @defgroup  SYSCFG0_DMARequest config
  * @{
  */
#define SYSCFG0_DMA_REQUEST_FC0_TX               0
#define SYSCFG0_DMA_REQUEST_FC0_RX               1
#define SYSCFG0_DMA_REQUEST_FC1_TX               2
#define SYSCFG0_DMA_REQUEST_FC1_RX               3
#define SYSCFG0_DMA_REQUEST_FC2_TX               4
#define SYSCFG0_DMA_REQUEST_FC2_RX               5
#define SYSCFG0_DMA_REQUEST_FC3_TX               6
#define SYSCFG0_DMA_REQUEST_FC3_RX               7
#define SYSCFG0_DMA_REQUEST_FC4_TX               8
#define SYSCFG0_DMA_REQUEST_FC4_RX               9
#define SYSCFG0_DMA_REQUEST_FC5_TX              10
#define SYSCFG0_DMA_REQUEST_FC5_RX              11
#define SYSCFG0_DMA_REQUEST_FC6_TX              12
#define SYSCFG0_DMA_REQUEST_FC6_RX              13
#define SYSCFG0_DMA_REQUEST_FC7_TX              14
#define SYSCFG0_DMA_REQUEST_FC7_RX              15
#define SYSCFG0_DMA_REQUEST_FC8_TX              16
#define SYSCFG0_DMA_REQUEST_FC8_RX              17
#define SYSCFG0_DMA_REQUEST_FC9_TX              18
#define SYSCFG0_DMA_REQUEST_FC9_RX              19
#define SYSCFG0_DMA_REQUEST_FC10_TX             20
#define SYSCFG0_DMA_REQUEST_FC10_RX             21
#define SYSCFG0_DMA_REQUEST_FC11_TX             22
#define SYSCFG0_DMA_REQUEST_FC11_RX             23
#define SYSCFG0_DMA_REQUEST_FC12_TX             24
#define SYSCFG0_DMA_REQUEST_FC12_RX             25
#define SYSCFG0_DMA_REQUEST_FC13_TX             26
#define SYSCFG0_DMA_REQUEST_FC13_RX             27
#define SYSCFG0_DMA_REQUEST_SOFTWARE            28
#define SYSCFG0_DMA_REQUEST_BTMR33_0            29
#define SYSCFG0_DMA_REQUEST_BTMR33_1            30
#define SYSCFG0_DMA_REQUEST_BTMR33_2            31
#define SYSCFG0_DMA_REQUEST_BTMR33_3            32
#define SYSCFG0_DMA_REQUEST_I2S0_TX             33
#define SYSCFG0_DMA_REQUEST_I2S0_RX             34
#define SYSCFG0_DMA_REQUEST_ISO781633_0_TX      35
#define SYSCFG0_DMA_REQUEST_ISO781633_0_RX      36
#define SYSCFG0_DMA_REQUEST_ISO781633_1_TX      37
#define SYSCFG0_DMA_REQUEST_ISO781633_1_RX      38
#define SYSCFG0_DMA_REQUEST_WAVER33             39
#define SYSCFG0_DMA_REQUEST_OSPI0_TX             46
#define SYSCFG0_DMA_REQUEST_OSPI0_RX             47
#define SYSCFG0_DMA_REQUEST_OSPI1_TX             48
#define SYSCFG0_DMA_REQUEST_OSPI1_RX             49
#define SYSCFG0_DMA_REQUEST_TMR1_CH1            50
#define SYSCFG0_DMA_REQUEST_TMR1_CH2            51
#define SYSCFG0_DMA_REQUEST_TMR1_CH4_TRIG_COM   52
#define SYSCFG0_DMA_REQUEST_TMR1_UP             53
#define SYSCFG0_DMA_REQUEST_TMR1_CH3            54
#define SYSCFG0_DMA_REQUEST_TMR2_CH1            55
#define SYSCFG0_DMA_REQUEST_TMR2_CH2            56
#define SYSCFG0_DMA_REQUEST_TMR2_CH3_UP         57
#define SYSCFG0_DMA_REQUEST_TMR2_CH4_TRIG_COM   58
#define SYSCFG0_DMA_REQUEST_TMR3_CH3            59
#define SYSCFG0_DMA_REQUEST_TMR3_UP             60
#define SYSCFG0_DMA_REQUEST_TMR3_CH1            61
#define SYSCFG0_DMA_REQUEST_TMR3_CH2_CH4        62
#define SYSCFG0_DMA_REQUEST_TMR3_TRIG           63
#define SYSCFG0_DMA_REQUEST_TMR4_CH3            64
#define SYSCFG0_DMA_REQUEST_TMR4_CH4_UP         65
#define SYSCFG0_DMA_REQUEST_TMR4_CH1_TRIG       66
#define SYSCFG0_DMA_REQUEST_TMR4_CH2            67
#define SYSCFG0_DMA_REQUEST_TMR5_CH1            68
#define SYSCFG0_DMA_REQUEST_TMR5_CH2            69
#define SYSCFG0_DMA_REQUEST_TMR5_CH3            70
#define SYSCFG0_DMA_REQUEST_TMR5_UP             71
#define SYSCFG0_DMA_REQUEST_TMR5_TRIG           72
#define SYSCFG0_DMA_REQUEST_TMR5_CH4            73
#define SYSCFG0_DMA_REQUEST_TMR6_CH4_TRIG       74
#define SYSCFG0_DMA_REQUEST_TMR6_CH3_UP         75
#define SYSCFG0_DMA_REQUEST_TMR6_CH2            76
#define SYSCFG0_DMA_REQUEST_TMR6_CH1            77
#define SYSCFG0_DMA_REQUEST_I2S1_TX             78
#define SYSCFG0_DMA_REQUEST_I2S1_RX             79
#define SYSCFG0_DMA_REQUEST_CRC                 80
#define SYSCFG0_DMA_REQUEST_DCMI                81
#define SYSCFG0_DMA_REQUEST_DAC_1               82
#define SYSCFG0_DMA_REQUEST_DAC_2               83
#define SYSCFG0_DMA_REQUEST_ADC_0               84
#define SYSCFG0_DMA_REQUEST_ADC_1               85
#define SYSCFG0_DMA_REQUEST_EADC                86
#define SYSCFG0_DMA_REQUEST_CDMA_ADC            87
#define IS_SYSCFG0_DMA_REQUEST(REQUEST) (((REQUEST) == SYSCFG0_DMA_REQUEST_FC0_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC0_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC1_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC1_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC2_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC2_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC3_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC3_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC4_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC4_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC5_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC5_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC6_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC6_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC7_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC7_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC8_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC8_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC9_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC9_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC10_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC10_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC11_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC11_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC12_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC12_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC13_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_FC13_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_SOFTWARE) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_BTMR33_0) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_BTMR33_1) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_BTMR33_2) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_BTMR33_3) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_I2S0_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_I2S0_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_ISO781633_0_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_ISO781633_0_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_ISO781633_1_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_ISO781633_1_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_WAVER33) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_OSPI0_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_OSPI0_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_OSPI1_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_OSPI1_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR1_CH1) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR1_CH2) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR1_CH4_TRIG_COM) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR1_UP) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR1_CH3) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR2_CH1) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR2_CH2) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR2_CH3_UP) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR2_CH4_TRIG_COM) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR3_CH3) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR3_UP) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR3_CH1) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR3_CH2_CH4) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR3_TRIG) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR4_CH3) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR4_CH4_UP) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR4_CH1_TRIG) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR4_CH2) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR5_CH1) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR5_CH2) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR5_CH3) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR5_UP) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR5_TRIG) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR5_CH4) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR6_CH4_TRIG) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR6_CH3_UP) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR6_CH2) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_TMR6_CH1) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_I2S1_TX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_I2S1_RX) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_CRC) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_DCMI) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_DAC_1) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_DAC_2) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_ADC_0) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_ADC_1) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_EADC) ||\
                                          ((REQUEST) == SYSCFG0_DMA_REQUEST_CDMA_ADC))

//CAN_CTRL
#define SYSCFG0_CAN0_WAKE      ((uint32_t)0x00000001)
#define SYSCFG0_CAN1_WAKE      ((uint32_t)0x00000002)
#define IS_CAN_CTRL_CONF(CMD)   (((CMD) == SYSCFG0_CAN0_WAKE) || \
                                 ((CMD) == SYSCFG0_CAN1_WAKE))


#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */

/** @defgroup  SYSCFG1_EGYx config
  * @{
  */
#define SYSCFG1_EGY0                                        (1UL << 0)
#define SYSCFG1_EGY1                                        (1UL << 1)
#define SYSCFG1_EGY2                                        (1UL << 2)
#define IS_SYSCFG1_EGY(EGY) ((((EGY) & (~0x00000007)) == 0x00) && ((EGY) != 0x00))

/** @defgroup  SYSCFG1_IntMask config
  * @{
  */
#define SYSCFG1_INTMASK_EXTI0                               (1UL << 0)
#define SYSCFG1_INTMASK_EXTI1                               (1UL << 1)
#define SYSCFG1_INTMASK_EXTI2                               (1UL << 2)
#define SYSCFG1_INTMASK_EXTI3                               (1UL << 3)
#define SYSCFG1_INTMASK_EXTI4                               (1UL << 4)
#define SYSCFG1_INTMASK_EXTI5                               (1UL << 5)
#define SYSCFG1_INTMASK_EXTI6                               (1UL << 6)
#define SYSCFG1_INTMASK_EXTI7                               (1UL << 7)
#define SYSCFG1_INTMASK_EXTI8                               (1UL << 8)
#define SYSCFG1_INTMASK_EXTI9                               (1UL << 9)
#define SYSCFG1_INTMASK_EXTI10                              (1UL << 10)
#define SYSCFG1_INTMASK_EXTI11                              (1UL << 11)
#define SYSCFG1_INTMASK_EXTI12                              (1UL << 12)
#define SYSCFG1_INTMASK_EXTI13                              (1UL << 13)
#define SYSCFG1_INTMASK_EXTI14                              (1UL << 14)
#define SYSCFG1_INTMASK_EXTI15                              (1UL << 15)
#define SYSCFG1_INTMASK_RTC                                 (1UL << 16)
#define SYSCFG1_INTMASK_RTC_ALARM                           (1UL << 17)
#define SYSCFG1_INTMASK_BTMR0                               (1UL << 18)
#define SYSCFG1_INTMASK_BTMR1                               (1UL << 19)
#define SYSCFG1_INTMASK_LPBTMR0                             (1UL << 20)
#define SYSCFG1_INTMASK_LPBTMR1                             (1UL << 21)
#define SYSCFG1_INTMASK_MPMU_CMP                            (1UL << 22)
#define SYSCFG1_INTMASK_SYSCON_LP                           (1UL << 23)
#define IS_SYSCFG1_INTMASK(INTMASK) ((((INTMASK) & (~0x00FFFFFF)) == 0x00) && ((INTMASK) != 0x00))

/** @defgroup  SYSCFG1_UART_ClkSel config
  * @{
  */
#define SYSCFG1_UART_CLKSRC_RCH                             (0UL)
#define SYSCFG1_UART_CLKSRC_PLL0                            (1UL)
#define SYSCFG1_UART_CLKSRC_PLL1                            (2UL)
#define SYSCFG1_UART_CLKSRC_XOH                             (3UL)
#define SYSCFG1_UART_CLKSRC_RCHD4                           (4UL)
#define SYSCFG1_UART_CLKSRC_RCHD48                          (5UL)
#define SYSCFG1_UART_CLKSRC_RCL                             (6UL)
#define SYSCFG1_UART_CLKSRC_XOL                             (7UL)
#define SYSCFG1_UART_CLKSRC_MASK                            (7UL)
#define IS_SYSCFG1_UART_CLKSRC(CLKSRC) ((CLKSRC) < 8UL)

/** @defgroup  SYSCFG1_Periph clock
  * @{
  */
#define SYSCFG1_Periph0Clock_CM0                            (1UL << 0)
#define SYSCFG1_Periph0Clock_CRYPTO                         (1UL << 7)
#define SYSCFG1_Periph0Clock_WAVER                          (1UL << 8)
#define SYSCFG1_Periph0Clock_HFM_COP                        (1UL << 9)
#define IS_SYSCFG1_PERIPH0CLK(PERIPH) ((((PERIPH) & (~0x00000381)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFG1_Periph clock
  * @{
  */
#define SYSCFG1_Periph1Clock_I2C14                           (1UL << 2)
#define SYSCFG1_Periph1Clock_BSPI0                           (1UL << 3)
#define SYSCFG1_Periph1Clock_BSPI1                           (1UL << 4)
#define SYSCFG1_Periph1Clock_BSPI2                           (1UL << 5)
#define SYSCFG1_Periph1Clock_BSPI3                           (1UL << 6)
#define SYSCFG1_Periph1Clock_BSPI4                           (1UL << 7)
#define SYSCFG1_Periph1Clock_BSPI5                           (1UL << 8)
#define SYSCFG1_Periph1Clock_UART14                          (1UL << 9)
#define SYSCFG1_Periph1Clock_UART15                          (1UL << 10)
#define SYSCFG1_Periph1Clock_UART16                          (1UL << 11)
#define SYSCFG1_Periph1Clock_UART17                          (1UL << 12)
#define SYSCFG1_Periph1Clock_UART18                          (1UL << 13)
#define SYSCFG1_Periph1Clock_UART19                          (1UL << 14)
#define SYSCFG1_Periph1Clock_ISO78162                       (1UL << 15)
#define SYSCFG1_Periph1Clock_ISO78163                       (1UL << 16)
#define SYSCFG1_Periph1Clock_BTMR_BPWM_GLOBAL               (1UL << 17)
#define SYSCFG1_Periph1Clock_CRYPTO                         (1UL << 18)
#define SYSCFG1_Periph1Clock_BTMR4                          (1UL << 19)
#define SYSCFG1_Periph1Clock_BTMR5                          (1UL << 20)
#define SYSCFG1_Periph1Clock_BTMR6                          (1UL << 21)
#define SYSCFG1_Periph1Clock_BTMR7                          (1UL << 22)
#define SYSCFG1_Periph1Clock_BPWM4                          (1UL << 23)
#define SYSCFG1_Periph1Clock_BPWM5                          (1UL << 24)
#define SYSCFG1_Periph1Clock_BPWM6                          (1UL << 25)
#define SYSCFG1_Periph1Clock_BPWM7                          (1UL << 26)
#define SYSCFG1_Periph1Clock_WDT2                           (1UL << 27)
#define IS_SYSCFG1_PERIPH1CLK(PERIPH) ((((PERIPH) & (~0x0FFFFFFC)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFG1_Periph reset
  * @{
  */
#define SYSCFG1_PeriphReset_BSPI0                            (1UL << 2)
#define SYSCFG1_PeriphReset_BSPI1                            (1UL << 3)
#define SYSCFG1_PeriphReset_BSPI2                            (1UL << 4)
#define SYSCFG1_PeriphReset_BSPI3                            (1UL << 5)
#define SYSCFG1_PeriphReset_BSPI4                            (1UL << 6)
#define SYSCFG1_PeriphReset_BSPI5                            (1UL << 7)
#define SYSCFG1_PeriphReset_UART14                           (1UL << 8)
#define SYSCFG1_PeriphReset_UART15                           (1UL << 9)
#define SYSCFG1_PeriphReset_UART16                           (1UL << 10)
#define SYSCFG1_PeriphReset_UART17                           (1UL << 11)
#define SYSCFG1_PeriphReset_UART18                           (1UL << 12)
#define SYSCFG1_PeriphReset_UART19                           (1UL << 13)
#define SYSCFG1_PeriphReset_I2C14                            (1UL << 14)
#define SYSCFG1_PeriphReset_ISO78162                        (1UL << 15)
#define SYSCFG1_PeriphReset_ISO78163                        (1UL << 16)
#define SYSCFG1_PeriphReset_BTMR_BPWM_GLOBAL                (1UL << 17)
#define SYSCFG1_PeriphReset_WAVER                           (1UL << 19)
#define SYSCFG1_PeriphReset_HFM_COP                         (1UL << 20)
#define SYSCFG1_PeriphReset_CRYPTO                          (1UL << 21)
#define SYSCFG1_PeriphReset_WDT2                            (1UL << 28)
#define IS_SYSCFG1_PERIPHRST(PERIPH) ((((PERIPH) & (~0x203BFFFC)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFG1_I2C_ClkSel config
  * @{
  */
#define SYSCFG1_I2C_CLKSRC_RCH                              (0UL)
#define SYSCFG1_I2C_CLKSRC_PLL0                             (1UL)
#define SYSCFG1_I2C_CLKSRC_PLL1                             (2UL)
#define SYSCFG1_I2C_CLKSRC_XOH                              (3UL)
#define SYSCFG1_I2C_CLKSRC_RCHD4                            (4UL)
#define SYSCFG1_I2C_CLKSRC_RCHD48                           (5UL)
#define SYSCFG1_I2C_CLKSRC_RCL                              (6UL)
#define SYSCFG1_I2C_CLKSRC_XOL                              (7UL)
#define SYSCFG1_I2C_CLKSRC_MASK                             (7UL)
#define IS_SYSCFG1_I2C_CLKSRC(CLKSRC) ((CLKSRC) < 8UL)

/** @defgroup  SYSCFG1_BasicTMR config
  * @{
  */
#define SYSCFG1_BTMR4                                     (0UL)
#define SYSCFG1_BTMR5                                     (1UL)
#define SYSCFG1_BTMR6                                     (2UL)
#define SYSCFG1_BTMR7                                     (3UL)
#define SYSCFG1_BPWM4                                     (4UL)
#define SYSCFG1_BPWM5                                     (5UL)
#define SYSCFG1_BPWM6                                     (6UL)
#define SYSCFG1_BPWM7                                     (7UL)
#define IS_SYSCFG1_BTMR(BTMR) ((BTMR) < 8UL)

/** @defgroup  SYSCFG1_BasicTMR_ClkSel config
  * @{
  */
#define IS_SYSCFG1_BTMR_CLKSRC_RCH                           (0UL)
#define IS_SYSCFG1_BTMR_CLKSRC_PLL0                          (1UL)
#define IS_SYSCFG1_BTMR_CLKSRC_PLL1                          (2UL)
#define IS_SYSCFG1_BTMR_CLKSRC_XOH                           (3UL)
#define IS_SYSCFG1_BTMR_CLKSRC_RCHD4                         (4UL)
#define IS_SYSCFG1_BTMR_CLKSRC_RCHD48                        (5UL)
#define IS_SYSCFG1_BTMR_CLKSRC_RCL                           (6UL)
#define IS_SYSCFG1_BTMR_CLKSRC_XOL                           (7UL)
#define IS_SYSCFG1_BTMR_CLKSRC_MASK                          (7UL)
#define IS_SYSCFG1_BTMR_CLKSRC(CLKSRC) ((CLKSRC) < 8UL)

/** @defgroup  SYSCFGLP_Periph reset
  * @{
  */
#define SYSCFGLP_PeriphReset_PMU                         (1UL << 0)
#define SYSCFGLP_PeriphReset_RETRAM                      (1UL << 1)
#define SYSCFGLP_PeriphReset_UART32K0                    (1UL << 2)
#define SYSCFGLP_PeriphReset_UART32K1                    (1UL << 3)
#define SYSCFGLP_PeriphReset_RTC_ALARM                   (1UL << 4)
#define SYSCFGLP_PeriphReset_COMP                        (1UL << 7)
#define SYSCFGLP_PeriphReset_LPBTMR0                     (1UL << 8)
#define SYSCFGLP_PeriphReset_LPBTMR1                     (1UL << 9)
#define IS_SYSCFGLP_PERIPHRST(PERIPH) ((((PERIPH) & (~0x0000039F)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFGLP_WDTRST cinfig
  * @{
  */
#define SYSCFGLP_WDTRST_SINGLE_CORE                      (0UL)
#define SYSCFGLP_WDTRST_TRI_CORE                         (2UL)
#define SYSCFGLP_WDTRST_WHOLE_CHIP                       (1UL)
#define IS_SYSCFGLP_WDTRST(WDTRST) ((WDTRST) < 3UL)

/** @defgroup  SYSCFGLP_Periph clock
  * @{
  */
#define SYSCFGLP_PeriphClock_RTC                         (1UL << 1)
#define SYSCFGLP_PeriphClock_RETRAM                      (1UL << 3)
#define SYSCFGLP_PeriphClock_UART32K0                    (1UL << 4)
#define SYSCFGLP_PeriphClock_UART32K1                    (1UL << 5)
#define SYSCFGLP_PeriphClock_PMU                         (1UL << 6)
#define SYSCFGLP_PeriphClock_RTC_ALARM                   (1UL << 7)
#define SYSCFGLP_PeriphClock_COMP                    (1UL << 9)
#define SYSCFGLP_PeriphClock_LPBTMR0                     (1UL << 10)
#define SYSCFGLP_PeriphClock_LPBTMR1                     (1UL << 11)
#define IS_SYSCFGLP_PERIPHCLK(PERIPH) ((((PERIPH) & (~0x00000EFA)) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup  SYSCFGLP APBLP clock
  * @{
  */
#define SYSCFGLP_APBLP_CLKSRC_POS             (3UL)
#define SYSCFGLP_APBLP_CLKSRC_RCH             (0UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define SYSCFGLP_APBLP_CLKSRC_PLL0            (1UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define SYSCFGLP_APBLP_CLKSRC_PLL1            (2UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define SYSCFGLP_APBLP_CLKSRC_XOH             (3UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define SYSCFGLP_APBLP_CLKSRC_RCHD4           (4UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define SYSCFGLP_APBLP_CLKSRC_RCHD48          (5UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define SYSCFGLP_APBLP_CLKSRC_RCL             (6UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define SYSCFGLP_APBLP_CLKSRC_XOL             (7UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define SYSCFGLP_APBLP_CLKSRC_MASK            (7UL << SYSCFGLP_APBLP_CLKSRC_POS)
#define IS_SYSCFGLP_APBLP_CLKSRC(CLKSRC)      ((CLKSRC&~SYSCFGLP_APBLP_CLKSRC_MASK) == 0)

#define SYSCFGLP_APBLP_CLKDIV_POS             (8UL)
#define SYSCFGLP_APBLP_CLKDIV_MASK            (0xFF << SYSCFGLP_APBLP_CLKDIV_POS)

/** @defgroup  SYSCFGLP PMU clock
  * @{
  */
#define SYSCFGLP_PMU_CLKSRC_POS             (0UL)
#define SYSCFGLP_PMU_CLKSRC_RCH             (0UL << SYSCFGLP_PMU_CLKSRC_POS)
#define SYSCFGLP_PMU_CLKSRC_PLL0            (1UL << SYSCFGLP_PMU_CLKSRC_POS)
#define SYSCFGLP_PMU_CLKSRC_PLL1            (2UL << SYSCFGLP_PMU_CLKSRC_POS)
#define SYSCFGLP_PMU_CLKSRC_XOH             (3UL << SYSCFGLP_PMU_CLKSRC_POS)
#define SYSCFGLP_PMU_CLKSRC_RCHD4           (4UL << SYSCFGLP_PMU_CLKSRC_POS)
#define SYSCFGLP_PMU_CLKSRC_RCHD48          (5UL << SYSCFGLP_PMU_CLKSRC_POS)
#define SYSCFGLP_PMU_CLKSRC_RCL             (6UL << SYSCFGLP_PMU_CLKSRC_POS)
#define SYSCFGLP_PMU_CLKSRC_XOL             (7UL << SYSCFGLP_PMU_CLKSRC_POS)
#define SYSCFGLP_PMU_CLKSRC_MASK            (7UL << SYSCFGLP_PMU_CLKSRC_POS)
#define IS_SYSCFGLP_PMU_CLKSRC(CLKSRC)      ((CLKSRC&~SYSCFGLP_PMU_CLKSRC_MASK) == 0)

#define SYSCFGLP_PMU_CLKDIV_POS               (0UL)
#define SYSCFGLP_PMU_CLKDIV_MASK              (0xFF << SYSCFGLP_PMU_CLKDIV_POS)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

/* Internal Flash Bank configuration functions ********************************/
void SYSCFG0_FlashAMicroSecTickConfig(uint32_t SYSCFG0_SysClock);
void SYSCFG0_FlashBMicroSecTickConfig(uint32_t SYSCFG0_SysClock);
void SYSCFG0_FlashSwitch(void);
void SYSCFG0_FlashAECCCmd(FunctionalState NewState);
void SYSCFG0_FlashBECCCmd(FunctionalState NewState);
void SYSCFG0_FlashACacheECCCmd(FunctionalState NewState);
void SYSCFG0_FlashBCacheECCCmd(FunctionalState NewState);
/* CM33 core1 configuration functions *****************************************/
void SYSCFG0_Core1BootAddrConfig(uint32_t SYSCFG0_Core1Addr);
void SYSCFG0_Core1ResetCmd(FunctionalState NewState);
void SYSCFG0_Core1WaitCmd(FunctionalState NewState);
/* CM0 configuration functions ************************************************/
void SYSCFG0_CM0SecurePrivConfig(uint32_t SYSCFG0_CM0Config);
/* CM33 peripheral functions **************************************************/
void SYSCFG0_Periph0Reset(uint32_t SYSCFG0_Periph);
void SYSCFG0_Periph1Reset(uint32_t SYSCFG0_Periph);
void SYSCFG0_Periph0ClockCmd(uint32_t SYSCFG0_Periph, FunctionalState NewState);
void SYSCFG0_Periph1ClockCmd(uint32_t SYSCFG0_Periph, FunctionalState NewState);
void SYSCFG0_TMRClockCmd(uint32_t SYSCFG0_TMRClock, FunctionalState NewState);
/* CM33 sleep/deep-sleep functions ********************************************/
void SYSCFG0_EnterSleepMode(void);
void SYSCFG0_EnterDeepSleepMode(void);
/* CM33 Misc. functions *******************************************************/
void SYSCFG0_Core0LockupResetCmd(FunctionalState NewState);
void SYSCFG0_Core1LockupResetCmd(FunctionalState NewState);

void SYSCFG0_OSPIXIPCmd(OSPI_Type* OSPIx, FunctionalState NewState);
void SYSCFG0_OSPIClockConfig(OSPI_Type* OSPIx, \
                             uint32_t SYSCFG0_OSPI_ClkSel, \
                             uint32_t SYSCFG0_OSPI_ClkDiv);
void SYSCFG0_OSPI_RDS_Delay(OSPI_Type* OSPIx, uint8_t Delay_Cycle);

void SYSCFG0_I2SClockConfig(I2S_Type* I2Sx, \
                             uint32_t SYSCFG0_I2S_ClkSel, \
                             uint32_t SYSCFG0_I2S_ClkDiv);
void SYSCFG0_I2SMasterClockConfig(I2S_Type* I2Sx, \
                                   uint32_t SYSCFG0_I2S_MClkDiv, \
                                   FunctionalState NewState);
void SYSCFG0_I2SPinsCmd(I2S_Type* I2Sx, FunctionalState NewState);

void SYSCFG0_FlexcommModeConfig(FLEXCOMM_Type FLEXCOMMx, uint32_t YSCON33_FCMode);
void SYSCFG0_FlexcommClockConfig(FLEXCOMM_Type FLEXCOMMx, \
                                  uint32_t SYSCFG0_FC_ClkSel, \
                                  uint32_t SYSCFG0_FC_ClkDiv);
void SYSCFG0_FlexcommUARTRxCmd(FLEXCOMM_Type FLEXCOMMx, FunctionalState NewState);

void SYSCFG0_SDIOClockConfig(SDIO_TypeDef *SDIOx, \
                              uint32_t SYSCFG0_SDIO_ClkSel, \
                              uint32_t SYSCFG0_SDIO_ClkDiv);

void SYSCFG0_ADCClockConfig(uint32_t SYSCFG0_ADC_ClkSel, uint32_t SYSCFG0_ADC_ClkDiv);
void SYSCFG0_ADCRegularExtTrigConfig(uint32_t SYSCFG0_ADC_RegularExtTrig);
void SYSCFG0_ADCInjectedExtTrigConfig(uint32_t SYSCFG0_ADC_InjectedExtTrig);

void SYSCFG0_CDMA_ADCClockConfig(uint32_t SYSCFG0_CDMA_ADC_ClkSel, \
                                  uint32_t SYSCFG0_CDMA_ADC_ClkDiv);

void SYSCFG0_DACClockConfig(uint32_t SYSCFG0_DAC_ClkSel, \
                             uint32_t SYSCFG0_DAC_ClkDiv);

void SYSCFG0_EADCClockConfig(uint32_t SYSCFG0_EADC_ClkSel, \
                              uint32_t SYSCFG0_EADC_ClkDiv);

void SYSCFG0_USBHSClockConfig(uint32_t SYSCFG0_USBHS_ClkSel, \
                               uint32_t SYSCFG0_USBHS_ClkDiv);

void SYSCFG0_USBFSClockConfig(uint32_t SYSCFG0_USBFS_ClkSel, \
                               uint32_t SYSCFG0_USBFS_ClkDiv);

void SYSCFG0_BasicTMRClockConfig(uint32_t SYSCFG0_BasicTMR, \
                                  uint32_t SYSCFG0_BasicTMR_ClkSel, \
                                  uint32_t SYSCFG0_BasicTMR_ClkDiv);

void SYSCFG0_DebugCmd(FunctionalState NewState);
uint32_t SYSCFG0_GetResetSource(void);
void SYSCFG0_DMARequestConfig(uint32_t SYSCFG0_DMAx_REQy, uint32_t SYSCFG0_DMARequest);
void SYSCFG0_CANCtrlCmd(uint32_t Periph, FunctionalState NewState);
void SYSCFG0_ADCVref_config(uint32_t SYSCFG0_ADC_VerfSource, uint32_t VerfValue);
void SYSCFG0_DACVref_config(uint32_t SYSCFG0_DAC_VerfSource, uint32_t VerfValue);
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */

/* Internal Flash Bank configuration functions ********************************/
void SYSCFG1_Flash0MicroSecTickConfig(uint32_t SYSCFG1_SysClock);
void SYSCFG1_Flash0ECCCmd(FunctionalState NewState);
void SYSCFG1_Flash0CacheECCCmd(FunctionalState NewState);
/* UART functions *************************************************************/
void SYSCFG1_UARTIRCmd(UART_Type *UARTx, FunctionalState NewState);
void SYSCFG1_UARTIRDutyConfig(uint16_t DutyHigh, uint16_t DutyLow);
void SYSCFG1_UARTPinsCmd(UART_Type *UARTx, FunctionalState NewState);
void SYSCFG1_UARTClockConfig(UART_Type *UARTx, \
                             uint32_t SYSCFG1_UART_ClkSel, \
                             uint32_t SYSCFG1_UART_ClkDiv);
/* CM0 peripheral functions ***************************************************/
void SYSCFG1_Periph0ClockCmd(uint32_t SYSCFG1_Periph, FunctionalState NewState);
void SYSCFG1_Periph1ClockCmd(uint32_t SYSCFG1_Periph, FunctionalState NewState);
void SYSCFG1_PeriphReset(uint32_t SYSCFG1_Periph);
/* CM0 Misc. functions ********************************************************/
void SYSCFG1_EGYCmd(uint32_t SYSCFG1_EGYx, FunctionalState NewState);
void SYSCFG1_IntMaskConfig(uint32_t SYSCFG1_IntMask, FunctionalState NewState);
void SYSCFG1_SetVectorTable(uint32_t VTOR_Address);
void SYSCFG1_IRQLatencyConfig(uint8_t Latency);
void SYSCFG1_LockupResetCmd(FunctionalState NewState);

void SYSCFG1_I2CClockConfig(uint32_t SYSCFG1_I2C_ClkSel, uint32_t SYSCFG1_I2C_ClkDiv);

void SYSCFG1_BasicTMRClockConfig(uint32_t SYSCFG1_BasicTMR, \
                                 uint32_t SYSCFG1_BasicTMR_ClkSel, \
                                 uint32_t SYSCFG1_BasicTMR_ClkDiv);

void SYSCFGLP_PeriphClockCmd(uint32_t SYSCFGLP_Periph, FunctionalState NewState);
void SYSCFGLP_PeriphReset(uint32_t SYSCFGLP_Periph);
void SYSCFGLP_WDTResetConfig(uint32_t SYSCFGLP_WDTReset);
void SYSCFGLP_CM0ResetCmd(FunctionalState NewState);
void SYSCFGLP_APBLPClockConfig(uint32_t SYSCFGLP_APBLP_ClkSel, \
                               uint32_t SYSCFGLP_APBLP_ClkDiv);
void SYSCFGLP_PMUClockConfig(uint32_t SYSCFGLP_PMU_ClkSel, \
                               uint32_t SYSCFGLP_PMU_ClkDiv);
void SYSCFG0_ADCVref_config(uint32_t SYSCFG0_ADC_VerfSource, uint32_t VerfValue);
void SYSCFG0_DACVref_config(uint32_t SYSCFG0_DAC_VerfSource, uint32_t VerfValue);
#ifdef __cplusplus
}
#endif

#endif /* __LIB_SYSCON_H */

/*********************************** END OF FILE ******************************/
