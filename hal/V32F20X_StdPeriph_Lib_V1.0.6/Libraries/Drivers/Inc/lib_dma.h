
/**
  ******************************************************************************
  * @file    lib_dma.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   DMA library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_DMA_H
#define __LIB_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/**
  * @brief  Return the current DMA and Channel index number.
  */
#define IS_DMA_ALL_PERIPH(PERIPH)              (((PERIPH) == DMA0) || \
                                                ((PERIPH) == DMA1))

/**
  * @brief  Return the current DMA and Channel index number.
  */
#define DMA_CHANNEL_GET_INDEX(Instance, DMAx, CHANNEL_NUM)\
(((uint32_t)(Instance) == ((uint32_t)DMA0_Channel0))? ((DMAx=DMA0)? (CHANNEL_NUM=0) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA1_Channel0))? ((DMAx=DMA1)? (CHANNEL_NUM=0) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA0_Channel1))? ((DMAx=DMA0)? (CHANNEL_NUM=1) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA1_Channel1))? ((DMAx=DMA1)? (CHANNEL_NUM=1) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA0_Channel2))? ((DMAx=DMA0)? (CHANNEL_NUM=2) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA1_Channel2))? ((DMAx=DMA1)? (CHANNEL_NUM=2) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA0_Channel3))? ((DMAx=DMA0)? (CHANNEL_NUM=3) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA1_Channel3))? ((DMAx=DMA1)? (CHANNEL_NUM=3) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA0_Channel4))? ((DMAx=DMA0)? (CHANNEL_NUM=4) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA1_Channel4))? ((DMAx=DMA1)? (CHANNEL_NUM=4) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA0_Channel5))? ((DMAx=DMA0)? (CHANNEL_NUM=5) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA1_Channel5))? ((DMAx=DMA1)? (CHANNEL_NUM=5) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA0_Channel6))? ((DMAx=DMA0)? (CHANNEL_NUM=6) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA1_Channel6))? ((DMAx=DMA1)? (CHANNEL_NUM=6) : 0) :\
 ((uint32_t)(Instance) == ((uint32_t)DMA0_Channel7))? ((DMAx=DMA0)? (CHANNEL_NUM=7) : 0) :\
                                                         ((DMAx=DMA1)? (CHANNEL_NUM=7) : 0))

/**************** SAR Register ****************/
#define SAR_SAR_Mask                     (0xFFFFFFFF)

/**************** DAR Register ****************/
#define DAR_DAR_Mask                     (0xFFFFFFFF)

/**************** CTL[1] Register *************/
#define DMA_CTL1_DONE                    ((0x01UL) << 12)
#define DMA_CTL1_BLOCK_TS_Mask           (0xfff)

/**************** CTL[0] Register *************/
#define DMA_CTL0_LLP_SRC_EN              ((0x01UL) << 28)
#define DMA_CTL0_LLP_DST_EN              ((0x01UL) << 27)
#define DMA_CTL0_TT_FC_0                 ((0x00UL) << 20)
#define DMA_CTL0_TT_FC_1                 ((0x01UL) << 20)
#define DMA_CTL0_TT_FC_2                 ((0x02UL) << 20)
#define DMA_CTL0_TT_FC_3                 ((0x03UL) << 20)
#define DMA_CTL0_TT_FC_Mask              ((0x07UL) << 20)
#define DMA_CTL0_DST_SCATTER_EN          ((0x01UL) << 18)
#define DMA_CTL0_SRC_GATHER_EN           ((0x01UL) << 17)
#define DMA_CTL0_SRC_MSIZE_1             ((0x00UL) << 14)
#define DMA_CTL0_SRC_MSIZE_4             ((0x01UL) << 14)
#define DMA_CTL0_SRC_MSIZE_8             ((0x02UL) << 14)
#define DMA_CTL0_SRC_MSIZE_16            ((0x03UL) << 14)
#define DMA_CTL0_SRC_MSIZE_32            ((0x04UL) << 14)
#define DMA_CTL0_SRC_MSIZE_64            ((0x05UL) << 14)
#define DMA_CTL0_SRC_MSIZE_128           ((0x06UL) << 14)
#define DMA_CTL0_SRC_MSIZE_256           ((0x07UL) << 14)
#define DMA_CTL0_SRC_MSIZE_Mask          ((0x07UL) << 14)
#define DMA_CTL0_DEST_MSIZE_1            ((0x00UL) << 11)
#define DMA_CTL0_DEST_MSIZE_4            ((0x01UL) << 11)
#define DMA_CTL0_DEST_MSIZE_8            ((0x02UL) << 11)
#define DMA_CTL0_DEST_MSIZE_16           ((0x03UL) << 11)
#define DMA_CTL0_DEST_MSIZE_32           ((0x04UL) << 11)
#define DMA_CTL0_DEST_MSIZE_64           ((0x05UL) << 11)
#define DMA_CTL0_DEST_MSIZE_128          ((0x06UL) << 11)
#define DMA_CTL0_DEST_MSIZE_256          ((0x07UL) << 11)
#define DMA_CTL0_DEST_MSIZE_Mask         ((0x07UL) << 11)
#define DMA_CTL0_SINC_0                  ((0x00UL) << 9)
#define DMA_CTL0_SINC_1                  ((0x01UL) << 9)
#define DMA_CTL0_SINC_2                  ((0x02UL) << 9)
#define DMA_CTL0_SINC_3                  ((0x03UL) << 9)
#define DMA_CTL0_SINC_Mask               ((0x03UL) << 9)
#define DMA_CTL0_DINC_0                  ((0x00UL) << 7)
#define DMA_CTL0_DINC_1                  ((0x01UL) << 7)
#define DMA_CTL0_DINC_2                  ((0x02UL) << 7)
#define DMA_CTL0_DINC_3                  ((0x03UL) << 7)
#define DMA_CTL0_DINC_Mask               ((0x03UL) << 7)
#define DMA_CTL0_SRC_TR_WIDTH_8          ((0x00UL) << 4)
#define DMA_CTL0_SRC_TR_WIDTH_16         ((0x01UL) << 4)
#define DMA_CTL0_SRC_TR_WIDTH_32         ((0x02UL) << 4)
#define DMA_CTL0_SRC_TR_WIDTH_64         ((0x03UL) << 4)
#define DMA_CTL0_SRC_TR_WIDTH_128        ((0x04UL) << 4)
#define DMA_CTL0_SRC_TR_WIDTH_256        ((0x05UL) << 4)
#define DMA_CTL0_SRC_TR_WIDTH_Mask       ((0x07UL) << 4)
#define DMA_CTL0_DST_TR_WIDTH_8          ((0x00UL) << 1)
#define DMA_CTL0_DST_TR_WIDTH_16         ((0x01UL) << 1)
#define DMA_CTL0_DST_TR_WIDTH_32         ((0x02UL) << 1)
#define DMA_CTL0_DST_TR_WIDTH_64         ((0x03UL) << 1)
#define DMA_CTL0_DST_TR_WIDTH_128        ((0x04UL) << 1)
#define DMA_CTL0_DST_TR_WIDTH_256        ((0x05UL) << 1)
#define DMA_CTL0_DST_TR_WIDTH_Mask       ((0x07UL) << 1)
#define DMA_CTL0_INT_EN                  ((0x01UL) << 0)

