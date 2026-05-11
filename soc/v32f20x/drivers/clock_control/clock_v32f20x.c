/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_clock

#include <zephyr/drivers/clock_control.h>
#include <zephyr/dt-bindings/clock/vango_v32f20x_clock.h>
#include <soc.h>
#include <lib_clk.h>
#include <lib_syscfg.h>

struct v32f20x_clock_config {
};

struct v32f20x_clock_data {
};

static int v32f20x_clock_on(const struct device *dev,
			   clock_control_subsys_t subsys)
{
	uint32_t clk_id = (uint32_t)subsys;

	if (clk_id < 32) {
		SYSCFG1_Periph0ClockCmd(1UL << clk_id, ENABLE);
	} else {
		SYSCFG1_Periph1ClockCmd(1UL << (clk_id - 32), ENABLE);
	}

	return 0;
}

static int v32f20x_clock_off(const struct device *dev,
			    clock_control_subsys_t subsys)
{
	uint32_t clk_id = (uint32_t)subsys;

	if (clk_id < 32) {
		SYSCFG1_Periph0ClockCmd(1UL << clk_id, DISABLE);
	} else {
		SYSCFG1_Periph1ClockCmd(1UL << (clk_id - 32), DISABLE);
	}

	return 0;
}

static int v32f20x_clock_get_rate(const struct device *dev,
				 clock_control_subsys_t subsys,
				 uint32_t *rate)
{
	uint32_t clk_id = (uint32_t)subsys;

	if (clk_id >= 100 && clk_id <= 105) {
		*rate = CLK_GetPCLK1Freq();
	} else {
		*rate = CLK_GetPCLK1Freq();
	}

	return 0;
}

static const struct clock_control_driver_api v32f20x_clock_api = {
	.on = v32f20x_clock_on,
	.off = v32f20x_clock_off,
	.get_rate = v32f20x_clock_get_rate,
};

static int v32f20x_clock_init(const struct device *dev)
{
	ARG_UNUSED(dev);
	return 0;
}

DEVICE_DT_INST_DEFINE(0, v32f20x_clock_init, NULL,
		      NULL, NULL, PRE_KERNEL_1,
		      CONFIG_CLOCK_CONTROL_INIT_PRIORITY,
		      &v32f20x_clock_api);
