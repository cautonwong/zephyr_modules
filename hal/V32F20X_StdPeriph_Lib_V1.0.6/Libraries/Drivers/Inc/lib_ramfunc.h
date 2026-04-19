/**
  ******************************************************************************
  * @file    lib_ramfunc.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   RAM function library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_RAMFUNC_H
#define __LIB_RAMFUNC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

__RAM_FUNC void FLASH_PowerCmd(FLASH_Type *FLASHx, FunctionalState NewState);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_RAMFUNC_H */

/*********************************** END OF FILE ******************************/
