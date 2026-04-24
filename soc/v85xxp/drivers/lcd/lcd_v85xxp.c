/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_lcd

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include "lib_lcd.h"

struct v85xxp_lcd_config {
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

/* Custom LCD API for V85XXP Segment Display */
struct v85xxp_lcd_api {
	void (*update_data)(const struct device *dev, uint8_t idx, uint32_t data);
	void (*clear)(const struct device *dev);
};

static void v85xxp_lcd_update_data(const struct device *dev, uint8_t idx, uint32_t data)
{
	/* V85XXP has data registers for segments. idx refers to DATA0, DATA1 etc. */
	if (idx < 16) {
		*((volatile uint32_t *)(&LCD->DATA0 + idx)) = data;
	}
}

static void v85xxp_lcd_clear(const struct device *dev)
{
	for (int i = 0; i < 16; i++) {
		*((volatile uint32_t *)(&LCD->DATA0 + i)) = 0;
	}
}

static const struct v85xxp_lcd_api lcd_api = {
	.update_data = v85xxp_lcd_update_data,
	.clear = v85xxp_lcd_clear,
};

static int v85xxp_lcd_init(const struct device *dev)
{
	const struct v85xxp_lcd_config *cfg = dev->config;
	LCD_InitType init;
	LCD_IOInitType io_init = {0};
	int ret;

	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) return ret;

	LCD_DeInit();
	LCD_StructInit(&init);
	init.Type = LCD_TYPE_4COM;
	init.Drv = LCD_DRV_300;
	init.FRQ = LCD_FRQ_128H;
	LCD_Init(&init);

	io_init.SegCtrl0 = 0xFFFFFFFF;
	io_init.SegCtrl1 = 0xFFFFFFFF;
	io_init.COMMode = 0xF; 
	LCD_Cmd(&io_init, ENABLE);

	return 0;
}

#define V85XXP_LCD_INIT(inst) \
	static const struct v85xxp_lcd_config v85xxp_lcd_cfg_##inst = { \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
	}; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_lcd_init, NULL, \
			      NULL, &v85xxp_lcd_cfg_##inst, \
			      POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY, \
			      &lcd_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_LCD_INIT)
