
/**
  ******************************************************************************
  * @file    lib_bpwm.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-07-06
  * @brief   This file contains all the functions prototypes for the BPWM firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_BPWM_H
#define __LIB_BPWM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup BPWM
  * @{
  */ 

/** @defgroup BPWM_Exported_Types
  * @{
  */ 
  
/** 
  * @brief  BPWM Time Base Init structure definition
  */
typedef struct
{
  uint32_t ClockDivision;  /*!< Specifies the clock division.
                                This parameter can be a value of @ref BPWM_Clock_Division */
  uint32_t Mode;           /*!< Specifies the counter mode.
                                This parameter can be a value of @ref BPWM_Counter_Mode */
  uint32_t ClockSource;    /*!< Specifies the Clock source.
                                This parameter can be a value of @ref BPWM_Clock_Source */
} BPWM_BaseInitType;

/** 
  * @brief  BPWM Output Compare Init structure definition  
  */
typedef struct
{
  uint32_t Channel;       /*!< Specifies the BPWM channel.
                               This parameter can be a value of @ref BPWM_Channel */
  uint32_t Period;        /*!< Specifies the value to be loaded into the Compare capture data register. 
                               This parameter can be a number between 0x0000 and 0xFFFF */
  uint32_t OutMode;       /*!< Specifies the Output mode.
                               This parameter can be a value of @ref BPWM_Output_mode */
} BPWM_OCInitType;

/** 
  * @brief  BPWM Input Capture Init structure definition  
  */
typedef struct
{
  uint32_t Channel;       /*!< Specifies the BPWM channel.
                               This parameter can be a value of @ref BPWM_Channel */
  uint32_t CaptureMode;   /*!< Specifies the Capture edge.
                               This parameter can be a value of @ref BPWM_Capture_Edge */
} BPWM_ICInitType;

/**
  * @}
  */ 

/** @defgroup BPWM_Exported_constants 
  * @{
  */
  
#if defined (V32F20XXX_CM0_CORE)
/* CM0 BPWM Instances */
#define IS_BPWM_ALL_INSTANCE(INSTANCE)  (((INSTANCE) == BPWM4) ||\
                                         ((INSTANCE) == BPWM5) ||\
                                         ((INSTANCE) == BPWM6) ||\
                                         ((INSTANCE) == BPWM7))
/* CM0 BPWM SEL Instances */
#define IS_BPWM_SEL_INSTANCE(INSTANCE)  ((INSTANCE) == BPWM4_7_SEL)
#endif 

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
/* CM33 BPWM Instances */
#define IS_BPWM_ALL_INSTANCE(INSTANCE)  (((INSTANCE) == BPWM0) ||\
                                         ((INSTANCE) == BPWM1) ||\
                                         ((INSTANCE) == BPWM2) ||\
                                         ((INSTANCE) == BPWM3) ||\
                                         ((INSTANCE) == BPWM4) ||\
                                         ((INSTANCE) == BPWM5) ||\
                                         ((INSTANCE) == BPWM6) ||\
                                         ((INSTANCE) == BPWM7))
/* CM33 BPWM SEL Instances */
#define IS_BPWM_SEL_INSTANCE(INSTANCE)  ((INSTANCE) == BPWM0_3_SEL||(INSTANCE) == BPWM4_7_SEL)
#endif /* _USE_CM33 */

/** @defgroup BPWM_Clock_Division
  * @{
  */
#define BPWM_CLKDIV_2                   ((uint32_t)0x00000000)  
#define BPWM_CLKDIV_4                   ((uint32_t)0x00000040)  
#define BPWM_CLKDIV_8                   ((uint32_t)0x00000080)  
#define BPWM_CLKDIV_16                  ((uint32_t)0x000000C0)  

