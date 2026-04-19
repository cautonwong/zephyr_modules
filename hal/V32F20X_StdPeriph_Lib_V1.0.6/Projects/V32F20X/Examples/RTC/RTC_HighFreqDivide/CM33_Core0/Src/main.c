/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-05
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/**
  * @brief  Enables or disables output of second pulse from high-frequency clock dividing.
  * @param  NewState: new state of output of second pulse
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void RTCALM_HighFreqSPOutputCmd(FunctionalState NewState)
{
  GPIO_InitType GPIO_InitStruct;

  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  
  if(NewState != DISABLE)
  {
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOI, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOI,GPIO_PinSource0, GPIO_AF0_RTC_PLLDIV0);
  }
  else
  {
    /* disable second pulse output by setting PI0 mode to default analog mode */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_Init(GPIOI, &GPIO_InitStruct);
  }
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  
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
  SystemClock_Config();

  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();
  
  /* select XOL 32768Hz */
  RTCEx_ClkSRCConfig(RTC_CLKSRC_32KXTAL);

  SYSCFGLP_PeriphClockCmd(SYSCFGLP_PeriphClock_RTC_ALARM, ENABLE);
  
  /* PLL1 frequency is 61.44MHz, we set PLLDIV = 61440000/2 - 1,
   * so 1Hz periodic pulse will be generated.
   */
  RTC_ALM_HighFreqDivideConfig(RTC_ALM_PLLDIVCLK_PLL1, 61440000/2 - 1);
  
  /* enable ouput of 1Hz periodic pulse */
  RTCALM_HighFreqSPOutputCmd(ENABLE);
  /* Delay 10 seconds */
  STD_Delay(10000);
  /* disable ouput of 1Hz periodic pulse */
  RTCALM_HighFreqSPOutputCmd(DISABLE);
  
  printf("RTC high freq divide test end\r\n");

  /* Infinite loop */
  while (1)
  {
  }
}


/**
  * @brief  AHB and APB Clock Configuration
  *         The Bus Clock is configured as follows :
  *            HCLK0    = PLL0   128 MHz
  *            PCLK0    = PLL0/2 64  MHz
  *            HCLK1    = PLL0/2 64  MHz
  *            PCLK1    = PLL0/2 64  MHz
  *            PLL1     = 61.44MHz
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
  
  /* PLL enabled */
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
  CLK_OscInitStruct.PLL1.PLL1_Frequency = CLK_PLL1_IN_32768_OUT_61_44M;
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
