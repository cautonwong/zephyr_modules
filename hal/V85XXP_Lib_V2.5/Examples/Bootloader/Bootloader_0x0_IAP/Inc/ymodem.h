/**
  ******************************************************************************
  * @file    ymodem.h
  * @author  Application Team
  * @version V4.3.0
  * @date    2018-09-04
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#ifndef _YMODEM_H_
#define _YMODEM_H_

#include "stdint.h"

/* Definitions ---------------------------------------------------------------*/
#define PACKET_SEQNO_INDEX      (1)
#define PACKET_SEQNO_COMP_INDEX (2)

#define PACKET_HEADER           (3)
#define PACKET_TRAILER          (2)
#define PACKET_OVERHEAD         (PACKET_HEADER + PACKET_TRAILER)
#define PACKET_SIZE             (128)
#define PACKET_1K_SIZE          (1024)

#define FILE_NAME_LENGTH        (256)
#define FILE_SIZE_LENGTH        (16)

#define SOH                     (0x01)  //Start @ 128 byte
#define STX                     (0x02)  //Start @ 1024 byte
#define EOT                     (0x04)  //End
#define ACK                     (0x06)  //Response
#define NAK                     (0x15)  //No response
#define CA                      (0x18)  //Aborted
#define CRC16                   (0x43)  //'C' == 0x43, 16-bit CRC 

#define ABORT1                  (0x41)  //'A' == 0x41, User aborted
#define ABORT2                  (0x61)  //'a' == 0x61, User aborted

#define NAK_TIMEOUT             (0x100000)
#define MAX_ERRORS              (5)

/*- Exported Function --------------------------------------------------------*/
int32_t Ymodem_Receive (uint8_t *buf);
uint8_t Ymodem_Transmit (uint8_t *buf, const uint8_t* sendFileName, uint32_t sizeFile);

#endif  /* _YMODEM_H_ */

/*********************************** END OF FILE ******************************/
