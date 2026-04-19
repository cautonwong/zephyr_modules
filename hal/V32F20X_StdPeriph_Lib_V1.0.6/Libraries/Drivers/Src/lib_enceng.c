/**
  * @file    lib_enceng.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   Encrypt & Hash Engine module driver.
******************************************************************************/
#include "lib_enceng.h"
#include "lib_syscfg.h"
#include <stdlib.h>
#include <string.h>

/**
  * @brief  Deinitializes the ENCENG peripheral registers to their default reset values
  * @param  None
  * @retval None
  */
void ENCENG_DeInit(void)
{
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_ENCENG);
}

/**
  * @brief  Initializes the ENCENG peripheral according to the specified parameters
  *         in the ENCENG_InitStruct.
  * @param  ENCENG_InitStruct: pointer to a ENCENG_InitType structure that contains
  *         the configuration information for the ENCENG peripheral.
  * @retval None
  */
void ENCENG_Init(ENCENG_InitType* ENCENG_InitStruct)
{
  /* Check the parameters */
  assert_parameters(IS_ENCENG_HMAC_KEY_SIZE(ENCENG_InitStruct->ENCENG_HmacKeySize));
  assert_parameters(IS_ENCENG_KEY_SWAP(ENCENG_InitStruct->ENCENG_KeySwap));
  assert_parameters(IS_ENCENG_DATA_SWAP(ENCENG_InitStruct->ENCENG_DataSwap));
  assert_parameters(IS_ENCENG_HASH_SELECT(ENCENG_InitStruct->ENCENG_HashSelect));
  assert_parameters(IS_ENCENG_KPAD(ENCENG_InitStruct->ENCENG_KpadEnable));
  assert_parameters(IS_ENCENG_ENCRYPT_KEY_SIZE(ENCENG_InitStruct->ENCENG_EncryptKeySize));
  assert_parameters(IS_ENCENG_ENCRYPT_SELECT(ENCENG_InitStruct->ENCENG_EncryptSelect));
  assert_parameters(IS_ENCENG_ENCRYPT_DIRECTION(ENCENG_InitStruct->ENCENG_EncryptDirection));
  assert_parameters(IS_ENCENG_ENCRYPT_MODE(ENCENG_InitStruct->ENCENG_EncryptMode));
  assert_parameters(IS_ENCENG_KEY_INDEX(ENCENG_InitStruct->ENCENG_KeyIndex));
  assert_parameters(IS_ENCENG_KEY_INDEX_ENABLE(ENCENG_InitStruct->ENCENG_KeyIndexEnable));
  assert_parameters(IS_ENCENG_ALGO_SELECT(ENCENG_InitStruct->ENCENG_AlgoSelect));
  
  ENCENG->CFG = ENCENG_InitStruct->ENCENG_HmacKeySize\
                |ENCENG_InitStruct->ENCENG_KeySwap\
                |ENCENG_InitStruct->ENCENG_DataSwap\
                |ENCENG_InitStruct->ENCENG_HashSelect\
                |ENCENG_InitStruct->ENCENG_KpadEnable\
                |ENCENG_InitStruct->ENCENG_EncryptKeySize\
                |ENCENG_InitStruct->ENCENG_EncryptSelect\
                |ENCENG_InitStruct->ENCENG_EncryptDirection\
                |ENCENG_InitStruct->ENCENG_EncryptMode\
                |ENCENG_InitStruct->ENCENG_KeyIndex\
                |ENCENG_InitStruct->ENCENG_KeyIndexEnable\
                |ENCENG_InitStruct->ENCENG_AlgoSelect;
}

/**
  * @brief  Flushes the Data in ENCENG to start a new encryption or hash.
  * @param  None
  * @retval None
  */
void ENCENG_Flush(void)
{
  ENCENG->CFG |= ENCENG_NEW;
  while(ENCENG->CFG&ENCENG_NEW){}
}

