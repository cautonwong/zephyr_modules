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
void Print_CurrentTime(void)
{
  RTC_TimeTypeDef rTime;
  
  /* Get time */
  RTC_GetTime(&rTime, RTC_INACCURATE);
#ifdef __GNUC__
  printf("20%lx-", rTime.Year);
  printf("%02lx-", rTime.Month);
  printf("%02lx   ", rTime.Date);
  printf("Weekday %lx   ", rTime.WeekDay);
  printf("%02lx:", rTime.Hours);
  printf("%02lx:", rTime.Minutes);
  printf("%02lx\r\n", rTime.Seconds);
#else
  printf("20%x-", rTime.Year);
  printf("%02x-", rTime.Month);
  printf("%02x   ", rTime.Date);
  printf("Weekday %x   ", rTime.WeekDay);
  printf("%02x:", rTime.Hours);
  printf("%02x:", rTime.Minutes);
  printf("%02x\r\n", rTime.Seconds);
#endif
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  PMU_WakeUpPinConfig(GPIO_Pin_6, IOA_EDGEBOTH);
  PMU_ClearIOAINTStatus(GPIO_Pin_6);
  PMU_INTConfig(PMU_INT_IOAEN, ENABLE);
  CORTEX_SetPriority_ClearPending_EnableIRQ(PMU_IRQn, 0);

  
  /* Selects VDCIN hysteresis */
  PMU_VDCINHYSConfig(PMU_VDCINHYSSEL_200MV);
  /* Enable VDCIN detector */
  PMU_VDCINDetectorCmd(ENABLE);
  
  printf("========================\r\n");
  Print_CurrentTime();

  test_success = 1;
  
  while (1)
  {       
     /* If VDCIN drop, enter sleep mode*/
    if (PMU_GetVDCINDropStatus())
    {
      /* Disable Watch Dog Timer */
      WDT_Disable();
      
      PMU_EnterSleepMode();
    }
    else
    {
      printf("VDCIN is not drop!\r\n");
      while (1);
    }
    WDT_Clear();
    /* Quit sleep mode, configure clocks/UART print */
    Print_CurrentTime();
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
