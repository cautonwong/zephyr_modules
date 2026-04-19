/**
  ******************************************************************************
  * @file    lib_i2c.c 
  * @author  VT Application Team
  * @version V1.0.0
  * @date    2021-10-18
  * @brief   I2C library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_i2c.h"

/*
// I2C_TAR register
*/
#define I2C_TAR_TAR_MASK               (0x3FFUL)
#define I2C_TAR_10BITADDR_MASTER       (1UL << 12)
/*
// I2C_CON register
*/
#define I2C_CON_MASTER_ENABLE          (1UL << 0)
#define I2C_CON_STANDARD_MODE          (1UL << 1)
#define I2C_CON_FAST_MODE              (1UL << 2)
#define I2C_CON_10BITADDR_SLAVE        (1UL << 3)
#define I2C_CON_RESTART_ENABLE         (1UL << 5)
#define I2C_CON_SLAVE_DISABLE          (1UL << 6)
/*
// I2C_ENABLE register
*/
#define I2C_ENABLE_ENABLE              (1UL << 0)
#define I2C_ENABLE_ENABLE_CLR          REG_BIT_NOT(I2C_ENABLE_ENABLE)
//#define REG_BIT_NOT(X)                 (~X)
/*
// I2C_TXSTS register
*/
#define I2C_TXSTS_TXFLEV_MASK          (7UL)
#define I2C_TXSTS_TXFLEV_CLR           REG_BIT_NOT(I2C_TXSTS_TXFLEV_MASK)
 /*
// I2C_RXSTS register
*/
#define I2C_RXSTS_RXFLEV_MAKS          (7UL)
#define I2C_RXSTS_RXFLEV_CLR           REG_BIT_NOT(I2C_RXSTS_RXFLEV_MAKS)
//registers default reset values
#define I2C_ENABLE_RSTVAL              (0UL)
#define I2C_CON_RSTVAL                 (0UL)
#define I2C_TAR_RSTVAL                 (0UL)
#define I2C_SAR_RSTVAL                 (0UL)
#define I2C_INTR_MASK_RSTVAL           (0UL)

#define I2C_RESTART_ENABLED() \
  I2Cx->CON |= I2C_CON_RESTART_ENABLE

#define I2C_CHECK_7B_ADDR_MATCHED() \
  if(I2Cx->IC_TX_ABRT_SOURCE & I2C_7B_ADDR_NOACK) \
      return 1

#define I2C_WAIT_UNTIL_TFE() \
  while (!(I2Cx->IC_STATUS & I2C_FLAG_TFE))

#define I2C_CHECK_TXDAT_ACK() \
  if(I2Cx->IC_TX_ABRT_SOURCE & I2C_TXDATA_NOACK) \
    return 1

#define I2C_WAIT_UNTIL_RFNE() \
  while (!(I2Cx->IC_STATUS & I2C_FLAG_RFNE))

/* Exported Functions ------------------------------------------------------- */

/**
  * @brief  Reset I2C device.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @retval None
  */
void I2C_DeInit(I2C_Type *I2Cx)
{
   __IO uint32_t dummy_data = 0UL;

   UNUSED(dummy_data);
  
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  
  /* Disable SPI */
  I2Cx->ENABLE = I2C_ENABLE_RSTVAL;
  /* write default values */
  I2Cx->CON = I2C_CON_RSTVAL;
  I2Cx->TAR = I2C_TAR_RSTVAL;
  I2Cx->SAR = I2C_SAR_RSTVAL;
  I2Cx->INTMASK = I2C_INTR_MASK_RSTVAL;
  /* Clear flag */
  dummy_data = I2Cx->INTCLR;
}

/**
  * @brief  Fills each I2C_InitType member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitType structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitType *I2C_InitStruct)
{
  I2C_InitStruct->Mode = I2C_MODE_SLAVE;
  I2C_InitStruct->SlaveAddress = 0x00; 
  I2C_InitStruct->OwnAddress = 0x00;
  I2C_InitStruct->Restart = I2C_RESTART_DISABLE;
  I2C_InitStruct->SpeedMode = I2C_SPEEDMODE_STANDARD;
  I2C_InitStruct->MasterAddressingMode = I2C_MASTERADDR_7B;
  I2C_InitStruct->RespondsAddressingMode = I2C_RESPADDR_7B;
}

/**
  * @brief  I2C initialization.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  I2C_InitStruct: I2C configuration.
  *             Mode:
  *                 I2C_MODE_MASTER
  *                 I2C_MODE_SLAVE
  *             SlaveAddress: slave device address
  *             OwnAddress: Own slave address
  *             Restart:
  *                 I2C_RESTART_ENABLE
  *                 I2C_RESTART_DISABLE
  *             SpeedMode:
  *                 I2C_SPEEDMODE_STANDARD
  *                 I2C_SPEEDMODE_FAST
  *             MasterAddressingMode:
  *                 I2C_MASTERADDR_7B
  *                 I2C_MASTERADDR_10B
  *             RespondsAddressingMode:
  *                 I2C_RESPADDR_7B
  *                 I2C_RESPADDR_10B
  * @retval None
  */
