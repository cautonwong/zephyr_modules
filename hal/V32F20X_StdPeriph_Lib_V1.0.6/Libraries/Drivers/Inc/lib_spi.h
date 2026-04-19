/**
  * @file    lib_spi.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-10-18
  * @brief   CM33 SPI library.
******************************************************************************/

#ifndef __LIB_SPI_H
#define __LIB_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "target.h"

#define IS_SPI_ALL_INSTANCE(__INSTANCE__)  (((__INSTANCE__) == SPI0)   ||\
                                            ((__INSTANCE__) == SPI1)   ||\
                                            ((__INSTANCE__) == SPI2)   ||\
                                            ((__INSTANCE__) == SPI3)   ||\
                                            ((__INSTANCE__) == SPI4)   ||\
                                            ((__INSTANCE__) == SPI5)   ||\
                                            ((__INSTANCE__) == SPI6)   ||\
                                            ((__INSTANCE__) == SPI7)   ||\
                                            ((__INSTANCE__) == SPI8)   ||\
                                            ((__INSTANCE__) == SPI9)   ||\
                                            ((__INSTANCE__) == SPI10)  ||\
                                            ((__INSTANCE__) == SPI11)  ||\
                                            ((__INSTANCE__) == SPI12)  ||\
                                            ((__INSTANCE__) == SPI13))


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/*!<****************  Bit definition for SPI CTRLR0  *****************/
#define SPI_CTRLR0_DFS_1BIT              (0x0UL << 16)
#define SPI_CTRLR0_DFS_2BIT              (0x1UL << 16)
#define SPI_CTRLR0_DFS_3BIT              (0x2UL << 16)
#define SPI_CTRLR0_DFS_4BIT              (0x3UL << 16)
#define SPI_CTRLR0_DFS_5BIT              (0x4UL << 16)
#define SPI_CTRLR0_DFS_6BIT              (0x5UL << 16)
#define SPI_CTRLR0_DFS_7BIT              (0x6UL << 16)
#define SPI_CTRLR0_DFS_8BIT              (0x7UL << 16)
#define SPI_CTRLR0_DFS_9BIT              (0x8UL << 16)
#define SPI_CTRLR0_DFS_10BIT             (0x9UL << 16)
#define SPI_CTRLR0_DFS_11BIT             (0xAUL << 16)
#define SPI_CTRLR0_DFS_12BIT             (0xBUL << 16)
#define SPI_CTRLR0_DFS_13BIT             (0xCUL << 16)
#define SPI_CTRLR0_DFS_14BIT             (0xDUL << 16)
#define SPI_CTRLR0_DFS_15BIT             (0xEUL << 16)
#define SPI_CTRLR0_DFS_16BIT             (0xFUL << 16)
#define SPI_CTRLR0_DFS_17BIT             (0x10UL << 16)
#define SPI_CTRLR0_DFS_18BIT             (0x11UL << 16)
#define SPI_CTRLR0_DFS_19BIT             (0x12UL << 16)
#define SPI_CTRLR0_DFS_20BIT             (0x13UL << 16)
#define SPI_CTRLR0_DFS_21BIT             (0x14UL << 16)
#define SPI_CTRLR0_DFS_22BIT             (0x15UL << 16)
#define SPI_CTRLR0_DFS_23BIT             (0x16UL << 16)
#define SPI_CTRLR0_DFS_24BIT             (0x17UL << 16)
#define SPI_CTRLR0_DFS_25BIT             (0x18UL << 16)
#define SPI_CTRLR0_DFS_26BIT             (0x19UL << 16)
#define SPI_CTRLR0_DFS_27BIT             (0x1AUL << 16)
#define SPI_CTRLR0_DFS_28BIT             (0x1BUL << 16)
#define SPI_CTRLR0_DFS_29BIT             (0x1CUL << 16)
#define SPI_CTRLR0_DFS_30BIT             (0x1DUL << 16)
#define SPI_CTRLR0_DFS_31BIT             (0x1EUL << 16)
#define SPI_CTRLR0_DFS_32BIT             (0x1FUL << 16)
#define SPI_CTRLR0_DFS_Mask              (0x1FUL << 16)
#define SPI_CTRLR0_FRF_SPI               (0UL << 4)
#define SPI_CTRLR0_FRF_SSP               (1UL << 4)
#define SPI_CTRLR0_FRF_MICROWIRE         (2UL << 4)
#define SPI_CTRLR0_FRF_Mask              (3UL << 4)
#define SPI_CTRLR0_SCPH_START_BIT        (1UL << 6)
#define SPI_CTRLR0_SCPH_MIDDLE_BIT       (0UL << 6)
#define SPI_CTRLR0_SCPOL_INACTIVE_HIGH   (1UL << 7)
#define SPI_CTRLR0_SCPOL_INACTIVE_LOW    (0UL << 7)
#define SPI_CTRLR0_TMOD_TX_AND_RX        (0UL << 8)
#define SPI_CTRLR0_TMOD_TX_ONLY          (1UL << 8)
#define SPI_CTRLR0_TMOD_RX_ONLY          (2UL << 8)
#define SPI_CTRLR0_TMOD_EEPROM_READ      (3UL << 8)
#define SPI_CTRLR0_TMOD_Mask             (3UL << 8)
#define SPI_CTRLR0_CFS_Mask              (0xFUL << 12)
#define SPI_CTRLR0_SPI_FRF_STANDARD      (0UL << 21)
#define SPI_CTRLR0_SPI_FRF_DUAL          (1UL << 21)
#define SPI_CTRLR0_SPI_FRF_QUAD          (2UL << 21)
#define SPI_CTRLR0_SPI_FRF_OCTAL         (3UL << 21)
#define SPI_CTRLR0_SPI_FRF_Mask          (3UL << 21)
#define SPI_CTRLR0_SPI_HYPERBUS_EN       (1UL << 24)
#define SPI_CTRLR0_SPI_DWS_EN            (1UL << 25)
#define SPI_CTRLR0_SPI_MASTER            (1UL << 31)
#define SPI_CTRLR0_SPI_SLAVE             (0UL << 31)

