/**
  ******************************************************************************
  * @file    lib_flash.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   FLASH library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_flash.h"

/* Private macro -------------------------------------------------------------*/

/** @defgroup FLASH_Private_Defines
  * @{
  */ 

#define FLASH_PASS_KEY             (0xBEEFBEEF)  /* FLASH Keys */
/* FLASH Status register */
#define FLASH_STATUS_Msk           ((uint8_t)0x1F)

/* FLASH_WC */
#define FLASH_WC_POS               (4UL)
#define FLASH_WC_MASK              (0x7FFFUL << FLASH_WC_POS)

#define FLASH_CLOCK_MAX            (200000000UL)
#define FLASH_R_TACC_CLOCK_MUL     (40000000UL)
#define FLASH_W_TPGH_TADS_TADH_MUL (50000000UL)

/**
  * @}
  */ 

/* Exported Functions ------------------------------------------------------- */

/** @defgroup FLASH_Private_Functions
  * @{
  */

/**
  * @brief  Wait for Flash to enter idle state.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval 0  Function succeeded.
  */
int FLASH_WaitForIdle(FLASH_Type *FLASHx)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));

  while (FLASHx->STATUS != 0)
  {
    if ((FLASHx->STATUS & (FLASH_GFC_STATUS_FAIL | FLASH_GFC_STATUS_SUCCESS)))
    {
      FLASHx->IRQ_STATUS_CLR = FLASH_STATUS_Msk;
      break;
    }
  }
  while((FLASHx->SFC_INFO_STATUS & FLASH_INFO_STATUS_MASK) != INFO_STATUS_IDLE)
  {;}
  return 0;
}

/**
  * @brief  Setting Flash timming time.
  * @note   This function should be called and executed from SRAM memory
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @param  sysclock: System clock.
  * @retval None.
  */
void FLASH_SetCycle(FLASH_Type *FLASHx, uint32_t sysclock)
{
  uint32_t tmp;
  uint32_t addr;

  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  
  if (sysclock > FLASH_CLOCK_MAX)
    sysclock = FLASH_CLOCK_MAX;
  
  /* Configure 1us cycles */

#if defined V32F20XXX_CM0_CORE
  addr = (uint32_t)&SYSCFG1->FLASHWC;
#else
  if(FLASHx == FLASHA)
  {
    addr = (uint32_t)&SYSCFG0->FLASHA_CTRL;
  }
  else if (FLASHx == FLASHB)
  {
    addr = (uint32_t)&SYSCFG0->FLASHB_CTRL;
  }
  else
  {
    addr = (uint32_t)&SYSCFG1->FLASHWC;
  }
#endif
  tmp = *(__IO uint32_t *)(addr);
  tmp &= ~(FLASH_WC_MASK);
  tmp |= (((sysclock/1000000UL)<<FLASH_WC_POS) & (FLASH_WC_MASK));
  *(__IO uint32_t *)(addr) = tmp;

  /* Flash clock < 200M */
  FLASHx->SFC_R_TPWS = 1UL;
  
  /* 19ns */
  FLASHx->SFC_R_TACC = (sysclock/FLASH_R_TACC_CLOCK_MUL) + 1;
  
  /* 2ns */
  FLASHx->SFC_R_TXYH = 1;
  FLASHx->SFC_W_TWPR = 1;
  
  /* 20ns */
  tmp = (sysclock/FLASH_W_TPGH_TADS_TADH_MUL) + 1;
  FLASHx->SFC_W_TPGH = tmp;
  FLASHx->SFC_W_TADS = tmp;
  FLASHx->SFC_W_TADH = tmp;
}

/**
  * @brief  Normal Flash page-erase.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @param  PageAddr: page-erase address.
  * @retval 0  Function succeeded.
  *         1  Function failed.
  */
int FLASH_PageErase(FLASH_Type *FLASHx, uint32_t PageAddr)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  assert_parameters(IS_FLASH_ADDRESS(PageAddr));
  
  FLASH_WaitForIdle(FLASHx);
  FLASHx->ADDR = PageAddr;
  FLASHx->CTRL = FLASH_GFC_CTRL_CMD_ERASE;
  FLASH_WaitForIdle(FLASHx);
  return 0;
}

/**
  * @brief  Normal Flash Program Byte.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval 0  Function succeeded.
  *         1  Function failed.
  */
