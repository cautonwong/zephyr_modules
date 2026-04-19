/**
  ******************************************************************************
  * @file    lib_bdma.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   This file provides all the BDMA firmware functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_bdma.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup BDMA 
  * @brief BDMA driver modules
  * @{
  */

/** @defgroup BDMA_Private_Defines
  * @{
  */

/* BDMA_CCTL register */
#define BDMA_CCTL_EN                    ((uint32_t)0x00000001)
#define BDMA_CCTL_SIZE_MASK             ((uint32_t)0x00000006)
#define BDMA_CCTL_SMODE_MASK            ((uint32_t)0x00000018)
#define BDMA_CCTL_DMODE_MASK            ((uint32_t)0x00000060)
#define BDMA_CCTL_TMODE                 ((uint32_t)0x00001000)
#define BDMA_CCTL_CONT                  ((uint32_t)0x00002000)
#define BDMA_CCTL_AESEN                 ((uint32_t)0x00004000)
#define BDMA_CCTL_STOP                  ((uint32_t)0x00008000)
#define BDMA_CCTL_PLEN_POS              (16UL)
#define BDMA_CCTL_PLEN_MASK             ((uint32_t)0x00FF0000)
#define BDMA_CCTL_FLEN_POS              (24UL)
#define BDMA_CCTL_FLEN_MASK             ((uint32_t)0xFF000000)
#define BDMA_CCTL

/* BDMA_CCTL register */
#define BDMA_AESCTL_ENC                 ((uint8_t)0x01) 
#define BDMA_AESCTL_MODE_MASK           ((uint8_t)0x0C) 

/**
  * @}
  */

/** @defgroup BDMA_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the BDMA channel peripheral registers to their default reset values.
  * @param  Channel: specifies the DMA channel to configure.
  *   This parameter can be one of the following values:
  *     @arg BDMA_CHANNEL_0: BDMA Channel 0 selected
  *     @arg BDMA_CHANNEL_1: BDMA Channel 1 selected
  *     @arg BDMA_CHANNEL_2: BDMA Channel 2 selected
  *     @arg BDMA_CHANNEL_3: BDMA Channel 3 selected
  * @retval None
  */
void BDMA_DeInit(uint32_t Channel)
{
  __IO uint32_t *addr;

  /* Check the parameters */
  assert_parameters(IS_BDMA_CHANNEL(Channel));

  /* channel x disable, clear stop */
  addr = &BDMA->C0CTL + Channel*8;
  SET_BIT(*addr, BDMA_CCTL_STOP);
  while (IS_BIT_SET(BDMA->STS, (1UL << Channel)))
  {
  }

  CLEAR_BIT(*addr, BDMA_CCTL_EN|BDMA_CCTL_STOP);

  /* Interrupt disable */
  CLEAR_BIT(BDMA->IE, ((1 << (Channel))     | \
                       (1 << (Channel + 4)) | \
                       (1 << (Channel + 8))));
  /* Interrupt status clear */
  WRITE_REG(BDMA->STS, ((1 << (Channel + 4)) | \
                        (1 << (Channel + 8)) | \
                        (1 << (Channel + 12))));
  /* BDMA_CxCTL */
  addr = &BDMA->C0CTL + Channel*8;
  CLEAR_REG(*addr);

  /* BDMA_CxSEL */
  addr = &BDMA->C0SEL + Channel*8;
  CLEAR_REG(*addr);

  /* BDMA_CxSRC */
  addr = &BDMA->C0SRC + Channel*8;
  CLEAR_REG(*addr);

  /* BDMA_CxDST */
  addr = &BDMA->C0DST + Channel*8;
  CLEAR_REG(*addr);
}

/**
  * @brief  Fills each BDMA_InitType member with its default value.
  * @param  BDMA_InitStruct: pointer to an BDMA_InitType structure which will be initialized.
  * @retval None
  */
