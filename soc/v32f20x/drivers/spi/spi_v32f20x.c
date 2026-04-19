/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_spi

#include <zephyr/kernel.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/reset.h>
#include <zephyr/drivers/pinctrl.h>
#include <soc.h>
#include <lib_spi.h>

struct spi_v32f20x_config {
	SPI_Type *regs;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct reset_dt_spec reset;
	const struct pinctrl_dev_config *pincfg;
};

struct spi_v32f20x_data {
	struct spi_context ctx;
};

static int spi_v32f20x_configure(const struct device *dev,
				 const struct spi_config *config)
{
	const struct spi_v32f20x_config *dev_conf = dev->config;
	struct spi_v32f20x_data *data = dev->data;
	SPI_InitType init_struct;
	uint32_t clock_rate;

	if (spi_context_configured(&data->ctx, config)) {
		return 0;
	}

	if (clock_control_get_rate(dev_conf->clock_dev, dev_conf->clock_subsys, &clock_rate) != 0) {
		return -EIO;
	}

	SPI_StructInit(&init_struct);
	init_struct.SPI_BaudRate = config->frequency;
	init_struct.SPI_BusClock = clock_rate;

	/* Data Size */
	uint32_t word_size = SPI_WORD_SIZE_GET(config->operation);
	if (word_size == 8) {
		init_struct.SPI_DataSize = SPI_DATASIZE_8B;
	} else if (word_size == 16) {
		init_struct.SPI_DataSize = SPI_DATASIZE_16B;
	} else {
		return -ENOTSUP;
	}

	/* Mode (CPOL/CPHA) */
	if (config->operation & SPI_MODE_CPOL) {
		init_struct.SPI_CPOL = SPI_CPOL_HIGH;
	} else {
		init_struct.SPI_CPOL = SPI_CPOL_LOW;
	}

	if (config->operation & SPI_MODE_CPHA) {
		init_struct.SPI_CPHA = SPI_CPHA_2EDGE;
	} else {
		init_struct.SPI_CPHA = SPI_CPHA_1EDGE;
	}

	/* Master/Slave */
	if (SPI_OP_MODE_GET(config->operation) == SPI_OP_MODE_MASTER) {
		init_struct.SPI_Mode = SPI_MODE_MASTER;
	} else {
		init_struct.SPI_Mode = SPI_MODE_SLAVE;
	}

	SPI_Init(dev_conf->regs, &init_struct);
	data->ctx.config = config;

	return 0;
}

static int spi_v32f20x_transceive(const struct device *dev,
				  const struct spi_config *config,
				  const struct spi_buf_set *tx_bufs,
				  const struct spi_buf_set *rx_bufs)
{
	const struct spi_v32f20x_config *dev_conf = dev->config;
	struct spi_v32f20x_data *data = dev->data;
	int ret;

	spi_context_lock(&data->ctx, false, NULL, NULL, config);

	ret = spi_v32f20x_configure(dev, config);
	if (ret < 0) {
		goto out;
	}

	spi_context_cs_control(&data->ctx, true);

	/* Simplified synchronous transceive for now */
	/* In professional driver, we should loop through bufs */
	const struct spi_buf *tx = tx_bufs ? tx_bufs->buffers : NULL;
	const struct spi_buf *rx = rx_bufs ? rx_bufs->buffers : NULL;

	if (tx && rx && tx->len == rx->len) {
		SPI_SendReceiveData(dev_conf->regs, tx->buf, rx->buf, tx->len);
	} else if (tx) {
		SPI_SendData(dev_conf->regs, tx->buf, tx->len);
	} else if (rx) {
		SPI_ReceiveData(dev_conf->regs, rx->buf, rx->len);
	}

	spi_context_cs_control(&data->ctx, false);

out:
	spi_context_release(&data->ctx, ret);
	return ret;
}

static const struct spi_driver_api spi_v32f20x_driver_api = {
	.transceive = spi_v32f20x_transceive,
};

static int spi_v32f20x_init(const struct device *dev)
{
	const struct spi_v32f20x_config *config = dev->config;
	struct spi_v32f20x_data *data = dev->data;
	int ret;

	ret = pinctrl_apply_state(config->pincfg, PINCTRL_STATE_DEFAULT);
	if (ret < 0) return ret;

	if (config->reset.dev != NULL) {
		reset_line_toggle(config->reset.dev, config->reset.id);
	}

	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	spi_context_unlock_unconditionally(&data->ctx);

	return 0;
}

#define SPI_V32F20X_INIT(n)                                                    \
	PINCTRL_DT_INST_DEFINE(n);                                                 \
	static const struct spi_v32f20x_config spi_v32f20x_config_##n = {          \
		.regs = (SPI_Type *)DT_INST_REG_ADDR(n),                               \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),                   \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, id),    \
		.reset = RESET_DT_SPEC_INST_GET_OR(n, {0}),                            \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(n),                           \
	};                                                                         \
	static struct spi_v32f20x_data spi_v32f20x_data_##n = {                    \
		SPI_CONTEXT_INIT_LOCK(spi_v32f20x_data_##n, ctx),                  \
		SPI_CONTEXT_INIT_SYNC(spi_v32f20x_data_##n, ctx),                  \
	};                                                                         \
	DEVICE_DT_INST_DEFINE(n, spi_v32f20x_init, NULL, &spi_v32f20x_data_##n,      \
			      &spi_v32f20x_config_##n, POST_KERNEL,                \
			      CONFIG_SPI_INIT_PRIORITY, &spi_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(SPI_V32F20X_INIT)
