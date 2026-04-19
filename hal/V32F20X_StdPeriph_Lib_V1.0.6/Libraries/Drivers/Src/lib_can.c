/**
  ******************************************************************************
  * @file    lib_can.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-03-05
  * @brief   This file provides all the CAN firmware functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "lib_can.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup CAN
  * @brief CAN driver modules
  * @{
  */

/** @defgroup CAN_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup CAN_Private_Defines
  * @{
  */
#define CAN_FF_MSK                   ((uint8_t)0x80)
#define CAN_RTR_MSK                  ((uint8_t)0x40)
#define CAN_DLC_MSK                  ((uint8_t)0x0F)

#define CAN_CDR_CLOCKOFF             ((uint8_t)0x08)

#define CAN_RMC_MSK                  ((uint8_t)0x1F)

#define CAN_ECC_ERROR_CODE_MSK       ((uint8_t)0xC0)
#define CAN_ECC_DIRECTION_MSK        ((uint8_t)0x20)
#define CAN_ECC_SEGMENT_MSK          ((uint8_t)0x1F)

#define CAN_ALC_MSK                  ((uint8_t)0x1F)
#define CAN_MOD_AFM                  ((uint8_t)0x08)

#define CAN_CMR_TR                   ((uint8_t)0x01)
#define CAN_CMR_AT                   ((uint8_t)0x02)
#define CAN_CMR_RRB                  ((uint8_t)0x04)
#define CAN_CMR_CDO                  ((uint8_t)0x08)
#define CAN_CMR_SRR                  ((uint8_t)0x10)

#define CAN_TIMEOUT                  ((uint32_t)0xFFFF)
/**
  * @}
  */

/** @defgroup CAN_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the CAN peripheral registers to their default reset values.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_DeInit(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  if (CANx == CAN0)
  {
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_CAN0);
  }
  else
  {
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_CAN1);
  }
}

/**
  * @brief  Fills each CAN_InitStruct member with its default value.
  * @param  CAN_InitStruct: pointer to an CAN_InitStruct structure which will be initialized.
  * @retval None
  */
void CAN_StructInit(CAN_InitType* CAN_InitStruct)
{
  CAN_InitStruct->CAN_Mode      = CAN_MODE_RESET;
  CAN_InitStruct->CAN_Prescaler = 0;
  CAN_InitStruct->CAN_SJW       = CAN_SJW_1TQ;
  CAN_InitStruct->CAN_TSEG1     = CAN_TSEG1_1TQ;
  CAN_InitStruct->CAN_TSEG2     = CAN_TSEG2_1TQ;
  CAN_InitStruct->CAN_SAM       = CAN_SAMPLING_1;
  CAN_InitStruct->CAN_OCR       = CAN_OCRMODE_NORMAL;
  CAN_InitStruct->CAN_EWLR      = 96;
}

/**
  * @brief  CAN initialization.
  * @param  CANx: where x can be 0, 1: select the CAN peripheral.
  * @param  CAN_InitStruct: pointer to a CAN_InitTypeDef structure that contains 
  *                         the configuration information for the CAN peripheral.
  * @retval None
  */
void CAN_Init(CAN_Type* CANx, CAN_InitType* CAN_InitStruct)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
  assert_parameters(IS_CAN_MODE(CAN_InitStruct->CAN_Mode));
  assert_parameters(IS_CAN_PRESCALER(CAN_InitStruct->CAN_Prescaler));
  assert_parameters(IS_CAN_SJW(CAN_InitStruct->CAN_SJW));
  assert_parameters(IS_CAN_TSEG1(CAN_InitStruct->CAN_TSEG1));
  assert_parameters(IS_CAN_TSEG2(CAN_InitStruct->CAN_TSEG2));
  assert_parameters(IS_CAN_SAM(CAN_InitStruct->CAN_SAM));
  assert_parameters(IS_CAN_OCRMODE(CAN_InitStruct->CAN_OCR));
  assert_parameters(IS_CAN_EWL(CAN_InitStruct->CAN_EWLR));

  /* enter reset mode */
  CANx->MOD = CAN_MODE_RESET;

  CANx->BTR0 = (CAN_InitStruct->CAN_SJW | \
                (CAN_InitStruct->CAN_Prescaler - 1));

  CANx->BTR1 = (CAN_InitStruct->CAN_SAM | \
                CAN_InitStruct->CAN_TSEG2 | \
                CAN_InitStruct->CAN_TSEG1 );

  CANx->OCR = CAN_InitStruct->CAN_OCR;
  CANx->EWLR = CAN_InitStruct->CAN_EWLR;
  
  CANx->MOD = CAN_InitStruct->CAN_Mode;
}

