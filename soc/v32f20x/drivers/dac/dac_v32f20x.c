/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_dac

#include <zephyr/device.h>
#include <zephyr/drivers/dac.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_dac.h"

struct dac_v32f20x_config {
	DAC_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

struct dac_v32f20x_data {
	uint8_t active_channels;
};

static int dac_v32f20x_channel_setup(const struct device *dev,
				     const struct dac_channel_cfg *channel_cfg)
{
	const struct dac_v32f20x_config *config = dev->config;
	DAC_InitType init_struct;

	if (channel_cfg->channel_id > 1) {
		return -EINVAL;
	}

	if (channel_cfg->resolution != 12) {
		return -ENOTSUP;
	}

	DAC_StructInit(&init_struct);
	init_struct.DAC_Trigger = DAC_TRIGGER_NONE;
	init_struct.DAC_OutputBuffer = DAC_OUTPUT_BUFFER_ENABLE;
	
	/* Initialize the specific channel */
	uint32_t hal_channel = (channel_cfg->channel_id == 0) ? DAC_CHANNEL_0 : DAC_CHANNEL_1;
	DAC_Init(hal_channel, &init_struct);
	DAC_Cmd(hal_channel, ENABLE);

	return 0;
}

static int dac_v32f20x_write_value(const struct device *dev, uint8_t channel,
				   uint32_t value)
{
	const struct dac_v32f20x_config *config = dev->config;

	if (channel > 1) {
		return -EINVAL;
	}

	if (value > 4095) {
		return -EINVAL;
	}

	if (channel == 0) {
		DAC_SetChannel0Data(DAC_ALIGN_12B_R, (uint16_t)value);
	} else {
		DAC_SetChannel1Data(DAC_ALIGN_12B_R, (uint16_t)value);
	}

	return 0;
}

static const struct dac_driver_api dac_v32f20x_driver_api = {
	.channel_setup = dac_v32f20x_channel_setup,
	.write_value = dac_v32f20x_write_value,
};

static int dac_v32f20x_init(const struct device *dev)
{
	const struct dac_v32f20x_config *config = dev->config;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) {
		return ret;
	}

	/* 2. Reset and basic init */
	DAC_DeInit();

	return 0;
}

#define DAC_V32F20X_INIT(n) \
	static const struct dac_v32f20x_config dac_v32f20x_config_##n = { \
		.base = (DAC_Type *)DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	static struct dac_v32f20x_data dac_v32f20x_data_##n; \
	DEVICE_DT_INST_DEFINE(n, dac_v32f20x_init, NULL, \
			      &dac_v32f20x_data_##n, &dac_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_DAC_INIT_PRIORITY, \
			      &dac_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(DAC_V32F20X_INIT)
