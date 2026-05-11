/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_MODULES_SOC_V32F20X_SOC_H_
#define ZEPHYR_MODULES_SOC_V32F20X_SOC_H_

#include <v32f20x.h>

/* 
 * CRITICAL FIX: Bridge naming discrepancy between Vango CMSIS (CM0) and Zephyr Kernel.
 * Vango (Standard CM0) uses SCB->SHP[2], while Zephyr's scb.c assumes SCB->SHPR.
 */
#if defined(CONFIG_CPU_CORTEX_M0)
#ifndef SHPR
#define SHPR SHP
#endif
#endif

#endif /* ZEPHYR_MODULES_SOC_V32F20X_SOC_H_ */
