# Copyright (c) 2024 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

# 1. Define the SoC library
zephyr_library()

# 2. Add SoC core
zephyr_library_sources(soc.c)
zephyr_compile_definitions(V32F209XX)

if(CONFIG_SOC_V32F20X_CPUMETER)
    zephyr_compile_definitions(V32F20XXX_CM0_CORE)
elseif(CONFIG_SOC_V32F20X_CPUAPP)
    zephyr_compile_definitions(V32F20XXX_CM33_CORE0)
endif()

if(CONFIG_CPU_CORTEX_M0)
    zephyr_compile_definitions(SHPR=SHP)
endif()

# 3. Global Header Injection
set(V32_HAL_DIR /root/fast_space/modules/hal/V32F20X_StdPeriph_Lib_V1.0.6)

# Use zephyr_include_directories for global visibility (including kernel offsets.c)
zephyr_include_directories(.)
zephyr_include_directories(${V32_HAL_DIR}/Libraries/include)
zephyr_include_directories(${V32_HAL_DIR}/Libraries/Drivers/Inc)
zephyr_include_directories(${V32_HAL_DIR}/Libraries/CMSIS/Include)
zephyr_include_directories(${V32_HAL_DIR}/Libraries/CMSIS/cm0)
zephyr_include_directories(${V32_HAL_DIR}/Libraries/CMSIS/cm33/core0)

# 4. Bind to kernel interface for universal visibility
target_include_directories(zephyr_interface INTERFACE ${V32_HAL_DIR}/Libraries/include)
target_compile_definitions(zephyr_interface INTERFACE CONFIG_SOC_FAMILY="vango")

# 5. Set the Linker Script
set(SOC_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld CACHE INTERNAL "")
