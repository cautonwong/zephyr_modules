/**
  ******************************************************************************
  * @file    lib_crypt.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2018-09-27
  * @brief   CRYPT library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_CRYPT_H
#define __LIB_CRYPT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

#define IS_CRYPT_ADDR(__ADDR__)        (((__ADDR__) < 0x4000) &&\
                                       (((__ADDR__) & 0x3UL) == 0UL))
/*
// Length @ CRYPT0_StartAdd
//        @ CRYPT0_StartMultiply
//        @ CRYPT0_StartSub
//        @ CRYPT0_StartRShift1
*/
#define CRYPT_LENGTH_32                (0x0U << 8)
#define CRYPT_LENGTH_64                (0x1U << 8)
#define CRYPT_LENGTH_96                (0x2U << 8)
#define CRYPT_LENGTH_128               (0x3U << 8)
#define CRYPT_LENGTH_160               (0x4U << 8)
#define CRYPT_LENGTH_192               (0x5U << 8)
#define CRYPT_LENGTH_224               (0x6U << 8)
#define CRYPT_LENGTH_256               (0x7U << 8)
#define CRYPT_LENGTH_288               (0x8U << 8)
#define CRYPT_LENGTH_320               (0x9U << 8)
#define CRYPT_LENGTH_352               (0xAU << 8)  
#define CRYPT_LENGTH_384               (0xBU << 8)
#define CRYPT_LENGTH_416               (0xCU << 8)
#define CRYPT_LENGTH_448               (0xDU << 8)
#define CRYPT_LENGTH_480               (0xEU << 8)
#define CRYPT_LENGTH_512               (0xFU << 8)
#define IS_CRYPT_LENGTH(__LENGTH__)    (((__LENGTH__) == CRYPT_LENGTH_32)  ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_64)  ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_32)  ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_96)  ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_128) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_160) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_192) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_224) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_256) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_288) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_320) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_352) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_384) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_416) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_448) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_480) ||\
                                        ((__LENGTH__) == CRYPT_LENGTH_512))
/*
// Nostop @ CRYPT0_StartAdd
//        @ CRYPT0_StartMultiply
//        @ CRYPT0_StartSub
//        @ CRYPT0_StartRShift1
*/
#define CRYPT_STOPCPU                   (0)
#define CRYPT_NOSTOPCPU                 (1UL << 15)
#define IS_CRYPT_NOSTOP(__NOSTOP__)     (((__NOSTOP__) == CRYPT_STOPCPU) ||\
                                         ((__NOSTOP__) == CRYPT_NOSTOPCPU))


/* Exported Functions ------------------------------------------------------- */
void CRYPTO_AddressAConfig(uint16_t AddrA);
void CRYPTO_AddressBConfig(uint16_t AddrB);
void CRYPTO_AddressOConfig(uint16_t AddrO);
uint8_t CRYPTO_GetCarryBorrowBit(void);
void CRYPTO_StartAdd(uint32_t Length, uint32_t Nostop);
void CRYPTO_StartMultiply(uint32_t Length, uint32_t Nostop);
void CRYPTO_StartSub(uint32_t Length, uint32_t Nostop);
void CRYPTO_StartRShift1(uint32_t Length, uint32_t Nostop);
void CRYPTO_WaitForLastOperation(void);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_CRYPT_H */

/*********************************** END OF FILE ******************************/
