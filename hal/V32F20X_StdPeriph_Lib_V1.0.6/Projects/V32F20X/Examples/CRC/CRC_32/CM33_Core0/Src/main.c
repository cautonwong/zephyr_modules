/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

const uint8_t buff[256] = {
  0x1c, 0x18, 0x00, 0x00, 0x3f, 0x0b, 0xee, 0x69, 0xef, 0x13, 
  0x82, 0x53, 0x16, 0x8e, 0x32, 0x6b, 0x7a, 0x4b, 0xd5, 0x06, 
  0x45, 0x8e, 0x0f, 0x61, 0x7d, 0xb1, 0x56, 0x1f, 0x8c, 0xe7, 
  0x8e, 0x66, 0xb8, 0x56, 0xad, 0x57, 0xab, 0x3b, 0x6d, 0x10, 
  0xeb, 0x99, 0xf2, 0x57, 0x62, 0x62, 0xd6, 0x34, 0xd6, 0xd7, 
  0x0d, 0x4b, 0x71, 0x59, 0x0f, 0x13, 0x39, 0x9b, 0x2f, 0x29, 
  0x98, 0xb4, 0x89, 0x32, 0xd4, 0x4c, 0x38, 0x3f, 0x97, 0x8d, 
  0x3c, 0x73, 0x67, 0x63, 0xb6, 0x5d, 0x2e, 0xf4, 0x7e, 0x22, 
  0xb2, 0x13, 0x08, 0x68, 0x1d, 0xde, 0xff, 0x4f, 0x75, 0x80, 
  0x0c, 0x2d, 0x24, 0x97, 0xd7, 0x2d, 0x70, 0x6a, 0xb0, 0x3e, 
  0x03, 0xb1, 0x0e, 0x55, 0x63, 0x60, 0x82, 0x5c, 0x7a, 0x73, 
  0x56, 0x6d, 0x0e, 0x6f, 0x5a, 0x2f, 0x49, 0xcc, 0x0e, 0x4b, 
  0x31, 0x51, 0x01, 0x01, 0x30, 0xbf, 0x15, 0x32, 0x8c, 0x1f, 
  0xa3, 0x02, 0xef, 0x55, 0x3c, 0x66, 0xdf, 0x80, 0xb9, 0x0f, 
  0x46, 0x10, 0x9d, 0x23, 0xea, 0x59, 0xf9, 0x60, 0xf5, 0xd3, 
  0x6f, 0x59, 0x6d, 0xfd, 0xaf, 0x4b, 0xbc, 0x5c, 0x57, 0x29, 
  0x28, 0xdc, 0xdb, 0x2d, 0x5b, 0x2c, 0x84, 0x13, 0xdb, 0xb4, 
  0x2c, 0x7e, 0x92, 0xfa, 0x68, 0x75, 0x46, 0x44, 0xf7, 0x58, 
  0x21, 0xa5, 0x1c, 0x6d, 0x29, 0x75, 0x08, 0x48, 0xc8, 0x9f, 
  0xe5, 0x66, 0x44, 0x10, 0x24, 0x23, 0x47, 0xe4, 0xca, 0x6c, 
  0x57, 0xec, 0xda, 0x39, 0x5e, 0x62, 0x66, 0x59, 0x22, 0x9e, 
  0x44, 0x35, 0xcd, 0xef, 0x94, 0x27, 0x65, 0xa8, 0x08, 0x41, 
  0x54, 0xb8, 0xff, 0x57, 0xe0, 0x2b, 0x03, 0x47, 0xb3, 0x2d, 
  0xdb, 0x23, 0x53, 0x17, 0xb1, 0x57, 0xaa, 0x77, 0x97, 0x09, 
  0x7e, 0xd7, 0x6f, 0x73, 0xf9, 0x63, 0x9e, 0x04, 0x21, 0x87, 
  0x7c, 0x45, 0x60, 0xd6, 0x9a, 0x0c
};

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/**
  * @brief  Calculate CRC32 by software.
  * @param  Data: Input data stream, MSByte in Data[0].
  * @param  DataSize: Size of the input data buffer in bytes.
  * @retval Return final 32-bit checksum
  */
uint32_t CRC32Cal(const uint8_t *Data, uint32_t DataSize)
{
  uint32_t i,j;
  uint32_t crc = 0xFFFFFFFF;
  uint32_t poly = 0x04C11DB7;

  poly = (poly & 0x55555555) << 1 | (poly & 0xAAAAAAAA) >> 1;
  poly = (poly & 0x33333333) << 2 | (poly & 0xCCCCCCCC) >> 2;
  poly = (poly & 0x0F0F0F0F) << 4 | (poly & 0xF0F0F0F0) >> 4;
  poly = (poly & 0x00FF00FF) << 8 | (poly & 0xFF00FF00) >> 8;
  poly = (poly & 0x0000FFFF) << 16 | (poly & 0xFFFF0000) >> 16;

  for (j = 0; j < DataSize; j++)
  {
    crc ^= Data[j];
    for (i = 0; i < 8; i++)
    {
      if (crc & 0x00000001)
      {
        crc = (crc >> 1) ^ poly;
      }
      else
      {
        crc = (crc >> 1);
      }
    }
  }

  crc ^= 0xFFFFFFFF;
  return crc;  
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  CRC_InitType CRC_InitStruct;
  uint32_t result;
  uint32_t expected;
    
  /* V32F20xxx CM33 core0 STD library initialization:
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Set NVIC Group Priority to 3
       - Low Level Initialization
     */
  STD_Init(CLK_GetHCLK0Freq());
  
  /* Configure the CM33/CM0 System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();
  
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_CRC, ENABLE);
  
  CRC_DeInit();
	
  CRC_StructInit(&CRC_InitStruct);
  CRC_Init(&CRC_InitStruct);
  CRC_WriteData(buff, sizeof(buff));
	
  result = CRC_Get32bitResult();
  expected = CRC32Cal(buff, sizeof(buff));
  if (result == expected)
  {
    printf("CRC32 result is expected\r\n");
  }
  else
  {
    printf("CRC32 result is not expected\r\n");
  }
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  AHB and APB Clock Configuration
  *         The Bus Clock is configured as follows :
  *            HCLK0    = RCH 48 MHz
  *            PCLK0    = RCH
  *            HCLK1     = RCH
  *            PCLK1     = RCH
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  CLK_InitType CLK_InitStruct = {0};
    
  /* Select RCH as AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0 |\
                            CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_RCH;
  CLK_InitStruct.AHBCLKDivider = 1U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_RCH;
  CLK_InitStruct.APBCLKDivider = 1U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Update 1ms tick */
  if (STD_InitTick(CLK_GetHCLK0Freq(), TICK_INT_PRIORITY) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**
  * @brief  Initialize the Low level.
  * @retval None
  */
void STD_lowInit(void)
{
  /* nothing to do */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the STD error return state */
  while(1)
  {
  }
}

#ifdef  ASSERT_ENABLED
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
