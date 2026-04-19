/**
  ******************************************************************************
  * @file    lib_hfm.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   HFM library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_HFM_H
#define __LIB_HFM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

typedef struct
{
  uint16_t Mode;
  uint16_t SampleLength;
  uint16_t CICRateSEL;
  uint16_t COMPSEL;
  uint16_t UploadSEL;
  uint16_t UploadEndianSEL;
  uint16_t BackupSEL;
} WAVER_InitType;

typedef struct
{
  uint32_t Mode;
  uint32_t ExchAddr;
  uint32_t WaveBaseAddr;
  uint32_t DSPInstrAddr;
  uint32_t DSPExchAddr;
} HFM_InitType;

typedef struct
{
  uint8_t Channel;
  uint8_t HARMNum;
  uint8_t AddSource;
  uint8_t AddEGYMode;
  uint8_t AddTypeSel;
  uint8_t AddPWRMode;
  uint8_t PowerThresholdSEL;
} EGY_InitType;

typedef struct
{
  uint8_t CF_Source;
  uint8_t CF_Polarity;
  uint8_t CF_PulsePeriod;
  uint8_t CF_Fast;
  uint16_t CF_Division;
  uint32_t ConstValue;
} CF_InitType;


#define EGY0                       ((uint8_t)0)
#define EGY1                       ((uint8_t)1)
#define EGY2                       ((uint8_t)2)
#define CF0                        ((uint8_t)0)
#define CF1                        ((uint8_t)1)
#define CF2                        ((uint8_t)2)
#define IS_EGY(__EGY__)            (((__EGY__) == EGY0)    ||\
                                    ((__EGY__) == EGY1)    ||\
                                    ((__EGY__) == EGY2))
//WAVER0
//Mode
#define WAVER_MODE_U_IA             ((uint16_t)0x0000)
#define WAVER_MODE_U_IA_IB          ((uint16_t)0x0001)
#define WAVER_MODE_3U_IA_IB_IC      ((uint16_t)0x0002)
#define IS_WAVER_MODE(__MODE__)     (((__MODE__) == WAVER_MODE_U_IA)         ||\
                                     ((__MODE__) == WAVER_MODE_U_IA_IB)      ||\
                                     ((__MODE__) == WAVER_MODE_3U_IA_IB_IC))
//SampleLength
#define WAVER_SAMPLELEN_256         ((uint16_t)0)
#define WAVER_SAMPLELEN_128         ((uint16_t)1)
#define IS_WAVER_SAMPLELEN(__SAMPLELEN__)     (((__SAMPLELEN__) == WAVER_SAMPLELEN_256)  ||\
                                               ((__SAMPLELEN__) == WAVER_SAMPLELEN_128))
//CICRateSEL
#define WAVER_CIC_DISABLE           ((uint16_t)0x0000)
#define WAVER_CIC_128               ((uint16_t)0x0004)
#define WAVER_CIC_64                ((uint16_t)0x0006)
#define IS_WAVER_CIC(__CIC__)     (((__CIC__) == WAVER_CIC_DISABLE)  ||\
                                   ((__CIC__) == WAVER_CIC_128)      ||\
                                   ((__CIC__) == WAVER_CIC_64))
//COMPSEL
#define WAVER_COMP_DISABLE          ((uint16_t)0x0000)
#define WAVER_COMP_ENABLE           ((uint16_t)0x0001)
#define IS_WAVER_COMP(__COMP__)     (((__COMP__) == WAVER_COMP_DISABLE)  ||\
                                     ((__COMP__) == WAVER_COMP_ENABLE))
//UploadSEL
#define WAVER_UPLOAD_DISABLE        ((uint16_t)0x0000)
#define WAVER_UPLOAD_SPI            ((uint16_t)0x0008)
#define WAVER_UPLOAD_M33            ((uint16_t)0x0010)
#define WAVER_UPLOAD_SPI_M33        ((uint16_t)0x0018)
#define IS_WAVER_UPLOAD(__UPLOAD__)     (((__UPLOAD__) == WAVER_UPLOAD_DISABLE)  ||\
                                         ((__UPLOAD__) == WAVER_UPLOAD_SPI)      ||\
                                         ((__UPLOAD__) == WAVER_UPLOAD_M33)      ||\
                                         ((__UPLOAD__) == WAVER_UPLOAD_SPI_M33))
//UploadEndianSEL
#define WAVER_UPLOAD_LITTLE_ENDIAN  ((uint16_t)0x0000)
#define WAVER_UPLOAD_BIG_ENDIAN     ((uint16_t)0x0100)
#define IS_WAVER_UPLOADENDIAN(__UPLOADENDIAN__)     (((__UPLOADENDIAN__) == WAVER_UPLOAD_LITTLE_ENDIAN)  ||\
                                                     ((__UPLOADENDIAN__) == WAVER_UPLOAD_BIG_ENDIAN))
//BackupSEL
#define WAVER_BACKUP_DISABLE        ((uint16_t)0x0000)
#define WAVER_BACKUP_ENABLE         ((uint16_t)0x0080)
#define IS_WAVER_BACKUP(__BACKUP__)     (((__BACKUP__) == WAVER_BACKUP_DISABLE)  ||\
                                         ((__BACKUP__) == WAVER_BACKUP_ENABLE))

//HFM
//Mode
#define HFM_MODE_U_IA             ((uint16_t)0x0000)
#define HFM_MODE_U_IA_IB          ((uint16_t)0x0001)
#define HFM_MODE_3U_IA_IB_IC      ((uint16_t)0x0002)
#define IS_HFM_MODE(__MODE__)     (((__MODE__) == HFM_MODE_U_IA)         ||\
                                   ((__MODE__) == HFM_MODE_U_IA_IB)      ||\
                                   ((__MODE__) == HFM_MODE_3U_IA_IB_IC))
/*
// INTMask @ HFM_INTConfig
//         @ HFM_GetINTStatus
//         @ HFM_ClearINTStatus
*/
#define HFM_INT_T2FDONE                  (1UL << 0)
#define HFM_INT_DSPDONE                  (1UL << 1)
#define HFM_INT_EGY0SPILL                (1UL << 2)
#define HFM_INT_EGY1SPILL                (1UL << 3)
#define HFM_INT_EGY2SPILL                (1UL << 4)
#define HFM_INT_MASK                     (0x1FUL)
#define IS_HFM_INTR(__INT__)             (((__INT__) == HFM_INT_T2FDONE)      ||\
                                          ((__INT__) == HFM_INT_DSPDONE)      ||\
                                          ((__INT__) == HFM_INT_EGY0SPILL)    ||\
                                          ((__INT__) == HFM_INT_EGY1SPILL)    ||\
                                          ((__INT__) == HFM_INT_EGY2SPILL))
