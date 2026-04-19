/**
  ******************************************************************************
  * @file    lib_syscfg0.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   SYSCFG0 library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_syscfg.h"

/* Private macro -------------------------------------------------------------*/
/* SYSCFG0_SW_CM33_1_RST */
#define SYSCFG0_SW_CM33_1_RST_RST         (1UL << 0)
/* SYSCFG0_CM33_WAIT */
#define SYSCFG0_CM33_WAIT_CORE1           (1UL << 16)
/* SYSCFG0_CM33_LOCK_RSTEN */
#define SYSCFG0_CM33_LOCK_RSTEN_CORE0     (1UL << 0)
#define SYSCFG0_CM33_LOCK_RSTEN_CORE1     (1UL << 16)
/* SYSCFG0_CADC_TRG_SEL */
#define SYSCFG0_ADC_TRG_SEL_INJ           (1UL << 0)
#define SYSCFG0_ADC_TRG_SEL_REG           (1UL << 1)
/* SYSCFG0_FC_I2S_SEL */
#define SYSCFG0_FC_I2S_SEL_I2S0           (1UL << 0)
#define SYSCFG0_FC_I2S_SEL_I2S1           (1UL << 1)
#define SYSCFG0_FC_I2S_SEL_FC0_UARTRX_DIS_POS  (4UL)
#define SYSCFG0_FC_I2S_SEL_UART_RXDIS0    (1UL << 4)
/* SYSCFG0_DBG_CFG */
#define SYSCFG0_DBG_CFG_DBGEN             (1UL << 0)
/* SYSCFG0_DMA_REQ */
#define SYSCFG0_DMA_REQ_MASK              (0xFFUL)
/* SYSCFG0_DUAL_BANK_CFG */
#define SYSCFG0_DUAL_BANK_SW              (1UL << 0)

/* SYSCFG0 Unlock */
#define SYSCFG0_UNLOCK()                  SYSCFG0->SYSCON_PASSWD = 0xBEEFBEEFUL
/* SYSCFG0 deep-sleep/sleep key */
#define SYSCFG0_SLP_DSLP_KEY              (0x55AAAA55UL)

/* Private constants ---------------------------------------------------------*/
/* OSPI XIP mode/clock divider/clock source configuration */
static const SYSCFG0_CfgType SYSCFG0_OSPI_Cfg[] = 
{
  { 0UL,  (1UL<<0) },
  { 16UL, (1UL<<16) }
};
/* I2S clock source configuration */
static const SYSCFG0_CfgType SYSCFG0_I2S_ClkSrc_Cfg[] = 
{
  { 0UL, (7UL<<0) },
  { 4UL, (7UL<<4) }
};
/* I2S clock divider configuration */
static const SYSCFG0_CfgType SYSCFG0_I2S_ClkDiv_Cfg[] = 
{
  { 0UL, (0xFFUL<<0) },
  { 8UL, (0xFFUL<<8) }
};
/* I2S MCK output configuration */
static const SYSCFG0_CfgType SYSCFG0_I2S_MCK_OutEn_Cfg[] = 
{
  { 8UL,  (1UL<<8) },
  { 17UL, (1UL<<17) }
};
/* I2S MCK divider configuration */
static const SYSCFG0_CfgType SYSCFG0_I2S_MCK_Div_Cfg[] = 
{
  { 0UL, (0xFFUL<<0) },
  { 9UL, (0xFFUL<<9) }
};
/* SDIO MCK divider configuration */
static const SYSCFG0_CfgType SYSCFG0_SDIO_ClkSrc_Cfg[] = 
{
  { 0UL, (0x7UL<<0) },
  { 16UL, (0x7UL<<16) }
};
/* SDIO clock source configuration */
static const SYSCFG0_CfgType SYSCFG0_SDIO_ClkDiv_Cfg[] = 
{
  { 3UL, (0xFFUL<<3) },
  { 19UL, (0xFFUL<<19) }
};
/**
  * @brief  Configures Flash Bank A 1us tick.
  * @param  SYSCFG0_SysClock: HCLK0 value
  * @retval None
  */
void SYSCFG0_FlashAMicroSecTickConfig(uint32_t SYSCFG0_SysClock)
{
  uint32_t tick_config = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_SYSCLK_VALUE(SYSCFG0_SysClock));
  
  tick_config = SYSCFG0_SysClock / 1000000UL;
  tick_config <<= SYSCON_FLASH_1US_CYCLE_POS;
  
  MODIFY_REG(SYSCFG0->FLASHA_CTRL, \
             SYSCON_FLASH_1US_CYCLE_MASK, \
             tick_config);
}

/**
  * @brief  Configures Flash Bank B 1us tick.
  * @param  SYSCFG0_SysClock: HCLK0 value
  * @retval None
  */
void SYSCFG0_FlashBMicroSecTickConfig(uint32_t SYSCFG0_SysClock)
{
  uint32_t tick_config = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_SYSCLK_VALUE(SYSCFG0_SysClock));
  
  tick_config = SYSCFG0_SysClock / 1000000UL;
  tick_config <<= SYSCON_FLASH_1US_CYCLE_POS;
  
  MODIFY_REG(SYSCFG0->FLASHB_CTRL, \
             SYSCON_FLASH_1US_CYCLE_MASK, \
             tick_config);
}

/**
  * @brief  Enables or disables Flash Bank A ECC function.
  * @param  NewState: new state of the Flash Bank A ECC function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_FlashAECCCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    CLEAR_BIT(SYSCFG0->FLASHA_CTRL, SYSCON_FLASH_ECC_DIS);
  }
  else
  {
    SET_BIT(SYSCFG0->FLASHA_CTRL, SYSCON_FLASH_ECC_DIS);
  }
}

/**
  * @brief  Switchs FLASHA and FLASHB function.
  * @param  None
  * @retval None
  */
void SYSCFG0_FlashSwitch(void)
{
  SYSCFG0_UNLOCK();
  NOR_BIT(SYSCFG0->FLASH_DUAL_BANK_SW, SYSCFG0_DUAL_BANK_SW);
}

/**
  * @brief  Enables or disables Flash Bank B ECC function.
  * @param  NewState: new state of the Flash Bank B ECC function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_FlashBECCCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    CLEAR_BIT(SYSCFG0->FLASHB_CTRL, SYSCON_FLASH_ECC_DIS);
  }
  else
  {
    SET_BIT(SYSCFG0->FLASHB_CTRL, SYSCON_FLASH_ECC_DIS);
  }
}

/**
  * @brief  Enables or disables Flash Bank A Cache ECC function.
  * @param  NewState: new state of the Flash Bank A Cache ECC function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_FlashACacheECCCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    CLEAR_BIT(SYSCFG0->FLASHA_CTRL, SYSCON_FLASH_CACHE_ECC_DIS);
  }
  else
  {
    SET_BIT(SYSCFG0->FLASHA_CTRL, SYSCON_FLASH_CACHE_ECC_DIS);
  }
}

/**
  * @brief  Enables or disables Flash Bank B Cache ECC function.
  * @param  NewState: new state of the Flash Bank B Cache ECC function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_FlashBCacheECCCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    CLEAR_BIT(SYSCFG0->FLASHB_CTRL, SYSCON_FLASH_CACHE_ECC_DIS);
  }
  else
  {
    SET_BIT(SYSCFG0->FLASHB_CTRL, SYSCON_FLASH_CACHE_ECC_DIS);
  }
}

/**
  * @brief  Configures CM33 core1 boot address.
  * @param  SYSCFG0_Core1Addr: CM33 core1 boot address
  * @retval None
  */
