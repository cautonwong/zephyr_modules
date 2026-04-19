/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

volatile unsigned char test_success;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Clock_Init:
              - PLLL input clock    : External 32K crystal
              - PLLL frequency      : 26M
              - AHB Clock source    : PLLL
              - AHB Clock frequency : 26M (PLLL divided by 1)
              - APB Clock frequency : 13M (AHB Clock divided by 2)
  * @param  None
  * @retval None
  */
void Clock_Init(void)
{
  CLK_InitTypeDef CLK_Struct;

  CLK_Struct.ClockType = CLK_TYPE_AHBSRC \
                        |CLK_TYPE_PLLL   \
                        |CLK_TYPE_HCLK   \
                        |CLK_TYPE_PCLK;
  CLK_Struct.AHBSource      = CLK_AHBSEL_LSPLL;
  CLK_Struct.PLLL.Frequency = CLK_PLLL_26_2144MHz;
  CLK_Struct.PLLL.Source    = CLK_PLLLSRC_XTALL;
  CLK_Struct.PLLL.State     = CLK_PLLL_ON;
  CLK_Struct.HCLK.Divider   = 1;
  CLK_Struct.PCLK.Divider   = 2;
  CLK_ClockConfig(&CLK_Struct);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  DMA_InitType DMA_InitStruct;
  DMA_AESInitType AESInitStruct;
  uint32_t i;
  uint8_t dst[16];
  uint8_t res[16];

#ifdef __ICCARM__
  #pragma data_alignment=4
#endif
  uint8_t key[24]
#ifndef __ICCARM__
  __attribute__((aligned (4)))
#endif
;

#ifdef __ICCARM__
  #pragma data_alignment=4
#endif
  uint8_t src[16]
#ifndef __ICCARM__
  __attribute__((aligned (4)))
#endif
;

  test_success = 0;

  for (i=0; i<24; i++)
    key[i] = i;

  for (i=0; i<16; i++)
    src[i] = 0x10*i + i;

  Clock_Init();
  Stdio_Init();

  /* DMA channel3 initialization */
  DMA_DeInit(DMA_CHANNEL_3);
  DMA_InitStruct.SrcAddr = (uint32_t)&src[0];
  DMA_InitStruct.DestAddr = (uint32_t)&dst[0];
  DMA_InitStruct.FrameLen = 0;
  DMA_InitStruct.PackLen = 4 - 1;
  DMA_InitStruct.ContMode = DMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = DMA_TRANSMODE_SINGLE;
  DMA_InitStruct.ReqSrc = DMA_REQSRC_SOFT;
  DMA_InitStruct.DestAddrMode = DMA_DESTADDRMODE_FEND;
  DMA_InitStruct.SrcAddrMode = DMA_SRCADDRMODE_FEND;
  DMA_InitStruct.TransSize = DMA_TRANSSIZE_WORD;
  DMA_Init(&DMA_InitStruct, DMA_CHANNEL_3);

  /* AES configuration, encode */
  DMA_AESDeInit();
  AESInitStruct.Direction = DMA_AESDIRECTION_ENCODE;
  AESInitStruct.Mode = DMA_AESMODE_192;
  AESInitStruct.KeyStr = (uint32_t *)&key[0];
  DMA_AESInit(&AESInitStruct);

  /* Enable AES and DMA channel3 */
  DMA_AESCmd(ENABLE);
  DMA_Cmd(DMA_CHANNEL_3, ENABLE);

  /* Waiting channel3 operation complete */
  while (DMA_GetINTStatus(DMA_INTSTS_C3BUSY));
  printf("encode:\r\n");
  for (i = 0; i < 16; i++)
  {
    printf("0x%x\t", dst[i]);
  }
  printf("\r\n");

  /////////////////////////////
  DMA_DeInit(DMA_CHANNEL_3);
  DMA_InitStruct.SrcAddr = (uint32_t)&dst[0];
  DMA_InitStruct.DestAddr = (uint32_t)&res[0];
  DMA_Init(&DMA_InitStruct, DMA_CHANNEL_3);

  /* AES configuration, decode */
  DMA_AESDeInit();
  AESInitStruct.Direction = DMA_AESDIRECTION_DECODE;
  AESInitStruct.KeyStr = (uint32_t *)&key[0];
  DMA_AESInit(&AESInitStruct);

  /* Enable AES and DMA channel3 */
  DMA_AESCmd(ENABLE);
  DMA_Cmd(DMA_CHANNEL_3, ENABLE);

  /* Waiting channel3 operation complete */
  while (DMA_GetINTStatus(DMA_INTSTS_C3BUSY));
  printf("decode:\r\n");
  for (i = 0; i < 16; i++)
  {
    printf("0x%x\t", res[i]);
  }
  printf("\r\n");

  /* Resource release */
  DMA_DeInit(DMA_CHANNEL_3);
  DMA_AESDeInit();

  test_success = 1;

  while (1)
  {
    WDT_Clear();
  }
}

#ifndef  ASSERT_NDEBUG
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
