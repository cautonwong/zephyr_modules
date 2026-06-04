# Copyright (c) 2024, Vango Technologies
# SPDX-License-Identifier: BSD-3-Clause

# This overrides MbedTLS software crypto with V32F20x hardware crypto logic
target_sources(tfm_s
    PRIVATE
        vango_crypto_accel.c
)

# Connect to the Vango hardware encryption engine source from Zephyr HAL
target_include_directories(tfm_s
    PRIVATE
        ${ZEPHYR_BASE}/../modules/hal/V32F20X_StdPeriph_Lib_V1.0.6/inc
)
