/**
  ******************************************************************************
  * @file    lib_syscfg1.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   SYSCON1 library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_syscfg.h"

/* Private macro -------------------------------------------------------------*/
/* SYSCFG1_IR_DUTY */
#define SYSCFG1_IR_DUTY_DUTYL_POS          (0UL)
#define SYSCFG1_IR_DUTY_DUTYH_POS          (16UL)
/* SYSCFG1_CLKSEL */
#define SYSCFG1_CLKSEL_UART_SCLKSEL_POS    (11UL)
#define SYSCFG1_CLKSEL_I2C_SCLKSEL_POS     (8UL)
#define SYSCFG1_CLKSEL_I2C_SCLKSEL_MASK    (7UL << SYSCFG1_CLKSEL_I2C_SCLKSEL_POS)
/* SYSCFG1_M0_CFG */
#define SYSCFG1_M0_CFG_IRQLATENCY_POS      (8UL)
#define SYSCFG1_M0_CFG_IRQLATENCY_MASK     (0xFFUL << SYSCFG1_M0_CFG_IRQLATENCY_POS)
#define SYSCFG1_M0_CFG_LOCK_RST_EN         (1UL << 0)

/* SYSCFG1 Unlock */
#define SYSCFG1_UNLOCK()                    SYSCFG1->PASSWD = 0xBEEFBEEFUL

/**
  * @brief  Configures Flash Bank 0 1us tick.
  * @param  SYSCFG1_SysClock: PCLK1 value
  * @retval None
  */
void SYSCFG1_Flash0MicroSecTickConfig(uint32_t SYSCFG1_SysClock)
{
  uint32_t tick_config = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_SYSCLK_VALUE(SYSCFG1_SysClock));
  
  tick_config = SYSCFG1_SysClock / 1000000UL;
  tick_config <<= SYSCON_FLASH_1US_CYCLE_POS;
  
  MODIFY_REG(SYSCFG1->FLASHWC, \
             SYSCON_FLASH_1US_CYCLE_MASK, \
             tick_config);
}

/**
  * @brief  Enables or disables Flash Bank 0 ECC function.
  * @param  NewState: new state of the Flash Bank 0 ECC function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_Flash0ECCCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    CLEAR_BIT(SYSCFG1->FLASHWC, SYSCON_FLASH_ECC_DIS);
  }
  else
  {
    SET_BIT(SYSCFG1->FLASHWC, SYSCON_FLASH_ECC_DIS);
  }
}

/**
  * @brief  Enables or disables Flash Bank 0 Cache ECC function.
  * @param  NewState: new state of the Flash Bank 0 Cache ECC function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_Flash0CacheECCCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    CLEAR_BIT(SYSCFG1->FLASHWC, SYSCON_FLASH_CACHE_ECC_DIS);
  }
  else
  {
    SET_BIT(SYSCFG1->FLASHWC, SYSCON_FLASH_CACHE_ECC_DIS);
  }
}

/**
  * @brief  Enables or disables UART IrDA function.
  * @param  UARTx: UART14 ~ UART19
  * @param  NewState: new state of the UART IrDA function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_UARTIRCmd(UART_Type *UARTx, FunctionalState NewState)
{
  uint32_t uart;
  
  /* Check the parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  uart = UART_GET_INDEX(UARTx);
  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG1->IREN, 1UL << uart);
  }
  else
  {
    CLEAR_BIT(SYSCFG1->IREN, 1UL << uart);
  }
}

/**
  * @brief  Configures UART transmit IrDA duty.
  * @param  DutyHigh: The high pulse width will be (DUTYH + 1)*APBCLK period.
  *          This parameter must be a number between 0 and 0xFFFF.
  * @param  DutyLow: The low pulse width will be (DUTYL + 1)*APBCLK period.
  *          This parameter must be a number between 0 and 0xFFFF.
  * @retval None
  */
void SYSCFG1_UARTIRDutyConfig(uint16_t DutyHigh, uint16_t DutyLow)
{
  uint32_t tmp = ((uint32_t)DutyHigh << SYSCFG1_IR_DUTY_DUTYH_POS) |\
                 ((uint32_t)DutyLow << SYSCFG1_IR_DUTY_DUTYL_POS);
  
  WRITE_REG(SYSCFG1->IR_DUTY, tmp);
}

