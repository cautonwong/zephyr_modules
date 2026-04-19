/**
  ******************************************************************************
  * @file    lib_can.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-03-05
  * @brief   This file contains all the functions prototypes for the CAN
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_CAN_H
#define __LIB_CAN_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @addtogroup CAN
  * @{
  */

/** @defgroup CAN_Exported_Constants
  * @{
  */

#define IS_CAN_ALL_PERIPH(PERIPH)     (((PERIPH) == CAN0) || \
                                       ((PERIPH) == CAN1))

/** @defgroup CAN_mode 
  * @{
  */
#define CAN_MODE_NORMAL                ((uint8_t)0x00)  /*!< normal mode */
#define CAN_MODE_RESET                 ((uint8_t)0x01)  /*!< Reset mode */
#define CAN_MODE_LISTENONLY            ((uint8_t)0x02)  /*!< ListenOnly mode */
#define CAN_MODE_SELFTEST              ((uint8_t)0x04)  /*!< SelfTest Loopback mode */
#define CAN_MODE_SLEEP                 ((uint8_t)0x10)  /*!< Sleep mode */
#define IS_CAN_MODE(MODE)              (((MODE) == CAN_MODE_NORMAL)     || \
                                        ((MODE) == CAN_MODE_LISTENONLY) || \
                                        ((MODE) == CAN_MODE_SELFTEST))
/**
  * @}
  */

/** @defgroup CAN_prescaler 
  * @{
  */
#define IS_CAN_PRESCALER(PRESCALER)    (((PRESCALER) >= 1)&&((PRESCALER) <= 64))
/**
  * @}
  */

/** @defgroup CAN_sjw
  * @{
  */
#define CAN_SJW_1TQ                    ((uint8_t)0x00<<6)  /*!< 1 time quantum */
#define CAN_SJW_2TQ                    ((uint8_t)0x01<<6)  /*!< 2 time quantum */
#define CAN_SJW_3TQ                    ((uint8_t)0x02<<6)  /*!< 3 time quantum */
#define CAN_SJW_4TQ                    ((uint8_t)0x03<<6)  /*!< 4 time quantum */
#define IS_CAN_SJW(SJW)                (((SJW) == CAN_SJW_1TQ) || ((SJW) == CAN_SJW_2TQ)|| \
                                        ((SJW) == CAN_SJW_3TQ) || ((SJW) == CAN_SJW_4TQ))
/**
  * @}
  */

/** @defgroup CAN_tseg1
  * @{
  */
#define CAN_TSEG1_1TQ                 ((uint8_t)0x00)  /*!< 1 time quantum */
#define CAN_TSEG1_2TQ                 ((uint8_t)0x01)  /*!< 2 time quantum */
#define CAN_TSEG1_3TQ                 ((uint8_t)0x02)  /*!< 3 time quantum */
#define CAN_TSEG1_4TQ                 ((uint8_t)0x03)  /*!< 4 time quantum */
#define CAN_TSEG1_5TQ                 ((uint8_t)0x04)  /*!< 5 time quantum */
#define CAN_TSEG1_6TQ                 ((uint8_t)0x05)  /*!< 6 time quantum */
#define CAN_TSEG1_7TQ                 ((uint8_t)0x06)  /*!< 7 time quantum */
#define CAN_TSEG1_8TQ                 ((uint8_t)0x07)  /*!< 8 time quantum */
#define CAN_TSEG1_9TQ                 ((uint8_t)0x08)  /*!< 9 time quantum */
#define CAN_TSEG1_10TQ                ((uint8_t)0x09)  /*!< 10 time quantum */
#define CAN_TSEG1_11TQ                ((uint8_t)0x0A)  /*!< 11 time quantum */
#define CAN_TSEG1_12TQ                ((uint8_t)0x0B)  /*!< 12 time quantum */
#define CAN_TSEG1_13TQ                ((uint8_t)0x0C)  /*!< 13 time quantum */
#define CAN_TSEG1_14TQ                ((uint8_t)0x0D)  /*!< 14 time quantum */
#define CAN_TSEG1_15TQ                ((uint8_t)0x0E)  /*!< 15 time quantum */
#define CAN_TSEG1_16TQ                ((uint8_t)0x0F)  /*!< 16 time quantum */
#define IS_CAN_TSEG1(TSEG1)           ((TSEG1) <= CAN_TSEG1_16TQ)
/**
  * @}
  */