/*************** CFG[0] Register **************/
#define DMA_CFG0_CH_PRIOR_0              ((0x00UL) << 5)
#define DMA_CFG0_CH_PRIOR_1              ((0x01UL) << 5)
#define DMA_CFG0_CH_PRIOR_2              ((0x02UL) << 5)
#define DMA_CFG0_CH_PRIOR_3              ((0x03UL) << 5)
#define DMA_CFG0_CH_PRIOR_4              ((0x04UL) << 5)
#define DMA_CFG0_CH_PRIOR_5              ((0x05UL) << 5)
#define DMA_CFG0_CH_PRIOR_6              ((0x06UL) << 5)
#define DMA_CFG0_CH_PRIOR_7              ((0x07UL) << 5)
#define DMA_CFG0_CH_PRIOR_Mask           ((0x07UL) << 5)
#define DMA_CFG0_CH_SUSP_No              ((0x00UL) << 8)
#define DMA_CFG0_CH_SUSP_EN              ((0x01UL) << 8)
#define DMA_CFG0_FIFO_EMPTY              ((0x01UL) << 9)
#define DMA_CFG0_HS_SEL_DST_HARDWARE     ((0x00UL) << 10)
#define DMA_CFG0_HS_SEL_DST_SOFTWARE     ((0x01UL) << 10)
#define DMA_CFG0_HS_SEL_SRC_HARDWARE     ((0x00UL) << 11)
#define DMA_CFG0_HS_SEL_SRC_SOFTWARE     ((0x01UL) << 11)
#define DMA_CFG0_DST_HS_POL_HIGH         ((0x00UL) << 18)
#define DMA_CFG0_DST_HS_POL_LOW          ((0x01UL) << 18)
#define DMA_CFG0_SRC_HS_POL_HIGH         ((0x00UL) << 19)
#define DMA_CFG0_SRC_HS_POL_LOW          ((0x01UL) << 19)
#define DMA_CFG0_RELOAD_SRC_EN           ((0x01UL) << 30)
#define DMA_CFG0_RELOAD_DST_EN           ((0x01UL) << 31)

