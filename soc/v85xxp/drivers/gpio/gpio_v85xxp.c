/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_gpio

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_utils.h>
#include <zephyr/drivers/clock_control.h>

#include <soc.h>
#include "lib_gpio.h"
#include "lib_clk.h"
#include "lib_pmu.h"

struct v85xxp_gpio_config {
	struct gpio_driver_config common;
	uintptr_t base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

struct v85xxp_gpio_data {
	struct gpio_driver_data common;
	sys_slist_t callbacks;
};

/* Port A uses PMUIO registers with a different register layout */
static inline bool is_pmuio(uintptr_t base)
{
	return (base >= 0x40014000 && base < 0x40015000);
}

static int v85xxp_gpio_pin_configure(const struct device *dev,
				     gpio_pin_t pin,
				     gpio_flags_t flags)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	GPIO_InitType init = {0};

	if (pin >= 16U) {
		return -EINVAL;
	}

	init.GPIO_Pin = BIT(pin);

	if ((flags & GPIO_INPUT) != 0U) {
		init.GPIO_Mode = GPIO_MODE_INPUT;
	} else if ((flags & GPIO_OUTPUT) != 0U) {
		if ((flags & GPIO_LINE_OPEN_DRAIN) != 0U) {
			init.GPIO_Mode = (flags & GPIO_INPUT) ? GPIO_MODE_INOUT_OD : GPIO_MODE_OUTPUT_OD;
		} else {
			init.GPIO_Mode = (flags & GPIO_INPUT) ? GPIO_MODE_INOUT_CMOS : GPIO_MODE_OUTPUT_CMOS;
		}
	} else if ((flags & GPIO_DISCONNECTED) != 0U) {
		init.GPIO_Mode = GPIO_MODE_FORBIDDEN;
	} else {
		return -ENOTSUP;
	}

	/* Port A (PMUIO) vs Port B-F use different init functions */
	if (is_pmuio(cfg->base)) {
		GPIOA_Init((GPIOA_Type *)cfg->base, &init);
	} else {
		GPIOBToF_Init((GPIO_Type *)cfg->base, &init);
	}

	/* Set initial output level */
	if ((flags & GPIO_OUTPUT) != 0U) {
		if ((flags & GPIO_OUTPUT_INIT_HIGH) != 0U) {
			if (is_pmuio(cfg->base)) {
				((GPIOA_Type *)cfg->base)->DAT |= BIT(pin);
			} else {
				((GPIO_Type *)cfg->base)->DAT |= BIT(pin);
			}
		} else if ((flags & GPIO_OUTPUT_INIT_LOW) != 0U) {
			if (is_pmuio(cfg->base)) {
				((GPIOA_Type *)cfg->base)->DAT &= ~BIT(pin);
			} else {
				((GPIO_Type *)cfg->base)->DAT &= ~BIT(pin);
			}
		}
	}

	return 0;
}

static int v85xxp_gpio_port_get_raw(const struct device *dev,
				    gpio_port_value_t *value)
{
	const struct v85xxp_gpio_config *cfg = dev->config;

	if (is_pmuio(cfg->base)) {
		*value = ((GPIOA_Type *)cfg->base)->STS;
	} else {
		*value = ((GPIO_Type *)cfg->base)->STS;
	}
	return 0;
}

static int v85xxp_gpio_port_set_masked_raw(const struct device *dev,
					   gpio_port_pins_t mask,
					   gpio_port_value_t value)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	uint32_t port_val;

	if (is_pmuio(cfg->base)) {
		port_val = ((GPIOA_Type *)cfg->base)->DAT;
		port_val = (port_val & ~mask) | (value & mask);
		((GPIOA_Type *)cfg->base)->DAT = (uint16_t)port_val;
	} else {
		port_val = ((GPIO_Type *)cfg->base)->DAT;
		port_val = (port_val & ~mask) | (value & mask);
		((GPIO_Type *)cfg->base)->DAT = (uint16_t)port_val;
	}
	return 0;
}

static int v85xxp_gpio_port_set_bits_raw(const struct device *dev,
					 gpio_port_pins_t pins)
{
	const struct v85xxp_gpio_config *cfg = dev->config;

	if (is_pmuio(cfg->base)) {
		((GPIOA_Type *)cfg->base)->DAT |= (uint16_t)pins;
	} else {
		((GPIO_Type *)cfg->base)->DAT |= (uint16_t)pins;
	}
	return 0;
}

