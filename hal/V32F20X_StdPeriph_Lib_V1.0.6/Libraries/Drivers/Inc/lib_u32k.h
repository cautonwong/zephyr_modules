/**
  ******************************************************************************
  * @file    lib_U32K.h 
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-27
  * @brief   U32K library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_U32K_H
#define __LIB_U32K_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */
  
/** @addtogroup U32K
  * @{
  */
  
/** @defgroup U32K Struct
  * @{
  */

typedef enum
{
  U32K0 = 0,
  U32K1,
} U32K_Type;


/** 
  * @brief U32K Struct 
  */

typedef struct
{
  uint32_t Baudrate;    /* U32K Baudrate value*/
  uint32_t Parity;      /* U32K Parity */
  uint32_t FirstBit;    /* U32K Receive order */
  uint32_t Debounce;    /* U32K De-bounce */
  uint32_t AutoCal;     /* U32K Auto-calibration off */
  uint32_t LineSel;     /* U32K Receive data */
  uint32_t Pcheck;      /* U32K Parity check pass */
  uint32_t WKU_nByte;   /* U32K Enable */
} U32K_InitType;

/**
  * @}
  */

/** @defgroup U32K Selection
  * @{
  */

#define IS_ALL_U32K(__U32KX__)    (((__U32KX__) == U32K0) || ((__U32KX__) == U32K1))

/**
  * @}
  */

/** @defgroup U32K Receive data select
  * @{
  */

#define U32K_USE_RX0                ((uint32_t)0x00000000)  /* Receive data IOB7*/
#define U32K_USE_RX1                ((uint32_t)0x00010000)  /* Receive data IOD14 */
#define U32K_USE_RX2                ((uint32_t)0x00020000)  /* Receive data IOG2 */
#define U32K_USE_RX3                ((uint32_t)0x00030000)  /* Receive data IOG8 */
#define U32K_USE_RX4                ((uint32_t)0x00040000)  /* Receive data IOD2 */
#define U32K_USE_RX5                ((uint32_t)0x00050000)  /* Receive data IOD4 */
#define IS_U32K_LINESEL(__LINE__)  (((__LINE__)==U32K_USE_RX0) || \
                                    ((__LINE__)==U32K_USE_RX1) || \
                                    ((__LINE__)==U32K_USE_RX2) || \
                                    ((__LINE__)==U32K_USE_RX3) || \
                                    ((__LINE__)==U32K_USE_RX4) || \
                                    ((__LINE__)==U32K_USE_RX5))

/**
  * @}
  */

/** @defgroup U32K Parity check pass
  * @{
  */

#define U32K_PARITY_CHECK_GOOD      ((uint32_t)0x00080000)  /* Parity check Pass */
#define U32K_PARITY_CHECK_NOT       ((uint32_t)0x00000000)  /* Parity check Fail */
#define IS_U32K_PARITY_CHECK(__CHECK__)  (((__CHECK__)==U32K_PARITY_CHECK_GOOD) || \
                                          ((__CHECK__)==U32K_PARITY_CHECK_NOT ))

/**
  * @}
  */

/** @defgroup U32K Parity mode control
  * @{
  */

#define U32K_PARITY_EVEN            ((uint32_t)0x00400000)  /* Parity mode EVEN */
#define U32K_PARITY_ODD             ((uint32_t)0x00500000)  /* Parity mode ODD */
#define U32K_PARITY_0               ((uint32_t)0x00600000)  /* Parity mode 0 */
#define U32K_PARITY_1               ((uint32_t)0x00700000)  /* Parity mode 1 */
#define U32K_PARITY_NONE            ((uint32_t)0x00000000)  /* Parity mode NONE */
#define IS_U32K_PARITY(__PARITY__)  (((__PARITY__)==U32K_PARITY_EVEN) || \
                                     ((__PARITY__)==U32K_PARITY_ODD ) || \
                                     ((__PARITY__)==U32K_PARITY_0   ) || \
                                     ((__PARITY__)==U32K_PARITY_1   ) || \
                                     ((__PARITY__)==U32K_PARITY_NONE))

