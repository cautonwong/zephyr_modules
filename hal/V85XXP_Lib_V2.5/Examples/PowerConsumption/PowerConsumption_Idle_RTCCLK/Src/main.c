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


#ifdef __GNUC__

extern void PMU_EnterIdle_FlashDSTB(void) __attribute__((section(".ram_exec")));

/**
  * @brief  Flash deep standby, enter idle mode.
  * @note   This function is executed in RAM.
  * @param  None
  * @retval None
  */
void PMU_EnterIdle_FlashDSTB(void)
{
  /* Flash deep standby */
  FLASH->PASS = 0x55AAAA55;
  FLASH->DSTB = 0xAA5555AA;
  /* Enter Idle mode */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  __WFI();
}

#endif


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  GPIO_InitType GPIO_InitStructure;
  CLK_InitTypeDef CLK_Struct;
  
  test_success = 0;

/* Normal mode */
if (PMU_GetModeStatus() == 1U)
{
  WDT_Disable();
  
  /* Forbidden all GPIOs */
  GPIO_InitStructure.GPIO_Mode = GPIO_MODE_FORBIDDEN;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_All;
  GPIOA_Init(GPIOA, &GPIO_InitStructure);
  GPIOBToF_Init(GPIOB, &GPIO_InitStructure);
  GPIOBToF_Init(GPIOC, &GPIO_InitStructure);
  GPIOBToF_Init(GPIOD, &GPIO_InitStructure);
  GPIOBToF_Init(GPIOE, &GPIO_InitStructure);
  GPIOBToF_Init(GPIOF, &GPIO_InitStructure);

  /* System clock be switched to RTC clock(32768Hz) */
  CLK_Struct.ClockType = CLK_TYPE_AHBSRC \
                             |CLK_TYPE_RTCCLK \
                             |CLK_TYPE_HCLK   \
                             |CLK_TYPE_PCLK;
  CLK_Struct.AHBSource      = CLK_AHBSEL_RTCCLK;
  CLK_Struct.RTCCLK.Source  = CLK_RTCCLKSRC_XTALL;
  CLK_Struct.RTCCLK.Divider = CLK_RTCCLKDIV_1;
  CLK_Struct.HCLK.Divider   = 1;
  CLK_Struct.PCLK.Divider   = 1;
  CLK_ClockConfig(&CLK_Struct);

  /* Power down BGP/RCH */
  ANA->REG3 |= (ANA_REG3_BGPPD | ANA_REG3_RCHPD);
  /* Disable AVCC output */
  ANA->REGF &= ~ANA_REGF_AVCCOEN;
  /* Power down ADC */
  ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN;
  /* Comparator 1 power control */
  ANA->REG3 &= ~ANA_REG3_CMP1PDN;
  /* Comparator 2 power control */
  ANA->REG3 &= ~ANA_REG3_CMP2PDN;
  /* Power down Tiny ADC */
  ANA->REGF &= ~ANA_REGF_ADTPDN;
  /* AVCC power up */
  ANA->REG8 &= ~ANA_REG8_AVCCLDOPD;
  /* Power down LCD */
  LCD->CTRL &= ~LCD_CTRL_EN;
  /* VDCIN detector control */ 
  ANA->REGA |= ANA_REGA_VDCINDETPD;
  /* VDD detector control */
  PMU_VDDDetectorCmd(PMU_VDDDET_OFF);

  CLK_APBPeriphralCmd(CLK_APBPERIPHRAL_ALL, DISABLE);
  CLK_AHBPeriphralCmd(CLK_AHBPERIPHRAL_ALL, DISABLE);

  /* Enter Idle mode */
  PMU_EnterIdle_FlashDSTB();
}

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
