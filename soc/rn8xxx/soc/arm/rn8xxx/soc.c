/*
 * Copyright (c) 2024 Your Organization
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include "soc.h"

/* Helper function for system init */
static int rn8xxx_init(void)
{
    /* Initialize system clock, etc. */
    /* This is a placeholder. Real code would call HAL init. */
    return 0;
}

SYS_INIT(rn8xxx_init, PRE_KERNEL_1, 0);