/**
  * @brief  Fills each CAN_FilterInitStruct member with its default value.
  * @param  CAN_FilterInitStruct: pointer to an CAN_FilterInitStruct structure which will be initialized.
  * @retval None
  */
void CAN_FilterStructInit(CAN_FilterInitType* CAN_FilterInitStruct)
{
  CAN_FilterInitStruct->CAN_FilterIDMode      = CAN_FILTER_ID_MODE_STD;
  CAN_FilterInitStruct->CAN_FilterAcceptMode  = CAN_FILTER_ACCEPT_MODE_DUAL;
  CAN_FilterInitStruct->CAN_FilterRTR         = CAN_FILTER_RTR_DATA;
  CAN_FilterInitStruct->CAN_FilterRTRMsk      = 1;
  CAN_FilterInitStruct->CAN_FilterStdID[0]    = 0xFFFF;
  CAN_FilterInitStruct->CAN_FilterStdID[1]    = 0xFFFF;
  CAN_FilterInitStruct->CAN_FilterStdIDMsk[0] = 0xFFFF;
  CAN_FilterInitStruct->CAN_FilterStdIDMsk[1] = 0xFFFF;
  CAN_FilterInitStruct->CAN_FilterData[0]     = 0xFF;
  CAN_FilterInitStruct->CAN_FilterData[1]     = 0xFF;
  CAN_FilterInitStruct->CAN_FilterDataMsk[0]  = 0xFF;
  CAN_FilterInitStruct->CAN_FilterDataMsk[1]  = 0xFF;
  CAN_FilterInitStruct->CAN_FilterExtID[0]    = 0xFFFFFFFF;
  CAN_FilterInitStruct->CAN_FilterExtID[1]    = 0xFFFFFFFF;
  CAN_FilterInitStruct->CAN_FilterExtIDMsk[0] = 0xFFFFFFFF;
  CAN_FilterInitStruct->CAN_FilterExtIDMsk[1] = 0xFFFFFFFF;
}

/**
  * @brief  CAN Filter initialization.
  * @param  CANx: where x can be 0, 1: select the CAN peripheral.
  * @param  CAN_FilterInitStruct: pointer to a CAN_FilterInitTypeDef structure
  *                               that contains the configuration information.
  * @retval None
  */
