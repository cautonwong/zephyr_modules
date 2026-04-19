/**
  * @file    target_isr.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   Main Interrupt Service Routines.
******************************************************************************/

#include "target_isr.h"
#include "main.h"


__IO uint32_t step = 1;

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
  /* Generate ETMR0 COM event by software */
  TMR_GenerateEvent(ETMR0, TMR_EventSource_COM);
}


/**
  * @brief  This function handles ETMR0 Trigger and commutation interrupts
  *   requests.
  * @param  None
  * @retval None
  */
void TMR1_TRG_COM_IRQHandler(void)
{
   /* Clear ETMR0 COM pending bit */
   TMR_ClearITPendingBit(ETMR0, TMR_IT_COM);

  if (step == 1)
  {
    /* Next step: Step 2 Configuration ---------------------------- */
    /*  Channel3 configuration */
    TMR_CCxCmd(ETMR0, TMR_Channel_3, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_3, TMR_CCxN_Disable);

    /*  Channel1 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_1, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_1, TMR_CCx_Enable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_1, TMR_CCxN_Disable);

    /*  Channel2 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_2, TMR_OCMode_PWM1 );
    TMR_CCxCmd(ETMR0, TMR_Channel_2, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_2, TMR_CCxN_Enable);
    step++;
  }
  else if (step == 2)
  {
    /* Next step: Step 3 Configuration ---------------------------- */
    /*  Channel2 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_2, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_2, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_2, TMR_CCxN_Enable);
    
    /*  Channel3 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_3, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_3, TMR_CCx_Enable);
     TMR_CCxNCmd(ETMR0, TMR_Channel_3, TMR_CCxN_Disable);

    /*  Channel1 configuration */
    TMR_CCxCmd(ETMR0, TMR_Channel_1, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_1, TMR_CCxN_Disable);
    step++;
  }
  else if (step == 3)
  {
    /* Next step: Step 4 Configuration ---------------------------- */
    /*  Channel3 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_3, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_3, TMR_CCx_Enable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_3, TMR_CCxN_Disable);

    /*  Channel2 configuration */
    TMR_CCxCmd(ETMR0, TMR_Channel_2, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_2, TMR_CCxN_Disable);

    /*  Channel1 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_1, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_1, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_1, TMR_CCxN_Enable);
    step++;
  }
  else if (step == 4)
  {
    /* Next step: Step 5 Configuration ---------------------------- */
    /*  Channel3 configuration */
    TMR_CCxCmd(ETMR0, TMR_Channel_3, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_3, TMR_CCxN_Disable);

    /*  Channel1 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_1, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_1, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_1, TMR_CCxN_Enable);

    /*  Channel2 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_2, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_2, TMR_CCx_Enable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_2, TMR_CCxN_Disable);
    step++;
  }
  else if (step == 5)
  {
    /* Next step: Step 6 Configuration ---------------------------- */
    /*  Channel3 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_3, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_3, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_3, TMR_CCxN_Enable);

    /*  Channel1 configuration */
    TMR_CCxCmd(ETMR0, TMR_Channel_1, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_1, TMR_CCxN_Disable);

    /*  Channel2 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_2, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_2, TMR_CCx_Enable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_2, TMR_CCxN_Disable);
    step++;
  }
  else
  {
    /* Next step: Step 1 Configuration ---------------------------- */
    /*  Channel1 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_1, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_1, TMR_CCx_Enable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_2, TMR_CCxN_Disable);

    /*  Channel3 configuration */
    TMR_SelectOCxM(ETMR0, TMR_Channel_3, TMR_OCMode_PWM1);
    TMR_CCxCmd(ETMR0, TMR_Channel_3, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_3, TMR_CCxN_Enable);

    /*  Channel2 configuration */
    TMR_CCxCmd(ETMR0, TMR_Channel_2, TMR_CCx_Disable);
    TMR_CCxNCmd(ETMR0, TMR_Channel_2, TMR_CCxN_Disable);
    step = 1;
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
