/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

extern unsigned int CMDBUF[1380];
unsigned int * g_HFM_POWERVALUE_ADDR;

int Vaule_Waver[1024] __attribute__((section(".ARM.__at_0x2100B000")));
unsigned char FFTexchange[1024]__attribute__((section(".ARM.__at_0x2100C000")));
unsigned int DSP_exchange[1024] __attribute__((section(".ARM.__at_0x2100D000")));


HFM_Type * g_HFM = HFM;
//WAVER0_Type * g_WAVER0 = WAVER0;
unsigned char recieve_data[50];
unsigned char recieve_count = 0;

/* Private functions ---------------------------------------------------------*/


void WAVER_CM0_Init(void)
{
  WAVER_InitType WAVER_InitStruct;
  
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_WAVER);
  SYSCFG1_Periph0ClockCmd(SYSCFG1_Periph0Clock_WAVER, ENABLE);

  WAVER_StructInit(&WAVER_InitStruct);
  WAVER_InitStruct.Mode = WAVER_MODE_U_IA_IB;
  WAVER_InitStruct.SampleLength = WAVER_SAMPLELEN_256;
  WAVER_InitStruct.CICRateSEL = WAVER_CIC_128;
  WAVER_InitStruct.COMPSEL = WAVER_COMP_DISABLE;
  WAVER_InitStruct.UploadSEL = WAVER_UPLOAD_SPI_M33;
  WAVER_InitStruct.UploadEndianSEL = WAVER_UPLOAD_LITTLE_ENDIAN;
  WAVER_InitStruct.BackupSEL = WAVER_BACKUP_DISABLE;
  WAVER_Init(&WAVER_InitStruct);
  WAVER_Cmd(ENABLE);
  
  return;
}


void DMA_CM0_Init(void)
{
  BDMA_InitType DMA_InitStruct;
  
  BDMA_DeInit(BDMA_CHANNEL_0);
  DMA_InitStruct.SrcAddr = (uint32_t)&WAVER0->DATA;
  DMA_InitStruct.SrcAddrMode = BDMA_SRCADDRMODE_FIX;
  DMA_InitStruct.DestAddr = (uint32_t)&Vaule_Waver[0];
  DMA_InitStruct.DestAddrMode = BDMA_DESTADDRMODE_FEND;
  DMA_InitStruct.FrameLen = 128 - 1;
  DMA_InitStruct.PackLen = 3 - 1;
  DMA_InitStruct.ContMode = BDMA_CONTMODE_ENABLE;
  DMA_InitStruct.TransMode = BDMA_TRANSMODE_PACK;
  DMA_InitStruct.ReqSrc = BDMA_REQSRC_WAVER0;
  DMA_InitStruct.TransSize = BDMA_TRANSSIZE_WORD;
  BDMA_Init(&DMA_InitStruct, BDMA_CHANNEL_0); 
  BDMA_INTConfig(BDMA_INT_C0FE, ENABLE);
  
  NVIC_EnableIRQ(BDMA_IRQn);
  NVIC_SetPriority(BDMA_IRQn,0);
  /* Enable BDMA channel0 */
  BDMA_Cmd(BDMA_CHANNEL_0, ENABLE);
  
}


void SPI0_Init(void)
{
  GPIO_InitType GPIO_InitStruct;
  BSPI_InitType SPI_InitStruct;
  
  /* CLOCK */
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI0);
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_BSPI0, ENABLE);
  
  
  /*
  PA9 -> BSPI0 MOSI 
  PC7 -> BSPI0 CK 
  PC8 -> BSPI0 CS 
  PC9 -> BSPI0 MISO 
  */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF14_BSPI0_MOSI);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF14_BSPI0_CK);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF14_BSPI0_CS);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF14_BSPI0_MISO);
  
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* SPI0 initialization, slave mode */
  BSPI_DeviceInit(BSPI0);
  BSPI_StructInit(&SPI_InitStruct);
  SPI_InitStruct.Mode = SPI_MODE_SLAVE;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_DISABLE;
  BSPI_Init(BSPI0, &SPI_InitStruct);
  
  /*Enable SPI0 */
  BSPI_Cmd(BSPI0, ENABLE);
  
  return;
}