void CAN_FilterInit(CAN_Type* CANx, CAN_FilterInitType* CAN_FilterInitStruct)
{
  uint8_t tmp = 0;
  uint8_t acr[4],amr[4];

  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
  assert_parameters(IS_CAN_FILTER_ACCEPT_MODE(CAN_FilterInitStruct->CAN_FilterAcceptMode));
  assert_parameters(IS_CAN_FILTERIDMODE(CAN_FilterInitStruct->CAN_FilterIDMode));
  assert_parameters(IS_CAN_FILTERRTRMODE(CAN_FilterInitStruct->CAN_FilterRTR));
  assert_parameters(IS_CAN_FILTERRTRMODE(CAN_FilterInitStruct->CAN_FilterRTRMsk));

  /*CAN_FilterMode */
  tmp = CANx->MOD;
  tmp &= ~CAN_MOD_AFM;
  tmp |= CAN_FilterInitStruct->CAN_FilterAcceptMode;

  /*enter reset mode */
  CANx->MOD = CAN_MODE_RESET;

  /*Standard Frame Format  */
  if(CAN_FilterInitStruct->CAN_FilterIDMode == CAN_FILTER_ID_MODE_STD)
  {
    /*Single Filter */
    if(CAN_FilterInitStruct->CAN_FilterAcceptMode == CAN_FILTER_ACCEPT_MODE_SINGLE)
    {
      acr[0] = (CAN_FilterInitStruct->CAN_FilterStdID[0]>>3) & 0xFF;
      acr[1] = (((CAN_FilterInitStruct->CAN_FilterStdID[0]<<5) & 0xE0) \
             |  ((CAN_FilterInitStruct->CAN_FilterRTR<<4) & 0x10));
      amr[0] = (CAN_FilterInitStruct->CAN_FilterStdIDMsk[0]>>3) & 0xFF;
      amr[1] = (((CAN_FilterInitStruct->CAN_FilterStdIDMsk[0]<<5) & 0xE0) \
             |  ((CAN_FilterInitStruct->CAN_FilterRTRMsk<<4) & 0x10));
      acr[2] =  CAN_FilterInitStruct->CAN_FilterData[0];
      acr[3] =  CAN_FilterInitStruct->CAN_FilterData[1];
      amr[2] =  CAN_FilterInitStruct->CAN_FilterDataMsk[0];
      amr[3] =  CAN_FilterInitStruct->CAN_FilterDataMsk[1];
    }
    /*Dual Filter */
    else
    {
      acr[0] =  (CAN_FilterInitStruct->CAN_FilterStdID[0]>>3) & 0xFF;
      acr[1] = ((CAN_FilterInitStruct->CAN_FilterStdID[0]<<5) & 0xE0) \
             | ((CAN_FilterInitStruct->CAN_FilterRTR<<4) & 0x10) \
             | ((CAN_FilterInitStruct->CAN_FilterData[0] >>4) & 0x0F);
      acr[2] =  (CAN_FilterInitStruct->CAN_FilterStdID[1]>>3) & 0xFF;
      acr[3] = ((CAN_FilterInitStruct->CAN_FilterStdID[1]<<5) & 0xE0) \
             | ((CAN_FilterInitStruct->CAN_FilterRTR<<4) & 0x10) \
             | ((CAN_FilterInitStruct->CAN_FilterData[0]) & 0x0F);
      amr[0] =  (CAN_FilterInitStruct->CAN_FilterStdIDMsk[0]>>3) & 0xFF;
      amr[1] = ((CAN_FilterInitStruct->CAN_FilterStdIDMsk[0]<<5) & 0xE0) \
             | ((CAN_FilterInitStruct->CAN_FilterRTRMsk<<4) & 0x10) \
             | ((CAN_FilterInitStruct->CAN_FilterDataMsk[0] >>4) & 0x0F);
      amr[2] =  (CAN_FilterInitStruct->CAN_FilterStdIDMsk[1]>>3) & 0xFF;
      amr[3] = ((CAN_FilterInitStruct->CAN_FilterStdIDMsk[1]<<5) & 0xE0) \
             | ((CAN_FilterInitStruct->CAN_FilterRTRMsk<<4) & 0x10) \
             | ((CAN_FilterInitStruct->CAN_FilterDataMsk[0]) & 0x0F);
    }
  }
  /* Extended Frame Format */
  else 
  {
    /* Single Filter */
    if(CAN_FilterInitStruct->CAN_FilterAcceptMode == CAN_FILTER_ACCEPT_MODE_SINGLE)
    {
      acr[0] = (CAN_FilterInitStruct->CAN_FilterExtID[0]>>21) & 0xFF;
      acr[1] = (CAN_FilterInitStruct->CAN_FilterExtID[0]>>13) & 0xFF;
      acr[2] = (CAN_FilterInitStruct->CAN_FilterExtID[0]>>5) & 0xFF;
      acr[3] = ((CAN_FilterInitStruct->CAN_FilterExtID[0]<<3) & 0xF8)  \
             | ((CAN_FilterInitStruct->CAN_FilterRTR<<2) & 0x04);
      amr[0] = (CAN_FilterInitStruct->CAN_FilterExtIDMsk[0]>>21) & 0xFF;
      amr[1] = (CAN_FilterInitStruct->CAN_FilterExtIDMsk[0]>>13) & 0xFF;
      amr[2] = (CAN_FilterInitStruct->CAN_FilterExtIDMsk[0]>>5) & 0xFF;
      amr[3] = ((CAN_FilterInitStruct->CAN_FilterExtIDMsk[0]<<3) & 0xF8) \
             | ((CAN_FilterInitStruct->CAN_FilterRTRMsk<<2) & 0x04);
    }
    /*Dual Filter */
    else
    {
      acr[0] = (CAN_FilterInitStruct->CAN_FilterExtID[0]>>21) & 0xFF;
      acr[1] = (CAN_FilterInitStruct->CAN_FilterExtID[0]>>13) & 0xFF;
      acr[2] = (CAN_FilterInitStruct->CAN_FilterExtID[1]>>21) & 0xFF;
      acr[3] = (CAN_FilterInitStruct->CAN_FilterExtID[1]>>13) & 0xFF;
      amr[0] = (CAN_FilterInitStruct->CAN_FilterExtIDMsk[0]>>21) & 0xFF;
      amr[1] = (CAN_FilterInitStruct->CAN_FilterExtIDMsk[0]>>13) & 0xFF;
      amr[2] = (CAN_FilterInitStruct->CAN_FilterExtIDMsk[1]>>21) & 0xFF;
      amr[3] = (CAN_FilterInitStruct->CAN_FilterExtIDMsk[1]>>13) & 0xFF;
    }

  }

  /* FilterID */
  CANx->ACCEPT.ACR[0] = acr[0];
  CANx->ACCEPT.ACR[1] = acr[1];
  CANx->ACCEPT.ACR[2] = acr[2];
  CANx->ACCEPT.ACR[3] = acr[3];

  /* FilterIDMsk */
  CANx->ACCEPT.AMR[0] = amr[0];
  CANx->ACCEPT.AMR[1] = amr[1];
  CANx->ACCEPT.AMR[2] = amr[2];
  CANx->ACCEPT.AMR[3] = amr[3];

  CANx->MOD = tmp;
}

