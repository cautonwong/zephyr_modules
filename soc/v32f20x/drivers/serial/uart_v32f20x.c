/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_uart

#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/pm/device.h>
#include <zephyr/pm/device_runtime.h>
#include <soc.h>
#include "lib_uart.h"
#include "lib_syscfg.h"

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
#include <zephyr/irq.h>
#endif

#undef IS_BIT_SET
#define IS_BIT_SET(value, bit) ((((value) >> (bit)) & (0x1)) != 0)

struct uart_v32f20x_config {
    UART_Type *base;
};

struct uart_v32f20x_data {
    struct uart_config uart_cfg;
};

static int uart_v32f20x_poll_in(const struct device *dev, unsigned char *p_char)
{
    const struct uart_v32f20x_config *config = dev->config;
    if (UART_GetFlag(config->base, UART_FLAG_RX) == SET) {
        *p_char = UART_ReceiveData(config->base);
        return 0;
    }
    return -1;
}

static void uart_v32f20x_poll_out(const struct device *dev, unsigned char out_char)
{
    const struct uart_v32f20x_config *config = dev->config;
    while (UART_GetFlag(config->base, UART_FLAG_TXE) == RESET);
    UART_SendData(config->base, out_char);
}

static int uart_v32f20x_configure(const struct device *dev, const struct uart_config *cfg)
{
    const struct uart_v32f20x_config *config = dev->config;
    UART_InitType init_struct;

    UART_StructInit(&init_struct);
    init_struct.Baudrate = cfg->baudrate;
    init_struct.SerialClock = 24000000;
    
    UART_Init(config->base, &init_struct);
    return 0;
}

static int uart_v32f20x_config_get(const struct device *dev, struct uart_config *cfg)
{
    struct uart_v32f20x_data *data = dev->data;
    *cfg = data->uart_cfg;
    return 0;
}

#ifdef CONFIG_PM_DEVICE
static int uart_v32f20x_pm_action(const struct device *dev, enum pm_device_action action)
{
#if !defined(CONFIG_SOC_V32F20X_CPU0)
    const struct uart_v32f20x_config *config = dev->config;
    uint32_t uart_idx = ((uintptr_t)config->base - 0x40000000) / 0x400;

    switch (action) {
    case PM_DEVICE_ACTION_SUSPEND:
        SYSCFG0_FlexcommUARTRxCmd((FLEXCOMM_Type)uart_idx, DISABLE);
        break;
    case PM_DEVICE_ACTION_RESUME:
        SYSCFG0_FlexcommUARTRxCmd((FLEXCOMM_Type)uart_idx, ENABLE);
        break;
    default:
        return -ENOTSUP;
    }
#endif
    return 0;
}
#endif

static const struct uart_driver_api uart_v32f20x_driver_api = {
    .poll_in = uart_v32f20x_poll_in,
    .poll_out = uart_v32f20x_poll_out,
    .configure = uart_v32f20x_configure,
    .config_get = uart_v32f20x_config_get,
};

static int uart_v32f20x_init(const struct device *dev)
{
    struct uart_v32f20x_data *data = dev->data;
    uart_v32f20x_configure(dev, &data->uart_cfg);

#ifdef CONFIG_PM_DEVICE_RUNTIME
    pm_device_runtime_enable(dev);
#endif

    return 0;
}

#define UART_V32F20X_DEVICE(n)                                                  static struct uart_v32f20x_data uart_v32f20x_data_##n = {                       .uart_cfg = {                                                                   .baudrate = DT_INST_PROP(n, current_speed),                                 .parity = UART_CFG_PARITY_NONE,                                             .stop_bits = UART_CFG_STOP_BITS_1,                                          .data_bits = UART_CFG_DATA_BITS_8,                                          .flow_ctrl = UART_CFG_FLOW_CTRL_NONE,                                   }                                                                       };                                                                          static const struct uart_v32f20x_config uart_v32f20x_config_##n = {             .base = (UART_Type *)DT_INST_REG_ADDR(n),                               };                                                                          PM_DEVICE_DT_INST_DEFINE(n, uart_v32f20x_pm_action);                       DEVICE_DT_INST_DEFINE(n, uart_v32f20x_init,                                                     PM_DEVICE_DT_INST_GET(n),                                                   &uart_v32f20x_data_##n,                                                     &uart_v32f20x_config_##n, PRE_KERNEL_1,                                     CONFIG_SERIAL_INIT_PRIORITY,                                                &uart_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(UART_V32F20X_DEVICE)
