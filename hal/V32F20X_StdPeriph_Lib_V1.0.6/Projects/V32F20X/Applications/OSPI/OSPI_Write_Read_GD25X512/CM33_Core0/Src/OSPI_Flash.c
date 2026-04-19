/**
  ******************************************************************************
  * @file   OSPI_Flash.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-12
  * @brief   Read and Write OSPI Flash
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "OSPI_Flash.h"

uint32_t word_buffer[66] __attribute__((aligned(4)));


/**
  * @brief  Deinitializes the specified OSPI peripherals
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void OSPI_Flash_DeInit(OSPI_Type *OSPIx)
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
  * @brief  Initializes the specified OSPI peripherals
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void OSPI_Flash_Init(OSPI_Type* OSPIx)
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
    /*GPIOG 2, 3,  5,-> SCK, DQS, CS*/
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource2,  GPIO_AF12_OSPI0_SCK);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource3,  GPIO_AF12_OSPI0_TXDM_RXDS);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource5,  GPIO_AF12_OSPI0_SS_0_N); 
    
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |\
                                 GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
      
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3  | GPIO_Pin_5;
    GPIO_Init(GPIOG, &GPIO_InitStruct);

    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_OSPI0);
    SYSCFG0_OSPIClockConfig(OSPI0, SYSCFG0_OSPI_CLKSRC_PLL0, 2);
		SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_OSPI0, ENABLE);
    SYSCFG0_OSPIXIPCmd(OSPI0, DISABLE);
    OSPI_Cmd(OSPI0, DISABLE);
  }
  else if(OSPIx == OSPI1)
  {
    /*GPIOE 7,  10, 11, 14 -> IO2,  CS, IO1, IO0*/
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7,  GPIO_AF12_OSPI1_IO2);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF12_OSPI1_SS_0_N);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF12_OSPI1_IO1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF12_OSPI1_IO0);
    /*GPIOF 12, 13, 14, 15 -> SCK, IO3, IO4, IO5*/
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF12_OSPI1_SCK);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF12_OSPI1_IO3);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF12_OSPI1_IO4);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF12_OSPI1_IO5);
    /*GPIOG 0, 1 -> IO6, IO7*/
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource0,  GPIO_AF12_OSPI1_IO6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource1,  GPIO_AF12_OSPI1_IO7);
    
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
      
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOG, &GPIO_InitStruct);
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_OSPI1);
    SYSCFG0_OSPIClockConfig(OSPI1, SYSCFG0_OSPI_CLKSRC_PLL0, 2);
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_OSPI1, ENABLE);
    SYSCFG0_OSPIXIPCmd(OSPI1, DISABLE);
    OSPI_Cmd(OSPI1, DISABLE);		
  }
}

/**
  * @brief  Resets FLASH by pulling down FLASH RESET# pin.
  * @notice Connnect pin AF12 to FLASH RESET# pin
  * @param  None
  * @retval None
  */
void OSPI_Flash_HardwareReset(void)
{
  /* pin AF12 is not dedicated to doing hardware reset,
   * you can select other pin when FLASH hardware reset is needed.
   */
  GPIO_InitType GPIO_InitStruct; 
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOF, &GPIO_InitStruct);
  GPIO_SetBits(GPIOF, GPIO_Pin_2);
  GPIO_ResetBits(GPIOF, GPIO_Pin_2);
  /* delay 1ms, FLASH hardware reset pulse width
   * should be greater than 1us
   */
  STD_Delay(1); 
  GPIO_SetBits(GPIOF, GPIO_Pin_2);
}

/**
  * @brief  Waits for completion of write operation in SPI mode
  * @param  OSPIx: To select OSPI controller, where x can be (0,1) 
  * @retval None
  */
