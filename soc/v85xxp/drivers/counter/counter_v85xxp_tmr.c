/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_tmr_counter

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/clock_control.h>

#include <soc.h>
#include "lib_tmr.h"
#include "lib_clk.h"

struct v85xxp_counter_config {
	TMR_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	uint32_t top;
};

struct v85xxp_counter_data {
	counter_top_callback_t top_cb;
	void *top_user_data;
};

static int v85xxp_counter_start(const struct device *dev)
{
	const struct v85xxp_counter_config *cfg = dev->config;
	TMR_Cmd(cfg->base, ENABLE);
	return 0;
}

static int v85xxp_counter_stop(const struct device *dev)
{
	const struct v85xxp_counter_config *cfg = dev->config;
	TMR_Cmd(cfg->base, DISABLE);
	return 0;
}

static uint32_t v85xxp_counter_get_value(const struct device *dev)
{
	const struct v85xxp_counter_config *cfg = dev->config;
	return TMR_GetCurrentValue(cfg->base);
}

static int v85xxp_counter_set_top_value(const struct device *dev,
					const struct counter_top_cfg *cfg_in)
{
	const struct v85xxp_counter_config *cfg = dev->config;
	struct v85xxp_counter_data *data = dev->data;
	TMR_InitType init;

	if ((cfg_in->ticks == 0U) || (cfg_in->ticks > 0xFFFFFFFFU)) return -EINVAL;

	TMR_StructInit(&init);
	init.ClockSource = TMR_CLKSRC_INTERNAL;
	init.EXTGT = TMR_EXTGT_DISABLE;
	init.Period = cfg_in->ticks;
	TMR_Init(cfg->base, &init);

	data->top_cb = cfg_in->callback;
	data->top_user_data = cfg_in->user_data;
	return 0;
}

static uint32_t v85xxp_counter_get_pending_int(const struct device *dev)
{
	const struct v85xxp_counter_config *cfg = dev->config;
	return TMR_GetINTStatus(cfg->base);
}

static uint32_t v85xxp_counter_get_top_value(const struct device *dev)
{
	const struct v85xxp_counter_config *cfg = dev->config;
	return cfg->top;
}

static uint32_t v85xxp_counter_get_freq(const struct device *dev)
{
	const struct v85xxp_counter_config *cfg = dev->config;
	uint32_t rate;

	if (clock_control_get_rate(cfg->clock_dev, cfg->clock_subsys, &rate) != 0) return 0;
	return rate;
}

static int v85xxp_counter_init(const struct device *dev)
{
	const struct v85xxp_counter_config *cfg = dev->config;
	TMR_InitType init;

	if (clock_control_on(cfg->clock_dev, cfg->clock_subsys) != 0) return -EIO;

	TMR_DeInit(cfg->base);
	TMR_StructInit(&init);
	init.ClockSource = TMR_CLKSRC_INTERNAL;
	init.EXTGT = TMR_EXTGT_DISABLE;
	init.Period = cfg->top;
	TMR_Init(cfg->base, &init);
	return 0;
}

static DEVICE_API(counter, v85xxp_counter_api) = {
	.start = v85xxp_counter_start,
	.stop = v85xxp_counter_stop,
	.get_value = v85xxp_counter_get_value,
	.set_top_value = v85xxp_counter_set_top_value,
	.get_pending_int = v85xxp_counter_get_pending_int,
	.get_top_value = v85xxp_counter_get_top_value,
	.get_freq = v85xxp_counter_get_freq,
};

#define V85XXP_COUNTER_INIT(inst) \
	static const struct v85xxp_counter_config v85xxp_counter_cfg_##inst = { \
		.base = (TMR_Type *)DT_INST_REG_ADDR(inst), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
		.top = DT_INST_PROP_OR(inst, max_top_value, 0xFFFFFFFF), \
	}; \
	static struct v85xxp_counter_data v85xxp_counter_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_counter_init, NULL, \
			      &v85xxp_counter_data_##inst, &v85xxp_counter_cfg_##inst, \
			      POST_KERNEL, CONFIG_COUNTER_INIT_PRIORITY, \
			      &v85xxp_counter_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_COUNTER_INIT)
