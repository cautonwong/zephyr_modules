/**
  ******************************************************************************
  * @file    lib_gpio.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   GPIO library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_GPIO_H
#define __LIB_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Types
  * @{
  */

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE) || \
                                    ((PERIPH) == GPIOF) || \
                                    ((PERIPH) == GPIOG) || \
                                    ((PERIPH) == GPIOH) || \
                                    ((PERIPH) == GPIOI))

/**
  * @}
  */
  
/** @defgroup GPIO Configuration Mode enumeration 
  * @{
  */ 

typedef enum
{ 
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog Mode */
} GPIOMode_TypeDef;
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN) || ((MODE) == GPIO_Mode_OUT) || \
                            ((MODE) == GPIO_Mode_AF) || ((MODE) == GPIO_Mode_AN))

/**
  * @}
  */
  
/** @defgroup GPIO Output type enumeration 
  * @{
  */ 

typedef enum
{ 
  GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
} GPIOOType_TypeDef;
#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))

/**
  * @}
  */
  
/** @defgroup GPIO Output Maximum frequency enumeration 
  * @{
  */ 
  
typedef enum
{ 
  GPIO_Speed_2MHz   = 0x00, /*!< Low speed */
  GPIO_Speed_25MHz  = 0x01, /*!< Medium speed */
  GPIO_Speed_50MHz  = 0x02, /*!< Fast speed */
  GPIO_Speed_100MHz = 0x03  /*!< High speed on 30 pF (80 MHz Output max speed on 15 pF) */
} GPIOSpeed_TypeDef;
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_2MHz) || ((SPEED) == GPIO_Speed_25MHz) || \
                              ((SPEED) == GPIO_Speed_50MHz)|| ((SPEED) == GPIO_Speed_100MHz)) 

/**
  * @}
  */
  
/** @defgroup GPIO Configuration PullUp PullDown enumeration 
  * @{
  */ 

typedef enum
{ 
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
} GPIOPuPd_TypeDef;
#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN))

/**
  * @}
  */
  
/** @defgroup GPIO Init structure definition  
  * @{
  */ 


typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */

  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef */

  GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef */

  GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef */
} GPIO_InitType;
/**
  * @}
  */

/** @defgroup GPIO_pins_define 
  * @{
  */ 
#define GPIO_Pin_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /* Pin 15 selected */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define IS_GPIO_PIN(__PIN__)        ((((uint32_t)(__PIN__) & (uint32_t)(GPIO_Pin_All)) != 0x00U) &&\
                                     (((uint32_t)(__PIN__) & (uint32_t)(~GPIO_Pin_All)) == 0x00U))
#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))
/**
  * @}
  */
  
/** @defgroup GPIO_Pin_sources 
  * @{
  */ 
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))
/**
  * @}
  */
  
/** @defgroup GPIO_Alternat_function_selection_define 
  * @{
  */ 
/** 
  * @brief   AF 0 selection  
  */ 
#define GPIO_AF0_MCO1          ((uint8_t)0x00)  /* MCO1 Alternate Function mapping */
#define GPIO_AF0_MCO2          ((uint8_t)0x00)  /* MCO2 Alternate Function mapping */
#define GPIO_AF0_MCO3          ((uint8_t)0x00)  /* MCO3 Alternate Function mapping */
#define GPIO_AF0_MCO4          ((uint8_t)0x00)  /* MCO4 Alternate Function mapping */
#define GPIO_AF0_RTC_PLLDIV0   ((uint8_t)0x00)  /* RTC PLLDIV Alternate Function mapping */
#define GPIO_AF0_RTC_PLLDIV1   ((uint8_t)0x00)  /* RTC PLLDIV Alternate Function mapping */
#define GPIO_AF0_RTC_IODET1    ((uint8_t)0x00)  /* RTC IODET Alternate Function mapping */
#define GPIO_AF0_RTC_IODET2    ((uint8_t)0x00)  /* RTC IODET Alternate Function mapping */
#define GPIO_AF0_RTC_SP_O      ((uint8_t)0x00)  /* RTC_SP Alternate Function mapping */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /* SWDIO Alternate Function mapping */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /* SWCLK Alternate Function mapping */
#define GPIO_AF0_M0_SWDIO      ((uint8_t)0x00)  /* M0_SWDIO Alternate Function mapping */
#define GPIO_AF0_M0_SWCLK      ((uint8_t)0x00)  /* M0_SWCLK Alternate Function mapping */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_GTMR0_IO1_ETR  ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_GTMR0_IO2      ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_GTMR0_IO3      ((uint8_t)0x01)  /*  Alternate Function mapping */ 
#define GPIO_AF1_GTMR0_IO4      ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_BKIN     ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_O1_N     ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_IO1      ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_IO2      ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_IO3      ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_IO4      ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_ETR      ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_O2_N     ((uint8_t)0x01)  /*  Alternate Function mapping */
#define GPIO_AF1_ETMR0_O3_N     ((uint8_t)0x01)  /*  Alternate Function mapping */

/** 
  * @brief   AF 2 selection  
  */ 
