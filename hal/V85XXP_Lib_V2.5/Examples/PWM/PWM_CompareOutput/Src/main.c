/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

volatile unsigned char test_success;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Clock_Init:
              - PLLL input clock    : External 32K crystal
              - PLLL frequency      : 26M
              - AHB Clock source    : PLLL
              - AHB Clock frequency : 26M (PLLL divided by 1)
              - APB Clock frequency : 13M (AHB Clock divided by 2)
  * @param  None
  * @retval None
  */
void Clock_Init(void)
{
  CLK_InitTypeDef CLK_Struct;

  CLK_Struct.ClockType = CLK_TYPE_AHBSRC \
                        |CLK_TYPE_PLLL   \
                        |CLK_TYPE_HCLK   \
                        |CLK_TYPE_PCLK;
  CLK_Struct.AHBSource      = CLK_AHBSEL_LSPLL;
  CLK_Struct.PLLL.Frequency = CLK_PLLL_26_2144MHz;
  CLK_Struct.PLLL.Source    = CLK_PLLLSRC_XTALL;
  CLK_Struct.PLLL.State     = CLK_PLLL_ON;
  CLK_Struct.HCLK.Divider   = 1;
  CLK_Struct.PCLK.Divider   = 2;
  CLK_ClockConfig(&CLK_Struct);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  PWM_BaseInitType PWM_BaseInitStruct;
  PWM_OCInitType PWM_OCInitStruct;

  test_success = 0;

  Clock_Init();

  /* PWM0 base initialization 
       - Count mode   : CONTINUOUS mode
       - Clock source : PCLK 13M
       - Clock Divide : divide by 16     */
  PWM_BaseInitStruct.ClockDivision = PWM_CLKDIV_16;
  PWM_BaseInitStruct.ClockSource = PWM_CLKSRC_APB;
  PWM_BaseInitStruct.Mode = PWM_MODE_CONTINUOUS;
  PWM_BaseInit(PWM0, &PWM_BaseInitStruct);

  /** PWM0 channel 0 Initialize:
       - Mode         : compare mode
       - Out Mode     : TOGGLE
       - Out line     : PWM0 output (IOB0)
       Output: 6.25Hz 
       High/Low = 1/1
    */   
  PWM_OLineConfig(PWM0_OUT0, PWM_OLINE_0);
  PWM_OCInitStruct.Channel = PWM_CHANNEL_0;
  PWM_OCInitStruct.OutMode = PWM_OUTMOD_TOGGLE;
  PWM_OCInitStruct.Period = 0x8000;
  PWM_OCInit(PWM0, &PWM_OCInitStruct);

  /** PWM0 channel 1 Initialize:
       - Mode         : compare mode
       - Out Mode     : TOGGLE_RESET
       - Out line     : PWM1 output (IOB6)
       Output: 12.5Hz 
       High/Low = (0x8000-0x2000)/(0xFFFF-0x6000) = 3/5
    */
  PWM_OLineConfig(PWM0_OUT1, PWM_OLINE_1);
  PWM_OCInitStruct.Channel = PWM_CHANNEL_1;
  PWM_OCInitStruct.OutMode = PWM_OUTMOD_TOGGLE_RESET;
  PWM_OCInitStruct.Period = 0x2000;
  PWM_OCInit(PWM0, &PWM_OCInitStruct);

  /** PWM0 channel 2 Initialize:
       - Mode         : compare mode
       - Out Mode     : TOGGLE_RESET
       - Out line     : PWM2 output (IOB13)
       Output: 12.5Hz 
       High/Low = = (0x8000-0x4000)/(0xFFFF-0x4000) = 1/3
    */  
  PWM_OLineConfig(PWM0_OUT2, PWM_OLINE_2);
  PWM_OCInitStruct.Channel = PWM_CHANNEL_2;
  PWM_OCInitStruct.OutMode = PWM_OUTMOD_TOGGLE_RESET;
  PWM_OCInitStruct.Period = 0x4000;
  PWM_OCInit(PWM0, &PWM_OCInitStruct);
  
  PWM_ClearCounter(PWM0);
  /* Enable PWM0 channel 0/1/2 output */
  PWM_OutputCmd(PWM0, PWM_CHANNEL_0, ENABLE);
  PWM_OutputCmd(PWM0, PWM_CHANNEL_1, ENABLE);
  PWM_OutputCmd(PWM0, PWM_CHANNEL_2, ENABLE);

  test_success = 1;
  
  while (1)
  {
    WDT_Clear();
  }
}

#ifndef  ASSERT_NDEBUG
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
