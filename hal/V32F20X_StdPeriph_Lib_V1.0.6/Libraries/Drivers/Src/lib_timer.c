/**
  ******************************************************************************
  * @file    lib_timer.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-03-05
  * @brief   This file provides all the TMR firmware functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_timer.h"


/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup TMR
  * @brief TMR driver modules
  * @{
  */

/** @defgroup TMR_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR_Private_Defines
  * @{
  */

/******************************************************************************/
/*                                                                            */
/*                                    TMR                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TMR_CR1 register  ********************/
#define  TMR_CR1_CEN                         ((uint16_t)0x0001)            /*!<Counter enable        */
#define  TMR_CR1_UDIS                        ((uint16_t)0x0002)            /*!<Update disable        */
#define  TMR_CR1_URS                         ((uint16_t)0x0004)            /*!<Update request source */
#define  TMR_CR1_OPM                         ((uint16_t)0x0008)            /*!<One pulse mode        */
#define  TMR_CR1_DIR                         ((uint16_t)0x0010)            /*!<Direction             */

#define  TMR_CR1_CMS                         ((uint16_t)0x0060)            /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define  TMR_CR1_CMS_0                       ((uint16_t)0x0020)            /*!<Bit 0 */
#define  TMR_CR1_CMS_1                       ((uint16_t)0x0040)            /*!<Bit 1 */

#define  TMR_CR1_ARPE                        ((uint16_t)0x0080)            /*!<Auto-reload preload enable     */

#define  TMR_CR1_CKD                         ((uint16_t)0x0300)            /*!<CKD[1:0] bits (clock division) */
#define  TMR_CR1_CKD_0                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TMR_CR1_CKD_1                       ((uint16_t)0x0200)            /*!<Bit 1 */

/*******************  Bit definition for TMR_CR2 register  ********************/
#define  TMR_CR2_CCPC                        ((uint16_t)0x0001)            /*!<Capture/Compare Preloaded Control        */
#define  TMR_CR2_CCUS                        ((uint16_t)0x0004)            /*!<Capture/Compare Control Update Selection */
#define  TMR_CR2_CCDS                        ((uint16_t)0x0008)            /*!<Capture/Compare DMA Selection            */

#define  TMR_CR2_MMS                         ((uint16_t)0x0070)            /*!<MMS[2:0] bits (Master Mode Selection) */
#define  TMR_CR2_MMS_0                       ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TMR_CR2_MMS_1                       ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TMR_CR2_MMS_2                       ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TMR_CR2_TI1S                        ((uint16_t)0x0080)            /*!<TI1 Selection */
#define  TMR_CR2_OIS1                        ((uint16_t)0x0100)            /*!<Output Idle state 1 (OC1 output)  */
#define  TMR_CR2_OIS1N                       ((uint16_t)0x0200)            /*!<Output Idle state 1 (OC1N output) */
#define  TMR_CR2_OIS2                        ((uint16_t)0x0400)            /*!<Output Idle state 2 (OC2 output)  */
#define  TMR_CR2_OIS2N                       ((uint16_t)0x0800)            /*!<Output Idle state 2 (OC2N output) */
#define  TMR_CR2_OIS3                        ((uint16_t)0x1000)            /*!<Output Idle state 3 (OC3 output)  */
#define  TMR_CR2_OIS3N                       ((uint16_t)0x2000)            /*!<Output Idle state 3 (OC3N output) */
#define  TMR_CR2_OIS4                        ((uint16_t)0x4000)            /*!<Output Idle state 4 (OC4 output)  */

/*******************  Bit definition for TMR_SMCR register  *******************/
#define  TMR_SMCR_SMS                        ((uint16_t)0x0007)            /*!<SMS[2:0] bits (Slave mode selection)    */
#define  TMR_SMCR_SMS_0                      ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TMR_SMCR_SMS_1                      ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TMR_SMCR_SMS_2                      ((uint16_t)0x0004)            /*!<Bit 2 */

#define  TMR_SMCR_TS                         ((uint16_t)0x0070)            /*!<TS[2:0] bits (Trigger selection)        */
#define  TMR_SMCR_TS_0                       ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TMR_SMCR_TS_1                       ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TMR_SMCR_TS_2                       ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TMR_SMCR_MSM                        ((uint16_t)0x0080)            /*!<Master/slave mode                       */

#define  TMR_SMCR_ETF                        ((uint16_t)0x0F00)            /*!<ETF[3:0] bits (External trigger filter) */
#define  TMR_SMCR_ETF_0                      ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TMR_SMCR_ETF_1                      ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TMR_SMCR_ETF_2                      ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TMR_SMCR_ETF_3                      ((uint16_t)0x0800)            /*!<Bit 3 */

#define  TMR_SMCR_ETPS                       ((uint16_t)0x3000)            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define  TMR_SMCR_ETPS_0                     ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TMR_SMCR_ETPS_1                     ((uint16_t)0x2000)            /*!<Bit 1 */

#define  TMR_SMCR_ECE                        ((uint16_t)0x4000)            /*!<External clock enable     */
#define  TMR_SMCR_ETP                        ((uint16_t)0x8000)            /*!<External trigger polarity */

/*******************  Bit definition for TMR_DIER register  *******************/
#define  TMR_DIER_UIE                        ((uint16_t)0x0001)            /*!<Update interrupt enable */
#define  TMR_DIER_CC1IE                      ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt enable   */
#define  TMR_DIER_CC2IE                      ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt enable   */
#define  TMR_DIER_CC3IE                      ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt enable   */
#define  TMR_DIER_CC4IE                      ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt enable   */
#define  TMR_DIER_COMIE                      ((uint16_t)0x0020)            /*!<COM interrupt enable                 */
#define  TMR_DIER_TIE                        ((uint16_t)0x0040)            /*!<Trigger interrupt enable             */
#define  TMR_DIER_BIE                        ((uint16_t)0x0080)            /*!<Break interrupt enable               */
#define  TMR_DIER_UDE                        ((uint16_t)0x0100)            /*!<Update DMA request enable            */
#define  TMR_DIER_CC1DE                      ((uint16_t)0x0200)            /*!<Capture/Compare 1 DMA request enable */
#define  TMR_DIER_CC2DE                      ((uint16_t)0x0400)            /*!<Capture/Compare 2 DMA request enable */
#define  TMR_DIER_CC3DE                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 DMA request enable */
#define  TMR_DIER_CC4DE                      ((uint16_t)0x1000)            /*!<Capture/Compare 4 DMA request enable */
#define  TMR_DIER_COMDE                      ((uint16_t)0x2000)            /*!<COM DMA request enable               */
#define  TMR_DIER_TDE                        ((uint16_t)0x4000)            /*!<Trigger DMA request enable           */

/********************  Bit definition for TMR_SR register  ********************/
#define  TMR_SR_UIF                          ((uint16_t)0x0001)            /*!<Update interrupt Flag              */
#define  TMR_SR_CC1IF                        ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt Flag   */
#define  TMR_SR_CC2IF                        ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt Flag   */
#define  TMR_SR_CC3IF                        ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt Flag   */
#define  TMR_SR_CC4IF                        ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt Flag   */
#define  TMR_SR_COMIF                        ((uint16_t)0x0020)            /*!<COM interrupt Flag                 */
#define  TMR_SR_TIF                          ((uint16_t)0x0040)            /*!<Trigger interrupt Flag             */
#define  TMR_SR_BIF                          ((uint16_t)0x0080)            /*!<Break interrupt Flag               */
#define  TMR_SR_CC1OF                        ((uint16_t)0x0200)            /*!<Capture/Compare 1 Overcapture Flag */
#define  TMR_SR_CC2OF                        ((uint16_t)0x0400)            /*!<Capture/Compare 2 Overcapture Flag */
#define  TMR_SR_CC3OF                        ((uint16_t)0x0800)            /*!<Capture/Compare 3 Overcapture Flag */
#define  TMR_SR_CC4OF                        ((uint16_t)0x1000)            /*!<Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TMR_EGR register  ********************/
#define  TMR_EGR_UG                          ((uint8_t)0x01)               /*!<Update Generation                         */
#define  TMR_EGR_CC1G                        ((uint8_t)0x02)               /*!<Capture/Compare 1 Generation              */
#define  TMR_EGR_CC2G                        ((uint8_t)0x04)               /*!<Capture/Compare 2 Generation              */
#define  TMR_EGR_CC3G                        ((uint8_t)0x08)               /*!<Capture/Compare 3 Generation              */
#define  TMR_EGR_CC4G                        ((uint8_t)0x10)               /*!<Capture/Compare 4 Generation              */
#define  TMR_EGR_COMG                        ((uint8_t)0x20)               /*!<Capture/Compare Control Update Generation */
#define  TMR_EGR_TG                          ((uint8_t)0x40)               /*!<Trigger Generation                        */
#define  TMR_EGR_BG                          ((uint8_t)0x80)               /*!<Break Generation                          */

/******************  Bit definition for TMR_CCMR1 register  *******************/
#define  TMR_CCMR1_CC1S                      ((uint16_t)0x0003)            /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TMR_CCMR1_CC1S_0                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TMR_CCMR1_CC1S_1                    ((uint16_t)0x0002)            /*!<Bit 1 */

#define  TMR_CCMR1_OC1FE                     ((uint16_t)0x0004)            /*!<Output Compare 1 Fast enable                 */
#define  TMR_CCMR1_OC1PE                     ((uint16_t)0x0008)            /*!<Output Compare 1 Preload enable              */

#define  TMR_CCMR1_OC1M                      ((uint16_t)0x0070)            /*!<OC1M[2:0] bits (Output Compare 1 Mode)       */
#define  TMR_CCMR1_OC1M_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TMR_CCMR1_OC1M_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TMR_CCMR1_OC1M_2                    ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TMR_CCMR1_OC1CE                     ((uint16_t)0x0080)            /*!<Output Compare 1Clear Enable                 */

#define  TMR_CCMR1_CC2S                      ((uint16_t)0x0300)            /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TMR_CCMR1_CC2S_0                    ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TMR_CCMR1_CC2S_1                    ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TMR_CCMR1_OC2FE                     ((uint16_t)0x0400)            /*!<Output Compare 2 Fast enable                 */
#define  TMR_CCMR1_OC2PE                     ((uint16_t)0x0800)            /*!<Output Compare 2 Preload enable              */

#define  TMR_CCMR1_OC2M                      ((uint16_t)0x7000)            /*!<OC2M[2:0] bits (Output Compare 2 Mode)       */
#define  TMR_CCMR1_OC2M_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TMR_CCMR1_OC2M_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TMR_CCMR1_OC2M_2                    ((uint16_t)0x4000)            /*!<Bit 2 */

#define  TMR_CCMR1_OC2CE                     ((uint16_t)0x8000)            /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TMR_CCMR1_IC1PSC                    ((uint16_t)0x000C)            /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TMR_CCMR1_IC1PSC_0                  ((uint16_t)0x0004)            /*!<Bit 0 */
#define  TMR_CCMR1_IC1PSC_1                  ((uint16_t)0x0008)            /*!<Bit 1 */

#define  TMR_CCMR1_IC1F                      ((uint16_t)0x00F0)            /*!<IC1F[3:0] bits (Input Capture 1 Filter)      */
#define  TMR_CCMR1_IC1F_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TMR_CCMR1_IC1F_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TMR_CCMR1_IC1F_2                    ((uint16_t)0x0040)            /*!<Bit 2 */
#define  TMR_CCMR1_IC1F_3                    ((uint16_t)0x0080)            /*!<Bit 3 */

#define  TMR_CCMR1_IC2PSC                    ((uint16_t)0x0C00)            /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler)  */
#define  TMR_CCMR1_IC2PSC_0                  ((uint16_t)0x0400)            /*!<Bit 0 */
#define  TMR_CCMR1_IC2PSC_1                  ((uint16_t)0x0800)            /*!<Bit 1 */

#define  TMR_CCMR1_IC2F                      ((uint16_t)0xF000)            /*!<IC2F[3:0] bits (Input Capture 2 Filter)       */
#define  TMR_CCMR1_IC2F_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TMR_CCMR1_IC2F_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TMR_CCMR1_IC2F_2                    ((uint16_t)0x4000)            /*!<Bit 2 */
#define  TMR_CCMR1_IC2F_3                    ((uint16_t)0x8000)            /*!<Bit 3 */

/******************  Bit definition for TMR_CCMR2 register  *******************/
#define  TMR_CCMR2_CC3S                      ((uint16_t)0x0003)            /*!<CC3S[1:0] bits (Capture/Compare 3 Selection)  */
#define  TMR_CCMR2_CC3S_0                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TMR_CCMR2_CC3S_1                    ((uint16_t)0x0002)            /*!<Bit 1 */

#define  TMR_CCMR2_OC3FE                     ((uint16_t)0x0004)            /*!<Output Compare 3 Fast enable           */
#define  TMR_CCMR2_OC3PE                     ((uint16_t)0x0008)            /*!<Output Compare 3 Preload enable        */

#define  TMR_CCMR2_OC3M                      ((uint16_t)0x0070)            /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TMR_CCMR2_OC3M_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TMR_CCMR2_OC3M_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TMR_CCMR2_OC3M_2                    ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TMR_CCMR2_OC3CE                     ((uint16_t)0x0080)            /*!<Output Compare 3 Clear Enable */

#define  TMR_CCMR2_CC4S                      ((uint16_t)0x0300)            /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TMR_CCMR2_CC4S_0                    ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TMR_CCMR2_CC4S_1                    ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TMR_CCMR2_OC4FE                     ((uint16_t)0x0400)            /*!<Output Compare 4 Fast enable    */
#define  TMR_CCMR2_OC4PE                     ((uint16_t)0x0800)            /*!<Output Compare 4 Preload enable */

#define  TMR_CCMR2_OC4M                      ((uint16_t)0x7000)            /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TMR_CCMR2_OC4M_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TMR_CCMR2_OC4M_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TMR_CCMR2_OC4M_2                    ((uint16_t)0x4000)            /*!<Bit 2 */

#define  TMR_CCMR2_OC4CE                     ((uint16_t)0x8000)            /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TMR_CCMR2_IC3PSC                    ((uint16_t)0x000C)            /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TMR_CCMR2_IC3PSC_0                  ((uint16_t)0x0004)            /*!<Bit 0 */
#define  TMR_CCMR2_IC3PSC_1                  ((uint16_t)0x0008)            /*!<Bit 1 */

