/**
  ******************************************************************************
  * @file    lib_uart.h 
  * @author  Application Team
  * @version V1.0
  * @date    2021-10-18
  * @brief   UART library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_UART_H
#define __LIB_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/*
// UART_DLAB register
*/
#define UART_DLAB_EN                   (0x80UL)
#define UART_DLAB_EN_CLR               REG_BIT_NOT(UART_DLAB_EN)
/*
// UART_LCR register
*/
#define UART_LCR_PARITY_MASK           (0x38UL)
#define UART_LCR_STOPBIT               (0x04UL)
#define UART_LCR_DATALEN_MASK          (0x03UL)
/*
// UART_FCR register
*/
#define UART_FCR_FIFOEN                (0x1UL)
#define UART_FCR_RXFIFORESET           (1UL << 1)
#define UART_FCR_TXFIFORESET           (1UL << 2)
#define UART_FCR_RT_MASK               (3UL << 6)
/*
// UART_LSR register
*/
#define UART_LSR_DR                    (1UL << 0)
#define UART_LSR_OE                    (1UL << 1)
#define UART_LSR_PE                    (1UL << 2)
#define UART_LSR_FE                    (1UL << 3)
#define UART_LSR_TEMT                  (1UL << 6)
#define UART_LSR_RFE                   (1UL << 7)
/*
// UART_IIR register
*/
#define UART_IIR_XFIFOR_MASK           (0xFUL)
#define UART_IIR_XFIFOR_BUSY_DETECT    (0x7UL)
#define UART_IIR_XFIFOR_RXFIFO_TIMEOUT (0xCUL)
#define UART_IIR_RT_FIFOEN             (3UL << 6)
/*
// UART_MCR register
*/
#define UART_MCR_IREN                  (1UL << 6)
#define UART_MCR_IREN_CLR              REG_BIT_NOT(UART_MCR_IREN)
/*
// UART_DLH register
*/
#define UART_DLH_DLH_MASK              (0xFFUL)
/*
// UART_DLL register
*/
#define UART_DLL_DLL_MASK              (0xFFUL)

// Registers' reset value
#define UART_MCR_RSTVAL                (0UL)
#define UART_DLL_RSTVAL                (0UL)
#define UART_DLH_RSTVAL                (0UL)
#define UART_LCR_RSTVAL                (0UL)
#define UART_IER_RSTVAL                (0UL)
#define UART_FCR_RSTVAL                (0UL)

#define UART_BASEADDR_OFFSET           (0x800UL)

typedef struct
{
  uint32_t Baudrate;
  uint32_t Parity;
  uint32_t DataLength;
  uint32_t StopBit;
  uint32_t SerialClock;
} UART_InitType;
//Parity
#define UART_PARITY_EVEN               (0x18UL)
#define UART_PARITY_ODD                (0x08UL)
#define UART_PARITY_0                  (0x38UL)
#define UART_PARITY_1                  (0x28UL)
#define UART_PARITY_NONE               (0x00UL)
#define IS_UART_PARITY(__PARITY__)     (((__PARITY__) == UART_PARITY_EVEN) ||\
                                        ((__PARITY__) == UART_PARITY_ODD) ||\
                                        ((__PARITY__) == UART_PARITY_0) ||\
                                        ((__PARITY__) == UART_PARITY_1) ||\
                                        ((__PARITY__) == UART_PARITY_NONE))
//SerialClock
#define IS_UART_SERIALCLK(__CLK__)     ((__CLK__) > 0)
//DataLength
#define UART_DATALEN_8B                (3UL)
#define UART_DATALEN_7B                (2UL)
#define UART_DATALEN_6B                (1UL)
#define UART_DATALEN_5B                (0UL)
#define IS_UART_DATALEN(__DATALEN__)   (((__DATALEN__) == UART_DATALEN_8B) ||\
                                        ((__DATALEN__) == UART_DATALEN_7B) ||\
                                        ((__DATALEN__) == UART_DATALEN_6B) ||\
                                        ((__DATALEN__) == UART_DATALEN_5B))
//StopBit
#define UART_STOPBIT_1                 (0x0UL)
#define UART_STOPBIT_1_5               (0x4UL)
#define UART_STOPBIT_2                 (0x4UL)
#define IS_UART_STOPBIT(__STOPBIT__)    (((__STOPBIT__) == UART_STOPBIT_1) ||\
                                         ((__STOPBIT__) == UART_STOPBIT_1_5) ||\
                                         ((__STOPBIT__) == UART_STOPBIT_2))

