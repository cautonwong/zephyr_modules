# Copyright (c) 2024 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

zephyr_sources(soc.c)

# Professional Practice: Define the specific chip macro required by Vango HAL
zephyr_library_definitions(V32F209XX)

# Ensure HAL and SOC headers are in the search path
zephyr_include_directories(.)
zephyr_include_directories(include)
