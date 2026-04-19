/**
  ******************************************************************************
  * @file    lib_timer.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-04-21
  * @brief   This file contains all the functions prototypes for the TMR firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_TIMER_H
#define __LIB_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup TMR
  * @{
  */

/** @defgroup TMR_Exported_Types
  * @{
  */ 

/** 
  * @brief  TMR Time Base Init structure definition
  * @note   This structure is used with all TMRx except for TMR0.
  */

typedef struct
{
  uint16_t TMR_Prescaler;         /*!< Specifies the prescaler value used to divide the TMR clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TMR_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TMR_Counter_Mode */

  uint16_t TMR_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */ 

  uint16_t TMR_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TMR_Clock_Division_CKD */

  uint8_t TMR_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF. 
                                       @note This parameter is valid only for ETMR0 and ETMR1. */
} TMR_TimeBaseInitType; 


/** 
  * @brief  TMR Output Compare Init structure definition  
  */
typedef struct
{
  uint16_t TMR_OCMode;        /*!< Specifies the TMR mode.
                                   This parameter can be a value of @ref TMR_Output_Compare_and_PWM_modes */

  uint16_t TMR_OutputState;   /*!< Specifies the TMR Output Compare state.
                                   This parameter can be a value of @ref TMR_Output_Compare_state */

  uint16_t TMR_OutputNState;  /*!< Specifies the TMR complementary Output Compare state.
                                   This parameter can be a value of @ref TMR_Output_Compare_N_state
                                   @note This parameter is valid only for ETMR0 and ETMR1. */

  uint16_t TMR_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TMR_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TMR_Output_Compare_Polarity */

  uint16_t TMR_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TMR_Output_Compare_N_Polarity
                                   @note This parameter is valid only for ETMR0 and ETMR1. */

  uint16_t TMR_OCIdleState;   /*!< Specifies the TMR Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TMR_Output_Compare_Idle_State
                                   @note This parameter is valid only for ETMR0 and ETMR1. */

  uint16_t TMR_OCNIdleState;  /*!< Specifies the TMR Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TMR_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for ETMR0 and ETMR1. */
} TMR_OCInitType;


/** 
  * @brief  TMR Input Capture Init structure definition  
  */
typedef struct
{
  uint16_t TMR_Channel;       /*!< Specifies the TMR channel.
                                  This parameter can be a value of @ref TMR_Channel */

  uint16_t TMR_ICPolarity;    /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TMR_Input_Capture_Polarity */

  uint16_t TMR_ICSelection;   /*!< Specifies the input.
                                  This parameter can be a value of @ref TMR_Input_Capture_Selection */

  uint16_t TMR_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TMR_Input_Capture_Prescaler */

  uint16_t TMR_ICFilter;      /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TMR_ICInitType;

/** 
  * @brief  BDTR structure definition 
  * @note   This structure is used only with ETMR0 and ETMR1.
  */
typedef struct
{
  uint16_t TMR_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref TMR_OSSR_Off_State_Selection_for_Run_mode_state */

  uint16_t TMR_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref TMR_OSSI_Off_State_Selection_for_Idle_mode_state */

  uint16_t TMR_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref TMR_Lock_level */ 

  uint16_t TMR_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

  uint16_t TMR_Break;            /*!< Specifies whether the TMR Break input is enabled or not. 
                                      This parameter can be a value of @ref TMR_Break_Input_enable_disable */

  uint16_t TMR_BreakPolarity;    /*!< Specifies the TMR Break Input pin polarity.
                                      This parameter can be a value of @ref TMR_Break_Polarity */

  uint16_t TMR_AutomaticOutput;  /*!< Specifies whether the TMR Automatic Output feature is enabled or not. 
                                      This parameter can be a value of @ref TMR_AOE_Bit_Set_Reset */
} TMR_BDTRInitType;


/**
  * @}
  */


/** @defgroup TMR_Exported_constants 
  * @{
  */

#define IS_TMR_ALL_PERIPH(PERIPH) (((PERIPH) == ETMR0) || \
                                   ((PERIPH) == ETMR1) || \
                                   ((PERIPH) == GTMR0) || \
                                   ((PERIPH) == GTMR1) || \
                                   ((PERIPH) == GTMR2) || \
                                   ((PERIPH) == GTMR3))

#define IS_TMR_ENHANCED_PERIPH(PERIPH) (((PERIPH) == ETMR0) || \
                                        ((PERIPH) == ETMR1))

#define IS_TMR_GENERAL_PERIPH(PERIPH) (((PERIPH) == GTMR0) || \
                                       ((PERIPH) == GTMR1) || \
                                       ((PERIPH) == GTMR2) || \
                                       ((PERIPH) == GTMR3))




/** @defgroup TMR_Output_Compare_and_PWM_modes 
  * @{
  */
#define TMR_OCMode_Timing            ((uint16_t)0x0000)
#define TMR_OCMode_Active            ((uint16_t)0x0010)
#define TMR_OCMode_Inactive          ((uint16_t)0x0020)
#define TMR_OCMode_Toggle            ((uint16_t)0x0030)
#define TMR_ForcedAction_InActive    ((uint16_t)0x0040)
#define TMR_ForcedAction_Active      ((uint16_t)0x0050)
#define TMR_OCMode_PWM1              ((uint16_t)0x0060)
#define TMR_OCMode_PWM2              ((uint16_t)0x0070)