static int v85xxp_gpio_port_clear_bits_raw(const struct device *dev,
					   gpio_port_pins_t pins)
{
	const struct v85xxp_gpio_config *cfg = dev->config;

	if (is_pmuio(cfg->base)) {
		((GPIOA_Type *)cfg->base)->DAT &= ~((uint16_t)pins);
	} else {
		((GPIO_Type *)cfg->base)->DAT &= ~((uint16_t)pins);
	}
	return 0;
}

static int v85xxp_gpio_port_toggle_bits(const struct device *dev,
					gpio_port_pins_t pins)
{
	const struct v85xxp_gpio_config *cfg = dev->config;

	if (is_pmuio(cfg->base)) {
		((GPIOA_Type *)cfg->base)->DAT ^= (uint16_t)pins;
	} else {
		((GPIO_Type *)cfg->base)->DAT ^= (uint16_t)pins;
	}
	return 0;
}

static int v85xxp_gpio_pin_interrupt_configure(const struct device *dev,
					       gpio_pin_t pin,
					       enum gpio_int_mode mode,
					       enum gpio_int_trig trig)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	uint32_t wakeup_event = IOA_DISABLE;

	if (!is_pmuio(cfg->base)) {
		return -ENOTSUP;
	}

	if (mode == GPIO_INT_MODE_DISABLED) {
		wakeup_event = IOA_DISABLE;
	} else if (mode == GPIO_INT_MODE_LEVEL) {
		wakeup_event = (trig == GPIO_INT_TRIG_HIGH) ? IOA_HIGH : IOA_LOW;
	} else if (mode == GPIO_INT_MODE_EDGE) {
		if (trig == GPIO_INT_TRIG_BOTH) {
			wakeup_event = IOA_EDGEBOTH;
		} else {
			wakeup_event = (trig == GPIO_INT_TRIG_HIGH) ? IOA_RISING : IOA_FALLING;
		}
	} else {
		return -ENOTSUP;
	}

	/* Configure PMU wakeup/interrupt for IOA */
	PMU_WakeUpPinConfig(BIT(pin), wakeup_event);

	/* Ensure PMU global interrupt for IOA is enabled */
	if (wakeup_event != IOA_DISABLE) {
		PMU_INTConfig(PMU_INT_IOAEN, ENABLE);
	}

	return 0;
}

static int v85xxp_gpio_manage_callback(const struct device *dev,
				       struct gpio_callback *callback,
				       bool set)
{
	struct v85xxp_gpio_data *data = dev->data;

	return gpio_manage_callback(&data->callbacks, callback, set);
}

static void v85xxp_pmu_isr(const struct device *dev)
{
	struct v85xxp_gpio_data *data = dev->data;
	uint16_t status;

	status = PMU_GetIOAAllINTStatus();
	if (status != 0) {
		/* Fire callbacks for Port A */
		gpio_fire_callbacks(&data->callbacks, dev, status);

		/* Clear processed interrupts */
		PMU_ClearIOAINTStatus(status);
	}
}

static int v85xxp_gpio_init(const struct device *dev)
{
	const struct v85xxp_gpio_config *cfg = dev->config;
	int ret;

	/* Enable peripheral clock */
	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) {
		return ret;
	}

	/* Port A (PMUIO) routes its interrupts through IRQ 0 (PMU) */
	if (is_pmuio(cfg->base)) {
		IRQ_CONNECT(DT_IRQN(DT_NODELABEL(pmu0)),
			    DT_IRQ(DT_NODELABEL(pmu0), priority),
			    v85xxp_pmu_isr, DEVICE_DT_GET(DT_NODELABEL(gpioa)), 0);
		irq_enable(DT_IRQN(DT_NODELABEL(pmu0)));
	}

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
	.manage_callback = v85xxp_gpio_manage_callback,
};

#define V85XXP_GPIO_INIT(inst) \
	static const struct v85xxp_gpio_config v85xxp_gpio_cfg_##inst = { \
		.common = { \
			.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_INST(inst), \
		}, \
		.base = DT_INST_REG_ADDR(inst), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, id), \
	}; \
	static struct v85xxp_gpio_data v85xxp_gpio_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_gpio_init, NULL, \
			      &v85xxp_gpio_data_##inst, &v85xxp_gpio_cfg_##inst, \
			      PRE_KERNEL_1, CONFIG_GPIO_INIT_PRIORITY, \
			      &v85xxp_gpio_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_GPIO_INIT)
