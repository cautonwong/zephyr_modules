# Copyright (c) 2024, Vango Technologies
# SPDX-License-Identifier: Apache-2.0
#
# Zephyr TF-M board wrapper for Vango V32F20x
# This file lives in modules/soc/v32f20x/tfm/vango_v32f20x_cpuapp/
# and is referenced via CONFIG_TFM_BOARD in sysbuild conf.
#
# It pulls in the V32F20x TF-M Platform Port from within the same soc module.

set(VANGO_BOARD_SELECTED True)

# Path to our platform port - relative to this file's directory
get_filename_component(VANGO_TFM_SOC_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

add_subdirectory(${VANGO_TFM_SOC_DIR}/platform/ext/target/vango/v32f20x v32f20x)

install(FILES       ${CMAKE_CURRENT_LIST_DIR}/ns/cpuarch_ns.cmake
        DESTINATION ${INSTALL_PLATFORM_NS_DIR}
        RENAME      cpuarch.cmake)

install(FILES       ${CMAKE_CURRENT_LIST_DIR}/config.cmake
        DESTINATION ${INSTALL_PLATFORM_NS_DIR})
