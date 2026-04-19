/**
  * @file    lib_ospi.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-04-19
  * @brief   
******************************************************************************/

#ifndef __LIB_OSPI_H
#define __LIB_OSPI_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "target.h"

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/*!<****************  Bit definition for OSPI CTRLR0  *****************/
#define OSPI_CTRLR0_DFS_1BIT              (0x0UL)
#define OSPI_CTRLR0_DFS_2BIT              (0x1UL)
#define OSPI_CTRLR0_DFS_3BIT              (0x2UL)
#define OSPI_CTRLR0_DFS_4BIT              (0x3UL)
#define OSPI_CTRLR0_DFS_5BIT              (0x4UL)
#define OSPI_CTRLR0_DFS_6BIT              (0x5UL)
#define OSPI_CTRLR0_DFS_7BIT              (0x6UL)
#define OSPI_CTRLR0_DFS_8BIT              (0x7UL)
#define OSPI_CTRLR0_DFS_9BIT              (0x8UL)
#define OSPI_CTRLR0_DFS_10BIT             (0x9UL)
#define OSPI_CTRLR0_DFS_11BIT             (0xAUL)
#define OSPI_CTRLR0_DFS_12BIT             (0xBUL)
#define OSPI_CTRLR0_DFS_13BIT             (0xCUL)
#define OSPI_CTRLR0_DFS_14BIT             (0xDUL)
#define OSPI_CTRLR0_DFS_15BIT             (0xEUL)
#define OSPI_CTRLR0_DFS_16BIT             (0xFUL)
#define OSPI_CTRLR0_DFS_17BIT             (0x10UL)
#define OSPI_CTRLR0_DFS_18BIT             (0x11UL)
#define OSPI_CTRLR0_DFS_19BIT             (0x12UL)
#define OSPI_CTRLR0_DFS_20BIT             (0x13UL)
#define OSPI_CTRLR0_DFS_21BIT             (0x14UL)
#define OSPI_CTRLR0_DFS_22BIT             (0x15UL)
#define OSPI_CTRLR0_DFS_23BIT             (0x16UL)
#define OSPI_CTRLR0_DFS_24BIT             (0x17UL)
#define OSPI_CTRLR0_DFS_25BIT             (0x18UL)
#define OSPI_CTRLR0_DFS_26BIT             (0x19UL)
#define OSPI_CTRLR0_DFS_27BIT             (0x1AUL)
#define OSPI_CTRLR0_DFS_28BIT             (0x1BUL)
#define OSPI_CTRLR0_DFS_29BIT             (0x1CUL)
#define OSPI_CTRLR0_DFS_30BIT             (0x1DUL)
#define OSPI_CTRLR0_DFS_31BIT             (0x1EUL)
#define OSPI_CTRLR0_DFS_32BIT             (0x1FUL)
#define OSPI_CTRLR0_DFS_Mask              (0x1FUL)
#define OSPI_CTRLR0_FRF_OSPI               (0UL << 6)
#define OSPI_CTRLR0_FRF_SSP               (1UL << 6)
#define OSPI_CTRLR0_FRF_MICROWIRE         (2UL << 6)
#define OSPI_CTRLR0_FRF_Mask              (3UL << 6)
#define OSPI_CTRLR0_SCPH_START_BIT        (1UL << 8)
#define OSPI_CTRLR0_SCPH_MIDDLE_BIT       (0UL << 8)
#define OSPI_CTRLR0_SCPOL_INACTIVE_HIGH   (0UL << 9)
#define OSPI_CTRLR0_SCPOL_INACTIVE_LOW    (1UL << 9)
#define OSPI_CTRLR0_TMOD_TX_AND_RX        (0UL << 10)
#define OSPI_CTRLR0_TMOD_TX_ONLY          (1UL << 10)
#define OSPI_CTRLR0_TMOD_RX_ONLY          (2UL << 10)
#define OSPI_CTRLR0_TMOD_EEPROM_READ      (3UL << 10)
#define OSPI_CTRLR0_TMOD_Mask             (3UL << 10)
#define OSPI_CTRLR0_CFS_Mask              (0xFUL << 16)
#define OSPI_CTRLR0_OSPI_FRF_STANDARD      (0UL << 22)
#define OSPI_CTRLR0_OSPI_FRF_DUAL          (1UL << 22)
#define OSPI_CTRLR0_OSPI_FRF_QUAD          (2UL << 22)
#define OSPI_CTRLR0_OSPI_FRF_OCTAL         (3UL << 22)
#define OSPI_CTRLR0_OSPI_FRF_Mask          (3UL << 22)
#define OSPI_CTRLR0_OSPI_HYPERBUS_EN       (1UL << 24)
#define OSPI_CTRLR0_OSPI_DWS_EN            (1UL << 25)
#define OSPI_CTRLR0_OSPI_MASTER            (1UL << 31)
#define OSPI_CTRLR0_OSPI_SLAVE             (0UL << 31)

