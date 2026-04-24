/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_usb_hs

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/reset.h>
#include <soc.h>

struct usb_v32f20x_config {
	uintptr_t base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int usb_v32f20x_init(const struct device *dev)
{
	const struct usb_v32f20x_config *config = dev->config;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Basic USB Core Initialization */
	/* Logic to enable USB PHY and global interrupts would go here */

	return 0;
}

#define USB_V32F20X_INIT(n) \
	static const struct usb_v32f20x_config usb_v32f20x_config_##n = { \
		.base = DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(n, usb_v32f20x_init, NULL, \
			      NULL, &usb_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(USB_V32F20X_INIT)
