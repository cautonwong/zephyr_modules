/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_wdt

#include <zephyr/kernel.h>
#include <zephyr/drivers/watchdog.h>
#include <soc.h>
#include <lib_wdt.h>

struct wdt_v32f20x_config {
	WDT_Type *regs;
};

struct wdt_v32f20x_data {
	wdt_callback_t callback;
	uint32_t timeout;
};

static int wdt_v32f20x_setup(const struct device *dev, uint8_t options)
{
	const struct wdt_v32f20x_config *config = dev->config;

	/* In V32F20X, WDT configuration is applied immediately during install_timeout.
	 * setup() just enables the counter.
	 */
	WDT_Cmd(config->regs, ENABLE);
	return 0;
}

static int wdt_v32f20x_disable(const struct device *dev)
{
	const struct wdt_v32f20x_config *config = dev->config;

	WDT_Cmd(config->regs, DISABLE);
	return 0;
}

static int wdt_v32f20x_install_timeout(const struct device *dev,
					const struct wdt_timeout_cfg *cfg)
{
	const struct wdt_v32f20x_config *config = dev->config;
	WDT_InitType init_struct;

	if (cfg->window.min != 0U || cfg->window.max == 0U) {
		return -EINVAL;
	}

	WDT_StructInit(&init_struct);
	/* Map ms to watchdog ticks (simplified mapping) */
	init_struct.WDT_Load = (cfg->window.max * 10); 
	
	if (cfg->callback) {
		init_struct.WDT_Mode = WDT_MODE_INT;
	} else {
		init_struct.WDT_Mode = WDT_MODE_RST;
	}

	WDT_Init(config->regs, &init_struct);
	return 0;
}

static int wdt_v32f20x_feed(const struct device *dev, int channel_id)
{
	const struct wdt_v32f20x_config *config = dev->config;
	ARG_UNUSED(channel_id);

	WDT_RestartCounter(config->regs);
	return 0;
}

static const struct watchdog_driver_api wdt_v32f20x_api = {
	.setup = wdt_v32f20x_setup,
	.disable = wdt_v32f20x_disable,
	.install_timeout = wdt_v32f20x_install_timeout,
	.feed = wdt_v32f20x_feed,
};

static int wdt_v32f20x_init(const struct device *dev)
{
	/* Watchdog clock is usually always on or managed by PMU */
	return 0;
}

#define WDT_V32F20X_INIT(n)                                                    \
	static const struct wdt_v32f20x_config wdt_v32f20x_config_##n = {          \
		.regs = (WDT_Type *)DT_INST_REG_ADDR(n),                               \
	};                                                                         \
	static struct wdt_v32f20x_data wdt_v32f20x_data_##n;                       \
	DEVICE_DT_INST_DEFINE(n, wdt_v32f20x_init, NULL, &wdt_v32f20x_data_##n,      \
			      &wdt_v32f20x_config_##n, PRE_KERNEL_1,               \
			      CONFIG_KERNEL_INIT_PRIORITY, &wdt_v32f20x_api);

DT_INST_FOREACH_STATUS_OKAY(WDT_V32F20X_INIT)