/*!<****************  Bit definition for OSPI CTRLR1  *****************/
#define OSPI_CTRLR1_NDF_Mask              (0xFFFFUL << 0)

/*!<****************  Bit definition for OSPI OSPIENR  *****************/
#define OSPI_OSPIENR_OSPIEN                 (1UL << 0)

/*!<****************  Bit definition for OSPI MWCR  *******************/
#define OSPI_MWCR_MWMOD_SEQUENTIAL        (1UL << 0)
#define OSPI_MWCR_MDD_TRANSMIT            (1UL << 1)
#define OSPI_MWCR_MDD_RECEIVE             (0UL << 1)
#define OSPI_MWCR_MHS_ENABLED             (1UL << 2)
 
/*!<****************  Bit definition for OSPI BAUDR  ******************/
#define OSPI_BAUDR_SCKDV_Mask             (0xFFFFUL << 0)

/*!<****************  Bit definition for OSPI TXFTLR  *****************/
#define OSPI_TXFTLR_TFT_Mask              (0x1FUL << 0)

/*!<****************  Bit definition for OSPI RXFTLR  *****************/
#define OSPI_RXFTLR_RFT_Mask              (0x3FUL << 0)

/*!<****************  Bit definition for OSPI SR  *********************/
#define OSPI_SR_BUSY                      (1UL << 0)
#define OSPI_SR_TFNF                      (1UL << 1)
#define OSPI_SR_TFE                       (1UL << 2)
#define OSPI_SR_RFNE                      (1UL << 3)
#define OSPI_SR_RFF                       (1UL << 4)
#define OSPI_SR_TXE                       (1UL << 5)

/*!<****************  Bit definition for OSPI IMR  ********************/
#define OSPI_IMR_TXEIM                    (1UL << 0)
#define OSPI_IMR_TXOIM                    (1UL << 1)
#define OSPI_IMR_RXUIM                    (1UL << 2)
#define OSPI_IMR_RXOIM                    (1UL << 3)
#define OSPI_IMR_RXFIM                    (1UL << 4)
#define OSPI_IMR_TXUIM                    (1UL << 7)


/*!<****************  Bit definition for OSPI ISR  ********************/
#define OSPI_ISR_TXEIS                    (1UL << 0)
#define OSPI_ISR_TXOIS                    (1UL << 1)
#define OSPI_ISR_RXUIS                    (1UL << 2)
#define OSPI_ISR_RXOIS                    (1UL << 3)
#define OSPI_ISR_RXFIS                    (1UL << 4)
#define OSPI_ISR_TXUIS                    (1UL << 7)

/*!<****************  Bit definition for OSPI RISR  *******************/
#define OSPI_RISR_TXEIR                   (1UL << 0)
#define OSPI_RISR_TXOIR                   (1UL << 1)
#define OSPI_RISR_RXUIR                   (1UL << 2)
#define OSPI_RISR_RXOIR                   (1UL << 3)
#define OSPI_RISR_RXFIR                   (1UL << 4)
#define OSPI_RISR_TXUIR                   (1UL << 7)


/*!<******************  Bit definition for OSPI DMACR  ****************/
#define OSPI_DMACR_RDMAE                  (1UL << 0)
#define OSPI_DMACR_TDMAE                  (1UL << 1)
#define OSPI_DMACR_Mask                   (3UL << 0)
#define OSPI_DMACR_IDMAE                  (1UL << 2)

/*!<*****************  Bit definition for OSPI DMATDLR  ***************/
#define OSPI_DMATDLR_DMATDL_Mask          (0x1FUL << 0)

/*!<*****************  Bit definition for OSPI DMARDLR  ***************/
#define OSPI_DMARDLR_DMARDL_Mask          (0x1FUL << 0)

