/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include "target_isr.h"
#include "main.h"
#include "lib_hfm.h"

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
  
  if(g_CIC_Init_flag == 1)
  {
    if(check_CIC_Done_status() == 1)
    {
      /* CIC_Integrate Done */
      if(g_CIC_process_flag == 1)
      {
        CIC_Comb_Start();
      }
      
      /* CIC_Comb Done */
      if(g_CIC_process_flag == 2)
      {
        g_CIC_process_flag = 3;
      }
    }
  }
}


unsigned int DMA_COUNT = 0;
void DMA0_CH0_IRQHandler(void)
{
  INTStatus status;
  status = DMA_GetITtatus(DMA0_Channel0, DMA_INT_BLOCK);
  if (status == SET)
  {
    DMA_ClearITStatus(DMA0_Channel0, DMA_INT_BLOCK);
    DMA_COUNT += 1;
  }
}

unsigned int EGY0_SPILL_COUNT = 0;
unsigned int DSP_Done_Flag = 0;
void HFM_COP_IRQHandler(void)
{
  if((HFM_GetINTStatus(HFM_INT_T2FDONE)) && (HFM->INTEN&HFM_INT_T2FDONE))
  {
    HFM_ClearINTStatus(HFM_INT_T2FDONE);

    /* start DSP calculate */
    HFM_DSP_StartManual();
  }
  
  if((HFM_GetINTStatus(HFM_INT_DSPDONE)) && (HFM->INTEN&HFM_INT_DSPDONE))
  {
    HFM_ClearINTStatus(HFM_INT_DSPDONE);
    DSP_Done_Flag = 1;
  }
  
  if((HFM_GetINTStatus(HFM_INT_EGY0SPILL)) && (HFM->INTEN&HFM_INT_EGY0SPILL))
  {
    EGY0_SPILL_COUNT += 1;
    HFM_ClearINTStatus(HFM_INT_EGY0SPILL);
  }

  if((HFM_GetINTStatus(HFM_INT_EGY1SPILL)) && (HFM->INTEN&HFM_INT_EGY1SPILL))
  {
    HFM_ClearINTStatus(HFM_INT_EGY1SPILL);
  }

  if((HFM_GetINTStatus(HFM_INT_EGY2SPILL)) && (HFM->INTEN&HFM_INT_EGY2SPILL))
  {
    HFM_ClearINTStatus(HFM_INT_EGY2SPILL);
  }
  
  return;
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
