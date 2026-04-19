/**
  ******************************************************************************
  * @file    lib_clk.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Clock library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_CLK_H
#define __LIB_CLK_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/*
* SYSCFGLP_RCH_CTRL0
*/
#define SYSCFGLP_RCH_CTRL0_RCHEN                      (1UL << 0)

/*
* SYSCFGLP_XOH_CTRL0
*/
// (configurations)
#define SYSCFGLP_XOH_CTRL0_XTALMF_CFG_MASK            (0x7FUL << 4)
// (control flow)
#define SYSCFGLP_XOH_CTRL0_BYPASS                     (1UL << 2)
#define SYSCFGLP_XOH_CTRL0_STABLE_GATE_FORCE_EN       (1UL << 1)
#define SYSCFGLP_XOH_CTRL0_XOHEN                      (1UL << 0)

/*
* RTC_ANA_CTRL_XTAL
*/
#define RTC_ANA_CTRL_XTAL_32KEXIST            (1UL << 17)
#define RTC_ANA_CTRL_XTAL_32KABSENT           (1UL << 16)
#define RTC_ANA_CTRL_XTAL_32KABSENT_CLR       (1UL << 15)
#define RTC_ANA_CTRL_XTAL_EN_SEL              (1UL << 10)
#define RTC_ANA_CTRL_XTAL_BYP_LV              (1UL << 9)
#define RTC_ANA_CTRL_XTAL_EN_LV               (1UL << 8)

/*
* SYSCFGLP_PLL0_CTRL0
*/
#define SYSCFGLP_PLL0_CTRL0_SW_WAIT_TIME_POS          (5UL)
#define SYSCFGLP_PLL0_CTRL0_SW_WAIT_TIME_MASK         (0xFFUL << SYSCFGLP_PLL0_CTRL0_SW_WAIT_TIME_POS)
#define SYSCFGLP_PLL0_CTRL0_SATBLE_GATE_SEL           (1UL << 3)
#define SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_POS            (1UL)
#define SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_MASK           (3UL << SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_POS)
#define PLL0_REFCLK_RCH_DIV4                           (0UL << SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_POS)
#define PLL0_REFCLK_XOH                                (1UL << SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_POS)
#define PLL0_REFCLK_RCH                                (2UL << SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_POS)
#define PLL0_REFCLK_RCH_DIV48                          (3UL << SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_POS)
#define SYSCFGLP_PLL0_CTRL0_CFG_MASK                  (SYSCFGLP_PLL0_CTRL0_SW_WAIT_TIME_MASK |\
                                                        SYSCFGLP_PLL0_CTRL0_SATBLE_GATE_SEL   |\
                                                        SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_MASK)
#define SYSCFGLP_PLL0_CTRL0_PLL0_LOCK                 (1UL << 31)
#define SYSCFGLP_PLL0_CTRL0_PLL0_STABLE               (1UL << 30)
#define SYSCFGLP_PLL0_CTRL0_STABLE_GATE_FORCE_EN      (1UL << 4)
#define SYSCFGLP_PLL0_CTRL0_PLL0EN                    (1UL << 0)
/*
* SYSCFGLP_PLL0_CTRL1
*/
#define SYSCFGLP_PLL0_CTRL1_DIV_INT_H_POS             (14UL)
#define SYSCFGLP_PLL0_CTRL1_DIV_INT_H_MASK            (3UL << SYSCFGLP_PLL0_CTRL1_DIV_INT_H_POS)
#define SYSCFGLP_PLL0_CTRL1_DIV_INT_L_POS             (5UL)
#define SYSCFGLP_PLL0_CTRL1_DIV_INT_L_MASK            (0x1FFUL << SYSCFGLP_PLL0_CTRL1_DIV_INT_L_POS)
#define SYSCFGLP_PLL0_CTRL1_DIV_PRE_POS               (0UL)
#define SYSCFGLP_PLL0_CTRL1_DIV_PRE_MASK              (0x1FUL << SYSCFGLP_PLL0_CTRL1_DIV_PRE_POS)
#define SYSCFGLP_PLL0_CTRL1_CFG_MASK                  (0xFFFFUL)

/*
* SYSCFGLP_PLL1_CTRL0
*/
#define SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS            (1UL)
#define SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_MASK           (7UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define PLL1_REFCLK_32KXTAL                            (0UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define PLL1_REFCLK_RCL                                (1UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define PLL1_REFCLK_RCH_DIV4                           (2UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define PLL1_REFCLK_XOH                                (3UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define PLL1_REFCLK_RCH                                (4UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define PLL1_REFCLK_PLL0                               (5UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define PLL1_REFCLK_PLL0_DIV                           (6UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define PLL1_REFCLK_RCH_DIV48                          (7UL << SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_POS)
#define SYSCFGLP_PLL1_CTRL0_REFCLK_DIV_POS            (4UL)
#define SYSCFGLP_PLL1_CTRL0_REFCLK_DIV_MASK           (0xFFUL << SYSCFGLP_PLL1_CTRL0_REFCLK_DIV_POS)
#define SYSCFGLP_PLL1_CTRL0_SATBLE_GATE_SEL           (1UL << 21)
#define SYSCFGLP_PLL1_CTRL0_SW_WAIT_TIME_POS          (23UL)
#define SYSCFGLP_PLL1_CTRL0_SW_WAIT_TIME_MASK         (0xFFUL << SYSCFGLP_PLL1_CTRL0_SW_WAIT_TIME_POS)
#define SYSCFGLP_PLL1_CTRL0_CFG_MASK                  (SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_MASK    |\
                                                        SYSCFGLP_PLL1_CTRL0_REFCLK_DIV_MASK    |\
                                                        SYSCFGLP_PLL1_CTRL0_SATBLE_GATE_SEL    |\
                                                        SYSCFGLP_PLL1_CTRL0_SW_WAIT_TIME_MASK)
