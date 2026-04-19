/**
  ******************************************************************************
  * @file    lib_std.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   STD module driver.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_std.h"
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
#include "misc.h"
#endif

/** @defgroup STD_Exported_Variables STD Exported Variables
  * @{
  */
__IO uint32_t nTick;

/**
  * @brief  Configure the time base source, NVIC and any required global low level hardware
  *         by calling the STD_lowInit() callback function to be optionally defined in user file.
  *
  * @note   STD_Init() function is called at the beginning of program after reset and before
  *         the clock configuration.
  *
  * @note   In the default implementation the System Timer (Systick) is used as source of time base.
  *         Once done, time base tick starts incrementing: the tick variable counter is incremented
  *         each 1ms in the SysTick_Handler() interrupt handler.
  *
  * @retval STD status
  */
STD_StatusType STD_Init(uint32_t SysClock)
{
  STD_StatusType status = STD_OK;
  
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
  
  /* Set Interrupt Group Priority */
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);
  
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */
  
  if (STD_InitTick(SysClock, TICK_INT_PRIORITY) != STD_OK)
  {
    status = STD_ERROR;
  }
  else
  {
    STD_lowInit();
  }
  
  /* Return function status */
  return status;
}

/**
  * @brief This function configures the source of the time base:
  *        The time source is configured to have 1ms time base with a dedicated
  *        Tick interrupt priority.
  * @note  The function is declared as __weak  to be overwritten  in case of other
  *       implementation  in user file.
  * @param SysClock Current system clock value.
  * @param TickPriority  Tick interrupt priority.
  * @retval STD status
  */
__weak STD_StatusType STD_InitTick(uint32_t SysClock, uint32_t TickPriority)
{
  STD_StatusType status = STD_OK;
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
  uint32_t prioritygroup;
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */
  
  /*Configure the SysTick to have interrupt in 1ms time basis*/
  if ((uint32_t)SysClock != 0UL)
  {
    if (SysTick_Config(SysClock/1000UL - 1UL) == 0UL)
    {
      /* Configure the SysTick IRQ priority */
      if (TickPriority < (1UL << __NVIC_PRIO_BITS))
      {
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
        prioritygroup = NVIC_GetPriorityGrouping();
        NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(prioritygroup, TickPriority, 0UL));
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */
#if defined (V32F20XXX_CM0_CORE)
        NVIC_SetPriority(SysTick_IRQn, TickPriority);
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */
      }
      else
      {
        status = STD_ERROR;
      }
    }
  }

  /* Return function status */
  return status;
}

/**
  * @brief Deinitializes Tick.
  * @note  The function is declared as __weak  to be overwritten  in case of other
  *       implementation  in user file.
  * @param None
  * @retval None
  */
__weak void STD_DeInitTick(void)
{
  SysTick->CTRL = 0UL;
}

/**
  * @brief This function is called to increment a global variable "nTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as __weak to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
__weak void STD_IncTick(void)
{
  nTick++;
}

/**
  * @brief Provide a tick value in millisecond.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
__weak uint32_t STD_GetTick(void)
{
  return nTick;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where nTick
  *       is incremented.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay  specifies the delay time length, in milliseconds.
  * @retval None
  */
__weak void STD_Delay(uint32_t Delay)
{
  uint32_t tickstart = STD_GetTick();
  uint32_t wait = Delay;

  /* Add a period to guaranty minimum wait */
  if (wait < STD_MAX_DELAY)
  {
    wait++;
  }

  while ((STD_GetTick() - tickstart) < wait)
  {
  }
}

/**
  * @brief  Initialize the Low level.
  * @retval None
  */
__weak void STD_lowInit(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the STD_lowInit could be implemented in the user file
   */
}

/*********************************** END OF FILE ******************************/
