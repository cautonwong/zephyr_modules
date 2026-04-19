/**
  * @file    target_isr.h
  * @author  Application Team
  * @version V1.0
  * @date    2021-09-26
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
void USB_HS_IRQHandler(void);
void USB_FS_IRQHandler(void);
   
#ifdef __cplusplus
}
#endif

#endif

/*********************************** END OF FILE ******************************/