/** @defgroup CAN_tseg2
  * @{
  */
#define CAN_TSEG2_1TQ                 ((uint8_t)0x00<<4)  /*!< 1 time quantum */
#define CAN_TSEG2_2TQ                 ((uint8_t)0x01<<4)  /*!< 2 time quantum */
#define CAN_TSEG2_3TQ                 ((uint8_t)0x02<<4)  /*!< 3 time quantum */
#define CAN_TSEG2_4TQ                 ((uint8_t)0x03<<4)  /*!< 4 time quantum */
#define CAN_TSEG2_5TQ                 ((uint8_t)0x04<<4)  /*!< 5 time quantum */
#define CAN_TSEG2_6TQ                 ((uint8_t)0x05<<4)  /*!< 6 time quantum */
#define CAN_TSEG2_7TQ                 ((uint8_t)0x06<<4)  /*!< 7 time quantum */
#define CAN_TSEG2_8TQ                 ((uint8_t)0x07<<4)  /*!< 8 time quantum */
#define IS_CAN_TSEG2(TSEG2)           (((TSEG2) == CAN_TSEG2_1TQ) || ((TSEG2) == CAN_TSEG2_2TQ) || \
                                       ((TSEG2) == CAN_TSEG2_3TQ) || ((TSEG2) == CAN_TSEG2_4TQ) || \
                                       ((TSEG2) == CAN_TSEG2_5TQ) || ((TSEG2) == CAN_TSEG2_6TQ) || \
                                       ((TSEG2) == CAN_TSEG2_7TQ) || ((TSEG2) == CAN_TSEG2_8TQ))
/**
  * @}
  */

/** @defgroup CAN_sampling
  * @{
  */
#define CAN_SAMPLING_3                ((uint8_t)0x80)
#define CAN_SAMPLING_1                ((uint8_t)0x00)
#define IS_CAN_SAM(SAMPLE)            (((SAMPLE) == CAN_SAMPLING_3) || \
                                       ((SAMPLE) == CAN_SAMPLING_1))
/**
  * @}
  */

/** @defgroup CAN_ocr_mode 
  * @{
  */
#define CAN_OCRMODE_RESERVED          ((uint8_t)0x00)
#define CAN_OCRMODE_RESERVED1         ((uint8_t)0x01)
#define CAN_OCRMODE_NORMAL            ((uint8_t)0x02)
#define CAN_OCRMODE_CLOCKOUT          ((uint8_t)0x03)
#define IS_CAN_OCRMODE(MODE)          (((MODE) == CAN_OCRMODE_RESERVED)  || \
                                       ((MODE) == CAN_OCRMODE_RESERVED1) || \
                                       ((MODE) == CAN_OCRMODE_NORMAL)    || \
                                       ((MODE) == CAN_OCRMODE_CLOCKOUT))
/**
  * @}
  */

/** @defgroup CAN_ewl_number 
  * @{
  */
#define IS_CAN_EWL(NUMBER)               (((NUMBER) > 0) && ((NUMBER) <= 127))
/**
  * @}
  */

/** @defgroup CAN_StartAddr 
  * @{
  */
#define IS_CAN_START_ADDR(ADDR)               ((ADDR) <= 0x3FU)
/**
  * @}
  */


/** @defgroup CAN_filter_mode 
  * @{
  */
#define CAN_FILTER_ACCEPT_MODE_SINGLE      ((uint8_t)0x08)  /*!< Single Filter */
#define CAN_FILTER_ACCEPT_MODE_DUAL        ((uint8_t)0x00)  /*!< Dual Filter */
/**
  * @}
  */

/** @defgroup CAN_filter_accept_mode 
  * @{
  */
#define IS_CAN_FILTER_ACCEPT_MODE(MODE)   (((MODE) == CAN_FILTER_ACCEPT_MODE_SINGLE) || \
                                           ((MODE) == CAN_FILTER_ACCEPT_MODE_DUAL))
