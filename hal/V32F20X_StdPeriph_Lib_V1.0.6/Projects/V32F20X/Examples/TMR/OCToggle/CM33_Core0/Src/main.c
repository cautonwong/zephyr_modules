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
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

TMR_TimeBaseInitType TMR_TimeBaseStructure = {0};
TMR_OCInitType  TMR_OCInitStructure = {0};
__IO uint16_t CCR1_Val = 32768;
__IO uint16_t CCR2_Val = 16384;
__IO uint16_t CCR3_Val = 8192;
__IO uint16_t CCR4_Val = 4096;

uint32_t SystemCoreClock = 48000000;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* System Clocks Configuration */
  RCC_Configuration();

  BSP_Printf_Init();
  
  /* NVIC Configuration */
  NVIC_Configuration();
  
  /* GPIO Configuration */
  GPIO_Configuration();
  
  /* ---------------------------------------------------------------------------
    GTMR0 Configuration: Output Compare Toggle Mode:
    TMR3CLK = SystemCoreClock,
    The objective is to get GTMR0 counter clock at 12 MHz:
    CC1 update rate = GTMR0 counter clock / CCR1_Val / 2 = 183.1 Hz
    CC2 update rate = GTMR0 counter clock / CCR2_Val / 2 = 366.2 Hz
    CC3 update rate = GTMR0 counter clock / CCR3_Val / 2 = 732.4 Hz
    CC4 update rate = GTMR0 counter clock / CCR4_Val / 2 = 1464.8 Hz
  ----------------------------------------------------------------------------*/


  TMR_DeInit(GTMR0);

  /* Time Base configuration */
  TMR_TimeBaseStructure.TMR_Prescaler = 3;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_Period = 65535;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseInit(GTMR0, &TMR_TimeBaseStructure);

  /* Output Compare Toggle Mode configuration: Channel1 */
  TMR_OCStructInit(&TMR_OCInitStructure);
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_Toggle;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OCInitStructure.TMR_Pulse = CCR1_Val;
  TMR_OCInitStructure.TMR_OCPolarity = TMR_OCPolarity_Low;
  TMR_OC1Init(GTMR0, &TMR_OCInitStructure);

  TMR_OC1PreloadConfig(GTMR0, TMR_OCPreload_Disable);
  
  /* Output Compare Toggle Mode configuration: Channel2 */
  TMR_OCInitStructure.TMR_Pulse = CCR2_Val;
  TMR_OC2Init(GTMR0, &TMR_OCInitStructure);
  
  TMR_OC2PreloadConfig(GTMR0, TMR_OCPreload_Disable);
  
  /* Output Compare Toggle Mode configuration: Channel3 */
  TMR_OCInitStructure.TMR_Pulse = CCR3_Val;
  TMR_OC3Init(GTMR0, &TMR_OCInitStructure);
  
  TMR_OC3PreloadConfig(GTMR0, TMR_OCPreload_Disable);
  
  /* Output Compare Toggle Mode configuration: Channel4 */
  TMR_OCInitStructure.TMR_Pulse = CCR4_Val;
  TMR_OC4Init(GTMR0, &TMR_OCInitStructure);

  TMR_OC4PreloadConfig(GTMR0, TMR_OCPreload_Disable);

  TMR_ARRPreloadConfig(GTMR0, ENABLE);
  
  /* TMR INT enable */
  TMR_ITConfig(GTMR0, TMR_IT_CC1 | TMR_IT_CC2 | TMR_IT_CC3 | TMR_IT_CC4, ENABLE);

  /* GTMR0 counter enable */
  TMR_Cmd(GTMR0, ENABLE);
  
  printf("GTMR0 counter enable.\r\n");
  while (1)
  {
  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemClock_Config();
  
  /* GTMR0 clocks enable */
  SYSCFG0_TMRClockCmd(SYSCFG0_TMRCLK_GTMR0, ENABLE);
}

/**
  * @brief  Configure the GTMR0 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};

  /* GPIOA Configuration: GTMR0 Channel 1 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIOB Configuration: Channel 2, 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF1_GTMR0_IO2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF1_GTMR0_IO3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF1_GTMR0_IO4);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF1_GTMR0_IO1_ETR);
  
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_EnableIRQ(GTMR0_IRQn);
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
