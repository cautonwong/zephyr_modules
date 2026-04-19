/**
  ******************************************************************************
  * @file    system_target_cm33.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   system source file.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __SYSTEM_TARGET_CM33_CORE0_H
#define __SYSTEM_TARGET_CM33_CORE0_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include "target.h"

/* ########################### System Configuration ######################### */         

extern void SystemInit(void);
extern void SystemUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_TARGET_CM33_CORE0_H */

/*********************************** END OF FILE ******************************/