/**
  * @}
  */

/** @defgroup CAN_filter_id_mode 
  * @{
  */
#define CAN_FILTER_ID_MODE_STD             ((uint8_t)0x00)
#define CAN_FILTER_ID_MODE_EXT             ((uint8_t)0x01)
#define IS_CAN_FILTERIDMODE(MODE)          (((MODE) == CAN_FILTER_ID_MODE_STD) || \
                                            ((MODE) == CAN_FILTER_ID_MODE_EXT))
/**
  * @}
  */

/** @defgroup CAN_filter_ptr 
  * @{
  */
#define CAN_FILTER_RTR_DATA                ((uint8_t)0x00)
#define CAN_FILTER_RTR_REMOTE              ((uint8_t)0x01)
#define IS_CAN_FILTERRTRMODE(MODE)        (((MODE) == CAN_FILTER_RTR_REMOTE) || \
                                           ((MODE) == CAN_FILTER_RTR_DATA))
/**
  * @}
  */

/** @defgroup CAN_ecc_error_code 
  * @{
  */
#define CAN_ECC_BIT_ERR                    ((uint8_t)0x00)
#define CAN_ECC_FORM_ERR                   ((uint8_t)0x01)
#define CAN_ECC_STUFF_ERR                  ((uint8_t)0x02)
#define CAN_ECC_OTHER_ERR                  ((uint8_t)0x03)
/**
  * @}
  */

/** @defgroup CAN_ecc_direction 
  * @{
  */
#define CAN_ECC_DIR_TRANSMISSION           ((uint8_t)0x00)
#define CAN_ECC_DIR_RECEPTION              ((uint8_t)0x01)
/**
  * @}
  */

/** @defgroup CAN_identifier_type 
  * @{
  */
#define CAN_ID_STANDARD                    ((uint8_t)0x00)  /*!< Standard Id */
#define CAN_ID_EXTENDED                    ((uint8_t)0x80)  /*!< Extended Id */
#define IS_CAN_IDTYPE(IDTYPE)              (((IDTYPE) == CAN_ID_STANDARD) || \
                                            ((IDTYPE) == CAN_ID_EXTENDED))
/**
  * @}
  */

/** @defgroup CAN_remote_transmission_request 
  * @{
  */
#define CAN_RTR_DATA                       ((uint8_t)0x00)  /*!< Data frame */
#define CAN_RTR_REMOTE                     ((uint8_t)0x40)  /*!< Remote frame */
#define IS_CAN_RTR(RTR)                    (((RTR) == CAN_RTR_DATA) || \
                                            ((RTR) == CAN_RTR_REMOTE))
/**
  * @}
  */

/** @defgroup CAN_dlc 
  * @{
  */
#define CAN_DLC_0                          ((uint8_t)0x00)
#define CAN_DLC_1                          ((uint8_t)0x01)
#define CAN_DLC_2                          ((uint8_t)0x02)
#define CAN_DLC_3                          ((uint8_t)0x03)
#define CAN_DLC_4                          ((uint8_t)0x04)
#define CAN_DLC_5                          ((uint8_t)0x05)
#define CAN_DLC_6                          ((uint8_t)0x06)
#define CAN_DLC_7                          ((uint8_t)0x07)
#define CAN_DLC_8                          ((uint8_t)0x08)
#define IS_CAN_DLC(DLC)                    ((DLC) <= CAN_DLC_8)
/**
  * @}
  */

/** @defgroup CAN_flag 
  * @{
  */
#define CAN_SR_RBS                         ((uint8_t)0x01)
#define CAN_SR_DOS                         ((uint8_t)0x02)
#define CAN_SR_TBS                         ((uint8_t)0x04)
#define CAN_SR_TCS                         ((uint8_t)0x08)
#define CAN_SR_RS                          ((uint8_t)0x10)
#define CAN_SR_TS                          ((uint8_t)0x20)
#define CAN_SR_ES                          ((uint8_t)0x40)
#define CAN_SR_BS                          ((uint8_t)0x80)
#define IS_CAN_FLAG(FLAG)                  (((FLAG) == CAN_SR_RBS) || \
                                            ((FLAG) == CAN_SR_DOS) || \
                                            ((FLAG) == CAN_SR_TBS) || \
                                            ((FLAG) == CAN_SR_TCS) || \
                                            ((FLAG) == CAN_SR_RS ) || \
                                            ((FLAG) == CAN_SR_TS ) || \
                                            ((FLAG) == CAN_SR_ES ) || \
                                            ((FLAG) == CAN_SR_BS ))