#define SYSCFGLP_PLL1_CTRL0_PLL1_LOCK                 (1UL << 31)
#define SYSCFGLP_PLL1_CTRL0_PLL1_STABLE               (1UL << 12)
#define SYSCFGLP_PLL1_CTRL0_STABLE_GATE_FORCE_EN      (1UL << 22)
#define SYSCFGLP_PLL1_CTRL0_PLL1_PWRDN                (1UL << 0)
/*
* SYSCFGLP_PLL1_CTRL1
*/
#define SYSCFGLP_PLL1_CTRL1_RESET                     (1UL << 0)
/*
* SYSCFGLP_PLL1_CTRL2
*/
#define SYSCFGLP_PLL1_CTRL2_CLKR_POS                  (0U)
#define SYSCFGLP_PLL1_CTRL2_CLKF_POS                  (6U)
#define SYSCFGLP_PLL1_CTRL2_CLKOD_POS                 (19U)
#define SYSCFGLP_PLL1_CTRL2_CFG_MASK                  (0x7FFFFFUL)
#define SYSCFGLP_PLL1_CTRL2_BYPASS                    (1UL << 23)
/*
* SYSCFGLP_PLL1_CTRL3
*/
#define SYSCFGLP_PLL1_CTRL3_CFG_MASK                  (0xFFFUL)
/*
* SYSCFGLP_XTAL_EXIST_CTRL
*/
#define SYSCFGLP_XTAL_EXIST_CTRL_XOH                  (1UL << 18)
/*
* SYSCFGLP_CLKOUT
*/
#define SYSCFGLP_CLKOUT_OUTEN                         (1UL << 0)
#define SYSCFGLP_CLKOUT_SEL_POS                       (8UL)
#define SYSCFGLP_CLKOUT_DIV_POS                       (16UL)

#define SYSCFG0_HCLK_SEL_RCH         ((uint32_t)0x00)
#define SYSCFG0_HCLK_SEL_PLL0        ((uint32_t)0x01)
#define SYSCFG0_HCLK_SEL_PLL1        ((uint32_t)0x02)
#define SYSCFG0_HCLK_SEL_XOH         ((uint32_t)0x03)
#define SYSCFG0_HCLK_SEL_RCH_DIV4    ((uint32_t)0x04)
#define SYSCFG0_HCLK_SEL_RCH_DIV48   ((uint32_t)0x05)
#define SYSCFG0_HCLK_SEL_32KRC       ((uint32_t)0x06)
#define SYSCFG0_HCLK_SEL_32KXTAL     ((uint32_t)0x07)
#define SYSCFG0_HCLK_SEL_MASK        ((uint32_t)0x07)

#define SYSCFG0_PCLK_SEL_POS         (4UL)
#define SYSCFG0_PCLK_SEL_RCH         ((uint32_t)0x00 << SYSCFG0_PCLK_SEL_POS)
#define SYSCFG0_PCLK_SEL_PLL0        ((uint32_t)0x01 << SYSCFG0_PCLK_SEL_POS)
#define SYSCFG0_PCLK_SEL_PLL1        ((uint32_t)0x02 << SYSCFG0_PCLK_SEL_POS)
#define SYSCFG0_PCLK_SEL_XOH         ((uint32_t)0x03 << SYSCFG0_PCLK_SEL_POS)
#define SYSCFG0_PCLK_SEL_RCH_DIV4    ((uint32_t)0x04 << SYSCFG0_PCLK_SEL_POS)
#define SYSCFG0_PCLK_SEL_RCH_DIV48   ((uint32_t)0x05 << SYSCFG0_PCLK_SEL_POS)
#define SYSCFG0_PCLK_SEL_32KRC       ((uint32_t)0x06 << SYSCFG0_PCLK_SEL_POS)
#define SYSCFG0_PCLK_SEL_32KXTAL     ((uint32_t)0x07 << SYSCFG0_PCLK_SEL_POS)
#define SYSCFG0_PCLK_SEL_MASK        ((uint32_t)0x07 << SYSCFG0_PCLK_SEL_POS)

#define SYSCFG1_HCLK_SEL_RCH         ((uint32_t)0x00)
#define SYSCFG1_HCLK_SEL_PLL0        ((uint32_t)0x01)
#define SYSCFG1_HCLK_SEL_PLL1        ((uint32_t)0x02)
#define SYSCFG1_HCLK_SEL_XOH         ((uint32_t)0x03)
#define SYSCFG1_HCLK_SEL_RCH_DIV4    ((uint32_t)0x04)
#define SYSCFG1_HCLK_SEL_RCH_DIV48   ((uint32_t)0x05)
#define SYSCFG1_HCLK_SEL_32KRC       ((uint32_t)0x06)
#define SYSCFG1_HCLK_SEL_32KXTAL     ((uint32_t)0x07)
#define SYSCFG1_HCLK_SEL_MASK        ((uint32_t)0x07)

