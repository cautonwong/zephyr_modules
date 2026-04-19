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
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
   
#ifdef __cplusplus
}
#endif

#endif

/*********************************** END OF FILE ******************************/