#define  TMR_CCMR2_IC3F                      ((uint16_t)0x00F0)            /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TMR_CCMR2_IC3F_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TMR_CCMR2_IC3F_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TMR_CCMR2_IC3F_2                    ((uint16_t)0x0040)            /*!<Bit 2 */
#define  TMR_CCMR2_IC3F_3                    ((uint16_t)0x0080)            /*!<Bit 3 */

#define  TMR_CCMR2_IC4PSC                    ((uint16_t)0x0C00)            /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TMR_CCMR2_IC4PSC_0                  ((uint16_t)0x0400)            /*!<Bit 0 */
#define  TMR_CCMR2_IC4PSC_1                  ((uint16_t)0x0800)            /*!<Bit 1 */

#define  TMR_CCMR2_IC4F                      ((uint16_t)0xF000)            /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TMR_CCMR2_IC4F_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TMR_CCMR2_IC4F_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TMR_CCMR2_IC4F_2                    ((uint16_t)0x4000)            /*!<Bit 2 */
#define  TMR_CCMR2_IC4F_3                    ((uint16_t)0x8000)            /*!<Bit 3 */

/*******************  Bit definition for TMR_CCER register  *******************/
#define  TMR_CCER_CC1E                       ((uint16_t)0x0001)            /*!<Capture/Compare 1 output enable                 */
#define  TMR_CCER_CC1P                       ((uint16_t)0x0002)            /*!<Capture/Compare 1 output Polarity               */
#define  TMR_CCER_CC1NE                      ((uint16_t)0x0004)            /*!<Capture/Compare 1 Complementary output enable   */
#define  TMR_CCER_CC1NP                      ((uint16_t)0x0008)            /*!<Capture/Compare 1 Complementary output Polarity */
#define  TMR_CCER_CC2E                       ((uint16_t)0x0010)            /*!<Capture/Compare 2 output enable                 */
#define  TMR_CCER_CC2P                       ((uint16_t)0x0020)            /*!<Capture/Compare 2 output Polarity               */
#define  TMR_CCER_CC2NE                      ((uint16_t)0x0040)            /*!<Capture/Compare 2 Complementary output enable   */
#define  TMR_CCER_CC2NP                      ((uint16_t)0x0080)            /*!<Capture/Compare 2 Complementary output Polarity */
#define  TMR_CCER_CC3E                       ((uint16_t)0x0100)            /*!<Capture/Compare 3 output enable                 */
#define  TMR_CCER_CC3P                       ((uint16_t)0x0200)            /*!<Capture/Compare 3 output Polarity               */
#define  TMR_CCER_CC3NE                      ((uint16_t)0x0400)            /*!<Capture/Compare 3 Complementary output enable   */
#define  TMR_CCER_CC3NP                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 Complementary output Polarity */
#define  TMR_CCER_CC4E                       ((uint16_t)0x1000)            /*!<Capture/Compare 4 output enable                 */
#define  TMR_CCER_CC4P                       ((uint16_t)0x2000)            /*!<Capture/Compare 4 output Polarity               */
#define  TMR_CCER_CC4NP                      ((uint16_t)0x8000)            /*!<Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TMR_CNT register  ********************/
#define  TMR_CNT_CNT                         ((uint16_t)0xFFFF)            /*!<Counter Value            */

/*******************  Bit definition for TMR_PSC register  ********************/
#define  TMR_PSC_PSC                         ((uint16_t)0xFFFF)            /*!<Prescaler Value          */

/*******************  Bit definition for TMR_ARR register  ********************/
#define  TMR_ARR_ARR                         ((uint16_t)0xFFFF)            /*!<actual auto-reload Value */

/*******************  Bit definition for TMR_RCR register  ********************/
#define  TMR_RCR_REP                         ((uint8_t)0xFF)               /*!<Repetition Counter Value */

/*******************  Bit definition for TMR_CCR1 register  *******************/
#define  TMR_CCR1_CCR1                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 1 Value  */

/*******************  Bit definition for TMR_CCR2 register  *******************/
#define  TMR_CCR2_CCR2                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 2 Value  */

/*******************  Bit definition for TMR_CCR3 register  *******************/
#define  TMR_CCR3_CCR3                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 3 Value  */

/*******************  Bit definition for TMR_CCR4 register  *******************/
#define  TMR_CCR4_CCR4                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 4 Value  */

/*******************  Bit definition for TMR_BDTR register  *******************/
#define  TMR_BDTR_DTG                        ((uint16_t)0x00FF)            /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TMR_BDTR_DTG_0                      ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TMR_BDTR_DTG_1                      ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TMR_BDTR_DTG_2                      ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TMR_BDTR_DTG_3                      ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TMR_BDTR_DTG_4                      ((uint16_t)0x0010)            /*!<Bit 4 */
#define  TMR_BDTR_DTG_5                      ((uint16_t)0x0020)            /*!<Bit 5 */
#define  TMR_BDTR_DTG_6                      ((uint16_t)0x0040)            /*!<Bit 6 */
#define  TMR_BDTR_DTG_7                      ((uint16_t)0x0080)            /*!<Bit 7 */

#define  TMR_BDTR_LOCK                       ((uint16_t)0x0300)            /*!<LOCK[1:0] bits (Lock Configuration) */
#define  TMR_BDTR_LOCK_0                     ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TMR_BDTR_LOCK_1                     ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TMR_BDTR_OSSI                       ((uint16_t)0x0400)            /*!<Off-State Selection for Idle mode */
#define  TMR_BDTR_OSSR                       ((uint16_t)0x0800)            /*!<Off-State Selection for Run mode  */
#define  TMR_BDTR_BKE                        ((uint16_t)0x1000)            /*!<Break enable                      */
#define  TMR_BDTR_BKP                        ((uint16_t)0x2000)            /*!<Break Polarity                    */
#define  TMR_BDTR_AOE                        ((uint16_t)0x4000)            /*!<Automatic Output enable           */
#define  TMR_BDTR_MOE                        ((uint16_t)0x8000)            /*!<Main Output enable                */

/*******************  Bit definition for TMR_DCR register  ********************/
#define  TMR_DCR_DBA                         ((uint16_t)0x001F)            /*!<DBA[4:0] bits (DMA Base Address) */
#define  TMR_DCR_DBA_0                       ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TMR_DCR_DBA_1                       ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TMR_DCR_DBA_2                       ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TMR_DCR_DBA_3                       ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TMR_DCR_DBA_4                       ((uint16_t)0x0010)            /*!<Bit 4 */

#define  TMR_DCR_DBL                         ((uint16_t)0x1F00)            /*!<DBL[4:0] bits (DMA Burst Length) */
#define  TMR_DCR_DBL_0                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TMR_DCR_DBL_1                       ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TMR_DCR_DBL_2                       ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TMR_DCR_DBL_3                       ((uint16_t)0x0800)            /*!<Bit 3 */
#define  TMR_DCR_DBL_4                       ((uint16_t)0x1000)            /*!<Bit 4 */

/*******************  Bit definition for TMR_DMAR register  *******************/
#define  TMR_DMAR_DMAB                       ((uint16_t)0xFFFF)            /*!<DMA register for burst accesses                    */

/*******************  Bit definition for TMR_OR register  *********************/
#define TMR_OR_TI4_RMP                       ((uint16_t)0x00C0)            /*!<TI4_RMP[1:0] bits (GTMR2 Input 4 remap)             */
#define TMR_OR_TI4_RMP_0                     ((uint16_t)0x0040)            /*!<Bit 0 */
#define TMR_OR_TI4_RMP_1                     ((uint16_t)0x0080)            /*!<Bit 1 */
#define TMR_OR_ITR1_RMP                      ((uint16_t)0x0C00)            /*!<ITR1_RMP[1:0] bits (ETMR1 Internal trigger 1 remap) */
#define TMR_OR_ITR1_RMP_0                    ((uint16_t)0x0400)            /*!<Bit 0 */
#define TMR_OR_ITR1_RMP_1                    ((uint16_t)0x0800)            /*!<Bit 1 */




/* ---------------------- TMR registers bit mask ------------------------ */
#define SMCR_ETR_Mask               ((uint16_t)0x00FF) 
#define CCMR_Offset                 ((uint16_t)0x0018)
#define CCER_CCE_Set                ((uint16_t)0x0001)  
#define	CCER_CCNE_Set               ((uint16_t)0x0004) 

/**
  * @}
  */



/** @defgroup TMR_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR_Private_Variables
  * @{
  */

/**
  * @}
  */


/** @defgroup TMR_Private_FunctionPrototypes
  * @{
  */

static void TI1_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter);
static void TI2_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter);
static void TI3_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter);
static void TI4_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter);
/**
  * @}
  */


/** @defgroup TMR_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TMRx peripheral registers to their default reset values.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @retval None
  */
void TMR_DeInit(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));

  if (TMRx == ETMR0)
  {
    SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_ETMR0);
  }
  else if (TMRx == ETMR1)
  {
    SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_ETMR1);
  }
  else if (TMRx == GTMR0)
  {
    SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_GTMR0);
  }
  else if (TMRx == GTMR1)
  {
    SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_GTMR1);
  }
  else if (TMRx == GTMR2)
  {
    SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_GTMR2);
  }
  else if (TMRx == GTMR3)
  {
    SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_GTMR3);
  }
}

/**
  * @brief  Initializes the TMRx Time Base Unit peripheral according to
  *         the specified parameters in the TMR_TimeBaseInitStruct.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_TimeBaseInitStruct: pointer to a TMR_TimeBaseInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  *         This parameter can be any combination of the following values:
  *             TMR_Prescaler: 0x0000~0xFFFF
  *             TMR_CounterMode:
  *                 TMR_CounterMode_Up
  *                 TMR_CounterMode_Down
  *                 TMR_CounterMode_CenterAligned1
  *                 TMR_CounterMode_CenterAligned2
  *                 TMR_CounterMode_CenterAligned3
  *             TMR_Period: 0x0000~0xFFFF
  *             TMR_ClockDivision:
  *                 TMR_CKD_DIV1
  *                 TMR_CKD_DIV2
  *                 TMR_CKD_DIV4
  *             TMR_RepetitionCounter: 0x00~0xFF
  * @retval None
  */
void TMR_TimeBaseInit(TMR_Type* TMRx, TMR_TimeBaseInitType* TMR_TimeBaseInitStruct)
{
  uint16_t tmpcr1 = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_COUNTER_MODE(TMR_TimeBaseInitStruct->TMR_CounterMode));
  assert_parameters(IS_TMR_CKD_DIV(TMR_TimeBaseInitStruct->TMR_ClockDivision));

  tmpcr1 = TMRx->CR1;

  /* Select the Counter Mode */
  tmpcr1 &= (uint16_t)(~(TMR_CR1_DIR | TMR_CR1_CMS));
  tmpcr1 |= (uint32_t)TMR_TimeBaseInitStruct->TMR_CounterMode;

  /* Set the clock division */
  tmpcr1 &=  (uint16_t)(~TMR_CR1_CKD);
  tmpcr1 |= (uint32_t)TMR_TimeBaseInitStruct->TMR_ClockDivision;

  TMRx->CR1 = tmpcr1;

  /* Set the Autoreload value */
  TMRx->ARR = TMR_TimeBaseInitStruct->TMR_Period ;

  /* Set the Prescaler value */
  TMRx->PSC = TMR_TimeBaseInitStruct->TMR_Prescaler;

  if ((TMRx == ETMR0) || (TMRx == ETMR1))
  {
    /* Set the Repetition Counter value */
    TMRx->RCR = TMR_TimeBaseInitStruct->TMR_RepetitionCounter;
  }

  /* Generate an update event to reload the Prescaler
     and the repetition counter(only for ETMR0 and ETMR1) value immediately */
  TMRx->EGR = TMR_PSCReloadMode_Immediate;
}

/**
  * @brief  Fills each TMR_TimeBaseInitStruct member with its default value.
  * @param  TMR_TimeBaseInitStruct : pointer to a TMR_TimeBaseInitTypeDef
  *         structure which will be initialized.
  * @retval None
  */
void TMR_TimeBaseStructInit(TMR_TimeBaseInitType* TMR_TimeBaseInitStruct)
{
  /* Set the default configuration */
  TMR_TimeBaseInitStruct->TMR_Period = 0xFFFF;
  TMR_TimeBaseInitStruct->TMR_Prescaler = 0x0000;
  TMR_TimeBaseInitStruct->TMR_ClockDivision = TMR_CKD_DIV1;
  TMR_TimeBaseInitStruct->TMR_CounterMode = TMR_CounterMode_Up;
  TMR_TimeBaseInitStruct->TMR_RepetitionCounter = 0x0000;
}
/**
  * @brief  Fills each TMR_OCInitStruct member with its default value.
  * @param  TMR_OCInitStruct : pointer to a TMR_OCInitType structure which will
  *         be initialized.
  * @retval None
  */
void TMR_OCStructInit(TMR_OCInitType* TMR_OCInitStruct)
{
  /* Set the default configuration */
  TMR_OCInitStruct->TMR_OCMode = TMR_OCMode_Timing;
  TMR_OCInitStruct->TMR_OutputState = TMR_OutputState_Disable;
  TMR_OCInitStruct->TMR_OutputNState = TMR_OutputNState_Disable;
  TMR_OCInitStruct->TMR_Pulse = 0x0000;
  TMR_OCInitStruct->TMR_OCPolarity = TMR_OCPolarity_High;
  TMR_OCInitStruct->TMR_OCNPolarity = TMR_OCPolarity_High;
  TMR_OCInitStruct->TMR_OCIdleState = TMR_OCIdleState_Reset;
  TMR_OCInitStruct->TMR_OCNIdleState = TMR_OCNIdleState_Reset;
}

/**
  * @brief  Fills each TMR_ICInitStruct member with its default value.
  * @param  TMR_ICInitStruct: pointer to a TMR_ICInitType structure which will
  *         be initialized.
  * @retval None
  */
