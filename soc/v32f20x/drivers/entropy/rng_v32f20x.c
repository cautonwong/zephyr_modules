/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_rng

#include <zephyr/kernel.h>
#include <zephyr/drivers/entropy.h>
#include <soc.h>
#include <lib_rng.h>

struct rng_v32f20x_config {
	RNG_Type *regs;
};

static int rng_v32f20x_get_entropy(const struct device *dev,
				   uint8_t *buffer,
				   uint16_t length)
{
	const struct rng_v32f20x_config *config = dev->config;
	uint32_t random_val;
	uint16_t i;

	for (i = 0; i < length; i++) {
		/* RNG_GetRandomNumber returns a 32-bit value */
		if ((i % 4) == 0) {
			/* Start new conversion if needed or wait for status */
			random_val = RNG_GetRandomNumber(config->regs);
		}
		buffer[i] = (uint8_t)(random_val >> ((i % 4) * 8));
	}

	return 0;
}

static const struct entropy_driver_api rng_v32f20x_api = {
	.get_entropy = rng_v32f20x_get_entropy,
};

static int rng_v32f20x_init(const struct device *dev)
{
	const struct rng_v32f20x_config *config = dev->config;

	RNG_Cmd(config->regs, ENABLE);
	return 0;
}

#define RNG_V32F20X_INIT(n)                                                    \
	static const struct rng_v32f20x_config rng_v32f20x_config_##n = {          \
		.regs = (RNG_Type *)DT_INST_REG_ADDR(n),                               \
	};                                                                         \
	DEVICE_DT_INST_DEFINE(n, rng_v32f20x_init, NULL, NULL,                     \
			      &rng_v32f20x_config_##n, PRE_KERNEL_1,               \
			      CONFIG_ENTROPY_INIT_PRIORITY, &rng_v32f20x_api);

DT_INST_FOREACH_STATUS_OKAY(RNG_V32F20X_INIT)
