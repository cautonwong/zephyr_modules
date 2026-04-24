/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_uart

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/irq.h>

#include <soc.h>
#include "lib_uart.h"
#include "lib_clk.h"

struct v85xxp_uart_config {
	UART_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct pinctrl_dev_config *pincfg;
	uint32_t baud_rate;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	void (*irq_config_func)(const struct device *dev);
#endif
};

struct v85xxp_uart_data {
	struct uart_config uart_cfg;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	uart_irq_callback_user_data_t callback;
	void *cb_data;
#endif
};

static int v85xxp_uart_poll_in(const struct device *dev, unsigned char *c)
{
	const struct v85xxp_uart_config *config = dev->config;

	if (UART_GetFlag(config->base, UART_FLAG_RXFULL) == RESET) {
		return -1;
	}

	*c = (unsigned char)UART_ReceiveData(config->base);
	return 0;
}

static void v85xxp_uart_poll_out(const struct device *dev, unsigned char c)
{
	const struct v85xxp_uart_config *config = dev->config;

	UART_SendData(config->base, c);
	while (UART_GetFlag(config->base, UART_FLAG_TXDONE) == RESET) {
		/* Wait */
	}
	UART_ClearFlag(config->base, UART_FLAG_TXDONE);
}

static int v85xxp_uart_err_check(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	uint32_t state = config->base->STATE;
	int err = 0;

	if (state & UART_STATE_RXOV_Msk) {
		err |= UART_ERROR_OVERRUN;
	}
	if (state & UART_STATE_RXPE_Msk) {
		err |= UART_ERROR_PARITY;
	}

	return err;
}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static int v85xxp_uart_fifo_fill(const struct device *dev, const uint8_t *tx_data, int len)
{
	const struct v85xxp_uart_config *config = dev->config;
	int num_tx = 0;

	while ((len - num_tx > 0) && (UART_GetFlag(config->base, UART_FLAG_TXFULL) == RESET)) {
		UART_SendData(config->base, tx_data[num_tx++]);
	}

	return num_tx;
}

static int v85xxp_uart_fifo_read(const struct device *dev, uint8_t *rx_data, const int len)
{
	const struct v85xxp_uart_config *config = dev->config;
	int num_rx = 0;

	while ((len - num_rx > 0) && (UART_GetFlag(config->base, UART_FLAG_RXFULL) == SET)) {
		rx_data[num_rx++] = UART_ReceiveData(config->base);
	}

	return num_rx;
}

static void v85xxp_uart_irq_tx_enable(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	UART_ITConfig(config->base, UART_IT_TXDONE, ENABLE);
}

static void v85xxp_uart_irq_tx_disable(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	UART_ITConfig(config->base, UART_IT_TXDONE, DISABLE);
}

static int v85xxp_uart_irq_tx_ready(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	return (UART_GetFlag(config->base, UART_FLAG_TXDONE) == SET);
}

static void v85xxp_uart_irq_rx_enable(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	UART_ITConfig(config->base, UART_IT_RXFULL, ENABLE);
}

static void v85xxp_uart_irq_rx_disable(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	UART_ITConfig(config->base, UART_IT_RXFULL, DISABLE);
}

static int v85xxp_uart_irq_rx_ready(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	return (UART_GetFlag(config->base, UART_FLAG_RXFULL) == SET);
}

static void v85xxp_uart_irq_callback_set(const struct device *dev, uart_irq_callback_user_data_t cb, void *user_data)
{
	struct v85xxp_uart_data *data = dev->data;
	data->callback = cb;
	data->cb_data = user_data;
}

static int v85xxp_uart_irq_is_pending(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	return (config->base->INTSTAT & (UART_INTSTAT_RXFULL_Msk | UART_INTSTAT_TXDONE_Msk));
}

static int v85xxp_uart_irq_update(const struct device *dev)
{
	return 1;
}

static void v85xxp_uart_isr(const struct device *dev)
{
	struct v85xxp_uart_data *data = dev->data;

	if (data->callback) {
		data->callback(dev, data->cb_data);
	}
}
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */

