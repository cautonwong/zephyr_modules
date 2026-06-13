/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * V32F20X TF-M Target Configuration
 */

#ifndef __V32F20X_TARGET_CFG_H__
#define __V32F20X_TARGET_CFG_H__

#include "Driver_USART.h"
#include "tfm_plat_defs.h"

/* Stdio UART driver instance */
#define TFM_DRIVER_STDIO    Driver_USART0

/* Platform init function declarations */
enum tfm_plat_err_t enable_fault_handlers(void);
enum tfm_plat_err_t system_reset_cfg(void);
enum tfm_plat_err_t nvic_interrupt_target_state_cfg(void);
enum tfm_plat_err_t nvic_interrupt_enable(void);

#endif /* __V32F20X_TARGET_CFG_H__ */