/*!<*****************  Bit definition for OSPI SPI_CTRLR0  ************/
#define OSPI_SPI_CTRLR0_TRANS_TYPE_TT0    (0UL << 0)
#define OSPI_SPI_CTRLR0_TRANS_TYPE_TT1    (1UL << 0)
#define OSPI_SPI_CTRLR0_TRANS_TYPE_TT2    (2UL << 0)
#define OSPI_SPI_CTRLR0_TRANS_TYPE_Mask   (3UL << 0)
#define OSPI_SPI_CTRLR0_ADDR_L0           (0x0UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L4           (0x1UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L8           (0x2UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L12          (0x3UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L16          (0x4UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L20          (0x5UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L24          (0x6UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L28          (0x7UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L32          (0x8UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L36          (0x9UL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L40          (0xAUL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L44          (0xBUL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L48          (0xCUL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L52          (0xDUL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L56          (0xEUL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L60          (0xFUL << 2)
#define OSPI_SPI_CTRLR0_ADDR_L_Mask       (0xFUL << 2)
#define OSPI_SPI_CTRLR0_XIP_MD_BIT_EN     (1UL << 7)
#define OSPI_SPI_CTRLR0_INST_L0           (0UL << 8)
#define OSPI_SPI_CTRLR0_INST_L4           (1UL << 8)
#define OSPI_SPI_CTRLR0_INST_L8           (2UL << 8)
#define OSPI_SPI_CTRLR0_INST_L16          (3UL << 8)
#define OSPI_SPI_CTRLR0_INST_L_Mask       (3UL << 8)
#define OSPI_SPI_CTRLR0_WAIT_CYCLES_Mask  (0x1FUL << 11)
#define OSPI_SPI_CTRLR0_OSPI_DDR_EN       (1UL << 16)
#define OSPI_SPI_CTRLR0_OSPI_RXDS_EN      (1UL << 18)
#define OSPI_SPI_CTRLR0_XIP_DFS_HC        (1UL << 19)
#define OSPI_SPI_CTRLR0_XIP_INST_EN       (1UL << 20)
#define OSPI_SPI_CTRLR0_OSPI_DM_EN        (1UL << 24)
#define OSPI_SPI_CTRLR0_OSPI_RXDS_SIG_EN  (1UL << 25)

/*!<**************  Bit definition for OSPI DDR_DRIVE_EDGE  ************/
#define OSPI_DDR_DRIVE_EDGE_TDE_Mask      (0xFFUL << 0)


/*!<**************  Bit definition for OSPI XIP_MODE_BITS  ************/
#define OSPI_XIP_MODE_BITS_Mask           (0xFFFFUL << 0)

/*!<**************  Bit definition for OSPI XIP_INCR_INST  ************/


/*!<**************  Bit definition for OSPI XIP_WRAP_INST  ************/


/*!<**************  Bit definition for OSPI XIP_WRITE_INCR_INST  ******/


/*!<**************  Bit definition for OSPI XIP_WRITE_WRAP_INST  ******/


/*!<**************  Bit definition for OSPI XIP_WRITE_CTRL  ***********/
#define OSPI_XIP_WRITE_CTRL_XIPWR_RXDS_SIG_EN      (1UL << 13)
#define OSPI_XIP_WRITE_CTRL_XIPWR_HYPERBUS_EN      (1UL << 12)
#define OSPI_XIP_WRITE_CTRL_WR_INST_DDR_EN         (1UL << 11)
#define OSPI_XIP_WRITE_CTRL_WR_SPI_DDR_EN          (1UL << 10)
#define OSPI_XIP_WRITE_CTRL_WR_INST_L0             (0UL << 8)
#define OSPI_XIP_WRITE_CTRL_WR_INST_L4             (1UL << 8)
#define OSPI_XIP_WRITE_CTRL_WR_INST_L8             (2UL << 8)
#define OSPI_XIP_WRITE_CTRL_WR_INST_L16            (3UL << 8)
#define OSPI_XIP_WRITE_CTRL_WR_INST_L_Mask         (3UL << 9)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L0             (0UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L4             (1UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L8             (2UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L12            (3UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L16            (4UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L20            (5UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L24            (6UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L28            (7UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_ADDR_L32            (8UL << 4)
#define OSPI_XIP_WRITE_CTRL_WR_TRANS_TYPE_TT0      (0UL << 2)
#define OSPI_XIP_WRITE_CTRL_WR_TRANS_TYPE_TT1      (1UL << 2)
#define OSPI_XIP_WRITE_CTRL_WR_TRANS_TYPE_TT2      (2UL << 2)
#define OSPI_XIP_WRITE_CTRL_WR_TRANS_TYPE_TT3      (3UL << 2)
#define OSPI_XIP_WRITE_CTRL_WR_TRANS_TYPE_Mask     (3UL << 2)
#define OSPI_XIP_WRITE_CTRL_WR_FRF_SPI_DUAL        (1UL << 0)
#define OSPI_XIP_WRITE_CTRL_WR_FRF_SPI_QUAD        (2UL << 0)
#define OSPI_XIP_WRITE_CTRL_WR_FRF_SPI_OCTAL       (3UL << 0)
#define OSPI_XIP_WRITE_CTRL_WR_FRF_Mask            (3UL << 0)

