/**
  * @file    lib_spi.c
  * @author  Application Team
  * @version V1.0
  * @date    2021-10-18
  * @brief   This file provides all the SPI firmware functions.
******************************************************************************/

#include "lib_spi.h"

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct: pointer to a SPI_InitType structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitType* SPI_InitStruct)
{
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8_Bit;
  SPI_InitStruct->SPI_TransferMode = SPI_TransferMode_TX_AND_RX;
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStruct->SPI_SCLKDivider = 2;
}

/**
  * @brief  Deinitialize the SPIx peripheral registers to their default reset values.
  * @param  SPIx:SPI0~SPI13  
  * @retval None
  */
void SPI_DeInit(SPI_Type* SPIx)
{
  uint32_t tmp = 0UL;

  UNUSED(tmp);

  /* Check the parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  
  SPIx->SSIENR &= (~SPI_SPIENR_SPIEN);
  SPIx->CTRL0 = 0;
  SPIx->IMR = 0;
  /* Clear Interrupt Status */
  tmp = SPIx-> ICR;
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *         parameters in the SPI_InitStruct.   
  * @param  SPIx:SPI0~SPI13
  * @param  SPI_InitStruct: pointer to a SPI_InitType structure that
  *         contains the configuration information for the specified SPI peripheral.             
  * @retval None
  */
void SPI_Init(SPI_Type* SPIx, SPI_InitType* SPI_InitStruct)
{
  uint32_t tmpreg = 0;
  uint32_t clockdiv;
  
  /* Check the parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_parameters(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_parameters(IS_SPI_SCLK_DIVIDER(SPI_InitStruct->SPI_SCLKDivider));
  assert_parameters(IS_SPI_TRANSFERMODE(SPI_InitStruct->SPI_TransferMode));

  tmpreg = SPIx->CTRL0;
  tmpreg &= ~(SPI_CTRLR0_TMOD_Mask | SPI_CTRLR0_SCPOL_INACTIVE_LOW \
              | SPI_CTRLR0_SCPH_START_BIT | SPI_CTRLR0_SPI_FRF_Mask \
              | SPI_CTRLR0_SPI_MASTER | SPI_CTRLR0_DFS_Mask);
  tmpreg |= (SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_CPHA \
             | SPI_InitStruct->SPI_TransferMode | SPI_InitStruct->SPI_DataSize);

  SPIx->CTRL0 = tmpreg;
  tmpreg = SPIx->CTRL0;
  /* SET sclkdiv */
  clockdiv = SPIx->BAUDR;
  clockdiv &= ~SPI_BAUDR_SCKDV_Mask;
  clockdiv |= SPI_InitStruct->SPI_SCLKDivider;
  SPIx->BAUDR = clockdiv;
  clockdiv = SPIx->BAUDR;
}

/**
  * @brief  Enables or disables the specified SPI Block peripheral.
  * @param  SPIx:SPI0~SPI13
  * @param  NewState: new state of the SPIx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_Type* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    SPIx->SSIENR |= SPI_SPIENR_SPIEN;
    SPIx->SER = 0x01;
  }
  else
  {
    SPIx->SSIENR &= (~SPI_SPIENR_SPIEN);
    SPIx->SER = 0x00;
  }
}

/**
  * @brief  
  * @param  
  * @param  
  * @retval None
  */
void SPI_SlaveSelectConfig(SPI_Type* SPIx, uint8_t SPI_SSel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_SSEL(SPI_SSel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    SPIx->SER = SPI_SSel;
  }
  else
  {
    SPIx->SER = 0x00;
  }
}

/**
  * @brief  Enables or disables the SPIx DMA interface.
  * @param  SPIx:SPI0~SPI13
  * @param  SPI_DMAReq: specifies the SPI DMA transfer request to be enabled or disabled. 
  *         This parameter can be any combination of the following values:
  *            @arg SPI_DMA_TX: Tx buffer DMA transfer request
  *            @arg SPI_DMA_RX: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected SPI DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_DMACmd(SPI_Type* SPIx, uint32_t SPI_DMAReq, FunctionalState NewState)
{
  uint32_t tmp;
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_DMA_CHANNEL(SPI_DMAReq));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = SPIx->DMACR;
  tmp = ~SPI_DMACR_Mask;
  if (NewState != DISABLE)
  {
    tmp |= SPI_DMAReq;
  }
  else
  {
    tmp &= (uint32_t)(~SPI_DMAReq);
  }
  SPIx->DMACR = tmp;
}

/**
  * @brief  Transmits a Data through the SPIx peripheral.
  * @param  SPIx:SPI0~SPI13     
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SPI_SendData(SPI_Type* SPIx, uint32_t Data)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  
  SPIx->DR = Data;
}

/**
  * @brief  Returns the most recent received data by the SPIx peripheral. 
  * @param  SPIx: To select the SPIx peripheral, where x can be: 0, 1. 
  * @retval The value of the received data.
  */
uint32_t SPI_ReceiveData(SPI_Type* SPIx)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  
  return SPIx->DR;
}

