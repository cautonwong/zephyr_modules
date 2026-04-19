/**
  ******************************************************************************
  * @file    lib_comp.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Comp library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_syscfg.h"
#include "lib_comp.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup COMP
  * @brief COMP driver modules
  * @{
  */

/** @defgroup COMP_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup COMP_Private_Defines
  * @{
  */
/*COMP_LONG_PULSE Register*/
#define COMP_LPULSE_TIME_MSK                     ((uint32_t)0x000001FE)

/*COMP_WKU_CTRL Register*/
#define COMP_WKU_SRC_MSK                         ((uint32_t)0x00000002)
#define COMP_WKU_TYPE_MSK                        ((uint32_t)0x0000001C)
#define COMP_WKU_MSK                             (COMP_WKU_SRC_MSK | COMP_WKU_TYPE_MSK)

/*COMP_INT_CTRL Register*/
#define COMP_INT_SRC_MSK                         ((uint32_t)0x00000020)
#define COMP_INT_TYPE_MSK                        ((uint32_t)0x0000001C)
#define COMP_INT_CTRL_MSK                        (COMP_INT_SRC_MSK | COMP_INT_TYPE_MSK)

/*COMP_CR Register*/
#define COMP_CR_HYST_MSK                         ((uint32_t)0x00000002)
#define COMP_CR_SPDPWR_MSK                       ((uint32_t)0x0000000C)
#define COMP_CR_SAMPLEMODE_MSK                   ((uint32_t)0x00030000)
#define COMP_CR_CLKDIV_MSK                       ((uint32_t)0x001C0000)
#define COMP_CR_MSK                              (COMP_CR_HYST_MSK | COMP_CR_SPDPWR_MSK | \
                                                  COMP_CR_SAMPLEMODE_MSK | COMP_CR_CLKDIV_MSK)

/*COMP_STATUS Register*/
#define COMP_STS_VAL_MSK                         ((uint32_t)0x00000004)

/**
  * @}
  */ 

/** @defgroup COMP_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the comparator registers to default value.
  * @param  None.
  * @retval None
  * @note   two comparator have same reset signal  
  */
void COMP_DeInit(void)
{
  SYSCFGLP_PeriphReset(SYSCFGLP_PeriphReset_COMP);
}

/**
  * @brief  Initialize the comparator according to the specified
  *         parameters in the COMP_InitStruct.
  * @param  COMPx: where x can be 0, 1 to select the comparator.
  * @param  COMP_InitStruct: pointer to a comparator structure that
  *         contains the configuration information for the specified comparator.
  * @retval None
  */
void COMP_Init(COMP_Type* COMPx, COMP_InitType* COMP_InitStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  assert_parameters(IS_COMP_MODE(COMP_InitStruct->COMP_Mode));
  assert_parameters(IS_FUNCTIONAL_STATE(COMP_InitStruct->COMP_HystEn));
  assert_parameters(IS_COMP_OUTPUT(COMP_InitStruct->COMP_OutputLevel));
  assert_parameters(IS_COMP_FILTER_CLKDIV(COMP_InitStruct->COMP_FilterClkDiv));
  assert_parameters(IS_COMP_FILTER_Period(COMP_InitStruct->COMP_FilterClkPeriod));
  
  tmpreg = (COMP_InitStruct->COMP_HystEn<<COMP_HystEn_POS ) | \
           (COMP_InitStruct->COMP_Mode                    ) | \
           (COMP_InitStruct->COMP_FilterClkPeriod         ) | \
           (COMP_InitStruct->COMP_FilterClkDiv);
  MODIFY_REG(COMPx->CMP_CTRL, COMP_CR_MSK, tmpreg);

  if(COMP_InitStruct->COMP_OutputLevel != COMP_Output_Negative)
  {
     SET_BIT(COMPx->CMP_EN,COMP_Output_Positive);
  }
  else
  {
     CLEAR_BIT(COMPx->CMP_EN,COMP_Output_Positive);
  } 
}

/**
  * @brief  Fill each COMP_InitStruct member with default value.
  * @param  COMP_InitStruct : pointer to a COMP_InitType structure which will 
  *         be initialized.
  * @retval None
  */
