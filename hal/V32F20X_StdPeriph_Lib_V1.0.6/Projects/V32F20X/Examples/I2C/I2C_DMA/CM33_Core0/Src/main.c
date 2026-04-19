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

uint8_t txbuff0[8] = {0};
uint8_t rxbuff0[8] = {0};
uint8_t txbuff1[8] = {0};
uint8_t rxbuff1[8] = {0};
void DMA_I2C_TX_RX(I2C_Type* Master_I2Cx, I2C_Type* Slave_I2Cx, uint32_t DMA_master_TxReq, \
  uint32_t DMA_master_RxReq, uint32_t DMA_Slave_RxReq);




static void SystemClock_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0;
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
  
  BSP_Printf_Init();
  
  printf("Hello World!\r\n");
  
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11,  GPIO_AF4_FC2_RTS_SCL_SSEL1);//SCL
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10,  GPIO_AF4_FC2_CTS_SDA_SSEL0);//SDA
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOH, &GPIO_InitStructure);  
  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4,  GPIO_AF5_FC3_TXD_SCL_MISO);//SCL
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource5,  GPIO_AF5_FC3_CTS_SDA_SSEL0);//SDA
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOB, &GPIO_InitStructure);    
  
  SYSCFG0_FlexcommClockConfig(FLEXCOMM3, SYSCFG0_FC_CLKSRC_RCH, 1);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_FC3, ENABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_FC3);
  SYSCFG0_FlexcommClockConfig(FLEXCOMM2, SYSCFG0_FC_CLKSRC_RCH, 1);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_FC2, ENABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_FC2);
  
  SYSCFG0_FlexcommModeConfig(FLEXCOMM2, SYSCFG0_FC_I2C);
  SYSCFG0_FlexcommModeConfig(FLEXCOMM3, SYSCFG0_FC_I2C);

  printf("Start I2C DMA transmit\r\n");
  for(i = 0; i< 500;i++)
  {
    __NOP();
  }
  DMA_I2C_TX_RX(I2C2, I2C3, SYSCFG0_DMA_REQUEST_FC2_TX, SYSCFG0_DMA_REQUEST_FC2_RX, SYSCFG0_DMA_REQUEST_FC3_RX);
  
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

