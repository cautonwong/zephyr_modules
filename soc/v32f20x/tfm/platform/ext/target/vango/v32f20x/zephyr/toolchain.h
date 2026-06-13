/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 *
 * Minimal Zephyr toolchain compatibility shim for TF-M builds.
 * The V32F20X HAL uses Zephyr-style __IOM/__IM/__OM macros
 * which map directly to CMSIS __IO/__I/__O conventions.
 */
#ifndef ZEPHYR_TOOLCHAIN_TFM_SHIM_H
#define ZEPHYR_TOOLCHAIN_TFM_SHIM_H

#ifndef __IOM
#define __IOM  volatile            /* Read-write (same as CMSIS __IO) */
#endif
#ifndef __IM
#define __IM   volatile const      /* Read-only  (same as CMSIS __I)  */
#endif
#ifndef __OM
#define __OM   volatile            /* Write-only (same as CMSIS __O)  */
#endif

#endif /* ZEPHYR_TOOLCHAIN_TFM_SHIM_H */
