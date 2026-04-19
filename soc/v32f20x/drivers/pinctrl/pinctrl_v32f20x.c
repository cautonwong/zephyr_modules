/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/pinctrl.h>
#include <zephyr/dt-bindings/pinctrl/vango-v32f20x-pinctrl.h>
#include <soc.h>
#include <lib_gpio.h>

/* Helper to get GPIO base from port ID */
static GPIO_Type *get_gpio_base(uint32_t port)
{
	switch (port) {
	case VANGO_PORT_A: return GPIOA;
	case VANGO_PORT_B: return GPIOB;
	case VANGO_PORT_C: return GPIOC;
	case VANGO_PORT_D: return GPIOD;
	case VANGO_PORT_E: return GPIOE;
	case VANGO_PORT_F: return GPIOF;
	case VANGO_PORT_G: return GPIOG;
	case VANGO_PORT_H: return GPIOH;
	case VANGO_PORT_I: return GPIOI;
	default: return NULL;
	}
}

int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt,
			   uintptr_t reg)
{
	ARG_UNUSED(reg);

	for (uint8_t i = 0; i < pin_cnt; i++) {
		uint32_t pinmux = pins[i].pinmux;
		uint32_t port_id = VANGO_PINMUX_PORT(pinmux);
		uint32_t af = VANGO_PINMUX_AF(pinmux);
		uint32_t pin = VANGO_PINMUX_PIN(pinmux);
		
		GPIO_Type *gpio = get_gpio_base(port_id);
		if (!gpio) return -EINVAL;

		/* 1. Apply AF configuration */
		GPIO_PinAFConfig(gpio, pin, af);
		
		/* 2. Configure GPIO Mode and Attributes */
		GPIO_InitType init_struct;
		GPIO_StructInit(&init_struct);
		init_struct.GPIO_Pin = BIT(pin);
		init_struct.GPIO_Mode = GPIO_Mode_AF;
		init_struct.GPIO_Speed = GPIO_Speed_50MHz;

		/* Pull-up / Pull-down */
		if (pins[i].bias_pull_up) {
			init_struct.GPIO_PuPd = GPIO_PuPd_UP;
		} else if (pins[i].bias_pull_down) {
			init_struct.GPIO_PuPd = GPIO_PuPd_DOWN;
		} else {
			init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		}

		/* Open-Drain */
		if (pins[i].drive_open_drain) {
			init_struct.GPIO_OType = GPIO_OType_OD;
		} else {
			init_struct.GPIO_OType = GPIO_OType_PP;
		}
		
		GPIO_Init(gpio, &init_struct);
	}

	return 0;
}
