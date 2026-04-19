/**
  * @file    lib_enceng_hash.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   Hash high level driver.
******************************************************************************/
#include "lib_enceng.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SHA_BLOCK_SIZE            64

void ENCENG_HASH(uint32_t HashSelect, 
                uint8_t *Input, uint32_t Ilen, 
                uint8_t Output[]);

void ENCENG_HMAC(uint32_t HashSelect, 
                    uint8_t *Input, uint32_t Ilen,
                    bool IsPUFKey, 
                    uint32_t KeyIndex, 
                    uint8_t *Key, 
                    uint32_t KeyLen,
                    uint8_t Output[]);
  
#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                            \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif

/**
  * @brief  Compute the HASH SHA1 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  Output: the returned digest
  * @retval None
  */
void ENCENG_SHA1(uint8_t *Input, uint32_t Ilen, uint8_t Output[20])
{
  ENCENG_HASH(ENCENG_HashSelect_SHA1, Input, Ilen, Output);
}

/**
  * @brief  Compute the HASH SHA256 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  Output: the returned digest
  * @retval None
  */
void ENCENG_SHA256(uint8_t *Input, uint32_t Ilen, uint8_t Output[32])
{
  ENCENG_HASH(ENCENG_HashSelect_SHA256, Input, Ilen, Output);
}

/**
  * @brief  Compute the HASH SM3 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  Output: the returned digest
  * @retval None
  */
void ENCENG_SM3(uint8_t *Input, uint32_t Ilen, uint8_t Output[32])
{
  ENCENG_HASH(ENCENG_HashSelect_SM3, Input, Ilen, Output);
}

/**
  * @brief  Compute the HASH digest.
  * @param  HashSelect: Hash algorithm.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  Output: the returned digest.
  * @retval None
  */
void ENCENG_HASH(uint32_t HashSelect, 
                uint8_t *Input, uint32_t Ilen, 
                uint8_t Output[])
{
  ENCENG_InitType ENCENG_InitStruct;
  uint32_t completeBlockLen;
  uint32_t used;
  uint8_t buffer[SHA_BLOCK_SIZE*2] __attribute__ ((aligned (4)));
  uint32_t i;
  uint32_t buffLen;
  uint32_t high;
  uint32_t low;
  
  ENCENG_DeInit();
  
  memset(&ENCENG_InitStruct, 0, sizeof(ENCENG_InitType));
  ENCENG_InitStruct.ENCENG_HashSelect = HashSelect;
  ENCENG_InitStruct.ENCENG_AlgoSelect = ENCENG_AlgoSelect_HASH;
  ENCENG_Init(&ENCENG_InitStruct);
  
  //Complete block data
  used = Ilen%SHA_BLOCK_SIZE;
  completeBlockLen = Ilen - used;
  ENCENG_SrcDataConfig(buffer, SHA_BLOCK_SIZE);
  ENCENG_DestDataConfig(Output);
  if (completeBlockLen > 0)
  {
    for (i = 0; i < completeBlockLen; i += SHA_BLOCK_SIZE)
    {
      memcpy(buffer, Input + i, SHA_BLOCK_SIZE);
      ENCENG_Cmd(ENABLE);
      ENCENG_Wait();
    }
  }
  
  //Non-Complete block data
  if (used <= (SHA_BLOCK_SIZE - 8 - 1))
  {
    /* Enough room for padding + length in current block */
    buffLen = SHA_BLOCK_SIZE;
  }
  else
  {
     /* We'll need an extra block */
    buffLen = 2*SHA_BLOCK_SIZE;
  }
  
  if (used > 0)
  {
    memcpy(buffer, Input + completeBlockLen, used);
  }
  
  //Add padding: 0x80 then 0x00 until 8 bytes remain for the length
  buffer[used] = 0x80;
  memset(buffer + used + 1, 0, buffLen -  used - 9 );
  
  //Add message length
  high = ( Ilen >> 29 );
  low  = ( Ilen <<  3 );
  
  PUT_UINT32_BE( high, buffer, buffLen - 8 );
  PUT_UINT32_BE( low,  buffer, buffLen - 4 );
  
  ENCENG_SrcDataConfig(buffer, buffLen);
  ENCENG_Cmd(ENABLE);
  ENCENG_Wait();
}

/**
  * @brief  Compute the HMAC SHA1 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for HMAC.
  * @param  KeyLen: length of the Key.
  * @param  Output: the returned digest.
  * @retval None
  */
void ENCENG_HMAC_SHA1(uint8_t *Input, uint32_t Ilen, 
                      uint8_t *Key, uint32_t KeyLen,
                      uint8_t Output[20])
{
  ENCENG_HMAC(ENCENG_HashSelect_SHA1, 
                  Input, Ilen, 
                  false, 
                  0, 
                  Key, 
                  KeyLen, 
                  Output);
}

