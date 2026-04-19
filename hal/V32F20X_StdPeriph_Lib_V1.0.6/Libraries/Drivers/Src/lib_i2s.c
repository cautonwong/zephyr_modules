/**
  * @file    lib_I2S.c
  * @author  Application Team
  * @version V1.0
  * @date    2021-04-20
  * @brief   This file provides all the I2S/I2S firmware functions.
******************************************************************************/

#include "lib_i2s.h"

#define CER_RESETVALUE       (0UL)
#define IER_RESETVALUE       (0UL)
#define IRER_RESETVALUE      (0UL)
#define ITER_RESETVALUE      (0UL)
#define RER_RESETVALUE       (0UL)
#define TER_RESETVALUE       (0UL)
#define IMR_RESETVALUE       (0UL)
#define DMACR_RESETVALUE     (0UL)

/**
  * @brief  Fills each I2S_InitStruct member with its default value.
  * @param  I2S_InitStruct: pointer to a I2S_InitType structure which will be initialized.
  * @retval None
  */
void I2S_StructInit(I2S_InitType* I2S_InitStruct)
{
  I2S_InitStruct->I2S_TransferMode = I2S_TransferMode_TX;
  I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16B;
}

/**
  * @brief  Deinitialize the I2Sx peripheral registers to their default reset values.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be the different instances.
  *                     
  * @retval None
  */
void I2S_DeInit(I2S_Type* I2Sx)
{
  __IO uint32_t tmp = 0UL;
  
  UNUSED(tmp);

  /* Check the parameters */
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  
  I2Sx-> CER = CER_RESETVALUE;
  I2Sx-> IER = IER_RESETVALUE;
  I2Sx-> IRER =IRER_RESETVALUE;
  I2Sx-> ITER =ITER_RESETVALUE;
  I2Sx-> RER = RER_RESETVALUE;
  I2Sx-> TER = TER_RESETVALUE;
  I2Sx-> IMR = IMR_RESETVALUE;
  I2Sx-> DMACR = DMACR_RESETVALUE;
  /* Clear Interrupt Status */
  tmp = I2Sx-> ROR;
  tmp = I2Sx-> TOR;
}

/**
  * @brief  Initializes the I2Sx peripheral according to the specified 
  *         parameters in the I2S_InitStruct.
  * @param  I2Sx: where x can be 0 or 1 to select the I2S peripheral.
  * @param  I2S_InitStruct: pointer to a I2S_InitType structure that
  *         contains the configuration information for the specified I2S peripheral.
  * @retval None
  */
void I2S_Init(I2S_Type* I2Sx, I2S_InitType* I2S_InitStruct)
{
  uint32_t temp_reg = 0;
  
  /* Check the parameters */
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_I2S_TRANSFERMODE(I2S_InitStruct->I2S_TransferMode));
  assert_parameters(IS_I2S_DATAFORMAT(I2S_InitStruct->I2S_DataFormat));

  /* Disable internal clock */
  I2Sx->CER &= ~I2S_CER_CLKEN;
  
  /* Disable transmitter and receiver */
  I2Sx->IRER &= ~I2S_IRER_RXEN;
  I2Sx->ITER &= ~I2S_ITER_TXEN;
  I2Sx->RER &= ~I2S_RER_RXCHEN;
  I2Sx->TER &= ~I2S_TER_TXCHEN;
  
  /* Configure data format, include data bit size and extended size */
  I2Sx->RCR = I2S_InitStruct->I2S_DataFormat & I2S_RCR_WLEN_Mask;
  I2Sx->TCR = I2S_InitStruct->I2S_DataFormat & I2S_TCR_WLEN_Mask;
  temp_reg = I2Sx->CCR;
  temp_reg &= ~I2S_CCR_WSS_CYCLES_Mask;
  temp_reg |= (I2S_InitStruct->I2S_DataFormat & I2S_CCR_WSS_CYCLES_Mask);
  I2Sx->CCR = temp_reg;
  
  if(I2S_InitStruct->I2S_TransferMode == I2S_TransferMode_TX)
  {
    I2Sx->ITER = I2S_ITER_TXEN;
    I2Sx->TER = I2S_TER_TXCHEN;
  }
  else if(I2S_InitStruct->I2S_TransferMode == I2S_TransferMode_RX)
  {
    I2Sx->IRER = I2S_IRER_RXEN;
    I2Sx->RER = I2S_RER_RXCHEN;
  }
}

