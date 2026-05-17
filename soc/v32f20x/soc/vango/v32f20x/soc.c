/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/pm/pm.h>
#include <soc.h>

void pm_state_set(enum pm_state state, uint8_t substate_id)
{
    ARG_UNUSED(substate_id);

    switch (state) {
    case PM_STATE_SUSPEND_TO_RAM:
        /* Vango V32 STOP mode logic */
        __WFI();
        break;
    case PM_STATE_SOFT_OFF:
        /* Vango V32 STANDBY mode logic */
        __WFI();
        break;
    default:
        break;
    }
}

void pm_state_exit_post_ops(enum pm_state state, uint8_t substate_id)
{
    ARG_UNUSED(state);
    ARG_UNUSED(substate_id);

    /* Re-enable interrupts and restore clocks if necessary */
    __enable_irq();
}

static int v32f20x_soc_init(void)
{
    return 0;
}

SYS_INIT(v32f20x_soc_init, PRE_KERNEL_1, 0);