/*************** CFG[1] Register **************/
#define DMA_CFG1_FCMODE_0                ((0x00UL) << 0)
#define DMA_CFG1_FCMODE_1                ((0x01UL) << 0)
#define DMA_CFG1_FIFO_MODE_0             ((0x00UL) << 1)
#define DMA_CFG1_FIFO_MODE_1             ((0x01UL) << 1)
#define DMA_CFG1_PROTCTL_0               ((0x00UL) << 2)
#define DMA_CFG1_PROTCTL_1               ((0x01UL) << 2)
#define DMA_CFG1_PROTCTL_2               ((0x01UL) << 3)
#define DMA_CFG1_PROTCTL_4               ((0x01UL) << 4)
#define DMA_CFG1_PROTCTL_Mask            ((0x07UL) << 2)
#define DMA_CFG1_DS_UPD_EN               ((0x01UL) << 5)
#define DMA_CFG1_SS_UPD_EN               ((0x01UL) << 6)
#define DMA_CFG1_SRC_PER_Mask            ((0xFUL) << 7)
#define DMA_CFG1_SRC_PER_0               ((0x0UL) << 7)
#define DMA_CFG1_SRC_PER_1               ((0x1UL) << 7)
#define DMA_CFG1_SRC_PER_2               ((0x2UL) << 7)
#define DMA_CFG1_SRC_PER_3               ((0x3UL) << 7)
#define DMA_CFG1_SRC_PER_4               ((0x4UL) << 7)
#define DMA_CFG1_SRC_PER_5               ((0x5UL) << 7)
#define DMA_CFG1_SRC_PER_6               ((0x6UL) << 7)
#define DMA_CFG1_SRC_PER_7               ((0x7UL) << 7)
#define DMA_CFG1_SRC_PER_8               ((0x8UL) << 7)
#define DMA_CFG1_SRC_PER_9               ((0x9UL) << 7)
#define DMA_CFG1_SRC_PER_10              ((0xAUL) << 7)
#define DMA_CFG1_SRC_PER_11              ((0xBUL) << 7)
#define DMA_CFG1_SRC_PER_12              ((0xCUL) << 7)
#define DMA_CFG1_SRC_PER_13              ((0xDUL) << 7)
#define DMA_CFG1_SRC_PER_14              ((0xEUL) << 7)
#define DMA_CFG1_SRC_PER_15              ((0xFUL) << 7)
#define DMA_CFG1_SRC_PER_Mask            ((0xFUL) << 7)
#define DMA_CFG1_DEST_PER_0              ((0x0UL) << 11)
#define DMA_CFG1_DEST_PER_1              ((0x1UL) << 11)
#define DMA_CFG1_DEST_PER_2              ((0x2UL) << 11)
#define DMA_CFG1_DEST_PER_3              ((0x3UL) << 11)
#define DMA_CFG1_DEST_PER_4              ((0x4UL) << 11)
#define DMA_CFG1_DEST_PER_5              ((0x5UL) << 11)
#define DMA_CFG1_DEST_PER_6              ((0x6UL) << 11)
#define DMA_CFG1_DEST_PER_7              ((0x7UL) << 11)
#define DMA_CFG1_DEST_PER_8              ((0x8UL) << 11)
#define DMA_CFG1_DEST_PER_9              ((0x9UL) << 11)
#define DMA_CFG1_DEST_PER_10             ((0xAUL) << 11)
#define DMA_CFG1_DEST_PER_11             ((0xBUL) << 11)
#define DMA_CFG1_DEST_PER_12             ((0xCUL) << 11)
#define DMA_CFG1_DEST_PER_13             ((0xDUL) << 11)
#define DMA_CFG1_DEST_PER_14             ((0xEUL) << 11)
#define DMA_CFG1_DEST_PER_15             ((0xFUL) << 11)
#define DMA_CFG1_DEST_PER_Mask           ((0xFUL) << 11)

/*************** RAWTFR Register **************/
#define DMA_RAWTFR_RAW0                  (0x00000001)
#define DMA_RAWTFR_RAW1                  (0x00000002)
#define DMA_RAWTFR_RAW2                  (0x00000004)
#define DMA_RAWTFR_RAW3                  (0x00000008)
#define DMA_RAWTFR_RAW4                  (0x00000010)
#define DMA_RAWTFR_RAW5                  (0x00000020)
#define DMA_RAWTFR_RAW6                  (0x00000040)
#define DMA_RAWTFR_RAW7                  (0x00000080)

/*************** RAWBLOCK Register **************/
#define DMA_RAWBLOCK_RAW0                (0x00000001)
#define DMA_RAWBLOCK_RAW1                (0x00000002)
#define DMA_RAWBLOCK_RAW2                (0x00000004)
#define DMA_RAWBLOCK_RAW3                (0x00000008)
#define DMA_RAWBLOCK_RAW4                (0x00000010)
#define DMA_RAWBLOCK_RAW5                (0x00000020)
#define DMA_RAWBLOCK_RAW6                (0x00000040)
#define DMA_RAWBLOCK_RAW7                (0x00000080)

/*************** RAWSRCTRAN Register **************/
#define DMA_RAWSRCTRAN_RAW0              (0x00000001)
#define DMA_RAWSRCTRAN_RAW1              (0x00000002)
#define DMA_RAWSRCTRAN_RAW2              (0x00000004)
#define DMA_RAWSRCTRAN_RAW3              (0x00000008)
#define DMA_RAWSRCTRAN_RAW4              (0x00000010)
#define DMA_RAWSRCTRAN_RAW5              (0x00000020)
#define DMA_RAWSRCTRAN_RAW6              (0x00000040)
#define DMA_RAWSRCTRAN_RAW7              (0x00000080)

/*************** RAWDSTTRAN Register **************/
#define DMA_RAWDSTTRAN_RAW0              (0x00000001)
#define DMA_RAWDSTTRAN_RAW1              (0x00000002)
#define DMA_RAWDSTTRAN_RAW2              (0x00000004)
#define DMA_RAWDSTTRAN_RAW3              (0x00000008)
#define DMA_RAWDSTTRAN_RAW4              (0x00000010)
#define DMA_RAWDSTTRAN_RAW5              (0x00000020)
#define DMA_RAWDSTTRAN_RAW6              (0x00000040)
#define DMA_RAWDSTTRAN_RAW7              (0x00000080)

/*************** RAWERR Register **************/
#define DMA_RAWERR_RAW0                  (0x00000001)
#define DMA_RAWERR_RAW1                  (0x00000002)
#define DMA_RAWERR_RAW2                  (0x00000004)
#define DMA_RAWERR_RAW3                  (0x00000008)
#define DMA_RAWERR_RAW4                  (0x00000010)
#define DMA_RAWERR_RAW5                  (0x00000020)
#define DMA_RAWERR_RAW6                  (0x00000040)
#define DMA_RAWERR_RAW7                  (0x00000080)

