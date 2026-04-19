/**
  ******************************************************************************
  * @file    ymodem.c
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

#include "target.h"
#include "common.h"
#include "ymodem.h"

uint8_t file_name[FILE_NAME_LENGTH];
uint8_t packet_data[PACKET_1K_SIZE + PACKET_OVERHEAD];
// User App Flash offset
uint32_t FlashDestination = ApplicationAddress;
uint16_t PageSize = PAGE_SIZE;
uint32_t EraseCounter = 0x0;
uint32_t NbrOfPage = 0;

uint32_t RamSource;
extern uint32_t tab_1024[1024/4];

/**
  * @brief   Receive one byte.
  * @param   c: the pointer to receive data.
             timeout: 
  * @retal    0：Function succesed.
             -1：Time-out occured.
**/
static int32_t Receive_Byte (uint8_t *c, uint32_t timeout)
{
  while (timeout-- > 0)
  {
    if (SerialKeyPressed(c) == 1)
    {
      return 0;
    }
  }
  return -1;
}


/**
  * @brief   Receive package.
  * @param   data ：the pointer of datas
             length：the length of datas
             timeout ：
  * @retal   0: Function successed
            -1: Time-out occured or datas error
             1: Be canced
**/
static int32_t Receive_Packet (uint8_t *data, int32_t *length, uint32_t timeout)
{
  uint16_t i, packet_size;
  uint8_t c;
  *length = 0;
  if (Receive_Byte(&c, timeout) != 0)
  {
    return -1;
  }
  switch (c)
  {
    case SOH:
      packet_size = PACKET_SIZE;
      break;
    case STX:
      packet_size = PACKET_1K_SIZE;
      break;
    case EOT:
      return 0;
    case CA:
      if ((Receive_Byte(&c, timeout) == 0) && (c == CA))
      {
        *length = -1;
        return 0;
      }
      else
      {
        return -1;
      }
    case ABORT1:
    case ABORT2:
      return 1;
    default:
      return -1;
  }
  *data = c;
  for (i = 1; i < (packet_size + PACKET_OVERHEAD); i ++)
  {
    if (Receive_Byte(data + i, timeout) != 0) //发送端超时
    {
      return -1; 
    }
  }
  if (data[PACKET_SEQNO_INDEX] != ((data[PACKET_SEQNO_COMP_INDEX] ^ 0xff) & 0xff)) //包编码号与其反码不一致
  {
    return -1;
  }
  *length = packet_size;
  return 0;
}

