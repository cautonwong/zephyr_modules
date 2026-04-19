/**
  * @file    main.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-05
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
#include "lib_u32k.h"
#include "lib_uart.h"
#include "lib_pmu.h"

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/*********************************** END OF FILE ******************************/