/**
  * @brief  Compute the HMAC SHA256 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for HMAC.
  * @param  KeyLen: length of the Key.
  * @param  Output: the returned digest.
  * @retval None
  */
void ENCENG_HMAC_SHA256(uint8_t *Input, uint32_t Ilen, 
                        uint8_t *Key, uint32_t KeyLen,
                        uint8_t Output[32])
{
  ENCENG_HMAC(ENCENG_HashSelect_SHA256,
                  Input, Ilen, 
                  false, 
                  0, 
                  Key, 
                  KeyLen, 
                  Output);
}

/**
  * @brief  Compute the HMAC SM3 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  Key: Key used for HMAC.
  * @param  KeyLen: length of the Key.
  * @param  Output: the returned digest.
  * @retval None
  */
void ENCENG_HMAC_SM3(uint8_t *Input, uint32_t Ilen, 
                     uint8_t *Key, uint32_t KeyLen,
                     uint8_t Output[32])
{
  ENCENG_HMAC(ENCENG_HashSelect_SM3, 
                  Input, Ilen, 
                  false, 
                  0, 
                  Key, 
                  KeyLen, 
                  Output);
}

/**
  * @brief  Compute the HMAC SHA1 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  KeyLen: length of the Key.
  * @param  Output: the returned digest.
  * @retval None
  */
void ENCENG_HMAC_SHA1_PUF(uint8_t *Input, uint32_t Ilen, 
                        uint32_t KeyIndex, uint32_t KeyLen, 
                        uint8_t Output[20])
{
  ENCENG_HMAC(ENCENG_HashSelect_SHA1,
                  Input, Ilen,
                  true, 
                  KeyIndex, 
                  NULL, 
                  KeyLen,
                  Output);
}

/**
  * @brief  Compute the HMAC SHA256 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  KeyLen: length of the Key.
  * @param  Output: the returned digest.
  * @retval None
  */
void ENCENG_HMAC_SHA256_PUF(uint8_t *Input, uint32_t Ilen, 
                          uint32_t KeyIndex, uint32_t KeyLen, 
                          uint8_t Output[32])
{
  ENCENG_HMAC(ENCENG_HashSelect_SHA256,
                  Input, Ilen,
                  true, 
                  KeyIndex, 
                  NULL, 
                  KeyLen,
                  Output);
}

/**
  * @brief  Compute the HMAC SM3 digest.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  KeyIndex: Index of PUF key.
  * @param  KeyLen: length of the Key.
  * @param  Output: the returned digest.
  * @retval None
  */
void ENCENG_HMAC_SM3_PUF(uint8_t *Input, uint32_t Ilen, 
                          uint32_t KeyIndex, uint32_t KeyLen, 
                          uint8_t Output[32])
{
  ENCENG_HMAC(ENCENG_HashSelect_SM3,
                  Input, Ilen,
                  true, 
                  KeyIndex, 
                  NULL, 
                  KeyLen,
                  Output);
}

/**
  * @brief  Compute the HMAC digest.
  * @param  HashSelect: Hash algorithm.
  * @param  Input: pointer to the Input buffer to be treated.
  * @param  Ilen: length of the Input buffer.
  * @param  IsPUFKey: use PUF key(true, false).
  * @param  KeyIndex: Index of PUF key.
  * @param  Key: Key used for HMAC.
  * @param  KeyLen: length of the Key.
  * @param  Output: the returned digest.
  * @retval None
  */
