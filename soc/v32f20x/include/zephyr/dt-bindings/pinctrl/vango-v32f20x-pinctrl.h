/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_MODULES_SOC_V32F20X_DT_BINDINGS_PINCTRL_H_
#define ZEPHYR_MODULES_SOC_V32F20X_DT_BINDINGS_PINCTRL_H_

/* Port IDs */
#define VANGO_PORT_A 0
#define VANGO_PORT_B 1
#define VANGO_PORT_C 2
#define VANGO_PORT_D 3
#define VANGO_PORT_E 4
#define VANGO_PORT_F 5
#define VANGO_PORT_G 6
#define VANGO_PORT_H 7
#define VANGO_PORT_I 8

/**
 * @brief Pinmux configuration bitfield
 * [0:3]   Alternate function
 * [4:7]   Pin number (0-15)
 * [8:11]  Port ID (0-8)
 */
#define VANGO_PINMUX(port, pin, af) \
	(((port) << 8) | ((pin) << 4) | (af))

#define VANGO_PINMUX_PORT(pinmux) (((pinmux) >> 8) & 0xF)
#define VANGO_PINMUX_PIN(pinmux)  (((pinmux) >> 4) & 0xF)
#define VANGO_PINMUX_AF(pinmux)   ((pinmux) & 0xF)

#endif /* ZEPHYR_MODULES_SOC_V32F20X_DT_BINDINGS_PINCTRL_H_ */