void SYSCFG0_Core1BootAddrConfig(uint32_t SYSCFG0_Core1Addr)
{
  WRITE_REG(SYSCFG0->CM33_SUBBOOT_NSEC_ADDR, SYSCFG0_Core1Addr>>7UL);
}

/**
  * @brief  Forces or releases CM33 core1 reset.
  * @param  NewState: new state of CM33 core1 reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_Core1ResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  SYSCFG0_UNLOCK();
  
  if (NewState == ENABLE)
  {
    WRITE_REG(SYSCFG0->SW_CM33_1_RST, SYSCFG0_SW_CM33_1_RST_RST);
  }
  else
  {
    WRITE_REG(SYSCFG0->SW_CM33_1_RST, 0UL);
  }
}

/**
  * @brief  Forces or releases CM33 core1 wait.
  * @param  NewState: new state of CM33 core1 wait.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_Core1WaitCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG0->CM33_WAIT, SYSCFG0_CM33_WAIT_CORE1);
  }
  else
  {
    CLEAR_BIT(SYSCFG0->CM33_WAIT, SYSCFG0_CM33_WAIT_CORE1);
  }
}

/**
  * @brief  Configures CM0 master Secure/Privilege transfer mode.
  * @param  SYSCFG0_CM0Config: specifies CM0 master transfer mode.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_CM0_SEC_PRIV: Secure and Privilege
  *            @arg SYSCFG0_CM0_SEC_UNPRIV: Secure and Unprivilege
  *            @arg SYSCFG0_CM0_NONSEC_PRIV: Non-Secure and Privilege
  *            @arg SYSCFG0_CM0_NONSEC_UNPRIV: Non-Secure and Unprivilege
  * @retval None
  */
void SYSCFG0_CM0SecurePrivConfig(uint32_t SYSCFG0_CM0Config)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(SYSCFG0_CM0Config));
  
  SYSCFG0_UNLOCK();
  WRITE_REG(SYSCFG0->CM0_NONSEC_CFG, 0);
  SYSCFG0_UNLOCK();
  WRITE_REG(SYSCFG0->CM0_NONSEC_CFG, SYSCFG0_CM0Config);
}

/**
  * @brief  Forces peripheral reset and wait until it released.
  * @param  SYSCFG0_Periph: specifies the APB1 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG0_Periph0Reset_EADC
  *            @arg SYSCFG0_Periph0Reset_SDIO1
  *            @arg SYSCFG0_Periph0Reset_SDIO0
  *            @arg SYSCFG0_Periph0Reset_I2S1
  *            @arg SYSCFG0_Periph0Reset_WDT1
  *            @arg SYSCFG0_Periph0Reset_WDT0
  *            @arg SYSCFG0_Periph0Reset_DAC
  *            @arg SYSCFG0_Periph0Reset_ISO78161
  *            @arg SYSCFG0_Periph0Reset_ISO78160
  *            @arg SYSCFG0_Periph0Reset_CAN1
  *            @arg SYSCFG0_Periph0Reset_CAN0
  *            @arg SYSCFG0_Periph0Reset_SCR
  *            @arg SYSCFG0_Periph0Reset_WAVER33
  *            @arg SYSCFG0_Periph0Reset_MAC1
  *            @arg SYSCFG0_Periph0Reset_MAC0
  *            @arg SYSCFG0_Periph0Reset_I2S0
  *            @arg SYSCFG0_Periph0Reset_OSPI1
  *            @arg SYSCFG0_Periph0Reset_OSPI0
  *            @arg SYSCFG0_Periph0Reset_CRC
  *            @arg SYSCFG0_Periph0Reset_ENCENG
  *            @arg SYSCFG0_Periph0Reset_USBFS
  *            @arg SYSCFG0_Periph0Reset_USBHS
  *            @arg SYSCFG0_Periph0Reset_CRYPTCOP
  * @retval None
  */
void SYSCFG0_Periph0Reset(uint32_t SYSCFG0_Periph)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_PERIPH0RST(SYSCFG0_Periph));
  
  SYSCFG0_UNLOCK();
  WRITE_REG(SYSCFG0->SW_RST0_REQ, SYSCFG0_Periph);
  while (IS_BIT_SET(SYSCFG0->SW_RST0_REQ, SYSCFG0_Periph))
  {
  }
}

/**
  * @brief  Forces peripheral reset and wait until it released.
  * @param  SYSCFG0_Periph: specifies the APB1 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG0_Periph1Reset_DMA1
  *            @arg SYSCFG0_Periph1Reset_DMA0
  *            @arg SYSCFG0_Periph1Reset_RNG
  *            @arg SYSCFG0_Periph1Reset_CMDA_ADC
  *            @arg SYSCFG0_Periph1Reset_ADC
  *            @arg SYSCFG0_Periph1Reset_GTMR3
  *            @arg SYSCFG0_Periph1Reset_GTMR2
  *            @arg SYSCFG0_Periph1Reset_GTMR1
  *            @arg SYSCFG0_Periph1Reset_GTMR0
  *            @arg SYSCFG0_Periph1Reset_ETMR1
  *            @arg SYSCFG0_Periph1Reset_ETMR0
  *            @arg SYSCFG0_Periph1Reset_BTMR0_3
  *            @arg SYSCFG0_Periph1Reset_FC13
  *            @arg SYSCFG0_Periph1Reset_FC12
  *            @arg SYSCFG0_Periph1Reset_FC11
  *            @arg SYSCFG0_Periph1Reset_FC10
  *            @arg SYSCFG0_Periph1Reset_FC9 
  *            @arg SYSCFG0_Periph1Reset_FC8 
  *            @arg SYSCFG0_Periph1Reset_FC7 
  *            @arg SYSCFG0_Periph1Reset_FC6 
  *            @arg SYSCFG0_Periph1Reset_FC5 
  *            @arg SYSCFG0_Periph1Reset_FC4 
  *            @arg SYSCFG0_Periph1Reset_FC3 
  *            @arg SYSCFG0_Periph1Reset_FC2 
  *            @arg SYSCFG0_Periph1Reset_FC1 
  *            @arg SYSCFG0_Periph1Reset_FC0
  * @retval None
  */
void SYSCFG0_Periph1Reset(uint32_t SYSCFG0_Periph)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_PERIPH1RST(SYSCFG0_Periph));
  
  SYSCFG0_UNLOCK();
  WRITE_REG(SYSCFG0->SW_RST1_REQ, SYSCFG0_Periph);
  while (IS_BIT_SET(SYSCFG0->SW_RST1_REQ, SYSCFG0_Periph))
  {
  }
}

