/**
  ******************************************************************************
  * @file    FM25Q32.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "FM25Q32.h"
#include <stdio.h>

__IO uint32_t nTicks;

/**
  * @brief  Get current ticks. 
  * @param  None
  * @retval None
  */
uint32_t System_GetTick(void)
{
  return nTicks;
}

/**
  * @brief  SPI initialization for flash memory device. 
  * @param  None
  * @retval None
  */
void FlashMem_SPI_Init(void)
{
  SPI_InitType SPI_InitStruct;
  GPIO_InitType GPIO_InitStruct;
  
  CORTEX_SystemTick_Config(26214400/1000 - 1);
  
  /* CSN pin output high */
  GPIO_WriteBit(CSN_GPIO_DAT, CSN_PinNum, 1);
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUTPUT_CMOS;
  GPIO_InitStruct.GPIO_Pin = CSN_Pin;
  GPIOBToF_Init(CSN_GPIO, &GPIO_InitStruct);

  SPI_DeviceInit(SPI_Flash);
  SPI_StructInit(&SPI_InitStruct);
  SPI_InitStruct.ClockDivision = SPI_CLKDIV_2;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_ENABLE;
  SPI_Init(SPI_Flash, &SPI_InitStruct);
  
  SPI_Cmd(SPI_Flash, ENABLE);
}

/**
  * @brief  SPI De-Initialization for flash memory device. 
  * @param  None
  * @retval None
  */
void FlashMem_SPI_DeInit(void)
{
  GPIO_InitType GPIO_InitStruct;
  
  SysTick->CTRL = 0;

  SPI_DeviceInit(SPI_Flash);
  
  /* CSN pin forbidden */
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIO_InitStruct.GPIO_Pin = CSN_Pin;
  GPIOBToF_Init(CSN_GPIO, &GPIO_InitStruct);
}

/**
  * @brief  SPI configure CSN pin. 
  */
void FlashMem_SPI_SetCSN(uint8_t level)
{
  if (level)    GPIO_WriteBit(CSN_GPIO_DAT, CSN_PinNum, 1);
  else          GPIO_WriteBit(CSN_GPIO_DAT, CSN_PinNum, 0);
}

/**
  * @brief  SPI transfer 
  * @param  
  * @retval 
  */
int32_t FlashMem_SPI_Transfer(uint8_t *w_data, uint8_t *r_data, uint32_t len, uint32_t Timeout)
{
  uint32_t tick_cur, Tickstart;
  uint32_t i;
  
  Tickstart = System_GetTick();
  
  for (i=0; i<len; i++)
  {
    /* While until TX FIFO is empty */
    while (SPI_GetStatus(SPI_Flash, SPI_STS_TXEMPTY) == 0U)
    {
      if (Timeout == 0UL)    return -1;
      else
      {
        tick_cur = System_GetTick();
        if (tick_cur >= Tickstart)
        {
          if ((tick_cur-Tickstart) > Timeout)    return -1;
        }
        else
        {
          if ((0xFFFFFFFFUL-Tickstart+tick_cur) > Timeout)    return -1;
        }
      }  
    }
    if (w_data == NULL)
      SPI_SendData(SPI_Flash, 0x00);
    else
      SPI_SendData(SPI_Flash, w_data[i]);
    
    /* Wait until receive FIFO is not empty, receive one byte data */
    while (SPI_GetStatus(SPI_Flash, SPI_STS_RNE) == 0U)
    {
      if (Timeout == 0UL)    return -1;
      else
      {
        tick_cur = System_GetTick();
        if (tick_cur >= Tickstart)
        {
          if ((tick_cur-Tickstart) > Timeout)    return -1;
        }
        else
        {
          if ((0xFFFFFFFFUL-Tickstart+tick_cur) > Timeout)    return -1;
        }
      }  
    }
    if (r_data == NULL)
      SPI_ReceiveData(SPI_Flash);
    else
      r_data[i] = SPI_ReceiveData(SPI_Flash);
  }
  
  while (SPI_GetStatus(SPI_Flash, SPI_STS_BSY) == 1U)
  {
    if (Timeout == 0UL)    return -1;
    else
    {
      tick_cur = System_GetTick();
      if (tick_cur >= Tickstart)
      {
        if ((tick_cur-Tickstart) > Timeout)    return -1;
      }
      else
      {
        if ((0xFFFFFFFFUL-Tickstart+tick_cur) > Timeout)    return -1;
      }
    }    
  }
  
  return 0;
}

