/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 *
 * --- Phase 5: High-Availability Flash Topology (2304KB Total) ---
 */

#ifndef __FLASH_LAYOUT_H__
#define __FLASH_LAYOUT_H__

#define FLASH_BASE_ADDRESS              (0x08000000)
#define FLASH_AREA_IMAGE_SECTOR_SIZE    (0x1000)   /* 4 KB */
#define FLASH_TOTAL_SIZE                (0x240000)  /* 2304 KB */

/* Partition Sizes (Task 1.1 Specification) */
#define FLASH_S_PARTITION_SIZE          (0x40000)   /* 256 KB */
#define FLASH_NS_PARTITION_SIZE         (0x50000)   /* 320 KB */
#define FLASH_MAX_PARTITION_SIZE        (FLASH_S_PARTITION_SIZE + FLASH_NS_PARTITION_SIZE)

#ifndef MCUBOOT_IMAGE_NUMBER
#define MCUBOOT_IMAGE_NUMBER            (2)
#endif

#define FLASH_DEV_NAME                  Driver_FLASH0

/* 0x000000 - 0x010000: MCUboot (64KB) */
#define FLASH_AREA_BL2_OFFSET           (0x0)
#define FLASH_AREA_BL2_SIZE             (0x10000)

/* Slot 0: S (256K) + NS (320K) = 576K */
#define FLASH_AREA_0_ID                 (1)
#define FLASH_AREA_0_OFFSET             (FLASH_AREA_BL2_OFFSET + FLASH_AREA_BL2_SIZE)
#define FLASH_AREA_0_SIZE               (FLASH_S_PARTITION_SIZE)

#define FLASH_AREA_1_ID                 (2)
#define FLASH_AREA_1_OFFSET             (FLASH_AREA_0_OFFSET + FLASH_AREA_0_SIZE)
#define FLASH_AREA_1_SIZE               (FLASH_NS_PARTITION_SIZE)

/* Slot 1: S (256K) + NS (320K) backup = 576K */
#define FLASH_AREA_2_ID                 (3)
#define FLASH_AREA_2_OFFSET             (0x0A0000)
#define FLASH_AREA_2_SIZE               (FLASH_S_PARTITION_SIZE)

#define FLASH_AREA_3_ID                 (4)
#define FLASH_AREA_3_OFFSET             (FLASH_AREA_2_OFFSET + FLASH_AREA_2_SIZE)
#define FLASH_AREA_3_SIZE               (FLASH_NS_PARTITION_SIZE)

/* TF-M Internal Areas (Reserved gap 0x130000 - 0x140000) */
#define FLASH_AREA_4_ID                 (5)
#define FLASH_AREA_4_OFFSET             (0x130000)
#define FLASH_AREA_4_SIZE               (0x4000)    /* PS (16KB) */

#define FLASH_AREA_5_ID                 (6)
#define FLASH_AREA_5_OFFSET             (FLASH_AREA_4_OFFSET + FLASH_AREA_4_SIZE)
#define FLASH_AREA_5_SIZE               (0x8000)    /* ITS (32KB) */

/* NV Counters: Bank A (8K) + Bank B (8K) = 16KB */
#define FLASH_AREA_NV_COUNTERS_ID       (7)
#define FLASH_AREA_NV_COUNTERS_OFFSET   (0x13C000)
#define FLASH_AREA_NV_COUNTERS_SIZE     (0x2000)

/* 0x140000 - 0x150000: Scratch (64KB) */
#define FLASH_AREA_SCRATCH_ID           (8)
#define FLASH_AREA_SCRATCH_OFFSET       (0x140000)
#define FLASH_AREA_SCRATCH_SIZE         (0x10000)

/* Post-Security Partitions (0x150000 onwards) */
#define FLASH_AREA_CPUMETER_OFFSET      (0x150000)
#define FLASH_AREA_CPUMETER_SIZE        (0x20000)   /* 128KB */

#define FLASH_AREA_STORAGE_OFFSET       (0x170000)
#define FLASH_AREA_STORAGE_SIZE         (0x20000)   /* 128KB */

#define FLASH_AREA_MODEL_OFFSET         (0x190000)
#define FLASH_AREA_MODEL_SIZE           (0x20000)   /* 128KB */

/* 0x1B0000 - 0x240000: Golden Recovery (576KB) */
#define FLASH_AREA_RECOVERY_OFFSET      (0x1B0000)
#define FLASH_AREA_RECOVERY_SIZE        (0x90000)

/* --- TF-M Driver Configuration --- */
#define TFM_HAL_FLASH_PROGRAM_UNIT       (0x4)
#define TFM_HAL_ITS_FLASH_DRIVER         Driver_FLASH0
#define TFM_HAL_ITS_PROGRAM_UNIT         (0x4)
#define TFM_HAL_ITS_FLASH_AREA_ADDR      (FLASH_BASE_ADDRESS + FLASH_AREA_5_OFFSET)
#define TFM_HAL_ITS_FLASH_AREA_SIZE      (FLASH_AREA_5_SIZE)
#define TFM_HAL_ITS_SECTORS_PER_BLOCK    (1)

#define TFM_HAL_PS_FLASH_DRIVER          Driver_FLASH0
#define TFM_HAL_PS_PROGRAM_UNIT          (0x4)
#define TFM_HAL_PS_FLASH_AREA_ADDR       (FLASH_BASE_ADDRESS + FLASH_AREA_4_OFFSET)
#define TFM_HAL_PS_FLASH_AREA_SIZE       (FLASH_AREA_4_SIZE)
#define TFM_HAL_PS_SECTORS_PER_BLOCK     (1)

/* Fix for compilation error: NV Backup Area required by TF-M platform-default */
#define TFM_OTP_NV_COUNTERS_AREA_ADDR       (FLASH_BASE_ADDRESS + FLASH_AREA_NV_COUNTERS_OFFSET)
#define TFM_OTP_NV_COUNTERS_AREA_SIZE       (FLASH_AREA_NV_COUNTERS_SIZE)
#define TFM_OTP_NV_COUNTERS_BACKUP_AREA_ADDR (TFM_OTP_NV_COUNTERS_AREA_ADDR + TFM_OTP_NV_COUNTERS_AREA_SIZE)
#define TFM_OTP_NV_COUNTERS_SECTOR_SIZE     (FLASH_AREA_IMAGE_SECTOR_SIZE)
#define TFM_OTP_NV_COUNTERS_MAX_ENTRIES     (TFM_OTP_NV_COUNTERS_AREA_SIZE / TFM_OTP_NV_COUNTERS_SECTOR_SIZE)

#define MCUBOOT_STATUS_MAX_ENTRIES      (FLASH_MAX_PARTITION_SIZE / FLASH_AREA_IMAGE_SECTOR_SIZE)
#define MCUBOOT_MAX_IMG_SECTORS         (FLASH_MAX_PARTITION_SIZE / FLASH_AREA_IMAGE_SECTOR_SIZE)

#endif /* __FLASH_LAYOUT_H__ */
