/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_pwm

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

#include <soc.h>
#include "lib_pwm.h"

struct v85xxp_pwm_config {
	PWM_Type *base;
	uint32_t clock_hz;
};

struct v85xxp_pwm_data {
	uint32_t period_cycles;
};

static int v85xxp_pwm_set_cycles(const struct device *dev,
				 uint32_t channel,
				 uint32_t period_cycles,
				 uint32_t pulse_cycles,
				 pwm_flags_t flags)
{
	const struct v85xxp_pwm_config *cfg = dev->config;
	struct v85xxp_pwm_data *data = dev->data;
	PWM_BaseInitType base_init;
	PWM_OCInitType oc_init;

	if (channel > 2U || period_cycles == 0U || period_cycles > 0xFFFFU) {
		return -EINVAL;
	}

	if (pulse_cycles > period_cycles || flags != 0U) {
		return -ENOTSUP;
	}

	PWM_BaseStructInit(&base_init);
	base_init.ClockSource = PWM_CLKSRC_APB;
	base_init.ClockDivision = PWM_CLKDIV_2;
	base_init.Mode = PWM_MODE_UPCOUNT;
	PWM_BaseInit(cfg->base, &base_init);

	PWM_OCStructInit(&oc_init);
	oc_init.Channel = channel;
	oc_init.Period = pulse_cycles;
	oc_init.OutMode = (pulse_cycles == 0U) ? PWM_OUTMOD_CONST : PWM_OUTMOD_RESET_SET;
	PWM_OCInit(cfg->base, &oc_init);

	PWM_CCRConfig(cfg->base, PWM_CHANNEL_0, period_cycles);
	PWM_OutputCmd(cfg->base, channel, ENABLE);

	data->period_cycles = period_cycles;
	return 0;
}

static int v85xxp_pwm_get_cycles_per_sec(const struct device *dev,
					 uint32_t channel,
					 uint64_t *cycles)
{
	const struct v85xxp_pwm_config *cfg = dev->config;

	ARG_UNUSED(channel);
	*cycles = cfg->clock_hz;
	return 0;
}

static int v85xxp_pwm_init(const struct device *dev)
{
	ARG_UNUSED(dev);
	return 0;
}

static DEVICE_API(pwm, v85xxp_pwm_api) = {
	.set_cycles = v85xxp_pwm_set_cycles,
	.get_cycles_per_sec = v85xxp_pwm_get_cycles_per_sec,
};

#define V85XXP_PWM_INIT(inst) \
	static const struct v85xxp_pwm_config v85xxp_pwm_cfg_##inst = { \
		.base = (PWM_Type *)DT_INST_REG_ADDR(inst), \
		.clock_hz = V85XXP_PCLK_CLOCK_HZ / 2U, \
	}; \
	static struct v85xxp_pwm_data v85xxp_pwm_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_pwm_init, NULL, \
			      &v85xxp_pwm_data_##inst, &v85xxp_pwm_cfg_##inst, \
			      POST_KERNEL, CONFIG_PWM_INIT_PRIORITY, \
			      &v85xxp_pwm_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_PWM_INIT)
