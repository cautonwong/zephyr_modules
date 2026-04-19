/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/init.h>
#include <soc.h>
#include <zephyr/arch/cpu.h>

#include <lib_clk.h>

void z_arm_platform_init(void)
{
    /* Call HAL SystemInit to configure core clocks and basic peripherals */
    SystemInit();
}

/**
 * @brief Perform basic hardware initialization at boot.
 */
static int v32f20x_init(void)
{
    /* Additional SoC specific initialization */
    
    return 0;
}

SYS_INIT(v32f20x_init, PRE_KERNEL_1, 0);