#define IS_HFM_INTC(__INT__)             ((((__INT__) & HFM_INT_MASK) != 0UL) &&\
                                          (((__INT__) & ~HFM_INT_MASK) == 0UL))
/*
// FlagMask @ HFM_GetFlagStatus
*/
#define HFM_FLAG_T2FDONE                  (1UL << 0)
#define HFM_FLAG_DSPDONE                  (1UL << 1)
#define IS_HFM_FLAG(__FLAG__)             (((__FLAG__) == HFM_FLAG_T2FDONE)    ||\
                                           ((__FLAG__) == HFM_FLAG_DSPDONE))
//EGY
//Channel
#define EGY_CHANNEL_A                      ((uint8_t)0x01)
#define EGY_CHANNEL_B                      ((uint8_t)0x02)
#define EGY_CHANNEL_C                      ((uint8_t)0x04)
#define EGY_CHANNEL_MASK                   ((uint8_t)0x07)
#define IS_EGY_CHANNEL(__CHANNEL__)        ((((__CHANNEL__) & EGY_CHANNEL_MASK) != 0)     && \
                                            (((__CHANNEL__) & (~EGY_CHANNEL_MASK)) == 0))
//HARMNum
#define IS_EGY_CF_HARM_NUM(__HARMNUM__)     (((__HARMNUM__) >= 0)  && ((__HARMNUM__) <= 20))
//CF_Division
#define IS_EGY_CF_DIV(__DIV__)              (((__DIV__) >= 0)  && ((__DIV__) <= 0xFFFF))
//CF_Source
#define CF_SOURCE_EGY0                      ((uint8_t)0x00)
#define CF_SOURCE_EGY1                      ((uint8_t)0x01)
#define CF_SOURCE_EGY2                      ((uint8_t)0x02)
#define CF_SOURCE_0                         ((uint8_t)0x03)
#define IS_EGY_CF_SOURCE(__SOURCE__)        (((__SOURCE__) == CF_SOURCE_EGY0)    ||\
                                             ((__SOURCE__) == CF_SOURCE_EGY1)    ||\
                                             ((__SOURCE__) == CF_SOURCE_EGY2)    ||\
                                             ((__SOURCE__) == CF_SOURCE_0))
