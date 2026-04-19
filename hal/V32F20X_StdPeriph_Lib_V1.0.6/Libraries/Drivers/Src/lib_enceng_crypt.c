/**
  * @file    lib_enceng_crypt.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   crypt high level driver.
******************************************************************************/
#include "lib_enceng.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define CRYPT_BLOCK_SIZE 16

void ENCENG_AES(uint32_t EncryptMode,
                uint32_t EncryptDirection,
                uint8_t *Input, uint32_t Ilen,
                bool IsPUFKey,
                uint32_t KeyIndex,
                uint8_t *Key,
                uint16_t KeyLen,
                uint8_t InitVectors[16],
                uint8_t *Output);

void ENCENG_SM4(uint32_t EncryptMode,
                uint32_t EncryptDirection,
                uint8_t *Input, uint32_t Ilen,
                bool IsPUFKey,
                uint32_t KeyIndex,
                uint8_t Key[16],
                uint8_t InitVectors[16],
                uint8_t *Output);
                
void ENCENG_Crypt(uint32_t EncryptSelect,
                  uint32_t EncryptMode,
                  uint32_t EncryptDirection,
                  uint8_t *Input, uint32_t Ilen,
                  bool IsPUFKey,
                  uint32_t KeyIndex,
                  uint8_t *Key,
                  uint16_t KeyLen,
                  uint8_t InitVectors[16],
                  uint8_t *Output);
