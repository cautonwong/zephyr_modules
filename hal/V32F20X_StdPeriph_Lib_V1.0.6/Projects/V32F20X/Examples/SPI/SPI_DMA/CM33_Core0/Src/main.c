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
static void DMA_SPI_TX_RX(SPI_Type* Master_SPIx, SPI_Type* Slave_SPIx, uint32_t DMA_master_TxReq, uint32_t DMA_master_RxReq, uint32_t DMA_Slave_TxReq, uint32_t DMA_Slave_RxReq);


#define     SPI_TRANS_DATA_LEN     32
uint32_t SPI_Master_Send_Data[SPI_TRANS_DATA_LEN];
uint32_t SPI_Master_Reci_Data[SPI_TRANS_DATA_LEN];
uint32_t SPI_Slave_Send_Data[SPI_TRANS_DATA_LEN];
uint32_t SPI_Slave_Reci_Data[SPI_TRANS_DATA_LEN];

unsigned int DMA_SPI_Master_Send_count = 0;
unsigned int DMA_SPI_Master_Reci_count = 0;
unsigned int DMA_SPI_Slave_Send_count = 0;
unsigned int DMA_SPI_Slave_Reci_count = 0;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint8_t loop = 0;
  GPIO_InitType GPIO_InitStructure;
  uint8_t txbuff0[8] = {0}, rxbuff0[8] = {0},  txbuff1[8] = {0}, rxbuff1[8] = {0}, err = 0;
  
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

  
  /* SPI33_2 clock */  
  SYSCFG0_FlexcommClockConfig(FLEXCOMM2, SYSCFG0_FC_CLKSRC_RCH, 1);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_FC2, ENABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Clock_FC2);
  SYSCFG0_FlexcommModeConfig(FLEXCOMM2, SYSCFG0_FC_SPI);
  
  /* SPI33_3 clock */  
  SYSCFG0_FlexcommClockConfig(FLEXCOMM3, SYSCFG0_FC_CLKSRC_RCH, 1);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_FC3, ENABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Clock_FC3);
  SYSCFG0_FlexcommModeConfig(FLEXCOMM3, SYSCFG0_FC_SPI_Slave);

  BSP_Printf_Init();
  
  printf("Hello World!\r\n");
  
  printf("SPI2 and SPI3 transform\r\n");
  
  /* Configure SPI 2 pin */
  GPIO_PinAFConfig(GPIOE,  GPIO_PinSource15, GPIO_AF4_FC2_SCK);//SCK
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11,  GPIO_AF4_FC2_TXD_SCL_MISO);//MISO
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10,  GPIO_AF4_FC2_RXD_SDA_MOSI);//MOSI
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource8,  GPIO_AF4_FC2_CTS_SDA_SSEL0);//CS

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
  GPIO_Init(GPIOH, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
  
  /* Configure SPI 3 pin */
  GPIO_PinAFConfig(GPIOA,  GPIO_PinSource5, GPIO_AF5_FC3_SCK);//SCK
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4,  GPIO_AF5_FC3_TXD_SCL_MISO);//MISO
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource5,  GPIO_AF5_FC3_RXD_SDA_MOSI);//MOSI
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4,  GPIO_AF5_FC3_CTS_SDA_SSEL0);//CS
  
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  SYSCFG0_FlexcommModeConfig(FLEXCOMM2, SYSCFG0_FC_SPI);
  SYSCFG0_FlexcommModeConfig(FLEXCOMM3, SYSCFG0_FC_SPI_Slave);
  
  /* transform data init */
  memset((void*)SPI_Master_Reci_Data, 0, sizeof(SPI_Master_Reci_Data));
  memset((void*)SPI_Slave_Reci_Data, 0, sizeof(SPI_Slave_Reci_Data));
  for(loop = 0; loop < SPI_TRANS_DATA_LEN; loop++)
  {
    SPI_Master_Send_Data[loop] = loop;
    SPI_Slave_Send_Data[loop] = loop+SPI_TRANS_DATA_LEN;
  }
  
  printf("Start SPI DMA transfer.\r\n");
  
  DMA_SPI_TX_RX(SPI2, SPI3, SYSCFG0_DMA_REQUEST_FC2_TX, SYSCFG0_DMA_REQUEST_FC2_RX, SYSCFG0_DMA_REQUEST_FC3_TX, SYSCFG0_DMA_REQUEST_FC3_RX);
  
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

