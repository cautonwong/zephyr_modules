/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_flash_controller

#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include <soc.h>
#include "lib_flash.h"

struct flash_v32f20x_config {
	uintptr_t base;
};

static const struct flash_parameters flash_v32f20x_parameters = {
	.write_block_size = 4,
	.erase_value = 0xff,
};

static int flash_v32f20x_read(const struct device *dev, off_t offset, void *data, size_t len)
{
	/* Memory-mapped read */
	memcpy(data, (void *)(offset + 0x08000000), len);
	return 0;
}

static int flash_v32f20x_erase(const struct device *dev, off_t offset, size_t len)
{
	uint32_t num_pages = len / 1024;
	uint32_t start_addr = (uint32_t)offset;

	FLASH_Unlock();
	for (uint32_t i = 0; i < num_pages; i++) {
		if (FLASH_ErasePage(start_addr + (i * 1024)) != FLASH_COMPLETE) {
			FLASH_Lock();
			return -EIO;
		}
	}
	FLASH_Lock();
	return 0;
}

static int flash_v32f20x_write(const struct device *dev, off_t offset, const void *data, size_t len)
{
	uint32_t *src = (uint32_t *)data;
	uint32_t dest = (uint32_t)offset;
	uint32_t count = len / 4;

	FLASH_Unlock();
	for (uint32_t i = 0; i < count; i++) {
		if (FLASH_ProgramWord(dest + (i * 4), src[i]) != FLASH_COMPLETE) {
			FLASH_Lock();
			return -EIO;
		}
	}
	FLASH_Lock();
	return 0;
}

static const struct flash_parameters *flash_v32f20x_get_parameters(const struct device *dev)
{
	return &flash_v32f20x_parameters;
}

static DEVICE_API(flash, flash_v32f20x_api) = {
	.read = flash_v32f20x_read,
	.write = flash_v32f20x_write,
	.erase = flash_v32f20x_erase,
	.get_parameters = flash_v32f20x_get_parameters,
};

static int flash_v32f20x_init(const struct device *dev)
{
	return 0;
}

DEVICE_DT_INST_DEFINE(0, flash_v32f20x_init, NULL, NULL, NULL, POST_KERNEL, 50, &flash_v32f20x_api);