/**
  * @brief  CAN Self Receive Request.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_SelfReceiveRequest(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  CANx->CMR = CAN_CMR_SRR;
}

/**
  * @brief  CAN Clear Data Overrun.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_ClearDataOverrun(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  CANx->CMR = CAN_CMR_CDO;
}

/**
  * @brief  CAN Release Receive Buffer.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_ReleaseReceiveBuffer(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  CANx->CMR = CAN_CMR_RRB;
}

/**
  * @brief  CAN Abort Transmission.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_AbortTransmission(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  CANx->CMR = CAN_CMR_AT;
}

/**
  * @brief  CAN Transmission Request.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_TransmissionRequest(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  CANx->CMR = CAN_CMR_TR;
}

/**
  * @brief  Initiates and transmits a CAN frame message.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @param  TxMessage: pointer to a structure which contains CAN Id, CAN DLC and CAN data.
  * @retval None.
  */
uint8_t CAN_Transmit(CAN_Type* CANx, CanTxMsg* TxMessage)
{
  uint8_t tmp = 0,fifo_addr = 0,i = 0;
  uint32_t j = 0;
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
  assert_parameters(IS_CAN_IDTYPE(TxMessage->ID_Type));
  assert_parameters(IS_CAN_RTR(TxMessage->RTR));
  assert_parameters(IS_CAN_DLC(TxMessage->DLC));

  /* Is the Transmit Buffer free */
  while(((CANx->SR & CAN_SR_TBS) == 0) && (j <= CAN_TIMEOUT))
  {
    j++;
  }
  if(j >= CAN_TIMEOUT)
  {
    return 2;
  }

  /* Write data to Transmit Buffer */
  /*TX Frame */
  tmp = TxMessage->ID_Type | TxMessage->RTR | TxMessage->DLC;
  CANx->TXBUF[0] = tmp;

  /*TX Identifier */
  if(TxMessage->ID_Type == CAN_ID_STANDARD)
  {
    tmp = (TxMessage->StdId >> 3) & 0xFF;
    CANx->TXBUF[1] = tmp;
    tmp = ((TxMessage->StdId << 5) & 0xFF) | (TxMessage->RTR >> 2);
    CANx->TXBUF[2] = tmp;
    fifo_addr = 3;
  }
  /*CAN_ID_EXTENDED */
  else
  {
    tmp = (TxMessage->ExtId >> 21) & 0xFF;
    CANx->TXBUF[1] = tmp;
    tmp = (TxMessage->ExtId >> 13) & 0xFF;
    CANx->TXBUF[2] = tmp;
    tmp = (TxMessage->ExtId >> 5) & 0xFF;
    CANx->TXBUF[3] = tmp;
    tmp = ((TxMessage->ExtId << 3) & 0xFF) | (TxMessage->RTR >> 4);
    CANx->TXBUF[4] = tmp;
    fifo_addr = 5;
  }
  /*TX Data */
  tmp = TxMessage->DLC;
  if(TxMessage->DLC > 8)
  {
    tmp = 8;
  }
  for(i=0; i<tmp; i++)
  {
    CANx->TXBUF[fifo_addr + i] = TxMessage->Data[i];
  }

  /* Transmit Request, Start Transmit */
  if((CANx->MOD & CAN_MODE_SELFTEST) == CAN_MODE_SELFTEST)
  {
    CANx->CMR = CAN_CMR_SRR;
  }
  else
  {
    CANx->CMR = CAN_CMR_TR;
  }

  return 0;
}