#define SYSCFG1_PCLK_SEL_POS         (3UL)
#define SYSCFG1_PCLK_SEL_RCH         ((uint32_t)0x00 << SYSCFG1_PCLK_SEL_POS)
#define SYSCFG1_PCLK_SEL_PLL0        ((uint32_t)0x01 << SYSCFG1_PCLK_SEL_POS)
#define SYSCFG1_PCLK_SEL_PLL1        ((uint32_t)0x02 << SYSCFG1_PCLK_SEL_POS)
#define SYSCFG1_PCLK_SEL_XOH         ((uint32_t)0x03 << SYSCFG1_PCLK_SEL_POS)
#define SYSCFG1_PCLK_SEL_RCH_DIV4    ((uint32_t)0x04 << SYSCFG1_PCLK_SEL_POS)
#define SYSCFG1_PCLK_SEL_RCH_DIV48   ((uint32_t)0x05 << SYSCFG1_PCLK_SEL_POS)
#define SYSCFG1_PCLK_SEL_32KRC       ((uint32_t)0x06 << SYSCFG1_PCLK_SEL_POS)
#define SYSCFG1_PCLK_SEL_32KXTAL     ((uint32_t)0x07 << SYSCFG1_PCLK_SEL_POS)
#define SYSCFG1_PCLK_SEL_MASK        ((uint32_t)0x07 << SYSCFG1_PCLK_SEL_POS)

/*
* SYS33_I2SCS
*/
#define SYS33_I2SCS_CLKSEL_MASK      ((uint32_t)0x07)
#define SYS33_I2SCS_CLKSEL_RCH       ((uint32_t)0x00)
#define SYS33_I2SCS_CLKSEL_PLL0      ((uint32_t)0x01)
#define SYS33_I2SCS_CLKSEL_PLL1      ((uint32_t)0x02)
#define SYS33_I2SCS_CLKSEL_XOH       ((uint32_t)0x03)
#define SYS33_I2SCS_CLKSEL_RCHD4     ((uint32_t)0x04)
#define SYS33_I2SCS_CLKSEL_RCHD48    ((uint32_t)0x05)
#define SYS33_I2SCS_CLKSEL_RCL       ((uint32_t)0x06)
#define SYS33_I2SCS_CLKSEL_XOL       ((uint32_t)0x07)
#define SYS33_I2SCS_CLKSEL_Offset    (4UL)

/*
* SYS33_I2SCD
*/
#define SYS33_I2SCD_CLKDIV_MASK      ((uint32_t)0xFF)
#define SYS33_I2SCD_CLKDIV_Offset    (8UL)

/*
* SYS33_FCCS
*/
#define SYS33_FCCS_CLKSEL_MASK      ((uint32_t)0x07)
#define SYS33_FCCS_CLKSEL_RCH       ((uint32_t)0x00)
#define SYS33_FCCS_CLKSEL_PLL0      ((uint32_t)0x01)
#define SYS33_FCCS_CLKSEL_PLL1      ((uint32_t)0x02)
#define SYS33_FCCS_CLKSEL_XOH       ((uint32_t)0x03)
#define SYS33_FCCS_CLKSEL_RCHD4     ((uint32_t)0x04)
#define SYS33_FCCS_CLKSEL_RCHD48    ((uint32_t)0x05)
#define SYS33_FCCS_CLKSEL_RCL       ((uint32_t)0x06)
#define SYS33_FCCS_CLKSEL_XOL       ((uint32_t)0x07)

/*
* SYS33_I2SCD
*/
#define SYS33_FCCD_CLKDIV_MASK      ((uint32_t)0xFF)

/** @defgroup CLK_PLL0Config  Type
  * @{
  */
typedef struct
{
  uint32_t CLKN0;
  uint32_t CLKN1;
  uint32_t CLKM;
  uint32_t PLL0_OUT;
} CLK_PLL0Config;

/** @defgroup CLK_PLL1Config  Type
  * @{
  */
typedef struct
{
  uint32_t PLL1_CTRL2;
  uint32_t PLL1_CTRL3;
  uint32_t PLL1_OUT;
} CLK_PLL1Config;

/** @defgroup CLK_PLL0InitType  Type
  * @{
  */
typedef struct
{
  uint32_t PLL0_State;   /*!< The new state of the PLL0.
                            This parameter can be a value of @ref CLK_PLL0_Config                      */
  uint32_t PLL0_Source;  /*!< CLK_PLL0Source: PLL0 entry clock source.
                            This parameter must be a value of @ref CLK_PLL0_Clock_Source               */
  uint32_t PLL0_M;       /*!< PLL0_M: Division factor for PLL0 VCO input clock.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 31             */
  uint32_t PLL0_1stN;    /*!< PLL0_1stN: First Multiplication factor for PLL0 VCO output clock.
                            This parameter must be a value of @ref CLK_PLL0_Clock_1stDivider    */
  uint32_t PLL0_2rdN;    /*!< PLL0_2rdN: Second Multiplication factor for PLL0 VCO output clock.
                             This parameter must be a number between Min_Data = 10 and Max_Data = 511    */
} CLK_PLL0InitType;