void ENCENG_HMAC(uint32_t HashSelect, 
                    uint8_t *Input, uint32_t Ilen,
                    bool IsPUFKey, 
                    uint32_t KeyIndex,
                    uint8_t *Key,
                    uint32_t KeyLen,
                    uint8_t Output[])
{
  uint8_t src1[SHA_BLOCK_SIZE*2] __attribute__ ((aligned (4)));
  uint8_t src2[SHA_BLOCK_SIZE*2] __attribute__ ((aligned (4)));
  uint32_t i;
  ENCENG_InitType ENCENG_InitStruct;
  uint32_t used;
  uint32_t completeBlockLen;
  uint32_t src1Len;
  uint32_t high;
  uint32_t low;
  uint32_t digestLen;

  ENCENG_DeInit();
  
  memset(&ENCENG_InitStruct, 0, sizeof(ENCENG_InitType));
  ENCENG_InitStruct.ENCENG_HmacKeySize = (KeyLen/4 -1) << ENCENG_HmacKeySize_SHIFT;
  ENCENG_InitStruct.ENCENG_HashSelect = HashSelect;
  if (IsPUFKey == true)
  {
    ENCENG_InitStruct.ENCENG_KpadEnable = ENCENG_KpadEnable_Enable;
    ENCENG_InitStruct.ENCENG_KeyIndex = KeyIndex;
    ENCENG_InitStruct.ENCENG_KeyIndexEnable = ENCENG_KeyIndexEnable_Enable;
  }
  ENCENG_InitStruct.ENCENG_AlgoSelect = ENCENG_AlgoSelect_HASH;
  ENCENG_Init(&ENCENG_InitStruct);
  
  //round 1
  //ipad
  memset(src1, 0x36, SHA_BLOCK_SIZE);
  if (IsPUFKey == false)
  {
    for (i = 0; i < KeyLen; i++)
    {
      src1[i] ^= Key[i];
    }
  }
  memset(src2 + SHA_BLOCK_SIZE, 0, SHA_BLOCK_SIZE);
  ENCENG_SrcDataConfig(src1, SHA_BLOCK_SIZE);
  ENCENG_DestDataConfig(src2 + SHA_BLOCK_SIZE);
  ENCENG_Cmd(ENABLE);
  ENCENG_Wait();
  
  used = Ilen%SHA_BLOCK_SIZE;
  
  //complete block data
  ENCENG_InitStruct.ENCENG_KpadEnable = ENCENG_KpadEnable_Disable;
  ENCENG_Init(&ENCENG_InitStruct);
  completeBlockLen = Ilen - used;
  if (completeBlockLen > 0)
  {
    for (i = 0; i < completeBlockLen; i += SHA_BLOCK_SIZE)
    {
      memcpy(src1, Input + i, SHA_BLOCK_SIZE);
      ENCENG_Cmd(ENABLE);
      ENCENG_Wait();
    }
  }
  
  //Non-complete block data
  if (used <= (SHA_BLOCK_SIZE - 8 - 1))
  {
    /* Enough room for padding + length in current block */
    src1Len = SHA_BLOCK_SIZE;
  }
  else
  {
     /* We'll need an extra block */
    src1Len = 2*SHA_BLOCK_SIZE;
  }
  
  if (used > 0)
  {
    memcpy(src1, Input + completeBlockLen, used);
  }
  
  //Add padding: 0x80 then 0x00 until 8 bytes remain for the length
  src1[used] = 0x80;
  memset(src1 + used + 1, 0, src1Len - used - 9 );
  
  //Add message length
  high = ((SHA_BLOCK_SIZE + Ilen) >> 29);
  low  = ((SHA_BLOCK_SIZE + Ilen) <<  3);
  
  PUT_UINT32_BE(high, src1, src1Len - 8);
  PUT_UINT32_BE(low,  src1, src1Len - 4);
	
  ENCENG_SrcDataConfig(src1, src1Len);
  ENCENG_Cmd(ENABLE);
  ENCENG_Wait();
  
  //round 2
  //opad
  memset(src2, 0x5C, SHA_BLOCK_SIZE);
  if (IsPUFKey == false)
  {
    for (i = 0; i < KeyLen; i++)
    {
      src2[i] ^= Key[i];
    }
  }
  if (HashSelect == ENCENG_HashSelect_SHA1)
  {
    digestLen = 20;
  }
  else if ((HashSelect == ENCENG_HashSelect_SHA256) \
    || (HashSelect == ENCENG_HashSelect_SM3))
  {
    digestLen = 32;
  }
  //Add padding: 0x80 then 0x00 until 8 bytes remain for the length
  src2[SHA_BLOCK_SIZE + digestLen] = 0x80;
  memset(src2 + SHA_BLOCK_SIZE + digestLen + 1, 0, SHA_BLOCK_SIZE -  digestLen \
    - 9 );
  
  //Add message length
  high = ((SHA_BLOCK_SIZE + digestLen) >> 29);
  low  = ((SHA_BLOCK_SIZE + digestLen) << 3);
  
  PUT_UINT32_BE(high, src2, SHA_BLOCK_SIZE*2 - 8);
  PUT_UINT32_BE(low,  src2, SHA_BLOCK_SIZE*2 - 4);
  
  ENCENG_Flush();
  if (IsPUFKey == true)
  {
    ENCENG_InitStruct.ENCENG_KpadEnable = ENCENG_KpadEnable_Enable;
    ENCENG_Init(&ENCENG_InitStruct);
  }
  ENCENG_SrcDataConfig(src2, SHA_BLOCK_SIZE*2);
  ENCENG_DestDataConfig(Output);
  ENCENG_Cmd(ENABLE);
  ENCENG_Wait();
}

/*********************************** END OF FILE ******************************/