/**
  * @}
  */

/** @defgroup CAN_interrupt_status
  * @{
  */
#define CAN_INT_RI                         ((uint8_t)0x01)
#define CAN_INT_TI                         ((uint8_t)0x02)
#define CAN_INT_EI                         ((uint8_t)0x04)
#define CAN_INT_DOI                        ((uint8_t)0x08)
#define CAN_INT_WUI                        ((uint8_t)0x10)
#define CAN_INT_EPI                        ((uint8_t)0x20)
#define CAN_INT_ALI                        ((uint8_t)0x40)
#define CAN_INT_BEI                        ((uint8_t)0x80)
#define IS_CAN_INTMSK(STATUS)              (((STATUS) == CAN_INT_RI)  || \
                                            ((STATUS) == CAN_INT_TI)  || \
                                            ((STATUS) == CAN_INT_EI)  || \
                                            ((STATUS) == CAN_INT_DOI) || \
                                            ((STATUS) == CAN_INT_WUI) || \
                                            ((STATUS) == CAN_INT_EPI) || \
                                            ((STATUS) == CAN_INT_ALI) || \
                                            ((STATUS) == CAN_INT_BEI))
/**
  * @}
  */

/** @defgroup CAN_clockout_division
  * @{
  */
#define CAN_CLOCKOUT_DIV2                  ((uint8_t)0x00)
#define CAN_CLOCKOUT_DIV4                  ((uint8_t)0x01)
#define CAN_CLOCKOUT_DIV6                  ((uint8_t)0x02)
#define CAN_CLOCKOUT_DIV8                  ((uint8_t)0x03)
#define CAN_CLOCKOUT_DIV10                 ((uint8_t)0x04)
#define CAN_CLOCKOUT_DIV12                 ((uint8_t)0x05)
#define CAN_CLOCKOUT_DIV14                 ((uint8_t)0x06)
#define CAN_CLOCKOUT_DIV1                  ((uint8_t)0x07)
#define IS_CAN_CLOCKOUTDIV(DIV)            ((DIV) <= CAN_CLOCKOUT_DIV1)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CAN_Exported_Types
  * @{
  */

/**
  * @brief  CAN Filter init structure definition
  */
typedef struct
{
  uint8_t  CAN_FilterIDMode;         /*!< Select filter mode */
  uint8_t  CAN_FilterAcceptMode;     /*!< Acceptance filter mode */

  uint8_t  CAN_FilterRTR;           /*!< filter RTR */
  uint8_t  CAN_FilterRTRMsk;        /*!< Filter RTR Msk */

  uint16_t CAN_FilterStdID[2];       /*!< The filter identification number  */
  uint16_t CAN_FilterStdIDMsk[2];    /*!< The filter mask number  */
  uint8_t  CAN_FilterData[2];        /*!< The filter data number  */
  uint8_t  CAN_FilterDataMsk[2];     /*!< The filter data mask number  */

  uint32_t CAN_FilterExtID[2];       /*!< The filter extened identification number  */
  uint32_t CAN_FilterExtIDMsk[2];    /*!< The filter extened mask number  */

} CAN_FilterInitType;


/**
  * @brief  CAN Ecc structure definition
  */
typedef struct
{
  uint8_t ErrorCode;               /*!< Specifies the Error code.*/
  uint8_t Direction;               /*!< Specifies the Direction.*/
  uint8_t SegmentCode;             /*!< Specifies */
}CAN_EccType;

/**
  * @brief  CAN Msg structure definition
  */
typedef struct
{
  union
  {
    uint16_t StdId;        /*!< Specifies the standard identifier.
                                This parameter can be a value between 0 to 0x7FF. */
    uint32_t ExtId;        /*!< Specifies the extended identifier.
                                This parameter can be a value between 0 to 0x1FFFFFFF. */
  };

  uint8_t ID_Type;         /*!< Specifies the type of identifier for the message that 
                                will be received. This parameter can be a value of  */
  uint8_t RTR;             /*!< Specifies the type of frame for the received message.
                                This parameter can be a value of 
                                @ref CAN_remote_transmission_request */
  uint8_t DLC;             /*!< Specifies the length of the frame that will be received.
                                This parameter can be a value between 0 to 8 */
  uint8_t Data[8];         /*!< Contains the data to be received. It ranges from 0 to 0xFF. */
}CanTxMsg,CanRxMsg;

/**
  * @brief  CAN init structure definition
  */
typedef struct
{
  uint8_t CAN_Mode;           /*!< Specifies the CAN operating */
  uint8_t CAN_Prescaler;      /*!< Baud Rate Prescaler. 1~64 */
  uint8_t CAN_SJW;            /*!< Synchronization Jump Width. 0~3 */
  uint8_t CAN_TSEG1;          /*!< The length of the bit period. 0~15 */
  uint8_t CAN_TSEG2;          /*!< The length of the bit period. 0~7 */
  uint8_t CAN_SAM;            /*!< Sampling times. 1time or 3times */
  uint8_t CAN_OCR;            /*!< Output Control Mode. 0~3 */
  uint8_t CAN_EWLR;           /*!< Error Warning Limit. Default:96 */
} CAN_InitType;

/**
  * @}
  */

/** @defgroup CAN_Exported_Functions
  * @{
  */

/* Exported Functions ------------------------------------------------------- */

void CAN_DeInit(CAN_Type* CANx);
void CAN_StructInit(CAN_InitType* CAN_InitStruct);
void CAN_Init(CAN_Type* CANx, CAN_InitType* CAN_InitStruct);

void CAN_FilterStructInit(CAN_FilterInitType* CAN_FilterInitStruct);
void CAN_FilterInit(CAN_Type* CANx, CAN_FilterInitType* CAN_FilterInitStruct);

void CAN_SelfReceiveRequest(CAN_Type* CANx);
void CAN_ClearDataOverrun(CAN_Type* CANx);
void CAN_ReleaseReceiveBuffer(CAN_Type* CANx);
void CAN_AbortTransmission(CAN_Type* CANx);
void CAN_TransmissionRequest(CAN_Type* CANx);

uint8_t CAN_Transmit(CAN_Type* CANx, CanTxMsg* TxMessage);
void CAN_GetTransmitFIFOData(CAN_Type* CANx, CanTxMsg* TxMessage);

void CAN_Receive(CAN_Type* CANx, CanRxMsg* RxMessage);
void CAN_ReceiveFIFO(CAN_Type* CANx, CanRxMsg* RxMessage);
uint8_t CAN_MessagePending(CAN_Type* CANx);

uint8_t CAN_GetReceiveBufferStartAddress(CAN_Type* CANx);
void CAN_SetReceiveBufferStartAddress(CAN_Type* CANx, uint8_t Addr);

void CAN_ClockOutCmd(CAN_Type* CANx, uint8_t NewState);
void CAN_ClockOutDivider(CAN_Type* CANx, uint8_t ClockDiv);

uint8_t CAN_GetArbitrationLostCaptureBit(CAN_Type* CANx);
uint8_t CAN_GetErrorCodeCapture(CAN_Type* CANx, CAN_EccType *CAN_EccStruct);
uint8_t CAN_GetReceiveErrorCounter(CAN_Type* CANx);
uint8_t CAN_GetTransmitErrorCounter(CAN_Type* CANx);

void CAN_Sleep(CAN_Type* CANx);
void CAN_WakeUp(CAN_Type* CANx);

FlagStatus CAN_GetFlagStatus(CAN_Type* CANx, uint8_t CAN_FLAG);
void CAN_INTConfig(CAN_Type* CANx, uint8_t INTMask, uint8_t NewState);
INTStatus CAN_GetINTStatus(CAN_Type* CANx, uint8_t CAN_INT);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif  /* __LIB_CAN_H */

/*********************************** END OF FILE ******************************/