void OSPI_Flash_SPIModeWaitForWriteEnd(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t status = 0;

  OSPI_Cmd(OSPIx, DISABLE);
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat   = OSPI_SPIFrameFormat_StandardSPI;
  OSPI_InitStructType.OSPI_TransferMode     = OSPI_TransferMode_TXAndRX;
  OSPI_InitStructType.OSPI_ADDRLength       = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat   = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStructType.OSPI_SCLKDivider      = 8;
  OSPI_InitStructType.OSPI_DataNumber       = 2;

  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_Cmd(OSPIx, ENABLE);

  do{
    OSPI_SendData(OSPIx, GD25X_CMD_ReadStatusReg);
    OSPI_SendData(OSPIx, GD25X_DummyByte);
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_RFNE));
    status = OSPI_ReceiveData(OSPIx);
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_RFNE));
    status = OSPI_ReceiveData(OSPIx);
  }while(status&GD25X_SR_WIP_MASK);

  while(SET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY));
  
  OSPI_Cmd(OSPIx, DISABLE);
}

/**
  * @brief  Waits for completion of write operation in SPI mode
  * @param  OSPIx: To select OSPI controller, where x can be (0,1) 
  * @retval None
  */
void OSPI_Flash_OPIModeWaitForWriteEnd(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t status = 0;

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat   = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode     = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength       = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_SCLKDivider      = 8;
  OSPI_InitStructType.OSPI_ADDRINSTFormat   = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber       = 1;
  OSPI_InitStructType.OSPI_WaitCycles       = 8;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_Cmd(OSPIx, ENABLE);
  do{
      OSPI_SendData(OSPIx, GD25X_CMD_ReadStatusReg);
      while(OSPI_GetFlagStatus(OSPIx, OSPI_FLAG_STATUS_RFNE) == RESET){}
      status = OSPI_ReceiveData(OSPIx);
      while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
    }while(status&GD25X_SR_WIP_MASK);

  OSPI_Cmd(OSPIx, DISABLE);
}


/**
  * @brief  Resets FLASH by software.
  * @notice Once the Reset command is accepted by the device, the device
  *         will take approximately tRST=30us to reset. During this period,
  *         no command will be accepted.  
  * @param  SSIx: where x can be (0,1) to select SSI controller
  * @retval None
  */
void OSPI_Flash_SoftwareReset(OSPI_Type* OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint8_t i = 0;
 
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_StandardSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_SCLKDivider           = 8;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStructType.OSPI_DataNumber            = 0;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPI_Cmd(OSPIx, ENABLE);
  OSPI_SendData(OSPIx, GD25X_CMD_ResetEnable);
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE) == RESET){}
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);
  for(i=0; i<255; i++)
  {
    __NOP(); __NOP();
  }

  OSPI_Cmd(OSPIx, ENABLE);
  OSPI_SendData(OSPIx, GD25X_CMD_Reset);
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE) == RESET){}
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);
  for(i=0; i<255; i++)
  {
    __NOP(); __NOP();
  }

  OSPI_Flash_SPIModeWaitForWriteEnd(OSPIx);
}

/**
  * @brief  Enables write operation in OPI mode
  * @notice Write operation must be enabled prior to every Page Program, Quad Page Program, Sector Erase, Block 
  *         Erase, Chip Erase, Write Status Register and Erase/Program Security Registers instruction
  * @param  OSPIx: To select SSI controller, where x can be (0,1) 
  * @retval none
  */
void OSPI_Flash_OPIModeWriteEnable(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat   = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode     = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength       = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_SCLKDivider      = 8;
  OSPI_InitStructType.OSPI_ADDRINSTFormat   = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber       = 0;
  OSPI_InitStructType.OSPI_WaitCycles       = 0;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPI_Cmd(OSPIx, ENABLE);
  OSPI_SendData(OSPIx, GD25X_CMD_WriteEnable);
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE) == RESET){}
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);
}

/**
  * @brief  Waits for the completion of entering OPI mode.
  * @param  OSPIx: To select SSI controller, where x can be (0,1)
  * @retval None
  */
