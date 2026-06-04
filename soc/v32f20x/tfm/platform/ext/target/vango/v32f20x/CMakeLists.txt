# Copyright (c) 2024, Vango Technologies
# SPDX-License-Identifier: BSD-3-Clause
#
# Vango V32F20x TF-M Platform Port
# Cortex-M33 with TrustZone-M, ARMv8-M.main
#

cmake_policy(SET CMP0076 NEW)
set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

#========================= Platform region defs ===============================#

target_include_directories(platform_region_defs
    INTERFACE
        partition
)

target_link_libraries(platform_region_defs
    INTERFACE
        tfm_fih_headers
)

#========================= Platform common defs ===============================#

# Use the standard TF-M common scatter file for ARM Cortex-M33 (GCC)
target_add_scatter_file(tfm_s
    $<$<C_COMPILER_ID:GNU>:${CMAKE_BINARY_DIR}/generated/platform/ext/common/gcc/tfm_isolation_s.ld>
)

target_sources(tfm_s
    PRIVATE
        startup_v32f20x.c
)

if(BL2)
    target_add_scatter_file(bl2
        $<$<C_COMPILER_ID:GNU>:${PLATFORM_DIR}/ext/common/gcc/tfm_common_bl2.ld>
    )
    target_sources(bl2
        PRIVATE
            startup_v32f20x.c
    )
endif()

#========================= Platform Secure ====================================#

target_include_directories(platform_s
    PUBLIC
        .
        partition
        ${PLATFORM_DIR}/..
)

target_sources(platform_s
    PRIVATE
        cmsis_drivers/Driver_Flash.c
        cmsis_drivers/Driver_USART.c
        $<$<BOOL:${TFM_PARTITION_PLATFORM}>:${CMAKE_CURRENT_SOURCE_DIR}/services/src/tfm_platform_hal_ioctl.c>
)

target_compile_options(platform_s
    PUBLIC
        ${COMPILER_CMSE_FLAG}
)

#========================= Platform BL2 =======================================#

if(BL2)
    target_include_directories(platform_bl2
        PUBLIC
            .
            partition
        PRIVATE
            ${PLATFORM_DIR}/..
    )

    target_sources(platform_bl2
        PRIVATE
            cmsis_drivers/Driver_Flash.c
            cmsis_drivers/Driver_USART.c
    )

    target_compile_definitions(platform_bl2
        PUBLIC
            TFM_SPM_LOG_LEVEL=${TFM_SPM_LOG_LEVEL}
    )
endif()

#========================= tfm_spm ============================================#

target_sources(tfm_spm
    PRIVATE
        tfm_hal_isolation.c
        tfm_hal_platform.c
        target_cfg.c
)

#========================= Hardware Crypto Accelerator =========================#

add_subdirectory(crypto)

#========================= Files for building NS side platform ================#

install(FILES       config.cmake
        DESTINATION ${INSTALL_PLATFORM_NS_DIR})

install(FILES       partition/flash_layout.h
                    partition/region_defs.h
        DESTINATION ${INSTALL_PLATFORM_NS_DIR}/partition)