/*!<****************  Bit definition for SPI CTRLR1  *****************/
#define SPI_CTRLR1_NDF_Mask              (0xFFFFUL << 0)

/*!<****************  Bit definition for SPI SPIENR  *****************/
#define SPI_SPIENR_SPIEN                 (1UL << 0)

/*!<****************  Bit definition for SPI MWCR  *******************/
#define SPI_MWCR_MWMOD_SEQUENTIAL        (1UL << 0)
#define SPI_MWCR_MDD_TRANSMIT            (1UL << 1)
#define SPI_MWCR_MDD_RECEIVE             (0UL << 1)
#define SPI_MWCR_MHS_ENABLED             (1UL << 2)
 
/*!<****************  Bit definition for SPI BAUDR  ******************/
#define SPI_BAUDR_SCKDV_Mask             (0xFFUL << 0)

/*!<****************  Bit definition for SPI TXFTLR  *****************/
#define SPI_TXFTLR_TFT_Mask              (0x1FUL << 0)

/*!<****************  Bit definition for SPI RXFTLR  *****************/
#define SPI_RXFTLR_RFT_Mask              (0x1FUL << 0)

/*!<****************  Bit definition for SPI SR  *********************/
#define SPI_SR_BUSY                      (1UL << 0)
#define SPI_SR_TFNF                      (1UL << 1)
#define SPI_SR_TFE                       (1UL << 2)
#define SPI_SR_RFNE                      (1UL << 3)
#define SPI_SR_RFF                       (1UL << 4)
#define SPI_SR_TXE                       (1UL << 5)

/*!<****************  Bit definition for SPI IMR  ********************/
#define SPI_IMR_TXEIM                    (1UL << 0)
#define SPI_IMR_TXOIM                    (1UL << 1)
#define SPI_IMR_RXUIM                    (1UL << 2)
#define SPI_IMR_RXOIM                    (1UL << 3)
#define SPI_IMR_RXFIM                    (1UL << 4)
#define SPI_IMR_MSTIM                    (1UL << 5)

/*!<******************  Bit definition for SPI DMACR  ****************/
#define SPI_DMACR_RDMAE                  (1UL << 0)
#define SPI_DMACR_TDMAE                  (1UL << 1)
#define SPI_DMACR_Mask                   (3UL << 0)
#define SPI_DMACR_IDMAE                  (1UL << 2)

/*!<*****************  Bit definition for SPI DMATDLR  ***************/
#define SPI_DMATDLR_DMATDL_Mask          (0x1FUL << 0)

