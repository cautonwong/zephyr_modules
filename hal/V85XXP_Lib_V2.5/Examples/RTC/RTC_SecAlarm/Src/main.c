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
  RTC_GetTime(&rTime, RTC_ACCURATE);
#ifdef __GNUC__
  printf("20%lx-", rTime.Year);
  printf("%02lx-", rTime.Month);
  printf("%02lx   ", rTime.Date);
  printf("Weekday %lx   ", rTime.WeekDay);
  printf("%02lx:", rTime.Hours);
  printf("%02lx:", rTime.Minutes);
  printf("%02lx\t", rTime.Seconds);
  printf("%02lx\r\n", rTime.SubSeconds);
#else
  printf("20%x-", rTime.Year);
  printf("%02x-", rTime.Month);
  printf("%02x   ", rTime.Date);
  printf("Weekday %x   ", rTime.WeekDay);
  printf("%02x:", rTime.Hours);
  printf("%02x:", rTime.Minutes);
  printf("%02x\t", rTime.Seconds);
  printf("%02x\r\n", rTime.SubSeconds);
#endif
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  RTC_TimeTypeDef Time_Struct;
  RTC_AlarmTypeDef RTC_AlarmStruct;

  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  if(PMU_GetResetSource(PMU_RSTSRC_DPORST))
  {
    PMU_ClearResetSource(PMU_RSTSRC_DPORST);
    /* Set time */
    /* 2017-10-10 10:10:10 0ms */
    Time_Struct.Year    = 0x17;
    Time_Struct.Month   = 0x10;
    Time_Struct.Date    = 0x10;
    Time_Struct.Hours   = 0x10;
    Time_Struct.Minutes = 0x10;
    Time_Struct.Seconds = 0x10;
    Time_Struct.WeekDay = 0x02;
    Time_Struct.SubSeconds = 0;
    RTC_SetTime(&Time_Struct, RTC_ACCURATE);
  }
  
  /* Alarm: 10:20:10 100ms */
  RTC_AlarmStruct.AlarmHours = 0x10;
  RTC_AlarmStruct.AlarmMinutes = 0x10;
  RTC_AlarmStruct.AlarmSeconds = 0x20;
  RTC_SetAlarm(&RTC_AlarmStruct);
  
  /* Configure RTC Alarm sleep wakeup source */
  PMU_SleepWKUSRCConfig_RTC(PMU_RTCEVT_ALARM, 0);
  
  /* Enable RTC Alarm */
  RTC_AlarmCmd(ENABLE);
  
  test_success = 1;
  
  printf("========================\r\n");
  Print_CurrentTime();
  
  WDT_Disable();
  if(PMU_EnterSleepMode() == 0)
  {
    printf("Wake up!\r\n");
  }
  else
  {
    printf("MODE is low, Error!\r\n");
  }

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
