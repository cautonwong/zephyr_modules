/**
  ******************************************************************************
  * @file    lib_pmu.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-06-30
  * @brief   PMU library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_pmu.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup PMU 
  * @brief PMU driver modules
  * @{
  */

/** @defgroup PMU_Private_Defines
  * @{
  */
/* Private macro -------------------------------------------------------------*/
#define CM0_DSLEEPPSWD_KEY             ((uint32_t)0xAA5555AA)
#define CM33_DSLEEPPSWD_KEY            ((uint32_t)0xAA5555AA)
#define DSLEEPEN_KEY                   ((uint32_t)0x55AAAA55)
#define SLEEPEN_KEY                    ((uint32_t)0x55AAAA55)

#define PMU_SLEEPEN_WKU                BIT31

#define PMU_CTRL_CM33_WKUINTEN         ((uint32_t)0x20000000)
#define PMU_CTRL_CM0_WKUINTEN          ((uint32_t)0x02000000)

#define PMU_CM33_CLKAUTO               ((uint32_t)0x10000000)
#define PMU_CM0_CLKAUTO                ((uint32_t)0x08000000)

#define PMU_WKUIN_CM33                 ((uint32_t)0x00000002)
#define PMU_WKUIN_CM0                  ((uint32_t)0x00000001)

#define PMU_RETRAM_CFG                 ((uint32_t)0x80000000)

/**
  * @}
  */

/**
  * @brief  Enters sleep mode.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @retval 1: Enter sleep mode failed.
  */
void PMU_EnterSleepMode(uint8_t CoreX)
{
  /* Check the parameters */
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
 
  if(CoreX == SLEEP_CORE_CM33)
  {
    /* Write in the CM33_SLPEN register the SLEEPEN KEY */
    PMU->CM33_SLPEN = SLEEPEN_KEY;
  }
  else
  {
    /* Write in the CM0_SLPEN register the SLEEPEN KEY */
    PMU->CM0_SLPEN = SLEEPEN_KEY;
  }
}

/**
  * @brief  Enters deep-sleep mode.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @retval 1: Enter deep-sleep mode failed.
  */
void PMU_EnterDSleepMode(uint8_t CoreX)
{
  /* Check the parameters */
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  
  SYSCFGLP_WDTResetConfig(SYSCFGLP_WDTRST_TRI_CORE);
  
  if(CoreX == SLEEP_CORE_CM33)
  {
    /* Write in the CM33_DSLPPSWD register the CM33_DSLEEPPSWD_KEY */
    PMU->CM33_DSLPPSWD = CM33_DSLEEPPSWD_KEY;
    /* Write in the CM33_DSLPEN register the DSLEEPEN_KEY */
    PMU->CM33_DSLPEN = DSLEEPEN_KEY;
  }
  else
  {
    /* Write in the CM0_DSLPPSWD register the CM0_DSLEEPPSWD_KEY */
    PMU->CM0_DSLPPSWD = CM0_DSLEEPPSWD_KEY;
    /* Write in the CM0_DSLPEN register the DSLEEPEN_KEY */
    PMU->CM0_DSLPEN = DSLEEPEN_KEY;
  }
}

/**
  * @brief  Wakeup event generate interrupt enable function.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @param  NewState:
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void PMU_WKUINTConfig(uint8_t CoreX, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if(CoreX == SLEEP_CORE_CM33)
  {
    if (NewState != DISABLE)
    {
      /* Write in the CTRL register the Wake up interrupt enable */
      PMU->CTRL |= PMU_CTRL_CM33_WKUINTEN;
    }
    else
    {
      /* Write in the CTRL register the Wake up interrupt disable */
      PMU->CTRL &= ~PMU_CTRL_CM33_WKUINTEN;
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Write in the CTRL register the Wake up interrupt enable */
      PMU->CTRL |= PMU_CTRL_CM0_WKUINTEN;
    }
    else
    {
      /* Write in the CTRL register the Wake up interrupt disable */
      PMU->CTRL &= ~PMU_CTRL_CM0_WKUINTEN;
    }
  }
}

/**
  * @brief  Wakeup source configration function.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @param  Src:
  *           @arg PMU_WKUSRC_XTAL 
  *           @arg PMU_WKUSRC_U32K1
  *           @arg PMU_WKUSRC_U32K0
  *           @arg PMU_WKUSRC_TIMER
  *           @arg PMU_WKUSRC_IO   
  *           @arg PMU_WKUSRC_COMP 
  *           @arg PMU_WKUSRC_RTC_ALM
  * @param  NewState:
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void PMU_WKUSRCConfig(uint8_t CoreX, uint32_t Src, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  assert_parameters(IS_PMU_WKU_SRC(Src));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if(CoreX == SLEEP_CORE_CM33)
  {
    if (NewState != DISABLE)
    {
      /* Write in the CTRL register the cm33 wake up source */
      PMU->CTRL |= (Src<<8);
    }
    else
    {
      PMU->CTRL &= ~(Src<<8);
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Write in the CTRL register the cm0 wake up source */
      PMU->CTRL |= Src;
    }
    else
    {
      PMU->CTRL &= ~Src;
    }
  }
}

