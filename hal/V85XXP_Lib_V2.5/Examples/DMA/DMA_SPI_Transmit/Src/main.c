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

#define Buffer_Size (8)

uint32_t i;
uint8_t Transmit_Buffer[Buffer_Size] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };

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
  SPI_InitType SPI_InitStruct;
  DMA_InitType DMA_InitStruct;

  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  /* SPI1 initialization, master mode */
  SPI_DeviceInit(SPI1);
  SPI_InitStruct.Mode = SPI_MODE_MASTER;
  SPI_InitStruct.ClockDivision = SPI_CLKDIV_32;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_DISABLE;
  SPI_InitStruct.SPH = SPI_SPH_0;
  SPI_InitStruct.SPO = SPI_SPO_0;
  SPI_InitStruct.SWAP = SPI_SWAP_DISABLE;
  SPI_Init(SPI1, &SPI_InitStruct);
  /* Enable SPI1 smart mode */
  SPI_SmartModeCmd(SPI1, ENABLE);
  
  /* Channel0 initialization, Transmit_Buffer -> SPI1_TXDAT */
  DMA_DeInit(DMA_CHANNEL_0);
  DMA_InitStruct.DestAddr = (uint32_t)&SPI1->TXDAT;
  DMA_InitStruct.SrcAddr = (uint32_t)&Transmit_Buffer[0];
  DMA_InitStruct.FrameLen = 1 - 1;
  DMA_InitStruct.PackLen = Buffer_Size - 1;
  DMA_InitStruct.ReqSrc = DMA_REQSRC_SPI1TX;
  DMA_InitStruct.TransSize = DMA_TRANSSIZE_BYTE;
  DMA_InitStruct.DestAddrMode = DMA_DESTADDRMODE_FIX;
  DMA_InitStruct.SrcAddrMode = DMA_SRCADDRMODE_FEND;
  DMA_InitStruct.ContMode = DMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = DMA_TRANSMODE_SINGLE;
  DMA_Init(&DMA_InitStruct, DMA_CHANNEL_0);
  
  /* Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);
  /* Enable channel 0 */
  DMA_Cmd(DMA_CHANNEL_0, ENABLE);
  
  /* Waiting DMA channel's operation done */
  while (DMA_GetINTStatus(DMA_INTSTS_C0BUSY));
  /* Waiting SPI1 transmit(via DMA channel) done */
  while (!SPI_GetStatus(SPI1, SPI_STS_DMATXDONE));
  SPI_ClearStatus(SPI1, SPI_STS_DMATXDONE);
    
  /* SPI/DMA resource release */
  DMA_DeInit(DMA_CHANNEL_0);
  SPI_DeviceInit(SPI1);
        
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
