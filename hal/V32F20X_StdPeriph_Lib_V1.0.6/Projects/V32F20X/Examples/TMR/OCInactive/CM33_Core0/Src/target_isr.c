/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include "target_isr.h"
#include "main.h"

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
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}


/**
  * @brief  This function handles ETMR1 CC interrupt request.
  * @param  None
  * @retval None
  */
void TMR2_CC_IRQHandler(void)
{
  if (TMR_GetITStatus(ETMR1, TMR_IT_CC1) != RESET)
  {
    /* Clear ETMR1 Capture Compare1 interrupt pending bit*/
    TMR_ClearITPendingBit(ETMR1, TMR_IT_CC1);

    /* PA.06 turnoff after 1000 ms */
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);
  }
  else if (TMR_GetITStatus(ETMR1, TMR_IT_CC2) != RESET)
  {
    /* Clear ETMR1 Capture Compare2 interrupt pending bit*/
    TMR_ClearITPendingBit(ETMR1, TMR_IT_CC2);

    /* PA.07 turnoff after 500 ms */
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);
  }
  else if (TMR_GetITStatus(ETMR1, TMR_IT_CC3) != RESET)
  {
    /* Clear ETMR1 Capture Compare3 interrupt pending bit*/
    TMR_ClearITPendingBit(ETMR1, TMR_IT_CC3);

    /* PA.08 turnoff after 250 ms */
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);
  }
  else
  {
    /* Clear ETMR1 Capture Compare4 interrupt pending bit*/
    TMR_ClearITPendingBit(ETMR1, TMR_IT_CC4);

    /* PA.09 turnoff after 125 ms */
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);
  }
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