/**
  * @}
  */

/** @defgroup U32K Receive order
  * @{
  */

#define U32K_FIRSTBIT_LSB           ((uint32_t)0x00000000)  /* Receive order LSB */
#define U32K_FIRSTBIT_MSB           ((uint32_t)0x00800000)  /* Receive order MSB */
#define IS_U32K_FIRSTBIT(__FIRST__)  (((__FIRST__)==U32K_FIRSTBIT_LSB) || \
                                      ((__FIRST__)==U32K_FIRSTBIT_MSB))

/**
  * @}
  */

/** @defgroup U32K De-bounce control
  * @{
  */

#define U32K_DEBOUNCE_0             ((uint32_t)0x00000000)  /* De-bounce control 0 */
#define U32K_DEBOUNCE_2             ((uint32_t)0x01000000)  /* De-bounce control 2 */
#define U32K_DEBOUNCE_3             ((uint32_t)0x02000000)  /* De-bounce control 3 */
#define U32K_DEBOUNCE_4             ((uint32_t)0x03000000)  /* De-bounce control 4 */
#define IS_U32K_DEBOUNCE(__DEBOUNCE__)  (((__DEBOUNCE__)==U32K_DEBOUNCE_0) || \
                                         ((__DEBOUNCE__)==U32K_DEBOUNCE_2) || \
                                         ((__DEBOUNCE__)==U32K_DEBOUNCE_3) || \
                                         ((__DEBOUNCE__)==U32K_DEBOUNCE_4))

/**
  * @}
  */

/** @defgroup U32K Auto-calibration off control
  * @{
  */

#define U32K_AUTO_CAL_ON            ((uint32_t)0x00000000)  /* Auto-calibration ON */
#define U32K_AUTO_CAL_OFF           ((uint32_t)0x04000000)  /* Auto-calibration OFF */
#define IS_U32K_AUTO_CAL(__CAL__)  (((__CAL__)==U32K_AUTO_CAL_ON ) || \
                                    ((__CAL__)==U32K_AUTO_CAL_OFF))

/**
  * @}
  */

/** @defgroup U32K Baud rate divider
  * @{
  */

#define IS_U32K_BAUDRATE(__BAUD__)  ((__BAUD__) <= 0xFFFFUL)  /* Baud rate */

/**
  * @}
  */

/** @defgroup U32K Enable the U32K wakeup to PMU CTRL
  * @{
  */

#define U32K_WKU_INT_ENABLE         ((uint32_t)0x08000000)  /* WKU ENABLE */
#define U32K_WKU_INT_DISABLE        ((uint32_t)0x00000000)  /* WKU DISABLE */

/**
  * @}
  */

/** @defgroup U32K Stop bit
  * @{
  */

#define U32K_PARITY_ERROR           ((uint32_t)0x10000000)  /* Stop bit ERROR */
#define U32K_PARITY_OK              ((uint32_t)0x00000000)  /* Stop bit OK */

/**
  * @}
  */

/** @defgroup U32K Interrupt status Write 1 to clear
  * @{
  */

#define U32K_WKU_INT_STS            ((uint32_t)0x40000000)  /* Interrupt status */

/**
  * @}
  */

/** @defgroup U32K Enable register
  * @{
  */

#define U32K_ENABLE                 ((uint32_t)0x80000000)  /* Enable register */

/**
  * @}
  */

/* Exported Functions ------------------------------------------------------- */
void U32K_DeInit(U32K_Type U32Kx);
void U32K_InitStruct_Init(U32K_InitType *U32K_InitStruct);
void U32K_Init(U32K_Type U32Kx, U32K_InitType *U32K_InitStruct);

void U32K_Cmd(U32K_Type U32Kx, uint32_t NewState);

void U32K_WKU_INT_Config(U32K_Type U32Kx, uint32_t NewState);
ITStatus U32K_GetINTStatus(U32K_Type U32Kx);
void U32K_ClearINTStatus(U32K_Type U32Kx);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __LIB_U32K_H */

/*********************************** END OF FILE ******************************/