/**
  * @brief  Gets CAN FIFO Data.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @param  TxMessage: pointer to a structure which contains CAN Id,ID_Type,RTR,DLC and CAN data.
  * @retval None.
  */
void CAN_GetTransmitFIFOData(CAN_Type* CANx, CanTxMsg* TxMessage)
{
  uint8_t tmp = 0,id[4],fifo_addr = 0,i = 0;
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  tmp = CANx->TXFIFO[0];
  TxMessage->ID_Type = tmp & CAN_FF_MSK;
  TxMessage->RTR = tmp & CAN_RTR_MSK;
  TxMessage->DLC = tmp & CAN_DLC_MSK;

  if((TxMessage->ID_Type & CAN_FF_MSK) == CAN_ID_STANDARD)
  {
    id[0] = CANx->TXFIFO[1];
    id[1] = CANx->TXFIFO[2];
    TxMessage->StdId = ((uint16_t)id[0] << 3) | ((uint16_t)id[1] >> 5);
    fifo_addr = 3;
  }
  else
  {
    id[0] = CANx->TXFIFO[1];
    id[1] = CANx->TXFIFO[2];
    id[2] = CANx->TXFIFO[3];
    id[3] = CANx->TXFIFO[4];
    TxMessage->ExtId = ((uint32_t)id[0] << 21) | ((uint32_t)id[1] << 13) \
                     | ((uint32_t)id[2] << 5 ) | ((uint32_t)id[3] >> 3);
    fifo_addr = 5;
  }
  
  tmp = TxMessage->DLC;
  if(TxMessage->DLC > 8)
  {
    tmp = 8;
  }
  
  for(i=0; i<tmp; i++)
  {
    TxMessage->Data[i] = CANx->TXFIFO[fifo_addr + i];
  }
}

/**
  * @brief  Receives a correct CAN frame.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @param  RxMessage: pointer to a structure receive frame which contains CAN Id,
  *         CAN DLC, CAN data 
  * @retval None
  */
