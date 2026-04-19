/******************************************************************************
 * @file     rn8xxx_ll_sysoption.h
 * @brief    system option driver header
 * @author   Renergy Technology
 *
 * @note
 * Copyright (C) , Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#ifndef RN8XXX_LL_DEVICES_H_
#define RN8XXX_LL_DEVICES_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Notes: The chip type macro define will be defined in ll driver. If no ll driver,
 *  Please add chip type macro define here. The code size will increase significantly
 *  if there is no chip type macro define.
 */

// #define RN831x_RN861x_MCU_V2 

#if !defined(RN831x_RN861x_MCU_V1) &&\
    !defined(RN831x_RN861x_MCU_V2) &&\
    !defined(RN831x_RN861x_MCU_V3) &&\
    !defined(RN821x_RN721x_SOC_B)  &&\
    !defined(RN821x_RN721x_SOC_C)  &&\
    !defined(RN821x_RN721x_SOC_D)  &&\
    !defined(RN821x_RN721x_SOC_V2) &&\
    !defined(RN821x_RN721x_SOC_V3) &&\
    !defined(RN202x_RN7326_SOC_B)  &&\
    !defined(RN202x_RN7326_SOC_V2)
#define RN_CM0_PLATFORM
#endif


#ifdef __cplusplus
}
#endif

#endif
/* r1921 */
