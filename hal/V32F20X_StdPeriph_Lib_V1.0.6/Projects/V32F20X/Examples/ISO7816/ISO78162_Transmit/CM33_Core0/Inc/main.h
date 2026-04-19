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
#include <stdio.h>
#include <string.h>

void Error_Handler(void);

#define     SAMPLE_IS07816      ISO78162

extern unsigned char g_recieve_data[256];
extern unsigned int g_recieve_count;
extern unsigned char g_send_data[256];
extern unsigned int g_send_count;

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/*********************************** END OF FILE ******************************/