#define IS_TMR_OC_MODE(MODE)         (((MODE) == TMR_OCMode_Timing)   || \
                                      ((MODE) == TMR_OCMode_Active)   || \
                                      ((MODE) == TMR_OCMode_Inactive) || \
                                      ((MODE) == TMR_OCMode_Toggle)   || \
                                      ((MODE) == TMR_OCMode_PWM1)     || \
                                      ((MODE) == TMR_OCMode_PWM2))
#define IS_TMR_OCM(MODE)             (((MODE) == TMR_OCMode_Timing)       || \
                                      ((MODE) == TMR_OCMode_Active)       || \
                                      ((MODE) == TMR_OCMode_Inactive)     || \
                                      ((MODE) == TMR_OCMode_Toggle)       || \
                                      ((MODE) == TMR_OCMode_PWM1)         || \
                                      ((MODE) == TMR_OCMode_PWM2)         || \
                                      ((MODE) == TMR_ForcedAction_Active) || \
                                      ((MODE) == TMR_ForcedAction_InActive))
#define IS_TMR_FORCED_ACTION(ACTION) (((ACTION) == TMR_ForcedAction_Active) || \
                                      ((ACTION) == TMR_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TMR_One_Pulse_Mode 
  * @{
  */
#define TMR_OPMode_Single      ((uint16_t)0x0008)
#define TMR_OPMode_Repetitive  ((uint16_t)0x0000)
#define IS_TMR_OPM_MODE(MODE)  (((MODE) == TMR_OPMode_Single) || \
                                ((MODE) == TMR_OPMode_Repetitive))
/**
  * @}
  */ 

/** @defgroup TMR_Channel 
  * @{
  */
#define TMR_Channel_1           ((uint16_t)0x0000)
#define TMR_Channel_2           ((uint16_t)0x0004)
#define TMR_Channel_3           ((uint16_t)0x0008)
#define TMR_Channel_4           ((uint16_t)0x000C)
#define IS_TMR_CHANNEL(CHANNEL) (((CHANNEL) == TMR_Channel_1) || \
                                 ((CHANNEL) == TMR_Channel_2) || \
                                 ((CHANNEL) == TMR_Channel_3) || \
                                 ((CHANNEL) == TMR_Channel_4))

#define IS_TMR_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TMR_Channel_1) || \
                                      ((CHANNEL) == TMR_Channel_2))

#define IS_TMR_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TMR_Channel_1) || \
                                               ((CHANNEL) == TMR_Channel_2) || \
                                               ((CHANNEL) == TMR_Channel_3))
/**
  * @}
  */

/** @defgroup TMR_Clock_Division_CKD
  * @{
  */
#define TMR_CKD_DIV1        ((uint16_t)0x0000)
#define TMR_CKD_DIV2        ((uint16_t)0x0100)
#define TMR_CKD_DIV4        ((uint16_t)0x0200)
#define IS_TMR_CKD_DIV(DIV) (((DIV) == TMR_CKD_DIV1) || \
                             ((DIV) == TMR_CKD_DIV2) || \
                             ((DIV) == TMR_CKD_DIV4))
/**
  * @}
  */

/** @defgroup TMR_Counter_Mode 
  * @{
  */
#define TMR_CounterMode_Up              ((uint16_t)0x0000)
#define TMR_CounterMode_Down            ((uint16_t)0x0010)
#define TMR_CounterMode_CenterAligned1  ((uint16_t)0x0020)
#define TMR_CounterMode_CenterAligned2  ((uint16_t)0x0040)
#define TMR_CounterMode_CenterAligned3  ((uint16_t)0x0060)
#define IS_TMR_COUNTER_MODE(MODE)       (((MODE) == TMR_CounterMode_Up) ||  \
                                         ((MODE) == TMR_CounterMode_Down) || \
                                         ((MODE) == TMR_CounterMode_CenterAligned1) || \
                                         ((MODE) == TMR_CounterMode_CenterAligned2) || \
                                         ((MODE) == TMR_CounterMode_CenterAligned3))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_Polarity 
  * @{
  */
#define TMR_OCPolarity_High           ((uint16_t)0x0000)
#define TMR_OCPolarity_Low            ((uint16_t)0x0002)
#define IS_TMR_OC_POLARITY(POLARITY)  (((POLARITY) == TMR_OCPolarity_High) || \
                                       ((POLARITY) == TMR_OCPolarity_Low))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_N_Polarity 
  * @{
  */
#define TMR_OCNPolarity_High           ((uint16_t)0x0000)
#define TMR_OCNPolarity_Low            ((uint16_t)0x0008)
#define IS_TMR_OCN_POLARITY(POLARITY)  (((POLARITY) == TMR_OCNPolarity_High) || \
                                        ((POLARITY) == TMR_OCNPolarity_Low))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_State 
  * @{
  */
#define TMR_OutputState_Disable     ((uint16_t)0x0000)
#define TMR_OutputState_Enable      ((uint16_t)0x0001)
#define IS_TMR_OUTPUT_STATE(STATE)  (((STATE) == TMR_OutputState_Disable) || \
                                     ((STATE) == TMR_OutputState_Enable))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_N_State
  * @{
  */
#define TMR_OutputNState_Disable     ((uint16_t)0x0000)
#define TMR_OutputNState_Enable      ((uint16_t)0x0004)
#define IS_TMR_OUTPUTN_STATE(STATE)  (((STATE) == TMR_OutputNState_Disable) || \
                                      ((STATE) == TMR_OutputNState_Enable))
