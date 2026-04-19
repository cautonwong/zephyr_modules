/**
  * @file    lib_enceng.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   Header file for lib_enceng.c
******************************************************************************/
#ifndef __LIB_ENCENG_H
#define __LIB_ENCENG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** 
  * @brief     Issue a new encryption or hash
  * @{
  */
#define ENCENG_NEW                          (1 << 11)

/** 
  * @brief     Issue the engine start
  * @{
  */
#define ENCENG_START                       (1 << 0)

/** 
  * @brief     Command has been finished
  * @{
  */
#define ENCENG_CMD_DONE                    (1 << 0)

#define IS_ENCENG_INT(I)                   ((I) == ENCENG_CMD_DONE)

/** 
  * @brief   ENCENG Init structure definition  
  */ 
typedef struct
{
  uint32_t ENCENG_HmacKeySize;
  uint32_t ENCENG_KeySwap;
  uint32_t ENCENG_DataSwap;
  uint32_t ENCENG_HashSelect;
  uint32_t ENCENG_KpadEnable;
  uint32_t ENCENG_EncryptKeySize;
  uint32_t ENCENG_EncryptSelect;
  uint32_t ENCENG_EncryptDirection;
  uint32_t ENCENG_EncryptMode;
  uint32_t ENCENG_KeyIndex;
  uint32_t ENCENG_KeyIndexEnable;
  uint32_t ENCENG_AlgoSelect;
}ENCENG_InitType;

/** 
  * @brief    The key size of HMAC
  * @{
  */ 
#define ENCENG_HmacKeySize_SHIFT           16
#define ENCENG_HmacKeySize_MASK            (0xF << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_1WORD           (0 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_2WORD           (1 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_3WORD           (2 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_4WORD           (3 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_5WORD           (4 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_6WORD           (5 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_7WORD           (6 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_8WORD           (7 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_9WORD           (8 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_10WORD          (9 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_11WORD          (10 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_12WORD          (11 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_13WORD          (12 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_14WORD          (13 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_15WORD          (14 << ENCENG_HmacKeySize_SHIFT)
#define ENCENG_HmacKeySize_16WORD          (15 << ENCENG_HmacKeySize_SHIFT)

#define IS_ENCENG_HMAC_KEY_SIZE(S)   (((S) == ENCENG_HmacKeySize_1WORD)\
                                      ||((S) == ENCENG_HmacKeySize_2WORD)\
                                      ||((S) == ENCENG_HmacKeySize_3WORD)\
                                      ||((S) == ENCENG_HmacKeySize_4WORD)\
                                      ||((S) == ENCENG_HmacKeySize_5WORD)\
                                      ||((S) == ENCENG_HmacKeySize_6WORD)\
                                      ||((S) == ENCENG_HmacKeySize_7WORD)\
                                      ||((S) == ENCENG_HmacKeySize_8WORD)\
                                      ||((S) == ENCENG_HmacKeySize_9WORD)\
                                      ||((S) == ENCENG_HmacKeySize_10WORD)\
                                      ||((S) == ENCENG_HmacKeySize_11WORD)\
                                      ||((S) == ENCENG_HmacKeySize_12WORD)\
                                      ||((S) == ENCENG_HmacKeySize_13WORD)\
                                      ||((S) == ENCENG_HmacKeySize_14WORD)\
                                      ||((S) == ENCENG_HmacKeySize_15WORD)\
                                      ||((S) == ENCENG_HmacKeySize_16WORD))
/** 
  * @brief    Swap the key input
  * @{
  */ 
#define ENCENG_KeySwap_SHIFT            15
#define ENCENG_KeySwap_MASK             (1 << ENCENG_KeySwap_SHIFT)
#define ENCENG_KeySwap_LSB              (0 << ENCENG_KeySwap_SHIFT)
#define ENCENG_KeySwap_MSB              (1 << ENCENG_KeySwap_SHIFT)

