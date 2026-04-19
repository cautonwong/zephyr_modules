/**
  * @file    SDIO.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   SDIO program head.
******************************************************************************/

#ifndef __SDIO_H
#define __SDIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "target.h"
#include "sdio_sdcard.h"
#include "ff.h"
#include "diskio.h"



#define Drv_SDIO0					0
#define Drv_SDIO1 				1

extern FATFS fs_sdio0,fs_sdio1;
extern FIL fnew,f1;

void SD_WriteDisk(void);
void SDIODelay_ms(uint32_t n);
#ifdef __cplusplus
}
#endif     

#endif /* __SRAM_H */

/*********************************** END OF FILE ******************************/