void COMP_StructInit(COMP_InitType* COMP_InitStruct)
{
  COMP_InitStruct->COMP_Mode = COMP_Mode_HighSpeed;
  COMP_InitStruct->COMP_HystEn = ENABLE;
  COMP_InitStruct->COMP_OutputLevel = COMP_Output_Positive;
  COMP_InitStruct->COMP_FilterClkDiv = COMP_Filter_ClkDiv_1;
  COMP_InitStruct->COMP_FilterClkPeriod = COMP_Filter_Period_0;
}

/**
  * @brief  Configure comparator wakeup parameter.
  * @param  COMPx: where x can be 0, 1 to select the COMP peripheral.
  * @param  WkuSrc: select sourece for wakeup detection
  *   This parameter can be: COMP_WAKEUP_SEL_FILTERED or COMP_WAKEUP_SEL_UNFILTERED.
  *     @arg COMP_WKU_SRC_FILTER :select comparator output(filtered output as input for wakeup detection)
  *     @arg COMP_WKU_SRC_UNFILTER:  select comparator raw output(unfiltered) as input for wakeup detection.
  * @param  WakeupTrig: select the sensitive level or pluse to  trig comparator wakeup  
  *   This parameter can be any combination of the following values:
  *     @arg COMP_WKU_EDGE_DISABLE :Select analog comparator edge and level sensitive is disabled
  *     @arg COMP_WKU_RISING:  Select analog comparator rising edge for wakeup sensitive.
  *     @arg COMP_WKU_FALLING : Select analog comparator falling edge for wakeup sensitive
  *     @arg COMP_WKU_BOTH:  Select analog comparator rising and falling edge for wakeup sensitive
  *     @arg COMP_WKU_LEVEL_DISABLE:  Select analog comparator rising and falling edge for wakeup sensitive
  *     @arg COMP_WKU_HIGH :Select analog comparator high level for wakeup sensitive
  *     @arg COMP_WKU_LOW: Select analog comparator low level for wakeup sensitive
  * @retval None
  */
void COMP_WKUInit(COMP_Type* COMPx, uint32_t WkuSrc, uint32_t WkuTrig)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  assert_parameters(IS_COMP_WKU_SRC(WkuSrc));
  assert_parameters(IS_COMP_WKU_TYPE(WkuTrig));

  tmpreg = WkuSrc | WkuTrig;
  MODIFY_REG(COMPx->WKU_CTRL, COMP_WKU_MSK, tmpreg);
}

/**
  * @brief  Enables or disables the specified comparator wakeup.
  * @param  COMPx: where x can be 0, 1 to select the comparator peripheral.
  * @param  NewState: new state of the specified comparator wakeup
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMP_WKUCmd(COMP_Type* COMPx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected COMP  WakeUp */
     SET_BIT(COMPx->WKU_CTRL,ENABLE);
  }
  else
  {
     /* Disable the selected COMP WakeUp */
     CLEAR_BIT(COMPx->WKU_CTRL,ENABLE);
  }
}

/**
  * @brief  Enables or disables the specified comparator.
  * @param  COMPx: where x can be 0, 1 to select the comparator peripheral.
  * @param  NewState: new state of the specified comparator enable
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMP_Cmd(COMP_Type* COMPx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the COMP*/
    SET_BIT(COMPx->CMP_EN,ENABLE);  
  }
  else
  {
    /* Disable the COMP*/
    CLEAR_BIT(COMPx->CMP_EN,ENABLE);
  }
}

/**
  * @brief  Return the output level (high or low) of the selected comparator. 
  *         The output level depends on the selected polarity.
  * @param  COMPx: where x can be 0, 1 to select the comparator peripheral.
  * @retval Returns the selected comparator output level: 
            RESET: comparator output low level
            SET: comparator output high level    
  */