/*!<**************  Bit definition for OSPI ENC_CFG  ***********/
#define OSPI_ENC_CFG_EN      (1UL << 16)

typedef struct{
  uint32_t OSPI_WorkingMode;
  uint32_t OSPI_SPIFrameFormat;
  uint32_t OSPI_TransferMode;
  uint32_t OSPI_DataNumber;
  uint32_t OSPI_DataLength;
  uint32_t OSPI_ADDRLength;
  uint32_t OSPI_INSTLength;
  uint32_t OSPI_ADDRINSTFormat;
  uint32_t OSPI_AddrDtrMode;
  uint32_t OSPI_InstructionDtrMode;
  uint32_t OSPI_Hyperbus;
  uint32_t OSPI_WaitCycles;
  uint32_t OSPI_CPOL;
  uint32_t OSPI_CPHA;
  uint32_t OSPI_SCLKDivider;
  uint32_t OSPI_RXDS;
  uint32_t OSPI_DDR_DRIVE_EDGE;
}OSPI_InitType;

#define OSPI_INSTRUCTION_DTR_DISABLE            (0X00000000)
#define OSPI_SPI_DTR_DISABLE                    (0X00000000)
#define OSPI_RXDS_DISABLE                       (0X00000000)
#define OSPI_SPI_DTR_ENABLE                     OSPI_SPI_CTRLR0_OSPI_DDR_EN
#define OSPI_RXDS_ENABLE                        OSPI_SPI_CTRLR0_OSPI_RXDS_EN

//OSPI_WorkingMode
#define OSPI_WorkingMode_Master                 OSPI_CTRLR0_OSPI_MASTER
#define OSPI_WorkingMode_Slave                  OSPI_CTRLR0_OSPI_SLAVE
#define IS_OSPI_WorkingMode(MODE)               (((MODE) == OSPI_CTRLR0_OSPI_MASTER) || \
                                                ((MODE) == OSPI_CTRLR0_OSPI_SLAVE))

//OSPI_SPIFrameFormat
#define OSPI_SPIFrameFormat_StandardSPI         OSPI_CTRLR0_OSPI_FRF_STANDARD
#define OSPI_SPIFrameFormat_DualSPI             OSPI_CTRLR0_OSPI_FRF_DUAL
#define OSPI_SPIFrameFormat_QuadSPI             OSPI_CTRLR0_OSPI_FRF_QUAD
#define OSPI_SPIFrameFormat_OctalSPI            OSPI_CTRLR0_OSPI_FRF_OCTAL
#define IS_OSPI_SPIFrameFormat(MODE)            (((MODE) == OSPI_SPIFrameFormat_StandardSPI) || \
                                                ((MODE) == OSPI_SPIFrameFormat_DualSPI) || \
                                                ((MODE) == OSPI_SPIFrameFormat_QuadSPI) || \
                                                ((MODE) == OSPI_SPIFrameFormat_OctalSPI))

//OSPI_TransferMode
#define OSPI_TransferMode_TXAndRX               OSPI_CTRLR0_TMOD_TX_AND_RX
#define OSPI_TransferMode_TX                    OSPI_CTRLR0_TMOD_TX_ONLY
#define OSPI_TransferMode_RX                    OSPI_CTRLR0_TMOD_RX_ONLY
#define OSPI_TransferMode_EEPROM_READ           OSPI_CTRLR0_TMOD_EEPROM_READ
#define IS_OSPI_TransferMode(MODE)              (((MODE) == OSPI_TransferMode_TXAndRX)     || \
                                               ((MODE) == OSPI_TransferMode_TX)          || \
                                               ((MODE) == OSPI_TransferMode_EEPROM_READ) || \
                                                ((MODE) == OSPI_TransferMode_RX))

//OSPI_DataNumber
#define IS_OSPI_DataNumber(MODE)                (((MODE) < 0x10000))

