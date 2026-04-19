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

void CM33_MAILBOX_IRQHandler(void);
void CM0_MAILBOX_IRQHandler(void);
void DMA0_IRQHandler(void);
void DMA1_IRQHandler(void);
void ENC_ENG_IRQHandler(void);
void I2S_IRQHandler(void);
void USB_HS_IRQHandler(void);
void USB_FS_IRQHandler(void);
void OSPI0_IRQHandler(void);
void OSPI1_IRQHandler(void);
void FLASHA_IRQHandler(void);
void FLASHB_IRQHandler(void);
void ISO78160_IRQHandler(void);
void ISO78161_IRQHandler(void);
void BTMR0_IRQHandler(void);
void BTMR1_IRQHandler(void);
void BTMR2_IRQHandler(void);
void BTMR3_IRQHandler(void);
void BPWM0_IRQHandler(void);
void BPWM1_IRQHandler(void);
void BPWM2_IRQHandler(void);
void BPWM3_IRQHandler(void);
void SDIO_0_IRQHandler(void);
void SDIO_1_IRQHandler(void);
void RNG_IRQHandler(void);
void CRC_IRQHandler(void);
void SCR_IRQHandler(void);
void CAN_0_IRQHandler(void);
void CAN_1_IRQHandler(void);
void TMR1_UP_IRQHandler(void);
void TMR1_BRK_IRQHandler(void);
void TMR1_CC_IRQHandler(void);
void TMR1_TRG_IRQHandler(void);
void TMR2_UP_IRQHandler(void);
void TMR2_BRK_IRQHandler(void);
void TMR2_CC_IRQHandler(void);
void TMR2_TRG_IRQHandler(void);
void GTMR0_IRQHandler(void);
void GTMR1_IRQHandler(void);
void TMR5_IRQHandler(void);
void TMR6_IRQHandler(void);
void ADC1_IRQHandler(void);
void ADC2_IRQHandler(void);
void MAC0_IRQHandler(void);
void MAC1_IRQHandler(void);
void DCMI_IRQHandler(void);
void FLEXCOMM0_IRQHandler(void);
void FLEXCOMM1_IRQHandler(void);
void FLEXCOMM2_IRQHandler(void);
void FLEXCOMM3_IRQHandler(void);
void FLEXCOMM4_IRQHandler(void);
void FLEXCOMM5_IRQHandler(void);
void FLEXCOMM6_IRQHandler(void);
void FLEXCOMM7_IRQHandler(void);
void FLEXCOMM8_IRQHandler(void);
void FLEXCOMM9_IRQHandler(void);
void FLEXCOMM10_IRQHandler(void);
void FLEXCOMM11_IRQHandler(void);
void FLEXCOMM12_IRQHandler(void);
void FLEXCOMM13_IRQHandler(void);
   
#ifdef __cplusplus
}
#endif

#endif

/*********************************** END OF FILE ******************************/