/**
  * @brief  Enables or disables the ENCENG peripheral.
  * @param  NewState: new state of the ENCENG peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ENCENG_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
	{
		ENCENG->CMD = ENCENG_START;
	}
	else
	{
		ENCENG->CMD = 0;
	}
}

/**
  * @brief  Wait ENCENG finished.
  * @param  None
  * @retval None
  */
void ENCENG_Wait(void)
{
  while(ENCENG->CMD&ENCENG_START){}
}

/**
  * @brief  Configure the source data address and length.
  * @param  Addr: address of the source data.
  *         Len: source data length.
  * @retval None
  */
void ENCENG_SrcDataConfig(uint8_t *Addr, uint32_t Len)
{
  /* Check the parameters */
  assert_parameters(IS_ENCENG_ADDR(Addr));
  assert_parameters(IS_ENCENG_BUFF_LENGTH(Len));
  
  ENCENG->SRCADDR = (uint32_t)Addr;
  ENCENG->SRCLEN = Len;
}

/**
  * @brief  Configure the destination data address.
  * @param  Addr: address of the data.
  * @retval None
  */
void ENCENG_DestDataConfig(uint8_t *Addr)
{
  /* Check the parameters */
  assert_parameters(IS_ENCENG_ADDR(Addr));
  ENCENG->DSTADDR = (uint32_t)Addr;
}

/**
  * @brief  Enables or disables ENCENG interrupt.
  * @param  INTMask: specifies the ENCENG interrupts to be enabled or disables.
  *         This parameter can be any combination of the following values:
  *             ENCENG_CMD_DONE
  * @param   NewState: new state of the ENCENG interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ENCENG_INTConfig(uint32_t INTMask, FunctionalState NewState)
{
  /* Parameter check */
  assert_parameters(IS_ENCENG_INT(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if(NewState == ENABLE)
  {
    ENCENG->INTMASK |= INTMask;
  }
  else
  {
    ENCENG->INTMASK &= ~INTMask;
  }
}

/**
  * @brief  Gets ENCENG interrupt status.
  * @param  INTMask: specifies the ENCENG interrupts to check.
  *         This parameter can be one of the following values:
  *             ENCENG_CMD_DONE
  * @retval The new state of ENCENG interrupt. (SET or RESET).
  */
ITStatus ENCENG_GetINTStatus(uint32_t INTMask)
{
  /* Parameter check */
  assert_parameters(IS_ENCENG_INT(INTMask));

  if(ENCENG->INTSTS & INTMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears ENCENG interrupt status.
  * @param  INTMask: specifies the ENCENG interrupts status to clear.
  *         This parameter can be any combination of the following values:
  *             ENCENG_CMD_DONE
  * @retval  None
  */
void ENCENG_ClearINTStatus(uint32_t INTMask)
{
  /* Parameter check */
  assert_parameters(IS_ENCENG_INT(INTMask));

  ENCENG->INTSTS = INTMask;
}

/**
  * @brief  Set ENCENG key registers.
  * @param  Key: Key data to fill key registers.
  *         KeyLen: Length of key data.
  *         KeyIndex: Key index.
  *           This parameter can be one of the following values:
  *           ENCENG_KeyIndex_0
  *           ENCENG_KeyIndex_1
  *           ENCENG_KeyIndex_2
  *           ENCENG_KeyIndex_3
  * @retval  None
  */
void ENCENG_SetKey(uint8_t *Key, uint8_t KeyLen, uint32_t KeyIndex)
{
  uint8_t i, j, k;
  
  /* Parameter check */
  assert_parameters(IS_ENCENG_KEY_LENGTH(KeyLen));
  assert_parameters(IS_ENCENG_KEY_INDEX(KeyIndex));
  
  for (k = 0; k < KeyLen/4; k++)
  {
    i = k/8 + (KeyIndex >> ENCENG_KeyIndex_SHIFT);
    j = k%8;
    ENCENG->KEY[i][j] = Key[4*k]|(Key[4*k + 1] << 8) \
                        |(Key[4*k + 2] << 16)|(Key[4*k + 3] << 24);
  }
}

/*********************************** END OF FILE ******************************/