/**
  * @}
  */

/** @defgroup TMR_Capture_Compare_State
  * @{
  */
#define TMR_CCx_Enable     ((uint16_t)0x0001)
#define TMR_CCx_Disable    ((uint16_t)0x0000)
#define IS_TMR_CCX(CCX)    (((CCX) == TMR_CCx_Enable) || ((CCX) == TMR_CCx_Disable))
/**
  * @}
  */

/** @defgroup TMR_Capture_Compare_N_State
  * @{
  */
#define TMR_CCxN_Enable     ((uint16_t)0x0004)
#define TMR_CCxN_Disable    ((uint16_t)0x0000)
#define IS_TMR_CCXN(CCXN)   (((CCXN) == TMR_CCxN_Enable) || ((CCXN) == TMR_CCxN_Disable))
/**
  * @}
  */

/** @defgroup TMR_Break_Input_enable_disable 
  * @{
  */
#define TMR_Break_Enable          ((uint16_t)0x1000)
#define TMR_Break_Disable         ((uint16_t)0x0000)
#define IS_TMR_BREAK_STATE(STATE) (((STATE) == TMR_Break_Enable) || ((STATE) == TMR_Break_Disable))
/**
  * @}
  */

/** @defgroup TMR_Break_Polarity 
  * @{
  */
#define TMR_BreakPolarity_Low            ((uint16_t)0x0000)
#define TMR_BreakPolarity_High           ((uint16_t)0x2000)
#define IS_TMR_BREAK_POLARITY(POLARITY)  (((POLARITY) == TMR_BreakPolarity_Low) || \
                                          ((POLARITY) == TMR_BreakPolarity_High))
/**
  * @}
  */

/** @defgroup TMR_AOE_Bit_Set_Reset 
  * @{
  */
#define TMR_AutomaticOutput_Enable           ((uint16_t)0x4000)
#define TMR_AutomaticOutput_Disable          ((uint16_t)0x0000)
#define IS_TMR_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TMR_AutomaticOutput_Enable) || \
                                              ((STATE) == TMR_AutomaticOutput_Disable))
/**
  * @}
  */

/** @defgroup TMR_Lock_level
  * @{
  */
#define TMR_LOCKLevel_OFF          ((uint16_t)0x0000)
#define TMR_LOCKLevel_1            ((uint16_t)0x0100)
#define TMR_LOCKLevel_2            ((uint16_t)0x0200)
#define TMR_LOCKLevel_3            ((uint16_t)0x0300)
#define IS_TMR_LOCK_LEVEL(LEVEL)   (((LEVEL) == TMR_LOCKLevel_OFF) || \
                                    ((LEVEL) == TMR_LOCKLevel_1)   || \
                                    ((LEVEL) == TMR_LOCKLevel_2)   || \
                                    ((LEVEL) == TMR_LOCKLevel_3))
/**
  * @}
  */

/** @defgroup TMR_OSSI_Off_State_Selection_for_Idle_mode_state 
  * @{
  */
#define TMR_OSSIState_Enable        ((uint16_t)0x0400)
#define TMR_OSSIState_Disable       ((uint16_t)0x0000)
#define IS_TMR_OSSI_STATE(STATE)    (((STATE) == TMR_OSSIState_Enable) || \
                                     ((STATE) == TMR_OSSIState_Disable))
/**
  * @}
  */

/** @defgroup TMR_OSSR_Off_State_Selection_for_Run_mode_state
  * @{
  */
#define TMR_OSSRState_Enable        ((uint16_t)0x0800)
#define TMR_OSSRState_Disable       ((uint16_t)0x0000)
#define IS_TMR_OSSR_STATE(STATE)    (((STATE) == TMR_OSSRState_Enable) || \
                                     ((STATE) == TMR_OSSRState_Disable))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_Idle_State 
  * @{
  */
#define TMR_OCIdleState_Set         ((uint16_t)0x0100)
#define TMR_OCIdleState_Reset       ((uint16_t)0x0000)
#define IS_TMR_OCIDLE_STATE(STATE)  (((STATE) == TMR_OCIdleState_Set) || \
                                     ((STATE) == TMR_OCIdleState_Reset))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_N_Idle_State 
  * @{
  */
#define TMR_OCNIdleState_Set         ((uint16_t)0x0200)
#define TMR_OCNIdleState_Reset       ((uint16_t)0x0000)
#define IS_TMR_OCNIDLE_STATE(STATE)  (((STATE) == TMR_OCNIdleState_Set) || \
                                      ((STATE) == TMR_OCNIdleState_Reset))
/**
  * @}
  */ 

/** @defgroup TMR_Input_Capture_Polarity 
  * @{
  */