//RXFELEV
#define UART_FIFOLEVEL_1               (0UL << 6)
#define UART_FIFOLEVEL_4               (1UL << 6)
#define UART_FIFOLEVEL_8               (2UL << 6)
#define UART_FIFOLEVEL_14              (3UL << 6)
#define IS_UART_RXFLEV(__RXFLEV__)     (((__RXFLEV__) == UART_FIFOLEVEL_1) ||\
                                        ((__RXFLEV__) == UART_FIFOLEVEL_4) ||\
                                        ((__RXFLEV__) == UART_FIFOLEVEL_8) ||\
                                        ((__RXFLEV__) == UART_FIFOLEVEL_14))

//INT
#define UART_INT_RX                    (1UL << 0)
#define UART_INT_TXE                   (1UL << 1)
#define UART_INT_RXERR                 (1UL << 2)
#define UART_INT_RXERR_OV              (1UL << 3)
#define UART_INT_RXERR_PE              (1UL << 4)
#define UART_INT_RXERR_FE              (1UL << 5)
#define UART_INT_BUSY_DETECT           (1UL << 6)
#define UART_INT_RXFIFO_TIMEOUT        (1UL << 7)
#define UART_INTEN_MASK                (UART_INT_RX | UART_INT_TXE | UART_INT_RXERR)
#define UART_INTCLR_MASK               (UART_INT_RXERR | UART_INT_BUSY_DETECT)
#define IS_UART_INTEN(__INT__)         ((((__INT__) & UART_INTEN_MASK) != 0U) &&\
                                        (((__INT__) & ~UART_INTEN_MASK) == 0U))
#define IS_UART_INTGET(__INT__)        (((__INT__) == UART_INT_RX)          ||\
                                        ((__INT__) == UART_INT_TXE)         ||\
                                        ((__INT__) == UART_INT_RXERR)       ||\
                                        ((__INT__) == UART_INT_RXERR_OV)    ||\
                                        ((__INT__) == UART_INT_RXERR_PE)    ||\
                                        ((__INT__) == UART_INT_RXERR_FE)    ||\
                                        ((__INT__) == UART_INT_BUSY_DETECT) ||\
                                        ((__INT__) == UART_INT_RXFIFO_TIMEOUT))
#define IS_UART_INTCLR(__INT__)        ((((__INT__) & UART_INTCLR_MASK) != 0U) &&\
                                        (((__INT__) & ~UART_INTCLR_MASK) == 0U))

// FlagMask
#define UART_FLAG_RX                   (0x80000000UL | (1UL<<0))
#define UART_FLAG_RXERR                (0x80000000UL | (1UL<<7))
#define UART_FLAG_RXERR_OV             (0x80000000UL | (1UL<<1))
#define UART_FLAG_RXERR_PE             (0x80000000UL | (1UL<<2))
#define UART_FLAG_RXERR_FE             (0x80000000UL | (1UL<<3))
#define UART_FLAG_BREAK_INT            (0x80000000UL | (1UL<<4))
#define UART_FLAG_TXE                  (0x80000000UL | (1UL<<6))
#define UART_FLAG_RXFIFO_USED          (0x40000000UL | (3UL<<6))
#define IS_UART_FLAGGET(__FLAG__)      (((__FLAG__) == UART_FLAG_RX)        ||\
                                        ((__FLAG__) == UART_FLAG_RXERR)     ||\
                                        ((__FLAG__) == UART_FLAG_RXERR_OV)  ||\
                                        ((__FLAG__) == UART_FLAG_RXERR_PE)  ||\
                                        ((__FLAG__) == UART_FLAG_RXERR_FE)  ||\
                                        ((__FLAG__) == UART_FLAG_BREAK_INT) ||\
                                        ((__FLAG__) == UART_FLAG_TXE)       ||\
                                        ((__FLAG__) == UART_FLAG_RXFIFO_USED))

/* Exported Functions ------------------------------------------------------- */
void UART_DeInit(UART_Type *UARTx);
void UART_StructInit(UART_InitType *UART_InitStruct);
void UART_Init(UART_Type *UARTx, UART_InitType *UART_InitStruct);

void UART_ReceiveFIFOConfig(UART_Type *UARTx, uint32_t Level, FunctionalState NewState);

void UART_INTConfig(UART_Type *UARTx, uint32_t INTMask, uint32_t NewState);
ITStatus UART_GetINTStatus(UART_Type *UARTx, uint32_t INTMask);
void UART_ClearINTStatus(UART_Type *UARTx, uint32_t INTMask);
FlagStatus UART_GetFlag(UART_Type *UARTx, uint32_t FlagMask);
uint8_t UART_GetINTPendingStatus(UART_Type *UARTx);

void UART_SendData(UART_Type *UARTx, uint8_t ch);
uint8_t UART_ReceiveData(UART_Type *UARTx);

void UART_IrDASIRCmd(UART_Type *UARTx, uint32_t NewState);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_UART_H */

/*********************************** END OF FILE ******************************/
