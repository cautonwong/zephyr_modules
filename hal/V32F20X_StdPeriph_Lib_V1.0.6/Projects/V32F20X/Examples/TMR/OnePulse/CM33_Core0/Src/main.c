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
  
  /* GTMR1 configuration: One Pulse mode ------------------------
     The external signal is connected to GTMR1_CH2 pin (PC.07),
     The Rising edge is used as active edge,
     The One Pulse signal is output on GTMR1_CH1 pin (PC.06)
     The TMR_Pulse defines the delay value
     The (TMR_Period -  TMR_Pulse) defines the One Pulse value.
     GTMR1 CLK = SystemCoreClock, GTMR1 counter clock is 24 MHz:
     The Autoreload value is 65535 (GTMR1->ARR), so the maximum frequency value
     to trigger the GTMR1 input is 24000000/65535 ~ 366.2 Hz.

     The TMR_Pulse defines the delay value, the delay value is fixed
     to 546.1 us:
     delay =  CCR1/GTMR1 counter clock = 546.1 us.
     The (TMR_Period - TMR_Pulse) defines the One Pulse value,
     the pulse value is fixed to 2.184 ms:
     One Pulse value = (TMR_Period - TMR_Pulse) / GTMR1 counter clock = 2.184 ms.
  ------------------------------------------------------------ */

  TMR_DeInit(GTMR1);

  /* Time Base configuration */
  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure);
  TMR_TimeBaseStructure.TMR_Prescaler = 1;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_Period = 65535;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseInit(GTMR1, &TMR_TimeBaseStructure);

  /* Output Compare Active Mode configuration: Channel1 */
  TMR_OCStructInit(&TMR_OCInitStructure);
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM2;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OCInitStructure.TMR_Pulse = 13106;

  TMR_OCInitStructure.TMR_OCPolarity = TMR_OCPolarity_High;
  TMR_OC1Init(GTMR1, &TMR_OCInitStructure);

  /* GTMR1 configuration in Input Capture Mode */
  TMR_ICStructInit(&TMR_ICInitStructure);
  TMR_ICInitStructure.TMR_Channel = TMR_Channel_2;
  TMR_ICInitStructure.TMR_ICPolarity = TMR_ICPolarity_Rising;
  TMR_ICInitStructure.TMR_ICSelection = TMR_ICSelection_DirectTI;
  TMR_ICInitStructure.TMR_ICPrescaler = TMR_ICPSC_DIV1;
  TMR_ICInitStructure.TMR_ICFilter = 0;

  TMR_ICInit(GTMR1, &TMR_ICInitStructure);
  
  /* One Pulse Mode selection */
  TMR_SelectOnePulseMode(GTMR1, TMR_OPMode_Single);

  /* Input Trigger selection */
  TMR_SelectInputTrigger(GTMR1, TMR_TS_TI2FP2);

  /* Slave Mode selection: Trigger Mode */
  TMR_SelectSlaveMode(GTMR1, TMR_SlaveMode_Trigger);
  
  printf("Slave Mode selection: Trigger Mode.\r\n");
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
  
  /* GTMR1 clocks enable */
  SYSCFG0_TMRClockCmd(SYSCFG0_TMRCLK_GTMR1, ENABLE);
}

/**
  * @brief  Configure the GTMR1 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};

  /* TIM4_CH1 pin (PC.06) configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* TIM4_CH2 pin (PC.07) configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF2_GTMR1_IO1);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF2_GTMR1_IO2);
  
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
