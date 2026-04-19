/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include "target_isr.h"
#include "main.h"

__IO uint16_t IC2Value = 0;
__IO uint16_t DutyCycle = 0;
__IO uint32_t Frequency = 0;

extern uint32_t SystemCoreClock;

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
  STD_IncTick();
}

/**
  * @brief  This function handles GTMR0 global interrupt request.
  * @param  None
  * @retval None
  */
void GTMR0_IRQHandler(void)
{
  if(TMR_GetITStatus(GTMR0, TMR_IT_CC2) == SET)
  {
    /* Clear TIM1 Capture compare interrupt pending bit */
    TMR_ClearITPendingBit(GTMR0, TMR_IT_CC2);
    
    /* Get the Input Capture value */
    IC2Value = TMR_GetCapture2(GTMR0);

    if (IC2Value != 0)
    {
      /* Duty cycle computation */
      DutyCycle = (TMR_GetCapture1(GTMR0) * 100) / IC2Value;

      /* Frequency computation */
      Frequency = SystemCoreClock / IC2Value;
    }
    else
    {
      DutyCycle = 0;
      Frequency = 0;
    }
    
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
