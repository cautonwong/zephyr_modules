/**
  ******************************************************************************
  * @file    lib_rng.h 
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-27
  * @brief   RNG library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_RNG_H
#define __LIB_RNG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/** 
  * @brief    RNG Status
  * @{
  */ 
#define RNG_STATUS_MASK                   (0xF << 0)
#define RNG_ERR_MASK                      (7 << 1)
#define RNG_VN_ERR                        (1 << 3)
#define RNG_CRNGT_ERR                     (1 << 2)
#define RNG_AUTOCORR_ERR                  (1 << 1)
#define RNG_EHR_VALID                     (1 << 0)

#define IS_RNG_STATUS(S)  (((S&(~(uint32_t)RNG_STATUS_MASK)) == 0) && (S != 0))
#define IS_ONE_RNG_STATUS(S) (((S) == RNG_VN_ERR)\
                              || ((S) == RNG_CRNGT_ERR)\
                              || ((S) == RNG_AUTOCORR_ERR)\
                              || ((S) == RNG_EHR_VALID))
#define IS_RNG_ERR(E)     (((E&(~(uint32_t)RNG_ERR_MASK)) == 0) && (E != 0))

/** 
  * @brief    RNG entopy source control
  * @{
  */ 
#define RNG_RNGEN                         (1 << 0)

/** 
  * @brief  RNG Configuration Structure definition
  */
typedef struct{
	uint32_t RNG_InverterChainSelect;   /*!< Selects the length of inverters in the ring oscillator.*/
	uint32_t RNG_SampleCount;           /*!< Sets the number of clock cycles between two consecutive*/
                                      /*!< ring oscillator samples.                               */
	uint32_t RNG_Bypass;                /*!< Bypass test funtions.                                  */
} RNG_InitType;

/** 
  * @brief    RNG_InverterChainSelect
  * @{
  */ 
#define RNG_INVCHNSEL_MASK           (3 << 0)
#define RNG_INVCHNSEL_SHORTEST       (0 << 0)
#define RNG_INVCHNSEL_SHORT          (1 << 0)
#define RNG_INVCHNSEL_LONG           (2 << 0)
#define RNG_INVCHNSEL_LONGEST        (3 << 0)

#define IS_RNG_INVERTER_CHAIN_SELECT(S) (((S) == RNG_INVCHNSEL_SHORTEST)\
                                         || ((S) == RNG_INVCHNSEL_SHORT)\
                                         || ((S) == RNG_INVCHNSEL_LONG)\
                                         || ((S) == RNG_INVCHNSEL_LONGEST))

/** 
  * @brief    RNG_Bypass
  * @{
  */ 
#define RNG_BYPASS_MASK              (7 << 1)
#define RNG_BYPASS_NONE              (0 << 1)
#define RNG_BYPASS_AUTOCORR_ERR      (1 << 3)
#define RNG_BYPASS_CRNGT_ERR         (1 << 2)
#define RNG_BYPASS_VN_ERR            (1 << 1)
#define IS_RNG_BYPASS(B) ((B&(~(uint32_t)RNG_BYPASS_MASK)) == 0)

#define IS_RNG_READ_DATA_LEN(L) ((L > 0) && (L <= 24))

/* Exported Functions ------------------------------------------------------- */
void RNG_DeInit(void);
void RNG_StructInit(RNG_InitType *RNG_InitStruct);
void RNG_Init(RNG_InitType *RNG_InitStruct);
void RNG_INTConfig(uint32_t INTMask, uint32_t NewState);
ITStatus RNG_GetINTStatus(uint32_t INTMask);
void RNG_ClearINTStatus(uint32_t INTMask);
void RNG_Cmd(uint32_t NewState);
void RNG_ReadData(uint8_t *buff, uint32_t len);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_RNG_H */

/*********************************** END OF FILE ******************************/
