/**
  ******************************************************************************
  * @file    lib_clk.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Clock library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_clk.h"
#include "lib_flash.h"

#define CM33_HCLK_MAX              (192000000UL)
#define CM0_HCLK_MAX               (CM33_HCLK_MAX/2)

/* Private define ------------------------------------------------------------*/
/* XOH dleay/timeout value */
#define XOH_DELAY_VALUE            (2UL)
#define XOH_TIMEOUT_VALUE          (90UL)
/* XOL dleay/timeout value */
#define XOL_DELAY_VALUE            (2000UL)
#define XOL_EXTCLK_DELAY_VALUE     (1UL)
/* PLL0 dleay/timeout value */
#define PLL0_TIMEOUT_VALUE         (10UL)
/* PLL1 dleay/timeout value */
#define PLL1_DELAY_VALUE           (1UL)
#define PLL1_TIMEOUT_VALUE         (160UL)
/* Clock configuration lock */
#define CLK_ANA_UNLOCK()           (SYSCFGLP->ANA_LOCK = 0xFEEBFEEBUL)
#define RTC_ANA_UNLOCK()           (RTCANA->ANALOCK = 0xFEEBFEEBUL)
/* SYSCON Key */
#define CLK_SYSCON_KEY             (0xBEEFBEEFUL)

/** @defgroup PLL0 config
  * @{
  */
const CLK_PLL0Config pll0_config[CLK_PLL0_FREQCFG_MAX] = 
{
  { (CLK_PLL0_1stN_2), (16UL), (3UL), 128000000UL },  /* 128M, refrence 12MHz */
  { (CLK_PLL0_1stN_2), (12UL), (2UL), 144000000UL },  /* 144M, refrence 12MHz */
  { (CLK_PLL0_1stN_2), (15UL), (2UL), 180000000UL },  /* 180M, refrence 12MHz */
  { (CLK_PLL0_1stN_2), (24UL), (3UL), 192000000UL },  /* 192M, refrence 12MHz */

  { (CLK_PLL0_1stN_1), (16UL), (6UL), 128000000UL },  /* 128M, refrence 48MHz */
  { (CLK_PLL0_1stN_1), (12UL), (4UL), 144000000UL },  /* 144M, refrence 48MHz */
  { (CLK_PLL0_1stN_1), (15UL), (4UL), 180000000UL },  /* 180M, refrence 48MHz */
  { (CLK_PLL0_1stN_1), (12UL), (3UL), 192000000UL },  /* 192M, refrence 48MHz */
};

/** @defgroup PLL1 config
  * @{
  */
#define CLKR_POS          SYSCFGLP_PLL1_CTRL2_CLKR_POS
#define CLKF_POS          SYSCFGLP_PLL1_CTRL2_CLKF_POS
#define CLKOD_POS         SYSCFGLP_PLL1_CTRL2_CLKOD_POS
static const CLK_PLL1Config pll1_config[CLK_PLL1_FREQCFG_MAX] = 
{
  { (0x00UL<<CLKR_POS)|(0x1D4BUL<<CLKF_POS)|(0x0UL<<CLKOD_POS), 0xEA5UL, 245760000UL },  /* 245.76M, refrence 32768Hz */
  { (0x00UL<<CLKR_POS)|(0x1F3FUL<<CLKF_POS)|(0x9UL<<CLKOD_POS), 0xF9FUL, 26214000UL },  /* 26.2144M, refrence 32768Hz */
  { (0x00UL<<CLKR_POS)|(0x1D4BUL<<CLKF_POS)|(0x3UL<<CLKOD_POS), 0xEA5UL, 61440000UL  },  /* 61.44M, refrence 32768Hz */
  { (0x00UL<<CLKR_POS)|(0x1D4BUL<<CLKF_POS)|(0x1UL<<CLKOD_POS), 0xEA5UL, 122880000UL },  /* 122.88M, refrence 32768Hz */
  { (0x00UL<<CLKR_POS)|(0x15F8UL<<CLKF_POS)|(0x0UL<<CLKOD_POS), 0xAFBUL, 184320000UL },  /* 184.32M, refrence 32768Hz */
  { (0x18UL<<CLKR_POS)|(0x02FFUL<<CLKF_POS)|(0x9UL<<CLKOD_POS), 0x17FUL, 36840000UL  },  /* 36.84M, refrence 12M */
  { (0x02UL<<CLKR_POS)|(0x0031UL<<CLKF_POS)|(0x0UL<<CLKOD_POS), 0x018UL, 200000000UL },  /* 200M, refrence 12M */
  { (0x00UL<<CLKR_POS)|(0x0017UL<<CLKF_POS)|(0x1UL<<CLKOD_POS), 0x00BUL, 144000000UL },  /* 144M, refrence 12M */
  { (0x18UL<<CLKR_POS)|(0x024BUL<<CLKF_POS)|(0x0UL<<CLKOD_POS), 0x125UL, 282240000UL }   /* 282.24M, refrence 12M */
};

/** @defgroup MCOx config
  * @{
  */
#define MCO_PIN_MAX                (4UL)
static MCO_Config mco_config[MCO_PIN_MAX] = 
{
  { GPIOA, GPIO_Pin_8,  GPIO_PinSource8,  GPIO_AF0_MCO1 },
  { GPIOC, GPIO_Pin_9,  GPIO_PinSource9,  GPIO_AF0_MCO2 },
  { GPIOE, GPIO_Pin_12, GPIO_PinSource12, GPIO_AF0_MCO3 },
  { GPIOF, GPIO_Pin_11, GPIO_PinSource11, GPIO_AF0_MCO4 }
};

/* Private function prototypes -----------------------------------------------*/
static uint32_t CLK_GetPLL0Freq(void);
static uint32_t CLK_GetPLL1Freq(void);

/**
  * @brief  Initialize the Oscillators according to the specified parameters in the
  *         CLK_OscInitType.
  * @param  RCC_OscInitStruct  pointer to an CLK_OscInitType structure that
  *         contains the configuration information for the Oscillators.
  * @retval STD status
  */