#define GPIO_AF2_GTMR3_IO1      ((uint8_t)0x02)  /* GTMR3_IO1 Alternate Function mapping */
#define GPIO_AF2_GTMR3_IO2      ((uint8_t)0x02)  /* GTMR3_IO2 Alternate Function mapping */
#define GPIO_AF2_GTMR3_IO3      ((uint8_t)0x02)  /* GTMR3_IO3 Alternate Function mapping */
#define GPIO_AF2_GTMR3_IO4      ((uint8_t)0x02)  /* GTMR3_IO4 Alternate Function mapping */
#define GPIO_AF2_GTMR1_IO1      ((uint8_t)0x02)  /* GTMR1_IO1 Alternate Function mapping */
#define GPIO_AF2_GTMR1_IO2      ((uint8_t)0x02)  /* GTMR1_IO2 Alternate Function mapping */
#define GPIO_AF2_GTMR1_IO3      ((uint8_t)0x02)  /* GTMR1_IO3 Alternate Function mapping */
#define GPIO_AF2_GTMR1_IO4      ((uint8_t)0x02)  /* GTMR1_IO4 Alternate Function mapping */
#define GPIO_AF2_GTMR2_IO1      ((uint8_t)0x02)  /* GTMR2_IO1 Alternate Function mapping */
#define GPIO_AF2_GTMR2_IO2      ((uint8_t)0x02)  /* GTMR2_IO2 Alternate Function mapping */
#define GPIO_AF2_GTMR2_IO3      ((uint8_t)0x02)  /* GTMR2_IO3 Alternate Function mapping */
#define GPIO_AF2_GTMR2_IO4      ((uint8_t)0x02)  /* GTMR2_IO4 Alternate Function mapping */
#define GPIO_AF2_GTMR1_ETR      ((uint8_t)0x02)  /* GTMR1_ETR Alternate Function mapping */
#define GPIO_AF2_GTMR2_ETR      ((uint8_t)0x02)  /* GTMR2_ETR Alternate Function mapping */
#define GPIO_AF2_GTMR3_ETR      ((uint8_t)0x02)  /* GTMR3_ETR Alternate Function mapping */

/** 
  * @brief   AF 3 selection  
  */ 
#define GPIO_AF3_ETMR1_ETR       ((uint8_t)0x03)  /* ETMR1_ETR Alternate Function mapping */ 
#define GPIO_AF3_ETMR1_O1_N      ((uint8_t)0x03)  /* ETMR1_O1_N Alternate Function mapping */
#define GPIO_AF3_ETMR1_BKIN      ((uint8_t)0x03)  /* ETMR1_BKIN Alternate Function mapping */
#define GPIO_AF3_ETMR1_O2_N      ((uint8_t)0x03)  /* ETMR1_O2_N Alternate Function mapping */
#define GPIO_AF3_ETMR1_O3_N      ((uint8_t)0x03)  /* ETMR1_O3_N Alternate Function mapping */
#define GPIO_AF3_ETMR1_IO1       ((uint8_t)0x03)  /* ETMR1_IO1 Alternate Function mapping */
#define GPIO_AF3_ETMR1_IO2       ((uint8_t)0x03)  /* ETMR1_IO2 Alternate Function mapping */
#define GPIO_AF3_ETMR1_IO3       ((uint8_t)0x03)  /* ETMR1_IO3 Alternate Function mapping */
#define GPIO_AF3_ETMR1_IO4       ((uint8_t)0x03)  /* ETMR1_IO4 Alternate Function mapping */
#define GPIO_AF3_BTMR0_3_EXT_CLK ((uint8_t)0x03)  /* BTMR0_3_EXT_CLK Alternate Function mapping */
#define GPIO_AF3_BPWM0           ((uint8_t)0x03)  /* BPWM0 Alternate Function mapping */
#define GPIO_AF3_BPWM1           ((uint8_t)0x03)  /* BPWM1 Alternate Function mapping */
#define GPIO_AF3_BPWM2           ((uint8_t)0x03)  /* BPWM2 Alternate Function mapping */
#define GPIO_AF3_BPWM3           ((uint8_t)0x03)  /* BPWM3 Alternate Function mapping */
#define GPIO_AF3_LPBTMR0_EXTIN   ((uint8_t)0x03)  /* LPBTMR0_EXTIN Alternate Function mapping */
#define GPIO_AF3_LPBTMR1_EXTIN   ((uint8_t)0x03)  /* LPBTMR1_EXTIN Alternate Function mapping */

/** 
  * @brief   AF 4 selection  
  */ 
#define GPIO_AF4_FC2_RTS_SCL_SSEL1  ((uint8_t)0x04)  /* _FC2_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF4_FC2_SSEL2          ((uint8_t)0x04)  /* FC2_SSEL2 Alternate Function mapping */
#define GPIO_AF4_FC0_SSEL2          ((uint8_t)0x04)  /* FC0_SSEL2 Alternate Function mapping */
#define GPIO_AF4_FC0_RTS_SCL_SSEL1  ((uint8_t)0x04)  /* FC0_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF4_FC0_CTS_SDA_SSEL0  ((uint8_t)0x04)  /* FC0_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF4_FC1_RTS_SCL_SSEL1  ((uint8_t)0x04)  /* FC1_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF4_FC1_CTS_SDA_SSEL0  ((uint8_t)0x04)  /* FC1_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF4_FC1_SSEL2          ((uint8_t)0x04)  /* FC1_SSEL2 Alternate Function mapping */
#define GPIO_AF4_FC2_CTS_SDA_SSEL0  ((uint8_t)0x04)  /* FC2_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF4_FC0_SCK            ((uint8_t)0x04)  /* FC0_SCK  Alternate Function mapping */
#define GPIO_AF4_FC0_RXD_SDA_MOSI   ((uint8_t)0x04)  /* FC0_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF4_FC2_SCK            ((uint8_t)0x04)  /* FC2_SCK Alternate Function mapping */
#define GPIO_AF4_FC1_SCK            ((uint8_t)0x04)  /* FC1_SCK Alternate Function mapping */
#define GPIO_AF4_FC1_RXD_SDA_MOSI   ((uint8_t)0x04)  /* FC1_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF4_FC1_TXD_SCL_MISO   ((uint8_t)0x04)  /* FC1_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF4_FC2_RXD_SDA_MOSI   ((uint8_t)0x04)  /* FC2_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF4_FC2_TXD_SCL_MISO   ((uint8_t)0x04)  /* FC2_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF4_FC2_SSEL3          ((uint8_t)0x04)  /* FC2_SSEL3 Alternate Function mapping */
#define GPIO_AF4_FC0_TXD_SCL_MISO   ((uint8_t)0x04)  /* FC0_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF4_FC0_SSEL3          ((uint8_t)0x04)  /* FC0_SSEL3 Alternate Function mapping */
#define GPIO_AF4_FC1_SSEL3          ((uint8_t)0x04)  /* FC1_SSEL3Alternate Function mapping */

