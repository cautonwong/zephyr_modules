/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main.h"
#include "QSPI_Flash.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t tx_buff[256] __attribute__((aligned (4))) = {0};
uint8_t rx_buff[256] __attribute__((aligned (4))) = {0};
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0, err = 0; 

  uint32_t FlashId;
  
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
  
  /* Configure DMA0 clock */
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
  
  BSP_Printf_Init();

  printf("QSPI_NOR_ReadWrite_DMA test begins!\r\n");

  QSPI_Flash_Init(FLASH_OSPIX);
  printf("QSPI flash init success\r\n");
  
  QSPI_Flash_SoftwareReset(FLASH_OSPIX);
  QSPI_Flash_QPIModeEnter(FLASH_OSPIX);
  
  FlashId = QSPI_Flash_QPIMode_IDRead(FLASH_OSPIX);
  
  if(FlashId != W25Q256FV_FLASHID && FlashId != W25Q256FQ_FLASHID)
  {
    printf("unexpected FLASH\r\n");
    while(1);
  }

  memset(rx_buff, 0, sizeof(rx_buff));
  for( i =0; i<256; i++)
  {
    tx_buff[i] = i;
  }
  
  /* Ensure that the written pages is in the erased sector.
   * In addition, the size of tx_buff and rx_buff is multiple of 4 bytes
   */
  QSPI_Flash_QPIMode_SectorErase(FLASH_OSPIX, FLASH_ERASE_ADDR);
  if(256 == QSPI_Flash_QPIMode_BufferWriteWithDMA(FLASH_OSPIX, FLASH_WRITE_START_ADDR - FLASH_BASE_ADDR, tx_buff, 256))
  {
    if(256 == QSPI_Flash_QPIMode_BufferReadWithDMA(FLASH_OSPIX, FLASH_WRITE_START_ADDR - FLASH_BASE_ADDR, rx_buff, 256))
    {
      for(i = 0; i < 256; i++)    
      {
        if(tx_buff[i] != rx_buff[i])
        {
          printf("read[%d] = 0x%x, write[%d] = 0x%x, read and write fail\r\n", i, rx_buff[i], i, tx_buff[i]);
          err = 1;
        }
      }
    }
    else
    {
      printf("read error\r\n");
      err = 1;
    }
  }
  else
  {
    printf("write error\r\n");
    err = 1;
  }
  
  if(err == 0)
  {
    printf("QSPI_NOR_ReadWrite_DMA test passes!\r\n");
  }
  else
  {
    printf("QSPI_NOR_ReadWrite_DMA test fails!\r\n");
  }

  QSPI_Flash_QPIModeExit(FLASH_OSPIX);
  QSPI_Flash_DeInit(FLASH_OSPIX);
  while(1)
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
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  
  /* RCH(48M) enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_RCH;
  CLK_OscInitStruct.RCHState = CLK_RCH_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_NONE;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_NONE;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
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