/**
  * @brief  Receive file via ymodem
  * @param  buf: pointer of file
  * @retal  The size of file
**/
int32_t Ymodem_Receive (uint8_t *buf)
{
  uint8_t file_size[FILE_SIZE_LENGTH];
  uint8_t *file_ptr, *buf_ptr;
  int32_t i, j;
  int32_t packet_length, session_done, file_done, packets_received, errors, session_begin, size = 0;

  FlashDestination = ApplicationAddress;

  for (session_done = 0, errors = 0, session_begin = 0; ;)
  {
    for (packets_received = 0, file_done = 0, buf_ptr = buf; ;)
    {
      switch (Receive_Packet(packet_data, &packet_length, NAK_TIMEOUT))
      {
        case 0:
          errors = 0;
          switch (packet_length)
          {
            // Be cancled
            case - 1:
              SerialPutChar(ACK);
              return 0;
            //Transfer aborted
            case 0:
              SerialPutChar(ACK);
              file_done = 1;
              break;
            // Package transfer
            default:
              if ((packet_data[PACKET_SEQNO_INDEX] & 0xff) != (packets_received & 0xff))
              {
                SerialPutChar(NAK);
              }
              else
              {
                if (packets_received == 0)
                {
                  // Package of file-name
                 if (packet_data[PACKET_HEADER] != 0)
                 {
                   for (i = 0, file_ptr = packet_data + PACKET_HEADER; (*file_ptr != 0) && (i < FILE_NAME_LENGTH);)
                   {
                     file_name[i++] = *file_ptr++;
                   }
                   file_name[i++] = '\0';
                   for (i = 0, file_ptr ++; (*file_ptr != ' ') && (i < FILE_SIZE_LENGTH);)
                   {
                     file_size[i++] = *file_ptr++;
                   }
                   file_size[i++] = '\0';
                                
                   // The size of package
                   Str2Int(file_size, &size); 

                   // Transfer end
                   if (size > (FLASH_SIZE - 1))
                   {
                     SerialPutChar(CA);
                     SerialPutChar(CA);
                     return -1;
                   }

                   NbrOfPage = FLASH_PagesMask(size);

                   // Flash erase
                   for (EraseCounter = 0; EraseCounter < NbrOfPage; EraseCounter++)
                   {
                     FLASH_SectorEraseUnderUnlock(FlashDestination + (PageSize * EraseCounter));
                   }
                   SerialPutChar(ACK);
                   SerialPutChar(CRC16);
                 }
                 // Has no file
                 else
                 {
                   SerialPutChar(ACK);
                   file_done = 1;
                   session_done = 1;
                   break;
                 }
               }
               // Package
               else
               {
                 memcpy(buf_ptr, packet_data + PACKET_HEADER, packet_length);
                 RamSource = (uint32_t)buf;
                 for (j = 0; (j < packet_length) && (FlashDestination <  ApplicationAddress + size); j += 4)
                 {
                   // Flash program
                   FLASH_ProgramOneWord(FlashDestination, *(uint32_t*)RamSource);

                   if (*(uint32_t*)FlashDestination != *(uint32_t*)RamSource)
                   {
                     // end
                     SerialPutChar(CA);
                     SerialPutChar(CA);
                     return -2;
                   }
                   FlashDestination += 4;
                   RamSource += 4;
                 }
                 SerialPutChar(ACK);
               }
               packets_received ++;
               session_begin = 1;
             }
           }
           break;
         case 1:
           SerialPutChar(CA);
           SerialPutChar(CA);
           return -3;
         default:
           if (session_begin > 0)
           {
             errors ++;
           }
           if (errors > MAX_ERRORS)
           {
             SerialPutChar(CA);
             SerialPutChar(CA);
             return 0;
           }
           SerialPutChar(CRC16);
           break;
         }
         if (file_done != 0)
         {
           break;
         }
      }
    if (session_done != 0)
    {
      break;
    }
  }
  return (int32_t)size;
}

/**
  * @brief  Check response
  * @param  c
  * @retal  0
**/
int32_t Ymodem_CheckResponse(uint8_t c)
{
    return 0;
}

/**
  * @brief   Initial packet
  * @param   data
             fileName 
             length
  * @retal   None
**/
void Ymodem_PrepareIntialPacket(uint8_t *data, const uint8_t* fileName, uint32_t *length)
{
  uint16_t i, j;
  uint8_t file_ptr[10];

  data[0] = SOH;
  data[1] = 0x00;
  data[2] = 0xff;
  for (i = 0; ((fileName[i] != '\0') && (i < FILE_NAME_LENGTH)); i++)
  {
    data[i + PACKET_HEADER] = fileName[i];
  }

  data[i + PACKET_HEADER] = 0x00;

  Int2Str (file_ptr, *length);
  for (j =0, i = i + PACKET_HEADER + 1; file_ptr[j] != '\0' ; )
  {
    data[i++] = file_ptr[j++];
  }

  for (j = i; j < PACKET_SIZE + PACKET_HEADER; j++)
  {
    data[j] = 0;
  }
}

