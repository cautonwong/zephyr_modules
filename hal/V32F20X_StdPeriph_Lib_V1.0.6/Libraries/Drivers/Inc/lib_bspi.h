/**
  ******************************************************************************
  * @file    lib_bspi.h 
  * @author  VT Application Team
  * @version V1.0.0
  * @date    2021-10-18
  * @brief   BSPI library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_BSPI_H
#define __LIB_BSPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   

typedef struct
{
  uint32_t Mode;
  uint32_t SPH;
  uint32_t SPO;
  uint32_t FirstBit;
  uint32_t ClockDivision;
  uint32_t CSNSoft;
  uint32_t SWAP;
} BSPI_InitType;

//Mode
#define SPI_MODE_MASTER         0
#define SPI_MODE_SLAVE          SPI_CTRL_MOD
//SPH
#define SPI_SPH_0               0
#define SPI_SPH_1               SPI_CTRL_SCKPHA
//SPO
#define SPI_SPO_0               0
#define SPI_SPO_1               SPI_CTRL_SCKPOL
//ClockDivision
#define SPI_CLKDIV_2            (0)  
#define SPI_CLKDIV_4            (SPI_CTRL_SCKSEL_0)  
#define SPI_CLKDIV_8            (SPI_CTRL_SCKSEL_1)  
#define SPI_CLKDIV_16           (SPI_CTRL_SCKSEL_0 | SPI_CTRL_SCKSEL_1) 
#define SPI_CLKDIV_32           (SPI_CTRL_SCKSEL_2) 
#define SPI_CLKDIV_64           (SPI_CTRL_SCKSEL_0 | SPI_CTRL_SCKSEL_2) 
#define SPI_CLKDIV_128          (SPI_CTRL_SCKSEL_1 | SPI_CTRL_SCKSEL_2)
//CSNSoft
#define SPI_CSNSOFT_ENABLE      SPI_CTRL_CSGPIO
#define SPI_CSNSOFT_DISABLE     0
//SWAP
#define SPI_SWAP_ENABLE         SPI_CTRL_SWAP
#define SPI_SWAP_DISABLE        0  

#define SPI_FIRSTBIT_MSB        (0UL)
#define SPI_FIRSTBIT_LSB        (0x1000UL)

//INT
#define SPI_INT_TX              (0x80000000|SPI_TXSTS_TXIEN)
#define SPI_INT_RX              (0x40000000|SPI_RXSTS_RXIEN)
                              
//status                      
#define SPI_STS_TXIF            (0x80000000|SPI_TXSTS_TXIF)
#define SPI_STS_TXEMPTY         (0x80000000|SPI_TXSTS_TXEMPTY)
#define SPI_STS_TXFUR           (0x80000000|SPI_TXSTS_TXFUR)
#define SPI_STS_RXIF            (0x40000000|SPI_RXSTS_RXIF)
#define SPI_STS_RXFULL          (0x40000000|SPI_RXSTS_RXFULL)
#define SPI_STS_RXFOV           (0x40000000|SPI_RXSTS_RXFOV)
#define SPI_STS_BSY             (0x20000000|SPI_MISC_BSY)
#define SPI_STS_RFF             (0x20000000|SPI_MISC_RFF)
#define SPI_STS_RNE             (0x20000000|SPI_MISC_RNE)
#define SPI_STS_TNF             (0x20000000|SPI_MISC_TNF)
#define SPI_STS_TFE             (0x20000000|SPI_MISC_TFE)
                              
//TXFLEV                      
#define SPI_TXFLEV_0            (0)
#define SPI_TXFLEV_1            (SPI_TXSTS_TXFLEV_0)
#define SPI_TXFLEV_2            (SPI_TXSTS_TXFLEV_1)
#define SPI_TXFLEV_3            (SPI_TXSTS_TXFLEV_0 | SPI_TXSTS_TXFLEV_1)
#define SPI_TXFLEV_4            (SPI_TXSTS_TXFLEV_2)
#define SPI_TXFLEV_5            (SPI_TXSTS_TXFLEV_0 | SPI_TXSTS_TXFLEV_2)
#define SPI_TXFLEV_6            (SPI_TXSTS_TXFLEV_1 | SPI_TXSTS_TXFLEV_2)
#define SPI_TXFLEV_7            (SPI_TXSTS_TXFLEV_0 | SPI_TXSTS_TXFLEV_1 | SPI_TXSTS_TXFLEV_2)
                               
//RXFLEV                       
#define SPI_RXFLEV_0            (0)
#define SPI_RXFLEV_1            (SPI_RXSTS_RXFLEV_0)
#define SPI_RXFLEV_2            (SPI_RXSTS_RXFLEV_1)
#define SPI_RXFLEV_3            (SPI_RXSTS_RXFLEV_0 | SPI_RXSTS_RXFLEV_1)
#define SPI_RXFLEV_4            (SPI_RXSTS_RXFLEV_2)
#define SPI_RXFLEV_5            (SPI_RXSTS_RXFLEV_2 | SPI_RXSTS_RXFLEV_0)
#define SPI_RXFLEV_6            (SPI_RXSTS_RXFLEV_2 | SPI_RXSTS_RXFLEV_1)
#define SPI_RXFLEV_7            (SPI_RXSTS_RXFLEV_2 | SPI_RXSTS_RXFLEV_1 | SPI_RXSTS_RXFLEV_0)



/****************************** SPI Instances *********************************/
#define IS_BSPI_ALL_INSTANCE(INSTANCE) (((INSTANCE) == BSPI0) || \
                                           ((INSTANCE) == BSPI1) || \
                                           ((INSTANCE) == BSPI2) || \
                                           ((INSTANCE) == BSPI3) || \
                                           ((INSTANCE) == BSPI4) || \
                                           ((INSTANCE) == BSPI5))
                   
