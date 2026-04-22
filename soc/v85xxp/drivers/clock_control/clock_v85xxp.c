/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_clock

#include <zephyr/drivers/clock_control.h>
#include <zephyr/dt-bindings/clock/v85xxp_clock.h>
#include <soc.h>
#include <lib_clk.h>

static int v85xxp_clock_on(const struct device *dev, clock_control_subsys_t subsys)
{
    uint32_t periph = (uint32_t)subsys;
    if (periph & 0x80000000) {
        CLK_APBPeriphralCmd(periph & 0x7FFFFFFF, ENABLE);
    } else {
        CLK_AHBPeriphralCmd(periph, ENABLE);
    }
    return 0;
}

static int v85xxp_clock_off(const struct device *dev, clock_control_subsys_t subsys)
{
    uint32_t periph = (uint32_t)subsys;
    if (periph & 0x80000000) {
        CLK_APBPeriphralCmd(periph & 0x7FFFFFFF, DISABLE);
    } else {
        CLK_AHBPeriphralCmd(periph, DISABLE);
    }
    return 0;
}

static const struct clock_control_driver_api v85xxp_clock_api = {
    .on = v85xxp_clock_on,
    .off = v85xxp_clock_off,
};

static int v85xxp_clock_init(const struct device *dev)
{
    return 0;
}

DEVICE_DT_INST_DEFINE(0, v85xxp_clock_init, NULL, NULL, NULL, PRE_KERNEL_1, 1, &v85xxp_clock_api);
