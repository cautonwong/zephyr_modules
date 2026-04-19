/**
  ******************************************************************************
  * @file    lib_btimer.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-05-12
  * @brief   This file provides all the BTMR firmware functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/  
#include "lib_btimer.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup BTMR
  * @brief BTMR driver modules
  * @{
  */

/** @defgroup BTMR_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */
  
/** @defgroup TIM_Private_Defines
  * @{
  */  
/*******************  Bit definition for BTMR CTRL register  ********************/
#define BTMR_CTRL_EN                    ((uint32_t)0x00000001)
#define BTMR_CTRL_EXTEN                 ((uint32_t)0x00000002)
#define BTMR_CTRL_EXTCLK                ((uint32_t)0x00000004)
#define BTMR_CTRL_INTEN                 ((uint32_t)0x00000008)

/*******************  Bit definition for BTMR CTRL register  ********************/
#define BTMR_INTSTS_INTSTS              ((uint32_t)0x00000001)

/************************** BTMR register reset value ***************************/
#define BTMR_CTRL_RSTValue              ((uint32_t)0x00000000)
#define BTMR_VALUE_RSTValue             ((uint32_t)0x00000000)
#define BTMR_RELOAD_RSTValue            ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup TIM_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup TIM_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup TIM_Private_FunctionPrototypes
  * @{
  */
  
/**
  * @}
  */

/** @defgroup TIM_Private_Functions
  * @{
  */
  
/**
  * @brief  Deinitializes the BTMRx peripheral registers to their default reset values.
  * @param  BTMRx: to select the BTMR peripheral.
  *         This parameter can be:
  *         CM0 : BTMR4 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  *         CM33 : BTMR0 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  * @retval None
  */
void BTMR_DeInit(BTMR_Type *BTMRx)
{
  /* Check the parameters */
  assert_parameters(IS_BTMR_ALL_INSTANCE(BTMRx));
  
  /* Disable timer */
  BTMRx->CTRL &= ~BTMR_CTRL_EN;
  
  /* Clear interrupt status */
  BTMRx->INTSTS = BTMR_INTSTS_INTSTS;
  
  /* write default reset values */
  BTMRx->CTRL   = BTMR_CTRL_RSTValue;
  BTMRx->RELOAD = BTMR_RELOAD_RSTValue;
  BTMRx->VALUE  = BTMR_VALUE_RSTValue;
}

/**
  * @brief  Fills each BTMR_InitType member with its default value.
  * @param  BTMR_InitStruct: pointer to an BTMR_InitType structure which will be initialized.
  * @retval None
  */
void BTMR_StructInit(BTMR_InitType *BTMR_InitStruct)
{
  /*--------------- Reset BTMR init structure parameters values ---------------*/
  /* Initialize the ClockSource member */
  BTMR_InitStruct->ExtClk = BTMR_CLKSRC_INTERNAL;
  
  /* Initialize the EXTGT member */
  BTMR_InitStruct->ExtEn = BTMR_EXTEN_DISABLE;
  
  /* Initialize the Period member */
  BTMR_InitStruct->Period = 0;
}

/**
  * @brief  Initializes the BTMRx peripheral according to 
  *         the specified parameters in the BTMR_InitStruct.
  * @param  BTMRx: to select the BTMR peripheral.
  *         This parameter can be:
  *         CM0 : BTMR4 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  *         CM33 : BTMR0 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  * @param  BTMR_InitStruct: pointer to a BTMR_InitStruct structure 
  *         that contains the configuration information for the 
  *         specified BTMRx peripheral.
  *         This parameter can be any combination of the following values:
  *             ExtClk:
  *                 BTMR_CLKSRC_INTERNAL
  *                 BTMR_CLKSRC_EXTERNAL
  *             ExtEn:
  *                 BTMR_EXTEN_DISABLE
  *                 BTMR_EXTEN_ENABLE
  *             Period: the auto-reload value
  * @retval None
  */
void BTMR_Init(BTMR_Type *BTMRx, BTMR_InitType *BTMR_InitStruct)
{
  uint32_t tmp;
  
  /* Check the parameters */
  assert_parameters(IS_BTMR_ALL_INSTANCE(BTMRx)); 
  assert_parameters(IS_BTMR_CLKSRC(BTMR_InitStruct->ExtClk));
  assert_parameters(IS_BTMR_EXTEN(BTMR_InitStruct->ExtEn));
 
  tmp = BTMRx->CTRL;
  tmp &= (uint32_t)(~((uint32_t)(BTMR_CTRL_EXTEN | BTMR_CTRL_EXTCLK)));
  tmp |= (BTMR_InitStruct->ExtClk | BTMR_InitStruct->ExtEn);
  BTMRx->CTRL = tmp;
  BTMRx->VALUE = BTMR_InitStruct->Period;
  BTMRx->RELOAD = BTMR_InitStruct->Period;
}

/**
  * @brief  Enables or disables BTMR interrupt.
  * @param  BTMRx: to select the BTMR peripheral.
  *         This parameter can be:
  *         CM0 : BTMR4 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  *         CM33 : BTMR0 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  * @param  NewState: new state of the specified BTMR interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BTMR_INTConfig(BTMR_Type *BTMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_BTMR_ALL_INSTANCE(BTMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    BTMRx->CTRL |= BTMR_CTRL_INTEN;
  }
  else
  {
    BTMRx->CTRL &= ~BTMR_CTRL_INTEN;
  }
}

/**
  * @brief  Checks whether the BTMR interrupt has occurred or not.
  * @param  BTMRx: to select the BTMR peripheral.
  *         This parameter can be:
  *         CM0 : BTMR4 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  *         CM33 : BTMR0 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  * @retval The new state of BTMR interrupt (SET or RESET).
  */
ITStatus BTMR_GetINTStatus(BTMR_Type *BTMRx)
{
  /* Check the parameters */
  assert_parameters(IS_BTMR_ALL_INSTANCE(BTMRx)); 
  
  if (BTMRx->INTSTS & BTMR_INTSTS_INTSTS)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears the BTMR interrupt status bit.
  * @param  BTMRx: to select the BTMR peripheral.
  *         This parameter can be:
  *         CM0 : BTMR4 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  *         CM33 : BTMR0 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  * @retval None.
  */
void BTMR_ClearINTStatus(BTMR_Type *BTMRx)
{
  /* Check the parameters */
  assert_parameters(IS_BTMR_ALL_INSTANCE(BTMRx));
  
  BTMRx->INTSTS = BTMR_INTSTS_INTSTS;
}

/**
  * @brief  Enables or disables the specified BTMR peripheral.
  * @param  BTMRx: to select the BTMR peripheral.
  *         This parameter can be:
  *         CM0 : BTMR4 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  *         CM33 : BTMR0 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  * @param  NewState: new state of the specified BTMR peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BTMR_Cmd(BTMR_Type *BTMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_BTMR_ALL_INSTANCE(BTMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    BTMRx->CTRL |= BTMR_CTRL_EN;
  }
  else
  {
    BTMRx->CTRL &= ~BTMR_CTRL_EN;
  }
}

/**
  * @brief  Gets the BTMRx Counter value.
  * @param  BTMRx: to select the BTMR peripheral.
  *         This parameter can be:
  *         CM0 : BTMR4 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  *         CM33 : BTMR0 ~ BTMR7, LPBTMR0 ~ LPBTMR1
  * @retval Counter Register value.
  */
uint32_t BTMR_GetCounter(BTMR_Type *BTMRx)
{
  /* Check the parameters */
  assert_parameters(IS_BTMR_ALL_INSTANCE(BTMRx));
  
  /* Get the Counter Register value */
  return (BTMRx->VALUE);
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
