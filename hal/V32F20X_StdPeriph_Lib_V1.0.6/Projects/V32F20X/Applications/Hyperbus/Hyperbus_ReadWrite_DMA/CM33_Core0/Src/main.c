/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hyperbus_psram.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

uint8_t tx_buff[64] __attribute__((aligned(4))) = {0};
uint32_t rx_buff[16] __attribute__((aligned(4))) = {0};

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0, err = 0;

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

  /* Configure DMA0 clock */
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_DMA0, ENABLE);

  BSP_Printf_Init();
  
  STD_Delay(5000);
  
  /* PSRAM IO INIT */
  HyperbusPSRAM_InitHyperbus(TEST_OSPI);
  HyperbusPSRAM_HardWareResetPSRAM();

  printf("Write 64 Bytes...\r\n");
  for(i = 0; i<64; i++)
  {
    tx_buff[i] = i;
  }
  
  printf("Write 64 bytes into PSRAM...\r\n");
  if(TEST_OSPI == OSPI0)
  {
    HyperbusPSRAM_WritePSRAM(TEST_OSPI, tx_buff, 0x60000010, 64);
  }
  else
  {
    HyperbusPSRAM_WritePSRAM(TEST_OSPI, tx_buff, 0x64000010, 64);
  }

  printf("Read 64 bytes from PSRAM...\r\n");
  if(TEST_OSPI == OSPI0)
  {
    HyperbusPSRAM_ReadPSRAM(TEST_OSPI, rx_buff, 0x60000010, 64);
  }
  else
  {
    HyperbusPSRAM_ReadPSRAM(TEST_OSPI, rx_buff, 0x64000010, 64);
  }
  printf("Perform data comparison...\r\n");
  
  for(i = 0; i < 64; i = i+4)
  {
    if(rx_buff[i/4] != *(uint32_t*)(tx_buff + i))
    {
      printf("Psram read and write err!, rxbuff[%d] = 0x%08x; txbuff[%d] = 0x%08x\r\n",\
      i/4, rx_buff[i/4], i/4, *(uint32_t*)(tx_buff + i));
      err++;
    }
  }
  if(err == 0)
  {
    printf("passed\r\n");
  }
  else
  {
    printf("failed\r\n");
  }  
  
  while(1)
  {

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