//OSPI_DataLength
#define OSPI_DataLength_1BIT                    OSPI_CTRLR0_DFS_1BIT 
#define OSPI_DataLength_2BIT                    OSPI_CTRLR0_DFS_2BIT 
#define OSPI_DataLength_3BIT                    OSPI_CTRLR0_DFS_3BIT 
#define OSPI_DataLength_4BIT                    OSPI_CTRLR0_DFS_4BIT 
#define OSPI_DataLength_5BIT                    OSPI_CTRLR0_DFS_5BIT 
#define OSPI_DataLength_6BIT                    OSPI_CTRLR0_DFS_6BIT 
#define OSPI_DataLength_7BIT                    OSPI_CTRLR0_DFS_7BIT 
#define OSPI_DataLength_8BIT                    OSPI_CTRLR0_DFS_8BIT 
#define OSPI_DataLength_9BIT                    OSPI_CTRLR0_DFS_9BIT 
#define OSPI_DataLength_10BIT                   OSPI_CTRLR0_DFS_10BIT
#define OSPI_DataLength_11BIT                   OSPI_CTRLR0_DFS_11BIT
#define OSPI_DataLength_12BIT                   OSPI_CTRLR0_DFS_12BIT
#define OSPI_DataLength_13BIT                   OSPI_CTRLR0_DFS_13BIT
#define OSPI_DataLength_14BIT                   OSPI_CTRLR0_DFS_14BIT
#define OSPI_DataLength_15BIT                   OSPI_CTRLR0_DFS_15BIT
#define OSPI_DataLength_16BIT                   OSPI_CTRLR0_DFS_16BIT
#define OSPI_DataLength_17BIT                   OSPI_CTRLR0_DFS_17BIT
#define OSPI_DataLength_18BIT                   OSPI_CTRLR0_DFS_18BIT
#define OSPI_DataLength_19BIT                   OSPI_CTRLR0_DFS_19BIT
#define OSPI_DataLength_20BIT                   OSPI_CTRLR0_DFS_20BIT
#define OSPI_DataLength_21BIT                   OSPI_CTRLR0_DFS_21BIT
#define OSPI_DataLength_22BIT                   OSPI_CTRLR0_DFS_22BIT
#define OSPI_DataLength_23BIT                   OSPI_CTRLR0_DFS_23BIT
#define OSPI_DataLength_24BIT                   OSPI_CTRLR0_DFS_24BIT
#define OSPI_DataLength_25BIT                   OSPI_CTRLR0_DFS_25BIT
#define OSPI_DataLength_26BIT                   OSPI_CTRLR0_DFS_26BIT
#define OSPI_DataLength_27BIT                   OSPI_CTRLR0_DFS_27BIT
#define OSPI_DataLength_28BIT                   OSPI_CTRLR0_DFS_28BIT
#define OSPI_DataLength_29BIT                   OSPI_CTRLR0_DFS_29BIT
#define OSPI_DataLength_30BIT                   OSPI_CTRLR0_DFS_30BIT
#define OSPI_DataLength_31BIT                   OSPI_CTRLR0_DFS_31BIT
#define OSPI_DataLength_32BIT                   OSPI_CTRLR0_DFS_32BIT
#define IS_OSPI_DataLength(LENGTH)              (((LENGTH) == OSPI_DataLength_1BIT) || \
                                                ((LENGTH) == OSPI_DataLength_2BIT) || \
                                                ((LENGTH) == OSPI_DataLength_3BIT) || \
                                                ((LENGTH) == OSPI_DataLength_4BIT) || \
                                                ((LENGTH) == OSPI_DataLength_5BIT) || \
                                                ((LENGTH) == OSPI_DataLength_6BIT) || \
                                                ((LENGTH) == OSPI_DataLength_7BIT) || \
                                                ((LENGTH) == OSPI_DataLength_8BIT) || \
                                                ((LENGTH) == OSPI_DataLength_9BIT) || \
                                                ((LENGTH) == OSPI_DataLength_10BIT) || \
                                                ((LENGTH) == OSPI_DataLength_11BIT) || \
                                                ((LENGTH) == OSPI_DataLength_12BIT) || \
                                                ((LENGTH) == OSPI_DataLength_13BIT) || \
                                                ((LENGTH) == OSPI_DataLength_14BIT) || \
                                                ((LENGTH) == OSPI_DataLength_15BIT) || \
                                                ((LENGTH) == OSPI_DataLength_16BIT) || \
                                                ((LENGTH) == OSPI_DataLength_17BIT) || \
                                                ((LENGTH) == OSPI_DataLength_18BIT) || \
                                                ((LENGTH) == OSPI_DataLength_19BIT) || \
                                                ((LENGTH) == OSPI_DataLength_20BIT) || \
                                                ((LENGTH) == OSPI_DataLength_21BIT) || \
                                                ((LENGTH) == OSPI_DataLength_22BIT) || \
                                                ((LENGTH) == OSPI_DataLength_23BIT) || \
                                                ((LENGTH) == OSPI_DataLength_24BIT) || \
                                                ((LENGTH) == OSPI_DataLength_25BIT) || \
                                                ((LENGTH) == OSPI_DataLength_26BIT) || \
                                                ((LENGTH) == OSPI_DataLength_27BIT) || \
                                                ((LENGTH) == OSPI_DataLength_28BIT) || \
                                                ((LENGTH) == OSPI_DataLength_29BIT) || \
                                                ((LENGTH) == OSPI_DataLength_30BIT) || \
                                                ((LENGTH) == OSPI_DataLength_31BIT) || \
                                                ((LENGTH) == OSPI_DataLength_32BIT))

