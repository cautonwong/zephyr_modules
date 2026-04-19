/**
  ******************************************************************************
  * @file    lib_sdio.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-04-16
  * @brief   SDIO library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_SDIO_H
#define __LIB_SDIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup SDIO
  * @{
  */

/** @defgroup SDIO_Exported_Types
  * @{
  */
typedef struct
{
  uint8_t Mode;                 /*!< Specifies the mode of the SDIO controller. */
  uint8_t ClockSource;          /*!< Specifies the clock source of the SDIO controller. */
  uint8_t ClockDiv;             /*!< Specifies the clock division of the SDIO controller. */
  uint32_t BusWide;             /*!< Specifies the bus wide of the SDIO controller. */
} SDIO_InitType;

typedef struct
{
  uint8_t  DMAMode;             /*!< Specifies the DMA mode of the SDIO controller. */
  uint32_t SDMAAddr;            /*!< Specifies the DMA address of the SDIO controller. */
  uint32_t SDMABufferBoundary;  /*!< Specifies the DMA buffer boundary of the SDIO controller. */
  uint8_t  BlockCount;          /*!< Specifies the block count of the SDIO controller. */
  uint16_t BlockSize;           /*!< Specifies the block size of the SDIO controller. */
  uint8_t  TransferDir;         /*!< Specifies the data transfer direction of the SDIO controller. */
  uint32_t MultiSingleMode;     /*!< Specifies whether data transfer is in single or multi mode */
} SDIO_DATAInitType;

typedef struct
{
  uint32_t CmdIndex;
  uint32_t CmdType;
  uint8_t  CmdAuto;
  uint32_t Argument;
  uint32_t Response;
  uint8_t  DataMode;   //0:CMD without data; 1:CMD with data
  SDIO_DATAInitType DataInit;
} SDIO_CMDInitType;

/** @defgroup SDIO_Exported_Constants
  * @{
  */

/** @defgroup SDIO_Mode
  * @{
  */
#define SDIO_MODE_SD                      ((uint8_t)0x00)
#define SDIO_MODE_SDR                     ((uint8_t)0x02)
#define SDIO_MODE_DDR                     ((uint8_t)0x03)
#define SDIO_MODE_HS200                   ((uint8_t)0x04)
#define SDIO_MODE_HS400                   ((uint8_t)0x05)
#define SDIO_MODE_EHS400                  ((uint8_t)0x06)
#define IS_SDIO_MODE(__MODE__)            (((__MODE__) == SDIO_MODE_SD)      || \
                                           ((__MODE__) == SDIO_MODE_SDR)     || \
                                           ((__MODE__) == SDIO_MODE_DDR)     || \
                                           ((__MODE__) == SDIO_MODE_HS200)   || \
                                           ((__MODE__) == SDIO_MODE_HS400)   || \
                                           ((__MODE__) == SDIO_MODE_EHS400))
/**
  * @}
  */

/** @defgroup SDIO_Clock_Source
  * @{
  */
#define SDIO_CLK_RCH                        ((uint32_t)0x00000000)
#define SDIO_CLK_PLL0                       ((uint32_t)0x00000001)
#define SDIO_CLK_PLL1                       ((uint32_t)0x00000002)
#define SDIO_CLK_XOH                        ((uint32_t)0x00000003)
#define SDIO_CLK_RCH_DIV4                   ((uint32_t)0x00000004)
#define SDIO_CLK_RCH_DIV48                  ((uint32_t)0x00000005)
#define SDIO_CLK_32KRC                      ((uint32_t)0x00000006)
#define SDIO_CLK_32KXTAL                    ((uint32_t)0x00000007)
#define IS_SDIO_CLK(__CLK__)                 (((__CLK__) == SDIO_CLK_RCH)       || \
                                              ((__CLK__) == SDIO_CLK_PLL0)      || \
                                              ((__CLK__) == SDIO_CLK_PLL1)      || \
                                              ((__CLK__) == SDIO_CLK_XOH)       || \
                                              ((__CLK__) == SDIO_CLK_RCH_DIV4)  || \
                                              ((__CLK__) == SDIO_CLK_RCH_DIV48) || \
                                              ((__CLK__) == SDIO_CLK_32KRC)     || \
                                              ((__CLK__) == SDIO_CLK_32KXTAL))
/**
  * @}
  */

/** @defgroup SDIO_Bus_Wide 
  * @{
  */
