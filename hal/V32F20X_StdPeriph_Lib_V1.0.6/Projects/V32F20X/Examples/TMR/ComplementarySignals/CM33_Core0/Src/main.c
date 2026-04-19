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
TMR_BDTRInitType TMR_BDTRInitStructure = {0};
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0;
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
  
  /* ---------------------------------------------------------------------------
  ETMR0 Configuration to:

  1/ Generate 3 complementary PWM signals with 3 different duty cycles:

    ETMR0 input clock (TMR1CLK) is set to 2 * APB2 clock (PCLK2), since APB2
    prescaler is different from 1.
    TMR1CLK = 2 * PCLK2
    PCLK2 = HCLK / 2
    => TMR1CLK = 2 * (HCLK / 2) = HCLK = SystemCoreClock

    TMR1CLK is fixed to SystemCoreClock, the ETMR0 Prescaler is equal to 0 so the
    ETMR0 counter clock used is SystemCoreClock (120MHz).

    The objective is to generate PWM signal at 17.57 KHz:
    - TMR1_Period = (SystemCoreClock / 17570) - 1

    The Three Duty cycles are computed as the following description:

    The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
    The channel 2 duty cycle is set to 25% so channel 2N is set to 75%.
    The channel 3 duty cycle is set to 12.5% so channel 3N is set to 87.5%.

    The Timer pulse is calculated as follows:
      - ChannelxPulse = DutyCycle * (TMR1_Period - 1) / 100

  2/ Insert a dead time equal to (11/SystemCoreClock) ns

  3/ Configure the break feature, active at High level, and using the automatic
     output enable feature

  4/ Use the Locking parameters level1.

  Note:
    SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
    Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
    function to update SystemCoreClock variable value. Otherwise, any configuration
    based on this variable will be incorrect.
  --------------------------------------------------------------------------- */

  /* Compute the value to be set in ARR register to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock / 17570) - 1;

  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 */
  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);

  /* Compute CCR2 value to generate a duty cycle at 25%  for channel 2 */
  Channel2Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);

  /* Compute CCR3 value to generate a duty cycle at 12.5%  for channel 3 */
  Channel3Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod - 1)) / 1000);

  TMR_DeInit(ETMR0);

  /* Time Base configuration */
  TMR_TimeBaseStructure.TMR_Prescaler = 0;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_Period = TimerPeriod;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseStructure.TMR_RepetitionCounter = 0;

  TMR_TimeBaseInit(ETMR0, &TMR_TimeBaseStructure);

  /* Channel 1, 2 and 3 Configuration in PWM mode */
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM2;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OCInitStructure.TMR_OutputNState = TMR_OutputNState_Enable;
  TMR_OCInitStructure.TMR_Pulse = Channel1Pulse;
  TMR_OCInitStructure.TMR_OCPolarity = TMR_OCPolarity_Low;
  TMR_OCInitStructure.TMR_OCNPolarity = TMR_OCNPolarity_Low;
  TMR_OCInitStructure.TMR_OCIdleState = TMR_OCIdleState_Set;
  TMR_OCInitStructure.TMR_OCNIdleState = TMR_OCNIdleState_Reset;

  TMR_OC1Init(ETMR0, &TMR_OCInitStructure);

  TMR_OCInitStructure.TMR_Pulse = Channel2Pulse;
  TMR_OC2Init(ETMR0, &TMR_OCInitStructure);

  TMR_OCInitStructure.TMR_Pulse = Channel3Pulse;
  TMR_OC3Init(ETMR0, &TMR_OCInitStructure);

  /* Automatic Output enable, Break, dead time and lock configuration*/
  TMR_BDTRInitStructure.TMR_OSSRState = TMR_OSSRState_Enable;
  TMR_BDTRInitStructure.TMR_OSSIState = TMR_OSSIState_Enable;
  TMR_BDTRInitStructure.TMR_LOCKLevel = TMR_LOCKLevel_1;
  TMR_BDTRInitStructure.TMR_DeadTime = 11;
  TMR_BDTRInitStructure.TMR_Break = TMR_Break_Enable;
  TMR_BDTRInitStructure.TMR_BreakPolarity = TMR_BreakPolarity_High;
  TMR_BDTRInitStructure.TMR_AutomaticOutput = TMR_AutomaticOutput_Enable;

  TMR_BDTRConfig(ETMR0, &TMR_BDTRInitStructure);

  /* ETMR0 counter enable */
  TMR_Cmd(ETMR0, ENABLE);

  /* Main Output Enable */
  TMR_CtrlPWMOutputs(ETMR0, ENABLE);

  printf("Main Output Enable.\r\n");
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
  
  /* ETMR0, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
  SYSCFG0_TMRClockCmd(SYSCFG0_TMRCLK_ETMR0, ENABLE);
}

/**
  * @brief  Configure the ETMR0 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};


  /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  /* GPIOE Configuration: BKIN, Channel 1N, 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_12;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF1_ETMR0_O1_N);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF1_ETMR0_O2_N);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF1_ETMR0_O3_N);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF1_ETMR0_BKIN);

  /* Connect TMR pins to AF1 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF1_ETMR0_IO1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF1_ETMR0_IO2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF1_ETMR0_IO3);
  
  
  
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