void OSPI_Flash_WaitForEnterOPIMode(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t Status;

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_WaitCycles            = 8;
  OSPI_InitStructType.OSPI_SCLKDivider           = 16;

  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber            = 1;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_Cmd(OSPIx, ENABLE);
  do{
    OSPI_SendData(OSPIx, GD25X_CMD_ReadConfigReg);
    OSPI_SendData(OSPIx, 0x00000);
    while(OSPI_GetFlagStatus(OSPIx, OSPI_FLAG_STATUS_RFNE) == RESET){}
    Status = (uint8_t)OSPI_ReceiveData(OSPIx);
    while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  }while((Status&GD25X_IOModeOctalWithDQS)!= GD25X_IOModeOctalWithDQS);

  OSPI_Cmd(OSPIx, DISABLE);
}


/**
  * @brief  Switches the FLASH from SPI mode to OPI mode.
  * @notice Upon power-up, the default state of the device is SPI mode
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval None
  */
void OSPI_Flash_EnterOPIMode(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStructType.OSPI_DataNumber            = 0;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
	OSPI_InitStructType.OSPI_SCLKDivider           = 8;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPI_Cmd(OSPIx, ENABLE);
  /* The Write Enable Latch (WEL) bit must be set prior to 
   * writing Nonvolatile/Volatile Configuration Register */
  OSPI_SendData(OSPIx, GD25X_CMD_WriteEnable);
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE) == RESET){}
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);

  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_DataLength            = OSPI_DataLength_32BIT;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStructType.OSPI_DataNumber            = 2;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_InitStructType.OSPI_SCLKDivider           = 8;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_Cmd(OSPIx, ENABLE);
  /* Issue WRCR command, 
   * set I/O mode register value to 10110111b(Octal with DQS).
   * Only the LSB is used to access different register settings, 
   * thereby 8-byte data '0xFFFEFFFF FEFFFFFF' represents '10110111b'
   */
  OSPI_SendData(OSPIx, GD25X_CMD_WriteConfigReg);
  OSPI_SendData(OSPIx, 0x00000);
  OSPI_SendData(OSPIx, 0xFFFEFFFF);
  OSPI_SendData(OSPIx, 0xFEFFFFFF);

  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE) == RESET){}
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);

  OSPI_Flash_WaitForEnterOPIMode(OSPIx);
}

/**
  * @brief  Waits for the completion of exiting OPI mode.
  * @param  OSPIx: To select SSI controller, where x can be (0,1)
  * @retval None
  */
void OSPI_Flash_WaitForExitOPIMode(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t  status = 0;

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat      = OSPI_SPIFrameFormat_StandardSPI;
  OSPI_InitStructType.OSPI_TransferMode        = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength          = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_SCLKDivider         = 16;
  OSPI_InitStructType.OSPI_ADDRINSTFormat      = OSPI_ADDRINSTFormat_TT0;
  OSPI_InitStructType.OSPI_WaitCycles          = 8;
  OSPI_InitStructType.OSPI_DataNumber          = 1;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_Cmd(OSPIx, ENABLE);
  do{
    OSPI_SendData(OSPIx, GD25X_CMD_ReadConfigReg);
    OSPI_SendData(OSPIx, GD25X_DummyByte);
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE));
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_RFNE));
    status = OSPI_ReceiveData(OSPIx);
    while(RESET == OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_RFNE));
    status = OSPI_ReceiveData(OSPIx);
  }while((status&GD25X_IOModeSPIWithDQS) != GD25X_IOModeSPIWithDQS);

  OSPI_Cmd(OSPIx, DISABLE);
}

/**
  * @brief  Switches the FLASH from OPI mode to SPI mode.
  * @notice Upon power-up, the default state of the device is SPI mode
  * @param  OSPIx: To select OSPI controller, where x can be (0,1) 
  * @retval None
  */
void OSPI_Flash_ExitOPIMode(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t i = 0;
  OSPI_Flash_OPIModeWriteEnable(OSPIx);
  
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_DataLength            = OSPI_DataLength_32BIT;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber            = 1;
  OSPI_InitStructType.OSPI_DataLength            = OSPI_DataLength_8BIT;
  OSPI_InitStructType.OSPI_WaitCycles            = 0;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPI_Cmd(OSPIx, ENABLE);
  OSPI_SendData(OSPIx, GD25X_CMD_WriteConfigReg);
  OSPI_SendData(OSPIx, 0x00000);
  OSPI_SendData(OSPIx, GD25X_IOModeSPIWithDQS);
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE) == RESET){}
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}

  OSPI_Cmd(OSPIx, DISABLE);
  OSPI_Flash_WaitForExitOPIMode(OSPIx);
}

