/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SOC_H_
#define _SOC_H_

#include <zephyr/sys/util.h>

/* Chip type definition for HAL */
#ifndef V32F209XX
#define V32F209XX
#endif

/* Core type definition for HAL */
#if defined(CONFIG_SOC_V32F20X_CPU0)
  #ifndef V32F20XXX_CM0_CORE
  #define V32F20XXX_CM0_CORE
  #endif
#elif defined(CONFIG_SOC_V32F20X_CPU1)
  #ifndef V32F20XXX_CM33_CORE0
  #define V32F20XXX_CM33_CORE0
  #endif
#endif

/* Avoid conflict with Zephyr's IS_BIT_SET */
#ifdef IS_BIT_SET
#undef IS_BIT_SET
#endif

/* Include target header from HAL */
#include <target.h>

/* 
 * Professional Polish: provide missing definitions for CM0 in HAL target.h 
 * The HAL's target.h only defines these for CM33 cores, but common driver code
 * in lib_syscfg0.c and others expect them to be available globally.
 */
#if defined(V32F20XXX_CM0_CORE)
  #ifndef SYSCFG0
    #define SYSCFG0 ((SYSCFG0_Type*) SYSCFG0_BASE)
  #endif
#endif

/* Ensure Zephyr's IS_BIT_SET version which is standard for drivers */
#undef IS_BIT_SET
#define IS_BIT_SET(value, bit) ((((value) >> (bit)) & (0x1)) != 0)

/* Define generic macros for drivers */
#ifndef BIT
#define BIT(n)  (1UL << (n))
#endif

/* PINMUX macros */
/* Pinctrl settings moved to dt-bindings */
#include <zephyr/dt-bindings/pinctrl/vango-v32f20x-pinctrl.h>

#endif /* _SOC_H_ */
