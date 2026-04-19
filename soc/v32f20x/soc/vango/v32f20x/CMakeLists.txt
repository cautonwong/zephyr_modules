# Copyright (c) 2024 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(.)

# Add sources
zephyr_library_sources(soc.c)

# For this Zephyr version, we MUST explicitly set SOC_LINKER_SCRIPT for Cortex-M
set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/arm/cortex_m/scripts/linker.ld CACHE INTERNAL "")
