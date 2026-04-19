/**
  * @file    QSPI_Flash.c
  * @author  Application Team
  * @version V1.0
  * @date    2022-03
  * @brief   This file provides all the operation functions for windbond W25Q256FV
******************************************************************************/

#include "QSPI_Flash.h"

uint32_t word_buffer[66] __attribute__((aligned(4)));

/**
  * @brief  Deinitializes QSPI-related peripherals
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void QSPI_Flash_DeInit(OSPI_Type *OSPIx)
{
  OSPI_Cmd(OSPIx, DISABLE);
  if(OSPIx == OSPI0)
  {
    SYSCFG0_OSPIXIPCmd(OSPI0, DISABLE);
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_OSPI0);
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_OSPI0, DISABLE);
  }
  else
  {
    SYSCFG0_OSPIXIPCmd(OSPI1, DISABLE);
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_OSPI1);
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_OSPI1, DISABLE);
  }
}

/**
  * @brief  Initializes QSPI-related peripherals
  * @note
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void QSPI_Flash_Init(OSPI_Type *OSPIx)
{
  GPIO_InitType GPIO_InitStruct; 
  GPIO_StructInit(&GPIO_InitStruct);

  if(OSPIx == OSPI0)
  {
    /*GPIOD 8, 9, 10, 11-> IO3, IO2, IO1, IO0*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8,  GPIO_AF12_OSPI0_IO3);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9,  GPIO_AF12_OSPI0_IO2);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF12_OSPI0_IO1);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF12_OSPI0_IO0);
    /*GPIOG 2,5-> SCK, CS*/
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource2,  GPIO_AF12_OSPI0_SCK);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource5,  GPIO_AF12_OSPI0_SS_0_N); 
    
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
      
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_5;
    GPIO_Init(GPIOG, &GPIO_InitStruct);
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_OSPI0);
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_OSPI0, ENABLE);
    /* disable XIP explicitly */
    SYSCFG0_OSPIXIPCmd(OSPI0, DISABLE);
  }
  else if(OSPIx == OSPI1)
  {
    /*GPIOE 7, 10, 11, 14 -> IO2,  CS, IO1, IO0*/
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7,  GPIO_AF12_OSPI1_IO2);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF12_OSPI1_SS_0_N);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF12_OSPI1_IO1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF12_OSPI1_IO0);
    /*GPIOF 12, 13 -> SCK, IO3*/
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF12_OSPI1_SCK);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF12_OSPI1_IO3);

    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
      
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOG, &GPIO_InitStruct);
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_OSPI1);
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_OSPI1, ENABLE);
    /* disable XIP explicitly */
    SYSCFG0_OSPIXIPCmd(OSPI1, DISABLE);
  }

  OSPI_Cmd(OSPIx, DISABLE);
  
  /* pin for external FLASH hardware reset */
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOF, &GPIO_InitStruct);
  GPIO_SetBits(GPIOF, GPIO_Pin_2);
}



