/**
  ******************************************************************************
  * @file    lib_ramfunc.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-04-14
  * @brief   RAM function library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_ramfunc.h"
#include "lib_flash.h"

/**
  * @brief  Power on or power off Flash.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @param  NewState: new state of the specified Flash power.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
__RAM_FUNC void FLASH_PowerCmd(FLASH_Type *FLASHx, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState == ENABLE)
  {
    FLASHx->SFC_POWRER_CFG = FLASH_POWERREADY_ON;
  }
  else
  {
    FLASHx->SFC_POWRER_CFG = FLASH_POWER_OFF;
  }
}
/*********************************** END OF FILE ******************************/
