/**
  ******************************************************************************
  * @file    lib_syscfglp.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   SYSCFGLP library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_syscfg.h"

/* Private macro -------------------------------------------------------------*/
/* SYSCFGLP_CM0_CTRL */
#define SYSCFGLP_CM0_CTRL_RST                               (1UL << 0)

/**
  * @brief  Forces peripheral reset and wait until it released.
  * @param  SYSCFGLP_Periph: specifies the peripheral to reset.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFGLP_PeriphReset_PMU
  *            @arg SYSCFGLP_PeriphReset_RETRAM
  *            @arg SYSCFGLP_PeriphReset_UART32K0
  *            @arg SYSCFGLP_PeriphReset_UART32K1
  *            @arg SYSCFGLP_PeriphReset_RTC_ALARM
  *            @arg SYSCFGLP_PeriphReset_COMP
  *            @arg SYSCFGLP_PeriphReset_LPBTMR0
  *            @arg SYSCFGLP_PeriphReset_LPBTMR1
  * @retval None
  */
void SYSCFGLP_PeriphReset(uint32_t SYSCFGLP_Periph)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFGLP_PERIPHRST(SYSCFGLP_Periph));
  
  WRITE_REG(SYSCFGLP->SW_RST_REQ, SYSCFGLP_Periph);
  while (IS_BIT_SET(SYSCFGLP->SW_RST_REQ, SYSCFGLP_Periph))
  {
  }
}

/**
  * @brief  Configures WDTs reset behavior.
  * @param  SYSCFGLP_WDTReset: this parameter can be one of the following values:
  *            @arg SYSCFGLP_WDTRST_SINGLE_CORE
  *            @arg SYSCFGLP_WDTRST_TRI_CORE
  *            @arg SYSCFGLP_WDTRST_WHOLE_CHIP
  * @retval None
  */
void SYSCFGLP_WDTResetConfig(uint32_t SYSCFGLP_WDTReset)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFGLP_WDTRST(SYSCFGLP_WDTReset));
  
  WRITE_REG(SYSCFGLP->WDT_RST_CTRL, SYSCFGLP_WDTReset);
}

/**
  * @brief  Enables or disables the peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access or work)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  SYSCFGLP_Periph: specifies the peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFGLP_PeriphClock_RTC:       RTC clock
  *            @arg SYSCFGLP_PeriphClock_RETRAM:    RETRAM clock
  *            @arg SYSCFGLP_PeriphClock_UART32K0:  UART32K0 clock
  *            @arg SYSCFGLP_PeriphClock_UART32K1:  UART32K1clock
  *            @arg SYSCFGLP_PeriphClock_PMU:       PMU clock
  *            @arg SYSCFGLP_PeriphClock_RTC_ALARM: RTC_ALARM clock
  *            @arg SYSCFGLP_PeriphClock_COMP:      COMP clock
  *            @arg SYSCFGLP_PeriphClock_LPBTMR0:   LPBTMR0 clock
  *            @arg SYSCFGLP_PeriphClock_LPBTMR1:   LPBTMR1 clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFGLP_PeriphClockCmd(uint32_t SYSCFGLP_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFGLP_PERIPHCLK(SYSCFGLP_Periph));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFGLP->PCLK_EN, SYSCFGLP_Periph);
  }
  else
  {
    CLEAR_BIT(SYSCFGLP->PCLK_EN, SYSCFGLP_Periph);
  }
}

/**
  * @brief  Forces or releases CM0 reset.
  * @param  NewState: new state of CM0 reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFGLP_CM0ResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState == ENABLE)
  {
    WRITE_REG(SYSCFGLP->CM0_CTRL, SYSCFGLP_CM0_CTRL_RST);
  }
  else
  {
    WRITE_REG(SYSCFGLP->CM0_CTRL, 0UL);
  }
}

/**
  * @brief  Configure APBLP clock.
  * @param  SYSCFGLP_APBLP_ClkSel: selects the APBLP clock.
  *          This parameter can be one of the following values:
  *            @arg SYSCFGLP_APBLP_CLKSRC_RCH
  *            @arg SYSCFGLP_APBLP_CLKSRC_PLL0
  *            @arg SYSCFGLP_APBLP_CLKSRC_PLL1
  *            @arg SYSCFGLP_APBLP_CLKSRC_XOH
  *            @arg SYSCFGLP_APBLP_CLKSRC_RCHD4
  *            @arg SYSCFGLP_APBLP_CLKSRC_RCHD48
  *            @arg SYSCFGLP_APBLP_CLKSRC_RCL
  *            @arg SYSCFGLP_APBLP_CLKSRC_XOL
  * @param  SYSCFGLP_APBLP_ClkDiv: specifies the division factor for APBLP clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFGLP_APBLPClockConfig(uint32_t SYSCFGLP_APBLP_ClkSel, \
                               uint32_t SYSCFGLP_APBLP_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFGLP_APBLP_CLKSRC(SYSCFGLP_APBLP_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFGLP_APBLP_ClkDiv));
  
  MODIFY_REG(SYSCFGLP->CLK_SEL, \
    SYSCFGLP_APBLP_CLKSRC_MASK, \
    SYSCFGLP_APBLP_ClkSel);
  
  MODIFY_REG(SYSCFGLP->CLK_DIV, \
    SYSCFGLP_APBLP_CLKDIV_MASK, \
    SYSCFGLP_APBLP_ClkDiv << SYSCFGLP_APBLP_CLKDIV_POS);
}

/**
  * @brief  Configure PMU clock.
  * @param  SYSCFGLP_PMU_ClkSel: selects the PMU clock.
  *          This parameter can be one of the following values:
  *            @arg SYSCFGLP_PMU_CLKSRC_RCH
  *            @arg SYSCFGLP_PMU_CLKSRC_PLL0
  *            @arg SYSCFGLP_PMU_CLKSRC_PLL1
  *            @arg SYSCFGLP_PMU_CLKSRC_XOH
  *            @arg SYSCFGLP_PMU_CLKSRC_RCHD4
  *            @arg SYSCFGLP_PMU_CLKSRC_RCHD48
  *            @arg SYSCFGLP_PMU_CLKSRC_RCL
  *            @arg SYSCFGLP_PMU_CLKSRC_XOL
  * @param  SYSCFGLP_PMU_ClkDiv: specifies the division factor for APBLP clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFGLP_PMUClockConfig(uint32_t SYSCFGLP_PMU_ClkSel, \
                               uint32_t SYSCFGLP_PMU_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFGLP_PMU_CLKSRC(SYSCFGLP_PMU_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFGLP_PMU_ClkDiv));
  
  MODIFY_REG(SYSCFGLP->CLK_SEL, \
    SYSCFGLP_PMU_CLKSRC_MASK, \
    SYSCFGLP_PMU_ClkSel);
  
  MODIFY_REG(SYSCFGLP->CLK_DIV, \
    SYSCFGLP_PMU_CLKDIV_MASK, \
    SYSCFGLP_PMU_ClkDiv << SYSCFGLP_PMU_CLKDIV_POS);
}

/*********************************** END OF FILE ******************************/