/**
  * @brief  Checks whether the specified SPIx flag is set or not.
  * @param  SPIx:SPI0~SPI13
  * @param  SPI_FLAG: specifies the SPI flag to check. 
  *          This parameter can be one of the following values:
  *            @arg SPI_FLAG_STATUS_TXE
  *            @arg SPI_FLAG_STATUS_RFF
  *            @arg SPI_FLAG_STATUS_RFNE
  *            @arg SPI_FLAG_STATUS_TFE 
  *            @arg SPI_FLAG_STATUS_TFNF
  *            @arg SPI_FLAG_STATUS_BUSY
  * @retval The new state of SPI_FLAG (SET or RESET).
  */
FlagStatus SPI_GetFlagStatus(SPI_Type* SPIx, uint16_t SPI_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_FLAG_STATUS(SPI_FLAG));
  
  if (SPIx->SR & SPI_FLAG)
  {
    bitstatus =  SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return bitstatus;
}

/**
  * @brief  Enables or disables the specified SPI interrupts.
  * @param  SPIx:SPI0~SPI13 
  * @param  SPI_IT: specifies the SPI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg SPI_IT_TXEI
  *            @arg SPI_IT_TXOI
  *            @arg SPI_IT_RXUI
  *            @arg SPI_IT_RXOI
  *            @arg SPI_IT_RXFI
  *            @arg SPI_IT_MSTI 
  * @param  NewState: new state of the specified SPI interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_ITConfig(SPI_Type* SPIx, uint16_t SPI_IT, FunctionalState NewState)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_INT(SPI_IT));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    SPIx->IMR |= SPI_IT;
  }
  else
  {
    SPIx->IMR &= (~SPI_IT);
  }
}

/**
  * @brief  Get SPI interrupts flags.
  * @param  SPIx:SPI0~SPI13
  * @param  SPI_IT: specifies the SPI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg SPI_IT_TXEI
  *            @arg SPI_IT_TXOI
  *            @arg SPI_IT_RXUI
  *            @arg SPI_IT_RXOI
  *            @arg SPI_IT_RXFI
  *            @arg SPI_IT_MSTI 
  * @retval The new state of SPI_INTFLAG (SET or RESET).
  */
ITStatus SPI_GetITStatus(SPI_Type* SPIx, uint16_t SPI_IT)
{
  ITStatus  bitstatus = RESET;
  
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_INT(SPI_IT));
  
  if (SPIx->RISR & SPI_IT)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Get and clear interrupt status of the specified SPI.
  * @param  SPIx:SPI0~SPI13
  * @param  SPI_IT: specifies the SPI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg SPI_IT_CLEAR_TXUI
  *            @arg SPI_IT_CLEAR_TXOI
  *            @arg SPI_IT_CLEAR_RXUI
  *            @arg SPI_IT_CLEAR_RXOI
  * @retval The new state of SPI_IT.
  */