#define  TMR_ICPolarity_Rising         ((uint16_t)0x0000)
#define  TMR_ICPolarity_Falling        ((uint16_t)0x0002)
#define  TMR_ICPolarity_BothEdge       ((uint16_t)0x000A)
#define IS_TMR_IC_POLARITY_LITE(POLARITY)   (((POLARITY) == TMR_ICPolarity_Rising) || \
                                        ((POLARITY) == TMR_ICPolarity_Falling)|| \
                                        ((POLARITY) == TMR_ICPolarity_BothEdge))
#define IS_TMR_IC_POLARITY(POLARITY) (((POLARITY) == TMR_ICPolarity_Rising) || \
                                      ((POLARITY) == TMR_ICPolarity_Falling))
/**
  * @}
  */

/** @defgroup TMR_Input_Capture_Selection 
  * @{
  */
#define TMR_ICSelection_DirectTI       ((uint16_t)0x0001) /*!< TMR Input 1, 2, 3 or 4 is selected to be 
                                                               connected to IC1, IC2, IC3 or IC4, respectively */
#define TMR_ICSelection_IndirectTI     ((uint16_t)0x0002) /*!< TMR Input 1, 2, 3 or 4 is selected to be
                                                               connected to IC2, IC1, IC4 or IC3, respectively. */
#define TMR_ICSelection_TRC            ((uint16_t)0x0003) /*!< TMR Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TMR_IC_SELECTION(SELECTION) (((SELECTION) == TMR_ICSelection_DirectTI) || \
                                        ((SELECTION) == TMR_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TMR_ICSelection_TRC))
/**
  * @}
  */ 


/** @defgroup TMR_Input_Capture_Prescaler 
  * @{
  */
#define TMR_ICPSC_DIV1                 ((uint16_t)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define TMR_ICPSC_DIV2                 ((uint16_t)0x0004) /*!< Capture performed once every 2 events. */
#define TMR_ICPSC_DIV4                 ((uint16_t)0x0008) /*!< Capture performed once every 4 events. */
#define TMR_ICPSC_DIV8                 ((uint16_t)0x000C) /*!< Capture performed once every 8 events. */
#define IS_TMR_IC_PRESCALER(PRESCALER) (((PRESCALER) == TMR_ICPSC_DIV1) || \
                                        ((PRESCALER) == TMR_ICPSC_DIV2) || \
                                        ((PRESCALER) == TMR_ICPSC_DIV4) || \
                                        ((PRESCALER) == TMR_ICPSC_DIV8))
/**
  * @}
  */ 

/** @defgroup TMR_interrupt_sources 
  * @{
  */
#define TMR_IT_Update        ((uint16_t)0x0001)
#define TMR_IT_CC1           ((uint16_t)0x0002)
#define TMR_IT_CC2           ((uint16_t)0x0004)
#define TMR_IT_CC3           ((uint16_t)0x0008)
#define TMR_IT_CC4           ((uint16_t)0x0010)
#define TMR_IT_COM           ((uint16_t)0x0020)
#define TMR_IT_Trigger       ((uint16_t)0x0040)
#define TMR_IT_Break         ((uint16_t)0x0080)
#define IS_TMR_IT(IT)        ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))
#define IS_TMR_GET_IT(IT)    (((IT) == TMR_IT_Update)  || \
                              ((IT) == TMR_IT_CC1)     || \
                              ((IT) == TMR_IT_CC2)     || \
                              ((IT) == TMR_IT_CC3)     || \
                              ((IT) == TMR_IT_CC4)     || \
                              ((IT) == TMR_IT_COM)     || \
                              ((IT) == TMR_IT_Trigger) || \
                              ((IT) == TMR_IT_Break))
/**
  * @}
  */

/** @defgroup TMR_DMA_sources 
  * @{
  */

#define TMR_DMA_Update            ((uint16_t)0x0100)
#define TMR_DMA_CC1               ((uint16_t)0x0200)
#define TMR_DMA_CC2               ((uint16_t)0x0400)
#define TMR_DMA_CC3               ((uint16_t)0x0800)
#define TMR_DMA_CC4               ((uint16_t)0x1000)
#define TMR_DMA_COM               ((uint16_t)0x2000)
#define TMR_DMA_Trigger           ((uint16_t)0x4000)
#define IS_TMR_DMA_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))
/**
  * @}
  */

/** @defgroup TMR_External_Trigger_Prescaler 
  * @{
  */
#define TMR_ExtTRGPSC_OFF                ((uint16_t)0x0000)
#define TMR_ExtTRGPSC_DIV2               ((uint16_t)0x1000)
#define TMR_ExtTRGPSC_DIV4               ((uint16_t)0x2000)
#define TMR_ExtTRGPSC_DIV8               ((uint16_t)0x3000)
#define IS_TMR_EXT_PRESCALER(PRESCALER)  (((PRESCALER) == TMR_ExtTRGPSC_OFF)  || \
                                          ((PRESCALER) == TMR_ExtTRGPSC_DIV2) || \
                                          ((PRESCALER) == TMR_ExtTRGPSC_DIV4) || \
                                          ((PRESCALER) == TMR_ExtTRGPSC_DIV8))
