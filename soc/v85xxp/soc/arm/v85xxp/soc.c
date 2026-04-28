/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/init.h>
#include <soc.h>
#include <lib_clk.h>

/* Initialize SoC-level clock system using professional HAL macros */
static int v85xxp_clock_init(void)
{
    /* Select RCOH as default clock source per hardware specification */
    MISC2->CLKSEL = MISC2_CLKSEL_CLKSEL_RCOH;

    return 0;
}

SYS_INIT(v85xxp_clock_init, PRE_KERNEL_1, 0);