/*!<*****************  Bit definition for SPI DMARDLR  ***************/
#define SPI_DMARDLR_DMARDL_Mask          (0x1FUL << 0)

typedef struct{
  uint32_t SPI_TransferMode;
  uint32_t SPI_DataSize;
  uint32_t SPI_CPOL;
  uint32_t SPI_CPHA;
  uint32_t SPI_SCLKDivider;
}SPI_InitType;

//SPI_TransferMode
#define SPI_TransferMode_TX_AND_RX        SPI_CTRLR0_TMOD_TX_AND_RX
#define SPI_TransferMode_TX               SPI_CTRLR0_TMOD_TX_ONLY
#define SPI_TransferMode_RX               SPI_CTRLR0_TMOD_RX_ONLY
#define SPI_TransferMode_EEPROM_READ      SPI_CTRLR0_TMOD_EEPROM_READ
#define IS_SPI_TRANSFERMODE(MODE)         (((MODE) == SPI_TransferMode_TX_AND_RX) || \
                                           ((MODE) == SPI_TransferMode_TX)        || \
                                           ((MODE) == SPI_TransferMode_RX)        || \
                                           ((MODE) == SPI_TransferMode_EEPROM_READ))

//SPI_DataSize;
#define SPI_DataSize_4_Bit                 SPI_CTRLR0_DFS_4BIT 
#define SPI_DataSize_5_Bit                 SPI_CTRLR0_DFS_5BIT 
#define SPI_DataSize_6_Bit                 SPI_CTRLR0_DFS_6BIT 
#define SPI_DataSize_7_Bit                 SPI_CTRLR0_DFS_7BIT 
#define SPI_DataSize_8_Bit                 SPI_CTRLR0_DFS_8BIT 
#define SPI_DataSize_9_Bit                 SPI_CTRLR0_DFS_9BIT 
#define SPI_DataSize_10_Bit                SPI_CTRLR0_DFS_10BIT
#define SPI_DataSize_11_Bit                SPI_CTRLR0_DFS_11BIT
#define SPI_DataSize_12_Bit                SPI_CTRLR0_DFS_12BIT
#define SPI_DataSize_13_Bit                SPI_CTRLR0_DFS_13BIT
#define SPI_DataSize_14_Bit                SPI_CTRLR0_DFS_14BIT
#define SPI_DataSize_15_Bit                SPI_CTRLR0_DFS_15BIT
#define SPI_DataSize_16_Bit                SPI_CTRLR0_DFS_16BIT
#define SPI_DataSize_17_Bit                SPI_CTRLR0_DFS_17BIT
#define SPI_DataSize_18_Bit                SPI_CTRLR0_DFS_18BIT
#define SPI_DataSize_19_Bit                SPI_CTRLR0_DFS_19BIT
#define SPI_DataSize_20_Bit                SPI_CTRLR0_DFS_20BIT
#define SPI_DataSize_21_Bit                SPI_CTRLR0_DFS_21BIT
#define SPI_DataSize_22_Bit                SPI_CTRLR0_DFS_22BIT
#define SPI_DataSize_23_Bit                SPI_CTRLR0_DFS_23BIT
#define SPI_DataSize_24_Bit                SPI_CTRLR0_DFS_24BIT
#define SPI_DataSize_25_Bit                SPI_CTRLR0_DFS_25BIT
#define SPI_DataSize_26_Bit                SPI_CTRLR0_DFS_26BIT
#define SPI_DataSize_27_Bit                SPI_CTRLR0_DFS_27BIT
#define SPI_DataSize_28_Bit                SPI_CTRLR0_DFS_28BIT
#define SPI_DataSize_29_Bit                SPI_CTRLR0_DFS_29BIT
#define SPI_DataSize_30_Bit                SPI_CTRLR0_DFS_30BIT
#define SPI_DataSize_31_Bit                SPI_CTRLR0_DFS_31BIT
#define SPI_DataSize_32_Bit                SPI_CTRLR0_DFS_32BIT

//SPI_SCLKDivider
#define IS_SPI_SCLK_DIVIDER(D)             (D <= 0xFFFE)