/** @defgroup CLK_PLL1InitType  Type
  * @{
  */
typedef struct
{
  uint32_t PLL1_State;   /*!< The new state of the PLL1.
                            This parameter can be a value of @ref CLK_PLL1_Config                      */
  uint32_t PLL1_Source;  /*!< CLK_PLL1Source: PLL1 entry clock source.
                            This parameter must be a value of @ref CLK_PLL1_Clock_Source               */
  uint32_t PLL1_Frequency;
} CLK_PLL1InitType;

/** @defgroup CLK_OscInitType  Type
  * @{
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref CLK_Oscillator_Type                   */
  uint32_t RCHState;             /*!< The new state of the RCHState.
                                      This parameter can be a value of @ref CLK_RCH_Config                        */
  uint32_t XOHState;             /*!< The new state of the XOHState.
                                      This parameter can be a value of @ref CLK_XOH_Config                        */
  uint32_t XOLState;             /*!< The new state of the XOLState.
                                      This parameter can be a value of @ref CLK_XOL_Config                        */
  CLK_PLL0InitType  PLL0;
  
  CLK_PLL1InitType  PLL1;
  
} CLK_OscInitType;

/** @defgroup CLK_InitType  Type
  * @{
  */
typedef struct
{
#if defined (V32F20XXX_CM33_CORE0)
  uint32_t BusClock;
#endif /* V32F20XXX_CM33_CORE0 */
  uint32_t AHBCLKSource;
  uint32_t AHBCLKDivider;
  uint32_t APBCLKSource;
  uint32_t APBCLKDivider;
} CLK_InitType;

/** @defgroup MCO_Config Type
  * @{
  */
typedef struct
{
  GPIO_Type *Port;
  uint16_t   Pin;
  uint8_t    PinSource;
  uint8_t    AFConfig;
} MCO_Config;

/** @defgroup MCO_InitType Type
  * @{
  */
typedef struct
{
  uint32_t Source;
  uint32_t Divider;
  FunctionalState Output;
} MCO_InitType;

/** @defgroup CLK_Oscillator_Type Oscillator Type
  * @{
  */
#define CLK_OSCILLATORTYPE_NONE        0x00000000U   /*!< Oscillator configuration unchanged */
#define CLK_OSCILLATORTYPE_RCH         0x00000001U   /*!< RCH to configure */
#define CLK_OSCILLATORTYPE_XOH         0x00000002U   /*!< XOH to configure */
#define CLK_OSCILLATORTYPE_XOL         0x00000004U   /*!< XOL to configure */
#define IS_CLK_TYPE(TYPE) ((TYPE) < 8UL)

/** @defgroup CLK_RCH_Config RCH Config
  * @{
  */
#define CLK_RCH_OFF                    0UL
#define CLK_RCH_ON                     SYSCFGLP_RCH_CTRL0_RCHEN
#define IS_CLK_RCH(RCH) (((RCH) == CLK_RCH_OFF) || ((RCH) == CLK_RCH_ON))

/** @defgroup CLK_XOH_Config XOH Config
  * @{
  */
#define CLK_XOH_OFF                    0U                         /*!< XOH clock deactivation */
#define CLK_XOH_ON                     SYSCFGLP_XOH_CTRL0_XOHEN  /*!< XOH clock activation */
#define CLK_XOH_BYPASS                 SYSCFGLP_XOH_CTRL0_BYPASS /*!< External clock source for XOH clock */
#define IS_CLK_XOH(XOH) (((XOH) == CLK_XOH_OFF) ||\
                         ((XOH) == CLK_XOH_ON)  ||\
                         ((XOH) == CLK_XOH_BYPASS))

/** @defgroup CLK_XOL_Config XOL Config
  * @{
  */
#define CLK_XOL_OFF                    0U                         /*!< XOH clock deactivation */
#define CLK_XOL_ON                     RTC_ANA_CTRL_XTAL_EN_LV    /*!< XOH clock activation */
#define CLK_XOL_BYPASS                 RTC_ANA_CTRL_XTAL_BYP_LV   /*!< External clock source for XOH clock */
#define IS_CLK_XOL(XOL) (((XOL) == CLK_XOL_OFF) ||\
                         ((XOL) == CLK_XOL_ON)  ||\
                         ((XOL) == CLK_XOL_BYPASS))

/** @defgroup CLK_PLL0_Config PLL0 Config
  * @{
  */
#define CLK_PLL0_NONE                  0U                  /*!< PLL0 configuration unchanged */
#define CLK_PLL0_OFF                   1U                  /*!< PLL0 deactivation */
#define CLK_PLL0_ON                    2U                  /*!< PLL0 activation */
#define IS_CLK_PLL0(PLL0) (((PLL0) == CLK_PLL0_NONE) ||\
                           ((PLL0) == CLK_PLL0_OFF)  ||\
                           ((PLL0) == CLK_PLL0_ON))

/** @defgroup CLK_PLL0_Clock_Source PLL0 Clock Source
  * @{
  */