/**
  * @brief  Encrypt and decrypt using AES in ECB Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for AES.
  * @param  KeyLen: length of the Key, must be a 16(128), 24(192) or 32(256).
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_AES_ECB(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t *Key, uint16_t KeyLen,
                    uint8_t *Output)
{
  ENCENG_AES(ENCENG_EncryptMode_ECB,
             EncryptDirection,
             Input, Ilen,
             false,
             0,
             Key, 
             KeyLen,
             NULL,
             Output);
}

/**
  * @brief  Encrypt and decrypt using AES in CBC Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for AES.
  * @param  KeyLen: length of the Key, must be a 16(128), 24(192) or 32(256).
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_AES_CBC(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t *Key, uint16_t KeyLen,
                    uint8_t InitVectors[16],
                    uint8_t *Output)
{
  ENCENG_AES(ENCENG_EncryptMode_CBC,
             EncryptDirection,
             Input, Ilen,
             false,
             0,
             Key,
             KeyLen,
             InitVectors,
             Output);
}

/**
  * @brief  Encrypt and decrypt using AES in CTR Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for AES.
  * @param  KeyLen: length of the Key, must be a 16(128), 24(192) or 32(256).
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_AES_CTR(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t *Key, uint16_t KeyLen,
                    uint8_t InitVectors[16],
                    uint8_t *Output)
{
  ENCENG_AES(ENCENG_EncryptMode_CTR,
             EncryptDirection,
             Input, Ilen,
             false,
             0,
             Key,
             KeyLen,
             InitVectors,
             Output);
}

/**
  * @brief  Encrypt and decrypt using AES in ECB Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  KeyLen: length of the Key, must be a 16(128), 24(192) or 32(256).
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_AES_ECB_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex, uint16_t KeyLen,
                        uint8_t *Output)
{
  ENCENG_AES(ENCENG_EncryptMode_ECB,
             EncryptDirection,
             Input, Ilen,
             true,
             KeyIndex,
             NULL, 
             KeyLen,
             NULL,
             Output);
}

/**
  * @brief  Encrypt and decrypt using AES in CBC Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  KeyLen: length of the Key, must be a 16(128), 24(192) or 32(256).
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_AES_CBC_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex, uint16_t KeyLen,
                        uint8_t InitVectors[16],
                        uint8_t *Output)
{
  ENCENG_AES(ENCENG_EncryptMode_CBC,
             EncryptDirection,
             Input, Ilen,
             true,
             KeyIndex,
             NULL,
             KeyLen,
             InitVectors,
             Output);
}

/**
  * @brief  Encrypt and decrypt using AES in CTR Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  KeyLen: length of the Key, must be a 16(128), 24(192) or 32(256).
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_AES_CTR_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex, uint16_t KeyLen,
                        uint8_t InitVectors[16],
                        uint8_t *Output)
{
  ENCENG_AES(ENCENG_EncryptMode_CTR,
             EncryptDirection,
             Input, Ilen,
             true,
             KeyIndex,
             NULL,
             KeyLen,
             InitVectors,
             Output);
}

/**
  * @brief  Encrypt and decrypt using AES.
  * @param  EncryptMode: 
  *          This parameter can be one of the following values:
  *           ENCENG_EncryptMode_ECB
  *           ENCENG_EncryptMode_CBC
  *           ENCENG_EncryptMode_CTR
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  IsPUFKey: use PUF key(true, false).
  * @param  KeyIndex: Index of PUF key.
  * @param  Key: Key used for AES.
  * @param  KeyLen: length of the Key, must be a 16(128), 24(192) or 32(256).
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_AES(uint32_t EncryptMode,
                uint32_t EncryptDirection,
                uint8_t *Input, uint32_t Ilen,
                bool IsPUFKey,
                uint32_t KeyIndex,
                uint8_t *Key,
                uint16_t KeyLen,
                uint8_t InitVectors[16],
                uint8_t *Output)
{
  ENCENG_Crypt(ENCENG_EncryptSelect_AES,
              EncryptMode,
              EncryptDirection,
              Input, Ilen,
              IsPUFKey,
              KeyIndex,
              Key,
              KeyLen,
              InitVectors,
              Output);
}

/**
  * @brief  Encrypt and decrypt using SM4 in ECB Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for AES.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_SM4_ECB(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t Key[16],
                    uint8_t *Output)
{
  ENCENG_SM4(ENCENG_EncryptMode_ECB,
             EncryptDirection,
             Input, Ilen,
             false,
             0,
             Key, 
             NULL,
             Output);
}

/**
  * @brief  Encrypt and decrypt using SM4 in CBC Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for AES.
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_SM4_CBC(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t Key[16],
                    uint8_t InitVectors[16],
                    uint8_t *Output)
{
  ENCENG_SM4(ENCENG_EncryptMode_CBC,
             EncryptDirection,
             Input, Ilen,
             false,
             0,
             Key,
             InitVectors,
             Output);
}

/**
  * @brief  Encrypt and decrypt using SM4 in CTR Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for AES.
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_SM4_CTR(uint32_t EncryptDirection,
                    uint8_t *Input, uint32_t Ilen,
                    uint8_t Key[16],
                    uint8_t InitVectors[16],
                    uint8_t *Output)
{
  ENCENG_SM4(ENCENG_EncryptMode_CTR,
             EncryptDirection,
             Input, Ilen,
             false,
             0,
             Key,
             InitVectors,
             Output);
}

/**
  * @brief  Encrypt and decrypt using SM4 in ECB Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_SM4_ECB_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex,
                        uint8_t *Output)
{
  ENCENG_SM4(ENCENG_EncryptMode_ECB,
             EncryptDirection,
             Input, Ilen,
             true,
             KeyIndex,
             NULL, 
             NULL,
             Output);
}

/**
  * @brief  Encrypt and decrypt using SM4 in CBC Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_SM4_CBC_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex,
                        uint8_t InitVectors[16],
                        uint8_t *Output)
{
  ENCENG_SM4(ENCENG_EncryptMode_CBC,
             EncryptDirection,
             Input, Ilen,
             true,
             KeyIndex,
             NULL,
             InitVectors,
             Output);
}

/**
  * @brief  Encrypt and decrypt using SM4 in CTR Mode.
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_SM4_CTR_PUF(uint32_t EncryptDirection,
                        uint8_t *Input, uint32_t Ilen,
                        uint32_t KeyIndex,
                        uint8_t InitVectors[16],
                        uint8_t *Output)
{
  ENCENG_SM4(ENCENG_EncryptMode_CTR,
             EncryptDirection,
             Input, Ilen,
             true,
             KeyIndex,
             NULL,
             InitVectors,
             Output);
}

/**
  * @brief  Encrypt and decrypt using SM4.
  * @param  EncryptMode: 
  *          This parameter can be one of the following values:
  *           ENCENG_EncryptMode_ECB
  *           ENCENG_EncryptMode_CBC
  *           ENCENG_EncryptMode_CTR
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  IsPUFKey: use PUF key(true, false).
  * @param  KeyIndex: Index of PUF key.
  * @param  Key: Key used for AES.
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_SM4(uint32_t EncryptMode,
                uint32_t EncryptDirection,
                uint8_t *Input, uint32_t Ilen,
                bool IsPUFKey,
                uint32_t KeyIndex,
                uint8_t Key[16],
                uint8_t InitVectors[16],
                uint8_t *Output)
{
  ENCENG_Crypt(ENCENG_EncryptSelect_SM4,
              EncryptMode,
              EncryptDirection,
              Input, Ilen,
              IsPUFKey,
              KeyIndex,
              Key,
              16,
              InitVectors,
              Output);
}

/**
  * @brief  Encrypt and decrypt.
  * @param  EncryptSelect: ENCENG_EncryptSelect_AES or ENCENG_EncryptSelect_SM4.
  * @param  EncryptMode: 
  *          This parameter can be one of the following values:
  *           ENCENG_EncryptMode_ECB
  *           ENCENG_EncryptMode_CBC
  *           ENCENG_EncryptMode_CTR
  * @param  EncryptDirection: ENCENG_EncryptDirection_ENCRYPT or 
  *                           ENCENG_EncryptDirection_DECRYPT.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilen: length of the Input buffer.
  * @param  IsPUFKey: use PUF key(true, false).
  * @param  KeyIndex: Index of PUF key.
  * @param  Key: Key used for AES.
  * @param  KeyLen: length of the Key, must be a 16(128), 24(192) or 32(256).
  * @param  InitVectors: Initialisation Vectors used for AES algorithm.
  * @param  Output: pointer to the returned buffer.
  * @retval None
  */
