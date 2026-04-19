/**
  ******************************************************************************
  * @file    lib_CodeRAM.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   Codes executed in SRAM.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_CODERAM_H
#define __LIB_CODERAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "target.h"   


/* Exported Functions ------------------------------------------------------- */
#ifndef __GNUC__
__RAM_FUNC void PMU_EnterIdle_FlashDSTB(void) __IN_RAMSECTION;
#endif
   
#ifdef __cplusplus
}
#endif

#endif /* __LIB_CODERAM_H */

/*********************************** END OF FILE ******************************/
