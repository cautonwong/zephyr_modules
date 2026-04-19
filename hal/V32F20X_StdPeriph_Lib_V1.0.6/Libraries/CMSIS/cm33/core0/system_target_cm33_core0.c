/**
  ******************************************************************************
  * @file    system_target_cm33.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   system source file.
  * @attention
  *
  ******************************************************************************
  */
#include "system_target_cm33_core0.h"
#include "board.h"

/**
  * @brief  Setup the microcontroller system
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */
#endif
  
}

/**
  * @brief  Initializes registers.
  * @param  None
  * @retval None
  */
void SystemUpdate(void)
{
}

/*********************************** END OF FILE ******************************/
