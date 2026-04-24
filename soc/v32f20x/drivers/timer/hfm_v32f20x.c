/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_hfm

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_hfm.h"

struct hfm_v32f20x_config {
	uintptr_t base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int hfm_v32f20x_init(const struct device *dev)
{
	const struct hfm_v32f20x_config *config = dev->config;
	HFM_InitType hfm_init;
	WAVER_InitType waver_init;
	int ret;

	/* 1. Enable Energy module clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. DeInit and Initialize HFM/WAVER submodules */
	HFM_DeInit();
	WAVER_DeInit();

	/* Configure WAVER (Waveform capture) */
	WAVER_StructInit(&waver_init);
	waver_init.Mode = WAVER_MODE_3U_IA_IB_IC;
	waver_init.SampleLength = WAVER_SAMPLELEN_256;
	WAVER_Init(&waver_init);
	WAVER_Cmd(ENABLE);

	/* Configure HFM (Energy calculation engine) */
	HFM_StructInit(&hfm_init);
	hfm_init.Mode = HFM_MODE_3U_IA_IB_IC;
	HFM_Init(&hfm_init);

	return 0;
}

#define HFM_V32F20X_INIT(n) \
	static const struct hfm_v32f20x_config hfm_v32f20x_config_##n = { \
		.base = DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(n, hfm_v32f20x_init, NULL, \
			      NULL, &hfm_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(HFM_V32F20X_INIT)