int FLASH_ProgramByte(FLASH_Type *FLASHx, uint32_t Addr, const uint8_t *ByteBuffer, uint32_t Length)
{
  uint32_t size_128b, byte_remaind, i, j, byte_head_length;
  uint32_t WordBuffer[4];
  uint32_t byte_buffer_addr;

  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  assert_parameters(IS_FLASH_ADDRESS(Addr));
  
  FLASH_WaitForIdle(FLASHx);
  if((Addr&0x0F)!=0)
  {
    byte_head_length = 16-(Addr&0x0F);   
    byte_buffer_addr = (uint32_t)&WordBuffer[0];
    for(i=0; i<16; i++)
    {
      if(i < (16-byte_head_length))
      {
        *(__IO uint8_t *)(byte_buffer_addr++) = 0xFFU;
      }
      else if(i < (16-byte_head_length + Length))
      {
        *(__IO uint8_t *)(byte_buffer_addr++) = *(__IO uint8_t *)(ByteBuffer++);
      }
      else
      {
        *(__IO uint8_t *)(byte_buffer_addr++) = 0xFFU;
      }
    }
    
    Addr = Addr&(~0x0FU);
    FLASHx->ADDR = Addr;
    for(j=0;j<4;j++)
    {
      FLASHx->DATA[j] = WordBuffer[j]; 
    }
    FLASHx->CTRL = FLASH_GFC_CTRL_CMD_WRITE;
    
    FLASH_WaitForIdle(FLASHx);  
    
    if(Length<=byte_head_length)
    {
      return 0;
    }  
    
    Addr = Addr+0x10;
    Length -= byte_head_length;
  }

  size_128b = Length/16;
  for (i=0; i<size_128b; i++)
  {
    FLASHx->ADDR = Addr + i*16;
    
    byte_buffer_addr = (uint32_t)&WordBuffer[0];
    for(j=0;j<16;j++)
    {
      *(__IO uint8_t *)(byte_buffer_addr++) = *(__IO uint8_t *)(ByteBuffer++);
    }
    
    for(j=0;j<4;j++)
    {
      FLASHx->DATA[j] = WordBuffer[j]; 
    }   
    FLASHx->CTRL = FLASH_GFC_CTRL_CMD_WRITE;
    FLASH_WaitForIdle(FLASHx);
  }
  
  byte_remaind = Length - (16UL*size_128b);
  if (byte_remaind)
  {
    FLASHx->ADDR = Addr + i*16;
    byte_buffer_addr = (uint32_t)&WordBuffer[0];
    for (i=0; i<byte_remaind; i++)
    {
      *(__IO uint8_t *)(byte_buffer_addr++) = *(__IO uint8_t *)(ByteBuffer++);
    }
    for (i=byte_remaind; i<16; i++)
    {
      *(__IO uint8_t *)(byte_buffer_addr++) = 0xFFU;
    }
    for(j=0;j<4;j++)
    {
      FLASHx->DATA[j] = WordBuffer[j]; 
    }
    FLASHx->CTRL = FLASH_GFC_CTRL_CMD_WRITE;
    
    FLASH_WaitForIdle(FLASHx);
  }
 
  return 0;
}

/**
  * @brief  Normal Flash Program Word.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval 0  Function succeeded.
  *         1  Function failed.
  */
