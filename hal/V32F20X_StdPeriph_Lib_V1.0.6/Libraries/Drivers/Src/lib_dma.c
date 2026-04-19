/**
  ******************************************************************************
  * @file    lib_dma.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   DMA library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_dma.h"

/* Private macro -------------------------------------------------------------*/

/**
  * @brief  Deinitializes the DMA Channelx registers to their default reset
  *         values.
  * @param  DMAx_Channely: where x can be (0 or 1), y cna be (0..7) to 
  *         select the DMA and Channel.
  * @retval None
  */
void DMA_DeInit(DMA_Channel_Type* DMAx_Channely)
{
  uint32_t Channel;
  DMA_Type *DMAx;
  
  /* Check the parameters */
  assert_parameters(IS_DMA_CHANNEL_ALL_PERIPH(DMAx_Channely));
  
  /* Get DMA and Channel index */
  DMA_CHANNEL_GET_INDEX(DMAx_Channely, DMAx, Channel);
  
  /* Disable the selected DMA Channelx */
  WRITE_REG(DMAx->CHENREG, (1<<(Channel+8) & (~(1<<Channel))));
  
  /* Reset channel registers to default value */
  WRITE_REG(DMAx_Channely->CTL[0], 1UL);
  WRITE_REG(DMAx_Channely->CTL[1], 0UL);
  WRITE_REG(DMAx_Channely->SAR, 0UL);
  WRITE_REG(DMAx_Channely->DAR, 0UL);
  WRITE_REG(DMAx_Channely->CFG[0], 0UL);
  WRITE_REG(DMAx_Channely->CFG[1], 0UL);
  
  /* Reset interrupt pending bits for DMA Channel */
  WRITE_REG(DMAx->MASKTFR, DMA_INT_Mask_WE0 << Channel);
  WRITE_REG(DMAx->CLEARTFR, DMA_INT_TC0 << Channel);
  WRITE_REG(DMAx->MASKBLOCK, DMA_INT_Mask_WE0 << Channel);
  WRITE_REG(DMAx->CLEARBLOCK, DMA_INT_TC0 << Channel);
  WRITE_REG(DMAx->MASKSRCTRAN, DMA_INT_Mask_WE0 << Channel);
  WRITE_REG(DMAx->CLEARSRCTRAN, DMA_INT_TC0 << Channel);
  WRITE_REG(DMAx->MASKDSTTRAN, DMA_INT_Mask_WE0 << Channel);
  WRITE_REG(DMAx->CLEARDSTTRAN, DMA_INT_TC0 << Channel);
  WRITE_REG(DMAx->MASKERR, DMA_INT_Mask_WE0 << Channel);
  WRITE_REG(DMAx->CLEARERR, DMA_INT_TC0 << Channel);
}

/**
  * @brief  Fills each DMA_InitStruct member with its default value.
  * @param  DMA_InitStruct : pointer to a DMA_InitType structure which will 
  *         be initialized.
  * @retval None
  */
void DMA_StructInit(DMA_InitType* DMA_InitStruct)
{
  DMA_InitStruct->DMA_Mode = DMA_MODE_NORMAL;
  DMA_InitStruct->DMA_DIR = DMA_DIR_Memory2Memory;
  DMA_InitStruct->DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_InitStruct->DMA_SourceTransferWidth = DMA_SourceTransferWidth_8Bit;
  DMA_InitStruct->DMA_DestinationBurstSize = DMA_DestinationBurstSize_1;
  DMA_InitStruct->DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_8Bit;
  DMA_InitStruct->DMA_SourceAddressControl = DMA_SourceAddressControl_Increment;
  DMA_InitStruct->DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStruct->DMA_SourceRequestSelect = DMA_SourceRequestSelect_0;
  DMA_InitStruct->DMA_DestinationRequestSelect = DMA_DestinationRequestSelect_0;
  DMA_InitStruct->DMA_SourceAddress = 0;
  DMA_InitStruct->DMA_DestinationAddress = 0;
  DMA_InitStruct->DMA_TransferSize = 0;
  DMA_InitStruct->DMA_Priority = DMA_Priority_0;
  DMA_InitStruct->DMA_LinkListAddress = 0;
}

/**
  * @brief  Initializes the DMA Channelx according to the specified
  *         parameters in the DMA_InitStruct.
  * @param  DMAx_Channely: where x can be (0 or 1), y cna be (0..7) to 
  *         select the DMA and Channel.
  * @param  DMA_InitStruct: pointer to a DMA_InitType structure that
  *         contains the configuration information for the specified DMA Channel.
  * @retval None
  */
