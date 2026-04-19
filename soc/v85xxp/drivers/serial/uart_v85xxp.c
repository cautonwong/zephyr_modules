/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_uart

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

#include <soc.h>
#include "lib_uart.h"

struct v85xxp_uart_config {
	UART_Type *base;
	uint32_t baud_rate;
};

struct v85xxp_uart_data {
	struct uart_config uart_cfg;
};

static uint32_t v85xxp_uart_gate_mask(UART_Type *base)
{
	switch ((uintptr_t)base) {
	case UART0_BASE:
		return MISC2_PCLKEN_UART0;
	case UART1_BASE:
		return MISC2_PCLKEN_UART1;
	case UART2_BASE:
		return MISC2_PCLKEN_UART2;
	case UART3_BASE:
		return MISC2_PCLKEN_UART3;
	case UART4_BASE:
		return MISC2_PCLKEN_UART4;
	case UART5_BASE:
		return MISC2_PCLKEN_UART5;
	default:
		return 0U;
	}
}

static uint32_t v85xxp_uart_pclk_hz(void)
{
	uint32_t clkdivh = (MISC2->CLKDIVH & MISC2_CLKDIVH_CLKDIVH) + 1U;
	uint32_t clkdivp = (MISC2->CLKDIVP & MISC2_CLKDIVP_CLKDIVP) + 1U;

	return (V85XXP_AHB_CLOCK_HZ / clkdivh) / clkdivp;
}

static void v85xxp_uart_apply_config(UART_Type *base, const struct uart_config *cfg)
{
	uint32_t pclk = v85xxp_uart_pclk_hz();
	uint32_t div = pclk / cfg->baudrate;

	if ((pclk % cfg->baudrate) > (cfg->baudrate / 2U)) {
		div++;
	}

	base->CTRL &= ~(UART_CTRL_RXEN_Msk | UART_CTRL_TXEN_Msk);
	base->CTRL2 &= ~(UART_CTRL2_PMODE_Msk | UART_CTRL2_MSB_Msk);
	base->BAUDDIV = div;
	base->CTRL = UART_CTRL_RXEN_Msk | UART_CTRL_TXEN_Msk;
}

static int v85xxp_uart_poll_in(const struct device *dev, unsigned char *c)
{
	const struct v85xxp_uart_config *config = dev->config;

	if ((config->base->STATE & UART_STATE_RXFULL_Msk) == 0U) {
		return -1;
	}

	*c = (unsigned char)config->base->DATA;
	return 0;
}

static void v85xxp_uart_poll_out(const struct device *dev, unsigned char c)
{
	const struct v85xxp_uart_config *config = dev->config;

	config->base->DATA = c;
	while ((config->base->STATE & UART_STATE_TXDONE_Msk) == 0U) {
	}
	config->base->STATE = UART_STATE_TXDONE_Msk;
}

static int v85xxp_uart_err_check(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	uint32_t state = config->base->STATE;
	int err = 0;

	if ((state & UART_STATE_RXOV_Msk) != 0U) {
		err |= UART_ERROR_OVERRUN;
	}

	if ((state & UART_STATE_RXPE_Msk) != 0U) {
		err |= UART_ERROR_PARITY;
	}

	if ((state & (UART_STATE_RXOV_Msk | UART_STATE_RXPE_Msk)) != 0U) {
		config->base->STATE = state & (UART_STATE_RXOV_Msk | UART_STATE_RXPE_Msk);
	}

	return err;
}

#ifdef CONFIG_UART_USE_RUNTIME_CONFIGURE
static int v85xxp_uart_configure(const struct device *dev, const struct uart_config *cfg)
{
	struct v85xxp_uart_data *data = dev->data;
	const struct v85xxp_uart_config *config = dev->config;

	if ((cfg->parity != UART_CFG_PARITY_NONE) ||
	    (cfg->stop_bits != UART_CFG_STOP_BITS_1) ||
	    (cfg->data_bits != UART_CFG_DATA_BITS_8) ||
	    (cfg->flow_ctrl != UART_CFG_FLOW_CTRL_NONE) ||
	    (cfg->baudrate == 0U)) {
		return -ENOTSUP;
	}

	data->uart_cfg = *cfg;
	v85xxp_uart_apply_config(config->base, cfg);

	return 0;
}

static int v85xxp_uart_config_get(const struct device *dev, struct uart_config *cfg)
{
	struct v85xxp_uart_data *data = dev->data;

	*cfg = data->uart_cfg;
	return 0;
}
#endif

static int v85xxp_uart_init(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	struct v85xxp_uart_data *data = dev->data;

	MISC2->PCLKEN |= v85xxp_uart_gate_mask(config->base);

	data->uart_cfg = (struct uart_config) {
		.baudrate = config->baud_rate,
		.parity = UART_CFG_PARITY_NONE,
		.stop_bits = UART_CFG_STOP_BITS_1,
		.data_bits = UART_CFG_DATA_BITS_8,
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE,
	};

	v85xxp_uart_apply_config(config->base, &data->uart_cfg);
	return 0;
}

static DEVICE_API(uart, v85xxp_uart_driver_api) = {
	.poll_in = v85xxp_uart_poll_in,
	.poll_out = v85xxp_uart_poll_out,
	.err_check = v85xxp_uart_err_check,
#ifdef CONFIG_UART_USE_RUNTIME_CONFIGURE
	.configure = v85xxp_uart_configure,
	.config_get = v85xxp_uart_config_get,
#endif
};

#define V85XXP_UART_INIT(inst) \
	static const struct v85xxp_uart_config v85xxp_uart_config_##inst = { \
		.base = (UART_Type *)DT_INST_REG_ADDR(inst), \
		.baud_rate = DT_INST_PROP_OR(inst, current_speed, 115200), \
	}; \
	static struct v85xxp_uart_data v85xxp_uart_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_uart_init, NULL, \
			      &v85xxp_uart_data_##inst, &v85xxp_uart_config_##inst, \
			      PRE_KERNEL_1, CONFIG_SERIAL_INIT_PRIORITY, \
			      &v85xxp_uart_driver_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_UART_INIT)