#define SDIO_BusWide_1b                     ((uint8_t)0x00)
#define SDIO_BusWide_4b                     ((uint8_t)0x02)
#define SDIO_BusWide_8b                     ((uint8_t)0x20)
#define IS_SDIO_BUS_WIDE(__WIDE__)          (((__WIDE__) == SDIO_BusWide_1b) || \
                                             ((__WIDE__) == SDIO_BusWide_4b) || \
                                             ((__WIDE__) == SDIO_BusWide_8b))
/**
  * @}
  */
  
/** @defgroup SDIO_DataMode
  * @{
  */
#define SDIO_CMD                           ((uint8_t)0x00)
#define SDIO_DATA                          ((uint8_t)0x01)
#define IS_SDIO_DATA_TYPE(__TYPE__)        (((__TYPE__) == SDIO_CMD)     || \
                                            ((__TYPE__) == SDIO_DATA))
/**
  * @}
  */

/** @defgroup SDIO_Command_Index
  * @{
  */
#define IS_SDIO_CMD_INDEX(__INDEX__)       ((__INDEX__) < 0x40)
/**
  * @}
  */
  
/** @defgroup SDIO_Command_Type
  * @{
  */
#define CMDTYPE_Normal                 ((uint32_t)0x00000000)
#define CMDTYPE_Abort                  ((uint32_t)0x00C00000)
#define IS_CMDTYPE(__CMDTYPE__)        (((__CMDTYPE__) == CMDTYPE_Normal) || \
                                        ((__CMDTYPE__) == CMDTYPE_Abort))
/**
  * @}
  */

/** @defgroup SDIO_Command_Auto
  * @{
  */ 
//CmdAuto
#define SDIO_CMDAUTO_No                     ((uint32_t)0x00000000)
#define SDIO_CMDAUTO_CMD12                  ((uint32_t)0x00000004)
#define SDIO_CMDAUTO_CMD23                  ((uint32_t)0x00000008)
#define IS_SDIO_CMDAUTO(__CMDAUTO__)        (((__CMDAUTO__) == SDIO_CMDAUTO_No)    || \
                                             ((__CMDAUTO__) == SDIO_CMDAUTO_CMD12) || \
                                             ((__CMDAUTO__) == SDIO_CMDAUTO_CMD12))
/**
  * @}
  */

/** @defgroup SDIO_Response_Registers 
  * @{
  */
#define SDIO_Response_No                    ((uint32_t)0x00000000)
#define SDIO_Response_Long                  ((uint32_t)0x00010000)
#define SDIO_Response_Short                 ((uint32_t)0x00020000)
#define IS_SDIO_RESPONSE(__RESPONSE__)      (((__RESPONSE__) == SDIO_Response_No)    || \
                                             ((__RESPONSE__) == SDIO_Response_Short) || \
                                             ((__RESPONSE__) == SDIO_Response_Long))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Direction 
  * @{
  */
#define SDIO_DATA_Read                    ((uint32_t)0x00000010)
#define SDIO_DATA_Write                   ((uint32_t)0x00000000)
#define IS_SDIO_DATATRANS(__DATATRANS__)  (((__DATATRANS__) == SDIO_DATA_Read) || \
                                            ((__DATATRANS__) == SDIO_DATA_Write))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Mode 
  * @{
  */
#define SDIO_DATA_Single                  ((uint32_t)0x00000000)
#define SDIO_DATA_Multi                   ((uint32_t)0x00000020)
#define IS_SDIO_DATABLCOK(__DATABLCOK__)  (((__DATABLCOK__) == SDIO_DATA_Single) || \
                                           ((__DATABLCOK__) == SDIO_DATA_Multi))
/**
  * @}
  */

/** @defgroup SDIO_Response_Registers 
  * @{
  */
#define SDIO_RESP1                          ((uint8_t)0x00)
#define SDIO_RESP2                          ((uint8_t)0x04)
#define SDIO_RESP3                          ((uint8_t)0x08)
#define SDIO_RESP4                          ((uint8_t)0x0C)
#define IS_SDIO_RESP(__RESP__)              (((__RESP__) == SDIO_RESP1) || \
                                             ((__RESP__) == SDIO_RESP2) || \
                                             ((__RESP__) == SDIO_RESP3) || \
                                             ((__RESP__) == SDIO_RESP4))
/**
  * @}
  */

/** @defgroup SDIO_DMA_Mode 
  * @{
  */
#define SDIO_NODMA                          ((uint8_t)0x00)
#define SDIO_SDMA                           ((uint8_t)0x01)
#define SDIO_ADMA                           ((uint8_t)0x02)
#define IS_SDIO_DMA_MODE(__MODE__)          (((__MODE__) == SDIO_NODMA) || \
                                             ((__MODE__) == SDIO_SDMA)  || \
                                             ((__MODE__) == SDIO_ADMA))
