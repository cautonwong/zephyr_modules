# Copyright (c) 2024 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

zephyr_library_named(v32f20x_drivers)

zephyr_library_include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

# 1. Foundation Infrastructure
zephyr_library_sources_ifdef(CONFIG_CLOCK_CONTROL_V32F20X  clock_control/clock_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_PINCTRL_V32F20X        pinctrl/pinctrl_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_RESET_V32F20X          reset/reset_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_DMA_V32F20X            dma/dma_v32f20x.c)

# 2. IO & Bus
zephyr_library_sources_ifdef(CONFIG_V32F20X_GPIO           gpio/gpio_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_V32F20X_UART           serial/uart_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_I2C_V32F20X            i2c/i2c_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_SPI_V32F20X            spi/spi_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_CAN_V32F20X            can/can_v32f20x.c)

# 3. Specialized High-Speed/Comm
zephyr_library_sources_ifdef(CONFIG_SDIO_V32F20X           sdio/sdio_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_OSPI_V32F20X           ospi/ospi_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_I2S_V32F20X            i2s/i2s_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_V32F20X_ISO7816        iso7816/iso7816_v32f20x.c)

# 4. Analog & Mixed Signal
zephyr_library_sources_ifdef(CONFIG_ADC_V32F20X            adc/adc_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_DAC_V32F20X            dac/dac_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_PWM_V32F20X            pwm/pwm_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_COMP_V32F20X           analog/comp_v32f20x.c)

# 5. Multimedia & Security
zephyr_library_sources_ifdef(CONFIG_DCMI_V32F20X           dcmi/dcmi_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_CRYPT_V32F20X          crypt/crypt_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_CRC_V32F20X            crc/crc_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_ENTROPY_V32F20X        entropy/rng_v32f20x.c)

# 6. System & IPC
zephyr_library_sources_ifdef(CONFIG_MAILBOX_V32F20X        mailbox/mailbox_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_FLASH_V32F20X          flash/flash_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_WATCHDOG_V32F20X       watchdog/wdt_v32f20x.c)
zephyr_library_sources_ifdef(CONFIG_COUNTER_V32F20X        timer/timer_v32f20x.c)
