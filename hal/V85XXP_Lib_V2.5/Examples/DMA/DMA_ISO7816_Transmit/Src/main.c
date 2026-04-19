/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private functions ---------------------------------------------------------*/

volatile unsigned char test_success;

uint8_t Transmit_Buffer[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };

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

void ISO78160_DMATransmitErrorHandle(void)
{
  /* Transmit error handle */
  if (ISO7816_GetINTStatus(ISO78160, ISO7816_INTSTS_TXRTYERR))
  {
    ISO7816_ClearINTStatus(ISO78160, ISO7816_INTSTS_TXRTYERR);

    DMA_StopTransmit(DMA_CHANNEL_0, ENABLE);
    /* Waiting DMA channel idle */
    while (DMA_GetINTStatus(DMA_INTSTS_C0BUSY)); 
    DMA_StopTransmit(DMA_CHANNEL_0, DISABLE);
   
    printf("DMA Transmit error\r\n");
    printf("DMA stop, clear busy, clear stop\r\n");
  }
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  ISO7816_InitType ISO7816_InitStruct;
  DMA_InitType DMA_InitStruct;

  test_success = 0;
                
  Clock_Init();
  Stdio_Init();

  /* ISO78160 initialization */
  ISO7816_DeInit(ISO78160);
  ISO7816_InitStruct.FirstBit = ISO7816_FIRSTBIT_MSB;
  ISO7816_InitStruct.Parity = ISO7816_PARITY_EVEN;
  ISO7816_InitStruct.Baudrate = 9600;
  ISO7816_InitStruct.TXRetry = ISO7816_TXRTY_0;
  ISO7816_InitStruct.RXACKLength = ISO7816_RXACKLEN_2;
  ISO7816_InitStruct.TXNACKLength = ISO7816_TXNACKLEN_2;
  ISO7816_Init(ISO78160, &ISO7816_InitStruct);

  /* Enable ISO78160 transmit error interrupt */
  ISO7816_INTConfig(ISO78160, ISO7816_INT_TXRTYERR, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(ISO78160_IRQn, 3);

  /* Channel0 initialization, Transmit_Buffer -> ISO78160->DATA*/
  DMA_DeInit(DMA_CHANNEL_0);
  DMA_InitStruct.DestAddr = (uint32_t)&ISO78160->DATA;
  DMA_InitStruct.SrcAddr = (uint32_t)&Transmit_Buffer[0];
  DMA_InitStruct.FrameLen = 1 - 1;
  DMA_InitStruct.PackLen = 8 - 1;
  DMA_InitStruct.ReqSrc = DMA_REQSRC_ISO78160TX;
  DMA_InitStruct.TransSize = DMA_TRANSSIZE_BYTE;
  DMA_InitStruct.DestAddrMode = DMA_DESTADDRMODE_FIX;
  DMA_InitStruct.SrcAddrMode = DMA_SRCADDRMODE_FEND;
  DMA_InitStruct.ContMode = DMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = DMA_TRANSMODE_SINGLE;
  DMA_Init(&DMA_InitStruct, DMA_CHANNEL_0);

  /* Enable ISO78160 */
  ISO7816_Cmd(ISO78160, ENABLE);
  /* Enable channel 0 */
  DMA_Cmd(DMA_CHANNEL_0, ENABLE);
  
  test_success = 1; 
  
  /* Waiting for DMA channel0 frame end */
  while (1)
  {
    if (DMA_GetINTStatus(DMA_INTSTS_C0FE))
    {
      DMA_ClearINTStatus(DMA_INTSTS_C0FE);
      break;
    }
  }

  /* Waiting ISO78160 transmit(via DMA channel) done */
  while (!ISO7816_GetFlag(ISO78160, ISO7816_FLAG_DMATXDONE));
  ISO7816_ClearFlag(ISO78160, ISO7816_FLAG_DMATXDONE); 

  /* ISO7816/DMA resource release */
  DMA_DeInit(DMA_CHANNEL_0);
  ISO7816_DeInit(ISO78160);  

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
