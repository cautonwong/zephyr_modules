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
#define EDAC_FreqDiv_256               (255)
#define EADC_CATTURE_POINT             (5)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EADC_InitType EADC_InitStructure;
DMA_InitType  DMA_InitStructure;
uint32_t EADC_Data[256*8];

uint32_t sinBuff[256] = 
{
    128,131,134,137,140,143,146,149,152,156,159,162,165,168,171,174,
    176,179,182,185,188,191,193,196,199,201,204,206,209,211,213,216,
    218,220,222,224,226,228,230,232,234,235,237,239,240,242,243,244,
    245,247,248,249,250,251,251,252,253,253,254,254,254,255,255,255,
    255,255,255,255,254,254,254,253,252,252,251,250,249,248,247,246,
    245,244,242,241,240,238,236,235,233,231,229,227,225,223,221,219,
    217,215,212,210,208,205,203,200,197,195,192,189,187,184,181,178,
    175,172,169,166,163,160,157,154,151,148,145,142,139,136,132,129,
    126,123,120,117,114,110,107,104,101, 98, 95, 92, 89, 86, 83, 80,
     77, 74, 72, 69, 66, 63, 61, 58, 55, 53, 50, 48, 45, 43, 41, 38,
     36, 34, 32, 30, 28, 26, 24, 22, 21, 19, 17, 16, 14, 13, 11, 10,
      9,  8,  7,  6,  5,  4,  3,  3,  2,  2,  1,  1,  0,  0,  0,  0,
      0,  0,  0,  1,  1,  1,  2,  2,  3,  4,  4,  5,  6,  7,  8,  9,
     11, 12, 13, 15, 16, 18, 19, 21, 23, 25, 26, 28, 30, 33, 35, 37,
     39, 41, 44, 46, 49, 51, 54, 56, 59, 61, 64, 67, 70, 72, 75, 78,
      81,84, 87, 90, 93, 96, 99, 102,105,108,111,115,118,121,124,127
};
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void SYSCON_Configuration(void);
void GPIO_Configuration(void);


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

  /* Configure the CM33/CM0 System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();

  SYSCON_Configuration();

  GPIO_Configuration();

  EADC_DeInit();

  EADC_StructInit(&EADC_InitStructure);
  EADC_InitStructure.EADC_ClkOutFreqDiv    = EADC_SYN_STEP_256;
  EADC_InitStructure.EADC_CdmaClkFreqDiv   = EADC_CDMA_CLK_DIV_8;
  EADC_InitStructure.EADC_CdmaMode         = EADC_CDMA_MODE_DISABLE;
  EADC_InitStructure.EADC_SeqSetsNum       = EADC_SEQ_SETS_NUM_16;
  EADC_InitStructure.EADC_SynStep          = EADC_SYN_STEP_1024;
  EADC_Init(&EADC_InitStructure);
  
  /* DMA configuration ------------------------------------------------------*/ 
  DMA_Cmd(DMA0, DISABLE);
  DMA_DeInit(DMA0_Channel0);
  
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_Mode                      = DMA_MODE_NORMAL; 
  DMA_InitStructure.DMA_DIR                       = DMA_DIR_Peripheral2Memory;
  DMA_InitStructure.DMA_SourceTransferWidth       = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationTransferWidth  = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_SourceAddressControl      = DMA_SourceAddressControl_Fixed;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_SourceRequestSelect       = DMA_SourceRequestSelect_0;
  DMA_InitStructure.DMA_DestinationRequestSelect  = DMA_DestinationRequestSelect_0;
  DMA_InitStructure.DMA_SourceAddress             = (uint32_t)&EADC->DR;
  DMA_InitStructure.DMA_DestinationAddress        = (uint32_t)&EADC_Data;
  DMA_InitStructure.DMA_TransferSize              = 256;
  DMA_InitStructure.DMA_Priority                  = DMA_Priority_0;
  
  SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0, SYSCFG0_DMA_REQUEST_EADC);

  DMA_Init(DMA0_Channel0, &DMA_InitStructure);  
  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);

  EADC_Channel_Config(EADC_CHANNEL_0, EADC_CATTURE_POINT, EADC_CP_TRIG_POS);
  EADC_Channel_Config(EADC_CHANNEL_1, EADC_CATTURE_POINT, EADC_CP_TRIG_POS);
  EADC_Channel_Config(EADC_CHANNEL_2, EADC_CATTURE_POINT, EADC_CP_TRIG_POS);
  EADC_Channel_Config(EADC_CHANNEL_3, EADC_CATTURE_POINT, EADC_CP_TRIG_POS);
  EADC_Channel_Config(EADC_CHANNEL_4, EADC_CATTURE_POINT, EADC_CP_TRIG_POS);
  EADC_Channel_Config(EADC_CHANNEL_5, EADC_CATTURE_POINT, EADC_CP_TRIG_POS);
  EADC_Channel_Config(EADC_CHANNEL_6, EADC_CATTURE_POINT, EADC_CP_TRIG_POS);
  EADC_Channel_Config(EADC_CHANNEL_7, EADC_CATTURE_POINT, EADC_CP_TRIG_POS);
  
  EADC_INTConfig(EADC_INT_OVF, ENABLE); 
  NVIC_EnableIRQ(EADC_IRQn);

  EADC_Cmd(EADC_CLK_IN, EADC_CHANNEL_0 | EADC_CHANNEL_1 | EADC_CHANNEL_3 | 
  EADC_CHANNEL_4 | EADC_CHANNEL_5 | EADC_CHANNEL_6 | EADC_CHANNEL_7, ENABLE); 
  
  printf("EADC clock in test\r\n");
  /* Infinite loop */
  while (1)
  {
    GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
    STD_Delay(2);
  }
}

