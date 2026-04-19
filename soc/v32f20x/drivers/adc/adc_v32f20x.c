/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_adc

#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include <lib_adc.h>

struct adc_v32f20x_config {
	ADC_Type *regs;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

struct adc_v32f20x_data {
	struct k_sem lock;
	struct adc_seq_table *seq_table;
	uint16_t *buffer;
	uint16_t *buffer_ptr;
};

static int adc_v32f20x_channel_setup(const struct device *dev,
				     const struct adc_channel_cfg *channel_cfg)
{
	if (channel_cfg->acquisition_time != ADC_ACQ_TIME_DEFAULT) {
		return -ENOTSUP;
	}

	if (channel_cfg->reference != ADC_REF_INTERNAL) {
		return -ENOTSUP;
	}

	return 0;
}

static int adc_v32f20x_read(const struct device *dev,
			    const struct adc_sequence *sequence)
{
	const struct adc_v32f20x_config *config = dev->config;
	struct adc_v32f20x_data *data = dev->data;
	int ret = 0;

	k_sem_take(&data->lock, K_FOREVER);

	/* Simplified single channel sync read for now */
	uint32_t channel = find_lsb_set(sequence->channels) - 1;
	
	ADC_ChannelSelect(config->regs, 1UL << channel);
	ADC_SoftwareStartConv(config->regs);

	while (ADC_GetFlagStatus(config->regs, ADC_FLAG_EOC) == RESET) {
		/* Timeout logic should be added here for production */
	}

	uint16_t val = ADC_GetConversionValue(config->regs);
	*(uint16_t *)sequence->buffer = val;

	k_sem_give(&data->lock);
	return ret;
}

static const struct adc_driver_api adc_v32f20x_driver_api = {
	.channel_setup = adc_v32f20x_channel_setup,
	.read = adc_v32f20x_read,
};

static int adc_v32f20x_init(const struct device *dev)
{
	const struct adc_v32f20x_config *config = dev->config;
	struct adc_v32f20x_data *data = dev->data;
	ADC_InitType init_struct;

	k_sem_init(&data->lock, 1, 1);

	clock_control_on(config->clock_dev, config->clock_subsys);

	ADC_StructInit(&init_struct);
	/* V32F20X ADC specific init */
	ADC_Init(config->regs, &init_struct);
	ADC_Cmd(config->regs, ENABLE);

	return 0;
}

#define ADC_V32F20X_INIT(n)                                                    \
	static const struct adc_v32f20x_config adc_v32f20x_config_##n = {          \
		.regs = (ADC_Type *)DT_INST_REG_ADDR(n),                               \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),                   \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, id),    \
	};                                                                         \
	static struct adc_v32f20x_data adc_v32f20x_data_##n;                       \
	DEVICE_DT_INST_DEFINE(n, adc_v32f20x_init, NULL, &adc_v32f20x_data_##n,      \
			      &adc_v32f20x_config_##n, POST_KERNEL,                \
			      CONFIG_ADC_INIT_PRIORITY, &adc_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(ADC_V32F20X_INIT)
