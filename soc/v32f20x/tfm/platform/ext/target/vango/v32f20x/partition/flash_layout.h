/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 *
 * Flash layout for Vango V32F20x with MCUBoot (BL2):
 *
 * 0x0800_0000 BL2 - MCUBoot (64 KB)
 * 0x0801_0000 Primary image area (576 KB):
 *    0x0801_0000 Secure image primary     (256 KB)
 *    0x0805_0000 Non-secure image primary (320 KB)
 * 0x080A_0000 Secondary image area (576 KB):
 *    0x080A_0000 Secure image secondary   (256 KB)
 *    0x080E_0000 Non-secure image secondary (320 KB)
 * 0x0813_0000 Protected Storage Area (16 KB)
 * 0x0813_4000 Internal Trusted Storage Area (8 KB)
 * 0x0813_6000 OTP / NV counters area (8 KB)
 *
 * V32F20x total flash: 2304 KB (0x240000)
 */

#ifndef __FLASH_LAYOUT_H__
#define __FLASH_LAYOUT_H__

/* V32F20x flash starts at 0x08000000 (internal flash base) */
#define FLASH_BASE_ADDRESS              (0x08000000)

/* Sector size of embedded flash (erase granularity) */
#define FLASH_AREA_IMAGE_SECTOR_SIZE    (0x1000)   /* 4 KB */

/* Total flash size */
#define FLASH_TOTAL_SIZE                (0x240000)  /* 2304 KB */

/* S and NS partition sizes */
#define FLASH_S_PARTITION_SIZE          (0x40000)   /* S partition: 256 KB */
#define FLASH_NS_PARTITION_SIZE         (0x50000)   /* NS partition: 320 KB */

#if (FLASH_S_PARTITION_SIZE > FLASH_NS_PARTITION_SIZE)
#define FLASH_MAX_PARTITION_SIZE FLASH_S_PARTITION_SIZE
#else
#define FLASH_MAX_PARTITION_SIZE FLASH_NS_PARTITION_SIZE
#endif

#ifndef MCUBOOT_IMAGE_NUMBER
#define MCUBOOT_IMAGE_NUMBER            (2)
#endif

/* Flash device name used by BL2 */
#define FLASH_DEV_NAME                  Driver_FLASH0

/* BL2 bootloader region */
#define FLASH_AREA_BL2_OFFSET           (0x0)
#define FLASH_AREA_BL2_SIZE             (0x10000)   /* 64 KB */

#if (MCUBOOT_IMAGE_NUMBER == 2)
/* Primary Secure image slot (Image 0) */
#define FLASH_AREA_0_ID                 (1)
#define FLASH_AREA_0_OFFSET             (FLASH_AREA_BL2_OFFSET + FLASH_AREA_BL2_SIZE)
#define FLASH_AREA_0_SIZE               (FLASH_S_PARTITION_SIZE)

/* Primary Non-Secure image slot (Image 1) */
#define FLASH_AREA_1_ID                 (2)
#define FLASH_AREA_1_OFFSET             (FLASH_AREA_0_OFFSET + FLASH_AREA_0_SIZE)
#define FLASH_AREA_1_SIZE               (FLASH_NS_PARTITION_SIZE)

/* Secondary Secure image slot (Image 0) */
#define FLASH_AREA_2_ID                 (3)
#define FLASH_AREA_2_OFFSET             (FLASH_AREA_1_OFFSET + FLASH_AREA_1_SIZE)
#define FLASH_AREA_2_SIZE               (FLASH_S_PARTITION_SIZE)

/* Secondary Non-Secure image slot (Image 1) */
#define FLASH_AREA_3_ID                 (4)
#define FLASH_AREA_3_OFFSET             (FLASH_AREA_2_OFFSET + FLASH_AREA_2_SIZE)
#define FLASH_AREA_3_SIZE               (FLASH_NS_PARTITION_SIZE)

/* Protected Storage */
#define FLASH_AREA_4_ID                 (5)
#define FLASH_AREA_4_OFFSET             (FLASH_AREA_3_OFFSET + FLASH_AREA_3_SIZE)
#define FLASH_AREA_4_SIZE               (0x4000)    /* 16 KB */