void DMA_Init(DMA_Channel_Type* DMAx_Channely, DMA_InitType* DMA_InitStruct)
{
  uint32_t tmpreg = 0, tmpreg1 = 0, tmpreg2 = 0;
  uint32_t size = 0;
  
  /* Check the parameters */
  assert_parameters(IS_DMA_CHANNEL_ALL_PERIPH(DMAx_Channely));
  assert_parameters(IS_DMA_DIR(DMA_InitStruct->DMA_DIR));
  assert_parameters(IS_DMA_SOURCE_BURST_SIZE(DMA_InitStruct->DMA_SourceBurstSize));
  assert_parameters(IS_DMA_SOURCE_TRANSFER_WIDTH(DMA_InitStruct->DMA_SourceTransferWidth));
  assert_parameters(IS_DMA_DESTINATION_BURST_SIZE(DMA_InitStruct->DMA_DestinationBurstSize));
  assert_parameters(IS_DMA_DESTINATION_TRANSFER_WIDTH(DMA_InitStruct->DMA_DestinationTransferWidth));
  assert_parameters(IS_DMA_SOURCE_ADDRESS_CONTROL(DMA_InitStruct->DMA_SourceAddressControl));
  assert_parameters(IS_DMA_DESTINATION_ADDRESS_CONTROL(DMA_InitStruct->DMA_DestinationAddressControl));
  assert_parameters(IS_DMA_SOURCE_REQUEST_SELECT(DMA_InitStruct->DMA_SourceRequestSelect));
  assert_parameters(IS_DMA_DESTINATION_REQUEST_SELECT(DMA_InitStruct->DMA_DestinationRequestSelect));
  assert_parameters(IS_DMA_TRANSFER_SIZE(DMA_InitStruct->DMA_TransferSize));
  
  tmpreg = READ_REG(DMAx_Channely->CTL[0]);
  if(DMA_InitStruct->DMA_Mode == DMA_MODE_LINK_LIST)
  {
    tmpreg |= (DMA_CTL0_LLP_SRC_EN | DMA_CTL0_LLP_DST_EN);
  }
  
  tmpreg &= (uint32_t)(~DMA_CTL0_SRC_MSIZE_Mask);
  tmpreg |= DMA_InitStruct->DMA_SourceBurstSize;
  
  tmpreg &= (uint32_t)(~DMA_CTL0_SRC_TR_WIDTH_Mask);
  tmpreg |= (DMA_InitStruct->DMA_SourceTransferWidth);
  
  tmpreg &= (uint32_t)(~DMA_CTL0_DEST_MSIZE_Mask);
  tmpreg |= DMA_InitStruct->DMA_DestinationBurstSize;
  
  tmpreg &= (uint32_t)(~DMA_CTL0_DST_TR_WIDTH_Mask);
  tmpreg |= (DMA_InitStruct->DMA_DestinationTransferWidth);
  
  tmpreg &= (uint32_t)(~DMA_CTL0_TT_FC_Mask);
  tmpreg |= DMA_InitStruct->DMA_DIR;
  
  tmpreg &= (uint32_t)(~DMA_CTL0_SINC_Mask);
  tmpreg |= (DMA_InitStruct->DMA_SourceAddressControl);
  
  tmpreg &= (uint32_t)(~DMA_CTL0_DINC_Mask);
  tmpreg |= (DMA_InitStruct->DMA_DestinationAddressControl);
  WRITE_REG(DMAx_Channely->CTL[0], tmpreg);
  

  tmpreg1 = READ_REG(DMAx_Channely->CFG[1]);
  tmpreg1 &= (uint32_t)(~DMA_CFG1_SRC_PER_Mask);
  tmpreg1 |= DMA_InitStruct->DMA_SourceRequestSelect;
  
  tmpreg1 &= (uint32_t)(~DMA_CFG1_DEST_PER_Mask);
  tmpreg1 |= DMA_InitStruct->DMA_DestinationRequestSelect;
  WRITE_REG(DMAx_Channely->CFG[1], tmpreg1);
  
  tmpreg1 = READ_REG(DMAx_Channely->CFG[1]);
  
  tmpreg2 = READ_REG(DMAx_Channely->CFG[0]);
  if(DMA_InitStruct->DMA_Mode == DMA_MODE_AUTO_RELOAD)
  {
    tmpreg2 |= (DMA_CFG0_RELOAD_SRC_EN | DMA_CFG0_RELOAD_DST_EN);
  }
  tmpreg2 &= (uint32_t)(~DMA_Priority_Mask);
  tmpreg2 |= DMA_InitStruct->DMA_Priority;
  WRITE_REG(DMAx_Channely->CFG[0], tmpreg2);

  WRITE_REG(DMAx_Channely->SAR, DMA_InitStruct->DMA_SourceAddress);
  WRITE_REG(DMAx_Channely->DAR, DMA_InitStruct->DMA_DestinationAddress);
  
  if (DMA_InitStruct->DMA_Mode == DMA_MODE_LINK_LIST)
  {
    WRITE_REG(DMAx_Channely->LLP, DMA_InitStruct->DMA_LinkListAddress);
  }
  else
  {
    WRITE_REG(DMAx_Channely->LLP, 0);
  }
  
  size = READ_REG(DMAx_Channely->CTL[1]);
  size &= (uint32_t)(~DMA_CTL1_BLOCK_TS_Mask);
  size |= DMA_InitStruct->DMA_TransferSize;
  WRITE_REG(DMAx_Channely->CTL[1], size);
}