/*************** STATUSTFR Register **************/
#define DMA_STATUSTFR_STATUS0            (0x00000001)
#define DMA_STATUSTFR_STATUS1            (0x00000002)
#define DMA_STATUSTFR_STATUS2            (0x00000004)
#define DMA_STATUSTFR_STATUS3            (0x00000008)
#define DMA_STATUSTFR_STATUS4            (0x00000010)
#define DMA_STATUSTFR_STATUS5            (0x00000020)
#define DMA_STATUSTFR_STATUS6            (0x00000040)
#define DMA_STATUSTFR_STATUS7            (0x00000080)

/*************** STATUSBLOCK Register **************/
#define DMA_STATUSBLOCK_STATUS0          (0x00000001)
#define DMA_STATUSBLOCK_STATUS1          (0x00000002)
#define DMA_STATUSBLOCK_STATUS2          (0x00000004)
#define DMA_STATUSBLOCK_STATUS3          (0x00000008)
#define DMA_STATUSBLOCK_STATUS4          (0x00000010)
#define DMA_STATUSBLOCK_STATUS5          (0x00000020)
#define DMA_STATUSBLOCK_STATUS6          (0x00000040)
#define DMA_STATUSBLOCK_STATUS7          (0x00000080)

/*************** STATUSSRCTRAN Register **************/
#define DMA_STATUSSRCTRAN_STATUS0        (0x00000001)
#define DMA_STATUSSRCTRAN_STATUS1        (0x00000002)
#define DMA_STATUSSRCTRAN_STATUS2        (0x00000004)
#define DMA_STATUSSRCTRAN_STATUS3        (0x00000008)
#define DMA_STATUSSRCTRAN_STATUS4        (0x00000010)
#define DMA_STATUSSRCTRAN_STATUS5        (0x00000020)
#define DMA_STATUSSRCTRAN_STATUS6        (0x00000040)
#define DMA_STATUSSRCTRAN_STATUS7        (0x00000080)

/*************** STATUSDSTTRAN Register **************/
#define DMA_STATUSDSTTRAN_STATUS0        (0x00000001)
#define DMA_STATUSDSTTRAN_STATUS1        (0x00000002)
#define DMA_STATUSDSTTRAN_STATUS2        (0x00000004)
#define DMA_STATUSDSTTRAN_STATUS3        (0x00000008)
#define DMA_STATUSDSTTRAN_STATUS4        (0x00000010)
#define DMA_STATUSDSTTRAN_STATUS5        (0x00000020)
#define DMA_STATUSDSTTRAN_STATUS6        (0x00000040)
#define DMA_STATUSDSTTRAN_STATUS7        (0x00000080)

/*************** STATUSERR Register **************/
#define DMA_STATUSERR_STATUS0            (0x00000001)
#define DMA_STATUSERR_STATUS1            (0x00000002)
#define DMA_STATUSERR_STATUS2            (0x00000004)
#define DMA_STATUSERR_STATUS3            (0x00000008)
#define DMA_STATUSERR_STATUS4            (0x00000010)
#define DMA_STATUSERR_STATUS5            (0x00000020)
#define DMA_STATUSERR_STATUS6            (0x00000040)
#define DMA_STATUSERR_STATUS7            (0x00000080)

/*************** MASKTFR Register **************/
#define DMA_MASKTFR_NT_MASK_WE0          (0x00000100)
#define DMA_MASKTFR_NT_MASK_WE1          (0x00000200)
#define DMA_MASKTFR_NT_MASK_WE2          (0x00000400)
#define DMA_MASKTFR_NT_MASK_WE3          (0x00000800)
#define DMA_MASKTFR_NT_MASK_WE4          (0x00001000)
#define DMA_MASKTFR_NT_MASK_WE5          (0x00002000)
#define DMA_MASKTFR_NT_MASK_WE6          (0x00004000)
#define DMA_MASKTFR_NT_MASK_WE7          (0x00008000)

#define DMA_INT_TC0                      DMA_RAWTFR_RAW0
#define DMA_INT_TC1                      DMA_RAWTFR_RAW1
#define DMA_INT_TC2                      DMA_RAWTFR_RAW2
#define DMA_INT_TC3                      DMA_RAWTFR_RAW3
#define DMA_INT_TC4                      DMA_RAWTFR_RAW4
#define DMA_INT_TC5                      DMA_RAWTFR_RAW5
#define DMA_INT_TC6                      DMA_RAWTFR_RAW6
#define DMA_INT_TC7                      DMA_RAWTFR_RAW7

#define DMA_INT_Mask_WE0                 DMA_MASKTFR_NT_MASK_WE0
#define DMA_INT_Mask_WE1                 DMA_MASKTFR_NT_MASK_WE1
#define DMA_INT_Mask_WE2                 DMA_MASKTFR_NT_MASK_WE2
#define DMA_INT_Mask_WE3                 DMA_MASKTFR_NT_MASK_WE3
#define DMA_INT_Mask_WE4                 DMA_MASKTFR_NT_MASK_WE4
#define DMA_INT_Mask_WE5                 DMA_MASKTFR_NT_MASK_WE5
#define DMA_INT_Mask_WE6                 DMA_MASKTFR_NT_MASK_WE6
#define DMA_INT_Mask_WE7                 DMA_MASKTFR_NT_MASK_WE7

