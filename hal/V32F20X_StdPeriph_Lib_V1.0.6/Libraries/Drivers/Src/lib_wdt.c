/**
  ******************************************************************************
  * @file    lib_wdt.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   WDT library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_wdt.h"

/* Private macro -------------------------------------------------------------*/
/* WDT_CTRL */
#define WDT_CTRL_EN                            (1UL << 0)

/* WDT_CTRL_KEY */
#define WDT_CTRL_KEY_MASK                      (0xFFFF0000UL)
#define WDT_CTRL_KEY                           (0xAA550000UL)
/* WDT_WIN_KEY */
#define WDT_WIN_KEY                            (0xAA550000UL)
/* WDT_CLR_KEY */
#define WDT_CLR_KEY                            (0x55AA0000UL)

/**
  * @brief  Enables or disables WDT timer.
  * @param  WDTx: specifies the WDT to configure.
  *          This parameter can be one of the following values:
  *            @arg WDT0
  *            @arg WDT1
  *            @arg WDT2
  * @param  NewState: new state of the specified WDT.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WDT_Cmd(WDT_Type *WDTx, FunctionalState NewState)
{
  uint32_t tmp;
  
  /* Check the parameters */
  assert_parameters(IS_WDT_ALL_PERIPH(WDTx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = READ_REG(WDTx->CTRL);
  MODIFY_REG(tmp, WDT_CTRL_KEY_MASK, WDT_CTRL_KEY);
  
  if (NewState == ENABLE)
  {
    SET_BIT(tmp, WDT_CTRL_EN);
    WRITE_REG(WDTx->CTRL, tmp);
  }
  else
  {
    CLEAR_BIT(tmp, WDT_CTRL_EN);
    WRITE_REG(WDTx->CTRL, tmp);
  }
}

/**
  * @brief  Configures WDT period value.
  * @param  WDTx: specifies the WDT to configure.
  *          This parameter can be one of the following values:
  *            @arg WDT0
  *            @arg WDT1
  *            @arg WDT2
  * @param  WDT_Period: selects the period to configure.
  *          This parameter can be one of the following values:
  *            @arg WDT_PERIOD_2S:   2 seconds period
  *            @arg WDT_PERIOD_4S:   4 seconds period
  *            @arg WDT_PERIOD_8S:   8 seconds period
  *            @arg WDT_PERIOD_16S:  16 seconds period
  * @retval None
  */
void WDT_PeriodConfig(WDT_Type *WDTx, uint32_t WDT_Period)
{
  uint32_t tmp;
  
  /* Check the parameters */
  assert_parameters(IS_WDT_ALL_PERIPH(WDTx));
  assert_parameters(IS_WDT_PERIOD(WDT_Period));
  
  tmp = READ_REG(WDTx->CTRL);
  MODIFY_REG(tmp, WDT_CTRL_KEY_MASK, WDT_CTRL_KEY);
  MODIFY_REG(tmp, WDT_PERIOD_MASK, WDT_Period);
  WRITE_REG(WDTx->CTRL, tmp);
}

/**
  * @brief  Configures WDT window value.
  * @note   When window value is 0, the window function be disabled.
  * @param  WDTx: specifies the WDT to configure.
  *          This parameter can be one of the following values:
  *            @arg WDT0
  *            @arg WDT1
  *            @arg WDT2
  * @param  WDT_WinValue: the window value to configure.
  *          This parameter must be a number between 0 and 0xFFFF.
  * @retval None
  */
void WDT_WinValueConfig(WDT_Type *WDTx, uint16_t WDT_WinValue)
{
  /* Check the parameters */
  assert_parameters(IS_WDT_ALL_PERIPH(WDTx));
  
  WRITE_REG(WDTx->WIN, WDT_WIN_KEY | (uint32_t)WDT_WinValue);
}

/**
  * @brief  Clears WDT timer value.
  * @param  WDTx: specifies the WDT to configure.
  *          This parameter can be one of the following values:
  *            @arg WDT0
  *            @arg WDT1
  *            @arg WDT2
  * @retval None
  */
void WDT_Clear(WDT_Type *WDTx)
{
  /* Check the parameters */
  assert_parameters(IS_WDT_ALL_PERIPH(WDTx));
  
  WRITE_REG(WDTx->CLR, WDT_CLR_KEY);
}

/**
  * @brief  Gets WDT timer value.
  * @param  WDTx: specifies the WDT to configure.
  *          This parameter can be one of the following values:
  *            @arg WDT0
  *            @arg WDT1
  *            @arg WDT2
  * @retval None
  */
uint16_t WDT_GetCounterValue(WDT_Type *WDTx)
{
  return (uint16_t)READ_REG(WDTx->CLR);
}

/*********************************** END OF FILE ******************************/