/** 
  * @brief   AF 5 selection  
  */ 
#define GPIO_AF5_FC3_CTS_SDA_SSEL0   ((uint8_t)0x05)  /* FC3_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF5_FC3_SCK             ((uint8_t)0x05)  /* FC3_SCK Alternate Function mapping */
#define GPIO_AF5_FC3_TXD_SCL_MISO    ((uint8_t)0x05)  /* FC3_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF5_FC3_RXD_SDA_MOSI    ((uint8_t)0x05)  /* FC3_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF5_FC3_SSEL3           ((uint8_t)0x05)  /* FC3_SSEL3 Alternate Function mapping */
#define GPIO_AF5_FC4_CTS_SDA_SSEL0   ((uint8_t)0x05)  /* FC4_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF5_FC4_SCK             ((uint8_t)0x05)  /* FC4_SCK  Alternate Function mapping */
#define GPIO_AF5_FC4_TXD_SCL_MISO    ((uint8_t)0x05)  /* FC4_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF5_FC4_RXD_SDA_MOSI    ((uint8_t)0x05)  /* FC4_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF5_FC3_RTS_SCL_SSEL1   ((uint8_t)0x05)  /* FC3_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF5_FC3_SSEL2           ((uint8_t)0x05)  /* FC3_SSEL2 Alternate Function mapping */
#define GPIO_AF5_I2S0_MCK            ((uint8_t)0x05)  /* I2S0_MCK Alternate Function mapping */
#define GPIO_AF5_I2S0_SD             ((uint8_t)0x05)  /* I2S0_DA Alternate Function mapping */
#define GPIO_AF5_I2S0_WS             ((uint8_t)0x05)  /* I2S0_WS Alternate Function mapping */
#define GPIO_AF5_I2S0_SCK            ((uint8_t)0x05)  /* I2S0_SCK Alternate Function mapping */
#define GPIO_AF5_FC4_SSEL2           ((uint8_t)0x05)  /* FC4_SSEL2 Alternate Function mapping */
#define GPIO_AF5_FC4_RTS_SCL_SSEL1   ((uint8_t)0x05)  /* FC4_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF5_FC4_SSEL3           ((uint8_t)0x05)  /* FC4_SSEL3 Alternate Function mapping */
/** 
  * @brief   AF 6 selection  
  */ 