int FLASH_ProgramWord(FLASH_Type *FLASHx, uint32_t Addr, const uint32_t *WordBuffer, uint32_t Length)
{
  uint32_t size_128b, word_remaind, i, j, word_head_length;

  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  assert_parameters(IS_FLASH_ADDRESS(Addr));
  
  FLASH_WaitForIdle(FLASHx);
  
  if((Addr&0x0F)!=0)
  {
    FLASHx->ADDR = Addr;  
    word_head_length = 4-((Addr&0x0F)>>2);
    for(i=0; i<4; i++)
    {
      if(i < (4 - word_head_length))
      {
        FLASHx->DATA[i] = 0xFFFFFFFFUL;     
      }
      else if(i < (4 - word_head_length + Length))
      {
        FLASHx->DATA[i] = *(uint32_t *)WordBuffer;
        WordBuffer++;
      }
      else
      {
        FLASHx->DATA[i] = 0xFFFFFFFFUL;    
      }
    }
    FLASHx->CTRL = FLASH_GFC_CTRL_CMD_WRITE;  
    FLASH_WaitForIdle(FLASHx);
    
    if(Length <= word_head_length)
    {
      return 0;
    }
    
    Addr = Addr&(~0x0FU);
    Addr = Addr+0x10;
    Length -=  word_head_length;
  } 
  
  
  size_128b = Length / 4UL;
  for (i=0; i<size_128b; i++)
  {
    FLASHx->ADDR = Addr + i*16;
    for(j=0; j<4; j++)
    {
      FLASHx->DATA[j] = *(uint32_t *)WordBuffer; 
      WordBuffer++;
    }
    FLASHx->CTRL = FLASH_GFC_CTRL_CMD_WRITE;  
    FLASH_WaitForIdle(FLASHx);
  }
  
  word_remaind = Length - (4UL*size_128b);
  if (word_remaind != 0UL)
  {
    FLASHx->ADDR = Addr + 16*i;
    
    for(i=0;i<4;i++)
    {
      if(word_remaind==0)
      {
        FLASHx->DATA[i] = 0xFFFFFFFFUL;     
      }
      else
      {
        FLASHx->DATA[i] = *(uint32_t *)WordBuffer;
        WordBuffer++;
        word_remaind--;
      }    
    }
    FLASHx->CTRL = FLASH_GFC_CTRL_CMD_WRITE;
    
    FLASH_WaitForIdle(FLASHx);
  }
  return 0;
}

/**
  * @brief  Flash chip erase function.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval None
  */
void FLASH_ChipErase(FLASH_Type *FLASHx)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  
  FLASH_WaitForIdle(FLASHx);
  FLASHx->ADDR = 0;
  FLASHx->CTRL = FLASH_GFC_CTRL_CMD_MERASE;
  FLASH_WaitForIdle(FLASHx);
}

/**
  * @brief  Flash info0 Read Word.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval 0  Function succeeded.
  */
int FLASH_INFO0ReadWord(FLASH_Type *FLASHx, uint32_t Addr, uint32_t *WordBuffer, uint32_t Length)
{
  uint32_t size_128b, word_remaind, i, j;
  uint32_t  word_head_length;

  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  
  FLASH_WaitForIdle(FLASHx);
  
  if ((Addr & 0x0F) != 0)
  {
    FLASHx->SFC_INFO_ADDR = Addr;
    FLASHx->SFC_INFO_WR_CTRL = FLASH_INFO_CTRL_CMD_READ;
    FLASHx->SFC_INFO_WR_START = FLASH_PASS_KEY;
    FLASH_WaitForIdle(FLASHx); 
    word_head_length = ((Addr&0x0F)>>2);
    
    while ((Length)&&(word_head_length<4))
    {
      *(WordBuffer++) = FLASHx->SFC_INFO_DATA[word_head_length]; 
      Length--;
      word_head_length++;
    }
    Addr = Addr&(~0x0FU);
    Addr = Addr+0x10;   
  }
  
  i = 0UL;
  size_128b = Length / 4UL;
  for (i=0; i<size_128b; i++)
  {
    FLASHx->SFC_INFO_ADDR = Addr + i*16;
    FLASHx->SFC_INFO_WR_CTRL = FLASH_INFO_CTRL_CMD_READ;
    FLASHx->SFC_INFO_WR_START = FLASH_PASS_KEY;
  
    FLASH_WaitForIdle(FLASHx);
    
    for(j=0;j<4;j++)
    {
      *(WordBuffer++) = FLASHx->SFC_INFO_DATA[j];
    }
  }
  word_remaind = Length - (4UL*size_128b);
  if (word_remaind != 0UL)
  {
    FLASHx->SFC_INFO_ADDR = Addr + i*16;
    FLASHx->SFC_INFO_WR_CTRL = FLASH_INFO_CTRL_CMD_READ;
    FLASHx->SFC_INFO_WR_START = FLASH_PASS_KEY;
    FLASH_WaitForIdle(FLASHx);
    
    j = 0;
     while (word_remaind)
    {
      *(WordBuffer++) = FLASHx->SFC_INFO_DATA[j++]; 
      word_remaind--;
    }
  }
  
  return 0;
}

/**
  * @brief  Flash info1 Read Word
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval 0  Function succeeded.
  */
