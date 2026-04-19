/**
  ******************************************************************************
  * @file    download.c
  * @author  Application Team
  * @version V2.0.1
  * @date    2022-06-30
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "common.h"

extern uint8_t file_name[FILE_NAME_LENGTH];

uint32_t tab_1024[1024/4] =
{
  0
};

/**
  * @brief  Receive file via Serial.
  * @inparam   None.
  * @outparam  None.
  * @retval None.
**/
void SerialDownload(void)
{
  int32_t Size = 0;

  SerialPutString("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
  Size = Ymodem_Receive((uint8_t*)&tab_1024[0]);
  if (Size > 0)
  {
    SerialPutString("\r\n IAP Completed Successfully!\r\n");
  }
  else if (Size == -1)
  {
    SerialPutString("\n\n\rThe image size is too large!\n\r");
  }
  else if (Size == -2)
  {
    SerialPutString("\n\n\rVerification failed!\n\r");
  }
  else if (Size == -3)
  {
    SerialPutString("\r\n\nAborted by user.\n\r");
  }
  else
  {
    SerialPutString("\n\rFailed to receive the file!\n\r");
  }
}
