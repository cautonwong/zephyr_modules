/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_flash_controller

#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include <soc.h>
#include <string.h>
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

        for (uint32_t i = 0; i < num_pages; i++) {
                if (FLASH_PageErase(FLASH0, start_addr + (i * 1024)) != 0) {
                        return -EIO;
                }
        }
        return 0;
}

static int flash_v32f20x_write(const struct device *dev, off_t offset, const void *data, size_t len)
{
        uint32_t *src = (uint32_t *)data;
        uint32_t dest = (uint32_t)offset;
        uint32_t count = len / 4;

        if (FLASH_ProgramWord(FLASH0, dest, src, count) != 0) {
                return -EIO;
        }

        return 0;
}

static const struct flash_parameters *flash_v32f20x_get_parameters(const struct device *dev)
{
        return &flash_v32f20x_parameters;
}

#if defined(CONFIG_FLASH_PAGE_LAYOUT)
static const struct flash_pages_layout flash_v32f20x_pages_layout = {
        .pages_count = 2304, /* 2.25MB / 1KB */
        .pages_size = 1024,
};

static void flash_v32f20x_pages_layout_get(const struct device *dev,
                                          const struct flash_pages_layout **layout,
                                          size_t *layout_size)
{
        *layout = &flash_v32f20x_pages_layout;
        *layout_size = 1;
}
#endif /* CONFIG_FLASH_PAGE_LAYOUT */

static DEVICE_API(flash, flash_v32f20x_api) = {
        .read = flash_v32f20x_read,
        .write = flash_v32f20x_write,
        .erase = flash_v32f20x_erase,
        .get_parameters = flash_v32f20x_get_parameters,
#if defined(CONFIG_FLASH_PAGE_LAYOUT)
        .page_layout = flash_v32f20x_pages_layout_get,
#endif
};

static int flash_v32f20x_init(const struct device *dev)
{
        return 0;
}

DEVICE_DT_INST_DEFINE(0, flash_v32f20x_init, NULL, NULL, NULL, POST_KERNEL, 50, &flash_v32f20x_api);
