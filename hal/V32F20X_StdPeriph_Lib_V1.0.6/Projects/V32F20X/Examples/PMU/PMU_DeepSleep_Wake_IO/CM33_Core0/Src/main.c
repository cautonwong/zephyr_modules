/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-05
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Wakeup_Src = 0;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void GPIO_Configuration(void);

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
  
  /* Configure the System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();

  Wakeup_Src = PMU_GetDSleepWKUSource(SLEEP_CORE_CM33);
  if (PMU_DSLPWKU_IO == Wakeup_Src)
  {
    printf("IO Deep Sleep Wakeup Wakeup_Src =0x%x.\r\n", Wakeup_Src);
  }

  STD_Delay(5000);
  
  GPIO_Configuration();
  
  GPIO_WKU_DeInit();
  
  printf("IO WKU INT Config:");
  printf("GPIOC_Pin_12\r\n");

  GPIO_WKU_Config(GPIOC, GPIO_Pin_12, GPIO_EVENT_HIGH_LEVEL);

  PMU_WKUGPIOConfig(SLEEP_CORE_CM33, GPIO_Pin_12, ENABLE);
  PMU_WKUGPIOConfig(SLEEP_CORE_CM0, GPIO_Pin_12, ENABLE);
  PMU_WKUSRCConfig(SLEEP_CORE_CM33, PMU_WKUSRC_IO, ENABLE);
  PMU_WKUSRCConfig(SLEEP_CORE_CM0, PMU_WKUSRC_IO, ENABLE);

  printf("Enter DeepSleep mode.\r\n");
  STD_DeInitTick();
  
  /*Close all unused periphral*/
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_ENCENG, DISABLE);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_WDT1\
    |SYSCFG0_Periph1Clock_WDT0\
    |SYSCFG0_Periph1Clock_SCR\
    |SYSCFG0_Periph1Clock_FC7, DISABLE);
  SYSCFG1_Periph0ClockCmd(SYSCFG1_Periph0Clock_CRYPTO, DISABLE);
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_WDT2, DISABLE);
  
  /*Switch APBLP PMU clock to RCL*/
  SYSCFGLP_APBLPClockConfig(SYSCFGLP_APBLP_CLKSRC_RCL, 1);
  SYSCFGLP_PMUClockConfig(SYSCFGLP_PMU_CLKSRC_RCL, 1);
  
  /*Power down BGP1, RCH1, PLLL and PLLH automatically*/
  PMU_CLKAUTO_Config(SLEEP_CORE_CM33, ENABLE);
  PMU_CLKAUTO_Config(SLEEP_CORE_CM0, ENABLE);
  
  PMU_EnterDSleepMode(SLEEP_CORE_CM0);
  PMU_EnterDSleepMode(SLEEP_CORE_CM33);
  printf("failed.\r\n");

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
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStruct;

  /* Configure PC13 as  input */
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_12 ;
  GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType  = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
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
