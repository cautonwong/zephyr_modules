# Copyright (c) 2026 Vango Technologies
# SPDX-License-Identifier: Apache-2.0

zephyr_library()
zephyr_library_sources(soc.c)

# Force specify the linker script for this SoC family
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld CACHE INTERNAL "")
