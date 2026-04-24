/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_dcmi

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/reset.h>
#include <soc.h>
#include "lib_dcmi.h"

struct dcmi_v32f20x_config {
	uintptr_t base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct reset_dt_spec reset;
};

/* Custom DCMI API for V32F20X */
struct dcmi_v32f20x_api {
	void (*start_capture)(const struct device *dev);
	void (*stop_capture)(const struct device *dev);
};

static void dcmi_v32f20x_start_capture(const struct device *dev)
{
	DCMI_CaptureCmd(ENABLE);
}

static void dcmi_v32f20x_stop_capture(const struct device *dev)
{
	DCMI_CaptureCmd(DISABLE);
}

static const struct dcmi_v32f20x_api dcmi_api = {
	.start_capture = dcmi_v32f20x_start_capture,
	.stop_capture = dcmi_v32f20x_stop_capture,
};

static int dcmi_v32f20x_init(const struct device *dev)
{
	const struct dcmi_v32f20x_config *config = dev->config;
	DCMI_InitTypeDef dcmi_init;
	int ret;

	/* 1. Reset and Enable Clock */
	if (reset_is_ready_dt(&config->reset)) {
		reset_line_toggle_dt(&config->reset);
	}
	
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Standard DCMI Initialization */
	DCMI_DeInit();
	DCMI_StructInit(&dcmi_init);
	DCMI_Init(&dcmi_init);
	DCMI_Cmd(ENABLE);

	return 0;
}

#define DCMI_V32F20X_INIT(n) \
	static const struct dcmi_v32f20x_config dcmi_v32f20x_config_##n = { \
		.base = DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
		.reset = RESET_DT_SPEC_INST_GET(n), \
	}; \
	DEVICE_DT_INST_DEFINE(n, dcmi_v32f20x_init, NULL, \
			      NULL, &dcmi_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE, \
			      &dcmi_api);

DT_INST_FOREACH_STATUS_OKAY(DCMI_V32F20X_INIT)
