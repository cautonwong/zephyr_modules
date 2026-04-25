/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SOC_H_
#define _SOC_H_

#include <target.h>

/* 
 * Compatibility Bridge: Zephyr scb.c expects SHPR member in SCB_Type.
 * Cortex-M0 (ARMv6-M) standard CMSIS uses SHP[2] instead.
 */
#if defined(CONFIG_CPU_CORTEX_M0) && !defined(SHPR)
#define SHPR SHP
#endif

#define V85XXP_AHB_CLOCK_HZ 6553600U
#define V85XXP_PCLK_CLOCK_HZ 6553600U

#endif /* _SOC_H_ */