#define GPIO_AF6_FC5_CTS_SDA_SSEL0     ((uint8_t)0x06)  /* FC5_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF6_FC5_SCK               ((uint8_t)0x06)  /* FC5_SCK  Alternate Function mapping */
#define GPIO_AF6_FC5_TXD_SCL_MISO      ((uint8_t)0x06)  /* FC5_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF6_FC5_RXD_SDA_MOSI      ((uint8_t)0x06)  /* FC5_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF6_I2S1_MCK              ((uint8_t)0x06)  /* I2S1_MCK Alternate Function mapping */
#define GPIO_AF6_I2S1_WS               ((uint8_t)0x06)  /* I2S1_WS Alternate Function mapping */
#define GPIO_AF6_I2S1_SCK              ((uint8_t)0x06)  /* I2S1_SCK Alternate Function mapping */
#define GPIO_AF6_I2S1_SD               ((uint8_t)0x06)  /* I2S1_SD Alternate Function mapping */
#define GPIO_AF6_FC5_SSEL3             ((uint8_t)0x06)  /* FC5_SSEL3 Alternate Function mapping */
#define GPIO_AF6_FC13_SSEL3            ((uint8_t)0x06)  /* FC13_SSEL3 Alternate Function mapping */
#define GPIO_AF6_FC12_SCK              ((uint8_t)0x06)  /* FC12_SCK  Alternate Function mapping */
#define GPIO_AF6_FC12_CTS_SDA_SSEL0    ((uint8_t)0x06)  /* FC12_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF6_FC12_RTS_SCL_SSEL1    ((uint8_t)0x06)  /* FC12_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF6_FC12_RXD_SDA_MOSI     ((uint8_t)0x06)  /* FC12_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF6_FC12_TXD_SCL_MISO     ((uint8_t)0x06)  /* FC12_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF6_FC12_SSEL2            ((uint8_t)0x06)  /* FC12_SSEL2 Alternate Function mapping */
#define GPIO_AF6_FC12_SSEL3            ((uint8_t)0x06)  /* FC12_SSEL3 Alternate Function mapping */
#define GPIO_AF6_FC13_SCK              ((uint8_t)0x06)  /* FC13_SCK  Alternate Function mapping */
#define GPIO_AF6_FC13_CTS_SDA_SSEL0    ((uint8_t)0x06)  /* FC13_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF6_FC13_RTS_SCL_SSEL1    ((uint8_t)0x06)  /* FC13_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF6_FC13_RXD_SDA_MOSI     ((uint8_t)0x06)  /* FC13_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF6_FC13_TXD_SCL_MISO     ((uint8_t)0x06)  /* FC13_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF6_FC13_SSEL2            ((uint8_t)0x06)  /* FC13_SSEL2 Alternate Function mapping */
#define GPIO_AF6_FC5_RTS_SCL_SSEL1     ((uint8_t)0x06)  /* FC5_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF6_FC5_SSEL2             ((uint8_t)0x06)  /* FC5_SSEL2 Alternate Function mapping */

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_FC7_CTS_SDA_SSEL0   ((uint8_t)0x07)  /* FC7_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF7_FC7_RTS_SCL_SSEL1   ((uint8_t)0x07)  /* FC7_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF7_FC7_TXD_SCL_MISO    ((uint8_t)0x07)  /* FC7_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF7_FC7_RXD_SDA_MOSI    ((uint8_t)0x07)  /* FC7_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF7_FC7_SCK             ((uint8_t)0x07)  /* FC7_SCK  Alternate Function mapping */
#define GPIO_AF7_FC6_SCK             ((uint8_t)0x07)  /* FC6_SCK  Alternate Function mapping */
#define GPIO_AF7_FC6_TXD_SCL_MISO    ((uint8_t)0x07)  /* FC6_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF7_FC6_RXD_SDA_MOSI    ((uint8_t)0x07)  /* FC6_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF7_FC6_CTS_SDA_SSEL0   ((uint8_t)0x07)  /* FC6_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF7_FC6_RTS_SCL_SSEL1   ((uint8_t)0x07)  /* FC6_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF7_FC8_TXD_SCL_MISO    ((uint8_t)0x07)  /* FC8_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF7_FC8_RXD_SDA_MOSI    ((uint8_t)0x07)  /* FC8_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF7_FC8_SCK             ((uint8_t)0x07)  /* FC8_SCK  Alternate Function mapping */
#define GPIO_AF7_FC8_CTS_SDA_SSEL0   ((uint8_t)0x07)  /* FC8_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF7_FC8_RTS_SCL_SSEL1   ((uint8_t)0x07)  /* FC8_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF7_FC8_SSEL2           ((uint8_t)0x07)  /* FC8_SSEL2 Alternate Function mapping */
#define GPIO_AF7_FC8_SSEL3           ((uint8_t)0x07)  /* FC8_SSEL3 Alternate Function mapping */
#define GPIO_AF7_FC7_SSEL3           ((uint8_t)0x07)  /* FC7_SSEL3 Alternate Function mapping */
#define GPIO_AF7_FC7_SSEL2           ((uint8_t)0x07)  /* FC7_SSEL2 Alternate Function mapping */
#define GPIO_AF7_FC6_SSEL3           ((uint8_t)0x07)  /* FC6_SSEL3 Alternate Function mapping */
#define GPIO_AF7_FC6_SSEL2           ((uint8_t)0x07)  /* FC6_SSEL2 Alternate Function mapping */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_FC10_TXD_SCL_MISO   ((uint8_t)0x08)  /* FC10_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF8_FC10_RXD_SDA_MOSI   ((uint8_t)0x08)  /* FC10_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF8_FC12_RXD_SDA_MOSI   ((uint8_t)0x08)  /* FC12_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF8_FC9_TXD_SCL_MISO    ((uint8_t)0x08)  /* FC9_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF8_FC9_RXD_SDA_MOSI    ((uint8_t)0x08)  /* FC9_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF8_FC9_SCK             ((uint8_t)0x08)  /* FC9_SCK  Alternate Function mapping */
#define GPIO_AF8_FC12_TXD_SCL_MISO   ((uint8_t)0x08)  /* FC12_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF8_FC11_TXD_SCL_MISO   ((uint8_t)0x08)  /* FC11_TXD_SCL_MISO Alternate Function mapping */
#define GPIO_AF8_FC11_RXD_SDA_MOSI   ((uint8_t)0x08)  /* FC11_RXD_SDA_MOSI Alternate Function mapping */
#define GPIO_AF8_FC11_CTS_SDA_SSEL0  ((uint8_t)0x08)  /* FC11_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF8_FC11_RTS_SCL_SSEL1  ((uint8_t)0x08)  /* FC11_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF8_FC10_RTS_SCL_SSEL1  ((uint8_t)0x08)  /* FC10_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF8_FC10_CTS_SDA_SSEL0  ((uint8_t)0x08)  /* FC10_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF8_FC10_SCK            ((uint8_t)0x08)  /* FC10_SCK  Alternate Function mapping */
#define GPIO_AF8_FC10_SSEL2          ((uint8_t)0x08)  /* FC10_SSEL2 Alternate Function mapping */
#define GPIO_AF8_FC10_SSEL3          ((uint8_t)0x08)  /* FC10_SSEL3 Alternate Function mapping */
#define GPIO_AF8_FC9_RTS_SCL_SSEL1   ((uint8_t)0x08)  /* FC9_RTS_SCL_SSEL1 Alternate Function mapping */
#define GPIO_AF8_FC9_SSEL2           ((uint8_t)0x08)  /* FC9_SSEL2 Alternate Function mapping */
#define GPIO_AF8_FC9_SSEL3           ((uint8_t)0x08)  /* FC9_SSEL3 Alternate Function mapping */
#define GPIO_AF8_FC9_CTS_SDA_SSEL0   ((uint8_t)0x08)  /* FC9_CTS_SDA_SSEL0 Alternate Function mapping */
#define GPIO_AF8_FC11_SCK            ((uint8_t)0x08)  /* FC11_SCK  Alternate Function mapping */
#define GPIO_AF8_FC11_SSEL3          ((uint8_t)0x08)  /* FC11_SSEL3 Alternate Function mapping */
#define GPIO_AF8_FC11_SSEL2          ((uint8_t)0x08)  /* FC11_SSEL2 Alternate Function mapping */

/** 
  * @brief   AF 9 selection 
  */ 
