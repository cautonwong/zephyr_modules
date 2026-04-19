/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lib_hfm.h"
#include "lib_bspi.h"
#include <string.h>

uint8_t DSPFlag = 0;
uint32_t DMA1flag_framend = 0,DMA1flag_framend1 = 0,T2Fflag = 0;
/* Private functions ---------------------------------------------------------*/

void SPIInit(void)
{
  BSPI_InitType SPI_InitStruct;
  GPIO_InitType GPIO_InitStructure;
  
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_BSPI0|SYSCFG1_Periph1Clock_BSPI1,ENABLE);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF14_BSPI0_MOSI);   //MOSI
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF14_BSPI0_CK);   //CK
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF14_BSPI0_CS);   //CS
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF14_BSPI0_MISO);   //MISO
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_8|GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF14_BSPI1_CK);    //sck
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF14_BSPI1_CS);   //CS
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF14_BSPI1_MISO);   //MISO
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF14_BSPI1_MOSI);   //MOSI

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* SPI initialization, master mode */
  BSPI_DeviceInit(BSPI0);
  BSPI_DeviceInit(BSPI1);
  
  SPI_InitStruct.ClockDivision = SPI_CLKDIV_2;
  SPI_InitStruct.Mode = SPI_MODE_MASTER;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_DISABLE;
  SPI_InitStruct.SPH = SPI_SPH_0;
  SPI_InitStruct.SPO = SPI_SPO_0;
  SPI_InitStruct.SWAP = SPI_SWAP_DISABLE;
  BSPI_Init(BSPI1, &SPI_InitStruct);
  
  /*Enable SPI3*/
  BSPI_TransmitFIFOLevelConfig(BSPI1, SPI_TXFLEV_0);
  BSPI_Cmd(BSPI1, ENABLE);
  
  /*Enable SPI0*/ 
  SPI_InitStruct.Mode = SPI_MODE_SLAVE;
  BSPI_Init(BSPI0, &SPI_InitStruct);
  
  BSPI_TransmitFIFOLevelConfig(BSPI0, SPI_RXFLEV_0);
  BSPI_Cmd(BSPI0, ENABLE);

}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  WAVER_InitType WAVER_InitStruct;
  HFM_InitType HFM_InitStructure;
  BDMA_InitType DMA_InitStructRx;

  /* V32F20xxx CM0 core STD library initialization:
       - HCLK 48 MHz, be configured be CM33 core0
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Low Level Initialization
     */
  STD_Init(48000000UL);
  BSP_Printf_Init();
  
  memset((void*)RxBuf,0,RXBufLength);
  memset((void*)RxBuf1,0,RXBuf1Length);
  DMA1flag_framend = 0;
  DSPFlag= 0;
  
  SPIInit(); 
  SYSCFG1_Periph0ClockCmd(SYSCFG1_Periph0Clock_WAVER,ENABLE);
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_WAVER);
  WAVER_StructInit(&WAVER_InitStruct);
  WAVER_InitStruct.Mode = WAVER_MODE_U_IA_IB;
  WAVER_InitStruct.SampleLength = WAVER_SAMPLELEN_256;
  WAVER_InitStruct.CICRateSEL = WAVER_CIC_128;
  WAVER_InitStruct.COMPSEL = WAVER_COMP_DISABLE;
  WAVER_InitStruct.UploadSEL = WAVER_UPLOAD_DISABLE;
  WAVER_InitStruct.UploadEndianSEL = WAVER_UPLOAD_LITTLE_ENDIAN;
  WAVER_InitStruct.BackupSEL = WAVER_BACKUP_DISABLE;
  WAVER_Init(&WAVER_InitStruct);
  
  BDMA_DeInit(BDMA_CHANNEL_1);
  DMA_InitStructRx.SrcAddr = (uint32_t)&WAVER0->DATA;
  DMA_InitStructRx.DestAddr = RxBuf;
  DMA_InitStructRx.FrameLen = 128 - 1;
  DMA_InitStructRx.PackLen = 3 - 1;
  DMA_InitStructRx.ContMode = BDMA_CONTMODE_ENABLE;
  DMA_InitStructRx.TransMode = BDMA_TRANSMODE_PACK;
  DMA_InitStructRx.ReqSrc = BDMA_REQSRC_WAVER0;
  DMA_InitStructRx.DestAddrMode = BDMA_DESTADDRMODE_FEND;
  DMA_InitStructRx.SrcAddrMode = BDMA_SRCADDRMODE_FIX;
  DMA_InitStructRx.TransSize = BDMA_TRANSSIZE_WORD;
  BDMA_Init(&DMA_InitStructRx, BDMA_CHANNEL_1); 
  BDMA_INTConfig(BDMA_INT_C1FE, ENABLE);
  /* Open DMA INT */
  NVIC_EnableIRQ(BDMA_IRQn);
  NVIC_SetPriority(BDMA_IRQn,0);
  BDMA_Cmd(BDMA_CHANNEL_1, ENABLE);
  
  SYSCFG1_Periph0ClockCmd(SYSCFG1_Periph0Clock_HFM_COP,ENABLE);
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_HFM_COP);
  /* Config HFM */	
  HFM_InitStructure.Mode = 1;
  HFM_InitStructure.ExchAddr = FFTExchAddr;
  HFM_InitStructure.WaveBaseAddr = RxBuf;
  HFM_InitStructure.DSPInstrAddr = 0x4000; //0x4000  (uint32_t)&CMDBUF[0]
  HFM_InitStructure.DSPExchAddr = DSPPowerAddr;
  HFM_Init(&HFM_InitStructure);
    
  HFM_ClearINTStatus(HFM_INT_T2FDONE|HFM_INT_DSPDONE);
  HFM_INTConfig(HFM_INT_T2FDONE|HFM_INT_DSPDONE,ENABLE);
  NVIC_EnableIRQ(HFM_COP_IRQn);
    
  WAVER_Cmd(ENABLE);
  
  printf("FFT 128 test.\r\n");

  while(1)
  {
    if(DMA1flag_framend)
    {
      DMA1flag_framend = 0;
      HFM_T2F_StartManual();
      HFM_T2F_WaitForManual();
      printf("T2F Done\r\n");
    }
    if(DMA1flag_framend1)
    {
      DMA1flag_framend1 = 0;
      HFM_T2F_StartManual();
      HFM_T2F_WaitForManual();
      printf("T2F Done\r\n");
    }
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
