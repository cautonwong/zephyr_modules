/**
  * @file    lib_i2s.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-04-20
  * @brief   
******************************************************************************/

#ifndef __LIB_I2S_H
#define __LIB_I2S_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "target.h"

typedef struct
{
  uint32_t I2S_TransferMode;  /*!< Specifies the I2S transfer mode.*/

  uint32_t I2S_DataFormat;    /*!< Specifies the data esolution of the receiver and transmitter.*/

}I2S_InitType;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/*!<****************  Bit definition for I2S IER  ******************/
#define I2S_IER_IEN                        (1 << 0)

/*!<****************  Bit definition for I2S IRER  *****************/
#define I2S_IRER_RXEN                      (1 << 0)

/*!<****************  Bit definition for I2S ITER  *****************/
#define I2S_ITER_TXEN                      (1 << 0)

/*!<****************  Bit definition for I2S CER  ******************/
#define I2S_CER_CLKEN                      (1 << 0)

/*!<****************  Bit definition for I2S CCR  ******************/
#define I2S_CCR_SCLKG_CYCLES_NO            (0 << 0)
#define I2S_CCR_SCLKG_CYCLES_12            (1 << 0)
#define I2S_CCR_SCLKG_CYCLES_16            (2 << 0)
#define I2S_CCR_SCLKG_CYCLES_20            (3 << 0)
#define I2S_CCR_SCLKG_CYCLES_24            (4 << 0)
#define I2S_CCR_SCLKG_CYCLES_Mask          (7 << 0)
#define I2S_CCR_WSS_CYCLES_16              (0 << 3)
#define I2S_CCR_WSS_CYCLES_24              (1 << 3)
#define I2S_CCR_WSS_CYCLES_32              (2 << 3)
#define I2S_CCR_WSS_CYCLES_Mask            (3 << 3)

/*!<***************  Bit definition for I2S RXFFR  *****************/
#define I2S_RXFFR_EN                       (1 << 0)

/*!<****************  Bit definition for I2S TXFFR  ****************/
#define I2S_TXFFR_EN                       (1 << 0)

/*!<****************  Bit definition for I2S RER  ******************/
#define I2S_RER_RXCHEN                     (1 << 0)

/*!<****************  Bit definition for I2S TER  ******************/
#define I2S_TER_TXCHEN                     (1 << 0)

/*!<****************  Bit definition for I2S RCR  ******************/
#define I2S_RCR_WLEN_IGNORE                (0 << 0)
#define I2S_RCR_WLEN_12_BIT                (1 << 0)
#define I2S_RCR_WLEN_16_BIT                (2 << 0)
#define I2S_RCR_WLEN_20_BIT                (3 << 0)
#define I2S_RCR_WLEN_24_BIT                (4 << 0)
#define I2S_RCR_WLEN_32_BIT                (5 << 0)
#define I2S_RCR_WLEN_Mask                  (7 << 0)

/*!<****************  Bit definition for I2S TCR  ******************/
#define I2S_TCR_WLEN_IGNORE                (0 << 0)
#define I2S_TCR_WLEN_12_BIT                (1 << 0)
#define I2S_TCR_WLEN_16_BIT                (2 << 0)
#define I2S_TCR_WLEN_20_BIT                (3 << 0)
#define I2S_TCR_WLEN_24_BIT                (4 << 0)
#define I2S_TCR_WLEN_32_BIT                (5 << 0)
#define I2S_TCR_WLEN_Mask                  (7 << 0)

/*!<****************  Bit definition for I2S ISR  ******************/
#define I2S_ISR_RXDA                       (1 << 0)
#define I2S_ISR_RXFO                       (1 << 1)
#define I2S_ISR_TXFE                       (1 << 4)
#define I2S_ISR_TXFO                       (1 << 5)

/*!<****************  Bit definition for I2S IMR  ******************/
#define I2S_IMR_RXDAM                      (1 << 0)
#define I2S_IMR_RXFOM                      (1 << 1)
#define I2S_IMR_TXFEM                      (1 << 4)
#define I2S_IMR_TXFOM                      (1 << 5)

