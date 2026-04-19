/**
  ******************************************************************************
  * @file    partition_target.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-10
  * @brief   CMSIS Device Header File for Initial Setup for Secure / Non-Secure 
  *          Zone.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __PARTITION_TARGET_H
#define __PARTITION_TARGET_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#if defined(V32F20XXX_CM33_CORE0)
  #include "partition_XXX.h"
//#elif defined()
  //#include ".h"
#else
  #error "Please select first the target V32F20XXX device used in your application (in target.h file)"
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PARTITION_TARGET_H */