/**
  * @brief  Initializes the DMA link list according to the specified
  *         parameters in the DMA_InitStruct.
  * @param  DMA_LLP: pointer to a DMA_LinkListType structure that
  *         contains the configuration information for the link list.
  * @param  DMA_LinkListInfo: pointer to a DMA_LinkListInfoType structure that
  *         contains the configuration information for the link list informations.
  * @retval None
  */
void DMA_LinkListInit(DMA_LinkListType* DMA_LLP, \
                        DMA_LinkListInfoType* DMA_LinkListInfo)
{
  uint32_t tmpreg = 0;
  
  assert_parameters(IS_DMA_LINK_LIST_ADDRESS(DMA_LinkListInfo->DMA_NextLLPAddr));
  assert_parameters(IS_DMA_TRANSFER_SIZE(DMA_LinkListInfo->DMA_TransferSize));
  assert_parameters(IS_DMA_SOURCE_TRANSFER_WIDTH(DMA_LinkListInfo->DMA_SourceTransferWidth));
  assert_parameters(IS_DMA_DESTINATION_TRANSFER_WIDTH(DMA_LinkListInfo->DMA_DestinationTransferWidth));
  assert_parameters(IS_DMA_SOURCE_ADDRESS_CONTROL(DMA_LinkListInfo->DMA_SourceAddressControl));
  assert_parameters(IS_DMA_DESTINATION_ADDRESS_CONTROL(DMA_LinkListInfo->DMA_DestinationAddressControl));
  
  WRITE_REG(DMA_LLP->SrcAddr, DMA_LinkListInfo->DMA_SourceAddress);
  WRITE_REG(DMA_LLP->DstAddr, DMA_LinkListInfo->DMA_DestinationAddress);
  WRITE_REG(DMA_LLP->LLP, DMA_LinkListInfo->DMA_NextLLPAddr);
  
  if (DMA_LinkListInfo->DMA_NextLLPAddr == 0)
  { 
    SET_BIT(DMA_LLP->CTL1, DMA_CTL1_DONE);
  }
  else
  {
    tmpreg |= (DMA_CTL0_LLP_DST_EN | DMA_CTL0_LLP_SRC_EN);
  }
  WRITE_REG(DMA_LLP->CTL1, DMA_LinkListInfo->DMA_TransferSize);
  
  tmpreg |= (DMA_LinkListInfo->DMA_SourceTransferWidth);
  tmpreg |= (DMA_LinkListInfo->DMA_DestinationTransferWidth);
  tmpreg |= (DMA_LinkListInfo->DMA_SourceAddressControl);
  tmpreg |= (DMA_LinkListInfo->DMA_DestinationAddressControl);
  tmpreg |= (DMA_LinkListInfo->DMA_SourceBurstSize);
  tmpreg |= (DMA_LinkListInfo->DMA_DestinationBurstSize);
  tmpreg |= (DMA_LinkListInfo->DMA_DIR);
  tmpreg |= DMA_CTL0_INT_EN;
  
  /* Write DMA CTL setting to DMA_LLP CTL0 */
  WRITE_REG(DMA_LLP->CTL0, tmpreg);
}

