/**
  * @file    timer.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include <stdint.h>
#include "timer.h"
#include "main.h"
#include "target_isr.h"



extern  __IO uint32_t lwip_localtime;


void delay_5ms(uint32_t delay5Ms)
{
  uint32_t time = lwip_localtime;

  while((lwip_localtime - time) < delay5Ms);
}


uint32_t get_time(void)
{
    return lwip_localtime;
}


//void SysTick_Handler(void)
//{
//  lwip_localtime += 10;
//   
//}



