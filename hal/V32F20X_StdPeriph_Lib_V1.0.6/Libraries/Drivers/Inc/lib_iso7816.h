/**
  ******************************************************************************
  * @file    lib_iso7816.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-07-06
  * @brief   ISO7816 library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_ISO7816_H
#define __LIB_ISO7816_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
#define IS_ISO7816_ALL_INSTANCE(__INSTANCE__) (((__INSTANCE__) == ISO78160) ||\
                                               ((__INSTANCE__) == ISO78161) ||\
                                               ((__INSTANCE__) == ISO78162) ||\
                                               ((__INSTANCE__) == ISO78163))
#else
#define IS_ISO7816_ALL_INSTANCE(__INSTANCE__) (((__INSTANCE__) == ISO78162) ||\
                                               ((__INSTANCE__) == ISO78163))
#endif /* _USE_CM33 */

typedef struct
{
  uint32_t FirstBit;
  uint32_t Parity;
  uint32_t SerialClock;
  uint32_t Baudrate;
  uint32_t TXRetry;
  uint32_t RXACKLength;
  uint32_t TXNACKLength;
} ISO7816_InitType;
//FirstBit
#define ISO7816_FIRSTBIT_MSB           (0x0UL)
#define ISO7816_FIRSTBIT_LSB           (0x800UL)
#define IS_ISO7816_FIRSTBIT(__FIRSTBIT__)  (((__FIRSTBIT__) == ISO7816_FIRSTBIT_MSB) ||\
                                            ((__FIRSTBIT__) == ISO7816_FIRSTBIT_LSB))
//Parity
#define ISO7816_PARITY_EVEN            (0UL)
#define ISO7816_PARITY_ODD             (0x2UL)
#define IS_ISO7816_PARITY(__PARITY__)  (((__PARITY__) == ISO7816_PARITY_EVEN) ||\
                                        ((__PARITY__) == ISO7816_PARITY_ODD))
//Baudrate
#define IS_ISO7816_BAUDRATE(__BAUDRATE__) ((200UL <= (__BAUDRATE__)) &&\
                                          ((__BAUDRATE__) <= 2625000UL))
//TXRetry
#define ISO7816_TXRTY_0            ((0x00U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_1            ((0x01U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_2            ((0x02U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_3            ((0x03U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_4            ((0x04U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_5            ((0x05U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_6            ((0x06U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_7            ((0x07U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_8            ((0x08U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_9            ((0x09U << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_10           ((0x0AU << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_11           ((0x0BU << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_12           ((0x0CU << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_13           ((0x0DU << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_14           ((0x0EU << 12) \
                                   | (1U << 10))
#define ISO7816_TXRTY_15           ((0x0FU << 12) \
                                   | (1U << 10))
#define IS_ISO7816_TXRTY(__TXRTY__)          (((__TXRTY__) == ISO7816_TXRTY_0)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_1)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_2)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_3)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_4)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_5)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_6)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_7)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_8)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_9)     || \
                                              ((__TXRTY__) == ISO7816_TXRTY_10)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_11)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_12)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_13)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_14)    || \
                                              ((__TXRTY__) == ISO7816_TXRTY_15))
//RXACKLength
#define ISO7816_RXACKLEN_2             (0UL)
#define ISO7816_RXACKLEN_1             (0x10000UL)
#define IS_ISO7816_RXACKLEN(__RXACKLEN__)  (((__RXACKLEN__) == ISO7816_RXACKLEN_2) ||\
                                            ((__RXACKLEN__) == ISO7816_RXACKLEN_1))
//TXNACKLength
#define ISO7816_TXNACKLEN_0            (0UL)
#define ISO7816_TXNACKLEN_1            (0x200UL)
#define ISO7816_TXNACKLEN_2            (0x200UL | 0x10UL)
#define IS_ISO7816_TXNACKLEN(__TXNACKLEN__)  (((__TXNACKLEN__) == ISO7816_TXNACKLEN_0) ||\
                                              ((__TXNACKLEN__) == ISO7816_TXNACKLEN_1) ||\
                                              ((__TXNACKLEN__) == ISO7816_TXNACKLEN_2))

#define IS_ISO7816_PRESCALER(__PRESCALER__)  ((__PRESCALER__) <= 0x80)

//SerialClock
#define IS_ISO7816_SERIALCLK(__CLK__)     ((__CLK__) > 0)

//interrupt
#define ISO7816_INT_TXRTYERR           (0x100UL)
#define ISO7816_INT_RXOV               (0x80UL)
#define ISO7816_INT_TXDONE             (0x40UL)
#define ISO7816_INT_RX                 (0x20UL)
#define ISO7816_INT_RXERR              (0x4UL)
#define ISO7816_INT_MASK               (ISO7816_INT_TXRTYERR  \
                                       |ISO7816_INT_RXOV      \
                                       |ISO7816_INT_TXDONE    \
                                       |ISO7816_INT_RX        \
                                       |ISO7816_INT_RXERR)
#define IS_ISO7816_INTC(__INT__)       ((((__INT__) & ISO7816_INT_MASK) != 0U) &&\
                                        (((__INT__) & ~ISO7816_INT_MASK) == 0U))   
#define IS_ISO7816_INTR(__INT__)       (((__INT__) == ISO7816_INT_TXRTYERR) ||\
                                        ((__INT__) == ISO7816_INT_RXOV)     ||\
                                        ((__INT__) == ISO7816_INT_TXDONE)   ||\
                                        ((__INT__) == ISO7816_INT_RX)       ||\
                                        ((__INT__) == ISO7816_INT_RXERR))
//status
#define ISO7816_FLAG_DMATXDONE         (0x200UL)
#define IS_ISO7816_FLAG(__FLAG__)      ((__FLAG__) == ISO7816_FLAG_DMATXDONE)


/* Exported Functions ------------------------------------------------------- */
void ISO7816_DeInit(ISO7816_Type *ISO7816x);
void ISO7816_StructInit(ISO7816_InitType *InitStruct);
void ISO7816_Init(ISO7816_Type *ISO7816x, ISO7816_InitType *ISO7816_InitStruct);

void ISO7816_Cmd(ISO7816_Type *ISO7816x, FunctionalState NewState);

void ISO7816_CLKDIVConfig(ISO7816_Type *ISO7816x, uint32_t Prescaler);
void ISO7816_CLKOutputCmd(ISO7816_Type *ISO7816x, FunctionalState NewState);

uint8_t ISO7816_ReceiveData(ISO7816_Type *ISO7816x);
void ISO7816_SendData(ISO7816_Type *ISO7816x, uint8_t ch);

void ISO7816_INTConfig(ISO7816_Type *ISO7816x, uint32_t INTMask, FunctionalState NewState);
ITStatus ISO7816_GetINTStatus(ISO7816_Type *ISO7816x, uint32_t INTMask);
void ISO7816_ClearINTStatus(ISO7816_Type *ISO7816x, uint32_t INTMask);

FlagStatus ISO7816_GetFlag(ISO7816_Type *ISO7816x, uint32_t FlagMask);
void ISO7816_ClearFlag(ISO7816_Type *ISO7816x, uint32_t FlagMask);

uint8_t ISO7816_GetLastTransmitACK(ISO7816_Type *ISO7816x);
uint8_t ISO7816_GetLastReceiveCHKSUM(ISO7816_Type *ISO7816x);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_ISO7816_H */

/*********************************** END OF FILE ******************************/