/**
  * @brief  Gets FLASH device ID in OPI mode
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval 32-bit FLASH device identification
  */
uint32_t OSPI_Flash_OPIModeReadID(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;
  uint32_t FLASHID = 0;

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat   = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode     = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength       = OSPI_ADDRLength_NO;
  OSPI_InitStructType.OSPI_SCLKDivider      = 8;

  OSPI_InitStructType.OSPI_ADDRINSTFormat   = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataLength       = OSPI_DataLength_32BIT;
  OSPI_InitStructType.OSPI_DataNumber       = 1;
  OSPI_InitStructType.OSPI_WaitCycles       = 8;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_Cmd(OSPIx, ENABLE);

  OSPI_SendData(OSPIx, GD25X_CMD_ReadFlashID);
  while(OSPI_GetFlagStatus(OSPIx, OSPI_FLAG_STATUS_RFNE) == RESET){}
  FLASHID = OSPI_ReceiveData(OSPIx);

  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);

  return FLASHID;
}

/**
  * @brief  Sets all memory within a specified sector (4K-bytes)
  *         to the erased state of all 1s (FFh) in OPI mode
  * @notice A Write Enable instruction must be executed before 
  *         the device will accept the sector erase instruction
  * @param  OSPIx: To select OSPI controller,where x can be (0,1)
  * @param  SectorAddr: sector address
  * @retval none
  */
void OSPI_Flash_OPIModeSectorErase(OSPI_Type *OSPIx, uint32_t SectorAddr)
{
  OSPI_InitType  OSPI_InitStructType;

  OSPI_Flash_OPIModeWriteEnable(OSPIx);

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat   = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode     = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_ADDRLength       = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_SCLKDivider      = 8;
  OSPI_InitStructType.OSPI_ADDRINSTFormat   = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber       = 0;
  OSPI_InitStructType.OSPI_WaitCycles       = 0;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPI_Cmd(OSPIx, ENABLE);
  OSPI_SendData(OSPIx, GD25X_CMD_SectorErase);
  OSPI_SendData(OSPIx, SectorAddr);
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_TFE) == RESET){}
  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);
  OSPI_Flash_OPIModeWaitForWriteEnd(OSPIx);
}


/**
  * @brief  Writes up to 256 bytes (a page) of data to a specified page with DMA in OPI mode
  * @notice This function demands that  WriteAddr is 4-byte aligned and NumByteToWrite 
  *         is multiple of 4 bytes for simplicity.
  * @param  OSPIx: To select OSPI controller, where x can be (0,1) 
  * @param  pBuffer: starting address of the Write operation
  * @param  WriteAddr: buffer holds the data
  * @param  NumByteToWrite: data length in unit of byte
  * @retval none
  */
