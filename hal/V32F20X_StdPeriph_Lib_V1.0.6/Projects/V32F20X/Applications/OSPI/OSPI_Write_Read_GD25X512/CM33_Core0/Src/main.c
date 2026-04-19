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
#include "OSPI_Flash.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

uint8_t tx_buff[1024] __attribute__((aligned(4))) = {0};

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0, err = 0;
  uint32_t FlashID;
  uint8_t *FlashData = NULL;
  
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
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
  BSP_Printf_Init();

  printf("OSPI_Write_Read_GD25X512 test begins!\r\n");

  for( i =0; i<1024; i++)
  {
    tx_buff[i] = i&0x7f;
  }

  OSPI_Flash_Init(Flash_OSPIx);
  OSPI_Flash_HardwareReset();
  printf("OSPI soft reset\r\n");
  OSPI_Flash_SoftwareReset(Flash_OSPIx);
  OSPI_Flash_EnterOPIMode(Flash_OSPIx);
  FlashID = OSPI_Flash_OPIModeReadID(Flash_OSPIx);
  if(FlashID != GD25X_FlashID0 && FlashID != GD25X_FlashID1)
  {
    printf("unexpected FLASH ID = %#x, expected FLASH ID: %#x or %#x\r\n", FlashID, GD25X_FlashID0, GD25X_FlashID1);
    return -1;
  }
  OSPI_Flash_OPIModeSectorErase(Flash_OSPIx, 0x0000);
  /* First sector is erased for write operation, and its size is 4KB.
   * Please make sure that the FLASH memory to be written is not out
   * of the erased sector.
   */
  if(sizeof(tx_buff) ==  OSPI_Flash_BufferWrite(Flash_OSPIx,
                                                tx_buff, 
                                                0x400,
                                                sizeof(tx_buff)))
  {
    OSPI_XIP_ReadConfig(Flash_OSPIx);
    FlashData = (uint8_t*)(FlashStartAddr + 0x400);

    for(i = 0;i < sizeof(tx_buff); i++)    
    {
      if(tx_buff[i] != FlashData[i])
      {
        printf("read[%d] = 0x%x, write[%d] = 0x%x, read and write fail\r\n", 
               i, FlashData[i], i, tx_buff[i]);
        err = 1;
      }
    }
  }
  else
  {
    err = 1;
  }

  if(err == 0)
  {
    printf("OSPI_Write_Read_GD25X512 test passed!\r\n");
  }
  else
  {
    printf("OSPI_Write_Read_GD25X512 test failed!\r\n");
  }
  
  OSPI_Flash_DeInit(Flash_OSPIx);

  while(1)
  {
    __NOP();
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
