/**
  ******************************************************************************
  * @file    lib_dcmi.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   DCMI library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_DCMI_H
#define __LIB_DCMI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/********************  Bits definition for DCMI_CR register  ******************/
#define DCMI_CR_CAPTURE                      ((uint32_t)0x00000001)
#define DCMI_CR_CM                           ((uint32_t)0x00000002)
#define DCMI_CR_CROP                         ((uint32_t)0x00000004)
#define DCMI_CR_JPEG                         ((uint32_t)0x00000008)
#define DCMI_CR_ESS                          ((uint32_t)0x00000010)
#define DCMI_CR_PCKPOL                       ((uint32_t)0x00000020)
#define DCMI_CR_HSPOL                        ((uint32_t)0x00000040)
#define DCMI_CR_VSPOL                        ((uint32_t)0x00000080)
#define DCMI_CR_FCRC_0                       ((uint32_t)0x00000100)
#define DCMI_CR_FCRC_1                       ((uint32_t)0x00000200)
#define DCMI_CR_EDM_0                        ((uint32_t)0x00000400)
#define DCMI_CR_EDM_1                        ((uint32_t)0x00000800)
#define DCMI_CR_CRE                          ((uint32_t)0x00001000)
#define DCMI_CR_ENABLE                       ((uint32_t)0x00004000)

/********************  Bits definition for DCMI_SR register  ******************/
#define DCMI_SR_HSYNC                        ((uint32_t)0x00000001)
#define DCMI_SR_VSYNC                        ((uint32_t)0x00000002)
#define DCMI_SR_FNE                          ((uint32_t)0x00000004)

/********************  Bits definition for DCMI_RIS register  *****************/
#define DCMI_RIS_FRAME_RIS                   ((uint32_t)0x00000001)
#define DCMI_RIS_OVR_RIS                     ((uint32_t)0x00000002)
#define DCMI_RIS_ERR_RIS                     ((uint32_t)0x00000004)
#define DCMI_RIS_VSYNC_RIS                   ((uint32_t)0x00000008)
#define DCMI_RIS_LINE_RIS                     ((uint32_t)0x00000010)
/* Legacy defines */
#define DCMI_RISR_FRAME_RIS                  DCMI_RIS_FRAME_RIS
#define DCMI_RISR_OVR_RIS                    DCMI_RIS_OVR_RIS
#define DCMI_RISR_ERR_RIS                    DCMI_RIS_ERR_RIS
#define DCMI_RISR_VSYNC_RIS                  DCMI_RIS_VSYNC_RIS
#define DCMI_RISR_LINE_RIS                   DCMI_RIS_LINE_RIS
#define DCMI_RISR_OVF_RIS                    DCMI_RIS_OVR_RIS

/********************  Bits definition for DCMI_IER register  *****************/
#define DCMI_IER_FRAME_IE                    ((uint32_t)0x00000001)
#define DCMI_IER_OVR_IE                      ((uint32_t)0x00000002)
#define DCMI_IER_ERR_IE                      ((uint32_t)0x00000004)
#define DCMI_IER_VSYNC_IE                    ((uint32_t)0x00000008)
#define DCMI_IER_LINE_IE                     ((uint32_t)0x00000010)

/* Legacy defines */
#define DCMI_IER_OVF_IE                      DCMI_IER_OVR_IE

/********************  Bits definition for DCMI_MIS register  ****************/
#define DCMI_MIS_FRAME_MIS                   ((uint32_t)0x00000001)
#define DCMI_MIS_OVR_MIS                     ((uint32_t)0x00000002)
#define DCMI_MIS_ERR_MIS                     ((uint32_t)0x00000004)
#define DCMI_MIS_VSYNC_MIS                   ((uint32_t)0x00000008)
#define DCMI_MIS_LINE_MIS                    ((uint32_t)0x00000010)

/* Legacy defines */
#define DCMI_MISR_FRAME_MIS                  DCMI_MIS_FRAME_MIS
#define DCMI_MISR_OVF_MIS                    DCMI_MIS_OVR_MIS
#define DCMI_MISR_ERR_MIS                    DCMI_MIS_ERR_MIS
#define DCMI_MISR_VSYNC_MIS                  DCMI_MIS_VSYNC_MIS
#define DCMI_MISR_LINE_MIS                   DCMI_MIS_LINE_MIS

/********************  Bits definition for DCMI_ICR register  *****************/
#define DCMI_ICR_FRAME_ISC                   ((uint32_t)0x00000001)
#define DCMI_ICR_OVR_ISC                     ((uint32_t)0x00000002)
#define DCMI_ICR_ERR_ISC                     ((uint32_t)0x00000004)
#define DCMI_ICR_VSYNC_ISC                   ((uint32_t)0x00000008)
#define DCMI_ICR_LINE_ISC                    ((uint32_t)0x00000010)

