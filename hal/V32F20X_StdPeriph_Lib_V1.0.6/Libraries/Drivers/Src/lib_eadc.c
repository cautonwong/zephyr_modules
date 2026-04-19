/**
  ******************************************************************************
  * @file    lib_eadc.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-11-3
  * @brief   This file provides all the EADC firmware functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  *//**
  * @brief  This function handles ADC0 global interrupts requests.
  * @param  None
  * @retval None
  */

#include "lib_syscfg.h"
#include "lib_eadc.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup EADC
  * @brief EADC driver modules
  * @{
  */

/** @defgroup EADC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup EADC_Private_Defines
  * @{
  */
#define EADC_FLAG_CP_RESET                  ((uint32_t)0x0000000F)
#define EADC_ADC_CLK_DIV_RESET              ((uint32_t)0x00FF0000)
#define EADC_CDMA_CLK_DIV_RESET             ((uint32_t)0x0E000000)
/**
  * @}
  */

/** @defgroup EADC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the EADC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void EADC_DeInit(void)
{
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_EADC);

  CLEAR_REG(EADC->CFG);
}

/**
  * @brief  Initializes the EADC peripheral according to the specified 
  *         parameters in the EADC_InitStruct.
  * @param  EADC_InitStruct: pointer to a EADC_InitTypeDef structure that
  *        contains the configuration information for the specified EADC channel.
  * @retval None
  */
void EADC_Init(EADC_InitType* EADC_InitStruct)
{  
  /* Check the EADC parameters */
  assert_parameters(IS_EADC_SYN_STEP(EADC_InitStruct->EADC_SynStep));
  assert_parameters(IS_EADC_CDMA_MODE(EADC_InitStruct->EADC_CdmaMode));
  assert_parameters(IS_EADC_SEQ_SETS_NUM(EADC_InitStruct->EADC_SeqSetsNum));
  assert_parameters(IS_EADC_CDMA_CLK_DIV(EADC_InitStruct->EADC_CdmaClkFreqDiv));
  
  if (EADC_InitStruct->EADC_CdmaMode != EADC_CDMA_MODE_ENABLE)
  {
    EADC_InitStruct->EADC_CdmaClkFreqDiv = EADC_CDMA_CLK_DIV_1;
  }
    
  CLEAR_BIT(EADC->CFG, (EADC_SEQ_SETS_NUM_RESET | \
                        EADC_CDMA_MODE_RESET  | \
                        EADC_SYN_STEP_RESET| \
                        EADC_ADC_CLK_DIV_RESET | \
                        EADC_CDMA_CLK_DIV_RESET));
  
  SET_BIT(EADC->CFG, ((EADC_InitStruct->EADC_SeqSetsNum) | \
                       EADC_InitStruct->EADC_CdmaMode | \
                       EADC_InitStruct->EADC_SynStep | \
                      (EADC_InitStruct->EADC_ClkOutFreqDiv << 16) | \
                       EADC_InitStruct->EADC_CdmaClkFreqDiv ));  
}

/**
  * @brief  Fills each EADC_InitStruct member with its default value.
  * @param  EADC_InitStruct : pointer to a EADC_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void EADC_StructInit(EADC_InitType* EADC_InitStruct)
{
  EADC_InitStruct->EADC_ClkOutFreqDiv = 0;
  EADC_InitStruct->EADC_CdmaMode = EADC_CDMA_MODE_DISABLE;
  EADC_InitStruct->EADC_SeqSetsNum = EADC_SEQ_SETS_NUM_2;
  EADC_InitStruct->EADC_SynStep = EADC_SYN_STEP_64;
  
}

/**
  * @brief  Configures the EADC channel 
  * @param  EADC_Channel: the selected EADC channel. 
  *   This parameter can be one of the following values:
  *     @arg EADC_CHANNEL_0: EADC Channel 0 selected
  *     @arg EADC_CHANNEL_1: EADC Channel 1 selected
  *     @arg EADC_CHANNEL_2: EADC Channel 2 selected
  *     @arg EADC_CHANNEL_3: EADC Channel 3 selected
  *     @arg EADC_CHANNEL_4: EADC Channel 4 selected
  *     @arg EADC_CHANNEL_5: EADC Channel 5 selected
  *     @arg EADC_CHANNEL_6: EADC Channel 6 selected
  *     @arg EADC_CHANNEL_7: EADC Channel 7 selected
  * @param  capturePoint: capture point of EADC channel,the vaule must be[0, 127]
  * @param  triggerEdge: select EADC channel capture point trigger  
  *   This parameter can be one of the following values:
  *     @arg EADC_CP_TRIG_POS: positive selected
  *     @arg EADC_CP_TRIG_NEG: negitive selected
  * @retval None
  */
void EADC_Channel_Config(uint32_t EADC_Channel, uint32_t capturePoint, uint32_t triggerEdge)
{
  uint32_t u32Temp1 = 0, u32Temp2 = 0;
  
  /* Check the EADC parameters */
  assert_parameters(IS_EADC_CHANNEL(EADC_Channel)); 
  assert_parameters(IS_EADC_CP(capturePoint)); 
  assert_parameters(IS_EADC_Trigger_Edge(triggerEdge)); 
      
  switch(EADC_Channel)
  {
    case EADC_CHANNEL_0:
    case EADC_CHANNEL_4:
      u32Temp1 = EADC_FLAG_CP_RESET;
      u32Temp2 =((triggerEdge << 7) | capturePoint);
      break;  
    case EADC_CHANNEL_1:
    case EADC_CHANNEL_5:    
      u32Temp1 = (EADC_FLAG_CP_RESET << 8);
      u32Temp2 =((triggerEdge << 15) | (capturePoint << 8));
      break;    
    case EADC_CHANNEL_2:
    case EADC_CHANNEL_6:    
      u32Temp1 = (EADC_FLAG_CP_RESET << 16);
      u32Temp2 =((triggerEdge << 23) | (capturePoint << 16));
      break;    
    case EADC_CHANNEL_3:
    case EADC_CHANNEL_7:
      u32Temp1 = (EADC_FLAG_CP_RESET << 24);
      u32Temp2 =((triggerEdge << 31) | (capturePoint << 24));
      break;    
    default:
      break;  
  }
   
  if (EADC_Channel <= EADC_CHANNEL_3)   
  {
    CLEAR_BIT(EADC->CP0, u32Temp1);
    SET_BIT(EADC->CP0, u32Temp2);
  }
  else
  {
    CLEAR_BIT(EADC->CP1, u32Temp1);
    SET_BIT(EADC->CP1, u32Temp2);
  }
  
}

/**
  * @brief  Enables or disables the specified EADC channel.
  * @param  EADC_CLKMode: the selected EADC channel. 
  * @param  EADC_Channel: the selected EADC channel. 
  *   This parameter can be one or more the following values:
  *     @arg EADC_CHANNEL_0: EADC Channel 0 selected
  *     @arg EADC_CHANNEL_1: EADC Channel 1 selected
  *     @arg EADC_CHANNEL_2: EADC Channel 2 selected
  *     @arg EADC_CHANNEL_3: EADC Channel 3 selected
  *     @arg EADC_CHANNEL_4: EADC Channel 4 selected
  *     @arg EADC_CHANNEL_5: EADC Channel 5 selected
  *     @arg EADC_CHANNEL_6: EADC Channel 6 selected
  *     @arg EADC_CHANNEL_7: EADC Channel 7 selected
  * @param  NewState: new state of the EADC channel. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EADC_Cmd(uint32_t EADC_CLKMode, uint32_t EADC_Channel, FunctionalState NewState)
{
  uint32_t tmp = 0;
  /* Check the parameters */
  assert_parameters(IS_EADC_CHANNEL_ALL(EADC_Channel));
  assert_parameters(IS_EADC_CLK_MODE(EADC_CLKMode));
  EADC_Channel &= 0x000000FF; 
  tmp = EADC->CFG;

  if (EADC_CLK_OUT == EADC_CLKMode)
  {
    tmp |= EADC_CLK_OUT;
  }
  else
  {
    tmp &= (~EADC_CLK_OUT);
  }
  
  if (NewState != DISABLE)
  {
    /* Enable the selected EADC channel */
    tmp |= EADC_Channel;
  }
  else
  {
    /* Disable the selected EADC channel */
    tmp &= ~EADC_Channel;
  }

  EADC->CFG = tmp;
}



