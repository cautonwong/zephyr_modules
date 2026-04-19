/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_pwm

#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/pinctrl.h>
#include <soc.h>
#include <lib_bpwm.h>

struct pwm_v32f20x_config {
	BPWM_Type *regs;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct pinctrl_dev_config *pincfg;
};

static int pwm_v32f20x_set_cycles(const struct device *dev, uint32_t channel,
				  uint32_t period_cycles, uint32_t pulse_cycles,
				  pwm_flags_t flags)
{
	const struct pwm_v32f20x_config *config = dev->config;

	if (channel >= 4) { /* BPWM usually has 4 channels */
		return -EINVAL;
	}

	/* Vango BPWM Configuration */
	BPWM_SetPeriod(config->regs, period_cycles);
	BPWM_SetCompare(config->regs, channel, pulse_cycles);

	if (flags & PWM_POLARITY_INVERTED) {
		/* Add polarity inversion logic if supported by HAL */
	}

	BPWM_Cmd(config->regs, ENABLE);
	return 0;
}

static int pwm_v32f20x_get_cycles_per_sec(const struct device *dev,
					  uint32_t channel, uint64_t *cycles)
{
	const struct pwm_v32f20x_config *config = dev->config;
	uint32_t rate;

	if (clock_control_get_rate(config->clock_dev, config->clock_subsys, &rate) != 0) {
		return -EIO;
	}

	*cycles = (uint64_t)rate;
	return 0;
}

static const struct pwm_driver_api pwm_v32f20x_api = {
	.set_cycles = pwm_v32f20x_set_cycles,
	.get_cycles_per_sec = pwm_v32f20x_get_cycles_per_sec,
};

static int pwm_v32f20x_init(const struct device *dev)
{
	const struct pwm_v32f20x_config *config = dev->config;
	int ret;

	ret = pinctrl_apply_state(config->pincfg, PINCTRL_STATE_DEFAULT);
	if (ret < 0) return ret;

	clock_control_on(config->clock_dev, config->clock_subsys);

	BPWM_InitType init_struct;
	BPWM_StructInit(&init_struct);
	BPWM_Init(config->regs, &init_struct);

	return 0;
}

#define PWM_V32F20X_INIT(n)                                                    \
	PINCTRL_DT_INST_DEFINE(n);                                                 \
	static const struct pwm_v32f20x_config pwm_v32f20x_config_##n = {          \
		.regs = (BPWM_Type *)DT_INST_REG_ADDR(n),                              \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),                   \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, id),    \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(n),                           \
	};                                                                         \
	DEVICE_DT_INST_DEFINE(n, pwm_v32f20x_init, NULL, NULL,                     \
			      &pwm_v32f20x_config_##n, POST_KERNEL,                \
			      CONFIG_PWM_INIT_PRIORITY, &pwm_v32f20x_api);

DT_INST_FOREACH_STATUS_OKAY(PWM_V32F20X_INIT)