/**
  * @brief  Enables or disables UART pins function.
  * @param  UARTx: UART14 ~ UART19
  * @param  NewState: new state of the UART pins function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_UARTPinsCmd(UART_Type *UARTx, FunctionalState NewState)
{
  uint32_t uart;
  
  /* Check the parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  uart = UART_GET_INDEX(UARTx);
 
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG1->UARTEN, 1UL << uart);
  }
  else
  {
    CLEAR_BIT(SYSCFG1->UARTEN, 1UL << uart);
  }
}

/**
  * @brief  Enables or disables EGY and CF pulse outputting function.
  * @param  SYSCFG1_EGYx: where x can (0..2) to select the EGY peripheral.
  * @param  NewState: new state of the EGY and CF pulse outputting function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_EGYCmd(uint32_t SYSCFG1_EGYx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG1_EGY(SYSCFG1_EGYx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG1->EGYCFEN, SYSCFG1_EGYx);
  }
  else
  {
    CLEAR_BIT(SYSCFG1->EGYCFEN, SYSCFG1_EGYx);
  }
}

/**
  * @brief  Enables or disables interrupt mask function.
  * @param  SYSCFG1_IntMask: specifies the interrupt to mask or not.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG1_INTMASK_EXTI0 ~ SYSCFG1_INTMASK_EXTI15
  *            @arg SYSCFG1_INTMASK_RTC
  *            @arg SYSCFG1_INTMASK_RTC_ALARM
  *            @arg SYSCFG1_INTMASK_BTMR0
  *            @arg SYSCFG1_INTMASK_BTMR1
  *            @arg SYSCFG1_INTMASK_LPBTMR0
  *            @arg SYSCFG1_INTMASK_LPBTMR1
  *            @arg SYSCFG1_INTMASK_MPMU_CMP
  *            @arg SYSCFG1_INTMASK_SYSCON_LP
  * @param  NewState: new state of the specified interrupt mask.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_IntMaskConfig(uint32_t SYSCFG1_IntMask, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG1_INTMASK(SYSCFG1_IntMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG1->M0_INT_MASK, SYSCFG1_IntMask);
  }
  else
  {
    CLEAR_BIT(SYSCFG1->M0_INT_MASK, SYSCFG1_IntMask);
  }
}

/**
  * @brief  Configures UART clock.
  * @param  UARTx: UART14 ~ UART19
  * @param  SYSCFG1_UART_ClkSel: selects UART clock source.
  *          This parameter can be onen of the following values:
  *            @arg SYSCFG1_UART_CLKSRC_RCH
  *            @arg SYSCFG1_UART_CLKSRC_PLL0
  *            @arg SYSCFG1_UART_CLKSRC_PLL1
  *            @arg SYSCFG1_UART_CLKSRC_XOH
  *            @arg SYSCFG1_UART_CLKSRC_RCHD4
  *            @arg SYSCFG1_UART_CLKSRC_RCHD48
  *            @arg SYSCFG1_UART_CLKSRC_RCL
  *            @arg SYSCFG1_UART_CLKSRC_XOL
  * @param  SYSCFG1_UART_ClkDiv: specifies the division factor for UART clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG1_UARTClockConfig(UART_Type *UARTx, \
                             uint32_t SYSCFG1_UART_ClkSel, \
                             uint32_t SYSCFG1_UART_ClkDiv)
{
  uint32_t uart;
  uint32_t clkdiv_reg_index, clkdiv_cfg_pos, clkdiv_cfg_mask, clkdiv_cfg_set;
  uint32_t clksel_cfg_pos, clksel_cfg_mask, clksel_cfg_set;

  /* Check the parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_SYSCFG1_UART_CLKSRC(SYSCFG1_UART_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG1_UART_ClkDiv));
  
  uart = UART_GET_INDEX(UARTx);
  
  clkdiv_reg_index = uart / 4UL;
  clkdiv_cfg_pos = (uart-(4UL*clkdiv_reg_index)) * 8UL;
  clkdiv_cfg_mask = SYSCON_CLK_DIV_MASK << clkdiv_cfg_pos;
  clkdiv_cfg_set = (SYSCFG1_UART_ClkDiv-1UL) << clkdiv_cfg_pos;
  
  clksel_cfg_pos = 3UL*uart + SYSCFG1_CLKSEL_UART_SCLKSEL_POS;
  clksel_cfg_mask = SYSCFG1_UART_CLKSRC_MASK << clksel_cfg_pos;
  clksel_cfg_set = SYSCFG1_UART_ClkSel << clksel_cfg_pos;
  
  if (clkdiv_reg_index)
    MODIFY_REG(SYSCFG1->UART_SCLK_DIV2, clkdiv_cfg_mask, clkdiv_cfg_set);
  else
    MODIFY_REG(SYSCFG1->UART_SCLK_DIV1, clkdiv_cfg_mask, clkdiv_cfg_set);
  
  SYSCFG1_UNLOCK();
  MODIFY_REG(SYSCFG1->CLKSEL, clksel_cfg_mask, clksel_cfg_set);
}

/**
  * @brief  Enables or disables the peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access or work)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  SYSCFG1_Periph: specifies the peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG1_Periph0Clock_CM0:         CM0 clock
  *            @arg SYSCFG1_Periph0Clock_CRYPTO:      CRYPTO clock
  *            @arg SYSCFG1_Periph0Clock_WAVER:       WAVER clock 
  *            @arg SYSCFG1_Periph0Clock_HFM_COP:     HFM_COP clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_Periph0ClockCmd(uint32_t SYSCFG1_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG1_PERIPH0CLK(SYSCFG1_Periph));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  SYSCFG1_UNLOCK();
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG1->CLKEN1, SYSCFG1_Periph);
  }
  else
  {
    CLEAR_BIT(SYSCFG1->CLKEN1, SYSCFG1_Periph);
  }
}

/**
  * @brief  Enables or disables the peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access or work)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  SYSCFG1_Periph: specifies the peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG1_Periph1Clock_I2C14:       I2C14 clock
  *            @arg SYSCFG1_Periph1Clock_BSPI0:       SPI0 clock
  *            @arg SYSCFG1_Periph1Clock_BSPI1:       SPI1 clock
  *            @arg SYSCFG1_Periph1Clock_BSPI2:       SPI2 clock
  *            @arg SYSCFG1_Periph1Clock_BSPI3:       SPI3 clock
  *            @arg SYSCFG1_Periph1Clock_BSPI4:       SPI4 clock
  *            @arg SYSCFG1_Periph1Clock_BSPI5:       SPI5 clock
  *            @arg SYSCFG1_Periph1Clock_UART14:      UART0 clock
  *            @arg SYSCFG1_Periph1Clock_UART15:      UART1 clock
  *            @arg SYSCFG1_Periph1Clock_UART16:      UART2 clock
  *            @arg SYSCFG1_Periph1Clock_UART17:      UART3 clock
  *            @arg SYSCFG1_Periph1Clock_UART18:      UART4 clock
  *            @arg SYSCFG1_Periph1Clock_UART19:      UART5 clock
  *            @arg SYSCFG1_Periph1Clock_ISO78162:   ISO78160 clock
  *            @arg SYSCFG1_Periph1Clock_ISO78163:   ISO78161 clock
  *            @arg SYSCFG1_Periph1Clock_BTMR_BPWM_GLOBAL:   BTMR0..3 BPWM0..3 global clock
  *            @arg SYSCFG1_Periph1Clock_CRYPTO:     CRYPTO clock
  *            @arg SYSCFG1_Periph1Clock_BTMR4:      BTMR4 clock
  *            @arg SYSCFG1_Periph1Clock_BTMR5:      BTMR5 clock
  *            @arg SYSCFG1_Periph1Clock_BTMR6:      BTMR6 clock
  *            @arg SYSCFG1_Periph1Clock_BTMR7:      BTMR7 clock
  *            @arg SYSCFG1_Periph1Clock_BPWM4:      BPWM4 clock
  *            @arg SYSCFG1_Periph1Clock_BPWM5:      BPWM5 clock
  *            @arg SYSCFG1_Periph1Clock_BPWM6:      BPWM6 clock
  *            @arg SYSCFG1_Periph1Clock_BPWM7:      BPWM7 clock
  *            @arg SYSCFG1_Periph1Clock_WDT2:       WDT2 clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_Periph1ClockCmd(uint32_t SYSCFG1_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG1_PERIPH1CLK(SYSCFG1_Periph));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  SYSCFG1_UNLOCK();
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG1->CLKEN2, SYSCFG1_Periph);
  }
  else
  {
    CLEAR_BIT(SYSCFG1->CLKEN2, SYSCFG1_Periph);
  }
}

/**
  * @brief  Forces peripheral reset and wait until it released.
  * @param  SYSCFG1_Periph: specifies the peripheral to reset.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG1_PeriphReset_BSPI0
  *            @arg SYSCFG1_PeriphReset_BSPI1
  *            @arg SYSCFG1_PeriphReset_BSPI2
  *            @arg SYSCFG1_PeriphReset_BSPI3
  *            @arg SYSCFG1_PeriphReset_BSPI4
  *            @arg SYSCFG1_PeriphReset_BSPI5
  *            @arg SYSCFG1_PeriphReset_UART14
  *            @arg SYSCFG1_PeriphReset_UART15
  *            @arg SYSCFG1_PeriphReset_UART16
  *            @arg SYSCFG1_PeriphReset_UART17
  *            @arg SYSCFG1_PeriphReset_UART18
  *            @arg SYSCFG1_PeriphReset_UART19
  *            @arg SYSCFG1_PeriphReset_I2C14
  *            @arg SYSCFG1_PeriphReset_ISO78162
  *            @arg SYSCFG1_PeriphReset_ISO78163
  *            @arg SYSCFG1_PeriphReset_BTMR_BPWM_GLOBAL
  *            @arg SYSCFG1_PeriphReset_WAVER
  *            @arg SYSCFG1_PeriphReset_HFM_COP
  *            @arg SYSCFG1_PeriphReset_CRYPTO
  *            @arg SYSCFG1_PeriphReset_WDT2
  * @retval None
  */
