/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private functions ---------------------------------------------------------*/
#define SYSTICK_CYCLE_1MS    (48000000/1000 - 1)

extern __IO uint32_t nTick;
void SysTick_IncTick(void)
{
  nTick++;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the STD error return state */
  /* Turn LED3 on */
  BSP_LED_On(LED3);
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
  
  /* Select RCH as AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0 | CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_RCH;
  CLK_InitStruct.AHBCLKDivider = 2U;
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
  
  /* PLL0 PLL1 enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_XOH | CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOHState = CLK_XOH_ON;
  CLK_OscInitStruct.XOLState = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_XOH;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKN0;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKN1;
  CLK_OscInitStruct.PLL0.PLL0_M      = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKM;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_ON;
  CLK_OscInitStruct.PLL1.PLL1_Source = CLK_PLL1SOURCE_XOL_32768;
  CLK_OscInitStruct.PLL1.PLL1_Frequency = CLK_PLL1_IN_32768_OUT_184_32M;
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
  CLK_InitStruct.APBCLKDivider = 2U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  CLK_InitStruct.BusClock = CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 2U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 4U;
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
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure the CM33 System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  SysTick_Config(128000000/1000 - 1);
  
  BSP_Printf_Init();
  STD_Delay(5000);
  printf("Start write disk\r\n");
  SD_WriteDisk();
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

//#define SYSCLK_RCH_48M          48000000UL
#define SYSCLK_SRC_RCHD4_PLL0_144M        144000000UL
//#define SYSCLK_SRC_XOH_PLL0_144M        144000000UL
//#define SYSCLK_SRC_XOL_PLL1_122M        122000000UL

#ifdef SYSCLK_RCH_48M
  uint32_t SystemCoreClock = SYSCLK_RCH_48M;
  static void SetSysClockTo48M_RCH(void);
#elif defined SYSCLK_SRC_RCHD4_PLL0_144M
  uint32_t SystemCoreClock = SYSCLK_SRC_RCHD4_PLL0_144M;
  static void SetSysClockTo144M_PLL0(void);
#elif defined SYSCLK_SRC_XOH_PLL0_144M
  uint32_t SystemCoreClock = SYSCLK_SRC_XOH_PLL0_144M;
  static void SetSysClockTo144M_PLL0_SRCXOH(void);
#elif defined SYSCLK_SRC_XOL_PLL1_122M
  uint32_t SystemCoreClock = SYSCLK_SRC_XOL_PLL1_122M;
  static void SetSysClockTo122M_PLL1_SRCXOL(void);
#endif

static void SetSysClock(void)
{
#ifdef SYSCLK_RCH_48M
  SetSysClockTo48M_RCH();
#elif defined SYSCLK_SRC_RCHD4_PLL0_144M
  SetSysClockTo144M_PLL0();
#elif defined SYSCLK_SRC_XOH_PLL0_144M
  SetSysClockTo144M_PLL0_SRCXOH();
#elif defined SYSCLK_SRC_XOL_PLL1_122M
  SetSysClockTo122M_PLL1_SRCXOL();
#endif
}

static void SetSysClockTo48M_RCH(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  
  #ifndef POWER_METER_MODE
  CLK_OscInitStruct.OscillatorType   = CLK_OSCILLATORTYPE_RCH;
  CLK_OscInitStruct.RCHState         = CLK_RCH_ON;
  CLK_OscInitStruct.PLL1.PLL1_State  = CLK_PLL1_NONE;
  CLK_OscInitStruct.PLL0.PLL0_State  = CLK_PLL0_NONE;
  CLK_OscConfig(&CLK_OscInitStruct);
  #endif
  CLK_InitStruct.AHBCLKSource  = CLK_AHBCLKSOURCE_RCH;
  CLK_InitStruct.AHBCLKDivider = 1;
  CLK_InitStruct.APBCLKSource  = CLK_APBCLKSOURCE_RCH;
  CLK_InitStruct.APBCLKDivider = 1;
  CLK_Config(&CLK_InitStruct);
}

static void SetSysClockTo144M_PLL0(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  #ifndef POWER_METER_MODE
  /* 
     PLL0_OUT = IN * PLL0_1stN * PLL0_2rdN / PLL0_M 
              = 12M * 2 * 24 / 4 = 144M 
  */
  CLK_OscInitStruct.OscillatorType   = CLK_OSCILLATORTYPE_RCH ;
  CLK_OscInitStruct.RCHState         = CLK_RCH_ON;
  CLK_OscInitStruct.PLL1.PLL1_State  = CLK_PLL1_NONE;
  CLK_OscInitStruct.PLL0.PLL0_State  = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_RCH_DIV4;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = CLK_PLL0_1stN_2;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = 24;
  CLK_OscInitStruct.PLL0.PLL0_M      = 4;
  CLK_OscConfig(&CLK_OscInitStruct);
  #endif
  /* HCLK 144M, PCLK 72M */
  CLK_InitStruct.AHBCLKSource  = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 1;
  CLK_InitStruct.APBCLKSource  = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 2;
  CLK_Config(&CLK_InitStruct);
}

static void SetSysClockTo144M_PLL0_SRCXOH(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  GPIO_InitType GPIO_InitStruct;
  
  #ifndef POWER_METER_MODE
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOH, &GPIO_InitStruct);

  /* 
     PLL0_OUT = IN * PLL0_1stN * PLL0_2rdN / PLL0_M 
              = 12M * 2 * 24 / 4 = 144M 
  */
  CLK_OscInitStruct.OscillatorType   = CLK_OSCILLATORTYPE_XOH;
  CLK_OscInitStruct.XOHState         = CLK_XOH_ON;
  CLK_OscInitStruct.PLL1.PLL1_State  = CLK_PLL1_NONE;
  CLK_OscInitStruct.PLL0.PLL0_State  = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_XOH;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = CLK_PLL0_1stN_2;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = 24;
  CLK_OscInitStruct.PLL0.PLL0_M      = 4;
  CLK_OscConfig(&CLK_OscInitStruct);
  #endif

  /* HCLK 144M, PCLK 72M */
  CLK_InitStruct.AHBCLKSource  = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 1;
  CLK_InitStruct.APBCLKSource  = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 2;
  CLK_Config(&CLK_InitStruct);
}

static void SetSysClockTo122M_PLL1_SRCXOL(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  GPIO_InitType GPIO_InitStruct;
  
  #ifndef POWER_METER_MODE
  /* 
     PLL0_OUT = IN * PLL0_1stN * PLL0_2rdN / PLL0_M 
              = 12M * 2 * 24 / 4 = 144M 
  */
  CLK_OscInitStruct.OscillatorType   = CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOLState         = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State  = CLK_PLL0_NONE;
  CLK_OscInitStruct.PLL1.PLL1_State  = CLK_PLL1_ON;
  CLK_OscInitStruct.PLL1.PLL1_Source = CLK_PLL1SOURCE_XOL_32768;
  CLK_OscInitStruct.PLL1.PLL1_Frequency   = CLK_PLL1_IN_32768_OUT_122_88M;

  CLK_OscConfig(&CLK_OscInitStruct);
  #endif

  /* HCLK 144M, PCLK 72M */
  CLK_InitStruct.AHBCLKSource  = CLK_AHBCLKSOURCE_PLL1;
  CLK_InitStruct.AHBCLKDivider = 1;
  CLK_InitStruct.APBCLKSource  = CLK_APBCLKSOURCE_PLL1;
  CLK_InitStruct.APBCLKDivider = 2;
  CLK_Config(&CLK_InitStruct);
}
/*********************************** END OF FILE ******************************/
