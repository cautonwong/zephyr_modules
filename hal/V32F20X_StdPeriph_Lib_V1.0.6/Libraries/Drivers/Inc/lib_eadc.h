
/**
  ******************************************************************************
  * @file    lib_eadc.c 
  * @author  VT Application Team
  * @version V1.0.0
  * @date    2021-11-2
  * @brief   This file contains all the functions prototypes for the EADC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_EADC_H
#define __LIB_EADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */
  
/** @addtogroup EADC
  * @{
  */

/** @defgroup EADC_Exported_Constants
  * @{
  */

#define EADC_CHANNEL_0                     ((uint32_t)0x00000001) 
#define EADC_CHANNEL_1                     ((uint32_t)0x00000002) 
#define EADC_CHANNEL_2                     ((uint32_t)0x00000004)
#define EADC_CHANNEL_3                     ((uint32_t)0x00000008)
#define EADC_CHANNEL_4                     ((uint32_t)0x00000010) 
#define EADC_CHANNEL_5                     ((uint32_t)0x00000020)
#define EADC_CHANNEL_6                     ((uint32_t)0x00000040) 
#define EADC_CHANNEL_7                     ((uint32_t)0x00000080)
#define IS_EADC_CHANNEL(CHANNEL)           (((CHANNEL) == EADC_CHANNEL_0) || \
                                            ((CHANNEL) == EADC_CHANNEL_1) || \
                                            ((CHANNEL) == EADC_CHANNEL_2) || \
                                            ((CHANNEL) == EADC_CHANNEL_3) || \
                                            ((CHANNEL) == EADC_CHANNEL_4) || \
                                            ((CHANNEL) == EADC_CHANNEL_5) || \
                                            ((CHANNEL) == EADC_CHANNEL_6) || \
                                            ((CHANNEL) == EADC_CHANNEL_7))
                                            
                                            
#define IS_EADC_CHANNEL_ALL(CHANNEL)        ((0UL == (CHANNEL & (uint32_t)0xFFFFFF00)) &&\
                                             (0UL != (CHANNEL & (uint32_t)0x000000FF)))

#define EADC_CLK_OUT                      ((uint32_t)0x01000000)
#define EADC_CLK_IN                       ((uint32_t)0x00000000)

#define IS_EADC_CLK_MODE(Status)          (((Status) == EADC_CLK_OUT)  || \
                                           ((Status) == EADC_CLK_IN))
                                            
#define IS_EADC_SYN_FAIL_CHANNEL(CHANNEL)  (((CHANNEL) == EADC_CHANNEL_0) || \
                                            ((CHANNEL) == EADC_CHANNEL_1))
                                            

#define EADC_CP_TRIG_POS                   ((uint32_t)0x00000000) 
#define EADC_CP_TRIG_NEG                   ((uint32_t)0x00000001) 
#define IS_EADC_Trigger_Edge(EDGE)         (((EDGE) == EADC_CP_TRIG_POS) || \
                                            ((EDGE) == EADC_CP_TRIG_NEG) )  

#define EADC_INT_SYN_FAIL_CH0             ((uint32_t)0x00000010)
#define EADC_INT_SYN_FAIL_CH1             ((uint32_t)0x00000020)
#define EADC_INT_UDP                      ((uint32_t)0x00000040)
#define EADC_INT_OVF                      ((uint32_t)0x00000080)
#define IS_EADC_INT(INT)                  (((INT) == EADC_INT_SYN_FAIL_CH0) || \
                                           ((INT) == EADC_INT_SYN_FAIL_CH1) || \
                                           ((INT) == EADC_INT_UDP) || \
                                           ((INT) == EADC_INT_OVF))
                                        
#define EADC_STS_SYN_FAIL_CH0             ((uint32_t)0x00000002)
#define EADC_STS_SYN_FAIL_CH1             ((uint32_t)0x00000004)
#define EADC_STS_UDP                      ((uint32_t)0x00000040)
#define EADC_STS_OVF                      ((uint32_t)0x00000080)

#define EADC_STS_FIFO                     ((uint32_t)0x00000001)
#define IS_EADC_STATUS(STATUS)            ((STATUS) == EADC_STS_FIFO)
                                                                     
#define IS_EADC_CP(CP)                    ((CP) <= 0x7F)

#define EADC_FLAG_CLK_OUT                 ((uint32_t)0x01000000)



#define EADC_CDMA_CLK_DIV_1               ((uint32_t)0x00000000)
#define EADC_CDMA_CLK_DIV_2               ((uint32_t)0x02000000)
#define EADC_CDMA_CLK_DIV_3               ((uint32_t)0x04000000)
#define EADC_CDMA_CLK_DIV_4               ((uint32_t)0x06000000)
#define EADC_CDMA_CLK_DIV_5               ((uint32_t)0x08000000)
#define EADC_CDMA_CLK_DIV_6               ((uint32_t)0x0A000000)
#define EADC_CDMA_CLK_DIV_7               ((uint32_t)0x0C000000)
#define EADC_CDMA_CLK_DIV_8               ((uint32_t)0x0E000000)
#define IS_EADC_CDMA_CLK_DIV(DIV)         (((DIV) == EADC_CDMA_CLK_DIV_1) || \
                                           ((DIV) == EADC_CDMA_CLK_DIV_2) || \
                                           ((DIV) == EADC_CDMA_CLK_DIV_3) || \
                                           ((DIV) == EADC_CDMA_CLK_DIV_4) || \
                                           ((DIV) == EADC_CDMA_CLK_DIV_5) || \
                                           ((DIV) == EADC_CDMA_CLK_DIV_6) || \
                                           ((DIV) == EADC_CDMA_CLK_DIV_7) || \
                                           ((DIV) == EADC_CDMA_CLK_DIV_8))

