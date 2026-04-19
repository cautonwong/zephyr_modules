/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_reset

#include <zephyr/drivers/reset.h>
#include <zephyr/kernel.h>
#include <soc.h>
#include <lib_syscfg.h>

struct reset_v32f20x_config {
    uint32_t base;
};

static int reset_v32f20x_line_assert(const struct device *dev, uint32_t id)
{
    uint32_t reset_bit;

    if (id < 32) {
#if defined(V32F20XXX_CM33_CORE0)
        reset_bit = 1UL << id;
        SYSCFG0_Periph0Reset(reset_bit);
        return 0;
#else
        return -ENOTSUP;
#endif
    } else if (id < 64) {
#if defined(V32F20XXX_CM33_CORE0)
        reset_bit = 1UL << (id - 32);
        SYSCFG0_Periph1Reset(reset_bit);
        return 0;
#else
        return -ENOTSUP;
#endif
    } else if (id < 96) {
        reset_bit = 1UL << (id - 64);
        SYSCFG1_PeriphReset(reset_bit);
        return 0;
    }

    return -EINVAL;
}

static int reset_v32f20x_line_deassert(const struct device *dev, uint32_t id)
{
    /* V32F20X reset is likely self-clearing or handled by the same function */
    return 0;
}

static int reset_v32f20x_line_toggle(const struct device *dev, uint32_t id)
{
    return reset_v32f20x_line_assert(dev, id);
}

static const struct reset_driver_api reset_v32f20x_api = {
    .status = NULL,
    .line_assert = reset_v32f20x_line_assert,
    .line_deassert = reset_v32f20x_line_deassert,
    .line_toggle = reset_v32f20x_line_toggle,
};

static int reset_v32f20x_init(const struct device *dev)
{
    return 0;
}

DEVICE_DT_INST_DEFINE(0, reset_v32f20x_init, NULL,
                     NULL, NULL,
                     PRE_KERNEL_1, CONFIG_RESET_INIT_PRIORITY,
                     &reset_v32f20x_api);
