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

int i;
__IO uint32_t Receive_Cnt; /* Increased by 1 when receive a byte data */
uint8_t Receive_Buffer[Buffer_Size];

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
  U32K_InitType U32K_InitStruct;
  GPIO_InitType GPIO_InitStruct;

  test_success = 0;

  Clock_Init();
  UART5->BAUDDIV = CLK_GetPCLKFreq()/9600;
  UART5->CTRL = UART_CTRL_TXEN;
  
  /* U32K0 receive line RX0(IOA12), input mode */
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
  GPIOA_Init(GPIOA, &GPIO_InitStruct);
  
  /* U32K0 initialization */
  U32K_DeInit(U32K0);
  U32K_InitStruct.AutoCal = U32K_AUTOCAL_ON;
  U32K_InitStruct.Debsel = U32K_DEBSEL_0;
  U32K_InitStruct.Baudrate = 9600;
  U32K_InitStruct.FirstBit = U32K_FIRSTBIT_LSB;
  U32K_InitStruct.LineSel = U32K_LINE_RX0;
  U32K_InitStruct.Parity = U32K_PARITY_EVEN;
  U32K_Init(U32K0, &U32K_InitStruct);
  
  /* Enable U32K0 receive interrupt */
  U32K_INTConfig(U32K0, U32K_INT_RX, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(U32K0_IRQn, 0);
  
  /* Enable U32K0 */
  Receive_Cnt = 0;
  U32K_Cmd(U32K0, ENABLE);
  
  test_success = 1;
  
  while (Receive_Cnt < Buffer_Size);
  
  /* U32K0 resource release */
  U32K_DeInit(U32K0);
  CORTEX_NVIC_DisableIRQ(U32K0_IRQn);
  /* U32K0 receive line RX0(IOA12), forbidden mode */
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
  GPIOA_Init(GPIOA, &GPIO_InitStruct);
  
  for (i=0; i<Buffer_Size; i++)
    printf("Receive[%d]\t0x%x\r\n", i, Receive_Buffer[i]);
  
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
