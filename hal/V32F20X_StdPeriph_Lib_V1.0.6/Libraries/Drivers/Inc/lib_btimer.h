/**
  ******************************************************************************
  * @file    lib_btimer.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-05-12
  * @brief   This file contains all the functions prototypes for the BTMR firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_BTIMER_H
#define __LIB_BTIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "target.h"


/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup BTMR
  * @{
  */

/** @defgroup BTMR_Exported_Types
  * @{
  */ 
  
/** 
  * @brief  BTMR Time Base Init structure definition
  */
typedef struct
{
  uint32_t Period;       /*!< Specifies the period value to be loaded.
                              This parameter must be a number between 0x00000000 and 0xFFFFFFFF.  */ 
  uint32_t ExtClk;       /*!< Specifies whether select the external clock signal as the clock source*/ 
  uint32_t ExtEn;        /*!< Specifies whether select timer external clock pin as the clock enable IO port*/           
} BTMR_InitType;

/**
  * @}
  */ 

/** @defgroup BTMR_Exported_constants 
  * @{
  */

#if defined (V32F20XXX_CM0_CORE)
/* CM0 BTMR Instances */
#define IS_BTMR_ALL_INSTANCE(__INSTANCE__)  (((__INSTANCE__) == BTMR4) ||\
                                             ((__INSTANCE__) == BTMR5) ||\
                                             ((__INSTANCE__) == BTMR6) ||\
                                             ((__INSTANCE__) == BTMR7) ||\
                                             ((__INSTANCE__) == LPBTMR0) ||\
                                             ((__INSTANCE__) == LPBTMR1))
#endif 

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
/* CM33 BTMR Instances */
#define IS_BTMR_ALL_INSTANCE(__INSTANCE__)  (((__INSTANCE__) == BTMR0) ||\
                                             ((__INSTANCE__) == BTMR1) ||\
                                             ((__INSTANCE__) == BTMR2) ||\
                                             ((__INSTANCE__) == BTMR3) ||\
                                             ((__INSTANCE__) == BTMR4) ||\
                                             ((__INSTANCE__) == BTMR5) ||\
                                             ((__INSTANCE__) == BTMR6) ||\
                                             ((__INSTANCE__) == BTMR7) ||\
                                             ((__INSTANCE__) == LPBTMR0)  ||\
                                             ((__INSTANCE__) == LPBTMR1))
#endif 


		
/** @defgroup BTMR_Clock_Source 
  * @{
  */
#define BTMR_CLKSRC_INTERNAL            ((uint32_t)0x00000000)
#define BTMR_CLKSRC_EXTERNAL            ((uint32_t)0x00000004)
#define IS_BTMR_CLKSRC(CLKSRC)          (((CLKSRC) == BTMR_CLKSRC_INTERNAL) ||\
                                        ((CLKSRC) == BTMR_CLKSRC_EXTERNAL))
/**
  * @}
  */

/** @defgroup BTMR_Clock_EXTEN
  * @{
  */
#define BTMR_EXTEN_DISABLE              ((uint32_t)0x00000000)
#define BTMR_EXTEN_ENABLE               ((uint32_t)0x00000002)
#define IS_BTMR_EXTEN(EXTEN)            (((EXTEN) == BTMR_EXTEN_DISABLE) ||\
                                        ((EXTEN) == BTMR_EXTEN_ENABLE))
/**
  * @}
  */ 

/**
  * @}
  */  

/** @defgroup BTMR_Exported_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup BTMR_Exported_Functions
  * @{
  */
void BTMR_DeInit(BTMR_Type *BTMRx);
void BTMR_StructInit(BTMR_InitType *InitStruct);
void BTMR_Init(BTMR_Type *BTMRx, BTMR_InitType *BTMR_InitStruct);
void BTMR_INTConfig(BTMR_Type *BTMRx, FunctionalState NewState);
ITStatus BTMR_GetINTStatus(BTMR_Type *BTMRx);
void BTMR_ClearINTStatus(BTMR_Type *BTMRx);
void BTMR_Cmd(BTMR_Type *BTMRx, FunctionalState NewState);
uint32_t BTMR_GetCounter(BTMR_Type *BTMRx);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_BTIMER_H */

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
