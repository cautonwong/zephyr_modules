/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private functions ---------------------------------------------------------*/
void UART5_ProtocolInit(void);

volatile unsigned char test_success;

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
  test_success = 0;
                
  Clock_Init();

  FLASH_Init(FLASH_CSMODE_DISABLE);
  FLASH_CycleInit();

  UART5_ProtocolInit();

  test_success = 1;

  printf("This is a Flash protection template\r\n");
  printf("===========================================\r\n");
  printf("1. Enable write protection.\r\n");
  printf("2. Disable write protection.\r\n");
  printf("3. Enable ICE protection.\r\n");
  printf("4. Disable ICE protection.\r\n");
  printf("5. Enable read protection.\r\n");
  printf("6. Disable read protection.\r\n");
  printf("===========================================\r\n");
  printf("Please input 1 ~ 6\r\n");
  printf("\r\n");

  while (1)
  {
    WDT_Clear();
  }
}

void UART5_ProtocolInit(void)
{
  UART_InitType UART_InitStruct;

  UART_DeInit(UART5);
  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.Mode = UART_MODE_TX | UART_MODE_RX;
  UART_InitStruct.Baudrate = 115200;
  UART_InitStruct.FirstBit = UART_FIRSTBIT_LSB;
  UART_InitStruct.Parity = UART_PARITY_NONE;
  UART_Init(UART5, &UART_InitStruct);

  UART_INTConfig(UART5, UART_INT_RX, ENABLE);
  UART_ClearINTStatus(UART5, UART_INTSTS_RX);
  CORTEX_SetPriority_ClearPending_EnableIRQ(UART5_IRQn, 0);
}

static void Flash_EnableWriteProtectionTest(void)
{
  uint8_t i;
  uint8_t wdata[16], rdata[16];

  for (i=0; i<16; i++)
  {
    wdata[i] = 17*i;
    rdata[i] = 0;
  }

  /* Disable Block-12(0x30000~0x33FFF)  */
  FLASH_WriteProtection(FLASH_BLOCK_12, DISABLE);
  FLASH_SectorErase(0x30000);
  FLASH_ProgramByte(0x30000, wdata, 16);
  for (i=0; i<16; i++)
    rdata[i] = *(__IO uint8_t *)(0x30000+i);
  
  printf("Block-12(0x30000~0x33FFF) Write Protection disabled\r\n");
  printf("0x30000 ~ 0x3000F write:\r\n");
  for (i=0; i<16; i++)
     printf("0x%x\t", wdata[i]);
  printf("\r\n");
  printf("0x30000 ~ 0x3000F read:\r\n");
  for (i=0; i<16; i++)
     printf("0x%x\t", rdata[i]);
  printf("\r\n");

  /* Enable Block-12(0x30000~0x33FFF)  */
  FLASH_WriteProtection(FLASH_BLOCK_12, ENABLE);
  FLASH_SectorErase(0x30000);
  for (i=0; i<16; i++)
    rdata[i] = *(__IO uint8_t *)(0x30000+i);
    
  printf("Block-12(0x30000~0x33FFF) Write Protection enabled\r\n");
  printf("Sector Erase(0x30000~0x303FF) fail\r\n");
  printf("0x30000 ~ 0x3000F read:\r\n");
  for (i=0; i<16; i++)
     printf("0x%x\t", rdata[i]);
  printf("\r\n");
  printf("\r\n");
}

static void Flash_DisableWriteProtectionTest(void)
{
  uint8_t i;
  uint8_t rdata[16];

  for (i=0; i<16; i++)
  {
    rdata[i] = 0;
  }

  /* Disable Block-12(0x30000~0x33FFF)  */
  FLASH_WriteProtection(FLASH_BLOCK_12, DISABLE);
  FLASH_SectorErase(0x30000);
  for (i=0; i<16; i++)
    rdata[i] = *(__IO uint8_t *)(0x30000+i);
  
  printf("Block-12(0x30000~0x33FFF) Write Protection disabled\r\n");
  printf("Sector Erase(0x30000~0x303FF) OK\r\n");
  printf("0x30000 ~ 0x3000F read:\r\n");
  for (i=0; i<16; i++)
     printf("0x%x\t", rdata[i]);
  printf("\r\n");
  printf("\r\n");    
}

static void Flash_EnableICEProtectionTest(void)
{
  FLASH_ICEProtection(ENABLE);
  printf("ICE Protection enabled, can not connect target with SWD\r\n");
  printf("\r\n");
}

static void Flash_DisableICEProtectionTest(void)
{
  printf("The last sector be erased\r\n");
  printf("ICE Protection disabled, reset target, can connect target with SWD\r\n");
  printf("\r\n");

  FLASH_ICEProtection(DISABLE);
}

static void Flash_EnableReadProtectionTest(void)
{
  uint8_t i;
  uint8_t rdata[16];

  FLASH_SetReadProtection(FLASH_BLOCK_12);
  FLASH_SectorErase(0x30000);
  for (i=0; i<16; i++)
    rdata[i] = *(__IO uint8_t *)(0x30000+i);

  printf("Block-12(0x30000~0x33FFF) Read Protection enabled\r\n");
  printf("Sector Erase(0x30000~0x303FF) OK\r\n");
  printf("0x30000 ~ 0x3000F read:\r\n");
  for (i=0; i<16; i++)
     printf("0x%x\t", rdata[i]);
  printf("\r\n");
  printf("\r\n");  
}

static void Flash_DisableReadProtectionTest(void)
{
  printf("Read Protection disabled, Chip erase\r\n");
  FLASH_ChipErase();
}

void UART5_InterruptService(void)
{
  uint8_t data = 0U;
  
  /* Error handle */
  if ((UART_GetINTStatus(UART5, UART_INTSTS_RXPE)) ||\
      (UART_GetINTStatus(UART5, UART_INTSTS_RXOV)))
  {
    UART_ClearINTStatus(UART5, UART_INTSTS_RXPE);
    UART_ClearINTStatus(UART5, UART_INTSTS_RXOV);
    printf("Recieved data error, data invalid, input again\r\n");
  }
  /* Get data */
  else
  {
    if (UART_GetINTStatus(UART5, UART_INTSTS_RX))
    {
      UART_ClearINTStatus(UART5, UART_INTSTS_RX);
      data = UART_ReceiveData(UART5);
    }
  }

  switch (data) 
  {
    case 1:
      printf("[1] Enable write protection.\r\n");
      Flash_EnableWriteProtectionTest();
      break;
    case 2:
      printf("[2] Disable write protection.\r\n");
      Flash_DisableWriteProtectionTest();
      break;
    case 3:
      printf("[3] Enable ICE protection.\r\n");
      Flash_EnableICEProtectionTest();
      break;
    case 4:
      printf("[4] Disable ICE protection.\r\n");
      Flash_DisableICEProtectionTest();
      break;
    case 5:
      printf("[5] Enable read protection.\r\n");
      Flash_EnableReadProtectionTest();
      break;
    case 6:
      printf("[6] Disable read protection.\r\n");
      Flash_DisableReadProtectionTest();
      break;
    default:
      printf("Recieved data invalid, input again\r\n");
      break;
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
