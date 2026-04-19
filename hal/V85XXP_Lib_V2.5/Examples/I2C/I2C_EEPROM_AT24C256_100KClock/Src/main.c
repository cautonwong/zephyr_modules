/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>

volatile unsigned char test_success;

/* Private functions ---------------------------------------------------------*/

uint8_t Wr_Buffer[512];
uint8_t Rd_Buffer[512];

/**
  * @brief  Clock_Init:
              - PLLL input clock    : External 32K crystal
              - PLLL frequency      : 26M
              - AHB Clock source    : PLLL
              - AHB Clock frequency : 26M (PLLL divided by 1)
              - APB Clock frequency : 26M (AHB Clock divided by 1)
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
  CLK_Struct.PCLK.Divider   = 1;
  CLK_ClockConfig(&CLK_Struct);
}


void EE_PowerUp(void)
{
  GPIO_InitType GPIO_InitStruct;

  /* IOE11 output high */
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUTPUT_CMOS;
  GPIOBToF_Init(GPIOE, &GPIO_InitStruct);
  
  GPIO_WriteBit(GPIO_E, 11, 1);
}

/**
  * @brief  Power down EEPROM
  */
void EE_PowerDown(void)
{
  /* IOE11 forbidden */
  GPIO_InitType GPIO_InitStruct;
  
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIOBToF_Init(GPIOE, &GPIO_InitStruct);  
}

int main(void)
{
  I2C_InitType I2C_InitStruct;
  I2C_WRType I2C_WRInitStruct;
  uint16_t retval;
  int i;
  uint8_t State_OK = 1;

  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  for (i=0; i<512; i++)
  {
    Wr_Buffer[i] = rand() % 256;
    Rd_Buffer[i] = 0;
  }
  EE_PowerUp();
    
  /* I2C initialization */
  I2C_DeInit(I2C_REMAP_DISABLE);
  I2C_StructInit(&I2C_InitStruct);
  I2C_Init(&I2C_InitStruct);
  
  /* Enable I2C */
  I2C_Cmd(ENABLE);  
  
  test_success = 1;
  
  /* Write the entire EEPROM with random numbers */
  I2C_WRInitStruct.SubAddrType = I2C_SUBADDR_2BYTE;
  I2C_WRInitStruct.SlaveAddr = 0xA0;
  I2C_WRInitStruct.PageRange = 64;
  I2C_WRInitStruct.Length = 512;
  I2C_WRInitStruct.pBuffer = Wr_Buffer;
  I2C_WRInitStruct.SubAddress = 0;
  retval = I2C_MasterWriteBytes(&I2C_WRInitStruct);
  if (retval)
  {  
    printf("I2C write error!\r\n");
    State_OK = 0;
  }
  
  /* Read datas from EEPROM */
  I2C_WRInitStruct.pBuffer = Rd_Buffer;
  retval = I2C_MasterReadBytes(&I2C_WRInitStruct);
  if (retval)
  {    
    printf("I2C read error!\r\n");
    State_OK = 0;
  }
  
  EE_PowerDown();
  I2C_DeInit(I2C_REMAP_DISABLE);
  
  /* Compare datas */
  for (i=0; i<512; i++)
  {
    if (Rd_Buffer[i] != Wr_Buffer[i])
    {      
      State_OK = 0;
      break;
    }
  }
  
  if (State_OK)
    printf("Write/read EEPROM OK!\r\n");
  else
    printf("Write/read EEPROM error!\r\n"); 
  
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