/**
  * @brief  Configures SCK gate function
  * @param  I2Sx: To select the I2Sx peripheral, where x can be the different instances.
  * @param  I2S_SCKGate: used to configure the gating of SCK cycles.
  *           This parameter can be one of the following values:
  *            @arg I2S_SCKGATE_NONE : no gating
  *            @arg I2S_SCKGATE_AFTER_12SCK : gate SCK after 12 SCK cycles
  *            @arg I2S_SCKGATE_AFTER_16SCK : gate SCK after 16 SCK cycles
  *            @arg I2S_SCKGATE_AFTER_20SCK : gate SCK after 20 SCK cycles
  *            @arg I2S_SCKGATE_AFTER_24SCK : gate SCK after 24 SCK cycles
  * @retval None
  */
void I2S_SCKGateConfig(I2S_Type* I2Sx, uint32_t I2S_SCKGate)
{
  uint32_t temp_reg = 0x00UL;
  
  /* Check the parameters */
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_I2S_SCKGATE(I2S_SCKGate));
  
  temp_reg = I2Sx->CCR;
  temp_reg &= ~I2S_CCR_SCLKG_CYCLES_Mask;
  temp_reg |= I2S_SCKGate;
  I2Sx->CCR = temp_reg;
}

/**
  * @brief  Enables or disables the specified I2S Block peripheral.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be the different instances.
  * @param  NewState: new state of the I2Sx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_Cmd(I2S_Type* I2Sx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    I2Sx->IER |= I2S_IER_IEN;
    I2Sx->CER = 0x01;
  }
  else
  {
    I2Sx->IER &= (~I2S_IER_IEN);
    I2Sx-> CER = 0x00;
  }
}

/**
  * @brief  Enables or disables the I2Sx DMA interface.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0 ~ 6
  * @param  I2S_DMAReq: specifies the I2S DMA transfer request to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2S_DMA_TX: Tx buffer DMA transfer request
  *            @arg I2S_DMA_RX: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected I2S DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_DMACmd(I2S_Type* I2Sx, uint32_t I2S_DMAReq, FunctionalState NewState)
{
  uint32_t tmp;
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_I2S_DMA_CHANNEL(I2S_DMAReq));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  tmp = I2Sx-> DMACR;
  tmp = ~I2S_DMACR_Mask;
  if (NewState != DISABLE)
  {
    tmp |= I2S_DMAReq;
  }
  else
  {
    tmp &= (uint32_t)(~I2S_DMAReq);
  }
  I2Sx->DMACR = tmp;
}


/**
  * @brief  Transmits a Data through the I2Sx peripheral.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1.     
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void I2S_LeftStereoSendData(I2S_Type* I2Sx, uint32_t Data)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  
  I2Sx->LTHR = Data;
}

/**
  * @brief  Transmits a Data through the I2Sx peripheral.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1.     
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void I2S_RightStereoSendData(I2S_Type* I2Sx, uint32_t Data)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  
  I2Sx->RTHR = Data;
}

/**
  * @brief  Returns the most recent received data by the I2Sx peripheral. 
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @retval The value of the received data.
  */
uint32_t I2S_LeftStereoReceiveData(I2S_Type* I2Sx)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  
  return I2Sx->LRBR;
}

/**
  * @brief  Returns the most recent received data by the I2Sx peripheral. 
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @retval The value of the received data.
  */
uint32_t I2S_RightStereoReceiveData(I2S_Type* I2Sx)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  
  return I2Sx->RRBR;
}

/**
  * @brief  Enables or disables the specified I2S interrupts.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @param  I2S_IT: specifies the I2S interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg I2S_INT_RXDA
  *            @arg I2S_INT_RXFO
  *            @arg I2S_INT_TXFE
  *            @arg I2S_INT_TXFO
  * @param  NewState: new state of the specified I2S interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_ITConfig(I2S_Type* I2Sx, uint16_t I2S_INT, FunctionalState NewState)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_I2S_INT(I2S_INT));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    I2Sx->IMR |= I2S_INT;
  }
  else
  {
    I2Sx->IMR &= (~I2S_INT);
  }
}

/**
  * @brief  Get I2S interrupts flags.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @param  I2S_IT: specifies the I2S interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg I2S_INT_RXDA
  *            @arg I2S_INT_RXFO
  *            @arg I2S_INT_TXFE
  *            @arg I2S_INT_TXFO
  * @retval The new state of I2S_INTFLAG (SET or RESET).
  */
