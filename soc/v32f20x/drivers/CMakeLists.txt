# Copyright (c) 2024 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

zephyr_library_named(v32f20x_drivers)

# Infrastructure
zephyr_library_sources_ifdef(CONFIG_CLOCK_CONTROL_V32F20X  clock_control/clock_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_PINCTRL_V32F20X        pinctrl/pinctrl_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_RESET_V32F20X          reset/reset_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_DMA_V32F20X            dma/dma_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_MBOX_V32F20X           mbox/mbox_v32f20x.c)

# IO & Bus
# Only build GPIO if enabled to avoid macro recursion bugs in certain cores
zephyr_library_sources_ifdef(CONFIG_GPIO_V32F20X           gpio/gpio_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_V32F20X_UART           serial/uart_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_I2C_V32F20X            i2c/i2c_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_SPI_V32F20X            spi/spi_v32f20x.c)

# Analog & Timers
zephyr_library_sources_ifdef(CONFIG_ADC_V32F20X            adc/adc_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_TIMER_V32F20X          timer/timer_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_WDT_V32F20X            watchdog/watchdog_v32f20x.c)

# System
zephyr_library_sources_ifdef(CONFIG_FLASH_V32F20X          flash/flash_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_ENTROPY_V32F20X        entropy/rng_v32f20x.c)