FlagStatus COMP_GetOutputVal(COMP_Type* COMPx)
{
  /* Check the parameters */
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  
  if(READ_BIT(COMPx->INT_STATUS, COMP_STS_VAL_MSK))
  {
     return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Enables or disables the specified comparator peripheral interrupts.
  * @param  COMPx: where x can be 0, 1 to select the COMP peripheral.
  * @param  LPulseTime: LPulseTime  can be 0~255.
  * @param  NewState: new state of the specified comparator interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMP_LPulseTime_Config(COMP_Type* COMPx, uint32_t LPulseTime, FunctionalState NewState)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  assert_parameters(IS_COMP_LPULSE_TIME(LPulseTime));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmpreg = (LPulseTime<<LPulseTime_POS);
  MODIFY_REG(COMPx->PULSE, COMP_LPULSE_TIME_MSK, tmpreg);

  if (NewState != DISABLE)
  {
    SET_BIT(COMPx->PULSE, ENABLE);
  }
  else
  {
    CLEAR_BIT(COMPx->PULSE, ENABLE);
  }
}

/**
  * @brief Configure comparator interrupt parameter.
  * @param  COMPx: where x can be 0, 1 to select the COMP peripheral.
  * @param  WkuSrc: select sourece for wakeup detection
  *   This parameter can be: COMP_WAKEUP_SEL_FILTERED or COMP_WAKEUP_SEL_UNFILTERED.
  *     @arg COMP_WKU_SRC_FILTER :select comparator output(filtered output as input for wakeup detection)
  *     @arg COMP_WKU_SRC_UNFILTER:  select comparator raw output(unfiltered) as input for wakeup detection.
  * @param  WakeupTrig: select the sensitive level or pluse to  trig comparator wakeup  
  *   This parameter can be any combination of the following values:
  *     @arg COMP_WKU_EDGE_DISABLE :Select analog comparator edge and level sensitive is disabled
  *     @arg COMP_WKU_RISING:  Select analog comparator rising edge for wakeup sensitive.
  *     @arg COMP_WKU_FALLING : Select analog comparator falling edge for wakeup sensitive
  *     @arg COMP_WKU_BOTH:  Select analog comparator rising and falling edge for wakeup sensitive
  *     @arg COMP_WKU_LEVEL_DISABLE:  Select analog comparator rising and falling edge for wakeup sensitive
  *     @arg COMP_WKU_HIGH :Select analog comparator high level for wakeup sensitive
  *     @arg COMP_WKU_LOW: Select analog comparator low level for wakeup sensitive
  * @param  NewState: new state of the specified comparator interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMP_INTConfig(COMP_Type* COMPx, uint32_t IntSrc, uint32_t IntType,FunctionalState NewState)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  assert_parameters(IS_COMP_INT_SRC(IntSrc));
  assert_parameters(IS_COMP_INT_TYPE(IntType));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmpreg = IntSrc | IntType;
  MODIFY_REG(COMPx->INT_CTRL, COMP_INT_CTRL_MSK, tmpreg);

  if (NewState != DISABLE)
  {
    SET_BIT(COMPx->INT_CTRL, ENABLE);
  }
  else
  {
    CLEAR_BIT(COMPx->INT_CTRL, ENABLE);
  }
}


/**
  * @brief  Check the COMPx's interrupt status 
  * @param  COMPx: where x can be 0, 1 to select the comparator peripheral.
  * @retval The new state of COMP_INT (SET or RESET).
  */
INTStatus COMP_GetINTStatus(COMP_Type* COMPx)
{
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));

  if(RESET != READ_BIT(COMPx->INT_STATUS, COMP_INT_STS))
  {
     return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Check the COMPx's wakeup status .
  * @param  COMPx: where x can be 0, 1 to select the comparator peripheral.
  * @retval The new state of COMP_WKU_STS (SET or RESET).
  */
INTStatus COMP_GetWKUStatus(COMP_Type* COMPx)
{
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));

  if(RESET != READ_BIT(COMPx->INT_STATUS, COMP_WKU_STS))
  {
     return SET;
  }
  else
  {
    return RESET;
  }
}


/**
  * @brief  Clear the COMPx's interrupt status
  * @param  COMPx: where x can be 0, 1 to select the comparator peripheral.
  * @retval None
  */
void COMP_ClearINTStatus(COMP_Type* COMPx)
{
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  
  WRITE_REG(COMPx->INT_STATUS, COMP_INT_STS);
}


/**
  * @brief  Clear the COMPx's wakeup status
  * @param  COMPx: where x can be 0, 1 to select the comparator peripheral.
  * @retval None
  */
void COMP_ClearWKUStatus(COMP_Type* COMPx)
{
  assert_parameters(IS_COMP_ALL_INSTANCE(COMPx));
  
  WRITE_REG(COMPx->INT_STATUS, COMP_WKU_STS);
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/*********************************** END OF FILE ******************************/