/**
  * @brief  Enables or disables the peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access or work)
  *         is disabled and the application software has to enable this clock before 
  *         using it.   
  * @param  SYSCFG0_Periph: specifies the peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG0_Periph0Clock_DMA1:       DMA1 clock
  *            @arg SYSCFG0_Periph0Clock_DMA0:       DMA0 clock 
  *            @arg SYSCFG0_Periph0Clock_DCMI:       DCMI clock
  *            @arg SYSCFG0_Periph0Clock_OSPI1:      OSPI1 clock
  *            @arg SYSCFG0_Periph0Clock_OSPI0:      OSPI0 clock
  *            @arg SYSCFG0_Periph0Clock_CRC:        CRC & Fast IO clock
  *            @arg SYSCFG0_Periph0Clock_SDIO1:      SDIO1 clock
  *            @arg SYSCFG0_Periph0Clock_SDIO0:      SDIO0 clock
  *            @arg SYSCFG0_Periph0Clock_CRYPTCOP:   CRYPTCOP clock
  *            @arg SYSCFG0_Periph0Clock_USBFS:      USBFS clock
  *            @arg SYSCFG0_Periph0Clock_USBHS:      USBHS clock
  *            @arg SYSCFG0_Periph0Clock_ENCENG:     ENCENG clock
  *            @arg SYSCFG0_Periph0Clock_MAC1:       MAC1 clock
  *            @arg SYSCFG0_Periph0Clock_MAC0:       MAC0 clock
  *            @arg SYSCFG0_Periph0Clock_CORE1:      CM33 core1 clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_Periph0ClockCmd(uint32_t SYSCFG0_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_PERIPH0CLK(SYSCFG0_Periph));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  SYSCFG0_UNLOCK();
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG0->CLK_EN1, SYSCFG0_Periph);
  }
  else
  {
    CLEAR_BIT(SYSCFG0->CLK_EN1, SYSCFG0_Periph);
  }
}

/**
  * @brief  Enables or disables the peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access or work)
  *         is disabled and the application software has to enable this clock before 
  *         using it.   
  * @param  SYSCFG0_Periph: specifies the peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG0_Periph1Clock_CDMA_ADC:       CDMA_ADC clock
  *            @arg SYSCFG0_Periph1Clock_WDT1:           WDT1 clock
  *            @arg SYSCFG0_Periph1Clock_WDT0:           WDT0 clock
  *            @arg SYSCFG0_Periph1Clock_WAVER33:        WAVER33 clock
  *            @arg SYSCFG0_Periph1Clock_SCR:            SCR clock
  *            @arg SYSCFG0_Periph1Clock_EADC:           EADC clock
  *            @arg SYSCFG0_Periph1Clock_DAC:            DAC clock
  *            @arg SYSCFG0_Periph1Clock_RNG:            RNG clock
  *            @arg SYSCFG0_Periph1Clock_ISO78161:       ISO78161 clock
  *            @arg SYSCFG0_Periph1Clock_ISO78160:       ISO78160 clock
  *            @arg SYSCFG0_Periph1Clock_ADC:            ADC clock
  *            @arg SYSCFG0_Periph1Clock_I2S1:           I2S1 clock
  *            @arg SYSCFG0_Periph1Clock_I2S0:           I2S0 clock
  *            @arg SYSCFG0_Periph1Clock_CAN1:           CAN1 clock
  *            @arg SYSCFG0_Periph1Clock_CAN0:           CAN0 clock
  *            @arg SYSCFG0_Periph1Clock_FC13:           FC13 clock
  *            @arg SYSCFG0_Periph1Clock_FC12:           FC12 clock
  *            @arg SYSCFG0_Periph1Clock_FC11:           FC11 clock
  *            @arg SYSCFG0_Periph1Clock_FC10:           FC10 clock
  *            @arg SYSCFG0_Periph1Clock_FC9:            FC9 clock
  *            @arg SYSCFG0_Periph1Clock_FC8:            FC8 clock
  *            @arg SYSCFG0_Periph1Clock_FC7:            FC7 clock
  *            @arg SYSCFG0_Periph1Clock_FC6:            FC6 clock
  *            @arg SYSCFG0_Periph1Clock_FC5:            FC5 clock
  *            @arg SYSCFG0_Periph1Clock_FC4:            FC4 clock
  *            @arg SYSCFG0_Periph1Clock_FC3:            FC3 clock
  *            @arg SYSCFG0_Periph1Clock_FC2:            FC2 clock
  *            @arg SYSCFG0_Periph1Clock_FC1:            FC1 clock
  *            @arg SYSCFG0_Periph1Clock_FC0:            FC0 clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_Periph1ClockCmd(uint32_t SYSCFG0_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_PERIPH1CLK(SYSCFG0_Periph));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  SYSCFG0_UNLOCK();
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG0->CLK_EN2, SYSCFG0_Periph);
  }
  else
  {
    CLEAR_BIT(SYSCFG0->CLK_EN2, SYSCFG0_Periph);
  }
}

/**
  * @brief  Enables or disables the Timer clock.
  * @note   After reset, the Timer clock (used for registers read/write access or work)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  SYSCFG0_TMRClock: specifies the Timer function to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG0_TMRCLK_BPWM3
  *            @arg SYSCFG0_TMRCLK_BPWM2
  *            @arg SYSCFG0_TMRCLK_BPWM1
  *            @arg SYSCFG0_TMRCLK_BPWM0
  *            @arg SYSCFG0_TMRCLK_BTMR3
  *            @arg SYSCFG0_TMRCLK_BTMR2
  *            @arg SYSCFG0_TMRCLK_BTMR1
  *            @arg SYSCFG0_TMRCLK_BTMR0
  *            @arg SYSCFG0_TMRCLK_GTMR3
  *            @arg SYSCFG0_TMRCLK_GTMR2
  *            @arg SYSCFG0_TMRCLK_GTMR1
  *            @arg SYSCFG0_TMRCLK_GTMR0
  *            @arg SYSCFG0_TMRCLK_ETMR1
  *            @arg SYSCFG0_TMRCLK_ETMR0
  *            @arg SYSCFG0_TMRCLK_BTMR_BPWM_GLOBAL
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_TMRClockCmd(uint32_t SYSCFG0_TMRClock, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_TMRCLK(SYSCFG0_TMRClock));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  SYSCFG0_UNLOCK();
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG0->PCLK_EN_TMR, SYSCFG0_TMRClock);
  }
  else
  {
    CLEAR_BIT(SYSCFG0->PCLK_EN_TMR, SYSCFG0_TMRClock);
  }
}

/**
  * @brief  CM33 system enters sleep mode.
  * @param  None
  * @retval None
  */
void SYSCFG0_EnterSleepMode(void)
{
  SYSCFG0_UNLOCK();
  WRITE_REG(SYSCFG0->CM33_SYS_SLEEPEN, SYSCFG0_SLP_DSLP_KEY);
}

/**
  * @brief  CM33 system enters deep sleep mode.
  * @param  None
  * @retval None
  */
void SYSCFG0_EnterDeepSleepMode(void)
{
  SYSCFG0_UNLOCK();
  WRITE_REG(SYSCFG0->CM33_SYS_DSLEEPEN, SYSCFG0_SLP_DSLP_KEY);
}

/**
  * @brief  Forces or releases CM33 core0 lockup reset function.
  * @param  NewState: new state of CM33 core0 lockup reset function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_Core0LockupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG0->CM33_LOCK_RST_EN, SYSCFG0_CM33_LOCK_RSTEN_CORE0);
  }
  else
  {
    CLEAR_BIT(SYSCFG0->CM33_LOCK_RST_EN, SYSCFG0_CM33_LOCK_RSTEN_CORE0);
  }
}

/**
  * @brief  Forces or releases CM33 core1 lockup reset function.
  * @param  NewState: new state of CM33 core1 lockup reset function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_Core1LockupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG0->CM33_LOCK_RST_EN, SYSCFG0_CM33_LOCK_RSTEN_CORE1);
  }
  else
  {
    CLEAR_BIT(SYSCFG0->CM33_LOCK_RST_EN, SYSCFG0_CM33_LOCK_RSTEN_CORE1);
  }
}

/**
  * @brief  Enables or disables OSPI XIP mode.
  * @param  OSPIx: specifies the OSPIx XIP mode to configures.
  *          This parameter can be: OSPI0 or OSPI1
  * @param  NewState: new state of OSPIx XIP mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_OSPIXIPCmd(OSPI_Type* OSPIx, FunctionalState NewState)
{
  uint32_t ssi;
  
  /* Check the parameters */
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  ssi = OSPI_GET_INDEX(OSPIx);

  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG0->OSPI_CTRL, SYSCFG0_OSPI_Cfg[ssi].SYSCFG0_CfgMask);
  }
  else
  {
    CLEAR_BIT(SYSCFG0->OSPI_CTRL, SYSCFG0_OSPI_Cfg[ssi].SYSCFG0_CfgMask);
  }
}

