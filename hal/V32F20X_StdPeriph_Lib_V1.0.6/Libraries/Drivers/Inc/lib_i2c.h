/**
  ******************************************************************************
  * @file    lib_i2c.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-10-18
  * @brief   Clock library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_IIC_H
#define __LIB_IIC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/*
// I2C Instances
*/
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
#define IS_I2C_ALL_INSTANCE(__INSTANCE__)  (((__INSTANCE__) == I2C0) ||\
                                            ((__INSTANCE__) == I2C1) ||\
                                            ((__INSTANCE__) == I2C2) ||\
                                            ((__INSTANCE__) == I2C3) ||\
                                            ((__INSTANCE__) == I2C4) ||\
                                            ((__INSTANCE__) == I2C5) ||\
                                            ((__INSTANCE__) == I2C6) ||\
                                            ((__INSTANCE__) == I2C7) ||\
                                            ((__INSTANCE__) == I2C8) ||\
                                            ((__INSTANCE__) == I2C9) ||\
                                            ((__INSTANCE__) == I2C10)||\
                                            ((__INSTANCE__) == I2C11)||\
                                            ((__INSTANCE__) == I2C12)||\
                                            ((__INSTANCE__) == I2C13)||\
                                            ((__INSTANCE__) == I2C14))

#else
#define IS_I2C_ALL_INSTANCE(__INSTANCE__)  (((__INSTANCE__) == I2C14) )
#endif
typedef struct
{
  uint32_t Mode;
  uint32_t SlaveAddress;
  uint32_t OwnAddress;
  uint16_t Restart;
  uint16_t SpeedMode;
  uint16_t MasterAddressingMode;
  uint16_t RespondsAddressingMode;
} I2C_InitType;
//Mode
#define I2C_MODE_MASTER                (0x00000041UL)
#define I2C_MODE_SLAVE                 (0x00000000UL)
#define IS_I2C_MODE(__MODE__)          (((__MODE__) == I2C_MODE_MASTER) ||\
                                        ((__MODE__) == I2C_MODE_SLAVE))
//Restart
#define I2C_RESTART_ENABLE             (0x00000020UL)
#define I2C_RESTART_DISABLE            (0x00000000UL)
#define IS_I2C_RESTART(__RESTART__)    (((__RESTART__) == I2C_RESTART_ENABLE) ||\
                                        ((__RESTART__) == I2C_RESTART_DISABLE))
//SpeedMode
#define I2C_SPEEDMODE_STANDARD         (0x00000002UL)
#define I2C_SPEEDMODE_FAST             (0x00000004UL)
#define IS_I2C_SPEEDMODE(__SPEED__)    (((__SPEED__) == I2C_SPEEDMODE_STANDARD) ||\
                                        ((__SPEED__) == I2C_SPEEDMODE_FAST))
//MasterAddressingMode
#define I2C_MASTERADDR_7B              (0x00000000UL)
#define I2C_MASTERADDR_10B             (0x00001000UL)
#define IS_I2C_MASTERADDR(__MODE__)    (((__MODE__) == I2C_MASTERADDR_7B) ||\
                                        ((__MODE__) == I2C_MASTERADDR_10B))
//RespondsAddressingMode
#define I2C_RESPADDR_7B                (0x00000000UL)
#define I2C_RESPADDR_10B               (0x00000008UL)
#define IS_I2C_RESPADDR(__MODE__)      (((__MODE__) == I2C_RESPADDR_7B) ||\
                                        ((__MODE__) == I2C_RESPADDR_10B))
//INT
#define I2C_INT_RX_DONE                (0x80000000UL|(1UL<<7))
#define I2C_INT_RD_REQ                 (0x40000000UL|(1UL<<5))
#define I2C_INT_TX_EMPTY               (0x20000000UL|(1UL<<4))
#define I2C_INT_TX_OVER                (0x10000000UL|(1UL<<3))
#define I2C_INT_TX_ABORT               (0x08000000UL|(1UL<<6))
#define I2C_INT_RXFULL                 (0x04000000UL|(1UL<<2))
#define I2C_INT_RXOVER                 (0x02000000UL|(1UL<<1))
#define I2C_INT_RXUNDER                (0x01000000UL|(1UL<<0))
#define I2C_INTEN_MASK                 (I2C_INT_RX_DONE \
                                       |I2C_INT_RD_REQ \
                                       |I2C_INT_TX_EMPTY \
                                       |I2C_INT_TX_OVER \
                                       |I2C_INT_RXFULL \
                                       |I2C_INT_RXOVER \
                                       |I2C_INT_TX_ABORT \
                                       |I2C_INT_RXUNDER)