void OSPI_Flash_PageWrite(OSPI_Type *OSPIx, const uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
  OSPI_InitType  OSPI_InitStructType;
  DMA_InitType DMA_InitStructure;
  uint32_t i;

  if(NumByteToWrite > FLASH_PAGESIZE)
  {
    NumByteToWrite = FLASH_PAGESIZE;
    printf("SPI_Flash_PageWrite too large!\r\n");
  }
  
  for(i = 0; i < NumByteToWrite; i = i+4)
  {
    word_buffer[2+(i/4)] = (pBuffer[i]<<24)|(pBuffer[i+1]<<16)|(pBuffer[i+2]<<8)|pBuffer[i+3];;
  }

  /*-- Write enable --*/
  OSPI_Flash_OPIModeWriteEnable(OSPIx);

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat  = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode    = OSPI_TransferMode_TX;
  OSPI_InitStructType.OSPI_DataLength      = OSPI_DataLength_32BIT;
  OSPI_InitStructType.OSPI_SCLKDivider     = 2;
  OSPI_InitStructType.OSPI_ADDRINSTFormat  = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber      = NumByteToWrite;
  OSPI_InitStructType.OSPI_WaitCycles      = 0;
  OSPI_InitStructType.OSPI_ADDRLength      = OSPI_ADDRLength_24BIT;
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  word_buffer[0] = GD25X_CMD_PageProgram;
  word_buffer[1] = WriteAddr;

  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_Cmd(DMA0, DISABLE);
  DMA_DeInit(DMA0_Channel0);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize           = DMA_SourceBurstSize_8;
  DMA_InitStructure.DMA_DestinationBurstSize      = DMA_DestinationBurstSize_8;
  DMA_InitStructure.DMA_SourceTransferWidth       = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth  = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_SourceAddress             = (uint32_t) (&word_buffer[0]);
  DMA_InitStructure.DMA_DestinationAddress        = (uint32_t) (&OSPIx->DR[0]);
  DMA_InitStructure.DMA_SourceAddressControl      = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_DIR                       = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_TransferSize              = (NumByteToWrite/4) + 2;
  
  if(OSPIx == OSPI0)
  {
    SYSCFG0->DMA0_REQ_SEL0 = SYSCFG0_DMA_REQUEST_OSPI0_TX;
  }
  if(OSPIx == OSPI1)
  {
    SYSCFG0->DMA0_REQ_SEL0 = SYSCFG0_DMA_REQUEST_OSPI1_TX;
  }
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
  
  OSPI_DMACmd(OSPIx, OSPI_DMA_TX, ENABLE);
  OSPI_DMA_TxFIFOLevelConfig(OSPIx, OSPI_FIFO_TX_THRESHOLD_8);
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

  OSPI_Flash_OPIModeWaitForWriteEnd(OSPIx);
}

/**
  * @brief  Writes data to FLASH with DMA in OPI mode
  * @notice This function demands that  WriteAddr is 4-byte aligned and
  *         NumByteToWrite is multiple of 4 bytes for simplicity. 
  * @param  OSPIx: To select OSPI controller, where x can be (0,1)
  * @param  pBuffer: buffer holds the data
  * @param  WriteAddr: starting address of the write operation
  * @param  NumByteToWrite: data length in unit of byte
  * @retval the number of bytes actually written
  */
