/**
  * @file    target_isr.h
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   This file contains the headers of the interrupt handlers.
******************************************************************************/

#ifndef __TARGET_ISR_H
#define __TARGET_ISR_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "target.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void I2C33_0_IRQHandler(void);
void I2C33_1_IRQHandler(void);
void DMA_IRQHandler(void);
void UART33_0_IRQHandler(void);
void UART33_1_IRQHandler(void);
void UART33_2_IRQHandler(void);
void UART33_3_IRQHandler(void);
void UART33_4_IRQHandler(void);
void UART33_5_IRQHandler(void);
void UART33_6_IRQHandler(void);
void UART33_7_IRQHandler(void);
void ISO78160_IRQHandler(void);
void ISO78161_IRQHandler(void);
void TMR33_0_IRQHandler(void);
void TMR33_1_IRQHandler(void);
void TMR33_2_IRQHandler(void);
void BTMR3_IRQHandler(void);
void BPWM0_IRQHandler(void);
void BPWM1_IRQHandler(void);
void BPWM2_IRQHandler(void);
void BPWM3_IRQHandler(void);
void FLASH33_IRQHandler(void);
void SPI33_0_IRQHandler(void);
void SPI33_1_IRQHandler(void);
void SPI33_2_IRQHandler(void);
void SPI33_3_IRQHandler(void);
void SPI33_4_IRQHandler(void);
void SCR33_IRQHandler(void);
void MAILBOX33_IRQHandler(void);
   
#ifdef __cplusplus
}
#endif

#endif

/*********************************** END OF FILE ******************************/