void I2C_Init(I2C_Type *I2Cx, I2C_InitType *I2C_InitStruct)
{
  uint32_t tmp1, tmp2, slave_addr;
  
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_MODE(I2C_InitStruct->Mode));
  assert_parameters(IS_I2C_RESTART(I2C_InitStruct->Restart));
  assert_parameters(IS_I2C_SPEEDMODE(I2C_InitStruct->SpeedMode));
  assert_parameters(IS_I2C_MASTERADDR(I2C_InitStruct->MasterAddressingMode));
  assert_parameters(IS_I2C_RESPADDR(I2C_InitStruct->RespondsAddressingMode));

  tmp1 = I2Cx->CON;
  tmp2 = I2Cx->TAR;
  tmp1 &= ~(I2C_CON_MASTER_ENABLE\
          |I2C_CON_STANDARD_MODE\
          |I2C_CON_FAST_MODE\
          |I2C_CON_10BITADDR_SLAVE\
          |I2C_CON_RESTART_ENABLE\
          |I2C_CON_SLAVE_DISABLE);
  tmp2 &= ~(I2C_TAR_10BITADDR_MASTER|I2C_TAR_TAR_MASK);
  
  tmp1 |= (I2C_InitStruct->Mode\
          |I2C_InitStruct->Restart\
          |I2C_InitStruct->SpeedMode\
          |I2C_InitStruct->RespondsAddressingMode);
  slave_addr = (I2C_InitStruct->SlaveAddress>>1) & I2C_TAR_TAR_MASK;
  tmp2 |= (I2C_InitStruct->MasterAddressingMode|slave_addr);
  
  I2Cx->CON = tmp1;
  I2Cx->TAR = tmp2;
  I2Cx->SAR = I2C_InitStruct->OwnAddress;
}

/**
  * @brief  Enables or disables I2C interrupt.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  INTMask: specifies the I2C interrupt source to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *             I2C_INT_RX_DONE
  *             I2C_INT_TX_ABORT
  *             I2C_INT_RD_REQ
  *             I2C_INT_TX_EMPTY
  *             I2C_INT_TX_OVER
  *             I2C_INT_RXFULL
  *             I2C_INT_RXOVER
  *             I2C_INT_RXUNDER
  * @param  NewState: new state of the specified I2C interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_INTConfig(I2C_Type *I2Cx, uint32_t INTMask, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_INTEN(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    I2Cx->INTMASK |= INTMask;
  }
  else
  {
    I2Cx->INTMASK &= ~INTMask;
  }
}

/**
  * @brief  Gets I2C interrupt status.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  INTMask: specifies the I2C interrupt source to check.
  *         This parameter can be one of the following values:
  *             I2C_INT_RX_DONE
  *             I2C_INT_TX_ABORT
  *             I2C_INT_RD_REQ
  *             I2C_INT_TX_EMPTY
  *             I2C_INT_TX_OVER
  *             I2C_INT_RXFULL
  *             I2C_INT_RXOVER
  *             I2C_INT_RXUNDER
  * @retval The new state of I2C interrupt (SET or RESET).
  */
