
/**
  ******************************************************************************
  * @file    lib_dac.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-11-11
  * @brief   This file contains all the functions prototypes for the DAC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_DAC_H
#define __LIB_DAC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */
  
/** @addtogroup DAC
  * @{
  */
  
/** @defgroup DAC_Exported_Constants
  * @{
  */
  
/** DAC_trigger_selection   */
#define DAC_TRIGGER_NONE                             ((uint32_t)0x00000000) /*!< Conversion is automatic once the DAC1_DHRxxxx register 
                                                                       has been loaded, and not by external trigger */
#define DAC_TRIGGER_T1_TRGO                          ((uint32_t)0x00000014) /*!< TIM1 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T2_TRGO                          ((uint32_t)0x0000000C) /*!< TIM2 TRGO selected as external conversion trigger for DAC channel*/
#define DAC_TRIGGER_T3_TRGO                          ((uint32_t)0x00000024) /*!< TIM3 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T4_TRGO                          ((uint32_t)0x00000004) /*!< TIM4 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T5_TRGO                          ((uint32_t)0x0000002C) /*!< TIM5 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T6_TRGO                          ((uint32_t)0x0000001C) /*!< TIM6 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_EXT_IT9                          ((uint32_t)0x00000034) /*!< EXTI Line9 event selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_SOFTWARE                         ((uint32_t)0x0000003C) /*!< Conversion started by software trigger for DAC channel */
#define IS_DAC_TRIGGER(TRIGGER)                      (((TRIGGER) == DAC_TRIGGER_NONE)    || \
                                                      ((TRIGGER) == DAC_TRIGGER_T1_TRGO) || \
                                                      ((TRIGGER) == DAC_TRIGGER_T2_TRGO) || \
                                                      ((TRIGGER) == DAC_TRIGGER_T3_TRGO) || \
                                                      ((TRIGGER) == DAC_TRIGGER_T4_TRGO) || \
                                                      ((TRIGGER) == DAC_TRIGGER_T5_TRGO) || \
                                                      ((TRIGGER) == DAC_TRIGGER_T6_TRGO) || \
                                                      ((TRIGGER) == DAC_TRIGGER_EXT_IT9) || \
                                                      ((TRIGGER) == DAC_TRIGGER_SOFTWARE))

/* DAC_wave_generation  */
#define DAC_WAVE_GENERATION_NONE                      ((uint32_t)0x00000000)
#define DAC_WAVE_GENERATION_NOISE                     ((uint32_t)0x00000040)
#define DAC_WAVE_GENERATION_TRIANGLE                  ((uint32_t)0x00000080)

#define IS_DAC_GENERATE_WAVE(WAVE)                    (((WAVE) == DAC_WAVE_GENERATION_NONE)  || \
                                                       ((WAVE) == DAC_WAVE_GENERATION_NOISE) || \
                                                       ((WAVE) == DAC_WAVE_GENERATION_TRIANGLE))

/** DAC_lfsrunmask_triangleamplitude */
#define DAC_LFSR_UNMASK_BIT0                          ((uint32_t)0x00000000) /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_1_0                      ((uint32_t)0x00000100) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_2_0                      ((uint32_t)0x00000200) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_3_0                      ((uint32_t)0x00000300) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_4_0                      ((uint32_t)0x00000400) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_5_0                      ((uint32_t)0x00000500) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_6_0                      ((uint32_t)0x00000600) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_7_0                      ((uint32_t)0x00000700) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_8_0                      ((uint32_t)0x00000800) /*!< Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_9_0                      ((uint32_t)0x00000900) /*!< Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_10_0                     ((uint32_t)0x00000A00) /*!< Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BITS_11_0                     ((uint32_t)0x00000B00) /*!< Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_TRIANGLE_AMPLITUDE_1                      ((uint32_t)0x00000000) /*!< Select max triangle amplitude of 1 */
#define DAC_TRIANGLE_AMPLITUDE_3                      ((uint32_t)0x00000100) /*!< Select max triangle amplitude of 3 */
#define DAC_TRIANGLE_AMPLITUDE_7                      ((uint32_t)0x00000200) /*!< Select max triangle amplitude of 7 */
#define DAC_TRIANGLE_AMPLITUDE_15                     ((uint32_t)0x00000300) /*!< Select max triangle amplitude of 15 */
#define DAC_TRIANGLE_AMPLITUDE_31                     ((uint32_t)0x00000400) /*!< Select max triangle amplitude of 31 */
#define DAC_TRIANGLE_AMPLITUDE_63                     ((uint32_t)0x00000500) /*!< Select max triangle amplitude of 63 */
#define DAC_TRIANGLE_AMPLITUDE_127                    ((uint32_t)0x00000600) /*!< Select max triangle amplitude of 127 */
#define DAC_TRIANGLE_AMPLITUDE_255                    ((uint32_t)0x00000700) /*!< Select max triangle amplitude of 255 */
#define DAC_TRIANGLE_AMPLITUDE_511                    ((uint32_t)0x00000800) /*!< Select max triangle amplitude of 511 */
#define DAC_TRIANGLE_AMPLITUDE_1023                   ((uint32_t)0x00000900) /*!< Select max triangle amplitude of 1023 */
#define DAC_TRIANGLE_AMPLITUDE_2047                   ((uint32_t)0x00000A00) /*!< Select max triangle amplitude of 2047 */
#define DAC_TRIANGLE_AMPLITUDE_4095                   ((uint32_t)0x00000B00) /*!< Select max triangle amplitude of 4095 */
#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE)  (((VALUE) == DAC_LFSR_UNMASK_BIT0)        || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_1_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_2_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_3_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_4_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_5_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_6_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_7_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_8_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_9_0)    || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_10_0)   || \
                                                       ((VALUE) == DAC_LFSR_UNMASK_BITS_11_0)   || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_1)    || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_3)    || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_7)    || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_15)   || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_31)   || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_63)   || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_127)  || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_255)  || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_511)  || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_1023) || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_2047) || \
                                                       ((VALUE) == DAC_TRIANGLE_AMPLITUDE_4095))