/**
  * @}
  */

/** @defgroup TMR_Internal_Trigger_Selection 
  * @{
  */
#define TMR_TS_ITR0                         ((uint16_t)0x0000)
#define TMR_TS_ITR1                         ((uint16_t)0x0010)
#define TMR_TS_ITR2                         ((uint16_t)0x0020)
#define TMR_TS_ITR3                         ((uint16_t)0x0030)
#define TMR_TS_TI1F_ED                      ((uint16_t)0x0040)
#define TMR_TS_TI1FP1                       ((uint16_t)0x0050)
#define TMR_TS_TI2FP2                       ((uint16_t)0x0060)
#define TMR_TS_ETRF                         ((uint16_t)0x0070)
#define IS_TMR_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TMR_TS_ITR0)    || \
                                             ((SELECTION) == TMR_TS_ITR1)    || \
                                             ((SELECTION) == TMR_TS_ITR2)    || \
                                             ((SELECTION) == TMR_TS_ITR3)    || \
                                             ((SELECTION) == TMR_TS_TI1F_ED) || \
                                             ((SELECTION) == TMR_TS_TI1FP1)  || \
                                             ((SELECTION) == TMR_TS_TI2FP2)  || \
                                             ((SELECTION) == TMR_TS_ETRF))
#define IS_TMR_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TMR_TS_ITR0) || \
                                                      ((SELECTION) == TMR_TS_ITR1) || \
                                                      ((SELECTION) == TMR_TS_ITR2) || \
                                                      ((SELECTION) == TMR_TS_ITR3))
/**
  * @}
  */

/** @defgroup TMR_TIx_External_Clock_Source 
  * @{
  */
#define TMR_TIxExternalCLK1Source_TI1      ((uint16_t)0x0050)
#define TMR_TIxExternalCLK1Source_TI2      ((uint16_t)0x0060)
#define TMR_TIxExternalCLK1Source_TI1ED    ((uint16_t)0x0040)
#define IS_TMR_TIXCLK_SOURCE(SOURCE) (((SOURCE) == TMR_TIxExternalCLK1Source_TI1) || \
                                      ((SOURCE) == TMR_TIxExternalCLK1Source_TI2) || \
                                      ((SOURCE) == TMR_TIxExternalCLK1Source_TI1ED))
/**
  * @}
  */

/** @defgroup TMR_External_Trigger_Polarity 
  * @{
  */
#define TMR_ExtTRGPolarity_Inverted        ((uint16_t)0x8000)
#define TMR_ExtTRGPolarity_NonInverted     ((uint16_t)0x0000)
#define IS_TMR_EXT_POLARITY(POLARITY)      (((POLARITY) == TMR_ExtTRGPolarity_Inverted) || \
                                            ((POLARITY) == TMR_ExtTRGPolarity_NonInverted))
/**
  * @}
  */

/** @defgroup TMR_Prescaler_Reload_Mode 
  * @{
  */
#define TMR_PSCReloadMode_Update           ((uint16_t)0x0000)
#define TMR_PSCReloadMode_Immediate        ((uint16_t)0x0001)
#define IS_TMR_PRESCALER_RELOAD(RELOAD)    (((RELOAD) == TMR_PSCReloadMode_Update) || \
                                            ((RELOAD) == TMR_PSCReloadMode_Immediate))
/**
  * @}
  */

/** @defgroup TMR_Encoder_Mode 
  * @{
  */
#define TMR_EncoderMode_TI1                ((uint16_t)0x0001)
#define TMR_EncoderMode_TI2                ((uint16_t)0x0002)
#define TMR_EncoderMode_TI12               ((uint16_t)0x0003)
#define IS_TMR_ENCODER_MODE(MODE)          (((MODE) == TMR_EncoderMode_TI1) || \
                                            ((MODE) == TMR_EncoderMode_TI2) || \
                                            ((MODE) == TMR_EncoderMode_TI12))
/**
  * @}
  */

/** @defgroup TMR_Event_Source 
  * @{
  */
#define TMR_EventSource_Update             ((uint16_t)0x0001)
#define TMR_EventSource_CC1                ((uint16_t)0x0002)
#define TMR_EventSource_CC2                ((uint16_t)0x0004)
#define TMR_EventSource_CC3                ((uint16_t)0x0008)
#define TMR_EventSource_CC4                ((uint16_t)0x0010)
#define TMR_EventSource_COM                ((uint16_t)0x0020)
#define TMR_EventSource_Trigger            ((uint16_t)0x0040)
#define TMR_EventSource_Break              ((uint16_t)0x0080)
#define IS_TMR_EVENT_SOURCE(SOURCE)        ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))
/**
  * @}
  */

/** @defgroup TMR_Update_Source 
  * @{
  */
