/**
  * @file    lib_ospi.c
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-21
  * @brief   This file provides all the OSPI/QSPI firmware functions.
******************************************************************************/

#include "lib_ospi.h"

/**
  * @brief  Fills each OSPI_InitStruct member with its default value.
  * @param  OSPI_InitStruct: pointer to a OSPI_InitType structure which will be initialized.
  * @retval None
  */
void OSPI_StructInit(OSPI_InitType* OSPI_InitStruct)
{
  /* Check the parameters */
  OSPI_InitStruct->OSPI_WorkingMode           = OSPI_WorkingMode_Master;
  OSPI_InitStruct->OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_DualSPI;
  OSPI_InitStruct->OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStruct->OSPI_DataNumber            = 0;
  OSPI_InitStruct->OSPI_DataLength            = OSPI_DataLength_8BIT;
  OSPI_InitStruct->OSPI_ADDRLength            = OSPI_ADDRLength_24BIT;
  OSPI_InitStruct->OSPI_INSTLength            = OSPI_INSTLength_8BIT;
  OSPI_InitStruct->OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStruct->OSPI_InstructionDtrMode    = OSPI_INSTRUCTION_DTR_DISABLE;
  OSPI_InitStruct->OSPI_AddrDtrMode           = OSPI_SPI_DTR_DISABLE;
  OSPI_InitStruct->OSPI_Hyperbus              = OSPI_Hyperbus_Disable;
  OSPI_InitStruct->OSPI_RXDS                  = OSPI_RXDS_DISABLE;
  OSPI_InitStruct->OSPI_WaitCycles            = 0;
  OSPI_InitStruct->OSPI_CPOL                  = OSPI_CPOL_Low;
  OSPI_InitStruct->OSPI_CPHA                  = OSPI_CPHA_1Edge;
  OSPI_InitStruct->OSPI_SCLKDivider           = 2;
  OSPI_InitStruct->OSPI_DDR_DRIVE_EDGE        = 0;
}
/**
  * @brief  Deinitialize the OSPIx peripheral registers to their default reset values.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be the different instances.
  *                     
  * @retval None
  */
void OSPI_DeInit(OSPI_Type* OSPIx)
{
  __IO uint32_t tmp = 0UL;

  UNUSED(tmp);

  /* Check the parameters */
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  
  OSPIx-> CTRLR0 = 0;
  OSPIx-> SPI_CTRLR0 = 0;
  OSPIx-> IMR = 0;
  /* Clear Interrupt Status */
  tmp = OSPIx-> ICR;
}


/**
  * @brief  Initializes the OSPIx peripheral according to the specified 
  *         parameters in the OSPI_InitStruct.
  *         
  * @param  OSPIx: where x can be 0 or 1 to select the OSPI peripheral.
  * @param  OSPI_InitStruct: pointer to a OSPI_InitType structure that
  *         contains the configuration information for the specified OSPI peripheral.             
  * @retval None
  */