#define GPIO_AF9_CMP0_OUT      ((uint8_t)0x09)  /* CMP0_OUT Alternate Function mapping */
#define GPIO_AF9_CAN0_RX       ((uint8_t)0x09)  /* CAN0_RX Alternate Function mapping */
#define GPIO_AF9_CAN0_TX       ((uint8_t)0x09)  /* CAN0_TX Alternate Function mapping */
#define GPIO_AF9_CAN1_RX       ((uint8_t)0x09)  /* CAN1_RX Alternate Function mapping */
#define GPIO_AF9_CAN1_TX       ((uint8_t)0x09)  /* CAN1_TX Alternate Function mapping */
#define GPIO_AF9_ISO78160_CLK  ((uint8_t)0x09)  /* ISO78160_CLK Alternate Function mapping */
#define GPIO_AF9_ISO78160_DAT  ((uint8_t)0x09)  /* ISO78160_DAT Alternate Function mapping */
#define GPIO_AF9_ISO78161_CLK  ((uint8_t)0x09)  /* ISO78161_CLK Alternate Function mapping */
#define GPIO_AF9_ISO78161_DAT  ((uint8_t)0x09)  /* ISO78161_DAT Alternate Function mapping */
#define GPIO_AF9_CMP1_OUT      ((uint8_t)0x09)  /* CMP1_OUT Alternate Function mapping */

/** 
  * @brief   AF 10 selection  
  */ 
#define GPIO_AF10_ISO78162_DAT ((uint8_t)0xA)  /* ISO78162_DAT Alternate Function mapping */
#define GPIO_AF10_ISO78163_CLK ((uint8_t)0xA)  /* ISO78163_CLK Alternate Function mapping */
#define GPIO_AF10_ISO78163_DAT ((uint8_t)0xA)  /* ISO78163_DAT Alternate Function mapping */
#define GPIO_AF10_EADC_D5      ((uint8_t)0xA)  /* EADC_D5 Alternate Function mapping */
#define GPIO_AF10_EADC_D6      ((uint8_t)0xA)  /* EADC_D6 Alternate Function mapping */
#define GPIO_AF10_EADC_D7      ((uint8_t)0xA)  /* EADC_D7 Alternate Function mapping */
#define GPIO_AF10_EADC_CLK     ((uint8_t)0xA)  /* EADC_CLK Alternate Function mapping */
#define GPIO_AF10_EADC_D0      ((uint8_t)0xA)  /* EADC_D0 Alternate Function mapping */
#define GPIO_AF10_EADC_D1      ((uint8_t)0xA)  /* EADC_D1 Alternate Function mapping */
#define GPIO_AF10_EADC_D2      ((uint8_t)0xA)  /* EADC_D2 Alternate Function mapping */
#define GPIO_AF10_EADC_D3      ((uint8_t)0xA)  /* EADC_D3 Alternate Function mapping */
#define GPIO_AF10_EADC_D4      ((uint8_t)0xA)  /* EADC_D4 Alternate Function mapping */
#define GPIO_AF10_ENGY_CF2     ((uint8_t)0xA)  /* ENGY_CF2 Alternate Function mapping */
#define GPIO_AF10_ISO78162_CLK ((uint8_t)0xA)  /* ISO78162_CLK Alternate Function mapping */

/** 
  * @brief   AF 11 selection  
  */ 
#define GPIO_AF11_RMII0_CLK_IN  ((uint8_t)0x0B)  /* RMII0_CLK_IN Alternate Function mapping */
#define GPIO_AF11_RMDIO0        ((uint8_t)0x0B)  /* RMDIO0 Alternate Function mapping */
#define GPIO_AF11_RMII1_TXD1    ((uint8_t)0x0B)  /* RMII1_TXD1 Alternate Function mapping */
#define GPIO_AF11_RMII0_RX_DV   ((uint8_t)0x0B)  /* RMII0_RX_DV Alternate Function mapping */
#define GPIO_AF11_RMDPPS_OUT0   ((uint8_t)0x0B)  /* RMDPPS_OUT0 Alternate Function mapping */
#define GPIO_AF11_RMII0_TX_EN   ((uint8_t)0x0B)  /* RMII0_TX_EN Alternate Function mapping */
#define GPIO_AF11_RMII0_TXD0    ((uint8_t)0x0B)  /* RMII0_TXD0 Alternate Function mapping */
#define GPIO_AF11_RMII0_TXD1    ((uint8_t)0x0B)  /* RMII0_TXD1 Alternate Function mapping */
#define GPIO_AF11_RMII1_CLK_IN  ((uint8_t)0x0B)  /* RMII1_CLK_IN Alternate Function mapping */
#define GPIO_AF11_RMDCLK0       ((uint8_t)0x0B)  /* RMDCLK0 Alternate Function mapping */
#define GPIO_AF11_RMII1_RXD0    ((uint8_t)0x0B)  /* RMII1_RXD0 Alternate Function mapping */
#define GPIO_AF11_RMII1_RXD1    ((uint8_t)0x0B)  /* RMII1_RXD1 Alternate Function mapping */
#define GPIO_AF11_RMII0_RXD0    ((uint8_t)0x0B)  /* RMII0_RXD0 Alternate Function mapping */
#define GPIO_AF11_RMII0_RXD1    ((uint8_t)0x0B)  /* RMII0_RXD1 Alternate Function mapping */
#define GPIO_AF11_RMDPPS_OUT1   ((uint8_t)0x0B)  /* RMDPPS_OUT1 Alternate Function mapping */
#define GPIO_AF11_RMDCLK1       ((uint8_t)0x0B)  /* RMDCLK1 Alternate Function mapping */
#define GPIO_AF11_RMDIO1        ((uint8_t)0x0B)  /* RMDIO1 Alternate Function mapping */
#define GPIO_AF11_RMII1_RX_DV   ((uint8_t)0x0B)  /* RMII1_RX_DV Alternate Function mapping */
#define GPIO_AF11_RMII1_TX_EN   ((uint8_t)0x0B)  /* RMII1_TX_EN Alternate Function mapping */
#define GPIO_AF11_RMII1_TXD0    ((uint8_t)0x0B)  /* RMII1_TXD0 Alternate Function mapping */