#define TMR_UpdateSource_Global            ((uint16_t)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
#define TMR_UpdateSource_Regular           ((uint16_t)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_TMR_UPDATE_SOURCE(SOURCE)       (((SOURCE) == TMR_UpdateSource_Global) || \
                                            ((SOURCE) == TMR_UpdateSource_Regular))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_Preload_State 
  * @{
  */
#define TMR_OCPreload_Enable               ((uint16_t)0x0008)
#define TMR_OCPreload_Disable              ((uint16_t)0x0000)
#define IS_TMR_OCPRELOAD_STATE(STATE)      (((STATE) == TMR_OCPreload_Enable) || \
                                            ((STATE) == TMR_OCPreload_Disable))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_Fast_State 
  * @{
  */
#define TMR_OCFast_Enable                  ((uint16_t)0x0004)
#define TMR_OCFast_Disable                 ((uint16_t)0x0000)
#define IS_TMR_OCFAST_STATE(STATE)         (((STATE) == TMR_OCFast_Enable) || \
                                            ((STATE) == TMR_OCFast_Disable))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_Clear_State 
  * @{
  */
#define TMR_OCClear_Enable                 ((uint16_t)0x0080)
#define TMR_OCClear_Disable                ((uint16_t)0x0000)
#define IS_TMR_OCCLEAR_STATE(STATE)        (((STATE) == TMR_OCClear_Enable) || \
                                            ((STATE) == TMR_OCClear_Disable))
/**
  * @}
  */

/** @defgroup TMR_Trigger_Output_Source 
  * @{
  */
#define TMR_TRGOSource_Reset               ((uint16_t)0x0000)
#define TMR_TRGOSource_Enable              ((uint16_t)0x0010)
#define TMR_TRGOSource_Update              ((uint16_t)0x0020)
#define TMR_TRGOSource_OC1                 ((uint16_t)0x0030)
#define TMR_TRGOSource_OC1Ref              ((uint16_t)0x0040)
#define TMR_TRGOSource_OC2Ref              ((uint16_t)0x0050)
#define TMR_TRGOSource_OC3Ref              ((uint16_t)0x0060)
#define TMR_TRGOSource_OC4Ref              ((uint16_t)0x0070)
#define IS_TMR_TRGO_SOURCE(SOURCE)         (((SOURCE) == TMR_TRGOSource_Reset)  || \
                                            ((SOURCE) == TMR_TRGOSource_Enable) || \
                                            ((SOURCE) == TMR_TRGOSource_Update) || \
                                            ((SOURCE) == TMR_TRGOSource_OC1)    || \
                                            ((SOURCE) == TMR_TRGOSource_OC1Ref) || \
                                            ((SOURCE) == TMR_TRGOSource_OC2Ref) || \
                                            ((SOURCE) == TMR_TRGOSource_OC3Ref) || \
                                            ((SOURCE) == TMR_TRGOSource_OC4Ref))
/**
  * @}
  */

/** @defgroup TMR_Slave_Mode 
  * @{
  */
#define TMR_SlaveMode_Reset                ((uint16_t)0x0004)
#define TMR_SlaveMode_Gated                ((uint16_t)0x0005)
#define TMR_SlaveMode_Trigger              ((uint16_t)0x0006)
#define TMR_SlaveMode_External1            ((uint16_t)0x0007)
#define IS_TMR_SLAVE_MODE(MODE)            (((MODE) == TMR_SlaveMode_Reset)   || \
                                            ((MODE) == TMR_SlaveMode_Gated)   || \
                                            ((MODE) == TMR_SlaveMode_Trigger) || \
                                            ((MODE) == TMR_SlaveMode_External1))
/**
  * @}
  */

/** @defgroup TMR_Master_Slave_Mode 
  * @{
  */
#define TMR_MasterSlaveMode_Enable         ((uint16_t)0x0080)
#define TMR_MasterSlaveMode_Disable        ((uint16_t)0x0000)
#define IS_TMR_MSM_STATE(STATE)            (((STATE) == TMR_MasterSlaveMode_Enable) || \
                                            ((STATE) == TMR_MasterSlaveMode_Disable))
/**
  * @}
  */

/** @defgroup TMR_Flags 
  * @{
  */
#define TMR_FLAG_Update                    ((uint16_t)0x0001)
#define TMR_FLAG_CC1                       ((uint16_t)0x0002)
#define TMR_FLAG_CC2                       ((uint16_t)0x0004)
#define TMR_FLAG_CC3                       ((uint16_t)0x0008)
#define TMR_FLAG_CC4                       ((uint16_t)0x0010)
#define TMR_FLAG_COM                       ((uint16_t)0x0020)
#define TMR_FLAG_Trigger                   ((uint16_t)0x0040)
#define TMR_FLAG_Break                     ((uint16_t)0x0080)
#define TMR_FLAG_CC1OF                     ((uint16_t)0x0200)
#define TMR_FLAG_CC2OF                     ((uint16_t)0x0400)
#define TMR_FLAG_CC3OF                     ((uint16_t)0x0800)
#define TMR_FLAG_CC4OF                     ((uint16_t)0x1000)
#define IS_TMR_GET_FLAG(FLAG)              (((FLAG) == TMR_FLAG_Update)  || \
                                            ((FLAG) == TMR_FLAG_CC1)     || \
                                            ((FLAG) == TMR_FLAG_CC2)     || \
                                            ((FLAG) == TMR_FLAG_CC3)     || \
                                            ((FLAG) == TMR_FLAG_CC4)     || \
                                            ((FLAG) == TMR_FLAG_COM)     || \
                                            ((FLAG) == TMR_FLAG_Trigger) || \
                                            ((FLAG) == TMR_FLAG_Break)   || \
                                            ((FLAG) == TMR_FLAG_CC1OF)   || \
                                            ((FLAG) == TMR_FLAG_CC2OF)   || \
                                            ((FLAG) == TMR_FLAG_CC3OF)   || \
                                            ((FLAG) == TMR_FLAG_CC4OF))