void SPI_ClearITStatus(SPI_Type* SPIx, uint16_t SPI_IT)
{
  __IO uint32_t tmp = 0UL;

  UNUSED(tmp);
  
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_CLEAR_INT(SPI_IT));
  
  if(SPI_IT & (SPI_IT_CLEAR_TXUI | SPI_IT_CLEAR_TXOI))
  {
    tmp = SPIx->TXOICR;
  }
  if(SPI_IT & SPI_IT_CLEAR_RXUI)
  {
    tmp = SPIx->RXUICR;
  }
  if(SPI_IT & SPI_IT_CLEAR_RXOI)
  {
    tmp = SPIx->RXOICR;
  }
}

/**
  * @brief  Set the threshold value for the transmit FIFO memory.
  * @param  SPIx:SPI0~SPI13
  * @param  TXFIFOLevel:The threshold value for the transmit FIFO memory.
  *          This parameter can be one of the following values:
  *            @arg SPI_FIFO_TX_THRESHOLD_1
  *            @arg SPI_FIFO_TX_THRESHOLD_4
  *            @arg SPI_FIFO_TX_THRESHOLD_8
  *            @arg SPI_FIFO_TX_THRESHOLD_16
  *            @arg SPI_FIFO_TX_THRESHOLD_24
  *            @arg SPI_FIFO_TX_THRESHOLD_32
  * @retval none.
  */
void SPI_TxFIFOThresholdConfig(SPI_Type* SPIx, uint32_t TXFIFOLevel)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_FIFO_TXLEVLE(TXFIFOLevel));
  
  SPIx->TXFTLR = TXFIFOLevel;
}

void SPI_DMA_TxFIFOLevelConfig(SPI_Type* SPIx, uint32_t TXFIFOLevel)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_FIFO_TXLEVLE(TXFIFOLevel));
  
  SPIx->DMATDLR = TXFIFOLevel;
}

/**
  * @brief  Get the number of valid data entries in the receive FIFO memory.
  * @param  SPIx:SPI0~SPI13
  * @param  TXFIFOLevel:The threshold value for the receive FIFO memory.
  *          This parameter can be one of the following values:
  *            @arg SPI_FIFO_RX_THRESHOLD_1
  *            @arg SPI_FIFO_RX_THRESHOLD_4
  *            @arg SPI_FIFO_RX_THRESHOLD_8
  *            @arg SPI_FIFO_RX_THRESHOLD_16
  *            @arg SPI_FIFO_RX_THRESHOLD_24
  *            @arg SPI_FIFO_RX_THRESHOLD_32
  * @retval none.
  */
void SPI_RxFIFOThresholdConfig(SPI_Type* SPIx, uint32_t RXFIFOLevel)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_FIFO_RXLEVLE(RXFIFOLevel));
  
  SPIx->RXFTLR = RXFIFOLevel;
}

void SPI_DMA_RxFIFOLevelConfig(SPI_Type* SPIx, uint32_t RXFIFOLevel)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  assert_parameters(IS_SPI_FIFO_RXLEVLE(RXFIFOLevel));
  
  SPIx->DMARDLR = RXFIFOLevel;
}

/**
  * @brief  Get the number of valid data entries in the transmit FIFO memory.
  * @param  SPIx:SPI0~SPI13
  * @retval The  number of valid data entries in the transmit FIFO memory.
  */
uint16_t SPI_GetTxFIFOLevel(SPI_Type* SPIx)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  
  return (SPIx->TXFLR & SPI_TXFTLR_TFT_Mask);
}

/**
  * @brief  Get the number of valid data entries in the receive FIFO memory.
  * @param  SPIx:SPI0~SPI13
  * @retval The  number of valid data entries in the receive FIFO memory.
  */
uint16_t SPI_GetRxFIFOLevel(SPI_Type* SPIx)
{
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  
  return (SPIx->RXFLR &SPI_RXFTLR_RFT_Mask);
}
/*********************************** END OF FILE ******************************/