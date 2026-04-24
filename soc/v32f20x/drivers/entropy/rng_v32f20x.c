/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_rng

#include <zephyr/device.h>
#include <zephyr/drivers/entropy.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_rng.h"

struct entropy_v32f20x_config {
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int entropy_v32f20x_get_entropy(const struct device *dev,
				       uint8_t *buffer,
				       uint16_t length)
{
	uint16_t pos = 0;
	uint16_t chunk;

	while (length > 0) {
		chunk = (length > 24) ? 24 : length;
		
		/* Wait for RNG data ready if needed, here we assume ready after init */
		RNG_ReadData(&buffer[pos], chunk);
		
		length -= chunk;
		pos += chunk;
	}

	return 0;
}

static const struct entropy_driver_api entropy_v32f20x_api_funcs = {
	.get_entropy = entropy_v32f20x_get_entropy
};

static int entropy_v32f20x_init(const struct device *dev)
{
	const struct entropy_v32f20x_config *config = dev->config;
	RNG_InitType init_struct;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Reset and Initialize RNG */
	RNG_DeInit();
	RNG_StructInit(&init_struct);
	RNG_Init(&init_struct);
	RNG_Cmd(ENABLE);

	return 0;
}

#define ENTROPY_V32F20X_INIT(n) \
	static const struct entropy_v32f20x_config entropy_v32f20x_config_##n = { \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(n, entropy_v32f20x_init, NULL, \
			      NULL, &entropy_v32f20x_config_##n, \
			      PRE_KERNEL_1, CONFIG_ENTROPY_INIT_PRIORITY, \
			      &entropy_v32f20x_api_funcs);

DT_INST_FOREACH_STATUS_OKAY(ENTROPY_V32F20X_INIT)
