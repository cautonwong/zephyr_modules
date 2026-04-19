/**
  ******************************************************************************
  * @file    delay.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-21
  * @brief  
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __DELAY_H
#define __DELAY_H 			   
  
#include <stdint.h>

#define SYSTEM_SUPPORT_OS		1

void delay_init(uint8_t SYSCLK);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
void delay_xms(uint32_t nms);
#endif





























