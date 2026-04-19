/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-03-05
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RTC_CMP_GPIO_Configuration(void);
void LED_GPIO_Configuration(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  RTC_COMP_InitType COMP_InitStructure;
  
  STD_Init(CLK_GetHCLK0Freq());
  BSP_Printf_Init();
  
  RTCEx_RTCWKUModuleClkCmd(RTC_ANA_CLK_RTC_CMP,ENABLE);
  
  RTC_CMP_GPIO_Configuration();
  LED_GPIO_Configuration();
  
  RTC_COMP_DeInit(RTC_COMP_Channel_0);
  RTC_COMP_StructInit(&COMP_InitStructure);
  COMP_InitStructure.RTC_COMP_FilterClkDiv = RTC_COMP_Filter_ClkDiv_1;
  COMP_InitStructure.COMP_FilterClkPeriod = RTC_COMP_Filter_Period_0;
  RTC_COMP_Init(&COMP_InitStructure);

  RTC_COMP_Cmd(RTC_COMP_Channel_0 , DISABLE);
  RTC_COMP_INTConfig(RTC_COMP_Channel_0,RTC_COMP_INT_HIGH,ENABLE);
  RTC_COMP_ClearINTStatus(RTC_COMP_Channel_0);
  RTC_COMP_Cmd(RTC_COMP_Channel_0 ,ENABLE);
  printf("RTC compare interrupt test.\r\n");
  NVIC_EnableIRQ(RTC_IRQn);

  while (1)
  {

  }
}





/**
  * @brief  Configure RTC_CMP GPIO.
  * @param  None
  * @retval None
  */
void RTC_CMP_GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStruct;

  /* Configure PI8 (RTC_COMP Ch0) as  input */
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8 ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure PC13 (RTC_COMP Ch0) as  AF pin*/
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource13, GPIO_AF9_CMP0_OUT);
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_13 ;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
}


void LED_GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStruct;
 
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 ;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;    
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
    
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
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