#define CLK_PLL0SOURCE_RCH_DIV4        PLL0_REFCLK_RCH_DIV4  /*!< RCH/4 selected as PLL0 entry clock source  */
#define CLK_PLL0SOURCE_XOH             PLL0_REFCLK_XOH       /*!< XOH clock selected as PLL0 entry clock source */
#define CLK_PLL0SOURCE_RCH             PLL0_REFCLK_RCH       /*!< RCH clock selected as PLL0 entry clock source */
#define CLK_PLL0SOURCE_RCH_DIV48       PLL0_REFCLK_RCH_DIV48 /*!< RCH/48 clock selected as PLL0 entry clock source */
#define IS_CLK_PLL0_SRC(SRC) (((SRC) == CLK_PLL0SOURCE_RCH_DIV4) ||\
                              ((SRC) == CLK_PLL0SOURCE_XOH)      ||\
                              ((SRC) == CLK_PLL0SOURCE_RCH)      ||\
                              ((SRC) == CLK_PLL0SOURCE_RCH_DIV48))

/** @defgroup CLK_PLL0_Clock_1stDivider PLL0 First Multiplication factor
  * @{
  */
#define CLK_PLL0_1stN_1               (0UL << SYSCFGLP_PLL0_CTRL1_DIV_INT_H_POS)
#define CLK_PLL0_1stN_2               (1UL << SYSCFGLP_PLL0_CTRL1_DIV_INT_H_POS)
#define CLK_PLL0_1stN_4               (2UL << SYSCFGLP_PLL0_CTRL1_DIV_INT_H_POS)
#define IS_CLK_PLL0_N1(N1) (((N1) == CLK_PLL0_1stN_1) ||\
                            ((N1) == CLK_PLL0_1stN_2) ||\
                            ((N1) == CLK_PLL0_1stN_4))

#define IS_CLK_PLL0_N2(N2) (((N2) > 9UL) && ((N2) < 512UL))

#define IS_CLK_PLL0_M(M) (((M) > 0UL) && ((M) < 32UL))


/** @defgroup PLL1_Frequency PLL1 Clock Frequency
  * @{
  */
#define CLK_PLL0_IN_12M_OUT_128M    (0U)
#define CLK_PLL0_IN_12M_OUT_144M    (1U)
#define CLK_PLL0_IN_12M_OUT_180M    (2U)
#define CLK_PLL0_IN_12M_OUT_192M    (3U)
#define CLK_PLL0_IN_48M_OUT_128M    (4U)
#define CLK_PLL0_IN_48M_OUT_144M    (5U)
#define CLK_PLL0_IN_48M_OUT_180M    (6U)
#define CLK_PLL0_IN_48M_OUT_192M    (7U)
#define CLK_PLL0_FREQCFG_MAX             (8UL)
#define IS_CLK_PLL0_FREQCFG(FREQCFG) ((FREQCFG) < CLK_PLL0_FREQCFG_MAX)

/** @defgroup PLL0 config
  * @{
  */
extern const CLK_PLL0Config pll0_config[CLK_PLL0_FREQCFG_MAX];
/** @defgroup CLK_PLL1_Config PLL1 Config
  * @{
  */
#define CLK_PLL1_NONE                  0U                  /*!< PLL1 configuration unchanged */
#define CLK_PLL1_OFF                   1U                  /*!< PLL1 deactivation */
#define CLK_PLL1_ON                    2U                  /*!< PLL1 activation */
#define IS_CLK_PLL1(PLL1) (((PLL1) == CLK_PLL1_NONE) ||\
                           ((PLL1) == CLK_PLL1_OFF)  ||\
                           ((PLL1) == CLK_PLL1_ON))

/** @defgroup CLK_PLL1_Clock_Source PLL1 Clock Source
  * @{
  */
#define CLK_PLL1SOURCE_XOL_32768       PLL1_REFCLK_32KXTAL   /*!< XOL selected as PLL1 entry clock source  */
#define CLK_PLL1SOURCE_RCL_32768       PLL1_REFCLK_RCL       /*!< RCL clock selected as PLL1 entry clock source */
#define CLK_PLL1SOURCE_RCH_DIV4_12M    PLL1_REFCLK_RCH_DIV4  /*!< RCH/4 clock selected as PLL1 entry clock source */
#define CLK_PLL1SOURCE_XOH_12M         PLL1_REFCLK_XOH       /*!< XOH clock selected as PLL1 entry clock source */
#define IS_CLK_PLL1_SRC(SRC) (((SRC) == CLK_PLL1SOURCE_XOL_32768)    ||\
                              ((SRC) == CLK_PLL1SOURCE_RCL_32768)    ||\
                              ((SRC) == CLK_PLL1SOURCE_RCH_DIV4_12M) ||\
                              ((SRC) == CLK_PLL1SOURCE_XOH_12M))

/** @defgroup PLL1_Frequency PLL1 Clock Frequency
  * @{
  */
#define CLK_PLL1_IN_32768_OUT_245_76M    (0U)
#define CLK_PLL1_IN_32768_OUT_26_2144M   (1U)
#define CLK_PLL1_IN_32768_OUT_61_44M     (2U)
#define CLK_PLL1_IN_32768_OUT_122_88M    (3U)
#define CLK_PLL1_IN_32768_OUT_184_32M    (4U)
#define CLK_PLL1_IN_12M_OUT_36_864M      (5U)
#define CLK_PLL1_IN_12M_OUT_200M         (6U)
#define CLK_PLL1_IN_12M_OUT_144M         (7U)
#define CLK_PLL1_IN_12M_OUT_282_24M      (8U)
#define CLK_PLL1_FREQCFG_MAX             (9UL)
#define IS_CLK_PLL1_FREQCFG(FREQCFG) ((FREQCFG) < CLK_PLL1_FREQCFG_MAX)

