/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/pinctrl.h>
#include <soc.h>
#include <lib_gpio.h>

int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt, uintptr_t reg)
{
    for (uint8_t i = 0; i < pin_cnt; i++) {
        /* V85XXP 使用 GPIO_AFConfig 接口 */
        uint32_t pinmux = pins[i].pinmux;
        if ((pinmux & 0xFFFF) <= 15) {
            GPIOBToF_AFConfig((GPIO_Type*)reg, pinmux, ENABLE);
        } else {
            GPIOA_AFConfig(pinmux, ENABLE);
        }
    }
    return 0;
}