#define IS_BPWM_CLKDIV(CLKDIV)          (((CLKDIV) == BPWM_CLKDIV_2) ||\
                                        ((CLKDIV) == BPWM_CLKDIV_4) ||\
                                        ((CLKDIV) == BPWM_CLKDIV_8) ||\
                                        ((CLKDIV) == BPWM_CLKDIV_16))
/**
  * @}
  */
  
/** @defgroup BPWM_Counter_Mode 
  * @{
  */
#define BPWM_MODE_STOP                  ((uint32_t)0x00000000)  
#define BPWM_MODE_UPCOUNT               ((uint32_t)0x00000010)  
#define BPWM_MODE_CONTINUOUS            ((uint32_t)0x00000020)  
#define BPWM_MODE_UPDOWN                ((uint32_t)0x00000030)  
#define IS_BPWM_CNTMODE(CNTMODE)        (((CNTMODE) == BPWM_MODE_STOP)       ||\
                                         ((CNTMODE) == BPWM_MODE_UPCOUNT)    ||\
                                         ((CNTMODE) == BPWM_MODE_CONTINUOUS) ||\
                                         ((CNTMODE) == BPWM_MODE_UPDOWN))
/**
  * @}
  */
  
/** @defgroup BPWM_Clock_Source 
  * @{
  */
#define BPWM_CLKSRC_APB                 ((uint32_t)0x00000008) 
#define BPWM_CLKSRC_APBD128             ((uint32_t)0x00000000) 
#define IS_BPWM_CLKSRC(CLKSRC)          (((CLKSRC) == BPWM_CLKSRC_APB) ||\
                                         ((CLKSRC) == BPWM_CLKSRC_APBD128))
/**
  * @}
  */

/** @defgroup BPWM_Channel 
  * @{
  */
#define BPWM_CHANNEL_0                  ((uint8_t)0x00) 
#define BPWM_CHANNEL_1                  ((uint8_t)0x01) 
#define BPWM_CHANNEL_2                  ((uint8_t)0x02) 
#define IS_BPWM_CHANNEL(CHANNEL)        (((CHANNEL) == BPWM_CHANNEL_0) ||\
                                         ((CHANNEL) == BPWM_CHANNEL_1) ||\
                                         ((CHANNEL) == BPWM_CHANNEL_2))
/**
  * @}
  */

/** @defgroup BPWM_Output_mode 
  * @{
  */
#define BPWM_OUTMOD_CONST               ((uint32_t)0x00000000)
#define BPWM_OUTMOD_SET                 ((uint32_t)0x00000020)
#define BPWM_OUTMOD_TOGGLE_RESET        ((uint32_t)0x00000040)
#define BPWM_OUTMOD_SET_RESET           ((uint32_t)0x00000060)
#define BPWM_OUTMOD_TOGGLE              ((uint32_t)0x00000080)
#define BPWM_OUTMOD_RESET               ((uint32_t)0x000000A0)
#define BPWM_OUTMOD_TOGGLE_SET          ((uint32_t)0x000000C0)
#define BPWM_OUTMOD_RESET_SET           ((uint32_t)0x000000E0)

#define IS_BPWM_OUTMODE(OUTMODE)        (((OUTMODE) == BPWM_OUTMOD_CONST)        ||\
                                         ((OUTMODE) == BPWM_OUTMOD_SET)          ||\
                                         ((OUTMODE) == BPWM_OUTMOD_TOGGLE_RESET) ||\
                                         ((OUTMODE) == BPWM_OUTMOD_SET_RESET)    ||\
                                         ((OUTMODE) == BPWM_OUTMOD_TOGGLE)       ||\
                                         ((OUTMODE) == BPWM_OUTMOD_RESET)        ||\
                                         ((OUTMODE) == BPWM_OUTMOD_TOGGLE_SET)   ||\
                                         ((OUTMODE) == BPWM_OUTMOD_RESET_SET))
/**
  * @}
  */										

/** @defgroup BPWM_Capture_Edge 
  * @{
  */
