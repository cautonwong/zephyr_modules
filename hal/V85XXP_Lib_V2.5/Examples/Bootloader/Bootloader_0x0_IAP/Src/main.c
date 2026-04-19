/**
  * @file    main.c
  * @author  Application Team
  * @version V2.0.1
  * @date    2022-06-30
  * @brief   Main program body.
******************************************************************************/

volatile unsigned char test_success;

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define FLASH_PASS_KEY
extern pFunction Jump_To_Application; 
extern uint32_t JumpAddress;
volatile uint32_t g_bAppRun;

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

void Delay_us(volatile uint32_t n)
{
  while (n--)
  {
    __NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();
    __NOP();__NOP();
  }
}

void Delay_ms(volatile uint32_t n)
{
  while (n--)
  {
    Delay_us(971);
  }
}

/**
  * @brief  Jump to APP.
  * @param  None.
  * @retval None.
**/
static void JumpToApp(void)
{
  /*Jedge the stack address£º0x200000000~0x20007FFF*/
  if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFF80000 ) == 0x20000000)
  {
    SerialPutString("Execute user Program!\r\n\n");

    /*Jump to the user code*/
    JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
    Jump_To_Application = (pFunction) JumpAddress;

    /*Set stack top value of user code as current stack top value */
    __set_MSP(*(__IO uint32_t*) ApplicationAddress);

    Jump_To_Application();
  }
  else
  {
    SerialPutString("no user Program\r\n\n");
    Main_Menu();
  }
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint8_t key;
  
  test_success = 0;
    
  Clock_Init();
  FLASH_CycleInit();
  test_success = 1;

  /*unlock Flash*/
  FLASH_Unlock();
  
  /*Configure UART5*/
  UART5->BAUDDIV = CLK_GetPCLKFreq()/115200;
  UART5->CTRL = UART_CTRL_TXEN|UART_CTRL_RXEN;

  Delay_ms(500);    
  /*If UART receive '5', excute IAP program*/
  SerialKeyPressed(&key);
  if (key == 0x35)
  { 
    g_bAppRun = 0;
    Main_Menu();
  }    
  /*Else, there will excute user code*/
  else
  {
    g_bAppRun = 1;
    /*Jump to user code*/
    JumpToApp(); 
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