/*!<****************  Bit definition for I2S RFCR  *****************/
#define I2S_RFCR_RXCHDT_LEVEL_1             (0 << 0)
#define I2S_RFCR_RXCHDT_LEVEL_2             (1 << 0)
#define I2S_RFCR_RXCHDT_LEVEL_3             (2 << 0)
#define I2S_RFCR_RXCHDT_LEVEL_4             (3 << 0)
#define I2S_RFCR_RXCHDT_LEVEL_5             (4 << 0)
#define I2S_RFCR_RXCHDT_LEVEL_6             (5 << 0)
#define I2S_RFCR_RXCHDT_LEVEL_7             (6 << 0)
#define I2S_RFCR_RXCHDT_LEVEL_8             (7 << 0)
#define I2S_RFCR_RXCHDT_LEVEL_Mask          (0xF << 0)

/*!<****************  Bit definition for I2S TFCR  *****************/
#define I2S_TFCR_TXCHET_LEVEL_1             (0 << 0)
#define I2S_TFCR_TXCHET_LEVEL_2             (1 << 0)
#define I2S_TFCR_TXCHET_LEVEL_3             (2 << 0)
#define I2S_TFCR_TXCHET_LEVEL_4             (3 << 0)
#define I2S_TFCR_TXCHET_LEVEL_5             (4 << 0)
#define I2S_TFCR_TXCHET_LEVEL_6             (5 << 0)
#define I2S_TFCR_TXCHET_LEVEL_7             (6 << 0)
#define I2S_TFCR_TXCHET_LEVEL_8             (7 << 0)
#define I2S_TFCR_TXCHET_LEVEL_Mask          (0xF << 0)

/*!<****************  Bit definition for I2S RFF  ******************/
#define I2S_RFF_RXCHFR                      (1 << 0)

/*!<*****************  Bit definition for I2S TFF  *****************/
#define I2S_TFF_TXCHFR                      (1 << 0)

/*!<***************  Bit definition for I2S DMACR  *****************/
#define I2S_DMACR_DMAEN_RXCH                (1 << 0)
#define I2S_DMACR_DMAEN_TXCH                (1 << 8)
#define I2S_DMACR_DMAEN_RXBLOCK             (1 << 16)
#define I2S_DMACR_DMAEN_TXBLOCK             (1 << 17)
#define I2S_DMACR_Mask                      (0x30101UL)


//I2S_TransferMode
#define I2S_TransferMode_TX                    (2UL << 0)
#define I2S_TransferMode_RX                    (1UL << 0)
#define IS_I2S_TRANSFERMODE(MODE)              (((MODE) == I2S_TransferMode_TX) ||\
                                                ((MODE) == I2S_TransferMode_RX))
//I2S_DataFormat
#define I2S_DataFormat_12B_E16B                (I2S_RCR_WLEN_12_BIT | I2S_CCR_WSS_CYCLES_16)
#define I2S_DataFormat_12B_E24B                (I2S_RCR_WLEN_12_BIT | I2S_CCR_WSS_CYCLES_24)
#define I2S_DataFormat_12B_E32B                (I2S_RCR_WLEN_12_BIT | I2S_CCR_WSS_CYCLES_32)
#define I2S_DataFormat_16B                     (I2S_RCR_WLEN_16_BIT | I2S_CCR_WSS_CYCLES_16)
#define I2S_DataFormat_16B_E24B                (I2S_RCR_WLEN_16_BIT | I2S_CCR_WSS_CYCLES_24)
#define I2S_DataFormat_16B_E32B                (I2S_RCR_WLEN_16_BIT | I2S_CCR_WSS_CYCLES_32)
#define I2S_DataFormat_20B_E24B                (I2S_RCR_WLEN_20_BIT | I2S_CCR_WSS_CYCLES_24)
#define I2S_DataFormat_20B_E32B                (I2S_RCR_WLEN_20_BIT | I2S_CCR_WSS_CYCLES_32)
#define I2S_DataFormat_24B                     (I2S_RCR_WLEN_24_BIT | I2S_CCR_WSS_CYCLES_24)
#define I2S_DataFormat_24B_E32B                (I2S_RCR_WLEN_24_BIT | I2S_CCR_WSS_CYCLES_32)
#define I2S_DataFormat_32B                     (I2S_RCR_WLEN_32_BIT | I2S_CCR_WSS_CYCLES_32)
#define IS_I2S_DATAFORMAT(DF)                  (((DF) == I2S_DataFormat_12B_E16B) ||\
                                                ((DF) == I2S_DataFormat_12B_E24B) ||\
                                                ((DF) == I2S_DataFormat_12B_E32B) ||\
                                                ((DF) == I2S_DataFormat_16B)      ||\
                                                ((DF) == I2S_DataFormat_16B_E24B) ||\
                                                ((DF) == I2S_DataFormat_16B_E32B) ||\
                                                ((DF) == I2S_DataFormat_20B_E24B) ||\
                                                ((DF) == I2S_DataFormat_20B_E32B) ||\
                                                ((DF) == I2S_DataFormat_24B)      ||\
                                                ((DF) == I2S_DataFormat_24B_E32B) ||\
                                                ((DF) == I2S_DataFormat_32B))