/** @defgroup BusCLKSource
  * @{
  */
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

#define CLK_BUSCLOCK0            (1UL)
#define CLK_BUSCLOCK1            (2UL)
#define IS_CLK_BUSCLK(BUS)           (((BUS) > 0UL) && ((BUS) < 4UL))

#define CLK_AHBCLKSOURCE_RCH          SYSCFG0_HCLK_SEL_RCH
#define CLK_AHBCLKSOURCE_PLL0         SYSCFG0_HCLK_SEL_PLL0
#define CLK_AHBCLKSOURCE_PLL1         SYSCFG0_HCLK_SEL_PLL1
#define CLK_AHBCLKSOURCE_XOH          SYSCFG0_HCLK_SEL_XOH
#define CLK_AHBCLKSOURCE_RCH_DIV4     SYSCFG0_HCLK_SEL_RCH_DIV4
#define CLK_AHBCLKSOURCE_RCH_DIV48    SYSCFG0_HCLK_SEL_RCH_DIV48
#define CLK_AHBCLKSOURCE_RCL          SYSCFG0_HCLK_SEL_32KRC
#define CLK_AHBCLKSOURCE_XOL          SYSCFG0_HCLK_SEL_32KXTAL

#define CLK_APBCLKSOURCE_RCH          SYSCFG0_PCLK_SEL_RCH
#define CLK_APBCLKSOURCE_PLL0         SYSCFG0_PCLK_SEL_PLL0
#define CLK_APBCLKSOURCE_PLL1         SYSCFG0_PCLK_SEL_PLL1
#define CLK_APBCLKSOURCE_XOH          SYSCFG0_PCLK_SEL_XOH
#define CLK_APBCLKSOURCE_RCH_DIV4     SYSCFG0_PCLK_SEL_RCH_DIV4
#define CLK_APBCLKSOURCE_RCH_DIV48    SYSCFG0_PCLK_SEL_RCH_DIV48
#define CLK_APBCLKSOURCE_RCL          SYSCFG0_PCLK_SEL_32KRC
#define CLK_APBCLKSOURCE_XOL          SYSCFG0_PCLK_SEL_32KXTAL
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */

#if defined (V32F20XXX_CM0_CORE)
#define CLK_AHBCLKSOURCE_RCH          SYSCFG1_HCLK_SEL_RCH
#define CLK_AHBCLKSOURCE_PLL0         SYSCFG1_HCLK_SEL_PLL0
#define CLK_AHBCLKSOURCE_PLL1         SYSCFG1_HCLK_SEL_PLL1
#define CLK_AHBCLKSOURCE_XOH          SYSCFG1_HCLK_SEL_XOH
#define CLK_AHBCLKSOURCE_RCH_DIV4     SYSCFG1_HCLK_SEL_RCH_DIV4
#define CLK_AHBCLKSOURCE_RCH_DIV48    SYSCFG1_HCLK_SEL_RCH_DIV48
#define CLK_AHBCLKSOURCE_RCL          SYSCFG1_HCLK_SEL_32KRC
#define CLK_AHBCLKSOURCE_XOL          SYSCFG1_HCLK_SEL_32KXTAL

#define CLK_APBCLKSOURCE_RCH          SYSCFG1_PCLK_SEL_RCH
#define CLK_APBCLKSOURCE_PLL0         SYSCFG1_PCLK_SEL_PLL0
#define CLK_APBCLKSOURCE_PLL1         SYSCFG1_PCLK_SEL_PLL1
#define CLK_APBCLKSOURCE_XOH          SYSCFG1_PCLK_SEL_XOH
#define CLK_APBCLKSOURCE_RCH_DIV4     SYSCFG1_PCLK_SEL_RCH_DIV4
#define CLK_APBCLKSOURCE_RCH_DIV48    SYSCFG1_PCLK_SEL_RCH_DIV48
#define CLK_APBCLKSOURCE_RCL          SYSCFG1_PCLK_SEL_32KRC
#define CLK_APBCLKSOURCE_XOL          SYSCFG1_PCLK_SEL_32KXTAL
#endif /* V32F20XXX_CM0_CORE */

#define IS_CLK_AHBSRC(SRC) (((SRC) == CLK_AHBCLKSOURCE_RCH)       ||\
                            ((SRC) == CLK_AHBCLKSOURCE_PLL0)      ||\
                            ((SRC) == CLK_AHBCLKSOURCE_PLL1)      ||\
                            ((SRC) == CLK_AHBCLKSOURCE_XOH)       ||\
                            ((SRC) == CLK_AHBCLKSOURCE_RCH_DIV4)  ||\
                            ((SRC) == CLK_AHBCLKSOURCE_RCH_DIV48) ||\
                            ((SRC) == CLK_AHBCLKSOURCE_RCL)       ||\
                            ((SRC) == CLK_AHBCLKSOURCE_XOL))

