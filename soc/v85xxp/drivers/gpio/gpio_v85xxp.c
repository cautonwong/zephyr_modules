/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_gpio

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_utils.h>

#include <soc.h>
#include "lib_gpio.h"

struct v85xxp_gpio_config {
	struct gpio_driver_config common;
	GPIO_Type *base;
};

struct v85xxp_gpio_data {
	struct gpio_driver_data common;
	gpio_port_value_t out_cache;
};

static int v85xxp_gpio_pin_configure(const struct device *dev,
				     gpio_pin_t pin,
				     gpio_flags_t flags)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	struct v85xxp_gpio_data *data = dev->data;
	GPIO_InitType init = {0};
	uint16_t pin_mask;

	if (pin >= 16U) {
		return -EINVAL;
	}

	if ((flags & GPIO_SINGLE_ENDED) != 0U &&
	    (flags & GPIO_LINE_OPEN_DRAIN) == 0U) {
		return -ENOTSUP;
	}

	if ((flags & GPIO_INPUT) != 0U) {
		init.GPIO_Mode = GPIO_MODE_INPUT;
	} else if ((flags & GPIO_OUTPUT) != 0U) {
		init.GPIO_Mode = ((flags & GPIO_LINE_OPEN_DRAIN) != 0U) ?
			GPIO_MODE_OUTPUT_OD : GPIO_MODE_OUTPUT_CMOS;
	} else {
		return -ENOTSUP;
	}

	pin_mask = BIT(pin);
	init.GPIO_Pin = pin_mask;
	GPIOBToF_Init(cfg->base, &init);

	if ((flags & GPIO_OUTPUT_INIT_HIGH) != 0U) {
		cfg->base->DAT |= pin_mask;
		data->out_cache |= pin_mask;
	} else if ((flags & GPIO_OUTPUT_INIT_LOW) != 0U) {
		cfg->base->DAT &= ~pin_mask;
		data->out_cache &= ~pin_mask;
	}

	return 0;
}

static int v85xxp_gpio_port_get_raw(const struct device *dev,
				    gpio_port_value_t *value)
{
	const struct v85xxp_gpio_config *cfg = dev->config;

	*value = cfg->base->STS;
	return 0;
}

static int v85xxp_gpio_port_set_masked_raw(const struct device *dev,
					   gpio_port_pins_t mask,
					   gpio_port_value_t value)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	struct v85xxp_gpio_data *data = dev->data;
	uint16_t out = (uint16_t)data->out_cache;

	out = (out & ~mask) | ((uint16_t)value & mask);
	cfg->base->DAT = out;
	data->out_cache = out;
	return 0;
}

static int v85xxp_gpio_port_set_bits_raw(const struct device *dev,
					 gpio_port_pins_t pins)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	struct v85xxp_gpio_data *data = dev->data;

	cfg->base->DAT |= (uint16_t)pins;
	data->out_cache = cfg->base->DAT;
	return 0;
}

static int v85xxp_gpio_port_clear_bits_raw(const struct device *dev,
					   gpio_port_pins_t pins)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	struct v85xxp_gpio_data *data = dev->data;

	cfg->base->DAT &= ~((uint16_t)pins);
	data->out_cache = cfg->base->DAT;
	return 0;
}

static int v85xxp_gpio_port_toggle_bits(const struct device *dev,
					gpio_port_pins_t pins)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	struct v85xxp_gpio_data *data = dev->data;

	cfg->base->DAT ^= (uint16_t)pins;
	data->out_cache = cfg->base->DAT;
	return 0;
}

static int v85xxp_gpio_pin_interrupt_configure(const struct device *dev,
					       gpio_pin_t pin,
					       enum gpio_int_mode mode,
					       enum gpio_int_trig trig)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(pin);
	ARG_UNUSED(mode);
	ARG_UNUSED(trig);
	return -ENOTSUP;
}

static int v85xxp_gpio_get_config(const struct device *dev,
				  gpio_pin_t pin,
				  gpio_flags_t *flags)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	uint16_t pin_mask;

	if (pin >= 16U) {
		return -EINVAL;
	}

	pin_mask = BIT(pin);
	*flags = 0;

	if ((cfg->base->IE & pin_mask) != 0U) {
		*flags |= GPIO_INPUT;
	}
	if ((cfg->base->OEN & pin_mask) != 0U) {
		*flags |= GPIO_OUTPUT;
	}
	if ((cfg->base->ATT & pin_mask) != 0U) {
		*flags |= GPIO_LINE_OPEN_DRAIN | GPIO_SINGLE_ENDED;
	}

	return 0;
}

static int v85xxp_gpio_init(const struct device *dev)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	struct v85xxp_gpio_data *data = dev->data;

	MISC2->HCLKEN |= MISC2_HCLKEN_GPIO;
	data->out_cache = cfg->base->DAT;
	return 0;
}

static DEVICE_API(gpio, v85xxp_gpio_api) = {
	.pin_configure = v85xxp_gpio_pin_configure,
	.port_get_raw = v85xxp_gpio_port_get_raw,
	.port_set_masked_raw = v85xxp_gpio_port_set_masked_raw,
	.port_set_bits_raw = v85xxp_gpio_port_set_bits_raw,
	.port_clear_bits_raw = v85xxp_gpio_port_clear_bits_raw,
	.port_toggle_bits = v85xxp_gpio_port_toggle_bits,
	.pin_interrupt_configure = v85xxp_gpio_pin_interrupt_configure,
	.get_config = v85xxp_gpio_get_config,
};

#define V85XXP_GPIO_INIT(inst) \
	static const struct v85xxp_gpio_config v85xxp_gpio_cfg_##inst = { \
		.common = { \
			.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_INST(inst), \
		}, \
		.base = (GPIO_Type *)DT_INST_REG_ADDR(inst), \
	}; \
	static struct v85xxp_gpio_data v85xxp_gpio_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_gpio_init, NULL, \
			      &v85xxp_gpio_data_##inst, &v85xxp_gpio_cfg_##inst, \
			      PRE_KERNEL_1, CONFIG_GPIO_INIT_PRIORITY, \
			      &v85xxp_gpio_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_GPIO_INIT)