#define IS_ENCENG_KEY_SWAP(S)         (((S) == ENCENG_KeySwap_LSB)\
                                       ||((S) == ENCENG_KeySwap_MSB))

/** 
  * @brief    Swap bytes in the word for hash and encryption
  * @{
  */ 
#define ENCENG_DataSwap_SHIFT            14
#define ENCENG_DataSwap_MASK             (1 << ENCENG_DataSwap_SHIFT)
#define ENCENG_DataSwap_LSB              (0 << ENCENG_DataSwap_SHIFT)
#define ENCENG_DataSwap_MSB              (1 << ENCENG_DataSwap_SHIFT)

#define IS_ENCENG_DATA_SWAP(S)        (((S) == ENCENG_DataSwap_LSB)\
                                       ||((S) == ENCENG_DataSwap_MSB))

/** 
  * @brief    Hash algorithm select
  * @{
  */ 
#define ENCENG_HashSelect_SHIFT          12
#define ENCENG_HashSelect_MASK           (3 << ENCENG_HashSelect_SHIFT)
#define ENCENG_HashSelect_SHA1           (0 << ENCENG_HashSelect_SHIFT)
#define ENCENG_HashSelect_SHA256         (1 << ENCENG_HashSelect_SHIFT)
#define ENCENG_HashSelect_SM3            (2 << ENCENG_HashSelect_SHIFT)

#define IS_ENCENG_HASH_SELECT(S)      (((S) == ENCENG_HashSelect_SHA1)\
                                       ||((S) == ENCENG_HashSelect_SHA256)\
                                       ||((S) == ENCENG_HashSelect_SM3))

/** 
  * @brief     Enable the IPAD and OPAD in HMAC
  * @{
  */
#define ENCENG_KpadEnable_SHIFT          10
#define ENCENG_KpadEnable_MASK           (1 << ENCENG_KpadEnable_SHIFT)
#define ENCENG_KpadEnable_Enable         (1 << ENCENG_KpadEnable_SHIFT)
#define ENCENG_KpadEnable_Disable        (0 << ENCENG_KpadEnable_SHIFT)

#define IS_ENCENG_KPAD(P)             (((P) == ENCENG_KpadEnable_Enable)\
                                       ||((P) == ENCENG_KpadEnable_Disable))

/** 
  * @brief     The size of Encryption Key
  * @{
  */
#define ENCENG_EncryptKeySize_SHIFT      8
#define ENCENG_EncryptKeySize_MASK       (3 << ENCENG_EncryptKeySize_SHIFT)
#define ENCENG_EncryptKeySize_128BIT     (0 << ENCENG_EncryptKeySize_SHIFT)
#define ENCENG_EncryptKeySize_192BIT     (1 << ENCENG_EncryptKeySize_SHIFT)
#define ENCENG_EncryptKeySize_256BIT     (2 << ENCENG_EncryptKeySize_SHIFT)

#define IS_ENCENG_ENCRYPT_KEY_SIZE(S) (((S) == ENCENG_EncryptKeySize_128BIT)\
                                       ||((S) == ENCENG_EncryptKeySize_192BIT)\
                                       ||((S) == ENCENG_EncryptKeySize_256BIT))

/** 
  * @brief     Select the encryption algorithm
  * @{
  */
#define ENCENG_EncryptSelect_SHIFT       7
#define ENCENG_EncryptSelect_MASK        (1 << ENCENG_EncryptSelect_SHIFT)
#define ENCENG_EncryptSelect_AES         (0 << ENCENG_EncryptSelect_SHIFT)
#define ENCENG_EncryptSelect_SM4         (1 << ENCENG_EncryptSelect_SHIFT)

#define IS_ENCENG_ENCRYPT_SELECT(S)   (((S) == ENCENG_EncryptSelect_AES)\
                                       ||((S) == ENCENG_EncryptSelect_SM4))

/** 
  * @brief     Encrypt or decrypt select
  * @{
  */
