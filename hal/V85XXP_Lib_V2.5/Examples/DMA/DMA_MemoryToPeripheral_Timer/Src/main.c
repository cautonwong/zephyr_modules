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

#define Frame_Size (8)
#define Pack_Size  (8)

uint32_t i;
uint32_t Src_Buffer[Frame_Size*Pack_Size];

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
  TMR_InitType TMR_InitStruct;
  GPIO_InitType GPIO_InitStruct;
  uint32_t tmp;

  test_success = 0;

  Clock_Init();
  
  /* IOB7, CMOS output mode, output low */
  GPIO_WriteBit(GPIO_B, 7, 0);
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUTPUT_CMOS;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIOBToF_Init(GPIOB, &GPIO_InitStruct);  
  
  tmp = GPIOBToF_ReadOutputData(GPIOB);
  for (i=0; i<(Frame_Size*Pack_Size); i++)
  {
    tmp ^= GPIO_Pin_7;
    Src_Buffer[i] = tmp;
  }
  
  /* Timer1 initialization:
       - Clock source: internal clock(APB clock 13107200Hz) 
       - Overflow interval: 10us */
  TMR_DeInit(TMR1);
  TMR_InitStruct.ClockSource = TMR_CLKSRC_INTERNAL;
  TMR_InitStruct.EXTGT = TMR_EXTGT_DISABLE;
  TMR_InitStruct.Period = 13107200/100000 - 1;
  TMR_Init(TMR1, &TMR_InitStruct);
  
  /* DMA channel0 initialization */
  DMA_DeInit(DMA_CHANNEL_0);
  DMA_InitStruct.DestAddr = (uint32_t)&GPIOB->DAT;
  DMA_InitStruct.SrcAddr = (uint32_t)&Src_Buffer[0];
  DMA_InitStruct.FrameLen = Frame_Size - 1;
  DMA_InitStruct.PackLen = Pack_Size - 1;
  DMA_InitStruct.ContMode = DMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = DMA_TRANSMODE_SINGLE;
  DMA_InitStruct.ReqSrc = DMA_REQSRC_TIMER1;
  DMA_InitStruct.DestAddrMode = DMA_DESTADDRMODE_FIX;
  DMA_InitStruct.SrcAddrMode = DMA_SRCADDRMODE_FEND;
  DMA_InitStruct.TransSize = DMA_TRANSSIZE_WORD;
  DMA_Init(&DMA_InitStruct, DMA_CHANNEL_0);
  
  /* Enable Timer1 */
  TMR_Cmd(TMR1, ENABLE);
  /* Enable DMA channel 0 */
  DMA_Cmd(DMA_CHANNEL_0, ENABLE);
  
  /* Waiting for operation complete */
  while (DMA_GetINTStatus(DMA_INTSTS_C0BUSY));

  /* Resource release */
  DMA_DeInit(DMA_CHANNEL_0);
  TMR_DeInit(TMR1);
  /* IOB7, forbidden mode */
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIOBToF_Init(GPIOB, &GPIO_InitStruct);

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