#define EADC_SYN_STEP_RESET               ((uint32_t)0x0000E000)
#define EADC_SYN_STEP_64                  ((uint32_t)0x00000000)
#define EADC_SYN_STEP_128                 ((uint32_t)0x00002000)
#define EADC_SYN_STEP_256                 ((uint32_t)0x00004000)
#define EADC_SYN_STEP_512                 ((uint32_t)0x00006000)
#define EADC_SYN_STEP_1024                ((uint32_t)0x00008000)
#define IS_EADC_SYN_STEP(STEP)            (((STEP) == EADC_SYN_STEP_64)  || \
                                           ((STEP) == EADC_SYN_STEP_128) || \
                                           ((STEP) == EADC_SYN_STEP_256) || \
                                           ((STEP) == EADC_SYN_STEP_512) || \
                                           ((STEP) == EADC_SYN_STEP_1024))

#define EADC_CDMA_MODE_RESET              ((uint32_t)0x00001000)
#define EADC_CDMA_MODE_ENABLE             ((uint32_t)0x00001000)
#define EADC_CDMA_MODE_DISABLE            ((uint32_t)0x00000000)
#define IS_EADC_CDMA_MODE(MODE)           (((MODE) == EADC_CDMA_MODE_ENABLE) || \
                                           ((MODE) == EADC_CDMA_MODE_DISABLE))

#define EADC_SEQ_SETS_NUM_RESET           ((uint32_t)0x00000F00)
#define EADC_SEQ_SETS_NUM_2               ((uint32_t)0x00000000)
#define EADC_SEQ_SETS_NUM_3               ((uint32_t)0x00000100)
#define EADC_SEQ_SETS_NUM_4               ((uint32_t)0x00000200)
#define EADC_SEQ_SETS_NUM_5               ((uint32_t)0x00000300)
#define EADC_SEQ_SETS_NUM_6               ((uint32_t)0x00000400)
#define EADC_SEQ_SETS_NUM_7               ((uint32_t)0x00000500)
#define EADC_SEQ_SETS_NUM_8               ((uint32_t)0x00000600)
#define EADC_SEQ_SETS_NUM_9               ((uint32_t)0x00000700)
#define EADC_SEQ_SETS_NUM_10              ((uint32_t)0x00000800)
#define EADC_SEQ_SETS_NUM_11              ((uint32_t)0x00000900)
#define EADC_SEQ_SETS_NUM_12              ((uint32_t)0x00000A00)
#define EADC_SEQ_SETS_NUM_13              ((uint32_t)0x00000B00)
#define EADC_SEQ_SETS_NUM_14              ((uint32_t)0x00000C00)
#define EADC_SEQ_SETS_NUM_15              ((uint32_t)0x00000D00)
#define EADC_SEQ_SETS_NUM_16              ((uint32_t)0x00000E00)
#define IS_EADC_SEQ_SETS_NUM(NUM)         (((NUM) == EADC_SEQ_SETS_NUM_2)  || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_3)  || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_4)  || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_5)  || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_6)  || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_7)  || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_8)  || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_9)  || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_10) || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_11) || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_12) || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_13) || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_14) || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_15) || \
                                           ((NUM) == EADC_SEQ_SETS_NUM_16))

#define EADC_STS_SYN_FAIL_NUM_CH0         ((uint32_t)0x00000F00)
#define EADC_STS_SYN_FAIL_NUM_CH1         ((uint32_t)0x0000F000)

/**
  * @}
  */


/** @defgroup EADC_Exported_Types
  * @{
  */
  
/** 
  * @brief  EADC Init structure definition
  */

typedef struct
{
  uint32_t EADC_CdmaClkFreqDiv;
  uint32_t EADC_ClkOutFreqDiv;     /*This parameter must range from 0 to 255.*/
  uint32_t EADC_SynStep;
  uint32_t EADC_CdmaMode;
  uint32_t EADC_SeqSetsNum;
}EADC_InitType;

/**
  * @}
  */

/** @defgroup EADC_Exported_Functions
  * @{
  */

void EADC_DeInit(void);
void EADC_Init(EADC_InitType* EADC_InitStruct);
void EADC_StructInit(EADC_InitType* EADC_InitStruct);

void EADC_Channel_Config(uint32_t EADC_Channel, uint32_t capturePoint, uint32_t triggerEdge);
void EADC_Cmd(uint32_t EADC_CLKMode, uint32_t EADC_Channel, FunctionalState NewState);

uint32_t EADC_GetSynFailNumber(uint32_t EADC_Channel);
FlagStatus EADC_GetFlagStatus(uint32_t EADC_FLAG);

void EADC_INTConfig(uint32_t EADC_IT, uint32_t NewState);

INTStatus EADC_GetINTStatus(uint32_t EADC_INT);
void EADC_ClearINTStatus(uint32_t EADC_INT);

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

#endif  /*__LIB_EADC_H */

/*********************************** END OF FILE ******************************/