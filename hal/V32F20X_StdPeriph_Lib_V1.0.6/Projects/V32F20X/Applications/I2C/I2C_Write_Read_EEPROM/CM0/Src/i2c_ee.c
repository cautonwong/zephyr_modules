/**
  ******************************************************************************
  * @file    i2c_ee.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-12
  * @brief   1. Read and Write EEPROM
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "i2c_ee.h"

uint8_t EE_State;

uint16_t EEPROM_SubAddress;

static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;   

/**
  * @brief  I2C config
  * @param  
  * @retval 
  */
static void I2C_Mode_Configu(void)
{
  I2C_InitType I2C_InitStruct;
  
  /*- Device Init ----------------------------------*/
  I2C_DeInit(EEPROM_I2C);
  I2C_StructInit(&I2C_InitStruct);
  /*- I2C Configuration ----------------------------*/
  I2C_InitStruct.Mode = I2C_MODE_MASTER;
  I2C_InitStruct.SlaveAddress = EEPROM_Block0_ADDRESS;
  I2C_InitStruct.Restart = I2C_RESTART_ENABLE;
  I2C_Init(EEPROM_I2C, &I2C_InitStruct);
  I2C_Cmd(EEPROM_I2C, ENABLE);
}

void I2C_EE_Init(void)
{
  GPIO_InitType  GPIO_InitStructure;
  
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_I2C14, ENABLE);
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_I2C14);
  
  /* PH14 -> I2C0_0 SCL; PH15 -> I2C0_0 SDA*/
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource14, GPIO_AF14_I2C14_SCL);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource15, GPIO_AF14_I2C14_SDA);
  
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
  
  I2C_Mode_Configu();
}

void I2C_EE_BufferWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
  u32 i = 0;
  EE_State = EE_Normal;
  Addr = WriteAddr % I2C_PageSize;
  count = I2C_PageSize - Addr;
  NumOfPage =  NumByteToWrite / I2C_PageSize;
  NumOfSingle = NumByteToWrite % I2C_PageSize;
 
  /* If WriteAddr is I2C_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage == 0) 
    {
      I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      I2C_EE_WaitForCrossPage();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else  
    {
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
        I2C_EE_WaitForCrossPage();
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;
      }

      if(NumOfSingle!=0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        I2C_EE_WaitForCrossPage();
      }
    }
  }
  /* If WriteAddr is not I2C_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage== 0) 
    {
      /* over one page */
      if(NumOfSingle > count)
      {
        temp = NumOfSingle - count;
        I2C_EE_PageWrite(pBuffer, WriteAddr, count);
        I2C_EE_WaitForCrossPage();
        WriteAddr += count;
        pBuffer += count;
        I2C_EE_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    /* If NumByteToWrite > I2C_PageSize */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / I2C_PageSize;
      NumOfSingle = NumByteToWrite % I2C_PageSize;  
      
      if(count != 0)
      {  
        I2C_EE_PageWrite(pBuffer, WriteAddr, count);
        I2C_EE_WaitForCrossPage();
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
        I2C_EE_WaitForCrossPage();
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;  
      }
      if(NumOfSingle != 0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle); 
        I2C_EE_WaitForCrossPage();
      }
    }
  }  
}

uint32_t I2C_EE_ByteWrite(u8* pBuffer, u16 WriteAddr)
{

  I2CTimeout = I2CT_LONG_TIMEOUT;
  EE_State = EE_Normal;
  while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_ACTIVE))
   {
    if((I2CTimeout--) == 0) return 0;
  } 
  
  /*- Send Start+SLA|W+ WriteAddr --------------------*/
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE, (WriteAddr >> 8 ) &0xFF);
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE, WriteAddr & 0xFF);

  /* Send STOP condition */
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE_STOP, *pBuffer);
  
  return 1;
}

/**
  * @brief  AT24C512 128bytes per page
  * @param  
  *    @arg pBuffer:
  *    @arg WriteAddr:
  *    @arg NumByteToWrite:
  * @retval none
  */
uint32_t I2C_EE_PageWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
{
  I2CTimeout = I2CT_LONG_TIMEOUT;
  EE_State = EE_Normal;
  while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_ACTIVE))
   {
    if((I2CTimeout--) == 0) return 0;
  } 
  
  /*- Send Start+SLA|W+ WriteAddr --------------------*/
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE, (WriteAddr >> 8 ) & 0xFF);
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE, WriteAddr & 0xFF);

  /* While there is data to be written */
  NumByteToWrite--;
  while(NumByteToWrite--)
  {
    /* Send the current byte */
    I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE, *pBuffer);
    while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_TFE) == RESET);
    /* Point to the next byte to be written */
    pBuffer++; 
  }
  /* Send STOP condition */
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE_STOP, *pBuffer);
  return 1;
}

uint32_t I2C_EE_BufferRead(u8* pBuffer, u16 ReadAddr, u16 NumByteToRead)
{
  uint32_t i=0;
  I2CTimeout = I2CT_LONG_TIMEOUT;
  EE_State = EE_Normal;
  while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_ACTIVE))
  {
    if((I2CTimeout--) == 0) return 0;
  }
  /*- Read From EEPROM ------------------------------*/
  /*- Send Start+SLA|W+0x00+0x00 --------------------*/
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE, (ReadAddr >> 8 ) &0xFF);
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_WRITE, ReadAddr & 0xFF);

  /*- restart + SLA|R-------------*/
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_READ_RESTART, 0x00);
  while(i++ < (I2C_TRANSFER_SIZE-2))
  {
    while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_RFNE) == RESET);
    *pBuffer++ = I2C_ReceiveData(EEPROM_I2C);
    I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_READ, 0x00);
  }
  while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_RFNE) == RESET);
  *pBuffer++ = I2C_ReceiveData(EEPROM_I2C);
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_READ_STOP, 0x00);
  while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_RFNE) == RESET);
  *pBuffer = I2C_ReceiveData(EEPROM_I2C);
  return 1;
}

void I2C_EE_WaitForCrossPage(void)
{
  uint16_t timeout = I2CT_LONG_TIMEOUT, temp = 0;
  EE_State = EE_Crossing_Page;
  /* timeout > 2ms ------------------ */
  while(timeout--);
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_READ_RESTART, 0x00);

  /* Clear the data in RXFIFO */
  while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_RFNE) == RESET);
  temp = I2C_ReceiveData(EEPROM_I2C);
  /* Send Stop */
  I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_READ_STOP, 0x00);
  /* Clear the data in RXFIFO */
  while(I2C_GetFlag(EEPROM_I2C, I2C_FLAG_RFNE) == RESET);
  temp = I2C_ReceiveData(EEPROM_I2C);
}

/*********************************************END OF FILE**********************/