/**
  * @brief  Waits for completion of write operation in SPI mode
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void QSPI_Flash_SPIMode_WaitForWriteEnd(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t status = 0;

  OSPI_Cmd(OSPIx, DISABLE);
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_StandardSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TXAndRX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStructType.OSPI_SCLKDivider           = 24;
  OSPI_InitStructType.OSPI_DataNumber            = 2;

  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_Cmd(OSPIx, ENABLE);

  do
  {
    OSPI_SendData(OSPIx, W25QX_CMD_READ_STATUS_REG);
    OSPI_SendData(OSPIx, FLASH_DUMMY_BYTE);
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_RFNE));
    status = OSPI_ReceiveData(OSPIx);
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_RFNE));
    status = OSPI_ReceiveData(OSPIx);
  }while(status&W25QX_SR_BUSY_MASK);

  while(SET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY));
  
  OSPI_Cmd(OSPIx, DISABLE);
}


/**
  * @brief  Resets FLASH by software.
  * @notice  Once the Reset command is accepted by the device, the device will take approximately
  *          tRST=30us to reset. During this period, no command will be accepted.
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void QSPI_Flash_SoftwareReset(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t i = 0;
  
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_StandardSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStructType.OSPI_DataNumber            = 0;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_InitStructType.OSPI_SCLKDivider           = 24;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  
  /* issue reset enable command */
  OSPI_Cmd(OSPIx, ENABLE);

  OSPI_SendData(OSPIx, W25QX_CMD_RESET_ENABLE);
  
  while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
  while(SET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY));

  OSPI_Cmd(OSPIx, DISABLE);
  
  for(i=0; i<255; i++)
  {
    __NOP(); __NOP();
  }
  
  /* issue Reset command */
  OSPI_Cmd(OSPIx, ENABLE);
  OSPI_SendData(OSPIx, W25QX_CMD_RESET);
  
  while(RESET == OSPI_GetFlagStatus(OSPIx, OSPI_FLAG_STATUS_TFE));
  while(SET == OSPI_GetFlagStatus(OSPIx, OSPI_FLAG_STATUS_BUSY));
  OSPI_Cmd(OSPIx, DISABLE);
  
  for(i=0; i<1000; i++)
  {
    __NOP(); __NOP();
  }

  QSPI_Flash_SPIMode_WaitForWriteEnd(OSPIx);
}


/**
  * @brief  Defines a public interface for issuing command in SPI mode.
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @param  cmd: FLASH operation command
  * @retval None
  */
void QSPI_Flash_SPIMode_SendCmd(OSPI_Type* OSPIx, uint8_t cmd)
{
  OSPI_InitType  OSPI_InitStructType;

  OSPI_Cmd(OSPIx, DISABLE);
  
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_StandardSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStructType.OSPI_DataNumber            = 0;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_InitStructType.OSPI_SCLKDivider           = 24;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  
  OSPI_Cmd(OSPIx, ENABLE);

  OSPI_SendData(OSPIx, cmd);
  while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
  while(SET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY));

  OSPI_Cmd(OSPIx, DISABLE);
}


/**
  * @brief  Defines a public interface for issuing command in QPI mode.
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @param  cmd: FLASH operation command
  * @retval None
  */
void QSPI_Flash_QPIMode_SendCmd(OSPI_Type* OSPIx, uint8_t cmd)
{
  OSPI_InitType  OSPI_InitStructType;

  OSPI_Cmd(OSPIx, DISABLE);
  
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_QuadSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber            = 0;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_InitStructType.OSPI_SCLKDivider           = 24;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  
  OSPI_Cmd(OSPIx, ENABLE);

  OSPI_SendData(OSPIx, cmd);
  while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
  while(SET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY));

  OSPI_Cmd(OSPIx, DISABLE);
}

/**
  * @brief  Switches the FLASH from SPI mode to QPI mode.
  * @notice Upon power-up, the default state of the device upon is Standard/Dual/Quad SPI mode
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void QSPI_Flash_QPIModeEnter(OSPI_Type *OSPIx)
{
  QSPI_Flash_SPIMode_SendCmd(OSPIx, W25QX_CMD_ENTER_QPI_MODE);
}


/**
  * @brief  Switches the FLASH from QPI mode to SPI mode.
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void QSPI_Flash_QPIModeExit(OSPI_Type *OSPIx)
{
  QSPI_Flash_QPIMode_SendCmd(OSPIx, W25QX_CMD_EXIT_QPI_MODE);
}


/**
  * @brief  Gets FLASH JEDEC ID in QPI mode
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval 24-bit JEDEC ID
  */
