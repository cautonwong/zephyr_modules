/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-05
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void CMP_GPIO_Configuration(void);
void GPIO_Configuration(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  COMP_InitType COMP_InitStructure;
  
  STD_Init(CLK_GetHCLK0Freq());

  /* Config COMP clock */
  SYSCFGLP_APBLPClockConfig(SYSCFGLP_APBLP_CLKSRC_RCL,32);
  SYSCFGLP_PeriphClockCmd(SYSCFGLP_PeriphClock_COMP, ENABLE);

  CMP_GPIO_Configuration();
  GPIO_Configuration();
  BSP_Printf_Init();
  COMP_DeInit();

  /* COMP configuration ------------------------------------------------------*/
  COMP_StructInit(&COMP_InitStructure);
  COMP_InitStructure.COMP_HystEn = ENABLE;
  COMP_InitStructure.COMP_OutputLevel = COMP_Output_Positive;
  COMP_InitStructure.COMP_FilterClkDiv = COMP_Filter_ClkDiv_128;
  COMP_InitStructure.COMP_FilterClkPeriod = COMP_Filter_Period_0;
  COMP_InitStructure.COMP_Mode = COMP_Mode_HighSpeed;
  COMP_Init(COMP0, &COMP_InitStructure);

  COMP_Cmd(COMP0 ,ENABLE);
  COMP_LPulseTime_Config(COMP0,255,ENABLE);
  
  GPIO_SetBits(GPIOC, GPIO_Pin_8);
  GPIO_ToggleBits(GPIOC, GPIO_Pin_8);
  
  printf("Compare pulse test\r\n");
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
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  
  /* RCH(48M) enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_RCH;
  CLK_OscInitStruct.RCHState = CLK_RCH_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_RCH_DIV4;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = CLK_PLL0_1stN_2;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = 24;
  CLK_OscInitStruct.PLL0.PLL0_M      = 2;
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
  CLK_InitStruct.AHBCLKDivider = 2U;
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
  * @brief  Configures the CMP GPIO ports.
  * @param  None
  * @retval None
  */
void CMP_GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStruct;

  /*Configure COMP0 Out PA8 pin*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF9_CMP0_OUT);

  /* Configure COMP0  PA11(Vip) & PA12(Vin) as input */
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 ;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
  * @brief  Configure  GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStruct;

  /*PC8 connect COMP0  PA11(Vip)*/
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
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