/* Private macros ------------------------------------------------------------*/
#define IS_BSPI_MODE(__MODE__)  (((__MODE__) == SPI_MODE_MASTER) || ((__MODE__) == SPI_MODE_SLAVE))

#define IS_BSPI_SPH(__SPH__)  (((__SPH__) == SPI_SPH_0) || ((__SPH__) == SPI_SPH_1))

#define IS_BSPI_SPO(__SPO__)  (((__SPO__) == SPI_SPO_0) || ((__SPO__) == SPI_SPO_1)) 

#define IS_BSPI_CLKDIV(__CLKDIV__)  (((__CLKDIV__) == SPI_CLKDIV_2) ||\
                                        ((__CLKDIV__) == SPI_CLKDIV_4) ||\
                                        ((__CLKDIV__) == SPI_CLKDIV_8) ||\
                                        ((__CLKDIV__) == SPI_CLKDIV_16)||\
                                        ((__CLKDIV__) == SPI_CLKDIV_32)||\
                                        ((__CLKDIV__) == SPI_CLKDIV_64)||\
                                        ((__CLKDIV__) == SPI_CLKDIV_128))

#define IS_BSPI_CSN(__CSN__)  (((__CSN__) == SPI_CSNSOFT_ENABLE) || ((__CSN__) == SPI_CSNSOFT_DISABLE))

#define IS_BSPI_SWAP(__SWAP__)  (((__SWAP__) == SPI_SWAP_ENABLE) || ((__SWAP__) == SPI_SWAP_DISABLE))

#define IS_BSPI_INT(__INT__)  ((((__INT__) & (SPI_INT_TX | SPI_INT_RX)) != 0U) &&\
                                  (((__INT__) & ~(SPI_INT_TX | SPI_INT_RX)) == 0U))

#define IS_BSPI_STSR(__STSR__)  (((__STSR__) == SPI_STS_TXIF)    ||\
                                    ((__STSR__) == SPI_STS_TXEMPTY) ||\
                                    ((__STSR__) == SPI_STS_TXFUR)   ||\
                                    ((__STSR__) == SPI_STS_RXFULL)  ||\
                                    ((__STSR__) == SPI_STS_RXFOV)   ||\
                                    ((__STSR__) == SPI_STS_BSY)     ||\
                                    ((__STSR__) == SPI_STS_RFF)     ||\
                                    ((__STSR__) == SPI_STS_RNE)     ||\
                                    ((__STSR__) == SPI_STS_TNF)     ||\
                                    ((__STSR__) == SPI_STS_TFE)     ||\
                                    ((__STSR__) == SPI_STS_RXIF))

#define IS_BSPI_STSC(__STSC__)  ((((__STSC__) & (SPI_STS_TXIF | SPI_STS_RXIF)) != 0U) &&\
                                    (((__STSC__) & ~(SPI_STS_TXIF | SPI_STS_RXIF)) == 0U))

