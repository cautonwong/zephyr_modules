/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_flash

#include <zephyr/kernel.h>
#include <zephyr/drivers/flash.h>
#include <soc.h>
#include <lib_flash.h>

struct flash_v32f20x_data {
	struct k_sem sem;
};

static const struct flash_parameters flash_v32f20x_parameters = {
	.write_block_size = 4,
	.erase_value = 0xff,
};

static int flash_v32f20x_read(const struct device *dev, off_t offset,
			      void *data, size_t len)
{
	/* Internal flash is memory mapped */
	memcpy(data, (void *)(DT_INST_REG_ADDR(0) + offset), len);
	return 0;
}

static int flash_v32f20x_write(const struct device *dev, off_t offset,
			       const void *data, size_t len)
{
	struct flash_v32f20x_data *dev_data = dev->data;
	int ret = 0;

	k_sem_take(&dev_data->sem, K_FOREVER);

	/* Vango HAL: Flash Program */
	if (FLASH_Program(DT_INST_REG_ADDR(0) + offset, (uint32_t *)data, len / 4) != SUCCESS) {
		ret = -EIO;
	}

	k_sem_give(&dev_data->sem);
	return ret;
}

static int flash_v32f20x_erase(const struct device *dev, off_t offset,
			       size_t size)
{
	struct flash_v32f20x_data *dev_data = dev->data;
	int ret = 0;

	k_sem_take(&dev_data->sem, K_FOREVER);

	/* Vango HAL: Flash Sector Erase (assuming 4KB sectors) */
	uint32_t num_sectors = size / 4096;
	for (uint32_t i = 0; i < num_sectors; i++) {
		if (FLASH_SectorErase(DT_INST_REG_ADDR(0) + offset + (i * 4096)) != SUCCESS) {
			ret = -EIO;
			break;
		}
	}

	k_sem_give(&dev_data->sem);
	return ret;
}

static const struct flash_parameters *
flash_v32f20x_get_parameters(const struct device *dev)
{
	ARG_UNUSED(dev);
	return &flash_v32f20x_parameters;
}

static const struct flash_driver_api flash_v32f20x_api = {
	.read = flash_v32f20x_read,
	.write = flash_v32f20x_write,
	.erase = flash_v32f20x_erase,
	.get_parameters = flash_v32f20x_get_parameters,
};

static int flash_v32f20x_init(const struct device *dev)
{
	struct flash_v32f20x_data *data = dev->data;
	k_sem_init(&data->lock, 1, 1);
	FLASH_Unlock();
	return 0;
}

static struct flash_v32f20x_data flash_v32f20x_data_0;

DEVICE_DT_INST_DEFINE(0, flash_v32f20x_init, NULL,
		      &flash_v32f20x_data_0, NULL, POST_KERNEL,
		      CONFIG_FLASH_INIT_PRIORITY, &flash_v32f20x_api);
