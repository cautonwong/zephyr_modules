/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include "target_isr.h"
#include "main.h"

__IO uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
__IO uint16_t CaptureNumber;
__IO uint32_t Capture = 0;
__IO uint32_t TMR3Freq;
extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */


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
  * @brief  This function handles BPWM0 interrupts requests.
  * @param  None
  * @retval None
  */
void BBPWM0_IRQHandler(void)
{

  if(BPWM_GetChannelINTStatus(BPWM0, BPWM_CHANNEL_0, BPWM_INT_CCIFG) != RESET)
  {
    /* Clear GTMR0 Capture compare interrupt pending bit */
    BPWM_ClearChannelINTStatus(BPWM0, BPWM_CHANNEL_0, BPWM_INT_CCIFG);

    if(CaptureNumber == 0)
    {
      /* Get the Input Capture value */
      IC3ReadValue1 = BPWM_GetCapture(BPWM0, BPWM_CHANNEL_0);
      CaptureNumber = 1;
    }
    else if(CaptureNumber == 1)
    {
      /* Get the Input Capture value */
      IC3ReadValue2 = BPWM_GetCapture(BPWM0, BPWM_CHANNEL_0);
      
      /* Capture computation */
      if (IC3ReadValue2 > IC3ReadValue1)
      {
        Capture = (IC3ReadValue2 - IC3ReadValue1); 
      }
      else
      {
        Capture = ((0xFFFF - IC3ReadValue1) + IC3ReadValue2); 
      }
      /* Frequency computation */ 
      TMR3Freq = (uint32_t) SystemCoreClock/ (2 * Capture);
      CaptureNumber = 0;
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
