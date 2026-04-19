/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include "target_isr.h"
#include "main.h"

extern volatile uint32_t g_bAppRun;
typedef void (*pFun)(void);

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + NMI_HAND_OFFSET));
    (*p)();
  }
  else
  {
      //Bootloader
  } 
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  pFun p;

  SerialPutString("\nEnter IAP HardFault!\n\r");
    
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + HardFault_HAND_OFFSET));
    (*p)();
  }
  else
  {     
    while (1)
    {
    }
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + SVC_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + PendSV_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + SysTick_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles PMU interrupt request.
  * @param  None
  * @retval None
  */
void PMU_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + PMU_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles RTC interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + RTC_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles U32K0 interrupt request.
  * @param  None
  * @retval None
  */
void U32K0_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + U32K0_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles U32K1 interrupt request.
  * @param  None
  * @retval None
  */
void U32K1_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + U32K1_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles I2C interrupt request.
  * @param  None
  * @retval None
  */
void I2C_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + I2C_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles SPI1 interrupt request.
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + SPI1_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles UART0 interrupt request.
  * @param  None
  * @retval None
  */
void UART0_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + UART0_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles UART1 interrupt request.
  * @param  None
  * @retval None
  */
void UART1_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + UART1_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles UART2 interrupt request.
  * @param  None
  * @retval None
  */
void UART2_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + UART2_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles UART3 interrupt request.
  * @param  None
  * @retval None
  */
void UART3_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + UART3_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles UART4 interrupt request.
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + UART4_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles UART5 interrupt request.
  * @param  None
  * @retval None
  */
void UART5_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + UART5_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles ISO78160 interrupt request.
  * @param  None
  * @retval None
  */
void ISO78160_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + ESAM0_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles ISO78161 interrupt request.
  * @param  None
  * @retval None
  */
void ISO78161_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + ESAM1_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles TMR0 interrupt request.
  * @param  None
  * @retval None
  */
void TMR0_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + TMR0_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles TMR1 interrupt request.
  * @param  None
  * @retval None
  */
void TMR1_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + TMR1_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles TMR2 interrupt request.
  * @param  None
  * @retval None
  */
void TMR2_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + TMR2_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles TMR3 interrupt request.
  * @param  None
  * @retval None
  */
void TMR3_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + TMR3_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles PWM0 interrupt request.
  * @param  None
  * @retval None
  */
void PWM0_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + PWM0_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles PWM1 interrupt request.
  * @param  None
  * @retval None
  */
void PWM1_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + PWM1_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles PWM2 interrupt request.
  * @param  None
  * @retval None
  */
void PWM2_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + PWM2_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles PWM3 interrupt request.
  * @param  None
  * @retval None
  */
void PWM3_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + PWM3_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles DMA interrupt request.
  * @param  None
  * @retval None
  */
void DMA_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + DMA_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles FLASH interrupt request.
  * @param  None
  * @retval None
  */
void FLASH_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + FLASH_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles ANA interrupt request.
  * @param  None
  * @retval None
  */
void ANA_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + ANA_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles SPI2 interrupt request.
  * @param  None
  * @retval None
  */
void SPI2_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + SPI2_HAND_OFFSET));
    (*p)();
  }
}

/**
  * @brief  This function handles SPI3 interrupt request.
  * @param  None
  * @retval None
  */
void SPI3_IRQHandler(void)
{
  pFun p;
  
  if (g_bAppRun)
  {
    p = (pFun)(*(__IO uint32_t*)(ApplicationAddress + SPI3_HAND_OFFSET));
    (*p)();
  }
}


/*********************************** END OF FILE ******************************/
