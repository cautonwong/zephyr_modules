/**
  * @file    main.c
  * @author  Application Team
  * @version V1.2.0
  * @date    2020-06-23
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
  GPIO_InitType GPIO_InitStruct;
  PMU_LowPWRTypeDef LowPower_InitStruct;
  
  test_success = 0;

  /* Clock initialization */
  Clock_Init();

  /* Disable WDT */
  WDT_Disable();

  /*------------------ Forbidden all GPIOs ------------------*/
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_All;
  GPIOA_Init(GPIOA, &GPIO_InitStruct);
  GPIOBToF_Init(GPIOB, &GPIO_InitStruct);
  GPIOBToF_Init(GPIOC, &GPIO_InitStruct);
  GPIOBToF_Init(GPIOD, &GPIO_InitStruct);
  GPIOBToF_Init(GPIOE, &GPIO_InitStruct);
  GPIOBToF_Init(GPIOF, &GPIO_InitStruct);
  
  test_success = 1;

  /*------------------ Low power configuration ------------------*/
  LowPower_InitStruct.AHBPeriphralDisable = PMU_AHB_ALL;
  LowPower_InitStruct.APBPeriphralDisable = PMU_APB_ALL;
  LowPower_InitStruct.BGPPower            = PMU_BGPPWR_OFF;
  LowPower_InitStruct.CMP1Power           = PMU_CMP1PWR_OFF;
  LowPower_InitStruct.CMP2Power           = PMU_CMP2PWR_OFF;
  LowPower_InitStruct.AVCCPower           = PMU_AVCCPWR_ON;
  LowPower_InitStruct.TADCPower           = PMU_TADCPWR_OFF;
  LowPower_InitStruct.LCDPower            = PMU_LCDPWER_OFF;
  LowPower_InitStruct.VDCINDetector       = PMU_VDCINDET_DISABLE;
  LowPower_InitStruct.VDDDetector         = PMU_VDDDET_OFF;
  PMU_EnterSleep_LowPower(&LowPower_InitStruct);

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