static int v85xxp_uart_init(const struct device *dev)
{
	const struct v85xxp_uart_config *config = dev->config;
	struct v85xxp_uart_data *data = dev->data;
	UART_InitType init_struct;
	uint32_t pclk;
	int ret;

	/* 1. Enable Clock */
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret != 0) return ret;

	/* 2. Apply Pinctrl */
	ret = pinctrl_apply_state(config->pincfg, PINCTRL_STATE_DEFAULT);
	if (ret < 0 && ret != -ENOENT) return ret;

	/* 3. Get Clock Rate */
	CLK_GetClockConfig(NULL); // Sync HAL state if needed
	pclk = CLK_GetPCLKFreq();

	/* 4. Configure UART via HAL */
	init_struct.UART_Baudrate = config->baud_rate;
	init_struct.UART_StopBits = UART_STOPBITS_1;
	init_struct.UART_Parity = UART_PARITY_NONE;
	UART_Init(config->base, &init_struct);

	data->uart_cfg.baudrate = config->baud_rate;

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	config->irq_config_func(dev);
#endif

	return 0;
}

static const struct uart_driver_api v85xxp_uart_driver_api = {
	.poll_in = v85xxp_uart_poll_in,
	.poll_out = v85xxp_uart_poll_out,
	.err_check = v85xxp_uart_err_check,
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.fifo_fill = v85xxp_uart_fifo_fill,
	.fifo_read = v85xxp_uart_fifo_read,
	.irq_tx_enable = v85xxp_uart_irq_tx_enable,
	.irq_tx_disable = v85xxp_uart_irq_tx_disable,
	.irq_tx_ready = v85xxp_uart_irq_tx_ready,
	.irq_rx_enable = v85xxp_uart_irq_rx_enable,
	.irq_rx_disable = v85xxp_uart_irq_rx_disable,
	.irq_rx_ready = v85xxp_uart_irq_rx_ready,
	.irq_is_pending = v85xxp_uart_irq_is_pending,
	.irq_update = v85xxp_uart_irq_update,
	.irq_callback_set = v85xxp_uart_irq_callback_set,
#endif
};

#define V85XXP_UART_IRQ_HANDLER_DECL(inst) \
	static void v85xxp_uart_irq_config_func_##inst(const struct device *dev);

#define V85XXP_UART_IRQ_HANDLER_FUNC(inst) \
	static void v85xxp_uart_irq_config_func_##inst(const struct device *dev) \
	{ \
		IRQ_CONNECT(DT_INST_IRQN(inst), \
			    DT_INST_IRQ(inst, priority), \
			    v85xxp_uart_isr, DEVICE_DT_INST_GET(inst), 0); \
		irq_enable(DT_INST_IRQN(inst)); \
	}

#define V85XXP_UART_INIT(inst) \
	PINCTRL_DT_INST_DEFINE(inst); \
	IF_ENABLED(CONFIG_UART_INTERRUPT_DRIVEN, (V85XXP_UART_IRQ_HANDLER_DECL(inst))) \
	static const struct v85xxp_uart_config v85xxp_uart_config_##inst = { \
		.base = (UART_Type *)DT_INST_REG_ADDR(inst), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(inst), \
		.baud_rate = DT_INST_PROP_OR(inst, current_speed, 115200), \
		IF_ENABLED(CONFIG_UART_INTERRUPT_DRIVEN, (.irq_config_func = v85xxp_uart_irq_config_func_##inst,)) \
	}; \
	static struct v85xxp_uart_data v85xxp_uart_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_uart_init, NULL, \
			      &v85xxp_uart_data_##inst, &v85xxp_uart_config_##inst, \
			      PRE_KERNEL_1, CONFIG_SERIAL_INIT_PRIORITY, \
			      &v85xxp_uart_driver_api); \
	IF_ENABLED(CONFIG_UART_INTERRUPT_DRIVEN, (V85XXP_UART_IRQ_HANDLER_FUNC(inst)))

DT_INST_FOREACH_STATUS_OKAY(V85XXP_UART_INIT)