void ENCENG_Crypt(uint32_t EncryptSelect,
                  uint32_t EncryptMode,
                  uint32_t EncryptDirection,
                  uint8_t *Input, uint32_t Ilen,
                  bool IsPUFKey,
                  uint32_t KeyIndex,
                  uint8_t *Key,
                  uint16_t KeyLen,
                  uint8_t InitVectors[16],
                  uint8_t *Output)
{
  ENCENG_InitType ENCENG_InitStruct;
  uint8_t src[32 + 16 + CRYPT_BLOCK_SIZE] __attribute__ ((aligned (4)));
  uint8_t *pSrc;
  uint32_t remainLen;
  uint32_t i;

  ENCENG_DeInit();
  memset(&ENCENG_InitStruct, 0, sizeof(ENCENG_InitType));
  ENCENG_InitStruct.ENCENG_EncryptKeySize = (KeyLen/8 - 2) << ENCENG_EncryptKeySize_SHIFT;
  ENCENG_InitStruct.ENCENG_EncryptSelect = EncryptSelect;
  ENCENG_InitStruct.ENCENG_EncryptDirection = EncryptDirection;
  ENCENG_InitStruct.ENCENG_EncryptMode = EncryptMode;
  if (IsPUFKey == true)
  {
    ENCENG_InitStruct.ENCENG_KeyIndex = KeyIndex;
    ENCENG_InitStruct.ENCENG_KeyIndexEnable = ENCENG_KeyIndexEnable_Enable;
  }
  ENCENG_InitStruct.ENCENG_AlgoSelect = ENCENG_AlgoSelect_ENCRYPT;
  ENCENG_Init(&ENCENG_InitStruct);
  
  //key + iv + first block
  pSrc = src;
  if (IsPUFKey == false)
  {
    memcpy(pSrc, Key, KeyLen);
    pSrc += KeyLen;
  }
  
  if (EncryptMode != ENCENG_EncryptMode_ECB)
  {
    memcpy(pSrc, InitVectors, 16);
    pSrc += 16;
  }
  memcpy(pSrc, Input, CRYPT_BLOCK_SIZE);
  pSrc += CRYPT_BLOCK_SIZE;
  ENCENG_SrcDataConfig(src, CRYPT_BLOCK_SIZE);
  ENCENG_DestDataConfig(Output);
  
  ENCENG_Cmd(ENABLE);
  ENCENG_Wait();
  
  ENCENG_InitStruct.ENCENG_KeyIndex = 0;
  ENCENG_InitStruct.ENCENG_KeyIndexEnable = 0;
  ENCENG_Init(&ENCENG_InitStruct);
  remainLen = Ilen - CRYPT_BLOCK_SIZE;
  if (remainLen > 0)
  {
    //The length should guarantee 16Bytes boundary
    for (i = CRYPT_BLOCK_SIZE; i < Ilen; i += CRYPT_BLOCK_SIZE)
    {
      memcpy(src, Input + i, CRYPT_BLOCK_SIZE);
      ENCENG_DestDataConfig(Output + i);
      ENCENG_Cmd(ENABLE);
      ENCENG_Wait();
    }
  }
}

/*********************************** END OF FILE ******************************/