/*!<*************  Bit definition for CONTROL register  **************/
#define DMA_CONTROL_FF_TH_SHIFT           (29UL)
#define DMA_CONTROL_TC_MSK                ((0x1UL) << 28)
#define DMA_CONTROL_SRC_WIDTH_SHIFT       (4UL)
#define DMA_CONTROL_DST_WIDTH_SHIFT       (1UL)
#define DMA_CONTROL_SRCAD_CTL_SHIFT       (9UL)
#define DMA_CONTROL_DSTAD_CTL_SHIFT       (7UL)

//DMA interrupt
#define DMA_INT_TFR                      (0)
#define DMA_INT_BLOCK                    (1)
#define DMA_INT_SRCTRAN                  (2)
#define DMA_INT_DSTTRAN                  (3)
#define DMA_INT_ERR                      (4)
#define IS_DMA_CONFIG_IT(INT)             (((INT) == DMA_INT_TFR)     || \
                                           ((INT) == DMA_INT_BLOCK)   || \
                                           ((INT) == DMA_INT_SRCTRAN) || \
                                           ((INT) == DMA_INT_DSTTRAN) || \
                                           ((INT) == DMA_INT_ERR))

/** 
  * @brief  DMA Init structure definition
  */
typedef struct
{
  uint32_t DMA_Mode;                              /*!< Specifies the DMA link list or auto-reload transfer state. */
  uint32_t DMA_DIR;                               /*!< Specifies the direction of the DMA Channelx data flow. */
  uint32_t DMA_SourceBurstSize;                   /*!< Specifies the source burst size. 
                                                  How many "SourceTransferWidth" will be transmmited at one times*/
  uint32_t DMA_DestinationBurstSize;              /*!< Specifies the Destination burst size. 
                                                  How many "DestinationTransferWidth" will be transmmited at one times*/
  uint32_t DMA_SourceTransferWidth;               /*!< Specifies the source transfer width. */
  uint32_t DMA_DestinationTransferWidth;          /*!< Specifies the destination transfer width. */
  uint32_t DMA_SourceAddressControl;              /*!< Specifies the source address control of the DMA Channelx. */
  uint32_t DMA_DestinationAddressControl;         /*!< Specifies the destination address control of the DMA Channelx. */
  uint32_t DMA_SourceRequestSelect;               /*!< Specifies the source request select of the DMA Channelx. */
  uint32_t DMA_DestinationRequestSelect;          /*!< Specifies the destination request select of the DMA Channelx. */
  uint32_t DMA_SourceAddress;                     /*!< Specifies the source address of the DMA Channelx. */
  uint32_t DMA_DestinationAddress;                /*!< Specifies the destination address of the DMA Channelx. */
  uint32_t DMA_TransferSize;                      /*!< Specifies the total transfer bytes of the DMA Channelx. */
  uint32_t DMA_Priority;                          /*!< Initialize the DMA_Priority member. */
  uint32_t DMA_LinkListAddress;                   /*!< Specifies the link list descriptor pointer address of the DMA Channelx. */
}DMA_InitType;

/** 
  * @brief  DMA Link List Control structure definition
  */
typedef struct
{
  uint32_t reserved:16;
  uint32_t dst_sel:1;
  uint32_t src_sel:1;
  uint32_t dst_ctrl:2;
  uint32_t src_ctrl:2;
  uint32_t dst_width:3;
  uint32_t src_width:3;
  uint32_t tc_msk:1;
  uint32_t ff_th:3;
}DMA_LinkListControlType;

/** 
  * @brief  DMA Link List structure definition
  */
typedef struct
{
  uint32_t SrcAddr;
  uint32_t DstAddr;
  uint32_t LLP;
  uint32_t CTL0;
  uint32_t CTL1;
}__attribute__((aligned(4))) DMA_LinkListType;

/** 
  * @brief  DMA Link List structure info definition
  */
typedef struct
{
  uint32_t DMA_DIR;                       /*!< Specifies the direction of the DMA Channelx data flow. */
  uint32_t DMA_SourceAddress;             /*!< Specifies the source address of the DMA Channelx. */
  uint32_t DMA_DestinationAddress;        /*!< Specifies the destination address of the DMA Channelx. */
  uint32_t DMA_NextLLPAddr;               /*!< Specifies the address of next DMA Link List. */
  uint32_t DMA_TransferSize;              /*!< Specifies the total transfer bytes of the DMA Channelx. */
  uint32_t DMA_SourceBurstSize;           /*!< Specifies the source burst size. 
                                          How many "SourceTransferWidth" will be transmmited at one times*/
  uint32_t DMA_DestinationBurstSize;      /*!< Specifies the Destination burst size. 
                                          How many "DestinationTransferWidth" will be transmmited at one times*/
  uint32_t DMA_SourceTransferWidth;       /*!< Specifies the source transfer width. */
  uint32_t DMA_DestinationTransferWidth;  /*!< Specifies the destination transfer width. */
  uint32_t DMA_SourceAddressControl;      /*!< Specifies the source address control of the DMA Channelx. */
  uint32_t DMA_DestinationAddressControl; /*!< Specifies the destination address control of the DMA Channelx. */
}DMA_LinkListInfoType;

