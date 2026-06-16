# Copyright (c) 2024, Vango Technologies
# SPDX-License-Identifier: BSD-3-Clause
#
# Platform configuration for Vango V32F20x

if(BL2)
    set(BL2_TRAILER_SIZE 0x10000 CACHE STRING "Trailer size")
else()
    set(BL2_TRAILER_SIZE 0x10400 CACHE STRING "Trailer size")
endif()

# V32F20x uses standard ARM TrustZone-M (SAU), NOT Nordic SPU
set(CONFIG_TFM_USE_TRUSTZONE          ON)
set(TFM_MULTI_CORE_TOPOLOGY           OFF)

set(MCUBOOT_USE_PSA_CRYPTO            ON    CACHE BOOL   "Use PSA Crypto APIs")
set(MCUBOOT_SIGNATURE_TYPE            "EC-P256" CACHE STRING "Signature algorithm")
set(MCUBOOT_HW_KEY                    OFF   CACHE BOOL   "Embed full public key in image")
set(MCUBOOT_BUILTIN_KEY               ON    CACHE BOOL   "Use builtin key for validation")

# V32F20x does not require Nordic SPU configuration
set(NRF_BOARD_SELECTED                FALSE)
set(TFM_PARTITION_INITIAL_ATTESTATION ON)
set(TFM_IA_MAX_TOKEN_SIZE 1024)