/**
  * @brief  Configure OSPIx clock.
  * @param  OSPI_Type: specifies the OSPIx to configures.
  *          This parameter can be: OSPI0 or OSPI1
  * @param  SYSCFG0_OSPI_ClkSel: selects the OSPIx clock.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_OSPI_CLKSRC_RCH
  *            @arg SYSCFG0_OSPI_CLKSRC_PLL0
  *            @arg SYSCFG0_OSPI_CLKSRC_PLL1
  *            @arg SYSCFG0_OSPI_CLKSRC_XOH
  *            @arg SYSCFG0_OSPI_CLKSRC_RCHD4
  *            @arg SYSCFG0_OSPI_CLKSRC_RCHD48
  *            @arg SYSCFG0_OSPI_CLKSRC_RCL
  *            @arg SYSCFG0_OSPI_CLKSRC_XOL
  * @param  SYSCFG0_OSPI_ClkDiv: specifies the division factor for OSPIx clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_OSPIClockConfig(OSPI_Type* OSPIx, \
                             uint32_t SYSCFG0_OSPI_ClkSel, \
                             uint32_t SYSCFG0_OSPI_ClkDiv)
{
  uint32_t ssi;
  
  /* Check the parameters */
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_SYSCFG0_OSPI_CLKSRC(SYSCFG0_OSPI_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_OSPI_ClkDiv));
  
  ssi = OSPI_GET_INDEX(OSPIx);
  
  MODIFY_REG(SYSCFG0->OSPI_SCLK_DIV, \
            (SYSCON_CLK_DIV_MASK << SYSCFG0_OSPI_Cfg[ssi].SYSCFG0_CfgPos), \
            ((SYSCFG0_OSPI_ClkDiv-1) << SYSCFG0_OSPI_Cfg[ssi].SYSCFG0_CfgPos));
  
  MODIFY_REG(SYSCFG0->OSPI_SCLK_SEL, \
            (SYSCFG0_OSPI_CLKSRC_MASK << SYSCFG0_OSPI_Cfg[ssi].SYSCFG0_CfgPos), \
            (SYSCFG0_OSPI_ClkSel << SYSCFG0_OSPI_Cfg[ssi].SYSCFG0_CfgPos));
}

/**
  * @brief  Configure OSPIx signal delay.
  * @param  OSPI_Type: specifies the OSPIx to configures.
  *          This parameter can be: OSPI0 or OSPI1
  * @param  Delay_Cycle: This parameter must be a number between 0 and 7.
  * @retval None
  */
void SYSCFG0_OSPI_RDS_Delay(OSPI_Type* OSPIx, uint8_t Delay_Cycle)
{
  uint32_t ssi;
  
   /* Check the parameters */
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_SYSCFG0_OSPI_RDS_DLY(Delay_Cycle));
  
  ssi = OSPI_GET_INDEX(OSPIx);
  
  MODIFY_REG(SYSCFG0->OSPI_CTRL, \
            (SYSCFG0_OSPI_RDS_DLY_MASK << SYSCFG0_OSPI_Cfg[ssi].SYSCFG0_CfgPos), \
            (Delay_Cycle << SYSCFG0_OSPI_Cfg[ssi].SYSCFG0_CfgPos));  
  
}

/**
  * @brief  Configure I2Sx clock.
  * @param  I2S_Type: specifies the I2Sx to configures.
  *          This parameter can be: I2S33_0 or I2S33_1
  * @param  SYSCFG0_I2S_ClkSel: selects the I2Sx clock.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_I2S_CLKSRC_RCH
  *            @arg SYSCFG0_I2S_CLKSRC_PLL0
  *            @arg SYSCFG0_I2S_CLKSRC_PLL1
  *            @arg SYSCFG0_I2S_CLKSRC_XOH
  *            @arg SYSCFG0_I2S_CLKSRC_RCHD4
  *            @arg SYSCFG0_I2S_CLKSRC_RCHD48
  *            @arg SYSCFG0_I2S_CLKSRC_RCL
  *            @arg SYSCFG0_I2S_CLKSRC_XOL
  * @param  SYSCFG0_I2S_ClkDiv: specifies the division factor for I2Sx clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_I2SClockConfig(I2S_Type* I2Sx, \
                             uint32_t SYSCFG0_I2S_ClkSel, \
                             uint32_t SYSCFG0_I2S_ClkDiv)
{
  uint32_t i2s;
  
  /* Check the parameters */
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_SYSCFG0_I2S_CLKSRC(SYSCFG0_I2S_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_I2S_ClkDiv));
  
  i2s = I2S_GET_INDEX(I2Sx);
  
  MODIFY_REG(SYSCFG0->I2S_CLK_DIV, \
             SYSCFG0_I2S_ClkDiv_Cfg[i2s].SYSCFG0_CfgMask, \
            (SYSCFG0_I2S_ClkDiv-1) << SYSCFG0_I2S_ClkDiv_Cfg[i2s].SYSCFG0_CfgPos);
  
  MODIFY_REG(SYSCFG0->I2S_CLK_SEL, \
             SYSCFG0_I2S_ClkSrc_Cfg[i2s].SYSCFG0_CfgMask, \
             SYSCFG0_I2S_ClkSel << SYSCFG0_I2S_ClkSrc_Cfg[i2s].SYSCFG0_CfgPos);
}

/**
  * @brief  Configures I2Sx master clock.
  * @param  I2S_Type: specifies the I2Sx to configures.
  *          This parameter can be: I2S33_0 or I2S33_1
  * @param  SYSCFG0_I2S_MClkDiv: specifies the division factor for I2Sx master clock
  *          This parameter must be a number between 1 and 256.
  * @param  NewState: new state of I2Sx master clock output function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_I2SMasterClockConfig(I2S_Type* I2Sx, \
                                   uint32_t SYSCFG0_I2S_MClkDiv, \
                                   FunctionalState NewState)
{
  uint32_t i2s;
  uint32_t cfg_mask, cfg_set;
  
  /* Check the parameters */
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_I2S_MClkDiv));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  i2s = I2S_GET_INDEX(I2Sx);
  
  cfg_mask = SYSCFG0_I2S_MCK_OutEn_Cfg[i2s].SYSCFG0_CfgMask |\
             SYSCFG0_I2S_MCK_Div_Cfg[i2s].SYSCFG0_CfgMask;
  
  cfg_set = (SYSCFG0_I2S_MClkDiv-1) << SYSCFG0_I2S_MCK_Div_Cfg[i2s].SYSCFG0_CfgPos;
  if (NewState == ENABLE)
  {
    SET_BIT(cfg_set, SYSCFG0_I2S_MCK_OutEn_Cfg[i2s].SYSCFG0_CfgMask);
  }

  MODIFY_REG(SYSCFG0->I2S_MCK_CTRL, cfg_mask, cfg_set);
}

