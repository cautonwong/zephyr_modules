/**
  ******************************************************************************
  * @file    upload.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "common.h"

/**
  * @brief  Upload file via Serial.
  * @param  None.
  * @retval None.
**/
void SerialUpload(void)
{
  uint32_t status = 0;
  SerialPutString("\n\n\rSelect Receive File ... (press any key to abort)\n\r");

//GetKey();
  if ( GetKey()== CRC16)
  {
    //Ymodem_Transmit's return value is 0, function successed
    status = Ymodem_Transmit((uint8_t*)ApplicationAddress, (const uint8_t*)"UploadedFlashImage.bin", FLASH_IMAGE_SIZE);

    if (status != 0)
    {
      SerialPutString("\n\rError occured while Transmitting File\n\r");
    }
    else
    {
      SerialPutString("\n\rFile Trasmitted Successfully \n\r");
    }
  }
  else
  {
    SerialPutString("\r\n\nAborted by user.\n\r");
  }
}
