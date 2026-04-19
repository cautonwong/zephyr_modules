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

void ISO78160_TransmitErrorHandle(void)
{
  /* Transmit error handle */
  if (ISO7816_GetINTStatus(ISO78160, ISO7816_INTSTS_TXRTYERR))
  {
    ISO7816_ClearINTStatus(ISO78160, ISO7816_INTSTS_TXRTYERR);
    printf("Transmit error\r\n");
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
  uint8_t data[4] = { 0x12, 0x34, 0x56, 0x78 };
  int i;

  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  /* ISO78160 initialization */
  ISO7816_DeInit(ISO78160);
  ISO7816_InitStruct.FirstBit = ISO7816_FIRSTBIT_MSB;
  ISO7816_InitStruct.Parity = ISO7816_PARITY_EVEN;
  ISO7816_InitStruct.Baudrate = 9600;
  ISO7816_InitStruct.TXRetry = ISO7816_TXRTY_5;
  ISO7816_InitStruct.RXACKLength = ISO7816_RXACKLEN_2;
  ISO7816_InitStruct.TXNACKLength = ISO7816_TXNACKLEN_2;
  ISO7816_Init(ISO78160, &ISO7816_InitStruct);

  /* Enable ISO78160 transmit error interrupt */
  ISO7816_INTConfig(ISO78160, ISO7816_INT_TXRTYERR, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(ISO78160_IRQn, 3);
  
  ISO7816_Cmd(ISO78160, ENABLE);
  
  test_success = 1;
  
  for (i=0; i<4; i++)
  {
    ISO7816_SendData(ISO78160, data[i]);
    while (!ISO7816_GetINTStatus(ISO78160, ISO7816_INTSTS_TXDONE));
    ISO7816_ClearINTStatus(ISO78160, ISO7816_INTSTS_TXDONE);
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
