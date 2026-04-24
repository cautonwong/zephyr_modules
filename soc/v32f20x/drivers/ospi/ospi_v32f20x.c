/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_ospi

#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_ospi.h"

struct ospi_v32f20x_config {
	OSPI_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

static int ospi_v32f20x_transceive(const struct device *dev,
				  const struct spi_config *spi_cfg,
				  const struct spi_buf_set *tx_bufs,
				  const struct spi_buf_set *rx_bufs)
{
	const struct ospi_v32f20x_config *config = dev->config;
	size_t tx_len = 0, rx_len = 0;
	const uint8_t *tx_ptr = NULL;
	uint8_t *rx_ptr = NULL;

	if (tx_bufs && tx_bufs->count > 0) {
		tx_ptr = tx_bufs->buffers[0].buf;
		tx_len = tx_bufs->buffers[0].len;
	}
	if (rx_bufs && rx_bufs->count > 0) {
		rx_ptr = rx_bufs->buffers[0].buf;
		rx_len = rx_bufs->buffers[0].len;
	}

	size_t max_len = (tx_len > rx_len) ? tx_len : rx_len;

	for (size_t i = 0; i < max_len; i++) {
		uint32_t data = 0xFF;

		if (i < tx_len) {
			data = tx_ptr[i];
		}

		/* Wait for TX FIFO not full */
		while (OSPI_GetFlagStatus(config->base, OSPI_FLAG_STATUS_TFNF) == RESET);
		OSPI_SendData(config->base, data);

		/* Wait for RX FIFO not empty */
		while (OSPI_GetFlagStatus(config->base, OSPI_FLAG_STATUS_RFNE) == RESET);
		data = OSPI_ReceiveData(config->base);

		if (i < rx_len) {
			rx_ptr[i] = (uint8_t)data;
		}
	}

	return 0;
}

static const struct spi_driver_api ospi_v32f20x_api = {
	.transceive = ospi_v32f20x_transceive,
};

static int ospi_v32f20x_init(const struct device *dev)
{
	const struct ospi_v32f20x_config *config = dev->config;
	OSPI_InitType ospi_init;
	int ret;

	/* 1. Enable peripheral clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Standard OSPI Initialization based on lib_ospi.c facts */
	OSPI_DeInit(config->base);
	OSPI_StructInit(&ospi_init);
	
	ospi_init.OSPI_WorkingMode = OSPI_WorkingMode_Master;
	ospi_init.OSPI_SPIFrameFormat = OSPI_SPIFrameFormat_OctalSPI;
	ospi_init.OSPI_DataLength = OSPI_DataLength_8BIT;
	ospi_init.OSPI_SCLKDivider = 2; /* Default divider */
	
	OSPI_Init(config->base, &ospi_init);
	OSPI_Cmd(config->base, ENABLE);

	return 0;
}

#define OSPI_V32F20X_INIT(n) \
	static const struct ospi_v32f20x_config ospi_v32f20x_config_##n = { \
		.base = (OSPI_Type *)DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(n, ospi_v32f20x_init, NULL, \
			      NULL, &ospi_v32f20x_config_##n, \
			      POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE, \
			      &ospi_v32f20x_api);

DT_INST_FOREACH_STATUS_OKAY(OSPI_V32F20X_INIT)