/**
  * @}
  */

/** @defgroup Option_Bytes_INFO
  * @{
  */
#define SDIO_INFO_SWR                     ((uint8_t)0x001)
/**
  * @}
  */
  
/** @defgroup SDIO_Clock_Division
  * @{
  */
#define SDIO0_CLKSEL_Pos                  (0)
#define SDIO0_CLKSEL_Msk                  ((uint32_t)0x00000007)
#define SDIO0_CLKDIV_Pos                  (3)
#define SDIO0_CLKDIV_Msk                  ((uint32_t)0x000003F8)
#define SDIO1_CLKSEL_Pos                  (16)
#define SDIO1_CLKSEL_Msk                  ((uint32_t)0x00070000)
#define SDIO1_CLKDIV_Pos                  (19)
#define SDIO1_CLKDIV_Msk                  ((uint32_t)0x03F80000)
/**
  * @}
  */
  
/** @defgroup SDIO_SDMA_Buffer_Boundary
  * @{
  */
#define SDIO_SRS_BSBC_SDMABB_4KB          ((uint32_t)0x00000000)
#define SDIO_SRS_BSBC_SDMABB_8KB          ((uint32_t)0x00001000)
#define SDIO_SRS_BSBC_SDMABB_16KB         ((uint32_t)0x00002000)
#define SDIO_SRS_BSBC_SDMABB_32KB         ((uint32_t)0x00003000)
#define SDIO_SRS_BSBC_SDMABB_64KB         ((uint32_t)0x00004000)
#define SDIO_SRS_BSBC_SDMABB_128KB        ((uint32_t)0x00005000)
#define SDIO_SRS_BSBC_SDMABB_256KB        ((uint32_t)0x00006000)
#define SDIO_SRS_BSBC_SDMABB_512KB        ((uint32_t)0x00007000)
/**
  * @}
  */

/******************  Bits definition for CMD register  *******************/
#define SDIO_CMD_DMA_EN              ((uint8_t)1<<0)
#define SDIO_CMD_BCE_EN              ((uint8_t)1<<1)
#define SDIO_CMD_ACE_MSK             ((uint8_t)3<<2)
#define SDIO_CMD_ACE_No              ((uint8_t)0<<2)
#define SDIO_CMD_ACE_CMD12           ((uint8_t)1<<2)
#define SDIO_CMD_ACE_CMD23           ((uint8_t)2<<2)
#define SDIO_CMD_DTDS                ((uint8_t)1<<4)
#define SDIO_CMD_MSBS                ((uint8_t)1<<5)
#define SDIO_CMD_RECT                ((uint8_t)1<<6)
#define SDIO_CMD_RECE                ((uint8_t)1<<7)
#define SDIO_CMD_RID                 ((uint8_t)1<<8)
#define SDIO_CMD_RTC_MSK             ((uint32_t)3<<16)
#define SDIO_CMD_RTC_136B            ((uint32_t)1<<16)
#define SDIO_CMD_RTC_48B             ((uint32_t)2<<16)
#define SDIO_CMD_RTC_48B_BUSY        ((uint32_t)3<<16)
#define SDIO_CMD_CRC_EN              ((uint32_t)1<<19)
#define SDIO_CMD_CICE_EN             ((uint32_t)1<<20)
#define SDIO_CMD_CIDX_POS            ((uint32_t)1<<24)
/******************  Bits definition for CTRL1 register  *******************/
#define SDIO_CTRL1_DATWIDTH_Msk          ((uint32_t)0x00000022)
#define SDIO_CTRL1_DATWIDTH_1BIT         ((uint32_t)0x00000000)
#define SDIO_CTRL1_DATWIDTH_4BIT         ((uint32_t)0x00000002)
#define SDIO_CTRL1_DATWIDTH_8BIT         ((uint32_t)0x00000020)

/******************  Bits definition for SDIO_MODE register  *******************/
#define SDIO_MODE_Msk                   ((uint32_t)0x00000007)


/******************  Bits definition for SDIO_CTRL1 register  *******************/
#define SDIO_CTRL1_VDD1VOT_Msk          ((uint32_t)0x00000E00)
#define SDIO_CTRL1_VDD1VOT_1_8V         ((uint32_t)0x00000A00)
#define SDIO_CTRL1_VDD1VOT_3_0V         ((uint32_t)0x00000C00)
#define SDIO_CTRL1_VDD1VOT_3_3V         ((uint32_t)0x00000E00)
#define IS_SDIO_VDD1(__VDD1__)          (((__VDD1__) == SDIO_CTRL1_VDD1VOT_1_8V)  || \
                                         ((__VDD1__) == SDIO_CTRL1_VDD1VOT_3_0V)  || \
                                         ((__VDD1__) == SDIO_CTRL1_VDD1VOT_3_3V))