void OSPI_Init(OSPI_Type* OSPIx, OSPI_InitType* OSPI_InitStruct)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0, DataNumber = 0, clockdiv;
  
  /* Check the parameters */
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_WorkingMode(OSPI_InitStruct->OSPI_WorkingMode));
  assert_parameters(IS_OSPI_SPIFrameFormat(OSPI_InitStruct->OSPI_SPIFrameFormat));
  assert_parameters(IS_OSPI_TransferMode(OSPI_InitStruct->OSPI_TransferMode));
  assert_parameters(IS_OSPI_DataNumber(OSPI_InitStruct->OSPI_DataNumber));
  assert_parameters(IS_OSPI_DataLength(OSPI_InitStruct->OSPI_DataLength));
  assert_parameters(IS_OSPI_ADDRLength(OSPI_InitStruct->OSPI_ADDRLength));
  assert_parameters(IS_OSPI_INSTLength(OSPI_InitStruct->OSPI_INSTLength));
  assert_parameters(IS_OSPI_ADDRINSTFormat(OSPI_InitStruct->OSPI_ADDRINSTFormat));
  assert_parameters(IS_OSPI_Hyperbus(OSPI_InitStruct->OSPI_Hyperbus));
  assert_parameters(IS_OSPI_WaitCycles(OSPI_InitStruct->OSPI_WaitCycles));
  assert_parameters(IS_OSPI_CPOL(OSPI_InitStruct->OSPI_CPOL));
  assert_parameters(IS_OSPI_CPHA(OSPI_InitStruct->OSPI_CPHA));

  tmpreg1 = OSPIx->CTRLR0;
  tmpreg1 &= ~(OSPI_CTRLR0_TMOD_Mask | OSPI_CTRLR0_SCPOL_INACTIVE_LOW \
              | OSPI_CTRLR0_SCPH_START_BIT | OSPI_CTRLR0_OSPI_FRF_Mask | OSPI_CTRLR0_OSPI_MASTER \
              | OSPI_CTRLR0_DFS_Mask | OSPI_CTRLR0_FRF_Mask | OSPI_CTRLR0_OSPI_HYPERBUS_EN);
  tmpreg1 = (OSPI_InitStruct->OSPI_CPOL | OSPI_InitStruct->OSPI_CPHA \
           | OSPI_InitStruct->OSPI_TransferMode | OSPI_InitStruct->OSPI_WorkingMode \
           | OSPI_InitStruct->OSPI_DataLength | OSPI_InitStruct->OSPI_Hyperbus \
           | OSPI_InitStruct->OSPI_SPIFrameFormat);
  OSPIx->CTRLR0 = tmpreg1;
  DataNumber = OSPIx->CTRL1;
  DataNumber &= ~OSPI_CTRLR1_NDF_Mask;
  DataNumber = (OSPI_InitStruct->OSPI_DataNumber - 1);
  OSPIx->CTRL1 = DataNumber;
  OSPIx->DDR_DRIVE_EDGE =0;
  tmpreg2 = OSPIx->SPI_CTRLR0;
  tmpreg2 &= ~(OSPI_SPI_CTRLR0_TRANS_TYPE_Mask | OSPI_SPI_CTRLR0_ADDR_L_Mask \
             | OSPI_SPI_CTRLR0_INST_L_Mask | OSPI_SPI_CTRLR0_WAIT_CYCLES_Mask \
             | OSPI_SPI_CTRLR0_OSPI_DDR_EN | OSPI_SPI_CTRLR0_OSPI_RXDS_EN  | OSPI_SPI_CTRLR0_OSPI_DM_EN | OSPI_SPI_CTRLR0_OSPI_RXDS_SIG_EN);
  if(OSPI_InitStruct->OSPI_Hyperbus == OSPI_Hyperbus_Enable)
  {
    if(OSPI_InitStruct->OSPI_TransferMode == OSPI_TransferMode_TX)
    {
      tmpreg2 |= ( OSPI_SPI_CTRLR0_OSPI_DM_EN | OSPI_SPI_CTRLR0_OSPI_RXDS_SIG_EN); 
    }
    else if(OSPI_InitStruct->OSPI_TransferMode == OSPI_TransferMode_RX)
    {
      tmpreg2 |= (OSPI_SPI_CTRLR0_OSPI_RXDS_SIG_EN);
    }
    OSPIx->DDR_DRIVE_EDGE = OSPI_InitStruct->OSPI_DDR_DRIVE_EDGE;
  }
  tmpreg2 |= ((OSPI_InitStruct->OSPI_WaitCycles << 11) | OSPI_InitStruct->OSPI_INSTLength \
               | OSPI_InitStruct->OSPI_ADDRLength | OSPI_InitStruct->OSPI_ADDRINSTFormat \
               | OSPI_InitStruct->OSPI_AddrDtrMode | OSPI_InitStruct->OSPI_InstructionDtrMode | OSPI_InitStruct->OSPI_RXDS);
  OSPIx->SPI_CTRLR0 = tmpreg2;
  
  //SET sclkdiv
  clockdiv = OSPIx->BAUDR;
  clockdiv &= ~OSPI_BAUDR_SCKDV_Mask;
  clockdiv |= ((OSPI_InitStruct->OSPI_SCLKDivider/2) << 1);
  OSPIx->BAUDR = clockdiv;
}