void SPI1_Init(void)
{
  GPIO_InitType GPIO_InitStruct;
  BSPI_InitType SPI_InitStruct;
  
  /* CLOCK */
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI1);
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_BSPI1, ENABLE);
  
  
  /*
  PA8  -> BSPI1 CK 
  PA10 -> BSPI1 CS 
  PA11 -> BSPI1 MISO 
  PA12 -> BSPI1 MOSI 
  */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,  GPIO_AF14_BSPI1_CK);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF14_BSPI1_CS);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF14_BSPI1_MISO);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF14_BSPI1_MOSI);
  
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* SPI0 initialization, MASTER mode */
  BSPI_DeviceInit(BSPI1);
  BSPI_StructInit(&SPI_InitStruct);
  SPI_InitStruct.Mode = SPI_MODE_MASTER;
  SPI_InitStruct.CSNSoft = SPI_CSNSOFT_ENABLE;
  BSPI_Init(BSPI1, &SPI_InitStruct);
  
  /*Enable SPI1 */
  BSPI_Cmd(BSPI1, ENABLE);
  
  return;
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  unsigned int i;
  GPIO_InitType GPIO_InitStructure;
  HFM_InitType  HFM_InitStruct;
  
  EGY_InitType EGY_InitStruct;
  CF_InitType  CF_InitStruct;
    
  STD_Init(48000000UL);
  
  SysTick_Config(48000);
  
  /* UART */
  BSP_Printf_Init();
  printf("test waver HFM EGY!\r\n");
  
  printf("HFM addr %x!\r\n", (unsigned int)g_HFM);
  
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_HFM_COP);
  SYSCFG1_Periph0ClockCmd(SYSCFG1_Periph0Clock_HFM_COP, ENABLE);
  
  /* hfm CONFIG */
  HFM_InitStruct.Mode = 1;
  HFM_InitStruct.ExchAddr = (uint32_t)FFTexchange;
  HFM_InitStruct.WaveBaseAddr = (uint32_t)&Vaule_Waver[0];
  HFM_InitStruct.DSPInstrAddr = (uint32_t)CMDBUF;
  HFM_InitStruct.DSPExchAddr = (uint32_t)&DSP_exchange[0];
  HFM_Init(&HFM_InitStruct);
  
  HFM_ClearINTStatus(HFM_INT_T2FDONE|HFM_INT_DSPDONE);
  HFM_INTConfig(HFM_INT_T2FDONE|HFM_INT_DSPDONE,ENABLE);
  NVIC_EnableIRQ(HFM_COP_IRQn);
  
  g_HFM_POWERVALUE_ADDR = (unsigned int*)HFM->POWERVALUE;
  
  /* create value in waver addr*/
  for(i = 0; i < 128; i++)
  {
    Vaule_Waver[i*3+0] = 1000*cos(2*3.1415926*i/128) + 2000*cos(2*3.1415926*2*i/128);
    Vaule_Waver[i*3+1] = 2000*cos(2*3.1415926*i/128 + 2*3.1415926/4)+4000*cos(2*3.1415926*i*2/128 + 2*3.1415926/4);
    Vaule_Waver[i*3+2] = 3000*cos(2*3.1415926*i/128 + 2*3.1415926/2)+6000*cos(2*3.1415926*i*2/128 + 2*3.1415926/2);
  }
  
  /* start T2F  */
  //HFM_T2F_StartManual();
  
  /***************************************************************************************
  EGY 
  ***************************************************************************************/
  /* config cf GPIO */
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF14_ENGY_CF0);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  /* config EGY */
  EGY_InitStruct.Channel = 7;//open ABC channel
  EGY_InitStruct.HARMNum = 0;//use Fundamental wave
  EGY_InitStruct.AddSource = EGY_ACCSOURCE_POWER;
  EGY_InitStruct.AddEGYMode = EGY_ACCEGYMODE_ORIGINAL;
  EGY_InitStruct.AddTypeSel = EGY_ACCTYPE_ACTIVEPOWER;
  EGY_InitStruct.AddPWRMode = EGY_ACCPOWERTYPE_ORGINAL;
  EGY_InitStruct.PowerThresholdSEL = 1;//use HFM_EGYPWRTH1
  EGY_Init(EGY0, &EGY_InitStruct);

  /* conig CF */
  CF_InitStruct.CF_Source = CF_SOURCE_EGY0;
  CF_InitStruct.CF_Polarity = CF_ORGINAL;
  CF_InitStruct.CF_PulsePeriod = CF_PERIOD_80MS;
  CF_InitStruct.CF_Fast = CF_FAST_X1;
  CF_InitStruct.CF_Division = 128;//curent 26214400/128 = 204800
  CF_InitStruct.ConstValue = 0;
  CF_Init(CF0, &CF_InitStruct);
  
  /* open CF out */
  CF_Cmd(CF0, ENABLE);

  EGY_PWR1ThresholdConfig(137329);

  /* write value to Power Value */
  for(i = 0;i < 27;i++)
  {
      HFM->POWERVALUE[i] = 1000 + 1000*i;
  }
 
 /* EGY0 USE ABC channel P
     so PWRVALUE[0]+PWRVALUE[1]+PWRVALUE[2] 1000+2000+3000=6000
     CF 137329*16384/(26214400/128)/6000 = 1s */

  /* Open HFM INT */
  HFM_INTConfig(HFM_INT_EGY0SPILL,ENABLE);
  NVIC_EnableIRQ(HFM_COP_IRQn);
  EGY_Cmd(EGY0, ENABLE);

  SYSCFG1->EGYCFEN = 7;//Open EGY and CF 0,1,2

  /***************************************************************************************
  WAVER 
  ***************************************************************************************/
  SPI0_Init();
  BSPI_ReceiveData(BSPI0);
  SPI1_Init();
  
  DMA_CM0_Init();
  WAVER_CM0_Init();

  printf("Test success\r\n");
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