//CF_Polarity
#define CF_ORGINAL                         ((uint8_t)0x00)
#define CF_OPPOSITE                        ((uint8_t)0x01)
#define IS_EGY_CF_POLARITY(__POLARITY__)   (((__POLARITY__) == CF_ORGINAL)    ||\
                                            ((__POLARITY__) == CF_OPPOSITE))
//CF_PulsePeriod
#define CF_PERIOD_80MS                      ((uint8_t)0x00)
#define CF_PERIOD_40MS                      ((uint8_t)0x01)
#define CF_PERIOD_20MS                      ((uint8_t)0x02)
#define CF_PERIOD_10MS                      ((uint8_t)0x03)
#define IS_EGY_CF_PERIOD(__PERIOD__)        (((__PERIOD__) == CF_PERIOD_80MS)    ||\
                                             ((__PERIOD__) == CF_PERIOD_40MS)    ||\
                                             ((__PERIOD__) == CF_PERIOD_20MS)    ||\
                                             ((__PERIOD__) == CF_PERIOD_10MS))
//CF_Fast
#define CF_FAST_X1                          ((uint8_t)0x00)
#define CF_FAST_X4                          ((uint8_t)0x01)
#define CF_FAST_X8                          ((uint8_t)0x02)
#define CF_FAST_X16                         ((uint8_t)0x03)
#define IS_EGY_CF_FAST(__FAST__)            (((__FAST__) == CF_FAST_X1)    ||\
                                             ((__FAST__) == CF_FAST_X4)    ||\
                                             ((__FAST__) == CF_FAST_X8)    ||\
                                             ((__FAST__) == CF_FAST_X16))
//AddSource
#define EGY_ACCSOURCE_POWER                 ((uint8_t)0x00)
#define EGY_ACCSOURCE_CURRENT               ((uint8_t)0x01)
#define EGY_ACCSOURCE_CONSTANT              ((uint8_t)0x02)
#define IS_EGY_ACCSOURCE(__ACCSOURCE__)     (((__ACCSOURCE__) == EGY_ACCSOURCE_POWER)      ||\
                                             ((__ACCSOURCE__) == EGY_ACCSOURCE_CURRENT)    ||\
                                             ((__ACCSOURCE__) == EGY_ACCSOURCE_CONSTANT))
//AddEGYMode
#define EGY_ACCEGYMODE_ORIGINAL             ((uint8_t)0x00)
#define EGY_ACCEGYMODE_ABSOLUTE             ((uint8_t)0x01)
#define IS_EGY_ACCEGYMODE(__ACCEGYMODE__)   (((__ACCEGYMODE__) == EGY_ACCEGYMODE_ORIGINAL)      ||\
                                             ((__ACCEGYMODE__) == EGY_ACCEGYMODE_ABSOLUTE))
//AddTypeSel
#define EGY_ACCTYPE_ACTIVEPOWER             ((uint8_t)0x00)
#define EGY_ACCTYPE_REACTIVEPOWER           ((uint8_t)0x01)
#define IS_EGY_ACCPOWRERSOURCE(__ACCTYPE__) (((__ACCTYPE__) == EGY_ACCTYPE_ACTIVEPOWER)      ||\
                                             ((__ACCTYPE__) == EGY_ACCTYPE_REACTIVEPOWER))
#define EGY_ACCTYPE_CURRETN_ABC             ((uint8_t)0x00)
#define EGY_ACCTYPE_CURRETN_A_BC            ((uint8_t)0x01)
#define IS_EGY_ACCCURRENTTYPE(__ACCTYPE__)  (((__ACCTYPE__) == EGY_ACCTYPE_CURRETN_ABC)      ||\
                                             ((__ACCTYPE__) == EGY_ACCTYPE_CURRETN_A_BC))
