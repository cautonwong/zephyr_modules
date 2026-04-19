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

extern unsigned char g_CIC_process_flag;
extern unsigned char g_CIC_Init_flag;

void Error_Handler(void);

extern void CIC_Integrate_Start(void);
extern void CIC_Comb_Start(void);
extern unsigned char check_CIC_Done_status(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/*********************************** END OF FILE ******************************/
