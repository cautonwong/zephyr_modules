
/**
  ******************************************************************************
  * @file    lib_gpio_ex.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   This file contains all the functions prototypes for the GPIO   
  *          Extension module firmware library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_GPIO_EX_H
#define __LIB_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIOEx
  * @{
  */ 

/** @defgroup GPIOEx_Exported_Types
  * @{
  */ 


/** 
  * @brief  IODET Time structure definition  
  */
typedef struct
{
  uint32_t Min      : 7;
  uint32_t Hour     : 6;
  uint32_t Date     : 6;
  uint32_t Month    : 5;
  uint32_t Year     : 7;
  uint32_t EdgeFlag : 1;
} IODET_DataType;

/**
  * @}
  */ 


/** @defgroup GPIOEx_Exported_constants 
  * @{
  */


/** @defgroup IODET_Trig_source
  * @{
  */
#define IODET_TRIG_DISABLE             ((uint32_t)0x00000000)  
#define IODET_TRIG_RISING              ((uint32_t)0x00000001)  
#define IODET_TRIG_FALLING             ((uint32_t)0x00000002)  
#define IODET_TRIG_BOTH                ((uint32_t)0x00000003)  
#define IS_IODET_TRIG(TRIG)            (((TRIG) == IODET_TRIG_DISABLE) ||\
                                        ((TRIG) == IODET_TRIG_RISING)  ||\
                                        ((TRIG) == IODET_TRIG_FALLING) ||\
                                        ((TRIG) == IODET_TRIG_BOTH))
/**                                    
  * @}                                 
  */                                   
                                       
/** @defgroup IODET_Pin                
  * @{                                 
  */                                   
#define IODET_PIN_C13                  ((uint32_t)0x00000000)  
#define IODET_PIN_I8                   ((uint32_t)0x00000001)  
#define IS_IODET_GPIO(GPIO)            (((GPIO) == IODET_PIN_C13) ||\
                                        ((GPIO) == IODET_PIN_I8))
/**                                    
  * @}                                 
  */                                   
                                       
#define IODET_EVENT_1_9                ((uint32_t)0x00000000)  
#define IODET_EVENT_NONE               ((uint32_t)0x00000001)  
#define IODET_EVENT_10                 ((uint32_t)0x00000002)  


/** @defgroup FAST_IO_pins_define 
  * @{
  */ 
