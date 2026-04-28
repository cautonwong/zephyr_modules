zephyr_library()

# SoC include directory for hal config and pinctrl_soc.h
zephyr_include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../../../soc/v85xxp/include
)

zephyr_include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/include
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/CMSIS_Include
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/Lib_Driver/inc
)

file(GLOB v85xxp_hal_src
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/Lib_Driver/src/*.c
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/device/lib_cortex.c
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/device/lib_LoadNVR.c
	${CMAKE_CURRENT_LIST_DIR}/../Libraries/CMSIS/device/lib_CodeRAM.c
)

# 之前这里有一个错误的 list(FILTER v85xxp_hal_src EXCLUDE REGEX ".*/lib_uart\\.c$")
# 它导致底层 UART 驱动未编译。现在我已经把它删除了。

zephyr_library_sources(${v85xxp_hal_src})

# Force include config to provide assert_parameters and other glue
zephyr_library_compile_options(-include vango_v85xxp_hal_config.h)
