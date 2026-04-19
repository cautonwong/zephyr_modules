/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

const uint8_t Input[256] = {
  0x1c, 0x3f, 0xef, 0x16, 0x7a, 0x45, 0x7d, 0x8c, 0xb8, 0xab, 
  0xeb, 0x62, 0xd6, 0x71, 0x39, 0x98, 0xd4, 0x97, 0x67, 0x2e, 
  0xb2, 0x1d, 0x75, 0x24, 0x70, 0x03, 0x63, 0x7a, 0x0e, 0x49, 
  0x31, 0x30, 0x8c, 0xef, 0xdf, 0x46, 0xea, 0xf5, 0x6d, 0xbc, 
  0x28, 0x5b, 0xdb, 0x92, 0x46, 0x21, 0x29, 0xc8, 0x44, 0x47, 
  0x57, 0x5e, 0x22, 0xcd, 0x65, 0x54, 0xe0, 0xb3, 0x53, 0xaa, 
  0x7e, 0xf9, 0x21, 0x60, 0xfc, 0x9f, 0xcf, 0x76, 0x5a, 0xa5, 
  0x5d, 0xec, 0x98, 0x0b, 0xcb, 0xc2, 0xb6, 0xd1, 0x19, 0xf8, 
  0xb4, 0xf7, 0x47, 0x8e, 0x92, 0x7d, 0x55, 0x84, 0x50, 0x63, 
  0x43, 0xda, 0xee, 0xa9, 0x11, 0x90, 0x6c, 0x4f, 0xbf, 0xa6, 
  0xca, 0x55, 0x4d, 0x1c, 0x08, 0xbb, 0xbb, 0xf2, 0x26, 0x81, 
  0x09, 0x28, 0x24, 0xa7, 0x37, 0xbe, 0x02, 0x2d, 0x45, 0xb4, 
  0xc0, 0x13, 0x33, 0x0a, 0x5e, 0x59, 0x01, 0xc0, 0xdc, 0xff, 
  0xaf, 0xd6, 0x3a, 0x05, 0x3d, 0x4c, 0x78, 0x6b, 0xab, 0x22, 
  0x96, 0x31, 0xf9, 0x58, 0x94, 0x57, 0x27, 0xee, 0x72, 0xdd, 
  0x35, 0xe4, 0x30, 0xc3, 0x23, 0x3a, 0xce, 0x09, 0xf1, 0xf0, 
  0x4c, 0xaf, 0x9f, 0x06, 0xaa, 0xb5, 0x2d, 0x7c, 0xe8, 0x1b, 
  0x9b, 0x52, 0x06, 0xe1, 0xe9, 0x88, 0x04, 0x07, 0x17, 0x1e, 
  0xe2, 0x8d, 0x25, 0x14, 0xa0, 0x73, 0x13, 0x6a, 0x3e, 0xb9, 
  0xe1, 0x20, 0xbc, 0x5f, 0x8f, 0x36, 0x1a, 0x65, 0x1d, 0xac, 
  0x58, 0xcb, 0x8b, 0x82, 0x76, 0x91, 0xd9, 0xb8, 0x74, 0xb7, 
  0x07, 0x4e, 0x52, 0x3d, 0x15, 0x44, 0x10, 0x23, 0x03, 0x9a, 
  0xae, 0x69, 0xd1, 0x50, 0x2c, 0x0f, 0x7f, 0x66, 0x8a, 0x15, 
  0x0d, 0xdc, 0xc8, 0x7b, 0x7b, 0xb2, 0xe6, 0x41, 0xc9, 0xe8, 
  0xe4, 0x67, 0xf7, 0x7e, 0xc2, 0xed, 0x05, 0x74, 0x80, 0xd3, 
  0xf3, 0xca, 0x1e, 0x19, 0xc1, 0x80
};

const uint8_t Expcted[32] = {
  0x71, 0x4a, 0x5d, 0x6c, 0x88, 0x3e, 0xd8, 0xe6, 0xa0, 0xe0, 
  0xd4, 0x8b, 0x14, 0x98, 0x9a, 0xf3, 0xb2, 0xc3, 0x00, 0xc0, 
  0x3f, 0xe1, 0x90, 0x2e, 0xbc, 0xfe, 0x34, 0xb9, 0x20, 0xd8, 
  0x58, 0xfe
};

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint8_t Output[32];
  
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
  
  SystemClock_Config();
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();
  
  printf("SM3 test.\r\n");
  
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_ENCENG, ENABLE);
  
  ENCENG_SM3((uint8_t *)Input, sizeof(Input), Output);
  
  if (memcmp(Expcted, Output, 32) == 0)
  {
    printf("SM3 disgest is expected.\r\n");
  }
  else
  {
    printf("SM3 disgest is not expected.\r\n");
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