//OSPI_ADDRLength
#define OSPI_ADDRLength_NO                      OSPI_SPI_CTRLR0_ADDR_L0
#define OSPI_ADDRLength_4BIT                    OSPI_SPI_CTRLR0_ADDR_L4
#define OSPI_ADDRLength_8BIT                    OSPI_SPI_CTRLR0_ADDR_L8
#define OSPI_ADDRLength_12BIT                   OSPI_SPI_CTRLR0_ADDR_L12
#define OSPI_ADDRLength_16BIT                   OSPI_SPI_CTRLR0_ADDR_L16
#define OSPI_ADDRLength_20BIT                   OSPI_SPI_CTRLR0_ADDR_L20
#define OSPI_ADDRLength_24BIT                   OSPI_SPI_CTRLR0_ADDR_L24
#define OSPI_ADDRLength_28BIT                   OSPI_SPI_CTRLR0_ADDR_L28
#define OSPI_ADDRLength_32BIT                   OSPI_SPI_CTRLR0_ADDR_L32
#define OSPI_ADDRLength_36BIT                   OSPI_SPI_CTRLR0_ADDR_L36
#define OSPI_ADDRLength_40BIT                   OSPI_SPI_CTRLR0_ADDR_L40
#define OSPI_ADDRLength_44BIT                   OSPI_SPI_CTRLR0_ADDR_L44
#define OSPI_ADDRLength_48BIT                   OSPI_SPI_CTRLR0_ADDR_L48
#define OSPI_ADDRLength_52BIT                   OSPI_SPI_CTRLR0_ADDR_L52
#define OSPI_ADDRLength_56BIT                   OSPI_SPI_CTRLR0_ADDR_L56
#define OSPI_ADDRLength_60BIT                   OSPI_SPI_CTRLR0_ADDR_L60
#define IS_OSPI_ADDRLength(LENGTH)              (((LENGTH) == OSPI_ADDRLength_NO) || \
                                                ((LENGTH) == OSPI_ADDRLength_4BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_8BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_12BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_16BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_20BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_24BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_28BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_32BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_36BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_40BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_44BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_48BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_52BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_56BIT) || \
                                                ((LENGTH) == OSPI_ADDRLength_60BIT))

//OSPI_INSTLength
#define OSPI_INSTLength_NO                      OSPI_SPI_CTRLR0_INST_L0 
#define OSPI_INSTLength_4BIT                    OSPI_SPI_CTRLR0_INST_L4 
#define OSPI_INSTLength_8BIT                    OSPI_SPI_CTRLR0_INST_L8 
#define OSPI_INSTLength_16BIT                   OSPI_SPI_CTRLR0_INST_L16
#define IS_OSPI_INSTLength(LENGTH)              (((LENGTH) == OSPI_INSTLength_NO) || \
                                                ((LENGTH) == OSPI_INSTLength_4BIT) || \
                                                ((LENGTH) == OSPI_INSTLength_8BIT) || \
                                                ((LENGTH) == OSPI_INSTLength_16BIT))

//OSPI_ADDRINSTFormat
#define OSPI_ADDRINSTFormat_TT0                 OSPI_SPI_CTRLR0_TRANS_TYPE_TT0
#define OSPI_ADDRINSTFormat_TT1                 OSPI_SPI_CTRLR0_TRANS_TYPE_TT1
#define OSPI_ADDRINSTFormat_TT2                 OSPI_SPI_CTRLR0_TRANS_TYPE_TT2
#define IS_OSPI_ADDRINSTFormat(MODE)            (((MODE) == OSPI_SPI_CTRLR0_TRANS_TYPE_TT0) || \
                                                ((MODE) == OSPI_SPI_CTRLR0_TRANS_TYPE_TT1) || \
                                                ((MODE) == OSPI_SPI_CTRLR0_TRANS_TYPE_TT2))