#define IS_TMR_CLEAR_FLAG(TMR_FLAG)        ((((TMR_FLAG) & (uint16_t)0xE100) == 0x0000) && ((TMR_FLAG) != 0x0000))
/**
  * @}
  */

/** @defgroup TMR_Input_Capture_Filer_Value 
  * @{
  */
#define IS_TMR_IC_FILTER(ICFILTER)         ((ICFILTER) <= 0xF)
/**
  * @}
  */

/** @defgroup TMR_External_Trigger_Filter 
  * @{
  */
#define IS_TMR_EXT_FILTER(EXTFILTER)       ((EXTFILTER) <= 0xF)
/**
  * @}
  */

/** @defgroup TMR_Legacy 
  * @{
  */
#define TMR_DMABurstLength_1Byte           TMR_DMABurstLength_1Transfer
#define TMR_DMABurstLength_2Bytes          TMR_DMABurstLength_2Transfers
#define TMR_DMABurstLength_3Bytes          TMR_DMABurstLength_3Transfers
#define TMR_DMABurstLength_4Bytes          TMR_DMABurstLength_4Transfers
#define TMR_DMABurstLength_5Bytes          TMR_DMABurstLength_5Transfers
#define TMR_DMABurstLength_6Bytes          TMR_DMABurstLength_6Transfers
#define TMR_DMABurstLength_7Bytes          TMR_DMABurstLength_7Transfers
#define TMR_DMABurstLength_8Bytes          TMR_DMABurstLength_8Transfers
#define TMR_DMABurstLength_9Bytes          TMR_DMABurstLength_9Transfers
#define TMR_DMABurstLength_10Bytes         TMR_DMABurstLength_10Transfers
#define TMR_DMABurstLength_11Bytes         TMR_DMABurstLength_11Transfers
#define TMR_DMABurstLength_12Bytes         TMR_DMABurstLength_12Transfers
#define TMR_DMABurstLength_13Bytes         TMR_DMABurstLength_13Transfers
#define TMR_DMABurstLength_14Bytes         TMR_DMABurstLength_14Transfers
#define TMR_DMABurstLength_15Bytes         TMR_DMABurstLength_15Transfers
#define TMR_DMABurstLength_16Bytes         TMR_DMABurstLength_16Transfers
#define TMR_DMABurstLength_17Bytes         TMR_DMABurstLength_17Transfers
#define TMR_DMABurstLength_18Bytes         TMR_DMABurstLength_18Transfers
/**
  * @}
  */
  
/**
  * @}
  */   

/** @defgroup TMR_Exported_Functions
  * @{
  */

/* Exported Functions ------------------------------------------------------- */

void TMR_DeInit(TMR_Type* TMRx);
void TMR_TimeBaseInit(TMR_Type* TMRx, TMR_TimeBaseInitType* TMR_TimeBaseInitStruct);
void TMR_TimeBaseStructInit(TMR_TimeBaseInitType* TMR_TimeBaseInitStruct);
void TMR_OCStructInit(TMR_OCInitType* TMR_OCInitStruct);
void TMR_ICStructInit(TMR_ICInitType* TMR_ICInitStruct);
void TMR_BDTRStructInit(TMR_BDTRInitType* TMR_BDTRInitStruct);
void TMR_PrescalerConfig(TMR_Type* TMRx, uint16_t Prescaler, uint16_t TMR_PSCReloadMode);
void TMR_OC1Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct);
void TMR_OC2Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct);
void TMR_OC3Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct);
void TMR_OC4Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct);
void TMR_ICInit(TMR_Type* TMRx, TMR_ICInitType* TMR_ICInitStruct);
void TMR_PWMIConfig(TMR_Type* TMRx, TMR_ICInitType* TMR_ICInitStruct);
void TMR_BDTRConfig(TMR_Type* TMRx, TMR_BDTRInitType *TMR_BDTRInitStruct);

