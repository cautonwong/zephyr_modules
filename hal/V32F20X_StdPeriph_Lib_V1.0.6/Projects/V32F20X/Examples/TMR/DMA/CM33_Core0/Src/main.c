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
uint16_t SRC_Buffer[3] = {0, 0, 0};
uint16_t TimerPeriod = 0;
uint32_t SystemCoreClock = 48000000;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void DMA_Configuration(void);

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

  /* DMA Configuration */
  DMA_Configuration();
  
  /* ETMR0 DMA Transfer example -------------------------------------------------
  TMR1CLK = SystemCoreClock, Prescaler = 0, ETMR0 counter clock = SystemCoreClock

  The objective is to configure ETMR0 channel 3 to generate complementary PWM
  signal with a frequency equal to 17.57 KHz:
     - TMR1_Period = (SystemCoreClock / 17570) - 1
  and a variable duty cycle that is changed by the DMA after a specific number of
  Update DMA request.

  The number of this repetitive requests is defined by the ETMR0 Repetition counter,
  each 3 Update Requests, the ETMR0 Channel 3 Duty Cycle changes to the next new 
  value defined by the SRC_Buffer . 
  -----------------------------------------------------------------------------*/

  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock / 17570 ) - 1;
  /* Compute CCR1 value to generate a duty cycle at 50% */
  SRC_Buffer[0] = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
  /* Compute CCR1 value to generate a duty cycle at 37.5% */
  SRC_Buffer[1] = (uint16_t) (((uint32_t) 375 * (TimerPeriod - 1)) / 1000);
  /* Compute CCR1 value to generate a duty cycle at 25% */
  SRC_Buffer[2] = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);

  TMR_DeInit(ETMR0);

  /* Time Base configuration */
  TMR_TimeBaseStructure.TMR_Prescaler = 0;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseStructure.TMR_Period = TimerPeriod;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseStructure.TMR_RepetitionCounter = 2;

  TMR_TimeBaseInit(ETMR0, &TMR_TimeBaseStructure);

  /* Channel 1, 2 and 3 Configuration in PWM mode */
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM2;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OCInitStructure.TMR_OutputNState = TMR_OutputNState_Enable;
  TMR_OCInitStructure.TMR_Pulse = SRC_Buffer[0];
  TMR_OCInitStructure.TMR_OCPolarity = TMR_OCPolarity_Low;
  TMR_OCInitStructure.TMR_OCNPolarity = TMR_OCNPolarity_Low;
  TMR_OCInitStructure.TMR_OCIdleState = TMR_OCIdleState_Set;
  TMR_OCInitStructure.TMR_OCNIdleState = TMR_OCNIdleState_Reset;

  TMR_OC3Init(ETMR0, &TMR_OCInitStructure);

  /* ETMR0 Update DMA Request enable */
  TMR_DMACmd(ETMR0, TMR_DMA_Update, ENABLE);
  
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
  
  /* DMA clock enable */
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
}

/**
  * @brief  Configure the ETMR0 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};

  /* GPIOA Configuration: Channel 3 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIOB Configuration: Channel 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Connect TMR pins to AF1 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF1_ETMR0_IO3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF1_ETMR0_O3_N);

}


/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */
void DMA_Configuration(void)
{
  DMA_InitType DMA_InitStructure = {0};
  
  DMA_Cmd(DMA0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_DMA0);
  
  /* DMA1 Channel5 Config */
  DMA_DeInit(DMA0_Channel0);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceAddress = (uint32_t) &SRC_Buffer;
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (&ETMR0->CCR3);
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_16Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_16Bit;
  DMA_InitStructure.DMA_TransferSize = 3;
  DMA_InitStructure.DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_Mode = DMA_MODE_AUTO_RELOAD;

  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0,SYSCFG0_DMA_REQUEST_TMR1_UP);

  DMA_Init(DMA0_Channel0, &DMA_InitStructure);

  /* DMA1 Channel0 enable */
  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);
  
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
