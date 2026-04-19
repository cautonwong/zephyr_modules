/**
  ******************************************************************************
  * @file    i2c_ee.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-12
  * @brief   1. Read and write EEPROM
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __I2C_EE_H
#define __I2C_EE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
#include "board.h"

#define u8                       uint8_t
#define u16                      uint16_t
#define u32                      uint32_t

//#define I2C_PageSize                  8

//#define I2C_PageSize                  16

#define I2C_PageSize                    (128)

#define EEPROM_I2C                      I2C14

#define I2CT_FLAG_TIMEOUT               ((uint32_t)0x10)
#define I2CT_LONG_TIMEOUT               ((uint32_t)(1000 * I2CT_FLAG_TIMEOUT))

#define EEPROM_DEBUG_ON                 0

#define EEPROM_INFO(fmt,arg...)         printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define EEPROM_ERROR(fmt,arg...)        printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define EEPROM_DEBUG(fmt,arg...)        do{\
                                        if(EEPROM_DEBUG_ON)\
                                        printf("<<-EEPROM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                        }while(0)

#define EE_Normal                       (0x01)
#define EE_Crossing_Page                (0x02)

#define I2C_TRANSFER_SIZE               (256UL)
#define EEP_Firstpage                   (0x00)
/*
 * AT24C512 64kB
 * 512 pages of 128 bytes each
 *
 * Device Address
 * 1 0 1 0 A2 A1 A0 R/W
 * 1 0 1 0 0  0  0  0 = 0XA0
 * 1 0 1 0 0  0  0  1 = 0XA1 
 */

/* EEPROM Addresses defines */
#define EEPROM_Block0_ADDRESS           0xA0

void I2C_EE_Init(void);
void I2C_EE_BufferWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite);
uint32_t I2C_EE_ByteWrite(u8* pBuffer, u16 WriteAddr);
uint32_t I2C_EE_PageWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite);
uint32_t I2C_EE_BufferRead(u8* pBuffer, u16 ReadAddr, u16 NumByteToRead);
void I2C_EE_WaitForCrossPage(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __I2C_EE_H */

/*********************************** END OF FILE ******************************/
