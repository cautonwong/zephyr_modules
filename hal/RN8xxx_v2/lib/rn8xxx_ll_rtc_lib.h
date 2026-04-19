/******************************************************************************
 * @file     rn8xxx_v2_rtc_lib.h
 * @brief    rtc driver header
 * @author   Renergy Technology
 *
 * @note
 * Copyright (C) , Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#ifndef RN8XXX_LL_RTC_LIB_H_
#define RN8XXX_LL_RTC_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rn8xxx_ll_devices.h"

/**********************************************************
  api return
**********************************************************/
typedef enum
{
    RTC_PASS = 0,
    RTC_FAIL = 1,
} eRtcRet_TypeDef;

/**
 * @brief LL_RTC_ReadDota
 *
 * @param
 *    none
 * @return
 *    unsigned short dota: dota value of RTC
 *
 */
unsigned short  LL_RTC_ReadDota(void);
#define RtcReadDota LL_RTC_ReadDota

/**
 * @brief LL_RTC_WriteDota
 *
 * @param
 *    in unsigned short dota: dota value of RTC
 * @return
 *    NVM_PASS: rtc-dota write pass
 *    NVM_FAIL: rtc-dota write fail
 *
 */
eRtcRet_TypeDef LL_RTC_WriteDota(unsigned short dota);
#define RtcWriteDota LL_RTC_WriteDota

#ifdef __cplusplus
}
#endif

#endif
/* r2041 */
