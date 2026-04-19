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

#define     SPI_TRANS_DATA_LEN     32
uint32_t SPI_Master_Send_Data[SPI_TRANS_DATA_LEN];
uint32_t SPI_Slave_Reci_Data[SPI_TRANS_DATA_LEN];

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint8_t loop = 0;
  GPIO_InitType GPIO_InitStructure;
  SPI_InitType SPI_InitTypeStruct;
  
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
  
  printf("SPI2 send data to SPI3\r\n");
  
  /* Configure SPI 2 pin */
  GPIO_PinAFConfig(GPIOE,  GPIO_PinSource15, GPIO_AF4_FC2_SCK);//SCK
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11,  GPIO_AF4_FC2_TXD_SCL_MISO);//MISO
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10,  GPIO_AF4_FC2_RXD_SDA_MOSI);//MOSI
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource7,  GPIO_AF4_FC2_RTS_SCL_SSEL1);//CS   SSEL1

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

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
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
  
  /* transform data init */
  memset((void*)SPI_Slave_Reci_Data, 0, sizeof(SPI_Slave_Reci_Data));
  for(loop = 0; loop < SPI_TRANS_DATA_LEN; loop++)
  {
    SPI_Master_Send_Data[loop] = loop;
  }
  
  SPI_Cmd(SPI2, DISABLE);
  SPI_Cmd(SPI3, DISABLE);
  
  SPI_DeInit(SPI2);
  SPI_DeInit(SPI3);

  SPI_StructInit(&SPI_InitTypeStruct);
  SPI_InitTypeStruct.SPI_SCLKDivider = 24;
  SPI_Init(SPI2, &SPI_InitTypeStruct);
  SPI_Init(SPI3, &SPI_InitTypeStruct);
  
  
  SPI_Cmd(SPI2, ENABLE);
  SPI_Cmd(SPI3, ENABLE);
  SPI_SlaveSelectConfig(SPI2, SPI_SSEL1, ENABLE);
  SPI_SlaveSelectConfig(SPI3, SPI_SSEL0, ENABLE);
  
  printf("Start spi polling.\r\n");
  
  /* clear flag */
  while(SPI_GetFlagStatus(SPI2, SPI_FLAG_STATUS_TFE) == RESET)
  {
  }
  while(SPI_GetFlagStatus(SPI3, SPI_FLAG_STATUS_RFNE) == SET)
  {
    SPI_ReceiveData(SPI3);
  }
  
  /* master send data and slave recieve data */
  for(loop = 0; loop < SPI_TRANS_DATA_LEN; loop++)
  {
    SPI_SendData(SPI2, SPI_Master_Send_Data[loop]);
    while(SPI_GetFlagStatus(SPI3, SPI_FLAG_STATUS_RFNE) == RESET)
    {
    }
    SPI_Slave_Reci_Data[loop] = SPI_ReceiveData(SPI3);
  }
  
  if(memcmp(SPI_Master_Send_Data, SPI_Slave_Reci_Data, SPI_TRANS_DATA_LEN) == 0)
  {
    printf("pass!");
  }
  else
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
