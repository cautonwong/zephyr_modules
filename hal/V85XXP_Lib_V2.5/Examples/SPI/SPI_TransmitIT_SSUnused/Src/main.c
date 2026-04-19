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
uint32_t i;
uint8_t Transmit_Buffer[Buffer_Size];
uint8_t Receive_Buffer[Buffer_Size];
__IO uint32_t Transmit_Cnt; /* Increased by 1 when transmit a byte data */
__IO uint32_t Receive_Cnt; /* Increased by 1 when receive a byte data */

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
  GPIO_InitType GPIO_InitStruct;
  
  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  for (i=0; i<Buffer_Size; i++)
    Transmit_Buffer[i] = i;
  
  /* IOB6 as slave select pin, CMOS output mode, output high */
  GPIO_WriteBit(GPIO_B, 6, 1);
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUTPUT_CMOS;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIOBToF_Init(GPIOB, &GPIO_InitStruct);
  
  /* SPI1 initialization, master mode, CS soft control(not use defalut CS pin ) */
  SPI_DeviceInit(SPI1);
  SPI_InitStruct.ClockDivision = SPI_CLKDIV_32;
  SPI_InitStruct.Mode = SPI_MODE_MASTER;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_ENABLE;
  SPI_InitStruct.SPH = SPI_SPH_0;
  SPI_InitStruct.SPO = SPI_SPO_0;
  SPI_InitStruct.SWAP = SPI_SWAP_DISABLE;
  SPI_Init(SPI1, &SPI_InitStruct);  
  
  /* Generate TX interrupt when data no. in TXFIFO < 1 */
  SPI_TransmitFIFOLevelConfig(SPI1, SPI_TXFLEV_0);
  /* Generate RX interrupt when data no. in RXFLFO > 0 */
  SPI_ReceiveFIFOLevelConfig(SPI1, SPI_RXFLEV_0);
  
  Transmit_Cnt = 0;
  Receive_Cnt = 0;
  
  /* Reset SS, slave be selected, active */
  GPIO_WriteBit(GPIO_B, 6, 0);
  
  /*Enable SPI1*/
  SPI_Cmd(SPI1, ENABLE);
  
  /* Enable SPI1 transmit interrupt, enter SPI1 Interrupt Service Routine */
  SPI_INTConfig(SPI1, SPI_INT_TX, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(SPI1_IRQn, 0);
  
  test_success = 1;
  
  /* Waiting receive operation done */
  while (Receive_Cnt < Buffer_Size)
  {
    if(SPI_GetStatus(SPI1, SPI_STS_RNE))
      Receive_Buffer[Receive_Cnt++] = SPI_ReceiveData(SPI1);
  }
  
  /* Set SS, slave be not selected, inactive */
  GPIO_WriteBit(GPIO_B, 6, 1);
  
  /* SPI resource release */
  SPI_DeviceInit(SPI1);
  CORTEX_NVIC_DisableIRQ(SPI1_IRQn);
  printf("SPI1 send finish!\r\n");
  
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