/**
  * @brief   Prepare packet
  * @param   SourceBuf：
             data：
             pktNo ：
             sizeBlk ：
  * @retal   None
**/
void Ymodem_PreparePacket(uint8_t *SourceBuf, uint8_t *data, uint8_t pktNo, uint32_t sizeBlk)
{
  uint16_t i, size, packetSize;
  uint8_t* file_ptr;

  packetSize = sizeBlk >= PACKET_1K_SIZE ? PACKET_1K_SIZE : PACKET_SIZE;
  size = sizeBlk < packetSize ? sizeBlk :packetSize;//sizeBlk<=packetsize size = sizeBlk, ize=packetsize
    
  if (packetSize == PACKET_1K_SIZE)
  {
    data[0] = STX;
  }
  else
  {
    data[0] = SOH;
  }
  data[1] = pktNo;
  data[2] = (~pktNo);
  file_ptr = SourceBuf;

  for (i = PACKET_HEADER; i < size + PACKET_HEADER; i++)
  {
    data[i] = *file_ptr++;
  }
  if ( size  <= packetSize)
  {
    for (i = size + PACKET_HEADER; i < packetSize + PACKET_HEADER; i++)
    {
      data[i] = 0x1A; // end
    }
  }
}

/**
  * @brief   Update CRC
  * @param   crcIn
             byte
  * @retal   CRC value
**/
uint16_t UpdateCRC16(uint16_t crcIn, uint8_t byte)
{
  uint32_t crc = crcIn;
  uint32_t in = byte|0x100;
  do
  {
    crc <<= 1;
    in <<= 1;
    if (in&0x100)
      ++crc;
    if (crc&0x10000)
      crc ^= 0x1021;
  }
  while (!(in&0x10000));
  return crc&0xffffu;
}

/**
  * @brief   Cal CRC value
  * @param   data
             size
  * @retal   CRC value
**/
uint16_t Cal_CRC16(const uint8_t* data, uint32_t size)
{
  uint32_t crc = 0;
  const uint8_t* dataEnd = data+size;
  while (data<dataEnd)
    crc = UpdateCRC16(crc,*data++);

  crc = UpdateCRC16(crc,0);
  crc = UpdateCRC16(crc,0);
  return crc&0xffffu;
}


/**
  * @brief   Get the size of YModem packet
  * @param   data 
             size
  * @retal   The size of packet
**/
uint8_t CalChecksum(const uint8_t* data, uint32_t size)
{
  uint32_t sum = 0;
  const uint8_t* dataEnd = data+size;
  while (data < dataEnd )
    sum += *data++;
  return sum&0xffu;
}

/**
  * @brief   ymodem Send packet
  * @param   data : the pointer of datas
             length：the length of packet
  * @retal   无
**/
void Ymodem_SendPacket(uint8_t *data, uint16_t length)
{
  uint16_t i;
  i = 0;
  while (i < length)
  {
    SerialPutChar(data[i]);
    i++;
  }
}

