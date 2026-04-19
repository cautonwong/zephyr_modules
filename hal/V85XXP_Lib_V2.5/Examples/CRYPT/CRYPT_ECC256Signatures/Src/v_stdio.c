/**
  * @file    v_stdio.h
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   standard printf.
******************************************************************************/

#include "v_stdio.h"
#include "target.h"
#include <stdio.h>

/**
  * @brief  printf init.
  * @param  None
  * @retval None
  */
void Stdio_Init(void)
{
  UART5->BAUDDIV = CLK_GetPCLKFreq()/115200;
  UART5->CTRL = UART_CTRL_TXEN;
}

/**
  * @brief   fputc.
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
  //while (UART5->STATE&UART_STATE_TXFULL);
  UART5->DATA = ch;
  while (!(UART5->STATE&UART_STATE_TXDONE)); 
  UART5->STATE = UART_STATE_TXDONE;
  return ch;
}

/*********************************** END OF FILE ******************************/