ITStatus I2C_GetINTStatus(I2C_Type *I2Cx, uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_INTGET(INTMask));
  
  if (I2Cx->RAWINTSTS & INTMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears I2C interrupt status bit.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  INTMask: specifies the I2C interrupt source to clear.
  *         This parameter can be any combination of the following values:
  *             I2C_INT_RX_DONE
  *             I2C_INT_TX_ABORT
  *             I2C_INT_RD_REQ
  *             I2C_INT_TX_OVER
  *             I2C_INT_RXOVER
  *             I2C_INT_RXUNDER
  * @retval None.
  */
void I2C_ClearINTStatus(I2C_Type *I2Cx, uint32_t INTMask)
{
  __IO uint32_t tmp = 0UL;

  UNUSED(tmp);
  
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_INTCLR(INTMask));
  
  if (INTMask & 0x80000000UL)
  {
    tmp = I2Cx->RXDONECLR;
  }
  if (INTMask & 0x40000000UL)
  {
    tmp = I2Cx->RDREQCLR;
  }
  if (INTMask & 0x20000000UL)
  {
    tmp = I2Cx->TXOCLR;
  }
  if (INTMask & 0x10000000UL)
  {
    tmp = I2Cx->RXOCLR;
  }
  if (INTMask & 0x08000000UL)
  {
    tmp = I2Cx->TXABTCLR;
  }
  if (INTMask & 0x01000000UL)
  {
    tmp = I2Cx->RXUCLR;
  }
}

/**
  * @brief  Clear all individual interrupt and combined interrupt.
  * @note   This function does not clear hardware clearable interrupts but software clearable interrupts
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @retval None
  */
void I2C_ClearAllINTStatus(I2C_Type *I2Cx)
{
  __IO uint32_t tmp = 0UL;

  UNUSED(tmp);
  
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx)); 
  
  tmp=I2Cx->INTCLR;
}

/**
  * @brief  Gets I2C status flag.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  FlagMask: specifies the I2C flag status to check.
  *         This parameter can be one of the following values:
  *             I2C_FLAG_BSY
  *             I2C_FLAG_TFNE
  *             I2C_FLAG_TFE
  *             I2C_FLAG_RFNE
  *             I2C_FLAG_RFF
  *             I2C_FLAG_MST_ACTIVITY
  *             I2C_FLAG_SLV_ACTIVITY
  *             I2C_FLAG_MST_HOLD_TX_FIFO_EMPTY
  *             I2C_FLAG_MST_HOLD_RX_FIFO_FULL
  *             I2C_FLAG_SLV_HOLD_TX_FIFO_EMPTY
  *             I2C_FLAG_SLV_HOLD_RX_FIFO_FULL
  * @retval Flag status.
  */
FlagStatus I2C_GetFlag(I2C_Type *I2Cx, uint32_t FlagMask)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx)); 
  assert_parameters(IS_I2C_FLAGR(FlagMask)); 
  
  if (I2Cx->STATUS & FlagMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Sends command and data frame.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  Command: the command to configure
  *         This parameter can be one of the following values:
  *             I2C_CMD_WRITE
  *             I2C_CMD_READ
  *             I2C_CMD_STOP
  *             I2C_CMD_RESTART
  *             I2C_CMD_WRITE_STOP
  *             I2C_CMD_WRITE_RESTART
  *             I2C_CMD_READ_STOP
  *             I2C_CMD_READ_RESTART
  * @param  ch: data write to data register
  * @retval None
  */
void I2C_SendCmdDataFrame(I2C_Type *I2Cx, uint16_t Command, uint8_t ch)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_CMD(Command));
  
  I2Cx->DATACMD = Command | ch;
}


/**
  * @brief  Read receive data register.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @retval Received data value
  */
uint8_t I2C_ReceiveData(I2C_Type *I2Cx)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx)); 
  
  return I2Cx->DATACMD;
}

/**
  * @brief  Enables or disables I2C.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  NewState: new state of the I2C peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_Type *I2Cx, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    I2Cx->ENABLE |= I2C_ENABLE_ENABLE;
  }
  else
  {
    I2Cx->ENABLE &= I2C_ENABLE_ENABLE_CLR;
  }
}

/**
  * @brief  Configures transmit FIFO level.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  FIFOLevel: selects transmit FIFO level
  *         This parameter can be one of the following values:
  *             I2C_TXFLEV_0 ~ I2C_TXFLEV_7
  * @retval None
  */
void I2C_TransmitFIFOLevelConfig(I2C_Type *I2Cx, uint32_t FIFOLevel)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx)); 
  assert_parameters(IS_I2C_TXFLEV(FIFOLevel));
  
  tmp = I2Cx->TXTL & I2C_TXSTS_TXFLEV_CLR;
  tmp |= FIFOLevel;
  I2Cx->TXTL = tmp;
}

/**
  * @brief  Configures receive FIFO level.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  FIFOLevel: selects receive FIFO level
  *         This parameter can be one of the following values:
  *             I2C_RXFLEV_0 ~ I2C_RXFLEV_7
  * @retval None
  */