uint32_t QSPI_Flash_QPIMode_IDRead(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t i = 0;
  uint32_t FlashID = 0;
  uint8_t  temp[3] = {0};

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_QuadSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_SCLKDivider           = 24;
  OSPI_InitStructType.OSPI_DataNumber            = 3;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPI_Cmd(OSPIx, ENABLE);
  
  OSPI_SendData(OSPIx, W25QX_CMD_READ_FLASH_ID);
  while(RESET == OSPI_GetFlagStatus(OSPIx, OSPI_FLAG_STATUS_TFE));

  for(i = 0; i < 3; i++)
  {
    while(RESET == OSPI_GetFlagStatus(OSPIx, OSPI_FLAG_STATUS_RFNE));
    temp[i] = OSPI_ReceiveData(OSPIx);
  }

  while(SET == OSPI_GetFlagStatus(OSPIx, OSPI_FLAG_STATUS_BUSY));
  OSPI_Cmd(OSPIx, DISABLE);
  
  FlashID = (temp[0]<<16 | temp[1]<<8 | temp[2]);

  return FlashID;
}


/**
  * @brief  Enables write operation in QPI mode
  * @notice Write operation must be enabled prior to every Page Program, Quad Page Program, Sector Erase, Block 
  *         Erase, Chip Erase, Write Status Register and Erase/Program Security Registers instruction
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval none
  */
void QSPI_Flash_QPIMode_WriteEnable(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_QuadSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber            = 0;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_InitStructType.OSPI_SCLKDivider           = 24;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPI_Cmd(OSPIx, ENABLE);

  OSPI_SendData(OSPIx, W25QX_CMD_WRITE_ENABLE);
  while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
  while(SET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY));

  OSPI_Cmd(OSPIx, DISABLE);
}


/**
  * @brief  Waits for completion of write operation in QPI mode
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval none
  */
void QSPI_Flash_QPIMode_WaitForWriteEnd(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t status = 0;
  
  OSPI_Cmd(OSPIx, DISABLE);
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_QuadSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_SCLKDivider           = 24;
  OSPI_InitStructType.OSPI_DataNumber            = 1;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  
  OSPI_Cmd(OSPIx, ENABLE);

  do
  {
    OSPI_SendData(OSPIx, W25QX_CMD_READ_STATUS_REG);
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_RFNE));
    status = OSPI_ReceiveData(OSPIx);
  }while(status&W25QX_SR_BUSY_MASK);

  while(SET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY));
  OSPI_Cmd(OSPIx, DISABLE);
}


/**
  * @brief  Sets all memory within a specified sector (4K-bytes) to the erased state of all 1s (FFh) in QPI mode
  * @notice A Write Enable instruction must be executed before the device will accept the Sector Erase 
  *         Instruction
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @param  SectorAddr: sector address
  * @retval none
  */
void QSPI_Flash_QPIMode_SectorErase(OSPI_Type *OSPIx, uint32_t SectorAddr)
{
  OSPI_InitType  OSPI_InitStructType;
  
  /*-- Write enable --*/
  QSPI_Flash_QPIMode_WriteEnable(OSPIx);
  
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_QuadSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber            = 0;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_InitStructType.OSPI_SCLKDivider           = 24;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPI_Cmd(OSPIx, ENABLE);
  
  OSPI_SendData(OSPIx, W25QX_CMD_SECTOR_ERASE);
  OSPI_SendData(OSPIx, SectorAddr);
  while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
  while(SET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY));
  OSPI_Cmd(OSPIx, DISABLE);

  QSPI_Flash_QPIMode_WaitForWriteEnd(OSPIx);
}


/**
  * @brief  Writes one byte to 256 bytes (a page) of data to a specified page with DMA in QPI mode
  * @notice A Write Enable instruction must be executed before the device will accept the Page Program Instruction 
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @param  PageWriteAddr: starting address of the Write operation
  * @param  Buff: buffer holds the data
  * @param  BuffLen: data length in unit of byte
  * @retval none
  */
