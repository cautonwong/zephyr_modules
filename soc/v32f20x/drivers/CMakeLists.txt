# Copyright (c) 2024 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

zephyr_library_named(v32f20x_drivers)

zephyr_library_include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

# System
zephyr_library_sources_ifdef(CONFIG_CLOCK_CONTROL_V32F20X  clock_control/clock_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_RESET_V32F20X          reset/reset_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_FLASH_V32F20X          flash/flash_v32f20x.c)

# IO
zephyr_library_sources_ifdef(CONFIG_PINCTRL_V32F20X        pinctrl/pinctrl_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_V32F20X_GPIO           gpio/gpio_v32f20x.c)

# Bus
zephyr_library_sources_ifdef(CONFIG_V32F20X_UART           serial/uart_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_I2C_V32F20X            i2c/i2c_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_SPI_V32F20X            spi/spi_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_CAN_V32F20X            can/can_v32f20x.c)

# Analog & IPC
zephyr_library_sources_ifdef(CONFIG_ADC_V32F20X            adc/adc_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_DMA_V32F20X            dma/dma_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_WDT_V32F20X            watchdog/wdt_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_ENTROPY_V32F20X        entropy/rng_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_V32F20X_MAILBOX        mailbox/mailbox_v32f20x.c)

# New High-Quality Drivers
zephyr_library_sources_ifdef(CONFIG_COUNTER_V32F20X        timer/timer_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_PWM_V32F20X            pwm/pwm_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_CRC_V32F20X            crc/crc_v32f20x.c)