/** DAC_output_buffer */
#define DAC_OUTPUT_BUFFER_ENABLE                      ((uint32_t)0x00000000)
#define DAC_OUTPUT_BUFFER_DISABLE                     ((uint32_t)0x00000002)
#define IS_DAC_OUTPUT_BUFFER_STATE(STATE)            (((STATE) == DAC_OUTPUT_BUFFER_ENABLE) || \
                                                      ((STATE) == DAC_OUTPUT_BUFFER_DISABLE))

/* DAC_CHANNEL_selection */
#define DAC_CHANNEL_0                                ((uint32_t)0x00000000)
#define DAC_CHANNEL_1                                ((uint32_t)0x00000010)
#define IS_DAC_CHANNEL(CHANNEL)                      (((CHANNEL) == DAC_CHANNEL_0) || \
                                                      ((CHANNEL) == DAC_CHANNEL_1))

/* DAC_data_alignment */
#define DAC_ALIGN_12B_R                              ((uint32_t)0x00000000)
#define DAC_ALIGN_12B_L                              ((uint32_t)0x00000004)
#define DAC_ALIGN_8B_R                               ((uint32_t)0x00000008)
#define IS_DAC_ALIGN(ALIGN)                          (((ALIGN) == DAC_ALIGN_12B_R) || \
                                                      ((ALIGN) == DAC_ALIGN_12B_L) || \
                                                      ((ALIGN) == DAC_ALIGN_8B_R))

/* DAC_wave_generation */
#define DAC_WAVE_NOISE                               ((uint32_t)0x00000040)
#define DAC_WAVE_TRIANGLE                            ((uint32_t)0x00000080)
#define IS_DAC_WAVE(WAVE)                            (((WAVE) == DAC_WAVE_NOISE) || \
                                                      ((WAVE) == DAC_WAVE_TRIANGLE))

/*  DAC_data   */
#define IS_DAC_DATA(DATA)                            ((DATA) <= 0xFFF0) 

/**
  * @}
  */


/** @defgroup DAC_Exported_Types
  * @{
  */
  
/** 
  * @brief  DAC Init structure definition
  */

typedef struct
{
  uint32_t DAC_Trigger;                      /*!< Specifies the external trigger for the selected DAC channel.
                                                  This parameter can be a value of @ref DAC_trigger_selection */

  uint32_t DAC_WaveGeneration;               /*!< Specifies whether DAC channel noise waves or triangle waves
                                                  are generated, or whether no wave is generated.
                                                  This parameter can be a value of @ref DAC_wave_generation */

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; /*!< Specifies the LFSR mask for noise wave generation or
                                                  the maximum amplitude triangle generation for the DAC channel. 
                                                  This parameter can be a value of @ref DAC_lfsrunmask_triangleamplitude */

  uint32_t DAC_OutputBuffer;                 /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                                  This parameter can be a value of @ref DAC_output_buffer */
}DAC_InitType;

/**
  * @}
  */

/** @defgroup DAC_Exported_Functions
  * @{
  */

void DAC_DeInit(void);
void DAC_Init(uint32_t DAC_Channel, DAC_InitType* DAC_InitStruct);
void DAC_StructInit(DAC_InitType* DAC_InitStruct);

void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);

void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);

void DAC_SetChannel0Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data1, uint16_t Data0);
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);

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

#endif  /*__LIB_DAC_H */

/*********************************** END OF FILE ******************************/