/**
  * @brief  GPIO Pin Wakeup source configration function.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @param  PinX:
  *           @arg GPIO_Pin_0 ~ GPIO_Pin_15
  * @param  NewState:
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void PMU_WKUGPIOConfig(uint8_t CoreX, uint32_t PinX, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  assert_parameters(IS_GPIO_PIN(PinX));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if(CoreX == SLEEP_CORE_CM33)
  {
    if (NewState != DISABLE)
    {
      /* Write in the IO_WKU_EN register the GPIO_Pin */
      PMU->IO_WKU_EN |= PinX;
    }
    else
    {
      PMU->IO_WKU_EN &= ~PinX;
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Write in the IO_WKU_EN register the GPIO_Pin */
      PMU->IO_WKU_EN |= (PinX<<16);
    }
    else
    {
      PMU->IO_WKU_EN &= ~(PinX<<16);
    }
  }
}

/**
  * @brief Whether to make BGP1 RCH1 PLL0 PLL1 power down when coreX in sleep or deep sleep mode
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @param  NewState:
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void PMU_CLKAUTO_Config(uint8_t CoreX, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if(CoreX == SLEEP_CORE_CM33)
  {
    if (NewState != DISABLE)
    {
      /* Write in the CTRL register the PMU_CM33_CLKAUTO */
      PMU->CTRL |= PMU_CM33_CLKAUTO;
    }
    else
    {
      PMU->CTRL &= ~PMU_CM33_CLKAUTO;
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Write in the CTRL register the PMU_CM0_CLKAUTO */
      PMU->CTRL |= PMU_CM0_CLKAUTO;
    }
    else
    {
      PMU->CTRL &= ~PMU_CM0_CLKAUTO;
    }
  }
}

/**
  * @brief Configuration retention RAM mode
  * @param  RamMode:
  *           @arg PMU_RAM_MODE_NORMAL
  *           @arg PMU_RAM_MODE_U32K
  * @retval None
  */
void PMU_RETRAMConfig(uint32_t RamMode)
{
  /* Check the parameters */
  assert_parameters(IS_PMU_RAM_MODE(RamMode));
  
  if(RamMode != PMU_RAM_MODE_NORMAL)
  {
    PMU->RETRAMCFG |= PMU_RETRAM_CFG;
  }
  else
  {
    PMU->RETRAMCFG &= ~PMU_RETRAM_CFG;
  }
}

/**
  * @brief Get UART32K valid byte count in RX buffer
  * @param  RamMode:
  *           @arg PMU_SRC_U32K0
  *           @arg PMU_SRC_U32K1
  * @retval None
  */
uint8_t PMU_GetU32kReceive(uint32_t U32kSrc)
{
  /* Check the parameters */
  assert_parameters(IS_PMU_SRC_U32K(U32kSrc));
  
  if(U32kSrc == PMU_SRC_U32K0)
  {
      return (uint8_t)(PMU->RETRAMSTS & 0x3F);
  }
  else
  {
     return (uint8_t)((PMU->RETRAMSTS >> 5) & 0x3F);
  }
}

/**
  * @brief  Gets reset source status.
  * @param  Status:
  *           @arg PMU_STS_WDT0      
  *           @arg PMU_STS_WDT1      
  *           @arg PMU_STS_CM33RSTPMU
  *           @arg PMU_STS_CM0RSTPMU 
  *           @arg PMU_STS_WDT2    
  *           @arg PMU_STS_DPORRST   
  *           @arg PMU_STS_PORRST    
  *           @arg PMU_STS_EXTRST    
  * @retval The new state of Reset source (SET or RESET).
  */