void TMR_ICStructInit(TMR_ICInitType* TMR_ICInitStruct)
{
  /* Set the default configuration */
  TMR_ICInitStruct->TMR_Channel = TMR_Channel_1;
  TMR_ICInitStruct->TMR_ICPolarity = TMR_ICPolarity_Rising;
  TMR_ICInitStruct->TMR_ICSelection = TMR_ICSelection_DirectTI;
  TMR_ICInitStruct->TMR_ICPrescaler = TMR_ICPSC_DIV1;
  TMR_ICInitStruct->TMR_ICFilter = 0x00;
}

/**
  * @brief  Fills each TMR_BDTRInitStruct member with its default value.
  * @param  TMR_BDTRInitStruct: pointer to a TMR_BDTRInitType structure which
  *         will be initialized.
  * @retval None
  */
void TMR_BDTRStructInit(TMR_BDTRInitType* TMR_BDTRInitStruct)
{
  /* Set the default configuration */
  TMR_BDTRInitStruct->TMR_OSSRState = TMR_OSSRState_Disable;
  TMR_BDTRInitStruct->TMR_OSSIState = TMR_OSSIState_Disable;
  TMR_BDTRInitStruct->TMR_LOCKLevel = TMR_LOCKLevel_OFF;
  TMR_BDTRInitStruct->TMR_DeadTime = 0x00;
  TMR_BDTRInitStruct->TMR_Break = TMR_Break_Disable;
  TMR_BDTRInitStruct->TMR_BreakPolarity = TMR_BreakPolarity_Low;
  TMR_BDTRInitStruct->TMR_AutomaticOutput = TMR_AutomaticOutput_Disable;
}

/**
  * @brief  Initializes the TMRx Channel1 according to the specified
  *         parameters in the TMR_OCInitStruct.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCInitStruct: pointer to a TMR_OCInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  *         This parameter can be any combination of the following values:
  *             TMR_OCMode:
  *                 TMR_OCMode_Timing
  *                 TMR_OCMode_Active
  *                 TMR_OCMode_Inactive
  *                 TMR_OCMode_Toggle
  *                 TMR_ForcedAction_InActive
  *                 TMR_ForcedAction_Active
  *                 TMR_OCMode_PWM1
  *                 TMR_OCMode_PWM2
  *             TMR_OutputState:
  *                 TMR_OutputState_Disable
  *                 TMR_OutputState_Enable
  *             TMR_OutputNState:
  *                 TMR_OutputNState_Disable
  *                 TMR_OutputNState_Enable
  *             TMR_Pulse: 0x0000~0xFFFF
  *             TMR_OCPolarity:
  *                 TMR_OCPolarity_High
  *                 TMR_OCPolarity_Low
  *             TMR_OCNPolarity:
  *                 TMR_OCNPolarity_High
  *                 TMR_OCNPolarity_Low
  *             TMR_OCIdleState:
  *                 TMR_OCIdleState_Set
  *                 TMR_OCIdleState_Reset
  *             TMR_OCNIdleState:
  *                 TMR_OCNIdleState_Set
  *                 TMR_OCNIdleState_Reset
  * @retval None
  */
void TMR_OC1Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OC_MODE(TMR_OCInitStruct->TMR_OCMode));
  assert_parameters(IS_TMR_OUTPUT_STATE(TMR_OCInitStruct->TMR_OutputState));
  assert_parameters(IS_TMR_OC_POLARITY(TMR_OCInitStruct->TMR_OCPolarity));
  /* Disable the Channel 1: Reset the CC1E Bit */
  TMRx->CCER &= (uint16_t)(~(uint16_t)TMR_CCER_CC1E);
  /* Get the TMRx CCER register value */
  tmpccer = TMRx->CCER;
  /* Get the TMRx CR2 register value */
  tmpcr2 =  TMRx->CR2;

  /* Get the TMRx CCMR1 register value */
  tmpccmrx = TMRx->CCMR1;

  /* Reset the Output Compare Mode Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCMR1_OC1M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCMR1_CC1S));

  /* Select the Output Compare Mode */
  tmpccmrx |= TMR_OCInitStruct->TMR_OCMode;

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC1P));
  /* Set the Output Compare Polarity */
  tmpccer |= TMR_OCInitStruct->TMR_OCPolarity;

  /* Set the Output State */
  tmpccer |= TMR_OCInitStruct->TMR_OutputState;

  if((TMRx == ETMR0) || (TMRx == ETMR1))
  {
    assert_parameters(IS_TMR_OUTPUTN_STATE(TMR_OCInitStruct->TMR_OutputNState));
    assert_parameters(IS_TMR_OCN_POLARITY(TMR_OCInitStruct->TMR_OCNPolarity));
    assert_parameters(IS_TMR_OCNIDLE_STATE(TMR_OCInitStruct->TMR_OCNIdleState));
    assert_parameters(IS_TMR_OCIDLE_STATE(TMR_OCInitStruct->TMR_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC1NP));
    /* Set the Output N Polarity */
    tmpccer |= TMR_OCInitStruct->TMR_OCNPolarity;

    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC1NE));
    /* Set the Output N State */
    tmpccer |= TMR_OCInitStruct->TMR_OutputNState;

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CR2_OIS1));
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CR2_OIS1N));

    /* Set the Output Idle state */
    tmpcr2 |= TMR_OCInitStruct->TMR_OCIdleState;
    /* Set the Output N Idle state */
    tmpcr2 |= TMR_OCInitStruct->TMR_OCNIdleState;
  }
  /* Write to TMRx CR2 */
  TMRx->CR2 = tmpcr2;

  /* Write to TMRx CCMR1 */
  TMRx->CCMR1 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TMRx->CCR1 = TMR_OCInitStruct->TMR_Pulse;

  /* Write to TMRx CCER */
  TMRx->CCER = tmpccer;
}


/**
  * @brief  Initializes the TMRx Channel2 according to the specified
  *         parameters in the TMR_OCInitStruct.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCInitStruct: pointer to a TMR_OCInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  *         This parameter can be any combination of the following values:
  *             TMR_OCMode:
  *                 TMR_OCMode_Timing
  *                 TMR_OCMode_Active
  *                 TMR_OCMode_Inactive
  *                 TMR_OCMode_Toggle
  *                 TMR_ForcedAction_InActive
  *                 TMR_ForcedAction_Active
  *                 TMR_OCMode_PWM1
  *                 TMR_OCMode_PWM2
  *             TMR_OutputState:
  *                 TMR_OutputState_Disable
  *                 TMR_OutputState_Enable
  *             TMR_OutputNState:
  *                 TMR_OutputNState_Disable
  *                 TMR_OutputNState_Enable
  *             TMR_Pulse: 0x0000~0xFFFF
  *             TMR_OCPolarity:
  *                 TMR_OCPolarity_High
  *                 TMR_OCPolarity_Low
  *             TMR_OCNPolarity:
  *                 TMR_OCNPolarity_High
  *                 TMR_OCNPolarity_Low
  *             TMR_OCIdleState:
  *                 TMR_OCIdleState_Set
  *                 TMR_OCIdleState_Reset
  *             TMR_OCNIdleState:
  *                 TMR_OCNIdleState_Set
  *                 TMR_OCNIdleState_Reset
  * @retval None
  */
void TMR_OC2Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OC_MODE(TMR_OCInitStruct->TMR_OCMode));
  assert_parameters(IS_TMR_OUTPUT_STATE(TMR_OCInitStruct->TMR_OutputState));
  assert_parameters(IS_TMR_OC_POLARITY(TMR_OCInitStruct->TMR_OCPolarity));
   /* Disable the Channel 2: Reset the CC2E Bit */
  TMRx->CCER &= (uint16_t)(~((uint16_t)TMR_CCER_CC2E));

  /* Get the TMRx CCER register value */
  tmpccer = TMRx->CCER;
  /* Get the TMRx CR2 register value */
  tmpcr2 =  TMRx->CR2;

  /* Get the TMRx CCMR1 register value */
  tmpccmrx = TMRx->CCMR1;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCMR1_OC2M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCMR1_CC2S));

  /* Select the Output Compare Mode */
  tmpccmrx |= (uint16_t)(TMR_OCInitStruct->TMR_OCMode << 8);

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC2P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCPolarity << 4);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputState << 4);

  if((TMRx == ETMR0) || (TMRx == ETMR1))
  {
    assert_parameters(IS_TMR_OUTPUTN_STATE(TMR_OCInitStruct->TMR_OutputNState));
    assert_parameters(IS_TMR_OCN_POLARITY(TMR_OCInitStruct->TMR_OCNPolarity));
    assert_parameters(IS_TMR_OCNIDLE_STATE(TMR_OCInitStruct->TMR_OCNIdleState));
    assert_parameters(IS_TMR_OCIDLE_STATE(TMR_OCInitStruct->TMR_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC2NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCNPolarity << 4);

    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC2NE));
    /* Set the Output N State */
    tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputNState << 4);

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CR2_OIS2));
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CR2_OIS2N));

    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCIdleState << 2);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCNIdleState << 2);
  }
  /* Write to TMRx CR2 */
  TMRx->CR2 = tmpcr2;

  /* Write to TMRx CCMR1 */
  TMRx->CCMR1 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TMRx->CCR2 = TMR_OCInitStruct->TMR_Pulse;

  /* Write to TMRx CCER */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TMRx Channel3 according to the specified
  *         parameters in the TMR_OCInitStruct.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCInitStruct: pointer to a TMR_OCInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  *         This parameter can be any combination of the following values:
  *             TMR_OCMode:
  *                 TMR_OCMode_Timing
  *                 TMR_OCMode_Active
  *                 TMR_OCMode_Inactive
  *                 TMR_OCMode_Toggle
  *                 TMR_ForcedAction_InActive
  *                 TMR_ForcedAction_Active
  *                 TMR_OCMode_PWM1
  *                 TMR_OCMode_PWM2
  *             TMR_OutputState:
  *                 TMR_OutputState_Disable
  *                 TMR_OutputState_Enable
  *             TMR_OutputNState:
  *                 TMR_OutputNState_Disable
  *                 TMR_OutputNState_Enable
  *             TMR_Pulse: 0x0000~0xFFFF
  *             TMR_OCPolarity:
  *                 TMR_OCPolarity_High
  *                 TMR_OCPolarity_Low
  *             TMR_OCNPolarity:
  *                 TMR_OCNPolarity_High
  *                 TMR_OCNPolarity_Low
  *             TMR_OCIdleState:
  *                 TMR_OCIdleState_Set
  *                 TMR_OCIdleState_Reset
  *             TMR_OCNIdleState:
  *                 TMR_OCNIdleState_Set
  *                 TMR_OCNIdleState_Reset
  * @retval None
  */
void TMR_OC3Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OC_MODE(TMR_OCInitStruct->TMR_OCMode));
  assert_parameters(IS_TMR_OUTPUT_STATE(TMR_OCInitStruct->TMR_OutputState));
  assert_parameters(IS_TMR_OC_POLARITY(TMR_OCInitStruct->TMR_OCPolarity));
  /* Disable the Channel 2: Reset the CC2E Bit */
  TMRx->CCER &= (uint16_t)(~((uint16_t)TMR_CCER_CC3E));

  /* Get the TMRx CCER register value */
  tmpccer = TMRx->CCER;
  /* Get the TMRx CR2 register value */
  tmpcr2 =  TMRx->CR2;

  /* Get the TMRx CCMR2 register value */
  tmpccmrx = TMRx->CCMR2;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCMR2_OC3M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCMR2_CC3S));
  /* Select the Output Compare Mode */
  tmpccmrx |= TMR_OCInitStruct->TMR_OCMode;

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC3P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCPolarity << 8);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputState << 8);

  if((TMRx == ETMR0) || (TMRx == ETMR1))
  {
    assert_parameters(IS_TMR_OUTPUTN_STATE(TMR_OCInitStruct->TMR_OutputNState));
    assert_parameters(IS_TMR_OCN_POLARITY(TMR_OCInitStruct->TMR_OCNPolarity));
    assert_parameters(IS_TMR_OCNIDLE_STATE(TMR_OCInitStruct->TMR_OCNIdleState));
    assert_parameters(IS_TMR_OCIDLE_STATE(TMR_OCInitStruct->TMR_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC3NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCNPolarity << 8);
    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC3NE));

    /* Set the Output N State */
    tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputNState << 8);
    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CR2_OIS3));
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CR2_OIS3N));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCIdleState << 4);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCNIdleState << 4);
  }
  /* Write to TMRx CR2 */
  TMRx->CR2 = tmpcr2;

  /* Write to TMRx CCMR2 */
  TMRx->CCMR2 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TMRx->CCR3 = TMR_OCInitStruct->TMR_Pulse;

  /* Write to TMRx CCER */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TMRx Channel4 according to the specified
  *         parameters in the TMR_OCInitStruct.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCInitStruct: pointer to a TMR_OCInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  *         This parameter can be any combination of the following values:
  *             TMR_OCMode:
  *                 TMR_OCMode_Timing
  *                 TMR_OCMode_Active
  *                 TMR_OCMode_Inactive
  *                 TMR_OCMode_Toggle
  *                 TMR_ForcedAction_InActive
  *                 TMR_ForcedAction_Active
  *                 TMR_OCMode_PWM1
  *                 TMR_OCMode_PWM2
  *             TMR_OutputState:
  *                 TMR_OutputState_Disable
  *                 TMR_OutputState_Enable
  *             TMR_OutputNState:
  *                 TMR_OutputNState_Disable
  *                 TMR_OutputNState_Enable
  *             TMR_Pulse: 0x0000~0xFFFF
  *             TMR_OCPolarity:
  *                 TMR_OCPolarity_High
  *                 TMR_OCPolarity_Low
  *             TMR_OCNPolarity:
  *                 TMR_OCNPolarity_High
  *                 TMR_OCNPolarity_Low
  *             TMR_OCIdleState:
  *                 TMR_OCIdleState_Set
  *                 TMR_OCIdleState_Reset
  *             TMR_OCNIdleState:
  *                 TMR_OCNIdleState_Set
  *                 TMR_OCNIdleState_Reset
  * @retval None
  */