#define IS_DMA_CHANNEL_ALL_PERIPH(PERIPH)      (((PERIPH) == DMA0_Channel0) || \
                                                ((PERIPH) == DMA0_Channel1) || \
                                                ((PERIPH) == DMA0_Channel2) || \
                                                ((PERIPH) == DMA0_Channel3) || \
                                                ((PERIPH) == DMA0_Channel4) || \
                                                ((PERIPH) == DMA0_Channel5) || \
                                                ((PERIPH) == DMA0_Channel6) || \
                                                ((PERIPH) == DMA0_Channel7) || \
                                                ((PERIPH) == DMA1_Channel0) || \
                                                ((PERIPH) == DMA1_Channel1) || \
                                                ((PERIPH) == DMA1_Channel2) || \
                                                ((PERIPH) == DMA1_Channel3) || \
                                                ((PERIPH) == DMA1_Channel4) || \
                                                ((PERIPH) == DMA1_Channel5) || \
                                                ((PERIPH) == DMA1_Channel6) || \
                                                ((PERIPH) == DMA1_Channel7))

//DMA_DIR
#define DMA_DIR_Memory2Memory                   DMA_CTL0_TT_FC_0
#define DMA_DIR_Memory2Peripheral               DMA_CTL0_TT_FC_1
#define DMA_DIR_Peripheral2Memory               DMA_CTL0_TT_FC_2
#define DMA_DIR_Peripheral2Peripheral           DMA_CTL0_TT_FC_3
#define IS_DMA_DIR(DIR)                         (((DIR) == DMA_DIR_Memory2Memory)     || \
                                                 ((DIR) == DMA_DIR_Memory2Peripheral) || \
                                                 ((DIR) == DMA_DIR_Peripheral2Memory) || \
                                                 ((DIR) == DMA_DIR_Peripheral2Peripheral))
                                                  
//DMA_Mode
#define DMA_MODE_NORMAL                          0
#define DMA_MODE_LINK_LIST                       1
#define DMA_MODE_AUTO_RELOAD                     2
#define IS_DMA_MODE(MODE)                        (((MODE) == DMA_MODE_NORMAL)    || \
                                                  ((MODE) == DMA_MODE_LINK_LIST) || \
                                                  ((MODE) == DMA_MODE_AUTO_RELOAD))
                            
//DMA_SourceBurstSize
#define DMA_SourceBurstSize_1                    DMA_CTL0_SRC_MSIZE_1
#define DMA_SourceBurstSize_4                    DMA_CTL0_SRC_MSIZE_4
#define DMA_SourceBurstSize_8                    DMA_CTL0_SRC_MSIZE_8
#define DMA_SourceBurstSize_16                   DMA_CTL0_SRC_MSIZE_16
#define DMA_SourceBurstSize_32                   DMA_CTL0_SRC_MSIZE_32
#define DMA_SourceBurstSize_64                   DMA_CTL0_SRC_MSIZE_64
#define DMA_SourceBurstSize_128                  DMA_CTL0_SRC_MSIZE_128
#define DMA_SourceBurstSize_256                  DMA_CTL0_SRC_MSIZE_256
#define IS_DMA_SOURCE_BURST_SIZE(S)              (((S) == DMA_SourceBurstSize_1)   || \
                                                  ((S) == DMA_SourceBurstSize_4)   || \
                                                  ((S) == DMA_SourceBurstSize_8)   || \
                                                  ((S) == DMA_SourceBurstSize_16)  || \
                                                  ((S) == DMA_SourceBurstSize_32)  || \
                                                  ((S) == DMA_SourceBurstSize_64)  || \
                                                  ((S) == DMA_SourceBurstSize_128) || \
                                                  ((S) == DMA_SourceBurstSize_256))

//DMA_DestinationBurstSize
#define DMA_DestinationBurstSize_1               DMA_CTL0_DEST_MSIZE_1
#define DMA_DestinationBurstSize_4               DMA_CTL0_DEST_MSIZE_4
#define DMA_DestinationBurstSize_8               DMA_CTL0_DEST_MSIZE_8
#define DMA_DestinationBurstSize_16              DMA_CTL0_DEST_MSIZE_16
#define DMA_DestinationBurstSize_32              DMA_CTL0_DEST_MSIZE_32
#define DMA_DestinationBurstSize_64              DMA_CTL0_DEST_MSIZE_64
#define DMA_DestinationBurstSize_128             DMA_CTL0_DEST_MSIZE_128
#define DMA_DestinationBurstSize_256             DMA_CTL0_DEST_MSIZE_256

#define IS_DMA_DESTINATION_BURST_SIZE(S)         (((S) == DMA_DestinationBurstSize_1)   || \
                                                  ((S) == DMA_DestinationBurstSize_4)   || \
                                                  ((S) == DMA_DestinationBurstSize_8)   || \
                                                  ((S) == DMA_DestinationBurstSize_16)  || \
                                                  ((S) == DMA_DestinationBurstSize_32)  || \
                                                  ((S) == DMA_DestinationBurstSize_64)  || \
                                                  ((S) == DMA_DestinationBurstSize_128) || \
                                                  ((S) == DMA_DestinationBurstSize_256))


//DMA_SourceTransferWidth
#define DMA_SourceTransferWidth_8Bit             DMA_CTL0_SRC_TR_WIDTH_8
#define DMA_SourceTransferWidth_16Bit            DMA_CTL0_SRC_TR_WIDTH_16
#define DMA_SourceTransferWidth_32Bit            DMA_CTL0_SRC_TR_WIDTH_32
#define DMA_SourceTransferWidth_64Bit            DMA_CTL0_SRC_TR_WIDTH_64
#define DMA_SourceTransferWidth_128Bit           DMA_CTL0_SRC_TR_WIDTH_128
#define DMA_SourceTransferWidth_256Bit           DMA_CTL0_SRC_TR_WIDTH_256
#define IS_DMA_SOURCE_TRANSFER_WIDTH(W)          (((W) == DMA_SourceTransferWidth_8Bit)  || \
                                                  ((W) == DMA_SourceTransferWidth_16Bit) || \
                                                  ((W) == DMA_SourceTransferWidth_32Bit) || \
                                                  ((W) == DMA_SourceTransferWidth_64Bit) || \
                                                  ((W) == DMA_SourceTransferWidth_128Bit) || \
                                                  ((W) == DMA_SourceTransferWidth_256Bit))

