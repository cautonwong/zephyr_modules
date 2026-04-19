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
#define VTOR_TABLE_NS_START_ADDR  0x00080000UL
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void NonSecure_Init(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* SAU/IDAU/SCR, FPU and Interrupts secure/non-secure allocation settings */
  /* already done in SystemInit() thanks to partition_XXX.h file */

  /* V32F20xxx CM33 core0 **SECURE** library initialization:
       - Secure Systick timer is configured by default as source of time base, but user
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
  
  /*release CM33 core1*/
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_CORE1, ENABLE);
  SYSCFG0_Core1BootAddrConfig(0x00100000UL);
  SYSCFG0_Core1WaitCmd(DISABLE);
  SYSCFG0_Core1ResetCmd(DISABLE);
  
  /*release CM0*/
  SYSCFG1_Periph0ClockCmd(SYSCFG1_Periph0Clock_CM0, ENABLE);
  SYSCFG1_SetVectorTable(0UL);
  SYSCFGLP_CM0ResetCmd(DISABLE);
  
  /* Non-secure initialization and switch to non-secure state */
  NonSecure_Init();
  
  while(1)
  {

  }
}

/**
  * @brief  AHB and APB Clock Configuration
  *         The Bus Clock is configured as follows :
  *            HCLK0    = RCH
  *            PCLK0    = RCH
  *            HCLK1     = RCH
  *            PCLK1     = RCH
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  CLK_InitType CLK_InitStruct = {0};

  CLK_InitStruct.BusClock = CLK_BUSCLOCK0|CLK_BUSCLOCK1;
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

/**
  * @brief  Non-secure call function
  *         This function is responsible for Non-secure initialization and switch
  *         to non-secure state
  * @retval None
  */
static void NonSecure_Init(void)
{
  funcptr_NS NonSecure_ResetHandler;

  SCB_NS->VTOR = VTOR_TABLE_NS_START_ADDR;

  /* Set non-secure main stack (MSP_NS) */
  __TZ_set_MSP_NS((*(uint32_t *)VTOR_TABLE_NS_START_ADDR));

  /* Get non-secure reset handler */
  NonSecure_ResetHandler = (funcptr_NS)(*((uint32_t *)((VTOR_TABLE_NS_START_ADDR) + 4U)));

  /* Start non-secure state software application */
  NonSecure_ResetHandler();
}

/**
  * @brief  Secure get system clock value.
  * @param  None
  * @retval System clock value
  */
CMSE_NS_ENTRY uint32_t SECURE_GetSysClockFreq(void)
{
  return CLK_GetHCLK0Freq();
}

/*********************************** END OF FILE ******************************/
