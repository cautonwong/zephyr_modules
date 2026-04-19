/**
  * @file    hyperbus_psram.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Read and Write Hyperbus PSRAM with DMA in Non-XIP mode
******************************************************************************/
/* Includes ------------------------------------------------------------------ */
#include "hyperbus_psram.h"

uint32_t word_buffer[18] __attribute__((aligned(4)));

/**
  * @brief  Initializes the specified Hyperbus master
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void HyperbusPSRAM_InitHyperbus(OSPI_Type* OSPIx)
{
  GPIO_InitType GPIO_InitStruct; 
  GPIO_StructInit(&GPIO_InitStruct);
  if(OSPIx == OSPI0)
  {
    /*GPIOD 8, 9, 10, 11, 12, 13, 14, 15-> IO3, IO2, IO1, IO0, IO6, IO7, IO4, IO5*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8,  GPIO_AF12_OSPI0_IO3);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9,  GPIO_AF12_OSPI0_IO2);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF12_OSPI0_IO1);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF12_OSPI0_IO0);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF12_OSPI0_IO6);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF12_OSPI0_IO7);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF12_OSPI0_IO4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF12_OSPI0_IO5);
    /* GPIOG 2, 3, 4, 5,-> CLK, RXDS, nCLK, CS# */
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource2,  GPIO_AF12_OSPI0_SCK);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource3,  GPIO_AF12_OSPI0_TXDM_RXDS);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource4,  GPIO_AF12_OSPI0_SCK_N);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource5,  GPIO_AF12_OSPI0_SS_0_N); 
    
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |\
                                 GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
      
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOG, &GPIO_InitStruct);
    
    SYSCFG0_OSPIXIPCmd(OSPI0, DISABLE);
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_OSPI0);
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_OSPI0, ENABLE);
    NVIC_DisableIRQ(OSPI0_IRQn);
  }
  else if(OSPIx == OSPI1)
  {
    /*GPIOE 7, 8, 10, 11, 13, 14 -> IO2, nCLK, CS, IO1, RXDS, IO0*/
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7,  GPIO_AF12_OSPI1_IO2);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8,  GPIO_AF12_OSPI1_SCK_N);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF12_OSPI1_SS_0_N);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF12_OSPI1_IO1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF12_OSPI1_TXDM_RXDS);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF12_OSPI1_IO0);
    /*GPIOF 12, 13, 14, 15 -> CLK, IO3, IO4, IO5*/
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF12_OSPI1_SCK);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF12_OSPI1_IO3);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF12_OSPI1_IO4);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF12_OSPI1_IO5);
    /*GPIOG 0, 1 -> IO6, IO7*/
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource0,  GPIO_AF12_OSPI1_IO6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource1,  GPIO_AF12_OSPI1_IO7);
    
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_13| GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
      
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOG, &GPIO_InitStruct);

    SYSCFG0_OSPIXIPCmd(OSPI1, DISABLE);
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_OSPI1);
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_OSPI1, ENABLE);
    NVIC_DisableIRQ(OSPI1_IRQn);
  }

  OSPI_ITConfig(OSPIx, OSPI_IT_TXEI, DISABLE);
  OSPI_ITConfig(OSPIx, OSPI_IT_RXFI, DISABLE);
  
  /* pin IOF2 is used for external PSRAM hardware reset */
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOF, &GPIO_InitStruct);
  GPIO_SetBits(GPIOF, GPIO_Pin_2);
}



/**
  * @brief  Resets external PSRAM by pull down its reset pin for more than 200ns
  * @param  None
  * @retval None
  */
void HyperbusPSRAM_HardWareResetPSRAM(void)
{
  uint32_t i = 0;
  GPIO_ResetBits(GPIOF, GPIO_Pin_2);
  for(i = 0; i<1000;i++)
  {
    __NOP();
  }
  GPIO_SetBits(GPIOF, GPIO_Pin_2);
}