#define ENCENG_EncryptDirection_SHIFT       6
#define ENCENG_EncryptDirection_MASK        (1 << ENCENG_EncryptDirection_SHIFT)
#define ENCENG_EncryptDirection_ENCRYPT     (0 << ENCENG_EncryptDirection_SHIFT)
#define ENCENG_EncryptDirection_DECRYPT     (1 << ENCENG_EncryptDirection_SHIFT)

#define IS_ENCENG_ENCRYPT_DIRECTION(D) (((D) == ENCENG_EncryptDirection_ENCRYPT)\
                                        ||((D) == ENCENG_EncryptDirection_DECRYPT))

/** 
  * @brief     Encryption or decryption mode
  * @{
  */
#define ENCENG_EncryptMode_SHIFT            4
#define ENCENG_EncryptMode_MASK             (3 << ENCENG_EncryptMode_SHIFT)
#define ENCENG_EncryptMode_ECB              (0 << ENCENG_EncryptMode_SHIFT)
#define ENCENG_EncryptMode_CBC              (1 << ENCENG_EncryptMode_SHIFT)
#define ENCENG_EncryptMode_CTR              (2 << ENCENG_EncryptMode_SHIFT)

#define IS_ENCENG_ENCRYPT_MODE(M)     (((M) == ENCENG_EncryptMode_ECB)\
                                       ||((M) == ENCENG_EncryptMode_CBC)\
                                       ||((M) == ENCENG_EncryptMode_CTR))

/** 
  * @brief     Key index
  * @{
  */
#define ENCENG_KeyIndex_SHIFT               2
#define ENCENG_KeyIndex_MASK                (3 << ENCENG_KeyIndex_SHIFT)
#define ENCENG_KeyIndex_0                   (0 << ENCENG_KeyIndex_SHIFT)
#define ENCENG_KeyIndex_1                   (1 << ENCENG_KeyIndex_SHIFT)
#define ENCENG_KeyIndex_2                   (2 << ENCENG_KeyIndex_SHIFT)
#define ENCENG_KeyIndex_3                   (3 << ENCENG_KeyIndex_SHIFT)

#define IS_ENCENG_KEY_INDEX(I)        (((I) == ENCENG_KeyIndex_0)\
                                       ||((I) == ENCENG_KeyIndex_1)\
                                       ||((I) == ENCENG_KeyIndex_2)\
                                       ||((I) == ENCENG_KeyIndex_3))

/** 
  * @brief     Key index enable
  * @{
  */
#define ENCENG_KeyIndexEnable_SHIFT          1
#define ENCENG_KeyIndexEnable_MASK           (0 << ENCENG_KeyIndexEnable_SHIFT)
#define ENCENG_KeyIndexEnable_Enable         (1 << ENCENG_KeyIndexEnable_SHIFT)
#define ENCENG_KeyIndexEnable_Disable        (0 << ENCENG_KeyIndexEnable_SHIFT)

#define IS_ENCENG_KEY_INDEX_ENABLE(E) (((E) == ENCENG_KeyIndexEnable_Enable)\
                                       ||((E) == ENCENG_KeyIndexEnable_Disable))

/** 
  * @brief     Encryption or hash algorithm select
  * @{
  */
#define ENCENG_AlgoSelect_SHIFT               0
#define ENCENG_AlgoSelect_MASK                (1 << ENCENG_AlgoSelect_SHIFT)
#define ENCENG_AlgoSelect_ENCRYPT             (1 << ENCENG_AlgoSelect_SHIFT)
#define ENCENG_AlgoSelect_HASH                (0 << ENCENG_AlgoSelect_SHIFT)

#define IS_ENCENG_ALGO_SELECT(S)      (((S) == ENCENG_AlgoSelect_ENCRYPT)\
                                       ||((S) == ENCENG_AlgoSelect_HASH))

#define IS_ENCENG_ADDR(A)             (((uint32_t)(A)%4) == 0)
#define IS_ENCENG_BUFF_LENGTH(L)      (((L)%16) == 0)
#define IS_ENCENG_KEY_LENGTH(L)       (((uint32_t)(L)%4) == 0)

