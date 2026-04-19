/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_clock

#include <zephyr/drivers/clock_control.h>
#include <zephyr/dt-bindings/clock/vango_v32f20x_clock.h>
#include <soc.h>
#include <lib_clk.h>

struct v32f20x_clock_config {
	/* No config needed for now */
};

struct v32f20x_clock_data {
	/* No dynamic state needed for now */
};

static int v32f20x_clock_on(const struct device *dev,
			   clock_control_subsys_t subsys)
{
	uint32_t clk_id = (uint32_t)subsys;

	/* 
	 * Vango V32F20X maps clocks through SYSCFG1->CLK_EN0/1
	 * Bit 0-31: EN0, Bit 32-63: EN1
	 */
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
	CLK_ClocksType clocks;

	CLK_GetClocksFreq(&clocks);

	/* 
	 * Assign rate based on peripheral bus mapping.
	 * Most peripherals in V32F20X are on PCLK1.
	 */
	if (clk_id >= 32 && clk_id <= 45) { /* FLEXCOMM 0-13 */
		*rate = clocks.PCLK1_Frequency;
	} else if (clk_id >= 100 && clk_id <= 105) { /* UART 14-19 */
		*rate = clocks.PCLK1_Frequency;
	} else {
		/* Default to HCLK for high speed peripherals like DMA */
		*rate = clocks.HCLK_Frequency;
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