/* Legacy defines */
#define DCMI_ICR_OVF_ISC                     DCMI_ICR_OVR_ISC

/********************  Bits definition for DCMI_ESCR register  ******************/
#define DCMI_ESCR_FSC                        ((uint32_t)0x000000FF)
#define DCMI_ESCR_LSC                        ((uint32_t)0x0000FF00)
#define DCMI_ESCR_LEC                        ((uint32_t)0x00FF0000)
#define DCMI_ESCR_FEC                        ((uint32_t)0xFF000000)

/********************  Bits definition for DCMI_ESUR register  ******************/
#define DCMI_ESUR_FSU                        ((uint32_t)0x000000FF)
#define DCMI_ESUR_LSU                        ((uint32_t)0x0000FF00)
#define DCMI_ESUR_LEU                        ((uint32_t)0x00FF0000)
#define DCMI_ESUR_FEU                        ((uint32_t)0xFF000000)

/********************  Bits definition for DCMI_CWSTRT register  ******************/
#define DCMI_CWSTRT_HOFFCNT                  ((uint32_t)0x00003FFF)
#define DCMI_CWSTRT_VST                      ((uint32_t)0x1FFF0000)

/********************  Bits definition for DCMI_CWSIZE register  ******************/
#define DCMI_CWSIZE_CAPCNT                   ((uint32_t)0x00003FFF)
#define DCMI_CWSIZE_VLINE                    ((uint32_t)0x3FFF0000)

/********************  Bits definition for DCMI_DR register  ******************/
#define DCMI_DR_BYTE0                        ((uint32_t)0x000000FF)
#define DCMI_DR_BYTE1                        ((uint32_t)0x0000FF00)
#define DCMI_DR_BYTE2                        ((uint32_t)0x00FF0000)
#define DCMI_DR_BYTE3                        ((uint32_t)0xFF000000)

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief   DCMI Init structure definition  
  */ 
typedef struct
{
  uint16_t DCMI_CaptureMode;      /*!< Specifies the Capture Mode: Continuous or Snapshot.
                                       This parameter can be a value of @ref DCMI_Capture_Mode */

  uint16_t DCMI_SynchroMode;      /*!< Specifies the Synchronization Mode: Hardware or Embedded.
                                       This parameter can be a value of @ref DCMI_Synchronization_Mode */

  uint16_t DCMI_PCKPolarity;      /*!< Specifies the Pixel clock polarity: Falling or Rising.
                                       This parameter can be a value of @ref DCMI_PIXCK_Polarity */

  uint16_t DCMI_VSPolarity;       /*!< Specifies the Vertical synchronization polarity: High or Low.
                                       This parameter can be a value of @ref DCMI_VSYNC_Polarity */

  uint16_t DCMI_HSPolarity;       /*!< Specifies the Horizontal synchronization polarity: High or Low.
                                       This parameter can be a value of @ref DCMI_HSYNC_Polarity */

  uint16_t DCMI_CaptureRate;      /*!< Specifies the frequency of frame capture: All, 1/2 or 1/4.
                                       This parameter can be a value of @ref DCMI_Capture_Rate */

  uint16_t DCMI_ExtendedDataMode; /*!< Specifies the data width: 8-bit, 10-bit, 12-bit or 14-bit.
                                       This parameter can be a value of @ref DCMI_Extended_Data_Mode */
} DCMI_InitTypeDef;

/** 
  * @brief   DCMI CROP Init structure definition  
  */ 
typedef struct
{
  uint16_t DCMI_VerticalStartLine;      /*!< Specifies the Vertical start line count from which the image capture
                                             will start. This parameter can be a value between 0x00 and 0x1FFF */

  uint16_t DCMI_HorizontalOffsetCount;  /*!< Specifies the number of pixel clocks to count before starting a capture.
                                             This parameter can be a value between 0x00 and 0x3FFF */

  uint16_t DCMI_VerticalLineCount;      /*!< Specifies the number of lines to be captured from the starting point.
                                             This parameter can be a value between 0x00 and 0x3FFF */

  uint16_t DCMI_CaptureCount;           /*!< Specifies the number of pixel clocks to be captured from the starting
                                             point on the same line.
                                             This parameter can be a value between 0x00 and 0x3FFF */
} DCMI_CROPInitTypeDef;

/** 
  * @brief   DCMI Embedded Synchronisation CODE Init structure definition  
  */ 
typedef struct
{
  uint8_t DCMI_FrameStartCode; /*!< Specifies the code of the frame start delimiter. */
  uint8_t DCMI_LineStartCode;  /*!< Specifies the code of the line start delimiter. */
  uint8_t DCMI_LineEndCode;    /*!< Specifies the code of the line end delimiter. */
  uint8_t DCMI_FrameEndCode;   /*!< Specifies the code of the frame end delimiter. */
} DCMI_CodesInitTypeDef;