#define IS_BSPI_TXFLEV(__TXFLEV__)  (((__TXFLEV__) == SPI_TXFLEV_0) ||\
                                        ((__TXFLEV__) == SPI_TXFLEV_1) ||\
                                        ((__TXFLEV__) == SPI_TXFLEV_2) ||\
                                        ((__TXFLEV__) == SPI_TXFLEV_3) ||\
                                        ((__TXFLEV__) == SPI_TXFLEV_4) ||\
                                        ((__TXFLEV__) == SPI_TXFLEV_5) ||\
                                        ((__TXFLEV__) == SPI_TXFLEV_6) ||\
                                        ((__TXFLEV__) == SPI_TXFLEV_7))

#define IS_BSPI_RXFLEV(__RXFLEV__)  (((__RXFLEV__) == SPI_RXFLEV_0) ||\
                                        ((__RXFLEV__) == SPI_RXFLEV_1) ||\
                                        ((__RXFLEV__) == SPI_RXFLEV_2) ||\
                                        ((__RXFLEV__) == SPI_RXFLEV_3) ||\
                                        ((__RXFLEV__) == SPI_RXFLEV_4) ||\
                                        ((__RXFLEV__) == SPI_RXFLEV_5) ||\
                                        ((__RXFLEV__) == SPI_RXFLEV_6) ||\
                                        ((__RXFLEV__) == SPI_RXFLEV_7))


/******************************************************************************/
/*                                                                            */
/*                               SPI controller (SPI)                         */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for SPIx_CTRL register      ******************/
#define SPI_CTRL_SCKSEL_Pos           (0U)                                     
#define SPI_CTRL_SCKSEL_Msk           (0x7U << SPI_CTRL_SCKSEL_Pos)            /*!< 0x00000007 */
#define SPI_CTRL_SCKSEL                SPI_CTRL_SCKSEL_Msk                     /*!< Master mode clock selection */
#define SPI_CTRL_SCKSEL_0             (0x1U << SPI_CTRL_SCKSEL_Pos)            /*!< 0x00000001 */
#define SPI_CTRL_SCKSEL_1             (0x2U << SPI_CTRL_SCKSEL_Pos)            /*!< 0x00000002 */
#define SPI_CTRL_SCKSEL_2             (0x4U << SPI_CTRL_SCKSEL_Pos)            /*!< 0x00000004 */
#define SPI_CTRL_SCKPOL_Pos           (4U)                                     
#define SPI_CTRL_SCKPOL_Msk           (0x1U << SPI_CTRL_SCKPOL_Pos)            /*!< 0x00000010 */
#define SPI_CTRL_SCKPOL                SPI_CTRL_SCKPOL_Msk                     /*!< SPI clock polarity */
#define SPI_CTRL_SCKPHA_Pos           (5U)                                     
#define SPI_CTRL_SCKPHA_Msk           (0x1U << SPI_CTRL_SCKPHA_Pos)            /*!< 0x00000020 */
#define SPI_CTRL_SCKPHA                SPI_CTRL_SCKPHA_Msk                     /*!< SPI clock phase */
#define SPI_CTRL_MOD_Pos              (8U)                                     
#define SPI_CTRL_MOD_Msk              (0x1U << SPI_CTRL_MOD_Pos)               /*!< 0x00000100 */
#define SPI_CTRL_MOD                   SPI_CTRL_MOD_Msk                        /*!< SPI Mode Selection register */
#define SPI_CTRL_SWAP_Pos             (9U)                                     
#define SPI_CTRL_SWAP_Msk             (0x1U << SPI_CTRL_SWAP_Pos)              /*!< 0x00000200 */
#define SPI_CTRL_SWAP                  SPI_CTRL_SWAP_Msk                       /*!< SPI MISO/MOSI swap control register */
#define SPI_CTRL_CSGPIO_Pos           (10U)                                     
#define SPI_CTRL_CSGPIO_Msk           (0x1U << SPI_CTRL_CSGPIO_Pos)            /*!< 0x00000400 */
#define SPI_CTRL_CSGPIO                SPI_CTRL_CSGPIO_Msk                     /*!< SPI CS pin is controlled by GPIO or H/W */
#define SPI_CTRL_SPIRST_Pos           (11U)                                     
#define SPI_CTRL_SPIRST_Msk           (0x1U << SPI_CTRL_SPIRST_Pos)            /*!< 0x00000800 */
#define SPI_CTRL_SPIRST                SPI_CTRL_SPIRST_Msk                     /*!< SPI Soft Reset */
#define SPI_CTRL_SPIEN_Pos            (15U)                                  
#define SPI_CTRL_SPIEN_Msk            (0x1U << SPI_CTRL_SPIEN_Pos)             /*!< 0x00008000 */
#define SPI_CTRL_SPIEN                 SPI_CTRL_SPIEN_Msk                      /*!< SPI enable */

