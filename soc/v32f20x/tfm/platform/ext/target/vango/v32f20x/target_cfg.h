/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Target Configuration for Vango V32F20x TF-M Platform
 */

#ifndef __TARGET_CFG_H__
#define __TARGET_CFG_H__

#include "tfm_plat_defs.h"

/* Memory regions structure (NS code/data boundaries) */
struct memory_region_limits {
    uint32_t non_secure_code_start;
    uint32_t non_secure_code_limit;
    uint32_t non_secure_data_start;
    uint32_t non_secure_data_limit;
};

extern struct memory_region_limits memory_regions;

/* Platform initialization functions */
enum tfm_plat_err_t enable_fault_handlers(void);
enum tfm_plat_err_t system_reset_cfg(void);
enum tfm_plat_err_t nvic_interrupt_target_state_cfg(void);
enum tfm_plat_err_t nvic_interrupt_enable(void);

#endif /* __TARGET_CFG_H__ */