void I2C_ReceiveFIFOLevelConfig(I2C_Type *I2Cx, uint32_t FIFOLevel)
{
  uint32_t tmp;
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx)); 
  assert_parameters(IS_I2C_RXFLEV(FIFOLevel));
  
  tmp = I2Cx->RXTL & I2C_RXSTS_RXFLEV_CLR;
  tmp |= FIFOLevel;
  I2Cx->RXTL = tmp;
}

/**
  * @brief  Gets transmit FIFO level.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @retval Transmit v level.
  */
uint8_t I2C_GetTransmitFIFOLevel(I2C_Type *I2Cx)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  
  return I2Cx->TXFLR;
}

/**
  * @brief  Gets receive FIFO level.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @retval Receive FIFO level.
  */
uint8_t I2C_GetReceiveFIFOLevel(I2C_Type *I2Cx)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  
  return I2Cx->RXFLR;
}

/**
  * @brief  Configures SCL clock frequency and duty-cycle.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @param  SpeedMode: configures the specified speed mode
  *             I2C_SPEEDMODE_STANDARD
  *             I2C_SPEEDMODE_FAST
  * @param  DutyH: SCL clock high-period count
  * @param  DutyL: SCL clock low-period count
  * @retval None
  */
void I2C_ClockFreqDutyConfig(I2C_Type *I2Cx, uint32_t SpeedMode, uint16_t DutyH, uint16_t DutyL)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_SPEEDMODE(SpeedMode));
  
  if (SpeedMode == I2C_SPEEDMODE_STANDARD)
  {
    I2Cx->SSCNTL = DutyL;
    I2Cx->SSCNTH = DutyH;
  }
  else
  {
    I2Cx->FSCNTL = DutyL;
    I2Cx->FSCNTH = DutyH;
  }
}

/**
  * @brief  Gets transmit abort status.
  * @param  I2Cx : select the I2C peripheral.
  *         CM0 : I2C14
  *         CM33 : I2C0 ~ I2C14
  * @retval Transmit abort status (SET or RESET)
  */
FlagStatus I2C_GetTransmitAbortStatus(I2C_Type *I2Cx, uint32_t Status)
{
  /* Check parameters */
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_TXABRT_STS(Status));
  
  if(I2Cx->TXABTSRC & Status)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Enables or disables the I2Cx DMA interface.
  * @param  I2Cx : select the I2C peripheral.
  *         CM33 : I2C0 ~ I2C13
  * @param  I2C_DMAReq: specifies the I2C DMA transfer request to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_DMA_TX: Tx buffer DMA transfer request
  *            @arg I2C_DMA_RX: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected I2C DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DMACmd(I2C_Type* I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState)
{
  uint32_t tmp;
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_DMA_CR(I2C_DMAReq));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  tmp = I2Cx-> DMACR;
  tmp &= ~I2C_DMACR_Mask;
  if (NewState != DISABLE)
  {
    tmp |= I2C_DMAReq;
  }
  else
  {
    tmp &= (uint32_t)(~I2C_DMAReq);
  }
  I2Cx->DMACR = tmp;
}

/**
  * @brief  Configures DMA transmit FIFO level.
  * @param  I2Cx : select the I2C peripheral.
  *         CM33 : I2C0 ~ I2C13
  * @param  TXFIFOLevel: selects transmit FIFO level
  *         This parameter can be one of the following values:
  *             I2C_TXFLEV_0 ~ I2C_TXFLEV_7
  * @retval None
  */
void I2C_DMA_TxFIFOLevelConfig(I2C_Type* I2Cx, uint32_t TXFIFOLevel)
{
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_TXFLEV(TXFIFOLevel));
  I2Cx->DMATDLR = TXFIFOLevel;
}

/**
  * @brief  Configures DMA receive FIFO level.
  * @param  I2Cx : select the I2C peripheral.
  *         CM33 : I2C0 ~ I2C13
  * @param  RXFIFOLevel: selects receive FIFO level
  *         This parameter can be one of the following values:
  *             I2C_RXFLEV_0 ~ I2C_RXFLEV_7
  * @retval None
  */
void I2C_DMA_RxFIFOLevelConfig(I2C_Type* I2Cx, uint32_t RXFIFOLevel)
{
  assert_parameters(IS_I2C_ALL_INSTANCE(I2Cx));
  assert_parameters(IS_I2C_RXFLEV(RXFIFOLevel));
  I2Cx->DMARDLR = RXFIFOLevel;
}

/*********************************** END OF FILE ******************************/