/**
  * @brief  Enables or disables the specified OSPI Block peripheral.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be the different instances.
  * @param  NewState: new state of the OSPIx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OSPI_Cmd(OSPI_Type* OSPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    OSPIx->OSPIENR |= OSPI_OSPIENR_OSPIEN;
    OSPIx ->SER = 0x01;
  }
  else
  {
    OSPIx->OSPIENR &= (~OSPI_OSPIENR_OSPIEN);
    OSPIx ->SER = 0x00;
  }
}



/**
  * @brief  Enables or disables the OSPIx DMA interface.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0 ~ 6
  * @param  OSPI_DMAReq: specifies the OSPI DMA transfer request to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg OSPI_DMA_TX: Tx buffer DMA transfer request
  *            @arg OSPI_DMA_RX: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected OSPI DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OSPI_DMACmd(OSPI_Type* OSPIx, uint32_t OSPI_DMAReq, FunctionalState NewState)
{
  uint32_t tmp;
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_DMA_CHANNEL(OSPI_DMAReq));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  tmp = OSPIx-> DMACR;
  tmp &= ~OSPI_DMACR_Mask;
  if (NewState != DISABLE)
  {
    tmp |= OSPI_DMAReq;
  }
  else
  {
    tmp &= (uint32_t)(~OSPI_DMAReq);
  }
  OSPIx->DMACR = tmp;
}


/**
  * @brief  Transmits a Data through the OSPIx peripheral.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1.     
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void OSPI_SendData(OSPI_Type* OSPIx, uint32_t Data)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  
  OSPIx->DR[0] = Data;
}


/**
  * @brief  Returns the most recent received data by the OSPIx peripheral. 
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @retval The value of the received data.
  */
uint32_t OSPI_ReceiveData(OSPI_Type* OSPIx)
{
  uint32_t tmp;
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  tmp = OSPIx->DR[0];
  return tmp;
}

/**
  * @brief  Checks whether the specified OSPIx flag is set or not.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @param  OSPI_FLAG: specifies the OSPI flag to check. 
  *          This parameter can be one of the following values:
  *            @arg OSPI_FLAG_STATUS_TXE
  *            @arg OSPI_FLAG_STATUS_RFF
  *            @arg OSPI_FLAG_STATUS_RFNE
  *            @arg OSPI_FLAG_STATUS_TFE 
  *            @arg OSPI_FLAG_STATUS_TFNF
  *            @arg OSPI_FLAG_STATUS_BUSY
  * @retval The new state of OSPI_FLAG (SET or RESET).
  */
FlagStatus OSPI_GetFlagStatus(OSPI_Type* OSPIx, uint16_t OSPI_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_FLAG_STATUS(OSPI_FLAG));
  
  if (OSPIx->SR & OSPI_FLAG)
  {
    bitstatus =  SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return  bitstatus;
}

/**
  * @brief  Enables or disables the specified OSPI interrupts.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @param  OSPI_IT: specifies the OSPI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg OSPI_IT_TXEI
  *            @arg OSPI_IT_TXOI
  *            @arg OSPI_IT_RXUI
  *            @arg OSPI_IT_RXOI
  *            @arg OSPI_IT_RXFI
  *            @arg OSPI_IT_TXUI 
  * @param  NewState: new state of the specified OSPI interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OSPI_ITConfig(OSPI_Type* OSPIx, uint16_t OSPI_IT, FunctionalState NewState)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_INT(OSPI_IT));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    OSPIx->IMR |= OSPI_IT;
  }
  else
  {
    OSPIx->IMR &= (~OSPI_IT);
  }
}

/**
  * @brief  Get OSPI interrupts flags.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @param  OSPI_IT: specifies the OSPI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg OSPI_IT_TXEI
  *            @arg OSPI_IT_TXOI
  *            @arg OSPI_IT_RXUI
  *            @arg OSPI_IT_RXOI
  *            @arg OSPI_IT_RXFI
  *            @arg OSPI_IT_TXUI 
  * @retval The new state of OSPI_INTFLAG (SET or RESET).
  */
ITStatus OSPI_GetITStatus(OSPI_Type* OSPIx, uint16_t OSPI_IT)
{
  ITStatus  bitstatus = RESET;
  
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_INT(OSPI_IT));
  
  if (OSPIx->ISR & OSPI_IT)
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
  * @brief  Get and clear interrupt status of the specified OSPI.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @param  OSPI_IT: specifies the OSPI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg OSPI_IT_TXUI
  *            @arg OSPI_IT_TXOI
  *            @arg OSPI_IT_RXUI
  *            @arg OSPI_IT_RXOI
  * @retval The new state of OSPI_IT.
  */
