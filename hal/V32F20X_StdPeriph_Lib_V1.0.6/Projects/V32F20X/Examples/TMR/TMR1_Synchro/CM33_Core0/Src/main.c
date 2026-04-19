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
TMR_BDTRInitType TMR_BDTRInitStructure  = {0};

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
  
  /* ETMR0 and TMRers(GTMR0 and GTMR1) synchronisation in parallel mode -----------
     1/ETMR0 is configured as Master TMRer:
     - PWM Mode is used
     - The ETMR0 Update event is used as Trigger Output

     2/GTMR0 and GTMR1 are slaves for ETMR0,
     - PWM Mode is used
     - The ITR0(ETMR0) is used as input trigger for both slaves
     - Gated mode is used, so starts and stops of slaves counters
       are controlled by the Master trigger output signal(update event).

    The Master TMRer ETMR0 is running at:
    ETMR0 frequency = ETMR0 counter clock / (TMR1_Period + 1) = 187.5 KHz
    and the duty cycle is equal to: TMR1_CCR1/(TMR1_ARR + 1) = 50%

    The GTMR0 is running at:
    (ETMR0 frequency)/ ((GTMR0 period +1)* (Repetition_Counter+1)) = 12.5 KHz and
    a duty cycle equal to TMR3_CCR1/(TMR3_ARR + 1) = 33.3%

    The GTMR1 is running at:
    (ETMR0 frequency)/ ((GTMR1 period +1)* (Repetition_Counter+1)) = 18.75 KHz and
    a duty cycle equal to TMR4_CCR1/(TMR4_ARR + 1) = 50%
  --------------------------------------------------------------------------- */
  
  TMR_DeInit(GTMR0);
  
  /* Time Base configuration */
  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure);
  TMR_TimeBaseStructure.TMR_Period = 2;
  TMR_TimeBaseStructure.TMR_Prescaler = 0;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseInit(GTMR0, &TMR_TimeBaseStructure);

  /* GTMR0 output mode configuration */
  TMR_OCStructInit(&TMR_OCInitStructure);
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM1;
  TMR_OCInitStructure.TMR_Pulse = 1;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OC1Init(GTMR0, &TMR_OCInitStructure);

  /* Slave Mode selection: GTMR0 */
  TMR_SelectSlaveMode(GTMR0, TMR_SlaveMode_Gated);
  TMR_SelectInputTrigger(GTMR0, TMR_TS_ITR0);

  TMR_DeInit(GTMR1);
  
  /* Time Base configuration */
  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure);
  TMR_TimeBaseStructure.TMR_Period = 1;
  TMR_TimeBaseStructure.TMR_Prescaler = 0;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseInit(GTMR1, &TMR_TimeBaseStructure);

  /* GTMR1 output mode configuration */
  TMR_OCStructInit(&TMR_OCInitStructure);
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM1;
  TMR_OCInitStructure.TMR_Pulse = 1;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OC1Init(GTMR1, &TMR_OCInitStructure);

  /* Slave Mode selection: GTMR1 */
  TMR_SelectSlaveMode(GTMR1, TMR_SlaveMode_Gated);
  TMR_SelectInputTrigger(GTMR1, TMR_TS_ITR0);


  TMR_DeInit(ETMR0);
  
  /* Time Base configuration */
  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure);
  TMR_TimeBaseStructure.TMR_Period = 255;
  TMR_TimeBaseStructure.TMR_Prescaler = 0;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseStructure.TMR_RepetitionCounter = 4;
  TMR_TimeBaseInit(ETMR0, &TMR_TimeBaseStructure);

  /* ETMR0 output mode configuration */
  TMR_OCStructInit(&TMR_OCInitStructure);
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM2;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OCInitStructure.TMR_OutputNState = TMR_OutputNState_Enable;
  TMR_OCInitStructure.TMR_Pulse = 127;
  TMR_OCInitStructure.TMR_OCPolarity = TMR_OCPolarity_Low;
  TMR_OCInitStructure.TMR_OCNPolarity = TMR_OCNPolarity_Low;
  TMR_OCInitStructure.TMR_OCIdleState = TMR_OCIdleState_Set;
  TMR_OCInitStructure.TMR_OCNIdleState = TMR_OCIdleState_Reset;
  TMR_OC1Init(ETMR0, &TMR_OCInitStructure);

  /* Automatic Output enable, Break, dead TMRe and lock configuration*/
  TMR_BDTRStructInit(&TMR_BDTRInitStructure);
  TMR_BDTRInitStructure.TMR_OSSRState = TMR_OSSRState_Enable;
  TMR_BDTRInitStructure.TMR_OSSIState = TMR_OSSIState_Enable;
  TMR_BDTRInitStructure.TMR_DeadTime = 5;
  TMR_BDTRConfig(ETMR0, &TMR_BDTRInitStructure);
  
  /* Master Mode selection */
  TMR_SelectOutputTrigger(ETMR0, TMR_TRGOSource_Update);
  
  /* ETMR0 enable counter */
  TMR_Cmd(ETMR0, ENABLE);

  /* GTMR0 enable counter */
  TMR_Cmd(GTMR0, ENABLE);
  
  /* GTMR1 enable counter */
  TMR_Cmd(GTMR1, ENABLE);
  
  /* ETMR0 Main Output Enable */
  TMR_CtrlPWMOutputs(ETMR0, ENABLE);
  
  printf("ETMR0 Main Output Enable.\r\n");
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
  
  /* ETMR0 GTMR0 GTMR1 clocks enable */
  SYSCFG0_TMRClockCmd(SYSCFG0_TMRCLK_ETMR0 | SYSCFG0_TMRCLK_GTMR0 | SYSCFG0_TMRCLK_GTMR1, ENABLE);

}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};

  /* GPIOE Configuration: Pin9 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF1_ETMR0_IO1);
  
  /* GPIOA Configuration: Pin15 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF1_GTMR0_IO2);
  
  /* GPIOB Configuration: Pin4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF2_GTMR1_IO3);

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
