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
int main(void)
{
  DMA_InitType  DMA_InitStructure;
  uint32_t tx_buff[128] = {0};
  uint32_t rx_buff[128] = {0};
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
  
	/* Configures print UART(UART7) to 115200 baudrate. */
  BSP_Printf_Init();
	
  for (i = 0; i < 128; i++)
  {
    tx_buff[i] = i+1;
    rx_buff[i] = 0;
  }
  /* DMA configuration ------------------------------------------------------*/ 
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);
  
  DMA_Cmd(DMA0, DISABLE);
  DMA_DeInit(DMA0_Channel0);

  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_SourceAddress = (uint32_t)tx_buff;
  DMA_InitStructure.DMA_DestinationAddress = (uint32_t)rx_buff;
  DMA_InitStructure.DMA_SourceAddressControl = DMA_SourceAddressControl_Increment;
  DMA_InitStructure.DMA_DestinationAddressControl = DMA_DestinationAddressControl_Increment;
  DMA_InitStructure.DMA_DIR = DMA_DIR_Memory2Memory;
  DMA_InitStructure.DMA_DestinationTransferWidth = DMA_DestinationTransferWidth_32Bit;
  DMA_InitStructure.DMA_SourceTransferWidth = DMA_SourceTransferWidth_32Bit;
  DMA_InitStructure.DMA_DestinationBurstSize = DMA_DestinationBurstSize_1;
  DMA_InitStructure.DMA_SourceBurstSize = DMA_SourceBurstSize_1;
  DMA_InitStructure.DMA_SourceRequestSelect = DMA_SourceRequestSelect_0;
  DMA_InitStructure.DMA_DestinationRequestSelect = DMA_DestinationRequestSelect_0;
  DMA_InitStructure.DMA_TransferSize = 128;
  
  DMA_Init(DMA0_Channel0, &DMA_InitStructure);
  
  DMA_Cmd(DMA0, ENABLE);
  DMA_ChannelCmd(DMA0_Channel0, ENABLE);
  
  while(DMA_GetITtatus(DMA0_Channel0, DMA_INT_TFR) == RESET);
  
  for(i = 0; i<128; i++)
  {
    if(tx_buff[i] != rx_buff[i])
    {
      printf("DMA_CM33 Memory2Memory transfer err, i = %d, tx_buff[%d] = 0x%x, rx_buff[%d] = 0x%x\r\n" \
      , i, i, tx_buff[i], i, rx_buff[i]);
      err = 1;
    }
  }
  if(err == 0)
  {
    printf("DMA_CM33 Normal Mode Memory2Memory transfer succeed!\r\n");
  }
  else
  {
    printf("DMA_CM33 Normal Mode Memory2Memory transfer failed!\r\n");
  }
  while(1)
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
