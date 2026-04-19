/**
  * @file    lib_rtc_comp.c
  * @author  Application Team
  * @version V1.0
  * @date    2021-10-14
  * @brief   This file provides all the RTC_COMP firmware functions.
******************************************************************************/

#include "lib_rtc_comp.h"
#include "lib_rtc_ex.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup RTC_COMP
  * @brief RTC_COMP driver modules
  * @{
  */

/** @defgroup RTC_COMP_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_COMP_Private_Defines
  * @{
  */

/*RTC_COMP_CFG Register*/
#define RTC_COMP_Filter_Period_MSK               ((uint32_t)0x00030000)
#define RTC_COMP_CLK_DIV_MSK                     ((uint32_t)0x001c0000)
#define RTC_COMP_CFG_MSK                         (RTC_COMP_Filter_Period_MSK | RTC_COMP_CLK_DIV_MSK)
#define RTC_COMP_ENBALE                          ((uint32_t)0x00000001)
#define RTC_COMP_INT_ENBALE                      ((uint32_t)0x00000002)
#define RTC_COMP_OUT_MSK                         ((uint32_t)0x01000000)
#define RTC_COMP_WKU_ENBALE                      ((uint32_t)0x00000008)
#define RTC_COMP_INT_MSK                         ((uint32_t)0x00000004)

/*RTC_COMP_WKU_INT Register*/
#define RTC_COMP_INT_STS                         ((uint32_t)0x00000001)
#define RTC_COMP_WKU_STS                         ((uint32_t)0x00010000)
/**
  * @}
  */

/** @defgroup RTC_COMP_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the RTC comparator register to default parameter.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @retval None
  */
void RTC_COMP_DeInit(uint32_t RTC_COMP_Channel)
{
  /* Check the parameters */
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));
  
  RTC_COMP_Cmd(RTC_COMP_Channel, DISABLE);
  
  RTC_COMP_ClearINTStatus(RTC_COMP_Channel);
  RTC_COMP_ClearWKUStatus(RTC_COMP_Channel);
  
}

/**
  * @brief  Initialize the rtc comparator according to the specified
  *         parameters in the RTC_COMP_InitStruct.
  * @param  RTC_COMP_InitStruct: pointer to a RTC_COMP_InitType structure that
  *         contains the configuration information for the specified RTC_COMP Channel.
  * @retval None
  */
void RTC_COMP_Init(RTC_COMP_InitType* RTC_COMP_InitStruct)
{  
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_parameters(IS_RTC_COMP_FILTER_CLKDIV(RTC_COMP_InitStruct->RTC_COMP_FilterClkDiv));
  assert_parameters(IS_RTC_COMP_FILTER_Period(RTC_COMP_InitStruct->COMP_FilterClkPeriod));

  tmpreg = (RTC_COMP_InitStruct->RTC_COMP_FilterClkDiv | \
           (RTC_COMP_InitStruct->COMP_FilterClkPeriod));
  
  MODIFY_REG(RTC_COMP->CMP_CTRL, RTC_COMP_CFG_MSK, tmpreg);
}

/**
  * @brief  Fill each RTC_COMP_InitStruct member with its default value.
  * @param  RTC_COMP_InitStruct : pointer to a RTC_COMP_InitType structure which will 
  *         be initialized.
  * @retval None
  */
void RTC_COMP_StructInit(RTC_COMP_InitType* RTC_COMP_InitStruct)
{
  RTC_COMP_InitStruct->RTC_COMP_FilterClkDiv = RTC_COMP_Filter_ClkDiv_1;
  RTC_COMP_InitStruct->COMP_FilterClkPeriod = RTC_COMP_Filter_Period_0;
}

/**
  * @brief  Configure rtc comparator wakeup initialization parameter.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @param  WkuMode: select the wakeup mode of the comparator .  
  *   This parameter can be any combination of the following values:
  *     @arg RTC_COMP_WKU_HIGH:select high level as analog comparator wakeup mode
  *     @arg RTC_COMP_WKU_LOW: select low level as analog comparator wakeup mode.
  * @retval None
  */
void RTC_COMP_WKUConfig(uint32_t RTC_COMP_Channel,uint32_t WkuMode, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));
  assert_parameters(IS_RTC_COMP_WKUMode(WkuMode));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (WkuMode != RTC_COMP_WKU_HIGH)
  {
     SET_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_WKU_HIGH<<(8*RTC_COMP_Channel)));
  }
  else
  {
     CLEAR_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_WKU_HIGH<<(8*RTC_COMP_Channel)));
  }

  if (NewState != DISABLE)
  {
     SET_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_WKU_ENBALE<<(8*RTC_COMP_Channel)));
  }
  else
  {
     CLEAR_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_WKU_ENBALE<<(8*RTC_COMP_Channel)));
  }

}