void TMR_OC4Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OC_MODE(TMR_OCInitStruct->TMR_OCMode));
  assert_parameters(IS_TMR_OUTPUT_STATE(TMR_OCInitStruct->TMR_OutputState));
  assert_parameters(IS_TMR_OC_POLARITY(TMR_OCInitStruct->TMR_OCPolarity));
  /* Disable the Channel 2: Reset the CC4E Bit */
  TMRx->CCER &= (uint16_t)(~((uint16_t)TMR_CCER_CC4E));

  /* Get the TMRx CCER register value */
  tmpccer = TMRx->CCER;
  /* Get the TMRx CR2 register value */
  tmpcr2 =  TMRx->CR2;

  /* Get the TMRx CCMR2 register value */
  tmpccmrx = TMRx->CCMR2;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCMR2_OC4M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCMR2_CC4S));

  /* Select the Output Compare Mode */
  tmpccmrx |= (uint16_t)(TMR_OCInitStruct->TMR_OCMode << 8);

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TMR_CCER_CC4P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCPolarity << 12);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputState << 12);

  if((TMRx == ETMR0) || (TMRx == ETMR1))
  {
    assert_parameters(IS_TMR_OCIDLE_STATE(TMR_OCInitStruct->TMR_OCIdleState));
    /* Reset the Output Compare IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CR2_OIS4));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCIdleState << 6);
  }
  /* Write to TMRx CR2 */
  TMRx->CR2 = tmpcr2;

  /* Write to TMRx CCMR2 */
  TMRx->CCMR2 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TMRx->CCR4 = TMR_OCInitStruct->TMR_Pulse;

  /* Write to TMRx CCER */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TMR peripheral according to the specified
  *         parameters in the TMR_ICInitStruct.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICInitStruct: pointer to a TMR_ICInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  *         This parameter can be any combination of the following values:
  *             TMR_Channel:
  *                 TMR_Channel_1
  *                 TMR_Channel_2
  *                 TMR_Channel_3
  *                 TMR_Channel_4
  *             TMR_ICPolarity:
  *                 TMR_ICPolarity_Rising
  *                 TMR_ICPolarity_Falling
  *                 TMR_ICPolarity_BothEdge
  *             TMR_ICSelection:
  *                 TMR_ICSelection_DirectTI
  *                 TMR_ICSelection_IndirectTI
  *                 TMR_ICSelection_TRC
  *             TMR_ICPrescaler:
  *                 TMR_ICPSC_DIV1
  *                 TMR_ICPSC_DIV2
  *                 TMR_ICPSC_DIV4
  *                 TMR_ICPSC_DIV8
  *             TMR_ICFilter: 0x0~0xF
  * @retval None
  */
void TMR_ICInit(TMR_Type* TMRx, TMR_ICInitType* TMR_ICInitStruct)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_CHANNEL(TMR_ICInitStruct->TMR_Channel));
  assert_parameters(IS_TMR_IC_SELECTION(TMR_ICInitStruct->TMR_ICSelection));
  assert_parameters(IS_TMR_IC_PRESCALER(TMR_ICInitStruct->TMR_ICPrescaler));
  assert_parameters(IS_TMR_IC_FILTER(TMR_ICInitStruct->TMR_ICFilter));
  assert_parameters(IS_TMR_IC_POLARITY(TMR_ICInitStruct->TMR_ICPolarity));

  if (TMR_ICInitStruct->TMR_Channel == TMR_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity,
               TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC1Prescaler(TMRx, TMR_ICInitStruct->TMR_ICPrescaler);
  }
  else if (TMR_ICInitStruct->TMR_Channel == TMR_Channel_2)
  {
    /* TI2 Configuration */
    TI2_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity,
               TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC2Prescaler(TMRx, TMR_ICInitStruct->TMR_ICPrescaler);
  }
  else if (TMR_ICInitStruct->TMR_Channel == TMR_Channel_3)
  {
    /* TI3 Configuration */
    TI3_Config(TMRx,  TMR_ICInitStruct->TMR_ICPolarity,
               TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC3Prescaler(TMRx, TMR_ICInitStruct->TMR_ICPrescaler);
  }
  else
  {
    /* TI4 Configuration */
    TI4_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity,
               TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC4Prescaler(TMRx, TMR_ICInitStruct->TMR_ICPrescaler);
  }
}


/**
  * @brief  Configures the TMR peripheral according to the specified
  *         parameters in the TMR_ICInitStruct to measure an external PWM signal.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICInitStruct: pointer to a TMR_ICInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  *         This parameter can be any combination of the following values:
  *             TMR_Channel:
  *                 TMR_Channel_1
  *                 TMR_Channel_2
  *                 TMR_Channel_3
  *                 TMR_Channel_4
  *             TMR_ICPolarity:
  *                 TMR_ICPolarity_Rising
  *                 TMR_ICPolarity_Falling
  *                 TMR_ICPolarity_BothEdge
  *             TMR_ICSelection:
  *                 TMR_ICSelection_DirectTI
  *                 TMR_ICSelection_IndirectTI
  *                 TMR_ICSelection_TRC
  *             TMR_ICPrescaler:
  *                 TMR_ICPSC_DIV1
  *                 TMR_ICPSC_DIV2
  *                 TMR_ICPSC_DIV4
  *                 TMR_ICPSC_DIV8
  *             TMR_ICFilter: 0x0~0xF
  * @retval None
  */
void TMR_PWMIConfig(TMR_Type* TMRx, TMR_ICInitType* TMR_ICInitStruct)
{
  uint16_t icoppositepolarity = TMR_ICPolarity_Rising;
  uint16_t icoppositeselection = TMR_ICSelection_DirectTI;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  /* Select the Opposite Input Polarity */
  if (TMR_ICInitStruct->TMR_ICPolarity == TMR_ICPolarity_Rising)
  {
    icoppositepolarity = TMR_ICPolarity_Falling;
  }
  else
  {
    icoppositepolarity = TMR_ICPolarity_Rising;
  }
  /* Select the Opposite Input */
  if (TMR_ICInitStruct->TMR_ICSelection == TMR_ICSelection_DirectTI)
  {
    icoppositeselection = TMR_ICSelection_IndirectTI;
  }
  else
  {
    icoppositeselection = TMR_ICSelection_DirectTI;
  }
  if (TMR_ICInitStruct->TMR_Channel == TMR_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity, TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC1Prescaler(TMRx, TMR_ICInitStruct->TMR_ICPrescaler);
    /* TI2 Configuration */
    TI2_Config(TMRx, icoppositepolarity, icoppositeselection, TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC2Prescaler(TMRx, TMR_ICInitStruct->TMR_ICPrescaler);
  }
  else
  {
    /* TI2 Configuration */
    TI2_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity, TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC2Prescaler(TMRx, TMR_ICInitStruct->TMR_ICPrescaler);
    /* TI1 Configuration */
    TI1_Config(TMRx, icoppositepolarity, icoppositeselection, TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC1Prescaler(TMRx, TMR_ICInitStruct->TMR_ICPrescaler);
  }
}

/**
  * @brief  Configures the: Break feature, dead time, Lock level, the OSSI,
  *         the OSSR State and the AOE(automatic output enable).
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_BDTRInitStruct: pointer to a TMR_BDTRInitType structure that
  *         contains the BDTR Register configuration  information for the TMR peripheral.
  *         This parameter can be any combination of the following values:
  *             TMR_OSSRState:
  *                 TMR_OSSRState_Enable
  *                 TMR_OSSRState_Disable
  *             TMR_OSSIState:
  *                 TMR_OSSIState_Enable
  *                 TMR_OSSIState_Disable
  *             TMR_LOCKLevel:
  *                 TMR_LOCKLevel_OFF
  *                 TMR_LOCKLevel_1
  *                 TMR_LOCKLevel_2
  *                 TMR_LOCKLevel_3
  *             TMR_DeadTime:
  *                 0x00~0xFF
  *             TMR_Break:
  *                 TMR_Break_Enable
  *                 TMR_Break_Disable
  *             TMR_BreakPolarity:
  *                 TMR_BreakPolarity_Low
  *                 TMR_BreakPolarity_High
  *             TMR_AutomaticOutput:
  *                 TMR_AutomaticOutput_Enable
  *                 TMR_AutomaticOutput_Disable
  * @retval None
  */
void TMR_BDTRConfig(TMR_Type* TMRx, TMR_BDTRInitType *TMR_BDTRInitStruct)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ENHANCED_PERIPH(TMRx));
  assert_parameters(IS_TMR_OSSR_STATE(TMR_BDTRInitStruct->TMR_OSSRState));
  assert_parameters(IS_TMR_OSSI_STATE(TMR_BDTRInitStruct->TMR_OSSIState));
  assert_parameters(IS_TMR_LOCK_LEVEL(TMR_BDTRInitStruct->TMR_LOCKLevel));
  assert_parameters(IS_TMR_BREAK_STATE(TMR_BDTRInitStruct->TMR_Break));
  assert_parameters(IS_TMR_BREAK_POLARITY(TMR_BDTRInitStruct->TMR_BreakPolarity));
  assert_parameters(IS_TMR_AUTOMATIC_OUTPUT_STATE(TMR_BDTRInitStruct->TMR_AutomaticOutput));

  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSR State,
     the OSSI State, the dead time value and the Automatic Output Enable Bit */
  TMRx->BDTR = (uint32_t)TMR_BDTRInitStruct->TMR_OSSRState | TMR_BDTRInitStruct->TMR_OSSIState |
             TMR_BDTRInitStruct->TMR_LOCKLevel | TMR_BDTRInitStruct->TMR_DeadTime |
             TMR_BDTRInitStruct->TMR_Break | TMR_BDTRInitStruct->TMR_BreakPolarity |
             TMR_BDTRInitStruct->TMR_AutomaticOutput;
}

/**
  * @brief  Enables or disables the specified TMR peripheral.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  NewState: new state of the TMRx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_Cmd(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TMR Counter */
    TMRx->CR1 |= TMR_CR1_CEN;
  }
  else
  {
    /* Disable the TMR Counter */
    TMRx->CR1 &= (uint16_t)(~((uint16_t)TMR_CR1_CEN));
  }
}

/**
  * @brief  Enables or disables the TMR peripheral Main Outputs.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  NewState: new state of the TMR peripheral Main Outputs.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_CtrlPWMOutputs(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ENHANCED_PERIPH(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the TMR Main Output */
    TMRx->BDTR |= TMR_BDTR_MOE;
  }
  else
  {
    /* Disable the TMR Main Output */
    TMRx->BDTR &= (uint16_t)(~((uint16_t)TMR_BDTR_MOE));
  }
}

/**
  * @brief  Enables or disables the specified TMR interrupts.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_IT: specifies the TMR interrupts sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *         @arg TMR_IT_Update: TMR update Interrupt source
  *         @arg TMR_IT_CC1: TMR Capture Compare 1 Interrupt source
  *         @arg TMR_IT_CC2: TMR Capture Compare 2 Interrupt source
  *         @arg TMR_IT_CC3: TMR Capture Compare 3 Interrupt source
  *         @arg TMR_IT_CC4: TMR Capture Compare 4 Interrupt source
  *         @arg TMR_IT_COM: TMR Commutation Interrupt source
  *         @arg TMR_IT_Trigger: TMR Trigger Interrupt source
  *         @arg TMR_IT_Break: TMR Break Interrupt source
  * @note
  *         TMR_IT_Break and TMR_IT_COM are used only with ETMR0 and ETMR1.
  * @param  NewState: new state of the TMR interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_ITConfig(TMR_Type* TMRx, uint16_t TMR_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_IT(TMR_IT));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TMRx->DIER |= TMR_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TMRx->DIER &= (uint16_t)~TMR_IT;
  }
}

/**
  * @brief  Configures the TMRx event to be generate by software.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_EventSource: specifies the event source.
  *         This parameter can be one or more of the following values:
  *         @arg TMR_EventSource_Update: Timer update Event source
  *         @arg TMR_EventSource_CC1: Timer Capture Compare 1 Event source
  *         @arg TMR_EventSource_CC2: Timer Capture Compare 2 Event source
  *         @arg TMR_EventSource_CC3: Timer Capture Compare 3 Event source
  *         @arg TMR_EventSource_CC4: Timer Capture Compare 4 Event source
  *         @arg TMR_EventSource_COM: Timer COM event source  
  *         @arg TMR_EventSource_Trigger: Timer Trigger Event source
  *         @arg TMR_EventSource_Break: Timer Break event source
  * @note
  *         TMR_EventSource_COM and TMR_EventSource_Break are used only with ETMR0 and ETMR1.
  * @retval None
  */
void TMR_GenerateEvent(TMR_Type* TMRx, uint16_t TMR_EventSource)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_EVENT_SOURCE(TMR_EventSource));

  /* Set the event sources */
  TMRx->EGR = TMR_EventSource;
}

/**
  * @brief  Enables or disables the TMRx's DMA Requests.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_DMASource: specifies the DMA Request sources.
  *         This parameter can be any combination of the following values:
  *         @arg TMR_DMA_Update: TMR update Interrupt source
  *         @arg TMR_DMA_CC1: TMR Capture Compare 1 DMA source
  *         @arg TMR_DMA_CC2: TMR Capture Compare 2 DMA source
  *         @arg TMR_DMA_CC3: TMR Capture Compare 3 DMA source
  *         @arg TMR_DMA_CC4: TMR Capture Compare 4 DMA source
  *         @arg TMR_DMA_COM: TMR Commutation DMA source
  *         @arg TMR_DMA_Trigger: TMR Trigger DMA source
  * @param  NewState: new state of the DMA Request sources.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_DMACmd(TMR_Type* TMRx, uint16_t TMR_DMASource, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_DMA_SOURCE(TMR_DMASource));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the DMA sources */
    TMRx->DIER |= TMR_DMASource;
  }
  else
  {
    /* Disable the DMA sources */
    TMRx->DIER &= (uint16_t)~TMR_DMASource;
  }
}


/**
  * @brief  Configures the TMRx internal Clock
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @retval None
  */
void TMR_InternalClockConfig(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TMRx->SMCR &=  (uint16_t)(~((uint16_t)TMR_SMCR_SMS));
}

/**
  * @brief  Configures the TMRx Internal Trigger as External Clock
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ITRSource: Trigger source.
  *         This parameter can be one of the following values:
  *         @arg TMR_TS_ITR0: Internal Trigger 0
  *         @arg TMR_TS_ITR1: Internal Trigger 1
  *         @arg TMR_TS_ITR2: Internal Trigger 2
  *         @arg TMR_TS_ITR3: Internal Trigger 3
  * @retval None
  */