#define IS_SPI_TRANSMIT_FIFO_THRESHOLD(TH) (TH <= SPI_TXFTLR_TFT_Mask)
#define IS_SPI_RECEIVE_FIFO_THRESHOLD(TH)  (TH <= SPI_RXFTLR_RFT_Mask)

//SPI_Clock_Polarity
#define SPI_CPOL_Low                       SPI_CTRLR0_SCPOL_INACTIVE_LOW
#define SPI_CPOL_High                      SPI_CTRLR0_SCPOL_INACTIVE_HIGH
#define IS_SPI_CPOL(CPOL)                  (((CPOL) == SPI_CPOL_Low) || \
                                            ((CPOL) == SPI_CPOL_High))

//SPI_Clock_Phase
#define SPI_CPHA_1Edge                     SPI_CTRLR0_SCPH_MIDDLE_BIT
#define SPI_CPHA_2Edge                     SPI_CTRLR0_SCPH_START_BIT
#define IS_SPI_CPHA(CPHA)                  (((CPHA) == SPI_CPHA_1Edge) || \
                                            ((CPHA) == SPI_CPHA_2Edge))

//SPI_IT
#define SPI_IT_TXEI                           SPI_IMR_TXEIM 
#define SPI_IT_TXOI                           SPI_IMR_TXOIM 
#define SPI_IT_RXUI                           SPI_IMR_RXUIM 
#define SPI_IT_RXOI                           SPI_IMR_RXOIM 
#define SPI_IT_RXFI                           SPI_IMR_RXFIM 
#define SPI_IT_MSTI                           SPI_IMR_MSTIM
#define IS_SPI_INT(INT)                       (((INT) == SPI_IT_TXEI) || \
                                               ((INT) == SPI_IT_TXOI) || \
                                               ((INT) == SPI_IT_RXUI) || \
                                               ((INT) == SPI_IT_RXOI) || \
                                               ((INT) == SPI_IT_RXFI) || \
                                               ((INT) == SPI_IT_MSTI))

//SPI_CLEAR_INT
#define SPI_IT_CLEAR_TXUI                       (1<<0)
#define SPI_IT_CLEAR_TXOI                       (1<<0)
#define SPI_IT_CLEAR_RXUI                       (1<<0)
#define SPI_IT_CLEAR_RXOI                       (1<<0)

#define IS_SPI_CLEAR_INT(S)                  (((S) == SPI_IT_CLEAR_TXUI) || \
                                              ((S) == SPI_IT_CLEAR_TXOI) || \
                                              ((S) == SPI_IT_CLEAR_RXUI) || \
                                              ((S) == SPI_IT_CLEAR_RXOI))
																							 
//SPI TXFIFOLEVEL
#define SPI_FIFO_TX_THRESHOLD_1             (0<<0)
#define SPI_FIFO_TX_THRESHOLD_4             (3<<0)
#define SPI_FIFO_TX_THRESHOLD_8             (7<<0)
#define SPI_FIFO_TX_THRESHOLD_16            (15<<0)
#define SPI_FIFO_TX_THRESHOLD_24            (23<<0)
#define SPI_FIFO_TX_THRESHOLD_32            (31<<0)
#define IS_SPI_FIFO_TXLEVLE(S)              (((S) == SPI_FIFO_TX_THRESHOLD_1) || \
                                              ((S) == SPI_FIFO_TX_THRESHOLD_4) || \
                                              ((S) == SPI_FIFO_TX_THRESHOLD_8) || \
                                              ((S) == SPI_FIFO_TX_THRESHOLD_16) || \
                                              ((S) == SPI_FIFO_TX_THRESHOLD_24) || \
                                              ((S) == SPI_FIFO_TX_THRESHOLD_32))
                                              
//SPI RXFIFOLEVEL
#define SPI_FIFO_RX_THRESHOLD_1              (0<<0)
#define SPI_FIFO_RX_THRESHOLD_4              (3<<0)
#define SPI_FIFO_RX_THRESHOLD_8              (7<<0)
#define SPI_FIFO_RX_THRESHOLD_16             (15<<0)
#define SPI_FIFO_RX_THRESHOLD_24             (23<<0)
#define SPI_FIFO_RX_THRESHOLD_32             (31<<0)
#define IS_SPI_FIFO_RXLEVLE(S)               (((S) == SPI_FIFO_RX_THRESHOLD_1) || \
                                              ((S) == SPI_FIFO_RX_THRESHOLD_4) || \
                                              ((S) == SPI_FIFO_RX_THRESHOLD_8) || \
                                               ((S) == SPI_FIFO_RX_THRESHOLD_16) || \
                                               ((S) == SPI_FIFO_RX_THRESHOLD_24) || \
                                               ((S) == SPI_FIFO_RX_THRESHOLD_32))
                                                