uint8_t PMU_GetResetSource(uint32_t Status)
{
  /* Check the parameters */
  assert_parameters(IS_PMU_STS_RST(Status));
  
  if(PMU->STS & Status)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Gets all reset source status.
  * @param  None
  * @retval All reset source status
  */
uint32_t PMU_GetAllResetSource()
{
  /* Return the PMU status */
  return (PMU->STS & PMU_STS_RSTMASK);
}

/**
  * @brief  Clear Reset status function.
  * @param  rstsrc:
  *           @arg PMU_STS_WDT0      
  *           @arg PMU_STS_WDT1      
  *           @arg PMU_STS_CM33RSTPMU
  *           @arg PMU_STS_CM0RSTPMU 
  *           @arg PMU_STS_WDT2    
  *           @arg PMU_STS_DPORRST   
  *           @arg PMU_STS_PORRST    
  *           @arg PMU_STS_EXTRST    
  * @retval None
  */
void PMU_ClearResetSource(uint32_t rstsrc)
{
  /* Check parameters */
  assert_parameters(IS_PMU_STS_RST(rstsrc));

  PMU->STS = rstsrc;
  while(PMU->STS & rstsrc)
  {}
}

/**
  * @brief  Gets XTAL status.
  * @param  Status:
  *            PMU_STS_XOH
  *            PMU_STS_XOL
  * @retval The state of XTAL (SET or RESET).
  */
uint32_t PMU_GetXTALStatus(uint32_t Status)
{
  assert_parameters(IS_PMU_STS_XTAL(Status));

  if(PMU->STS & Status)
  {
    /* XTAL status is set */
    return SET;
  }
  else
  {
    /* XTAL status is reset */
    return RESET;
  }
}

/**
  * @brief  Get sleep wakeup source function.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @retval All wakeup source.
  */
uint32_t PMU_GetSleepWKUSource(uint8_t CoreX)
{
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  
  if(CoreX == SLEEP_CORE_CM33)
  {
    /* Return the PMU_CM33 sleep wakeup source function */
    return PMU->CM33PWRSTS & PMU_SLPWKU_MASK;
  }
  else
  {
    /* Return the PMU_CM0 sleep wakeup source function */
    return PMU->CM0PWRSTS & PMU_SLPWKU_MASK;
  }
}

/**
  * @brief  Get deep sleep wakeup source function.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @retval All wakeup source.
  */
uint32_t PMU_GetDSleepWKUSource(uint8_t CoreX)
{
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  
  if(CoreX == SLEEP_CORE_CM33)
  {
    /* Return the PMU_CM33 deep sleep wakeup source function */
    return PMU->CM33PWRSTS & PMU_DSLPWKU_MASK;
  }
  else
  {
    /* Return the PMU_CM0 deep sleep wakeup source function */
    return PMU->CM0PWRSTS & PMU_DSLPWKU_MASK;
  }
}

/**
  * @brief  Get PMU State machine code function.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @retval PMU State.
  */
uint32_t PMU_GetPMUState(uint8_t CoreX)
{
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  
  if(CoreX == SLEEP_CORE_CM33)
  {
    /* Return the PMU_CM33 State machine code function */
    return (PMU->CM33PWRSTS & PMU_STS_STATE) >> 16;
  }
  else
  {
    /* Return the PMU_CM0 State machine code function */
    return (PMU->CM0PWRSTS & PMU_STS_STATE) >> 16;
  }
}

/**
  * @brief  Get PMU wakeup interrupt State function.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @retval Wakeup interrupt State (SET or RESET).
  */
uint8_t PMU_GetWKUInterruptStatus(uint8_t CoreX)
{
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  
  if(CoreX == SLEEP_CORE_CM33)
  {
    if(PMU->WKUINT & PMU_WKUIN_CM33)
    {
      /* PMU_CM33 is set */
      return SET;
    }
    else
    {
      /* PMU_CM33 is reset */
      return RESET;
    }
  }
  else
  {
    if(PMU->WKUINT & PMU_WKUIN_CM0)
    {
      /* PMU_CM0 is set */
      return SET;
    }
    else
    {
      /* PMU_CM0 is reset */
      return RESET;
    }
  }
}

/**
  * @brief  Clear PMU wakeup interrupt status function.
  * @param  CoreX:
  *           @arg SLEEP_CORE_CM33
  *           @arg SLEEP_CROE_CM0 
  * @retval None
  */
void PMU_ClearWKUInterruptStatus(uint8_t CoreX)
{
  /* Check parameters */
  assert_parameters(IS_CHIP_CORE_SEL(CoreX));
  
  if(CoreX == SLEEP_CORE_CM33)
  {
    /* Clear wakeup interrupt CM33 */
    PMU->WKUINT = PMU_WKUIN_CM33;

  }
  else
  {
    /* Clear wakeup interrupt CM0 */
    PMU->WKUINT = PMU_WKUIN_CM0;
  }
}

/**
  * @brief  PMU cycle count config function.
  * @param  module:
  *           @arg PMU_CYCLE_PWG 
  *           @arg PMU_CYCLE_CKG 
  *           @arg PMU_CYCLE_PWUP
  *           @arg PMU_CYCLE_RST 
  *           @arg PMU_CYCLE_ISO 
  * @param  cycle: 0~15
  * @retval None
  */
void PMU_WaitCycleConfig(uint32_t module, uint8_t cycle)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_PMU_CYCLE_MODULE(module));
  assert_parameters(IS_PMU_CYCLE_COUNT(cycle));

  tmp = PMU->WAITCYCLE;
  tmp &= ~(0xF<<module);
  tmp |= cycle<<module;

  /* Write in the WAITCYCLE register the cycle count config function */
  PMU->WAITCYCLE = tmp;
}

/**
  * @brief  Enable XTAL wakeup source.
  * @param  WakupSrc:
  *           @arg XTAL32K_EXIST_WKU
  *           @arg XOH_EXIST_WKU
  * @param  NewState:
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void PMU_XTALWKUSRCConfig(uint32_t WakeupSrc, FunctionalState NewState)
{
  assert_parameters(IS_XTAL_EXIST_WKU_EN(WakeupSrc));
  if (NewState != DISABLE)
  {
    SYSCFGLP->XTAL_EXIST_CTRL |= WakeupSrc;
  }
  else
  {
    SYSCFGLP->XTAL_EXIST_CTRL &= ~WakeupSrc;
  }
}

/**
  * @}
  */

/**
  * @}
  */
/*********************************** END OF FILE ******************************/