void TMR_ITRxExternalClockConfig(TMR_Type* TMRx, uint16_t TMR_InputTriggerSource)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_INTERNAL_TRIGGER_SELECTION(TMR_InputTriggerSource));
  /* Select the Internal Trigger */
  TMR_SelectInputTrigger(TMRx, TMR_InputTriggerSource);
  /* Select the External clock mode1 */
  TMRx->SMCR |= TMR_SlaveMode_External1;
}

/**
  * @brief  Configures the TMRx Trigger as External Clock
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_TIxExternalCLKSource: Trigger source.
  *         This parameter can be one of the following values:
  *         @arg TMR_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
  *         @arg TMR_TIxExternalCLK1Source_TI1: Filtered Timer Input 1
  *         @arg TMR_TIxExternalCLK1Source_TI2: Filtered Timer Input 2
  * @param  TMR_ICPolarity: specifies the TIx Polarity.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICPolarity_Rising
  *         @arg TMR_ICPolarity_Falling
  * @param  ICFilter : specifies the filter value.
  *         This parameter must be a value between 0x0 and 0xF.
  * @retval None
  */
void TMR_TIxExternalClockConfig(TMR_Type* TMRx, uint16_t TMR_TIxExternalCLKSource, uint16_t TMR_ICPolarity, uint16_t ICFilter)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_TIXCLK_SOURCE(TMR_TIxExternalCLKSource));
  assert_parameters(IS_TMR_IC_POLARITY(TMR_ICPolarity));
  assert_parameters(IS_TMR_IC_FILTER(ICFilter));
  /* Configure the Timer Input Clock Source */
  if (TMR_TIxExternalCLKSource == TMR_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TMRx, TMR_ICPolarity, TMR_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TMRx, TMR_ICPolarity, TMR_ICSelection_DirectTI, ICFilter);
  }
  /* Select the Trigger source */
  TMR_SelectInputTrigger(TMRx, TMR_TIxExternalCLKSource);
  /* Select the External clock mode1 */
  TMRx->SMCR |= TMR_SlaveMode_External1;
}

/**
  * @brief  Configures the External clock Mode1
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ExtTRGPrescaler: The external Trigger Prescaler.
  *         This parameter can be one of the following values:
  *         @arg TMR_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *         @arg TMR_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *         @arg TMR_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *         @arg TMR_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TMR_ExtTRGPolarity: The external Trigger Polarity.
  *         This parameter can be one of the following values:
  *         @arg TMR_ExtTRGPolarity_Inverted: active low or falling edge active.
  *         @arg TMR_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *         This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TMR_ETRClockMode1Config(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_EXT_PRESCALER(TMR_ExtTRGPrescaler));
  assert_parameters(IS_TMR_EXT_POLARITY(TMR_ExtTRGPolarity));
  assert_parameters(IS_TMR_EXT_FILTER(ExtTRGFilter));
  /* Configure the ETR Clock source */
  TMR_ETRConfig(TMRx, TMR_ExtTRGPrescaler, TMR_ExtTRGPolarity, ExtTRGFilter);

  /* Get the TMRx SMCR register value */
  tmpsmcr = TMRx->SMCR;
  /* Reset the SMS Bits */
  tmpsmcr &= (uint16_t)(~((uint16_t)TMR_SMCR_SMS));
  /* Select the External clock mode1 */
  tmpsmcr |= TMR_SlaveMode_External1;
  /* Select the Trigger selection : ETRF */
  tmpsmcr &= (uint16_t)(~((uint16_t)TMR_SMCR_TS));
  tmpsmcr |= TMR_TS_ETRF;
  /* Write to TMRx SMCR */
  TMRx->SMCR = tmpsmcr;
}

/**
  * @brief  Configures the External clock Mode2
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ExtTRGPrescaler: The external Trigger Prescaler.
  *         This parameter can be one of the following values:
  *         @arg TMR_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *         @arg TMR_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *         @arg TMR_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *         @arg TMR_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TMR_ExtTRGPolarity: The external Trigger Polarity.
  *         This parameter can be one of the following values:
  *         @arg TMR_ExtTRGPolarity_Inverted: active low or falling edge active.
  *         @arg TMR_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *         This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TMR_ETRClockMode2Config(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_EXT_PRESCALER(TMR_ExtTRGPrescaler));
  assert_parameters(IS_TMR_EXT_POLARITY(TMR_ExtTRGPolarity));
  assert_parameters(IS_TMR_EXT_FILTER(ExtTRGFilter));
  /* Configure the ETR Clock source */
  TMR_ETRConfig(TMRx, TMR_ExtTRGPrescaler, TMR_ExtTRGPolarity, ExtTRGFilter);
  /* Enable the External clock mode2 */
  TMRx->SMCR |= TMR_SMCR_ECE;
}

/**
  * @brief  Configures the TMRx External Trigger (ETR).
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ExtTRGPrescaler: The external Trigger Prescaler.
  *         This parameter can be one of the following values:
  *         @arg TMR_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *         @arg TMR_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *         @arg TMR_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *         @arg TMR_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TMR_ExtTRGPolarity: The external Trigger Polarity.
  *         This parameter can be one of the following values:
  *         @arg TMR_ExtTRGPolarity_Inverted: active low or falling edge active.
  *         @arg TMR_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *         This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TMR_ETRConfig(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_EXT_PRESCALER(TMR_ExtTRGPrescaler));
  assert_parameters(IS_TMR_EXT_POLARITY(TMR_ExtTRGPolarity));
  assert_parameters(IS_TMR_EXT_FILTER(ExtTRGFilter));
  tmpsmcr = TMRx->SMCR;
  /* Reset the ETR Bits */
  tmpsmcr &= SMCR_ETR_Mask;
  /* Set the Prescaler, the Filter value and the Polarity */
  tmpsmcr |= (uint16_t)(TMR_ExtTRGPrescaler | (uint16_t)(TMR_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
  /* Write to TMRx SMCR */
  TMRx->SMCR = tmpsmcr;
}

/**
  * @brief  Configures the TMRx Prescaler.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  Prescaler: specifies the Prescaler Register value
  * @param  TMR_PSCReloadMode: specifies the TMR Prescaler Reload mode
  *         This parameter can be one of the following values:
  *         @arg TMR_PSCReloadMode_Update: The Prescaler is loaded at the update event.
  *         @arg TMR_PSCReloadMode_Immediate: The Prescaler is loaded immediately.
  * @retval None
  */
void TMR_PrescalerConfig(TMR_Type* TMRx, uint16_t Prescaler, uint16_t TMR_PSCReloadMode)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_PRESCALER_RELOAD(TMR_PSCReloadMode));
  /* Set the Prescaler value */
  TMRx->PSC = Prescaler;
  /* Set or reset the UG Bit */
  TMRx->EGR = TMR_PSCReloadMode;
}

/**
  * @brief  Specifies the TMRx Counter Mode to be used.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_CounterMode: specifies the Counter Mode to be used
  *         This parameter can be one of the following values:
  *         @arg TMR_CounterMode_Up: TIM Up Counting Mode
  *         @arg TMR_CounterMode_Down: TIM Down Counting Mode
  *         @arg TMR_CounterMode_CenterAligned1: TIM Center Aligned Mode1
  *         @arg TMR_CounterMode_CenterAligned2: TIM Center Aligned Mode2
  *         @arg TMR_CounterMode_CenterAligned3: TIM Center Aligned Mode3
  * @retval None
  */
void TMR_CounterModeConfig(TMR_Type* TMRx, uint16_t TMR_CounterMode)
{
  uint16_t tmpcr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_COUNTER_MODE(TMR_CounterMode));
  tmpcr1 = TMRx->CR1;
  /* Reset the CMS and DIR Bits */
  tmpcr1 &= (uint16_t)(~((uint16_t)(TMR_CR1_DIR | TMR_CR1_CMS)));
  /* Set the Counter Mode */
  tmpcr1 |= TMR_CounterMode;
  /* Write to TMRx CR1 register */
  TMRx->CR1 = tmpcr1;
}

/**
  * @brief  Selects the Input Trigger source
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_InputTriggerSource: The Input Trigger source.
  *         This parameter can be one of the following values:
  *         @arg TMR_TS_ITR0: Internal Trigger 0
  *         @arg TMR_TS_ITR1: Internal Trigger 1
  *         @arg TMR_TS_ITR2: Internal Trigger 2
  *         @arg TMR_TS_ITR3: Internal Trigger 3
  *         @arg TMR_TS_TI1F_ED: TI1 Edge Detector
  *         @arg TMR_TS_TI1FP1: Filtered Timer Input 1
  *         @arg TMR_TS_TI2FP2: Filtered Timer Input 2
  *         @arg TMR_TS_ETRF: External Trigger input
  * @retval None
  */
void TMR_SelectInputTrigger(TMR_Type* TMRx, uint16_t TMR_InputTriggerSource)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_TRIGGER_SELECTION(TMR_InputTriggerSource));
  /* Get the TMRx SMCR register value */
  tmpsmcr = TMRx->SMCR;
  /* Reset the TS Bits */
  tmpsmcr &= (uint16_t)(~((uint16_t)TMR_SMCR_TS));
  /* Set the Input Trigger source */
  tmpsmcr |= TMR_InputTriggerSource;
  /* Write to TMRx SMCR */
  TMRx->SMCR = tmpsmcr;
}

/**
  * @brief  Configures the TMRx Encoder Interface.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_EncoderMode: specifies the TMRx Encoder Mode.
  *         This parameter can be one of the following values:
  *         @arg TMR_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
  *         @arg TMR_EncoderMode_TI2: Counter counts on TI2FP2 edge depending on TI1FP1 level.
  *         @arg TMR_EncoderMode_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
  *                                    on the level of the other input.
  * @param  TMR_IC1Polarity: specifies the IC1 Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_ICPolarity_Falling: IC Falling edge.
  *         @arg TMR_ICPolarity_Rising: IC Rising edge.
  * @param  TMR_IC2Polarity: specifies the IC2 Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_ICPolarity_Falling: IC Falling edge.
  *         @arg TMR_ICPolarity_Rising: IC Rising edge.
  * @retval None
  */
void TMR_EncoderInterfaceConfig(TMR_Type* TMRx, uint16_t TMR_EncoderMode, uint16_t TMR_IC1Polarity, uint16_t TMR_IC2Polarity)
{
  uint16_t tmpsmcr = 0;
  uint16_t tmpccmr1 = 0;
  uint16_t tmpccer = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_ENCODER_MODE(TMR_EncoderMode));
  assert_parameters(IS_TMR_IC_POLARITY(TMR_IC1Polarity));
  assert_parameters(IS_TMR_IC_POLARITY(TMR_IC2Polarity));

  /* Get the TMRx SMCR register value */
  tmpsmcr = TMRx->SMCR;

  /* Get the TMRx CCMR1 register value */
  tmpccmr1 = TMRx->CCMR1;

  /* Get the TMRx CCER register value */
  tmpccer = TMRx->CCER;

  /* Set the encoder Mode */
  tmpsmcr &= (uint16_t)(~((uint16_t)TMR_SMCR_SMS));
  tmpsmcr |= TMR_EncoderMode;

  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCMR1_CC1S)) & (uint16_t)(~((uint16_t)TMR_CCMR1_CC2S)));
  tmpccmr1 |= TMR_CCMR1_CC1S_0 | TMR_CCMR1_CC2S_0;

  /* Set the TI1 and the TI2 Polarities */
  tmpccer &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCER_CC1P)) & ((uint16_t)~((uint16_t)TMR_CCER_CC2P)));
  tmpccer |= (uint16_t)(TMR_IC1Polarity | (uint16_t)(TMR_IC2Polarity << (uint16_t)4));

  /* Write to TMRx SMCR */
  TMRx->SMCR = tmpsmcr;
  /* Write to TMRx CCMR1 */
  TMRx->CCMR1 = tmpccmr1;
  /* Write to TMRx CCER */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Forces the TMRx output 1 waveform to active or inactive level.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ForcedAction: specifies the forced Action to be set to the output waveform.
  *         This parameter can be one of the following values:
  *         @arg TMR_ForcedAction_Active: Force active level on OC1REF
  *         @arg TMR_ForcedAction_InActive: Force inactive level on OC1REF.
  * @retval None
  */
void TMR_ForcedOC1Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_FORCED_ACTION(TMR_ForcedAction));

  tmpccmr1 = TMRx->CCMR1;
  /* Reset the OC1M Bits */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCMR1_OC1M);
  /* Configure The Forced output Mode */
  tmpccmr1 |= TMR_ForcedAction;
  /* Write to TMRx CCMR1 register */
  TMRx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the TMRx output 2 waveform to active or inactive level.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ForcedAction: specifies the forced Action to be set to the output waveform.
  *         This parameter can be one of the following values:
  *         @arg TMR_ForcedAction_Active: Force active level on OC2REF
  *         @arg TMR_ForcedAction_InActive: Force inactive level on OC2REF.
  * @retval None
  */
void TMR_ForcedOC2Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_FORCED_ACTION(TMR_ForcedAction));

  tmpccmr1 = TMRx->CCMR1;
  /* Reset the OC2M Bits */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCMR1_OC2M);
  /* Configure The Forced output Mode */
  tmpccmr1 |= (uint16_t)(TMR_ForcedAction << 8);
  /* Write to TMRx CCMR1 register */
  TMRx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the TMRx output 3 waveform to active or inactive level.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ForcedAction: specifies the forced Action to be set to the output waveform.
  *         This parameter can be one of the following values:
  *         @arg TMR_ForcedAction_Active: Force active level on OC3REF
  *         @arg TMR_ForcedAction_InActive: Force inactive level on OC3REF.
  * @retval None
  */
void TMR_ForcedOC3Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_FORCED_ACTION(TMR_ForcedAction));

  tmpccmr2 = TMRx->CCMR2;
  /* Reset the OC1M Bits */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCMR2_OC3M);
  /* Configure The Forced output Mode */
  tmpccmr2 |= TMR_ForcedAction;
  /* Write to TMRx CCMR2 register */
  TMRx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Forces the TMRx output 4 waveform to active or inactive level.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ForcedAction: specifies the forced Action to be set to the output waveform.
  *         This parameter can be one of the following values:
  *         @arg TMR_ForcedAction_Active: Force active level on OC4REF
  *         @arg TMR_ForcedAction_InActive: Force inactive level on OC4REF.
  * @retval None
  */
