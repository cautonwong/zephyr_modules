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
#include "common.h"

void Delay_us(volatile uint32_t n);
void Delay_ms(volatile uint32_t n);


#ifdef __cplusplus
}
#endif     

#endif /* __MAIN_H */

/*********************************** END OF FILE ******************************/
