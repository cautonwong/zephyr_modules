/**
  ******************************************************************************
  * @file    lib_comp.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Comp library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_COMP_H
#define __LIB_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */
  
/** @addtogroup COMP
  * @{
  */

/** @defgroup COMP_Exported_Constants
  * @{
  */
#define IS_COMP_ALL_INSTANCE(__INSTANCE__)       (((__INSTANCE__) == COMP0) || \
                                                  ((__INSTANCE__) == COMP1))

#define COMP_HystEn_POS                          (1UL)


#define COMP_Mode_UltraLowPower                  ((uint32_t)0x00000000)
#define COMP_Mode_LowPower                       ((uint32_t)0x00000004)
#define COMP_Mode_MediumSpeed                    ((uint32_t)0x00000008)
#define COMP_Mode_HighSpeed                      ((uint32_t)0x0000000C)
#define IS_COMP_MODE(__MODE__)                    (((__MODE__) == COMP_Mode_UltraLowPower) || \
                                                   ((__MODE__) == COMP_Mode_LowPower)      || \
                                                   ((__MODE__) == COMP_Mode_MediumSpeed)   || \
                                                   ((__MODE__) == COMP_Mode_HighSpeed))


#define COMP_Output_Negative                      ((uint32_t)0x00000000)
#define COMP_Output_Positive                      ((uint32_t)0x00000004)
#define IS_COMP_OUTPUT(__OUTPUT__)                (((__OUTPUT__) == COMP_Output_Positive) || \
                                                   ((__OUTPUT__) == COMP_Output_Negative))

#define LPulseTime_POS                            (1UL)
#define COMP_LPULSE_TIME                          (0xFF)
#define IS_COMP_LPULSE_TIME(__TIME__)             (((__TIME__) & ~COMP_LPULSE_TIME) == 0U) 


#define COMP_Filter_ClkDiv_1                      ((uint32_t)0x00000000)  
#define COMP_Filter_ClkDiv_2                      ((uint32_t)0x00040000) 
#define COMP_Filter_ClkDiv_4                      ((uint32_t)0x00080000) 
#define COMP_Filter_ClkDiv_8                      ((uint32_t)0x000C0000) 
#define COMP_Filter_ClkDiv_16                     ((uint32_t)0x00100000)
#define COMP_Filter_ClkDiv_32                     ((uint32_t)0x00140000)
#define COMP_Filter_ClkDiv_64                     ((uint32_t)0x00180000)
#define COMP_Filter_ClkDiv_128                    ((uint32_t)0x001C0000)
#define IS_COMP_FILTER_CLKDIV(__DIV__)            (((__DIV__) == COMP_Filter_ClkDiv_1)  || \
                                                   ((__DIV__) == COMP_Filter_ClkDiv_2)  || \
                                                   ((__DIV__) == COMP_Filter_ClkDiv_4)  || \
                                                   ((__DIV__) == COMP_Filter_ClkDiv_8)  || \
                                                   ((__DIV__) == COMP_Filter_ClkDiv_16) || \
                                                   ((__DIV__) == COMP_Filter_ClkDiv_32) || \
                                                   ((__DIV__) == COMP_Filter_ClkDiv_64) || \
                                                   ((__DIV__) == COMP_Filter_ClkDiv_128))


#define COMP_Filter_Period_0                      ((uint32_t)0x00000000)
#define COMP_Filter_Period_1                      ((uint32_t)0x00010000)
#define COMP_Filter_Period_2                      ((uint32_t)0x00020000)
#define COMP_Filter_Period_3                      ((uint32_t)0x00030000)
#define IS_COMP_FILTER_Period(__Period__)         (((__Period__) == COMP_Filter_Period_0) || \
                                                   ((__Period__) == COMP_Filter_Period_1) || \
                                                   ((__Period__) == COMP_Filter_Period_2) || \
                                                   ((__Period__) == COMP_Filter_Period_3))


#define COMP_INT_EDGE_DISABLE                     ((uint32_t)0x00000000)
#define COMP_INT_RISING                           ((uint32_t)0x00000008)
#define COMP_INT_FALLING                          ((uint32_t)0x00000010)
#define COMP_INT_BOTH                             ((uint32_t)0x00000018)
#define COMP_INT_LEVEL_DISABLE                    ((uint32_t)0x00000004)
#define COMP_INT_HIGH                             ((uint32_t)0x0000000C)
#define COMP_INT_LOW                              ((uint32_t)0x00000014)
#define IS_COMP_INT_TYPE(__TYPE__)                (((__TYPE__) == COMP_INT_EDGE_DISABLE )  || \
                                                   ((__TYPE__) == COMP_INT_RISING       )  || \
                                                   ((__TYPE__) == COMP_INT_FALLING      )  || \
                                                   ((__TYPE__) == COMP_INT_BOTH         )  || \
                                                   ((__TYPE__) == COMP_INT_LEVEL_DISABLE)  || \
                                                   ((__TYPE__) == COMP_INT_HIGH         )  || \
                                                   ((__TYPE__) == COMP_INT_LOW))