//OSPI_SCLKDivider
#define IS_OSPI_SCLK_DIVIDER(D)                 (D <= 0xFFFE)

#define IS_OSPI_TRANSMIT_FIFO_THRESHOLD(TH)     (TH <= OSPI_TXFTLR_TFT_Mask)
#define IS_OSPI_RECEIVE_FIFO_THRESHOLD(TH)      (TH <= OSPI_RXFTLR_RFT_Mask)

//OSPI_Hyperbus
#define OSPI_Hyperbus_Enable                    OSPI_CTRLR0_OSPI_HYPERBUS_EN
#define OSPI_Hyperbus_Disable                   (0UL)
#define IS_OSPI_Hyperbus(MODE)                  (((MODE) == OSPI_Hyperbus_Enable) || \
                                                ((MODE) == OSPI_Hyperbus_Disable))

//OSPI_WaitCycles
#define IS_OSPI_WaitCycles(Cycles)              (((Cycles) < 32))

//OSPI_Clock_Polarity
#define OSPI_CPOL_Low                           OSPI_CTRLR0_SCPOL_INACTIVE_HIGH
#define OSPI_CPOL_High                          OSPI_CTRLR0_SCPOL_INACTIVE_LOW
#define IS_OSPI_CPOL(CPOL)                      (((CPOL) == OSPI_CPOL_Low) || \
                                                ((CPOL) == OSPI_CPOL_High))

//OSPI_Clock_Phase
#define OSPI_CPHA_1Edge                         OSPI_CTRLR0_SCPH_MIDDLE_BIT
#define OSPI_CPHA_2Edge                         OSPI_CTRLR0_SCPH_START_BIT
#define IS_OSPI_CPHA(CPHA)                      (((CPHA) == OSPI_CPHA_1Edge) || \
                                                ((CPHA) == OSPI_CPHA_2Edge))

//OSPI TXFIFOLEVEL
#define OSPI_FIFO_TX_THRESHOLD_1                (0UL << 0)
#define OSPI_FIFO_TX_THRESHOLD_4                (3UL << 0)
#define OSPI_FIFO_TX_THRESHOLD_8                (7UL << 0)
#define OSPI_FIFO_TX_THRESHOLD_16               (15UL << 0)
#define OSPI_FIFO_TX_THRESHOLD_24               (23UL << 0)
#define OSPI_FIFO_TX_THRESHOLD_32               (31UL << 0)
#define IS_OSPI_FIFO_TXLEVLE(S)                 (((S) == OSPI_FIFO_TX_THRESHOLD_1) || \
                                                ((S) == OSPI_FIFO_TX_THRESHOLD_4) || \
                                                ((S) == OSPI_FIFO_TX_THRESHOLD_8) || \
                                                ((S) == OSPI_FIFO_TX_THRESHOLD_16) || \
                                                ((S) == OSPI_FIFO_TX_THRESHOLD_24) || \
                                                ((S) == OSPI_FIFO_TX_THRESHOLD_32))

//OSPI RXFIFOLEVEL
#define OSPI_FIFO_RX_THRESHOLD_1                (0UL << 0)
#define OSPI_FIFO_RX_THRESHOLD_4                (3UL << 0)
#define OSPI_FIFO_RX_THRESHOLD_8                (7UL << 0)
#define OSPI_FIFO_RX_THRESHOLD_16               (15UL << 0)
#define OSPI_FIFO_RX_THRESHOLD_24               (23UL << 0)
#define OSPI_FIFO_RX_THRESHOLD_32               (31UL << 0)
#define IS_OSPI_FIFO_RXLEVLE(S)                 (((S) == OSPI_FIFO_RX_THRESHOLD_1) || \
                                                ((S) == OSPI_FIFO_RX_THRESHOLD_4) || \
                                                ((S) == OSPI_FIFO_RX_THRESHOLD_8) || \
                                                ((S) == OSPI_FIFO_RX_THRESHOLD_16) || \
                                                ((S) == OSPI_FIFO_RX_THRESHOLD_24) || \
                                                ((S) == OSPI_FIFO_RX_THRESHOLD_32))