/** 
  * @brief   AF 12 selection  
  */ 
#define GPIO_AF12_SDIO0_D4         ((uint8_t)0xC)  /* SDIO0_D4 Alternate Function mapping */
#define GPIO_AF12_SDIO0_D5         ((uint8_t)0xC)  /* SDIO0_D5 Alternate Function mapping */
#define GPIO_AF12_SDIO0_D6         ((uint8_t)0xC)  /* SDIO0_D6 Alternate Function mapping */
#define GPIO_AF12_SDIO0_D7         ((uint8_t)0xC)  /* SDIO0_D7 Alternate Function mapping */
#define GPIO_AF12_SDIO0_D0         ((uint8_t)0xC)  /* SDIO0_D0 Alternate Function mapping */
#define GPIO_AF12_SDIO0_D1         ((uint8_t)0xC)  /* SDIO0_D1 Alternate Function mapping */
#define GPIO_AF12_SDIO0_D2         ((uint8_t)0xC)  /* SDIO0_D2 Alternate Function mapping */
#define GPIO_AF12_SDIO0_D3         ((uint8_t)0xC)  /* SDIO0_D3 Alternate Function mapping */
#define GPIO_AF12_SDIO0_CLK        ((uint8_t)0xC)  /* SDIO0_CLK Alternate Function mapping */
#define GPIO_AF12_SDIO0_CMD        ((uint8_t)0xC)  /* SDIO0_CMD Alternate Function mapping */
#define GPIO_AF12_OSPI0_IO3        ((uint8_t)0xC)  /* OSPI0_IO3 Alternate Function mapping */
#define GPIO_AF12_OSPI0_IO2        ((uint8_t)0xC)  /* OSPI0_IO2 Alternate Function mapping */
#define GPIO_AF12_OSPI0_IO1        ((uint8_t)0xC)  /* OSPI0_IO1 Alternate Function mapping */
#define GPIO_AF12_OSPI0_IO0        ((uint8_t)0xC)  /* OSPI0_IO0 Alternate Function mapping */
#define GPIO_AF12_OSPI0_IO6        ((uint8_t)0xC)  /* OSPI0_IO6 Alternate Function mapping */
#define GPIO_AF12_OSPI0_IO7        ((uint8_t)0xC)  /* OSPI0_IO7 Alternate Function mapping */
#define GPIO_AF12_OSPI0_IO4        ((uint8_t)0xC)  /* OSPI0_IO4 Alternate Function mapping */
#define GPIO_AF12_OSPI0_IO5        ((uint8_t)0xC)  /* OSPI0_IO5 Alternate Function mapping */
#define GPIO_AF12_OSPI1_IO2        ((uint8_t)0xC)  /* OSPI1_IO2 Alternate Function mapping */
#define GPIO_AF12_OSPI1_SCK_N      ((uint8_t)0xC)  /* OSPI1_SCK_N Alternate Function mapping */
#define GPIO_AF12_OSPI1_SS_0_N     ((uint8_t)0xC)  /* OSPI1_SS_0_N Alternate Function mapping */
#define GPIO_AF12_OSPI1_IO1        ((uint8_t)0xC)  /* OSPI1_IO1 Alternate Function mapping */
#define GPIO_AF12_OSPI1_TXDM_RXDS  ((uint8_t)0xC)  /* OSPI1_TXDM_RXDS Alternate Function mapping */
#define GPIO_AF12_OSPI1_IO0        ((uint8_t)0xC)  /* OSPI1_IO0 Alternate Function mapping */
#define GPIO_AF12_SDIO1_D0         ((uint8_t)0xC)  /* SDIO1_D0 Alternate Function mapping */
#define GPIO_AF12_SDIO1_D1         ((uint8_t)0xC)  /* SDIO1_D1 Alternate Function mapping */
#define GPIO_AF12_SDIO1_D2         ((uint8_t)0xC)  /* SDIO1_D2 Alternate Function mapping */
#define GPIO_AF12_SDIO1_CLK        ((uint8_t)0xC)  /* SDIO1_CLK Alternate Function mapping */
#define GPIO_AF12_SDIO1_D4         ((uint8_t)0xC)  /* SDIO1_D4 Alternate Function mapping */
#define GPIO_AF12_SDIO1_D5         ((uint8_t)0xC)  /* SDIO1_D5 Alternate Function mapping */
#define GPIO_AF12_SDIO1_D6         ((uint8_t)0xC)  /* SDIO1_D6 Alternate Function mapping */
#define GPIO_AF12_SDIO1_D7         ((uint8_t)0xC)  /* SDIO1_D7 Alternate Function mapping */
#define GPIO_AF12_OSPI1_SCK        ((uint8_t)0xC)  /* OSPI1_SCK Alternate Function mapping */
#define GPIO_AF12_OSPI1_IO3        ((uint8_t)0xC)  /* OSPI1_IO3 Alternate Function mapping */
#define GPIO_AF12_OSPI1_IO4        ((uint8_t)0xC)  /* OSPI1_IO4 Alternate Function mapping */
#define GPIO_AF12_OSPI1_IO5        ((uint8_t)0xC)  /* OSPI1_IO5 Alternate Function mapping */
#define GPIO_AF12_OSPI1_IO6        ((uint8_t)0xC)  /* OSPI1_IO6 Alternate Function mapping */
#define GPIO_AF12_OSPI1_IO7        ((uint8_t)0xC)  /* OSPI1_IO7 Alternate Function mapping */
#define GPIO_AF12_OSPI0_SCK        ((uint8_t)0xC)  /* OSPI0_SCK Alternate Function mapping */
#define GPIO_AF12_OSPI0_TXDM_RXDS  ((uint8_t)0xC)  /* OSPI0_TXDM_RXDS Alternate Function mapping */
#define GPIO_AF12_OSPI0_SCK_N      ((uint8_t)0xC)  /* OSPI0_SCK_N Alternate Function mapping */
#define GPIO_AF12_OSPI0_SS_0_N     ((uint8_t)0xC)  /* OSPI0_SS_0_N Alternate Function mapping */
#define GPIO_AF12_SDIO1_WR_PRT     ((uint8_t)0xC)  /* SDIO1_WR_PRT Alternate Function mapping */
#define GPIO_AF12_SDIO1_CARD_DET   ((uint8_t)0xC)  /* SDIO1_CARD_DET Alternate Function mapping */
#define GPIO_AF12_SDIO0_WR_PRT     ((uint8_t)0xC)  /* SDIO0_WR_PRT Alternate Function mapping */
#define GPIO_AF12_SDIO0_CARD_DET   ((uint8_t)0xC)  /* SDIO0_CARD_DET Alternate Function mapping */
#define GPIO_AF12_SDIO1_CMD        ((uint8_t)0xC)  /* SDIO1_CMD Alternate Function mapping */
#define GPIO_AF12_SDIO1_D3         ((uint8_t)0xC)  /* SDIO1_D3 Alternate Function mapping */

