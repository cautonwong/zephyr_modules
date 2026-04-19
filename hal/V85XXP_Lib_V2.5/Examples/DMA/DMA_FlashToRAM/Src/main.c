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

#define Buffer_Size (16)

const uint32_t Src_Const_Buffer[Buffer_Size] = 
{
  0x00000000, 0x11111111, 0x22222222, 0x33333333, 
  0x44444444, 0x55555555, 0x66666666, 0x77777777,
  0x88888888, 0x99999999, 0xAAAAAAAA, 0xBBBBBBBB,
  0xCCCCCCCC, 0xDDDDDDDD, 0xEEEEEEEE, 0xFFFFFFFF
};

uint32_t Dst_Buffer[Buffer_Size] = { 0 };

__IO uint32_t flag_dmaerr; /* Set to 1 if an error transfer is detected */

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
  uint32_t i;

  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  /* DMA channel0 initialization */
  DMA_DeInit(DMA_CHANNEL_0);
  DMA_InitStruct.DestAddr = (uint32_t)&Dst_Buffer[0];
  DMA_InitStruct.SrcAddr = (uint32_t)&Src_Const_Buffer[0];
  DMA_InitStruct.FrameLen = 1 - 1;
  DMA_InitStruct.PackLen = Buffer_Size - 1;
  DMA_InitStruct.ContMode = DMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = DMA_TRANSMODE_SINGLE;
  DMA_InitStruct.ReqSrc = DMA_REQSRC_SOFT;
  DMA_InitStruct.DestAddrMode = DMA_DESTADDRMODE_FEND;
  DMA_InitStruct.SrcAddrMode = DMA_SRCADDRMODE_FEND;
  DMA_InitStruct.TransSize = DMA_TRANSSIZE_WORD;
  DMA_Init(&DMA_InitStruct, DMA_CHANNEL_0);
  
  /* Enable DMA channel0 data abort interrupt */
  DMA_INTConfig(DMA_INT_C0DA, ENABLE);
  /* Enable DMA NVIC interrupt */
  CORTEX_SetPriority_ClearPending_EnableIRQ(DMA_IRQn, 0);
  
  flag_dmaerr = 0;/* Set to 1 if an error transfer is detected */
  /* Enable channel0, start operation */
  DMA_Cmd(DMA_CHANNEL_0, ENABLE);
  
  /* Waiting for operation complete */
  while (DMA_GetINTStatus(DMA_INTSTS_C0BUSY));
  
  /* DMA channel0 resource release */
  DMA_DeInit(DMA_CHANNEL_0);
  CORTEX_NVIC_DisableIRQ(DMA_IRQn);
  
  for (i=0; i<16; i++)
  {
    if (Dst_Buffer[i] != Src_Const_Buffer[i])
    {
      printf("DMA Flash to RAM ERROR!\r\n");
      test_success = 0;
      while (1)
      {
        WDT_Clear();
      }
    }
  }
  
  if (flag_dmaerr)
  {
    printf("DMA Flash to RAM ERROR!\r\n");
    test_success = 0;
  }
  else
  {
    printf("DMA Flash to RAM OK!\r\n");
    test_success = 1;
  }
  
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