STD_StatusType CLK_OscConfig(CLK_OscInitType *CLK_OscInitStruct)
{
  uint32_t tickstart;
  STD_StatusType status = STD_OK;
  
  /* Check Null pointer */
  if (CLK_OscInitStruct == NULL)
  {
    return STD_ERROR;
  }
  
  /* Check the parameters */
  assert_parameters(IS_CLK_TYPE(CLK_OscInitStruct->OscillatorType));
  
  CLK_ANA_UNLOCK();
  
  /*----------------------------- RCH Configuration --------------------------*/
  if (IS_BIT_SET(CLK_OscInitStruct->OscillatorType, CLK_OSCILLATORTYPE_RCH))
  {
    /* Check the parameters */
    assert_parameters(IS_CLK_RCH(CLK_OscInitStruct->RCHState));
    /* nothing to do */
  }
  
  /*----------------------------- XOH Configuration --------------------------*/
  if (IS_BIT_SET(CLK_OscInitStruct->OscillatorType, CLK_OSCILLATORTYPE_XOH))
  {
    /* Check if the XOH is used as HCLK/PCLK or not */
    if ((IS_HCLK_SOURCE_XOH) || (IS_PCLK_SOURCE_XOH))
    {
      /* nothing to do */
    }
    else
    {
      /* Check the parameters */
      assert_parameters(IS_CLK_XOH(CLK_OscInitStruct->XOHState));
      
      if (CLK_OscInitStruct->XOHState == CLK_XOH_OFF)
      {
        CLEAR_BIT(SYSCFGLP->XOH_CTRL0, SYSCFGLP_XOH_CTRL0_BYPASS);
        CLEAR_BIT(SYSCFGLP->XOH_CTRL0, SYSCFGLP_XOH_CTRL0_XOHEN);
      }
      else if (CLK_OscInitStruct->XOHState == CLK_XOH_ON)
      {
        CLEAR_BIT(SYSCFGLP->XOH_CTRL0, SYSCFGLP_XOH_CTRL0_BYPASS);
        SET_BIT(SYSCFGLP->XOH_CTRL0, SYSCFGLP_XOH_CTRL0_XOHEN);
        STD_Delay(XOH_DELAY_VALUE);
        SET_BIT(SYSCFGLP->XOH_CTRL0, SYSCFGLP_XOH_CTRL0_STABLE_GATE_FORCE_EN);
        tickstart = STD_GetTick();
        while (READ_BIT(SYSCFGLP->XTAL_EXIST_CTRL, SYSCFGLP_XTAL_EXIST_CTRL_XOH) == 0U)
        {
          if((STD_GetTick() - tickstart) > XOH_TIMEOUT_VALUE)
          {
            return STD_TIMEOUT;
          }
        }
      }
      else if (CLK_OscInitStruct->XOHState == CLK_XOH_BYPASS)
      {
        SET_BIT(SYSCFGLP->XOH_CTRL0, SYSCFGLP_XOH_CTRL0_XOHEN);
        SET_BIT(SYSCFGLP->XOH_CTRL0, SYSCFGLP_XOH_CTRL0_BYPASS);
        SET_BIT(SYSCFGLP->XOH_CTRL0, SYSCFGLP_XOH_CTRL0_STABLE_GATE_FORCE_EN);
        tickstart = STD_GetTick();
        while (READ_BIT(SYSCFGLP->XTAL_EXIST_CTRL, SYSCFGLP_XTAL_EXIST_CTRL_XOH) == 0U)
        {
          if((STD_GetTick() - tickstart) > XOH_TIMEOUT_VALUE)
          {
            return STD_TIMEOUT;
          }
        }
      }
      else
      {
        return STD_ERROR;
      }
    }
  }

  /*----------------------------- XOL Configuration --------------------------*/
  if (IS_BIT_SET(CLK_OscInitStruct->OscillatorType, CLK_OSCILLATORTYPE_XOL))
  {
    /* Check the parameters */
    assert_parameters(IS_CLK_XOL(CLK_OscInitStruct->XOLState));
    
    RTC_ANA_UNLOCK();
    
    if (CLK_OscInitStruct->XOLState == CLK_XOL_OFF)
    {
      CLEAR_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_BYP_LV);
      CLEAR_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_EN_LV);
    }
    else if (CLK_OscInitStruct->XOLState == CLK_XOL_ON)
    {
      if (!READ_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_32KEXIST))
      {
        CLEAR_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_BYP_LV);
        SET_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_EN_LV);
        STD_Delay(XOL_DELAY_VALUE);
        if (!READ_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_32KEXIST))
        {
          return STD_TIMEOUT;
        }
        RTCANA->XTAL |= RTC_ANA_CTRL_XTAL_EN_SEL;
        CLK_ClearXTAL32KAbsentStatus();
      }
    }
    else if (CLK_OscInitStruct->XOLState == CLK_XOL_BYPASS)
    {
      SET_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_BYP_LV);
      CLEAR_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_EN_LV);
      STD_Delay(XOL_EXTCLK_DELAY_VALUE);
    }
  }
  
  /* Check the parameters */
  assert_parameters(IS_CLK_PLL0(CLK_OscInitStruct->PLL0.PLL0_State));
  
  /*----------------------------- PLL0 Configuration --------------------------*/
  if (CLK_OscInitStruct->PLL0.PLL0_State != CLK_PLL0_NONE)
  {
    
    /* Check if the PLL0 is used as HCLK/PCLK or not */
    if ((!IS_HCLK_SOURCE_PLL0) && (!IS_PCLK_SOURCE_PLL0))
    {
      if (CLK_OscInitStruct->PLL0.PLL0_State == CLK_PLL0_ON)
      {
        /* Check the parameters */
        assert_parameters(IS_CLK_PLL0_SRC(CLK_OscInitStruct->PLL0.PLL0_Source));
        assert_parameters(IS_CLK_PLL0_N1(CLK_OscInitStruct->PLL0.PLL0_1stN));
        assert_parameters(IS_CLK_PLL0_N2(CLK_OscInitStruct->PLL0.PLL0_2rdN));
        assert_parameters(IS_CLK_PLL0_M(CLK_OscInitStruct->PLL0.PLL0_M));
        
        if(CLK_OscInitStruct->PLL0.PLL0_Source == CLK_PLL0SOURCE_XOH)
        {
          if (READ_BIT(SYSCFGLP->XTAL_EXIST_CTRL, SYSCFGLP_XTAL_EXIST_CTRL_XOH) == 0U)
            return STD_ERROR;
        }
        
        /* Hardware control flow */
        CLEAR_BIT(SYSCFGLP->PLL0_CTRL0, SYSCFGLP_PLL0_CTRL0_SATBLE_GATE_SEL);
        
        /* Disable the PLL0 */
        CLEAR_BIT(SYSCFGLP->PLL0_CTRL0, SYSCFGLP_PLL0_CTRL0_PLL0EN);
        
        /* Set clock source */
        MODIFY_REG(SYSCFGLP->PLL0_CTRL0,                 \
                   SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_MASK,  \
                   CLK_OscInitStruct->PLL0.PLL0_Source);
        
        /* Set multiplication and division factors */
        MODIFY_REG(SYSCFGLP->PLL0_CTRL1,                 \
                   SYSCFGLP_PLL0_CTRL1_CFG_MASK,         \
                  (CLK_OscInitStruct->PLL0.PLL0_1stN)     \
                 |(CLK_OscInitStruct->PLL0.PLL0_2rdN << SYSCFGLP_PLL0_CTRL1_DIV_INT_L_POS) \
                 |(CLK_OscInitStruct->PLL0.PLL0_M << SYSCFGLP_PLL0_CTRL1_DIV_PRE_POS));
        
        CLEAR_BIT(SYSCFGLP->PLL0_CTRL0, SYSCFGLP_PLL0_CTRL0_SATBLE_GATE_SEL);
        /* Enable the PLL0 */
        SET_BIT(SYSCFGLP->PLL0_CTRL0, SYSCFGLP_PLL0_CTRL0_PLL0EN);
        
        tickstart = STD_GetTick();
        while (READ_BIT(SYSCFGLP->PLL0_CTRL0, SYSCFGLP_PLL0_CTRL0_PLL0_STABLE) == 0U)
        {
          if((STD_GetTick() - tickstart) > PLL0_TIMEOUT_VALUE)
          {
            return STD_TIMEOUT;
          }
        }
      }
      else
      {
        /* Disable the PLL0 */
        CLEAR_BIT(SYSCFGLP->PLL0_CTRL0, SYSCFGLP_PLL0_CTRL0_PLL0EN);
      }
    }
    else
    {
      if (CLK_OscInitStruct->PLL0.PLL0_State == CLK_PLL0_OFF)
      {
         status = STD_ERROR;
      }
      else
      {
        /* Do not return error if request repeats the current configuration */
        if ((READ_BIT(SYSCFGLP->PLL0_CTRL0, SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_MASK) != CLK_OscInitStruct->PLL0.PLL0_Source) || \
            (READ_BIT(SYSCFGLP->PLL0_CTRL1, SYSCFGLP_PLL0_CTRL1_CFG_MASK) != ((CLK_OscInitStruct->PLL0.PLL0_1stN)     \
                                                                               |(CLK_OscInitStruct->PLL0.PLL0_2rdN << SYSCFGLP_PLL0_CTRL1_DIV_INT_L_POS) \
                                                                               |(CLK_OscInitStruct->PLL0.PLL0_M << SYSCFGLP_PLL0_CTRL1_DIV_PRE_POS))))
        {
          status = STD_ERROR;
        }
      }
    }
  }
  
  /* Check the parameters */
  assert_parameters(IS_CLK_PLL1(CLK_OscInitStruct->PLL1.PLL1_State));
  
  /*----------------------------- PLL1 Configuration --------------------------*/
  if (CLK_OscInitStruct->PLL1.PLL1_State != CLK_PLL1_NONE)
  {
    /* Check if the PLL0 is used as HCLK/PCLK or not */
    if ((!IS_HCLK_SOURCE_PLL1) && (!IS_PCLK_SOURCE_PLL1))
    {
      if (CLK_OscInitStruct->PLL1.PLL1_State == CLK_PLL1_ON)
      {
        /* Check the parameters */
        assert_parameters(IS_CLK_PLL1_SRC(CLK_OscInitStruct->PLL1.PLL1_Source));
        assert_parameters(IS_CLK_PLL1_FREQCFG(CLK_OscInitStruct->PLL1.PLL1_Frequency));
        
        if(CLK_OscInitStruct->PLL1.PLL1_Source == CLK_PLL1SOURCE_XOH_12M)
        {
          if (READ_BIT(SYSCFGLP->XTAL_EXIST_CTRL, SYSCFGLP_XTAL_EXIST_CTRL_XOH) == 0U)
            return STD_ERROR;
        }
        else if(CLK_OscInitStruct->PLL1.PLL1_Source  == CLK_PLL1SOURCE_XOL_32768)
        {
          if (READ_BIT(RTCANA->XTAL, RTC_ANA_CTRL_XTAL_32KEXIST) == 0U)
            return STD_ERROR;
        }
        else
        {
        
        }
        
        /* Hardware control flow */
        CLEAR_BIT(SYSCFGLP->PLL1_CTRL0, SYSCFGLP_PLL1_CTRL0_SATBLE_GATE_SEL);
        
        /* Hold reset */
        WRITE_REG(SYSCFGLP->PLL1_CTRL1, SYSCFGLP_PLL1_CTRL1_RESET);
        
        /* Disable the PLL1 */
        SET_BIT(SYSCFGLP->PLL1_CTRL0, SYSCFGLP_PLL1_CTRL0_PLL1_PWRDN);
        
        /* Set the clock source */
        MODIFY_REG(SYSCFGLP->PLL1_CTRL0,                 \
                   SYSCFGLP_PLL1_CTRL0_REFCLK_SEL_MASK,  \
                   CLK_OscInitStruct->PLL1.PLL1_Source);
        
        /* Configure the PLL1 */
        WRITE_REG(SYSCFGLP->PLL1_CTRL2, \
                  pll1_config[CLK_OscInitStruct->PLL1.PLL1_Frequency].PLL1_CTRL2);
        WRITE_REG(SYSCFGLP->PLL1_CTRL3, \
                  pll1_config[CLK_OscInitStruct->PLL1.PLL1_Frequency].PLL1_CTRL3);
        
        /* Enable the PLL1 */
        CLEAR_BIT(SYSCFGLP->PLL1_CTRL0, SYSCFGLP_PLL1_CTRL0_PLL1_PWRDN);
        STD_Delay(PLL1_DELAY_VALUE);
        /* Release reset */
        WRITE_REG(SYSCFGLP->PLL1_CTRL1, 0UL);
        
        tickstart = STD_GetTick();
        while (READ_BIT(SYSCFGLP->PLL1_CTRL0, SYSCFGLP_PLL1_CTRL0_PLL1_STABLE) == 0U)
        {
          if((STD_GetTick() - tickstart) > PLL1_TIMEOUT_VALUE)
          {
            return STD_TIMEOUT;
          }
        }
      }
      else
      {
        /* Disable the PLL1 */
        SET_BIT(SYSCFGLP->PLL1_CTRL0, SYSCFGLP_PLL1_CTRL0_PLL1_PWRDN);
      }
    }
    else
    {
      if (CLK_OscInitStruct->PLL1.PLL1_State == CLK_PLL1_OFF)
      {
         status = STD_ERROR;
      }
      else
      {
        /* Do not return error if request repeats the current configuration */
        if ((SYSCFGLP->PLL1_CTRL2 != pll1_config[CLK_OscInitStruct->PLL1.PLL1_Frequency].PLL1_CTRL2) ||\
            (SYSCFGLP->PLL1_CTRL3 != pll1_config[CLK_OscInitStruct->PLL1.PLL1_Frequency].PLL1_CTRL3))
        {
          status = STD_ERROR;
        }
      }
    }
  }
  
  return status;
}