/**************  Bits definition for SPIx_TXSTS register     ******************/
#define SPI_TXSTS_TXFFLAG_Pos         (0U)                                     
#define SPI_TXSTS_TXFFLAG_Msk         (0xFU << SPI_TXSTS_TXFFLAG_Pos)          /*!< 0x0000000F */
#define SPI_TXSTS_TXFFLAG              SPI_TXSTS_TXFFLAG_Msk                   /*!< Transmit FIFO Data Level */
#define SPI_TXSTS_TXFFLAG_0           (0x1U << SPI_TXSTS_TXFFLAG_Pos)          /*!< 0x00000001 */
#define SPI_TXSTS_TXFFLAG_1           (0x2U << SPI_TXSTS_TXFFLAG_Pos)          /*!< 0x00000002 */
#define SPI_TXSTS_TXFFLAG_2           (0x4U << SPI_TXSTS_TXFFLAG_Pos)          /*!< 0x00000004 */
#define SPI_TXSTS_TXFFLAG_3           (0x8U << SPI_TXSTS_TXFFLAG_Pos)          /*!< 0x00000008 */
#define SPI_TXSTS_TXFLEV_Pos          (4U)                                     
#define SPI_TXSTS_TXFLEV_Msk          (0x7U << SPI_TXSTS_TXFLEV_Pos)           /*!< 0x00000070 */
#define SPI_TXSTS_TXFLEV               SPI_TXSTS_TXFLEV_Msk                    /*!< Transmit FIFO interrupt level register */
#define SPI_TXSTS_TXFLEV_0            (0x1U << SPI_TXSTS_TXFLEV_Pos)           /*!< 0x00000010 */
#define SPI_TXSTS_TXFLEV_1            (0x2U << SPI_TXSTS_TXFLEV_Pos)           /*!< 0x00000020 */
#define SPI_TXSTS_TXFLEV_2            (0x4U << SPI_TXSTS_TXFLEV_Pos)           /*!< 0x00000040 */
#define SPI_TXSTS_TXFUR_Pos           (8U)                                     
#define SPI_TXSTS_TXFUR_Msk           (0x1U << SPI_TXSTS_TXFUR_Pos)            /*!< 0x00000100 */
#define SPI_TXSTS_TXFUR                SPI_TXSTS_TXFUR_Msk                     /*!< Transmit FIFO under run register */
#define SPI_TXSTS_TXEMPTY_Pos         (9U)                                     
#define SPI_TXSTS_TXEMPTY_Msk         (0x1U << SPI_TXSTS_TXEMPTY_Pos)          /*!< 0x00000200 */
#define SPI_TXSTS_TXEMPTY              SPI_TXSTS_TXEMPTY_Msk                   /*!< Transmot FIFO empty register */
#define SPI_TXSTS_TXIEN_Pos           (14U)                                     
#define SPI_TXSTS_TXIEN_Msk           (0x1U << SPI_TXSTS_TXIEN_Pos)            /*!< 0x00004000 */
#define SPI_TXSTS_TXIEN                SPI_TXSTS_TXIEN_Msk                     /*!< SPI Transmit Interrupt Enable */
#define SPI_TXSTS_TXIF_Pos            (15U)                                     
#define SPI_TXSTS_TXIF_Msk            (0x1U << SPI_TXSTS_TXIF_Pos)             /*!< 0x00008000 */
#define SPI_TXSTS_TXIF                 SPI_TXSTS_TXIF_Msk                      /*!< SPI Transmit Interrupt flag */

