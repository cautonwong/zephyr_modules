/**
  ******************************************************************************
  * @file    misc.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   MISC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __MISC_H
#define __MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 1 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 0 bit  for subpriority */



#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_3))
                                       
void NVIC_PriorityGroupConfig(uint32_t PriorityGroup);
#endif

#ifdef __cplusplus
}
#endif
     
#endif  /* __MISC_H */

/*********************************** END OF FILE ******************************/
