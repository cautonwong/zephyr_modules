/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_spi

#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/pm/device.h>
#include <zephyr/pm/device_runtime.h>
#include <soc.h>
#include "lib_spi.h"

struct spi_v32f20x_config {
    SPI_Type *base;
    const struct pinctrl_dev_config *pcfg;
};

struct spi_v32f20x_data {
    struct spi_context ctx;
};

static int spi_v32f20x_transceive(const struct device *dev,
                                 const struct spi_config *config,
                                 const struct spi_buf_set *tx_bufs,
                                 const struct spi_buf_set *rx_bufs)
{
    /* SPI transceive implementation */
    return 0;
}

static int spi_v32f20x_release(const struct device *dev,
                              const struct spi_config *config)
{
    return 0;
}

static const struct spi_driver_api spi_v32f20x_api = {
    .transceive = spi_v32f20x_transceive,
    .release = spi_v32f20x_release,
};

#ifdef CONFIG_PM_DEVICE
static int spi_v32f20x_pm_action(const struct device *dev, enum pm_device_action action)
{
    const struct spi_v32f20x_config *config = dev->config;
    int ret;

    switch (action) {
    case PM_DEVICE_ACTION_SUSPEND:
        ret = pinctrl_apply_state(config->pcfg, PINCTRL_STATE_SLEEP);
        if (ret == -ENOENT) ret = 0;
        SPI_Ctrl(config->base, DISABLE);
        break;
    case PM_DEVICE_ACTION_RESUME:
        ret = pinctrl_apply_state(config->pcfg, PINCTRL_STATE_DEFAULT);
        SPI_Ctrl(config->base, ENABLE);
        break;
    default:
        return -ENOTSUP;
    }
    return ret;
}
#endif

static int spi_v32f20x_init(const struct device *dev)
{
    const struct spi_v32f20x_config *config = dev->config;
    int ret;

    ret = pinctrl_apply_state(config->pcfg, PINCTRL_STATE_DEFAULT);
    if (ret < 0) return ret;

#ifdef CONFIG_PM_DEVICE_RUNTIME
    pm_device_runtime_enable(dev);
#endif

    return 0;
}

#define SPI_V32F20X_INIT(n)                                                    \
    static const struct spi_v32f20x_config spi_v32f20x_config_##n = {          \
        .base = (SPI_Type *)DT_INST_REG_ADDR(n),                               \
        .pcfg = PINCTRL_DT_INST_DEV_CONFIG_GET(n),                             \
    };                                                                         \
    static struct spi_v32f20x_data spi_v32f20x_data_##n;                       \
    PM_DEVICE_DT_INST_DEFINE(n, spi_v32f20x_pm_action);                        \
    DEVICE_DT_INST_DEFINE(n, spi_v32f20x_init, PM_DEVICE_DT_INST_GET(n),       \
                          &adc_v32f20x_data_##n, &adc_v32f20x_config_##n,      \
                          POST_KERNEL, CONFIG_SPI_INIT_PRIORITY,               \
                          &spi_v32f20x_api);

DT_INST_FOREACH_STATUS_OKAY(SPI_V32F20X_INIT)