//DMA_DestinationTransferWidth
#define DMA_DestinationTransferWidth_8Bit        DMA_CTL0_DST_TR_WIDTH_8
#define DMA_DestinationTransferWidth_16Bit       DMA_CTL0_DST_TR_WIDTH_16
#define DMA_DestinationTransferWidth_32Bit       DMA_CTL0_DST_TR_WIDTH_32
#define DMA_DestinationTransferWidth_64Bit       DMA_CTL0_DST_TR_WIDTH_64
#define DMA_DestinationTransferWidth_128Bit      DMA_CTL0_DST_TR_WIDTH_128
#define DMA_DestinationTransferWidth_256Bit      DMA_CTL0_DST_TR_WIDTH_256
#define IS_DMA_DESTINATION_TRANSFER_WIDTH(W)     (((W) == DMA_DestinationTransferWidth_8Bit)  || \
                                                  ((W) == DMA_DestinationTransferWidth_16Bit) || \
                                                  ((W) == DMA_DestinationTransferWidth_32Bit) || \
                                                  ((W) == DMA_DestinationTransferWidth_64Bit) || \
                                                  ((W) == DMA_DestinationTransferWidth_128Bit) || \
                                                  ((W) == DMA_DestinationTransferWidth_256Bit))
                                         
//DMA_SourceAddressControl
#define DMA_SourceAddressControl_Increment        DMA_CTL0_SINC_0
#define DMA_SourceAddressControl_Decrement        DMA_CTL0_SINC_1
#define DMA_SourceAddressControl_Fixed            DMA_CTL0_SINC_2
#define IS_DMA_SOURCE_ADDRESS_CONTROL(C)          (((C) == DMA_SourceAddressControl_Increment) || \
                                                   ((C) == DMA_SourceAddressControl_Decrement) || \
                                                   ((C) == DMA_SourceAddressControl_Fixed))
                                              
//DMA_DestinationAddressControl
#define DMA_DestinationAddressControl_Increment   DMA_CTL0_DINC_0
#define DMA_DestinationAddressControl_Decrement   DMA_CTL0_DINC_1
#define DMA_DestinationAddressControl_Fixed       DMA_CTL0_DINC_2
#define IS_DMA_DESTINATION_ADDRESS_CONTROL(C)     (((C) == DMA_DestinationAddressControl_Increment) || \
                                                   ((C) == DMA_DestinationAddressControl_Decrement) || \
                                                   ((C) == DMA_DestinationAddressControl_Fixed))
                                          
//DMA_SourceRequestSelect
#define DMA_SourceRequestSelect_0                 DMA_CFG1_SRC_PER_0 
#define DMA_SourceRequestSelect_1                 DMA_CFG1_SRC_PER_1 
#define DMA_SourceRequestSelect_2                 DMA_CFG1_SRC_PER_2 
#define DMA_SourceRequestSelect_3                 DMA_CFG1_SRC_PER_3 
#define DMA_SourceRequestSelect_4                 DMA_CFG1_SRC_PER_4 
#define DMA_SourceRequestSelect_5                 DMA_CFG1_SRC_PER_5 
#define DMA_SourceRequestSelect_6                 DMA_CFG1_SRC_PER_6 
#define DMA_SourceRequestSelect_7                 DMA_CFG1_SRC_PER_7 
#define DMA_SourceRequestSelect_8                 DMA_CFG1_SRC_PER_8 
#define DMA_SourceRequestSelect_9                 DMA_CFG1_SRC_PER_9 
#define DMA_SourceRequestSelect_10                DMA_CFG1_SRC_PER_10
#define DMA_SourceRequestSelect_11                DMA_CFG1_SRC_PER_11
#define DMA_SourceRequestSelect_12                DMA_CFG1_SRC_PER_12
#define DMA_SourceRequestSelect_13                DMA_CFG1_SRC_PER_13
#define DMA_SourceRequestSelect_14                DMA_CFG1_SRC_PER_14
#define DMA_SourceRequestSelect_15                DMA_CFG1_SRC_PER_15
#define IS_DMA_SOURCE_REQUEST_SELECT(S)           (((S) == DMA_SourceRequestSelect_0 ) || \
                                                   ((S) == DMA_SourceRequestSelect_1 ) || \
                                                   ((S) == DMA_SourceRequestSelect_2 ) || \
                                                   ((S) == DMA_SourceRequestSelect_3 ) || \
                                                   ((S) == DMA_SourceRequestSelect_4 ) || \
                                                   ((S) == DMA_SourceRequestSelect_5 ) || \
                                                   ((S) == DMA_SourceRequestSelect_6 ) || \
                                                   ((S) == DMA_SourceRequestSelect_7 ) || \
                                                   ((S) == DMA_SourceRequestSelect_8 ) || \
                                                   ((S) == DMA_SourceRequestSelect_9 ) || \
                                                   ((S) == DMA_SourceRequestSelect_10) || \
                                                   ((S) == DMA_SourceRequestSelect_11) || \
                                                   ((S) == DMA_SourceRequestSelect_12) || \
                                                   ((S) == DMA_SourceRequestSelect_13) || \
                                                   ((S) == DMA_SourceRequestSelect_14) || \
                                                   ((S) == DMA_SourceRequestSelect_15))
                                                   
