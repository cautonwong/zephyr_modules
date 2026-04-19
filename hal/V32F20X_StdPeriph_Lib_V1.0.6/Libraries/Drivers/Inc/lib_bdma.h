/**
  ******************************************************************************
  * @file    lib_bdma.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   This file contains all the functions prototypes for the BDMA
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_BDMA_H
#define __LIB_BDMA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup BDMA
  * @{
  */

/** @defgroup Channel
  * @{
  */

#define BDMA_CHANNEL_0                  ((uint32_t)0x00000000)
#define BDMA_CHANNEL_1                  ((uint32_t)0x00000001)
#define BDMA_CHANNEL_2                  ((uint32_t)0x00000002)
#define BDMA_CHANNEL_3                  ((uint32_t)0x00000003)
#define IS_BDMA_CHANNEL(__CH__)         (((__CH__) == BDMA_CHANNEL_0) || \
                                         ((__CH__) == BDMA_CHANNEL_1) || \
                                         ((__CH__) == BDMA_CHANNEL_2) || \
                                         ((__CH__) == BDMA_CHANNEL_3))

/**
  * @}
  */

/** @defgroup Request Source
  * @{
  */

typedef enum {
  BDMA_REQSRC_SOFT                      = 0,
  BDMA_REQSRC_UART0_0_TX                = 2,
  BDMA_REQSRC_UART0_0_RX                = 3,
  BDMA_REQSRC_UART0_1_TX                = 4,
  BDMA_REQSRC_UART0_1_RX                = 5,
  BDMA_REQSRC_UART0_2_TX                = 6,
  BDMA_REQSRC_UART0_2_RX                = 7,
  BDMA_REQSRC_UART0_3_TX                = 8,
  BDMA_REQSRC_UART0_3_RX                = 9,
  BDMA_REQSRC_UART0_4_TX                = 10,
  BDMA_REQSRC_UART0_4_RX                = 11,
  BDMA_REQSRC_UART0_5_TX                = 12,
  BDMA_REQSRC_UART0_5_RX                = 13,
  BDMA_REQSRC_ISO78162_TX             = 14,
  BDMA_REQSRC_ISO78162_RX             = 15,
  BDMA_REQSRC_ISO78163_TX             = 16,
  BDMA_REQSRC_ISO78163_RX             = 17,
  BDMA_REQSRC_BTMR0_0                   = 18,
  BDMA_REQSRC_BTMR0_1                   = 19,
  BDMA_REQSRC_BTMR0_2                   = 20,
  BDMA_REQSRC_BTMR0_3                   = 21,
  BDMA_REQSRC_BSPI0_TX                 = 26,
  BDMA_REQSRC_BSPI0_RX                 = 27,
  BDMA_REQSRC_BSPI1_TX                 = 28,
  BDMA_REQSRC_BSPI1_RX                 = 29,
  BDMA_REQSRC_BSPI2_TX                 = 30,
  BDMA_REQSRC_BSPI2_RX                 = 31,
  BDMA_REQSRC_BSPI3_TX                 = 32,
  BDMA_REQSRC_BSPI3_RX                 = 33,
  BDMA_REQSRC_BSPI4_TX                 = 34,
  BDMA_REQSRC_BSPI4_RX                 = 35,
  BDMA_REQSRC_BSPI5_TX                 = 36,
  BDMA_REQSRC_BSPI5_RX                 = 37,
  BDMA_REQSRC_WAVER0                    = 38
} BDMA_ReqSrcType;
#define IS_BDMA_REQSRC(__SRC__)        (((__SRC__) == BDMA_REQSRC_SOFT)          || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_0_TX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_0_RX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_1_TX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_1_RX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_2_TX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_2_RX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_3_TX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_3_RX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_4_TX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_4_RX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_5_TX)    || \
                                        ((__SRC__) == BDMA_REQSRC_UART0_5_RX)    || \
                                        ((__SRC__) == BDMA_REQSRC_ISO78162_TX) || \
                                        ((__SRC__) == BDMA_REQSRC_ISO78162_RX) || \
                                        ((__SRC__) == BDMA_REQSRC_ISO78163_TX) || \
                                        ((__SRC__) == BDMA_REQSRC_ISO78163_RX) || \
                                        ((__SRC__) == BDMA_REQSRC_BTMR0_0)       || \
                                        ((__SRC__) == BDMA_REQSRC_BTMR0_1)       || \
                                        ((__SRC__) == BDMA_REQSRC_BTMR0_2)       || \
                                        ((__SRC__) == BDMA_REQSRC_BTMR0_3)       || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI0_TX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI0_RX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI1_TX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI1_RX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI2_TX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI2_RX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI3_TX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI3_RX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI4_TX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI4_RX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI5_TX)     || \
                                        ((__SRC__) == BDMA_REQSRC_BSPI5_RX)     || \
                                        ((__SRC__) == BDMA_REQSRC_WAVER0))