/**
  * @brief  Enables or disables the specified pins for I2Sx functions.
  * @note   By default, I2Sx cannot use the specified pins because of
  *           Flexcomm4/5 function. When the specified pins used as
  *           I2S0 function, Flexcomm4 cannot use these pins.When the 
  *           specified pins used as I2S1 function, Flexcomm5 cannot 
  *           use these pins.
  * @param  I2S_Type: specifies the I2Sx to configures.
  *          This parameter can be: I2S33_0 or I2S33_1
  * @param  NewState: new state of I2Sx pin function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_I2SPinsCmd(I2S_Type* I2Sx, FunctionalState NewState)
{
  uint32_t cfg_tmp;
  
  /* Check the parameters */
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (I2Sx == I2S0)
    cfg_tmp = SYSCFG0_FC_I2S_SEL_I2S0;
  else
    cfg_tmp = SYSCFG0_FC_I2S_SEL_I2S1;

  
  if (NewState == ENABLE)
  {
    SET_BIT(SYSCFG0->FC_I2S_SEL, cfg_tmp);
  }
  else
  {
    CLEAR_BIT(SYSCFG0->FC_I2S_SEL, cfg_tmp);
  }
}

/**
  * @brief  Configures Flexcomm mode.
  * @param  FLEXCOMMx: where x can (0..13) to select the Flexcomm peripheral.
  * @param  SYSCFG0_FCMode: configures the Flexcomm mode.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_FC_None
  *            @arg SYSCFG0_FC_UART
  *            @arg SYSCFG0_FC_SPI
  *            @arg SYSCFG0_FC_SPI_Slave
  *            @arg SYSCFG0_FC_I2C
  * @retval None
  */
void SYSCFG0_FlexcommModeConfig(FLEXCOMM_Type FLEXCOMMx, uint32_t SYSCFG0_FCMode)
{
  uint32_t reg_index, cfg_pos, cfg_mask, cfg_set;
  
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_FCSEL(SYSCFG0_FCMode));
  
  reg_index = FLEXCOMMx / 8UL;
  cfg_pos = (FLEXCOMMx-(reg_index*8UL)) * 4UL;
  cfg_mask = SYSCFG0_FC_SEL_MASK << cfg_pos;
  cfg_set = SYSCFG0_FCMode << cfg_pos;
  
  MODIFY_REG(SYSCFG0->FC_CTRL[reg_index], cfg_mask, cfg_set);
}

/**
  * @brief  Configures Flexcomm clock.
  * @param  FLEXCOMMx: where x can (0..13) to select the Flexcomm peripheral.
  * @param  SYSCFG0_FC_ClkSel: selects the Flexcomm clock.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_FC_CLKSRC_RCH
  *            @arg SYSCFG0_FC_CLKSRC_PLL0
  *            @arg SYSCFG0_FC_CLKSRC_PLL1
  *            @arg SYSCFG0_FC_CLKSRC_XOH
  *            @arg SYSCFG0_FC_CLKSRC_RCHD4
  *            @arg SYSCFG0_FC_CLKSRC_RCHD48
  *            @arg SYSCFG0_FC_CLKSRC_RCL
  *            @arg SYSCFG0_FC_CLKSRC_XOL
  * @param  SYSCFG0_FC_ClkDiv: specifies the division factor for Flexcomm clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_FlexcommClockConfig(FLEXCOMM_Type FLEXCOMMx, \
                                  uint32_t SYSCFG0_FC_ClkSel, \
                                  uint32_t SYSCFG0_FC_ClkDiv)
{
  uint32_t clksel_reg_index, clksel_cfg_pos, clksel_cfg_mask, clksel_cfg_set;
  uint32_t clkdiv_reg_index, clkdiv_cfg_pos, clkdiv_cfg_mask, clkdiv_cfg_set;
  
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_FC_CLKSRC(SYSCFG0_FC_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_FC_ClkDiv));
  
  clkdiv_reg_index = FLEXCOMMx / 4UL;
  clkdiv_cfg_pos = (FLEXCOMMx-(clkdiv_reg_index*4UL)) * 8UL;
  clkdiv_cfg_mask = SYSCON_CLK_DIV_MASK << clkdiv_cfg_pos;
  clkdiv_cfg_set = (SYSCFG0_FC_ClkDiv-1UL) << clkdiv_cfg_pos;
  
  clksel_reg_index = FLEXCOMMx / 10UL;
  clksel_cfg_pos = (FLEXCOMMx-(clksel_reg_index*10UL)) * 3UL;
  clksel_cfg_mask = SYSCFG0_FC_CLKSRC_MASK << clksel_cfg_pos;
  clksel_cfg_set = SYSCFG0_FC_ClkSel <<clksel_cfg_pos; 
  
  MODIFY_REG(SYSCFG0->FC_SCLK_DIV[clkdiv_reg_index], clkdiv_cfg_mask, clkdiv_cfg_set);
  MODIFY_REG(SYSCFG0->FC_SCLK_SEL[clksel_reg_index], clksel_cfg_mask, clksel_cfg_set);
}

/**
  * @brief  Enables or disables the specified Flexcomm UART receiver.
  * @param  FLEXCOMMx: where x can (0..13) to select the Flexcomm peripheral.
  * @param  NewState: new state of the specified Flexcomm UART receiver.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_FlexcommUARTRxCmd(FLEXCOMM_Type FLEXCOMMx, FunctionalState NewState)
{  
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    CLEAR_BIT(SYSCFG0->FC_I2S_SEL, SYSCFG0_FC_I2S_SEL_UART_RXDIS0<<FLEXCOMMx);
  }
  else
  {
    SET_BIT(SYSCFG0->FC_I2S_SEL, SYSCFG0_FC_I2S_SEL_UART_RXDIS0<<FLEXCOMMx);
  }
}

/**
  * @brief  Configure SDIOx clock.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SYSCFG0_SDIO_ClkSel: selects the SDIOx clock.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_SDIO_CLKSRC_RCH
  *            @arg SYSCFG0_SDIO_CLKSRC_PLL0
  *            @arg SYSCFG0_SDIO_CLKSRC_PLL1
  *            @arg SYSCFG0_SDIO_CLKSRC_XOH
  *            @arg SYSCFG0_SDIO_CLKSRC_RCHD4
  *            @arg SYSCFG0_SDIO_CLKSRC_PLL0D
  *            @arg SYSCFG0_SDIO_CLKSRC_RCL
  *            @arg SYSCFG0_SDIO_CLKSRC_XOL
  * @param  SYSCFG0_SDIO_ClkDiv: specifies the division factor for SDIOx clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_SDIOClockConfig(SDIO_TypeDef *SDIOx, uint32_t SYSCFG0_SDIO_ClkSel, uint32_t SYSCFG0_SDIO_ClkDiv)
{
  uint32_t sdio;
  
  /* Check the parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_SYSCFG0_I2S_CLKSRC(SYSCFG0_SDIO_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_SDIO_ClkDiv));
  
  sdio = SDIO_GET_INDEX(SDIOx);
  
  MODIFY_REG(SYSCFG0->SDIO_CTRL, \
             SYSCFG0_SDIO_ClkDiv_Cfg[sdio].SYSCFG0_CfgMask, \
            (SYSCFG0_SDIO_ClkDiv-1) << SYSCFG0_SDIO_ClkDiv_Cfg[sdio].SYSCFG0_CfgPos);
  
  MODIFY_REG(SYSCFG0->SDIO_CTRL, \
             SYSCFG0_SDIO_ClkSrc_Cfg[sdio].SYSCFG0_CfgMask, \
             SYSCFG0_SDIO_ClkSel << SYSCFG0_SDIO_ClkSrc_Cfg[sdio].SYSCFG0_CfgPos);
}

/**
  * @brief  Configures ADC clock.
  * @param  SYSCFG0_ADC_ClkSel: selects the ADC clock source.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_ADC_CLKSRC_RCHD48
  *            @arg SYSCFG0_ADC_CLKSRC_PLL0
  *            @arg SYSCFG0_ADC_CLKSRC_PLL1
  *            @arg SYSCFG0_ADC_CLKSRC_RCH
  *            @arg SYSCFG0_ADC_CLKSRC_RCHD4
  * @param  SYSCFG0_ADC_ClkDiv: specifies the division factor for ADC clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_ADCClockConfig(uint32_t SYSCFG0_ADC_ClkSel, uint32_t SYSCFG0_ADC_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_ADC_CLKSRC(SYSCFG0_ADC_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_ADC_ClkDiv));
  
  WRITE_REG(SYSCFG0->ADC_CLK_DIV, (SYSCFG0_ADC_ClkDiv-1UL));
  WRITE_REG(SYSCFG0->ADC_CLK_SEL, SYSCFG0_ADC_ClkSel);
}

/**
  * @brief  Configures ADC regular channel external trigger source.
  * @param  SYSCFG0_ADC_RegularExtTrig: selects the ADC regular channel external trigger source.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_ADCRegularExtTrig_EXTI11
  *            @arg SYSCFG0_ADCRegularExtTrig_ETMR1
  * @retval None
  */
