/**
  ******************************************************************************
  * @file    lib_rtc_comp.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-08-2
  * @brief   This file contains all the functions prototypes for the RTC-COMP firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


#ifndef __LIB_RTC_COMP_H
#define __LIB_RTC_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */
  
/** @addtogroup RTC_COMP
  * @{
  */

/** @defgroup RTC_COMP_Exported_Constants
  * @{
  */

#define RTC_COMP_Channel_0                            ((uint32_t)0x00000000)
#define RTC_COMP_Channel_1                            ((uint32_t)0x00000001)
#define IS_RTC_COMP_CHANNEL(CHANNEL)                  (((CHANNEL) == RTC_COMP_Channel_0) || \
                                                       ((CHANNEL) == RTC_COMP_Channel_1))

#define RTC_COMP_Filter_ClkDiv_1                      ((uint32_t)0x00000000)  
#define RTC_COMP_Filter_ClkDiv_2                      ((uint32_t)0x00040000) 
#define RTC_COMP_Filter_ClkDiv_4                      ((uint32_t)0x00080000) 
#define RTC_COMP_Filter_ClkDiv_8                      ((uint32_t)0x000C0000) 
#define RTC_COMP_Filter_ClkDiv_16                     ((uint32_t)0x00100000)
#define RTC_COMP_Filter_ClkDiv_32                     ((uint32_t)0x00140000)
#define RTC_COMP_Filter_ClkDiv_64                     ((uint32_t)0x00180000)
#define RTC_COMP_Filter_ClkDiv_128                    ((uint32_t)0x001C0000)
#define IS_RTC_COMP_FILTER_CLKDIV(__DIV__)            (((__DIV__) == RTC_COMP_Filter_ClkDiv_1)  || \
                                                       ((__DIV__) == RTC_COMP_Filter_ClkDiv_2)  || \
                                                       ((__DIV__) == RTC_COMP_Filter_ClkDiv_4)  || \
                                                       ((__DIV__) == RTC_COMP_Filter_ClkDiv_8)  || \
                                                       ((__DIV__) == RTC_COMP_Filter_ClkDiv_16) || \
                                                       ((__DIV__) == RTC_COMP_Filter_ClkDiv_32) || \
                                                       ((__DIV__) == RTC_COMP_Filter_ClkDiv_64) || \
                                                       ((__DIV__) == RTC_COMP_Filter_ClkDiv_128))


#define RTC_COMP_Filter_Period_0                       ((uint32_t)0x00000000)
#define RTC_COMP_Filter_Period_1                       ((uint32_t)0x00010000)
#define RTC_COMP_Filter_Period_2                       ((uint32_t)0x00020000)
#define RTC_COMP_Filter_Period_3                       ((uint32_t)0x00030000)
#define IS_RTC_COMP_FILTER_Period(__Period__)          (((__Period__) == RTC_COMP_Filter_Period_0) || \
                                                        ((__Period__) == RTC_COMP_Filter_Period_1) || \
                                                        ((__Period__) == RTC_COMP_Filter_Period_2) || \
                                                        ((__Period__) == RTC_COMP_Filter_Period_3))

#define RTC_COMP_FLAG_WAKEUP                           ((uint32_t)0x00010000)
#define IS_RTC_COMP_STATUS(FLAG)                       ((FLAG) == RTC_COMP_FLAG_WAKEUP) 
                                                       
#define RTC_COMP_WKU_HIGH                              ((uint32_t)0x00000010)
#define RTC_COMP_WKU_LOW                               ((uint32_t)0x00000000)
#define IS_RTC_COMP_WKUMode(__MODE__)                  (((__MODE__) == RTC_COMP_WKU_HIGH) || \
                                                        ((__MODE__) == RTC_COMP_WKU_LOW))

#define RTC_COMP_EOC_INT                               ((uint32_t)0x00000001)
#define IS_RTC_COMP_INT(INT)                            ((INT) == RTC_COMP_EOC_INT)
                                                     
#define RTC_COMP_INT_HIGH                              ((uint32_t)0x00000000)
#define RTC_COMP_INT_LOW                               ((uint32_t)0x00000001)
#define IS_RTC_COMP_INT_MODE(__MODE__)                 (((__MODE__) == RTC_COMP_INT_HIGH) || \
                                                        ((__MODE__) == RTC_COMP_INT_LOW))

#define RTC_COMP_OUT_LOW                               ((uint32_t)0x00000000)
#define RTC_COMP_OUT_HIGH                              ((uint32_t)0x00000001)
#define IS_RTC_COMP_OUT(__OUT__)                       (((__OUTPUT__) == RTC_COMP_OUT_LOW) || \
                                                        ((__OUTPUT__) == RTC_COMP_OUT_HIGH))



/**
  * @}
  */

/** @defgroup RTC_COMP_Exported_Types
  * @{
  */  
  
/** 
  * @brief  RTC_COMP Init structure definition
  */
  
typedef struct
{
  uint32_t RTC_COMP_FilterClkDiv;                   /*!< Specifies Filter clock divider */
  uint32_t COMP_FilterClkPeriod;                    /*!< Specifies Filter clock period */
} RTC_COMP_InitType;

/**
  * @}
  */

/** @defgroup RTC_COMP_Exported_Functions
  * @{
  */

void RTC_COMP_DeInit(uint32_t RTC_COMP_Channel);
void RTC_COMP_Init(RTC_COMP_InitType* RTC_COMP_InitStruct);
void RTC_COMP_StructInit(RTC_COMP_InitType* RTC_COMP_InitStruct);
void RTC_COMP_Cmd(uint32_t RTC_COMP_Channel, FunctionalState NewState);

void RTC_COMP_WKUConfig(uint32_t RTC_COMP_Channel,uint32_t WkuMode, FunctionalState NewState);
void RTC_COMP_INTConfig(uint32_t RTC_COMP_Channel,uint32_t IntMode, FunctionalState NewState);

FlagStatus RTC_COMP_GetOutputVal(uint32_t RTC_COMP_Channel);

FlagStatus RTC_COMP_GetWKUStatus(uint32_t RTC_COMP_Channel);
void RTC_COMP_ClearWKUStatus(uint32_t RTC_COMP_Channel);

INTStatus RTC_COMP_GetINTStatus(uint32_t RTC_COMP_Channel);
void RTC_COMP_ClearINTStatus(uint32_t RTC_COMP_Channel);

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

#endif  /*__LIB_RTC_COMP_H */

/*********************************** END OF FILE ******************************/
