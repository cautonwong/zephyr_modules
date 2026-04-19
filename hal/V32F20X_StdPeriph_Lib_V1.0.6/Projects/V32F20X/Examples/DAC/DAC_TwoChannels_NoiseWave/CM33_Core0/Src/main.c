/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-04
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void DAC_GPIO_Configuration(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  DAC_InitType          DAC_InitStructure;
  TMR_TimeBaseInitType  TMR_TimeBaseStructure;
  
  STD_Init(CLK_GetHCLK0Freq());
  BSP_Printf_Init();
  
  SYSCFG0_TMRClockCmd(SYSCFG0_TMRCLK_ETMR1,ENABLE);
  SYSCFG0_DACClockConfig(SYSCFG0_DAC_CLKSRC_RCH,1);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_DAC,ENABLE);
  
  SYSCFG0_DACVref_config(SYSCFG0_DAC_VERF_Internal,SYSCFG0_DAC_VERF_3_2V);

  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure); 
  TMR_TimeBaseStructure.TMR_Period           = 20-1;
  TMR_TimeBaseStructure.TMR_Prescaler        = 1;
  TMR_TimeBaseStructure.TMR_ClockDivision    = 0x0;
  TMR_TimeBaseStructure.TMR_CounterMode      = TMR_CounterMode_Up;  
  TMR_TimeBaseInit(ETMR1, &TMR_TimeBaseStructure);
  TMR_SelectOutputTrigger(ETMR1, TMR_TRGOSource_Update);
  
  DAC_GPIO_Configuration();
  DAC_DeInit();

  DAC_StructInit(&DAC_InitStructure);
  DAC_InitStructure.DAC_Trigger                      = DAC_TRIGGER_T2_TRGO;
  DAC_InitStructure.DAC_WaveGeneration               = DAC_WAVE_GENERATION_NOISE;
  DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSR_UNMASK_BITS_11_0; 
  DAC_InitStructure.DAC_OutputBuffer                 = DAC_OUTPUT_BUFFER_DISABLE; 
  DAC_Init(DAC_CHANNEL_0, &DAC_InitStructure);
  DAC_Init(DAC_CHANNEL_1, &DAC_InitStructure);

  DAC_Cmd(DAC_CHANNEL_0, ENABLE);
  DAC_Cmd(DAC_CHANNEL_1, ENABLE);

  TMR_Cmd(ETMR1, ENABLE);
 
  printf("DAC two channels noise wave test\r\n");
  while (1)
  {
  }
}


/**
  * @brief  Configures the DAC GPIO PIN.
  * @param  None
  * @retval None
  */
void DAC_GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStruct;

  /* Configure PA4(DAC Ch0) PA5(DAC Ch1)as analog input */
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
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