int FLASH_INFO1ReadWord(FLASH_Type *FLASHx, uint32_t Addr, uint32_t *WordBuffer, uint32_t Length)
{
  uint32_t size_128b, word_remaind, i, j;
  uint32_t  word_head_length;

  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  
  FLASH_WaitForIdle(FLASHx);
  
  if ((Addr&0x0F) != 0)
  {
    FLASHx->SFC_INFO_ADDR = Addr;
    FLASHx->SFC_INFO_WR_CTRL = FLASH_INFO_CTRL_CMD_READ|FLASH_INFO_CTRL_SELINFO1;
    FLASHx->SFC_INFO_WR_START = FLASH_PASS_KEY;
    FLASH_WaitForIdle(FLASHx); 
    word_head_length = ((Addr&0x0F)>>2);
    
    while (Length && (word_head_length<4))
    {
      *(WordBuffer++) = FLASHx->SFC_INFO_DATA[word_head_length]; 
      Length--;
      word_head_length++;
    }
    Addr = Addr&(~0x0FU);
    Addr = Addr+0x10;   
  }
  
  i = 0UL;
  size_128b = Length / 4UL;
  for (i=0; i<size_128b; i++)
  {
    FLASHx->SFC_INFO_ADDR = Addr + i*16;
    FLASHx->SFC_INFO_WR_CTRL = FLASH_INFO_CTRL_CMD_READ|FLASH_INFO_CTRL_SELINFO1;
    FLASHx->SFC_INFO_WR_START = FLASH_PASS_KEY;
  
    FLASH_WaitForIdle(FLASHx);
    
    for(j=0;j<4;j++)
    {
      *(WordBuffer++) = FLASHx->SFC_INFO_DATA[j];
    }
  }
  word_remaind = Length - (4UL*size_128b);
  if (word_remaind != 0UL)
  {
    FLASHx->SFC_INFO_ADDR = Addr + i*16;
    FLASHx->SFC_INFO_WR_CTRL = FLASH_INFO_CTRL_CMD_READ|FLASH_INFO_CTRL_SELINFO1;
    FLASHx->SFC_INFO_WR_START = FLASH_PASS_KEY;
    FLASH_WaitForIdle(FLASHx);
    
    j = 0;
     while (word_remaind)
    {
      *(WordBuffer++) = FLASHx->SFC_INFO_DATA[j++]; 
      word_remaind--;
    }
  }
  
  return 0;
}

/**
  * @brief  Initializes FLASHx cache.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval None
  */
void FLASH_Cache_Init(FLASH_Type *FLASHx)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  
  FLASHx->CHCHE_CCR |= FLASH_CACHE_CCR_POWREQ |\
                       FLASH_CACHE_CCR_POWMAN |\
                       FLASH_CACHE_CCR_MANINV;
  while(!(FLASHx->CHCHE_SR & FLASH_CACHE_SR_POWSTAT));
  FLASHx->CHCHE_CCR |= FLASH_CACHE_CCR_STATISTICEN |\
                       FLASH_CACHE_CCR_PREFETCH    |\
                       FLASH_CACHE_CCR_INVREQ;
}

/**
  * @brief  Enables or disables FLASHx cache.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval None
  */
void FLASH_Cache_Cmd(FLASH_Type *FLASHx, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState == ENABLE)
  {
    FLASHx->CHCHE_CCR |= FLASH_CACHE_CCR_EN;
  }
  else
  {
    FLASHx->CHCHE_CCR &= ~FLASH_CACHE_CCR_EN;
  }
}

/**
  * @brief  Refresh cache.
  * @param  FLASHx: Select the FLASH peripheral. 
  *   This parameter can be one of the following values:
  *   FLASHA, FLASHB, FLASH0.
  * @retval None
  */
void FLASH_Cache_Refresh(FLASH_Type *FLASHx)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_ALL_INSTANCE(FLASHx));
  
  if(FLASHx->CHCHE_CCR & FLASH_CACHE_CCR_MANINV)
  {
    if(!(FLASHx->CHCHE_CCR & FLASH_CACHE_CCR_EN))
    {
      FLASHx->CHCHE_CCR |= FLASH_CACHE_CCR_INVREQ;
    }
    else
    {
      FLASHx->CHCHE_CCR &= ~FLASH_CACHE_CCR_EN;
      FLASHx->CHCHE_CCR |= FLASH_CACHE_CCR_INVREQ;
      FLASHx->CHCHE_CCR |= FLASH_CACHE_CCR_EN;
    }
  }
}
/**
  * @}
  */

/*********************************** END OF FILE ******************************/
