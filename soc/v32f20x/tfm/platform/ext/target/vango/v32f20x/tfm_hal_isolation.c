/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * TF-M Hardware Abstraction Layer - Memory/Peripheral Isolation
 * for Vango V32F20x (ARMv8-M with standard SAU)
 *
 * Unlike Nordic nRF5340 which uses a proprietary SPU, V32F20x
 * uses the standard ARM SAU (Security Attribution Unit) for TrustZone.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis.h"
#include "region_defs.h"
#include "tfm_hal_isolation.h"
#include "tfm_plat_defs.h"

/* SAU region numbers for V32F20x */
#define SAU_REGION_NS_FLASH     0  /* Non-Secure Flash */
#define SAU_REGION_NS_RAM       1  /* Non-Secure RAM */
#define SAU_REGION_PERIPH_NS    2  /* Non-Secure Peripherals */
#define SAU_REGION_NSC_VENEER   3  /* Non-Secure Callable veneer */
#define SAU_TOTAL_REGIONS       4

static void sau_configure(void)
{
    /* Disable SAU before configuration */
    TZ_SAU_Disable();

    /* Region 0: NS Flash (NS application code) */
    SAU->RNR = SAU_REGION_NS_FLASH;
    SAU->RBAR = (NS_PARTITION_START & SAU_RBAR_BADDR_Msk);
    SAU->RLAR = ((NS_PARTITION_START + NS_PARTITION_SIZE - 1) & SAU_RLAR_LADDR_Msk)
                 | SAU_RLAR_ENABLE_Msk;

    /* Region 1: NS RAM (NS application data) */
    SAU->RNR = SAU_REGION_NS_RAM;
    SAU->RBAR = (NS_DATA_START & SAU_RBAR_BADDR_Msk);
    SAU->RLAR = ((NS_DATA_START + NS_DATA_SIZE - 1) & SAU_RLAR_LADDR_Msk)
                 | SAU_RLAR_ENABLE_Msk;

    /* Region 2: NS Peripheral space */
    SAU->RNR = SAU_REGION_PERIPH_NS;
    SAU->RBAR = (0x40000000 & SAU_RBAR_BADDR_Msk);  /* V32F20x peripheral base */
    SAU->RLAR = ((0x4FFFFFFF) & SAU_RLAR_LADDR_Msk)
                 | SAU_RLAR_ENABLE_Msk;

    /* Region 3: NSC veneer - Non-Secure Callable */
    SAU->RNR = SAU_REGION_NSC_VENEER;
    SAU->RBAR = (S_CODE_LIMIT - TFM_LINKER_VENEERS_SIZE + 1) & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (S_CODE_LIMIT & SAU_RLAR_LADDR_Msk)
                 | SAU_RLAR_NSC_Msk   /* Mark as NSC */
                 | SAU_RLAR_ENABLE_Msk;

    /* Enable SAU - treat all regions NOT listed above as Secure */
    TZ_SAU_Enable();
}

FIH_RET_TYPE(enum tfm_hal_status_t) tfm_hal_set_up_static_boundaries(
                                        uintptr_t *p_spm_thread_context)
{
    (void)p_spm_thread_context;

    /* Configure SAU for V32F20x TrustZone partitioning */
    sau_configure();

    FIH_RET(fih_int_encode(TFM_HAL_SUCCESS));
}

FIH_RET_TYPE(enum tfm_hal_status_t) tfm_hal_memory_check(
                                           uintptr_t boundary,
                                           uintptr_t base,
                                           size_t size,
                                           uint32_t access_type)
{
    (void)boundary;
    (void)access_type;

    /* Basic range validation - NS memory must be within NS partition */
    if (base >= NS_DATA_START && (base + size) <= (NS_DATA_START + NS_DATA_SIZE)) {
        FIH_RET(fih_int_encode(TFM_HAL_SUCCESS));
    }
    if (base >= NS_CODE_START && (base + size) <= (NS_CODE_START + NS_CODE_SIZE)) {
        FIH_RET(fih_int_encode(TFM_HAL_SUCCESS));
    }

    FIH_RET(fih_int_encode(TFM_HAL_ERROR_MEM_FAULT));
}