#define BPWM_CM_DISABLE                 ((uint32_t)0x00000000)
#define BPWM_CM_RISING                  ((uint32_t)0x00004000)
#define BPWM_CM_FALLING                 ((uint32_t)0x00008000)
#define BPWM_CM_BOTH                    ((uint32_t)0x0000C000)
#define IS_BPWM_CAPMODE(CAPMODE)        (((CAPMODE) == BPWM_CM_DISABLE) ||\
                                         ((CAPMODE) == BPWM_CM_RISING)  ||\
                                         ((CAPMODE) == BPWM_CM_FALLING) ||\
                                         ((CAPMODE) == BPWM_CM_BOTH))
/**
  * @}
  */	
  
#define IS_BPWM_CCR(CCR)                ((CCR) < 0x10000U)

/** @defgroup BPWM_interrupt_sources 
  * @{
  */
#define BPWM_INT_CCIFG                  ((uint32_t)0x00000001)
#define BPWM_INT_COV                    ((uint32_t)0x00000002)
#define BPWM_INT_MASK                   (BPWM_INT_CCIFG | BPWM_INT_COV)

#define IS_BPWM_CH_INTR(INT)            (((INT) == BPWM_INT_CCIFG) ||\
                                         ((INT) == BPWM_INT_COV))
#define IS_BPWM_CH_INTC(INT)            ((((INT) & BPWM_INT_MASK) != 0U) &&\
                                         (((INT) & ~BPWM_INT_MASK) == 0U))
/**
  * @}
  */	
  										
/** @defgroup BPWM_output_selection
  * @{
  */
#define BPWM0_OUT0                      ((uint32_t)0x00000000)
#define BPWM0_OUT1                      ((uint32_t)0x00000001)
#define BPWM0_OUT2                      ((uint32_t)0x00000002)
#define BPWM1_OUT0                      ((uint32_t)0x00000004)
#define BPWM1_OUT1                      ((uint32_t)0x00000005)
#define BPWM1_OUT2                      ((uint32_t)0x00000006)
#define BPWM2_OUT0                      ((uint32_t)0x00000008)
#define BPWM2_OUT1                      ((uint32_t)0x00000009)
#define BPWM2_OUT2                      ((uint32_t)0x0000000A)
#define BPWM3_OUT0                      ((uint32_t)0x0000000C)
#define BPWM3_OUT1                      ((uint32_t)0x0000000D)
#define BPWM3_OUT2                      ((uint32_t)0x0000000E)
#define BPWM4_OUT0                      BPWM0_OUT0
#define BPWM4_OUT1                      BPWM0_OUT1
#define BPWM4_OUT2                      BPWM0_OUT2
#define BPWM5_OUT0                      BPWM1_OUT0
#define BPWM5_OUT1                      BPWM1_OUT1
#define BPWM5_OUT2                      BPWM1_OUT2
#define BPWM6_OUT0                      BPWM2_OUT0
#define BPWM6_OUT1                      BPWM2_OUT1
#define BPWM6_OUT2                      BPWM2_OUT2
#define BPWM7_OUT0                      BPWM3_OUT0
#define BPWM7_OUT1                      BPWM3_OUT1
#define BPWM7_OUT2                      BPWM3_OUT2

#define IS_BPWM_OUTSEL(OUTSEL)          (((OUTSEL) == BPWM0_OUT0) ||\
                                         ((OUTSEL) == BPWM0_OUT1) ||\
                                         ((OUTSEL) == BPWM0_OUT2) ||\
                                         ((OUTSEL) == BPWM1_OUT0) ||\
                                         ((OUTSEL) == BPWM1_OUT1) ||\
                                         ((OUTSEL) == BPWM1_OUT2) ||\
                                         ((OUTSEL) == BPWM2_OUT0) ||\
                                         ((OUTSEL) == BPWM2_OUT1) ||\
                                         ((OUTSEL) == BPWM2_OUT2) ||\
                                         ((OUTSEL) == BPWM3_OUT0) ||\
                                         ((OUTSEL) == BPWM3_OUT1) ||\
                                         ((OUTSEL) == BPWM3_OUT2))