void QSPI_Flash_QPIMode_PageWriteWithDMA(OSPI_Type *OSPIx, uint32_t PageWriteAddr, uint8_t *Buff, uint32_t BuffLen)
{
  OSPI_InitType  OSPI_InitStructType;
  DMA_InitType DMA_InitStructure;
  uint32_t i;
  
  word_buffer[0] = W25QX_CMD_PAGE_PROGRAM;
  word_buffer[1] = PageWriteAddr;
  
  /* switch byte order */
  for(i = 0; i + 4 <= BuffLen; i += 4)
  {
    
    word_buffer[2+i/4] = (Buff[i+3]<<24)|(Buff[i+2]<<16)|(Buff[i+1]<<8)|Buff[i];
  }

  QSPI_Flash_QPIMode_WriteEnable(OSPIx);

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat = OSPI_SPIFrameFormat_QuadSPI;
  OSPI_InitStructType.OSPI_TransferMode = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_DataLength = OSPI_DataLength_32BIT;
  OSPI_InitStructType.OSPI_SCLKDivider = 2;
  OSPI_InitStructType.OSPI_ADDRINSTFormat = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber = BuffLen/4;
  OSPI_InitStructType.OSPI_WaitCycles = 0;
  OSPI_InitStructType.OSPI_ADDRLength = OSPI_ADDRLength_24BIT;

  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_DMACmd(OSPIx, OSPI_DMA_TX, ENABLE);
  OSPI_DMA_TxFIFOLevelConfig(OSPIx, OSPI_FIFO_TX_THRESHOLD_8);
  
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_Cmd(DMA0, DISABLE);
  DMA_DeInit(DMA0_Channel0);
  
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize = DMA_SourceBurstSize_8;
  DMA_InitStructure.DMA_DestinationBurstSize = DMA_DestinationBurstSize_8;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_SourceAddress = (uint32_t) (word_buffer);
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (&OSPIx->DR[0]);
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_TransferSize = (BuffLen/4) + 2;

  if(OSPIx == OSPI0)
  {
    SYSCFG0->DMA0_REQ_SEL0 = SYSCFG0_DMA_REQUEST_OSPI0_TX;
  }
  if(OSPIx == OSPI1)
  {
    SYSCFG0->DMA0_REQ_SEL0 = SYSCFG0_DMA_REQUEST_OSPI1_TX;
  }
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
  
  OSPI_Cmd(OSPIx, ENABLE);

  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);

  while(DMA_GetITtatus(DMA0_Channel0, DMA_INT_TFR) == RESET);
  DMA_ClearITStatus(DMA0_Channel0, DMA_INT_TFR);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_Cmd(DMA0, DISABLE);

  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE) == RESET){}
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);

  QSPI_Flash_QPIMode_WaitForWriteEnd(OSPIx);
}



/**
  * @brief  Writes data to FLASH with DMA in QPI mode
  * @notice A Write Enable instruction must be executed before the device will accept
  *         the Page Program Instruction 
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @param  PageWriteAddr: starting address of the Write operation
  * @param  Buff: buffer holds the data
  * @param  BuffLen: data length in unit of byte
  * @retval the number of bytes actually written
  */
