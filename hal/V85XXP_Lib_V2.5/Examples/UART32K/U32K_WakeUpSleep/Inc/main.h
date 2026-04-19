/**
  * @file    main.h
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program head.
******************************************************************************/

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "target.h"
#include "v_stdio.h"
#include <stdio.h>

#define Buffer_MaxSize (64)
   
extern __IO uint32_t Receive_Done;
extern __IO uint32_t Receive_Cnt; /* Increased by 1 when receive a byte data */
extern uint8_t Receive_Buffer[Buffer_MaxSize];

#ifdef __cplusplus
}
#endif     

#endif /* __MAIN_H */

/*********************************** END OF FILE ******************************/