/**
  * @}
  */

/** @defgroup InitType
  * @{
  */

typedef struct
{
  uint32_t DestAddr;          /* destination address */
  uint32_t SrcAddr;           /* source address */
  uint8_t  FrameLen;          /* Frame length */
  uint8_t  PackLen;           /* Package length */
  uint32_t ContMode;          /* Continuous mode */
  uint32_t TransMode;         /* Transfer mode */  
  BDMA_ReqSrcType ReqSrc;     /* DMA request source */
  uint32_t DestAddrMode;      /* Destination address mode */
  uint32_t SrcAddrMode;       /* Source address mode */
  uint32_t TransSize;         /* Transfer size mode */
} BDMA_InitType;

/**
  * @}
  */

/** @defgroup Cont Mode
  * @{
  */

#define BDMA_CONTMODE_ENABLE            ((uint32_t)0x00002000)
#define BDMA_CONTMODE_DISABLE           ((uint32_t)0x00000000)
#define IS_BDMA_CONTMOD(__CONTMOD__)    (((__CONTMOD__) == BDMA_CONTMODE_ENABLE) || \
                                         ((__CONTMOD__) == BDMA_CONTMODE_DISABLE))

/**
  * @}
  */

/** @defgroup Trans Mode
  * @{
  */

#define BDMA_TRANSMODE_SINGLE           ((uint32_t)0x00000000)
#define BDMA_TRANSMODE_PACK             ((uint32_t)0x00001000)
#define IS_BDMA_TRANSMOD(__TRANSMOD__)  (((__TRANSMOD__) == BDMA_TRANSMODE_SINGLE) || \
                                         ((__TRANSMOD__) == BDMA_TRANSMODE_PACK))

/**
  * @}
  */

/** @defgroup Dest Addr Mode
  * @{
  */

#define BDMA_DESTADDRMODE_FIX           ((uint32_t)0x00000000)
#define BDMA_DESTADDRMODE_PEND          ((uint32_t)0x00000020)
#define BDMA_DESTADDRMODE_FEND          ((uint32_t)0x00000040)
#define IS_BDMA_DESTADDRMOD(__DAM__)    (((__DAM__) == BDMA_DESTADDRMODE_FIX)  || \
                                         ((__DAM__) == BDMA_DESTADDRMODE_PEND) || \
                                         ((__DAM__) == BDMA_DESTADDRMODE_FEND))

/**
  * @}
  */

/** @defgroup Source Addr Mode
  * @{
  */

#define BDMA_SRCADDRMODE_FIX            ((uint32_t)0x00000000)
#define BDMA_SRCADDRMODE_PEND           ((uint32_t)0x00000008)
#define BDMA_SRCADDRMODE_FEND           ((uint32_t)0x00000010)
#define IS_BDMA_SRCADDRMOD(__SAM__)     (((__SAM__) == BDMA_SRCADDRMODE_FIX)  || \
                                         ((__SAM__) == BDMA_SRCADDRMODE_PEND) || \
                                         ((__SAM__) == BDMA_SRCADDRMODE_FEND))

/**
  * @}
  */

/** @defgroup Trans Size
  * @{
  */

#define BDMA_TRANSSIZE_BYTE             ((uint32_t)0x00000000)
#define BDMA_TRANSSIZE_HWORD            ((uint32_t)0x00000002)
#define BDMA_TRANSSIZE_WORD             ((uint32_t)0x00000004)
#define IS_BDMA_TRANSSIZE(__TSIZE__)    (((__TSIZE__) == BDMA_TRANSSIZE_BYTE)  || \
                                         ((__TSIZE__) == BDMA_TRANSSIZE_HWORD) || \
                                         ((__TSIZE__) == BDMA_TRANSSIZE_WORD))

/**
  * @}
  */

/** @defgroup Aligned Address
  * @{
  */
  
#define IS_BDMA_ALIGNEDADDR_WORD(__ADDRW__)    (((__ADDRW__) & 0x3U) == 0U)
#define IS_BDMA_ALIGNEDADDR_HWORD(__ADDRHW__)  (((__ADDRHW__) & 0x1U) == 0U)

/**
  * @}
  */

/** @defgroup AES InitType
  * @{
  */

typedef struct
{
  uint32_t Mode;             /* AES mode */
  uint32_t Direction;        /* Direction */
  uint32_t *KeyStr;          /* AES key */
} BDMA_AESInitType;

/**
  * @}
  */

/** @defgroup AES Mode
  * @{
  */

#define BDMA_AESMODE_128                ((uint32_t)0x00000000)
#define BDMA_AESMODE_192                ((uint32_t)0x00000004)
#define BDMA_AESMODE_256                ((uint32_t)0x00000008)
#define IS_BDMA_AESMOD(__AESMOD__)      (((__AESMOD__) == BDMA_AESMODE_128) || \
                                         ((__AESMOD__) == BDMA_AESMODE_192) || \
                                         ((__AESMOD__) == BDMA_AESMODE_256))

