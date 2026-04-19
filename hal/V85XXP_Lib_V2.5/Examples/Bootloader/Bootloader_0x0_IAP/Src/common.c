/**
  ******************************************************************************
  * @file    common.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#include "common.h"

pFunction Jump_To_Application;
uint32_t JumpAddress;

extern uint32_t FlashDestination;
extern volatile uint32_t g_bAppRun;

/**
  * @brief  Integer switch to string.
  * @inparam   intnum.
  * @outparam  str
  * @retval None.
**/
void Int2Str(uint8_t* str, int32_t intnum)
{
  uint32_t i, j ;
  uint32_t Div = 1000000000;
  uint32_t Status = 0;

  for (i = 0; i < 10; i++)
  {
    j = 0;
    str[j++] = (intnum / Div) + 48;
  
    intnum = intnum % Div;
    Div /= 10;
    if ((str[j-1] == '0') & (Status == 0))
    {
      j = 0;
    }
    else
    {
      Status++;
    }
  }
}

/**
  * @brief  String switch to integer.
  * @inparam   inputstr:
  * @outparam  intnum��
  * @retval 0: Error.
            1��Correct.
**/
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
  uint32_t i = 0, res = 0;
  uint32_t val = 0;

  if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
  {
    if (inputstr[2] == '\0')
    {
      return 0;
    }
    for (i = 2; i < 11; i++)
    {
      if (inputstr[i] == '\0')
      {
        *intnum = val;
        res = 1;
        break;
      }
      if (ISVALIDHEX(inputstr[i]))
      {
        val = (val << 4) + CONVERTHEX(inputstr[i]);
      }
      else
      {
        res = 0;
        break;
      }
    }

    if (i >= 11)
    {
      res = 0;
    }
  }
  else
  {
    for (i = 0; i < 11; i++)
    {
      if (inputstr[i] == '\0')
      {
        *intnum = val;
        res = 1;
        break;
      }
      else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
      {
        val = val << 10;
        *intnum = val;
        res = 1;
        break;
      }
      else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
      {
        val = val << 20;
        *intnum = val;
        res = 1;
        break;
      }
      else if (ISVALIDDEC(inputstr[i]))
      {
        val = val * 10 + CONVERTDEC(inputstr[i]);
      }
      else
      {
        res = 0;
        break;
      }
    }
    if (i >= 11)
    {
      res = 0;
    }
  }

  return res;
}

/**
  * @brief    Get an integer from the HyperTerminal.
  * @inparam  num
  * @outparam intnum:
  * @retval 0: Abort by user.
            1��Correct.
**/
uint32_t GetIntegerInput(int32_t * num)
{
  uint8_t inputstr[16];

  while (1)
  {
    GetInputString(inputstr);
    if (inputstr[0] == '\0') continue;
    if ((inputstr[0] == 'a' || inputstr[0] == 'A') && inputstr[1] == '\0')
    {
      SerialPutString("User Cancelled \r\n");
      return 0;
    }

    if (Str2Int(inputstr, num) == 0)
    {
      SerialPutString("Error, Input again: \r\n");
    }
    else
    {
      return 1;
    }
  }
}


/**
  * @brief    Test whether the terminal has buttons pressed.
  * @inparam  key.
  * @outparam None.
  * @retval 0: Error.
            1��Correct.
**/
uint32_t SerialKeyPressed(uint8_t *key)
{
  if (UART5->STATE&UART_STATE_RXFULL)
  {
    *key = (uint8_t)UART5->DATA;
    return 1;
  }
  else
  {
    return 0;
  }
}


/**
  * @brief    GetKey.
  * @inparam  None.
  * @outparam None.
  * @retval   The key of user pressed.
**/
uint8_t GetKey(void)
{
  uint8_t key = 0;

  // Wait for key be pressed
  while (1)
  {
    if (SerialKeyPressed((uint8_t*)&key)) 
    {
      break;
    }
  }
  return key;
}


/**
  * @brief    Send a character by serial port.
  * @inparam  C: The character you should send.
  * @outparam None.
  * @retval   None.
**/
void SerialPutChar(uint8_t c)
{
  UART5->DATA = c;
  /* wait for transmit done */
  while (!(UART5->STATE&UART_STATE_TXDONE));
  UART5->STATE |= UART_STATE_TXDONE;
}

