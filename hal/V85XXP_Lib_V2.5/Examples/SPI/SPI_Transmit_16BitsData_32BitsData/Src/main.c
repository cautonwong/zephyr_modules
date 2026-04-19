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

#define CSN_GPIO     GPIOB
#define CSN_GPIO_DAT GPIO_B
#define CSN_Pin      GPIO_Pin_9
#define CSN_PinNum   9

uint32_t Transmit_Buffer_32b[4] = { 0x11111111, 0x22222222, 0x33333333, 0x44444444 };
uint32_t Transmit_Buffer_16b[4] = { 0x1111, 0x2222, 0x3333, 0x4444 };

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
  * @brief  Configure SPI CSN pin level.
  * @param  None
  * @retval None
  */
void SPI_CSNConfig(uint8_t level)
{
  if (level)    GPIO_WriteBit(CSN_GPIO_DAT, CSN_PinNum, 1);
  else          GPIO_WriteBit(CSN_GPIO_DAT, CSN_PinNum, 0);
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
  uint8_t i;

  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  /* CSN pin output high, inactive */
  GPIO_WriteBit(CSN_GPIO_DAT, CSN_PinNum, 1);
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUTPUT_CMOS;
  GPIO_InitStruct.GPIO_Pin = CSN_Pin;
  GPIOBToF_Init(CSN_GPIO, &GPIO_InitStruct);
  
  /* SPI1 initialization, master mode */
  SPI_DeviceInit(SPI1);
  SPI_InitStruct.ClockDivision = SPI_CLKDIV_32;
  SPI_InitStruct.Mode = SPI_MODE_MASTER;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_ENABLE;
  SPI_InitStruct.SPH = SPI_SPH_0;
  SPI_InitStruct.SPO = SPI_SPO_0;
  SPI_InitStruct.SWAP = SPI_SWAP_DISABLE;
  SPI_Init(SPI1, &SPI_InitStruct);
  
  /*Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);
  
  /* Send 4 32-Bits datas */
  for (i=0; i<4; i++)
  {
    /* CSN active */
    SPI_CSNConfig(0);
    /* Loop while until TXFIFO is empty */
    while (SPI_GetStatus(SPI1, SPI_STS_TFE) == 0);
    SPI_SendData(SPI1, (Transmit_Buffer_32b[i]>>24)&0xff);
    SPI_SendData(SPI1, (Transmit_Buffer_32b[i]>>16)&0xff);
    SPI_SendData(SPI1, (Transmit_Buffer_32b[i]>>8)&0xff);
    SPI_SendData(SPI1, (Transmit_Buffer_32b[i])&0xff); 
    /* While loop until idle */
    while (SPI_GetStatus(SPI1, SPI_STS_BSY) == 1);
    /* CSN inactive */
    SPI_CSNConfig(1);
  }
  printf("SPI1 send 4*32Bits datas finish!\r\n");
  
  /* Send 4 16-Bits datas */
  for (i=0; i<4; i++)
  {
    /* CSN active */
    SPI_CSNConfig(0);
    /* Loop while until TXFIFO is empty */
    while (SPI_GetStatus(SPI1, SPI_STS_TFE) == 0);
    SPI_SendData(SPI1, (Transmit_Buffer_16b[i]>>8)&0xff);
    SPI_SendData(SPI1, (Transmit_Buffer_16b[i])&0xff); 
    /* While loop until idle */
    while (SPI_GetStatus(SPI1, SPI_STS_BSY) == 1);
    /* CSN inactive */
    SPI_CSNConfig(1);
  }
  printf("SPI1 send 4*16Bits datas finish!\r\n");

  /* SPI1 and CSN pin release */
  SPI_DeviceInit(SPI1);
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIO_InitStruct.GPIO_Pin = CSN_Pin;
  GPIOBToF_Init(CSN_GPIO, &GPIO_InitStruct);

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