/**
  * @brief  Get the synchronization failed times of Channel.
  * @param  EADC_Channel: the selected EADC channel. 
  *   This parameter can be one of the following values:
  *     @arg EADC_CHANNEL_0: EADC Channel1 selected
  *     @arg EADC_CHANNEL_1: EADC Channel2 selected
  * @retval The the synchronization failed times.
  */
uint32_t EADC_GetSynFailNumber(uint32_t EADC_Channel)
{
  uint32_t u32Temp = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_EADC_SYN_FAIL_CHANNEL(EADC_Channel));
  
  if (EADC_CHANNEL_0 == EADC_Channel)
  {
    u32Temp = READ_BIT(EADC->INTSTS, EADC_STS_SYN_FAIL_NUM_CH0);
  }
  else 
  {
    u32Temp = READ_BIT(EADC->INTSTS, EADC_STS_SYN_FAIL_NUM_CH1);
  }
    
  return u32Temp;
}

/**
  * @brief  Check the EADC status .
  * @param  EADC_FLAG: specifies the status to check.
  *          This parameter can be one of the following values:
  *            @arg EADC_STS_FIFO: FIFO not empty
  * @retval The new state of EADC_STS_FIFO (SET or RESET).
  */
FlagStatus EADC_GetFlagStatus(uint32_t EADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t u32Temp = 0;
 
  /* Check the parameters */ 
  assert_parameters(IS_EADC_STATUS(EADC_FLAG));
  
  u32Temp = READ_BIT(EADC->INTSTS, EADC_STS_FIFO);  
  if(u32Temp != (uint32_t)RESET)
  {
     bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/**
  * @brief  Enables or disables EADC specified interrupt.
  * @param  EADC_INT: specifies the EADC interrupt source to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg EADC_INT_OVF: Error of overflow interrupt
  *     @arg EADC_INT_UDF: Error of under flow interrupt
  *     @arg EADC_INT_SYN_FAIL_CH0: channel 0 synchronization fail number (bigger than 5 ) interrupt
  *     @arg EADC_INT_SYN_FAIL_CH1: channel 1 synchronization fail number (bigger than 5 ) interrupt
  * @param  NewState: new state of the specified EADC interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EADC_INTConfig(uint32_t EADC_INT, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_EADC_INT(EADC_INT));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
    
  if (NewState != DISABLE)
  {
    SET_BIT(EADC->INTEN, EADC_INT);    
  }
  else
  {
    CLEAR_BIT(EADC->INTEN, EADC_INT);
  }
}

/**
  * @brief  Gets EADC specified interrupt status.
  * @param  EADC_INT: specifies the EADC interrupt source to check.
  *         This parameter can be one of the following values:
  *     @arg EADC_INT_OVF: Error of overflow interrupt
  *     @arg EADC_INT_UDF: Error of under flow interrupt
  *     @arg EADC_INT_SYN_FAIL_CH0: channel 0 synchronization fail number (bigger than 5 ) interrupt
  *     @arg EADC_INT_SYN_FAIL_CH1: channel 1 synchronization fail number (bigger than 5 ) interrupt
  * @retval  The new state of EADC specified interrupt status (SET or RESET).
  */
INTStatus EADC_GetINTStatus(uint32_t EADC_INT)
{
  uint32_t u32Temp = 0UL;
  FlagStatus bitstatus = RESET;
  
  /* Check parameters */
  assert_parameters(IS_EADC_INT(EADC_INT));
  
  switch (EADC_INT)
  {
    case EADC_INT_OVF:
    case EADC_INT_UDP:
      u32Temp = READ_BIT(EADC->INTSTS, EADC_INT);  
      break;
    case EADC_INT_SYN_FAIL_CH0:
      u32Temp = READ_BIT(EADC->INTSTS, EADC_STS_SYN_FAIL_CH0);  
      break; 
    case EADC_INT_SYN_FAIL_CH1:
      u32Temp = READ_BIT(EADC->INTSTS, EADC_STS_SYN_FAIL_CH1);  
      break;  
    default:
      break;      
  }
  
  if(u32Temp != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return  bitstatus;
}

/**
  * @brief  Clear EADC specified interrupt status.
  * @param  EADC_INT: specifies the EADC interrupt source to check.
  *         This parameter can be one of the following values:
  *     @arg EADC_INT_OVF: Error of overflow interrupt
  *     @arg EADC_INT_UDF: Error of under flow interrupt
  *     @arg EADC_INT_SYN_FAIL_CH0: channel 0 synchronization fail number (bigger than 5 ) interrupt
  *     @arg EADC_INT_SYN_FAIL_CH1: channel 1 synchronization fail number (bigger than 5 ) interrupt
  * @retval  The new state of EADC specified interrupt status (SET or RESET).
  */
void EADC_ClearINTStatus(uint32_t EADC_INT)
{
  /* Check parameters */
  assert_parameters(IS_EADC_INT(EADC_INT));

  switch (EADC_INT)
  {
    case EADC_INT_OVF:
    case EADC_INT_UDP:
      WRITE_REG(EADC->INTSTS, EADC_INT);  
      break; 
    case EADC_INT_SYN_FAIL_CH0:
      WRITE_REG(EADC->INTSTS, EADC_STS_SYN_FAIL_CH0);  
      break;
    case EADC_INT_SYN_FAIL_CH1:
      WRITE_REG(EADC->INTSTS, EADC_STS_SYN_FAIL_CH1);  
      break;  
    default:
      break;    
  }
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

