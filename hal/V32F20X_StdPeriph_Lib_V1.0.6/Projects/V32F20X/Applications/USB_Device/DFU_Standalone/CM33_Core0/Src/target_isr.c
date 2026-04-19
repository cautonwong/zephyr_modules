/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include "target_isr.h"
#include "main.h"

extern USB_OTG_CORE_HANDLE USB_OTG_dev;
extern uint32_t USBD_OTG_ISR_Handler(USB_OTG_CORE_HANDLE * pdev);

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
extern uint32_t USBD_OTG_EP1IN_ISR_Handler(USB_OTG_CORE_HANDLE * pdev);
extern uint32_t USBD_OTG_EP1OUT_ISR_Handler(USB_OTG_CORE_HANDLE * pdev);
#endif

extern uint8_t DeviceState;

uint8_t *USER_INFORMATION[11] = {
  (uint8_t *) ">STATE: Application IDLE        ",
  (uint8_t *) ">STATE: Application Detach      ",
  (uint8_t *) ">STATE: DFU IDLE                ",
  (uint8_t *) ">STATE: DFU Download Synch      ",
  (uint8_t *) ">STATE: DFU Download Busy       ",
  (uint8_t *) ">STATE: DFU Download IDLE       ",
  (uint8_t *) ">STATE: DFU Manifest Synch      ",
  (uint8_t *) ">STATE: DFU Manifest            ",
  (uint8_t *) ">STATE: DFU Manifest Wait Reset ",
  (uint8_t *) ">STATE: DFU Upload IDLE         ",
  (uint8_t *) ">STATE: DFU ERROR               "
};

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
  * @brief  OTG_FS_IRQHandler
  *          This function handles USB-On-The-Go FS global interrupt request.
  *          requests.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_FS
void USB_FS_IRQHandler(void)
#else
void USB_HS_IRQHandler(void)
#endif
{
  USBD_OTG_ISR_Handler(&USB_OTG_dev);
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
