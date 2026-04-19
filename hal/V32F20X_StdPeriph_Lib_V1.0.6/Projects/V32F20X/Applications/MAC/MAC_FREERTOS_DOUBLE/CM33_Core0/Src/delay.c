/**
  ******************************************************************************
  * @file    delay.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-21
  * @brief  
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "delay.h" 
#include "target.h"
#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"		
#include "task.h"
#endif

static uint8_t  fac_us = 0;
static uint16_t fac_ms = 0;

 
extern void xPortSysTickHandler(void);
 

// delay init
// SYSCLK:system clk freq
void delay_init(uint8_t SYSCLK)
{
	uint32_t reload = 0;

	fac_us = SYSCLK;
	reload = SYSCLK;
	reload *= 1000000/configTICK_RATE_HZ;
	fac_ms = 1000/configTICK_RATE_HZ;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; // open SYSTICK interrupt
	SysTick->LOAD = reload; 			
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // openSYSTICK    
  NVIC_SetPriority(SysTick_IRQn, 15);    
}


void delay_us(uint32_t nus)
{		
	uint32_t ticks = 0;
	uint32_t told = 0,tnow = 0,tcnt = 0;
	uint32_t reload = SysTick->LOAD;
  
	ticks = nus*fac_us; 						
	told = SysTick->VAL;
  
	while(1)
	{
		tnow = SysTick->VAL;	
		if(tnow != told)
		{	    
			if(tnow < told)tcnt += told - tnow;	
			else tcnt += reload - tnow + told;	    
			told = tnow;
			if(tcnt >= ticks)break;			
		}  
	};										    
} 

// delay nms
// nms:0~65535
void delay_ms(uint32_t nms)
{	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED) // RTOS running
	{		
		if(nms>=fac_ms)						
		{ 
   			vTaskDelay(nms/fac_ms);	 		//FreeRTOS delay
		}
		nms%=fac_ms;				 
	}
  
	delay_us((uint32_t)(nms*1000));			
}

// delay nms, Not for task scheduling
void delay_xms(uint32_t nms)
{
	uint32_t i = 0;
  
	for(i=0;i<nms;i++) delay_us(1000);
}

			 
