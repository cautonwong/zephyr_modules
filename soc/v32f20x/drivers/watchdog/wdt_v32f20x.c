/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_wdt

#include <zephyr/kernel.h>
#include <zephyr/drivers/watchdog.h>
#include <soc.h>
#include <lib_wdt.h>

struct wdt_v32f20x_config {
        WDT_Type *regs;
};

struct wdt_v32f20x_data {
        wdt_callback_t callback;
        uint32_t timeout;
};

static int wdt_v32f20x_setup(const struct device *dev, uint8_t options)
{
        const struct wdt_v32f20x_config *config = dev->config;

        WDT_Cmd(config->regs, ENABLE);
        return 0;
}

static int wdt_v32f20x_disable(const struct device *dev)
{
        const struct wdt_v32f20x_config *config = dev->config;

        WDT_Cmd(config->regs, DISABLE);
        return 0;
}

static int wdt_v32f20x_install_timeout(const struct device *dev,
                                        const struct wdt_timeout_cfg *cfg)
{
        const struct wdt_v32f20x_config *config = dev->config;

        if (cfg->window.min != 0U || cfg->window.max == 0U) {
                return -EINVAL;
        }

        /* Map ms to watchdog periods */
        uint32_t period = WDT_PERIOD_16S;
        if (cfg->window.max <= 2000) {
            period = WDT_PERIOD_2S;
        } else if (cfg->window.max <= 4000) {
            period = WDT_PERIOD_4S;
        } else if (cfg->window.max <= 8000) {
            period = WDT_PERIOD_8S;
        }

        WDT_PeriodConfig(config->regs, period);
        WDT_WinValueConfig(config->regs, 0xFFFF); /* Disable window */
        
        return 0;
}

static int wdt_v32f20x_feed(const struct device *dev, int channel_id)
{
        const struct wdt_v32f20x_config *config = dev->config;
        ARG_UNUSED(channel_id);

        WDT_Clear(config->regs);
        return 0;
}

static const struct wdt_driver_api wdt_v32f20x_api = {
        .setup = wdt_v32f20x_setup,
        .disable = wdt_v32f20x_disable,
        .install_timeout = wdt_v32f20x_install_timeout,
        .feed = wdt_v32f20x_feed,
};

static int wdt_v32f20x_init(const struct device *dev)
{
        return 0;
}

#define WDT_V32F20X_INIT(n)                                                    \
        static const struct wdt_v32f20x_config wdt_v32f20x_config_##n = {          \
                .regs = (WDT_Type *)DT_INST_REG_ADDR(n),                               \
        };                                                                         \
        static struct wdt_v32f20x_data wdt_v32f20x_data_##n;                       \
        DEVICE_DT_INST_DEFINE(n, wdt_v32f20x_init, NULL, &wdt_v32f20x_data_##n,      \
                              &wdt_v32f20x_config_##n, PRE_KERNEL_1,               \
                              CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &wdt_v32f20x_api);

DT_INST_FOREACH_STATUS_OKAY(WDT_V32F20X_INIT)
