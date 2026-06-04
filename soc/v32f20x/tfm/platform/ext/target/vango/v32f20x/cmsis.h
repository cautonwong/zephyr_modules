/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 *
 * Unified CMSIS wrapper header for Vango V32F20x Platform Porting.
 */

#ifndef __VANGO_CMSIS_H__
#define __VANGO_CMSIS_H__

/* Ensure chip type is defined for target.h compilation */
#if !defined(V32F209XX) && !defined(V32F207XX)
#define V32F209XX
#endif

#if !defined(V32F20XXX_CM33_CORE0) && !defined(V32F20XXX_CM33_CORE1) && !defined(V32F20XXX_CM0_CORE)
#define V32F20XXX_CM33_CORE0
#endif

#include "v32f20x.h"

#endif /* __VANGO_CMSIS_H__ */
