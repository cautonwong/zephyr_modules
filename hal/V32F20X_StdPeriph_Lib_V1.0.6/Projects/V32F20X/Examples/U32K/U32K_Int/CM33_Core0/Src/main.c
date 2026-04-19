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
U32K_InitType U32K_InitStruct;
UART_InitType  UART_InitStructure;
uint32_t u32kCount = 0;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void GPIO_Configuration(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0;
  uint32_t uart_clk;

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
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();

  GPIO_Configuration();

  uart_clk = CLK_GetUART14_19ClockFreq(UART15);

  UART_DeInit(UART15);
  UART_StructInit(&UART_InitStructure);
  UART_InitStructure.Baudrate = 9600;
  UART_InitStructure.SerialClock = uart_clk;
  UART_InitStructure.DataLength = UART_DATALEN_8B;
  UART_InitStructure.Parity  = UART_PARITY_NONE;
  UART_InitStructure.StopBit = UART_STOPBIT_1;
  UART_Init(UART15, &UART_InitStructure);
  SYSCFG1_UARTPinsCmd(UART15, ENABLE);

  U32K_DeInit(U32K0);
  U32K_InitStruct_Init(&U32K_InitStruct);
  U32K_InitStruct.Baudrate = 9600;
  U32K_InitStruct.AutoCal  = U32K_AUTO_CAL_ON;
  U32K_InitStruct.Debounce = U32K_DEBOUNCE_0;
  U32K_InitStruct.FirstBit = U32K_FIRSTBIT_LSB;
  U32K_InitStruct.Parity   = U32K_PARITY_NONE;
  U32K_InitStruct.Pcheck   = U32K_PARITY_CHECK_NOT;
  U32K_InitStruct.LineSel  = U32K_USE_RX1;
  U32K_InitStruct.WKU_nByte = 3;
  U32K_Init(U32K0, &U32K_InitStruct);
  
  U32K_Cmd(U32K0, ENABLE);
  U32K_ClearINTStatus(U32K0);
  U32K_WKU_INT_Config(U32K0, ENABLE);

  PMU_RETRAMConfig(PMU_RAM_MODE_U32K);
 
  printf("Wait U32K rcv data\r\n");
  
  while(1)
  {
    u32kCount = PMU_GetU32kReceive(PMU_SRC_U32K0);
    
    if (u32kCount >= 3)
    {
      PMU_RETRAMConfig(PMU_RAM_MODE_NORMAL);
      U32K_Cmd(U32K0, DISABLE);
      printf("uart count:%d\r\n", u32kCount);
      for(i= 0; i < u32kCount; i++)
      {
        printf("uart_rcv_u32k = 0x%x \r\n",RETRAM->RAM[i]);
      }

      break;
    }
  }
  printf("pass");
  
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
  
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOLState = CLK_XOL_ON;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  //U32k clock source from XOL
  RTCEx_ClkSRCConfig(RTC_CLKSRC_32KXTAL);
  
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
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStruct;
  
  /* Enable UART32K clocks */
  SYSCFGLP_PeriphClockCmd(SYSCFGLP_PeriphClock_UART32K0, ENABLE);
  /* Enable RETRAM clocks */
  SYSCFGLP_PeriphClockCmd(SYSCFGLP_PeriphClock_RETRAM, ENABLE);
  SYSCFGLP_PeriphReset(SYSCFGLP_PeriphReset_UART32K0);
  /*Configure UART14 RX PD14 pin*/
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF14_UART15_RX);
  /* Configure PD14 & PD15 as alternate input */
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
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
