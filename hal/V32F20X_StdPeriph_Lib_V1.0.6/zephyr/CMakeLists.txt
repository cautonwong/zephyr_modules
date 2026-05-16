# Zephyr HAL for V32F20X - Professional Version Refactored

zephyr_library_named(v32f20x_hal)

# 1. Global Chip/Core definitions for HAL library
zephyr_library_compile_definitions(V32F209XX)
zephyr_library_compile_definitions(_USE_TARGET_DRIVER)

if(CONFIG_SOC_V32F20X_CPU0)
    zephyr_library_compile_definitions(V32F20XXX_CM0_CORE)
elseif(CONFIG_SOC_V32F20X_CPU1)
    zephyr_library_compile_definitions(V32F20XXX_CM33_CORE0)
endif()

# 2. Includes
zephyr_library_include_directories(include)
zephyr_library_include_directories(../Libraries/include)
zephyr_library_include_directories(../Libraries/Drivers/Inc)
zephyr_library_include_directories(../Libraries/CMSIS/Include)

# 3. Sources
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_ADC      ../Libraries/Drivers/Src/lib_adc.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_CAN      ../Libraries/Drivers/Src/lib_can.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_CLK      ../Libraries/Drivers/Src/lib_clk.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_CRC      ../Libraries/Drivers/Src/lib_crc.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_CRYPT    ../Libraries/Drivers/Src/lib_crypt.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_DAC      ../Libraries/Drivers/Src/lib_dac.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_DMA      ../Libraries/Drivers/Src/lib_dma.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_FLASH    ../Libraries/Drivers/Src/lib_flash.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_GPIO     ../Libraries/Drivers/Src/lib_gpio.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_I2C      ../Libraries/Drivers/Src/lib_i2c.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_MAILBOX  ../Libraries/Drivers/Src/lib_mailbox.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_SPI      ../Libraries/Drivers/Src/lib_spi.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_SYSCFG   ../Libraries/Drivers/Src/lib_syscfg1.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_TIMER    ../Libraries/Drivers/Src/lib_timer.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_UART     ../Libraries/Drivers/Src/lib_uart.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_WDT      ../Libraries/Drivers/Src/lib_wdt.c)

# SYSCFG0 is CM33 specific
if(NOT CONFIG_CPU_CORTEX_M0)
    zephyr_library_sources_ifdef(CONFIG_VANGO_V32F20X_HAL_SYSCFG ../Libraries/Drivers/Src/lib_syscfg0.c)
endif()