#define I2C_INTCLR_MASK                (I2C_INT_RX_DONE \
                                       |I2C_INT_RD_REQ \
                                       |I2C_INT_TX_OVER \
                                       |I2C_INT_RXOVER \
                                       |I2C_INT_TX_ABORT \
                                       |I2C_INT_RXUNDER)
#define IS_I2C_INTEN(__INT__)          ((((__INT__) & I2C_INTEN_MASK) != 0U) &&\
                                        (((__INT__) & ~I2C_INTEN_MASK) == 0U))
#define IS_I2C_INTGET(__INT__)         (((__INT__) == I2C_INT_RX_DONE) ||\
                                        ((__INT__) == I2C_INT_RD_REQ) ||\
                                        ((__INT__) == I2C_INT_TX_ABORT) ||\
                                        ((__INT__) == I2C_INT_TX_EMPTY) ||\
                                        ((__INT__) == I2C_INT_TX_OVER) ||\
                                        ((__INT__) == I2C_INT_RXFULL) ||\
                                        ((__INT__) == I2C_INT_RXOVER) ||\
                                        ((__INT__) == I2C_INT_RXUNDER))
#define IS_I2C_INTCLR(__INT__)         ((((__INT__) & I2C_INTCLR_MASK) != 0U) &&\
                                        (((__INT__) & ~I2C_INTCLR_MASK) == 0U))
//Status
#define I2C_FLAG_ACTIVE                 (1UL << 0)
#define I2C_FLAG_TFNE                   (1UL << 1)           //Tx FIFO not full
#define I2C_FLAG_TFE                    (1UL << 2)           //Tx FIFO is empty
#define I2C_FLAG_RFNE                   (1UL << 3)           //Rx FIFO is not empty
#define I2C_FLAG_RFF                    (1UL << 4)           //Rx FIFO is full
#define I2C_FLAG_MST_ACTIVITY           (1UL << 5)
#define I2C_FLAG_SLV_ACTIVITY           (1UL << 6)
#define I2C_FLAG_MST_HOLD_TX_FIFO_EMPTY (1UL << 7)
#define I2C_FLAG_MST_HOLD_RX_FIFO_FULL  (1UL << 8)
#define I2C_FLAG_SLV_HOLD_TX_FIFO_EMPTY (1UL << 9)
#define I2C_FLAG_SLV_HOLD_RX_FIFO_FULL  (1UL << 10)
#define IS_I2C_FLAGR(__FLAGR__)         (((__FLAGR__) == I2C_FLAG_ACTIVE) ||\
                                        ((__FLAGR__) == I2C_FLAG_TFNE) ||\
                                        ((__FLAGR__) == I2C_FLAG_TFE) ||\
                                        ((__FLAGR__) == I2C_FLAG_RFNE) ||\
                                        ((__FLAGR__) == I2C_FLAG_RFF) ||\
                                        ((__FLAGR__) == I2C_FLAG_MST_ACTIVITY) ||\
                                        ((__FLAGR__) == I2C_FLAG_SLV_ACTIVITY) ||\
                                        ((__FLAGR__) == I2C_FLAG_MST_HOLD_TX_FIFO_EMPTY) ||\
                                        ((__FLAGR__) == I2C_FLAG_MST_HOLD_RX_FIFO_FULL) ||\
                                        ((__FLAGR__) == I2C_FLAG_SLV_HOLD_TX_FIFO_EMPTY) ||\
                                        ((__FLAGR__) == I2C_FLAG_SLV_HOLD_RX_FIFO_FULL))