void ENCENG_DeInit(void);
void ENCENG_Init(ENCENG_InitType* ENCENG_InitStruct);
void ENCENG_Flush(void);
void ENCENG_Cmd(FunctionalState NewState);
void ENCENG_Wait(void);
void ENCENG_SrcDataConfig(uint8_t *Addr, uint32_t Len);
void ENCENG_DestDataConfig(uint8_t *Addr);
void ENCENG_INTConfig(uint32_t INTMask, FunctionalState NewState);
ITStatus ENCENG_GetINTStatus(uint32_t INTMask);
void ENCENG_ClearINTStatus(uint32_t INTMask);
void ENCENG_SetKey(uint8_t *Key, uint8_t KeyLen, uint32_t KeyIndex);

/*Hash functions*/
void ENCENG_SHA1(uint8_t *Input, uint32_t Ilen, uint8_t Output[20]);
void ENCENG_SHA256(uint8_t *Input, uint32_t Ilen, uint8_t Output[32]);
void ENCENG_SM3(uint8_t *Input, uint32_t Ilen, uint8_t Output[32]);
void ENCENG_HMAC_SHA1(uint8_t *Input, uint32_t Ilen, 
                      uint8_t *Key, uint32_t KeyLen,
                      uint8_t Output[20]);
void ENCENG_HMAC_SHA256(uint8_t *Input, uint32_t Ilen, 
                        uint8_t *Key, uint32_t KeyLen,
                        uint8_t Output[32]);
void ENCENG_HMAC_SM3(uint8_t *Input, uint32_t Ilen, 
                     uint8_t *Key, uint32_t KeyLen,
                     uint8_t Output[32]);
void ENCENG_HMAC_SHA1_PUF(uint8_t *Input, uint32_t Ilen, 
                          uint32_t KeyIndex, uint32_t KeyLen, 
                          uint8_t Output[20]);
void ENCENG_HMAC_SHA256_PUF(uint8_t *Input, uint32_t Ilen, 
                            uint32_t KeyIndex, uint32_t KeyLen, 
                            uint8_t Output[32]);
void ENCENG_HMAC_SM3_PUF(uint8_t *Input, uint32_t Ilen, 
                         uint32_t KeyIndex, uint32_t KeyLen, 
                         uint8_t Output[32]);

/*Crypt functions*/
void ENCENG_AES_ECB(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t *Key, uint16_t KeyLen,
                    uint8_t *Output);
void ENCENG_AES_CBC(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t *Key, uint16_t KeyLen,
                    uint8_t InitVectors[16],
                    uint8_t *Output);
void ENCENG_AES_CTR(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t *Key, uint16_t KeyLen,
                    uint8_t InitVectors[16],
                    uint8_t *Output);
void ENCENG_AES_ECB_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex, uint16_t KeyLen,
                        uint8_t *Output);
void ENCENG_AES_CBC_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex, uint16_t KeyLen,
                        uint8_t InitVectors[16],
                        uint8_t *Output);
void ENCENG_AES_CTR_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex, uint16_t KeyLen,
                        uint8_t InitVectors[16],
                        uint8_t *Output);

void ENCENG_SM4_ECB(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t Key[16],
                    uint8_t *Output);
void ENCENG_SM4_CBC(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t Key[16],
                    uint8_t InitVectors[16],
                    uint8_t *Output);
void ENCENG_SM4_CTR(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t Key[16],
                    uint8_t InitVectors[16],
                    uint8_t *Output);
void ENCENG_SM4_ECB_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex,
                        uint8_t *Output);
void ENCENG_SM4_CBC_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex,
                        uint8_t InitVectors[16],
                        uint8_t *Output);
void ENCENG_SM4_CTR_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex,
                        uint8_t InitVectors[16],
                        uint8_t *Output);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LIB_ENCENG_H */

/*********************************** END OF FILE ******************************/
