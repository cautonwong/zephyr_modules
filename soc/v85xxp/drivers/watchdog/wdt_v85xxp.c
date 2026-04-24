/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_wdt

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#include <zephyr/device.h>
#include <zephyr/drivers/watchdog.h>
#include <zephyr/drivers/clock_control.h>

#include <soc.h>
#include "lib_wdt.h"
#include "lib_clk.h"

struct v85xxp_wdt_config {
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

struct v85xxp_wdt_data {
	bool installed;
};

static int v85xxp_wdt_install_timeout(const struct device *dev,
				      const struct wdt_timeout_cfg *cfg)
{
	struct v85xxp_wdt_data *data = dev->data;

	if (cfg->window.min != 0U || cfg->window.max == 0U) {
		return -ENOTSUP;
	}

	if (cfg->window.max <= 2000U) {
		WDT_SetPeriod(WDT_2_SECS);
	} else if (cfg->window.max <= 4000U) {
		WDT_SetPeriod(WDT_4_SECS);
	} else if (cfg->window.max <= 8000U) {
		WDT_SetPeriod(WDT_8_SECS);
	} else {
		WDT_SetPeriod(WDT_16_SECS);
	}

	data->installed = true;
	return 0;
}

static int v85xxp_wdt_setup(const struct device *dev, uint8_t options)
{
	struct v85xxp_wdt_data *data = dev->data;

	ARG_UNUSED(options);
	if (!data->installed) return -EINVAL;

	WDT_Clear();
	WDT_Enable();
	return 0;
}

static int v85xxp_wdt_disable(const struct device *dev)
{
	WDT_Disable();
	return 0;
}

static int v85xxp_wdt_feed(const struct device *dev, int channel_id)
{
	ARG_UNUSED(channel_id);
	WDT_Clear();
	return 0;
}

static int v85xxp_wdt_init(const struct device *dev)
{
	const struct v85xxp_wdt_config *cfg = dev->config;

	if (clock_control_on(cfg->clock_dev, cfg->clock_subsys) != 0) return -EIO;
	WDT_Disable();
	return 0;
}

static DEVICE_API(wdt, v85xxp_wdt_api) = {
	.setup = v85xxp_wdt_setup,
	.disable = v85xxp_wdt_disable,
	.install_timeout = v85xxp_wdt_install_timeout,
	.feed = v85xxp_wdt_feed,
};

#define V85XXP_WDT_INIT(inst) \
	static const struct v85xxp_wdt_config v85xxp_wdt_cfg_##inst = { \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
	}; \
	static struct v85xxp_wdt_data v85xxp_wdt_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_wdt_init, NULL, \
			      &v85xxp_wdt_data_##inst, &v85xxp_wdt_cfg_##inst, \
			      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE, \
			      &v85xxp_wdt_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_WDT_INIT)