/** @defgroup DCMI_Capture_Mode 
  * @{
  */ 
#define DCMI_CaptureMode_Continuous    ((uint16_t)0x0000) /*!< The received data are transferred continuously 
                                                               into the destination memory through the DMA */
#define DCMI_CaptureMode_SnapShot      ((uint16_t)0x0002) /*!< Once activated, the interface waits for the start of 
                                                               frame and then transfers a single frame through the DMA */
#define IS_DCMI_CAPTURE_MODE(MODE)(((MODE) == DCMI_CaptureMode_Continuous) || \
                                   ((MODE) == DCMI_CaptureMode_SnapShot))

/** @defgroup DCMI_Synchronization_Mode
  * @{
  */ 
#define DCMI_SynchroMode_Hardware    ((uint16_t)0x0000) /*!< Hardware synchronization data capture (frame/line start/stop)
                                                             is synchronized with the HSYNC/VSYNC signals */
#define DCMI_SynchroMode_Embedded    ((uint16_t)0x0010) /*!< Embedded synchronization data capture is synchronized with 
                                                             synchronization codes embedded in the data flow */
#define IS_DCMI_SYNCHRO(MODE)(((MODE) == DCMI_SynchroMode_Hardware) || \
                              ((MODE) == DCMI_SynchroMode_Embedded))

/** @defgroup DCMI_PIXCK_Polarity 
  * @{
  */ 
#define DCMI_PCKPolarity_Falling    ((uint16_t)0x0000) /*!< Pixel clock active on Falling edge */
#define DCMI_PCKPolarity_Rising     ((uint16_t)0x0020) /*!< Pixel clock active on Rising edge */
#define IS_DCMI_PCKPOLARITY(POLARITY)(((POLARITY) == DCMI_PCKPolarity_Falling) || \
                                      ((POLARITY) == DCMI_PCKPolarity_Rising))

/** @defgroup DCMI_VSYNC_Polarity 
  * @{
  */ 
#define DCMI_VSPolarity_Low     ((uint16_t)0x0000) /*!< Vertical synchronization active Low */
#define DCMI_VSPolarity_High    ((uint16_t)0x0080) /*!< Vertical synchronization active High */
#define IS_DCMI_VSPOLARITY(POLARITY)(((POLARITY) == DCMI_VSPolarity_Low) || \
                                     ((POLARITY) == DCMI_VSPolarity_High))

/** @defgroup DCMI_HSYNC_Polarity 
  * @{
  */ 
#define DCMI_HSPolarity_Low     ((uint16_t)0x0000) /*!< Horizontal synchronization active Low */
#define DCMI_HSPolarity_High    ((uint16_t)0x0040) /*!< Horizontal synchronization active High */
#define IS_DCMI_HSPOLARITY(POLARITY)(((POLARITY) == DCMI_HSPolarity_Low) || \
                                     ((POLARITY) == DCMI_HSPolarity_High))

/** @defgroup DCMI_Capture_Rate 
  * @{
  */ 
#define DCMI_CaptureRate_All_Frame     ((uint16_t)0x0000) /*!< All frames are captured */
#define DCMI_CaptureRate_1of2_Frame    ((uint16_t)0x0100) /*!< Every alternate frame captured */
#define DCMI_CaptureRate_1of4_Frame    ((uint16_t)0x0200) /*!< One frame in 4 frames captured */
#define IS_DCMI_CAPTURE_RATE(RATE) (((RATE) == DCMI_CaptureRate_All_Frame) || \
                                    ((RATE) == DCMI_CaptureRate_1of2_Frame) ||\
                                    ((RATE) == DCMI_CaptureRate_1of4_Frame))

/** @defgroup DCMI_Extended_Data_Mode 
  * @{
  */ 
#define DCMI_ExtendedDataMode_8b     ((uint16_t)0x0000) /*!< Interface captures 8-bit data on every pixel clock */
#define DCMI_ExtendedDataMode_10b    ((uint16_t)0x0400) /*!< Interface captures 10-bit data on every pixel clock */
#define DCMI_ExtendedDataMode_12b    ((uint16_t)0x0800) /*!< Interface captures 12-bit data on every pixel clock */
#define DCMI_ExtendedDataMode_14b    ((uint16_t)0x0C00) /*!< Interface captures 14-bit data on every pixel clock */
#define IS_DCMI_EXTENDED_DATA(DATA)(((DATA) == DCMI_ExtendedDataMode_8b) || \
                                    ((DATA) == DCMI_ExtendedDataMode_10b) ||\
                                    ((DATA) == DCMI_ExtendedDataMode_12b) ||\
                                    ((DATA) == DCMI_ExtendedDataMode_14b))

