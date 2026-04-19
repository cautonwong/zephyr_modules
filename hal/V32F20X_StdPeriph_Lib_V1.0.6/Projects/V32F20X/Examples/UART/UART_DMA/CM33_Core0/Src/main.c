/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "board.h"
#include "lib_uart.h"
#include "lib_gpio.h"
#include "lib_syscfg.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

static void DMA_UART_TX_RX(UART_Type *Send_UARTx, UART_Type *Reci_UARTx, uint32_t DMA_TxReq, uint32_t DMA_RxReq);
uint8_t tx_buff[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8_t rx_buff[8] = {0};

unsigned int DMA_UART_TX_count = 0;
unsigned int DMA_UART_RX_count = 0;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  GPIO_InitType GPIO_InitStructure;
  UART_InitType UART_InitStruct;
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
  
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_DMA0);
  
  /* init cm33_uart7 PA2 PA3 */
  BSP_Printf_Init();
  printf("UART2 and UART3 transform..\r\n");
  
  /*GPIO H11,10 -> UART2 TX, RX*/
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF4_FC2_TXD_SCL_MISO);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF4_FC2_RXD_SDA_MOSI);  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOH, &GPIO_InitStructure);  
  
  SYSCFG0_FlexcommClockConfig(FLEXCOMM2, SYSCFG0_FC_CLKSRC_RCH, 1);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_FC2, ENABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Clock_FC2);
  SYSCFG0_FlexcommModeConfig(FLEXCOMM2, SYSCFG0_FC_UART);

  uart_clk = CLK_GetFlexcommClockFreq(FLEXCOMM7);
  
  UART_DeInit(UART2);
  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.SerialClock = uart_clk;
  UART_InitStruct.Baudrate = 115200;
  UART_InitStruct.DataLength = UART_DATALEN_8B;
  UART_InitStruct.Parity  = UART_PARITY_NONE;
  UART_InitStruct.StopBit = UART_STOPBIT_1;
  UART_Init(UART2, &UART_InitStruct);

  printf("Start UART DMA transfer.\r\n");
  
  /* UART2 TX dma send to UART7 RX dma */
  DMA_UART_TX_RX(UART2, UART7, SYSCFG0_DMA_REQUEST_FC2_TX, SYSCFG0_DMA_REQUEST_FC7_RX);
  
  DMA_Cmd(DMA0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel1, DISABLE);
  
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

static void DMA_UART_TX_RX(UART_Type *Send_UARTx, UART_Type *Reci_UARTx, uint32_t DMA_TxReq, uint32_t DMA_RxReq)
{
  uint8_t temp = 0, i = 0, err = 0;
  DMA_InitType  DMA_InitStructure;

  /* SET recieve FIFO level */
  UART_ReceiveFIFOConfig(Reci_UARTx, UART_FIFOLEVEL_1, ENABLE);
  
   /*CH0 IRQ Test*/
  DMA_Cmd(DMA0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel1, DISABLE);
  
  DMA_ITConfig(DMA0_Channel0, DMA_INT_BLOCK, DISABLE);
  DMA_ITConfig(DMA0_Channel1, DMA_INT_BLOCK, DISABLE);
  
  DMA_DeInit(DMA0_Channel0);
  DMA_DeInit(DMA0_Channel1);
  
  while(UART_GetFlag(Reci_UARTx, UART_FLAG_RX) == SET)
  {
    temp = UART_ReceiveData(Reci_UARTx);
  }
  
  /* CH0 -> UART TX */
  DMA_StructInit(&DMA_InitStructure); 
  DMA_InitStructure.DMA_SourceAddress = (uint32_t) (&(tx_buff[0]));  
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (&(Send_UARTx->THR));
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_8Bit;
  DMA_InitStructure.DMA_DestinationBurstSize = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_8Bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_TransferSize = 8;
  DMA_InitStructure.DMA_DestinationRequestSelect = DMA_DestinationRequestSelect_0;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0, DMA_TxReq);
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
  
  /*CH1 -> UART RX*/
  DMA_StructInit(&DMA_InitStructure); 
  DMA_InitStructure.DMA_SourceAddress = (uint32_t)(&(Reci_UARTx->RBR));
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (&(rx_buff[0]));
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_8Bit;
  DMA_InitStructure.DMA_DestinationBurstSize = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_8Bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_TransferSize = 8;
  DMA_InitStructure.DMA_SourceRequestSelect = DMA_SourceRequestSelect_1;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ1, DMA_RxReq);
  DMA_Init(DMA0_Channel1, &DMA_InitStructure);
  
  /* enable dma interrupt */
  NVIC_EnableIRQ(DMA0_CH0_IRQn);
  NVIC_EnableIRQ(DMA0_CH1_IRQn);
  DMA_ITConfig(DMA0_Channel0, DMA_INT_BLOCK, ENABLE);
  DMA_ITConfig(DMA0_Channel1, DMA_INT_BLOCK, ENABLE);

  /* enable dma */
  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel1, ENABLE);
  
  
  while((DMA_UART_TX_count == 0)||(DMA_UART_RX_count == 0))
  {
  }
  

  
  if(memcmp(tx_buff, rx_buff, 8) == 0)
  {
    printf("pass!");
  }
  else
  {
    printf("fail!");
  }
  
  return;
}

/*********************************** END OF FILE ******************************/