/**
  * @}
  */									

/** @defgroup BPWM_output_line
  * @{
  */
#define BPWM_OLINE_0                    ((uint32_t)0x00000001)
#define BPWM_OLINE_1                    ((uint32_t)0x00000002)
#define BPWM_OLINE_2                    ((uint32_t)0x00000004)
#define BPWM_OLINE_3                    ((uint32_t)0x00000008)
#define BPWM_OLINE_MASK                 ((uint32_t)0x0000000F)

#define IS_BPWM_OUTLINE(OUTLINE)        ((((OUTLINE) & BPWM_OLINE_MASK) != 0U) &&\
                                         (((OUTLINE) & ~BPWM_OLINE_MASK) == 0U))
/**
  * @}
  */											

/** @defgroup BPWM_output_level
  * @{
  */
#define BPWM_LEVEL_HIGH                 ((uint32_t)0x00000004)
#define BPWM_LEVEL_LOW                  ((uint32_t)0x00000000)
#define IS_BPWM_OUTLVL(OUTLVL)          (((OUTLVL) == BPWM_LEVEL_HIGH) ||\
                                        ((OUTLVL) == BPWM_LEVEL_LOW))
/**
  * @}
  */									

/** @defgroup BPWM_input_selection
  * @{
  */
#define BPWM1_IN2                       ((uint32_t)0x00000014)
#define BPWM1_IN1                       ((uint32_t)0x00000012)
#define BPWM1_IN0                       ((uint32_t)0x00000010)
#define BPWM0_IN2                       ((uint32_t)0x00000004)
#define BPWM0_IN1                       ((uint32_t)0x00000002)
#define BPWM0_IN0                       ((uint32_t)0x00000000)
#define BPWM3_IN2                       ((uint32_t)0x00000114)
#define BPWM3_IN1                       ((uint32_t)0x00000112)
#define BPWM3_IN0                       ((uint32_t)0x00000110)
#define BPWM2_IN2                       ((uint32_t)0x00000104)
#define BPWM2_IN1                       ((uint32_t)0x00000102)
#define BPWM2_IN0                       ((uint32_t)0x00000100)
#define BPWM5_IN2                       BPWM1_IN2
#define BPWM5_IN1                       BPWM1_IN1
#define BPWM5_IN0                       BPWM1_IN0
#define BPWM4_IN2                       BPWM0_IN2
#define BPWM4_IN1                       BPWM0_IN1
#define BPWM4_IN0                       BPWM0_IN0
#define BPWM7_IN2                       BPWM3_IN2
#define BPWM7_IN1                       BPWM3_IN1
#define BPWM7_IN0                       BPWM3_IN0
#define BPWM6_IN2                       BPWM2_IN2
#define BPWM6_IN1                       BPWM2_IN1
#define BPWM6_IN0                       BPWM2_IN0
#define IS_BPWM_INSEL(INSEL)            (((INSEL) == BPWM1_IN2) ||\
                                         ((INSEL) == BPWM1_IN1) ||\
                                         ((INSEL) == BPWM1_IN0) ||\
                                         ((INSEL) == BPWM0_IN2) ||\
                                         ((INSEL) == BPWM0_IN1) ||\
                                         ((INSEL) == BPWM0_IN0) ||\
                                         ((INSEL) == BPWM3_IN2) ||\
                                         ((INSEL) == BPWM3_IN1) ||\
                                         ((INSEL) == BPWM3_IN0) ||\
                                         ((INSEL) == BPWM2_IN2) ||\
                                         ((INSEL) == BPWM2_IN1) ||\
                                         ((INSEL) == BPWM2_IN0))
/**
  * @}
  */										