//I2C_Command
#define I2C_CMD_WRITE                  (0UL)
#define I2C_CMD_READ                   (0x100UL)
#define I2C_CMD_STOP                   (0x200UL)
#define I2C_CMD_RESTART                (0x400UL)
#define I2C_CMD_WRITE_STOP             (I2C_CMD_WRITE | I2C_CMD_STOP)
#define I2C_CMD_WRITE_RESTART          (I2C_CMD_WRITE | I2C_CMD_RESTART)
#define I2C_CMD_READ_STOP              (I2C_CMD_READ | I2C_CMD_STOP)
#define I2C_CMD_READ_RESTART           (I2C_CMD_READ | I2C_CMD_RESTART)
#define I2C_CMD_READ_RESTART_STOP      (I2C_CMD_READ | I2C_CMD_RESTART | I2C_CMD_STOP)
#define IS_I2C_CMD(__CMD__)           (((__CMD__) == I2C_CMD_WRITE) ||\
                                       ((__CMD__) == I2C_CMD_READ) ||\
                                       ((__CMD__) == I2C_CMD_STOP) ||\
                                       ((__CMD__) == I2C_CMD_RESTART) ||\
                                       ((__CMD__) == I2C_CMD_WRITE_STOP) ||\
                                       ((__CMD__) == I2C_CMD_WRITE_RESTART) ||\
                                       ((__CMD__) == I2C_CMD_READ_STOP) ||\
                                       ((__CMD__) == I2C_CMD_READ_RESTART) ||\
                                       ((__CMD__) == I2C_CMD_READ_RESTART_STOP))
//TXFLEV
#define I2C_TXFLEV_0                   (0UL)
#define I2C_TXFLEV_1                   (1UL)
#define I2C_TXFLEV_2                   (2UL)
#define I2C_TXFLEV_3                   (3UL)
#define I2C_TXFLEV_4                   (4UL)
#define I2C_TXFLEV_5                   (5UL)
#define I2C_TXFLEV_6                   (6UL)
#define I2C_TXFLEV_7                   (7UL)
#define IS_I2C_TXFLEV(__TXFLEV__)     (((__TXFLEV__) == I2C_TXFLEV_0) ||\
                                       ((__TXFLEV__) == I2C_TXFLEV_1) ||\
                                       ((__TXFLEV__) == I2C_TXFLEV_2) ||\
                                       ((__TXFLEV__) == I2C_TXFLEV_3) ||\
                                       ((__TXFLEV__) == I2C_TXFLEV_4) ||\
                                       ((__TXFLEV__) == I2C_TXFLEV_5) ||\
                                       ((__TXFLEV__) == I2C_TXFLEV_6) ||\
                                       ((__TXFLEV__) == I2C_TXFLEV_7))
//RXFLEV
#define I2C_RXFLEV_0                   (0UL)
#define I2C_RXFLEV_1                   (1UL)
#define I2C_RXFLEV_2                   (2UL)
#define I2C_RXFLEV_3                   (3UL)
#define I2C_RXFLEV_4                   (4UL)
#define I2C_RXFLEV_5                   (5UL)
#define I2C_RXFLEV_6                   (6UL)
#define I2C_RXFLEV_7                   (7UL)
#define IS_I2C_RXFLEV(__RXFLEV__)      (((__RXFLEV__) == I2C_RXFLEV_0) ||\
                                        ((__RXFLEV__) == I2C_RXFLEV_1) ||\
                                        ((__RXFLEV__) == I2C_RXFLEV_2) ||\
                                        ((__RXFLEV__) == I2C_RXFLEV_3) ||\
                                        ((__RXFLEV__) == I2C_RXFLEV_4) ||\
                                        ((__RXFLEV__) == I2C_RXFLEV_5) ||\
                                        ((__RXFLEV__) == I2C_RXFLEV_6) ||\
                                        ((__RXFLEV__) == I2C_RXFLEV_7))

