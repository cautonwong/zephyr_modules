/**
  * @file    main.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-04
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
#include "lib_dac.h"
#include "lib_timer.h"
#include "lib_dma.h"

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/*********************************** END OF FILE ******************************/
