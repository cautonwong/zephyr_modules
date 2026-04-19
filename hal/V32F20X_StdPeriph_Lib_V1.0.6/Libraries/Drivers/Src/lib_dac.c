/**
  ******************************************************************************
  * @file    lib_dac.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Dac library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lib_dac.h"
#include "target.h"


/** @defgroup DAC_Private_Defines
  * @{
  */
/* CR register Mask */ 
#define DAC_CR_CLEAR_MASK                            ((uint32_t)0x00000FFE)

/* DAC channel1 enable */
#define DAC_CR_EN1                                   ((uint32_t)0x00000001)

/* DAC channel1 DMA enable */
#define DAC_CR_DMAEN1                                ((uint32_t)0x00001000)

/* DAC one Channels SWTRIG masks */
#define DAC_SWTRIGR_SWTRIG1                          ((uint32_t)0x00000001)

/* DAC Dual Channels SWTRIG masks */
#define DAC_DUAL_SWTRIG_SET                          ((uint32_t)0x00000003)

/* DOR register offset */
#define DAC_DOR_OFFSET                               ((uint32_t)0x0000002C)


/** @defgroup DAC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void DAC_DeInit(void)
{
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_DAC);
}

/**
  * @brief  Initializes the DAC peripheral according to the specified 
  *         parameters in the DAC_InitStruct.
  * @param  DAC_Channel: the selected DAC channel. 
  *   This parameter can be one of the following values:
  *     @arg DAC_CHANNEL_0: DAC Channel 0 selected
  *     @arg DAC_CHANNEL_1: DAC Channel 1 selected
  * @param  DAC_InitStruct: pointer to a DAC_InitType structure that
  *        contains the configuration information for the specified DAC channel.
  * @retval None
  */
void DAC_Init(uint32_t DAC_Channel, DAC_InitType* DAC_InitStruct)
{
  /* Check the DAC parameters */
  assert_parameters(IS_DAC_CHANNEL(DAC_Channel));
  assert_parameters(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
  assert_parameters(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
  assert_parameters(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
  assert_parameters(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));

  /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
  CLEAR_BIT(DAC->CR, (DAC_CR_CLEAR_MASK << DAC_Channel));
  
  /* Configure for the selected DAC channel: buffer output, trigger, wave generation,
     mask/amplitude for wave generation */
  /* Set TSELx and TENx bits according to DAC_Trigger value */
  /* Set WAVEx bits according to DAC_WaveGeneration value */
  /* Set MAMPx bits according to DAC_LFSRUnmask_TriangleAmplitude value */ 
  /* Set BOFFx bit according to DAC_OutputBuffer value */   
  /* Calculate CR register value depending on DAC_Channel and Write to DAC CR */
  SET_BIT(DAC->CR, ((DAC_InitStruct->DAC_Trigger | \
                    DAC_InitStruct->DAC_WaveGeneration | \
                    DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | \
                    DAC_InitStruct->DAC_OutputBuffer) << DAC_Channel));
                    
}

/**
  * @brief  Fills each DAC_InitStruct member with its default value.
  * @param  DAC_InitStruct : pointer to a DAC_InitType structure which will
  *         be initialized.
  * @retval None
  */
void DAC_StructInit(DAC_InitType* DAC_InitStruct)
{
  /*--------------- Reset DAC init structure parameters values -----------------*/
  /* Initialize the DAC_Trigger member */
  DAC_InitStruct->DAC_Trigger = DAC_TRIGGER_NONE;
  /* Initialize the DAC_WaveGeneration member */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WAVE_GENERATION_NONE;
  /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSR_UNMASK_BIT0;
  /* Initialize the DAC_OutputBuffer member */
  DAC_InitStruct->DAC_OutputBuffer = DAC_OUTPUT_BUFFER_ENABLE;
}

/**
  * @brief  Enables or disables the specified DAC channel.
  * @param  DAC_Channel: the selected DAC channel. 
  *   This parameter can be one of the following values:
  *     @arg DAC_CHANNEL_0: DAC Channel 0 selected
  *     @arg DAC_CHANNEL_1: DAC Channel 1 selected
  * @param  NewState: new state of the DAC channel. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_DAC_CHANNEL(DAC_Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel */
    SET_BIT(DAC->CR, (DAC_CR_EN1 << DAC_Channel));
  }
  else
  {
    /* Disable the selected DAC channel */
    CLEAR_BIT(DAC->CR, (DAC_CR_EN1 << DAC_Channel));
  }
}

/**
  * @brief  Enables or disables the specified DAC channel DMA request.
  * @param  DAC_Channel: the selected DAC channel. 
  *   This parameter can be one of the following values:
  *     @arg DAC_CHANNEL_0: DAC Channel 0 selected
  *     @arg DAC_CHANNEL_1: DAC Channel 1 selected
  * @param  NewState: new state of the selected DAC channel DMA request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_DAC_CHANNEL(DAC_Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel DMA request */
    SET_BIT(DAC->CR, (DAC_CR_DMAEN1 << DAC_Channel));
  }
  else
  {
    /* Disable the selected DAC channel DMA request */
    CLEAR_BIT(DAC->CR, (DAC_CR_DMAEN1 << DAC_Channel));
  }
}

