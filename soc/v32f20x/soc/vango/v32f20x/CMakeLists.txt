# Copyright (c) 2024 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

# 1. Define the SoC library
zephyr_library()

# 2. Add SoC core
zephyr_library_sources(soc.c)
zephyr_compile_definitions(V32F209XX)

if(CONFIG_SOC_V32F20X_CPU0)
    zephyr_compile_definitions(V32F20XXX_CM0_CORE)
elseif(CONFIG_SOC_V32F20X_CPU1)
    zephyr_compile_definitions(V32F20XXX_CM33_CORE0)
endif()

if(CONFIG_CPU_CORTEX_M0)
    zephyr_compile_definitions(SHPR=SHP)
endif()

# 3. Global Header Injection
set(V32_HAL_DIR /root/fast_space/modules/hal/V32F20X_StdPeriph_Lib_V1.0.6)
zephyr_library_include_directories(include)
zephyr_library_include_directories(.)
zephyr_library_include_directories(${V32_HAL_DIR}/Libraries/include)
zephyr_library_include_directories(${V32_HAL_DIR}/Libraries/Drivers/Inc)
zephyr_library_include_directories(${V32_HAL_DIR}/Libraries/CMSIS/Include)

# 4. Bind to kernel interface for universal visibility
target_include_directories(zephyr_interface INTERFACE ${V32_HAL_DIR}/Libraries/include)

# 5. Set the Linker Script
set(SOC_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld CACHE INTERNAL "")