/**
  * @brief  Enables or disables the specified DMA Channelx.
  * @param  DMAx_Channely: where x can be (0 or 1), y cna be (0..7) to 
  *         select the DMA and Channel.
  * @param  NewState: new state of the DMA Channelx. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_ChannelCmd(DMA_Channel_Type* DMAx_Channely, FunctionalState NewState)
{
  uint32_t Channel;
  DMA_Type *DMAx;
  
  /* Check the parameters */
  assert_parameters(IS_DMA_CHANNEL_ALL_PERIPH(DMAx_Channely));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  /* Get DMA and Channel index */
  DMA_CHANNEL_GET_INDEX(DMAx_Channely, DMAx, Channel);

  if (NewState != DISABLE)
  {
    /* Enable the selected DMA Channelx */
    WRITE_REG(DMAx->CHENREG, ((1<<(Channel+8))|(1<<Channel)));
  }
  else
  {
    /* Disable the selected DMA Channelx */
    WRITE_REG(DMAx->CHENREG, (1<<(Channel+8) & (~(1<<Channel))));
  }
}
/**
  * @brief  Enables or disables the specified DMA.
  * @param  NewState: new state of the DMA Channelx. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_Cmd(DMA_Type* DMAx, FunctionalState NewState)
{
  __IO uint32_t tmp = 0UL;
  UNUSED(tmp);
  
  /* Check the parameters */
  assert_parameters(IS_DMA_ALL_PERIPH(DMAx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMA Channelx */
    WRITE_REG(DMAx->DMACFGREG, 0x01);
    tmp = READ_REG(DMAx->DMACFGREG);
  }
  else
  {
    /* Disable the selected DMA Channelx */
    WRITE_REG(DMAx->DMACFGREG, 0x00);
  }
}

/**
  * @brief  Enables or disables the specified DMA Channelx interrupts.
  * @param  DMAx_Channely: where x can be (0 or 1), y cna be (0..7) to 
  *         select the DMA and Channel.
  * @param  DMA_IT: specifies the DMA interrupts sources to be enabled
  *         or disabled. 
  *         This parameter can be one of the following values:
  *           @arg DMA_INT_TFR
  *           @arg DMA_INT_BLOCK
  *           @arg DMA_INT_SRCTRAN
  *           @arg DMA_INT_DSTTRAN
  *           @arg DMA_INT_ERR
  * @param  NewState: new state of the specified DMA interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_ITConfig(DMA_Channel_Type* DMAx_Channely, uint32_t DMA_IT, FunctionalState NewState)
{
  uint32_t Channel;
  DMA_Type *DMAx;
  
  /* Check the parameters */
  assert_parameters(IS_DMA_CHANNEL_ALL_PERIPH(DMAx_Channely));
  assert_parameters(IS_DMA_CONFIG_IT(DMA_IT));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  /* Get DMA and Channel index */
  DMA_CHANNEL_GET_INDEX(DMAx_Channely, DMAx, Channel);
  
  if(DMA_IT == DMA_INT_TFR)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKTFR, ((1<<(Channel+8))|(1<<Channel)));
    }
    else
    {
      /* Disable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKTFR, (1<<(Channel+8) & (~(1<<Channel))));
    }
  }
  else if(DMA_IT == DMA_INT_BLOCK)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKBLOCK, ((1<<(Channel+8))|(1<<Channel)));
    }
    else
    {
      /* Disable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKBLOCK, (1<<(Channel+8) & (~(1<<Channel))));
    }
  }
  else if(DMA_IT == DMA_INT_SRCTRAN)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKSRCTRAN, ((1<<(Channel+8))|(1<<Channel)));
    }
    else
    {
      /* Disable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKSRCTRAN, (1<<(Channel+8) & (~(1<<Channel))));
    }
  }
  else if(DMA_IT == DMA_INT_DSTTRAN)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKDSTTRAN, ((1<<(Channel+8))|(1<<Channel)));
    }
    else
    {
      /* Disable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKDSTTRAN, (1<<(Channel+8) & (~(1<<Channel))));
    }
  }
  else if(DMA_IT == DMA_INT_ERR)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKERR, ((1<<(Channel+8))|(1<<Channel)));
    }
    else
    {
      /* Disable the selected DMA interrupts */
      WRITE_REG(DMAx->MASKERR, (1<<(Channel+8) & (~(1<<Channel))));
    }
  }
}

/**
  * @brief  Returns the DMA Status.
  * @param  DMA_Channelx: where x can be 0 to 7 to select the DMA Channel.
  * @retval None
  */
FlagStatus DMA_GetChnEnStatus(DMA_Channel_Type* DMAx_Channely)
{
  uint32_t Channel,tmpreg;
  DMA_Type *DMAx;
  assert_parameters(IS_DMA_CHANNEL_ALL_PERIPH(DMAx_Channely));
  
  /* Get DMA and Channel index */
  DMA_CHANNEL_GET_INDEX(DMAx_Channely, DMAx, Channel); 

  tmpreg = READ_REG(DMAx->CHENREG);

  return ((tmpreg >> Channel) & 0x01);
}

