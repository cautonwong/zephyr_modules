/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define AES_KEY_SIZE    (24U)
#define AES_TEXT_SIZE   (16U)

__ALIGN_BEGIN static const uint8_t key[AES_KEY_SIZE] __ALIGN_END = 
{
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
};

__ALIGN_BEGIN static const uint8_t Plaintext[AES_TEXT_SIZE] __ALIGN_END = 
{
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
  0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
};

__ALIGN_BEGIN static const uint8_t Ciphertext[AES_TEXT_SIZE] __ALIGN_END = 
{
  0xDD, 0xA9, 0x7C, 0xA4, 0x86, 0x4C, 0xDF, 0xE0,
  0x6E, 0xAF, 0x70, 0xA0, 0xEC, 0x0D, 0x71, 0x91
};

__ALIGN_BEGIN static uint8_t PlainBuffer[AES_TEXT_SIZE] __ALIGN_END = { 0 };
__ALIGN_BEGIN static uint8_t CipherBuffer[AES_TEXT_SIZE] __ALIGN_END = { 0 };
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  BDMA_InitType DMA_InitStruct;
  BDMA_AESInitType AESInitStruct;
  
  /* V32F20xxx CM0 core STD library initialization:
       - HCLK 48 MHz, 
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Low Level Initialization
     */
  STD_Init(48000000UL);
  BSP_Printf_Init();
  
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  
  /*- Encode -------------------------------------------------------------------*/
  /* DMA channel 3 configuration */
  BDMA_DeInit(BDMA_CHANNEL_3);
  BDMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.SrcAddr      = (uint32_t)&Plaintext[0];
  DMA_InitStruct.SrcAddrMode  = BDMA_SRCADDRMODE_FEND;
  DMA_InitStruct.DestAddr     = (uint32_t)&CipherBuffer[0];
  DMA_InitStruct.DestAddrMode = BDMA_DESTADDRMODE_FEND;
  DMA_InitStruct.FrameLen     = 1 - 1;
  DMA_InitStruct.PackLen      = 4 - 1;
  DMA_InitStruct.TransSize    = BDMA_TRANSSIZE_WORD;
  DMA_InitStruct.ReqSrc       = BDMA_REQSRC_SOFT;
  DMA_InitStruct.ContMode     = BDMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode    = BDMA_TRANSMODE_SINGLE;
  BDMA_Init(&DMA_InitStruct, BDMA_CHANNEL_3);
  
  /* AES configuration, encode */
  BDMA_AESDeInit();
  BDMA_AESStructInit(&AESInitStruct);
  AESInitStruct.Direction = BDMA_AESDIRECTION_ENCODE;
  AESInitStruct.Mode = BDMA_AESMODE_192;
  AESInitStruct.KeyStr = (uint32_t *)&key[0];
  BDMA_AESInit(&AESInitStruct);
  
  /* Enable DMA channel3 */
  BDMA_AESCmd(ENABLE);
  BDMA_Cmd(BDMA_CHANNEL_3, ENABLE);
  /* Wait until DMA channel3 idle */
  while (SET == BDMA_GetFlagStatus(BDMA_FLAG_C3BUSY))
  {
  }
  
  if (0 != memcmp(CipherBuffer, Ciphertext, AES_TEXT_SIZE))
  {
    BSP_LED_On(LED2);
    while (1);
    /* Encode error handler */
    
  }
  
  /*- Decode -------------------------------------------------------------------*/
  BDMA_DeInit(BDMA_CHANNEL_3);
  DMA_InitStruct.SrcAddr = (uint32_t)&Ciphertext[0];
  DMA_InitStruct.DestAddr = (uint32_t)&PlainBuffer[0];
  BDMA_Init(&DMA_InitStruct, BDMA_CHANNEL_3);
  
  /* AES configuration, decode */
  BDMA_AESDeInit();
  BDMA_AESStructInit(&AESInitStruct);
  AESInitStruct.Direction = BDMA_AESDIRECTION_DECODE;
  AESInitStruct.Mode = BDMA_AESMODE_192;
  AESInitStruct.KeyStr = (uint32_t *)&key[0];
  BDMA_AESInit(&AESInitStruct);

  /* Enable AES and DMA channel3 */
  BDMA_AESCmd(ENABLE);
  BDMA_Cmd(BDMA_CHANNEL_3, ENABLE);
  
  /* Wait until DMA channel3 idle */
  while (SET == BDMA_GetFlagStatus(BDMA_FLAG_C3BUSY))
  {
  }
  
  if (0 != memcmp(PlainBuffer, Plaintext, AES_TEXT_SIZE))
  {
    BSP_LED_On(LED2);
    while (1);
    /* Encode error handler */
    
  }
  else
  {
    BSP_LED_On(LED1);
    printf("DMA AES result is expected\r\n");
  }
  
  while (1)
  {
    ;
  }
}

/**
  * @brief  Initialize the Low level.
  * @retval None
  */
void STD_lowInit(void)
{
  /* nothing to do */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the STD error return state */
  while(1)
  {
  }
}

#ifdef  ASSERT_ENABLED
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_errhandler error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_errhandler error line source number
  * @retval None
  */
void assert_errhandler(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************** END OF FILE ******************************/
