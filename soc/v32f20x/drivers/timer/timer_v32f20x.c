/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_timer

#include <zephyr/kernel.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/logging/log.h>
#include <soc.h>
#include <lib_timer.h>

LOG_MODULE_REGISTER(v32f20x_timer, CONFIG_COUNTER_LOG_LEVEL);

struct timer_v32f20x_config {
	struct counter_config_info info;
	TIMER_Type *regs;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

struct timer_v32f20x_data {
	counter_alarm_callback_t callback;
	void *user_data;
};

static int timer_v32f20x_start(const struct device *dev)
{
	const struct timer_v32f20x_config *config = dev->config;

	TIMER_Cmd(config->regs, ENABLE);
	return 0;
}

static int timer_v32f20x_stop(const struct device *dev)
{
	const struct timer_v32f20x_config *config = dev->config;

	TIMER_Cmd(config->regs, DISABLE);
	return 0;
}

static uint32_t timer_v32f20x_get_value(const struct device *dev)
{
	const struct timer_v32f20x_config *config = dev->config;

	return TIMER_GetCounter(config->regs);
}

static int timer_v32f20x_set_alarm(const struct device *dev, uint8_t chan,
				   const struct counter_alarm_cfg *alarm_cfg)
{
	const struct timer_v32f20x_config *config = dev->config;
	struct timer_v32f20x_data *data = dev->data;

	if (chan != 0) {
		return -ENOTSUP;
	}

	data->callback = alarm_cfg->callback;
	data->user_data = alarm_cfg->user_data;

	TIMER_SetCompare0(config->regs, alarm_cfg->ticks);
	TIMER_INTConfig(config->regs, TIMER_INT_CC0, ENABLE);

	return 0;
}

static const struct counter_driver_api timer_v32f20x_api = {
	.start = timer_v32f20x_start,
	.stop = timer_v32f20x_stop,
	.get_value = timer_v32f20x_get_value,
	.set_alarm = timer_v32f20x_set_alarm,
};

static int timer_v32f20x_init(const struct device *dev)
{
	const struct timer_v32f20x_config *config = dev->config;
	uint32_t clock_rate;
	TIMER_InitType init_struct;

	if (clock_control_on(config->clock_dev, config->clock_subsys) != 0) {
		return -EIO;
	}

	if (clock_control_get_rate(config->clock_dev, config->clock_subsys, &clock_rate) != 0) {
		return -EIO;
	}

	TIMER_StructInit(&init_struct);
	/* Setup for 1MHz resolution if possible, or use raw clock */
	init_struct.TIMER_Prescaler = (clock_rate / 1000000) - 1;
	TIMER_Init(config->regs, &init_struct);

	return 0;
}

#define TIMER_V32F20X_INIT(n)                                                  \
	static const struct timer_v32f20x_config timer_v32f20x_config_##n = {      \
		.info = { .max_top_value = 0xFFFFFFFF },                               \
		.regs = (TIMER_Type *)DT_INST_REG_ADDR(n),                             \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),                   \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, id),    \
	};                                                                         \
	static struct timer_v32f20x_data timer_v32f20x_data_##n;                   \
	DEVICE_DT_INST_DEFINE(n, timer_v32f20x_init, NULL,                         \
			      &timer_v32f20x_data_##n,                              \
			      &timer_v32f20x_config_##n, PRE_KERNEL_1,              \
			      CONFIG_COUNTER_INIT_PRIORITY,                         \
			      &timer_v32f20x_api);

DT_INST_FOREACH_STATUS_OKAY(TIMER_V32F20X_INIT)
