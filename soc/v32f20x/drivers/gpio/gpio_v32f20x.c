/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_gpio

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_utils.h>
#include <zephyr/irq.h>
#include <soc.h>
#include <lib_gpio.h>
#include <lib_gpio_ex.h>

/* Global array to store GPIO devices for ISR routing */
static const struct device *gpio_v32f20x_devices[9];

struct gpio_v32f20x_config {
	struct gpio_driver_config common;
	GPIO_Type *regs;
	uint8_t port_idx;
};

struct gpio_v32f20x_data {
	struct gpio_driver_data common;
	sys_slist_t callbacks;
};

static int gpio_v32f20x_pin_configure(const struct device *dev,
				      gpio_pin_t pin,
				      gpio_flags_t flags)
{
	const struct gpio_v32f20x_config *config = dev->config;
	GPIO_InitType init_struct;

	GPIO_StructInit(&init_struct);
	init_struct.GPIO_Pin = BIT(pin);

	if (flags & GPIO_OUTPUT) {
		init_struct.GPIO_Mode = GPIO_Mode_OUT;
		init_struct.GPIO_OType = (flags & GPIO_OPEN_DRAIN) ? GPIO_OType_OD : GPIO_OType_PP;

		if (flags & GPIO_OUTPUT_INIT_HIGH) {
			GPIO_SetBits(config->regs, BIT(pin));
		} else if (flags & GPIO_OUTPUT_INIT_LOW) {
			GPIO_ResetBits(config->regs, BIT(pin));
		}
	} else if (flags & GPIO_DISCONNECTED) {
		init_struct.GPIO_Mode = GPIO_Mode_AN;
	} else {
		init_struct.GPIO_Mode = GPIO_Mode_IN;
	}

	if (flags & GPIO_PULL_UP) {
		init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	} else if (flags & GPIO_PULL_DOWN) {
		init_struct.GPIO_PuPd = GPIO_PuPd_DOWN;
	} else {
		init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	}

	init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(config->regs, &init_struct);

	return 0;
}

static int gpio_v32f20x_port_get_raw(const struct device *dev,
				    gpio_port_value_t *value)
{
	const struct gpio_v32f20x_config *config = dev->config;
	*value = GPIO_ReadInputData(config->regs);
	return 0;
}

static int gpio_v32f20x_port_set_masked_raw(const struct device *dev,
					   gpio_port_pins_t mask,
					   gpio_port_value_t value)
{
	const struct gpio_v32f20x_config *config = dev->config;
	uint32_t port_val;

	port_val = GPIO_ReadOutputData(config->regs);
	port_val = (port_val & ~mask) | (value & mask);
	GPIO_Write(config->regs, port_val);
	return 0;
}

static int gpio_v32f20x_port_set_bits_raw(const struct device *dev,
					 gpio_port_pins_t mask)
{
	const struct gpio_v32f20x_config *config = dev->config;
	GPIO_SetBits(config->regs, mask);
	return 0;
}

static int gpio_v32f20x_port_clear_bits_raw(const struct device *dev,
					   gpio_port_pins_t mask)
{
	const struct gpio_v32f20x_config *config = dev->config;
	GPIO_ResetBits(config->regs, mask);
	return 0;
}

static int gpio_v32f20x_port_toggle_bits(const struct device *dev,
					gpio_port_pins_t mask)
{
	const struct gpio_v32f20x_config *config = dev->config;
	GPIO_ToggleBits(config->regs, mask);
	return 0;
}

static int gpio_v32f20x_pin_interrupt_configure(const struct device *dev,
						gpio_pin_t pin,
						enum gpio_int_mode mode,
						enum gpio_int_trig trig)
{
	const struct gpio_v32f20x_config *config = dev->config;
	uint16_t event = GPIO_EVENT_DISABLE;

	if (mode != GPIO_INT_MODE_DISABLED) {
		if (mode == GPIO_INT_MODE_LEVEL) {
			event = (trig == GPIO_INT_TRIG_LOW) ? GPIO_EVENT_LOW_LEVEL : GPIO_EVENT_HIGH_LEVEL;
		} else {
			if (trig == GPIO_INT_TRIG_BOTH) {
				event = GPIO_EVENT_DUAL_EDGE;
			} else {
				event = (trig == GPIO_INT_TRIG_LOW) ? GPIO_EVENT_FALLING_EDGE : GPIO_EVENT_RISING_EDGE;
			}
		}
	}

