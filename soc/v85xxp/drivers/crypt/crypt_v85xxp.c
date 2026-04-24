/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_crypt

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>

#include <soc.h>
#include "lib_crypt.h"
#include "lib_clk.h"

struct v85xxp_crypt_config {
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int v85xxp_crypt_init(const struct device *dev)
{
	const struct v85xxp_crypt_config *cfg = dev->config;
	int ret;

	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) return ret;

	/* Crypt is a basic functional accelerator, no specific state init required */
	return 0;
}

#define V85XXP_CRYPT_INIT(inst) \
	static const struct v85xxp_crypt_config v85xxp_crypt_cfg_##inst = { \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_crypt_init, NULL, \
			      &v85xxp_crypt_cfg_##inst, NULL, \
			      POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_CRYPT_INIT)
