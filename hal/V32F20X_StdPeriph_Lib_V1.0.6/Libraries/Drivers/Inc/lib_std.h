/**
  ******************************************************************************
  * @file    lib_std.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   STD module driver.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_STD_H
#define __LIB_STD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

#define STD_MAX_DELAY        (0xFFFFFFFFUL)

/* Exported functions --------------------------------------------------------*/ 

STD_StatusType STD_Init(uint32_t SysClock);
void           STD_lowInit(void);

STD_StatusType STD_InitTick(uint32_t SysClock, uint32_t TickPriority);
void           STD_DeInitTick(void);
void           STD_IncTick(void);
uint32_t       STD_GetTick(void);
void           STD_Delay(uint32_t Delay);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_STD_H */

/*********************************** END OF FILE ******************************/