#define FAST_IOD_Pin_0                 ((uint32_t)0x00000001)  /* IOD Pin 0 selected */
#define FAST_IOD_Pin_1                 ((uint32_t)0x00000002)  /* IOD Pin 1 selected */
#define FAST_IOD_Pin_2                 ((uint32_t)0x00000004)  /* IOD Pin 2 selected */
#define FAST_IOD_Pin_3                 ((uint32_t)0x00000008)  /* IOD Pin 3 selected */
#define FAST_IOD_Pin_4                 ((uint32_t)0x00000010)  /* IOD Pin 4 selected */
#define FAST_IOD_Pin_5                 ((uint32_t)0x00000020)  /* IOD Pin 5 selected */
#define FAST_IOD_Pin_6                 ((uint32_t)0x00000040)  /* IOD Pin 6 selected */
#define FAST_IOD_Pin_7                 ((uint32_t)0x00000080)  /* IOD Pin 7 selected */
#define FAST_IOD_Pin_8                 ((uint32_t)0x00000100)  /* IOD Pin 8 selected */
#define FAST_IOD_Pin_9                 ((uint32_t)0x00000200)  /* IOD Pin 9 selected */
#define FAST_IOD_Pin_10                ((uint32_t)0x00000400)  /* IOD Pin 10 selected */
#define FAST_IOD_Pin_11                ((uint32_t)0x00000800)  /* IOD Pin 11 selected */
#define FAST_IOD_Pin_12                ((uint32_t)0x00001000)  /* IOD Pin 12 selected */
#define FAST_IOD_Pin_13                ((uint32_t)0x00002000)  /* IOD Pin 13 selected */
#define FAST_IOD_Pin_14                ((uint32_t)0x00004000)  /* IOD Pin 14 selected */
#define FAST_IOD_Pin_15                ((uint32_t)0x00008000)  /* IOD Pin 15 selected */
#define FAST_IOE_Pin_0                 ((uint32_t)0x00010000)  /* IOE Pin 0 selected */
#define FAST_IOE_Pin_1                 ((uint32_t)0x00020000)  /* IOE Pin 1 selected */
#define FAST_IOE_Pin_2                 ((uint32_t)0x00040000)  /* IOE Pin 2 selected */
#define FAST_IOE_Pin_3                 ((uint32_t)0x00080000)  /* IOE Pin 3 selected */
#define FAST_IOE_Pin_4                 ((uint32_t)0x00100000)  /* IOE Pin 4 selected */
#define FAST_IOE_Pin_5                 ((uint32_t)0x00200000)  /* IOE Pin 5 selected */
#define FAST_IOE_Pin_6                 ((uint32_t)0x00400000)  /* IOE Pin 6 selected */
#define FAST_IOE_Pin_7                 ((uint32_t)0x00800000)  /* IOE Pin 7 selected */
#define FAST_IOE_Pin_8                 ((uint32_t)0x01000000)  /* IOE Pin 8 selected */
#define FAST_IOE_Pin_9                 ((uint32_t)0x02000000)  /* IOE Pin 9 selected */
#define FAST_IOE_Pin_10                ((uint32_t)0x04000000)  /* IOE Pin 10 selected */
#define FAST_IOE_Pin_11                ((uint32_t)0x08000000)  /* IOE Pin 11 selected */
#define FAST_IOE_Pin_12                ((uint32_t)0x10000000)  /* IOE Pin 12 selected */
#define FAST_IOE_Pin_13                ((uint32_t)0x20000000)  /* IOE Pin 13 selected */
#define FAST_IOE_Pin_14                ((uint32_t)0x40000000)  /* IOE Pin 14 selected */
#define FAST_IOE_Pin_15                ((uint32_t)0x80000000)  /* IOE Pin 15 selected */
#define FAST_IO_Pin_All                ((uint32_t)0xFFFFFFFF)  /* All pins selected */

#define IS_FAST_IO_PIN(PIN)            ((((PIN) & (uint32_t)0x00) == 0x00) && ((PIN) != (uint32_t)0x00))
#define IS_GET_FAST_IO_PIN(PIN)        (((PIN) == FAST_IOD_Pin_0) || \
                                        ((PIN) == FAST_IOD_Pin_1) || \
                                        ((PIN) == FAST_IOD_Pin_2) || \
                                        ((PIN) == FAST_IOD_Pin_3) || \
                                        ((PIN) == FAST_IOD_Pin_4) || \
                                        ((PIN) == FAST_IOD_Pin_5) || \
                                        ((PIN) == FAST_IOD_Pin_6) || \
                                        ((PIN) == FAST_IOD_Pin_7) || \
                                        ((PIN) == FAST_IOD_Pin_8) || \
                                        ((PIN) == FAST_IOD_Pin_9) || \
                                        ((PIN) == FAST_IOD_Pin_10) || \
                                        ((PIN) == FAST_IOD_Pin_11) || \
                                        ((PIN) == FAST_IOD_Pin_12) || \
                                        ((PIN) == FAST_IOD_Pin_13) || \
                                        ((PIN) == FAST_IOD_Pin_14) || \
                                        ((PIN) == FAST_IOD_Pin_15) || \
                                        ((PIN) == FAST_IOE_Pin_0) || \
                                        ((PIN) == FAST_IOE_Pin_1) || \
                                        ((PIN) == FAST_IOE_Pin_2) || \
                                        ((PIN) == FAST_IOE_Pin_3) || \
                                        ((PIN) == FAST_IOE_Pin_4) || \
                                        ((PIN) == FAST_IOE_Pin_5) || \
                                        ((PIN) == FAST_IOE_Pin_6) || \
                                        ((PIN) == FAST_IOE_Pin_7) || \
                                        ((PIN) == FAST_IOE_Pin_8) || \
                                        ((PIN) == FAST_IOE_Pin_9) || \
                                        ((PIN) == FAST_IOE_Pin_10) || \
                                        ((PIN) == FAST_IOE_Pin_11) || \
                                        ((PIN) == FAST_IOE_Pin_12) || \
                                        ((PIN) == FAST_IOE_Pin_13) || \
                                        ((PIN) == FAST_IOE_Pin_14) || \
                                        ((PIN) == FAST_IOE_Pin_15))