//AddPWRMode
#define EGY_ACCPOWERTYPE_POSITIVE           ((uint8_t)0x00)
#define EGY_ACCPOWERTYPE_NEGATIVE           ((uint8_t)0x01)
#define EGY_ACCPOWERTYPE_ORGINAL            ((uint8_t)0x02)
#define EGY_ACCPOWERTYPE_ABSOLUTE           ((uint8_t)0x03)
#define IS_EGY_ACCPOWRERTYPE(__ACCTYPE__)   (((__ACCTYPE__) == EGY_ACCPOWERTYPE_POSITIVE)      ||\
                                             ((__ACCTYPE__) == EGY_ACCPOWERTYPE_NEGATIVE)      ||\
                                             ((__ACCTYPE__) == EGY_ACCPOWERTYPE_ORGINAL)       ||\
                                             ((__ACCTYPE__) == EGY_ACCPOWERTYPE_ABSOLUTE))
//PowerThresholdSEL
#define EGY_POWRTHRESHOLD_PWRTH0            ((uint8_t)0x00)
#define EGY_POWRTHRESHOLD_PWRTH1            ((uint8_t)0x01)
#define IS_POWRTHRESHOLD_PWRTH(__PWRTH__)   (((__PWRTH__) == EGY_POWRTHRESHOLD_PWRTH0)      ||\
                                             ((__PWRTH__) == EGY_POWRTHRESHOLD_PWRTH1))
//PWRCRP thresholds
#define IS_EGY_PWRCRP_THRESHOLD(THRESHOLD)   ((THRESHOLD) <= 0xFFFFFFFF)
//PWR thresholds
#define IS_EGY_PWR_THRESHOLD(THRESHOLD)      ((THRESHOLD) <= 0xFFFFFFFF)
//EGY Clear
#define EGY_MASK_CFCNT2                  (1 << 6)
#define EGY_MASK_CFCNT1                  (1 << 5)
#define EGY_MASK_CFCNT0                  (1 << 4)
#define EGY_MASK_EGYOUT2                 (1 << 2)
#define EGY_MASK_EGYOUT1                 (1 << 1)
#define EGY_MASK_EGYOUT0                 (1 << 0)
#define EGY_CLEAR_MASK                   (0x77)
#define IS_EGY_CLEARC(__CLEAR__)         ((((__CLEAR__) & EGY_CLEAR_MASK) != 0UL) &&\
                                          (((__CLEAR__) & ~EGY_CLEAR_MASK) == 0UL))

/* Exported Functions ------------------------------------------------------- */
/* WAVER Functions ------------------------------------------------------- */
void WAVER_DeInit(void);
void WAVER_StructInit(WAVER_InitType *WAVER_InitStruct);
void WAVER_Init(WAVER_InitType *WAVER_InitStruct);
void WAVER_Cmd(uint32_t NewState);

/* HFM Functions ------------------------------------------------------- */
void HFM_DeInit(void);
void HFM_StructInit(HFM_InitType *HFM_InitStruct);
void HFM_Init(HFM_InitType *HFM_InitStruct);
void HFM_INTConfig(uint32_t INTMask, uint32_t NewState);
ITStatus HFM_GetINTStatus(uint32_t INTMask);
void HFM_ClearINTStatus(uint32_t INTMask);
FlagStatus HFM_GetFlag(uint32_t FlagMask);

void HFM_T2F_StartManual(void);
void HFM_DSP_StartManual(void);
void HFM_T2F_WaitForManual(void);
void HFM_DSP_WaitForManual(void);

/* EGY Functions ------------------------------------------------------- */
void EGY_StructInit(EGY_InitType *EGY_InitStruct);
void EGY_Init(uint8_t EGY, EGY_InitType *EGY_InitStruct);
void CF_StructInit(CF_InitType *CF_InitStruct);
void CF_Init(uint8_t EGY, CF_InitType *CF_InitStruct);
void EGY_PWRCRP_Cmd(FunctionalState NewState);
void EGY_CRP_Cmd(FunctionalState NewState);
void EGY_Cmd(uint8_t EGY, FunctionalState NewState);
void EGY_PWRCRPThresholdConfig(uint32_t HighThreshold, uint32_t LowThreshold);
void EGY_PWR0ThresholdConfig(uint32_t Threshold);
void EGY_PWR1ThresholdConfig(uint32_t Threshold);
void EGY_PRCThresholdConfig(uint32_t Threshold);
void EGY_Clear(uint8_t Mask);
void CF_Cmd(uint8_t CF, FunctionalState NewState);

#ifdef __cplusplus
}
#endif
     
#endif  /* __HFM_H */

/*********************************** END OF FILE ******************************/
