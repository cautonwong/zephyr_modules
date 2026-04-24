/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_sdio

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_sdio.h"

struct sdio_v32f20x_config {
	SDIO_TypeDef *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

/* Custom SDIO API for V32F20X */
struct sdio_v32f20x_api {
	int (*send_cmd)(const struct device *dev, uint32_t cmd, uint32_t arg, uint32_t resp_type, uint32_t *resp);
};

static int sdio_v32f20x_send_cmd(const struct device *dev, uint32_t cmd, uint32_t arg, uint32_t resp_type, uint32_t *resp)
{
	const struct sdio_v32f20x_config *config = dev->config;
	SDIO_CMDInitType cmd_init;

	SDIO_CmdStructInit(&cmd_init);
	cmd_init.CmdIndex = cmd;
	cmd_init.Argument = arg;
	cmd_init.Response = resp_type;
	cmd_init.DataMode = SDIO_NODATA;

	if (SDIO_SendCommand(config->base, &cmd_init) != STD_OK) {
		return -EIO;
	}

	if (resp && resp_type != SDIO_Response_No) {
		resp[0] = SDIO_GetResponse(config->base, SDIO_RESP1);
	}

	return 0;
}

static const struct sdio_v32f20x_api sdio_api = {
	.send_cmd = sdio_v32f20x_send_cmd,
};

static int sdio_v32f20x_init(const struct device *dev)
{
	const struct sdio_v32f20x_config *config = dev->config;
	SDIO_InitType sdio_init;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Standard SDIO Initialization */
	SDIO_DeInit(config->base);
	
	sdio_init.BusWide = SDIO_CTRL1_DATWIDTH_1BIT;
	sdio_init.ClockDiv = 0x80;
	sdio_init.Mode = SDIO_DEVICE_SDCard;
	
	SDIO_Init(config->base, &sdio_init);
	SDIO_SWReset(config->base);

	return 0;
}

#define SDIO_V32F20X_INIT(n) \
	static const struct sdio_v32f20x_config sdio_v32f20x_config_##n = { \
		.base = (SDIO_TypeDef *)DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(n, sdio_v32f20x_init, NULL, \
			      NULL, &sdio_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE, \
			      &sdio_api);

DT_INST_FOREACH_STATUS_OKAY(SDIO_V32F20X_INIT)
