/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_MODULES_SOC_V32F20X_PINCTRL_SOC_H_
#define ZEPHYR_MODULES_SOC_V32F20X_PINCTRL_SOC_H_

#include <zephyr/sys/util.h>
#include <zephyr/types.h>

/**
 * @brief Vango pinctrl SoC pin configuration
 */
typedef struct pinctrl_soc_pin {
	uint32_t pinmux;
	bool bias_pull_up;
	bool bias_pull_down;
	bool drive_open_drain;
} pinctrl_soc_pin_t;

/**
 * @brief Utility macro to initialize a pin configuration.
 * Vango DTS structure uses groups (e.g. group1) inside states.
 */
#define Z_PINCTRL_STATE_PIN_INIT(node_id, prop, idx)				\
	{									\
		.pinmux = DT_PROP_BY_IDX(node_id, prop, idx),			\
		.bias_pull_up = DT_PROP_OR(node_id, bias_pull_up, 0),		\
		.bias_pull_down = DT_PROP_OR(node_id, bias_pull_down, 0),	\
		.drive_open_drain = DT_PROP_OR(node_id, drive_open_drain, 0),	\
	},

/**
 * @brief Utility macro to initialize a state from a pin configuration.
 * Scans children of the state node (groups) and processes their pinmux properties.
 */
#define Z_PINCTRL_STATE_PINS_INIT(node_id, prop)				\
	{DT_FOREACH_CHILD_VARGS(node_id, DT_FOREACH_PROP_ELEM, pinmux, Z_PINCTRL_STATE_PIN_INIT)}

#endif /* ZEPHYR_MODULES_SOC_V32F20X_PINCTRL_SOC_H_ */
