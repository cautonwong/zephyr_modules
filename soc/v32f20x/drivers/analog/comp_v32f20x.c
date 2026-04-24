/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_comparator

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_comp.h"

struct comp_v32f20x_config {
	COMP_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

struct comp_v32f20x_data {
	/* State data */
};

/* Custom API for Comparator since Zephyr has no standard COMP subsystem */
struct comp_v32f20x_driver_api {
	int (*get_value)(const struct device *dev);
	void (*set_enable)(const struct device *dev, bool enable);
};

static int comp_v32f20x_get_value(const struct device *dev)
{
	const struct comp_v32f20x_config *config = dev->config;
	return (COMP_GetOutputVal(config->base) == SET) ? 1 : 0;
}

static void comp_v32f20x_set_enable(const struct device *dev, bool enable)
{
	const struct comp_v32f20x_config *config = dev->config;
	COMP_Cmd(config->base, enable ? ENABLE : DISABLE);
}

static const struct comp_v32f20x_driver_api comp_api = {
	.get_value = comp_v32f20x_get_value,
	.set_enable = comp_v32f20x_set_enable,
};

static int comp_v32f20x_init(const struct device *dev)
{
	const struct comp_v32f20x_config *config = dev->config;
	COMP_InitType init_struct;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) {
		return ret;
	}

	/* 2. Basic hardware initialization */
	COMP_StructInit(&init_struct);
	init_struct.COMP_Mode = COMP_Mode_HighSpeed;
	init_struct.COMP_HystEn = ENABLE;
	init_struct.COMP_OutputLevel = COMP_Output_Positive;
	
	COMP_Init(config->base, &init_struct);

	return 0;
}

#define COMP_V32F20X_INIT(n) \
	static const struct comp_v32f20x_config comp_v32f20x_config_##n = { \
		.base = (COMP_Type *)DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	static struct comp_v32f20x_data comp_v32f20x_data_##n; \
	DEVICE_DT_INST_DEFINE(n, comp_v32f20x_init, NULL, \
			      &comp_v32f20x_data_##n, &comp_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, \
			      &comp_api);

DT_INST_FOREACH_STATUS_OKAY(COMP_V32F20X_INIT)
