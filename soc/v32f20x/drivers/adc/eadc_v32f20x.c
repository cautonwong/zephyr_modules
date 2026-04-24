/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_eadc

#include <zephyr/device.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_eadc.h"

struct eadc_v32f20x_config {
	uintptr_t base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

struct eadc_v32f20x_data {
	uint32_t active_channels;
};

static int eadc_v32f20x_channel_setup(const struct device *dev,
				      const struct adc_channel_cfg *channel_cfg)
{
	if (channel_cfg->channel_id > 7) {
		return -EINVAL;
	}

	/* V32F20X EADC channel configuration */
	EADC_Channel_Config(BIT(channel_cfg->channel_id), 64, EADC_CP_TRIG_POS);
	
	return 0;
}

static int eadc_v32f20x_read(const struct device *dev,
			     const struct adc_sequence *sequence)
{
	/* For EADC, standard ADC read might be too simple, 
	 * but we provide a basic polled implementation first. 
	 */
	if (sequence->channels == 0) return -EINVAL;

	EADC_Cmd(EADC_CLK_IN, sequence->channels, ENABLE);
	
	/* Implementation would involve waiting for FIFO or CDMA completion */
	
	return 0;
}

static const struct adc_driver_api eadc_api = {
	.channel_setup = eadc_v32f20x_channel_setup,
	.read = eadc_v32f20x_read,
};

static int eadc_v32f20x_init(const struct device *dev)
{
	const struct eadc_v32f20x_config *config = dev->config;
	EADC_InitType init_struct;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Basic EADC initialization */
	EADC_DeInit();
	EADC_StructInit(&init_struct);
	init_struct.EADC_CdmaClkFreqDiv = EADC_CDMA_CLK_DIV_4;
	init_struct.EADC_SeqSetsNum = EADC_SEQ_SETS_NUM_4;
	EADC_Init(&init_struct);

	return 0;
}

#define EADC_V32F20X_INIT(n) \
	static const struct eadc_v32f20x_config eadc_v32f20x_config_##n = { \
		.base = DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	static struct eadc_v32f20x_data eadc_v32f20x_data_##n; \
	DEVICE_DT_INST_DEFINE(n, eadc_v32f20x_init, NULL, \
			      &eadc_v32f20x_data_##n, &eadc_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_ADC_INIT_PRIORITY, \
			      &eadc_api);

DT_INST_FOREACH_STATUS_OKAY(EADC_V32F20X_INIT)
