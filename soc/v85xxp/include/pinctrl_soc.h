/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_MODULES_SOC_V85XXP_PINCTRL_SOC_H_
#define ZEPHYR_MODULES_SOC_V85XXP_PINCTRL_SOC_H_

#include <zephyr/sys/util.h>
#include <zephyr/devicetree.h>
#include <zephyr/types.h>

/**
 * @brief V85XXP Pinctrl pin type
 */
typedef struct {
	uint32_t pinmux; /* Alternate function / pinmux encoding */
	bool bias_pull_up;
	bool bias_pull_down;
} pinctrl_soc_pin_t;

#define Z_PINCTRL_STATE_PIN_INIT(node_id, prop, idx) \
	{ \
		.pinmux = DT_PROP_BY_IDX(node_id, prop, idx), \
		.bias_pull_up = DT_PROP_OR(node_id, bias_pull_up, 0), \
		.bias_pull_down = DT_PROP_OR(node_id, bias_pull_down, 0), \
	},

#define Z_PINCTRL_STATE_PINS_INIT(node_id, prop) \
	{ DT_FOREACH_CHILD_VARGS(node_id, DT_FOREACH_PROP_ELEM, pinmux, Z_PINCTRL_STATE_PIN_INIT) }

#endif /* ZEPHYR_MODULES_SOC_V85XXP_PINCTRL_SOC_H_ */
