/**
  ******************************************************************************
  * @file    FM25Q32.h
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
  
#ifndef __FM25Q32
#define __FM25Q32

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

extern __IO uint32_t nTicks;

// SPIx be used
#define SPI_Flash SPI3

#define CSN_GPIO     GPIOD
#define CSN_GPIO_DAT GPIO_D
#define CSN_Pin      GPIO_Pin_4
#define CSN_PinNum   4

//FM25Q command
#define FM25Q_WriteEnable                 0x06
#define FM25Q_WriteDisable                0x04
#define FM25Q_ReadStatusReg_1             0x05
#define FM25Q_ReadStatusReg_2             0x35
#define FM25Q_Volatile_SR_WriteEnable     0x50
#define FM25Q_WriteStatusReg              0x01
#define FM25Q_SectorErase_4KB             0x20
#define FM25Q_BlockErase_32KB             0x52
#define FM25Q_BlockErase_64KB             0xD8
#define FM25Q_ChipErase                   0xC7
#define FM25Q_ReadData                    0x03
#define FM25Q_PageProgram                 0x02 

void FlashMemory_Test(void);


uint32_t System_GetTick(void);
void FlashMem_SPI_Init(void);
void FlashMem_SPI_DeInit(void);
void FlashMem_SPI_SetCSN(uint8_t level);
int32_t FlashMem_SPI_Transfer(uint8_t *w_data, uint8_t *r_data, uint32_t len, uint32_t Timeout);

int32_t FlashMem_WriteEnable(void);
int32_t FlashMem_WriteDisable(void);

int32_t FlashMem_WaitForIdle(uint32_t Tickstart, uint32_t Timeout);

int32_t FlashMem_ReadStaReg_1(uint8_t *data);
int32_t FlashMem_ReadStaReg_2(uint8_t *data);
int32_t FlashMem_WriteStaReg(uint8_t StaReg1, uint8_t StaReg2);

int32_t FlashMem_SectorErase_4KB(uint32_t addr);
int32_t FlashMem_BlockErase_32KB(uint32_t addr);
int32_t FlashMem_BlockErase_64KB(uint32_t addr);
int32_t FlashMem_ChipErase(void);

int32_t FlashMem_Read(uint8_t *data, uint32_t addr, uint16_t num, uint32_t Timeout);
int32_t FlashMem_PageWrite(uint8_t *data, uint32_t addr, uint16_t num, uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __FM25Q32 */