/** @defgroup BPWM_input_Line
  * @{
  */
#define BPWM_ILINE_0                    ((uint32_t)0x00000000)
#define BPWM_ILINE_1                    ((uint32_t)0x00000001)
#define BPWM_ILINE_2                    ((uint32_t)0x00000002)
#define BPWM_ILINE_3                    ((uint32_t)0x00000003)
#define IS_BPWM_INLINE(INLINE)          (((INLINE) == BPWM_ILINE_0) ||\
                                         ((INLINE) == BPWM_ILINE_1) ||\
                                         ((INLINE) == BPWM_ILINE_2) ||\
                                         ((INLINE) == BPWM_ILINE_3))
/**
  * @}
  */ 
  
#define  BPWM_OUTPUT_OFF                ((uint32_t)0x0000000b)  
  
/**
  * @}
  */ 

/** @defgroup BPWM_Exported_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup BPWM_Exported_Functions
  * @{
  */

void BPWM_DeInit(BPWM_Type *BPWMx);
void BPWM_BaseStructInit(BPWM_BaseInitType *BPWM_BaseInitStruct);
void BPWM_BaseInit(BPWM_Type *BPWMx, BPWM_BaseInitType *BPWM_BaseInitStruct);
void BPWM_OCStructInit(BPWM_OCInitType *BPWM_OCInitType);
void BPWM_OCInit(BPWM_Type *BPWMx, BPWM_OCInitType *BPWM_OCInitType);
void BPWM_ICStructInit(BPWM_ICInitType *BPWM_ICInitType);
void BPWM_ICInit(BPWM_Type *BPWMx, BPWM_ICInitType *BPWM_ICInitType);
void BPWM_BaseINTConfig(BPWM_Type *BPWMx, FunctionalState NewState);
ITStatus BPWM_GetBaseINTStatus(BPWM_Type *BPWMx);
void BPWM_ClearBaseINTStatus(BPWM_Type *BPWMx);
void BPWM_ChannelINTConfig(BPWM_Type *BPWMx, uint32_t Channel, FunctionalState NewState);
ITStatus BPWM_GetChannelINTStatus(BPWM_Type *BPWMx, uint32_t Channel, uint32_t IntMask);
void BPWM_ClearChannelINTStatus(BPWM_Type *BPWMx, uint32_t Channel, uint32_t IntMask);
void BPWM_ClearCounter(BPWM_Type *BPWMx);
void BPWM_CCRConfig(BPWM_Type *BPWMx, uint32_t Channel, uint16_t Period);
void BPWM_OLineConfig(BPWM_SEL_Type *BPWMx_SEL, uint32_t OLine, uint32_t OutSelection);
void BPWM_OutputCmd(BPWM_Type *BPWMx, uint32_t Channel, FunctionalState NewState);
void BPWM_SetOutLevel(BPWM_Type *BPWMx, uint32_t Channel, uint32_t Level);
void BPWM_OC0Init(BPWM_Type *BPWMx, BPWM_OCInitType *OCInitType);
void BPWM_OC1Init(BPWM_Type *BPWMx, BPWM_OCInitType *OCInitType);
void BPWM_OC2Init(BPWM_Type *BPWMx, BPWM_OCInitType *OCInitType);
void BPWM_IC0Init(BPWM_Type *BPWMx, uint32_t CaptureMode);
void BPWM_IC1Init(BPWM_Type *BPWMx, uint32_t CaptureMode);
void BPWM_IC2Init(BPWM_Type *BPWMx, uint32_t CaptureMode);
void BPWM_ILineConfig(BPWM_SEL_Type *BPWMx_SEL, uint32_t ILine, uint32_t InSelection);
uint8_t BPWM_GetSCCI(BPWM_Type *BPWMx, uint32_t Channel);
uint32_t BPWM_GetCapture(BPWM_Type *BPWMx, uint32_t Channel);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_BPWM_H */
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
