/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include <string.h>
#include "target_isr.h"
#include "main.h"

extern CanTxMsg TxMessage;
extern CanRxMsg RxMessage;
extern void Print_CAN_data(CanTxMsg *msg);
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
  * @brief  This function handles CAN0 interrupt request.
  * @param  None
  * @retval None
  */
void CAN0_IRQHandler(void)
{
	uint8_t tmp;
  tmp = CAN0->IR;
  if(tmp & CAN_INT_RI)
  {
    CAN_Receive(CAN0,&RxMessage);
    CAN_ReleaseReceiveBuffer(CAN0);
    printf("CAN0 Receive DATA: \r\n");
    Print_CAN_data(&RxMessage); 
		if(memcmp(&TxMessage.Data, &RxMessage.Data, 8))
		{
			printf("error.\r\n");
		}
		else
		{
			printf("success.\r\n");
		}
  }
}

/**
  * @brief  This function handles CAN1 interrupt request.
  * @param  None
  * @retval None
  */
void CAN1_IRQHandler(void)
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
