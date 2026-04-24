# Copyright (c) 2026 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

zephyr_library_named(v85xxp_drivers)

# Infrastructure
zephyr_library_sources_ifdef(CONFIG_CLOCK_CONTROL_V85XXP  clock_control/clock_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_PINCTRL_V85XXP        pinctrl/pinctrl_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_DMA_V85XXP            dma/dma_v85xxp.c)

# IO & Bus
zephyr_library_sources_ifdef(CONFIG_V85XXP_GPIO           gpio/gpio_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_V85XXP_UART           serial/uart_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_I2C_V85XXP            i2c/i2c_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_SPI_V85XXP            spi/spi_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_V85XXP_ISO7816        iso7816/iso7816_v85xxp.c)

# Analog & Timers
zephyr_library_sources_ifdef(CONFIG_ADC_V85XXP            adc/adc_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_PWM_V85XXP            pwm/pwm_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_RTC_V85XXP            rtc/rtc_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_WDT_V85XXP            watchdog/wdt_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_COUNTER_V85XXP_TMR    counter/counter_v85xxp_tmr.c)

# System & Graphics
zephyr_library_sources_ifdef(CONFIG_FLASH_V85XXP          flash/flash_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_LCD_V85XXP            lcd/lcd_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_CRYPT_V85XXP          crypt/crypt_v85xxp.c)
zephyr_library_sources_ifdef(CONFIG_ANALOG_V85XXP       analog/analog_v85xxp.c)
