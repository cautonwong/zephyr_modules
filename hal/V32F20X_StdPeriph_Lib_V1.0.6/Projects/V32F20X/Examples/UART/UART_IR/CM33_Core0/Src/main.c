/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lib_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

#define IRDA_FRE    38000

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
  
  /* Configure the System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  
  BSP_Printf_Init();
  
  uint32_t uart_clk;
  GPIO_InitType GPIO_InitStruct;
  UART_InitType UART_InitStruct;
  
  /*Configure UART19 TX pin*/
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF14_UART19_TX);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF14_UART19_RX);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_UART19, ENABLE);
  SYSCFG1_PeriphReset(SYSCFG1_Periph1Clock_UART19);
  SYSCFG1_UARTClockConfig(UART19, SYSCFG1_UART_CLKSRC_RCH, 1);

  uart_clk = CLK_GetUART14_19ClockFreq(UART19);

  UART_IrDASIRCmd(UART19, ENABLE);

  UART_DeInit(UART19);
  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.Baudrate = 9600;
  UART_InitStruct.SerialClock = uart_clk;
  UART_InitStruct.DataLength = UART_DATALEN_8B;
  UART_InitStruct.Parity  = UART_PARITY_NONE;
  UART_InitStruct.StopBit = UART_STOPBIT_1;
  UART_Init(UART19, &UART_InitStruct);
  SYSCFG1_UARTPinsCmd(UART19, ENABLE); 
  
  SYSCFG1_UARTIRDutyConfig(uart_clk*1/(IRDA_FRE*3), uart_clk*2/(IRDA_FRE*3));
  SYSCFG1_UARTIRCmd(UART19, ENABLE);
  
  for(uint32_t i=0; i<10; i++)
  {
    UART_SendData(UART19, 0x55);
    while(UART_GetFlag(UART19, UART_FLAG_TXE) == RESET);
  }
  
  printf("UART IR test success.\r\n");
  while(1)
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