void DMA_SPI_TX_RX(SPI_Type* Master_SPIx, SPI_Type* Slave_SPIx, uint32_t DMA_master_TxReq, uint32_t DMA_master_RxReq, uint32_t DMA_Slave_TxReq, uint32_t DMA_Slave_RxReq)
{  
  DMA_InitType  DMA_InitStructure;
  SPI_InitType SPI_InitTypeStruct;
  
  SPI_Cmd(Slave_SPIx,  DISABLE);
  SPI_Cmd(Master_SPIx, DISABLE);
  
  SPI_DeInit(Master_SPIx);
  SPI_DeInit(Slave_SPIx);

  SPI_StructInit(&SPI_InitTypeStruct);
  SPI_InitTypeStruct.SPI_SCLKDivider = 24;
  SPI_Init(Master_SPIx, &SPI_InitTypeStruct);
  SPI_Init(Slave_SPIx, &SPI_InitTypeStruct);
  
  
  SPI_DMACmd(Master_SPIx, SPI_DMA_TX | SPI_DMA_RX, ENABLE);
  SPI_DMACmd(Slave_SPIx, SPI_DMA_TX | SPI_DMA_RX, ENABLE);
  
  SPI_Cmd(Slave_SPIx, ENABLE);
  SPI_Cmd(Master_SPIx, ENABLE);
  SPI_SlaveSelectConfig(Slave_SPIx, SPI_SSEL0, ENABLE);
  SPI_SlaveSelectConfig(Master_SPIx, SPI_SSEL0, ENABLE);
  
  DMA_Cmd(DMA0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel1, DISABLE);
  DMA_ChannelCmd(DMA0_Channel2, DISABLE);
  DMA_ChannelCmd(DMA0_Channel3, DISABLE);
  
  DMA_ITConfig(DMA0_Channel0, DMA_INT_BLOCK, DISABLE);
  DMA_ITConfig(DMA0_Channel1, DMA_INT_BLOCK, DISABLE);
  DMA_ITConfig(DMA0_Channel2, DMA_INT_BLOCK, DISABLE);
  DMA_ITConfig(DMA0_Channel3, DMA_INT_BLOCK, DISABLE);
  
  DMA_DeInit(DMA0_Channel0);
  DMA_DeInit(DMA0_Channel1);
  DMA_DeInit(DMA0_Channel2);
  DMA_DeInit(DMA0_Channel3);
  
  /* CH0 -> SPI33_2 master TX */
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceAddress = (uint32_t) (&(SPI_Master_Send_Data[0]));
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (&(Master_SPIx->DR));
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_TransferSize = SPI_TRANS_DATA_LEN;
  DMA_InitStructure.DMA_DestinationRequestSelect = DMA_DestinationRequestSelect_0;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0, DMA_master_TxReq);
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
  

  /* CH1 -> SPI33_2 master RX */
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceAddress = (uint32_t)(&(Master_SPIx->DR));
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (&(SPI_Master_Reci_Data[0]));
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_TransferSize = SPI_TRANS_DATA_LEN;
  DMA_InitStructure.DMA_SourceRequestSelect = DMA_SourceRequestSelect_1;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ1, DMA_master_RxReq);
  DMA_Init(DMA0_Channel1, &DMA_InitStructure);
  
  /*CH2 -> SPI33_3 slave TX*/
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceAddress = (uint32_t) (&(SPI_Slave_Send_Data[0]));
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (&(Slave_SPIx->DR));
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_TransferSize = SPI_TRANS_DATA_LEN;
  DMA_InitStructure.DMA_DestinationRequestSelect = DMA_DestinationRequestSelect_2;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ2, DMA_Slave_TxReq);
  DMA_Init(DMA0_Channel2, &DMA_InitStructure);
  
  /*CH3 -> SPI33_3 slave RX*/
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceAddress = (uint32_t)(&(Slave_SPIx->DR));
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t) (&(SPI_Slave_Reci_Data[0]));
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_TransferSize = SPI_TRANS_DATA_LEN;
  DMA_InitStructure.DMA_SourceRequestSelect = DMA_SourceRequestSelect_3;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ3, DMA_Slave_RxReq);
  DMA_Init(DMA0_Channel3, &DMA_InitStructure);
  
  
  NVIC_EnableIRQ(DMA0_CH0_IRQn);
  NVIC_EnableIRQ(DMA0_CH1_IRQn);
  NVIC_EnableIRQ(DMA0_CH2_IRQn);
  NVIC_EnableIRQ(DMA0_CH3_IRQn);
  DMA_ITConfig(DMA0_Channel0, DMA_INT_BLOCK, ENABLE);
  DMA_ITConfig(DMA0_Channel1, DMA_INT_BLOCK, ENABLE);
  DMA_ITConfig(DMA0_Channel2, DMA_INT_BLOCK, ENABLE);
  DMA_ITConfig(DMA0_Channel3, DMA_INT_BLOCK, ENABLE);
  
  DMA_Cmd(DMA0, ENABLE);/* DMA_Cmd must config before DMA_ChannelCmd */
  DMA_ChannelCmd(DMA0_Channel2, ENABLE);/* slave dma must open before master */
  DMA_ChannelCmd(DMA0_Channel3, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel1, ENABLE);
  

  while((DMA_SPI_Master_Send_count = 0)||(DMA_SPI_Master_Reci_count == 0)||(DMA_SPI_Slave_Send_count == 0)||(DMA_SPI_Slave_Reci_count == 0))
  {
  }
  
  if((memcmp(SPI_Master_Send_Data, SPI_Slave_Reci_Data, SPI_TRANS_DATA_LEN) == 0)&&(memcmp(SPI_Slave_Send_Data, SPI_Master_Reci_Data, SPI_TRANS_DATA_LEN) == 0))
  {
    printf("pass!");
  }
  else
  {
    printf("fail!");
  }
}

/*********************************** END OF FILE ******************************/