void CAN_Receive(CAN_Type* CANx, CanRxMsg* RxMessage)
{
  uint8_t tmp,id[4],fifo_addr,i;
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  tmp = CANx->RXBUF[0];
  RxMessage->ID_Type = tmp & CAN_FF_MSK;
  RxMessage->RTR = tmp & CAN_RTR_MSK;
  RxMessage->DLC = tmp & CAN_DLC_MSK;

  if((RxMessage->ID_Type & CAN_FF_MSK) == CAN_ID_STANDARD)
  {
    id[0] = CANx->RXBUF[1];
    id[1] = CANx->RXBUF[2];
    RxMessage->StdId = ((uint16_t)id[0] << 3) | ((uint16_t)id[1] >> 5);
    fifo_addr = 3;
  }
  else
  {
    id[0] = CANx->RXBUF[1];
    id[1] = CANx->RXBUF[2];
    id[2] = CANx->RXBUF[3];
    id[3] = CANx->RXBUF[4];
    RxMessage->ExtId = ((uint32_t)id[0] << 21) | ((uint32_t)id[1] << 13) \
                     | ((uint32_t)id[2] << 5 ) | ((uint32_t)id[3] >> 3);
    fifo_addr = 5;
  }
  
  tmp = RxMessage->DLC;
  if(RxMessage->DLC > 8)
  {
    tmp = 8;
  }
 
  for(i = 0; i < tmp; i++)
  {
    RxMessage->Data[i] = CANx->RXBUF[fifo_addr + i];
  }
}

/**
  * @brief  Receives a correct CAN frame.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @param  RxMessage: pointer to a structure receive frame which contains CAN Id,
  *         CAN DLC, CAN data 
  * @retval None
  */
void CAN_ReceiveFIFO(CAN_Type* CANx, CanRxMsg* RxMessage)
{
  uint8_t tmp,id[4],fifo_addr,i;
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  fifo_addr = CAN_GetReceiveBufferStartAddress(CANx);

  tmp = CANx->RXFIFO[fifo_addr%64];
  RxMessage->ID_Type = tmp & CAN_FF_MSK;
  RxMessage->RTR = tmp & CAN_RTR_MSK;
  RxMessage->DLC = tmp & CAN_DLC_MSK;

  if((RxMessage->ID_Type & CAN_FF_MSK) == CAN_ID_STANDARD)
  {
      id[0] = CANx->RXFIFO[(fifo_addr + 1)%64];
      id[1] = CANx->RXFIFO[(fifo_addr + 2)%64];
      RxMessage->StdId = ((uint16_t)id[0] << 3) | ((uint16_t)id[1] >> 5);
      fifo_addr += 3;
  }
  else
  {
    id[0] = CANx->RXFIFO[(fifo_addr + 1)%64];
    id[1] = CANx->RXFIFO[(fifo_addr + 2)%64];
    id[2] = CANx->RXFIFO[(fifo_addr + 3)%64];
    id[3] = CANx->RXFIFO[(fifo_addr + 4)%64];
    RxMessage->ExtId = ((uint32_t)id[0] << 21) | ((uint32_t)id[1] << 13) \
                     | ((uint32_t)id[2] << 5 ) | ((uint32_t)id[3] >> 3);
    fifo_addr += 5;
  }
  
  tmp = RxMessage->DLC;
  if(RxMessage->DLC > 8)
  {
    tmp = 8;
  }

  for(i=0; i<tmp; i++)
  {
    RxMessage->Data[i] = CANx->RXFIFO[(fifo_addr + i)%64];
  }
}

/**
  * @brief  Returns the CANx's Receive Buffer Start Address(RBSA).
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval Receive Buffer Start Address.
  */
uint8_t CAN_GetReceiveBufferStartAddress(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  return CANx->RBSA;
}