void BDMA_StructInit(BDMA_InitType *BDMA_InitStruct)
{
  /*-------------- Reset DMA init structure parameters values ---------------*/
  /* Initialize the DestAddr member */
  BDMA_InitStruct->DestAddr = 0;
  /* Initialize the SrcAddr member */
  BDMA_InitStruct->SrcAddr = 0;
  /* Initialize the FrameLen member */
  BDMA_InitStruct->FrameLen = 0;
  /* Initialize the PackLen member */
  BDMA_InitStruct->PackLen = 0;
  /* Initialize the ContMode member */
  BDMA_InitStruct->ContMode = BDMA_CONTMODE_DISABLE;
  /* Initialize the TransMode member */
  BDMA_InitStruct->TransMode = BDMA_TRANSMODE_SINGLE;
  /* Initialize the ReqSrc member */
  BDMA_InitStruct->ReqSrc = BDMA_REQSRC_SOFT;
  /* Initialize the DestAddrMode member */
  BDMA_InitStruct->DestAddrMode = BDMA_DESTADDRMODE_FIX;
  /* Initialize the SrcAddrMode member */
  BDMA_InitStruct->SrcAddrMode = BDMA_SRCADDRMODE_FIX;
  /* Initialize the TransSize member */
  BDMA_InitStruct->TransSize = BDMA_TRANSSIZE_BYTE;
}

/**
  * @brief  Initializes DMA channel.
  * @param  BDMA_InitStruct: pointer to a BDMA_InitType structure that
  *         contains the configuration information for the specified DMA Channel.
  * @param  Channel: specifies the DMA channel to configure.
  *   This parameter can be one of the following values:
  *     @arg BDMA_CHANNEL_0: BDMA Channel 0 selected
  *     @arg BDMA_CHANNEL_1: BDMA Channel 1 selected
  *     @arg BDMA_CHANNEL_2: BDMA Channel 2 selected
  *     @arg BDMA_CHANNEL_3: BDMA Channel 3 selected
  * @retval None
  */
void BDMA_Init(BDMA_InitType *BDMA_InitStruct, uint32_t Channel)
{
  uint32_t tmp;
  __IO uint32_t *addr;

  /* Check parameters */
  assert_parameters(IS_BDMA_CHANNEL(Channel));
  assert_parameters(IS_BDMA_CONTMOD(BDMA_InitStruct->ContMode));
  assert_parameters(IS_BDMA_TRANSMOD(BDMA_InitStruct->TransMode));
  assert_parameters(IS_BDMA_REQSRC(BDMA_InitStruct->ReqSrc));
  assert_parameters(IS_BDMA_DESTADDRMOD(BDMA_InitStruct->DestAddrMode));
  assert_parameters(IS_BDMA_SRCADDRMOD(BDMA_InitStruct->SrcAddrMode));
  assert_parameters(IS_BDMA_TRANSSIZE(BDMA_InitStruct->TransSize));

  addr = &BDMA->C0SEL + Channel*8;
  WRITE_REG(*addr, BDMA_InitStruct->ReqSrc);

  addr = &BDMA->C0DST + Channel*8;
  WRITE_REG(*addr, BDMA_InitStruct->DestAddr);

  addr = &BDMA->C0SRC + Channel*8;
  WRITE_REG(*addr, BDMA_InitStruct->SrcAddr);

  addr = &BDMA->C0CTL + Channel*8;
  tmp = READ_REG(*addr);
  tmp &= ~(BDMA_CCTL_FLEN_MASK  | \
           BDMA_CCTL_PLEN_MASK  | \
           BDMA_CCTL_CONT       | \
           BDMA_CCTL_TMODE      | \
           BDMA_CCTL_DMODE_MASK | \
           BDMA_CCTL_SMODE_MASK | \
           BDMA_CCTL_SIZE_MASK);
  tmp |= ((BDMA_InitStruct->FrameLen << BDMA_CCTL_FLEN_POS) | \
          (BDMA_InitStruct->PackLen << BDMA_CCTL_PLEN_POS)  | \
          (BDMA_InitStruct->ContMode)                       | \
          (BDMA_InitStruct->TransMode)                      | \
          (BDMA_InitStruct->DestAddrMode)                   | \
          (BDMA_InitStruct->SrcAddrMode)                    | \
          (BDMA_InitStruct->TransSize));
  WRITE_REG(*addr, tmp);
}

