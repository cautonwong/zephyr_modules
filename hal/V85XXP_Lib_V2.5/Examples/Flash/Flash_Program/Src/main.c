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
  uint32_t i;
  uint32_t CheckSum;
  uint32_t w_buffer[256];
  uint16_t hw_buffer[512];
  uint8_t b_buffer[1024];
  
  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  
  for (i=0; i<1024; i++)
  {
    b_buffer[i] = i % 256;
    if ((i%2) == 0)
      hw_buffer[i/2] = 0x1234 + i;
    if ((i%4) == 0)
      w_buffer[i/4] = 0x12345678 + i;
  }
  
  FLASH_Init(FLASH_CSMODE_DISABLE);
  FLASH_CycleInit();
    
  FLASH_SectorErase(0x10000);                    //erase 0x10000~0x103FC
  FLASH_ProgramByte(0x10000, b_buffer, 1024);     //Byte program
  for (i = 0; i < 1024; i++)
  {
    printf("%2x\t", *((__IO uint8_t *)(i + 0x10000)));
    if ((i%10) == 9)
      printf("\r\n");
  }
  printf("\r\n");
  
  FLASH_SectorErase(0x10000);                    //erase 0x10000~0x103FC
  FLASH_ProgramHWord(0x10000, hw_buffer, 512);   //Half-word program
  for (i = 0; i < 1024; i += 2)
  {
    printf("%4x\t", *((__IO uint16_t *)(i + 0x10000)));
    if ((i%10) == 9)
      printf("\r\n");
  }
  printf("\r\n");

  FLASH_SectorErase(0x10000);                     //erase 0x10000~0x103FC
  for (i = 0; i < 1024; i++)
  {
    printf("%2x\t", *((__IO uint8_t *)(i + 0x10000)));
    if ((i%10) == 9)
      printf("\r\n");
  }
  printf("\r\n");
    
  FLASH_ProgramWord(0x10000, w_buffer, 256);     //Word program
  for (i = 0; i < 1024; i += 4)
  {
#ifdef __GNUC__
    printf("%8lx\t", *((__IO uint32_t *)(i + 0x10000)));
#else
    printf("%8x\t", *((__IO uint32_t *)(i + 0x10000)));
#endif
    if ((i%20) == 16)
      printf("\r\n");
  }
  printf("\r\n");
  
  CheckSum = 0;                                  //CheckSum 0x10000~0x103FC
  for (i = 0; i < 256; i++)
  {
    CheckSum += w_buffer[i];
  }

  /* Enable flash(NVIC) interrupt */
  FLASH_INTConfig(FLASH_INT_CS, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(FLASH_IRQn, 0);
  
  FLASH_SetCheckSumCompValue(CheckSum);
  FLASH_SetCheckSumRange(0x10000, 0x103FC);
  FLASH_Init(FLASH_CSMODE_ALWAYSON); 
  
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