//OSPI DMA
#define OSPI_DMA_TX                              OSPI_DMACR_TDMAE
#define OSPI_DMA_RX                              OSPI_DMACR_RDMAE
#define IS_OSPI_DMA_CHANNEL(C)                   (((C) == OSPI_DMA_TX) || \
                                                 ((C) == OSPI_DMA_RX) || \
                                                 ((C) == (OSPI_DMA_TX|OSPI_DMA_RX)))

//OSPI Status
#define OSPI_FLAG_STATUS_TXE                     OSPI_SR_TXE 
#define OSPI_FLAG_STATUS_RFF                     OSPI_SR_RFF
#define OSPI_FLAG_STATUS_RFNE                    OSPI_SR_RFNE
#define OSPI_FLAG_STATUS_TFE                     OSPI_SR_TFE
#define OSPI_FLAG_STATUS_TFNF                    OSPI_SR_TFNF
#define OSPI_FLAG_STATUS_BUSY                    OSPI_SR_BUSY

#define IS_OSPI_FLAG_STATUS(S)                   (((S) == OSPI_FLAG_STATUS_TXE) || \
                                                 ((S) == OSPI_FLAG_STATUS_RFF) || \
                                                 ((S) == OSPI_FLAG_STATUS_RFNE) || \
                                                 ((S) == OSPI_FLAG_STATUS_TFE) || \
                                                 ((S) == OSPI_FLAG_STATUS_TFNF) || \
                                                 ((S) == OSPI_FLAG_STATUS_BUSY))

//OSPI_IT
#define OSPI_IT_TXEI                             OSPI_RISR_TXEIR 
#define OSPI_IT_TXOI                             OSPI_RISR_TXOIR 
#define OSPI_IT_RXUI                             OSPI_RISR_RXUIR 
#define OSPI_IT_RXOI                             OSPI_RISR_RXOIR 
#define OSPI_IT_RXFI                             OSPI_RISR_RXFIR 
#define OSPI_IT_TXUI                             OSPI_RISR_TXUIR 
 

#define IS_OSPI_INT(INT)                           (((INT) == OSPI_IT_TXEI) || \
                                                   ((INT) == OSPI_IT_TXOI) || \
                                                   ((INT) == OSPI_IT_RXUI) || \
                                                   ((INT) == OSPI_IT_RXOI) || \
                                                   ((INT) == OSPI_IT_RXFI) || \
                                                   ((INT) == OSPI_IT_TXUI))

/* Exported functions ------------------------------------------------------- */

//OSPI
void OSPI_DeInit(OSPI_Type* OSPIx);
void OSPI_StructInit(OSPI_InitType* OSPI_InitStruct);
void OSPI_Init(OSPI_Type* OSPIx, OSPI_InitType* OSPI_InitStruct);
void OSPI_Cmd(OSPI_Type* OSPIx, FunctionalState NewState);
void OSPI_DMACmd(OSPI_Type* OSPIx, uint32_t OSPI_DMAReq, FunctionalState NewState);

void OSPI_SendData(OSPI_Type* OSPIx, uint32_t Data);
uint32_t OSPI_ReceiveData(OSPI_Type* OSPIx);

FlagStatus OSPI_GetFlagStatus(OSPI_Type* OSPIx, uint16_t OSPI_FLAG);
void OSPI_ITConfig(OSPI_Type* OSPIx, uint16_t OSPI_IT, FunctionalState NewState);
ITStatus OSPI_GetITStatus(OSPI_Type* OSPIx, uint16_t OSPI_IT);
void OSPI_ClearITStatus(OSPI_Type* OSPIx, uint16_t OSPI_IT);

void OSPI_TxFIFOThresholdConfig(OSPI_Type* OSPIx, uint32_t TXFIFOLevel);
void OSPI_RxFIFOThresholdConfig(OSPI_Type* OSPIx, uint32_t RXFIFOLevel);
uint16_t OSPI_GetTxFIFOLevel(OSPI_Type* OSPIx);
uint16_t OSPI_GetRxFIFOLevel(OSPI_Type* OSPIx);
void OSPI_DMA_TxFIFOLevelConfig(OSPI_Type* OSPIx, uint32_t TXFIFOLevel);
void OSPI_DMA_RxFIFOLevelConfig(OSPI_Type* OSPIx, uint32_t RXFIFOLevel);
void OSPI_ENC_Cmd(OSPI_Type* OSPIx, FunctionalState NewState);
#ifdef __cplusplus
}
#endif
#endif /* __LIB_OSPI_H */

/*********************************** END OF FILE ******************************/