/**
  * @brief  Enable or disable the specified rtc comparator.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @param  NewState: new state of the specified comparator enable
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_COMP_Cmd(uint32_t RTC_COMP_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected RTC_COMP*/
    SET_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_ENBALE<<(8*RTC_COMP_Channel)));  
  }
  else
  {
    /* Disable the selected RTC_COMP*/
    CLEAR_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_ENBALE<<(8*RTC_COMP_Channel)));
  }
}

/**
  * @brief  Enables or disables the specified rtc comparator interrupts.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @param  IntMode: select the interrupt mode of the comparator .  
  *   This parameter can be any combination of the following values:
  *     @arg RTC_COMP_INT_LOW:select low level as analog comparator interrupt mode
  *     @arg RTC_COMP_INT_HIGH: select high level as analog comparator interrupt mode.
  * @param  NewState: new state of the specified RTC_COMP interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_COMP_INTConfig(uint32_t RTC_COMP_Channel,uint32_t IntMode, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  assert_parameters(IS_RTC_COMP_INT_MODE(IntMode));

  if (IntMode != RTC_COMP_INT_HIGH)
  {
    /* Enable the selected RTC_COMP  WakeUp */
     SET_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_INT_MSK << (8*RTC_COMP_Channel)));
  }
  else
  {
     /* Disable the selected RTC_COMP WakeUp */
     CLEAR_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_INT_MSK <<  (8*RTC_COMP_Channel)));
  }

  if (NewState != DISABLE)
  {
    SET_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_INT_ENBALE << (8*RTC_COMP_Channel)));
  }
  else
  {
    CLEAR_BIT(RTC_COMP->CMP_CTRL,(RTC_COMP_INT_ENBALE << (8*RTC_COMP_Channel)));
  }

}

/**
  * @brief  Return the output level (high or low) of the selected rtc comparator.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @retval Returns the selected RTC comparator output level: 
            RESET: comparator output low level
            SET: comparator output high level
  */
FlagStatus RTC_COMP_GetOutputVal(uint32_t RTC_COMP_Channel)
{
  
  /* Check the parameters */
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));

  if(READ_BIT(RTC_COMP->CMP_CTRL, (RTC_COMP_OUT_MSK << RTC_COMP_Channel)))
  {
     return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Check the RTC_COMPx's wakeup status.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @retval The new state of RTC_COMP_WKU_STS (SET or RESET).
  */
FlagStatus RTC_COMP_GetWKUStatus(uint32_t RTC_COMP_Channel)
{
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));

  if(READ_BIT(RTC_COMP->CMP_STS, (RTC_COMP_WKU_STS << RTC_COMP_Channel)))
  {
     return SET;
  }
  else
  {
     return RESET;
  }
}

/**
  * @brief  Clear the RTC_COMPx's wakeup status.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @retval None
  */
void RTC_COMP_ClearWKUStatus(uint32_t RTC_COMP_Channel)
{
  /* Check the parameters */
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));
  
  WRITE_REG(RTC_COMP->CMP_STS, (RTC_COMP_WKU_STS << RTC_COMP_Channel));
}

/**
  * @brief  Check whether the specified RTC_COMPx's interrupt status.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @retval The new state of RTC_COMP_INT_STS (SET or RESET).
  */
INTStatus RTC_COMP_GetINTStatus(uint32_t RTC_COMP_Channel)
{
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));
 
  if(READ_BIT(RTC_COMP->CMP_STS, (RTC_COMP_INT_STS << RTC_COMP_Channel)))
  {
     return SET;
  }
  else
  {
     return RESET;
  }
}

/**
  * @brief  Clear the RTC_COMPx's interrupt status.
  * @param  RTC_COMP_Channel: RTC_COMP_Channel can be RTC_COMP_Channel_0, RTC_COMP_Channel_1.
  * @retval None
  */

void RTC_COMP_ClearINTStatus(uint32_t RTC_COMP_Channel)
{
  /* Check the parameters */
  assert_parameters(IS_RTC_COMP_CHANNEL(RTC_COMP_Channel));

  WRITE_REG(RTC_COMP->CMP_STS, (RTC_COMP_INT_STS << RTC_COMP_Channel));
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