/**
  * @brief  Enables or disables DMA channel.
  * @param  Channel: specifies the DMA channel to configure.
  *   This parameter can be one of the following values:
  *     @arg BDMA_CHANNEL_0: BDMA Channel 0 selected
  *     @arg BDMA_CHANNEL_1: BDMA Channel 1 selected
  *     @arg BDMA_CHANNEL_2: BDMA Channel 2 selected
  *     @arg BDMA_CHANNEL_3: BDMA Channel 3 selected
  * @param  NewState: new state of the DMA channel.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BDMA_Cmd(uint32_t Channel, FunctionalState NewState)
{
  __IO uint32_t *addr;

  /* Check parameters */
  assert_parameters(IS_BDMA_CHANNEL(Channel)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  addr = &BDMA->C0CTL + Channel*8;

  if (NewState == ENABLE)
  {
    SET_BIT(*addr, BDMA_CCTL_EN);
  }
  else
  {
    CLEAR_BIT(*addr, BDMA_CCTL_EN);
  }
}



/**
  * @brief  Stops DMA transmit.
  * @param  Channel: specifies the DMA channel to configure.
  *   This parameter can be one of the following values:
  *     @arg BDMA_CHANNEL_0: BDMA Channel 0 selected
  *     @arg BDMA_CHANNEL_1: BDMA Channel 1 selected
  *     @arg BDMA_CHANNEL_2: BDMA Channel 2 selected
  *     @arg BDMA_CHANNEL_3: BDMA Channel 3 selected
  * @param  NewState: new state of the DMA channel stop state.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BDMA_StopCmd(uint32_t Channel, FunctionalState NewState)
{
  __IO uint32_t *addr;

  /* Check parameters */
  assert_parameters(IS_BDMA_CHANNEL(Channel)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  addr = &BDMA->C0CTL + Channel*8;

  if (NewState == ENABLE)
  {
    SET_BIT(*addr, BDMA_CCTL_STOP);
    while (IS_BIT_SET(BDMA->STS, (1UL << Channel)))
    {
    }
  }
  else
  {
    CLEAR_BIT(*addr, BDMA_CCTL_STOP);
  }
}

/**
  * @brief  Gets DMA channel status.
  * @param  Flag: specifies the DMA channel busy flag to check.
  *           @arg BDMA_FLAG_C0BUSY: BDMA Channel 0 busy flag(only read)
  *           @arg BDMA_FLAG_C1BUSY: BDMA Channel 1 busy flag(only read)
  *           @arg BDMA_FLAG_C2BUSY: BDMA Channel 2 busy flag(only read)
  *           @arg BDMA_FLAG_C3BUSY: BDMA Channel 2 busy flag(only read)
  * @retval The new state of DMA channel busy flag (SET or RESET).
  */
FlagStatus BDMA_GetFlagStatus(uint32_t Flag)
{
  /* Check parameters */
  assert_parameters(IS_BDMA_FLAG(Flag)); 

  if (IS_BIT_SET(BDMA->STS, Flag))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Enables or disables DMA interrupt.
  * @param  INTMask: specifies the DMA interrupt source to configure.
  *         This parameter can be any combination of the following values:
  *           @arg BDMA_INT_C0DA: BDMA Channel 0 data abort interrupt mask
  *           @arg BDMA_INT_C1DA: BDMA Channel 1 data abort interrupt mask
  *           @arg BDMA_INT_C2DA: BDMA Channel 2 data abort interrupt mask
  *           @arg BDMA_INT_C3DA: BDMA Channel 3 data abort interrupt mask
  *           @arg BDMA_INT_C0FE: BDMA Channel 0 frame end interrupt mask
  *           @arg BDMA_INT_C1FE: BDMA Channel 1 frame end interrupt mask
  *           @arg BDMA_INT_C2FE: BDMA Channel 2 frame end interrupt mask
  *           @arg BDMA_INT_C3FE: BDMA Channel 3 frame end interrupt mask
  *           @arg BDMA_INT_C0PE: BDMA Channel 0 package end interrupt mask
  *           @arg BDMA_INT_C1PE: BDMA Channel 1 package end interrupt mask
  *           @arg BDMA_INT_C2PE: BDMA Channel 2 package end interrupt mask
  *           @arg BDMA_INT_C3PE: BDMA Channel 3 package end interrupt mask
  * @param  NewState: new state of the DMA interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BDMA_INTConfig(uint32_t INTMask, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_BDMA_INTC(INTMask)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == ENABLE)
  {
    SET_BIT(BDMA->IE, INTMask);
  }
  else
  {
    CLEAR_BIT(BDMA->IE, INTMask);
  }
}