/**
  * @}
  */

/** @defgroup AES Direction
  * @{
  */

#define BDMA_AESDIRECTION_DECODE        ((uint32_t)0x00000000)
#define BDMA_AESDIRECTION_ENCODE        ((uint32_t)0x00000001)
#define IS_BDMA_AESDIR(__AESDIR__)      (((__AESDIR__) == BDMA_AESDIRECTION_DECODE) || \
                                         ((__AESDIR__) == BDMA_AESDIRECTION_ENCODE))

/**
  * @}
  */

/** @defgroup Int Mask
  * @{
  */

#define BDMA_INT_C3DA                   ((uint32_t)0x00000800)
#define BDMA_INT_C2DA                   ((uint32_t)0x00000400)
#define BDMA_INT_C1DA                   ((uint32_t)0x00000200)
#define BDMA_INT_C0DA                   ((uint32_t)0x00000100)
#define BDMA_INT_C3FE                   ((uint32_t)0x00000080)
#define BDMA_INT_C2FE                   ((uint32_t)0x00000040)
#define BDMA_INT_C1FE                   ((uint32_t)0x00000020)
#define BDMA_INT_C0FE                   ((uint32_t)0x00000010)
#define BDMA_INT_C3PE                   ((uint32_t)0x00000008)
#define BDMA_INT_C2PE                   ((uint32_t)0x00000004)
#define BDMA_INT_C1PE                   ((uint32_t)0x00000002)
#define BDMA_INT_C0PE                   ((uint32_t)0x00000001)
#define BDMA_INT_MASK                   ((uint32_t)0x00000FFF)
#define IS_BDMA_INTC(__INT__)           ((((__INT__) & BDMA_INT_MASK) != 0U) && \
                                         (((__INT__) & ~BDMA_INT_MASK) == 0U))
#define IS_BDMA_INTR(__INT__)           (((__INT__) == BDMA_INT_C3DA) || \
                                         ((__INT__) == BDMA_INT_C2DA) || \
                                         ((__INT__) == BDMA_INT_C1DA) || \
                                         ((__INT__) == BDMA_INT_C0DA) || \
                                         ((__INT__) == BDMA_INT_C3FE) || \
                                         ((__INT__) == BDMA_INT_C2FE) || \
                                         ((__INT__) == BDMA_INT_C1FE) || \
                                         ((__INT__) == BDMA_INT_C0FE) || \
                                         ((__INT__) == BDMA_INT_C3PE) || \
                                         ((__INT__) == BDMA_INT_C2PE) || \
                                         ((__INT__) == BDMA_INT_C1PE) || \
                                         ((__INT__) == BDMA_INT_C0PE))

/**
  * @}
  */

/** @defgroup Flag
  * @{
  */

#define BDMA_FLAG_C0BUSY                ((uint32_t)0x00000001)
#define BDMA_FLAG_C1BUSY                ((uint32_t)0x00000002)
#define BDMA_FLAG_C2BUSY                ((uint32_t)0x00000004)
#define BDMA_FLAG_C3BUSY                ((uint32_t)0x00000008)
#define IS_BDMA_FLAG(__FLAG__)          (((__FLAG__) == BDMA_FLAG_C0BUSY) || \
                                         ((__FLAG__) == BDMA_FLAG_C1BUSY) || \
                                         ((__FLAG__) == BDMA_FLAG_C2BUSY) || \
                                         ((__FLAG__) == BDMA_FLAG_C3BUSY))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @defgroup DMA_CM0_Exported_Functions
  * @{
  */

void BDMA_DeInit(uint32_t Channel);
void BDMA_StructInit(BDMA_InitType *BDMA_InitStruct);
void BDMA_Init(BDMA_InitType *BDMA_InitStruct, uint32_t Channel);

void BDMA_Cmd(uint32_t Channel, FunctionalState NewState);
void BDMA_StopCmd(uint32_t Channel, FunctionalState NewState);

FlagStatus BDMA_GetFlagStatus(uint32_t Flag);

void BDMA_INTConfig(uint32_t INTMask, FunctionalState NewState);
INTStatus BDMA_GetINTStatus(uint32_t INTMask);
void BDMA_ClearINTStatus(uint32_t INTMask);

uint8_t BDMA_GetFrameLenTransferred(uint32_t Channel);
uint8_t BDMA_GetPackLenTransferred(uint32_t Channel);

void BDMA_AESDeInit(void);
void BDMA_AESStructInit(BDMA_AESInitType *BDMA_AESInitStruct);
void BDMA_AESInit(BDMA_AESInitType *AES_InitStruct);

void BDMA_AESCmd(FunctionalState NewState);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_BDMA_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/*********************************** END OF FILE ******************************/