	GPIO_INT_Config(config->regs, BIT(pin), event);
	return 0;
}

static int gpio_v32f20x_manage_callback(const struct device *dev,
				       struct gpio_callback *callback,
				       bool set)
{
	struct gpio_v32f20x_data *data = dev->data;
	return gpio_manage_callback(&data->callbacks, callback, set);
}

static void gpio_v32f20x_isr(const void *arg)
{
	uint32_t pr = EXTI->PR & 0xFFFF;

	for (int i = 0; i < 16; i++) {
		if (pr & BIT(i)) {
			uint32_t cr = ((uint32_t *)&EXTI->CR1)[i / 4];
			uint32_t port_idx = (cr >> ((i % 4) * 4)) & 0xF;

			if (port_idx < ARRAY_SIZE(gpio_v32f20x_devices)) {
				const struct device *dev = gpio_v32f20x_devices[port_idx];
				if (dev) {
					struct gpio_v32f20x_data *data = dev->data;
					gpio_fire_callbacks(&data->callbacks, dev, BIT(i));
				}
			}
			EXTI->PR = BIT(i);
		}
	}
}

static const struct gpio_driver_api gpio_v32f20x_driver_api = {
	.pin_configure = gpio_v32f20x_pin_configure,
	.port_get_raw = gpio_v32f20x_port_get_raw,
	.port_set_masked_raw = gpio_v32f20x_port_set_masked_raw,
	.port_set_bits_raw = gpio_v32f20x_port_set_bits_raw,
	.port_clear_bits_raw = gpio_v32f20x_port_clear_bits_raw,
	.port_toggle_bits = gpio_v32f20x_port_toggle_bits,
	.pin_interrupt_configure = gpio_v32f20x_pin_interrupt_configure,
	.manage_callback = gpio_v32f20x_manage_callback,
};

static int gpio_v32f20x_init(const struct device *dev)
{
	const struct gpio_v32f20x_config *config = dev->config;
	gpio_v32f20x_devices[config->port_idx] = dev;
	return 0;
}

/* 
 * Professional approach: Define a global IRQ connection helper that runs once.
 * We use the interrupts from INSTANCE 0 as the source of truth for the entire GPIO block.
 */
#define GPIO_V32F20X_IRQ_CONNECT(idx, inst) \
	IRQ_CONNECT(DT_INST_IRQ_BY_IDX(inst, idx, irq), \
		    DT_INST_IRQ_BY_IDX(inst, idx, priority), \
		    gpio_v32f20x_isr, NULL, 0); \
	irq_enable(DT_INST_IRQ_BY_IDX(inst, idx, irq));

#define GPIO_V32F20X_INIT(n)                                                   \
	static const struct gpio_v32f20x_config gpio_v32f20x_config_##n = {        \
		.common = {                                                            \
			.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_INST(n),               \
		},                                                                     \
		.regs = (GPIO_Type *)DT_INST_REG_ADDR(n),                              \
		.port_idx = (DT_INST_REG_ADDR(n) - 0x40104000) / 0x400,                \
	};                                                                         \
	static struct gpio_v32f20x_data gpio_v32f20x_data_##n;                     \
	DEVICE_DT_INST_DEFINE(n, gpio_v32f20x_init, NULL,                         \
			      &gpio_v32f20x_data_##n,                              \
			      &gpio_v32f20x_config_##n, PRE_KERNEL_1,              \
			      CONFIG_GPIO_INIT_PRIORITY,                           \
			      &gpio_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(GPIO_V32F20X_INIT)

/* Final touch: Connect interrupts exactly once using index 0 as template */
#if DT_NUM_INST_STATUS_OKAY(vango_v32f20x_gpio) > 0
static int gpio_v32f20x_irq_init(void)
{
	LISTIFY(16, GPIO_V32F20X_IRQ_CONNECT, (;), 0)
	return 0;
}
SYS_INIT(gpio_v32f20x_irq_init, PRE_KERNEL_1, CONFIG_GPIO_INIT_PRIORITY);
#endif
