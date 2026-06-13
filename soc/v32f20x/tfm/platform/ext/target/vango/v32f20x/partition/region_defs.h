/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __REGION_DEFS_H__
#define __REGION_DEFS_H__

#include "flash_layout.h"

/* Stack/heap sizes */
#define BL2_HEAP_SIZE           (0x00001000)
#define BL2_MSP_STACK_SIZE      (0x00001800)

#ifdef ENABLE_HEAP
    #define S_HEAP_SIZE         (0x0000200)
#endif

#define S_MSP_STACK_SIZE        (0x00000800)
#define S_PSP_STACK_SIZE        (0x00000800)

#define NS_HEAP_SIZE            (0x00001000)
#define NS_STACK_SIZE           (0x000001E0)

/*
 * V32F20x memory map:
 *   Flash: 0x08000000 - 0x0823FFFF (2304 KB)
 *   SRAM:  0x20000000 - 0x2010FFFF (1088 KB)
 *
 * TrustZone SAU regions:
 *   S_ROM_ALIAS_BASE  = 0x08000000 (Secure Flash)
 *   NS_ROM_ALIAS_BASE = 0x08000000 (Same, partitioned by BL2 slot offset)
 *   S_RAM_ALIAS_BASE  = 0x20000000
 *   NS_RAM_ALIAS_BASE = 0x20000000
 */
#define S_ROM_ALIAS_BASE        (0x08000000)
#define NS_ROM_ALIAS_BASE       (0x08000000)
#define S_RAM_ALIAS_BASE        (0x20000000)
#define NS_RAM_ALIAS_BASE       (0x20000000)
#define TOTAL_RAM_SIZE          (0x110000)   /* 1088 KB */

/* Image offsets */
#define S_IMAGE_PRIMARY_PARTITION_OFFSET  (FLASH_AREA_0_OFFSET)
#define NS_IMAGE_PRIMARY_PARTITION_OFFSET (FLASH_AREA_0_OFFSET + FLASH_S_PARTITION_SIZE)

#define IMAGE_S_CODE_SIZE \
            (FLASH_S_PARTITION_SIZE - BL2_HEADER_SIZE - 0x2000)
#define IMAGE_NS_CODE_SIZE \
            (FLASH_NS_PARTITION_SIZE - BL2_HEADER_SIZE - BL2_TRAILER_SIZE)

/* Alias macros */
#define S_ROM_ALIAS(x)  (S_ROM_ALIAS_BASE + (x))
#define NS_ROM_ALIAS(x) (NS_ROM_ALIAS_BASE + (x))
#define S_RAM_ALIAS(x)  (S_RAM_ALIAS_BASE + (x))
#define NS_RAM_ALIAS(x) (NS_RAM_ALIAS_BASE + (x))

/* Secure image code region */
#define S_IMAGE_PRIMARY_AREA_OFFSET \
                        (S_IMAGE_PRIMARY_PARTITION_OFFSET + BL2_HEADER_SIZE)
#define S_CODE_START    (S_ROM_ALIAS(S_IMAGE_PRIMARY_AREA_OFFSET))
#define S_CODE_SIZE     (IMAGE_S_CODE_SIZE)
#define S_CODE_LIMIT    (S_CODE_START + S_CODE_SIZE - 1)

/* Secure data (RAM) region */
#define S_DATA_START    (S_RAM_ALIAS(0x0))
#define S_DATA_SIZE     (TOTAL_RAM_SIZE / 2)
#define S_DATA_LIMIT    (S_DATA_START + S_DATA_SIZE - 1)

/* Veneer region (CMSE NSC) */
#define TFM_LINKER_VENEERS_LOCATION_END
#define TFM_LINKER_VENEERS_SIZE         (0x400)
#define TFM_LINKER_VENEERS_START        (S_CODE_LIMIT + 1 - TFM_LINKER_VENEERS_SIZE)
#define S_CODE_VECTOR_TABLE_SIZE        (0x154)

/* Non-secure image code region */
#define NS_IMAGE_PRIMARY_AREA_OFFSET \
                        (NS_IMAGE_PRIMARY_PARTITION_OFFSET + BL2_HEADER_SIZE)
#define NS_CODE_START   (NS_ROM_ALIAS(NS_IMAGE_PRIMARY_AREA_OFFSET))
#define NS_CODE_SIZE    (IMAGE_NS_CODE_SIZE)
#define NS_CODE_LIMIT   (NS_CODE_START + NS_CODE_SIZE - 1)

/* Non-secure data (RAM) region */
#define NS_DATA_START   (NS_RAM_ALIAS(S_DATA_SIZE))
#define NS_DATA_SIZE    (TOTAL_RAM_SIZE - S_DATA_SIZE)
#define NS_DATA_LIMIT   (NS_DATA_START + NS_DATA_SIZE - 1)

/* NS partition info */
#define NS_PARTITION_START \
            (NS_ROM_ALIAS(NS_IMAGE_PRIMARY_PARTITION_OFFSET))
#define NS_PARTITION_SIZE (FLASH_NS_PARTITION_SIZE)

/* Secondary partition */
#define SECONDARY_PARTITION_START \
            (NS_ROM_ALIAS(FLASH_AREA_2_OFFSET))
#define SECONDARY_PARTITION_SIZE (FLASH_AREA_2_SIZE)

#ifdef BL2
/* BL2 regions */
#define BL2_CODE_START    (S_ROM_ALIAS(FLASH_AREA_BL2_OFFSET))
#define BL2_CODE_SIZE     (FLASH_AREA_BL2_SIZE)
#define BL2_CODE_LIMIT    (BL2_CODE_START + BL2_CODE_SIZE - 1)

#define BL2_DATA_START    (S_RAM_ALIAS(0x0))
#define BL2_DATA_SIZE     (TOTAL_RAM_SIZE)
#define BL2_DATA_LIMIT    (BL2_DATA_START + BL2_DATA_SIZE - 1)
#endif /* BL2 */

/* Shared boot/runtime measurement data */
#define BOOT_TFM_SHARED_DATA_BASE   S_RAM_ALIAS_BASE
#define BOOT_TFM_SHARED_DATA_SIZE   (0x400)
#define BOOT_TFM_SHARED_DATA_LIMIT  (BOOT_TFM_SHARED_DATA_BASE + \
                                     BOOT_TFM_SHARED_DATA_SIZE - 1)
#define SHARED_BOOT_MEASUREMENT_BASE  BOOT_TFM_SHARED_DATA_BASE
#define SHARED_BOOT_MEASUREMENT_SIZE  BOOT_TFM_SHARED_DATA_SIZE
#define SHARED_BOOT_MEASUREMENT_LIMIT BOOT_TFM_SHARED_DATA_LIMIT

/* PSA test scratch area */
#define PSA_TEST_SCRATCH_AREA_SIZE  (0x400)
#define PSA_TEST_SCRATCH_AREA_BASE  (NS_DATA_LIMIT + 1 - PSA_TEST_SCRATCH_AREA_SIZE)

#endif /* __REGION_DEFS_H__ */
