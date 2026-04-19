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
  uint32_t data_a[2] = { 0xFFFFFFFF, 0xFFFFFFFF };
  uint32_t data_b[2] = { 5, 0x80000000 };
  uint32_t data_o[2] = { 0 };
  
  test_success = 0;
  
  /* Clock initialization */
  Clock_Init();
  /* Print initialization */
  Stdio_Init();
  
  /* Configure address */
  CRYPT_AddressAConfig((uint32_t)&data_a[0]);
  CRYPT_AddressBConfig((uint32_t)&data_b[0]);
  CRYPT_AddressOConfig((uint32_t)&data_o[0]);
  
  /* Start operation */
  CRYPT_StartAdd(CRYPT_LENGTH_64, CRYPT_STOPCPU);
  /* Waiting for operation done */
  CRYPT_WaitForLastOperation();
  
  printf("Carry bit is %d\r\n", CRYPT_GetCarryBorrowBit());
#ifdef __GNUC__
  printf("Result[63:32] 0x%08lx\r\n", data_o[1]);
  printf("Result[31: 0] 0x%08lx\r\n", data_o[0]);
#else
  printf("Result[63:32] 0x%08x\r\n", data_o[1]);
  printf("Result[31: 0] 0x%08x\r\n", data_o[0]);
#endif

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
