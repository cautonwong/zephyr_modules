/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*  Audio Freq = PLL1    / I2S_CLKDIV / (bits in single channel * left and rigth channel)
    48K        = 245.76M / 160        / (16                     * 2)
  */
#define I2S_FS_48K

#ifdef I2S_FS_48K
 #define PLAY_I2S_CLKDIV               (160) /* PLL1 245.76M / 160 */
 #define PLAY_I2S_MCKDIV               (20)  /* PLL1 245.76M / 20 */
#endif /* I2S_FS_48K */

uint16_t i2s_data[8] = 
{ 
  0x1111, 0x2222, 0x3333, 0x4444,
  0x5555, 0x6666, 0x7777, 0x8888,
};

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static STD_StatusType PLL_I2S_Config(void);
static void I2S0_DMA_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  STD_StatusType ret;
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
  BSP_Printf_Init();
  
  /* Configure the CM33/CM0 System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  
  /* Configure PLL1 for I2S clock */
  ret = PLL_I2S_Config();
  if (STD_OK != ret)
  {
    Error_Handler();
  }
  
  /* I2S0, DMA configuration */
  I2S0_DMA_Config();
  
  /* Enable the I2S0 DMA Stream*/
  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);
  
  /* Enable the I2S DMA request */
  I2S_DMACmd(PLAY_I2S, I2S_DMA_TX, ENABLE);
  
  /* Enable the I2S0 */
  I2S_Cmd(PLAY_I2S, ENABLE);
  
  printf("I2S DMA init success\r\n");
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
  CLK_InitStruct.AHBCLKSource  = CLK_AHBCLKSOURCE_RCH;
  CLK_InitStruct.AHBCLKDivider = 1U;
  CLK_InitStruct.APBCLKSource  = CLK_APBCLKSOURCE_RCH;
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
  * @brief  Configure PLL1 for I2S0 clock.
  * @param  None
  * @retval None
  */
STD_StatusType PLL_I2S_Config(void)
{
  CLK_OscInitType CLK_OscInitStruct;
  
  CLK_OscInitStruct.OscillatorType      = CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOLState            = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State     = CLK_PLL0_NONE;
  CLK_OscInitStruct.PLL1.PLL1_State     = CLK_PLL1_ON;
  CLK_OscInitStruct.PLL1.PLL1_Source    = CLK_PLL1SOURCE_XOL_32768;
  CLK_OscInitStruct.PLL1.PLL1_Frequency = CLK_PLL1_IN_32768_OUT_245_76M;
  return (CLK_OscConfig(&CLK_OscInitStruct));
}

/**
  * @brief  Configure I2S0 DMA
  * @param  None
  * @retval None
  */
void I2S0_DMA_Config(void)
{
  I2S_InitType I2S_InitStructure;
  DMA_InitType DMA_InitStructure;
  
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_I2S0, ENABLE);
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
  
  /* Disable FC4, enable I2S0 pins' function */
  SYSCFG0_FlexcommModeConfig(FLEXCOMM4, SYSCFG0_FC_None);
  SYSCFG0_I2SPinsCmd(PLAY_I2S, ENABLE);
  
  /* I2S clock configuration */
  SYSCFG0_I2SClockConfig(PLAY_I2S, \
                         SYSCFG0_I2S_CLKSRC_PLL1, \
                         PLAY_I2S_CLKDIV);
  
  /* I2S Master clock configuration */
  SYSCFG0_I2SMasterClockConfig(PLAY_I2S, \
                               PLAY_I2S_MCKDIV, \
                               ENABLE);
  
  /* Reset I2S */
  PLAY_I2S_PERH_RESET();
  
  /* PLAY_I2S peripheral configuration */
  I2S_DeInit(PLAY_I2S);
  /* Tx mode */
  I2S_InitStructure.I2S_TransferMode = I2S_TransferMode_TX;
  /* Data format: 16B data with no extended bits */
  I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16B;
  /* Initialize the I2S peripheral with the structure above */
  I2S_Init(PLAY_I2S, &I2S_InitStructure);
  
  /* No clock gating for SCK */
  I2S_SCKGateConfig(PLAY_I2S, I2S_SCKGATE_NONE);
  
  /* Configure DMA I2S request */
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0, PLAY_I2S_DMA_REQ);
  
  /* Set the parameters to be configured */
  DMA_DeInit(DMA0_Channel0);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceAddress = (uint32_t)&i2s_data[0];
  DMA_InitStructure.DMA_DestinationAddress = PLAY_I2S_ADDRESS;
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Fixed;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Memory2Peripheral;
  DMA_InitStructure.DMA_TransferSize = (uint32_t)8;
  DMA_InitStructure.DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_16Bit;
  DMA_InitStructure.DMA_DestinationBurstSize = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_16Bit;
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
}

/**
  * @brief  Initialize the Low level.
  * @retval None
  */
void STD_lowInit(void)
{
  GPIO_InitType GPIO_InitStructure;
  
  GPIO_PinAFConfig(PLAY_I2S_WS_GPIO, PLAY_I2S_WS_PINSRC, GPIO_AF5_I2S0_WS);
  GPIO_PinAFConfig(PLAY_I2S_SCK_GPIO, PLAY_I2S_CLK_PINSRC, GPIO_AF5_I2S0_SCK);
  GPIO_PinAFConfig(PLAY_I2S_SD_GPIO, PLAY_I2S_SD_PINSRC, GPIO_AF5_I2S0_SD);
  GPIO_PinAFConfig(PLAY_I2S_MCK_GPIO, PLAY_I2S_MCK_PINSRC, GPIO_AF5_I2S0_MCK);
  
  /* Configure pins as AF pushpull */
  GPIO_InitStructure.GPIO_Pin = PLAY_I2S_MCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PLAY_I2S_MCK_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = PLAY_I2S_WS_PIN;
  GPIO_Init(PLAY_I2S_WS_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = PLAY_I2S_CLK_PIN;
  GPIO_Init(PLAY_I2S_SCK_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = PLAY_I2S_SD_PIN;
  GPIO_Init(PLAY_I2S_SD_GPIO, &GPIO_InitStructure);
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
