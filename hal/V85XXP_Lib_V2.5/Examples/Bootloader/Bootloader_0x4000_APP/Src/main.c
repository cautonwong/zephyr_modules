/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

volatile unsigned char test_success;

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define FLASH_IAP_ADDR 0x00000000//IAP start address

//Jump to IAP peogram
typedef  void (*IapFun)(void);
IapFun JumpToIap;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Error_Handle.
  * @param  None
  * @retval None
  */
void Error_Handle(void)
{
  while (1);
}

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
  uint8_t key;
  uint32_t val;
  
  test_success = 0;
  
  Clock_Init();
  
  UART5->BAUDDIV = CLK_GetPCLKFreq()/115200;
  UART5->CTRL = UART_CTRL_TXEN|UART_CTRL_RXEN;
  
  val = __get_MSP();
  printf("msp 0x%x\r\n", (unsigned int)val);
  printf("Enter App test.\r\n");

  NVIC_SetPendingIRQ(UART5_IRQn);
  NVIC_EnableIRQ(UART5_IRQn);
  
  test_success = 0;
  
  while (1)
  {
    SerialKeyPressed(&key);
    /*If UART receive '6', jump to IAP program*/
    if(key == 0x36) 
    {    
      JumpToIap=(IapFun)*(volatile uint32_t*)(FLASH_IAP_ADDR+4);
      __set_MSP(*(__IO uint32_t*) FLASH_IAP_ADDR);
      /*Jump to IAP program*/
      JumpToIap();
    }
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

uint32_t SerialKeyPressed(uint8_t *key)
{
  if (UART5->STATE&UART_STATE_RXFULL)
  {
    *key = (uint8_t)UART5->DATA;
    return 1;
  }
  else
  {
    return 0;
  }
}

/*********************************** END OF FILE ******************************/