void TMR_Cmd(TMR_Type* TMRx, FunctionalState NewState);
void TMR_CtrlPWMOutputs(TMR_Type* TMRx, FunctionalState NewState);
void TMR_ITConfig(TMR_Type* TMRx, uint16_t TMR_IT, FunctionalState NewState);
void TMR_GenerateEvent(TMR_Type* TMRx, uint16_t TMR_EventSource);
void TMR_DMAConfig(TMR_Type* TMRx, uint16_t TMR_DMABase, uint16_t TMR_DMABurstLength);
void TMR_DMACmd(TMR_Type* TMRx, uint16_t TMR_DMASource, FunctionalState NewState);
void TMR_InternalClockConfig(TMR_Type* TMRx);
void TMR_ITRxExternalClockConfig(TMR_Type* TMRx, uint16_t TMR_InputTriggerSource);
void TMR_TIxExternalClockConfig(TMR_Type* TMRx, uint16_t TMR_TIxExternalCLKSource, uint16_t TMR_ICPolarity, uint16_t ICFilter);
void TMR_ETRClockMode1Config(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TMR_ETRClockMode2Config(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TMR_ETRConfig(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TMR_PrescalerConfig(TMR_Type* TMRx, uint16_t Prescaler, uint16_t TMR_PSCReloadMode);
void TMR_CounterModeConfig(TMR_Type* TMRx, uint16_t TMR_CounterMode);
void TMR_SelectInputTrigger(TMR_Type* TMRx, uint16_t TMR_InputTriggerSource);
void TMR_EncoderInterfaceConfig(TMR_Type* TMRx, uint16_t TMR_EncoderMode, uint16_t TMR_IC1Polarity, uint16_t TMR_IC2Polarity);
void TMR_ForcedOC1Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction);
void TMR_ForcedOC2Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction);
void TMR_ForcedOC3Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction);
void TMR_ForcedOC4Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction);
void TMR_ARRPreloadConfig(TMR_Type* TMRx, FunctionalState NewState);
void TMR_SelectCOM(TMR_Type* TMRx, FunctionalState NewState);
void TMR_SelectCCDMA(TMR_Type* TMRx, FunctionalState NewState);
void TMR_CCPreloadControl(TMR_Type* TMRx, FunctionalState NewState);
void TMR_OC1PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload);
void TMR_OC2PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload);
void TMR_OC3PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload);
void TMR_OC4PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload);
void TMR_OC1FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast);
void TMR_OC2FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast);
void TMR_OC3FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast);
void TMR_OC4FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast);
void TMR_ClearOC1Ref(TMR_Type* TMRx, uint16_t TMR_OCClear);
void TMR_ClearOC2Ref(TMR_Type* TMRx, uint16_t TMR_OCClear);
void TMR_ClearOC3Ref(TMR_Type* TMRx, uint16_t TMR_OCClear);
void TMR_ClearOC4Ref(TMR_Type* TMRx, uint16_t TMR_OCClear);
void TMR_OC1PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity);
void TMR_OC1NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity);
void TMR_OC2PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity);
void TMR_OC2NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity);
void TMR_OC3PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity);
void TMR_OC3NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity);
void TMR_OC4PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity);
void TMR_CCxCmd(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_CCx);
void TMR_CCxNCmd(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_CCxN);
void TMR_SelectOCxM(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_OCMode);
void TMR_UpdateDisableConfig(TMR_Type* TMRx, FunctionalState NewState);
void TMR_UpdateRequestConfig(TMR_Type* TMRx, uint16_t TMR_UpdateSource);
void TMR_SelectHallSensor(TMR_Type* TMRx, FunctionalState NewState);
void TMR_SelectOnePulseMode(TMR_Type* TMRx, uint16_t TMR_OPMode);
void TMR_SelectOutputTrigger(TMR_Type* TMRx, uint16_t TMR_TRGOSource);
void TMR_SelectSlaveMode(TMR_Type* TMRx, uint16_t TMR_SlaveMode);
void TMR_SelectMasterSlaveMode(TMR_Type* TMRx, uint16_t TMR_MasterSlaveMode);
void TMR_SetCounter(TMR_Type* TMRx, uint16_t Counter);
void TMR_SetAutoreload(TMR_Type* TMRx, uint16_t Autoreload);
void TMR_SetCompare1(TMR_Type* TMRx, uint16_t Compare1);
void TMR_SetCompare2(TMR_Type* TMRx, uint16_t Compare2);
void TMR_SetCompare3(TMR_Type* TMRx, uint16_t Compare3);
void TMR_SetCompare4(TMR_Type* TMRx, uint16_t Compare4);
void TMR_SetIC1Prescaler(TMR_Type* TMRx, uint16_t TMR_ICPSC);
void TMR_SetIC2Prescaler(TMR_Type* TMRx, uint16_t TMR_ICPSC);
void TMR_SetIC3Prescaler(TMR_Type* TMRx, uint16_t TMR_ICPSC);
void TMR_SetIC4Prescaler(TMR_Type* TMRx, uint16_t TMR_ICPSC);
void TMR_SetClockDivision(TMR_Type* TMRx, uint16_t TMR_CKD);
uint16_t TMR_GetCapture1(TMR_Type* TMRx);
uint16_t TMR_GetCapture2(TMR_Type* TMRx);
uint16_t TMR_GetCapture3(TMR_Type* TMRx);
uint16_t TMR_GetCapture4(TMR_Type* TMRx);
uint16_t TMR_GetCounter(TMR_Type* TMRx);
uint16_t TMR_GetPrescaler(TMR_Type* TMRx);
FlagStatus TMR_GetFlagStatus(TMR_Type* TMRx, uint16_t TMR_FLAG);
void TMR_ClearFlag(TMR_Type* TMRx, uint16_t TMR_FLAG);
ITStatus TMR_GetITStatus(TMR_Type* TMRx, uint16_t TMR_IT);
void TMR_ClearITPendingBit(TMR_Type* TMRx, uint16_t TMR_IT);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */




#endif  /* __LIB_TIMER_H */