uint32_t OSPI_Flash_BufferWrite(OSPI_Type *OSPIx, const uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, Count = 0, temp = 0;
  Addr = (uint8_t)(WriteAddr % FLASH_PAGESIZE);
  Count = (uint8_t)(FLASH_PAGESIZE - Addr);
  NumOfPage = (uint8_t)(NumByteToWrite / FLASH_PAGESIZE);
  NumOfSingle = (uint8_t)(NumByteToWrite % FLASH_PAGESIZE);
  
  if((WriteAddr%4) != 0
    ||(NumByteToWrite%4) != 0)
  {
    return 0;
  }

  /* WriteAddr is page-aligned */
  if(Addr == 0)
  {
    if(NumOfPage == 0)
    {
      OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, NumOfSingle);
    }
    else
    {
      while(NumOfPage--)
      {
        OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, FLASH_PAGESIZE);
        WriteAddr += FLASH_PAGESIZE;
        pBuffer += FLASH_PAGESIZE;
      }
      if(NumOfSingle != 0)
      {
        OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
  /* WriteAddr is not page-aligned */
  else
  {
    if(NumOfPage == 0)
    {
      /* first page can't hold the rest bytes */
      if(NumOfSingle > Count)
      {
        temp = NumOfSingle - Count;
        OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, Count);
        WriteAddr += Count;
        pBuffer += Count;
        OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, temp);
      }
      else
      {
        OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else
    {
      /* write the rest bytes into first page*/
      NumByteToWrite -= Count;
      NumOfPage   = (uint8_t)(NumByteToWrite / FLASH_PAGESIZE);
      NumOfSingle = (uint8_t)(NumByteToWrite % FLASH_PAGESIZE);
      OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, Count);
      
      WriteAddr += Count;
      pBuffer += Count;

      while(NumOfPage--)
      {
        OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, FLASH_PAGESIZE);
        WriteAddr += FLASH_PAGESIZE;
        pBuffer += FLASH_PAGESIZE;
      }
      if(NumOfSingle != 0)
      {
        OSPI_Flash_PageWrite(OSPIx, pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
  
  return NumByteToWrite;
}

/**
  * @brief  Reads data From FLASH with DMA in OPI mode
  * @param  OSPIx: To select SSI controller, where x can be (0,1) 
  * @param  ReadAddr: starting address of the Read operation
  * @param  pBuffer: the pointer to the buffer that receives data
  * @param  NumByteToRead: the length in bytes of the buffer pointed to by the parameter pBuffer
  * @retval the number of bytes actually read and placed in Buff
  */
void OSPI_Flash_BufferRead(OSPI_Type *OSPIx, uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
  OSPI_InitType  OSPI_InitStructType;
  DMA_InitType DMA_InitStructure;

  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_SCLKDivider           = 48;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber            = NumByteToRead;
  OSPI_InitStructType.OSPI_WaitCycles            = 16;
  OSPI_Init(OSPIx, &OSPI_InitStructType);
  OSPI_RxFIFOThresholdConfig(OSPIx, OSPI_FIFO_RX_THRESHOLD_8);
  
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_Cmd(DMA0, DISABLE);
  DMA_DeInit(DMA0_Channel0);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize            = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_DestinationBurstSize       = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_SourceTransferWidth        = DMA_SourceTransferWidth_8Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth   = DMA_DestinationTransferWidth_8Bit;
  DMA_InitStructure.DMA_SourceAddress              = (uint32_t) (&OSPIx->DR[0]);
  DMA_InitStructure.DMA_DestinationAddress         = (uint32_t) (pBuffer);
  DMA_InitStructure.DMA_SourceAddressControl       = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl  = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_DIR                        = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_TransferSize               = NumByteToRead;
  
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

  OSPI_SendData(OSPIx, GD25X_CMD_OctalOutputFastRead);
  OSPI_SendData(OSPIx, ReadAddr);
  
  while(DMA_GetITtatus(DMA0_Channel0, DMA_INT_TFR) == RESET);
  DMA_ClearITStatus(DMA0_Channel0, DMA_INT_TFR);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_Cmd(DMA0, DISABLE);

  while(OSPI_GetFlagStatus(OSPIx,OSPI_FLAG_STATUS_BUSY) == SET){}
  OSPI_Cmd(OSPIx, DISABLE);
}



/**
  * @brief  Configures XIP read in OPI mode
  * @param  OSPIx: where x can be (0,1) to select OSPI controller
  * @retval none
  */
void OSPI_XIP_ReadConfig(OSPI_Type *OSPIx)
{
  OSPI_InitType  OSPI_InitStructType;

  SYSCFG0_OSPIXIPCmd(OSPIx, DISABLE);
  OSPI_Cmd(OSPIx, DISABLE);  
  
  OSPI_StructInit(&OSPI_InitStructType);
  OSPI_InitStructType.OSPI_SPIFrameFormat        = OSPI_SPIFrameFormat_OctalSPI;
  OSPI_InitStructType.OSPI_TransferMode          = OSPI_TransferMode_RX;
  OSPI_InitStructType.OSPI_ADDRLength            = OSPI_ADDRLength_24BIT;
  OSPI_InitStructType.OSPI_ADDRINSTFormat        = OSPI_ADDRINSTFormat_TT2;
  OSPI_InitStructType.OSPI_DataNumber            = 4;
  OSPI_InitStructType.OSPI_WaitCycles            = 16;  /*dummy clocks*/
  OSPI_InitStructType.OSPI_SCLKDivider           = 2; 
  OSPI_Init(OSPIx, &OSPI_InitStructType);

  OSPIx->SPI_CTRLR0 |= (OSPI_SPI_CTRLR0_XIP_INST_EN |OSPI_SPI_CTRLR0_XIP_DFS_HC);

  OSPIx->XIP_INCR_INST = GD25X_CMD_OctalOutputFastRead;

  OSPI_Cmd(OSPIx, ENABLE);
  SYSCFG0_OSPIXIPCmd(OSPIx, ENABLE);
}









/*********************************** END OF FILE ******************************/