//SPI DMA
#define SPI_DMA_TX                            SPI_DMACR_TDMAE
#define SPI_DMA_RX                            SPI_DMACR_RDMAE
#define IS_SPI_DMA_CHANNEL(C)                 (((C) == SPI_DMA_TX) || \
                                               ((C) == SPI_DMA_RX) || \
                                               ((C) == (SPI_DMA_TX|SPI_DMA_RX)))

//SPI Status
#define SPI_FLAG_STATUS_TXE                   SPI_SR_TXE 
#define SPI_FLAG_STATUS_RFF                   SPI_SR_RFF
#define SPI_FLAG_STATUS_RFNE                  SPI_SR_RFNE
#define SPI_FLAG_STATUS_TFE                   SPI_SR_TFE
#define SPI_FLAG_STATUS_TFNF                  SPI_SR_TFNF
#define SPI_FLAG_STATUS_BUSY                  SPI_SR_BUSY

#define IS_SPI_FLAG_STATUS(S)                 (((S) == SPI_FLAG_STATUS_TXE) || \
                                               ((S) == SPI_FLAG_STATUS_RFF) || \
                                               ((S) == SPI_FLAG_STATUS_RFNE) || \
                                               ((S) == SPI_FLAG_STATUS_TFE) || \
                                               ((S) == SPI_FLAG_STATUS_TFNF) || \
                                               ((S) == SPI_FLAG_STATUS_BUSY))

//SPI SSEL
#define SPI_SSEL0                              (0x01UL)
#define SPI_SSEL1                              (0x02UL)
#define SPI_SSEL2                              (0x04UL)
#define SPI_SSEL3                              (0x08UL)
#define IS_SPI_SSEL(SSEL)                      ((((uint8_t)(SSEL) & (uint8_t)(0xF)) != 0x00U) &&\
                                               (((uint8_t)(SSEL) & (uint8_t)(~0xF)) == 0x00U))


/* Exported functions ------------------------------------------------------- */
//SPI
void SPI_DeInit(SPI_Type* SPIx);
void SPI_StructInit(SPI_InitType* SPI_InitStruct);
void SPI_Init(SPI_Type* SPIx, SPI_InitType* SPI_InitStruct);
void SPI_Cmd(SPI_Type* SPIx, FunctionalState NewState);
void SPI_DMACmd(SPI_Type* SPIx, uint32_t SPI_DMAReq, FunctionalState NewState);
void SPI_SendData(SPI_Type* SPIx, uint32_t Data);
uint32_t SPI_ReceiveData(SPI_Type* SPIx);
FlagStatus SPI_GetFlagStatus(SPI_Type* SPIx, uint16_t SPI_FLAG);
void SPI_ITConfig(SPI_Type* SPIx, uint16_t SPI_IT, FunctionalState NewState);
ITStatus SPI_GetITStatus(SPI_Type* SPIx, uint16_t SPI_IT);
void SPI_ClearITStatus(SPI_Type* SPIx, uint16_t SPI_IT);
void SPI_TxFIFOThresholdConfig(SPI_Type* SPIx, uint32_t TXFIFOLevel);
void SPI_RxFIFOThresholdConfig(SPI_Type* SPIx, uint32_t RXFIFOLevel);
void SPI_DMA_TxFIFOLevelConfig(SPI_Type* SPIx, uint32_t TXFIFOLevel);
void SPI_DMA_RxFIFOLevelConfig(SPI_Type* SPIx, uint32_t RXFIFOLevel);
uint16_t SPI_GetTxFIFOLevel(SPI_Type* SPIx);
uint16_t SPI_GetRxFIFOLevel(SPI_Type* SPIx);
void SPI_SlaveSelectConfig(SPI_Type* SPIx, uint8_t SPI_SSel, FunctionalState NewState);
#ifdef __cplusplus
}
#endif
#endif /* __LIB_SPI_H */

/*********************************** END OF FILE ******************************/