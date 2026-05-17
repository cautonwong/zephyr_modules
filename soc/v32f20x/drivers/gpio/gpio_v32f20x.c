/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_gpio

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_utils.h>
#include <zephyr/irq.h>
#include <soc.h>

struct gpio_v32f20x_config {
        struct gpio_driver_config common;
        uintptr_t base;
        uint8_t port_idx;
};

struct gpio_v32f20x_data {
        struct gpio_driver_data common;
};

static int gpio_v32f20x_config(const struct device *dev,
                             gpio_pin_t pin, gpio_flags_t flags)
{
    return 0;
}

static int gpio_v32f20x_port_set_masked_raw(const struct device *dev,
                                          gpio_port_pins_t mask,
                                          gpio_port_value_t value)
{
    return 0;
}

static int gpio_v32f20x_port_set_bits_raw(const struct device *dev,
                                        gpio_port_pins_t pins)
{
    return 0;
}

static int gpio_v32f20x_port_clear_bits_raw(const struct device *dev,
                                          gpio_port_pins_t pins)
{
    return 0;
}

static int gpio_v32f20x_port_toggle_bits(const struct device *dev,
                                           gpio_port_pins_t pins)
{
    return 0;
}

static int gpio_v32f20x_pin_interrupt_configure(const struct device *dev,
                                              gpio_pin_t pin,
                                              enum gpio_int_mode mode,
                                              enum gpio_int_trig trig)
{
    return 0;
}

static const struct gpio_driver_api gpio_v32f20x_driver_api = {
        .pin_configure = gpio_v32f20x_config,
        .port_get_raw = NULL,
        .port_set_masked_raw = gpio_v32f20x_port_set_masked_raw,
        .port_set_bits_raw = gpio_v32f20x_port_set_bits_raw,
        .port_clear_bits_raw = gpio_v32f20x_port_clear_bits_raw,
        .port_toggle_bits = gpio_v32f20x_port_toggle_bits,
        .pin_interrupt_configure = gpio_v32f20x_pin_interrupt_configure,
};

static int gpio_v32f20x_init(const struct device *dev)
{
    return 0;
}

#define GPIO_V32F20X_INIT(n)                                                           static const struct gpio_v32f20x_config gpio_v32f20x_config_##n = {                    .common = {                                                                            .port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_INST(n),                   },                                                                             .base = DT_INST_REG_ADDR(n),                                                   .port_idx = DT_INST_PROP(n, vango_port),                               };                                                                                                                                                            static struct gpio_v32f20x_data gpio_v32f20x_data_##n;                                                                                                        DEVICE_DT_INST_DEFINE(n, gpio_v32f20x_init, NULL,                                                 &gpio_v32f20x_data_##n,                                                        &gpio_v32f20x_config_##n, POST_KERNEL,                                         CONFIG_GPIO_INIT_PRIORITY,                                                     &gpio_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(GPIO_V32F20X_INIT)
