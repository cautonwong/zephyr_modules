/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_adc

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/adc.h>

#include <soc.h>
#include "lib_adc.h"

struct v85xxp_adc_data {
	uint32_t channels;
};

static uint32_t v85xxp_adc_channel_to_hal(uint8_t id)
{
	switch (id) {
	case 0: return ADC_CHANNEL_GND0;
	case 1: return ADC_CHANNEL_BAT1;
	case 2: return ADC_CHANNEL_BATRTC;
	case 3: return ADC_CHANNEL_CH3;
	case 4: return ADC_CHANNEL_CH4;
	case 5: return ADC_CHANNEL_CH5;
	case 6: return ADC_CHANNEL_CH6;
	case 7: return ADC_CHANNEL_CH7;
	case 8: return ADC_CHANNEL_CH8;
	case 9: return ADC_CHANNEL_CH9;
	case 10: return ADC_CHANNEL_TEMP;
	case 11: return ADC_CHANNEL_CH11;
	case 12: return ADC_CHANNEL_DVCC;
	default:
		return 0U;
	}
}

static int v85xxp_adc_channel_setup(const struct device *dev,
				    const struct adc_channel_cfg *channel_cfg)
{
	struct v85xxp_adc_data *data = dev->data;

	if (channel_cfg->channel_id > 12U) {
		return -EINVAL;
	}

	data->channels |= BIT(channel_cfg->channel_id);
	return 0;
}

static int v85xxp_adc_read(const struct device *dev,
			  const struct adc_sequence *sequence)
{
	struct v85xxp_adc_data *data = dev->data;
	ADC_InitType init;
	uint8_t ch;
	int16_t sample;

	if (sequence->buffer == NULL || sequence->buffer_size < sizeof(int16_t)) {
		return -EINVAL;
	}

	for (ch = 0U; ch <= 12U; ch++) {
		if ((sequence->channels & BIT(ch)) != 0U) {
			break;
		}
	}

	if (ch > 12U || (data->channels & BIT(ch)) == 0U) {
		return -EINVAL;
	}

	ADC_StructInit(&init);
	init.Mode = (ch == 10U) ? ADC_MODE_TEMP : ADC_MODE_DC;
	init.ClockSource = ADC_CLKSRC_RCH;
	init.SkipSample = ADC_SKIP_0;
	init.AverageSample = ADC_AVERAGE_2;
	init.TriggerSource = ADC_TRIGSOURCE_OFF;
	init.Channel = v85xxp_adc_channel_to_hal(ch);
	init.ResDivEnable = 0U;
	init.AverageEnable = 0U;
	ADC_Init(&init);
	ADC_Cmd(ENABLE);
	ADC_StartManual();
	if (ADC_WaitForManual(0xFFFFFFU) == 0U) {
		ADC_Cmd(DISABLE);
		return -EIO;
	}

	sample = ADC_GetADCConversionValue(v85xxp_adc_channel_to_hal(ch));
	*((int16_t *)sequence->buffer) = sample;
	ADC_Cmd(DISABLE);
	return 0;
}

static int v85xxp_adc_read_async(const struct device *dev,
				const struct adc_sequence *sequence,
				struct k_poll_signal *async)
{
	ARG_UNUSED(async);
	return v85xxp_adc_read(dev, sequence);
}

static int v85xxp_adc_init(const struct device *dev)
{
	struct v85xxp_adc_data *data = dev->data;

	data->channels = 0U;
	return 0;
}

static DEVICE_API(adc, v85xxp_adc_api) = {
	.channel_setup = v85xxp_adc_channel_setup,
	.read = v85xxp_adc_read,
	.read_async = v85xxp_adc_read_async,
};

static struct v85xxp_adc_data v85xxp_adc_data;

DEVICE_DT_INST_DEFINE(0, v85xxp_adc_init, NULL,
		      &v85xxp_adc_data, NULL,
		      POST_KERNEL, CONFIG_ADC_INIT_PRIORITY,
		      &v85xxp_adc_api);