void DMA_I2C_TX_RX(I2C_Type* Master_I2Cx, I2C_Type* Slave_I2Cx, uint32_t DMA_master_TxReq, uint32_t DMA_master_RxReq, uint32_t DMA_Slave_RxReq)
{
  uint32_t i = 0, err = 0;
  
  DMA_InitType  DMA_InitStructure;
  I2C_InitType  I2C_InitStruct;
  
  for(i = 0; i<8; i++)
  {
    txbuff0[i] = i + 10;
    rxbuff0[i] = 0;
    txbuff1[i] = i + 5;
    rxbuff1[i] = 0;
  }
  
  I2C_Cmd(Slave_I2Cx,  DISABLE);
  I2C_Cmd(Master_I2Cx, DISABLE);

  I2C_Cmd(Master_I2Cx, DISABLE);
  I2C_Cmd(Slave_I2Cx, DISABLE);
  I2C_INTConfig(Slave_I2Cx, I2C_INT_RD_REQ, DISABLE);
  NVIC_DisableIRQ(FLEXCOMM3_IRQn);
  
  /*- Device Init ----------------------------------*/
  I2C_DeInit(Slave_I2Cx);
  I2C_DeInit(Master_I2Cx);

  /*- I2C Configuration ----------------------------*/
  I2C_StructInit(&I2C_InitStruct);
  I2C_InitStruct.Mode = I2C_MODE_MASTER;
  I2C_InitStruct.SlaveAddress = 0x50;
  I2C_InitStruct.OwnAddress   = (0xA0 >> 1);
  I2C_InitStruct.Restart = I2C_RESTART_ENABLE;
  I2C_Init(Master_I2Cx, &I2C_InitStruct);
  
  I2C_StructInit(&I2C_InitStruct);
  I2C_InitStruct.Mode = I2C_MODE_SLAVE;
  I2C_InitStruct.OwnAddress = (0x50 >> 1);
  I2C_Init(Slave_I2Cx, &I2C_InitStruct);
 
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel1, DISABLE);
  DMA_ChannelCmd(DMA0_Channel2, DISABLE);
  DMA_Cmd(DMA0, DISABLE);
  
  DMA_DeInit(DMA0_Channel0);
  DMA_DeInit(DMA0_Channel1);
  DMA_DeInit(DMA0_Channel2);
  
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize           = DMA_SourceBurstSize_4;
  DMA_InitStructure.DMA_DestinationBurstSize      = DMA_DestinationBurstSize_4;
  DMA_InitStructure.DMA_SourceTransferWidth       = DMA_SourceTransferWidth_8Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth  = DMA_DestinationTransferWidth_8Bit;
  DMA_InitStructure.DMA_DestinationAddress        = (uint32_t) (&Master_I2Cx -> DATACMD);
  DMA_InitStructure.DMA_SourceAddress             = (uint32_t) (txbuff0);
  DMA_InitStructure.DMA_SourceAddressControl      = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_DIR                       = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_TransferSize              = 4;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0, DMA_master_TxReq);
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
  
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize           = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_DestinationBurstSize      = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_SourceTransferWidth       = DMA_SourceTransferWidth_8Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth  = DMA_DestinationTransferWidth_8Bit;
  DMA_InitStructure.DMA_SourceAddress             = (uint32_t) (&Slave_I2Cx -> DATACMD);
  DMA_InitStructure.DMA_DestinationAddress        = (uint32_t) (rxbuff1);
  DMA_InitStructure.DMA_SourceAddressControl      = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_DIR                       = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_SourceRequestSelect       = DMA_SourceRequestSelect_1;
  DMA_InitStructure.DMA_TransferSize              = 8;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ1, DMA_Slave_RxReq);
  DMA_Init(DMA0_Channel1, &DMA_InitStructure);
  
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceBurstSize           = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_DestinationBurstSize      = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_SourceTransferWidth       = DMA_SourceTransferWidth_8Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth  = DMA_DestinationTransferWidth_8Bit;
  DMA_InitStructure.DMA_SourceAddress             = (uint32_t) (&Master_I2Cx -> DATACMD);
  DMA_InitStructure.DMA_DestinationAddress        = (uint32_t) (rxbuff0);
  DMA_InitStructure.DMA_SourceAddressControl      = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_DIR                       = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_SourceRequestSelect       = DMA_SourceRequestSelect_2;
  DMA_InitStructure.DMA_TransferSize              = 8;
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ2, DMA_master_RxReq);
  DMA_Init(DMA0_Channel2, &DMA_InitStructure);
  
  I2C_DMACmd(Master_I2Cx, I2C_DMA_TX | I2C_DMA_RX, ENABLE);
  I2C_DMACmd(Slave_I2Cx, I2C_DMA_RX, ENABLE);
  I2C_DMA_TxFIFOLevelConfig(Master_I2Cx, I2C_TXFLEV_4);
  I2C_DMA_RxFIFOLevelConfig(Slave_I2Cx, I2C_RXFLEV_0);
  I2C_DMA_RxFIFOLevelConfig(Master_I2Cx, I2C_RXFLEV_0);

  I2C_INTConfig(Slave_I2Cx, I2C_INT_RD_REQ, ENABLE);
  NVIC_EnableIRQ(FLEXCOMM3_IRQn);
  
  I2C_Cmd(Slave_I2Cx, ENABLE);
  I2C_Cmd(Master_I2Cx, ENABLE);
 
  printf("i2c test begine\r\n");

  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel1, ENABLE);
  DMA_ChannelCmd(DMA0_Channel2, ENABLE);
  
  while(DMA_GetITtatus(DMA0_Channel0, DMA_INT_TFR) == RESET);
  DMA_ClearITStatus(DMA0_Channel0, DMA_INT_TFR);
  
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_WRITE, txbuff0[4]);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_WRITE, txbuff0[5]);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_WRITE, txbuff0[6]);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_WRITE_STOP, txbuff0[7]);
  
  while(DMA_GetITtatus(DMA0_Channel1, DMA_INT_TFR) == RESET);
  DMA_ClearITStatus(DMA0_Channel1, DMA_INT_TFR);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel1, DISABLE);
  
  while(I2C_GetFlag(Master_I2Cx, I2C_FLAG_ACTIVE) == SET);
  while(I2C_GetFlag(Slave_I2Cx, I2C_FLAG_ACTIVE) == SET);
  
  for(i = 0; i< 500;i++)
  {
    __NOP();
  }
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_READ_RESTART, 0x00);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_READ, 0x00);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_READ, 0x00);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_READ, 0x00);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_READ, 0x00);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_READ, 0x00);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_READ, 0x00);
  I2C_SendCmdDataFrame(Master_I2Cx, I2C_CMD_READ_STOP, 0x00);
  
  while(DMA_GetITtatus(DMA0_Channel2, DMA_INT_TFR) == RESET);
  DMA_ClearITStatus(DMA0_Channel2, DMA_INT_TFR);
  DMA_ChannelCmd(DMA0_Channel2, DISABLE);
  DMA_Cmd(DMA0, DISABLE);

  while(I2C_GetFlag(Master_I2Cx, I2C_FLAG_ACTIVE) == SET);
  while(I2C_GetFlag(Slave_I2Cx, I2C_FLAG_ACTIVE) == SET);
  
  I2C_Cmd(I2C2, DISABLE);
  I2C_Cmd(I2C3, DISABLE);
  
  for(i = 0; i<8; i++)
  {
    if(txbuff0[i] != rxbuff1[i])
    {
      err = 1;
    }
    if(txbuff1[i] != rxbuff0[i])
    {
      err = 1;
    }
  }
  if(err == 0)
  {
    printf("pass\r\n");
  }
  else
  {
    printf("fail\r\n");
  }
}

/*********************************** END OF FILE ******************************/
