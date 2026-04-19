/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_flash_controller

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>

#include <soc.h>
#include "lib_flash.h"

#define V85XXP_FLASH_SIZE       DT_REG_SIZE(DT_NODELABEL(flash0))
#define V85XXP_FLASH_WRITE_BLK  4U
#define V85XXP_FLASH_ERASE_BLK  1024U

struct v85xxp_flash_config {
	FLASH_Type *base;
};

static const struct flash_parameters v85xxp_flash_parameters = {
	.write_block_size = V85XXP_FLASH_WRITE_BLK,
	.erase_value = 0xFF,
};

#if defined(CONFIG_FLASH_PAGE_LAYOUT)
static const struct flash_pages_layout v85xxp_flash_layout = {
	.pages_count = V85XXP_FLASH_SIZE / V85XXP_FLASH_ERASE_BLK,
	.pages_size = V85XXP_FLASH_ERASE_BLK,
};
#endif

static bool v85xxp_flash_bounds_ok(off_t offset, size_t len)
{
	if ((offset < 0) || ((size_t)offset > V85XXP_FLASH_SIZE)) {
		return false;
	}

	if (len > (V85XXP_FLASH_SIZE - (size_t)offset)) {
		return false;
	}

	return true;
}

static int v85xxp_flash_read(const struct device *dev, off_t offset, void *data, size_t len)
{
	ARG_UNUSED(dev);

	if (len == 0U) {
		return 0;
	}

	if ((data == NULL) || !v85xxp_flash_bounds_ok(offset, len)) {
		return -EINVAL;
	}

	memcpy(data, (const void *)(uintptr_t)offset, len);
	return 0;
}

static int v85xxp_flash_write(const struct device *dev, off_t offset,
			      const void *data, size_t len)
{
	ARG_UNUSED(dev);

	if (len == 0U) {
		return 0;
	}

	if ((data == NULL) || !v85xxp_flash_bounds_ok(offset, len)) {
		return -EINVAL;
	}

	if (((offset % V85XXP_FLASH_WRITE_BLK) != 0U) ||
	    ((len % V85XXP_FLASH_WRITE_BLK) != 0U)) {
		return -EINVAL;
	}

	FLASH_ProgramWord((uint32_t)offset, (uint32_t *)data, len / V85XXP_FLASH_WRITE_BLK);
	return 0;
}

static int v85xxp_flash_erase(const struct device *dev, off_t offset, size_t size)
{
	ARG_UNUSED(dev);
	off_t addr = offset;
	size_t remaining = size;

	if (size == 0U) {
		return 0;
	}

	if (!v85xxp_flash_bounds_ok(offset, size)) {
		return -EINVAL;
	}

	if (((offset % V85XXP_FLASH_ERASE_BLK) != 0U) ||
	    ((size % V85XXP_FLASH_ERASE_BLK) != 0U)) {
		return -EINVAL;
	}

	while (remaining > 0U) {
		FLASH_SectorErase((uint32_t)addr);
		addr += V85XXP_FLASH_ERASE_BLK;
		remaining -= V85XXP_FLASH_ERASE_BLK;
	}

	return 0;
}

static const struct flash_parameters *v85xxp_flash_get_parameters(const struct device *dev)
{
	ARG_UNUSED(dev);
	return &v85xxp_flash_parameters;
}

static int v85xxp_flash_get_size(const struct device *dev, uint64_t *size)
{
	ARG_UNUSED(dev);

	if (size == NULL) {
		return -EINVAL;
	}

	*size = V85XXP_FLASH_SIZE;
	return 0;
}

#if defined(CONFIG_FLASH_PAGE_LAYOUT)
static void v85xxp_flash_pages_layout(const struct device *dev,
				      const struct flash_pages_layout **layout,
				      size_t *layout_size)
{
	ARG_UNUSED(dev);
	*layout = &v85xxp_flash_layout;
	*layout_size = 1U;
}
#endif

static int v85xxp_flash_init(const struct device *dev)
{
	const struct v85xxp_flash_config *cfg = dev->config;

	ARG_UNUSED(cfg);
	FLASH_Init(FLASH_CSMODE_DISABLE);
	FLASH_CycleInit();
	return 0;
}

static DEVICE_API(flash, v85xxp_flash_api) = {
	.read = v85xxp_flash_read,
	.write = v85xxp_flash_write,
	.erase = v85xxp_flash_erase,
	.get_parameters = v85xxp_flash_get_parameters,
	.get_size = v85xxp_flash_get_size,
#if defined(CONFIG_FLASH_PAGE_LAYOUT)
	.page_layout = v85xxp_flash_pages_layout,
#endif
};

#define V85XXP_FLASH_INIT(inst) \
	static const struct v85xxp_flash_config v85xxp_flash_cfg_##inst = { \
		.base = (FLASH_Type *)DT_INST_REG_ADDR(inst), \
	}; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_flash_init, NULL, \
			      NULL, &v85xxp_flash_cfg_##inst, \
			      POST_KERNEL, CONFIG_FLASH_INIT_PRIORITY, \
			      &v85xxp_flash_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_FLASH_INIT)