/**
  * @brief   ymodem send file
  * @param   buf: the pointer of  file
             sendFileName : String pointer of file-name
             sizeFile：the length of file
  * @retal   0: Fnction successed
**/
uint8_t Ymodem_Transmit (uint8_t *buf, const uint8_t* sendFileName, uint32_t sizeFile)
{
  uint8_t FileName[FILE_NAME_LENGTH];
  uint8_t *buf_ptr, tempCheckSum ;    
  uint8_t receivedC[2], CRC16_F = 0;
  uint8_t i;
  uint16_t tempCRC, blkNumber;
  uint32_t errors, ackReceived, size = 0, pktSize;

  errors = 0;
  ackReceived = 0;
  for (i = 0; i < (FILE_NAME_LENGTH - 1); i++)
  {
    FileName[i] = sendFileName[i];
  }
  CRC16_F = 1;

  // 1. prepare first packet
  Ymodem_PrepareIntialPacket(&packet_data[0], FileName, &sizeFile);

  do
  {
    // Send packet
    Ymodem_SendPacket(packet_data, PACKET_SIZE + PACKET_HEADER);
    // Send CRC checksum
    if (CRC16_F)
    {
      tempCRC = Cal_CRC16(&packet_data[3], PACKET_SIZE);
      SerialPutChar(tempCRC >> 8);
      SerialPutChar(tempCRC & 0xFF);
    }
    else
    {
      tempCheckSum = CalChecksum (&packet_data[3], PACKET_SIZE);
      SerialPutChar(tempCheckSum);
    }
         
    if (Receive_Byte(&receivedC[0], 1000000) == 0)         
    {    
      receivedC[1]=receivedC[0];
      if(Receive_Byte(&receivedC[0], 1000000) == 0)  
      {
        if ((receivedC[1] == ACK)&&(receivedC[0]==CRC16))
        {
          // packet be transferred
           ackReceived = 1;
        }
      }
    }
    else
    {
      errors++;
    }
  } while (!ackReceived && (errors < 0x0A));

  if (errors >=  0x0A)
  {   
    return errors;
  }
    
    
  buf_ptr = buf;
  size = sizeFile;
  blkNumber = 0x01;
    
  // 2. Send 1024 byte datas
  while (size)
  {
    // Prepare next packet
    Ymodem_PreparePacket(buf_ptr, &packet_data[0], blkNumber, size);
    ackReceived = 0;
    receivedC[0]= 0;
    errors = 0;
        
    do
    {
      // Send next packet
      if (size >= PACKET_1K_SIZE)
      {
        pktSize = PACKET_1K_SIZE;
      }
      else
      {
        pktSize = PACKET_SIZE;
      }
      Ymodem_SendPacket(packet_data, pktSize + PACKET_HEADER);
      // Send CRC checksum
      if (CRC16_F)
      {
        tempCRC = Cal_CRC16(&packet_data[3], pktSize);
        SerialPutChar(tempCRC >> 8);
        SerialPutChar(tempCRC & 0xFF);
      }
      else
      {
        tempCheckSum = CalChecksum (&packet_data[3], pktSize);
        //SerialPutChar(tempCheckSum);
        SerialPutChar(tempCheckSum);
      }

      // Wait for response
      if ((Receive_Byte(&receivedC[0], 100000) == 0)  && (receivedC[0] == ACK))
      {
        ackReceived = 1;
        if (size > pktSize)
        {
          buf_ptr += pktSize;
          size -= pktSize;
          if (blkNumber == (FLASH_IMAGE_SIZE/1024))
          {
            return 0xFF; // Error
          }
          else
          {
            blkNumber++;
          }
        }
        else
        {
          buf_ptr += pktSize;
          size = 0;
        }
      }
      else
      {
        errors++;
      }
    } while (!ackReceived && (errors < 0x0A));

    // Return error
    if (errors >=  0x0A)
    {
      return errors;
    }
  }
    
  // 3. Send EOT
  ackReceived = 0;
  receivedC[0] = 0x00;
  errors = 0;
  do
  {
    SerialPutChar(EOT);
    // Send (EOT);
    // Wait for response
    if ((Receive_Byte(&receivedC[0], 10000) == 0)  && receivedC[0] == ACK)
    {
      ackReceived = 1;
    }
    else
    {
      errors++;
    }
  } while (!ackReceived && (errors < 0x0A));

  if (errors >=  0x0A)
  {
    return errors;
  }

  // Prepare last packet, SOH 00 FF NUL[128] CRC CRC
  ackReceived = 0;
  receivedC[0] = 0x00;
  errors = 0;

  packet_data[0] = SOH;
  packet_data[1] = 0x00;
  packet_data [2] = 0xFF;

  for (i = PACKET_HEADER; i < (PACKET_SIZE + PACKET_HEADER); i++)
  {
    packet_data[i] = 0x00;
  }

  do
  {
    // Send datas' packet
    Ymodem_SendPacket(packet_data, PACKET_SIZE + PACKET_HEADER);
    // Send CRC checksum
    tempCRC = Cal_CRC16(&packet_data[3], PACKET_SIZE);
    SerialPutChar(tempCRC >> 8);
    SerialPutChar(tempCRC & 0xFF);

    // Wait for response   
    if (Receive_Byte(&receivedC[0], 10000) == 0)
    {
      if (receivedC[0] == ACK)
      {
        ackReceived = 1;
      }
    }
    else
    {
      errors++;
    }
  } while (!ackReceived && (errors < 0x0A));

    // Return error
    if (errors >=  0x0A)
    {
        return errors;
    }
    
    return 0; 
}

/*********************************** END OF FILE ******************************/