#define IS_CLK_APBSRC(SRC) (((SRC) == CLK_APBCLKSOURCE_RCH)       ||\
                            ((SRC) == CLK_APBCLKSOURCE_PLL0)      ||\
                            ((SRC) == CLK_APBCLKSOURCE_PLL1)      ||\
                            ((SRC) == CLK_APBCLKSOURCE_XOH)       ||\
                            ((SRC) == CLK_APBCLKSOURCE_RCH_DIV4)  ||\
                            ((SRC) == CLK_APBCLKSOURCE_RCH_DIV48) ||\
                            ((SRC) == CLK_APBCLKSOURCE_RCL)       ||\
                            ((SRC) == CLK_APBCLKSOURCE_XOL))

#define IS_CLK_AHBDIV(DIV) (((DIV) > 0UL) && ((DIV) < 257UL))

#define IS_CLK_APBDIV(DIV) (((DIV) > 0UL) && ((DIV) < 257UL))

#define IS_PLL0_SOURCE_XOH    ((SYSCFGLP->PLL0_CTRL0&SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_MASK) == PLL0_REFCLK_XOH)
#define IS_PLL1_SOURCE_XOH    ((SYSCFGLP->PLL1_CTRL0&SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_MASK) == PLL1_REFCLK_XOH)
#define IS_PLL1_SOURCE_PLL0   ((SYSCFGLP->PLL1_CTRL0&SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_MASK) == PLL1_REFCLK_PLL0)

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

#define IS_HCLK_SOURCE_PLL0    ((SYSCFG0->CLK_SEL&SYSCFG0_HCLK_SEL_MASK) == SYSCFG0_HCLK_SEL_PLL0)
#define IS_HCLK_SOURCE_PLL1    ((SYSCFG0->CLK_SEL&SYSCFG0_HCLK_SEL_MASK) == SYSCFG0_HCLK_SEL_PLL1)
#define IS_HCLK_SOURCE_XOH     (((SYSCFG0->CLK_SEL&SYSCFG0_HCLK_SEL_MASK) == SYSCFG0_HCLK_SEL_XOH) ||\
                               ((IS_HCLK_SOURCE_PLL0) && (IS_PLL0_SOURCE_XOH)) ||\
                               ((IS_HCLK_SOURCE_PLL1) && (IS_PLL1_SOURCE_XOH)) ||\
                               ((IS_HCLK_SOURCE_PLL1) && (IS_PLL1_SOURCE_PLL0) && (IS_PLL0_SOURCE_XOH)))

#define IS_PCLK_SOURCE_PLL0    ((SYSCFG0->CLK_SEL&SYSCFG0_PCLK_SEL_MASK) == SYSCFG0_PCLK_SEL_PLL0)
#define IS_PCLK_SOURCE_PLL1    ((SYSCFG0->CLK_SEL&SYSCFG0_PCLK_SEL_MASK) == SYSCFG0_PCLK_SEL_PLL1)
#define IS_PCLK_SOURCE_XOH     (((SYSCFG0->CLK_SEL&SYSCFG0_PCLK_SEL_MASK) == SYSCFG0_PCLK_SEL_XOH) ||\
                               ((IS_PCLK_SOURCE_PLL0) && (IS_PLL0_SOURCE_XOH)) ||\
                               ((IS_PCLK_SOURCE_PLL1) && (IS_PLL1_SOURCE_XOH)) ||\
                               ((IS_PCLK_SOURCE_PLL1) && (IS_PLL1_SOURCE_PLL0) && (IS_PLL0_SOURCE_XOH)))
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */

#if defined (V32F20XXX_CM0_CORE)

#define IS_HCLK_SOURCE_PLL0    ((SYSCFG1->CLKSEL&SYSCFG1_HCLK_SEL_MASK) == SYSCFG1_HCLK_SEL_PLL0)
#define IS_HCLK_SOURCE_PLL1    ((SYSCFG1->CLKSEL&SYSCFG1_HCLK_SEL_MASK) == SYSCFG1_HCLK_SEL_PLL1)
#define IS_HCLK_SOURCE_XOH     (((SYSCFG1->CLKSEL&SYSCFG1_HCLK_SEL_MASK) == SYSCFG1_HCLK_SEL_XOH)  ||\
                               ((IS_HCLK_SOURCE_PLL0) && (IS_PLL0_SOURCE_XOH)) ||\
                               ((IS_HCLK_SOURCE_PLL1) && (IS_PLL1_SOURCE_XOH)) ||\
                               ((IS_HCLK_SOURCE_PLL1) && (IS_PLL1_SOURCE_PLL0) && (IS_PLL0_SOURCE_XOH)))
                               
#define IS_PCLK_SOURCE_PLL0    ((SYSCFG1->CLKSEL&SYSCFG1_PCLK_SEL_MASK) == SYSCFG1_PCLK_SEL_PLL0)
#define IS_PCLK_SOURCE_PLL1    ((SYSCFG1->CLKSEL&SYSCFG1_PCLK_SEL_MASK) == SYSCFG1_PCLK_SEL_PLL1)
#define IS_PCLK_SOURCE_XOH     (((SYSCFG1->CLKSEL&SYSCFG1_PCLK_SEL_MASK) == SYSCFG1_PCLK_SEL_XOH)  ||\
                               ((IS_PCLK_SOURCE_PLL0) && (IS_PLL0_SOURCE_XOH)) ||\
                               ((IS_PCLK_SOURCE_PLL1) && (IS_PLL1_SOURCE_XOH)) ||\
                               ((IS_PCLK_SOURCE_PLL1) && (IS_PLL1_SOURCE_PLL0) && (IS_PLL0_SOURCE_XOH)))

