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
uint8_t TX_Buffer[4] = { 0x12, 0x34, 0x56, 0x78 };
uint32_t nTXLen;
uint8_t RX_Buffer[4] = { 0x00, 0x00, 0x00, 0x00 };
uint32_t nRXLen;
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
  UART_InitType UART_InitStruct;
  uint32_t i;

  test_success = 0;
  nTXLen = 0;
  nRXLen = 0;

  Clock_Init();
  Stdio_Init();
  
  /* UART0 initialization */
  UART_DeInit(UART0);
  UART_InitStruct.Baudrate = 9600;
  UART_InitStruct.FirstBit = UART_FIRSTBIT_LSB;
  UART_InitStruct.Mode = UART_MODE_TX|UART_MODE_RX;
  UART_InitStruct.Parity = UART_PARITY_ODD;
  UART_Init(UART0, &UART_InitStruct);
  
  UART_INTConfig(UART0,UART_INT_TXDONE, ENABLE);
  UART_INTConfig(UART0,UART_INT_RX, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(UART0_IRQn, 0);
  
  UART_SendData(UART0, TX_Buffer[0]);
  nTXLen++;
  
  while(nTXLen<4)
  {
    WDT_Clear();
  }
  
  printf("UART0 send datas finish!\r\n");

  test_success = 1;
  
  for(i=0; i<4; i++)
  {
    if(TX_Buffer[i] != RX_Buffer[i])
    {
      printf("UART0 Receive datas error!\r\n");
    }
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