/**
  * @brief  Initialize the CPU, AHB and APB buses clocks according to the specified
  *         parameters in the CLK_InitStruct.
  * @param  CLK_InitStruct  pointer to an CLK_InitType structure that contains
  *         the configuration information for the AHB and APB clock.
  * @retval STD_OK
  */
STD_StatusType CLK_Config(CLK_InitType *CLK_InitStruct)
{
  /* Check the parameters */
  assert_parameters(IS_CLK_AHBSRC(CLK_InitStruct->AHBCLKSource));
  assert_parameters(IS_CLK_APBSRC(CLK_InitStruct->APBCLKSource));
  assert_parameters(IS_CLK_AHBDIV(CLK_InitStruct->AHBCLKDivider));
  assert_parameters(IS_CLK_APBDIV(CLK_InitStruct->APBCLKDivider));
  
#if defined (V32F20XXX_CM33_CORE0)
  
  /* Check the parameters */
  assert_parameters(IS_CLK_BUSCLK(CLK_InitStruct->BusClock));
  
  if (IS_BIT_SET(CLK_InitStruct->BusClock, CLK_BUSCLOCK0))
  {
    /* Set Flash BankA/B RW parameters by Max */
    FLASH_SetCycle(FLASHA, CM33_HCLK_MAX);
    FLASH_SetCycle(FLASHB, CM33_HCLK_MAX);
    
    if (CLK_InitStruct->AHBCLKDivider < (READ_REG(SYSCFG0->HCLK_DIV)+1UL))
    { /* Set lower division factor, switch clock source first */
      WRITE_REG(SYSCFG0->SYSCON_PASSWD, CLK_SYSCON_KEY);
      MODIFY_REG(SYSCFG0->CLK_SEL, SYSCFG0_HCLK_SEL_MASK, CLK_InitStruct->AHBCLKSource);
      WRITE_REG(SYSCFG0->SYSCON_PASSWD, CLK_SYSCON_KEY);
      WRITE_REG(SYSCFG0->HCLK_DIV, CLK_InitStruct->AHBCLKDivider-1);
    }
    else
    { /* Set higher division factor, configure division factor first */
      WRITE_REG(SYSCFG0->SYSCON_PASSWD, CLK_SYSCON_KEY);
      WRITE_REG(SYSCFG0->HCLK_DIV, CLK_InitStruct->AHBCLKDivider-1);
      WRITE_REG(SYSCFG0->SYSCON_PASSWD, CLK_SYSCON_KEY);
      MODIFY_REG(SYSCFG0->CLK_SEL, SYSCFG0_HCLK_SEL_MASK, CLK_InitStruct->AHBCLKSource);
    }
    
    if (CLK_InitStruct->APBCLKDivider < (READ_REG(SYSCFG0->PCLK_DIV)+1))
    { /* Set lower division factor, switch clock source first */
      WRITE_REG(SYSCFG0->SYSCON_PASSWD, CLK_SYSCON_KEY);
      MODIFY_REG(SYSCFG0->CLK_SEL, SYSCFG0_PCLK_SEL_MASK, CLK_InitStruct->APBCLKSource);
      WRITE_REG(SYSCFG0->SYSCON_PASSWD, CLK_SYSCON_KEY);
      WRITE_REG(SYSCFG0->PCLK_DIV, CLK_InitStruct->APBCLKDivider-1);
    }
    else
    { /* Set higher division factor, configure division factor first */
      WRITE_REG(SYSCFG0->SYSCON_PASSWD, CLK_SYSCON_KEY);
      WRITE_REG(SYSCFG0->PCLK_DIV, CLK_InitStruct->APBCLKDivider-1);
      WRITE_REG(SYSCFG0->SYSCON_PASSWD, CLK_SYSCON_KEY);
      MODIFY_REG(SYSCFG0->CLK_SEL, SYSCFG0_PCLK_SEL_MASK, CLK_InitStruct->APBCLKSource);
    }
    
    /* Set Flash BankA/B RW parameters */
    FLASH_SetCycle(FLASHA, CLK_GetHCLK0Freq());
    FLASH_SetCycle(FLASHB, CLK_GetHCLK0Freq());
  }
  
  if (IS_BIT_SET(CLK_InitStruct->BusClock, CLK_BUSCLOCK1))
  {
    /* Set Flash Bank0 RW parameters by Max */
    FLASH_SetCycle(FLASH0, CM0_HCLK_MAX);
    
    if (CLK_InitStruct->AHBCLKDivider < (READ_REG(SYSCFG1->CLKDIVH)+1UL))
    { /* Set lower division factor, switch clock source first */
      WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
      MODIFY_REG(SYSCFG1->CLKSEL, SYSCFG1_HCLK_SEL_MASK, CLK_InitStruct->AHBCLKSource);
      WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
      WRITE_REG(SYSCFG1->CLKDIVH, CLK_InitStruct->AHBCLKDivider-1);
    }
    else
    { /* Set higher division factor, configure division factor first */
      WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
      WRITE_REG(SYSCFG1->CLKDIVH, CLK_InitStruct->AHBCLKDivider-1);
      WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
      MODIFY_REG(SYSCFG1->CLKSEL, SYSCFG1_HCLK_SEL_MASK, CLK_InitStruct->AHBCLKSource);
    }
    
    if (CLK_InitStruct->APBCLKDivider < (READ_REG(SYSCFG1->CLKDIVP)+1UL))
    { /* Set lower division factor, switch clock source first */
      WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
      MODIFY_REG(SYSCFG1->CLKSEL, \
                 SYSCFG1_PCLK_SEL_MASK, \
                 CLK_InitStruct->APBCLKSource >> (SYSCFG0_PCLK_SEL_POS - SYSCFG1_PCLK_SEL_POS));
      WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
      WRITE_REG(SYSCFG1->CLKDIVP, CLK_InitStruct->APBCLKDivider-1);
    }
    else
    { /* Set higher division factor, configure division factor first */
      WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
      WRITE_REG(SYSCFG1->CLKDIVP, CLK_InitStruct->APBCLKDivider-1);
      WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
      MODIFY_REG(SYSCFG1->CLKSEL, \
                 SYSCFG1_PCLK_SEL_MASK, \
                 CLK_InitStruct->APBCLKSource >> (SYSCFG0_PCLK_SEL_POS - SYSCFG1_PCLK_SEL_POS));
    }
    
    /* Set Flash Bank0 RW parameters by Max */
    FLASH_SetCycle(FLASH0, CLK_GetHCLK1Freq());
  }
  
#endif /* V32F20XXX_CM33_CORE0 */
  
#if defined (V32F20XXX_CM0_CORE)
  
  if (CLK_InitStruct->AHBCLKDivider < (SYSCFG1->CLKDIVH+1UL))
  { /* Set lower division factor, switch clock source first */
    WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
    MODIFY_REG(SYSCFG1->CLKSEL, SYSCFG1_HCLK_SEL_MASK, CLK_InitStruct->AHBCLKSource);
    WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
    WRITE_REG(SYSCFG1->CLKDIVH, CLK_InitStruct->AHBCLKDivider-1);
  }
  else
  { /* Set higher division factor, configure division factor first */
    WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
    WRITE_REG(SYSCFG1->CLKDIVH, CLK_InitStruct->AHBCLKDivider-1);
    WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
    MODIFY_REG(SYSCFG1->CLKSEL, SYSCFG1_HCLK_SEL_MASK, CLK_InitStruct->AHBCLKSource);
  }
  
  WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
  WRITE_REG(SYSCFG1->CLKDIVP, CLK_InitStruct->APBCLKDivider-1);
  WRITE_REG(SYSCFG1->PASSWD, CLK_SYSCON_KEY);
  MODIFY_REG(SYSCFG1->CLKSEL, SYSCFG1_PCLK_SEL_MASK, CLK_InitStruct->APBCLKSource);
  
#endif /* V32F20XXX_CM0_CORE */
  
  return STD_OK;
}