#define SDIO_CTRL1_VDD2VOT_Msk          ((uint32_t)0x0000E000)
#define SDIO_CTRL1_VDD2VOT_1_2V         ((uint32_t)0x00008000)
#define SDIO_CTRL1_VDD2VOT_1_8V         ((uint32_t)0x0000A000)
#define IS_SDIO_VDD2(__VDD2__)          (((__VDD2__) == SDIO_CTRL1_VDD2VOT_1_2V)  || \
                                         ((__VDD2__) == SDIO_CTRL1_VDD2VOT_1_8V))

/******************  Bits definition for SDIO_CTRL2 register  *******************/
#define SDIO_CTRL2_ICE          ((uint8_t)1<<0)

/******************  Bits definition for SDIO_HRS12 register  *******************/
#define SDIO_IT_CC              ((uint32_t)0x00000001)
#define SDIO_IT_TC              ((uint32_t)0x00000002)
#define SDIO_IT_DMA             ((uint32_t)0x00000008)

//Device
#define SDIO_DEVICE_SDCard                     ((uint32_t)0x00000000)
#define SDIO_DEVICE_SDR                        ((uint32_t)0x00000002)
#define SDIO_DEVICE_DDR                        ((uint32_t)0x00000003)
#define SDIO_DEVICE_HS200                      ((uint32_t)0x00000004)
#define SDIO_DEVICE_HS400                      ((uint32_t)0x00000005)
#define SDIO_DEVICE_ENHANCEDHS400              ((uint32_t)0x00000006)
#define IS_SDIO_DEVICE(__DEVICE__)             (((__DEVICE__) == SDIO_DEVICE_SDCard)  || \
                                                ((__DEVICE__) == SDIO_DEVICE_SDR)     || \
																								((__DEVICE__) == SDIO_DEVICE_DDR)     || \
																								((__DEVICE__) == SDIO_DEVICE_HS200)   || \
																								((__DEVICE__) == SDIO_DEVICE_HS400)   || \
                                                ((__DEVICE__) == SDIO_DEVICE_ENHANCEDHS400))

#define SDIO_STATUS_CMD_COMPLETE             ((uint32_t)0x00000001)
#define SDIO_STATUS_TRANF_COMPLETE           ((uint32_t)0x00000002)	
#define SDIO_STATUS_GAP_EVENT                ((uint32_t)0x00000004)
#define SDIO_STATUS_DMA                      ((uint32_t)0x00000008)
#define SDIO_STATUS_WR_BUFFER                ((uint32_t)0x00000010)
#define SDIO_STATUS_RD_BUFFER                ((uint32_t)0x00000020)
#define SDIO_STATUS_INSERT_CARD              ((uint32_t)0x00000040)
#define SDIO_STATUS_REMOVE_CARD              ((uint32_t)0x00000080)
#define SDIO_STATUS_CARD_STATUS              ((uint32_t)0x00000100)
#define SDIO_STATUS_CMD_QUE                  ((uint32_t)0x00004000)
#define SDIO_STATUS_CMD_TIMEOUT              ((uint32_t)0x00010000)
#define SDIO_STATUS_CMD_CRCERR               ((uint32_t)0x00020000)
#define SDIO_STATUS_CMD_ENDBITERR            ((uint32_t)0x00040000)
#define SDIO_STATUS_CMD_INDEXERR             ((uint32_t)0x00080000)
#define SDIO_STATUS_DATA_TIMEOUT             ((uint32_t)0x00100000)
#define SDIO_STATUS_CRCERR                   ((uint32_t)0x00200000)
#define SDIO_STATUS_CRCBITERR                ((uint32_t)0x00400000)
#define SDIO_STATUS_LIMITERR                 ((uint32_t)0x00800000)
#define SDIO_STATUS_AUTOCMDERR               ((uint32_t)0x01000000)
#define SDIO_STATUS_ADMAERR                  ((uint32_t)0x02000000)
#define SDIO_STATUS_RESERR                   ((uint32_t)0x04000000)
#define SDIO_STATUS_ALL                      ((uint32_t)0x07FF41FF)
#define IS_SDIO_STATUSMASK(__MASK__)         ((((__MASK__) & SDIO_STATUS_ALL) != 0)  && \
                                              (((__MASK__) & ~SDIO_STATUS_ALL) == 0))
																				 
