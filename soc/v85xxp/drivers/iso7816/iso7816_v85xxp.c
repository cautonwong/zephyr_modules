/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_iso7816

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>

#include <soc.h>
#include "lib_iso7816.h"
#include "lib_clk.h"

struct v85xxp_iso7816_config {
	ISO7816_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int v85xxp_iso7816_init(const struct device *dev)
{
	const struct v85xxp_iso7816_config *cfg = dev->config;
	ISO7816_InitType init;
	int ret;

	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) return ret;

	ISO7816_DeInit(cfg->base);
	ISO7816_StructInit(&init);
	init.Baudrate = 9600; /* Default T=0/T=1 baudrate */
	ISO7816_Init(cfg->base, &init);
	ISO7816_Cmd(cfg->base, ENABLE);

	return 0;
}

#define V85XXP_ISO7816_INIT(inst) \
	static const struct v85xxp_iso7816_config v85xxp_iso7816_cfg_##inst = { \
		.base = (ISO7816_Type *)DT_INST_REG_ADDR(inst), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_iso7816_init, NULL, \
			      NULL, &v85xxp_iso7816_cfg_##inst, \
			      POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_ISO7816_INIT)