/**
  * @brief  Gets DMA interrupt status.
  * @param  INTMask: specifies the DMA interrupt source to check.
  *         This parameter can be one of the following values:
  *           @arg BDMA_INT_C0DA: BDMA Channel 0 data abort interrupt mask
  *           @arg BDMA_INT_C1DA: BDMA Channel 1 data abort interrupt mask
  *           @arg BDMA_INT_C2DA: BDMA Channel 2 data abort interrupt mask
  *           @arg BDMA_INT_C3DA: BDMA Channel 3 data abort interrupt mask
  *           @arg BDMA_INT_C0FE: BDMA Channel 0 frame end interrupt mask
  *           @arg BDMA_INT_C1FE: BDMA Channel 1 frame end interrupt mask
  *           @arg BDMA_INT_C2FE: BDMA Channel 2 frame end interrupt mask
  *           @arg BDMA_INT_C3FE: BDMA Channel 3 frame end interrupt mask
  *           @arg BDMA_INT_C0PE: BDMA Channel 0 package end interrupt mask
  *           @arg BDMA_INT_C1PE: BDMA Channel 1 package end interrupt mask
  *           @arg BDMA_INT_C2PE: BDMA Channel 2 package end interrupt mask
  *           @arg BDMA_INT_C3PE: BDMA Channel 3 package end interrupt mask
  * @retval The new state of DMA interrupt (SET or RESET).
  */
INTStatus BDMA_GetINTStatus(uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_BDMA_INTR(INTMask)); 

  if (IS_BIT_SET(BDMA->STS, (INTMask << 4)))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears DMA interrupt status.
  * @param  INTMask: specifies the DMA interrupt source to clear.
  *         This parameter can be any combination of the following values:
  *           @arg BDMA_INT_C0DA: BDMA Channel 0 data abort interrupt mask
  *           @arg BDMA_INT_C1DA: BDMA Channel 1 data abort interrupt mask
  *           @arg BDMA_INT_C2DA: BDMA Channel 2 data abort interrupt mask
  *           @arg BDMA_INT_C3DA: BDMA Channel 3 data abort interrupt mask
  *           @arg BDMA_INT_C0FE: BDMA Channel 0 frame end interrupt mask
  *           @arg BDMA_INT_C1FE: BDMA Channel 1 frame end interrupt mask
  *           @arg BDMA_INT_C2FE: BDMA Channel 2 frame end interrupt mask
  *           @arg BDMA_INT_C3FE: BDMA Channel 3 frame end interrupt mask
  *           @arg BDMA_INT_C0PE: BDMA Channel 0 package end interrupt mask
  *           @arg BDMA_INT_C1PE: BDMA Channel 1 package end interrupt mask
  *           @arg BDMA_INT_C2PE: BDMA Channel 2 package end interrupt mask
  *           @arg BDMA_INT_C3PE: BDMA Channel 3 package end interrupt mask
  * @retval None
  */
void BDMA_ClearINTStatus(uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_BDMA_INTC(INTMask));

  WRITE_REG(BDMA->STS, (INTMask << 4));
}

/**
  * @brief  Gets current frame transferred length.
  * @param  Channel: specifies the DMA channel to check.
  *   This parameter can be one of the following values:
  *     @arg BDMA_CHANNEL_0: BDMA Channel 0 selected
  *     @arg BDMA_CHANNEL_1: BDMA Channel 1 selected
  *     @arg BDMA_CHANNEL_2: BDMA Channel 2 selected
  *     @arg BDMA_CHANNEL_3: BDMA Channel 3 selected
  * @retval Current frame transferred length.
  */
uint8_t BDMA_GetFrameLenTransferred(uint32_t Channel)
{
  __IO uint32_t *addr;
  
  /* Check parameters */
  assert_parameters(IS_BDMA_CHANNEL(Channel)); 
    
  addr = &BDMA->C0LEN + Channel*8;

  return (uint8_t)(((READ_REG(*addr) & 0xFF00) >> 8));
}

/**
  * @brief  Gets current package transferred length.
  * @param  Channel: specifies the DMA channel to check.
  *   This parameter can be one of the following values:
  *     @arg BDMA_CHANNEL_0: BDMA Channel 0 selected
  *     @arg BDMA_CHANNEL_1: BDMA Channel 1 selected
  *     @arg BDMA_CHANNEL_2: BDMA Channel 2 selected
  *     @arg BDMA_CHANNEL_3: BDMA Channel 3 selected
  * @retval Current package transferred length.
  */
