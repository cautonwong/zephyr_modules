/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_enceng

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_enceng.h"

struct enceng_v32f20x_config {
	uintptr_t base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int enceng_v32f20x_init(const struct device *dev)
{
	const struct enceng_v32f20x_config *config = dev->config;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Basic hardware initialization */
	ENCENG_DeInit();
	
	/* Module is an accelerator, usually ready after clock enable and deinit */
	return 0;
}

#define ENCENG_V32F20X_INIT(n) \
	static const struct enceng_v32f20x_config enceng_v32f20x_config_##n = { \
		.base = DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(n, enceng_v32f20x_init, NULL, \
			      NULL, &enceng_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(ENCENG_V32F20X_INIT)