/** @defgroup GPIO_Event 
  * @{
  */
#define GPIO_EXTI_MODE_DISABLE           ((uint16_t)0x00)
#define GPIO_EXTI_MODE_EDGE              ((uint16_t)0x01)
#define GPIO_EXTI_MODE_LEVEL             ((uint16_t)0x02)
#define GPIO_EXTI_MODE_DUAL_EDGE         ((uint16_t)0x03)
#define GPIO_EXTI_POLA_HIGH_OR_RISING    ((uint16_t)0x00)
#define GPIO_EXTI_POLA_LOW_OR_FALLING    ((uint16_t)0x01)



#define GPIO_EVENT_DISABLE               GPIO_EXTI_MODE_DISABLE
#define GPIO_EVENT_RISING_EDGE           (GPIO_EXTI_MODE_EDGE | (GPIO_EXTI_POLA_HIGH_OR_RISING<<2))
#define GPIO_EVENT_FALLING_EDGE          (GPIO_EXTI_MODE_EDGE | (GPIO_EXTI_POLA_LOW_OR_FALLING<<2))
#define GPIO_EVENT_DUAL_EDGE             GPIO_EXTI_MODE_DUAL_EDGE
#define GPIO_EVENT_HIGH_LEVEL            (GPIO_EXTI_MODE_LEVEL | (GPIO_EXTI_POLA_HIGH_OR_RISING<<2))
#define GPIO_EVENT_LOW_LEVEL             (GPIO_EXTI_MODE_LEVEL | (GPIO_EXTI_POLA_LOW_OR_FALLING<<2))
#define IS_GPIO_EVENT(__EVT__)           (((__EVT__) == GPIO_EVENT_DISABLE     ) || \
                                          ((__EVT__) == GPIO_EVENT_RISING_EDGE ) || \
                                          ((__EVT__) == GPIO_EVENT_FALLING_EDGE) || \
                                          ((__EVT__) == GPIO_EVENT_DUAL_EDGE   ) || \
                                          ((__EVT__) == GPIO_EVENT_HIGH_LEVEL  ) || \
                                          ((__EVT__) == GPIO_EVENT_LOW_LEVEL   ))

/**
  * @}
  */

/**
  * @}
  */ 

/** @defgroup GPIOEx_Exported_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup GPIOEx_Exported_Functions
  * @{
  */
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1) 
void IODET_ModeConfig(uint32_t IODET_Pin, uint32_t TrigSrc);
uint8_t IODET_GetEventStatus(uint32_t IODET_Pin);
void IODET_GetFIFODataOnce(uint32_t IODET_Pin, IODET_DataType *IODET_DataStruct);

void FAST_IO_Cmd(uint32_t FAST_IO_Pin, FunctionalState NewState);
uint8_t FAST_IO_ReadOutputDataBit(uint32_t FAST_IO_Pin);
void FAST_IO_SetBits(uint32_t FAST_IO_Pin);
void FAST_IO_ResetBits(uint32_t FAST_IO_Pin);
void FAST_IO_ToggleBits(uint32_t FAST_IO_Pin);
#endif

void GPIO_WKU_DeInit();
void GPIO_INT_Config(GPIO_Type* GPIOx, uint16_t GPIO_Pin, uint16_t Event);
void GPIO_WKU_Config(GPIO_Type* GPIOx, uint16_t GPIO_Pin, uint16_t Event);
FlagStatus GPIO_GetWKUStatus(uint16_t GPIO_Pin);
void GPIO_ClearWKUStatus(uint16_t GPIO_Pin);
void GPIO_GenerateSWInterrupt(uint16_t GPIO_Pin);

FlagStatus GPIO_GetFlagStatus(uint16_t GPIO_Pin);
void GPIO_ClearFlag(uint16_t GPIO_Pin);
INTStatus GPIO_GetINTStatus(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_GPIO_EX_H */
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




