/** @defgroup DCMI_interrupt_sources 
  * @{
  */ 
#define DCMI_IT_FRAME    ((uint16_t)0x0001)
#define DCMI_IT_OVF      ((uint16_t)0x0002)
#define DCMI_IT_ERR      ((uint16_t)0x0004)
#define DCMI_IT_VSYNC    ((uint16_t)0x0008)
#define DCMI_IT_LINE     ((uint16_t)0x0010)
#define IS_DCMI_CONFIG_IT(IT) ((((IT) & (uint16_t)0xFFE0) == 0x0000) && ((IT) != 0x0000))
#define IS_DCMI_GET_IT(IT) (((IT) == DCMI_IT_FRAME) || \
                            ((IT) == DCMI_IT_OVF) || \
                            ((IT) == DCMI_IT_ERR) || \
                            ((IT) == DCMI_IT_VSYNC) || \
                            ((IT) == DCMI_IT_LINE))

/** @defgroup DCMI_Flags 
  * @{
  */ 
/** 
  * @brief   DCMI SR register  
  */ 
#define DCMI_FLAG_HSYNC     ((uint16_t)0x2001)
#define DCMI_FLAG_VSYNC     ((uint16_t)0x2002)
#define DCMI_FLAG_FNE       ((uint16_t)0x2004)
/** 
  * @brief   DCMI RISR register  
  */ 
#define DCMI_FLAG_FRAMERI    ((uint16_t)0x0001)
#define DCMI_FLAG_OVFRI      ((uint16_t)0x0002)
#define DCMI_FLAG_ERRRI      ((uint16_t)0x0004)
#define DCMI_FLAG_VSYNCRI    ((uint16_t)0x0008)
#define DCMI_FLAG_LINERI     ((uint16_t)0x0010)
/** 
  * @brief   DCMI MISR register  
  */ 
#define DCMI_FLAG_FRAMEMI    ((uint16_t)0x1001)
#define DCMI_FLAG_OVFMI      ((uint16_t)0x1002)
#define DCMI_FLAG_ERRMI      ((uint16_t)0x1004)
#define DCMI_FLAG_VSYNCMI    ((uint16_t)0x1008)
#define DCMI_FLAG_LINEMI     ((uint16_t)0x1010)
#define IS_DCMI_GET_FLAG(FLAG) (((FLAG) == DCMI_FLAG_HSYNC) || \
                                ((FLAG) == DCMI_FLAG_VSYNC) || \
                                ((FLAG) == DCMI_FLAG_FNE) || \
                                ((FLAG) == DCMI_FLAG_FRAMERI) || \
                                ((FLAG) == DCMI_FLAG_OVFRI) || \
                                ((FLAG) == DCMI_FLAG_ERRRI) || \
                                ((FLAG) == DCMI_FLAG_VSYNCRI) || \
                                ((FLAG) == DCMI_FLAG_LINERI) || \
                                ((FLAG) == DCMI_FLAG_FRAMEMI) || \
                                ((FLAG) == DCMI_FLAG_OVFMI) || \
                                ((FLAG) == DCMI_FLAG_ERRMI) || \
                                ((FLAG) == DCMI_FLAG_VSYNCMI) || \
                                ((FLAG) == DCMI_FLAG_LINEMI))
                                
#define IS_DCMI_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFFE0) == 0x0000) && ((FLAG) != 0x0000))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the DCMI configuration to the default reset state ****/ 
void DCMI_DeInit(void);

/* Initialization and Configuration functions *********************************/
void DCMI_Init(DCMI_InitTypeDef* DCMI_InitStruct);
void DCMI_StructInit(DCMI_InitTypeDef* DCMI_InitStruct);
void DCMI_CROPConfig(DCMI_CROPInitTypeDef* DCMI_CROPInitStruct);
void DCMI_CROPCmd(FunctionalState NewState);
void DCMI_SetEmbeddedSynchroCodes(DCMI_CodesInitTypeDef* DCMI_CodesInitStruct);
void DCMI_JPEGCmd(FunctionalState NewState);

/* Image capture functions ****************************************************/
void DCMI_Cmd(FunctionalState NewState);
void DCMI_CaptureCmd(FunctionalState NewState);
uint32_t DCMI_ReadData(void);

/* Interrupts and flags management functions **********************************/
void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState);
FlagStatus DCMI_GetFlagStatus(uint16_t DCMI_FLAG);
void DCMI_ClearFlag(uint16_t DCMI_FLAG);
ITStatus DCMI_GetITStatus(uint16_t DCMI_IT);
void DCMI_ClearITPendingBit(uint16_t DCMI_IT);

#ifdef __cplusplus
}
#endif

#endif /*__LIB_DCMI_H */

/*********************************** END OF FILE ******************************/
