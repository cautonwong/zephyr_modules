/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_ana_cmp

#include <zephyr/device.h>
#include <zephyr/irq.h>
#include <soc.h>
#include "lib_ana.h"

typedef void (*ana_cmp_callback_t)(const struct device *dev);

struct ana_cmp_v32f20x_data {
    ana_cmp_callback_t callback;
};

static void ana_cmp_v32f20x_isr(const struct device *dev)
{
    struct ana_cmp_v32f20x_data *data = dev->data;
    
    /* Clear Interrupt Flag */
    ANA_ClearINTStatus(ANA_INT_CMP0);
    
    if (data->callback) {
        data->callback(dev);
    }
}

int ana_cmp_v32f20x_set_callback(const struct device *dev, ana_cmp_callback_t cb)
{
    struct ana_cmp_v32f20x_data *data = dev->data;
    data->callback = cb;
    return 0;
}

static int ana_cmp_v32f20x_init(const struct device *dev)
{
    /* Production HW Init: Enable Comparator 0 for Power Down Detection */
    ANA_CMP0_Cmd(ENABLE);
    
    IRQ_CONNECT(DT_INST_IRQN(0), DT_INST_IRQ_PRIORITY(0),
                ana_cmp_v32f20x_isr, DEVICE_DT_INST_GET(0), 0);
    irq_enable(DT_INST_IRQN(0));
    
    return 0;
}

static struct ana_cmp_v32f20x_data ana_cmp_data_0;

DEVICE_DT_INST_DEFINE(0, ana_cmp_v32f20x_init, NULL,
                    &ana_cmp_data_0, NULL,
                    POST_KERNEL, 60, NULL);