#else /* MCUBOOT_IMAGE_NUMBER == 1 */
/* Primary slot (S+NS) */
#define FLASH_AREA_0_ID                 (1)
#define FLASH_AREA_0_OFFSET             (FLASH_AREA_BL2_OFFSET + FLASH_AREA_BL2_SIZE)
#define FLASH_AREA_0_SIZE               (FLASH_S_PARTITION_SIZE + FLASH_NS_PARTITION_SIZE)

/* Secondary slot (S+NS) */
#define FLASH_AREA_2_ID                 (FLASH_AREA_0_ID + 1)
#define FLASH_AREA_2_OFFSET             (FLASH_AREA_0_OFFSET + FLASH_AREA_0_SIZE)
#define FLASH_AREA_2_SIZE               (FLASH_S_PARTITION_SIZE + FLASH_NS_PARTITION_SIZE)

/* Protected Storage */
#define FLASH_AREA_4_ID                 (FLASH_AREA_2_ID + 1)
#define FLASH_AREA_4_OFFSET             (FLASH_AREA_2_OFFSET + FLASH_AREA_2_SIZE)
#define FLASH_AREA_4_SIZE               (0x4000)    /* 16 KB */
#endif

/* Internal Trusted Storage */
#define FLASH_AREA_5_ID                 (FLASH_AREA_4_ID + 1)
#define FLASH_AREA_5_OFFSET             (FLASH_AREA_4_OFFSET + FLASH_AREA_4_SIZE)
#define FLASH_AREA_5_SIZE               (0x2000)    /* 8 KB */

/* NV Counters */
#define FLASH_AREA_NV_COUNTERS_ID       (FLASH_AREA_5_ID + 1)
#define FLASH_AREA_NV_COUNTERS_OFFSET   (FLASH_AREA_5_OFFSET + FLASH_AREA_5_SIZE)
#define FLASH_AREA_NV_COUNTERS_SIZE     (FLASH_AREA_IMAGE_SECTOR_SIZE)

/* Scratch area for MCUboot swap */
#define FLASH_AREA_SCRATCH_ID           (FLASH_AREA_NV_COUNTERS_ID + 1)
#define FLASH_AREA_SCRATCH_OFFSET       (0x140000)
#define FLASH_AREA_SCRATCH_SIZE         (0x10000)   /* 64 KB */

/* V32F20X flash program unit (write granularity) */
#define TFM_HAL_FLASH_PROGRAM_UNIT       (0x4)

/* ITS/PS flash driver and program unit */
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

/* Max number of status entries (MCUBoot) */
#define MCUBOOT_STATUS_MAX_ENTRIES      (FLASH_MAX_PARTITION_SIZE / \
                                         FLASH_AREA_IMAGE_SECTOR_SIZE)

/* Maximum number of image sectors (S or NS) */
#define MCUBOOT_MAX_IMG_SECTORS         (FLASH_MAX_PARTITION_SIZE / \
                                         FLASH_AREA_IMAGE_SECTOR_SIZE)

/* OTP / Provisioning area */
#define TFM_OTP_NV_COUNTERS_AREA_ADDR       (FLASH_BASE_ADDRESS + FLASH_AREA_NV_COUNTERS_OFFSET)
#define TFM_OTP_NV_COUNTERS_AREA_SIZE       (FLASH_AREA_NV_COUNTERS_SIZE)
#define TFM_OTP_NV_COUNTERS_SECTOR_SIZE     (FLASH_AREA_IMAGE_SECTOR_SIZE)
#define TFM_OTP_NV_COUNTERS_BACKUP_AREA_ADDR (FLASH_BASE_ADDRESS + FLASH_AREA_NV_COUNTERS_OFFSET + FLASH_AREA_NV_COUNTERS_SIZE)

#define FLASH_OTP_NV_COUNTERS_AREA_OFFSET   (FLASH_AREA_NV_COUNTERS_OFFSET)
#define FLASH_OTP_NV_COUNTERS_AREA_SIZE     (FLASH_AREA_NV_COUNTERS_SIZE * 2)
#define FLASH_OTP_NV_COUNTERS_SECTOR_SIZE   (FLASH_AREA_IMAGE_SECTOR_SIZE)

#endif /* __FLASH_LAYOUT_H__ */
