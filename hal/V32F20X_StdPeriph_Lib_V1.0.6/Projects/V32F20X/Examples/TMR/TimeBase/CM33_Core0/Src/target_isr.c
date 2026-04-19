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
  * @brief  This function handles ETMR1 interrupt request.
  * @param  None
  * @retval None
  */
void ETMR1_CC_IRQHandler(void)
{

  if (TMR_GetITStatus(ETMR1, TMR_IT_CC1) != RESET)
  {
    TMR_ClearITPendingBit(ETMR1, TMR_IT_CC1 );

    /* Pin PC.06 toggling with frequency = 73.24 Hz */
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6)));
    capture = TMR_GetCapture1(ETMR1);
    TMR_SetCompare1(ETMR1, capture + CCR1_Val);
  }

  if (TMR_GetITStatus(ETMR1, TMR_IT_CC2) != RESET)
  {
    TMR_ClearITPendingBit(ETMR1, TMR_IT_CC2);
    
    /* Pin PC.07 toggling with frequency = 109.8 Hz */
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7)));
    capture = TMR_GetCapture2(ETMR1);
    TMR_SetCompare2(ETMR1, capture + CCR2_Val);
  }

  if (TMR_GetITStatus(ETMR1, TMR_IT_CC3) != RESET)
  {
    TMR_ClearITPendingBit(ETMR1, TMR_IT_CC3);
    
    /* Pin PC.08 toggling with frequency = 219.7 Hz */
    GPIO_WriteBit(GPIOC, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_8)));
    capture = TMR_GetCapture3(ETMR1);
    TMR_SetCompare3(ETMR1, capture + CCR3_Val);
  }

  if (TMR_GetITStatus(ETMR1, TMR_IT_CC4) != RESET)
  {
    TMR_ClearITPendingBit(ETMR1, TMR_IT_CC4);
    
    /* Pin PC.09 toggling with frequency = 439.4 Hz */
    GPIO_WriteBit(GPIOC, GPIO_Pin_9, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9)));
    capture = TMR_GetCapture4(ETMR1);
    TMR_SetCompare4(ETMR1, capture + CCR4_Val);
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