/**
  * @brief  Select the clock source to output on MCO pin.
  * @param  CLK_MCOx  specifies the output direction for the clock source.
  *            @arg @ref CLK_MCO1  Clock source to output on MCO1 pin(PA8).
  *            @arg @ref CLK_MCO2  Clock source to output on MCO2 pin(PC9).
  *            @arg @ref CLK_MCO3  Clock source to output on MCO4 pin(PE12).
  *            @arg @ref CLK_MCO4  Clock source to output on MCO5 pin(PF11).
  * @param  MCO_InitStruct  pointer to an MCO_InitType structure that contains
  *         the configuration information for the MCOx.
  *         MCO_InitStruct->Source  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref CLK_MCOSOURCE_RCH        RCH selected as MCO source
  *            @arg @ref CLK_MCOSOURCE_PLL0       PLL0 clock selected as MCO source
  *            @arg @ref CLK_MCOSOURCE_PLL1       PLL1 clock selected as MCO source
  *            @arg @ref CLK_MCOSOURCE_XOH        XOH clock selected as MCO sourcee
  *            @arg @ref CLK_MCOSOURCE_RCL        RCL clock selected as MCO source
  *            @arg @ref CLK_MCOSOURCE_XOL        XOL clock selected as MCO source
  *            @arg @ref CLK_MCOSOURCE_USBHS_UTMI USBHS UTMI clock selected as MCO source
  *         MCO_InitStruct->Divider  specifies the MCO prescaler.
  *          This parameter must be a number between 1 and 256.
  *         MCO_InitStruct->Output  enables or disables MCO output function
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CLK_MCOConfig(uint32_t CLK_MCOx, MCO_InitType *MCO_InitStruct)
{
  GPIO_InitType GPIO_InitStruct;
  
  /* Check the parameters */
  assert_parameters(IS_CLK_MCO(CLK_MCOx));
  assert_parameters(IS_CLK_MCOSOURCE(MCO_InitStruct->Source));
  assert_parameters(IS_CLK_MCODIV(MCO_InitStruct->Divider));
  assert_parameters(IS_FUNCTIONAL_STATE(MCO_InitStruct->Output));
  
  /* Configure the MCO pin in alternate function mode */
  GPIO_InitStruct.GPIO_Pin = mco_config[CLK_MCOx].Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(mco_config[CLK_MCOx].Port, &GPIO_InitStruct);
  
  GPIO_PinAFConfig(mco_config[CLK_MCOx].Port, \
                   mco_config[CLK_MCOx].PinSource, \
                   mco_config[CLK_MCOx].AFConfig);
  
  if (MCO_InitStruct->Output != ENABLE)
  {
    WRITE_REG(SYSCFGLP->CLKOUT[CLK_MCOx], MCO_InitStruct->Source |\
                                           ((MCO_InitStruct->Divider-1) << SYSCFGLP_CLKOUT_DIV_POS));
  }
  else
  {
    WRITE_REG(SYSCFGLP->CLKOUT[CLK_MCOx], MCO_InitStruct->Source |\
                                           ((MCO_InitStruct->Divider-1) << SYSCFGLP_CLKOUT_DIV_POS) |\
                                           SYSCFGLP_CLKOUT_OUTEN);
  }
}

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

