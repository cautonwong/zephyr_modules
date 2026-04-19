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

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	
uint8_t source[128] = {0};
uint8_t dest0[128] = {0};
uint8_t dest1[128] = {0};
extern unsigned char DMA_COUNT;

int main(void)
{
  DMA_InitType DMA_InitStructure;
  DMA_LinkListType DMA_LLP[2];
  DMA_LinkListInfoType DMA_LinkListInfo;
  uint32_t i=0, err = 0;
  
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
  
	SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_DMA0);
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
  
  /* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();
  printf("hello word\r\n");
  
  for(i = 0; i < 128; i++)
  {
    source[i] = i+1;
    dest0[i]  = 0;
    dest1[i]  = 0;
  }
  

  DMA_Cmd(DMA0, DISABLE);
  DMA_ChannelCmd(DMA0_Channel0, DISABLE);
  DMA_DeInit(DMA0_Channel0);

  DMA_StructInit(&DMA_InitStructure);
  DMA_LinkListInfo.DMA_SourceAddress = (uint32_t)source;
  DMA_LinkListInfo.DMA_DestinationAddress = (uint32_t)dest0;
  DMA_LinkListInfo.DMA_NextLLPAddr = (uint32_t)&DMA_LLP[1];
  DMA_LinkListInfo.DMA_TransferSize = 32;
  DMA_LinkListInfo.DMA_DIR = DMA_DIR_Memory2Memory;
  DMA_LinkListInfo.DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_LinkListInfo.DMA_DestinationBurstSize = DMA_DestinationBurstSize_1;
  DMA_LinkListInfo.DMA_SourceTransferWidth = DMA_SourceTransferWidth_8Bit;
  DMA_LinkListInfo.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_8Bit;
  DMA_LinkListInfo.DMA_SourceAddressControl = DMA_SourceAddressControl_Fixed;
  DMA_LinkListInfo.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_LinkListInit(&DMA_LLP[0], &DMA_LinkListInfo);
  
  DMA_LinkListInfo.DMA_SourceAddress = (uint32_t)source;
  DMA_LinkListInfo.DMA_DestinationAddress = (uint32_t)dest1;
	DMA_LinkListInfo.DMA_NextLLPAddr = (uint32_t)&DMA_LLP[0];
  DMA_LinkListInfo.DMA_TransferSize = 32;
  DMA_LinkListInfo.DMA_DIR = DMA_DIR_Memory2Memory;
  DMA_LinkListInfo.DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_LinkListInfo.DMA_DestinationBurstSize = DMA_DestinationBurstSize_1;
  DMA_LinkListInfo.DMA_SourceTransferWidth = DMA_SourceTransferWidth_8Bit;
  DMA_LinkListInfo.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_8Bit;
  DMA_LinkListInfo.DMA_SourceAddressControl = DMA_SourceAddressControl_Fixed;
  DMA_LinkListInfo.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_LinkListInit(&DMA_LLP[1], &DMA_LinkListInfo);
   
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_DIR  = DMA_DIR_Memory2Memory;
  DMA_InitStructure.DMA_Mode = DMA_MODE_LINK_LIST;
  DMA_InitStructure.DMA_LinkListAddress = (uint32_t)&DMA_LLP[0];
  DMA_InitStructure.DMA_TransferSize = 32;
	SYSCFG0_DMARequestConfig(SYSCFG0_DMA0_REQ0, SYSCFG0_DMA_REQUEST_SOFTWARE);
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);

	NVIC_EnableIRQ(DMA0_CH0_IRQn);
  DMA_ITConfig(DMA0_Channel0, DMA_INT_BLOCK, ENABLE);

  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);
	
  while (DMA_COUNT <=50)
  {}
  printf("DMA link list memory to memory test\r\n");
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
  CLK_InitType CLK_InitStruct = {0};
  
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
