/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

unsigned char g_recieve_data[256];
unsigned int g_recieve_count = 0;
unsigned char g_send_data[256];
unsigned int g_send_count = 0;

#define ISO7816_BUFFER_SIZE  (5U)
const uint8_t TransmitBuffer[ISO7816_BUFFER_SIZE] = { 0x00, 0xB0, 0x99, 0x01, 0X08 };

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

unsigned char test_command = 0;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  GPIO_InitType  GPIO_InitStructure;
  ISO7816_InitType ISO7816_InitStruct;
  int i;
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

  /* uart */ 
  BSP_Printf_Init();
  printf("Hello World!\r\n");
    
  /* ESAM reset GPIO A9 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_WriteBit(GPIOA, GPIO_Pin_9, RESET);
   
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_ISO78161, ENABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Clock_ISO78161);
  
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF9_ISO78161_CLK);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource5, GPIO_AF9_ISO78161_DAT);
  
  /*ISO7816 DATA G5*/
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  
  /*ISO7816 CLK E2*/
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;  
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  /* config */
  ISO7816_DeInit(SAMPLE_IS07816);
  ISO7816_StructInit(&ISO7816_InitStruct);
  ISO7816_InitStruct.Baudrate = 8065;
  ISO7816_InitStruct.FirstBit = ISO7816_FIRSTBIT_LSB;
  ISO7816_InitStruct.Parity = ISO7816_PARITY_EVEN;
  ISO7816_InitStruct.RXACKLength = ISO7816_RXACKLEN_1;
  ISO7816_InitStruct.SerialClock = 48000000UL;;
  ISO7816_InitStruct.TXNACKLength = ISO7816_TXNACKLEN_0;
  ISO7816_InitStruct.TXRetry = ISO7816_TXRTY_0;
  ISO7816_Init(SAMPLE_IS07816, &ISO7816_InitStruct);
  
  /* Enable ISO78160 transmit error interrupt */
  ISO7816_INTConfig(SAMPLE_IS07816, ISO7816_INT_TXRTYERR, ENABLE);
  ISO7816_INTConfig(SAMPLE_IS07816, ISO7816_INT_RX, ENABLE);     //ENABLE   RX
  ISO7816_INTConfig(SAMPLE_IS07816, ISO7816_INT_TXDONE, DISABLE);//DISABLE TX
  
  /* NVIC cinfiguration */
  NVIC_EnableIRQ(ISO78160_1_IRQn);
  
  ISO7816_CLKDIVConfig(SAMPLE_IS07816, 16); //48/16 = 3M
  ISO7816_CLKOutputCmd(SAMPLE_IS07816, ENABLE);
  
  ISO7816_Cmd(SAMPLE_IS07816, ENABLE);
  
  printf("ISO7816 init success\r\n");
  
  /* delay 2ms */
  memset(g_recieve_data, 0, sizeof(g_recieve_data));
  g_recieve_count = 0;
  STD_Delay(2);
  
  /* reset pullup */  
  GPIO_WriteBit(GPIOA, GPIO_Pin_9, SET);
  
  while(g_recieve_count != 13)
  {
  }
  
  /* check esam ATR */
  if((g_recieve_data[0] != 0x3B)||(g_recieve_data[1] != 0x69))
  {
    printf("fail!");
    while(1)
    {
    }
  }
  
  /* send command to read Esam Number */
  memset(g_recieve_data, 0, sizeof(g_recieve_data));
  g_recieve_count = 0;
  for (i=0; i<ISO7816_BUFFER_SIZE; i++)
  {
    ISO7816_SendData(SAMPLE_IS07816, TransmitBuffer[i]);
    while (RESET == ISO7816_GetINTStatus(SAMPLE_IS07816, ISO7816_INT_TXDONE))
    {
    }
    ISO7816_ClearINTStatus(SAMPLE_IS07816, ISO7816_INT_TXDONE);
  }
  
  while(g_recieve_count != 11)
  {
  }
  
  /* check esam ATR */
  if((g_recieve_data[9] != 0x90)||(g_recieve_data[10] != 0x00))
  {
    printf("fail!");
  }
  
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