/**
  * @brief  Returns the CM33 system HCLK frequency.
  * @param  None
  * @retval CM33 system HCLK frequency in Hz
  */
uint32_t CLK_GetHCLK0Freq(void)
{
  uint32_t clock_source, clock_value;
  uint32_t hclk_div;
  
  clock_source = READ_BIT(SYSCFG0->CLK_SEL, SYSCFG0_HCLK_SEL_MASK);
  switch (clock_source)
  {
    case SYSCFG0_HCLK_SEL_RCH:
      clock_value = RCH_VALUE;
      break;
    
    case SYSCFG0_HCLK_SEL_PLL0:
      clock_value = CLK_GetPLL0Freq();
      break;
    
    case SYSCFG0_HCLK_SEL_PLL1:
      clock_value = CLK_GetPLL1Freq();
      break;
    
    case SYSCFG0_HCLK_SEL_XOH:
      clock_value = XOH_VALUE;
      break;
    
    case SYSCFG0_HCLK_SEL_RCH_DIV4:
      clock_value = RCH_VALUE / 4UL;
      break;
    
    case SYSCFG0_HCLK_SEL_RCH_DIV48:
      clock_value = RCH_VALUE / 48UL;
      break;
    
    case SYSCFG0_HCLK_SEL_32KXTAL:
    case SYSCFG0_HCLK_SEL_32KRC:
      clock_value = 32768UL;
      break;
    
    default:
      clock_value = 0UL;
  }
  hclk_div = READ_REG(SYSCFG0->HCLK_DIV) + 1UL;
  return (clock_value / hclk_div);
}

