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
  STD_IncTick();
}

void ISO78162_IRQHandler(void)
{
  if (ISO7816_GetINTStatus(SAMPLE_IS07816, ISO7816_INT_TXRTYERR))
  {
    ISO7816_ClearINTStatus(SAMPLE_IS07816, ISO7816_INT_TXRTYERR);
    /* Transmit error handler start */   
  }
  
  if (ISO7816_GetINTStatus(SAMPLE_IS07816, ISO7816_INT_TXDONE))
  {
    ISO7816_ClearINTStatus(SAMPLE_IS07816, ISO7816_INT_TXDONE);
    
  }
  
  if (ISO7816_GetINTStatus(SAMPLE_IS07816, ISO7816_INT_RX))
  {
    ISO7816_ClearINTStatus(SAMPLE_IS07816, ISO7816_INT_RX);
    g_recieve_data[g_recieve_count] = ISO7816_ReceiveData(SAMPLE_IS07816);
    g_recieve_count += 1;
    if(g_recieve_count >= 256)
    {
      g_recieve_count = 0;
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