void TMR_ForcedOC4Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_FORCED_ACTION(TMR_ForcedAction));

  tmpccmr2 = TMRx->CCMR2;
  /* Reset the OC2M Bits */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCMR2_OC4M);
  /* Configure The Forced output Mode */
  tmpccmr2 |= (uint16_t)(TMR_ForcedAction << 8);
  /* Write to TMRx CCMR2 register */
  TMRx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables TMRx peripheral Preload register on ARR.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  NewState: new state of the TMRx peripheral Preload register
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_ARRPreloadConfig(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ARR Preload Bit */
    TMRx->CR1 |= TMR_CR1_ARPE;
  }
  else
  {
    /* Reset the ARR Preload Bit */
    TMRx->CR1 &= (uint16_t)~((uint16_t)TMR_CR1_ARPE);
  }
}

/**
  * @brief  Selects the TMR peripheral Commutation event.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  NewState: new state of the Commutation event.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_SelectCOM(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ENHANCED_PERIPH(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the COM Bit */
    TMRx->CR2 |= TMR_CR2_CCUS;
  }
  else
  {
    /* Reset the COM Bit */
    TMRx->CR2 &= (uint16_t)~((uint16_t)TMR_CR2_CCUS);
  }
}

/**
  * @brief  Selects the TMRx peripheral Capture Compare DMA source.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  NewState: new state of the Capture Compare DMA source
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_SelectCCDMA(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CCDS Bit */
    TMRx->CR2 |= TMR_CR2_CCDS;
  }
  else
  {
    /* Reset the CCDS Bit */
    TMRx->CR2 &= (uint16_t)~((uint16_t)TMR_CR2_CCDS);
  }
}

/**
  * @brief  Sets or Resets the TMR peripheral Capture Compare Preload Control bit.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  NewState: new state of the Capture Compare Preload Control bit
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_CCPreloadControl(TMR_Type* TMRx, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CCPC Bit */
    TMRx->CR2 |= TMR_CR2_CCPC;
  }
  else
  {
    /* Reset the CCPC Bit */
    TMRx->CR2 &= (uint16_t)~((uint16_t)TMR_CR2_CCPC);
  }
}

/**
  * @brief  Enables or disables the TMRx peripheral Preload register on CCR1.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCPreload: new state of the TMRx peripheral Preload register
  *         This parameter can be one of the following values:
  *         @arg TMR_OCPreload_Enable
  *         @arg TMR_OCPreload_Disable
  * @retval None
  */
void TMR_OC1PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCPRELOAD_STATE(TMR_OCPreload));

  tmpccmr1 = TMRx->CCMR1;
  /* Reset the OC1PE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCMR1_OC1PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= TMR_OCPreload;
  /* Write to TMRx CCMR1 register */
  TMRx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the TMRx peripheral Preload register on CCR2.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCPreload: new state of the TMRx peripheral Preload register
  *         This parameter can be one of the following values:
  *         @arg TMR_OCPreload_Enable
  *         @arg TMR_OCPreload_Disable
  * @retval None
  */
void TMR_OC2PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCPRELOAD_STATE(TMR_OCPreload));

  tmpccmr1 = TMRx->CCMR1;
  /* Reset the OC2PE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCMR1_OC2PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= (uint16_t)(TMR_OCPreload << 8);
  /* Write to TMRx CCMR1 register */
  TMRx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the TMRx peripheral Preload register on CCR3.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCPreload: new state of the TMRx peripheral Preload register
  *         This parameter can be one of the following values:
  *         @arg TMR_OCPreload_Enable
  *         @arg TMR_OCPreload_Disable
  * @retval None
  */
void TMR_OC3PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCPRELOAD_STATE(TMR_OCPreload));

  tmpccmr2 = TMRx->CCMR2;
  /* Reset the OC3PE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCMR2_OC3PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= TMR_OCPreload;
  /* Write to TMRx CCMR2 register */
  TMRx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables the TMRx peripheral Preload register on CCR4.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCPreload: new state of the TMRx peripheral Preload register
  *         This parameter can be one of the following values:
  *         @arg TMR_OCPreload_Enable
  *         @arg TMR_OCPreload_Disable
  * @retval None
  */
void TMR_OC4PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCPRELOAD_STATE(TMR_OCPreload));

  tmpccmr2 = TMRx->CCMR2;
  /* Reset the OC4PE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCMR2_OC4PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= (uint16_t)(TMR_OCPreload << 8);
  /* Write to TMRx CCMR2 register */
  TMRx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TMRx Output Compare 1 Fast feature.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCFast: new state of the Output Compare Fast Enable Bit.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCFast_Enable: TMR output compare fast enable
  *         @arg TMR_OCFast_Disable: TMR output compare fast disable
  * @retval None
  */
void TMR_OC1FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCFAST_STATE(TMR_OCFast));

  /* Get the TMRx CCMR1 register value */
  tmpccmr1 = TMRx->CCMR1;
  /* Reset the OC1FE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCMR1_OC1FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= TMR_OCFast;
  /* Write to TMRx CCMR1 */
  TMRx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Configures the TMRx Output Compare 2 Fast feature.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCFast: new state of the Output Compare Fast Enable Bit.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCFast_Enable: TMR output compare fast enable
  *         @arg TMR_OCFast_Disable: TMR output compare fast disable
  * @retval None
  */
void TMR_OC2FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCFAST_STATE(TMR_OCFast));

  /* Get the TMRx CCMR1 register value */
  tmpccmr1 = TMRx->CCMR1;
  /* Reset the OC2FE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCMR1_OC2FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= (uint16_t)(TMR_OCFast << 8);
  /* Write to TMRx CCMR1 */
  TMRx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Configures the TMRx Output Compare 3 Fast feature.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCFast: new state of the Output Compare Fast Enable Bit.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCFast_Enable: TMR output compare fast enable
  *         @arg TMR_OCFast_Disable: TMR output compare fast disable
  * @retval None
  */
void TMR_OC3FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCFAST_STATE(TMR_OCFast));

  /* Get the TMRx CCMR2 register value */
  tmpccmr2 = TMRx->CCMR2;
  /* Reset the OC3FE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCMR2_OC3FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= TMR_OCFast;
  /* Write to TMRx CCMR2 */
  TMRx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TMRx Output Compare 4 Fast feature.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCFast: new state of the Output Compare Fast Enable Bit.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCFast_Enable: TMR output compare fast enable
  *         @arg TMR_OCFast_Disable: TMR output compare fast disable
  * @retval None
  */
void TMR_OC4FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCFAST_STATE(TMR_OCFast));

  /* Get the TMRx CCMR2 register value */
  tmpccmr2 = TMRx->CCMR2;
  /* Reset the OC4FE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCMR2_OC4FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= (uint16_t)(TMR_OCFast << 8);
  /* Write to TMRx CCMR2 */
  TMRx->CCMR2 = tmpccmr2;
}


/**
  * @brief  Clears or safeguards the OCREF1 signal on an external event
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCClear: new state of the Output Compare Clear Enable Bit.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCClear_Enable: TMR Output clear enable
  *         @arg TMR_OCClear_Disable: TMR Output clear disable
  * @retval None
  */
void TMR_ClearOC1Ref(TMR_Type* TMRx, uint16_t TMR_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCCLEAR_STATE(TMR_OCClear));

  tmpccmr1 = TMRx->CCMR1;

  /* Reset the OC1CE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCMR1_OC1CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= TMR_OCClear;
  /* Write to TMRx CCMR1 register */
  TMRx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF2 signal on an external event
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCClear: new state of the Output Compare Clear Enable Bit.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCClear_Enable: TMR Output clear enable
  *         @arg TMR_OCClear_Disable: TMR Output clear disable
  * @retval None
  */
void TMR_ClearOC2Ref(TMR_Type* TMRx, uint16_t TMR_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCCLEAR_STATE(TMR_OCClear));

  tmpccmr1 = TMRx->CCMR1;
  /* Reset the OC2CE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCMR1_OC2CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= (uint16_t)(TMR_OCClear << 8);
  /* Write to TMRx CCMR1 register */
  TMRx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF3 signal on an external event
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCClear: new state of the Output Compare Clear Enable Bit.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCClear_Enable: TMR Output clear enable
  *         @arg TMR_OCClear_Disable: TMR Output clear disable
  * @retval None
  */
void TMR_ClearOC3Ref(TMR_Type* TMRx, uint16_t TMR_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCCLEAR_STATE(TMR_OCClear));

  tmpccmr2 = TMRx->CCMR2;
  /* Reset the OC3CE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCMR2_OC3CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= TMR_OCClear;
  /* Write to TMRx CCMR2 register */
  TMRx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF4 signal on an external event
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCClear: new state of the Output Compare Clear Enable Bit.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCClear_Enable: TMR Output clear enable
  *         @arg TMR_OCClear_Disable: TMR Output clear disable
  * @retval None
  */
void TMR_ClearOC4Ref(TMR_Type* TMRx, uint16_t TMR_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCCLEAR_STATE(TMR_OCClear));

  tmpccmr2 = TMRx->CCMR2;
  /* Reset the OC4CE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCMR2_OC4CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= (uint16_t)(TMR_OCClear << 8);
  /* Write to TMRx CCMR2 register */
  TMRx->CCMR2 = tmpccmr2;
}


/**
  * @brief  Configures the TMRx channel 1 polarity.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCPolarity: specifies the OC1 Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_OCPolarity_High: Output Compare active high
  *         @arg TMR_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC1PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OC_POLARITY(TMR_OCPolarity));

  tmpccer = TMRx->CCER;
  /* Set or Reset the CC1P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCER_CC1P);
  tmpccer |= TMR_OCPolarity;
  /* Write to TMRx CCER register */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configures the TMRx Channel 1N polarity.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCNPolarity: specifies the OC1N Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_OCNPolarity_High: Output Compare active high
  *         @arg TMR_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC1NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ENHANCED_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCN_POLARITY(TMR_OCNPolarity));

  tmpccer = TMRx->CCER;
  /* Set or Reset the CC1NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCER_CC1NP);
  tmpccer |= TMR_OCNPolarity;
  /* Write to TMRx CCER register */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configures the TMRx channel 2 polarity.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCPolarity: specifies the OC2 Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_OCPolarity_High: Output Compare active high
  *         @arg TMR_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC2PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OC_POLARITY(TMR_OCPolarity));

  tmpccer = TMRx->CCER;
  /* Set or Reset the CC2P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCER_CC2P);
  tmpccer |= (uint16_t)(TMR_OCPolarity << 4);
  /* Write to TMRx CCER register */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configures the TMRx Channel 2N polarity.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCNPolarity: specifies the OC2N Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_OCNPolarity_High: Output Compare active high
  *         @arg TMR_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC2NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ENHANCED_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCN_POLARITY(TMR_OCNPolarity));

  tmpccer = TMRx->CCER;
  /* Set or Reset the CC2NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCER_CC2NP);
  tmpccer |= (uint16_t)(TMR_OCNPolarity << 4);
  /* Write to TMRx CCER register */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configures the TMRx channel 3 polarity.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCPolarity: specifies the OC3 Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_OCPolarity_High: Output Compare active high
  *         @arg TMR_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC3PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OC_POLARITY(TMR_OCPolarity));

  tmpccer = TMRx->CCER;
  /* Set or Reset the CC3P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCER_CC3P);
  tmpccer |= (uint16_t)(TMR_OCPolarity << 8);
  /* Write to TMRx CCER register */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configures the TMRx Channel 3N polarity.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCNPolarity: specifies the OC3N Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_OCNPolarity_High: Output Compare active high
  *         @arg TMR_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC3NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity)
{
  uint16_t tmpccer = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ENHANCED_PERIPH(TMRx));
  assert_parameters(IS_TMR_OCN_POLARITY(TMR_OCNPolarity));

  tmpccer = TMRx->CCER;
  /* Set or Reset the CC3NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCER_CC3NP);
  tmpccer |= (uint16_t)(TMR_OCNPolarity << 8);
  /* Write to TMRx CCER register */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configures the TMRx channel 4 polarity.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OCPolarity: specifies the OC4 Polarity
  *         This parameter can be one of the following values:
  *         @arg TMR_OCPolarity_High: Output Compare active high
  *         @arg TMR_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC4PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OC_POLARITY(TMR_OCPolarity));

  tmpccer = TMRx->CCER;
  /* Set or Reset the CC4P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCER_CC4P);
  tmpccer |= (uint16_t)(TMR_OCPolarity << 12);
  /* Write to TMRx CCER register */
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Enables or disables the TMR Capture Compare Channel x.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_Channel: specifies the TMR Channel
  *         This parameter can be one of the following values:
  *         @arg TMR_Channel_1: TMR Channel 1
  *         @arg TMR_Channel_2: TMR Channel 2
  *         @arg TMR_Channel_3: TMR Channel 3
  *         @arg TMR_Channel_4: TMR Channel 4
  * @param  TMR_CCx: specifies the TMR Channel CCxE bit new state.
  *         This parameter can be one of the following values:
  *         @arg TMR_CCx_Enable
  *         @arg TMR_CCx_Disable
  * @retval None
  */
void TMR_CCxCmd(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_CCx)
{
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_CHANNEL(TMR_Channel));
  assert_parameters(IS_TMR_CCX(TMR_CCx));

  tmp = CCER_CCE_Set << TMR_Channel;

  /* Reset the CCxE Bit */
  TMRx->CCER &= (uint16_t)~ tmp;

  /* Set or reset the CCxE Bit */ 
  TMRx->CCER |=  (uint16_t)(TMR_CCx << TMR_Channel);
}

/**
  * @brief  Enables or disables the TMR Capture Compare Channel xN.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_Channel: specifies the TMR Channel
  *         This parameter can be one of the following values:
  *         @arg TMR_Channel_1: TMR Channel 1
  *         @arg TMR_Channel_2: TMR Channel 2
  *         @arg TMR_Channel_3: TMR Channel 3
  * @param  TMR_CCxN: specifies the TMR Channel CCxNE bit new state.
  *         This parameter can be one of the following values:
  *         @arg TMR_CCxN_Enable
  *         @arg TMR_CCxN_Disable
  * @retval None
  */