/**
  * @brief  AHB and APB Clock Configuration
  *         The Clock is configured as follows :
  *            Select RCH as AHB and APB clock.
  *            Open XOH, select XOH as PLL0 source.
  *            config PLL0 frequency, open PLL0.
  *            Open XOL, select XOL as PLL1 source.
  *            config PLL1 frequency, open PLL1.
  *            Select PLL0 as HCLK0 and PCLK0 source.
  *            Set 1 to HCLK0 Divider.
  *            Set 1 to PCLK0 Divider.
  *            Select PLL0 as HCLK1 and PCLK1 source.
  *            Set 2 to HCLK1 Divider.
  *            Set 2 to PCLK1 Divider.
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
  CLK_InitStruct.AHBCLKDivider = 2U;
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
  
  /* PLL0(48M) enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_XOH | CLK_OSCILLATORTYPE_XOL;
  CLK_OscInitStruct.XOHState = CLK_XOH_ON;
  CLK_OscInitStruct.XOLState = CLK_XOL_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_XOH;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKN0;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKN1;
  CLK_OscInitStruct.PLL0.PLL0_M      = pll0_config[CLK_PLL0_IN_12M_OUT_128M].CLKM;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_ON;
  CLK_OscInitStruct.PLL1.PLL1_Source = CLK_PLL1SOURCE_XOH_12M;
  CLK_OscInitStruct.PLL1.PLL1_Frequency = CLK_PLL1_IN_12M_OUT_144M;
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
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void SYSCON_Configuration(void)
{
  /* EADC CLK = RCH/4 */
  SYSCFG0_EADCClockConfig(SYSCFG0_EADC_CLKSRC_RCH, 4);

  /* Enable EADC clocks */
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_EADC, ENABLE);

  /* Enable DMA clocks */
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure;
  
  /*Configure EADC Ch0 PF13 pin,Ch1 PF14 pin,Ch2 PF15 pin*/
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF10_EADC_D0);
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF10_EADC_D1);
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF10_EADC_D2);
  /* Configure PF13 PF14 PF15 as alternate input */  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  /*Configure EADC Ch3 PG0 pin,Ch4 PG1 pin*/
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource0, GPIO_AF10_EADC_D3);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource1, GPIO_AF10_EADC_D4);
  /* Configure PG0 PG1 as alternate input */ 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  
  /*Configure EADC Ch5 PE7 pin,Ch6 PE8 pin,Ch7 PE9 pin*/
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF10_EADC_D5);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF10_EADC_D6);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF10_EADC_D7);
  /* Configure PE7 PE8 PE9 as alternate input */  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  /*Configure EADC clock in PF12 pin*/
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF10_EADC_CLK);  // CLK
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  /* Configure F12 as alternate input */  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  /* Configure B10 as output for EADC clock in*/  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
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