/**
  * @brief  Sets the CANx's Receive Buffer Start Address(RBSA).
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_SetReceiveBufferStartAddress(CAN_Type* CANx, uint8_t Addr)
{
  uint8_t tmp =0;

  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
  assert_parameters(IS_CAN_START_ADDR(Addr));

  tmp = CANx->MOD;
  if(tmp & CAN_MODE_RESET)
  {
    CANx->RBSA = Addr;
  }
  else
  {
    CANx->MOD |= CAN_MODE_RESET;
    CANx->RBSA = Addr;
    CANx->MOD &= ~CAN_MODE_RESET;
  }
}

/**
  * @brief  Enables or disables CAN Clock out.
  * @param  CANx: where x can be 0, 1: select the CAN peripheral.
  * @param  NewState: This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void CAN_ClockOutCmd(CAN_Type* CANx, uint8_t NewState)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    CANx->CDR |= CAN_CDR_CLOCKOFF;
  }
  else
  {
    CANx->CDR &= ~CAN_CDR_CLOCKOFF;
  }
}

/**
  * @brief  Configures CAN Clock out divider.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @param  ClockDiv: Select the clock out divider
  *   This parameter can be one of the following values:
  *     @arg CAN_CLOCKOUT_DIV2: 2 frequency division
  *     @arg CAN_CLOCKOUT_DIV4: 4 frequency division 
  *     @arg CAN_CLOCKOUT_DIV6: 6 frequency division
  *     @arg CAN_CLOCKOUT_DIV8: 8 frequency division
  *     @arg CAN_CLOCKOUT_DIV10: 10 frequency division
  *     @arg CAN_CLOCKOUT_DIV12: 12 frequency division
  *     @arg CAN_CLOCKOUT_DIV14: 14 frequency division
  *     @arg CAN_CLOCKOUT_DIV1: 1 frequency division
  * @retval None.
  */
void CAN_ClockOutDivider(CAN_Type* CANx, uint8_t ClockDiv)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
  assert_parameters(IS_CAN_CLOCKOUTDIV(ClockDiv));

  CANx->CDR |= ClockDiv;
}

/**
  * @brief  Gets the number of pending received messages.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval rmc : receive message counter.
  */
uint8_t CAN_MessagePending(CAN_Type* CANx)
{
  uint8_t rmc;
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  rmc = CANx->RMC;
  rmc &= CAN_RMC_MSK;
  
  return rmc;
}

/**
  * @brief  Gets CANx's Arbitration Lost Capture Bit (ALC).
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval CAN Arbitration Lost Capture Bit.
*/
uint8_t CAN_GetArbitrationLostCaptureBit(CAN_Type* CANx)
{
  uint8_t alc = 0;

  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  alc = (CANx->ALC & CAN_ALC_MSK);

  return alc;
}


/**
  * @brief  Returns the CANx's Error Code Capture(ECC).
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval Error code Capture
  *          - EC: Error Code. Bit[7:6]
  *                0: Bit error
  *                1: Form error
  *                2: Stuff error
  *                3: Some other type of error
  *          - DIR: Direction. Bit5
  *                1: during reception
  *                0: during transmission
  *          - SC: Segment Code. Bit[4:0]
  */
uint8_t CAN_GetErrorCodeCapture(CAN_Type* CANx, CAN_EccType *CAN_EccStruct)
{
  uint8_t tmp = 0;

  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  tmp = CANx->ECC;
  CAN_EccStruct->ErrorCode   = (tmp & CAN_ECC_ERROR_CODE_MSK) >> 6;
  CAN_EccStruct->Direction   = (tmp & CAN_ECC_DIRECTION_MSK) >> 5;
  CAN_EccStruct->SegmentCode = (tmp & CAN_ECC_SEGMENT_MSK) >> 0;

  return CANx->ECC;
}

/**
  * @brief  Returns the CANx's Receive Error Counter(RXERR).
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval Receive Error Counter
  */
uint8_t CAN_GetReceiveErrorCounter(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  return CANx->RXERR;
}

/**
  * @brief  Returns the CANx's Transmit Error Counter(TXERR).
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @retval Transmit Error Counter
  */
uint8_t CAN_GetTransmitErrorCounter(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  return CANx->TXERR;
}
/**
  * @brief  CAN enter sleep mode.
  * @param  CANx: where x can be 0, 1: select the CAN peripheral.
  * @retval None
  */
