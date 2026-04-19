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
#define CORE_LR_START_ADDR   0x00040000UL   /* must be same as LR_IROM2 */
#define QSPI_DAT_ER_START_ADDR  0x60000000UL
#define QSPI_DAT_CODE_LEN       0x00001000UL
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

volatile uint32_t  mismatch_cnt = 0;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0, err = 0; 

  uint32_t FlashId;
  uint8_t *Buff = NULL;
  uint32_t Bufflen;
  
  uint8_t *FlashData = NULL;
  uint8_t FlashDataByte = 0;
  
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

  /* Configure DMA0 clock */
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);

  BSP_Printf_Init();

  printf("QSPI_NOR_ExecuteInPlace test begins!\r\n");

  QSPI_Flash_Init(FLASH_OSPIX);
  printf("QSPI flash init success\r\n");
  
  QSPI_Flash_SoftwareReset(FLASH_OSPIX);
  QSPI_Flash_QPIModeEnter(FLASH_OSPIX);
  
  FlashId = QSPI_Flash_QPIMode_IDRead(FLASH_OSPIX);
  
  if(FlashId != W25Q256FV_FLASHID
    && FlashId != W25Q256FQ_FLASHID)
  {
    printf("unexpected FLASH ID = %#x, expected FLASH ID = %#x or %#x\r\n", FlashId, W25Q256FV_FLASHID, W25Q256FQ_FLASHID);
    while(1);
  }

  /* Ensure that the written pages is within the erased sector(sector size is 4KB).
   * In addition, the code size is multiple of 4 bytes
   */
  Buff = (uint8_t *)CORE_LR_START_ADDR;

  Bufflen = QSPI_DAT_CODE_LEN;
  
  QSPI_Flash_QPIMode_SectorErase(FLASH_OSPIX, 0);

  if(Bufflen != QSPI_Flash_QPIMode_BufferWriteWithDMA(FLASH_OSPIX, 0, Buff, Bufflen))
  {
    printf("failed to write data to FLASH with DMA\r\n");
    while(1)
    {
    }
  }

  QSPI_XIP_ReadConfig(FLASH_OSPIX);
  
  FlashData = (uint8_t*)(QSPI_DAT_ER_START_ADDR);

  for(i = 0; i < Bufflen; i++)
  {
    FlashDataByte = FlashData[i];

    if(FlashDataByte != Buff[i])
    {
      printf("flash addr: 0x%08x, written data:%02x, original data:%02x \r\n",
              ((uint32_t)QSPI_DAT_ER_START_ADDR + i), FlashDataByte,  Buff[i]);
      mismatch_cnt++;
    }
  }
  
  if(mismatch_cnt)
  {
    printf("QSPI_NOR_ExecuteInPlace test ends[failed]!\r\n");
  }
  else
  {
    printf("QSPI_NOR_ExecuteInPlace test ends[passed]!\r\n");
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
