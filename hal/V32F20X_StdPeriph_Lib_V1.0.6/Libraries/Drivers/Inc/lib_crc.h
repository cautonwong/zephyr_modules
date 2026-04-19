/**
  ******************************************************************************
  * @file    crc.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-04-16
  * @brief   CRC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_CRC_H
#define __LIB_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
#include <stdbool.h>

typedef struct CRC_InitType
{
  uint32_t CRC_Polynomial;          /*!< CRC polynomial. */
  uint32_t CRC_ReverseIn;           /*!< Reverse bits on input. */
  uint32_t CRC_ComplementIn;        /*!< Perform 1's complement on input. */
  uint32_t CRC_ReverseOut;          /*!< Reverse bits on output. */
  uint32_t CRC_ComplementOut;       /*!< Perform 1's complement on output. */
  uint32_t Seed;                    /*!< Starting checksum value. */
} CRC_InitType;

/** 
  * @brief    CRC_Polynomial
  * @{
  */ 
#define CRC_Polynomial_SHIFT                  0
#define CRC_Polynomial_MASK                   (3 << CRC_Polynomial_SHIFT)
#define CRC_Polynomial_CRCCCITT               (0 << CRC_Polynomial_SHIFT)
#define CRC_Polynomial_CRC16                  (1 << CRC_Polynomial_SHIFT)
#define CRC_Polynomial_CRC32                  (2 << CRC_Polynomial_SHIFT)

#define IS_CRC_POLYNOMIAL(P)        (((P) == CRC_Polynomial_CRCCCITT)\
                                    || ((P) == CRC_Polynomial_CRC16)\
                                    || ((P) == CRC_Polynomial_CRC32))

/** 
  * @brief    CRC_ReverseIn
  * @{
  */ 
#define CRC_ReverseIn_SHIFT                   2
#define CRC_ReverseIn_MASK                    (1 << CRC_ReverseIn_SHIFT)
#define CRC_ReverseIn_Disable                 (0 << CRC_ReverseIn_SHIFT)
#define CRC_ReverseIn_Enable                  (1 << CRC_ReverseIn_SHIFT)

#define IS_CRC_REVERSEIN(R)         (((R) == CRC_ReverseIn_Disable)\
                                    || ((R) == CRC_ReverseIn_Enable))

/** 
  * @brief    CRC_ComplementIn
  * @{
  */ 
#define CRC_ComplementIn_SHIFT                3
#define CRC_ComplementIn_MASK                 (1 << CRC_ComplementIn_SHIFT)
#define CRC_ComplementIn_Disable              (0 << CRC_ComplementIn_SHIFT)
#define CRC_ComplementIn_Enable               (1 << CRC_ComplementIn_SHIFT)

#define IS_CRC_COMPLEMENTIN(C)      (((C) == CRC_ComplementIn_Disable)\
                                    || ((C) == CRC_ComplementIn_Enable))

/** 
  * @brief    CRC_ReverseOut
  * @{
  */ 
#define CRC_ReverseOut_SHIFT                  4
#define CRC_ReverseOut_MASK                   (1 << CRC_ReverseOut_SHIFT)
#define CRC_ReverseOut_Disable                (0 << CRC_ReverseOut_SHIFT)
#define CRC_ReverseOut_Enable                 (1 << CRC_ReverseOut_SHIFT)

#define IS_CRC_REVERSEOUT(R)        (((R) == CRC_ReverseOut_Disable)\
                                    || ((R) == CRC_ReverseOut_Enable))

/** 
  * @brief    CRC_ComplementOut
  * @{
  */ 
#define CRC_ComplementOut_SHIFT               5
#define CRC_ComplementOut_MASK                (1 << CRC_ComplementOut_SHIFT)
#define CRC_ComplementOut_Disable             (0 << CRC_ComplementOut_SHIFT)
#define CRC_ComplementOut_Enable              (1 << CRC_ComplementOut_SHIFT)

#define IS_CRC_COMPLEMENTOUT(C)     (((C) == CRC_ComplementOut_Disable)\
                                    || ((C) == CRC_ComplementOut_Enable))

/* Exported Functions ------------------------------------------------------- */

void CRC_DeInit(void);
void CRC_StructInit(CRC_InitType *CRC_InitStruct);
void CRC_Init(CRC_InitType *CRC_InitStruct);
void CRC_WriteData(const uint8_t *Data, uint32_t DataSize);
uint32_t CRC_Get32bitResult(void);
uint16_t CRC_Get16bitResult(void);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_CRC_H */

/*********************************** END OF FILE ******************************/
