/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
/* Private functions ---------------------------------------------------------*/

#define BUFFER_SIZE (16UL)

static const uint32_t SrcBuffer[BUFFER_SIZE] = 
{
  0x00000000, 0x11111111, 0x22222222, 0x33333333,
  0x44444444, 0x55555555, 0x66666666, 0x77777777,
  0x88888888, 0x99999999, 0xAAAAAAAA, 0xBBBBBBBB,
  0xCCCCCCCC, 0xDDDDDDDD, 0xEEEEEEEE, 0xFFFFFFFF
};

static uint32_t DstBuffer[BUFFER_SIZE] = { 0 };

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  BDMA_InitType DMA_InitStruct;
  
  /* V32F20xxx CM0 core STD library initialization:
       - HCLK 48 MHz
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Low Level Initialization
     */
  STD_Init(48000000UL);
  BSP_Printf_Init();
  
  BSP_Printf_Init();
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  
  /* BDMA channel0 configuration */
  BDMA_DeInit(BDMA_CHANNEL_0);
  BDMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.SrcAddr = (uint32_t)&SrcBuffer[0];
  DMA_InitStruct.SrcAddrMode = BDMA_SRCADDRMODE_FEND;
  DMA_InitStruct.DestAddr = (uint32_t)&DstBuffer[0];
  DMA_InitStruct.DestAddrMode = BDMA_DESTADDRMODE_FEND;
  DMA_InitStruct.FrameLen = 1 - 1;
  DMA_InitStruct.PackLen = 16 - 1;
  DMA_InitStruct.TransSize = BDMA_TRANSSIZE_WORD;
  DMA_InitStruct.ReqSrc = BDMA_REQSRC_SOFT;
  DMA_InitStruct.ContMode = BDMA_CONTMODE_DISABLE;
  DMA_InitStruct.TransMode = BDMA_TRANSMODE_SINGLE;
  BDMA_Init(&DMA_InitStruct, BDMA_CHANNEL_0);
  
  /* Enable BDMA channel0 */
  BDMA_Cmd(BDMA_CHANNEL_0, ENABLE);
  
  /* Wait until BDMA channel0 idle */
  while (SET == BDMA_GetFlagStatus(BDMA_FLAG_C0BUSY))
  {
  }
  
  if (0 == memcmp(SrcBuffer, DstBuffer, 4*BUFFER_SIZE))
  {
    /* Handler code, a transfer is correctly completed */
    BSP_LED_On(LED1);
    printf("DMA result is expected\r\n");
  }
  else
  {
    /* Handler code, a transfer error is detected */
    BSP_LED_On(LED2);
    printf("DMA result is not expected\r\n");
  }
  
  while (1)
  {
    ;
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