/** 
  * @brief   AF 13 selection  
  */ 
#define GPIO_AF13_DCMI_HSYNC   ((uint8_t)0x0D)  /* DCMI_HSYNC Alternate Function mapping */
#define GPIO_AF13_DCMI_PIXCLK  ((uint8_t)0x0D)  /* DCMI_PIXCLK Alternate Function mapping */
#define GPIO_AF13_DCMI_D0      ((uint8_t)0x0D)  /* DCMI_D0 Alternate Function mapping */
#define GPIO_AF13_DCMI_D1      ((uint8_t)0x0D)  /* DCMI_D1 Alternate Function mapping */
#define GPIO_AF13_DCMI_D10     ((uint8_t)0x0D)  /* DCMI_D10 Alternate Function mapping */
#define GPIO_AF13_DCMI_D5      ((uint8_t)0x0D)  /* DCMI_D5 Alternate Function mapping */
#define GPIO_AF13_DCMI_VSYNC   ((uint8_t)0x0D)  /* DCMI_VSYNC Alternate Function mapping */
#define GPIO_AF13_DCMI_D6      ((uint8_t)0x0D)  /* DCMI_D6 Alternate Function mapping */
#define GPIO_AF13_DCMI_D7      ((uint8_t)0x0D)  /* DCMI_D7 Alternate Function mapping */
#define GPIO_AF13_DCMI_D2      ((uint8_t)0x0D)  /* DCMI_D2 Alternate Function mapping */
#define GPIO_AF13_DCMI_D3      ((uint8_t)0x0D)  /* DCMI_D3 Alternate Function mapping */
#define GPIO_AF13_DCMI_D8      ((uint8_t)0x0D)  /* DCMI_D8 Alternate Function mapping */
#define GPIO_AF13_DCMI_D4      ((uint8_t)0x0D)  /* DCMI_D4 Alternate Function mapping */
#define GPIO_AF13_DCMI_D9      ((uint8_t)0x0D)  /* DCMI_D9 Alternate Function mapping */
#define GPIO_AF13_DCMI_D11     ((uint8_t)0x0D)  /* DCMI_D11 Alternate Function mapping */
#define GPIO_AF13_DCMI_D12     ((uint8_t)0x0D)  /* DCMI_D12 Alternate Function mapping */
#define GPIO_AF13_DCMI_D13     ((uint8_t)0x0D)  /* DCMI_D13 Alternate Function mapping */
/** 
  * @brief   AF 14 selection  
  */ 
