/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_mailbox

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/irq.h>
#include <soc.h>
#include <lib_mailbox.h>

typedef void (*mailbox_v32f20x_callback_t)(const struct device *dev, uint32_t msg, void *user_data);

struct mailbox_v32f20x_config {
	MAILBOX_Type *regs;
	void (*irq_config_func)(const struct device *dev);
};

struct mailbox_v32f20x_data {
	mailbox_v32f20x_callback_t cb;
	void *user_data;
};

/* API to send message to the other core */
int mailbox_v32f20x_send(const struct device *dev, uint32_t msg)
{
	const struct mailbox_v32f20x_config *config = dev->config;
	
	/* Vango HAL API: Send data to other core */
	MAILBOX_SendData(config->regs, msg);
	return 0;
}

/* API to register a callback for received messages */
void mailbox_v32f20x_set_callback(const struct device *dev, mailbox_v32f20x_callback_t cb, void *user_data)
{
	struct mailbox_v32f20x_data *data = dev->data;
	data->cb = cb;
	data->user_data = user_data;
}

static void mailbox_v32f20x_isr(const struct device *dev)
{
	const struct mailbox_v32f20x_config *config = dev->config;
	struct mailbox_v32f20x_data *data = dev->data;

	if (MAILBOX_GetITStatus(config->regs)) {
		uint32_t msg = MAILBOX_ReceiveData(config->regs);
		MAILBOX_ClearITStatus(config->regs);
		
		if (data->cb) {
			data->cb(dev, msg, data->user_data);
		}
	}
}

static int mailbox_v32f20x_init(const struct device *dev)
{
	const struct mailbox_v32f20x_config *config = dev->config;

	config->irq_config_func(dev);
	MAILBOX_INTConfig(config->regs, ENABLE);

	return 0;
}

#define MAILBOX_V32F20X_INIT(n)                                                \
	static void mailbox_v32f20x_irq_config_##n(const struct device *dev)       \
	{                                                                          \
		IRQ_CONNECT(DT_INST_IRQN(n), DT_INST_IRQ(n, priority),                \
			    mailbox_v32f20x_isr, DEVICE_DT_INST_GET(n), 0);          \
		irq_enable(DT_INST_IRQN(n));                                           \
	}                                                                          \
	static const struct mailbox_v32f20x_config mailbox_v32f20x_config_##n = {  \
		.regs = (MAILBOX_Type *)DT_INST_REG_ADDR(n),                           \
		.irq_config_func = mailbox_v32f20x_irq_config_##n,                     \
	};                                                                         \
	static struct mailbox_v32f20x_data mailbox_v32f20x_data_##n;               \
	DEVICE_DT_INST_DEFINE(n, mailbox_v32f20x_init, NULL,                       \
			      &mailbox_v32f20x_data_##n,                           \
			      &mailbox_v32f20x_config_##n, PRE_KERNEL_1,           \
			      CONFIG_KERNEL_INIT_PRIORITY, NULL);

DT_INST_FOREACH_STATUS_OKAY(MAILBOX_V32F20X_INIT)
