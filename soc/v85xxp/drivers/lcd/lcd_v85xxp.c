/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 *
 * V85XXP Segment LCD Driver
 *
 * The V85XXP LCD controller drives static segment displays with
 * 4/6/8 COM multiplexing. Zephyr's display subsystem targets
 * framebuffer-based graphical displays, so this driver provides
 * a SoC-specific API for segment control.
 */

#define DT_DRV_COMPAT v85xxp_lcd

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/pm/device.h>
#include <soc.h>
#include <lib_lcd.h>
#include <lib_pmu.h>

/* Public API for V85XXP segment LCD */
#include <zephyr/drivers/misc/v85xxp_lcd.h>

struct v85xxp_lcd_config {
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	uint32_t dtype;   /* 4COM, 6COM, 8COM */
	uint32_t drv;     /* driving resistance */
	uint32_t freq;    /* scan frequency */
	uint32_t bias;    /* bias selection */
	uint32_t voltage; /* VLCD voltage selection */
};

static int v85xxp_lcd_init(const struct device *dev)
{
	const struct v85xxp_lcd_config *cfg = dev->config;
	LCD_InitType init;
	LCD_IOInitType io_init = {0};
	int ret;

	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) {
		return ret;
	}

	LCD_DeInit();
	LCD_StructInit(&init);

	/* Apply DTS-configured parameters */
	init.Type = cfg->dtype;
	init.Drv  = cfg->drv;
	init.FRQ  = cfg->freq;
	LCD_Init(&init);

	/* Configure bias mode */
	LCD_BiasModeConfig(cfg->bias);

	/* Configure VLCD voltage */
	LCD_VoltageConfig(cfg->voltage);

	/* Enable all segment and COM pins */
	io_init.SegCtrl0 = 0xFFFFFFFF;
	io_init.SegCtrl1 = 0xFFFFFFFF;
	io_init.COMMode  = (cfg->dtype == LCD_TYPE_4COM) ? 0xFU :
			   (cfg->dtype == LCD_TYPE_6COM) ? 0x3FU : 0xFFU;
	LCD_Cmd(&io_init, ENABLE);

	return 0;
}

#ifdef CONFIG_PM_DEVICE
static int v85xxp_lcd_pm_action(const struct device *dev,
				enum pm_device_action action)
{
	switch (action) {
	case PM_DEVICE_ACTION_SUSPEND:
		PMU_LCDPWER_OFF;
		LCD_Cmd(NULL, DISABLE);
		break;
	case PM_DEVICE_ACTION_RESUME:
		LCD_Cmd(NULL, ENABLE);
		break;
	default:
		return -ENOTSUP;
	}
	return 0;
}
#endif

/* Custom segment LCD API implementation */

static void v85xxp_lcd_update_data(const struct device *dev, uint8_t idx, uint32_t data)
{
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

static uint32_t v85xxp_lcd_get_data(const struct device *dev, uint8_t idx)
{
	if (idx < 16) {
		return *((volatile uint32_t *)(&LCD->DATA0 + idx));
	}
	return 0;
}

static int v85xxp_lcd_enable(const struct device *dev, bool enable)
{
	LCD_Cmd(NULL, enable ? ENABLE : DISABLE);
	return 0;
}

static const struct v85xxp_lcd_driver_api v85xxp_lcd_api = {
	.update_data = v85xxp_lcd_update_data,
	.clear       = v85xxp_lcd_clear,
	.get_data    = v85xxp_lcd_get_data,
	.enable      = v85xxp_lcd_enable,
};

#define V85XXP_LCD_INIT(inst) \
	static const struct v85xxp_lcd_config v85xxp_lcd_cfg_##inst = { \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
		.dtype    = DT_INST_PROP_OR(inst, lcd_type, 0), \
		.drv      = DT_INST_PROP_OR(inst, lcd_drv, 0), \
		.freq     = DT_INST_PROP_OR(inst, lcd_freq, 1), \
		.bias     = DT_INST_PROP_OR(inst, lcd_bias, 0), \
		.voltage  = DT_INST_PROP_OR(inst, lcd_voltage, 0), \
	}; \
	PM_DEVICE_DT_INST_DEFINE(inst, v85xxp_lcd_pm_action); \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_lcd_init, \
			      PM_DEVICE_DT_INST_GET(inst), \
			      NULL, &v85xxp_lcd_cfg_##inst, \
			      POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY, \
			      &v85xxp_lcd_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_LCD_INIT)
