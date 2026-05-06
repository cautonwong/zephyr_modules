/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/pinctrl.h>
#include <zephyr/dt-bindings/pinctrl/vango-v85xxp-pinctrl.h>
#include <soc.h>
#include <lib_gpio.h>

/*
 * Pinmux Encoding (from vango-v85xxp-pinctrl.h):
 * [0:15]  AF Mask / Bit Pattern
 * [16:23] Pin Number (0-15)
 * [24:31] Port ID (0-5)
 */

int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt, uintptr_t reg)
{
	ARG_UNUSED(reg);

	for (uint8_t i = 0; i < pin_cnt; i++) {
		uint32_t pinmux = pins[i].pinmux;
		uint32_t port = (pinmux >> 24) & 0xFF;
		uint32_t af_mask = pinmux & 0xFFFF;

		if (port == V85XXP_PORT_A) {
			/* PMUIO uses GPIOA_AFConfig */
			GPIOA_AFConfig(af_mask, ENABLE);
		} else if (port >= V85XXP_PORT_B && port <= V85XXP_PORT_F) {
			/* AHB GPIOs use GPIOBToF_AFConfig */
			/* Note: HAL takes GPIO_Type* which we can derive from port ID */
			GPIO_Type *gpio_base = (GPIO_Type *)(0x40000020 + ((port - 1) * 0x20));
			GPIOBToF_AFConfig(gpio_base, af_mask, ENABLE);
		}
	}
	return 0;
}