//I2S_SCKGate
#define I2S_SCKGATE_NONE                        (I2S_CCR_SCLKG_CYCLES_NO)
#define I2S_SCKGATE_AFTER_12SCK                 (I2S_CCR_SCLKG_CYCLES_12)
#define I2S_SCKGATE_AFTER_16SCK                 (I2S_CCR_SCLKG_CYCLES_16)
#define I2S_SCKGATE_AFTER_20SCK                 (I2S_CCR_SCLKG_CYCLES_20)
#define I2S_SCKGATE_AFTER_24SCK                 (I2S_CCR_SCLKG_CYCLES_24)
#define IS_I2S_SCKGATE(SCKGATE)                 (((SCKGATE) == I2S_SCKGATE_NONE)        ||\
                                                 ((SCKGATE) == I2S_SCKGATE_AFTER_12SCK) ||\
                                                 ((SCKGATE) == I2S_SCKGATE_AFTER_16SCK) ||\
                                                 ((SCKGATE) == I2S_SCKGATE_AFTER_20SCK) ||\
                                                 ((SCKGATE) == I2S_SCKGATE_AFTER_24SCK))

//I2S TXFIFOLEVEL
#define I2S_FIFO_TX_THRESHOLD_1                I2S_TFCR_TXCHET_LEVEL_1
#define I2S_FIFO_TX_THRESHOLD_2                I2S_TFCR_TXCHET_LEVEL_2
#define I2S_FIFO_TX_THRESHOLD_3                I2S_TFCR_TXCHET_LEVEL_3
#define I2S_FIFO_TX_THRESHOLD_4                I2S_TFCR_TXCHET_LEVEL_4
#define I2S_FIFO_TX_THRESHOLD_5                I2S_TFCR_TXCHET_LEVEL_5
#define I2S_FIFO_TX_THRESHOLD_6                I2S_TFCR_TXCHET_LEVEL_6
#define I2S_FIFO_TX_THRESHOLD_7                I2S_TFCR_TXCHET_LEVEL_7
#define I2S_FIFO_TX_THRESHOLD_8                I2S_TFCR_TXCHET_LEVEL_8
#define IS_I2S_FIFO_TXLEVLE(S)                 (((S) == I2S_FIFO_TX_THRESHOLD_1) || \
                                                ((S) == I2S_FIFO_TX_THRESHOLD_2) || \
                                                ((S) == I2S_FIFO_TX_THRESHOLD_3) || \
                                                ((S) == I2S_FIFO_TX_THRESHOLD_4) || \
                                                ((S) == I2S_FIFO_TX_THRESHOLD_5) || \
                                                ((S) == I2S_FIFO_TX_THRESHOLD_6) || \
                                                ((S) == I2S_FIFO_TX_THRESHOLD_7) || \
                                                ((S) == I2S_FIFO_TX_THRESHOLD_8))
                                       