/**
  * @brief  Returns the CM33 system PCLK frequency.
  * @param  None
  * @retval CM33 system PCLK frequency in Hz
  */
uint32_t CLK_GetPCLK0Freq(void)
{
//  uint32_t pclk_div, hclk_value;
//  
//  pclk_div = READ_REG(SYSCFG0->PCLK_DIV) + 1UL;
//  hclk_value = CLK_GetHCLK0Freq();
//  return (hclk_value / pclk_div);
  
  uint32_t clock_source, clock_value;
  uint32_t pclk_div;
  
  clock_source = READ_BIT(SYSCFG0->CLK_SEL, SYSCFG0_PCLK_SEL_MASK);
  switch (clock_source)
  {
    case SYSCFG0_PCLK_SEL_RCH:
      clock_value = RCH_VALUE;
      break;
    
    case SYSCFG0_PCLK_SEL_PLL0:
      clock_value = CLK_GetPLL0Freq();
      break;
    
    case SYSCFG0_PCLK_SEL_PLL1:
      clock_value = CLK_GetPLL1Freq();
      break;
    
    case SYSCFG0_PCLK_SEL_XOH:
      clock_value = XOH_VALUE;
      break;
    
    case SYSCFG0_PCLK_SEL_RCH_DIV4:
      clock_value = RCH_VALUE / 4UL;
      break;
    
    case SYSCFG0_PCLK_SEL_RCH_DIV48:
      clock_value = RCH_VALUE / 48UL;
      break;
    
    case SYSCFG0_PCLK_SEL_32KXTAL:
    case SYSCFG0_PCLK_SEL_32KRC:
      clock_value = 32768UL;
      break;
    
    default:
      clock_value = 0UL;
  }
  pclk_div = READ_REG(SYSCFG0->PCLK_DIV) + 1UL;
  return (clock_value / pclk_div);
}



/**
  * @brief  Returns the CM33 system I2S internal frequency.
  * @param  None
  * @retval I2S frequency in Hz
  */
uint32_t CLK_GetI2SClockFreq(I2S_Type *I2Sx)
{
  uint32_t csoffset, clksel, clk_value;
  uint32_t cdoffset, clk_div;
  uint32_t i2s;
  
  /* Check the parameters */
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  i2s = I2S_GET_INDEX(I2Sx);
  
  csoffset = i2s * SYS33_I2SCS_CLKSEL_Offset;
  clksel = READ_REG(SYSCFG0->I2S_CLK_SEL) >> csoffset;
  clksel &= SYS33_I2SCS_CLKSEL_MASK;
  
  cdoffset = i2s * SYS33_I2SCD_CLKDIV_Offset;
  clk_div = READ_REG(SYSCFG0->I2S_CLK_DIV) >> cdoffset;
  clk_div &= SYS33_I2SCD_CLKDIV_MASK;
  clk_div += 1UL;
  
  switch (clksel)
  {
    case SYS33_I2SCS_CLKSEL_RCH:
      clk_value = RCH_VALUE;
      break;
    
    case SYS33_I2SCS_CLKSEL_PLL0:
      clk_value = CLK_GetPLL0Freq();
      break;
    
    case SYS33_I2SCS_CLKSEL_PLL1:
      clk_value = CLK_GetPLL1Freq();
      break;
    
    case SYS33_I2SCS_CLKSEL_XOH:
      clk_value = XOH_VALUE;
      break;
    
    case SYS33_I2SCS_CLKSEL_RCHD4:
      clk_value = RCH_VALUE >> 2UL;
      break;
    
    case SYS33_I2SCS_CLKSEL_RCHD48:
      clk_value = RCH_VALUE / 48UL;
      break;
    
    case SYS33_I2SCS_CLKSEL_RCL:
      clk_value = RCL_VALUE;
      break;
    
    case SYS33_I2SCS_CLKSEL_XOL:
      clk_value = XOL_VALUE;
      break;
    
    default:
      clk_value = 0UL;
      break;
  }
  
  return (clk_value / clk_div);
}

/**
  * @brief  Returns Flexcomm clock.
  * @param  FLEXCOMMx: where x can (0..13) to select the Flexcomm peripheral.
  * @retval FLEXCOMMx clock frequency in Hz
  */
