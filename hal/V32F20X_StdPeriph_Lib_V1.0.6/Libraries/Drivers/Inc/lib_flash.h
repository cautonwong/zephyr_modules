/**
  ******************************************************************************
  * @file    lib_flash.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   FLASH library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_FLASH_H
#define __LIB_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

#ifdef V32F20XXX_CM0_CORE
#define IS_FLASH_ALL_INSTANCE(INSTANCE) (((INSTANCE) == FLASH0))
#endif

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
#define IS_FLASH_ALL_INSTANCE(INSTANCE) (((INSTANCE) == FLASHA) || \
                                         ((INSTANCE) == FLASHB) || \
                                         ((INSTANCE) == FLASH0))
#endif

/** @defgroup FLASH_Exported_Constants
  * @{
  */

/** @defgroup Option_Bytes_Cache_CTRL 
  * @{
  */
#define FLASH_CACHE_CCR_EN              ((uint8_t)0x01)  /*!< FLASH Cache enable */
#define FLASH_CACHE_CCR_INVREQ          ((uint8_t)0x02)  /*!< FLASH Manual invalidate request */
#define FLASH_CACHE_CCR_POWREQ          ((uint8_t)0x04)  /*!< FLASH Manual SRAM power request */
#define FLASH_CACHE_CCR_POWMAN          ((uint8_t)0x08)  /*!< FLASH Power control */
#define FLASH_CACHE_CCR_MANINV          ((uint8_t)0x10)  /*!< FLASH Cache Invalidate control */
#define FLASH_CACHE_CCR_PREFETCH        ((uint8_t)0x20)  /*!< FLASH Cache Pre-fetch enable control */
#define FLASH_CACHE_CCR_STATISTICEN     ((uint8_t)0x40)  /*!< FLASH Statistics logic enable control */
/**
  * @}
  */

/** @defgroup Option_Bytes_Cache_Status
  * @{
  */
#define FLASH_CACHE_SR_Msk           ((uint8_t)0x03)  /*!< FLASH Cache Status mask */
#define FLASH_CACHE_SR_INVSTAT       ((uint8_t)0x04)  /*!< FLASH Invalidate Status */
#define FLASH_CACHE_SR_POWSTAT       ((uint8_t)0x10)  /*!< FLASH SRAM power acknowledges */
/**
  * @}
  */

/** @defgroup Option_Bytes_FLASHGFC_CTRL
  * @{
  */
#define FLASH_GFC_CTRL_CMD_MAKS         ((uint8_t)0x07)  /*!< FLASH GFC CMD mask */
#define FLASH_GFC_CTRL_CMD_READ         ((uint8_t)0x01)  /*!< FLASH GFC CMD Read */
#define FLASH_GFC_CTRL_CMD_WRITE        ((uint8_t)0x02)  /*!< FLASH GFC CMD Write */
#define FLASH_GFC_CTRL_CMD_ERASE        ((uint8_t)0x04)  /*!< FLASH GFC CMD Erase */
#define FLASH_GFC_CTRL_CMD_MERASE       ((uint8_t)0x07)  /*!< FLASH GFC CMD MErase */
/**
  * @}
  */

/** @defgroup Option_Bytes_FLASHGFC_STATUS
  * @{
  */
#define FLASH_GFC_STATUS_FINISH         ((uint8_t)0x10)  /*!< FLASH GFC Finish status */
#define FLASH_GFC_STATUS_FAIL           ((uint8_t)0x08)  /*!< FLASH GFC Fail status */
#define FLASH_GFC_STATUS_SUCCESS        ((uint8_t)0x04)  /*!< FLASH GFC Success status */
#define FLASH_GFC_STATUS_ACCEPT         ((uint8_t)0x02)  /*!< FLASH GFC Accept status */
#define FLASH_GFC_STATUS_PENDING        ((uint8_t)0x01)  /*!< FLASH GFC Pending status */
/**
  * @}
  */

/** @defgroup Option_Bytes_FLASHGFC_IRQ_STATUS_CLR
  * @{
  */
