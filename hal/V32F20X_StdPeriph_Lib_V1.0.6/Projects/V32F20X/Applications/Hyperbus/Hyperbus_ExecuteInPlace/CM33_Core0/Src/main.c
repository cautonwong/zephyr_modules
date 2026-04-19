/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hyperbus_psram.h"

uint8_t tx_buff[64] = {0};
uint32_t rx_buff[16] = {0};


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0, err = 0; 
  uint32_t DWORD;
  
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
  BSP_Printf_Init();
  
  STD_Delay(5000);
  
  HyperbusPSRAM_InitHyperbus(TEST_OSPI);
  HyperbusPSRAM_HardWareResetPSRAM( );

  for(i = 0; i<64; i++)
  {
    tx_buff[i] = i;
  }
  
  printf("Write 64 Bytes into PSRAM...\r\n");
  if(TEST_OSPI == OSPI0)
  {
    HyperbusPSRAM_WritePSRAM(TEST_OSPI, tx_buff, 0x60000010, 64);
  }
  else
  {
    HyperbusPSRAM_WritePSRAM(TEST_OSPI, tx_buff, 0x64000010, 64);
  }

  printf("Read the written 64 Bytes...\r\n");
  if(TEST_OSPI == OSPI0)
  {
    HyperbusPSRAM_ReadPSRAM(TEST_OSPI,rx_buff, 0x60000010, 64);
  }
  else
  {
    HyperbusPSRAM_ReadPSRAM(TEST_OSPI, rx_buff, 0x64000010, 64);
  }
  printf("Perform data comparison...\r\n");
  
  for(i = 0; i < 64; i = i+4)
  {
    DWORD = ((uint32_t)(tx_buff[i+0] << 0) 
            | (uint32_t)(tx_buff[i+1] << 8)
            | (uint32_t)(tx_buff[i+2] << 16)
            | (uint32_t)(tx_buff[i+3] << 24));

    if(rx_buff[i/4] != DWORD)
    {
      printf("Psram read and write err!, rxbuff[%d] = 0x%08x; txbuff[%d] = 0x%08x\r\n",\
      i/4, rx_buff[i/4], i/4, DWORD);
      err++;
    }
  }
  if(err == 0)
  {
    printf("passed\r\n");
  }
  else
  {
    printf("failed\r\n");
  }  
  
  while(1)
  {

  }
}


/**
  * @brief  AHB and APB Clock Configuration
  *         The Bus Clock is configured as follows :
  *            HCLK0    = PLL0 180 MHz
  *            PCLK0    = PLL0 180 MHz
  *            HCLK1     = PLL0 64 MHz
  *            PCLK1     = PLL0 64 MHz
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  
  /* Select RCH as AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0 | CLK_BUSCLOCK1;
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
  
  /* PLL enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_XOH | CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOHState = CLK_XOH_ON;
  CLK_OscInitStruct.XOLState = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_XOH;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = pll0_config[CLK_PLL0_IN_12M_OUT_180M].CLKN0;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = pll0_config[CLK_PLL0_IN_12M_OUT_180M].CLKN1;
  CLK_OscInitStruct.PLL0.PLL0_M      = pll0_config[CLK_PLL0_IN_12M_OUT_180M].CLKM;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_ON;
  CLK_OscInitStruct.PLL1.PLL1_Source = CLK_PLL1SOURCE_XOH_12M;
  CLK_OscInitStruct.PLL1.PLL1_Frequency = CLK_PLL1_IN_12M_OUT_144M;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL0 as  AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 1U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 1U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  CLK_InitStruct.BusClock = CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 2U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 2U;
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
