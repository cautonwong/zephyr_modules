/**
  ******************************************************************************
  * @file   OSPI_Flash.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-12
  * @brief   1. Read and write Flash
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __OSPI_FlASH_H
#define __OSPI_FlASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
#include "board.h"

/* Private macro -------------------------------------------------------------*/
#define Flash_OSPIx                      OSPI0
#define FlashStartAddr                   0x60000000UL


#define Flash_IO_Mode_SPI               (0X0001UL)
#define Flash_IO_Mode_OSPI_STR          (0X0002UL)
#define Flash_IO_Mode_OSPI_DDR          (0X0003UL)

#define FLASH_PAGESIZE                  (256)
#define GD25X_DummyByte                 (0XFF)
#define GD25X_FlashID0                   (0xC8481AFF)
#define GD25X_FlashID1                   (0xC8481AC8)
#define GD25X_SR_WIP_MASK               (0x01)
#define GD25X_IOModeOctalWithDQS        (0xB7)
#define GD25X_IOModeSPIWithDQS          (0xFF)

/* GD25X512 instructions list */
#define GD25X_CMD_ResetEnable           (0x66)
#define GD25X_CMD_Reset                 (0x99)
#define GD25X_CMD_ReadStatusReg         (0x05)
#define GD25X_CMD_WriteEnable           (0x06)
#define GD25X_CMD_WriteConfigReg        (0x81)
#define GD25X_CMD_ReadConfigReg         (0x85)
#define GD25X_CMD_ReadFlashID           (0x9F)
#define GD25X_CMD_SectorErase           (0X20)
#define GD25X_CMD_PageProgram           (0X82)
#define GD25X_CMD_OctalOutputFastRead   (0x8b) 


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void OSPI_Flash_DeInit(OSPI_Type *OSPIx);
void OSPI_Flash_Init(OSPI_Type* SSIx);
void OSPI_Flash_HardwareReset(void);
void OSPI_Flash_SoftwareReset(OSPI_Type* OSPIx);
void OSPI_Flash_EnterOPIMode(OSPI_Type *OSPIx);
void OSPI_Flash_ExitOPIMode(OSPI_Type *OSPIx);
uint32_t OSPI_Flash_OPIModeReadID(OSPI_Type *OSPIx);
void OSPI_Flash_OPIModeSectorErase(OSPI_Type *OSPIx, uint32_t SectorAddr);
uint32_t OSPI_Flash_BufferWrite(OSPI_Type *OSPIx, const uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
void OSPI_Flash_BufferRead(OSPI_Type *OSPIx, uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void OSPI_XIP_ReadConfig(OSPI_Type *OSPIx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*#ifndef __OSPI_FlASH_H*/

/*********************************** END OF FILE ******************************/
