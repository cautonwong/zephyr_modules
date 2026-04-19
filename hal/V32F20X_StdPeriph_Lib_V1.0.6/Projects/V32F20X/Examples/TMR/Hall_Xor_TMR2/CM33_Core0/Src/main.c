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
  
  /* GPIO Configuration */
  GPIO_Configuration();
  
  /* Interrupt Configuration */
  NVIC_Configuration();
  
  /* ETMR1 XOR mode configuration--------------------------------------------
  ETMR1 channel1 ,channel2 and channel3 as HALL signal input channel, Trigger
  generated each signal edge.-----------------------------------------------
  ------------------------------------------------------------ */

  TMR_DeInit(ETMR1);

  /* Time Base configuration */
  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure);
  TMR_TimeBaseStructure.TMR_Period = 65535;
  TMR_TimeBaseStructure.TMR_Prescaler = 0;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseInit(ETMR1, &TMR_TimeBaseStructure);

  /* Config TI1 TRC as input source */
  TMR_ICStructInit(&TMR_ICInitStructure);
  TMR_ICInitStructure.TMR_Channel = TMR_Channel_1;
  TMR_ICInitStructure.TMR_ICSelection = TMR_ICSelection_TRC;

  TMR_ICInit(ETMR1, &TMR_ICInitStructure);
  
  TMR_SelectHallSensor(ETMR1, ENABLE);
  
  /* Select XOR signal as trigger */
  TMR_SelectInputTrigger(ETMR1, TMR_TS_TI1F_ED);
  
  /* ETMR1 counter reset each trigger */
  TMR_SelectSlaveMode(ETMR1, TMR_SlaveMode_Reset);
  
  /* Trigger interrupt enable */
  TMR_ITConfig(ETMR1, TMR_IT_Trigger , ENABLE);

  /* TMR counter enable */
  TMR_Cmd(ETMR1, ENABLE);
  
  printf("TMR counter enable.\r\n");
  while (1)
  {
    /* Generate HALL signal */
    GPIO_ResetBits(GPIOF, GPIO_Pin_14);
    STD_Delay(100);
    GPIO_SetBits(GPIOF, GPIO_Pin_13);
    STD_Delay(100);
    GPIO_ResetBits(GPIOF, GPIO_Pin_12);
    STD_Delay(100);
    GPIO_SetBits(GPIOF, GPIO_Pin_14);
    STD_Delay(100);
    GPIO_ResetBits(GPIOF, GPIO_Pin_13);
    STD_Delay(100);    
    GPIO_SetBits(GPIOF, GPIO_Pin_12);
    STD_Delay(100);

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
}

/**
  * @brief  Configure the GTMR0 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};

  /* GPIOC Configuration: Pin6, 7, 8 and 9 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF3_ETMR1_IO1);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF3_ETMR1_IO2);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF3_ETMR1_IO3);

  /* HALL signal (PF12 ,PF13 ,PF14) and trigger flag signal(PF15) configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
  GPIO_SetBits(GPIOF, GPIO_Pin_12);
  GPIO_ResetBits(GPIOF, (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15));

}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_EnableIRQ(ETMR1_TRG_COM_IRQn);
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