#define COMP_WKU_SRC_FILTER                       ((uint32_t)0x00000000)
#define COMP_WKU_SRC_UNFILTER                     ((uint32_t)0x00000002)
#define IS_COMP_WKU_SRC(__SRC__)                  (((__SRC__) == COMP_WKU_SRC_FILTER ) || \
                                                   ((__SRC__) == COMP_WKU_SRC_UNFILTER))    
                                                

#define COMP_WKU_EDGE_DISABLE                     ((uint32_t)0x00000000)
#define COMP_WKU_RISING                           ((uint32_t)0x00000008)
#define COMP_WKU_FALLING                          ((uint32_t)0x00000010)
#define COMP_WKU_BOTH                             ((uint32_t)0x00000018)
#define COMP_WKU_LEVEL_DISABLE                    ((uint32_t)0x00000004)
#define COMP_WKU_HIGH                             ((uint32_t)0x0000000C)
#define COMP_WKU_LOW                              ((uint32_t)0x00000014)                   
#define IS_COMP_WKU_TYPE(__TYPE__)                (((__TYPE__) == COMP_WKU_EDGE_DISABLE )  || \
                                                   ((__TYPE__) == COMP_WKU_RISING       )  || \
                                                   ((__TYPE__) == COMP_WKU_FALLING      )  || \
                                                   ((__TYPE__) == COMP_WKU_BOTH         )  || \
                                                   ((__TYPE__) == COMP_WKU_LEVEL_DISABLE)  || \
                                                   ((__TYPE__) == COMP_WKU_HIGH         )  || \
                                                   ((__TYPE__) == COMP_WKU_LOW))                                                 

#define COMP_INT_SRC_FILTERE                      ((uint32_t)0x00000000)
#define COMP_INT_SRC_UNFILTER                     ((uint32_t)0x00000020)
#define IS_COMP_INT_SRC(__SRC__)                  (((__SRC__) == COMP_INT_SRC_FILTERE) || \
                                                   ((__SRC__) == COMP_INT_SRC_UNFILTER))


#define COMP_INT_STS                              ((uint32_t)0x00000002)
#define COMP_WKU_STS                              ((uint32_t)0x00000001)

  
/**
  * @}
  */


/** @defgroup COMP_Exported_Types
  * @{
  */
  
/** 
  * @brief  COMP Init structure definition
  */

typedef struct
{
  uint32_t COMP_Mode;                               /*!< Specifies the Mode,Can select HighSpeed,UltraLowPower Mode*/
  uint32_t COMP_HystEn;                             /*!< Specifies the period of long pulse,[0,255]*/
  uint32_t COMP_OutputLevel;                        /*!< Specifies the Output 1: vip>vin 1,vip<vin 0,0:vip>vin 0,vip<vin 1 */
  uint32_t COMP_FilterClkDiv;                       /*!< Specifies Filter clock divider */
  uint32_t COMP_FilterClkPeriod;                    /*!< Specifies Filter clock period */
} COMP_InitType;

/**
  * @}
  */

/** @defgroup COMP_Exported_Functions
  * @{
  */

void COMP_DeInit(void);

void COMP_Init(COMP_Type* COMPx, COMP_InitType* COMP_InitStruct);
void COMP_StructInit(COMP_InitType* COMP_InitStruct);

void COMP_WKUInit(COMP_Type* COMPx, uint32_t WakeupSrc, uint32_t WakeupTrig);
void COMP_WKUCmd(COMP_Type* COMPx, FunctionalState NewState);

void COMP_Cmd(COMP_Type* COMPx, FunctionalState NewState);

FlagStatus COMP_GetOutputVal(COMP_Type* COMPx);

void COMP_INTConfig(COMP_Type* COMPx, uint32_t IntSrc, uint32_t IntType,FunctionalState NewState);
void COMP_LPulseTime_Config(COMP_Type* COMPx, uint32_t LPulseTime, FunctionalState NewState);

INTStatus COMP_GetINTStatus(COMP_Type* COMPx);
INTStatus COMP_GetWKUStatus(COMP_Type* COMPx);

void COMP_ClearINTStatus(COMP_Type* COMPx);
void COMP_ClearWKUStatus(COMP_Type* COMPx);

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

#endif  /*__LIB_COMP_H */

/*********************************** END OF FILE ******************************/