uint32_t CLK_GetFlexcommClockFreq(FLEXCOMM_Type FLEXCOMMx)
{
  uint32_t clksel_reg_index, clksel_cfg_pos, clksel_cfg;
  uint32_t clkdiv_reg_index, clkdiv_cfg_pos, clkdiv_cfg;
  uint32_t clk_value, clk_div;
  
  clkdiv_reg_index = FLEXCOMMx / 4UL;
  clkdiv_cfg_pos = (FLEXCOMMx-(clkdiv_reg_index*4UL)) * 8UL;
  clkdiv_cfg = SYSCFG0->FC_SCLK_DIV[clkdiv_reg_index] >> clkdiv_cfg_pos;
  clkdiv_cfg &= SYS33_FCCD_CLKDIV_MASK;
  clk_div = clkdiv_cfg + 1UL;
  
  clksel_reg_index = FLEXCOMMx / 10UL;
  clksel_cfg_pos = (FLEXCOMMx-(clksel_reg_index*10UL)) * 3UL;
  clksel_cfg = SYSCFG0->FC_SCLK_SEL[clksel_reg_index] >> clksel_cfg_pos;
  clksel_cfg &= SYS33_FCCS_CLKSEL_MASK;
  
  switch (clksel_cfg)
  {
    case SYS33_FCCS_CLKSEL_RCH:
      clk_value = RCH_VALUE;
      break;
    
    case SYS33_FCCS_CLKSEL_PLL0:
      clk_value = CLK_GetPLL0Freq();
      break;
    
    case SYS33_FCCS_CLKSEL_PLL1:
      clk_value = CLK_GetPLL1Freq();
      break;
    
    case SYS33_FCCS_CLKSEL_XOH:
      clk_value = XOH_VALUE;
      break;
    
    case SYS33_FCCS_CLKSEL_RCHD4:
      clk_value = RCH_VALUE >> 2UL;
      break;
    
    case SYS33_FCCS_CLKSEL_RCHD48:
      clk_value = RCH_VALUE / 48UL;
      break;
    
    case SYS33_FCCS_CLKSEL_RCL:
      clk_value = RCL_VALUE;
      break;
    
    case SYS33_FCCS_CLKSEL_XOL:
      clk_value = XOL_VALUE;
      break;
    
    default:
      clk_value = 0UL;
      break;
  }
  
  return (clk_value / clk_div);
}

/**
  * @brief  Enables or disables USB autotrim.
  * @param  This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CLK_AutotrimCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  if(ENABLE == NewState)
  {
    SYSCFGLP->AUTOTRIM_CTRL |= SYSLP_AUTOTRIMC_EN;
  }
  else
  {
    SYSCFGLP->AUTOTRIM_CTRL &= ~SYSLP_AUTOTRIMC_EN;
  }
}

/**
  * @brief  Autotrim initilization.
  * @param  Autotrim_Initstruct: pointer to a Autotrim_InitType structure
  *         that contains the configuration information for autotrim.
  * @retval None
  */
void CLK_AutotrimInit(Autotrim_InitType *Autotrim_Initstruct)
{
  uint32_t tmp;
  
  /* Check the parameters */
  assert_parameters(IS_RCC_AUTOTRIM_SRC_SEL(Autotrim_Initstruct->Autotrim_SRC));
  assert_parameters(Autotrim_Initstruct->Autotrim_UpperExpt <= SYSLP_AUTOTRIM_UPPER_EXPT_MASK);
  assert_parameters(Autotrim_Initstruct->Autotrim_LowerExpt <= SYSLP_AUTOTRIM_LOWER_EXPT_MASK);
  
  tmp = SYSCFGLP->AUTOTRIM_CTRL;
  tmp &= ~SYSLP_AUTOTRIMC_SRC_SEL;
  tmp |= Autotrim_Initstruct->Autotrim_SRC;
  SYSCFGLP->AUTOTRIM_CTRL = tmp;
  SYSCFGLP->AUTOTRIM_UPPER_EXPT = Autotrim_Initstruct->Autotrim_UpperExpt;
  SYSCFGLP->AUTOTRIM_LOWER_EXPT = Autotrim_Initstruct->Autotrim_LowerExpt;
}

#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */

/**
  * @brief  Returns the CM0 system HCLK frequency.
  * @param  None
  * @retval CM0 system HCLK frequency in Hz
  */
uint32_t CLK_GetHCLK1Freq(void)
{
  uint32_t clock_source, clock_value;
  uint32_t hclk_div;
  
  clock_source = READ_BIT(SYSCFG1->CLKSEL, SYSCFG1_HCLK_SEL_MASK);
  switch (clock_source)
  {
    case SYSCFG1_HCLK_SEL_RCH:
      clock_value = RCH_VALUE;
      break;
    
    case SYSCFG1_HCLK_SEL_PLL0:
      clock_value = CLK_GetPLL0Freq();
      break;
    
    case SYSCFG1_HCLK_SEL_PLL1:
      clock_value = CLK_GetPLL1Freq();
      break;
    
    case SYSCFG1_HCLK_SEL_XOH:
      clock_value = XOH_VALUE;
      break;
    
    case SYSCFG1_HCLK_SEL_RCH_DIV4:
      clock_value = RCH_VALUE / 4UL;
      break;
    
    case SYSCFG1_HCLK_SEL_RCH_DIV48:
      clock_value = RCH_VALUE / 48UL;
      break;
    
    case SYSCFG1_HCLK_SEL_32KXTAL:
    case SYSCFG1_HCLK_SEL_32KRC:
      clock_value = 32768UL;
      break;
    
    default:
      clock_value = 0UL;
  }
  hclk_div = READ_REG(SYSCFG1->CLKDIVH) + 1UL;

  return (clock_value / hclk_div);
}

/**
  * @brief  Returns the CM0 system PCLK frequency.
  * @param  None
  * @retval CM0 system PCLK frequency in Hz
  */
uint32_t CLK_GetPCLK1Freq(void)
{
//  uint32_t pclk_div, hclk_value;
//  
//  pclk_div = READ_REG(SYSCFG1->CLKDIVP) + 1UL;
//  hclk_value = CLK_GetHCLK1Freq();
//  return (hclk_value / pclk_div);
  
  uint32_t clock_source, clock_value;
  uint32_t pclk_div;
  
  clock_source = READ_BIT(SYSCFG1->CLKSEL, SYSCFG1_PCLK_SEL_MASK);
  switch (clock_source)
  {
    case SYSCFG1_PCLK_SEL_RCH:
      clock_value = RCH_VALUE;
      break;
    
    case SYSCFG1_PCLK_SEL_PLL0:
      clock_value = CLK_GetPLL0Freq();
      break;
    
    case SYSCFG1_PCLK_SEL_PLL1:
      clock_value = CLK_GetPLL1Freq();
      break;
    
    case SYSCFG1_PCLK_SEL_XOH:
      clock_value = XOH_VALUE;
      break;
    
    case SYSCFG1_PCLK_SEL_RCH_DIV4:
      clock_value = RCH_VALUE / 4UL;
      break;
    
    case SYSCFG1_PCLK_SEL_RCH_DIV48:
      clock_value = RCH_VALUE / 48UL;
      break;
    
    case SYSCFG1_PCLK_SEL_32KXTAL:
    case SYSCFG1_PCLK_SEL_32KRC:
      clock_value = 32768UL;
      break;
    
    default:
      clock_value = 0UL;
  }
  pclk_div = READ_REG(SYSCFG1->CLKDIVP) + 1UL;

  return (clock_value / pclk_div);
}

