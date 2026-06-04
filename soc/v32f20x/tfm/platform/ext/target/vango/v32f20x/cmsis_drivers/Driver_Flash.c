/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * CMSIS Flash Driver for Vango V32F20x
 * This provides TF-M with the CMSIS Driver_Flash interface backed by
 * V32F20x's internal flash (lib_flash HAL)
 */

#include "Driver_Flash.h"
#include "region_defs.h"
#include "flash_layout.h"
#include <string.h>
#include <stdint.h>

#ifndef ARG_UNUSED
#define ARG_UNUSED(arg)  ((void)arg)
#endif

/* Flash operations implemented via generic CMSIS-style stubs.
 * TODO: Vango engineers connect these to lib_flash.h HAL calls:
 *   FLASH_PageErase(FLASH0, addr)
 *   FLASH_ProgramWord(FLASH0, dest, src, count)
 */

#define FLASH_DRIVER_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0)

static const ARM_DRIVER_VERSION FlashDriverVersion = {
    ARM_FLASH_API_VERSION,
    FLASH_DRIVER_VERSION
};

static const ARM_FLASH_CAPABILITIES FlashDriverCapabilities = {
    .event_ready  = 0,
    .data_width   = 2,  /* 32-bit */
    .erase_chip   = 0,
};

static ARM_DRIVER_VERSION GetVersion(void)
{
    return FlashDriverVersion;
}

static ARM_FLASH_CAPABILITIES GetCapabilities(void)
{
    return FlashDriverCapabilities;
}

static int32_t Initialize(ARM_Flash_SignalEvent_t cb_event)
{
    ARG_UNUSED(cb_event);
    return ARM_DRIVER_OK;
}

static int32_t Uninitialize(void)
{
    return ARM_DRIVER_OK;
}

static int32_t PowerControl(ARM_POWER_STATE state)
{
    ARG_UNUSED(state);
    return ARM_DRIVER_OK;
}

static int32_t ReadData(uint32_t addr, void *data, uint32_t cnt)
{
    /* V32F20x internal flash is memory-mapped at 0x08000000 */
    memcpy(data, (const void *)(FLASH_BASE_ADDRESS + addr), cnt);
    return ARM_DRIVER_OK;
}

static int32_t ProgramData(uint32_t addr, const void *data, uint32_t cnt)
{
    /*
     * TODO: Vango engineers replace with:
     *   FLASH_ProgramWord(FLASH0, FLASH_BASE_ADDRESS + addr, (uint32_t *)data, cnt/4)
     */
    ARG_UNUSED(addr);
    ARG_UNUSED(data);
    ARG_UNUSED(cnt);
    return ARM_DRIVER_OK;
}

static int32_t EraseSector(uint32_t addr)
{
    /*
     * TODO: Vango engineers replace with:
     *   FLASH_PageErase(FLASH0, FLASH_BASE_ADDRESS + addr)
     */
    ARG_UNUSED(addr);
    return ARM_DRIVER_OK;
}

static int32_t EraseChip(void)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_FLASH_STATUS GetStatus(void)
{
    ARM_FLASH_STATUS status = {0};
    return status;
}

static ARM_FLASH_INFO FlashInfo = {
    .sector_info  = NULL,
    .sector_count = FLASH_TOTAL_SIZE / FLASH_AREA_IMAGE_SECTOR_SIZE,
    .sector_size  = FLASH_AREA_IMAGE_SECTOR_SIZE,
    .page_size    = 4,        /* 4-byte (word) write */
    .program_unit = 4,
    .erased_value = 0xFF,
};

static ARM_FLASH_INFO* GetInfo(void)
{
    return &FlashInfo;
}

ARM_DRIVER_FLASH Driver_FLASH0 = {
    .GetVersion      = GetVersion,
    .GetCapabilities = GetCapabilities,
    .Initialize      = Initialize,
    .Uninitialize    = Uninitialize,
    .PowerControl    = PowerControl,
    .ReadData        = ReadData,
    .ProgramData     = ProgramData,
    .EraseSector     = EraseSector,
    .EraseChip       = EraseChip,
    .GetStatus       = GetStatus,
    .GetInfo         = GetInfo,
};