void TMR_CCxNCmd(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_CCxN)
{
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ENHANCED_PERIPH(TMRx));
  assert_parameters(IS_TMR_COMPLEMENTARY_CHANNEL(TMR_Channel));
  assert_parameters(IS_TMR_CCXN(TMR_CCxN));

  tmp = CCER_CCNE_Set << TMR_Channel;

  /* Reset the CCxNE Bit */
  TMRx->CCER &= (uint16_t) ~tmp;

  /* Set or reset the CCxNE Bit */ 
  TMRx->CCER |=  (uint16_t)(TMR_CCxN << TMR_Channel);
}


/**
  * @brief  Selects the TMR Output Compare Mode.
  * @note   This function disables the selected channel before changing the Output Compare Mode.
  *         User has to enable this channel using TMR_CCxCmd and TMR_CCxNCmd functions.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_Channel: specifies the TMR Channel
  *         This parameter can be one of the following values:
  *         @arg TMR_Channel_1: TMR Channel 1
  *         @arg TMR_Channel_2: TMR Channel 2
  *         @arg TMR_Channel_3: TMR Channel 3
  *         @arg TMR_Channel_4: TMR Channel 4
  * @param  TMR_OCMode: specifies the TMR Output Compare Mode.
  *         This parameter can be one of the following values:
  *         @arg TMR_OCMode_Timing
  *         @arg TMR_OCMode_Active
  *         @arg TMR_OCMode_Toggle
  *         @arg TMR_OCMode_PWM1
  *         @arg TMR_OCMode_PWM2
  *         @arg TMR_ForcedAction_Active
  *         @arg TMR_ForcedAction_InActive
  * @retval None
  */
void TMR_SelectOCxM(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_OCMode)
{
  uint32_t tmp = 0;
  uint16_t tmp1 = 0;

  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_CHANNEL(TMR_Channel));
  assert_parameters(IS_TMR_OCM(TMR_OCMode));

  tmp = (uint32_t) TMRx;
  tmp += CCMR_Offset;

  tmp1 = CCER_CCE_Set << (uint16_t)TMR_Channel;

  /* Disable the Channel: Reset the CCxE Bit */
  TMRx->CCER &= (uint16_t) ~tmp1;

  if((TMR_Channel == TMR_Channel_1) ||(TMR_Channel == TMR_Channel_3))
  {
    tmp += (TMR_Channel>>1);

    /* Reset the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TMR_CCMR1_OC1M);
   
    /* Configure the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp |= TMR_OCMode;
  }
  else
  {
    tmp += (uint16_t)(TMR_Channel - (uint16_t)4)>> (uint16_t)1;

    /* Reset the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TMR_CCMR1_OC2M);
    
    /* Configure the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp |= (uint16_t)(TMR_OCMode << 8);
  }
}

/**
  * @brief  Enables or Disables the TMRx Update event.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  NewState: new state of the TMRx UDIS bit
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_UpdateDisableConfig(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the Update Disable Bit */
    TMRx->CR1 |= TMR_CR1_UDIS;
  }
  else
  {
    /* Reset the Update Disable Bit */
    TMRx->CR1 &= (uint16_t)~((uint16_t)TMR_CR1_UDIS);
  }
}

/**
  * @brief  Configures the TMRx Update Request Interrupt source.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_UpdateSource: specifies the Update source.
  *         This parameter can be one of the following values:
  *         @arg TMR_UpdateSource_Regular: Source of update is the counter overflow/underflow
  *                                        or the setting of UG bit, or an update generation
  *                                        through the slave mode controller.
  *         @arg TMR_UpdateSource_Global: Source of update is counter overflow/underflow.
  * @retval None
  */
void TMR_UpdateRequestConfig(TMR_Type* TMRx, uint16_t TMR_UpdateSource)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_UPDATE_SOURCE(TMR_UpdateSource));

  if (TMR_UpdateSource != TMR_UpdateSource_Global)
  {
    /* Set the URS Bit */
    TMRx->CR1 |= TMR_CR1_URS;
  }
  else
  {
    /* Reset the URS Bit */
    TMRx->CR1 &= (uint16_t)~((uint16_t)TMR_CR1_URS);
  }
}

/**
  * @brief  Enables or disables the TMRx's Hall sensor interface.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  NewState: new state of the TMRx Hall sensor interface.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_SelectHallSensor(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the TI1S Bit */
    TMRx->CR2 |= TMR_CR2_TI1S;
  }
  else
  {
    /* Reset the TI1S Bit */
    TMRx->CR2 &= (uint16_t)~((uint16_t)TMR_CR2_TI1S);
  }
}

/**
  * @brief  Selects the TMRx's One Pulse Mode.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_OPMode: specifies the OPM Mode to be used.
  *         This parameter can be one of the following values:
  *         @arg TMR_OPMode_Single
  *         @arg TMR_OPMode_Repetitive
  * @retval None
  */
void TMR_SelectOnePulseMode(TMR_Type* TMRx, uint16_t TMR_OPMode)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_OPM_MODE(TMR_OPMode));

  /* Reset the OPM Bit */
  TMRx->CR1 &= (uint16_t)~((uint16_t)TMR_CR1_OPM);
  /* Configure the OPM Mode */
  TMRx->CR1 |= TMR_OPMode;
}

/**
  * @brief  Selects the TMRx Trigger Output Mode.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_TRGOSource: specifies the Trigger Output source.
  *         This paramter can be one of the following values:
  *         @arg TMR_TRGOSource_Reset: The UG bit in the TMR_EGR register is used as the trigger output (TRGO).
  *         @arg TMR_TRGOSource_Enable: The Counter Enable CEN is used as the trigger output (TRGO).
  *         @arg TMR_TRGOSource_Update: The update event is selected as the trigger output (TRGO).
  *         @arg TMR_TRGOSource_OC1: The trigger output sends a positive pulse when the CC1IF flag
  *                                   is to be set, as soon as a capture or compare match occurs (TRGO).
  *         @arg TMR_TRGOSource_OC1Ref: OC1REF signal is used as the trigger output (TRGO).
  *         @arg TMR_TRGOSource_OC2Ref: OC2REF signal is used as the trigger output (TRGO).
  *         @arg TMR_TRGOSource_OC3Ref: OC3REF signal is used as the trigger output (TRGO).
  *         @arg TMR_TRGOSource_OC4Ref: OC4REF signal is used as the trigger output (TRGO).
  * @retval None
  */
void TMR_SelectOutputTrigger(TMR_Type* TMRx, uint16_t TMR_TRGOSource)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_TRGO_SOURCE(TMR_TRGOSource));

  /* Reset the MMS Bits */
  TMRx->CR2 &= (uint16_t)~((uint16_t)TMR_CR2_MMS);
  /* Select the TRGO source */
  TMRx->CR2 |=  TMR_TRGOSource;
}

/**
  * @brief  Selects the TMRx Slave Mode.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_SlaveMode: specifies the Timer Slave Mode.
  *         This parameter can be one of the following values:
  *         @arg TMR_SlaveMode_Reset: Rising edge of the selected trigger signal (TRGI) re-initializes
  *                                   the counter and triggers an update of the registers.
  *         @arg TMR_SlaveMode_Gated: The counter clock is enabled when the trigger signal (TRGI) is high.
  *         @arg TMR_SlaveMode_Trigger: The counter starts at a rising edge of the trigger TRGI.
  *         @arg TMR_SlaveMode_External1: Rising edges of the selected trigger (TRGI) clock the counter.
  * @retval None
  */
void TMR_SelectSlaveMode(TMR_Type* TMRx, uint16_t TMR_SlaveMode)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_SLAVE_MODE(TMR_SlaveMode));

  /* Reset the SMS Bits */
  TMRx->SMCR &= (uint16_t)~((uint16_t)TMR_SMCR_SMS);
  /* Select the Slave Mode */
  TMRx->SMCR |= TMR_SlaveMode;
}

/**
  * @brief  Sets or Resets the TMRx Master/Slave Mode.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_MasterSlaveMode: specifies the Timer Master Slave Mode.
  *         This parameter can be one of the following values:
  *         @arg TMR_MasterSlaveMode_Enable: synchronization between the current timer
  *                                          and its slaves (through TRGO).
  *         @arg TMR_MasterSlaveMode_Disable: No action
  * @retval None
  */
void TMR_SelectMasterSlaveMode(TMR_Type* TMRx, uint16_t TMR_MasterSlaveMode)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_MSM_STATE(TMR_MasterSlaveMode));

  /* Reset the MSM Bit */
  TMRx->SMCR &= (uint16_t)~((uint16_t)TMR_SMCR_MSM);
  
  /* Set or Reset the MSM Bit */
  TMRx->SMCR |= TMR_MasterSlaveMode;
}

/**
  * @brief  Sets the TMRx Counter Register value
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void TMR_SetCounter(TMR_Type* TMRx, uint16_t Counter)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Set the Counter Register value */
  TMRx->CNT = Counter;
}

/**
  * @brief  Sets the TMRx Autoreload Register value
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  Autoreload: specifies the Autoreload register new value.
  * @retval None
  */
void TMR_SetAutoreload(TMR_Type* TMRx, uint16_t Autoreload)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Set the Autoreload Register value */
  TMRx->ARR = Autoreload;
}

/**
  * @brief  Sets the TMRx Capture Compare1 Register value
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  Compare1: specifies the Capture Compare1 register new value.
  * @retval None
  */
void TMR_SetCompare1(TMR_Type* TMRx, uint16_t Compare1)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Set the Capture Compare1 Register value */
  TMRx->CCR1 = Compare1;
}

/**
  * @brief  Sets the TMRx Capture Compare2 Register value
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  Compare2: specifies the Capture Compare2 register new value.
  * @retval None
  */
void TMR_SetCompare2(TMR_Type* TMRx, uint16_t Compare2)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Set the Capture Compare2 Register value */
  TMRx->CCR2 = Compare2;
}

/**
  * @brief  Sets the TMRx Capture Compare3 Register value
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  Compare3: specifies the Capture Compare3 register new value.
  * @retval None
  */
void TMR_SetCompare3(TMR_Type* TMRx, uint16_t Compare3)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Set the Capture Compare3 Register value */
  TMRx->CCR3 = Compare3;
}

/**
  * @brief  Sets the TMRx Capture Compare4 Register value
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  Compare4: specifies the Capture Compare4 register new value.
  * @retval None
  */
void TMR_SetCompare4(TMR_Type* TMRx, uint16_t Compare4)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Set the Capture Compare4 Register value */
  TMRx->CCR4 = Compare4;
}

/**
  * @brief  Sets the TMRx Input Capture 1 prescaler.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICPSC: specifies the Input Capture1 prescaler new value.
  *         This parameter can be one of the following values:
  *         @arg TMR_IC_PSC_DIV1: no prescaler
  *         @arg TMR_IC_PSC_DIV2: capture is done once every 2 events
  *         @arg TMR_IC_PSC_DIV4: capture is done once every 4 events
  *         @arg TMR_IC_PSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TMR_SetIC1Prescaler(TMR_Type* TMRx, uint16_t TMR_ICPSC)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_IC_PRESCALER(TMR_ICPSC));
  
  /* Reset the IC1PSC Bits */
  TMRx->CCMR1 &= (uint16_t)~((uint16_t)TMR_CCMR1_IC1PSC);
  /* Set the IC1PSC value */
  TMRx->CCMR1 |= TMR_ICPSC;
}

/**
  * @brief  Sets the TMRx Input Capture 2 prescaler.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICPSC: specifies the Input Capture2 prescaler new value.
  *         This parameter can be one of the following values:
  *         @arg TMR_IC_PSC_DIV1: no prescaler
  *         @arg TMR_IC_PSC_DIV2: capture is done once every 2 events
  *         @arg TMR_IC_PSC_DIV4: capture is done once every 4 events
  *         @arg TMR_IC_PSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TMR_SetIC2Prescaler(TMR_Type* TMRx, uint16_t TMR_ICPSC)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_IC_PRESCALER(TMR_ICPSC));
  
  /* Reset the IC2PSC Bits */
  TMRx->CCMR1 &= (uint16_t)~((uint16_t)TMR_CCMR1_IC2PSC);
  /* Set the IC2PSC value */
  TMRx->CCMR1 |= (uint16_t)(TMR_ICPSC << 8);
}

/**
  * @brief  Sets the TMRx Input Capture 3 prescaler.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICPSC: specifies the Input Capture3 prescaler new value.
  *         This parameter can be one of the following values:
  *         @arg TMR_IC_PSC_DIV1: no prescaler
  *         @arg TMR_IC_PSC_DIV2: capture is done once every 2 events
  *         @arg TMR_IC_PSC_DIV4: capture is done once every 4 events
  *         @arg TMR_IC_PSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TMR_SetIC3Prescaler(TMR_Type* TMRx, uint16_t TMR_ICPSC)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_IC_PRESCALER(TMR_ICPSC));

  /* Reset the IC3PSC Bits */
  TMRx->CCMR2 &= (uint16_t)~((uint16_t)TMR_CCMR2_IC3PSC);
  /* Set the IC3PSC value */
  TMRx->CCMR2 |= TMR_ICPSC;
}

/**
  * @brief  Sets the TMRx Input Capture 4 prescaler.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICPSC: specifies the Input Capture4 prescaler new value.
  *         This parameter can be one of the following values:
  *         @arg TMR_IC_PSC_DIV1: no prescaler
  *         @arg TMR_IC_PSC_DIV2: capture is done once every 2 events
  *         @arg TMR_IC_PSC_DIV4: capture is done once every 4 events
  *         @arg TMR_IC_PSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TMR_SetIC4Prescaler(TMR_Type* TMRx, uint16_t TMR_ICPSC)
{  
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_IC_PRESCALER(TMR_ICPSC));

  /* Reset the IC4PSC Bits */
  TMRx->CCMR2 &= (uint16_t)~((uint16_t)TMR_CCMR2_IC4PSC);
  /* Set the IC4PSC value */
  TMRx->CCMR2 |= (uint16_t)(TMR_ICPSC << 8);
}

/**
  * @brief  Sets the TMRx Clock Division value.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_CKD: specifies the clock division value.
  *         This parameter can be one of the following value:
  *         @arg TMR_CKD_DIV1: TDTS = Tck_tim
  *         @arg TMR_CKD_DIV2: TDTS = 2*Tck_tim
  *         @arg TMR_CKD_DIV4: TDTS = 4*Tck_tim
  * @retval None
  */
