# Zephyr HAL for V85XXP - conditional compilation per library module

zephyr_library_named(v85xxp_hal)

# SoC include directory for hal config and pinctrl_soc.h
zephyr_include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../../../soc/v85xxp/include
)

zephyr_include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/include
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/CMSIS_Include
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/Lib_Driver/inc
)

# Core CMSIS device sources — always compiled
zephyr_library_sources(
	../Libraries/CMSIS/device/lib_cortex.c
	../Libraries/CMSIS/device/lib_LoadNVR.c
	../Libraries/CMSIS/device/lib_CodeRAM.c
	../Libraries/CMSIS/device/system_target.c
)

# Core HAL modules — always compiled
zephyr_library_sources(
	../Libraries/Lib_Driver/src/lib_misc.c
	../Libraries/Lib_Driver/src/lib_clk.c
	../Libraries/Lib_Driver/src/lib_version.c
)

# Peripherals — conditionally compiled via Kconfig
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_ADC      ../Libraries/Lib_Driver/src/lib_adc.c      ../Libraries/Lib_Driver/src/lib_adc_tiny.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_ANA      ../Libraries/Lib_Driver/src/lib_ana.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_CMP      ../Libraries/Lib_Driver/src/lib_cmp.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_CRYPT    ../Libraries/Lib_Driver/src/lib_crypt.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_DMA      ../Libraries/Lib_Driver/src/lib_dma.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_FLASH    ../Libraries/Lib_Driver/src/lib_flash.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_GPIO     ../Libraries/Lib_Driver/src/lib_gpio.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_I2C      ../Libraries/Lib_Driver/src/lib_i2c.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_ISO7816  ../Libraries/Lib_Driver/src/lib_iso7816.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_LCD      ../Libraries/Lib_Driver/src/lib_lcd.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_PMU      ../Libraries/Lib_Driver/src/lib_pmu.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_PWM      ../Libraries/Lib_Driver/src/lib_pwm.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_RTC      ../Libraries/Lib_Driver/src/lib_rtc.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_SPI      ../Libraries/Lib_Driver/src/lib_spi.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_TMR      ../Libraries/Lib_Driver/src/lib_tmr.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_U32K     ../Libraries/Lib_Driver/src/lib_u32k.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_UART     ../Libraries/Lib_Driver/src/lib_uart.c)
zephyr_library_sources_ifdef(CONFIG_VANGO_V85XXP_HAL_WDT      ../Libraries/Lib_Driver/src/lib_wdt.c)

# Force include config to provide assert_parameters and other glue
zephyr_library_compile_options(-include vango_v85xxp_hal_config.h)