void SYSCFG0_ADCRegularExtTrigConfig(uint32_t SYSCFG0_ADC_RegularExtTrig)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_ADCRegularExtTrig(SYSCFG0_ADC_RegularExtTrig));
  
  MODIFY_REG(SYSCFG0->ADC_TRG_SEL, \
             SYSCFG0_ADC_TRG_SEL_REG, \
             SYSCFG0_ADC_RegularExtTrig);
}

/**
  * @brief  Configures ADC injected channel external trigger source.
  * @param  SYSCFG0_ADC_InjectedExtTrig: selects the ADC injected channel external trigger source.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_ADC_InjectedExtTrig_EXTI15
  *            @arg SYSCFG0_ADC_InjectedExtTrig_ETMR1
  * @retval None
  */
void SYSCFG0_ADCInjectedExtTrigConfig(uint32_t SYSCFG0_ADC_InjectedExtTrig)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_ADCInjectedExtTrig(SYSCFG0_ADC_InjectedExtTrig));
  
  MODIFY_REG(SYSCFG0->ADC_TRG_SEL, \
             SYSCFG0_ADC_TRG_SEL_INJ, \
             SYSCFG0_ADC_InjectedExtTrig);
}

/**
  * @brief  Configures CDMA ADC clock.
  * @param  SYSCFG0_CDMA_ADC_ClkSel: selects the CDMA ADC clock source.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_CDMA_ADC_CLKSRC_RCH
  *            @arg SYSCFG0_CDMA_ADC_CLKSRC_PLL0
  *            @arg SYSCFG0_CDMA_ADC_CLKSRC_PLL1
  *            @arg SYSCFG0_CDMA_ADC_CLKSRC_XOH
  *            @arg SYSCFG0_CDMA_ADC_CLKSRC_RCHD4
  *            @arg SYSCFG0_CDMA_ADC_CLKSRC_RCHD48
  *            @arg SYSCFG0_CDMA_ADC_CLKSRC_RCL
  *            @arg SYSCFG0_CDMA_ADC_CLKSRC_XOL
  * @param  SYSCFG0_CDMA_ADC_ClkDiv: specifies the division factor for CDMA ADC clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_CDMA_ADCClockConfig(uint32_t SYSCFG0_CDMA_ADC_ClkSel, \
                                  uint32_t SYSCFG0_CDMA_ADC_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_CDMAADC_CLKSRC(SYSCFG0_CDMA_ADC_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_CDMA_ADC_ClkDiv));
  
  WRITE_REG(SYSCFG0->CDMA_ADC_CLK_DIV, (SYSCFG0_CDMA_ADC_ClkDiv-1UL));
  WRITE_REG(SYSCFG0->CDMA_ADC_CLK_SEL, SYSCFG0_CDMA_ADC_ClkSel);
}

/**
  * @brief  Configures DAC clock.
  * @param  SYSCFG0_DAC_ClkSel: selects the DAC clock source.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_DAC_CLKSRC_RCH
  *            @arg SYSCFG0_DAC_CLKSRC_PLL0
  *            @arg SYSCFG0_DAC_CLKSRC_PLL1
  *            @arg SYSCFG0_DAC_CLKSRC_XOH
  *            @arg SYSCFG0_DAC_CLKSRC_RCHD4
  *            @arg SYSCFG0_DAC_CLKSRC_RCHD48
  * @param  SYSCFG0_DAC_ClkDiv: specifies the division factor for DAC clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_DACClockConfig(uint32_t SYSCFG0_DAC_ClkSel, \
                             uint32_t SYSCFG0_DAC_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_DAC_CLKSRC(SYSCFG0_DAC_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_DAC_ClkDiv));
  
  WRITE_REG(SYSCFG0->DAC_CLK_DIV, (SYSCFG0_DAC_ClkDiv-1UL));
  WRITE_REG(SYSCFG0->DAC_CLK_SEL, SYSCFG0_DAC_ClkSel);
}

/**
  * @brief  Configures EADC clock.
  * @param  SYSCFG0_EADC_ClkSel: selects the EADC clock source.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_EADC_CLKSRC_RCHD48
  *            @arg SYSCFG0_EADC_CLKSRC_PLL0
  *            @arg SYSCFG0_EADC_CLKSRC_PLL1
  *            @arg SYSCFG0_EADC_CLKSRC_XOH
  *            @arg SYSCFG0_EADC_CLKSRC_RCHD4
  *            @arg SYSCFG0_EADC_CLKSRC_RCH
  * @param  SYSCFG0_EADC_ClkDiv: specifies the division factor for EADC clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_EADCClockConfig(uint32_t SYSCFG0_EADC_ClkSel, \
                              uint32_t SYSCFG0_EADC_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_EADC_CLKSRC(SYSCFG0_EADC_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_EADC_ClkDiv));
  
  WRITE_REG(SYSCFG0->EADC_CLK_DIV, (SYSCFG0_EADC_ClkDiv-1UL));
  WRITE_REG(SYSCFG0->EADC_CLK_SEL, SYSCFG0_EADC_ClkSel);
}

/**
  * @brief  Configures USBHS clock.
  * @param  SYSCFG0_USBHS_ClkSel: selects the USBHS clock source.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_USBHS_CLKSRC_PLL0
  *            @arg SYSCFG0_USBHS_CLKSRC_RCHD4
  *            @arg SYSCFG0_USBHS_CLKSRC_PLL1
  *            @arg SYSCFG0_USBHS_CLKSRC_XOH
  *            @arg SYSCFG0_USBHS_CLKSRC_RCH
  * @param  SYSCFG0_USBHS_ClkDiv: specifies the division factor for USBHS clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_USBHSClockConfig(uint32_t SYSCFG0_USBHS_ClkSel, \
                               uint32_t SYSCFG0_USBHS_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_USBHS_CLKSRC(SYSCFG0_USBHS_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_USBHS_ClkDiv));
  
  WRITE_REG(SYSCFG0->USB0_CLK_DIV, (SYSCFG0_USBHS_ClkDiv-1UL));
  WRITE_REG(SYSCFG0->USB0_CLK_SEL, SYSCFG0_USBHS_ClkSel);
}

/**
  * @brief  Configures USBFS clock.
  * @param  SYSCFG0_USBFS_ClkSel: selects the USBFS clock source.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_USBFS_CLKSRC_RCH
  *            @arg SYSCFG0_USBFS_CLKSRC_PLL0
  *            @arg SYSCFG0_USBFS_CLKSRC_PLL1
  *            @arg SYSCFG0_USBFS_CLKSRC_XOH
  * @param  SYSCFG0_USBFS_ClkDiv: specifies the division factor for USBFS clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_USBFSClockConfig(uint32_t SYSCFG0_USBFS_ClkSel, \
                               uint32_t SYSCFG0_USBFS_ClkDiv)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_USBFS_CLKSRC(SYSCFG0_USBFS_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_USBFS_ClkDiv));
  
  WRITE_REG(SYSCFG0->USB1_CLK_DIV, (SYSCFG0_USBFS_ClkDiv-1UL));
  WRITE_REG(SYSCFG0->USB1_CLK_SEL, SYSCFG0_USBFS_ClkSel);
}

/**
  * @brief  Configure basic timer clock.
  * @param  SYSCFG0_BasicTMR: specifies the basic timer clock to configures.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_BTMR0
  *            @arg SYSCFG0_BTMR1
  *            @arg SYSCFG0_BTMR2
  *            @arg SYSCFG0_BTMR3
  *            @arg SYSCFG0_BPWM0
  *            @arg SYSCFG0_BPWM1
  *            @arg SYSCFG0_BPWM2
  *            @arg SYSCFG0_BPWM3
  * @param  SYSCFG0_BasicTMR_ClkSel: selects the basic timer clock.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_BTMR_CLKSRC_RCH
  *            @arg SYSCFG0_BTMR_CLKSRC_PLL0
  *            @arg SYSCFG0_BTMR_CLKSRC_PLL1
  *            @arg SYSCFG0_BTMR_CLKSRC_XOH
  *            @arg SYSCFG0_BTMR_CLKSRC_RCHD4
  *            @arg SYSCFG0_BTMR_CLKSRC_RCHD48
  *            @arg SYSCFG0_BTMR_CLKSRC_RCL
  *            @arg SYSCFG0_BTMR_CLKSRC_XOL
  * @param  SYSCFG0_BasicTMR_ClkDiv: specifies the division factor for basic timer clock
  *          This parameter must be a number between 1 and 256.
  * @retval None
  */
