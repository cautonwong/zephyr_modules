/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_crc

#include <zephyr/kernel.h>
#include <zephyr/drivers/crc.h>
#include <soc.h>
#include <lib_crc.h>

/* Vango hardware CRC supports multiple polynomials */
static uint32_t crc_v32f20x_compute(const struct device *dev,
				    const uint8_t *data, size_t len,
				    uint32_t seed, const struct crc_config *config)
{
	/* Vango CRC HAL mapping */
	CRC_InitType init_struct;
	CRC_StructInit(&init_struct);

	/* Simplified mapping: Vango hardware usually supports CCITT, CRC32, etc. */
	CRC_Init(&init_struct);
	return CRC_CalcBlockCRC((uint8_t *)data, len);
}

/* Note: Zephyr doesn't have a standard CRC driver API in all versions, 
 * often it's provided as a utility. If implementing as a driver: 
 */
static int crc_v32f20x_init(const struct device *dev)
{
	/* Enable CRC clock */
	return 0;
}

DEVICE_DT_INST_DEFINE(0, crc_v32f20x_init, NULL, NULL, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY, NULL);