ITStatus I2S_GetITStatus(I2S_Type* I2Sx, uint16_t I2S_INT)
{
  ITStatus  bitstatus = RESET;
  
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_I2S_INT(I2S_INT));
  
  if (I2Sx-> ISR & I2S_INT)
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
  * @brief  Get and clear interrupt status of the specified I2S.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @param  I2S_IT: specifies the I2S interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg I2S_INT_RXFO
  *            @arg I2S_INT_TXFO
  * @retval The new state of I2S_IT.
  */
void I2S_ClearITStatus(I2S_Type* I2Sx, uint16_t I2S_INT)
{
  __IO uint32_t tmp = 0UL;
 
  UNUSED(tmp);

  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_I2S_INT(I2S_INT));
  if(I2S_INT == I2S_INT_RXFO)
  {
    tmp = I2Sx->ROR;
  }
  else
  {
    tmp = I2Sx->TOR;
  }
}

/**
  * @brief  Set the threshold value for the transmit FIFO memory.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @param  TXFIFOLevel:The threshold value for the transmit FIFO memory.
  *          This parameter can be one of the following values:
  *            @arg I2S_FIFO_TX_THRESHOLD_1
  *            @arg I2S_FIFO_TX_THRESHOLD_2
  *            @arg I2S_FIFO_TX_THRESHOLD_3
  *            @arg I2S_FIFO_TX_THRESHOLD_4
  *            @arg I2S_FIFO_TX_THRESHOLD_5
  *            @arg I2S_FIFO_TX_THRESHOLD_6
  *            @arg I2S_FIFO_TX_THRESHOLD_7
  *            @arg I2S_FIFO_TX_THRESHOLD_8
  * @retval none.
  */
void I2S_TxFIFOThresholdConfig(I2S_Type* I2Sx, uint32_t TXFIFOLevel)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_I2S_FIFO_TXLEVLE(TXFIFOLevel));
  I2Sx->TFCR = TXFIFOLevel;
}

/**
  * @brief  Get the number of valid data entries in the receive FIFO memory.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @param  TXFIFOLevel:The threshold value for the receive FIFO memory.
  *          This parameter can be one of the following values:
  *            @arg I2S_FIFO_RX_THRESHOLD_1
  *            @arg I2S_FIFO_RX_THRESHOLD_2
  *            @arg I2S_FIFO_RX_THRESHOLD_3
  *            @arg I2S_FIFO_RX_THRESHOLD_4
  *            @arg I2S_FIFO_RX_THRESHOLD_5
  *            @arg I2S_FIFO_RX_THRESHOLD_6
  *            @arg I2S_FIFO_RX_THRESHOLD_7
  *            @arg I2S_FIFO_RX_THRESHOLD_8
  * @retval none.
  */
void I2S_RxFIFOThresholdConfig(I2S_Type* I2Sx, uint32_t RXFIFOLevel)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  assert_parameters(IS_I2S_FIFO_RXLEVLE(RXFIFOLevel));
  I2Sx->RFCR = RXFIFOLevel;
}

/**
  * @brief  Transmit channel FIFO Reset. 
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @retval The value of the received data.
  */
void I2S_TransmitChannelFIFOReset(I2S_Type* I2Sx)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  I2Sx->TER &= ~I2S_TER_TXCHEN;
  I2Sx->ITER &= ~I2S_ITER_TXEN;
  I2Sx->TFF = I2S_TFF_TXCHFR;
}

/**
  * @brief  Receive channel FIFO Reset. 
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @retval none.
  */
void I2S_ReceiveChannelFIFOReset(I2S_Type* I2Sx)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  I2Sx->RER &= ~I2S_RER_RXCHEN;
  I2Sx->IRER &= ~I2S_IRER_RXEN;
  I2Sx->RFF = I2S_RFF_RXCHFR;
}

/**
  * @brief  Flushes all the RX FIFOs.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @retval none.
  */
void I2S_TransmitBlockFIFOReset(I2S_Type* I2Sx)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  I2Sx->ITER &= ~I2S_ITER_TXEN;
  I2Sx->TXFFR = I2S_TXFFR_EN;
}

/**
  * @brief  Flushes all the TX FIFOs.
  * @param  I2Sx: To select the I2Sx peripheral, where x can be: 0, 1. 
  * @retval none.
  */
void I2S_ReceiveBlockFIFOReset(I2S_Type* I2Sx)
{
  assert_parameters(IS_I2S_ALL_INSTANCE(I2Sx));
  I2Sx->IRER &= ~I2S_IRER_RXEN;
  I2Sx->RXFFR = I2S_RXFFR_EN;
}

/*********************************** END OF FILE ******************************/