uint8_t BDMA_GetPackLenTransferred(uint32_t Channel)
{
  __IO uint32_t *addr;

  /* Check parameters */
  assert_parameters(IS_BDMA_CHANNEL(Channel)); 

  addr = &BDMA->C0LEN + Channel*8;

  return (uint8_t)((READ_REG(*addr) & 0xFF));
}

/**
  * @brief  Initializes the DMA AES channel3 registers to their default reset values.
  * @param  None
  * @retval None
  */
void BDMA_AESDeInit(void)
{
  /*set default reset values*/
  CLEAR_REG(BDMA->AESCTL);
  CLEAR_REG(BDMA->AESKEY0);
  CLEAR_REG(BDMA->AESKEY1);
  CLEAR_REG(BDMA->AESKEY2); 
  CLEAR_REG(BDMA->AESKEY3);
  CLEAR_REG(BDMA->AESKEY4);
  CLEAR_REG(BDMA->AESKEY5);
  CLEAR_REG(BDMA->AESKEY6); 
  CLEAR_REG(BDMA->AESKEY7);
}

/**
  * @brief  Fills each BDMA_AESInitType member with its default value.
  * @param  BDMA_AESInitType: pointer to an BDMA_AESInitType structure which will be initialized.
  * @retval None
  */
void BDMA_AESStructInit(BDMA_AESInitType *BDMA_AESInitStruct)
{
  /*-------------- Reset BDMA AES init structure parameters values ---------------*/
  /* Initialize the aes128 mode*/
  BDMA_AESInitStruct->Mode = BDMA_AESMODE_128;
  /* Initialize the aes decode */
  BDMA_AESInitStruct->Direction = BDMA_AESDIRECTION_DECODE;
}

/**
  * @brief  Initializes AES.
  * @param  AES_InitStruct: AES configuration.
  *             Mode:
  *               @arg BDMA_AESMODE_128
  *               @arg BDMA_AESMODE_192
  *               @arg BDMA_AESMODE_256
  *             Direction:
  *               @arg BDMA_AESDIRECTION_ENCODE
  *               @arg BDMA_AESDIRECTION_DECODE
  *             KeyStr: the pointer to BDMA_AESKEYx register
  * @retval None
  */
void BDMA_AESInit(BDMA_AESInitType *AES_InitStruct)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BDMA_AESMOD(AES_InitStruct->Mode)); 
  assert_parameters(IS_BDMA_AESDIR(AES_InitStruct->Direction)); 

  tmp = READ_REG(BDMA->AESCTL);
  tmp &= ~(BDMA_AESCTL_MODE_MASK | \
           BDMA_AESCTL_ENC);
  tmp |= (AES_InitStruct->Mode   | \
          AES_InitStruct->Direction);
  WRITE_REG(BDMA->AESCTL, tmp);

  WRITE_REG(BDMA->AESKEY0, AES_InitStruct->KeyStr[0]);
  WRITE_REG(BDMA->AESKEY1, AES_InitStruct->KeyStr[1]);
  WRITE_REG(BDMA->AESKEY2, AES_InitStruct->KeyStr[2]);
  WRITE_REG(BDMA->AESKEY3, AES_InitStruct->KeyStr[3]);

  if ((AES_InitStruct->Mode == BDMA_AESMODE_192) || \
      (AES_InitStruct->Mode == BDMA_AESMODE_256))
  {
    WRITE_REG(BDMA->AESKEY4, AES_InitStruct->KeyStr[4]);
    WRITE_REG(BDMA->AESKEY5, AES_InitStruct->KeyStr[5]);
  }

  if (AES_InitStruct->Mode == BDMA_AESMODE_256)
  {
    WRITE_REG(BDMA->AESKEY6, AES_InitStruct->KeyStr[6]);
    WRITE_REG(BDMA->AESKEY7, AES_InitStruct->KeyStr[7]);
  }
}

/**
  * @brief  Enables or disables AES encrypt/decrypt function of DMA channel3.
  * @param  NewState: new state of the AES function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BDMA_AESCmd(FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  

  if (NewState == ENABLE)
  {
    SET_BIT(BDMA->C3CTL, BDMA_CCTL_AESEN);
  }
  else
  {
    CLEAR_BIT(BDMA->C3CTL, BDMA_CCTL_AESEN);
  }
}

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
