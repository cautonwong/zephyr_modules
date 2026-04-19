/**
  ******************************************************************************
  * @file   hyperbus_psram.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Read and Write Hyperbus PSRAM in XIP mode
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __HYPERBUS_PSRAM_H
#define __HYPERBUS_PSRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
#include "board.h"

/* use OSPI1 as Hyperbus*/
#define TEST_OSPI  OSPI1

#define HyperbusReadInLinearBurst   0xA0000000
#define HyperbusWriteInLinearBurst  0x20000000

#define OSPI0_PSRAM_StartAddr   0x60000000
#define OSPI1_PSRAM_StartAddr   0x64000000

void HyperbusPSRAM_InitHyperbus(OSPI_Type* OSPIx);
void HyperbusPSRAM_HardWareResetPSRAM(void);
void HyperbusPSRAM_WritePSRAM(OSPI_Type* OSPIx, uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
void HyperbusPSRAM_ReadPSRAM(OSPI_Type* OSPIx, uint32_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*#ifndef __HYPERBUS_PSRAM_H*/

/*********************************** END OF FILE ******************************/