#define SDIO_FLAG_CMDSENT                        ((uint32_t)0x00000001) 
#define SDIO_FLAG_TRANComplete                   ((uint32_t)0x00000002)
#define SDIO_FLAG_DMA                            ((uint32_t)0x00000008)
#define SDIO_FLAG_WriterBuffer                   ((uint32_t)0x00000010)
#define SDIO_FLAG_ReadBuffer                     ((uint32_t)0x00000020)
#define SDIO_FLAG_InsertCard                     ((uint32_t)0x00000040)
#define SDIO_FLAG_ERR                            ((uint32_t)0x00008000)
#define SDIO_FLAG_CMDTIMEOUT                     ((uint32_t)0x00010000)
#define SDIO_FLAG_CMDCRCERR                      ((uint32_t)0x00020000)
#define SDIO_FLAG_CMDENDBITERR                   ((uint32_t)0x00040000)
#define SDIO_FLAG_CMDIndexERR                    ((uint32_t)0x00080000)
#define SDIO_FLAG_ResponseERR                    ((uint32_t)0x04000000)
#define SDIO_FLAG_ALL                            ((uint32_t)0x07FF41F8)

#define SDIO_INTEN_CMDSENT                        ((uint32_t)0x00000001) 
#define SDIO_INTEN_TRANComplete                   ((uint32_t)0x00000002)
#define SDIO_INTEN_BlockGap                       ((uint32_t)0x00000004)
#define SDIO_INTEN_DMA                            ((uint32_t)0x00000008)
#define SDIO_INTEN_WriterBuffer                   ((uint32_t)0x00000010)
#define SDIO_INTEN_ReadBuffer                     ((uint32_t)0x00000020)
#define SDIO_INTEN_InsertCard                     ((uint32_t)0x00000040)
#define SDIO_FINTEN_ERR                            ((uint32_t)0x00008000)
#define SDIO_INTEN_CMDTIMEOUT                     ((uint32_t)0x00010000)
#define SDIO_INTEN_CMDCRCERR                      ((uint32_t)0x00020000)
#define SDIO_INTEN_CMDENDBITERR                   ((uint32_t)0x00040000)
#define SDIO_INTEN_CMDIndexERR                    ((uint32_t)0x00080000)
#define SDIO_INTEN_ResponseERR                    ((uint32_t)0x04000000)
#define SDIO_INTEN_ALL                            ((uint32_t)0x07FF41F8)
/**
  * @}
  */
  
/* Exported Functions -----RemoveCard -------------------------------------------------- */
void SDIO_DeInit(SDIO_TypeDef *SDIOx);
void SDIO_SWReset(SDIO_TypeDef *SDIOx);
void SDIO_Init(SDIO_TypeDef *SDIOx, SDIO_InitType* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitType* SDIO_InitStruct);
void SDIO_SelectDevice(SDIO_TypeDef *SDIOx, uint8_t Device);
STD_StatusType SDIO_SendCommand(SDIO_TypeDef *SDIOx, SDIO_CMDInitType *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CMDInitType* SDIO_CmdInitStruct);
uint8_t SDIO_GetCommandResponse(SDIO_TypeDef *SDIOx);
uint32_t SDIO_GetResponse(SDIO_TypeDef *SDIOx, uint32_t SDIO_RESP);
uint32_t SDIO_ReadData(SDIO_TypeDef *SDIOx);
void SDIO_VDD1Cmd(SDIO_TypeDef *SDIOx, FunctionalState NewState);
void SDIO_SetVDD1Voltage(SDIO_TypeDef *SDIOx, uint16_t Volatage);
void SDIO_VDD2Cmd(SDIO_TypeDef *SDIOx, FunctionalState NewState);
void SDIO_SetVDD2Voltage(SDIO_TypeDef *SDIOx, uint16_t Volatage);
void SDIO_ClockCmd(SDIO_TypeDef *SDIOx, FunctionalState NewState);
void SDIO_CRCCheckCmd(SDIO_TypeDef *SDIOx, FunctionalState NewState);

void SDIO_ITConfig(SDIO_TypeDef *SDIOx, uint32_t SDIO_IT, FunctionalState NewState);
void SDIO_StatusConfig(SDIO_TypeDef *SDIOx, uint32_t SDIO_Status, FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(SDIO_TypeDef *SDIOx, uint32_t SDIO_FLAG);
ITStatus SDIO_GetITStatus(SDIO_TypeDef *SDIOx, uint32_t SDIO_IT);
void SDIO_ClearITStatus(SDIO_TypeDef *SDIOx, uint32_t SDIO_IT);
#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_SDIO_H */

/**
  * @}
  */
  
/**
  * @}
  */

/*********************************** END OF FILE ******************************/