#define GPIO_AF14_BSPI1_CK         ((uint8_t)0x0E)  /* BSPI1_CK Alternate Function mapping */
#define GPIO_AF14_BSPI0_MOSI       ((uint8_t)0x0E)  /* BSPI0_MOSI Alternate Function mapping */
#define GPIO_AF14_BSPI1_CS         ((uint8_t)0x0E)  /* BSPI1_CS Alternate Function mapping */
#define GPIO_AF14_BSPI1_MISO       ((uint8_t)0x0E)  /* BSPI1_MISO Alternate Function mapping */
#define GPIO_AF14_BSPI1_MOSI       ((uint8_t)0x0E)  /* BSPI1_MOSI Alternate Function mapping */
#define GPIO_AF14_BSPI3_CS         ((uint8_t)0x0E)  /* BSPI3_CS Alternate Function mapping */
#define GPIO_AF14_BTMR4_7_EXT_CLK  ((uint8_t)0x0E)  /* BTMR4_7_EXT_CLK Alternate Function mapping */
#define GPIO_AF14_BPWM5            ((uint8_t)0x0E)  /* BPWM5 Alternate Function mapping */
#define GPIO_AF14_ENGY_CF1         ((uint8_t)0x0E)  /* ENGY_CF1 Alternate Function mapping */
#define GPIO_AF14_ENGY_CF2         ((uint8_t)0x0E)  /* ENGY_CF2 Alternate Function mapping */
#define GPIO_AF14_UART14_RX        ((uint8_t)0x0E)  /* UART14_RX Alternate Function mapping */
#define GPIO_AF14_UART14_TX        ((uint8_t)0x0E)  /* UART14_TX Alternate Function mapping */
#define GPIO_AF14_UART17_TX        ((uint8_t)0x0E)  /* UART17_TX Alternate Function mapping */
#define GPIO_AF14_BSPI0_CK         ((uint8_t)0x0E)  /* BSPI0_CK Alternate Function mapping */
#define GPIO_AF14_BSPI0_CS         ((uint8_t)0x0E)  /* BSPI0_CS Alternate Function mapping */
#define GPIO_AF14_BSPI0_MISO       ((uint8_t)0x0E)  /* BSPI0_MISO Alternate Function mapping */
#define GPIO_AF14_BSPI2_CK         ((uint8_t)0x0E)  /* BSPI2_CK Alternate Function mapping */
#define GPIO_AF14_BSPI3_MISO       ((uint8_t)0x0E)  /* BSPI3_MISO Alternate Function mapping */
#define GPIO_AF14_BSPI3_CK         ((uint8_t)0x0E)  /* BSPI3_CK Alternate Function mapping */
#define GPIO_AF14_BSPI3_MOSI       ((uint8_t)0x0E)  /* BSPI3_MOSI Alternate Function mapping */
#define GPIO_AF14_UART18_TX        ((uint8_t)0x0E)  /* UART18_TX Alternate Function mapping */
#define GPIO_AF14_UART18_RX        ((uint8_t)0x0E)  /* UART18_RX Alternate Function mapping */
#define GPIO_AF14_UART19_TX        ((uint8_t)0x0E)  /* UART19_TX Alternate Function mapping */
#define GPIO_AF14_UART19_RX        ((uint8_t)0x0E)  /* UART19_RX Alternate Function mapping */
#define GPIO_AF14_BSPI5_CS         ((uint8_t)0x0E)  /* BSPI5_CS Alternate Function mapping */
#define GPIO_AF14_BSPI5_CK         ((uint8_t)0x0E)  /* BSPI5_CK Alternate Function mapping */
#define GPIO_AF14_BSPI5_MISO       ((uint8_t)0x0E)  /* BSPI5_MISO Alternate Function mapping */
#define GPIO_AF14_UART15_RX        ((uint8_t)0x0E)  /* UART15_RX Alternate Function mapping */
#define GPIO_AF14_UART15_TX        ((uint8_t)0x0E)  /* UART15_TX Alternate Function mapping */
#define GPIO_AF14_UART16_RX        ((uint8_t)0x0E)  /* UART16_RX Alternate Function mapping */
#define GPIO_AF14_UART16_TX        ((uint8_t)0x0E)  /* UART16_TX Alternate Function mapping */
#define GPIO_AF14_BSPI4_CK         ((uint8_t)0x0E)  /* BSPI4_CK Alternate Function mapping */
#define GPIO_AF14_BSPI4_CS         ((uint8_t)0x0E)  /* BSPI4_CS Alternate Function mapping */
#define GPIO_AF14_BSPI4_MISO       ((uint8_t)0x0E)  /* BSPI4_MISO Alternate Function mapping */
#define GPIO_AF14_BSPI4_MOSI       ((uint8_t)0x0E)  /* BSPI4_MOSI Alternate Function mapping */
#define GPIO_AF14_UART17_RX        ((uint8_t)0x0E)  /* UART17_RX Alternate Function mapping */
#define GPIO_AF14_BSPI5_MOSI       ((uint8_t)0x0E)  /* BSPI5_MOSI Alternate Function mapping */
#define GPIO_AF14_ENGY_CF0         ((uint8_t)0x0E)  /* ENGY_CF0 Alternate Function mapping */
#define GPIO_AF14_BPWM4            ((uint8_t)0x0E)  /* BPWM4 Alternate Function mapping */
#define GPIO_AF14_BPWM6            ((uint8_t)0x0E)  /* BPWM6 Alternate Function mapping */
#define GPIO_AF14_BSPI2_MISO       ((uint8_t)0x0E)  /* BSPI2_MISO Alternate Function mapping */
#define GPIO_AF14_I2C14_SCL        ((uint8_t)0x0E)  /* I2C14_SCL Alternate Function mapping */
#define GPIO_AF14_I2C14_SDA        ((uint8_t)0x0E)  /* I2C14_SDA Alternate Function mapping */
#define GPIO_AF14_BPWM7            ((uint8_t)0x0E)  /* BPWM7 Alternate Function mapping */
#define GPIO_AF14_BSPI2_CS         ((uint8_t)0x0E)  /* BSPI2_CS Alternate Function mapping */
#define GPIO_AF14_BSPI2_MOSI       ((uint8_t)0x0E)  /* BSPI2_MOSI Alternate Function mapping */
/** 
  * @brief   AF 15 selection  
  */ 

#define IS_GPIO_AF(AF) ((AF) < 0x0FU)

/**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/ 

/** @defgroup GPIO_Exported_Functions
  * @{
  */

/* Initialization and Configuration functions *********************************/
void GPIO_StructInit(GPIO_InitType* GPIO_InitStruct);
void GPIO_Init(GPIO_Type* GPIOx, GPIO_InitType* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_Type* GPIOx, uint16_t GPIO_Pin);

/* GPIO Read and Write functions **********************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_Type* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_Type* GPIOx);
void GPIO_SetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_Type* GPIOx, uint16_t PortVal);
void GPIO_ToggleBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin);

/* GPIO Alternate functions configuration function ****************************/
void GPIO_PinAFConfig(GPIO_Type* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_GPIO_H */
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
