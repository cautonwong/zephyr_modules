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
TMR_ICInitType  TMR_ICInitStructure = {0};
TMR_OCInitType  TMR_OCInitStructure = {0};

uint32_t SystemCoreClock = 48000000;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);

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
  
  /* GPIO Configuration */
  GPIO_Configuration();
  
  /* Use ETMR1 generate clock to drive GTMR1--------------------
  ETMR1 PWM frequency = 1 kHz
  GTMR1 PWM frequency = 20.8 Hz
  ------------------------------------------------------------ */

  TMR_DeInit(ETMR1);
  TMR_DeInit(GTMR1);
  
  /* Time Base configuration */
  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure);
  TMR_TimeBaseStructure.TMR_Period = 47;
  TMR_TimeBaseStructure.TMR_Prescaler = 999;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseInit(ETMR1, &TMR_TimeBaseStructure);

  TMR_TimeBaseStructure.TMR_Prescaler = 0;
  TMR_TimeBaseInit(GTMR1, &TMR_TimeBaseStructure);

  /* ETMR1 and GTMR1 output mode configuration */
  TMR_OCStructInit(&TMR_OCInitStructure);
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM1;
  TMR_OCInitStructure.TMR_Pulse = 23;
  TMR_OCInitStructure.TMR_OCPolarity = TMR_OCPolarity_High;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OC1Init(ETMR1, &TMR_OCInitStructure);

  TMR_OC3Init(GTMR1, &TMR_OCInitStructure);

  /* configure GTMR1 channel2 to get clock signal */
  TMR_ICStructInit(&TMR_ICInitStructure);
  TMR_ICInitStructure.TMR_Channel = TMR_Channel_2;
  TMR_ICInitStructure.TMR_ICPolarity = TMR_ICPolarity_Rising;
  TMR_ICInitStructure.TMR_ICSelection = TMR_ICSelection_DirectTI;
  TMR_ICInitStructure.TMR_ICPrescaler = TMR_ICPSC_DIV1;
  TMR_ICInitStructure.TMR_ICFilter = 0x0;

  TMR_ICInit(GTMR1, &TMR_ICInitStructure);
  
  /* Select the GTMR1 Input Trigger: TI2FP2 */
  TMR_SelectInputTrigger(GTMR1, TMR_TS_TI2FP2);

  /* Select the slave Mode: External1 Mode */
  TMR_SelectSlaveMode(GTMR1, TMR_SlaveMode_External1);

  /* ETMR1 enable counter */
  TMR_Cmd(ETMR1, ENABLE);

  /* GTMR1 enable counter */
  TMR_Cmd(GTMR1, ENABLE);
  
  /* ETMR1 Main Output Enable */
  TMR_CtrlPWMOutputs(ETMR1, ENABLE);
  
  printf("ETMR1 Main Output Enable.\r\n");
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
  
  /* ETMR1 clocks enable */
  SYSCFG0_TMRClockCmd(SYSCFG0_TMRCLK_ETMR1, ENABLE);
  
  /* GTMR1 clocks enable */
  SYSCFG0_TMRClockCmd(SYSCFG0_TMRCLK_GTMR1, ENABLE);
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};

  /* GPIOC Configuration: Pin6, 7, 8 and 9 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF3_ETMR1_IO1);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF2_GTMR1_IO2);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF2_GTMR1_IO3);
  
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
