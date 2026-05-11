/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_uart32k

#include <zephyr/device.h>
#include <zephyr/drivers/serial.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/irq.h>

#include <soc.h>
#include "lib_u32k.h"

struct uart32k_v85xxp_config {
	U32K_Type *regs;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	void (*irq_config_func)(const struct device *dev);
#endif
};

struct uart32k_v85xxp_data {
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	uart_irq_callback_user_data_t callback;
	void *cb_data;
#endif
};

static int uart32k_v85xxp_poll_in(const struct device *dev, unsigned char *c)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;

	if (U32K_GetINTStatus(cfg->regs, U32K_INTSTS_RX)) {
		*c = U32K_ReceiveData(cfg->regs);
		U32K_ClearINTStatus(cfg->regs, U32K_INTSTS_RX);
		return 0;
	}

	return -1;
}

static void uart32k_v85xxp_poll_out(const struct device *dev, unsigned char c)
{
	/* UART32K is receive-only hardware */
	ARG_UNUSED(dev);
	ARG_UNUSED(c);
}

static int uart32k_v85xxp_err_check(const struct device *dev)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	uint32_t status = U32K_GetINTStatus(cfg->regs, U32K_INTSTS_Msk);
	int errors = 0;

	if (status & U32K_INTSTS_RXOV) {
		errors |= UART_ERROR_OVERRUN;
	}
	if (status & U32K_INTSTS_RXPE) {
		errors |= UART_ERROR_PARITY;
	}

	return errors;
}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static int uart32k_v85xxp_fifo_fill(const struct device *dev,
				  const uint8_t *tx_data,
				  int size)
{
	/* Receive-only hardware */
	return 0;
}

static int uart32k_v85xxp_fifo_read(const struct device *dev,
				  uint8_t *rx_data,
				  const int size)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	int count = 0;

	while ((count < size) && U32K_GetINTStatus(cfg->regs, U32K_INTSTS_RX)) {
		rx_data[count++] = U32K_ReceiveData(cfg->regs);
		U32K_ClearINTStatus(cfg->regs, U32K_INTSTS_RX);
	}

	return count;
}

static void uart32k_v85xxp_irq_tx_enable(const struct device *dev)
{
	/* No TX */
}

static void uart32k_v85xxp_irq_tx_disable(const struct device *dev)
{
	/* No TX */
}

static int uart32k_v85xxp_irq_tx_ready(const struct device *dev)
{
	return 0;
}

static void uart32k_v85xxp_irq_rx_enable(const struct device *dev)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	U32K_INTConfig(cfg->regs, U32K_INT_RX, ENABLE);
}

static void uart32k_v85xxp_irq_rx_disable(const struct device *dev)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	U32K_INTConfig(cfg->regs, U32K_INT_RX, DISABLE);
}

static int uart32k_v85xxp_irq_rx_ready(const struct device *dev)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	return U32K_GetINTStatus(cfg->regs, U32K_INTSTS_RX);
}

static void uart32k_v85xxp_irq_err_enable(const struct device *dev)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	U32K_INTConfig(cfg->regs, U32K_INT_RXOV | U32K_INT_RXPE, ENABLE);
}

static void uart32k_v85xxp_irq_err_disable(const struct device *dev)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	U32K_INTConfig(cfg->regs, U32K_INT_RXOV | U32K_INT_RXPE, DISABLE);
}

static int uart32k_v85xxp_irq_is_pending(const struct device *dev)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	return U32K_GetINTStatus(cfg->regs, U32K_INTSTS_Msk);
}

static int uart32k_v85xxp_irq_update(const struct device *dev)
{
	return 1;
}

static void uart32k_v85xxp_irq_callback_set(const struct device *dev,
					  uart_irq_callback_user_data_t cb,
					  void *cb_data)
{
	struct uart32k_v85xxp_data *data = dev->data;

	data->callback = cb;
	data->cb_data = cb_data;
}

static void uart32k_v85xxp_isr(const struct device *dev)
{
	struct uart32k_v85xxp_data *data = dev->data;

	if (data->callback) {
		data->callback(dev, data->cb_data);
	}
}
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */

static int uart32k_v85xxp_init(const struct device *dev)
{
	const struct uart32k_v85xxp_config *cfg = dev->config;
	U32K_InitType init;
	int ret;

	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) {
		return ret;
	}

	U32K_StructInit(&init);
	/* Default: 9600 baud, None parity, LSB first, AutoCal ON */
	U32K_Init(cfg->regs, &init);
	U32K_Cmd(cfg->regs, ENABLE);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	cfg->irq_config_func(dev);
#endif

	return 0;
}

static const struct uart_driver_api uart32k_v85xxp_driver_api = {
	.poll_in = uart32k_v85xxp_poll_in,
	.poll_out = uart32k_v85xxp_poll_out,
	.err_check = uart32k_v85xxp_err_check,
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.fifo_fill = uart32k_v85xxp_fifo_fill,
	.fifo_read = uart32k_v85xxp_fifo_read,
	.irq_tx_enable = uart32k_v85xxp_irq_tx_enable,
	.irq_tx_disable = uart32k_v85xxp_irq_tx_disable,
	.irq_tx_ready = uart32k_v85xxp_irq_tx_ready,
	.irq_rx_enable = uart32k_v85xxp_irq_rx_enable,
	.irq_rx_disable = uart32k_v85xxp_irq_rx_disable,
	.irq_rx_ready = uart32k_v85xxp_irq_rx_ready,
	.irq_err_enable = uart32k_v85xxp_irq_err_enable,
	.irq_err_disable = uart32k_v85xxp_irq_err_disable,
	.irq_is_pending = uart32k_v85xxp_irq_is_pending,
	.irq_update = uart32k_v85xxp_irq_update,
	.irq_callback_set = uart32k_v85xxp_irq_callback_set,
#endif
};

#define UART32K_V85XXP_INIT(n)						\
	static void uart32k_v85xxp_irq_config_##n(const struct device *dev) \
	{								\
		IRQ_CONNECT(DT_INST_IRQN(n),				\
			    DT_INST_IRQ(n, priority),			\
			    uart32k_v85xxp_isr, DEVICE_DT_INST_GET(n), 0); \
		irq_enable(DT_INST_IRQN(n));				\
	}								\
									\
	static const struct uart32k_v85xxp_config uart32k_v85xxp_cfg_##n = { \
		.regs = (U32K_Type *)DT_INST_REG_ADDR(n),		\
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),	\
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, id), \
		.irq_config_func = uart32k_v85xxp_irq_config_##n,	\
	};								\
									\
	static struct uart32k_v85xxp_data uart32k_v85xxp_data_##n;	\
									\
	DEVICE_DT_INST_DEFINE(n, uart32k_v85xxp_init,			\
			      NULL, &uart32k_v85xxp_data_##n,		\
			      &uart32k_v85xxp_cfg_##n, PRE_KERNEL_1,	\
			      CONFIG_SERIAL_INIT_PRIORITY,		\
			      &uart32k_v85xxp_driver_api);

DT_INST_FOREACH_STATUS_OKAY(UART32K_V85XXP_INIT)
