/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_spi

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/pinctrl.h>

#include <soc.h>
#include "lib_spi.h"
#include "lib_clk.h"

struct v85xxp_spi_config {
	SPI_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct pinctrl_dev_config *pincfg;
};

struct v85xxp_spi_data {
	struct spi_config cfg;
};

static uint32_t v85xxp_spi_clk_div(const struct spi_config *cfg)
{
	if (cfg->frequency >= 2000000U) {
		return SPI_CLKDIV_2;
	}
	if (cfg->frequency >= 1000000U) {
		return SPI_CLKDIV_4;
	}
	if (cfg->frequency >= 500000U) {
		return SPI_CLKDIV_8;
	}
	return SPI_CLKDIV_16;
}

static int v85xxp_spi_configure(const struct device *dev,
				const struct spi_config *cfg)
{
	const struct v85xxp_spi_config *config = dev->config;
	struct v85xxp_spi_data *data = dev->data;
	SPI_InitType init;

	if (SPI_OP_MODE_GET(cfg->operation) != SPI_OP_MODE_MASTER ||
	    SPI_WORD_SIZE_GET(cfg->operation) != 8U ||
	    (cfg->operation & SPI_TRANSFER_LSB) != 0U) {
		return -ENOTSUP;
	}

	SPI_StructInit(&init);
	init.Mode = SPI_MODE_MASTER;
	init.SPH = (cfg->operation & SPI_MODE_CPHA) ? SPI_SPH_1 : SPI_SPH_0;
	init.SPO = (cfg->operation & SPI_MODE_CPOL) ? SPI_SPO_1 : SPI_SPO_0;
	init.FirstBit = SPI_FIRSTBIT_MSB;
	init.ClockDivision = v85xxp_spi_clk_div(cfg);
	init.CSNSoft = SPI_CSNSOFT_DISABLE;
	init.SWAP = SPI_SWAP_DISABLE;

	SPI_DeviceInit(config->base);
	SPI_Init(config->base, &init);
	SPI_Cmd(config->base, ENABLE);
	data->cfg = *cfg;
	return 0;
}

static int v85xxp_spi_transceive(const struct device *dev,
				 const struct spi_config *cfg,
				 const struct spi_buf_set *tx_bufs,
				 const struct spi_buf_set *rx_bufs)
{
	const struct v85xxp_spi_config *config = dev->config;
	size_t tx_len = 0U, rx_len = 0U, i;
	size_t max_len;

	if (v85xxp_spi_configure(dev, cfg) != 0) {
		return -ENOTSUP;
	}

	for (i = 0; tx_bufs && i < tx_bufs->count; i++) {
		tx_len += tx_bufs->buffers[i].len;
	}
	for (i = 0; rx_bufs && i < rx_bufs->count; i++) {
		rx_len += rx_bufs->buffers[i].len;
	}

	max_len = (tx_len > rx_len) ? tx_len : rx_len;
	for (i = 0; i < max_len; i++) {
		uint8_t txd = 0xFFU;
		uint8_t rxd;

		if (tx_bufs && tx_bufs->count > 0U && i < tx_bufs->buffers[0].len) {
			txd = ((const uint8_t *)tx_bufs->buffers[0].buf)[i];
		}

		SPI_SendData(config->base, txd);
		while (SPI_GetStatus(config->base, SPI_STS_RNE) == 0U) {
		}
		rxd = SPI_ReceiveData(config->base);

		if (rx_bufs && rx_bufs->count > 0U && i < rx_bufs->buffers[0].len) {
			((uint8_t *)rx_bufs->buffers[0].buf)[i] = rxd;
		}
	}

	return 0;
}

static int v85xxp_spi_release(const struct device *dev,
			      const struct spi_config *cfg)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(cfg);
	return 0;
}

static int v85xxp_spi_init(const struct device *dev)
{
	const struct v85xxp_spi_config *cfg = dev->config;
	int ret;

	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) return ret;

	ret = pinctrl_apply_state(cfg->pincfg, PINCTRL_STATE_DEFAULT);
	if (ret < 0 && ret != -ENOENT) return ret;

	SPI_DeviceInit(cfg->base);
	return 0;
}

static DEVICE_API(spi, v85xxp_spi_api) = {
	.transceive = v85xxp_spi_transceive,
	.release = v85xxp_spi_release,
};

#define V85XXP_SPI_INIT(inst) \
	PINCTRL_DT_INST_DEFINE(inst); \
	static const struct v85xxp_spi_config v85xxp_spi_cfg_##inst = { \
		.base = (SPI_Type *)DT_INST_REG_ADDR(inst), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(inst), \
	}; \
	static struct v85xxp_spi_data v85xxp_spi_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_spi_init, NULL, \
			      &v85xxp_spi_data_##inst, &v85xxp_spi_cfg_##inst, \
			      POST_KERNEL, CONFIG_SPI_INIT_PRIORITY, \
			      &v85xxp_spi_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_SPI_INIT)