/**
  * @brief    Send strings by serial port.
  * @inparam  s: The string need to send.
  * @outparam None.
  * @retval   None.
**/
void Serial_PutString(uint8_t *s)
{
  while (*s != '\0')
  {
    SerialPutChar(*s);
    s++;
  }
}

/**
  * @brief    Get a string from serial port.
  * @inparam  *s.
  * @outparam None.
  * @retval   None.
**/
void GetInputString(uint8_t * buffP)
{
  uint32_t bytes_read = 0;
  uint8_t c = 0;
  do
  {
    c = GetKey();
    if (c == '\r')
      break;
    if (c == '\b')// Backspace ����  
    {
      if (bytes_read > 0)
      {
        SerialPutString("\b \b");
        bytes_read --;
      }
      continue;
    }
    if (bytes_read >= CMD_STRING_SIZE )
    {
      SerialPutString("Command string size overflow\r\n");
      bytes_read = 0;
      continue;
    }
    if (c >= 0x20 && c <= 0x7E)
    {
      buffP[bytes_read++] = c;
      SerialPutChar(c);
    }
  }
  while (1);
  SerialPutString(("\n\r"));
  buffP[bytes_read] = '\0';
}

/**
  * @brief    Calculate the number of Falsh page.
  * @inparam  Size: Length of file.
  * @outparam None.
  * @retval   The number of Falsh page.
**/
uint32_t FLASH_PagesMask(volatile uint32_t Size)
{
  uint32_t pagenumber = 0x0;
  uint32_t size = Size;

  if ((size % PAGE_SIZE) != 0)
  {
    pagenumber = (size / PAGE_SIZE) + 1;
  }
  else
  {
    pagenumber = size / PAGE_SIZE;
  }
  return pagenumber;
}


/**
  * @brief    Main_Menu.
  * @inparam  None.
  * @outparam None.
  * @retval   None.
**/
 void Main_Menu(void)
{
  uint8_t key = 0;

  while (1)
  {
    SerialPutString("================== Main Menu ==========================\r\n\n");
    SerialPutString("  Download Image To the Target Internal Flash ------- 1\r\n\n");
    SerialPutString("  Upload Image From the Target Internal Flash ------- 2\r\n\n");
    SerialPutString("  Execute The New Program --------------------------- 3\r\n\n");

    if ((FLASH->PASS) == 0)
    {
      SerialPutString("  Disable the write protection --------------------- 4\r\n\n");
    }

    SerialPutString("========================================================\r\n\n");

    key = GetKey();

    if (key == 0x31)
    {
      /* Download user application in the Flash */
      SerialDownload();
    }
    else if (key == 0x32)
    {
      /* Upload user application from the Flash */
      SerialUpload();
    }
    else if (key == 0x33)
    {
      g_bAppRun = 1;
      SerialPutString("Execute user Program\r\n\n");
      JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);

      Jump_To_Application = (pFunction) JumpAddress;
      /*Initial stack pointer of user code*/
      __set_MSP(*(__IO uint32_t*) ApplicationAddress);
      Jump_To_Application();
    }

    else if ((key == 0x34) && ((FLASH->PASS) == 0))
    {
      /*Unlock FLASH*/
      FLASH_Unlock();
    }
    else
    {
      if ((FLASH->PASS) != 0)
      {
        SerialPutString("Invalid number! ==> The number should be either 1, 2 or 3\r\n\n\n");
      }
      else
      {
        SerialPutString("Invalid number! ==> The number should be either 1, 2, 3 or 4\r\n\n\n");
      }
    }        
  }
}
/**
  * @brief  Erase FLASH sector.
  * @param  SectorAddr: sector address.
  * @retval None
  */
void FLASH_SectorEraseUnderUnlock(uint32_t SectorAddr)
{
  FLASH->PGADDR = SectorAddr;
  FLASH->SERASE = FLASH_SERASE_KEY;
  while (FLASH->SERASE != 0);
}

/**
  * @brief  FLASH one word progarm .
  * @param  Addr: program address
            Word: word to write
  * @retval None  
  */
void FLASH_ProgramOneWord(uint32_t Addr, uint32_t Word)
{
  FLASH->PGADDR = Addr;
  FLASH->PGDATA = Word;
}

/**
  * @brief  Unlock FLASH.
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
  FLASH->PASS = 0x55AAAA55;
}

/**
  * @brief  Lock FLASH.
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
  FLASH->PASS = 0;
}
