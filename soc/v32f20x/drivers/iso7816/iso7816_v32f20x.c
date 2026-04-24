/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_iso7816

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_iso7816.h"

struct iso7816_v32f20x_config {
	ISO7816_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int iso7816_v32f20x_init(const struct device *dev)
{
	const struct iso7816_v32f20x_config *config = dev->config;
	ISO7816_InitType iso_init;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Standard ISO7816 Initialization based on lib_iso7816.c facts */
	ISO7816_DeInit(config->base);
	ISO7816_StructInit(&iso_init);
	
	iso_init.Baudrate = 9600; /* Standard SmartCard initial baudrate */
	
	ISO7816_Init(config->base, &iso_init);
	ISO7816_Cmd(config->base, ENABLE);

	return 0;
}

#define ISO7816_V32F20X_INIT(n) \
	static const struct iso7816_v32f20x_config iso7816_v32f20x_config_##n = { \
		.base = (ISO7816_Type *)DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(n, iso7816_v32f20x_init, NULL, \
			      NULL, &iso7816_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(ISO7816_V32F20X_INIT)
