/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_analog

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>

#include <soc.h>
#include "lib_ana.h"
#include "lib_clk.h"

struct v85xxp_analog_config {
	uintptr_t base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int v85xxp_analog_init(const struct device *dev)
{
	const struct v85xxp_analog_config *cfg = dev->config;
	int ret;

	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) {
		return ret;
	}

	/* Analog module is complex; drivers usually expose specific APIs. 
	 * For now, we ensure the clock is enabled and the module is ready.
	 */
	return 0;
}

#define V85XXP_ANALOG_INIT(inst) \
	static const struct v85xxp_analog_config v85xxp_analog_cfg_##inst = { \
		.base = DT_INST_REG_ADDR(inst), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_analog_init, NULL, \
			      NULL, &v85xxp_analog_cfg_##inst, \
			      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_ANALOG_INIT)
