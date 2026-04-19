/**
  ******************************************************************************
  * @file    board.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   1. Set of firmware functions to manage Leds
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
#include <stdio.h>

typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
}Led_Type;

typedef enum 
{  
  BUTTON1 = 0,
  BUTTON2 = 1
}Button_Type;

typedef enum 
{  
  DOWN = 0,
  UP = 1
}Button_Status;

/**
 * @brief LED
 */
#define LEDn                                    3

#define LED1_PIN                                GPIO_Pin_12
#define LED1_GPIO_PORT                          GPIOB

#define LED2_PIN                                GPIO_Pin_13
#define LED2_GPIO_PORT                          GPIOB

#define LED3_PIN                                GPIO_Pin_14
#define LED3_GPIO_PORT                          GPIOB

/**
 * @brief Key push-button
 */
#define BUTTONn                                    2

#define BUTTON1_PIN                                GPIO_Pin_10
#define BUTTON1_GPIO_PORT                          GPIOB

#define BUTTON2_PIN                                GPIO_Pin_11
#define BUTTON2_GPIO_PORT                          GPIOB

void BSP_Printf_Init(void);
void BSP_LED_Init(Led_Type Led);
void BSP_LED_On(Led_Type Led);
void BSP_LED_Off(Led_Type Led);
void BSP_LED_Toggle(Led_Type Led);
void BSP_PB_Init(Button_Type Button);
Button_Status BSP_PB_GetState(Button_Type Button);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BOARD_H */

/*********************************** END OF FILE ******************************/
