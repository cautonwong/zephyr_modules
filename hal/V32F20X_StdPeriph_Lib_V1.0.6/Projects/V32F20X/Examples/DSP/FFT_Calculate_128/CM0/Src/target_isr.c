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
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
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

extern uint8_t DSPFlag;
/**
  * @brief  This function handles HFM Handler.
  * @param  None
  * @retval None
  */
void HFM_COP_IRQHandler(void)
{
  if(HFM_GetINTStatus(HFM_INT_T2FDONE))
  {
    HFM_ClearINTStatus(HFM_INT_T2FDONE);
    HFM_DSP_StartManual();
    HFM_DSP_WaitForManual();
    printf("DSP Done\r\n");
  }
  if(HFM_GetINTStatus(HFM_INT_DSPDONE))
  {
    DSPFlag = 1;
    HFM_ClearINTStatus(HFM_INT_DSPDONE);
  }
}

extern uint32_t DMA1flag_framend,DMA1flag_framend1;
/**
  * @brief  This function handles DMA Handler.
  * @param  None
  * @retval None
  */
void BDMA_IRQHandler(void)
{
  if (BDMA_GetINTStatus(BDMA_INT_C1FE))
  {
    BDMA_ClearINTStatus(BDMA_INT_C1FE);
    if(BDMA->C1DST == RxBuf)
    {
      DMA1flag_framend = 1;
      BDMA_StopCmd(BDMA_CHANNEL_1,ENABLE);
      BDMA_StopCmd(BDMA_CHANNEL_1,DISABLE);
      BDMA->C1DST = RxBuf1;
      HFM->WAVE_BADDR = RxBuf;
    }
    else
    {
      DMA1flag_framend1 = 1;
      BDMA_StopCmd(BDMA_CHANNEL_1,ENABLE);
      BDMA_StopCmd(BDMA_CHANNEL_1,DISABLE);
      BDMA->C1DST = RxBuf;
      HFM->WAVE_BADDR = RxBuf1;
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
