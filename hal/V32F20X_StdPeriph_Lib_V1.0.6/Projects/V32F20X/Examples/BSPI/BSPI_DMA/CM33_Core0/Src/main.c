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
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

uint8_t Transmit_Buffer_8b[8] __attribute__((section(".ARM.__at_0x2100B000")));
uint8_t Recieve_Buffer_8b[8] __attribute__((section(".ARM.__at_0x2100C000")));

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0;
  GPIO_InitType GPIO_InitStruct;
  BSPI_InitType SPI_InitStruct;
  BDMA_InitType DMA_InitStruct;
  
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
  
  printf("\r\n BSPI0 send data to BSPI2");
  
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_BSPI0, ENABLE);
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI0);
  
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_BSPI2, ENABLE);
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI2);

  
  /*
  PA9 -> BSPI0 MOSI 
  PC7 -> BSPI0 CK 
  PC8 -> BSPI0 CS 
  PC9 -> BSPI0 MISO 
  */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF14_BSPI0_MOSI);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF14_BSPI0_MISO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF14_BSPI0_CK);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF14_BSPI0_CS);
  
  /*config spi sck mosi*/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  /*config spi miso*/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /*config spi cs*/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  /* SPI0 initialization, master mode */
  BSPI_DeviceInit(BSPI0);
  BSPI_StructInit(&SPI_InitStruct);
  SPI_InitStruct.Mode = SPI_MODE_MASTER;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_DISABLE;  //CS controlled by hardware
  BSPI_Init(BSPI0, &SPI_InitStruct);
  
  /*Enable SPI0 */
  BSPI_Cmd(BSPI0, ENABLE);

  /*
  I3  -> BSPI2 MOSI 
  C10 -> BSPI2 CK 
  I2  -> BSPI2 CS 
  H14 -> BSPI2 MISO 
  */
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource3,  GPIO_AF14_BSPI2_MOSI);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF14_BSPI2_CK);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource14, GPIO_AF14_BSPI2_MISO);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource12, GPIO_AF14_BSPI2_CS);
  
  /*config spi sck*/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  /*config spi mosi*/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3;
  GPIO_Init(GPIOI, &GPIO_InitStruct);
  
  /*config spi miso*/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_14;
  GPIO_Init(GPIOH, &GPIO_InitStruct);
  
  /*config spi cs*/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2;
  GPIO_Init(GPIOI, &GPIO_InitStruct);
  
  /* CSN pin output high, inactive */
  GPIO_SetBits(GPIOI, GPIO_Pin_2);
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_Init(GPIOI, &GPIO_InitStruct);
  
  /* SPI0 initialization, master mode */
  BSPI_DeviceInit(BSPI2);
  BSPI_StructInit(&SPI_InitStruct);
  SPI_InitStruct.Mode = SPI_MODE_SLAVE;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_DISABLE;
  BSPI_Init(BSPI2, &SPI_InitStruct);
  
  /*Enable SPI2 */
  BSPI_Cmd(BSPI2, ENABLE);
  
  /* DMA config BSPI0 TX*/
  BDMA_DeInit(BDMA_CHANNEL_0);
  BDMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.SrcAddr = (uint32_t)&Transmit_Buffer_8b[0];
  DMA_InitStruct.SrcAddrMode = BDMA_SRCADDRMODE_FEND;
  DMA_InitStruct.DestAddr = (uint32_t)&(BSPI0->TXDAT);
  DMA_InitStruct.DestAddrMode = BDMA_DESTADDRMODE_FIX;
  DMA_InitStruct.FrameLen = 1 - 1;
  DMA_InitStruct.PackLen = 8 - 1;
  DMA_InitStruct.TransSize = BDMA_TRANSSIZE_BYTE;
  DMA_InitStruct.ReqSrc = BDMA_REQSRC_BSPI0_TX;
  DMA_InitStruct.ContMode = BDMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = BDMA_TRANSMODE_SINGLE;
  BDMA_Init(&DMA_InitStruct, BDMA_CHANNEL_0);
  
  /* DMA config BSPI2 RX*/
  BDMA_DeInit(BDMA_CHANNEL_2);
  BDMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.SrcAddr =  (uint32_t)&(BSPI2->RXDAT);
  DMA_InitStruct.SrcAddrMode = BDMA_SRCADDRMODE_FIX;
  DMA_InitStruct.DestAddr = (uint32_t)&Recieve_Buffer_8b[0];
  DMA_InitStruct.DestAddrMode = BDMA_DESTADDRMODE_FEND;
  DMA_InitStruct.FrameLen = 1 - 1;
  DMA_InitStruct.PackLen = 8 - 1;
  DMA_InitStruct.TransSize = BDMA_TRANSSIZE_BYTE;
  DMA_InitStruct.ReqSrc = BDMA_REQSRC_BSPI2_RX;
  DMA_InitStruct.ContMode = BDMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = BDMA_TRANSMODE_SINGLE;
  BDMA_Init(&DMA_InitStruct, BDMA_CHANNEL_2);
  
  for(i = 0; i < 8; i++)
  {
    Transmit_Buffer_8b[i] = i+1;
  }
  
  /* Enable BDMA channel0 */
  BDMA_Cmd(BDMA_CHANNEL_0, ENABLE);
  /* Enable BDMA channel0 */
  BDMA_Cmd(BDMA_CHANNEL_2, ENABLE);
  
  printf("BDMA enabled\r\n");
  
  while((BDMA_GetINTStatus(BDMA_INT_C0PE) == RESET)||(BDMA_GetINTStatus(BDMA_INT_C2PE) == RESET))
  {
  }
  
  if(memcmp(Recieve_Buffer_8b, Transmit_Buffer_8b, 8) == 0)
  {
    printf("\r\n pass");
  }
  else
  {
    printf("\r\n fail");
  }
  
  while (1)
  {
    ;
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
