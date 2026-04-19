/**
  ******************************************************************************
  * @file    lib_mailbox.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Mailbox library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_MAILBOX_H
#define __LIB_MAILBOX_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @defgroup MB_Int Interrupt index
  * @{
  */
#define MB_INT_CM33_CORE0                      (0UL)
#define MB_INT_CM33_CORE1                      (1UL)
#define MB_INT_CM0_CORE                        (2UL)
#if defined (V32F20XXX_CM33_CORE0)
#define IS_MB_INT(INT) (((INT) == MB_INT_CM33_CORE1) ||\
                        ((INT) == MB_INT_CM0_CORE))
#endif /* V32F20XXX_CM33_CORE0 */
#if defined (V32F20XXX_CM33_CORE1)
#define IS_MB_INT(INT) (((INT) == MB_INT_CM33_CORE0) ||\
                        ((INT) == MB_INT_CM0_CORE))
#endif /* V32F20XXX_CM33_CORE1 */
#if defined (V32F20XXX_CM0_CORE)
#define IS_MB_INT(INT) (((INT) == MB_INT_CM33_CORE0) ||\
                        ((INT) == MB_INT_CM33_CORE1))
#endif /* V32F20XXX_CM0_CORE */

/* Exported functions --------------------------------------------------------*/ 

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

void     MB33_MutexInit(void);
void     MB33_SetMutex(void);
uint32_t MB33_GetMutex(void);

#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */

void     MB_SetInterrupt(uint32_t MB_Int);
void     MB_ClearInterrupt(uint32_t MB_Int);
ITStatus MB_GetInterrupt(uint32_t MB_Int);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_MAILBOX_H */

/*********************************** END OF FILE ******************************/
