/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_mbox

#include <zephyr/device.h>
#include <zephyr/drivers/mbox.h>
#include <zephyr/irq.h>
#include <soc.h>
#include "lib_mailbox.h"

struct mbox_v32f20x_config {
    uint32_t irqs[2];
};

struct mbox_v32f20x_data {
    mbox_callback_t cb;
    void *user_data;
};

static int mbox_v32f20x_send(const struct device *dev, uint32_t channel, const struct mbox_msg *msg)
{
    if (msg != NULL) {
        return -ENOTSUP;
    }

    if (channel == 0) {
        MB_SetInterrupt(MB_INT_CM0_CORE);
    } else if (channel == 1) {
        MB_SetInterrupt(MB_INT_CM33_CORE0);
    } else {
        return -EINVAL;
    }

    return 0;
}

static int mbox_v32f20x_register_callback(const struct device *dev, uint32_t channel,
                                        mbox_callback_t cb, void *user_data)
{
    struct mbox_v32f20x_data *data = dev->data;

#if defined(CONFIG_SOC_V32F20X_CPU0)
    if (channel != 0) return -EINVAL;
#elif defined(CONFIG_SOC_V32F20X_CPU1)
    if (channel != 1) return -EINVAL;
#endif

    data->cb = cb;
    data->user_data = user_data;

    return 0;
}

static int mbox_v32f20x_set_enabled(const struct device *dev, uint32_t channel, bool enabled)
{
    const struct mbox_v32f20x_config *config = dev->config;

    if (channel >= 2) return -EINVAL;

    if (enabled) {
        irq_enable(config->irqs[channel]);
    } else {
        irq_disable(config->irqs[channel]);
    }
    return 0;
}

static uint32_t mbox_v32f20x_max_channels_get(const struct device *dev)
{
    return 2;
}

static void mbox_v32f20x_isr(const struct device *dev)
{
    struct mbox_v32f20x_data *data = dev->data;

#if defined(CONFIG_SOC_V32F20X_CPU0)
    MB_ClearInterrupt(MB_INT_CM33_CORE0);
    if (data->cb) {
        data->cb(dev, 0, data->user_data, NULL);
    }
#elif defined(CONFIG_SOC_V32F20X_CPU1)
    MB_ClearInterrupt(MB_INT_CM0_CORE);
    if (data->cb) {
        data->cb(dev, 1, data->user_data, NULL);
    }
#endif
}

static const struct mbox_driver_api mbox_v32f20x_api = {
    .send = mbox_v32f20x_send,
    .register_callback = mbox_v32f20x_register_callback,
    .set_enabled = mbox_v32f20x_set_enabled,
    .max_channels_get = mbox_v32f20x_max_channels_get,
};

static int mbox_v32f20x_init(const struct device *dev)
{
#if defined(CONFIG_SOC_V32F20X_CPU0)
    IRQ_CONNECT(DT_INST_IRQ_BY_IDX(0, 0, irq),
                DT_INST_IRQ_BY_IDX(0, 0, priority),
                mbox_v32f20x_isr, DEVICE_DT_INST_GET(0), 0);
#elif defined(CONFIG_SOC_V32F20X_CPU1)
    IRQ_CONNECT(DT_INST_IRQ_BY_IDX(0, 1, irq),
                DT_INST_IRQ_BY_IDX(0, 1, priority),
                mbox_v32f20x_isr, DEVICE_DT_INST_GET(0), 0);
#endif
    return 0;
}

static struct mbox_v32f20x_data mbox_v32f20x_data_0;
static const struct mbox_v32f20x_config mbox_v32f20x_config_0 = {
    .irqs = {
        DT_INST_IRQ_BY_IDX(0, 0, irq),
        DT_INST_IRQ_BY_IDX(0, 1, irq),
    },
};

DEVICE_DT_INST_DEFINE(0, mbox_v32f20x_init, NULL,
                    &mbox_v32f20x_data_0, &mbox_v32f20x_config_0,
                    POST_KERNEL, CONFIG_MBOX_INIT_PRIORITY,
                    &mbox_v32f20x_api);