void SYSCFG0_BasicTMRClockConfig(uint32_t SYSCFG0_BasicTMR, \
                                  uint32_t SYSCFG0_BasicTMR_ClkSel, \
                                  uint32_t SYSCFG0_BasicTMR_ClkDiv)
{
  uint32_t clksel_cfg_pos, clksel_cfg_mask, clksel_cfg_set;
  uint32_t clkdiv_reg_index, clkdiv_cfg_pos, clkdiv_cfg_mask, clkdiv_cfg_set;
  
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_BTMR(SYSCFG0_BasicTMR));
  assert_parameters(SYSCFG0_BTMR_CLKSRC(SYSCFG0_BasicTMR_ClkSel));
  assert_parameters(IS_SYSCON_CLK_DIV(SYSCFG0_BasicTMR_ClkDiv));
  
  clkdiv_reg_index = SYSCFG0_BasicTMR / 4UL;
  clkdiv_cfg_pos = (SYSCFG0_BasicTMR - (4UL*clkdiv_reg_index)) * 8UL;
  clkdiv_cfg_mask = SYSCON_CLK_DIV_MASK << clkdiv_cfg_pos;
  clkdiv_cfg_set = (SYSCFG0_BasicTMR_ClkDiv-1UL) << clkdiv_cfg_pos;
  
  clksel_cfg_pos = SYSCFG0_BasicTMR * 4UL;
  clksel_cfg_mask = SYSCFG0_BasicTMR_ClkSel << clksel_cfg_pos;
  clksel_cfg_set = SYSCFG0_BasicTMR_ClkSel << clksel_cfg_pos;
  
  MODIFY_REG(SYSCFG0->TIMER0_DIV[clkdiv_reg_index], \
             clkdiv_cfg_mask, \
             clkdiv_cfg_set);
  
  MODIFY_REG(SYSCFG0->TIMER0_SEL, \
             clksel_cfg_mask, \
             clksel_cfg_set);
}

/**
  * @brief  Enables or disables debug function.
  * @param  NewState: new state of debug function.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_DebugCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState == ENABLE)
  {
    WRITE_REG(SYSCFG0->DBG_CFG, SYSCFG0_DBG_CFG_DBGEN);
  }
  else
  {
    WRITE_REG(SYSCFG0->DBG_CFG, 0UL);
  }
}

/**
  * @brief  Gets reset source status.
  * @param  None
  * @retval Reset source
  */
uint32_t SYSCFG0_GetResetSource(void)
{
  return (SYSCFG0->M33_SW_REG);
}