void CAN_Sleep(CAN_Type* CANx)
{
  /* Check parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
	
	if (CANx == CAN0)
  {
    SYSCFG0_CANCtrlCmd(SYSCFG0_CAN0_WAKE, ENABLE);
  }
  else
  {
    SYSCFG0_CANCtrlCmd(SYSCFG0_CAN1_WAKE, ENABLE);
  }
  CANx->MOD |= CAN_MODE_SLEEP;
}

/**
  * @brief  CAN exit sleep mode.
  * @param  CANx: where x can be 0, 1: select the CAN peripheral.
  * @retval None
  */
void CAN_WakeUp(CAN_Type* CANx)
{
  /* Check parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  CANx->MOD &= ~CAN_MODE_SLEEP;
	if (CANx == CAN0)
  {
    SYSCFG0_CANCtrlCmd(SYSCFG0_CAN0_WAKE, DISABLE);
  }
  else
  {
    SYSCFG0_CANCtrlCmd(SYSCFG0_CAN1_WAKE, DISABLE);
  }
}

/**
  * @brief  Checks whether the specified CAN flag is set or not.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @param  CAN_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
*     @arg CAN_FLAG_RBS: Receive buffer status
*     @arg CAN_FLAG_DOS: Data overun status
*     @arg CAN_FLAG_TBS: Tranmission buffer status
*     @arg CAN_FLAG_TCS: Tranmission complete status
*     @arg CAN_FLAG_RS: Receive status
*     @arg CAN_FLAG_TS: Tranmission status
*     @arg CAN_FLAG_ES: Errors status
*     @arg CAN_FLAG_BS: Bus status
  * @retval The new state of CAN_FLAG (SET or RESET).
  */
FlagStatus CAN_GetFlagStatus(CAN_Type* CANx, uint8_t CAN_FLAG)
{

  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
  assert_parameters(IS_CAN_FLAG(CAN_FLAG));

  if(CANx->SR & CAN_FLAG)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Checks whether the specified CAN flag is set or not.
  * @param  CANx: where x can be 0 or 1 to select the CAN peripheral.
  * @param  CAN_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg CAN_INT_RI: Receive Interrupt.
  *     @arg CAN_INT_TI: Transmit Interrupt
  *     @arg CAN_INT_EI: Error Warning Interrupt
  *     @arg CAN_INT_DOI: Data Overrun Interrupt
  *     @arg CAN_INT_WUI: Wake-Up Interrupt
  *     @arg CAN_INT_EPI: Error Passive Interrupt
  *     @arg CAN_INT_ALI: Arbitration Lost Interrupt
  *     @arg CAN_INT_BEI: Bus Error Interrupt
  * @attention reading the IR automatically clears all the interrupts int the register with 
  *         the exception of Receive Interrupt
  * @retval The new state of CAN_INT_STATUS.
  */
INTStatus CAN_GetINTStatus(CAN_Type* CANx, uint8_t CAN_INT)
{
  /* Check the parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));

  if(CANx->IR & CAN_INT)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Enables or disables CAN specified interrupt.
  * @param  CANx: where x can be 0, 1: select the CAN peripheral.
  * @param  INTMask: specifies the CAN interrupt source to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg CAN_INT_RI: Receive Interrupt.
  *     @arg CAN_INT_TI: Transmit Interrupt
  *     @arg CAN_INT_EI: Error Warning Interrupt
  *     @arg CAN_INT_DOI: Data Overrun Interrupt
  *     @arg CAN_INT_WUI: Wake-Up Interrupt
  *     @arg CAN_INT_EPI: Error Passive Interrupt
  *     @arg CAN_INT_ALI: Arbitration Lost Interrupt
  *     @arg CAN_INT_BEI: Bus Error Interrupt
  * @param  NewState: new state of the CAN interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CAN_INTConfig(CAN_Type* CANx, uint8_t CAN_INT, uint8_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_CAN_ALL_PERIPH(CANx));
  assert_parameters(IS_CAN_INTMSK(CAN_INT));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    CANx->IER |= CAN_INT;
  }
  else
  {
    CANx->IER &= ~CAN_INT;
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/*********************************** END OF FILE ******************************/
