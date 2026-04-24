/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_i2s

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_i2s.h"

struct i2s_v32f20x_config {
	I2S_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int i2s_v32f20x_init(const struct device *dev)
{
	const struct i2s_v32f20x_config *config = dev->config;
	I2S_InitType i2s_init;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Standard I2S Initialization based on lib_i2s.c facts */
	I2S_DeInit(config->base);
	I2S_StructInit(&i2s_init);
	
	i2s_init.Mode = I2S_MODE_MASTER;
	i2s_init.Standard = I2S_STANDARD_PHILLIPS;
	i2s_init.DataFormat = I2S_DATAFORMAT_16B;
	i2s_init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
	i2s_init.AudioFreq = I2S_AUDIOFREQ_44K;
	
	I2S_Init(config->base, &i2s_init);
	I2S_Cmd(config->base, ENABLE);

	return 0;
}

#define I2S_V32F20X_INIT(n) \
	static const struct i2s_v32f20x_config i2s_v32f20x_config_##n = { \
		.base = (I2S_Type *)DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(n, i2s_v32f20x_init, NULL, \
			      NULL, &i2s_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(I2S_V32F20X_INIT)