void TMR_SetClockDivision(TMR_Type* TMRx, uint16_t TMR_CKD)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_CKD_DIV(TMR_CKD));
  
  /* Reset the CKD Bits */
  TMRx->CR1 &= (uint16_t)~((uint16_t)TMR_CR1_CKD);
  /* Set the CKD value */
  TMRx->CR1 |= TMR_CKD;
}

/**
  * @brief  Gets the TMRx Input Capture 1 value.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @retval Capture Compare 1 Register value.
  */
uint16_t TMR_GetCapture1(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Get the Capture 1 Register value */
  return TMRx->CCR1;
}

/**
  * @brief  Gets the TMRx Input Capture 2 value.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @retval Capture Compare 2 Register value.
  */
uint16_t TMR_GetCapture2(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Get the Capture 2 Register value */
  return TMRx->CCR2;
}

/**
  * @brief  Gets the TMRx Input Capture 3 value.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @retval Capture Compare 3 Register value.
  */
uint16_t TMR_GetCapture3(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx)); 
  
  /* Get the Capture 3 Register value */
  return TMRx->CCR3;
}

/**
  * @brief  Gets the TMRx Input Capture 4 value.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @retval Capture Compare 4 Register value.
  */
uint16_t TMR_GetCapture4(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Get the Capture 4 Register value */
  return TMRx->CCR4;
}

/**
  * @brief  Gets the TMRx Counter value.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @retval Counter Register value.
  */
uint16_t TMR_GetCounter(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Get the Counter Register value */
  return TMRx->CNT;
}

/**
  * @brief  Gets the TMRx Prescaler value.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @retval Prescaler Register value.
  */
uint16_t TMR_GetPrescaler(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  
  /* Get the Prescaler Register value */
  return TMRx->PSC;
}

/**
  * @brief  Checks whether the specified TMR flag is set or not.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *         @arg TMR_FLAG_Update: TMR update Flag
  *         @arg TMR_FLAG_CC1: TMR Capture Compare 1 Flag
  *         @arg TMR_FLAG_CC2: TMR Capture Compare 2 Flag
  *         @arg TMR_FLAG_CC3: TMR Capture Compare 3 Flag
  *         @arg TMR_FLAG_CC4: TMR Capture Compare 4 Flag
  *         @arg TMR_FLAG_COM: TMR Commutation Flag
  *         @arg TMR_FLAG_Trigger: TMR Trigger Flag
  *         @arg TMR_FLAG_Break: TMR Break Flag
  *         @arg TMR_FLAG_CC1OF: TMR Capture Compare 1 overcapture Flag
  *         @arg TMR_FLAG_CC2OF: TMR Capture Compare 2 overcapture Flag
  *         @arg TMR_FLAG_CC3OF: TMR Capture Compare 3 overcapture Flag
  *         @arg TMR_FLAG_CC4OF: TMR Capture Compare 4 overcapture Flag
  * @note
  *         TMR_FLAG_Break and TMR_FLAG_COM are used only with ETMR0 or ETMR1.
  * @retval The new state of TMR_FLAG (SET or RESET).
  */
FlagStatus TMR_GetFlagStatus(TMR_Type* TMRx, uint16_t TMR_FLAG)
{ 
  ITStatus bitstatus = RESET;  
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_GET_FLAG(TMR_FLAG));
  
  if ((TMRx->SR & TMR_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the TMRx's pending flags.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_FLAG: specifies the flag bit to clear.
  *         This parameter can be one of the following values:
  *         @arg TMR_FLAG_Update: TMR update Flag
  *         @arg TMR_FLAG_CC1: TMR Capture Compare 1 Flag
  *         @arg TMR_FLAG_CC2: TMR Capture Compare 2 Flag
  *         @arg TMR_FLAG_CC3: TMR Capture Compare 3 Flag
  *         @arg TMR_FLAG_CC4: TMR Capture Compare 4 Flag
  *         @arg TMR_FLAG_COM: TMR Commutation Flag
  *         @arg TMR_FLAG_Trigger: TMR Trigger Flag
  *         @arg TMR_FLAG_Break: TMR Break Flag
  *         @arg TMR_FLAG_CC1OF: TMR Capture Compare 1 overcapture Flag
  *         @arg TMR_FLAG_CC2OF: TMR Capture Compare 2 overcapture Flag
  *         @arg TMR_FLAG_CC3OF: TMR Capture Compare 3 overcapture Flag
  *         @arg TMR_FLAG_CC4OF: TMR Capture Compare 4 overcapture Flag
  * @note
  *         TMR_FLAG_Break and TMR_FLAG_COM are used only with ETMR0 or ETMR1.
  * @retval None
  */
void TMR_ClearFlag(TMR_Type* TMRx, uint16_t TMR_FLAG)
{  
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_CLEAR_FLAG(TMR_FLAG));
   
  /* Clear the flags */
  TMRx->SR = (uint16_t)~TMR_FLAG;
}

/**
  * @brief  Checks whether the TMR interrupt has occurred or not.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_IT: specifies the TMR interrupt source to check.
  *         This parameter can be one of the following values:
  *         @arg TMR_IT_Update: TMR update Interrupt source
  *         @arg TMR_IT_CC1: TMR Capture Compare 1 Interrupt source
  *         @arg TMR_IT_CC2: TMR Capture Compare 2 Interrupt source
  *         @arg TMR_IT_CC3: TMR Capture Compare 3 Interrupt source
  *         @arg TMR_IT_CC4: TMR Capture Compare 4 Interrupt source
  *         @arg TMR_IT_COM: TMR Commutation Interrupt source
  *         @arg TMR_IT_Trigger: TMR Trigger Interrupt source
  *         @arg TMR_IT_Break: TMR Break Interrupt source
  * @note
  *         TMR_IT_Break and TMR_IT_COM are used only with ETMR0 or ETMR1.
  * @retval The new state of the TMR_IT(SET or RESET).
  */
ITStatus TMR_GetITStatus(TMR_Type* TMRx, uint16_t TMR_IT)
{
  ITStatus bitstatus = RESET;  
  uint16_t ITStatus = 0x0, itenable = 0x0;
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_GET_IT(TMR_IT));
   
  ITStatus = TMRx->SR & TMR_IT;
  
  itenable = TMRx->DIER & TMR_IT;
  if ((ITStatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the TMRx's interrupt pending bits.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_IT: specifies the pending bit to clear.
  *         This parameter can be one of the following values:
  *         @arg TMR_IT_Update: TMR update Interrupt source
  *         @arg TMR_IT_CC1: TMR Capture Compare 1 Interrupt source
  *         @arg TMR_IT_CC2: TMR Capture Compare 2 Interrupt source
  *         @arg TMR_IT_CC3: TMR Capture Compare 3 Interrupt source
  *         @arg TMR_IT_CC4: TMR Capture Compare 4 Interrupt source
  *         @arg TMR_IT_COM: TMR Commutation Interrupt source
  *         @arg TMR_IT_Trigger: TMR Trigger Interrupt source
  *         @arg TMR_IT_Break: TMR Break Interrupt source
  * @note
  *         TMR_IT_Break and TMR_IT_COM are used only with ETMR0 or ETMR1.
  * @retval None
  */
void TMR_ClearITPendingBit(TMR_Type* TMRx, uint16_t TMR_IT)
{
  /* Check the parameters */
  assert_parameters(IS_TMR_ALL_PERIPH(TMRx));
  assert_parameters(IS_TMR_IT(TMR_IT));
  /* Clear the IT pending Bit */
  TMRx->SR = (uint16_t)~TMR_IT;
}

/**
  * @brief  Configure the TI1 as Input.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICPolarity : The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICPolarity_Rising
  *         @arg TMR_ICPolarity_Falling
  * @param  TMR_ICSelection: specifies the input to be used.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICSelection_DirectTI: TMR Input 1 is selected to be connected to IC1.
  *         @arg TMR_ICSelection_IndirectTI: TMR Input 1 is selected to be connected to IC2.
  *         @arg TMR_ICSelection_TRC: TMR Input 1 is selected to be connected to TRC.
  * @param  TMR_ICFilter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection, uint16_t TMR_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0;
  /* Disable the Channel 1: Reset the CC1E Bit */
  TMRx->CCER &= (uint16_t)~((uint16_t)TMR_CCER_CC1E);
  tmpccmr1 = TMRx->CCMR1;
  tmpccer = TMRx->CCER;
  /* Select the Input and set the filter */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCMR1_CC1S)) & ((uint16_t)~((uint16_t)TMR_CCMR1_IC1F)));
  tmpccmr1 |= (uint16_t)(TMR_ICSelection | (uint16_t)(TMR_ICFilter << (uint16_t)4));
  
  /* Select the Polarity and set the CC1E Bit */
  tmpccer &= (uint16_t)~((uint16_t)(TMR_CCER_CC1P));
  tmpccer |= (uint16_t)(TMR_ICPolarity | (uint16_t)TMR_CCER_CC1E);

  /* Write to TMRx CCMR1 and CCER registers */
  TMRx->CCMR1 = tmpccmr1;
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICPolarity : The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICPolarity_Rising
  *         @arg TMR_ICPolarity_Falling
  * @param  TMR_ICSelection: specifies the input to be used.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICSelection_DirectTI: TMR Input 2 is selected to be connected to IC2.
  *         @arg TMR_ICSelection_IndirectTI: TMR Input 2 is selected to be connected to IC1.
  *         @arg TMR_ICSelection_TRC: TMR Input 2 is selected to be connected to TRC.
  * @param  TMR_ICFilter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection, uint16_t TMR_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;
  /* Disable the Channel 2: Reset the CC2E Bit */
  TMRx->CCER &= (uint16_t)~((uint16_t)TMR_CCER_CC2E);
  tmpccmr1 = TMRx->CCMR1;
  tmpccer = TMRx->CCER;
  tmp = (uint16_t)(TMR_ICPolarity << 4);
  /* Select the Input and set the filter */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCMR1_CC2S)) & ((uint16_t)~((uint16_t)TMR_CCMR1_IC2F)));
  tmpccmr1 |= (uint16_t)(TMR_ICFilter << 12);
  tmpccmr1 |= (uint16_t)(TMR_ICSelection << 8);
  
  /* Select the Polarity and set the CC2E Bit */
  tmpccer &= (uint16_t)~((uint16_t)(TMR_CCER_CC2P));
  tmpccer |=  (uint16_t)(tmp | (uint16_t)TMR_CCER_CC2E);

  /* Write to TMRx CCMR1 and CCER registers */
  TMRx->CCMR1 = tmpccmr1 ;
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI3 as Input.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICPolarity : The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICPolarity_Rising
  *         @arg TMR_ICPolarity_Falling
  * @param  TMR_ICSelection: specifies the input to be used.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICSelection_DirectTI: TMR Input 3 is selected to be connected to IC3.
  *         @arg TMR_ICSelection_IndirectTI: TMR Input 3 is selected to be connected to IC4.
  *         @arg TMR_ICSelection_TRC: TMR Input 3 is selected to be connected to TRC.
  * @param  TMR_ICFilter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI3_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection, uint16_t TMR_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;
  /* Disable the Channel 3: Reset the CC3E Bit */
  TMRx->CCER &= (uint16_t)~((uint16_t)TMR_CCER_CC3E);
  tmpccmr2 = TMRx->CCMR2;
  tmpccer = TMRx->CCER;
  tmp = (uint16_t)(TMR_ICPolarity << 8);
  /* Select the Input and set the filter */
  tmpccmr2 &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCMR2_CC3S)) & ((uint16_t)~((uint16_t)TMR_CCMR2_IC3F)));
  tmpccmr2 |= (uint16_t)(TMR_ICSelection | (uint16_t)(TMR_ICFilter << (uint16_t)4));

  /* Select the Polarity and set the CC3E Bit */
  tmpccer &= (uint16_t)~((uint16_t)(TMR_CCER_CC3P));
  tmpccer |= (uint16_t)(tmp | (uint16_t)TMR_CCER_CC3E);

  /* Write to TMRx CCMR2 and CCER registers */
  TMRx->CCMR2 = tmpccmr2;
  TMRx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI4 as Input.
  * @param  TMRx: to select the TMR peripheral.
  *         This parameter can be: ETMR0 ~ ETMR1, GTMR0 ~ GTMR3
  * @param  TMR_ICPolarity : The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICPolarity_Rising
  *         @arg TMR_ICPolarity_Falling
  * @param  TMR_ICSelection: specifies the input to be used.
  *         This parameter can be one of the following values:
  *         @arg TMR_ICSelection_DirectTI: TMR Input 4 is selected to be connected to IC4.
  *         @arg TMR_ICSelection_IndirectTI: TMR Input 4 is selected to be connected to IC3.
  *         @arg TMR_ICSelection_TRC: TMR Input 4 is selected to be connected to TRC.
  * @param  TMR_ICFilter: Specifies the Input Capture Filter.
  *         This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI4_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection, uint16_t TMR_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

   /* Disable the Channel 4: Reset the CC4E Bit */
  TMRx->CCER &= (uint16_t)~((uint16_t)TMR_CCER_CC4E);
  tmpccmr2 = TMRx->CCMR2;
  tmpccer = TMRx->CCER;
  tmp = (uint16_t)(TMR_ICPolarity << 12);
  /* Select the Input and set the filter */
  tmpccmr2 &= (uint16_t)((uint16_t)(~(uint16_t)TMR_CCMR2_CC4S) & ((uint16_t)~((uint16_t)TMR_CCMR2_IC4F)));
  tmpccmr2 |= (uint16_t)(TMR_ICSelection << 8);
  tmpccmr2 |= (uint16_t)(TMR_ICFilter << 12);

  /* Select the Polarity and set the CC4E Bit */
  tmpccer &= (uint16_t)~((uint16_t)(TMR_CCER_CC4P));
  tmpccer |= (uint16_t)(tmp | (uint16_t)TMR_CCER_CC4E);

  /* Write to TMRx CCMR2 and CCER registers */
  TMRx->CCMR2 = tmpccmr2;
  TMRx->CCER = tmpccer;
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
