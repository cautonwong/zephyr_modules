/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_pmu

#include <zephyr/device.h>
#include <soc.h>
#include "lib_pmu.h"

struct pmu_v32f20x_config {
	uintptr_t base;
};

static int pmu_v32f20x_init(const struct device *dev)
{
	/* PMU is always clocked and ready after power-on.
	 * We initialize default wakeup sources here.
	 */
	PMU_WKUINTConfig(SLEEP_CORE_CM33, ENABLE);
	PMU_WKUINTConfig(SLEEP_CORE_CM0, ENABLE);
	
	return 0;
}

#define PMU_V32F20X_INIT(n) \
	static const struct pmu_v32f20x_config pmu_v32f20x_config_##n = { \
		.base = DT_INST_REG_ADDR(n), \
	}; \
	DEVICE_DT_INST_DEFINE(n, pmu_v32f20x_init, NULL, \
			      NULL, &pmu_v32f20x_config_##n, \
			      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(PMU_V32F20X_INIT)