/**
  * @brief  Write enable 
  * @param  None
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_WriteEnable(void)
{
  uint8_t tmp;
  int32_t retval;

  tmp = FM25Q_WriteEnable;
  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(&tmp, NULL, 1, 2);
  FlashMem_SPI_SetCSN(1);

  return retval;
}

/**
  * @brief  Write disbale 
  * @param  None
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_WriteDisable(void)
{
  uint8_t tmp;
  int32_t retval;

  tmp = FM25Q_WriteDisable;
  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(&tmp, NULL, 1, 2);
  FlashMem_SPI_SetCSN(1);

  return retval;
}

/**
  * @brief  Read status register 1
  * @param  [out]data: The pointer of read data
  * @note   S7    S6   S5  S4   S3   S2   S1   S0
  *         SRP0  SEC  TB  BP2  BP1  BP0  WEL  WIP
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_ReadStaReg_1(uint8_t *data)
{
  uint8_t wBuffer[2] = { FM25Q_ReadStatusReg_1, 0x00 };
  uint8_t rBuffer[2];
  int32_t retval;

  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(wBuffer, rBuffer, 2, 2);
  FlashMem_SPI_SetCSN(1);

  *data = rBuffer[1];
  return retval;
}

/**
  * @brief  Read status register 2
  * @param  [out]data: The pointer of read data
  * @note   S15   S14   S13  S12   S11   S10   S9   S8
  *         SUS   CMP   LB3  LB2   LB1   LB0   QE   SRP1
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_ReadStaReg_2(uint8_t *data)
{
  uint8_t wBuffer[2] = { FM25Q_ReadStatusReg_2, 0x00 };
  uint8_t rBuffer[2];
  int32_t retval;

  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(wBuffer, rBuffer, 2, 2);
  FlashMem_SPI_SetCSN(1);

  *data = rBuffer[1];
  return retval;
} 

/**
  * @brief  Wait for idle
  */
int32_t FlashMem_WaitForIdle(uint32_t Tickstart, uint32_t Timeout)
{
  uint8_t data;
  uint32_t tick_cur;

  do 
  {
    FlashMem_ReadStaReg_1(&data);

    if (Timeout == 0UL)
    {
      return -1;
    }
    else
    {
      tick_cur = System_GetTick();
      if (tick_cur >= Tickstart)
      {
        if ((tick_cur-Tickstart) > Timeout)
        {
          return -1;
        }
      }
      else
      {
        if ((0xFFFFFFFFUL-Tickstart+tick_cur) > Timeout)
        {
          return -1;
        }
      }
    }

  } while((data & 0x01) == 0x01);

  return 0;
}

