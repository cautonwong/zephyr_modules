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

uint8_t bsrc[] = "This is a uart5 DMA send test program!\r\n";
__IO uint32_t flag_framend;
__IO uint32_t flag_uarterr;
__IO uint32_t delay_cycles;

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
  UART_InitType UART_InitStruct;
  uint8_t tx_size;
  
  test_success = 0;

  Clock_Init();
  
  /* UART5 initialization */
  UART_DeInit(UART5);
  UART_InitStruct.Baudrate = 115200;
  UART_InitStruct.FirstBit = UART_FIRSTBIT_LSB;
  UART_InitStruct.Mode = UART_MODE_TX;
  UART_InitStruct.Parity = UART_PARITY_NONE;
  UART_Init(UART5, &UART_InitStruct);
  
  /* Enable UART5 transmit error interrupt(transmit overrun) */
  UART_INTConfig(UART5, UART_INT_TXOV, ENABLE);
  /* Enable DMA NVIC interrupt */
  NVIC_ClearPendingIRQ(UART5_IRQn);
  NVIC_EnableIRQ(UART5_IRQn);
  
  /* DMA channel2 initialization */
  tx_size = (sizeof(bsrc) / sizeof(bsrc[0])) - 1;
  DMA_DeInit(DMA_CHANNEL_2);
  DMA_InitStruct.DestAddr = (uint32_t)&UART5->DATA;
  DMA_InitStruct.SrcAddr = (uint32_t)&bsrc[0];
  DMA_InitStruct.FrameLen = 1 - 1;
  DMA_InitStruct.PackLen = tx_size - 1;
  DMA_InitStruct.ContMode = DMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = DMA_TRANSMODE_SINGLE;
  DMA_InitStruct.ReqSrc = DMA_REQSRC_UART5TX;
  DMA_InitStruct.DestAddrMode = DMA_DESTADDRMODE_FIX;
  DMA_InitStruct.SrcAddrMode = DMA_SRCADDRMODE_FEND;
  DMA_InitStruct.TransSize = DMA_TRANSSIZE_BYTE;
  DMA_Init(&DMA_InitStruct, DMA_CHANNEL_2);
  
  /* Enable DMA channel2 frame end interrupt */
  DMA_INTConfig(DMA_INT_C2FE, ENABLE);
  /* Enable DMA NVIC interrupt */
  NVIC_ClearPendingIRQ(DMA_IRQn);
  NVIC_EnableIRQ(DMA_IRQn);
  
  flag_framend = 0;
  flag_uarterr = 0;
  DMA_Cmd(DMA_CHANNEL_2, ENABLE);
  
  /* Waiting for DMA channel2 frame end interrupt */
  while (flag_framend == 0);
  /* Waiting for UART5 transmit(via DMA channel) complete */
  while(UART_GetFlag(UART5, UART_FLAG_DMATXDONE) == 0);
  UART_ClearFlag(UART5, UART_FLAG_DMATXDONE);

  /* DMA channel2, UART5 resource release */
  DMA_DeInit(DMA_CHANNEL_2);
  UART_DeInit(UART5);
  NVIC_DisableIRQ(DMA_IRQn);
  NVIC_DisableIRQ(UART5_IRQn);
  
  /* Print initialization */
  Stdio_Init();
  if (flag_uarterr)
  {
    printf("Send finish, transmit error!\r\n");
    test_success = 0;
  }
  else
  {
    printf("Send finish, transmit ok!\r\n");
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
