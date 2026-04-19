/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/*- Core1 boot address -*/
#define CORE1_BOOT_ADDR               (0x00100000)
/*- SRAM shared -*/
#define SRAM_SHARED                   (*(__IO uint32_t *)(0x20010000))
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void StartCore1(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
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
  
  /* UART configuration */
  BSP_Printf_Init();
  
  /* Mailbox mutex init to 1 */
  MB33_MutexInit();
  SRAM_SHARED = 0;
  
  /* Start core1 */
  StartCore1();

  printf("Start core1\r\n");

  while(1)
  {
    while (MB33_GetMutex() == 0UL)
    {
    }
    
    SRAM_SHARED++;
    
    printf("CORE1: update shared variable to %d\r\n", SRAM_SHARED);
    
    /* Set mutex to allow access other core to shared variable */
    MB33_SetMutex();
    
    /* Add several nop instructions to allow the opposite core to get the mutex */
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
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

/**
  * @brief  Start CM33 core1.
  * @retval None
  */
static void StartCore1(void)
{
  /* Enable CM33 core1 clock */
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_CORE1, ENABLE);
  
  /* Configure CM33 core1 boot address */
  SYSCFG0_Core1BootAddrConfig(CORE1_BOOT_ADDR);
  
  /* Halt CM33 core1 */
  SYSCFG0_Core1WaitCmd(ENABLE);
  SYSCFG0_Core1ResetCmd(ENABLE);
  
  /* Release CM33 core1 */
  SYSCFG0_Core1WaitCmd(DISABLE);
  SYSCFG0_Core1ResetCmd(DISABLE);
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