//DMA_DestinationRequestSelect
#define DMA_DestinationRequestSelect_0            DMA_CFG1_DEST_PER_0 
#define DMA_DestinationRequestSelect_1            DMA_CFG1_DEST_PER_1 
#define DMA_DestinationRequestSelect_2            DMA_CFG1_DEST_PER_2 
#define DMA_DestinationRequestSelect_3            DMA_CFG1_DEST_PER_3 
#define DMA_DestinationRequestSelect_4            DMA_CFG1_DEST_PER_4 
#define DMA_DestinationRequestSelect_5            DMA_CFG1_DEST_PER_5 
#define DMA_DestinationRequestSelect_6            DMA_CFG1_DEST_PER_6 
#define DMA_DestinationRequestSelect_7            DMA_CFG1_DEST_PER_7 
#define DMA_DestinationRequestSelect_8            DMA_CFG1_DEST_PER_8 
#define DMA_DestinationRequestSelect_9            DMA_CFG1_DEST_PER_9 
#define DMA_DestinationRequestSelect_10           DMA_CFG1_DEST_PER_10
#define DMA_DestinationRequestSelect_11           DMA_CFG1_DEST_PER_11
#define DMA_DestinationRequestSelect_12           DMA_CFG1_DEST_PER_12
#define DMA_DestinationRequestSelect_13           DMA_CFG1_DEST_PER_13
#define DMA_DestinationRequestSelect_14           DMA_CFG1_DEST_PER_14
#define DMA_DestinationRequestSelect_15           DMA_CFG1_DEST_PER_15
#define IS_DMA_DESTINATION_REQUEST_SELECT(S)     (((S) == DMA_DestinationRequestSelect_0 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_1 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_2 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_3 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_4 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_5 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_6 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_7 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_8 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_9 ) || \
                                                  ((S) == DMA_DestinationRequestSelect_10) || \
                                                  ((S) == DMA_DestinationRequestSelect_11) || \
                                                  ((S) == DMA_DestinationRequestSelect_12) || \
                                                  ((S) == DMA_DestinationRequestSelect_13) || \
                                                  ((S) == DMA_DestinationRequestSelect_14) || \
                                                  ((S) == DMA_DestinationRequestSelect_15))

#define DMA_Priority_0                           ((uint32_t)0x00000000)
#define DMA_Priority_1                           ((uint32_t)0x00000020) 
#define DMA_Priority_2                           ((uint32_t)0x00000040)
#define DMA_Priority_3                           ((uint32_t)0x00000060)
#define DMA_Priority_4                           ((uint32_t)0x00000080)
#define DMA_Priority_5                           ((uint32_t)0x000000a0)
#define DMA_Priority_6                           ((uint32_t)0x000000c0)
#define DMA_Priority_7                           ((uint32_t)0x000000e0)
#define DMA_Priority_Mask                        ((uint32_t)0x000000e0)
#define IS_DMA_PRIORITY(PRIORITY)                (((PRIORITY) == DMA_Priority_0) || \
                                                  ((PRIORITY) == DMA_Priority_1) || \
                                                  ((PRIORITY) == DMA_Priority_2) || \
                                                  ((PRIORITY) == DMA_Priority_3) || \
                                                  ((PRIORITY) == DMA_Priority_4) || \
                                                  ((PRIORITY) == DMA_Priority_5) || \
                                                  ((PRIORITY) == DMA_Priority_6) || \
                                                  ((PRIORITY) == DMA_Priority_7)) 
                                   
#define IS_DMA_TRANSFER_SIZE(S)                  ((S&0xffffe000) == 0)
#define IS_DMA_LINK_LIST_ADDRESS(ADDR)           ((ADDR&0x3) == 0)

/* Exported functions ------------------------------------------------------- */
void      DMA_DeInit(DMA_Channel_Type* DMAx_Channely);
void      DMA_StructInit(DMA_InitType* DMA_InitStruct);
void      DMA_Init(DMA_Channel_Type* DMAx_Channely, DMA_InitType* DMA_InitStruct);
void      DMA_LinkListInit(DMA_LinkListType* DMA_LLP, \
                             DMA_LinkListInfoType* DMA_LinkListInfo);
void      DMA_ChannelCmd(DMA_Channel_Type* DMAx_Channely, FunctionalState NewState);
void      DMA_Cmd(DMA_Type* DMAx, FunctionalState NewState);
void      DMA_ITConfig(DMA_Channel_Type* DMAx_Channely, uint32_t DMA_IT, FunctionalState NewState);
FlagStatus DMA_GetChnEnStatus(DMA_Channel_Type* DMAx_Channely);
ITStatus  DMA_GetITtatus(DMA_Channel_Type* DMAx_Channely, uint32_t DMA_IT);
void      DMA_ClearITStatus(DMA_Channel_Type* DMAx_Channely, uint32_t DMA_IT);
uint16_t  DMA_GetCurrTransferredCounter(DMA_Channel_Type* DMAx_Channely);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_DMA_H */

/*********************************** END OF FILE ******************************/
