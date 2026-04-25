/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_VANGO_V85XXP_PINCTRL_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_VANGO_V85XXP_PINCTRL_H_

/* UART0 Pinmux Definitions (Based on HAL lib_gpio.h) */
#define V85XXP_PIN_UART0_TX  1 /* Port A/B/C/D/E/F specific ID */
#define V85XXP_PIN_UART0_RX  2

/* GPIO Flag Definitions */
#define V85XXP_GPIO_POS_BIT  (1 << 31)

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_VANGO_V85XXP_PINCTRL_H_ */