#define I2C_7B_ADDR_NOACK              (1UL << 0)
#define I2C_10ADDR1_NOACK              (1UL << 1)
#define I2C_10ADDR2_NOACK              (1UL << 2)
#define I2C_TXDATA_NOACK               (1UL << 3)
#define I2C_GCALL_NOACK                (1UL << 4)
#define I2C_GCALL_READ                 (1UL << 5)
#define I2C_SBYTE_ACKDET               (1UL << 7)
#define I2C_10B_RD_NORSTRT             (1UL << 10)
#define I2C_SLV_ARBLOST                (1UL << 14)
#define I2C_MASTER_LOST                (1UL << 12)
#define I2C_USER_ABRT                  (1UL << 16)
#define IS_I2C_TXABRT_STS(__STS__)     (((__STS__) == I2C_7B_ADDR_NOACK)  ||\
                                        ((__STS__) == I2C_10ADDR1_NOACK)  ||\
                                        ((__STS__) == I2C_10ADDR2_NOACK)  ||\
                                        ((__STS__) == I2C_TXDATA_NOACK)   ||\
                                        ((__STS__) == I2C_GCALL_NOACK)    ||\
                                        ((__STS__) == I2C_GCALL_READ)     ||\
                                        ((__STS__) == I2C_SBYTE_ACKDET)   ||\
                                        ((__STS__) == I2C_10B_RD_NORSTRT) ||\
                                        ((__STS__) == I2C_SLV_ARBLOST)    ||\
                                        ((__STS__) == I2C_MASTER_LOST)    ||\
                                        ((__STS__) == I2C_USER_ABRT))
                                        
#define I2C_DMACR_Mask                  (3UL << 0)
//I2C DMA
#define I2C_DMA_TX                      (1UL << 1)
#define I2C_DMA_RX                      (1UL << 0)
#define IS_I2C_DMA_CR(C)                (((C) == I2C_DMA_TX) || \
                                         ((C) == I2C_DMA_RX) || \
                                         ((C) == (I2C_DMA_TX|I2C_DMA_RX)))
                                                 
typedef struct
{
  uint8_t  SubAddrType;
  uint32_t PageRange;
  uint16_t SubAddress;
  uint8_t *pBuffer;
  uint32_t Length;
} I2C_WRType;
//SubAddrType
#define I2C_SUBADDR_1BYTE              (1U)
#define I2C_SUBADDR_2BYTE              (2U)
#define I2C_SUBADDR_OTHER              (3U)
#define I2C_SUBADDR_TYPE(__TYPE__)     (((__TYPE__) == I2C_SUBADDR_1BYTE) ||\
                                        ((__TYPE__) == I2C_SUBADDR_2BYTE) ||\
                                        ((__TYPE__) == I2C_SUBADDR_OTHER))
/* Exported Functions ------------------------------------------------------- */
void I2C_DeInit(I2C_Type *I2Cx);
void I2C_StructInit(I2C_InitType *I2C_InitStruct);
void I2C_Init(I2C_Type *I2Cx, I2C_InitType *I2C_InitStruct);
void I2C_INTConfig(I2C_Type *I2Cx, uint32_t INTMask, FunctionalState NewState);
ITStatus I2C_GetINTStatus(I2C_Type *I2Cx, uint32_t INTMask);
void I2C_ClearINTStatus(I2C_Type *I2Cx, uint32_t INTMask);
void I2C_ClearAllINTStatus(I2C_Type *I2Cx);
FlagStatus I2C_GetFlag(I2C_Type *I2Cx, uint32_t FlagMask);
FlagStatus I2C_GetTransmitAbortStatus(I2C_Type *I2Cx, uint32_t Status);
void I2C_SendCmdDataFrame(I2C_Type *I2Cx, uint16_t Command, uint8_t ch);
uint8_t I2C_ReceiveData(I2C_Type *I2Cx);
void I2C_Cmd(I2C_Type *I2Cx, FunctionalState NewState);
void I2C_TransmitFIFOLevelConfig(I2C_Type *I2Cx, uint32_t FIFOLevel);
void I2C_ReceiveFIFOLevelConfig(I2C_Type *I2Cx, uint32_t FIFOLevel);
uint8_t I2C_GetTransmitFIFOLevel(I2C_Type *I2Cx);
uint8_t I2C_GetReceiveFIFOLevel(I2C_Type *I2Cx);
void I2C_ClockFreqDutyConfig(I2C_Type *I2Cx, uint32_t SpeedMode, uint16_t DutyH, uint16_t DutyL);
/* CM33 I2C */
void I2C_DMACmd(I2C_Type* I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState);
void I2C_DMA_TxFIFOLevelConfig(I2C_Type* I2Cx, uint32_t TXFIFOLevel);
void I2C_DMA_RxFIFOLevelConfig(I2C_Type* I2Cx, uint32_t RXFIFOLevel);

#ifdef __cplusplus
}
#endif

#endif  /* __LIB_IIC_H */

/*********************************** END OF FILE ******************************/