//I2S RXFIFOLEVEL
#define I2S_FIFO_RX_THRESHOLD_1                I2S_RFCR_RXCHDT_LEVEL_1
#define I2S_FIFO_RX_THRESHOLD_2                I2S_RFCR_RXCHDT_LEVEL_2
#define I2S_FIFO_RX_THRESHOLD_3                I2S_RFCR_RXCHDT_LEVEL_3
#define I2S_FIFO_RX_THRESHOLD_4                I2S_RFCR_RXCHDT_LEVEL_4
#define I2S_FIFO_RX_THRESHOLD_5                I2S_RFCR_RXCHDT_LEVEL_5
#define I2S_FIFO_RX_THRESHOLD_6                I2S_RFCR_RXCHDT_LEVEL_6
#define I2S_FIFO_RX_THRESHOLD_7                I2S_RFCR_RXCHDT_LEVEL_7
#define I2S_FIFO_RX_THRESHOLD_8                I2S_RFCR_RXCHDT_LEVEL_8
#define IS_I2S_FIFO_RXLEVLE(S)                (((S) == I2S_FIFO_RX_THRESHOLD_1) || \
                                               ((S) == I2S_FIFO_RX_THRESHOLD_2) || \
                                               ((S) == I2S_FIFO_RX_THRESHOLD_3) || \
                                               ((S) == I2S_FIFO_RX_THRESHOLD_4) || \
                                               ((S) == I2S_FIFO_RX_THRESHOLD_5) || \
                                               ((S) == I2S_FIFO_RX_THRESHOLD_6) || \
                                               ((S) == I2S_FIFO_RX_THRESHOLD_7) || \
                                               ((S) == I2S_FIFO_RX_THRESHOLD_8))
                                       

//I2S DMA
#define I2S_DMA_TX                    (I2S_DMACR_DMAEN_TXCH | I2S_DMACR_DMAEN_TXBLOCK)
#define I2S_DMA_RX                    (I2S_DMACR_DMAEN_RXCH | I2S_DMACR_DMAEN_RXBLOCK)
#define IS_I2S_DMA_CHANNEL(C)         (((C) == I2S_DMA_TX) || \
                                       ((C) == I2S_DMA_RX) || \
                                       ((C) == (I2S_DMA_TX|I2S_DMA_RX)))

//I2S_INT
#define I2S_INT_RXDA           I2S_ISR_RXDA 
#define I2S_INT_RXFO           I2S_ISR_RXFO 
#define I2S_INT_TXFE           I2S_ISR_TXFE 
#define I2S_INT_TXFO           I2S_ISR_TXFO 
#define IS_I2S_INT(INT)        (((INT) == I2S_INT_RXDA) || \
                                ((INT) == I2S_INT_RXFO) || \
                                ((INT) == I2S_INT_TXFE) || \
                                ((INT) == I2S_INT_TXFO))

/* Exported functions ------------------------------------------------------- */

//I2S
void I2S_DeInit(I2S_Type* I2Sx);
void I2S_StructInit(I2S_InitType* I2S_InitStruct);
void I2S_Init(I2S_Type* I2Sx, I2S_InitType* I2S_InitStruct);
void I2S_SCKGateConfig(I2S_Type* I2Sx, uint32_t I2S_SCKGate);
void I2S_Cmd(I2S_Type* I2Sx, FunctionalState NewState);
void I2S_DMACmd(I2S_Type* I2Sx, uint32_t I2S_DMAReq, FunctionalState NewState);

void I2S_LeftStereoSendData(I2S_Type* I2Sx, uint32_t Data);
void I2S_RightStereoSendData(I2S_Type* I2Sx, uint32_t Data);
uint32_t I2S_LeftStereoReceiveData(I2S_Type* I2Sx);
uint32_t I2S_RightStereoReceiveData(I2S_Type* I2Sx);

FlagStatus I2S_GetFlagStatus(I2S_Type* I2Sx, uint16_t I2S_FLAG);
void I2S_ITConfig(I2S_Type* I2Sx, uint16_t I2S_INT, FunctionalState NewState);
ITStatus I2S_GetITStatus(I2S_Type* I2Sx, uint16_t I2S_INT);
void I2S_ClearITStatus(I2S_Type* I2Sx, uint16_t I2S_INT);

void I2S_TxFIFOThresholdConfig(I2S_Type* I2Sx, uint32_t TXFIFOLevel);
void I2S_RxFIFOThresholdConfig(I2S_Type* I2Sx, uint32_t RXFIFOLevel);
uint16_t I2S_GetTxFIFOLevel(I2S_Type* I2Sx);
uint16_t I2S_GetRxFIFOLevel(I2S_Type* I2Sx);

void I2S_TransmitChannelFIFOReset(I2S_Type* I2Sx);
void I2S_ReceiveChannelFIFOReset(I2S_Type* I2Sx);
void I2S_TransmitBlockFIFOReset(I2S_Type* I2Sx);
void I2S_ReceiveBlockFIFOReset(I2S_Type* I2Sx);

#ifdef __cplusplus
}
#endif
#endif /* __LIB_I2S_H */

/*********************************** END OF FILE ******************************/