/**
  * @brief  Configures DMA request.
  * @param  SYSCFG0_DMAx_REQy: where x can be (0..1), y can be (0..15) to select the
  *           DMA request index to configure.
  * @param  SYSCFG0_DMARequest: selects the DMA request.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_DMA_REQUEST_FC0_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC0_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC1_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC1_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC2_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC2_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC3_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC3_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC4_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC4_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC5_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC5_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC6_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC6_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC7_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC7_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC8_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC8_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC9_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC9_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC10_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC10_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC11_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC11_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC12_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC12_RX
  *            @arg SYSCFG0_DMA_REQUEST_FC13_TX
  *            @arg SYSCFG0_DMA_REQUEST_FC13_RX
  *            @arg SYSCFG0_DMA_REQUEST_SOFTWARE
  *            @arg SYSCFG0_DMA_REQUEST_BTMR33_0
  *            @arg SYSCFG0_DMA_REQUEST_BTMR33_1
  *            @arg SYSCFG0_DMA_REQUEST_BTMR33_2
  *            @arg SYSCFG0_DMA_REQUEST_BTMR33_3
  *            @arg SYSCFG0_DMA_REQUEST_I2S0_TX
  *            @arg SYSCFG0_DMA_REQUEST_I2S0_RX
  *            @arg SYSCFG0_DMA_REQUEST_ISO781633_0_TX
  *            @arg SYSCFG0_DMA_REQUEST_ISO781633_0_RX
  *            @arg SYSCFG0_DMA_REQUEST_ISO781633_1_TX
  *            @arg SYSCFG0_DMA_REQUEST_ISO781633_1_RX
  *            @arg SYSCFG0_DMA_REQUEST_WAVER33
  *            @arg SYSCFG0_DMA_REQUEST_OSPI0_TX
  *            @arg SYSCFG0_DMA_REQUEST_OSPI0_RX
  *            @arg SYSCFG0_DMA_REQUEST_OSPI1_TX
  *            @arg SYSCFG0_DMA_REQUEST_OSPI1_RX
  *            @arg SYSCFG0_DMA_REQUEST_ETMR0_CH1
  *            @arg SYSCFG0_DMA_REQUEST_ETMR0_CH2
  *            @arg SYSCFG0_DMA_REQUEST_ETMR0_CH4_TRIG_COM
  *            @arg SYSCFG0_DMA_REQUEST_ETMR0_UP
  *            @arg SYSCFG0_DMA_REQUEST_ETMR0_CH3
  *            @arg SYSCFG0_DMA_REQUEST_ETMR1_CH1
  *            @arg SYSCFG0_DMA_REQUEST_ETMR1_CH2
  *            @arg SYSCFG0_DMA_REQUEST_ETMR1_CH3_UP
  *            @arg SYSCFG0_DMA_REQUEST_ETMR1_CH4_TRIG_COM
  *            @arg SYSCFG0_DMA_REQUEST_GTMR0_CH3
  *            @arg SYSCFG0_DMA_REQUEST_GTMR0_UP
  *            @arg SYSCFG0_DMA_REQUEST_GTMR0_CH1
  *            @arg SYSCFG0_DMA_REQUEST_GTMR0_CH2_CH4
  *            @arg SYSCFG0_DMA_REQUEST_GTMR0_TRIG
  *            @arg SYSCFG0_DMA_REQUEST_GTMR1_CH3
  *            @arg SYSCFG0_DMA_REQUEST_GTMR1_CH4_UP
  *            @arg SYSCFG0_DMA_REQUEST_GTMR1_CH1_TRIG
  *            @arg SYSCFG0_DMA_REQUEST_GTMR1_CH2
  *            @arg SYSCFG0_DMA_REQUEST_GTMR2_CH1
  *            @arg SYSCFG0_DMA_REQUEST_GTMR2_CH2
  *            @arg SYSCFG0_DMA_REQUEST_GTMR2_CH3
  *            @arg SYSCFG0_DMA_REQUEST_GTMR2_UP
  *            @arg SYSCFG0_DMA_REQUEST_GTMR2_TRIG
  *            @arg SYSCFG0_DMA_REQUEST_GTMR2_CH4
  *            @arg SYSCFG0_DMA_REQUEST_GTMR3_CH4_TRIG
  *            @arg SYSCFG0_DMA_REQUEST_GTMR3_CH3_UP
  *            @arg SYSCFG0_DMA_REQUEST_GTMR3_CH2
  *            @arg SYSCFG0_DMA_REQUEST_GTMR3_CH1
  *            @arg SYSCFG0_DMA_REQUEST_I2S1_TX
  *            @arg SYSCFG0_DMA_REQUEST_I2S1_RX
  *            @arg SYSCFG0_DMA_REQUEST_CRC
  *            @arg SYSCFG0_DMA_REQUEST_DCMI
  *            @arg SYSCFG0_DMA_REQUEST_DAC_1
  *            @arg SYSCFG0_DMA_REQUEST_DAC_2
  *            @arg SYSCFG0_DMA_REQUEST_ADC_0
  *            @arg SYSCFG0_DMA_REQUEST_ADC_1
  *            @arg SYSCFG0_DMA_REQUEST_EADC
  *            @arg SYSCFG0_DMA_REQUEST_CDMA_ADC
  * @retval None
  */
void SYSCFG0_DMARequestConfig(uint32_t SYSCFG0_DMAx_REQy, uint32_t SYSCFG0_DMARequest)
{
  uint32_t addr, pos;
  
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_DMA_REQINDEX(SYSCFG0_DMAx_REQy));
  assert_parameters(IS_SYSCFG0_DMA_REQUEST(SYSCFG0_DMARequest));
  
  addr = (uint32_t)&SYSCFG0->DMA0_REQ_SEL0;
  addr = addr + (SYSCFG0_DMAx_REQy & 0xFFFFFFFCUL);
  
  pos = SYSCFG0_DMAx_REQy & 0x00000003UL;
  pos = 8UL * pos;
  
  MODIFY_REG(*(__IO uint32_t *)(addr), \
             SYSCFG0_DMA_REQ_MASK << pos, \
             SYSCFG0_DMARequest << pos);
}


/**
  * @brief  CAN Wake or Test Config.
  * @param  Periph:  This parameter can be one of the following values:
  *              SYSCFG0_CAN0_WAKE
  *              SYSCFG0_CAN1_WAKE
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG0_CANCtrlCmd(uint32_t Periph, FunctionalState NewState)
{
  assert_parameters(IS_CAN_CTRL_CONF(Periph));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SYSCFG0->CAN_CTRL |= Periph;
  }
  else
  {
    SYSCFG0->CAN_CTRL &= ~Periph;
  }

}


/**
  * @brief  Configures ADC reference voltage.
  * @param  SYSCFG0_ADC_VerfSource: selects the ADC reference voltage.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_ADC_VERF_EXTI
  *            @arg SYSCFG0_ADC_VERF_Internal
  * @param  VerfValue: value of internal reference voltage.If you used 
  *          SYSCFG0_ADC_VERF_EXTI,this parameter is invalid
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_ADC_VERF_3_2V
  *            @arg SYSCFG0_ADC_VERF_2_8V
  *            @arg SYSCFG0_ADC_VERF_2_4V
  *            @arg SYSCFG0_ADC_VERF_2_0V
  *            @arg SYSCFG0_ADC_VERF_1_6V
  * @retval None
  */
void SYSCFG0_ADCVref_config(uint32_t SYSCFG0_ADC_VerfSource, uint32_t VerfValue)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_ADC_VERF(SYSCFG0_ADC_VerfSource));
  assert_parameters(IS_SYSCFG0_ADC_VERF_VAL(VerfValue));
  
  if (SYSCFG0_ADC_VERF_Internal == SYSCFG0_ADC_VerfSource)
  {
    SYSCFG0->ADDA_REF_CFG &= ~(7U << 1);
    SYSCFG0->ADDA_REF_CFG |= VerfValue;
  }

  SYSCFG0->ADDA_REF_CFG &= ~(1U);
  SYSCFG0->ADDA_REF_CFG |= SYSCFG0_ADC_VerfSource;
}


/**
  * @brief  Configures DAC reference voltage.
  * @param  SYSCFG0_DAC_VerfSource: selects the DAC reference voltage.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_DAC_VERF_EXTI
  *            @arg SYSCFG0_DAC_VERF_Internal
  * @param  VerfValue: value of internal reference voltage.If you used 
  *          SYSCFG0_DAC_VERF_EXTI,this parameter is invalid
  *          This parameter can be one of the following values:
  *            @arg SYSCFG0_DAC_VERF_3_2V
  *            @arg SYSCFG0_DAC_VERF_2_8V
  *            @arg SYSCFG0_DAC_VERF_2_4V
  *            @arg SYSCFG0_DAC_VERF_2_0V
  *            @arg SYSCFG0_DAC_VERF_1_6V
  * @retval None
  */
void SYSCFG0_DACVref_config(uint32_t SYSCFG0_DAC_VerfSource, uint32_t VerfValue)
{
  /* Check the parameters */
  assert_parameters(IS_SYSCFG0_DAC_VERF(SYSCFG0_DAC_VerfSource));
  assert_parameters(IS_SYSCFG0_DAC_VERF_VAL(VerfValue));
  
  if (SYSCFG0_DAC_VERF_Internal == SYSCFG0_DAC_VerfSource)
  {
    SYSCFG0->ADDA_REF_CFG &= ~(7U << 17);
    SYSCFG0->ADDA_REF_CFG |= VerfValue;
  }

  SYSCFG0->ADDA_REF_CFG &= ~(1U << 16);
  SYSCFG0->ADDA_REF_CFG |= SYSCFG0_DAC_VerfSource;
}

/*********************************** END OF FILE ******************************/
