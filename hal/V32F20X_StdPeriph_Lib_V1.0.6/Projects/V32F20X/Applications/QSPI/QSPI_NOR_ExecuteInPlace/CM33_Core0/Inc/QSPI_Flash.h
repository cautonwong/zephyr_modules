/**
  ******************************************************************************
  * @file    QSPI_Flash.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-12
  * @brief   Header file for QSPI flash operation
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __QSPI_FlASH_H
#define __QSPI_FlASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
#include "board.h"

/* Exported constants --------------------------------------------------------*/
#define FLASH_OSPIX          OSPI0
#define W25Q256FV_FLASHID    ((uint32_t)0xEF6019)
#define W25Q256FQ_FLASHID    ((uint32_t)0xEF4019)

#define FLASH_ERASE_ADDR         0x0000
#define FLASH_BASE_ADDR          0x60000000
#define FLASH_WRITE_START_ADDR   0x60000000

#define FLASH_ERASE_ADDR    0x0000
#define FLASH_DUMMY_BYTE    (0xA5)
#define FLASH_PAGESIZE      (0x100)
#define FLASH_SECTORSIZE    (0x1000)
#define FLASH_BLOCKSIZE     (0x10000)

#define W25QX_SR_BUSY_MASK   0x00000001
   
/* winbond FLASH commands */
#define W25QX_CMD_RESET_ENABLE      0x66
#define W25QX_CMD_RESET             0x99
#define W25QX_CMD_READ_STATUS_REG   0x05
#define W25QX_CMD_ENTER_QPI_MODE    0x38
#define W25QX_CMD_EXIT_QPI_MODE     0xFF
#define W25QX_CMD_READ_FLASH_ID     0x9F
#define W25QX_CMD_SECTOR_ERASE      0x20
#define W25QX_CMD_BLOCK_ERASE       0xD8
#define W25QX_CMD_CHIP_ERASE        0xC7
#define W25QX_CMD_WRITE_ENABLE      0x06
#define W25QX_CMD_WRITE_DISABLE     0x04
#define W25QX_CMD_FAST_READ         0x0B
#define W25QX_CMD_SET_READ_PARA     0xC0
#define W25QX_CMD_PAGE_PROGRAM      0x02


/* Exported functions prototypes ---------------------------------------------*/
void QSPI_Flash_Init(OSPI_Type *OSPIx);
void QSPI_Flash_DeInit(OSPI_Type *OSPIx);
void QSPI_Flash_SoftwareReset(OSPI_Type *OSPIx);
void QSPI_Flash_QPIModeEnter(OSPI_Type *OSPIx);
void QSPI_Flash_QPIModeExit(OSPI_Type *OSPIx);
uint32_t QSPI_Flash_QPIMode_IDRead(OSPI_Type *OSPIx);
void QSPI_Flash_QPIMode_SectorErase(OSPI_Type *OSPIx, uint32_t SectorAddr);
uint32_t QSPI_Flash_QPIMode_BufferWriteWithDMA(OSPI_Type *OSPIx,uint32_t SectorAddr, uint8_t *Buff, uint32_t BuffLen);
uint32_t QSPI_Flash_QPIMode_BufferReadWithDMA(OSPI_Type *OSPIx, uint32_t ReadAddr, uint8_t *Buff, uint32_t BuffLen);
void QSPI_XIP_ReadConfig(OSPI_Type *OSPIx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __I2C_EE_H */

/*********************************** END OF FILE ******************************/