void SYSCFG1_PeriphReset(uint32_t SYSCFG1_Periph)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG1_PERIPHRST(SYSCFG1_Periph));
  
  SYSCFG1_UNLOCK();
  WRITE_REG(SYSCFG1->SW_RST_REQ, SYSCFG1_Periph);
  while (IS_BIT_SET(SYSCFG1->SW_RST_REQ, SYSCFG1_Periph))
  {
  }
}

/**
  * @brief  Sets the vector table location of CM0.
  * @param  VTOR_Address: Vector Table location
  * @retval None
  */
void SYSCFG1_SetVectorTable(uint32_t VTOR_Address)
{
  WRITE_REG(SYSCFG1->M0_IVT_BADDR, VTOR_Address);
}

/**
  * @brief  Configures CM0 IRQ latency.
  * @param  Latency: 0~255
  * @retval None
  */
void SYSCFG1_IRQLatencyConfig(uint8_t Latency)
{
  MODIFY_REG(SYSCFG1->M0_CFG, \
             SYSCFG1_M0_CFG_IRQLATENCY_MASK, \
             (Latency << SYSCFG1_M0_CFG_IRQLATENCY_POS));
}

/**
  * @brief  Forces or releases CM0 lockup reset function.
  * @param  NewState: new state of CM0 lockup reset function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG1_LockupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG1->M0_CFG, SYSCFG1_M0_CFG_LOCK_RST_EN);
  }
  else
  {
    CLEAR_BIT(SYSCFG1->M0_CFG, SYSCFG1_M0_CFG_LOCK_RST_EN);
  }
}

/**
  * @brief  Configures I2C0 clock.
  * @param  SYSCFG1_I2C_ClkSel: selects I2C0 clock source.
  *          This parameter can be onen of the following values:
  *            @arg SYSCFG1_I2C_CLKSRC_RCH
  *            @arg SYSCFG1_I2C_CLKSRC_PLL0
  *            @arg SYSCFG1_I2C_CLKSRC_PLL1
  *            @arg SYSCFG1_I2C_CLKSRC_XOH
  *            @arg SYSCFG1_I2C_CLKSRC_RCHD4
  *            @arg SYSCFG1_I2C_CLKSRC_RCHD48
  *            @arg SYSCFG1_I2C_CLKSRC_RCL
  *            @arg SYSCFG1_I2C_CLKSRC_XOL
  * @param  SYSCFG1_I2C_ClkDiv: specifies the division factor for I2C0 clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG1_I2CClockConfig(uint32_t SYSCFG1_I2C_ClkSel, uint32_t SYSCFG1_I2C_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG1_I2C_CLKSRC(SYSCFG1_I2C_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG1_I2C_ClkDiv));
  
  WRITE_REG(SYSCFG1->I2C_SCLK_DIV, (SYSCFG1_I2C_ClkDiv-1));
  
  SYSCFG1_UNLOCK();
  MODIFY_REG(SYSCFG1->CLKSEL, \
             SYSCFG1_CLKSEL_I2C_SCLKSEL_MASK, \
             (SYSCFG1_I2C_ClkSel << SYSCFG1_CLKSEL_I2C_SCLKSEL_POS));
}

/**
  * @brief  Configure basic timer clock.
  * @param  SYSCFG1_BasicTMR: specifies the basic timer clock to configures.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG1_BTMR4
  *            @arg SYSCFG1_BTMR5
  *            @arg SYSCFG1_BTMR6
  *            @arg SYSCFG1_BTMR7
  *            @arg SYSCFG1_BPWM4
  *            @arg SYSCFG1_BPWM5
  *            @arg SYSCFG1_BPWM6
  *            @arg SYSCFG1_BPWM7
  * @param  SYSCFG1_BasicTMR_ClkSel: selects the basic timer clock.
  *          This parameter can be one of the following values:
  *            @arg IS_SYSCFG1_BTMR_CLKSRC_RCH
  *            @arg IS_SYSCFG1_BTMR_CLKSRC_PLL0
  *            @arg IS_SYSCFG1_BTMR_CLKSRC_PLL1
  *            @arg IS_SYSCFG1_BTMR_CLKSRC_XOH
  *            @arg IS_SYSCFG1_BTMR_CLKSRC_RCHD4
  *            @arg IS_SYSCFG1_BTMR_CLKSRC_RCHD48
  *            @arg IS_SYSCFG1_BTMR_CLKSRC_RCL
  *            @arg IS_SYSCFG1_BTMR_CLKSRC_XOL
  * @param  SYSCFG1_BasicTMR_ClkDiv: specifies the division factor for basic timer clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG1_BasicTMRClockConfig(uint32_t SYSCFG1_BasicTMR, \
                                 uint32_t SYSCFG1_BasicTMR_ClkSel, \
                                 uint32_t SYSCFG1_BasicTMR_ClkDiv)
{
  uint32_t clksel_cfg_pos, clksel_cfg_mask, clksel_cfg_set;
  uint32_t clkdiv_reg_index, clkdiv_cfg_pos, clkdiv_cfg_mask, clkdiv_cfg_set;
  
  /* Check the parameters */
  assert_parameters(IS_SYSCFG1_BTMR(SYSCFG1_BasicTMR));
  assert_parameters(IS_SYSCFG1_BTMR_CLKSRC(SYSCFG1_BasicTMR_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG1_BasicTMR_ClkDiv));
  
  clkdiv_reg_index = SYSCFG1_BasicTMR / 4UL;
  clkdiv_cfg_pos = (SYSCFG1_BasicTMR - (4UL*clkdiv_reg_index)) * 8UL;
  clkdiv_cfg_mask = SYSCON_CLK_DIV_MASK << clkdiv_cfg_pos;
  clkdiv_cfg_set = (SYSCFG1_BasicTMR_ClkDiv-1UL) << clkdiv_cfg_pos;
  
  clksel_cfg_pos = SYSCFG1_BasicTMR * 4UL;
  clksel_cfg_mask = SYSCFG1_BasicTMR_ClkSel << clksel_cfg_pos;
  clksel_cfg_set = SYSCFG1_BasicTMR_ClkSel << clksel_cfg_pos;
  
  MODIFY_REG(SYSCFG1->TIMER0_DIV[clkdiv_reg_index], \
             clkdiv_cfg_mask, \
             clkdiv_cfg_set);
  
  MODIFY_REG(SYSCFG1->TIMER0_SEL, \
             clksel_cfg_mask, \
             clksel_cfg_set);
}

/*********************************** END OF FILE ******************************/