/**************  Bits definition for SPIx_TXDAT register     ******************/
#define SPI_TXDAT_SPITXD_Pos          (0U)                                     
#define SPI_TXDAT_SPITXD_Msk          (0xFFU << SPI_TXDAT_SPITXD_Pos)             /*!< 0x000000FF */
#define SPI_TXDAT_SPITXD               SPI_TXDAT_SPITXD_Msk                      /*!< Write data to SPI Transmit FIFO */

/**************  Bits definition for SPIx_RXSTS register     ******************/
#define SPI_RXSTS_RXFFLAG_Pos         (0U)                                     
#define SPI_RXSTS_RXFFLAG_Msk         (0xFU << SPI_RXSTS_RXFFLAG_Pos)          /*!< 0x0000000F */
#define SPI_RXSTS_RXFFLAG              SPI_RXSTS_RXFFLAG_Msk                   /*!< Receive FIFO Data Level */
#define SPI_RXSTS_RXFFLAG_0           (0x1U << SPI_RXSTS_RXFFLAG_Pos)          /*!< 0x00000001 */
#define SPI_RXSTS_RXFFLAG_1           (0x2U << SPI_RXSTS_RXFFLAG_Pos)          /*!< 0x00000002 */
#define SPI_RXSTS_RXFFLAG_2           (0x4U << SPI_RXSTS_RXFFLAG_Pos)          /*!< 0x00000004 */
#define SPI_RXSTS_RXFFLAG_3           (0x8U << SPI_RXSTS_RXFFLAG_Pos)          /*!< 0x00000008 */
#define SPI_RXSTS_RXFLEV_Pos          (4U)                                     
#define SPI_RXSTS_RXFLEV_Msk          (0x7U << SPI_RXSTS_RXFLEV_Pos)           /*!< 0x00000070 */
#define SPI_RXSTS_RXFLEV               SPI_RXSTS_RXFLEV_Msk                    /*!< Receive FIFO interrupt level register */
#define SPI_RXSTS_RXFLEV_0            (0x1U << SPI_RXSTS_RXFLEV_Pos)           /*!< 0x00000010 */
#define SPI_RXSTS_RXFLEV_1            (0x2U << SPI_RXSTS_RXFLEV_Pos)           /*!< 0x00000020 */
#define SPI_RXSTS_RXFLEV_2            (0x4U << SPI_RXSTS_RXFLEV_Pos)           /*!< 0x00000040 */
#define SPI_RXSTS_RXFOV_Pos           (8U)                                     
#define SPI_RXSTS_RXFOV_Msk           (0x1U << SPI_RXSTS_RXFOV_Pos)            /*!< 0x00000100 */
#define SPI_RXSTS_RXFOV                SPI_RXSTS_RXFOV_Msk                     /*!< Receive FIFO over run register */
#define SPI_RXSTS_RXFULL_Pos          (9U)                                     
#define SPI_RXSTS_RXFULL_Msk          (0x1U << SPI_RXSTS_RXFULL_Pos)           /*!< 0x00000200 */
#define SPI_RXSTS_RXFULL               SPI_RXSTS_RXFULL_Msk                    /*!< Receive FIFO full register */
#define SPI_RXSTS_RXIEN_Pos           (14U)                                     
#define SPI_RXSTS_RXIEN_Msk           (0x1U << SPI_RXSTS_RXIEN_Pos)            /*!< 0x00004000 */
#define SPI_RXSTS_RXIEN                SPI_RXSTS_RXIEN_Msk                     /*!< SPI Receive Interrupt Enable */
#define SPI_RXSTS_RXIF_Pos            (15U)                                    
#define SPI_RXSTS_RXIF_Msk            (0x1U << SPI_RXSTS_RXIF_Pos)             /*!< 0x00008000 */
#define SPI_RXSTS_RXIF                 SPI_RXSTS_RXIF_Msk                      /*!< SPI Receive Interrupt flag */

/**************  Bits definition for SPIx_RXDAT register     ******************/
#define SPI_RXDAT_SPIRXD_Pos          (0U)                                     
#define SPI_RXDAT_SPIRXD_Msk          (0xFFU << SPI_RXDAT_SPIRXD_Pos)             /*!< 0x000000FF */
#define SPI_RXDAT_SPIRXD               SPI_RXDAT_SPIRXD_Msk                      /*!< Read data from SPI Receive FIFO */