/**
  * @brief  Writes data to PSRAM in Non-XIP mode
  * @notice For simplicity, NumByteToWrite is multiple of 4 bytes and NumByteToWrite is not greater than 64.
  * @param  OSPIx: To select OSPI controller, where x can be (0,1)
  * @param  pBuffer: buffer holds the data
  * @param  WriteAddr: starting address of the write operation
  * @param  NumByteToWrite: data length in unit of byte
  * @retval None
  */
void HyperbusPSRAM_WritePSRAM(OSPI_Type* OSPIx, uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
  OSPI_InitType  OSPI_InitStructType;
  DMA_InitType  DMA_InitStructure;
  uint32_t i;

  if(NumByteToWrite == 0 || NumByteToWrite%4 != 0 || NumByteToWrite > 64)
  {
    return;
  }
  
  for(i = 0; i < NumByteToWrite; i = i+4)
  {
    word_buffer[2+(i/4)] = (pBuffer[i+3]<<24)|(pBuffer[i+2]<<16)|(pBuffer[i+1]<<8)|pBuffer[i+0];;
  }
  
  /* fill the command-address */
  if(OSPIx == OSPI1)
  {
    word_buffer[0] = HyperbusWriteInLinearBurst | (((WriteAddr - OSPI1_PSRAM_StartAddr) & 0xfffffff8)>>4);
    word_buffer[1] = (WriteAddr - OSPI1_PSRAM_StartAddr) & 0x7;
  }
  else
  {
    word_buffer[0] = HyperbusWriteInLinearBurst | (((WriteAddr- OSPI0_PSRAM_StartAddr) & 0xfffffff8)>>4);
    word_buffer[1] = (WriteAddr - OSPI0_PSRAM_StartAddr) & 0x7;
  }

  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel1, DISABLE);
  DMA_Cmd(DMA0, DISABLE);
  
  DMA_DeInit(DMA0_Channel0);
  DMA_DeInit(DMA0_Channel1);
  
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize           = DMA_SourceBurstSize_16;
  DMA_InitStructure.DMA_DestinationBurstSize      = DMA_DestinationBurstSize_16;
  DMA_InitStructure.DMA_SourceTransferWidth       = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth  = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_SourceAddress             = (uint32_t) (&word_buffer[0]);
  DMA_InitStructure.DMA_DestinationAddress        = (uint32_t) (&TEST_OSPI->DR[0]); 
  DMA_InitStructure.DMA_SourceAddressControl      = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_DIR                       = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_TransferSize              = NumByteToWrite/4 + 2;
  
  if(OSPIx == OSPI0)
  {
    SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0,SYSCFG0_DMA_REQUEST_OSPI0_TX);
  }
  if(OSPIx == OSPI1)
  {
    SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0,SYSCFG0_DMA_REQUEST_OSPI1_TX);
  }
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
  

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_INSTLength            = OSPI_INSTLength_NO;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_48BIT;
  OSPI_InitStructType.OSPI_DataLength            = OSPI_DataLength_32BIT;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_AddrDtrMode           = OSPI_SPI_DTR_ENABLE;
  OSPI_InitStructType.OSPI_Hyperbus              = OSPI_Hyperbus_Enable;
  OSPI_InitStructType.OSPI_RXDS                  = OSPI_RXDS_DISABLE;
  OSPI_InitStructType.OSPI_DataNumber            = NumByteToWrite/4 + 2;
  OSPI_InitStructType.OSPI_WaitCycles            = 6;
  OSPI_InitStructType.OSPI_SCLKDivider           = 4;
  OSPI_InitStructType.OSPI_DDR_DRIVE_EDGE        = 1;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  
  OSPI_DMACmd(TEST_OSPI, OSPI_DMA_TX, ENABLE);
  OSPI_DMA_TxFIFOLevelConfig(OSPIx, OSPI_FIFO_TX_THRESHOLD_16);
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
}


/**
  * @brief  Reads data From PSRAM in Non-XIP mode
  * @notice This function demands that NumByteToRead is multiple of 4 bytes for simplicity.
  * @param  OSPIx: To select OSPI controller, where x can be (0,1) 
  * @param  pBuffer: the pointer to the buffer that receives data
  * @param  ReadAddr: starting address of the Read operation
  * @param  NumByteToRead: the length in bytes of the buffer pointed to by the parameter pBuffer
  * @retval None
  */