/**
  * @brief  Returns the UART14_19 Serial clock frequency.
  * @param  None
  * @retval UART Serial clock frequency in Hz
  */
uint32_t CLK_GetUART14_19ClockFreq(UART_Type *UARTx)
{
  uint32_t uart;
  uint32_t clkdiv_reg_index, clkdiv_cfg_pos, clkdiv_cfg;
  uint32_t clksel_cfg_pos, clksel_cfg;
  uint32_t clk_value, clk_div;

  /* Check the parameters */
  assert_parameters(IS_UART14_19_ALL_INSTANCE(UARTx));
  
  uart = UART14_19_GET_INDEX(UARTx);
  
  clkdiv_reg_index = uart / 4UL;
  clkdiv_cfg_pos = (uart-(4UL*clkdiv_reg_index)) * 8UL;
  if (clkdiv_reg_index)
    clkdiv_cfg = READ_REG(SYSCFG1->UART_SCLK_DIV2) >> clkdiv_cfg_pos;
  else
    clkdiv_cfg = READ_REG(SYSCFG1->UART_SCLK_DIV1) >> clkdiv_cfg_pos;
  clkdiv_cfg &= SYSCON_CLK_DIV_MASK;
  clk_div = clkdiv_cfg + 1UL;
  
  clksel_cfg_pos = 3UL*uart + 11UL;
  clksel_cfg = READ_REG(SYSCFG1->CLKSEL) >> clksel_cfg_pos;
  clksel_cfg &= SYSCFG1_UART_CLKSRC_MASK;
  
  switch (clksel_cfg)
  {
    case SYSCFG1_UART_CLKSRC_RCH:
      clk_value = RCH_VALUE;
      break;
    
    case SYSCFG1_UART_CLKSRC_PLL0:
      clk_value = CLK_GetPLL0Freq();
      break;
    
    case SYSCFG1_UART_CLKSRC_PLL1:
      clk_value = CLK_GetPLL1Freq();
      break;
    
    case SYSCFG1_UART_CLKSRC_XOH:
      clk_value = XOH_VALUE;
      break;
    
    case SYSCFG1_UART_CLKSRC_RCHD4:
      clk_value = RCH_VALUE >> 2UL;
      break;
    
    case SYSCFG1_UART_CLKSRC_RCHD48:
      clk_value = RCH_VALUE / 48UL;
      break;
    
    case SYSCFG1_UART_CLKSRC_RCL:
      clk_value = RCL_VALUE;
      break;
    
    case SYSCFG1_UART_CLKSRC_XOL:
      clk_value = XOL_VALUE;
      break;
    
    default:
      clk_value = 0UL;
      break;
  }
  
  return (clk_value / clk_div);
}

/**
  * @brief  Compute PLL1 clock frequency.
  * @retval PLL1 frequency
  */
static uint32_t CLK_GetPLL0Freq(void)
{
  uint32_t n1, n2, m;
  uint32_t pll0_source, pll0_in, pll0_out;
  uint32_t tmp;
  
  pll0_source = READ_BIT(SYSCFGLP->PLL0_CTRL0, SYSCFGLP_PLL0_CTRL0_REFCLK_SEL_MASK);
  switch (pll0_source)
  {
    case PLL0_REFCLK_RCH_DIV4:
      pll0_in = RCH_VALUE / 4UL;
      break;
    
    case PLL0_REFCLK_XOH:
      pll0_in = XOH_VALUE;
      break;
    
    case PLL0_REFCLK_RCH:
      pll0_in = RCH_VALUE;
      break;
    
    case PLL0_REFCLK_RCH_DIV48:
      pll0_in = RCH_VALUE / 48UL;
      break;
    
    default:
      return 0UL;
  }
  
  tmp = READ_REG(SYSCFGLP->PLL0_CTRL1);
  n1 = READ_BIT(tmp, SYSCFGLP_PLL0_CTRL1_DIV_INT_H_MASK);
  if (n1 == CLK_PLL0_1stN_1)
    n1 = 1UL;
  else if (n1 == CLK_PLL0_1stN_2)
    n1 = 2UL;
  else
    n1 = 4UL;
  
  n2 = READ_BIT(tmp, SYSCFGLP_PLL0_CTRL1_DIV_INT_L_MASK);
  n2 >>= SYSCFGLP_PLL0_CTRL1_DIV_INT_L_POS;
  
  m = READ_BIT(tmp, SYSCFGLP_PLL0_CTRL1_DIV_PRE_MASK);
  m >>= SYSCFGLP_PLL0_CTRL1_DIV_PRE_POS;
  
  pll0_out = pll0_in *n1 * n2 / m;
  
  return (pll0_out);
}

/**
  * @brief  Compute PLL1 clock frequency.
  * @retval PLL1 frequency
  */
static uint32_t CLK_GetPLL1Freq(void)
{
  uint32_t pll1_out = 0UL;
  uint32_t pll1_ctrl2, pll1_ctrl3;
  uint32_t index;
  
  pll1_ctrl2 = READ_REG(SYSCFGLP->PLL1_CTRL2);
  pll1_ctrl3 = READ_REG(SYSCFGLP->PLL1_CTRL3);
 
  for (index=0UL; index<CLK_PLL1_FREQCFG_MAX; index++)
  {
    if (pll1_ctrl2 == pll1_config[index].PLL1_CTRL2)
    {
      if (pll1_ctrl3 == pll1_config[index].PLL1_CTRL3)
      {
        pll1_out = pll1_config[index].PLL1_OUT;
        break;
      }
    }
    else
    {
      continue;
    }
  }
  
  return (pll1_out);
}

/**
  * @brief  Get XTAL 32k absent State function.
  * @param  None
  * @retval XTAK 32K absent State (SET or RESET).
  */
uint8_t CLK_GetXTAL32KAbsentStatus(void)
{
  if (RTCANA->XTAL & RTC_ANA_CTRL_XTAL_32KABSENT)
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

/**
  * @brief  clear XTAL 32k absent State function.
  * @param  None
  * @retval XTAK 32K absent State (SET or RESET).
  */
void CLK_ClearXTAL32KAbsentStatus(void)
{
  RTCANA->XTAL &= ~RTC_ANA_CTRL_XTAL_32KABSENT_CLR;
}

/*********************************** END OF FILE ******************************/
