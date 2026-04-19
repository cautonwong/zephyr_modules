/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include "target_isr.h"
#include "main.h"

uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
    while (1)
  {
  }
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles GTMR0 interrupt request.
  * @param  None
  * @retval None
  */
void GTMR0_IRQHandler(void)
{
  /* TMR3_CH1 toggling with frequency = 183.1 Hz */
  if (TMR_GetITStatus(GTMR0, TMR_IT_CC1) != RESET)
  {
    TMR_ClearITPendingBit(GTMR0, TMR_IT_CC1 );
    capture = TMR_GetCapture1(GTMR0);
    TMR_SetCompare1(GTMR0, capture + CCR1_Val );
  }

  /* TMR3_CH2 toggling with frequency = 366.2 Hz */
  if (TMR_GetITStatus(GTMR0, TMR_IT_CC2) != RESET)
  {
    TMR_ClearITPendingBit(GTMR0, TMR_IT_CC2);
    capture = TMR_GetCapture2(GTMR0);
    TMR_SetCompare2(GTMR0, capture + CCR2_Val);
  }

  /* TMR3_CH3 toggling with frequency = 732.4 Hz */
  if (TMR_GetITStatus(GTMR0, TMR_IT_CC3) != RESET)
  {
    TMR_ClearITPendingBit(GTMR0, TMR_IT_CC3);
    capture = TMR_GetCapture3(GTMR0);
    TMR_SetCompare3(GTMR0, capture + CCR3_Val);
  }

  /* TMR3_CH4 toggling with frequency = 1464.8 Hz */
  if (TMR_GetITStatus(GTMR0, TMR_IT_CC4) != RESET)
  {
    TMR_ClearITPendingBit(GTMR0, TMR_IT_CC4);
    capture = TMR_GetCapture4(GTMR0);
    TMR_SetCompare4(GTMR0, capture + CCR4_Val);
  }
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*
void PPP_IRQHandler(void)
{
  PPP_IRQHandler(&PPPHandle);
}
*/

/*********************************** END OF FILE ******************************/