void OSPI_ClearITStatus(OSPI_Type* OSPIx, uint16_t OSPI_IT)
{
  __IO uint32_t tmp = 0UL;

  UNUSED(tmp);
  
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_INT(OSPI_IT));
  if(OSPI_IT & (OSPI_IT_TXUI | OSPI_IT_TXOI))
  {
	  tmp = OSPIx->TXEICR;
  }
  if(OSPI_IT & OSPI_IT_RXUI)
  {
	  tmp = OSPIx->RXUICR;
  }
  if(OSPI_IT & OSPI_IT_RXOI)
  {
	  tmp = OSPIx->RXOICR;
  }
}

/**
  * @brief  Set the threshold value for the transmit FIFO memory.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @param  TXFIFOLevel:The threshold value for the transmit FIFO memory.
  *          This parameter can be one of the following values:
  *            @arg OSPI_FIFO_TX_THRESHOLD_1
  *            @arg OSPI_FIFO_TX_THRESHOLD_4
  *            @arg OSPI_FIFO_TX_THRESHOLD_8
  *            @arg OSPI_FIFO_TX_THRESHOLD_16
  *            @arg OSPI_FIFO_TX_THRESHOLD_24
  *            @arg OSPI_FIFO_TX_THRESHOLD_32
  * @retval none.
  */
void OSPI_TxFIFOThresholdConfig(OSPI_Type* OSPIx, uint32_t TXFIFOLevel)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_FIFO_TXLEVLE(TXFIFOLevel));
  OSPIx->TXFTLR = TXFIFOLevel;
}

/**
  * @brief  Get the number of valid data entries in the receive FIFO memory.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @param  TXFIFOLevel:The threshold value for the receive FIFO memory.
  *          This parameter can be one of the following values:
  *            @arg OSPI_FIFO_RX_THRESHOLD_1
  *            @arg OSPI_FIFO_RX_THRESHOLD_4
  *            @arg OSPI_FIFO_RX_THRESHOLD_8
  *            @arg OSPI_FIFO_RX_THRESHOLD_16
  *            @arg OSPI_FIFO_RX_THRESHOLD_24
  *            @arg OSPI_FIFO_RX_THRESHOLD_32
  * @retval none.
  */
void OSPI_RxFIFOThresholdConfig(OSPI_Type* OSPIx, uint32_t RXFIFOLevel)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_FIFO_RXLEVLE(RXFIFOLevel));
  OSPIx->RXFTLR = RXFIFOLevel;
}

void OSPI_DMA_TxFIFOLevelConfig(OSPI_Type* OSPIx, uint32_t TXFIFOLevel)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_FIFO_TXLEVLE(TXFIFOLevel));
  OSPIx->DMATDLR = TXFIFOLevel;
}

void OSPI_DMA_RxFIFOLevelConfig(OSPI_Type* OSPIx, uint32_t RXFIFOLevel)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_OSPI_FIFO_RXLEVLE(RXFIFOLevel));
  OSPIx->DMARDLR = RXFIFOLevel;
}

/**
  * @brief  Get the number of valid data entries in the transmit FIFO memory.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @retval The  number of valid data entries in the transmit FIFO memory.
  */
uint16_t OSPI_GetTxFIFOLevel(OSPI_Type* OSPIx)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  return (OSPIx->TXFLR & OSPI_TXFTLR_TFT_Mask);
}


/**
  * @brief  Get the number of valid data entries in the receive FIFO memory.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @retval The  number of valid data entries in the receive FIFO memory.
  */
uint16_t OSPI_GetRxFIFOLevel(OSPI_Type* OSPIx)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  return (OSPIx->RXFLR & OSPI_RXFTLR_RFT_Mask);
}

/**
  * @brief  Enables or disables the specified OSPI's encryption of external read/write data.
  * @param  OSPIx: To select the OSPIx peripheral, where x can be: 0, 1. 
  * @param  NewState: new state of the specified OSPI interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OSPI_ENC_Cmd(OSPI_Type* OSPIx, FunctionalState NewState)
{
  assert_parameters(IS_OSPI_ALL_INSTANCE(OSPIx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  if (NewState != DISABLE)
  {
    OSPIx->ENC_CFG |= OSPI_ENC_CFG_EN;
  }
  else
  {
    OSPIx->ENC_CFG &= (~OSPI_ENC_CFG_EN);
  }  
}
/*********************************** END OF FILE ******************************/