/**************  Bits definition for SPIx_MISC register      ******************/
#define SPI_MISC_TFE_Pos              (0U)                                    
#define SPI_MISC_TFE_Msk              (0x1U << SPI_MISC_TFE_Pos)               /*!< 0x0000001 */
#define SPI_MISC_TFE                   SPI_MISC_TFE_Msk                        /*!< Transmit FIFO Empty Flag */
#define SPI_MISC_TNF_Pos              (1U)                                    
#define SPI_MISC_TNF_Msk              (0x1U << SPI_MISC_TNF_Pos)               /*!< 0x0000002 */
#define SPI_MISC_TNF                   SPI_MISC_TNF_Msk                        /*!< Transmit FIFO Not Full Flag */
#define SPI_MISC_RNE_Pos              (2U)                                    
#define SPI_MISC_RNE_Msk              (0x1U << SPI_MISC_RNE_Pos)               /*!< 0x0000004 */
#define SPI_MISC_RNE                   SPI_MISC_RNE_Msk                        /*!< Receive FIFO Not Empty Flag */
#define SPI_MISC_RFF_Pos              (3U)                                    
#define SPI_MISC_RFF_Msk              (0x1U << SPI_MISC_RFF_Pos)               /*!< 0x0000008 */
#define SPI_MISC_RFF                   SPI_MISC_RFF_Msk                        /*!< Receive FIFO Full Flag */
#define SPI_MISC_BSY_Pos              (4U)                                    
#define SPI_MISC_BSY_Msk              (0x1U << SPI_MISC_BSY_Pos)               /*!< 0x0000010 */
#define SPI_MISC_BSY                   SPI_MISC_BSY_Msk                        /*!< SPI Controller Busy Flag */
#define SPI_MISC_SMART_Pos            (8U)                                    
#define SPI_MISC_SMART_Msk            (0x1U << SPI_MISC_SMART_Pos)             /*!< 0x0000100 */
#define SPI_MISC_SMART                 SPI_MISC_SMART_Msk                      /*!< SPI FIFO SMART Mode Register */
#define SPI_MISC_OVER_Pos             (9U)                                    
#define SPI_MISC_OVER_Msk             (0x1U << SPI_MISC_OVER_Pos)              /*!< 0x0000200 */
#define SPI_MISC_OVER                  SPI_MISC_OVER_Msk                       /*!< SPI FIFO Over Write Mode */









/* Exported Functions ------------------------------------------------------- */
/* SPI Exported Functions Group1: 
                                  (De)Initialization -------------------------*/
void BSPI_DeviceInit(BSPI_Type *SPIx);
void BSPI_Init(BSPI_Type *SPIx, BSPI_InitType *InitStruct);
void BSPI_StructInit(BSPI_InitType *InitStruct);
/* SPI Exported Functions Group2: 
                                  Interrupt (flag) ---------------------------*/
void BSPI_INTConfig(BSPI_Type *SPIx, uint32_t INTMask, uint32_t NewState);
uint8_t BSPI_GetStatus(BSPI_Type *SPIx, uint32_t Status);
void BSPI_ClearStatus(BSPI_Type *SPIx, uint32_t Status);
/* SPI Exported Functions Group3: 
                                  Transfer datas -----------------------------*/
void BSPI_SendData(BSPI_Type *SPIx, uint8_t ch);
uint8_t BSPI_ReceiveData(BSPI_Type *SPIx);
/* SPI Exported Functions Group4: 
                                  MISC Configuration -------------------------*/
void BSPI_Cmd(BSPI_Type *SPIx, uint32_t NewState);
void BSPI_TransmitFIFOLevelConfig(BSPI_Type *SPIx, uint32_t FIFOLevel);
void BSPI_ReceiveFIFOLevelConfig(BSPI_Type *SPIx, uint32_t FIFOLevel);
uint8_t BSPI_GetTransmitFIFOLevel(BSPI_Type *SPIx);
uint8_t BSPI_GetReceiveFIFOLevel(BSPI_Type *SPIx);
void BSPI_SmartModeCmd(BSPI_Type *SPIx, uint32_t NewState);
void BSPI_OverWriteModeCmd(BSPI_Type *SPIx, uint32_t NewState);


#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_BSPI_H */

/******************* (C) COPYRIGHT Vango Technologies, Inc *****END OF FILE****/