#define FLASH_GFC_IRQSTATUS_CLR_READ_OVERFLOW ((uint8_t)0x10)  /*!< FLASH GFC IRQ overflow status */
#define FLASH_GFC_IRQSTATUS_CLR_CMD_REJECT    ((uint8_t)0x08)  /*!< FLASH GFC IRQ reject status */
#define FLASH_GFC_IRQSTATUS_CLR_CMD_FAIL      ((uint8_t)0x04)  /*!< FLASH GFC IRQ fail status */
#define FLASH_GFC_IRQSTATUS_CLR_CMD_SUCCESS   ((uint8_t)0x02)  /*!< FLASH GFC IRQ success status */
#define FLASH_GFC_IRQSTATUS_CLR_CMD_ACCEPT    ((uint8_t)0x01)  /*!< FLASH GFC IRQ accept status */
/**
  * @}
  */

/** @defgroup Option_Bytes_FLASHSFC_INFO0_CTRL
  * @{
  */
#define FLASH_INFO_CTRL_SELINFO_MAKS     ((uint8_t)0x04)
#define FLASH_INFO_CTRL_SELINFO0         ((uint8_t)0x00)
#define FLASH_INFO_CTRL_SELINFO1         ((uint8_t)0x04)
#define FLASH_INFO_CTRL_CMD_MAKS         ((uint8_t)0x03)
#define FLASH_INFO_CTRL_CMD_READ         ((uint8_t)0x00)
#define FLASH_INFO_CTRL_CMD_WRITE        ((uint8_t)0x01)
#define FLASH_INFO_CTRL_CMD_ERASE        ((uint8_t)0x02)
#define FLASH_INFO_CTRL_CMD_MERASE       ((uint8_t)0x03)
/**
  * @}
  */

/** @defgroup Option_Bytes_FLASHSFC_STATUS
  * @{
  */
#define FLASH_SFC_STATUS_MAKS         ((uint8_t)0x07)
#define FLASH_SFC_STATUS_IDLE         ((uint8_t)0x00)
#define FLASH_SFC_STATUS_POWER        ((uint8_t)0x01)
#define FLASH_SFC_STATUS_BUSY         ((uint8_t)0x02)
#define FLASH_SFC_STATUS_READ         ((uint8_t)0x03)
/**
  * @}
  */

/** @defgroup Option_Bytes_FLASH_INFO_STATUS
  * @{
  */
#define FLASH_INFO_STATUS_MASK            ((uint8_t)0x01)
#define INFO_STATUS_BUSY                  ((uint8_t)0x01)
#define INFO_STATUS_IDLE                  ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup Option_Bytes_FLASH_POWER_STATUS
  * @{
  */
#define FLASH_POWER_ON                    ((uint8_t)0x01)
#define FLASH_POWER_OFF                   ((uint8_t)0x00)
#define FLASH_POWERREADY_ON               ((uint8_t)0x02)
#define FLASH_POWERREADY_OFF              ((uint8_t)0x00)
/**
  * @}
  */

#define IS_FLASH_ADDRESS(ADDR)            ((((ADDR) >= 0x00000000) && ((ADDR) < 0x00200000)) || \
                                           (((ADDR) >= 0x01000000) && ((ADDR) < 0x01040000)))

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions
  * @{
  */

int FLASH_WaitForIdle(FLASH_Type *FLASHx);
void FLASH_SetCycle(FLASH_Type *FLASHx, uint32_t sysclock);
int FLASH_PageErase(FLASH_Type *FLASHx, uint32_t PageAddr);
int FLASH_ProgramByte(FLASH_Type *FLASHx, uint32_t Addr, const uint8_t *ByteBuffer, uint32_t Length);
int FLASH_ProgramWord(FLASH_Type *FLASHx, uint32_t Addr, const uint32_t *WordBuffer, uint32_t Length);
void FLASH_ChipErase(FLASH_Type *FLASHx);
int FLASH_INFO0ReadWord(FLASH_Type *FLASHx, uint32_t Addr, uint32_t *WordBuffer, uint32_t Length);
int FLASH_INFO1ReadWord(FLASH_Type *FLASHx, uint32_t Addr, uint32_t *WordBuffer, uint32_t Length);

void FLASH_Cache_Init(FLASH_Type *FLASHx);
void FLASH_Cache_Cmd(FLASH_Type *FLASHx, FunctionalState NewState);
void FLASH_Cache_Refresh(FLASH_Type *FLASHx);
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif
     
#endif  /* __FLASH_H */

/*********************************** END OF FILE ******************************/