/**
  * @brief  Write status register 1 and 2
  * @param  StaReg1: The value write status register 1
  *         StaReg2: The value write status register 2
  * @note   register 1
  *         S7    S6   S5  S4   S3   S2   S1   S0
  *         SRP0  SEC  TB  BP2  BP1  BP0  WEL  WIP
  *         register 2
  *         S15   S14   S13  S12   S11   S10   S9   S8
  *         SUS   CMP   LB3  LB2   LB1   LB0   QE   SRP1 
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_WriteStaReg(uint8_t StaReg1, uint8_t StaReg2)
{
  int32_t retval;
  uint8_t wBuffer[3];
  uint32_t Tickstart;

  retval = FlashMem_WriteEnable();
  if (retval)    return retval;

  wBuffer[0] = FM25Q_Volatile_SR_WriteEnable;
  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(wBuffer, NULL, 1, 2);
  FlashMem_SPI_SetCSN(1);
  if (retval)    return retval;

  wBuffer[0] = FM25Q_WriteStatusReg;
  wBuffer[1] = StaReg1;
  wBuffer[2] = StaReg2;
  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(wBuffer, NULL, 3, 2);
  FlashMem_SPI_SetCSN(1);
  if (retval)    return retval;  

  Tickstart = System_GetTick();
  return FlashMem_WaitForIdle(Tickstart, 2);
}

/**
  * @brief  Sector erase(4K-bytes)
  * @param  addr: The address of specified sector to the erased state of all 1s
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_SectorErase_4KB(uint32_t addr)
{
  int32_t retval;
  uint8_t wBuffer[4];
  uint32_t Tickstart;

  retval = FlashMem_WriteEnable();
  if (retval)    return retval;

  wBuffer[0] = FM25Q_SectorErase_4KB;
  wBuffer[1] = (uint8_t)(addr>>16);
  wBuffer[2] = (uint8_t)(addr>>8); 
  wBuffer[3] = (uint8_t)(addr);
  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(wBuffer, NULL, 4, 2);
  FlashMem_SPI_SetCSN(1);
  if (retval)    return retval;

  Tickstart = System_GetTick();
  return FlashMem_WaitForIdle(Tickstart, 300);
}

/**
  * @brief  Block erase(32K-bytes)
  * @param  addr: The address of specified block to the erased state of all 1s
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_BlockErase_32KB(uint32_t addr)
{
  int32_t retval;
  uint8_t wBuffer[4];
  uint32_t Tickstart;

  retval = FlashMem_WriteEnable();
  if (retval)    return retval;

  wBuffer[0] = FM25Q_BlockErase_32KB;
  wBuffer[1] = (uint8_t)(addr>>16);
  wBuffer[2] = (uint8_t)(addr>>8); 
  wBuffer[3] = (uint8_t)(addr);
  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(wBuffer, NULL, 4, 2);
  FlashMem_SPI_SetCSN(1);
  if (retval)    return retval;

  Tickstart = System_GetTick();
  return FlashMem_WaitForIdle(Tickstart, 1800);
}

/**
  * @brief  Block erase(64K-bytes)
  * @param  addr: The address of specified block to the erased state of all 1s
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_BlockErase_64KB(uint32_t addr)
{
  int32_t retval;
  uint8_t wBuffer[4];
  uint32_t Tickstart;

  retval = FlashMem_WriteEnable();
  if (retval)    return retval;

  wBuffer[0] = FM25Q_BlockErase_64KB;
  wBuffer[1] = (uint8_t)(addr>>16);
  wBuffer[2] = (uint8_t)(addr>>8); 
  wBuffer[3] = (uint8_t)(addr);
  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(wBuffer, NULL, 4, 2);
  FlashMem_SPI_SetCSN(1);
  if (retval)    return retval;

  Tickstart = System_GetTick();
  return FlashMem_WaitForIdle(Tickstart, 2000);
}

/**
  * @brief  Chip erase
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_ChipErase(void)
{
  int32_t retval;
  uint8_t wBuffer;
  uint32_t Tickstart;

  retval = FlashMem_WriteEnable();
  if (retval)    return retval;

  wBuffer = FM25Q_ChipErase;
  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(&wBuffer, NULL, 1, 2);
  FlashMem_SPI_SetCSN(1);
  if (retval)    return retval;

  Tickstart = System_GetTick();
  return FlashMem_WaitForIdle(Tickstart, 128000);
}

/**
  * @brief  Read
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_Read(uint8_t *data, uint32_t addr, uint16_t num, uint32_t Timeout)
{
  int32_t retval;
  uint8_t wBuffer[4];
  
  wBuffer[0] = FM25Q_ReadData;
  wBuffer[1] = (uint8_t)(addr>>16);
  wBuffer[2] = (uint8_t)(addr>>8); 
  wBuffer[3] = (uint8_t)(addr);

  FlashMem_SPI_SetCSN(0);

  retval = FlashMem_SPI_Transfer(wBuffer, NULL, 4, 2);
  if (retval)
  {    
    FlashMem_SPI_SetCSN(1); 
    return retval;
  }

  retval = FlashMem_SPI_Transfer(NULL, data, num, Timeout);
  FlashMem_SPI_SetCSN(1);

  return retval;
}

/**
  * @brief  Page write
  * @note   This function allows from one byte to 256 bytes (a page) of data to be
  *         programmed at previously erased (FFh) memory locations
  * @retval ARM_DRIVER_OK or Error code(<0)
  */