/**
  * @brief  Enables or disables the selected DAC channel software trigger.
  * @param  DAC_Channel: the selected DAC channel. 
  *   This parameter can be one of the following values:
  *     @arg DAC_CHANNEL_0: DAC Channel 0 selected
  *     @arg DAC_CHANNEL_1: DAC Channel 1 selected
  * @param  NewState: new state of the selected DAC channel software trigger.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_DAC_CHANNEL(DAC_Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
 
  if (NewState != DISABLE)
  {
    /* Enable software trigger for the selected DAC channel */
    SET_BIT(DAC->SWTRGR, (uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4));     
  }
  else
  {
    /* Disable software trigger for the selected DAC channel */
    CLEAR_BIT(DAC->SWTRGR, (uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4));     
  }
}

/**
  * @brief  Enables or disables simultaneously the two DAC channels software
  *   triggers.
  * @param  NewState: new state of the DAC channels software triggers.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
 
  if (NewState != DISABLE)
  {
    /* Enable software trigger for both DAC channels */
    SET_BIT(DAC->SWTRGR, DAC_DUAL_SWTRIG_SET);
  }
  else
  {
    /* Disable software trigger for both DAC channels */
    CLEAR_BIT(DAC->SWTRGR, DAC_DUAL_SWTRIG_SET);
  }
}

/**
  * @brief  Enables or disables the selected DAC channel wave generation.
  * @param  DAC_Channel: the selected DAC channel. 
  *   This parameter can be one of the following values:
  *     @arg DAC_CHANNEL_0: DAC Channel 0 selected
  *     @arg DAC_CHANNEL_1: DAC Channel 1 selected
  * @param  DAC_Wave: Specifies the wave type to enable or disable.
  *   This parameter can be one of the following values:
  *     @arg DAC_WAVE_NOISE: noise wave generation
  *     @arg DAC_WAVE_TRIANGLE: triangle wave generation
  * @param  NewState: new state of the selected DAC channel wave generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_DAC_CHANNEL(DAC_Channel));
  assert_parameters(IS_DAC_WAVE(DAC_Wave)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
 
  if (NewState != DISABLE)
  {
    /* Enable the selected wave generation for the selected DAC channel */
    SET_BIT(DAC->CR, (DAC_Wave << DAC_Channel));
  }
  else
  {
    /* Disable the selected wave generation for the selected DAC channel */
    CLEAR_BIT(DAC->CR, (DAC_Wave << DAC_Channel));
  }
}

/**
  * @brief  Set the specified data holding register value for DAC channel 0.
  * @param  DAC_Align: Specifies the data alignment for DAC channel1.
  *   This parameter can be one of the following values:
  *     @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
  *     @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
  *     @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
  * @param  Data : Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannel0Data(uint32_t DAC_Align, uint16_t Data)
{  
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_parameters(IS_DAC_ALIGN(DAC_Align));
  assert_parameters(IS_DAC_DATA(Data));
  
  tmp =(uint32_t)&DAC->DHR12R1 + DAC_Align;
  /* Set the DAC channel1 selected data holding register */
  *(__IO uint32_t *) tmp = Data;
}

/**
  * @brief  Set the specified data holding register value for DAC channel 1.
  * @param  DAC_Align: Specifies the data alignment for DAC channel2.
  *   This parameter can be one of the following values:
  *     @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
  *     @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
  *     @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
  * @param  Data : Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_parameters(IS_DAC_ALIGN(DAC_Align));
  assert_parameters(IS_DAC_DATA(Data));
    
  tmp =(uint32_t)&DAC->DHR12R2 + DAC_Align;
  
  /* Set the DAC channel2 selected data holding register */
  *(__IO uint32_t *)tmp = Data;
}

/**
  * @brief  Set the specified data holding register value for dual channel
  *   DAC.
  * @param  DAC_Align: Specifies the data alignment for dual channel DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
  *     @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
  *     @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
  * @param  Data1: Data for DAC Channel 1 to be loaded in the selected data 
  *   holding register.
  * @param  Data0: Data for DAC Channel 0 to be loaded in the selected data 
  *   holding register.
  * @retval None
  */
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data1, uint16_t Data0)
{
  uint32_t data = 0, tmp = 0;
  
  /* Check the parameters */
  assert_parameters(IS_DAC_ALIGN(DAC_Align));
  assert_parameters(IS_DAC_DATA(Data0));
  assert_parameters(IS_DAC_DATA(Data1));
  
  /* Calculate and set dual DAC data holding register value */
  if (DAC_Align == DAC_ALIGN_8B_R)
  {
    data = ((uint32_t)Data1 << 8) | Data0; 
  }
  else
  {
    data = ((uint32_t)Data1 << 16) | Data0;
  }
  
  tmp =(uint32_t)&DAC->DHR12RD +DAC_Align;

  /* Set the dual DAC selected data holding register */
  *(__IO uint32_t *)tmp = data;
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  DAC_Channel: the selected DAC channel. 
  *   This parameter can be one of the following values:
  *     @arg DAC_CHANNEL_0: DAC Channel 0 selected
  *     @arg DAC_CHANNEL_1: DAC Channel 1 selected
  * @retval The selected DAC channel data output value.
  */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel)
{
  __IO uint32_t tmp = 0;
 
  /* Check the parameters */
  assert_parameters(IS_DAC_CHANNEL(DAC_Channel));
  
  tmp = (uint32_t) DAC_BASE ;
  tmp += DAC_DOR_OFFSET + ((uint32_t)DAC_Channel >> 2);

  /* Returns the DAC channel data output register value */
  return (uint16_t) (*(__IO uint32_t*) tmp);
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