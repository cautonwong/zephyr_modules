/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-03
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_InitType ADC_InitStructure;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void SYSCON_Configuration(void);
void GPIO_Configuration(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t result;
  uint32_t expected;
  
  /* V32F20xxx CM33 core0 STD library initialization:
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Set NVIC Group Priority to 3
       - Low Level Initialization
     */
  STD_Init(CLK_GetHCLK0Freq());
  
  /* Configure the CM33/CM0 System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();

  SYSCON_Configuration();

  GPIO_Configuration();
  
  /* Set the ADC reference voltage. */
  SYSCFG0_ADCVref_config(SYSCFG0_ADC_VERF_EXTI, SYSCFG0_ADC_VERF_3_2V);
 
  /*Must be call first*/
  ADC_DeInit();

  /* ADC0 Configuration ------------------------------------------------------*/
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Mode                  = ADC_Mode_RegInjecSimult;
  ADC_InitStructure.ADC_ScanMode              = DISABLE;
  ADC_InitStructure.ADC_ContinuousMode        = ENABLE;
  ADC_InitStructure.ADC_ExternalTrig          = ADC_EXT_TRIG_CONV_NONE;
  ADC_InitStructure.ADC_DataAlign             = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NumOfChannel          = 1;
  ADC_InitStructure.ADC_BtimerTrig            = DISABLE;
  ADC_Init(ADC0, &ADC_InitStructure);

  /* ADC1 Configuration ------------------------------------------------------*/
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Mode                  = ADC_Mode_RegInjecSimult;
  ADC_InitStructure.ADC_ScanMode              = DISABLE;
  ADC_InitStructure.ADC_ContinuousMode        = ENABLE;
  ADC_InitStructure.ADC_ExternalTrig          = ADC_EXT_TRIG_CONV_NONE;
  ADC_InitStructure.ADC_DataAlign             = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NumOfChannel          = 1;
  ADC_InitStructure.ADC_BtimerTrig            = DISABLE;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel configuration */ 
  ADC_RegularChannelConfig(ADC0, ADC_Channel_6, 1, ADC_SampleTime_28_5);
  /* ADC1 regular channel configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_28_5);

  /* Enable ADC0 */
  ADC_Ctrl(ADC0, ENABLE);

  /* Enable ADC0 reset calibration register */   
  ADC_RstCalibration(ADC0);
  /* Check the end of ADC0 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC0));

  /* Start ADC0 calibration */
  ADC_StartCalibration(ADC0);
  
  printf("Start ADC0 calibration\r\n");
  /* Check the end of ADC0 calibration */
  while(ADC_GetCalibrationStatus(ADC0));
 
  /* Enable ADC1 */
  ADC_Ctrl(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_RstCalibration(ADC1);
  /* Check the ADC_RstCalibration of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));

  /* Enable EOC interrupt */
  ADC_INTConfig(ADC0, ADC_INT_EC, ENABLE);
  NVIC_EnableIRQ(ADC0_IRQn);

  /* Start ADC0 Software Conversion */ 
  ADC_SoftwareStartConvCtrl(ADC0, ENABLE);
 
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  AHB and APB Clock Configuration
  *         The Clock is configured as follows :
  *            Select RCH as AHB and APB clock.
  *            Open XOH, select XOH as PLL0 source.
  *            config PLL0 frequency, open PLL0.
  *            Open XOL, select XOL as PLL1 source.
  *            config PLL1 frequency, open PLL1.
  *            Select PLL0 as HCLK0 and PCLK0 source.
  *            Set 1 to HCLK0 Divider.
  *            Set 1 to PCLK0 Divider.
  *            Select PLL0 as HCLK1 and PCLK1 source.
  *            Set 2 to HCLK1 Divider.
  *            Set 2 to PCLK1 Divider.
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  
  /* Select RCH as AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0 | CLK_BUSCLOCK1;
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
  
  /* PLL0(48M) enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_XOH | CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOHState = CLK_XOH_ON;
  CLK_OscInitStruct.XOLState = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_XOH;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKN0;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKN1;
  CLK_OscInitStruct.PLL0.PLL0_M      = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKM;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_ON;
  CLK_OscInitStruct.PLL1.PLL1_Source = CLK_PLL1SOURCE_XOL_32768;
  CLK_OscInitStruct.PLL1.PLL1_Frequency = CLK_PLL1_IN_32768_OUT_184_32M;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL0 as  AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 1U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 2U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  CLK_InitStruct.BusClock = CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_PLL0;
  CLK_InitStruct.AHBCLKDivider = 2U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_PLL0;
  CLK_InitStruct.APBCLKDivider = 2U;
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
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void SYSCON_Configuration(void)
{
  /* ADCCLK = RCH/5 */
  SYSCFG0_ADCClockConfig(SYSCFG0_ADC_CLKSRC_RCH, 4);

  /* Enable ADC clocks */
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_ADC, ENABLE);
  
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStruct;

  /* Configure PA6 (ADC Ch6)as analog input */
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure PC1 (ADC Ch11)as analog input */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
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