int32_t FlashMem_PageWrite(uint8_t *data, uint32_t addr, uint16_t num, uint32_t Timeout)
{
  int32_t retval;
  uint8_t wBuffer[4];
  uint32_t Tickstart;

  retval = FlashMem_WriteEnable();
  if (retval)    return retval;

  wBuffer[0] = FM25Q_PageProgram;
  wBuffer[1] = (uint8_t)(addr>>16);
  wBuffer[2] = (uint8_t)(addr>>8); 
  wBuffer[3] = (uint8_t)(addr);

  FlashMem_SPI_SetCSN(0);
  retval = FlashMem_SPI_Transfer(wBuffer, NULL, 4, 2);
  if (retval)
  {    
    FlashMem_SPI_SetCSN(1); 
    return retval;
  }

  retval = FlashMem_SPI_Transfer(data, NULL, num, 5);
  FlashMem_SPI_SetCSN(1);

  if (retval)    return retval;

  Tickstart = System_GetTick();
  return FlashMem_WaitForIdle(Tickstart, Timeout);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  Error_Handler
  */
void Error_Handler(void)
{
  printf("Errors ocuur!!!\r\n");
  while (1);
}

uint8_t rData[1024];
uint8_t wData[1024];

/**
  * @brief  This is a flash memory device test program
  */
void FlashMemory_Test(void)
{
  int32_t retval;
  uint32_t i, j;
  __IO uint8_t err;
  uint32_t Start_Addr;

  /* SPI clock is 6553600 */
  FlashMem_SPI_Init();

  for (i=0; i<1024; i++)
    wData[i] = (uint8_t)(0x33);

  /*- Sector Erase ------------------------------------------------------------------------------------------*/
  Start_Addr = 5*4096;
  retval = FlashMem_SectorErase_4KB(Start_Addr);
  if (retval)    Error_Handler();

  err = 0;
  for (i=0; i<4; i++) 
  {
    retval = FlashMem_Read(rData, 1024*i+Start_Addr, 1024, 15);
    if (retval)    Error_Handler();

    for (j=0; j<1024; j++)
    {
      if (rData[i] != 0xFF)
        err = 1;
    }  
  }
  if (err)    printf("FlashMem_SectorErase_4KB error!\r\n");
  else        printf("FlashMem_SectorErase_4KB OK!\r\n");

  /*- Page write ------------------------------------------------------------------------------------------*/
  err = 0;
  retval = FlashMem_PageWrite(wData, Start_Addr, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData+256, Start_Addr+256, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData+256*2, Start_Addr+256*2, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData+256*3, Start_Addr+256*3, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_Read(rData, Start_Addr, 1024, 10);
  if (retval)    Error_Handler();

  for (i=0; i<1024; i++)
  {
    if (rData[i] != wData[i])
      err = 1;
  }
  if (err)    printf("FlashMem_PageWrite error!\r\n");
  else        printf("FlashMem_PageWrite OK!\r\n");

  /*- Sector Erase ------------------------------------------------------------------------------------------*/
  retval = FlashMem_SectorErase_4KB(Start_Addr);
  if (retval)    Error_Handler();

  err = 0;
  for (i=0; i<4; i++) 
  {
    retval = FlashMem_Read(rData, 1024*i+Start_Addr, 1024, 15);
    if (retval)    Error_Handler();

    for (j=0; j<1024; j++)
    {
      if (rData[i] != 0xFF)
        err = 1;
    }  
  }
  if (err)    printf("FlashMem_SectorErase_4KB error!\r\n");
  else        printf("FlashMem_SectorErase_4KB OK!\r\n");

  /*- Block Erase 32KB ------------------------------------------------------------------------------------------*/
  Start_Addr = 55*32*1024;
  err = 0;
  retval = FlashMem_BlockErase_32KB(Start_Addr);
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData, Start_Addr, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData+256, Start_Addr+32*1024-256, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_Read(rData, Start_Addr, 256, 15);
  if (retval)    Error_Handler(); 

  retval = FlashMem_Read(rData+256, Start_Addr+32*1024-256, 256, 15);
  if (retval)    Error_Handler(); 

  for (i=0; i<512; i++)
  {
    if (rData[i] != wData[i])
      err = 1;
  }

  if (err)    printf("FlashMem_BlockErase_32KB[0] error!\r\n");
  else        printf("FlashMem_BlockErase_32KB[0] OK!\r\n");

  retval = FlashMem_BlockErase_32KB(Start_Addr);
  if (retval)    Error_Handler();

  retval = FlashMem_Read(rData, Start_Addr, 256, 15);
  if (retval)    Error_Handler(); 

  retval = FlashMem_Read(rData+256, Start_Addr+32*1024-256, 256, 15);
  if (retval)    Error_Handler(); 

  for (i=0; i<512; i++)
  {
    if (rData[i] != 0xFF)
      err = 1;
  }

  if (err)    printf("FlashMem_BlockErase_32KB[1] error!\r\n");
  else        printf("FlashMem_BlockErase_32KB[1] OK!\r\n");

  /*- Block Erase 64KB ------------------------------------------------------------------------------------------*/
  Start_Addr = 13*64*1024;
  err = 0;
  retval = FlashMem_BlockErase_64KB(Start_Addr);
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData, Start_Addr, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData+256, Start_Addr+64*1024-256, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_Read(rData, Start_Addr, 256, 10);
  if (retval)    Error_Handler(); 

  retval = FlashMem_Read(rData+256, Start_Addr+64*1024-256, 256, 15);
  if (retval)    Error_Handler(); 

  for (i=0; i<512; i++)
  {
    if (rData[i] != wData[i])
      err = 1;
  }

  if (err)    printf("FlashMem_BlockErase_64KB[0] error!\r\n");
  else        printf("FlashMem_BlockErase_64KB[0] OK!\r\n");

  retval = FlashMem_BlockErase_64KB(Start_Addr);
  if (retval)    Error_Handler();

  retval = FlashMem_Read(rData, Start_Addr, 256, 15);
  if (retval)    Error_Handler(); 

  retval = FlashMem_Read(rData+256, Start_Addr+64*1024-256, 256, 15);
  if (retval)    Error_Handler(); 

  for (i=0; i<512; i++)
  {
    if (rData[i] != 0xFF)
      err = 1;
  }

  if (err)    printf("FlashMem_BlockErase_64KB[1] error!\r\n");
  else        printf("FlashMem_BlockErase_64KB[1] OK!\r\n");

  /*- Chip Erase ------------------------------------------------------------------------------------------*/ 
  err = 0;
  retval = FlashMem_ChipErase();
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData, Start_Addr, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_PageWrite(wData+256, Start_Addr+4*1024*1024-256, 256, 15);
  if (retval)    Error_Handler();

  retval = FlashMem_Read(rData, Start_Addr, 256, 15);
  if (retval)    Error_Handler(); 

  retval = FlashMem_Read(rData+256, Start_Addr+4*1024*1024-256, 256, 15);
  if (retval)    Error_Handler(); 

  for (i=0; i<512; i++)
  {
    if (rData[i] != wData[i])
      err = 1;
  }

  if (err)    printf("FlashMem_ChipErase[0] error!\r\n");
  else        printf("FlashMem_ChipErase[0] OK!\r\n");


  retval = FlashMem_ChipErase();
  if (retval)    Error_Handler();

  retval = FlashMem_Read(rData, Start_Addr, 256, 15);
  if (retval)    Error_Handler(); 

  retval = FlashMem_Read(rData+256, Start_Addr+4*1024*1024-256, 256, 15);
  if (retval)    Error_Handler(); 

  for (i=0; i<512; i++)
  {
    if (rData[i] != 0xFF)
      err = 1;
  }

  if (err)    printf("FlashMem_ChipErase[1] error!\r\n");
  else        printf("FlashMem_ChipErase[1] OK!\r\n");


  FlashMem_SPI_DeInit();
  printf("============================ Flash memory device test end! ============================\r\n");
}