uint32_t  QSPI_Flash_QPIMode_BufferWriteWithDMA(OSPI_Type *OSPIx, uint32_t FlashMemOffset, uint8_t *Buff, uint32_t BuffLen)
{
  uint32_t FirstPageOffset;
  uint32_t FirstPageRest;
  uint32_t NumOfPage;
  uint32_t BytesRest;
  uint32_t temp;
  
  if((FlashMemOffset%4) != 0
    || (BuffLen%4) != 0)
  {
    return 0;
  }
  
  FirstPageOffset = (FlashMemOffset % FLASH_PAGESIZE);
  FirstPageRest = (FLASH_PAGESIZE - FirstPageOffset);
  NumOfPage = (BuffLen/FLASH_PAGESIZE);
  BytesRest = (BuffLen%FLASH_PAGESIZE);

  /* FlashMemOffset is page-aligned */
  if(FirstPageOffset == 0)
  {
    if(NumOfPage == 0)
    {
      QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff, BytesRest);
    }
    else
    {
      while(NumOfPage--)
      {
        QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff, FLASH_PAGESIZE);
        FlashMemOffset += FLASH_PAGESIZE;
        Buff += FLASH_PAGESIZE;
      }
      if(BytesRest != 0)
      {
        QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff, BytesRest);
      }
    }
  }
  /* FlashMemOffset is not page-aligned */
  else
  {
    if(NumOfPage == 0)
    {
      /* first page can't hold the rest bytes */
      if(BytesRest > FirstPageRest)
      {
        temp = BytesRest - FirstPageRest;
        QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff, FirstPageRest);
        FlashMemOffset += FirstPageRest;
        Buff += FirstPageRest;
        QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff,  temp);
      }
      else
      {
        QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff,  BytesRest);
      }
    }
    else
    {
      /* write the rest bytes into first page*/
      QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff,  FirstPageRest);
      
      FlashMemOffset += FirstPageRest;
      Buff += FirstPageRest;
      BuffLen -= FirstPageRest;
      NumOfPage = (BuffLen /FLASH_PAGESIZE);
      BytesRest = (BuffLen % FLASH_PAGESIZE);

      while(NumOfPage--)
      {
        QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff,  FLASH_PAGESIZE);
        FlashMemOffset += FLASH_PAGESIZE;
        Buff += FLASH_PAGESIZE;
      }
      if(BytesRest != 0)
      {
        QSPI_Flash_QPIMode_PageWriteWithDMA(OSPIx, FlashMemOffset, Buff,  BytesRest);
      }
    }
  }
  
  return BuffLen;
}


/**
  * @brief  Reads data From FLASH with DMA in QPI mode
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @param  ReadAddr: starting address of the Read operation
  * @param  Buff: the pointer to the buffer that receives data
  * @param  BuffLen: the length in bytes of the buffer pointed to by the parameter Buff
  * @retval the number of bytes actually read and placed in Buff
  */
uint32_t QSPI_Flash_QPIMode_BufferReadWithDMA(OSPI_Type *OSPIx, uint32_t ReadAddr, uint8_t *Buff, uint32_t BuffLen)
{
  OSPI_InitType  OSPI_InitStructType;
  DMA_InitType DMA_InitStructure;
  uint32_t i = 0;
  
  if(BuffLen %4)
  {
    return 0;
  }

  OSPI_RxFIFOThresholdConfig(OSPIx, OSPI_FIFO_RX_THRESHOLD_8);

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_QuadSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_DataLength            = OSPI_DataLength_32BIT;
  OSPI_InitStructType.OSPI_SCLKDivider           = 48;

  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;

  OSPI_InitStructType.OSPI_DataNumber            = BuffLen;
  OSPI_InitStructType.OSPI_WaitCycles            = 2;  /* the default number of dummy clock, refer to winbond datasheet */
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_Cmd(DMA0, DISABLE);
  DMA_DeInit(DMA0_Channel0);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_DestinationBurstSize = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_SourceAddress = (uint32_t) (&OSPIx->DR[0]);
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (Buff);
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_TransferSize = BuffLen/4;
  
  if(OSPIx == OSPI0)
  {
    SYSCFG0->DMA0_REQ_SEL0 = SYSCFG0_DMA_REQUEST_OSPI0_RX;
  }
  if(OSPIx == OSPI1)
  {
    SYSCFG0->DMA0_REQ_SEL0 = SYSCFG0_DMA_REQUEST_OSPI1_RX;
  }
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
  
  OSPI_DMACmd(OSPIx, OSPI_DMA_RX, ENABLE);
  OSPI_DMA_RxFIFOLevelConfig(OSPIx, OSPI_FIFO_RX_THRESHOLD_1);
  
  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);

  OSPI_Cmd(OSPIx, ENABLE);
  OSPI_SendData(OSPIx, W25QX_CMD_FAST_READ);
  OSPI_SendData(OSPIx, ReadAddr);
  
  while(DMA_GetITtatus(DMA0_Channel0, DMA_INT_TFR) == RESET);
  DMA_ClearITStatus(DMA0_Channel0, DMA_INT_TFR);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_Cmd(DMA0, DISABLE);

  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);
  return BuffLen;
}
