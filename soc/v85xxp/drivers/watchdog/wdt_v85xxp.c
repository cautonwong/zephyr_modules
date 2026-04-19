/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_wdt

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#include <zephyr/device.h>
#include <zephyr/drivers/watchdog.h>

#include <soc.h>
#include "lib_wdt.h"

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
	if (!data->installed) {
		return -EINVAL;
	}

	WDT_Clear();
	WDT_Enable();
	return 0;
}

static int v85xxp_wdt_disable(const struct device *dev)
{
	ARG_UNUSED(dev);
	WDT_Disable();
	return 0;
}

static int v85xxp_wdt_feed(const struct device *dev, int channel_id)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(channel_id);
	WDT_Clear();
	return 0;
}

static int v85xxp_wdt_init(const struct device *dev)
{
	ARG_UNUSED(dev);
	WDT_Disable();
	return 0;
}

static DEVICE_API(wdt, v85xxp_wdt_api) = {
	.setup = v85xxp_wdt_setup,
	.disable = v85xxp_wdt_disable,
	.install_timeout = v85xxp_wdt_install_timeout,
	.feed = v85xxp_wdt_feed,
};

static struct v85xxp_wdt_data v85xxp_wdt_data;

DEVICE_DT_INST_DEFINE(0, v85xxp_wdt_init, NULL,
		      &v85xxp_wdt_data, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &v85xxp_wdt_api);