#endif /* V32F20XXX_CM0_CORE */

/** @defgroup CLK_MCO_Index MCO Index
  * @{
  */
#define CLK_MCO1               (0UL)
#define CLK_MCO2               (1UL)
#define CLK_MCO3               (2UL)
#define CLK_MCO4               (3UL)
#define IS_CLK_MCO(MCO) ((MCO) < 4UL)

/** @defgroup CLK_MCO_Source MCO Source
  * @{
  */
#define CLK_MCOSOURCE_RCH        (0UL << SYSCFGLP_CLKOUT_SEL_POS)
#define CLK_MCOSOURCE_PLL0       (1UL << SYSCFGLP_CLKOUT_SEL_POS)
#define CLK_MCOSOURCE_PLL1       (2UL << SYSCFGLP_CLKOUT_SEL_POS)
#define CLK_MCOSOURCE_XOH        (3UL << SYSCFGLP_CLKOUT_SEL_POS)
#define CLK_MCOSOURCE_RCL        (4UL << SYSCFGLP_CLKOUT_SEL_POS)
#define CLK_MCOSOURCE_XOL        (5UL << SYSCFGLP_CLKOUT_SEL_POS)
#define CLK_MCOSOURCE_USBHS_UTMI (6UL << SYSCFGLP_CLKOUT_SEL_POS)
#define IS_CLK_MCOSOURCE(MCOSOURCE) (((MCOSOURCE) == CLK_MCOSOURCE_RCH)  ||\
                                     ((MCOSOURCE) == CLK_MCOSOURCE_PLL0) ||\
                                     ((MCOSOURCE) == CLK_MCOSOURCE_PLL1) ||\
                                     ((MCOSOURCE) == CLK_MCOSOURCE_XOH)  ||\
                                     ((MCOSOURCE) == CLK_MCOSOURCE_RCL)  ||\
                                     ((MCOSOURCE) == CLK_MCOSOURCE_XOL)  ||\
                                     ((MCOSOURCE) == CLK_MCOSOURCE_USBHS_UTMI))

#define IS_CLK_MCODIV(MCODIV) (((MCODIV) > 0UL) && ((MCODIV) < 257UL))

//AUTOTRIM
#define SYSLP_AUTOTRIMC_EN             ((uint32_t)0x00000001)
#define SYSLP_AUTOTRIMC_SRC_SEL_RCH    ((uint32_t)0x00000000)
#define SYSLP_AUTOTRIMC_SRC_SEL_PLL    ((uint32_t)0x00000002)
#define SYSLP_AUTOTRIMC_SRC_SEL        ((uint32_t)0x00000002)
#define SYSLP_AUTOTRIM_UPPER_EXPT_MASK    ((uint32_t)0x0007FFFF)
#define SYSLP_AUTOTRIM_LOWER_EXPT_MASK    ((uint32_t)0x0007FFFF)
#define AUTOTRIM_SRC_RCH            SYSLP_AUTOTRIMC_SRC_SEL_RCH
#define AUTOTRIM_SRC_PLL            SYSLP_AUTOTRIMC_SRC_SEL_PLL
#define IS_RCC_AUTOTRIM_SRC_SEL(VALUE)  (((VALUE) == AUTOTRIM_SRC_RCH) || ((VALUE) == AUTOTRIM_SRC_PLL))
/**
  * @brief  Autotrim Init Structure definition
  */

typedef struct
{
  uint32_t Autotrim_SRC; //select autotrim source clk
  uint32_t Autotrim_UpperExpt;
  uint32_t Autotrim_LowerExpt;
} Autotrim_InitType;

/* Exported functions --------------------------------------------------------*/ 

STD_StatusType CLK_OscConfig(CLK_OscInitType *CLK_OscInitStruct);
STD_StatusType CLK_Config(CLK_InitType *CLK_InitStruct);
void           CLK_MCOConfig(uint32_t CLK_MCOx, MCO_InitType *MCO_InitStruct);

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

uint32_t       CLK_GetHCLK0Freq(void);
uint32_t       CLK_GetPCLK0Freq(void);
uint32_t       CLK_GetI2SClockFreq(I2S_Type *I2Sx);
uint32_t       CLK_GetFlexcommClockFreq(FLEXCOMM_Type FLEXCOMMx);
void CLK_AutotrimCmd(FunctionalState NewState);
void CLK_AutotrimInit(Autotrim_InitType *Autotrim_Initstruct);

#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */

uint32_t       CLK_GetHCLK1Freq(void);
uint32_t       CLK_GetPCLK1Freq(void);
uint32_t       CLK_GetUART14_19ClockFreq(UART_Type *UARTx);
uint8_t        CLK_GetXTAL32KAbsentStatus(void);
void           CLK_ClearXTAL32KAbsentStatus(void);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_CLK_H */

/*********************************** END OF FILE ******************************/
