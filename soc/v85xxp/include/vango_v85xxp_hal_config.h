/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_MODULES_SOC_V85XXP_HAL_CONFIG_H_
#define ZEPHYR_MODULES_SOC_V85XXP_HAL_CONFIG_H_

#include <target.h>
#include <lib_rtc.h>
#include <lib_clk.h>
#include <lib_LoadNVR.h>
#include <lib_cortex.h>
#include <lib_gpio.h>
#include <lib_ana.h>

/* Satisfy HAL's assertion macro requirements */
#define assert_parameters(expr) ((void)0)

#endif /* ZEPHYR_MODULES_SOC_V85XXP_HAL_CONFIG_H_ */