void HyperbusPSRAM_ReadPSRAM(OSPI_Type* OSPIx, uint32_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
  OSPI_InitType  OSPI_InitStructType;
  DMA_InitType  DMA_InitStructure;
  uint32_t i;

  if(NumByteToRead == 0 || NumByteToRead%4 != 0)
  {
    return;
  }

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_INSTLength            = OSPI_INSTLength_NO;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_48BIT;
  OSPI_InitStructType.OSPI_DataLength            = OSPI_DataLength_32BIT;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_AddrDtrMode           = OSPI_SPI_DTR_ENABLE;
  OSPI_InitStructType.OSPI_Hyperbus              = OSPI_Hyperbus_Enable;
  OSPI_InitStructType.OSPI_RXDS                  = OSPI_RXDS_ENABLE;
  OSPI_InitStructType.OSPI_DataNumber            = NumByteToRead/4;
  OSPI_InitStructType.OSPI_WaitCycles            = 6;
  OSPI_InitStructType.OSPI_SCLKDivider           = 4;
  OSPI_InitStructType.OSPI_DDR_DRIVE_EDGE        = 1;
  OSPI_Init(TEST_OSPI, &OSPI_InitStructType);
  
  DMA_ChannelCmd(DMA0_Channel1, DISABLE);
  DMA_Cmd(DMA0, DISABLE);
  DMA_DeInit(DMA0_Channel1);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize           = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_DestinationBurstSize      = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_SourceTransferWidth       = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth  = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_SourceAddress             = (uint32_t) (&TEST_OSPI->DR[0]);
  DMA_InitStructure.DMA_DestinationAddress        = (uint32_t) (pBuffer);
  DMA_InitStructure.DMA_SourceAddressControl      = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_DIR                       = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_TransferSize              = NumByteToRead/4;
  DMA_InitStructure.DMA_SourceRequestSelect       = DMA_SourceRequestSelect_1;
  
  if(TEST_OSPI == OSPI0)
  {
    SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ1,SYSCFG0_DMA_REQUEST_OSPI0_RX);
  }
  if(TEST_OSPI == OSPI1)
  {
    SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ1,SYSCFG0_DMA_REQUEST_OSPI1_RX);
  }
  
  DMA_Init(DMA0_Channel1, &DMA_InitStructure);
  OSPI_DMACmd(TEST_OSPI, OSPI_DMA_RX, ENABLE);
  OSPI_DMA_RxFIFOLevelConfig(TEST_OSPI, OSPI_FIFO_RX_THRESHOLD_1);
  
  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel1, ENABLE);

  OSPI_Cmd(TEST_OSPI, ENABLE);
  if(TEST_OSPI == OSPI1)
  {
    OSPI_SendData(TEST_OSPI, (HyperbusReadInLinearBurst|(((ReadAddr - OSPI1_PSRAM_StartAddr) & 0xfffffff8)>>4)));
    OSPI_SendData(TEST_OSPI, (ReadAddr - OSPI1_PSRAM_StartAddr) & 0x7);
  }
  else
  {
    OSPI_SendData(TEST_OSPI, (HyperbusReadInLinearBurst|(((ReadAddr - OSPI0_PSRAM_StartAddr) & 0xfffffff8)>>4)));
    OSPI_SendData(TEST_OSPI, (ReadAddr - OSPI0_PSRAM_StartAddr) & 0x7);
  }
  
  while(DMA_GetITtatus(DMA0_Channel1, DMA_INT_TFR) == RESET);
  DMA_ClearITStatus(DMA0_Channel1, DMA_INT_TFR);
  DMA_ChannelCmd(DMA0_Channel1, DISABLE);
  DMA_Cmd(DMA0, DISABLE);
  
  while(OSPI_GetFlagStatus(TEST_OSPI,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(TEST_OSPI, DISABLE);
}



