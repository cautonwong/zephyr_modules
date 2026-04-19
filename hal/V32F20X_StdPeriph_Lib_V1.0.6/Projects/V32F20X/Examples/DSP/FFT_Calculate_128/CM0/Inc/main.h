/**
  * @file    main.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program head.
******************************************************************************/

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "target.h"
#include "target_isr.h"
#include "board.h"

#define FFTExchAddr  0x2100B000
#define DSPPowerAddr  0x2100C000
#define RxBuf  0x2100A000
#define RXBufLength 4096
#define RxBuf1  0x21008000
#define RXBuf1Length 4096

//uint8_t DSPFlag = 0;
//uint32_t DMA1flag_framend = 0,DMA1flag_framend1 = 0,T2Fflag = 0;

void Error_Handler(void);

#ifdef __cplusplus
}
#endif     

#endif /* __MAIN_H */

/*********************************** END OF FILE ******************************/