/**
  * @brief  Checks whether the specified DMA Channelx interrupt flag is set or not.
  * @param  DMAx_Channely: where x can be (0 or 1), y cna be (0..7) to 
  *         select the DMA and Channel.
  * @param  DMA_FLAG: specifies the interrupt flag to check.
  * @retval The new state of DMA_FLAG (SET or RESET).
  */
ITStatus DMA_GetITtatus(DMA_Channel_Type* DMAx_Channely, uint32_t DMA_IT)
{
  FlagStatus bitstatus = RESET;
  uint32_t Channel;
  DMA_Type *DMAx;
  
  /* Check the parameters */
  assert_parameters(IS_DMA_CHANNEL_ALL_PERIPH(DMAx_Channely));
  assert_parameters(IS_DMA_CONFIG_IT(DMA_IT));
  
  /* Get DMA and Channel index */
  DMA_CHANNEL_GET_INDEX(DMAx_Channely, DMAx, Channel);
  
  if(DMA_IT == DMA_INT_TFR)
  {
    bitstatus = READ_REG(DMAx->RAWTFR);
    bitstatus = ((bitstatus >> Channel) & 0X01);
  }
  
  else if(DMA_IT == DMA_INT_BLOCK)
  {
    bitstatus = READ_REG(DMAx->RAWBLOCK);
    bitstatus = ((bitstatus >> Channel) & 0X01);
  }
  
  else if(DMA_IT == DMA_INT_SRCTRAN)
  {
    bitstatus = READ_REG(DMAx->RAWSRCTRAN);
    bitstatus = ((bitstatus >> Channel) & 0X01);
  }
  
  else if(DMA_IT == DMA_INT_DSTTRAN)
  {
    bitstatus = READ_REG(DMAx->RAWDSTTRAN);
    bitstatus = ((bitstatus >> Channel) & 0X01);
  }
  
  else if(DMA_IT == DMA_INT_ERR)
  {
    bitstatus = READ_REG(DMAx->RAWERR);
    bitstatus = ((bitstatus >> Channel) & 0X01);
  }
  
  return  bitstatus;
}

/**
  * @brief  Checks whether the specified DMA Channelx interrupt has occurred or not.
  * @param  DMAx_Channely: where x can be (0 or 1), y cna be (0..7) to 
  *         select the DMA and Channel.
  * @param  DMA_IT: specifies the DMA interrupt source to check. 
  * @retval The new state of DMA_IT (SET or RESET).
  */
void DMA_ClearITStatus(DMA_Channel_Type* DMAx_Channely, uint32_t DMA_IT)
{
  uint32_t Channel;
  DMA_Type *DMAx;
  
  /* Check the parameters */
  assert_parameters(IS_DMA_CHANNEL_ALL_PERIPH(DMAx_Channely));
  assert_parameters(IS_DMA_CONFIG_IT(DMA_IT));
  
  /* Get DMA and Channel index */
  DMA_CHANNEL_GET_INDEX(DMAx_Channely, DMAx, Channel);
  
  if(DMA_IT == DMA_INT_TFR)
  {
    WRITE_REG(DMAx->CLEARTFR, (1 << Channel));
  }
  
  else if(DMA_IT == DMA_INT_BLOCK)
  {
    WRITE_REG(DMAx->CLEARBLOCK, (1 << Channel));
  }
  
  else if(DMA_IT == DMA_INT_SRCTRAN)
  {
    WRITE_REG(DMAx->CLEARSRCTRAN, (1 << Channel));
  }
  
  else if(DMA_IT == DMA_INT_DSTTRAN)
  {
    WRITE_REG(DMAx-> CLEARDSTTRAN, (1 << Channel));
  }
  
  else if(DMA_IT == DMA_INT_ERR)
  {
    WRITE_REG(DMAx->CLEARERR, (1 << Channel));
  }
}

/**
  * @brief  Memoryto Peripheral mode, returns the number of transferred data units 
  *         in the current DMA Streamx transfer.
  * @param  DMAx_Channely: where x can be (0 or 1), y cna be (0..7) to 
  *         select the DMA and Channel.
  * @retval The number of transferred data units in the current DMA Streamx transfer.
  */
uint16_t DMA_GetCurrTransferredCounter(DMA_Channel_Type* DMAx_Channely)
{
  /* Check the parameters */
  assert_parameters(IS_DMA_CHANNEL_ALL_PERIPH(DMAx_Channely));
  
  return ((uint16_t)(DMAx_Channely->CTL[1] & 0xFFF));
}

/*********************************** END OF FILE ******************************/
