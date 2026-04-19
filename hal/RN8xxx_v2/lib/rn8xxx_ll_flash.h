/******************************************************************************
 * @file     rn8xxx_ll_flash.h
 * @brief    non-valatile flash memory driver header
 * @author   Renergy Technology
 *
 * @note
 * Copyright (C) , Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#ifndef RN8XXX_LL_FLASH_H_
#define RN8XXX_LL_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rn8xxx_ll_devices.h"

/**********************************************************
  api return
**********************************************************/
typedef enum
{
    FLASH_PASS = 0,
    FLASH_COUNT_ERROR = 6,
    FLASH_INVALID_PAGE = 8,
    FLASH_SRC_ADDR_NOT_ALIGN = 10,
    FLASH_SRC_ADDR_NOT_MAPPED = 11,
    FLASH_DST_ADDR_NOT_ALIGN = 12,
    FLASH_DST_ADDR_NOT_MAPPED = 13,
    FLASH_VOL_INVALID = 20,
    FLASH_CLK_ERROR = 21
} eFlashRet_TypeDef;

/**
 * @brief flash page erase
 *
 * @param pg page number
 * @return eFlashRet_TypeDef interface result
 */
eFlashRet_TypeDef LL_FLASH_PageErase(unsigned int pg);
#define flashPageErase LL_FLASH_PageErase

/**
 * @brief flash sector erase
 *
 * @param sec sector number
 * @return eFlashRet_TypeDef interface result
 */
eFlashRet_TypeDef LL_FLASH_SectorErase(unsigned int sec);
#define flashSectorErase LL_FLASH_SectorErase

/**
 * @brief flash program
 *
 * @param dst_addr flash program address, must page aligned
 * @param src_addr program source address
 * @param len program byte length. When the len exceeds the page size,
 *   the len must be page aligned. The last page programming supports
 *   non-page aligned, the remaing data will be filled with 0xff
 * @return eFlashRet_TypeDef interface result
 */
eFlashRet_TypeDef LL_FLASH_Program(unsigned int dst_addr, unsigned int src_addr, unsigned int len);
#define flashProgram LL_FLASH_Program

/**
 * @brief flash cache enable
 *
 */
void    LL_FLASH_CacheOn(void);
#define cacheOn LL_FLASH_CacheOn

/**
 * @brief flash cache disable
 *
 */
void    LL_FLASH_CacheOff(void);
#define cacheOff LL_FLASH_CacheOff

#ifdef __cplusplus
}
#endif

#endif
/* r1944 */
