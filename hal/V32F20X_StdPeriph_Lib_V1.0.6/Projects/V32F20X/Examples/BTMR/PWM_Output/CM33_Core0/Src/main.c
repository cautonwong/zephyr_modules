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
BPWM_BaseInitType BPWM_TimeBaseStructure = {0};
BPWM_OCInitType  BPWM_OCInitStructure = {0};

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
  
  /* GPIO Configuration */
  GPIO_Configuration();
  
  BSP_Printf_Init();
  
  BPWM_DeInit(BPWM0);
  BPWM_BaseStructInit(&BPWM_TimeBaseStructure);
  BPWM_TimeBaseStructure.Mode = BPWM_MODE_UPCOUNT;
  BPWM_TimeBaseStructure.ClockSource = BPWM_CLKSRC_APB;
  BPWM_TimeBaseStructure.ClockDivision = BPWM_CLKDIV_8;
  BPWM_BaseInit(BPWM0, &BPWM_TimeBaseStructure);
  
  BPWM_OCStructInit(&BPWM_OCInitStructure);
  BPWM_OCInitStructure.Channel = BPWM_CHANNEL_0;
  BPWM_OCInitStructure.Period = 255;
  BPWM_OCInitStructure.OutMode = BPWM_OUTMOD_TOGGLE;
  BPWM_OCInit(BPWM0, &BPWM_OCInitStructure);
  
  BPWM_OCInitStructure.Channel = BPWM_CHANNEL_1;
  BPWM_OCInitStructure.Period = 63;
  BPWM_OCInitStructure.OutMode = BPWM_OUTMOD_TOGGLE_RESET;
  BPWM_OCInit(BPWM0, &BPWM_OCInitStructure);
  
  BPWM_OCInitStructure.Channel = BPWM_CHANNEL_2;
  BPWM_OCInitStructure.Period = 63;
  BPWM_OCInitStructure.OutMode = BPWM_OUTMOD_RESET_SET;
  BPWM_OCInit(BPWM0, &BPWM_OCInitStructure);
  
  BPWM_OLineConfig(BPWM0_3_SEL, BPWM_OLINE_0, BPWM0_OUT0);
  BPWM_OLineConfig(BPWM0_3_SEL, BPWM_OLINE_1, BPWM0_OUT1);
  BPWM_OLineConfig(BPWM0_3_SEL, BPWM_OLINE_2, BPWM0_OUT2);
  
  BPWM_ClearCounter(BPWM0);
  
  BPWM_OutputCmd(BPWM0, BPWM_CHANNEL_0, ENABLE);
  BPWM_OutputCmd(BPWM0, BPWM_CHANNEL_1, ENABLE);
  BPWM_OutputCmd(BPWM0, BPWM_CHANNEL_2, ENABLE);
  
  printf("PWM output init success\r\n");
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
  SYSCFG0_TMRClockCmd(SYSCFG0_TMRCLK_BTMR_BPWM_GLOBAL | SYSCFG0_TMRCLK_BPWM0, ENABLE);
}

/**
  * @brief  Configure the ETMR0 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};

  /* GPIOF Configuration: Pin 6 Pin 7 Pin 8 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource6,GPIO_AF3_BTMR0_3_EXT_CLK);
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource7,GPIO_AF3_BTMR0_3_EXT_CLK);
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource8,GPIO_AF3_BTMR0_3_EXT_CLK);
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
