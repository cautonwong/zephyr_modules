/**
  * @file    target.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-12-14
  * @brief   
******************************************************************************/

#ifndef __TARGET_H
#define __TARGET_H

#include <stdint.h>
#include <zephyr/toolchain.h>

#ifdef V32F209XX
#elif defined V32F207XX
  #ifdef V32F20XXX_CM33_CORE1
    #error  "V32F20XXX_CM33_CORE1 should not be defined."
  #elif defined V32F20XXX_CM0_CORE
    #error  "V32F20XXX_CM0_CORE should not be defined."
  #endif//V32F20XXX_CM33_CORE1
#else
  #error  "V32F20XXX chip type should be defined."
#endif

#ifdef __cplusplus
 extern "C" {
#endif 
/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */
/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */
typedef enum IRQn {
  
  /* Auxiliary constants */
  NotAvail_IRQn                = -128, 
  
  /* Cortex-M33 Core interrupts */
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1) 
  NonMaskableInt_IRQn         = -14,               /**< Non Maskable Interrupt */
  HardFault_IRQn              = -13,               /**< Cortex-M33 SV Hard Fault Interrupt */
  MemoryManagement_IRQn       = -12,               /**< Cortex-M33 Memory Management Interrupt */
  BusFault_IRQn               = -11,               /**< Cortex-M33 Bus Fault Interrupt */
  UsageFault_IRQn             = -10,               /**< Cortex-M33 Usage Fault Interrupt */
  SecureFault_IRQn            = -9,                /**< Cortex-M33 Secure Fault Interrupt */
  SVCall_IRQn                 = -5,                /**< Cortex-M33 SV Call Interrupt */
  DebugMonitor_IRQn           = -4,                /**< Cortex-M33 Debug Monitor Interrupt */
  PendSV_IRQn                 = -2,                /**< Cortex-M33 Pend SV Interrupt */
  SysTick_IRQn                = -1,                /**< Cortex-M33 System Tick Interrupt */  
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */
  
  /* Cortex-M0 Core interrupts */
#if defined (V32F20XXX_CM0_CORE)
  NMI_IRQn                    = -14,               /*!< Non Maskable Interrupt */
  HardFault_IRQn              = -13,               /*!< Cortex-M0 Hard Fault Interrupt */
  SVC_IRQn                    = -5,                /*!< Cortex-M0 SV Call Interrupt */
  PendSV_IRQn                 = -2,                /*!< Cortex-M0 Pend SV Interrupt */
  SysTick_IRQn                = -1,                /*!< Cortex-M0 System Tick Interrupt */
#endif /* interrupts */

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
  CM33_MAILBOX_IRQn           = 0,
  CM0_MAILBOX_IRQn            = 1,
  I2S0_IRQn                   = 4,
  I2S1_IRQn                   = 5,
  USB_HS_IRQn                 = 6,
  USB_FS_IRQn                 = 7,
  OSPI0_IRQn                  = 8,
  OSPI1_IRQn                  = 9,
  FLASHA_IRQn                 = 10,
  FLASHB_IRQn                 = 11,
  ISO78160_1_IRQn             = 12,
  MEM_ECC_IRQn                = 13,
  BTMR0_IRQn                  = 14,
  BTMR1_IRQn                  = 15,
  BTMR2_IRQn                  = 16,
  BTMR3_IRQn                  = 17,
  BPWM0_IRQn                  = 18,
  BPWM1_IRQn                  = 19,
  BPWM2_IRQn                  = 20,
  BPWM3_IRQn                  = 21,
  SDIO0_IRQn                  = 22,
  SDIO1_IRQn                  = 23,
  RNG_IRQn                    = 24,
  EADC_IRQn                   = 25,
  SCR_IRQn                    = 26,
  CAN0_IRQn                   = 27,
  CAN1_IRQn                   = 28,
  ETMR0_UP_IRQn                = 29,
  ETMR0_BRK_IRQn               = 30,
  ETMR0_CC_IRQn                = 31,
  ETMR0_TRG_COM_IRQn           = 32,
  ETMR1_UP_IRQn                = 33,
  ETMR1_BRK_IRQn               = 34,
  ETMR1_CC_IRQn                = 35,
  ETMR1_TRG_COM_IRQn           = 36,
  GTMR0_IRQn                   = 37,
  GTMR1_IRQn                   = 38,
  GTMR2_IRQn                   = 39,
  GTMR3_IRQn                   = 40,
  DMA0_CH0_IRQn               = 41,
  DMA0_CH1_IRQn               = 42,
  DMA0_CH2_IRQn               = 43,
  DMA0_CH3_IRQn               = 44,
  DMA0_CH4_IRQn               = 45,
  DMA0_CH5_IRQn               = 46,
  DMA0_CH6_IRQn               = 47,
  DMA0_CH7_IRQn               = 48,
  ADC0_IRQn                   = 51,
  ADC1_IRQn                   = 52,
  ENCENG_IRQn                 = 53,
  MAC0_SBD_IRQn               = 54,
  MAC0_PMT_IRQn               = 55,
  MAC1_SBD_IRQn               = 56,
  MAC1_PMT_IRQn               = 57,
  DCMI_IRQn                   = 58,
  CDMA_ADC_IRQn               = 59,
  FLEXCOMM0_IRQn              = 60,
  FLEXCOMM1_IRQn              = 61,
  FLEXCOMM2_IRQn              = 62,
  FLEXCOMM3_IRQn              = 63,
  FLEXCOMM4_IRQn              = 64,
  FLEXCOMM5_IRQn              = 65,
  FLEXCOMM6_IRQn              = 66,
  FLEXCOMM7_IRQn              = 67,
  FLEXCOMM8_IRQn              = 68,
  FLEXCOMM9_IRQn              = 69,
  FLEXCOMM10_IRQn             = 70,
  FLEXCOMM11_IRQn             = 71,
  FLEXCOMM12_IRQn             = 72,
  FLEXCOMM13_IRQn             = 73,
  DMA1_CH0_IRQn               = 74,
  DMA1_CH1_IRQn               = 75,
  DMA1_CH2_IRQn               = 76,
  DMA1_CH3_IRQn               = 77,
  DMA1_CH4_IRQn               = 78,
  DMA1_CH5_IRQn               = 79,
  DMA1_CH6_IRQn               = 80,
  DMA1_CH7_IRQn               = 81,
  EXTI0_IRQn                  = 82,
  EXTI1_IRQn                  = 83,
  EXTI2_IRQn                  = 84,
  EXTI3_IRQn                  = 85,
  EXTI4_IRQn                  = 86,
  EXTI5_IRQn                  = 87,
  EXTI6_IRQn                  = 88,
  EXTI7_IRQn                  = 89,
  EXTI8_IRQn                  = 90,
  EXTI9_IRQn                  = 91,
  EXTI10_IRQn                 = 92,
  EXTI11_IRQn                 = 93,
  EXTI12_IRQn                 = 94,
  EXTI13_IRQn                 = 95,
  EXTI14_IRQn                 = 96,
  EXTI15_IRQn                 = 97,
#endif /* V32F20XXX_CM33_CORE0 && V32F20XXX_CM33_CORE1 */
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
  I2C14_IRQn                  = 98,
  BDMA_IRQn                   = 99,
  UART14_IRQn                 = 100,
  UART15_IRQn                 = 101,
  UART16_IRQn                 = 102,
  UART17_IRQn                 = 103,
  UART18_IRQn                 = 104,
  UART19_IRQn                 = 105,
  ISO78162_IRQn               = 106,
  ISO78163_IRQn               = 107,
  BTMR4_IRQn                  = 108,
  BTMR5_IRQn                  = 109,
  BTMR6_IRQn                  = 110,
  BTMR7_IRQn                  = 111,
  BPWM4_IRQn                  = 112,
  BPWM5_IRQn                  = 113,
  BPWM6_IRQn                  = 114,
  BPWM7_IRQn                  = 115,
  FLASH0_IRQn                 = 116,
  BSPI0_IRQn                  = 117,
  BSPI1_IRQn                  = 118,
  BSPI2_IRQn                  = 119,
  BSPI3_IRQn                  = 120,
  BSPI4_IRQn                  = 121,
  BSPI5_IRQn                  = 122,
  HFM_COP_IRQn                = 123,
  RTC_IRQn                    = 124,
  PMU_IRQn                    = 125,
  RTC_ALM_IRQn                = 126,
  SYSCFGLP_ANA_IRQn          = 127,
  LPBTMR_IRQn                 = 128,
  COMP_IRQn                   = 130,
#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */
#if defined (V32F20XXX_CM0_CORE)
  PMU_IRQn                    = 0 ,
  I2C14_IRQn                  = 1 ,
  BDMA_IRQn                   = 2 ,
  UART14_IRQn                 = 3 ,
  UART15_IRQn                 = 4 ,
  UART16_IRQn                 = 5 ,
  UART17_IRQn                 = 6 ,
  UART18_IRQn                 = 7 ,
  UART19_IRQn                 = 8 ,
  ISO78162_IRQn               = 9 ,
  ISO78163_IRQn               = 10,
  MEM_ECC_IRQn                = 11,
  BTMR4_5_IRQn                = 12,
  BTMR6_IRQn                  = 13,
  BTMR7_IRQn                  = 14,
  BPWM4_IRQn                  = 15,
  BPWM5_IRQn                  = 16,
  BPWM6_IRQn                  = 17,
  BPWM7_IRQn                  = 18,
  HFM_COP_IRQn                = 19,
  BSPI0_IRQn                  = 20,
  BSPI1_IRQn                  = 21,
  BSPI2_IRQn                  = 22,
  BSPI3_IRQn                  = 23,
  BSPI4_IRQn                  = 24,
  BSPI5_IRQn                  = 25,
  FLASH0_IRQn                 = 26,
  RTC_RTCALM_IRQn             = 27,
  MAILBOX_IRQn                = 28,
  GPIO_IRQn                   = 29,
  SYSCFGLP_ANA_CMP_IRQn      = 30,
  LPBTMR_IRQn                 = 31,
#endif /* V32F20XXX_CM0_CORE */
} IRQn_Type;

#if defined (V32F20XXX_CM33_CORE0)
#define __SAUREGION_PRESENT       1U        /* SAU regions present */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U        /* FPU present */
#define __DSP_PRESENT             1U        /* DSP extension present */
#include "core_cm33.h"                      /* Core Peripheral Access Layer */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#include "system_target_cm33_core0_s.h"     /* Device specific configuration file */
#else
#include "system_target_cm33_core0.h"       /* Device specific configuration file */
#endif
#endif /* V32F20XXX_CM33_CORE0 */

#if defined (V32F20XXX_CM33_CORE1)
#define __SAUREGION_PRESENT       0U        /* SAU regions present */
#define __MPU_PRESENT             0U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0U        /* FPU present */
#define __DSP_PRESENT             0U        /* DSP extension present */
#include "core_cm33.h"                      /* Core Peripheral Access Layer */
#include "system_target_cm33_core1.h"       /* Device specific configuration file */
#endif /* V32F20XXX_CM33_CORE1 */

#if defined (V32F20XXX_CM0_CORE)
 #define __Vendor_SysTickConfig         0         /*!< target uses systick config */
 #define __NVIC_PRIO_BITS               2         /*!< target uses 2 Bits for the Priority Levels */
 #include "core_cm0.h"
 #include "system_target_cm0.h"                   /* Device specific configuration file */
#endif /* V32F20XXX_CM0_CORE */


#if defined ( __CC_ARM )
#  pragma anon_unions
#endif /* __CC_ARM */


/** 
  * @brief ISO7816 Controller
  */
typedef struct
{
       uint32_t RESERVED1;    /*!< Reserved,                                                            0x00 */
  __IO uint32_t BAUDDIVL;     /*!< ISO7816 x  baud-rate low byte register,              Address offset: 0x04 */
  __IO uint32_t BAUDDIVH;     /*!< ISO7816 x  baud-rate high byte register,             Address offset: 0x08 */
  __IO uint32_t DATA;         /*!< ISO7816 x  data register,                            Address offset: 0x0C */
  __IO uint32_t INFO;         /*!< ISO7816 x  information register,                     Address offset: 0x10 */
  __IO uint32_t CFG;          /*!< ISO7816 x  control register,                         Address offset: 0x14 */
  __IO uint32_t CLK;
} ISO7816_Type;



typedef struct {
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000000) SPI Control Register.                                      */
  __IOM uint32_t  TXSTS;                        /*!< (@ 0x00000004) SPI Transmit Status Register.                              */
  __IOM uint32_t  TXDAT;                        /*!< (@ 0x00000008) SPI Transmit FIFO register.                                */
  __IOM uint32_t  RXSTS;                        /*!< (@ 0x0000000C) SPI Receive Status Register.                               */
  __IM  uint32_t  RXDAT;                        /*!< (@ 0x00000010) SPI Receive FIFO Register.                                 */
  __IOM uint32_t  MISC;                         /*!< (@ 0x00000014) SPI Misc. Control Register.                                */
}BSPI_Type;  

/**
  * @brief CRC (CRC)
  */
  
typedef struct {                                /*!< (@ 0x20300000) CRC Structure                                              */
  __IOM uint32_t  MODE;                         /*!< (@ 0x00000000) MODE                                                       */
  __IOM uint32_t  SEED;                         /*!< (@ 0x00000004) SEED                                                       */
  __IM  uint32_t  SUM;                          /*!< (@ 0x00000008) SUM                                                        */
  __IOM uint32_t  WR_DATA;                      /*!< (@ 0x0000000C) WR_DATA                                                    */
  __IM  uint32_t  STATUS;                       /*!< (@ 0x00000010) STATUS                                                     */
  __IO  uint32_t  RESERVED[2];                  /*!< (@ 0x00000014-18) RESERVED                                                */
  __IOM uint32_t  IO_OUT;                       /*!< (@ 0x0000001C) IO_OUT                                                     */
} CRC_Type;                                     /*!< Size = 32 (0x20)                                                          */

/**
  * @brief RNG (RNG)
  */

typedef struct {                                /*!< (@ 0x40060100) RNG Structure                                              */
  __IO uint32_t IMR;                            /*!< (@ 0x00000000) RNG interrupt mask register.                               */
  __IO uint32_t ISR;                            /*!< (@ 0x00000004) RNG interrupt status register.                             */
  __IO uint32_t ICR;                            /*!< (@ 0x00000008) RNG interrupt clear register.                              */
  __IO uint32_t CFG;                            /*!< (@ 0x0000000C) RNG config register.                                       */
       uint32_t RESERVED1;                      /*!< (@ 0x00000010) Reserved.                                                  */
  __IO uint32_t DATA[6];                        /*!< (@ 0x00000014) RNG data register 0~5.                                       */
  __IO uint32_t CMD;                            /*!< (@ 0x0000002C) RNG source enable register.                                */
  __IO uint32_t CNT;                            /*!< (@ 0x00000030) RNG sample counter register.                               */
       uint32_t RESERVED2;                      /*!< (@ 0x00000034) Reserved.                                                  */
  __IO uint32_t BYPASS;                         /*!< (@ 0x00000038) RNG testing bypass register.                               */
} RNG_Type;

/**
  * BTMR (BTMR)
  */

typedef struct {
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000000) Control register of Timer x                                */
  __IOM uint32_t  VALUE;                        /*!< (@ 0x00000004) Current count register of Timer x                          */
  __IOM uint32_t  RELOAD;                       /*!< (@ 0x00000008) Reload register of Timer x.                                */
  __IOM uint32_t  INTSTS;                       /*!< (@ 0x0000000C) Interrupt status register of Timer x.                      */
} BTMR_Type;

/**
  * PWM (PWM)
  */
typedef struct {
  __IOM uint32_t  CTL;                          /*!< (@ 0x00000000) Control register of PWM Timer 0                            */
  __IM  uint32_t  TAR;                          /*!< (@ 0x00000004) Current count register of PWM Timer x.                     */
  __IOM uint32_t  CCTL[3];                      /*!< (@ 0x00000008) Compare/capture control register x(x=0~3) for
                                                                    PWM timer x.                                               */
  __IOM uint32_t  CCR[3];                       /*!< (@ 0x00000014) Compare/capture data register x for PWM timer
                                                                    x.                                                         */
} BPWM_Type;
/**
  * @brief Timers are 16 bits timers with PWM and capture function. (PWM_SEL)
  */
typedef struct {
  __IOM uint32_t  O_SEL;                        /*!< (@ 0x00000000) PWM output selection register.                             */
  __IOM uint32_t  I_SEL01;                      /*!< (@ 0x00000004) Input of PWM0 and PWM1 selection register.                 */
  __IOM uint32_t  I_SEL23;                      /*!< (@ 0x00000008) Input of PWM2 and PWM3 selection register.                 */
} BPWM_SEL_Type;


/**
  * @brief CAN (CAN)
  */
typedef struct {                                /*!< (@ 0x40080000) CAN Structure                                              */
  __IOM uint32_t  MOD;                          /*!< (@ 0x00000000) Mode                                                       */
  __OM  uint32_t  CMR;                          /*!< (@ 0x00000004) Command                                                    */
  __IM  uint32_t  SR;                           /*!< (@ 0x00000008) Status                                                     */
  __IM  uint32_t  IR;                           /*!< (@ 0x0000000C) Interrupt                                                  */
  __IOM uint32_t  IER;                          /*!< (@ 0x00000010) Interrupt enable                                           */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  BTR0;                         /*!< (@ 0x00000018) Bus Timing 0                                               */
  __IOM uint32_t  BTR1;                         /*!< (@ 0x0000001C) Bus Timing 1                                               */
  __IOM uint32_t  OCR;                          /*!< (@ 0x00000020) Output Control Register                                    */
  __IM  uint32_t  RESERVED1[2];
  __IM  uint32_t  ALC;                          /*!< (@ 0x0000002C) Arbitration Lost Capture                                   */
  __IM  uint32_t  ECC;                          /*!< (@ 0x00000030) Error Code Capture                                         */
  __IOM uint32_t  EWLR;                         /*!< (@ 0x00000034) Error Warning Limit                                        */
  __IOM uint32_t  RXERR;                        /*!< (@ 0x00000038) Receive Error Counter                                      */
  __IOM uint32_t  TXERR;                        /*!< (@ 0x0000003C) CAN TX error register                                      */
  
  union {
    __IM  uint32_t RXBUF[13];                   /*!< (@ 0x00000040) RX buffer register                                         */
    __OM  uint32_t TXBUF[13];                   /*!< (@ 0x00000040) TX buffer register                                         */
    struct{                                     /*!< (@ 0x00000040) ACR and AMR Registers                                      */
      __IOM uint32_t ACR[4];
      __IOM uint32_t AMR[4];
    }ACCEPT;
  };
  __IM  uint32_t  RMC;                          /*!< (@ 0x00000074) Receive Message Counter                                    */
  __IOM uint32_t  RBSA;                         /*!< (@ 0x00000078) Receive Buffer Start Address                               */
  __IOM uint32_t  CDR;                          /*!< (@ 0x0000007C) Clock Divider                                              */
  __IM  uint32_t  RXFIFO[64];                   /*!< (@ 0x00000080~0x0000017C       */
  __IM  uint32_t  TXFIFO[13];                   /*!< (@ 0x00000180~0x000001B0       */
} CAN_Type;                                     /*!< Size = 128 (0x80)                                                         */


/**
  * @brief SCR (SCR) // @2021-06-16
  */
typedef struct {                                /*!< (@ 0x40070000) SCR Structure                                              */
  __IOM uint32_t  APB0PPC_SEC;                  /*!< (@ 0x00000000) APB0PPC security config                                   */
  __IOM uint32_t  APB0PPC_AP;                   /*!< (@ 0x00000004) APB0PPC access privilage config                           */
  __IOM uint32_t  APB0PPC_RESP;                 /*!< (@ 0x00000008) APB0PPC security error response config                    */
  __IOM uint32_t  APB0PPC_SEC1;                 /*!< (@ 0x0000000C) APB0PPC security config1                                  */
  __IOM uint32_t  APB0PPC_AP1;                  /*!< (@ 0x00000010) APB0PPC access privilage config1                          */
  __IOM uint32_t  APB0PPC_SYNC_SEC;             /*!< (@ 0x00000014) APB0PPC_SYNC non-security config                          */
  __IOM uint32_t  APB0PPC_SYNC_AP;              /*!< (@ 0x00000018) APB0PPC_SYNC access privilage config                      */
  __IOM uint32_t  APB0PPC_SYNC_RESP;            /*!< (@ 0x0000001C) APB0PPC_SYNC security error response config               */
  __IOM uint32_t  DMA0_SEC;                     /*!< (@ 0x00000020) DMA0 security config                                       */
  __IOM uint32_t  DMA0_AP;                      /*!< (@ 0x00000024) DMA0 access privilage config                               */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  DMA1_SEC;                     /*!< (@ 0x00000030) DMA1 security config                                       */
  __IOM uint32_t  DMA1_AP;                      /*!< (@ 0x00000034) DMA1 access privilage config                               */
  __IM  uint32_t  RESERVED1[2];
  __IOM uint32_t  ETH0_SEC;                     /*!< (@ 0x00000040) MAC0 non-security config                                   */
  __IOM uint32_t  ETH0_AP;                      /*!< (@ 0x00000044) MAC0 access privilage config                               */
  __IM  uint32_t  RESERVED2[2];
  __IOM uint32_t  ETH1_SEC;                     /*!< (@ 0x00000050) MAC1 non-security config                                   */
  __IOM uint32_t  ETH1_AP;                      /*!< (@ 0x00000054) MAC1 access privilage config                               */
  __IM  uint32_t  RESERVED3[2]; 
  __IOM uint32_t  ENCENG_SEC;                   /*!< (@ 0x00000060) ENCENG non-security config                                 */
  __IOM uint32_t  ENCENG_AP;                    /*!< (@ 0x00000064) ENCENG access privilage config                             */
  __IM  uint32_t  RESERVED4[6]; // 0x68 ~ 0x6C
  __IOM uint32_t  SDIO0_SEC;                    /*!< (@ 0x00000080) SDIO0 non-security config                                  */
  __IOM uint32_t  SDIO0_AP;                     /*!< (@ 0x00000084) SDIO0 access privilage config                              */
  __IM  uint32_t  RESERVED6[2]; // 0x88 ~ 0x8C
  __IOM uint32_t  SDIO1_SEC;                    /*!< (@ 0x00000090) SDIO1 non-security config                                  */
  __IOM uint32_t  SDIO1_AP;                     /*!< (@ 0x00000094) SDIO1 access privilage config                              */
  __IM  uint32_t  RESERVED7[2]; // 0x98 ~ 0x9C
  __IOM uint32_t  OSPI0_SEC;                    /*!< (@ 0x000000A0) OSPI0 non-security config                                   */
  __IOM uint32_t  OSPI0_AP;                     /*!< (@ 0x000000A4) OSPI0 access privilage config                               */
  __IOM uint32_t  OSPI0_RESP;                   /*!< (@ 0x000000A8) OSPI0 security error response config                        */
  __IM  uint32_t  RESERVED8;
  __IOM uint32_t  OSPI1_SEC;                    /*!< (@ 0x000000B0) OSPI1 non-security config                                   */
  __IOM uint32_t  OSPI1_AP;                     /*!< (@ 0x000000B4) OSPI1 access privilage config                               */
  __IOM uint32_t  OSPI1_RESP;                   /*!< (@ 0x000000B8) OSPI1 security error response config                        */
  __IM  uint32_t  RESERVED9;
  __IOM uint32_t  M0BRIDGE_SEC;                 /*!< (@ 0x000000C0) M0BRIDGE non-security config                               */
  __IOM uint32_t  M0BRIDGE_AP;                  /*!< (@ 0x000000C4) M0BRIDGE access privilage config                           */
  __IOM uint32_t  M0BRIDGE_RESP;                /*!< (@ 0x000000C8) M0BRIDGE security error response config                    */
  __IM  uint32_t  RESERVED10;
  __IOM uint32_t  USBHS_SEC;                    /*!< (@ 0x000000D0) USBHS non-security config                                  */
  __IOM uint32_t  USBHS_AP;                     /*!< (@ 0x000000D4) USBHS access privilage config                              */
  __IOM uint32_t  USBHS_RESP;                   /*!< (@ 0x000000D8) USBHS security error response config                       */
  __IM  uint32_t  RESERVED11;
  __IOM uint32_t  USBFS_SEC;                    /*!< (@ 0x000000E0) USBFS non-security config                                  */
  __IOM uint32_t  USBFS_AP;                     /*!< (@ 0x000000E4) USBFS access privilage config                              */
  __IOM uint32_t  USBFS_RESP;                   /*!< (@ 0x000000E8) USBFS security error response config                       */
  __IM  uint32_t  RESERVED12;
  __IOM uint32_t  IRQ;                          /*!< (@ 0x000000F0) SCR security violation interrupt                           */
  __IOM uint32_t  INT_EN;                       /*!< (@ 0x000000F4) SCR violation interrupt enable register                    */
  __IM  uint32_t  BUSY;                         /*!< (@ 0x000000F8) The status of SCR configuration                            */
} SCR_Type;                                     /*!< Size = 252 (0xfc)                                                         */


/**
  * @brief DAC (DAC)
  */
typedef struct {                                /*!< (@ 0x400A0000) DAC Structure                                              */
  __IOM uint32_t  CR;                           /*!< (@ 0x00000000) DAC_CR                                                     */
  __IOM uint32_t  SWTRGR;                       /*!< (@ 0x00000004) DAC_SWTRGR                                                 */
  __IOM uint32_t  DHR12R1;                      /*!< (@ 0x00000008) DAC_DHR12R1                                                */
  __IOM uint32_t  DHR12L1;                      /*!< (@ 0x0000000C) DAC_DHR12L1                                                */
  __IOM uint32_t  DHR8R1;                       /*!< (@ 0x00000010) DAC_DHR8R1                                                 */
  __IOM uint32_t  DHR12R2;                      /*!< (@ 0x00000014) DAC_DHR12R2                                                */
  __IOM uint32_t  DHR12L2;                      /*!< (@ 0x00000018) DAC_DHR12L2                                                */
  __IOM uint32_t  DHR8R2;                       /*!< (@ 0x0000001C) DAC_DHR8R2                                                 */
  __IOM uint32_t  DHR12RD;                      /*!< (@ 0x00000020) DAC_DHR12RD                                                */
  __IOM uint32_t  DHR12LD;                      /*!< (@ 0x00000024) DAC_DHR12LD                                                */
  __IOM uint32_t  DHR8RD;                       /*!< (@ 0x00000028) DAC_DHR8RD                                                 */
  __IM  uint32_t  DOR1;                         /*!< (@ 0x0000002C) DAC_DOR1                                                   */
  __IM  uint32_t  DOR2;                         /*!< (@ 0x00000030) DAC_DOR2                                                   */
} DAC_Type;                                     /*!< Size = 52 (0x34)                                                          */



/**
  * @brief EADC (External ADC)
  */
typedef struct
{                                    /*!< (@ 0x400A0800) External ADC Structure                                  */
  __IO uint32_t CFG;                 /*!< (@ 0x00000000) External ADC configure register                         */  
  __IO uint32_t CP0;                 /*!< (@ 0x00000004) External ADC capture point register                     */
  __IO uint32_t CP1;                 /*!< (@ 0x00000008) External ADC capture point register                     */
  __IO uint32_t INTSTS;              /*!< (@ 0x0000000c) External ADC stataus register                           */
  __IO uint32_t INTEN;               /*!< (@ 0x00000010) External ADC interrupt mask register                    */
  __IO uint32_t RESERVED[3];         
  __IO uint32_t DR;                  /*!< (@ 0x00000020) External ADC data register                              */
} EADC_Type;


/** 
  * @brief CDMA analog to Digital Converter  
  */
typedef struct
{                                        /*!< (@ 0x400A1800) CDMA_ADC Structure                                    */
  __IO uint32_t CSR;                     /*!< (@ 0x00000000) CDMA_ADC contrtol register                            */
  __IO uint32_t CFG;                     /*!< (@ 0x00000004) CDMA_ADC config register                              */
  __IO uint32_t STS;                     /*!< (@ 0x0000008) CDMA_ADC Stataus register                              */ 
  __IO uint32_t DATA[4];                 /*!< (@ [0x0000000c,0x00000018] CDMA_ADC the conversion resultl           */
  __IM uint32_t RESERVED;
  __IO uint32_t DATA1[4];
} CDMA_ADC_Type;

/**
  * @brief SYSCFG0 (SYSCFG0)
  */

typedef struct {                                /*!< (@ 0x40200000) SYSCFG0 Structure                                         */
  __IOM uint32_t  SRAMINT_STS;                  /*!< (@ 0x00000000) SRAM Parity Error Interrupt status                         */
  __IOM uint32_t  SRAM_INIT;                    /*!< (@ 0x00000004) SRAM initialize and PE configuration                       */
  __IOM uint32_t  SRAM_CTRL0;                   /*!< (@ 0x00000008) sram control register0                                     */
  __IOM uint32_t  SRAM_CTRL1;                   /*!< (@ 0x0000000C) sram control register1                                     */
  __IOM uint32_t  FLASHA_CTRL;                  /*!< (@ 0x00000010) Flasha control register                                    */
  __IOM uint32_t  FLASH_DUAL_BANK_SW;           /*!< (@ 0x00000014) Dual Bank Flash switch Register                            */
  __IOM uint32_t  FLASH_TEST_CTRL;              /*!< (@ 0x00000018) flash test control register                                */
  __IOM uint32_t  FLASHB_CTRL;                  /*!< (@ 0x0000001C) Flashb control register                                    */
  __IOM uint32_t  FLASHA_SRAM_CTRL0;            /*!< (@ 0x00000020) Flasha sram control register0                              */
  __IOM uint32_t  FLASHB_SRAM_CTRL0;            /*!< (@ 0x00000024) Flashb sram control register0                              */
  __IOM uint32_t  USB_SRAM_CTRL;                /*!< (@ 0x00000028) USB sram control register                                  */
  __IOM uint32_t  SDIO_SRAM_CTRL;               /*!< (@ 0x0000002C) SDIO sram control register                                 */
  __IOM uint32_t  CM33_SUBBOOT_SEC_ADDR;        /*!< (@ 0x00000030) sub cm33 core security boot address                        */
  __IOM uint32_t  CM33_SUBBOOT_NSEC_ADDR;       /*!< (@ 0x00000034) sub cm33 core nonsecurity boot address                     */
  __IOM uint32_t  SW_CM33_0_RST;                /*!< (@ 0x00000038) CM33_0 Soft Reset Request Register                         */
  __IOM uint32_t  SW_CM33_1_RST;                /*!< (@ 0x0000003C) CM33_1 Soft Reset Request Register                         */
  __IOM uint32_t  CM0_NONSEC_CFG;               /*!< (@ 0x00000040) Cm33 config CM0 non-security transfer                      */
  __IOM uint32_t  SW_RST0_REQ;                  /*!< (@ 0x00000044) Soft Reset Request Register                                */
  __IOM uint32_t  SW_RST1_REQ;                  /*!< (@ 0x00000048) Soft Reset Request Register                                */
  __IOM uint32_t  CM33_WAIT;                    /*!< (@ 0x0000004C) CM33 wait control register                                 */
  __IOM uint32_t  CM33_SYS_DSLEEPEN;            /*!< (@ 0x00000050) Cm33 enable cm33_sys enter deepsleep mode                  */
  __IOM uint32_t  CM33_SYS_SLEEPEN;             /*!< (@ 0x00000054) Cm33 enable cm33_sys enter sleep mode                      */
  __IOM uint32_t  CM33_CORE0_STCALIB;           /*!< (@ 0x00000058) CM33_CORE0 SysTick Calibration Register                    */
  __IOM uint32_t  CM33_DEBUG;                   /*!< (@ 0x0000005C) CM33 Debug CFG Register                                    */
  __IOM uint32_t  CM33_LOCK_RST_EN;             /*!< (@ 0x00000060) Reset CM33 control when lockup occurred                    */
  __IOM uint32_t  CM33_WIC;                     /*!< (@ 0x00000064) CM33 WIC control register                                  */
  __IOM uint32_t  CM33_CORE1_STCALIB;           /*!< (@ 0x00000068) CM33_CORE1 SysTick Calibration Register                    */
  __IOM uint32_t  CM33_CFG;                     /*!< (@ 0x0000006C) CM33 config register                                       */
  __IOM uint32_t  MAC_SRAM_CTRL;                /*!< (@ 0x00000070) MAC sram control register                                  */
  __IOM uint32_t  MAC_CTRL;                     /*!< (@ 0x00000074) MAC control register                                       */
  __IOM uint32_t  CAN_CTRL;                     /*!< (@ 0x00000078) CAN control Register                                       */
  __IOM uint32_t  OSPI_CTRL;                    /*!< (@ 0x0000007C) OSPI control and status register                            */
  __IOM uint32_t  OSPI_SCLK_SEL;                /*!< (@ 0x00000080) OSPI sclk source select register                            */
  __IOM uint32_t  OSPI_SCLK_DIV;                /*!< (@ 0x00000084) OSPI sclk divider register                                  */
  __IOM uint32_t  I2S_CLK_SEL;                  /*!< (@ 0x00000088) I2S clk source select register                             */
  __IOM uint32_t  I2S_CLK_DIV;                  /*!< (@ 0x0000008C) I2S clk divider register                                   */
  __IOM uint32_t  I2S_MCK_CTRL;                 /*!< (@ 0x00000090) I2S mck control register                                   */
  __IOM uint32_t  ROM_CTRL;                     /*!< (@ 0x00000094) rom control register                                       */
  __IOM uint32_t  ENCENG_CTRL;                  /*!< (@ 0x00000098) ENCENG control register                                    */
  __IOM uint32_t  SDIO_CTRL;                    /*!< (@ 0x0000009C) SDIO control register                                      */
  __IOM uint32_t  FC_CTRL[2];                   /*!< (@ 0x000000A0) FC control Register0                                       */
  __IOM uint32_t  FC_SCLK_DIV[4];               /*!< (@ 0x000000A8) FC_SCLK divider control register0                          */
  __IOM uint32_t  FC_SCLK_SEL[2];               /*!< (@ 0x000000B8) FC_SCLK select register0                                   */
  __IOM uint32_t  CM33_MAIN_EXTI_CLR;           /*!< (@ 0x000000C0) main cm33 exti interrupt clear register                    */
  __IOM uint32_t  CM33_SUB_EXTI_CLR;            /*!< (@ 0x000000C4) sub cm33 exti interrupt clear register                     */
  __IOM uint32_t  TIMER_CFG;                    /*!< (@ 0x000000C8) timer config register                                      */
  __IM  uint32_t  RESERVED;
  __IM  uint32_t  MEM_ECC_STS1;                 /*!< (@ 0x000000D0) memory ECC status register1                                */
  __IM  uint32_t  MEM_ECC_STS2;                 /*!< (@ 0x000000D4) memory ECC status register2                                */
  __IOM uint32_t  MEM_ECC_INT_CLR;              /*!< (@ 0x000000D8) Register0000 Abstract                                      */
  __IOM uint32_t  MEM_ECC_INT_EN;               /*!< (@ 0x000000DC) Memory ECC interrupt enable register                       */
  __IOM uint32_t  ADC_CLK_SEL;                  /*!< (@ 0x000000E0) ADC clk source select register                             */
  __IOM uint32_t  ADC_CLK_DIV;                  /*!< (@ 0x000000E4) ADC clock divider value                                    */
  __IOM uint32_t  ADC_TRG_SEL;                  /*!< (@ 0x000000E8) ADC trigger source select register                         */
  __IOM uint32_t  CDMA_ADC_CLK_SEL;             /*!< (@ 0x000000EC) CDMA ADC clk source select register                        */
  __IOM uint32_t  CDMA_ADC_CLK_DIV;             /*!< (@ 0x000000F0) CDMA ADC clock divider value                               */
  __IOM uint32_t  ADDA_REF_CFG;                 /*!< (@ 0x000000F4) ADC and DAC reference voltage config                       */
  __IOM uint32_t  ADDA_REF_TRIM;                /*!< (@ 0x000000F8) ADC and DAC reference voltage trim                         */
  __IOM uint32_t  TRIM_UNLOCK;                  /*!< (@ 0x000000FC) TRIM_UNLOCK Abstract                                       */
  __IOM uint32_t  MEM_SIZE_M33;                 /*!< (@ 0x00000100) flash and sram in sys_cm33 size config                     */
  __IOM uint32_t  IP_CONFIG;                    /*!< (@ 0x00000104) IP config register                                         */
  __IOM uint32_t  FLASH_WR_PRT_CTRL;            /*!< (@ 0x00000108) Flash infor page writer protect control register           */
  __IOM uint32_t  ENCENG_FLASH_PROT;            /*!< (@ 0x0000010C) ENCENG and flash read protect                              */
  __IOM uint32_t  ROM_CFG_LOCK;                 /*!< (@ 0x00000110) Registers configed in ROM lock control                     */
  __IOM uint32_t  ROM_SW_CFG_LOCK;              /*!< (@ 0x00000114) Registers configed in ROM lock control                     */
  __IOM uint32_t  CORE1_CODESNP_START_ADDR;     /*!< (@ 0x00000118) Sub CM33 code snooper re-start address register            */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  DMA0_REQ_SEL0;                /*!< (@ 0x00000120) DMA0 request select register0                              */
  __IOM uint32_t  DMA0_REQ_SEL1;                /*!< (@ 0x00000124) DMA0 request select register1                              */
  __IOM uint32_t  DMA0_REQ_SEL2;                /*!< (@ 0x00000128) DMA0 request select register2                              */
  __IOM uint32_t  DMA0_REQ_SEL3;                /*!< (@ 0x0000012C) DMA0 request select register3                              */
  __IOM uint32_t  DMA1_REQ_SEL0;                /*!< (@ 0x00000130) DMA1 request select register0                              */
  __IOM uint32_t  DMA1_REQ_SEL1;                /*!< (@ 0x00000134) DMA1 request select register1                              */
  __IOM uint32_t  DMA1_REQ_SEL2;                /*!< (@ 0x00000138) DMA1 request select register2                              */
  __IOM uint32_t  DMA1_REQ_SEL3;                /*!< (@ 0x0000013C) DMA1 request select register3                              */
  __IOM uint32_t  CLK_SEL;                      /*!< (@ 0x00000140) Clock selection register.                                  */
  __IOM uint32_t  HCLK_DIV;                     /*!< (@ 0x00000144) AHB Bus clock divider control register                     */
  __IOM uint32_t  PCLK_DIV;                     /*!< (@ 0x00000148) APB clock divider control register                         */
  __IOM uint32_t  CLK_EN1;                      /*!< (@ 0x0000014C) IP clock enable control register1                          */
  __IOM uint32_t  CLK_EN2;                      /*!< (@ 0x00000150) IP clock enable control register2                          */
  __IOM uint32_t  PCLK_EN_TMR;                  /*!< (@ 0x00000154) Timer APB clock enable control register                    */
  __IOM uint32_t  DAC_CLK_SEL;                  /*!< (@ 0x00000158) DAC clk source select register                             */
  __IOM uint32_t  DAC_CLK_DIV;                  /*!< (@ 0x0000015C) DAC clk divider register                                   */
  __IOM uint32_t  EADC_CLK_SEL;                 /*!< (@ 0x00000160) EADC clk source select register                            */
  __IOM uint32_t  EADC_CLK_DIV;                 /*!< (@ 0x00000164) EADC clk divider register                                  */
  __IOM uint32_t  USB0_CLK_SEL;                 /*!< (@ 0x00000168) USBHS clk source select register                           */
  __IOM uint32_t  USB0_CLK_DIV;                 /*!< (@ 0x0000016C) USBHS clk divider register                                 */
  __IOM uint32_t  USB1_CLK_SEL;                 /*!< (@ 0x00000170) USBFS clk source select register                           */
  __IOM uint32_t  USB1_CLK_DIV;                 /*!< (@ 0x00000174) USBFS clk divider register                                 */
  __IOM uint32_t  MB_DUALM33_EXC;               /*!< (@ 0x00000178) main and sub cm33 exclusion mailbox register               */
  __IOM uint32_t  MB_DUALM33_INT;               /*!< (@ 0x0000017C) main and sub cm33 mailbox interrupt set                    */
  __IOM uint32_t  MB_DUALM33_INTCLR;            /*!< (@ 0x00000180) main and sub cm33 mailbox interrupt clr                    */
  __IOM uint32_t  MB_M33ToM0_INT;               /*!< (@ 0x00000184) main cm33 and cm0 mailbox interrupt set                    */
  __IOM uint32_t  MB_M0ToM33_INT;               /*!< (@ 0x00000188) main cm0 to cm33 mailbox interrupt clear and
                                                                       interrupt status                                        */
  __IOM uint32_t  MB_INT_MASK;                  /*!< (@ 0x0000018C) all the mailbox interrupt mask register                    */
  __IOM uint32_t  FC_I2S_SEL;                   /*!< (@ 0x00000190) flexcomm and i2s function selection                        */
  __IOM uint32_t  SW_SYSLP_CTRL;                /*!< (@ 0x00000194) SYSLP control register                                     */
  __IOM uint32_t  DBG_CFG;                      /*!< (@ 0x00000198) debug mode config register                                 */
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  SYSCON_PASSWD;                /*!< (@ 0x000001A0) Write access protect password Register                     */
  __IM  uint32_t  RESERVED3[3];
  __IOM uint32_t  TIMER0_SEL;                   /*!< (@ 0x000001B0) Timer clk select register                                  */
  __IOM uint32_t  TIMER0_DIV[2];                /*!< (@ 0x000001B4) Timer0 cmsdk divider config register                       */
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  M33_SW_REG;
} SYSCFG0_Type;                                /*!< Size = 444 (0x1bc)                                                        */

/**
  * @brief SYS_CON0 (SYS_CON0)
  */
typedef struct {
  __IOM uint32_t SRAMINT;                      /*!< (@ 0x00000000                                                               */
  __IOM uint32_t SRAMINIT;                     /*!< (@ 0x00000004                                                               */
  __IOM uint32_t IREN;                         /*!< (@ 0x00000008                                                               */
  __IOM uint32_t UARTEN;                       /*!< (@ 0x0000000c                                                               */
  __IOM uint32_t EGYCFEN;                      /*!< (@ 0x00000010                                                               */
  __IM  uint32_t RESERVED0;                    /*!< (@ 0x00000014                                                               */
  __IOM uint32_t PASSWD;                       /*!< (@ 0x00000018                                                               */
  __IOM uint32_t SRAM_CTRL0;                   /*!< (@ 0x0000001c                                                               */
  __IOM uint32_t SRAM_CTRL1;                   /*!< (@ 0x00000020                                                               */
  __IOM uint32_t FLASH_SRAM_CTRL;              /*!< (@ 0x00000024                                                               */
  __IOM uint32_t M0_INT_MASK;                  /*!< (@ 0x00000028                                                               */
  __IM  uint32_t RESERVED1[3];                 /*!< (@ 0x0000002c-0x34                                                          */
  __IOM uint32_t UART_SCLK_DIV2;               /*!< (@ 0x00000038                                                               */
  __IOM uint32_t FLASHTEST;                    /*!< (@ 0x0000003c                                                               */
  __IOM uint32_t FLASHWC;                      /*!< (@ 0x00000040                                                               */
  __IOM uint32_t CLKSEL;                       /*!< (@ 0x00000044                                                               */
  __IOM uint32_t CLKDIVH;                      /*!< (@ 0x00000048                                                               */
  __IOM uint32_t CLKDIVP;                      /*!< (@ 0x0000004c                                                               */
  __IOM uint32_t UART_SCLK_DIV1;               /*!< (@ 0x00000050                                                               */
  __IM  uint32_t RESERVED2;                    /*!< (@ 0x00000054                                                               */
  __IOM uint32_t CLKEN1;                       /*!< (@ 0x00000058                                                               */
  __IOM uint32_t CLKEN2;                       /*!< (@ 0x0000005c                                                               */
  __IOM uint32_t SW_RST_REQ;                   /*!< (@ 0x00000060                                                               */
  __IOM uint32_t M0_IVT_BADDR;                 /*!< (@ 0x00000064                                                               */
  __IOM uint32_t M0_STCALIB;                   /*!< (@ 0x00000068                                                               */
  __IOM uint32_t M0_CFG;                       /*!< (@ 0x0000006c                                                               */
  __IM  uint32_t RESERVED3;                    /*!< (@ 0x00000070                                                               */
  __IOM uint32_t I2C_SCLK_DIV;                 /*!< (@ 0x00000074                                                               */
  __IOM uint32_t M0_SEC_CTRL;                  /*!< (@ 0x00000078                                                               */
  __IOM uint32_t IR_DUTY;                      /*!< (@ 0x0000007c                                                               */
  __IOM uint32_t MB_M0ToM33_INT;               /*!< (@ 0x00000080                                                               */
  __IOM uint32_t MB_M33ToM0_INTCLR;            /*!< (@ 0x00000084                                                               */
  __IOM uint32_t MB_INT_MASK;                  /*!< (@ 0x00000088                                                               */
  __IOM uint32_t MB_M33ToM0_STS;               /*!< (@ 0x0000008c                                                               */
  __IOM uint32_t MEM_ECC_STS;                  /*!< (@ 0x00000090                                                               */
  __IOM uint32_t INT_MEM_ECC;                  /*!< (@ 0x00000094                                                               */
  __IOM uint32_t MEM_ECC_INT_EN;               /*!< (@ 0x00000098                                                               */
  __IM  uint32_t RESERVED4;                    /*!< (@ 0x0000009c                                                               */
  __IOM uint32_t CM0_NONSEC_REG;               /*!< (@ 0x000000a0                                                               */
  __IM  uint32_t RESERVED5[3];                 /*!< (@ 0x000000a4-0x000000ac                                                    */
  __IOM uint32_t TIMER0_SEL;                   /*!< (@ 0x000000b0                                                               */
  __IOM uint32_t TIMER0_DIV[2];                /*!< (@ 0x000000b4                                                               */
} SYSCFG1_Type;

/**
  * @brief ENCENG (ENCENG)
  */
typedef struct {
  uint32_t RESERVED1;                            /*!< (@ 0x00000000) Reserved                                                   */
  __IOM uint32_t CFG;                            /*!< (@ 0x00000004) ENCENG configuration register.                             */ 
  __IOM uint32_t CMD;                            /*!< (@ 0x00000008) ENCENG command register.                                   */
  uint32_t RESERVED2;                            /*!< (@ 0x0000000C) Reserved                                                   */
  __IOM uint32_t SRCLEN;                         /*!< (@ 0x00000010) Source data length register.                               */
  __IOM uint32_t SRCADDR;                        /*!< (@ 0x00000014) Source data address register.                              */
  __IOM uint32_t DSTADDR;                        /*!< (@ 0x00000018) Destination data address register.                         */
  __IM  uint32_t RESERVED;                       /*!< (@ 0x0000001C) Reserved                                                   */
  __IOM uint32_t INTMASK;                        /*!< (@ 0x00000020) ENCENG interrupt mask register.                            */
  __IOM uint32_t INTSTS;                         /*!< (@ 0x00000024) ENCENG interrupt status register.                          */
  __IM  uint32_t RESERVED3[2];                  
  __IOM uint32_t KEY[4][8];                      /*!< (@ 0x00000030) ENCENG key register.                                       */
} ENCENG_Type;

/**
  * @brief FLASH Register (FLASH)
  */
typedef struct {
  __IOM  uint32_t  CHCHE_CCR;
  __IOM  uint32_t  CHCHE_SR;
  __IOM  uint32_t  CHCHE_IRQMASK;
  __IOM  uint32_t  CHCHE_IRQSTAT;
  __IOM  uint32_t  CHCHE_HWPARAMS;
  __IOM  uint32_t  CHCHE_CSHR;
  __IOM  uint32_t  CHCHE_CSMR;
	__IM   uint32_t  RESERVED[1017];
  __IOM  uint32_t  SFC_SPEC_CTRL;
  __IOM  uint32_t  SFC_INT_EN;
  __IOM  uint32_t  SFC_INT_STS;
  __IOM  uint32_t  SFC_STATUS;
  __IOM  uint32_t  SFC_R_TAS;
  __IOM  uint32_t  SFC_R_TPWS;
  __IOM  uint32_t  SFC_R_TACC;
  __IOM  uint32_t  SFC_R_TXYH;
  __IOM  uint32_t  SFC_W_TWPR;
  __IOM  uint32_t  SFC_W_TNVS;
  __IOM  uint32_t  SFC_W_TPGS;
  __IOM  uint32_t  SFC_W_TPROG;
  __IOM  uint32_t  SFC_W_TPGH;
  __IOM  uint32_t  SFC_W_TWHD;
  __IOM  uint32_t  SFC_W_TADS;
  __IOM  uint32_t  SFC_W_TADH;
  __IOM  uint32_t  SFC_W_TRCH;
  __IOM  uint32_t  SFC_W_TERASE;
  __IOM  uint32_t  SFC_W_TME;
  __IOM  uint32_t  SFC_W_TNVH;
  __IOM  uint32_t  SFC_W_TNVH1;
  __IOM  uint32_t  SFC_S_TWK;
  __IOM  uint32_t  SFC_INFO_ADDR;
  __IOM  uint32_t  SFC_INFO_DATA[4];
  __IOM  uint32_t  SFC_INFO_WR_CTRL;
  __IOM  uint32_t  SFC_INFO_WR_START;
  __IM   uint32_t  RESERVED1[2];
  __IOM  uint32_t  SFC_REPAIR_REG0;
  __IOM  uint32_t  SFC_REPAIR_REG1;
  __IM   uint32_t  RESERVED2;
  __IOM  uint32_t  SFC_WAIT_NXT_READ_CYCLES;
  __IOM  uint32_t  SFC_INFO_STATUS;
  __IOM  uint32_t  SFC_POWRER_CFG;
  __IM   uint32_t  RESERVED32[987];
  __IOM  uint32_t  IRQ_ENABLE_SET;
  __IOM  uint32_t  IRQ_ENABLE_CLR;
  __IOM  uint32_t  IRQ_STATUS_SET;
  __IOM  uint32_t  IRQ_STATUS_CLR;
  __IOM  uint32_t  IRQ_STATUS;
  __IOM  uint32_t  CTRL;
  __IOM  uint32_t  STATUS;
  __IOM  uint32_t  ADDR;
  __IOM  uint32_t  DATA[4];
} FLASH_Type;


/**
  * @brief WAVER Register (WAVER0)
  */
typedef struct {                                /*!< (@ 0x21014000) WAVER Structure                                            */
  __IM  uint32_t  RESERVED[8];
  __IOM uint32_t  CFG;                          /*!< (@ 0x00000020) WAVER0 configuration register                              */
  __IM  uint32_t  RESERVED1[3];
  __IOM uint32_t  MODE;                         /*!< (@ 0x00000030) WAVER0 mode configuration register                         */
  __IM  uint32_t  RESERVED2[3];
  __IOM uint32_t  DATA;                         /*!< (@ 0x00000040) WAVER0 data register                                       */
  __IOM uint32_t  DATABAK;                      /*!< (@ 0x00000044) WAVER0 backup data register                                */
  __IM  uint32_t  RESERVED3;
  __IOM uint32_t  INFO;                         /*!< (@ 0x0000004C) WAVER0 information register                                */
  __IOM uint32_t  STATE;                        /*!< (@ 0x00000050) WAVER0 state register                                      */
} WAVER0_Type;  

/**
  * @brief HFM Register (HFM)
  */
typedef struct {
  __IOM uint32_t  DEVID;
  __IOM uint32_t  CFG;
  __IOM uint32_t  STS;
  __IOM uint32_t  EXCH_BADDR;
  __IOM uint32_t  WAVE_BADDR;
  __IOM uint32_t  DSPINSTR_BADDR;
  __IOM uint32_t  DSPEXCH_BADDR;
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  CMD;
  __IOM uint32_t  INTEN;
  __IOM uint32_t  INTSTS;
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  EGY_CONST0;
  __IOM uint32_t  EGY_CONST1;
  __IOM uint32_t  EGY_CONST2;
  __IOM uint32_t  DSP_CFG;
  __IOM uint32_t  EGY_CFG;
  __IOM uint32_t  EGY_PROCTH;
  __IOM uint32_t  EGY_PWRTH0;
  __IOM uint32_t  EGY_PWRTH1;
  __IOM uint32_t  EGY_CFDIVTH;
  __IOM uint32_t  EGY_CLR;
  __IM  uint32_t  RESERVED3;
  __IOM uint32_t  EGY_CLKDIV;
  __IOM uint32_t  EGY_OUTL0;
  __IOM uint32_t  EGY_OUTH0;
  __IOM uint32_t  EGY_OUTL1;
  __IOM uint32_t  EGY_OUTH1;
  __IOM uint32_t  EGY_OUTL2;
  __IOM uint32_t  EGY_OUTH2;
  __IOM uint32_t  EGY_CFCNT0;
  __IOM uint32_t  EGY_CFCNT1;
  __IOM uint32_t  EGY_CFCNT2;
  __IM  uint32_t  RESERVED4[3];
  __IOM uint32_t  EGY_CRPSTS;
  __IOM uint32_t  PWROVTHH;
  __IOM uint32_t  PWROVTHL;
  __IM  uint32_t  RESERVED5;
  __IOM uint32_t  DSPCALICFGADDR;  //0xA0
  __IM  uint32_t  RESERVED6[55];
  __IOM uint32_t  POWERVALUE[27];
} HFM_Type;


/**
  * @brief SDIO Register (SDIO33)
  */
typedef struct {
  __IOM uint32_t  INFO;                   /*!< (@ 0x00000000) General Information                                      */
  __IOM uint32_t  DEBOUNCE;               /*!< (@ 0x00000004) Configure De-bounce                                      */
  __IOM uint32_t  CTRL0;                  /*!< (@ 0x00000008) CTRL0                                                    */
  __IOM uint32_t  RESERVED0;              /*!< (@ 0x0000000C) Reserved                                                 */
  __IOM uint32_t  PHY;                    /*!< (@ 0x00000010) PHY                                                      */
  __IM  uint32_t  RESERVED1;              /*!< (@ 0x00000014) Reserved                                                 */
  __IOM uint32_t  MODE;                   /*!< (@ 0x00000018) MODE                                                     */
  __IOM uint32_t  IODELAY;                /*!< (@ 0x0000001C) IO DELAY                                                 */
  __IM  uint32_t  RESERVED2[22];          /*!< (@ 0x00000020~0x00000074) Reserved                                      */
  __IOM uint32_t  INFO1;                  /*!< (@ 0x00000078) Information                                              */
  __IOM uint32_t  INFO2;                  /*!< (@ 0x0000007c) Information                                              */
  __IOM uint32_t  FSMM;                   /*!< (@ 0x00000080) FSMM                                                     */
  __IOM uint32_t  STATUS0;                /*!< (@ 0x00000084) STATUS0                                                  */
  __IOM uint32_t  STATUS1;                /*!< (@ 0x00000088) STATUS1                                                  */
  __IOM uint32_t  TUNE_REQ;               /*!< (@ 0x0000008C) Tune Force Request                                       */
  __IOM uint32_t  BOOTERR;                /*!< (@ 0x00000090) Boot Error                                               */
  __IOM uint32_t  SPEED;                  /*!< (@ 0x00000094) Speed                                                    */
  __IOM uint32_t  BLOCKGAP;               /*!< (@ 0x00000098) Read block gap                                           */
  __IM  uint32_t  RESERVED3[24];          /*!< (@ 0x0000009C~0x000000F8) Reserved                                      */
  __IOM uint32_t  CRS63;                  /*!< (@ 0x000000FC) Host Controller Version/Slot Interrupt Status            */
  __IM  uint32_t  RESERVED4[64];          /*!< (@ 0x0000009C~0x000000F8) Reserved                                      */
  __IOM uint32_t  ADDR;
  __IOM uint32_t  BLOCK_COUNT;
  __IOM uint32_t  ARG;
  __IOM uint32_t  CMD;
  __IOM uint32_t  RESP1;
  __IOM uint32_t  RESP2;
  __IOM uint32_t  RESP3;
  __IOM uint32_t  RESP4;
  __IOM uint32_t  DATA;
  __IOM uint32_t  STATUS2;
  __IOM uint32_t  CTRL1;
  __IOM uint32_t  CTRL2;
  __IOM uint32_t  STATUS3;
  __IOM uint32_t  STATUS3_MASK;
  __IOM uint32_t  INTEN;
  __IOM uint32_t  ACES;
  __IOM uint32_t  CAP1;
  __IOM uint32_t  CAP2;
  __IOM uint32_t  CAP3;
  __IOM uint32_t  CAP4;
  __IOM uint32_t  FE;
  __IOM uint32_t  AES;
  __IOM uint32_t  ASSA1;
  __IOM uint32_t  ASSA2;
  __IOM uint32_t  PV1;
  __IOM uint32_t  SRS25;
  __IOM uint32_t  SRS26;
  __IOM uint32_t  SRS27;
  __IM  uint32_t  RESERVED5;
  __IOM uint32_t  PVU;
  __IM  uint32_t  RESERVED6[98];
  __IOM uint32_t  CQV;
  __IOM uint32_t  CQCAP;
  __IOM uint32_t  CQCON;
  __IOM uint32_t  CQCTL;
  __IOM uint32_t  CQIS;
  __IOM uint32_t  CQISTE;
  __IOM uint32_t  CQISIE;
  __IOM uint32_t  IC;
  __IOM uint32_t  CQTDLBA;
  __IOM uint32_t  CQTDLBAU;
  __IOM uint32_t  CQTD;
  __IOM uint32_t  TCN;
  __IOM uint32_t  DQS;
  __IOM uint32_t  DPT;
  __IOM uint32_t  TC;
  __IM  uint32_t  RESERVED7;
  __IOM uint32_t  SSC1;
  __IOM uint32_t  SSC2;
  __IOM uint32_t  CRDCT;
  __IOM uint32_t  RMEM;
  __IOM uint32_t  TEI;
  __IOM uint32_t  CRI;
  __IOM uint32_t  CRA;
} SDIO_TypeDef;


/**
  * @brief ADC (ADC)
  */

typedef struct {                                /*!< (@ 0x400A1000) ADC Structure                                             */
  __IOM uint32_t  STS;                          /*!< (@ 0x00000000) ADC status register                                        */
  __IOM uint32_t  CTRL1;                        /*!< (@ 0x00000004) ADC_control\_register1                                     */
  __IOM uint32_t  CTRL2;                        /*!< (@ 0x00000008) ADC_control\_register2                                     */
  __IOM uint32_t  SMPT1;                        /*!< (@ 0x0000000C) ADC_sample\_time\_register1                                */
  __IOM uint32_t  SMPT2;                        /*!< (@ 0x00000010) ADC_sample\_time\_register2                                */
  __IOM uint32_t  JOFS1;                        /*!< (@ 0x00000014) ADC_injected\_channel\_data\_offset\_register              */
  __IOM uint32_t  JOFS2;                        /*!< (@ 0x00000018) ADC_injected\_channel\_data\_offset\_register              */
  __IOM uint32_t  JOFS3;                        /*!< (@ 0x0000001C) ADC_injected\_channel\_data\_offset\_register              */
  __IOM uint32_t  JOFS4;                        /*!< (@ 0x00000020) ADC_injected\_channel\_data\_offset\_register              */
  __IOM uint32_t  WHTR;                         /*!< (@ 0x00000024) ADC watchdog high threshold register                       */
  __IOM uint32_t  WLTR;                         /*!< (@ 0x00000028) ADC watchdog low threshold register                        */
  __IOM uint32_t  RSQ1;                         /*!< (@ 0x0000002C) ADC regular sequence register 1                            */
  __IOM uint32_t  RSQ2;                         /*!< (@ 0x00000030) ADC regular sequence register 2                            */
  __IOM uint32_t  RSQ3;                         /*!< (@ 0x00000034) ADC regular sequence register 3                            */
  __IOM uint32_t  JSQ;                          /*!< (@ 0x00000038) ADC injected sequence register                             */
  __IM  uint32_t  JDOR1;                        /*!< (@ 0x0000003C) ADC injected data register 1                               */
  __IM  uint32_t  JDOR2;                        /*!< (@ 0x00000040) ADC injected data register 2                               */
  __IM  uint32_t  JDOR3;                        /*!< (@ 0x00000044) ADC injected data register 3                               */
  __IM  uint32_t  JDOR4;                        /*!< (@ 0x00000048) ADC injected data register 4                               */
  __IM  uint32_t  RDOR;                         /*!< (@ 0x0000004C) ADC regular data register                                  */
  __IOM uint32_t  CFG;                          /*!< (@ 0x00000050) Some configure for sar adc                                 */
} ADC_Type;                                     /*!< Size = 84 (0x54)                                                          */


/**
  * @brief SYSCFGLP (SYSCFGLP)
  */

typedef struct {                                /*!< (@ 0x40102000) SYSCFGLP Structure                                        */
  __IOM uint32_t  SW_RST_REQ;                   /*!< (@ 0x00000000) SYS_LP soft reset request register                         */
  __IOM uint32_t  TRIM_UNLOCK;                  /*!< (@ 0x00000004) TRIM Register unlock                                       */
  __IOM uint32_t  XOH_CTRL0;                    /*!< (@ 0x00000008) XOH control register0                                      */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  RCH_CTRL0;                    /*!< (@ 0x00000010) RCH control register0                                      */
  __IOM uint32_t  RCH_CTRL1;                    /*!< (@ 0x00000014) RCH freqency triming control register1                     */
  __IOM uint32_t  RCH_CTRL2;                    /*!< (@ 0x00000018) RCH control register2                                      */
  __IOM uint32_t  PLL0_CTRL0;                   /*!< (@ 0x0000001C) PLL0 control register                                      */
  __IOM uint32_t  PLL0_CTRL1;                   /*!< (@ 0x00000020) PLL0 control register                                      */
  __IM  uint32_t  PLL0_CTRL2;                   /*!< (@ 0x00000024) PLL0 control register2                                     */
  __IOM uint32_t  PLL1_CTRL0;                   /*!< (@ 0x00000028) PLL1 control register0                                     */
  __IOM uint32_t  PLL1_CTRL1;                   /*!< (@ 0x0000002C) PLL1 control register1                                     */
  __IOM uint32_t  PLL1_CTRL2;                   /*!< (@ 0x00000030) PLL1 control register2                                     */
  __IOM uint32_t  PLL1_CTRL3;                   /*!< (@ 0x00000034) PLL1 control register3                                     */
  __IOM uint32_t  PLL1_CTRL4;                   /*!< (@ 0x00000038) PLL1 control register4                                     */
  __IOM uint32_t  WDT_RST_CTRL;                 /*!< (@ 0x0000003C) WDT reset scope control register                           */
  __IOM uint32_t  PCLK_EN;                      /*!< (@ 0x00000040) Syslp pclk enable register                                 */
  __IOM uint32_t  CLK_SEL;                      /*!< (@ 0x00000044) PMU and APB clock source control register                  */
  __IOM uint32_t  CLK_DIV;                      /*!< (@ 0x00000048) PMU and APB clock divider control register                 */
  __IOM uint32_t  PVSENS_MAIN;                  /*!< (@ 0x0000004C) PVSENS in main domain IOLATCH and DS congigure
                                                                    register                                                   */
  __IOM uint32_t  CM0_CTRL;                     /*!< (@ 0x00000050) Cm0 control register                                       */
  __IOM uint32_t  ANA_LOCK;                     /*!< (@ 0x00000054) Analog lock register                                       */
  __IOM uint32_t  PWR_STS;                      /*!< (@ 0x00000058) Power status register                                      */
  __IOM uint32_t  PWR_INT_CLR;                  /*!< (@ 0x0000005C) Power status interrupt clear register                      */
  __IOM uint32_t  TRIM;                         /*!< (@ 0x00000060) IP in syslp trim register                                  */
  __IOM uint32_t  MPMU_CFG1;                    /*!< (@ 0x00000064) Main PMU config register1                                  */
  __IOM uint32_t  MPMU_CFG2;                    /*!< (@ 0x00000068) Main PMU config register2                                  */
  __IOM uint32_t  MPMU_CFG3;                    /*!< (@ 0x0000006C) Main PMU config register3                                  */
  __IM  uint32_t  MPMU_STS;                     /*!< (@ 0x00000070) Main PMU status register                                   */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  MPMU_TEST;                    /*!< (@ 0x00000078) MPMU test register                                         */
  __IOM uint32_t  RETRAM_CTRL;                  /*!< (@ 0x0000007C) retram control register                                    */
  __IOM uint32_t  AUTOTRIM_CTRL;                /*!< (@ 0x00000080) rch autotrim control register                              */
  __IOM uint32_t  AUTOTRIM_UPPER_EXPT;          /*!< (@ 0x00000084) autotrim upper expect value register                       */
  __IOM uint32_t  AUTOTRIM_LOWER_EXPT;          /*!< (@ 0x00000088) autotrim lower expect value register                       */
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  CLKOUT[4];                    /*!< (@ 0x00000090) Chip clock source output config register                   */
  __IOM uint32_t  DBG_CTRL;                     /*!< (@ 0x000000A0) debug ctrol register                                       */
  __IOM uint32_t  XTAL_EXIST_CTRL;              /*!< (@ 0x000000A4) xtal exist interrupt and wku enable control register       */
  __IOM uint32_t  XTAL_EXIST_INT_CLR;           /*!< (@ 0x000000A8) XTAL EXIST interrupt clear register                        */
  __IOM uint32_t  CM33_MAIN_CODE_SNOOPER_CTRL;  /*!< (@ 0x000000AC) Main cm33 code snooper control register                    */
  __IOM uint32_t  CM33_SUB_CODE_SNOOPER_CTRL;   /*!< (@ 0x000000B0) Sub cm33 code snooper control register                     */
  __IOM uint32_t  CM0_CODE_SNOOPER_CTRL;        /*!< (@ 0x000000B4) CM0 code snooper control register                          */
  __IOM uint32_t  MEM_SIZE_M0;                  /*!< (@ 0x000000B8) flash and sram in sys_cm0 size config                      */
  __IM  uint32_t  RESERVED3;
  __IOM uint32_t  APBPPCLP_SEC;                 /*!< (@ 0x000000C0) APBPPCLP non-security config                               */
  __IOM uint32_t  APBPPCLP_AP;                  /*!< (@ 0x000000C4) APBPPCLP access privilage config                           */
  __IOM uint32_t  APBPPCLP_RESP;                /*!< (@ 0x000000C8) APBPPCLP security error response config                    */
  __IM  uint32_t  RESERVED4[5];
  __IOM uint32_t  CORE_CONFIG;                  /*!< (@ 0x000000E0) core config register                                       */
  __IOM uint32_t  FLASH_PRT_CTRL;               /*!< (@ 0x000000E4) Flash infor page protect control register                  */
  __IM  uint32_t  RESERVED5;
  __IOM uint32_t  ROM_CFG_LOCK;                 /*!< (@ 0x000000EC) Registers configed in ROM lock control                     */
  __IM  uint32_t  REV_ID;                       /*!< (@ 0x000000F0) version ID register                                        */
} SYSCFGLP_Type;                               /*!< Size = 244 (0xf4)                                                         */

/**
  * @brief PMU (PMU)
  */
typedef struct {                                /*!< (@ 0x41100800) PMU Structure                                             */
  __IOM uint32_t  CM0_DSLPEN;                   /*!< (@ 0x00000000) CM0 sys deep sleep enable register                        */
  __IOM uint32_t  CM0_DSLPPSWD;                 /*!< (@ 0x00000004) CM0 sys deep sleep password register                      */
  __IOM uint32_t  CM0_SLPEN;                    /*!< (@ 0x00000008) CM0 sleep enable register                                 */
  __IOM uint32_t  CM33_DSLPEN;                  /*!< (@ 0x0000000C) CM33 sys deep sleep enable register                       */
  __IOM uint32_t  CM33_DSLPPSWD;                /*!< (@ 0x00000010) CM33 sys deep sleep password register                     */
  __IOM uint32_t  CM33_SLPEN;                   /*!< (@ 0x00000014) CM33 sleep enable register                                */
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000018) PMU control register                                      */
  __IOM uint32_t  STS;                          /*!< (@ 0x0000001C) PMU Status register                                       */
  __IOM uint32_t  CM0PWRSTS;                    /*!< (@ 0x00000020) CM0 power status register                                 */
  __IOM uint32_t  CM33PWRSTS;                   /*!< (@ 0x00000024) CM33 power status register                                */
  __IOM uint32_t  WKUINT;                       /*!< (@ 0x00000028) wakeup interrupt register                                 */
  __IOM uint32_t  WAITCYCLE;                    /*!< (@ 0x0000002C) wait cycle register                                       */
  __IOM uint32_t  IO_WKU_EN;                    /*!< (@ 0x00000030)   register           */
  __IOM uint32_t  UART32K_0_CFG;                /*!< (@ 0x00000034) UART 32K #0 Configuration Register                        */
  __IOM uint32_t  UART32K_1_CFG;                /*!< (@ 0x00000038) UART 32K #1 Configuration Register                        */
  __IOM uint32_t  RETRAMCFG;                    /*!< (@ 0x0000003C) Retention RAM Configuration Register                      */
  __IOM uint32_t  RETRAMSTS;                    /*!< (@ 0x00000040) Retention RAM status Register                             */
} PMU_Type;                                     /*!< Size = 280 (0x118)                                                       */

typedef struct {                                /*!< (@ 0x40100000) RETRAM Structure                                          */  
  __IOM uint8_t  RAM[256];
} RETRAM_Type;

/**
  * @brief RTC_ALM (RTC_ALM)
  */
typedef struct {                             /*!< (@ 0x40102800) RTC_ALM Structure                                          */
  __IOM uint32_t  WKUSEC;                    /*!< (@ 0x00000000) This register is used to control the multi-second
                                                                 wake-up function.                                          */
  __IOM uint32_t  WKUMIN;                    /*!< (@ 0x00000004) This register is used to control the multi-minute
                                                                 wake-up function.                                          */
  __IOM uint32_t  WKUHOUR;                   /*!< (@ 0x00000008) This register is used to control the multi-hour
                                                                 wake-up function.                                          */
  __IOM uint32_t  WKUCNT;                    /*!< (@ 0x0000000C) This is register is used to set the counter clock
                                                                 and counter value of WKUCNT.                               */
  __IOM uint32_t  ITV;                       /*!< (@ 0x00000010) This register is used to control wake-up and
                                                                 interrupt interval of RTC.                                 */
  __IOM uint32_t  SITV;                      /*!< (@ 0x00000014) Multi second wake-up interval control register.            */
  __IOM uint32_t  ALARMTIME;                 /*!< (@ 0x00000018) Used to control the accurate second and millisecond
                                                                 alarm function.                                            */
  __IOM uint32_t  ALARMSEC;                  /*!< (@ 0x0000001C) Used to control the inaccurate second alarm function.      */
  __IOM uint32_t  ALARMMIN;                  /*!< (@ 0x00000020) Used to control the minute alarm function.                 */
  __IOM uint32_t  ALARMHOUR;                 /*!< (@ 0x00000024) Used to control the hour alarm function.                   */
  __IOM uint32_t  ALARMDAY;                  /*!< (@ 0x00000028) Used to control the day alarm function.                    */
  __IOM uint32_t  ALARMMONTH;                /*!< (@ 0x0000002C) Used to control the month alarm function.                  */
  __IOM uint32_t  ALARMYEAR;                 /*!< (@ 0x00000030) Used to control the year alarm function.                   */
  __IOM uint32_t  ALARMCTL;                  /*!< (@ 0x00000034) Alarm function contol register.                            */
  __IOM uint32_t  INTEN;                     /*!< (@ 0x00000038) Interrupt enable.                                          */
  __IOM uint32_t  INTSTS;                    /*!< (@ 0x0000003C) Interrupt status.                                          */
  __IM  uint32_t  WKUCNTR;                   /*!< (@ 0x00000040) This register is used to represent the current
                                                                 WKUCNT value.                                              */
  __IOM uint32_t  CFGVALID;                  /*!< (@ 0x00000044) Config of wakeup and alarm starts to be valid.             */
  __IM  uint32_t  STS;                       /*!< (@ 0x00000048) RTC wakeup or alarm config status.                         */
  __IOM uint32_t  DIVCAPCTRL;                /*!< (@ 0x0000004C) High-frequency clock divide and second pulse capture 
                                                                 control register                                           */
  __IOM uint32_t  PLLDIV;                    /*!< (@ 0x00000050) PLL divider register                                       */
} RTCALM_Type;    /*!< Size = 84 (0x54)                                                          */


/**
  * @brief RTC (RTC)
  */
typedef struct {                                /*!< (@ 0x40103000) RTC Structure                                              */
  __IOM uint32_t  SEC;                          /*!< (@ 0x00000000) RTC second time register.                                  */
  __IOM uint32_t  MIN;                          /*!< (@ 0x00000004) RTC minute time register.                                  */
  __IOM uint32_t  HOUR;                         /*!< (@ 0x00000008) RTC hour time register.                                    */
  __IOM uint32_t  DAY;                          /*!< (@ 0x0000000C) RTC day time register.                                     */
  __IOM uint32_t  WEEK;                         /*!< (@ 0x00000010) RTC week time register.                                    */
  __IOM uint32_t  MON;                          /*!< (@ 0x00000014) RTC month time register.                                   */
  __IOM uint32_t  YEAR;                         /*!< (@ 0x00000018) RTC year time register.                                    */
  __IOM uint32_t  TIME;                         /*!< (@ 0x0000001C) RTC accurate second/millisecond time.                      */
  __IM  uint32_t  PLL_DIV_AC;                   /*!< (@ 0x00000020) RTC pll divider value after aoto calibration
                                                                    compensation.                                              */
  __IM  uint32_t  RESERVED[3];
  __IOM uint32_t  CAL;                          /*!< (@ 0x00000030) RTC calibration register.                                  */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000038) RTC control register.                                      */
  __IM  uint32_t  RESERVED2[2];
  __IOM uint32_t  PWD;                          /*!< (@ 0x00000044) This register is used to protect the RTC_CE port's
                                                                    access.                                                    */
  __IOM uint32_t  CE;                           /*!< (@ 0x00000048) Unlock the access of RTC register.                         */
  __IOM uint32_t  LOAD;                         /*!< (@ 0x0000004C) RTC read data register.                                    */
  __IOM uint32_t  INTSTS;                       /*!< (@ 0x00000050) RTC interrupt status.                                      */
  __IOM uint32_t  INTEN;                        /*!< (@ 0x00000054) RTC interrupt enable.                                      */
  __IOM uint32_t  WKUSEC;                       /*!< (@ 0x00000058) Used to control the second wakeup function.                */
  __IOM uint32_t  WKUMIN;                       /*!< (@ 0x0000005C) Used to control the minute wku function.                   */
  __IOM uint32_t  WKUHOUR;                      /*!< (@ 0x00000060) Used to control the hour wku function.                     */
  __IOM uint32_t  WKUDAY;                       /*!< (@ 0x00000064) Used to control the day wku function.                      */
  __IOM uint32_t  WKUMONTH;                     /*!< (@ 0x00000068) Used to control the month wku function.                    */
  __IOM uint32_t  WKUYEAR;                      /*!< (@ 0x0000006C) Used to control the year wku function.                     */
  __IOM uint32_t  WKUCTRL;                     /*!< (@ 0x00000070) Used to control the wku config infomation.                 */
  __IM  uint32_t  RESERVED3[3];
  __IOM uint32_t  ACCTRL;                       /*!< (@ 0x00000080) RTC calibration control register.                          */
  __IOM uint32_t  ACTI;                         /*!< (@ 0x00000084) Auto-calibration Ti control register.                      */
  __IOM uint32_t  ACF200;                       /*!< (@ 0x00000088) Auto-calibration F200 control register.                    */
  __IOM uint32_t  ACADCW;                       /*!< (@ 0x0000008C) Auto-calibration manual ADC value control register.        */
  __IOM uint32_t  ACP0;                         /*!< (@ 0x00000090) The P0 registers are used for auto-calibration.            */
  __IOM uint32_t  ACP1;                         /*!< (@ 0x00000094) The P1 registers are used for auto-calibration.            */
  __IOM uint32_t  ACP2;                         /*!< (@ 0x00000098) The P2 registers are used for auto-calibration.            */
  __IM  uint32_t  ACP3;                         /*!< (@ 0x0000009C) The P3 registers are used for auto-calibration.            */
  __IOM uint32_t  ACP4;                         /*!< (@ 0x000000A0) The P4 registers are used for auto-calibration.            */
  __IOM uint32_t  ACP5;                         /*!< (@ 0x000000A4) The P5 registers are used for auto-calibration.            */
  __IOM uint32_t  ACP6;                         /*!< (@ 0x000000A8) The P6 registers are used for auto-calibration.            */
  __IOM uint32_t  ACP7;                         /*!< (@ 0x000000AC) The P7 registers are used for auto-calibration.            */
  __IOM uint32_t  ACK1;                         /*!< (@ 0x000000B0) The K1~K5 registers are used for auto-calibration.         */
  __IOM uint32_t  ACK2;                         /*!< (@ 0x000000B4) The K1~K5 registers are used for auto-calibration.         */
  __IOM uint32_t  ACK3;                         /*!< (@ 0x000000B8) The K1~K5 registers are used for auto-calibration.         */
  __IOM uint32_t  ACK4;                         /*!< (@ 0x000000BC) The K1~K5 registers are used for auto-calibration.         */
  __IOM uint32_t  ACK5;                         /*!< (@ 0x000000C0) The K1~K5 registers are used for auto-calibration.         */
  __IOM uint32_t  ACTEMP;                       /*!< (@ 0x000000C4) This register is used to store the calculated
                                                                    result of current temperature.                             */
  __IM  uint32_t  ACPPM;                        /*!< (@ 0x000000C8) RTC auto-calibration calculated PPM register.              */
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  ACKTEMP;                      /*!< (@ 0x000000D0) Control different section temperature.                     */
  __IM  uint32_t  RESERVED5[5];
  __IOM uint32_t  IODECMODE;                    /*!< (@ 0x000000E8) The register is used to control the enable switch
                                                                    and mode of detecting rtc data.                            */
  __IM  uint32_t  DECDATAIO0;                   /*!< (@ 0x000000EC) The register is used to read data from RTC FIFO
                                                                    0.                                                         */
  __IM  uint32_t  DECDATAIO1;                   /*!< (@ 0x000000F0) The register is used to read data from RTC FIFO
                                                                    1.                                                         */
  __IM  uint32_t  FIFOSTS;                      /*!< (@ 0x000000F4) RTC fifo status.                                           */
} RTC_Type;                                     /*!< Size = 248 (0xf8)                                                         */


/**
  * @brief RTCANA (RTCANA)
  */
typedef struct {                                /*!< (@ 0x40103800) RTCANA Structure                                     */
  __IM  uint32_t  RESERVED0;                    /*!< (@ 0x00000000) Reserved                                                   */
  __IOM uint32_t  SWRSTPSWD;                    /*!< (@ 0x00000004) RTC soft reset password register                           */
  __IOM uint32_t  XTAL;                         /*!< (@ 0x00000008) External 32768Hz OSC control register                      */
  __IM  uint32_t  RESERVED1[4];                 /*!< (@ 0x0000000C) Reserved                                                   */
  __IOM uint32_t  ANALOCK;                      /*!< (@ 0x0000001C) Analog lock register                                       */
  __IM  uint32_t  RESERVED2[5];                 /*!< (@ 0x00000020) Reserved                                                   */
  __IOM uint32_t  RTCCTRL;                      /*!< (@ 0x00000034) RTC Analog control register                                */
  __IOM uint32_t  ADCCTRL;                      /*!< (@ 0x00000038) ADC control register                                       */
  __IOM uint32_t  ADCCTRLCFG;                   /*!< (@ 0x0000003C) ADC configuration register                                 */
  __IOM uint32_t  ADCCTRLCFG2;                  /*!< (@ 0x00000040) ADC configuration register 2                               */
  __IM  uint32_t  RESERVED3[5];                 /*!< (@ 0x00000044) Reserved                                                   */
  __IOM uint32_t  RTCCTRLPSWD;                  /*!< (@ 0x00000058) RTCCTRL access protection register                         */
  __IM  uint32_t  RESERVED4[4];                 /*!< (@ 0x0000005C) Reserved                                                   */
  __IOM uint32_t  CLKEN;                        /*!< (@ 0x0000006C) RTC Analog submodule clock enable register                 */
  __IOM uint32_t  SWRST;                        /*!< (@ 0x00000070) RTC Analog submodule soft reset register                   */
  __IOM uint32_t  CMPWKUINT;                    /*!< (@ 0x00000074) RTC CMP wakeup interrupt status register                   */
  __IOM uint32_t  CMPCFG;                       /*!< (@ 0x00000078) RTC CMP configuration register                             */
  __IOM uint32_t  GPIOMODER;                    /*!< (@ 0x0000007C) RTC GPIO port mode register                                */
  __IOM uint32_t  GPIOOTYPER;                   /*!< (@ 0x00000080) RTC GPIO port output type register                         */
  __IOM uint32_t  GPIOOSPEEDR;                  /*!< (@ 0x00000084) RTC GPIO output drive strength                             */
  __IOM uint32_t  GPIOPUPDR;                    /*!< (@ 0x00000088) RTC GPIO port pull-up and pull-down register               */
  __IM  uint32_t  GPIOIDR;                      /*!< (@ 0x0000008C) RTC GPIO port input data register                          */
  __IOM uint32_t  GPIOODR;                      /*!< (@ 0x00000090) RTC_GPIO port output data register                         */
  __IOM uint32_t  GPIOBSRR;                     /*!< (@ 0x00000094) RTC GPIO port bit set/reset register                       */
  __IOM uint32_t  GPIOLCKR;                     /*!< (@ 0x00000098) RTC GPIO port lock control register                        */
  __IOM uint32_t  GPIOAFRH;                     /*!< (@ 0x0000009C) RTC GPIO port alternate function selection register        */
  __IOM uint32_t  GPIOIS;                       /*!< (@ 0x000000A0) RTC GPIO input signal config register                      */
  __IOM uint32_t  EXTIEMRIMR;                   /*!< (@ 0x000000A4) RTC io exti wakeup mask register                           */
  __IOM uint32_t  EXTIMODE;                     /*!< (@ 0x000000A8) RTC io exti interrupt and wakerup mode config register     */
  __IOM uint32_t  EXTIPOLA;                     /*!< (@ 0x000000AC) RTC io exti interrupt and wakerup polarity config register */
  __IOM uint32_t  EXTICFG;                      /*!< (@ 0x000000B0) RTC io external input signal deglitch control register     */
  __IOM uint32_t  WKUSTS;                       /*!< (@ 0x000000B4) RTC only wakeup status register                            */
  __IOM uint32_t  TMRCFG;                       /*!< (@ 0x000000B8) RTC timer configuration register                           */
  __IOM uint32_t  TMRCNT;                       /*!< (@ 0x000000BC) RTC timer count register                                   */
  __IM  uint32_t  RESERVED5[16];;               /*!< (@ 0x000000C0) Reserved                                                   */
} RTCANA_Type;       /*!< Size = 256 (0x100)                                                        */

/**
  * @brief RTC_RAM (RTC_RAM)
  */
typedef struct
{
  __IOM uint32_t  RAM[64];
} RTC_RAM_Type;

/**
  * @brief GPIO (GPIO)
  */
typedef struct {                                /*!< (@ 0x40104000) GPIOA Structure                                            */
  __IOM uint32_t  MODER;                        /*!< (@ 0x00000000) GPIO port mode register                                    */
  __IOM uint32_t  OTYPER;                       /*!< (@ 0x00000004) GPIO_OTYPER Abstract                                       */
  __IOM uint32_t  OSPEEDR;                      /*!< (@ 0x00000008) GPIO output drive strength                                 */
  __IOM uint32_t  PUPDR;                        /*!< (@ 0x0000000C) GPIO port pull-up and pull-down register                   */
  __IM  uint32_t  IDR;                          /*!< (@ 0x00000010) GPIO port input data register                              */
  __IOM uint32_t  ODR;                          /*!< (@ 0x00000014) GPIO port output data register                             */
  __IOM uint32_t  BSRR;                         /*!< (@ 0x00000018) GPIO port bit set/reset register                           */
  __IOM uint32_t  LCKR;                         /*!< (@ 0x0000001C) GPIO_LCKR Abstract                                         */
  __IOM uint32_t  AFR[2];                       /*!< (@ 0x00000020-24) P0 to P15 Alternate function selection                  */
} GPIO_Type;                                    /*!< Size = 40 (0x28)                                                          */


/**
  * @brief IO_CTRL (IO_CTRL)
  */

typedef struct {                                /*!< (@ 0x40106400) IO_CTRL Structure                                          */
  __IOM uint32_t  IOA_IS;                       /*!< (@ 0x00000000) IOA IS signal configure register                           */
  __IOM uint32_t  IOB_IS;                       /*!< (@ 0x00000004) IOB IS signal configure register                           */
  __IOM uint32_t  IOC_IS;                       /*!< (@ 0x00000008) IOC IS signal configure register                           */
  __IOM uint32_t  IOD_IS;                       /*!< (@ 0x0000000C) IOD IS signal configure register                           */
  __IOM uint32_t  IOE_IS;                       /*!< (@ 0x00000010) IOE IS signal configure register                           */
  __IOM uint32_t  IOF_IS;                       /*!< (@ 0x00000014) IOF IS signal configure register                           */
  __IOM uint32_t  IOG_IS;                       /*!< (@ 0x00000018) IOG IS signal configure register                           */
  __IOM uint32_t  IOH_IS;                       /*!< (@ 0x0000001C) IOH IS signal configure register                           */
  __IOM uint32_t  IOI_IS;                       /*!< (@ 0x00000020) IOI IS signal configure register                           */
  __IM  uint32_t  RESERVED[3];
  __IOM uint32_t  SCATTER_IO_CFG[3];            /*!< (@ 0x00000030) SCATTER IO PE/PS signal configure register                 */
  __IM  uint32_t  RESERVED1[5];
  __IOM uint32_t  FAST_IO_CFG;                  /*!< (@ 0x00000050) Fast IO enable control                                     */
} IO_CTRL_Type;                                 /*!< Size = 84 (0x54)                                                          */

/**
  * @brief IO_EXTI (IO_EXTI)
  */
typedef struct {                                /*!< (@ 0x40106800) IO_EXTI Structure                                          */
  __IOM uint32_t  IMR;                          /*!< (@ 0x00000000) io exti interrupt mask register                            */
  __IOM uint32_t  EMR;                          /*!< (@ 0x00000004) io exti wakeup mask register                               */
  __IOM uint32_t  MODE;                         /*!< (@ 0x00000008) io exti interrupt and wakerup mode config register         */
  __IOM uint32_t  POLA;                         /*!< (@ 0x0000000C) io exti interrupt and wakerup polarity config register     */
  __IOM uint32_t  SWIER;                        /*!< (@ 0x00000010) io interrupt software control register                     */
  __IOM uint32_t  PR;                           /*!< (@ 0x00000014) io exti interrupt pending register                         */
  __IOM uint32_t  NODEG;                        /*!< (@ 0x00000018) io external input signal deglitch control register         */
  __IOM uint32_t  CR1;                          /*!< (@ 0x0000001C) exti input pin select register1                            */
  __IOM uint32_t  CR2;                          /*!< (@ 0x00000020) exti input pin select register2                            */
  __IOM uint32_t  CR3;                          /*!< (@ 0x00000024) exti input pin select register3                            */
  __IOM uint32_t  CR4;                          /*!< (@ 0x00000028) exti input pin select register4                            */
  __IOM uint32_t  WKU;                          /*!< (@ 0x0000002C) io exti iwake up state                                     */
} IO_EXTI_Type;                                 /*!< Size = 44 (0x2c)                                                          */

/**
  * @brief UART Controller (UART)
  */
typedef struct {                                /*!< (@ 0x40000000) UART Structure                                            */
  
  union {
    __IM  uint32_t RBR;                         /*!< (@ 0x00000000) Receive buffer register                                    */
    __IOM uint32_t DLL;                         /*!< (@ 0x00000000) Divisor latch low register                                 */
    __IOM uint32_t THR;                         /*!< (@ 0x00000000) Transmit holding register                                  */
  };
  
  union {
    __IOM uint32_t DLH;                         /*!< (@ 0x00000004) Divisor latch high register                                */
    __IOM uint32_t IER;                         /*!< (@ 0x00000004) Interrupt enable register                                  */
  };
  
  union {
    __IOM uint32_t FCR;                         /*!< (@ 0x00000008) FIFO control register                                      */
    __IOM uint32_t IIR;                         /*!< (@ 0x00000008) Interrupt identification register                          */
  };
  __IOM uint32_t  LCR;                          /*!< (@ 0x0000000C) Line control register                                      */
  __IOM uint32_t  MCR;                          /*!< (@ 0x00000010) Modem control register                                     */
  __IM  uint32_t  LSR;                          /*!< (@ 0x00000014) Line status register                                       */
  __IM  uint32_t  RESERVED[25];
  __IM  uint32_t  USR;                          /*!< (@ 0x0000007C) UART status register                                       */
  __IM  uint32_t  RESERVED1[16];
  __IOM uint32_t  DLF;                          /*!< (@ 0x000000C0) Divisor latch fraction register                            */
} UART_Type;                                    /*!< Size = 196 (0xc4)                                                         */


/**
  * @brief I2C Controller (I2C)
  */
typedef struct {                                /*!< (@ 0x40000000) I2C Structure                                             */
  __IOM uint32_t  CON;                          /*!< (@ 0x00000000) I2C control register                                       */
  __IOM uint32_t  TAR;                          /*!< (@ 0x00000004) I2C target address register                                */
  __IOM uint32_t  SAR;                          /*!< (@ 0x00000008) I2C slave address register                                 */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  DATACMD;                      /*!< (@ 0x00000010) I2C Rx/Tx data buffer and command register                 */
  __IOM uint32_t  SSCNTH;                       /*!< (@ 0x00000014) Standard speed I2C clock SCL high count register           */
  __IOM uint32_t  SSCNTL;                       /*!< (@ 0x00000018) Standard speed I2C clock SCL low count register            */
  __IOM uint32_t  FSCNTH;                       /*!< (@ 0x0000001C) Fast Mode or Fast Mode Plus I2C clock SCL high
                                                                    count register                                             */
  __IOM uint32_t  FSCNTL;                       /*!< (@ 0x00000020) Fast Mode or Fast Mode Plus I2C clock SCL low
                                                                    count register                                             */
  __IM  uint32_t  RESERVED1[2];
  __IM  uint32_t  INTSTS;                       /*!< (@ 0x0000002C) I2C interrupt status register                              */
  __IOM uint32_t  INTMASK;
  __IM  uint32_t  RAWINTSTS;
  __IOM uint32_t  RXTL;
  __IOM uint32_t  TXTL;
  __IM  uint32_t  INTCLR;
  __IM  uint32_t  RXUCLR;
  __IM  uint32_t  RXOCLR;                       /*!< (@ 0x00000048) Clear RX_OVER interrupt register                           */
  __IM  uint32_t  TXOCLR;                       /*!< (@ 0x0000004C) Clear TX_OVER interrupt register                           */
  __IM  uint32_t  RDREQCLR;                     /*!< (@ 0x00000050) Clear RD_REQ interrupt register                            */
  __IM  uint32_t  TXABTCLR;                     /*!< (@ 0x00000054) Clear TX_ABRT interrupt register                           */
  __IM  uint32_t  RXDONECLR;
  __IM  uint32_t  ACTCLR;
  __IM  uint32_t  STOPDETCLR;
  __IM  uint32_t  STARTDETCLR;                  /*!< (@ 0x00000064) Clear START_DET interrupt register                         */
  __IM  uint32_t  GENCALLCLR;                   /*!< (@ 0x00000068) Clear GEN_CALL interrupt register                          */
  __IOM uint32_t  ENABLE;                       /*!< (@ 0x0000006C) I2C enable register                                        */
  __IM  uint32_t  STATUS;                       /*!< (@ 0x00000070) I2C status register                                        */
  __IM  uint32_t  TXFLR;                        /*!< (@ 0x00000074) I2C transmit FIFO level register                           */
  __IM  uint32_t  RXFLR;                        /*!< (@ 0x00000078) I2C Receive FIFO Level Register                            */
  __IOM uint32_t  SDAHOLD;                      /*!< (@ 0x0000007C) I2C SDA hold time length register                          */
  __IM  uint32_t  TXABTSRC;                     /*!< (@ 0x00000080) I2C transmit abort source register                         */
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  DMACR;
  __IOM uint32_t  DMATDLR;
  __IOM uint32_t  DMARDLR;
  __IOM uint32_t  SDASETUP;                     /*!< (@ 0x00000094) I2C SDA setup register                                     */
  __IOM uint32_t  ACKGC;                        /*!< (@ 0x00000098) I2C ACK General Call register                              */
  __IM  uint32_t  ENSTS;
  __IOM uint32_t  SPKLEN;
  __IM  uint32_t  RESERVED5;
  __IM  uint32_t  RESDETCLR;                    /*!< (@ 0x000000A8) Clear RESTART_DET interrupt register                       */
  __IM  uint32_t  RESERVED6[18];
  __IOM uint32_t  COMPPARAM1;                   /*!< (@ 0x000000F4) Component Parameter register 1                             */
} I2C_Type;                                     /*!< Size = 248 (0xf8)                                                         */


/**
  * @brief SPI Controller (SPI)
  */
typedef struct {                                /*!< (@ 0x40000000) SPI Structure                                             */
  __IOM uint32_t  CTRL0;                        /*!< (@ 0x00000000) This register controls the serial data transfer.           */
  __IOM uint32_t  CTRL1;                        /*!< (@ 0x00000004) This register exists only when spi is configured
                                                                    as a master device.                                        */
  __OM  uint32_t  SSIENR;                       /*!< (@ 0x00000008) This register enables and disables the spi.                */
  __IOM uint32_t  MWCR;                         /*!< (@ 0x0000000C) This register controls the direction of the data
                                                                    word for the half-duplex Microwire serial
                                                                    protocol.                                                  */
  __IOM uint32_t  SER;                          /*!< (@ 0x00000010) This register is valid only when the spi is configured
                                                                    as a master device.                                        */
  __IOM uint32_t  BAUDR;                        /*!< (@ 0x00000014) SPI Misc. control register                                 */
  __IOM uint32_t  TXFTLR;                       /*!< (@ 0x00000018) This register controls the threshold value for
                                                                    the transmit FIFO memory.                                  */
  __IOM uint32_t  RXFTLR;                       /*!< (@ 0x0000001C) This register controls the threshold value for
                                                                    the receive FIFO memory.                                   */
  __IM  uint32_t  TXFLR;                        /*!< (@ 0x00000020) This register contains the number of valid data
                                                                    entries in the transmit FIFO memory.                       */
  __IM  uint32_t  RXFLR;                        /*!< (@ 0x00000024) This register contains the number of valid data
                                                                    entries in the receive FIFO memory.                        */
  __IM  uint32_t  SR;                           /*!< (@ 0x00000028) This is a read-only register used to indicate
                                                                    the current transfer status.                               */
  __IOM uint32_t  IMR;                          /*!< (@ 0x0000002C) This read/write reigster masks or enables all
                                                                    interrupts generated by the spi.                           */
  __IM  uint32_t  ISR;                          /*!< (@ 0x00000030) This register reports the status of the spi interrupts
                                                                    after they have been masked.                               */
  __IM  uint32_t  RISR;                         /*!< (@ 0x00000034) This read-only register reports the status of
                                                                    the spi interrupts prior to masking.                       */
  __IM  uint32_t  TXOICR;                       /*!< (@ 0x00000038) Transmit FIFO Overflow Interrupt Clear Register            */
  __IM  uint32_t  RXOICR;                       /*!< (@ 0x0000003C) Receive FIFO Overflow Interrupt Clear Register             */
  __IM  uint32_t  RXUICR;                       /*!< (@ 0x00000040) Receive FIFO Underflow Interrupt Clear Register            */
  __IM  uint32_t  MSTICR;                       /*!< (@ 0x00000044) Multi-Master Interrupt Clear Register                      */
  __IM  uint32_t  ICR;                          /*!< (@ 0x00000048) Interrupt Clear Register                                   */
  __IOM uint32_t  DMACR;                        /*!< (@ 0x0000004C) This register is only valid when spi is configured
                                                                    with a set of DMA Controller interface.                    */
  __IOM uint32_t  DMATDLR;                      /*!< (@ 0x00000050) This register is only valid when the spi is configured
                                                                    with a set of DMA interface signals.                       */
  __IOM uint32_t  DMARDLR;                      /*!< (@ 0x00000054) This register is only valid when spi is configured
                                                                    with a set of DMA interface signals.                       */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  DR;                           /*!< (@ 0x00000060) The spi data register                                      */
  __IM  uint32_t  RESERVED1[35];
  __IOM uint32_t  RX_SAMPLE_DELAY;              /*!< (@ 0x000000F0) This register is only valid when the spi is configured
                                                                    with rxd sample delay logic.                               */
  __IOM uint32_t  SPI_CTRLR0;                   /*!< (@ 0x000000F4) SPI control0 register                                      */
} SPI_Type;                                     /*!< Size = 248 (0xf8)                                                         */


/**
  * @brief OSPI Controller (OSPI)
  */
typedef struct {
  __IOM  uint32_t  CTRLR0;                      /*!< (@ 0x00000000) Control Register 0                                         */
  __IOM  uint32_t  CTRL1;                       /*!< (@ 0x00000004) Control Register 1                                         */
  __IOM  uint32_t  OSPIENR;                     /*!< (@ 0x00000008) OSPI Enable Register                                       */
  __IOM  uint32_t  MWCR;                        /*!< (@ 0x0000000C) Microwire Control Register                                 */
  __IOM  uint32_t  SER;                         /*!< (@ 0x00000010) Slave Enable Register                                      */
  __IOM  uint32_t  BAUDR;                       /*!< (@ 0x00000014) Baud Rate Select                                           */
  __IOM  uint32_t  TXFTLR;                      /*!< (@ 0x00000018) Transmit FIFO Threshold Level                              */
  __IOM  uint32_t  RXFTLR;                      /*!< (@ 0x0000001C) Receive FIFO Threshold Level                               */
  __IM   uint32_t  TXFLR;                       /*!< (@ 0x00000020) Transmit FIFO Level Register                               */
  __IM   uint32_t  RXFLR;                       /*!< (@ 0x00000024) Receive FIFO Level Register                                */
  __IM   uint32_t  SR;                          /*!< (@ 0x00000028) Status Register                                            */
  __IOM  uint32_t  IMR;                         /*!< (@ 0x0000002C) Interrupt Mask Register                                    */
  __IM   uint32_t  ISR;                         /*!< (@ 0x00000030) Interrupt Status Register                                  */
  __IM   uint32_t  RISR;                        /*!< (@ 0x00000034) Raw Interrupt Status Register                              */
  __IM   uint32_t  TXEICR;                      /*!< (@ 0x00000038) Transmit FIFO Error Interrupt Clear Registers              */
  __IM   uint32_t  RXOICR;                      /*!< (@ 0x0000003C) Receive FIFO Overflow Interrupt Clear Register             */
  __IM   uint32_t  RXUICR;                      /*!< (@ 0x00000040) Receive FIFO Underflow Interrupt Clear Register            */
  __IM   uint32_t  Reserved0;                   /*!< (@ 0x00000044) Reserved                                                   */
  __IM   uint32_t  ICR;                         /*!< (@ 0x00000048) Interrupt Clear Register                                   */
  __IOM  uint32_t  DMACR;                       /*!< (@ 0x0000004C) DMA Control Register                                       */
  __IOM  uint32_t  DMATDLR;                     /*!< (@ 0x00000050) DMA Transmit Data Level                                    */
  __IOM  uint32_t  DMARDLR;                     /*!< (@ 0x00000054) DMA Receive Data Level                                     */
  __IM   uint32_t  Reserved1;                   /*!< (@ 0x00000058) Reserved                                                   */
  __IM   uint32_t  Reserved2;                   /*!< (@ 0x0000005C) Reserved                                                   */
  __IOM  uint32_t  DR[36];                      /*!< (@ 0x00000060) OSPI Data Register                                         */
  __IOM  uint32_t  RX_SAMPLE_DELAY;             /*!< (@ 0x000000F0) RX Sample Delay Register                                   */
  __IOM  uint32_t  SPI_CTRLR0;                  /*!< (@ 0x000000F4) SPI Control Register                                       */
  __IOM  uint32_t  DDR_DRIVE_EDGE;              /*!< (@ 0x000000F8) Transmit Drive Edge Register                               */
  __IM   uint32_t  Reserved3;                   /*!< (@ 0x000000FC) Reserved                                                   */
  __IOM  uint32_t  XIP_INCR_INST;               /*!< (@ 0x00000100) XIP INCR transfer opcode                                   */
  __IOM  uint32_t  XIP_WRAP_INST;               /*!< (@ 0x00000104) XIP WRAP transfer opcode                                   */
  __IM   uint32_t  Reserved4[14];               /*!< (@ 0x00000108) Reserved                                                   */
  __IOM  uint32_t  XIP_WRITE_INCR_INST;         /*!< (@ 0x00000140) XIP Write INCR transfer opcode                             */
  __IOM  uint32_t  XIP_WRITE_WRAP_INST;         /*!< (@ 0x00000144) XIP Write WRAP transfer opcode                             */
  __IOM  uint32_t  XIP_WRITE_CTRL;              /*!< (@ 0x00000148) XIP Write Control Register                                 */
  __IM   uint32_t  RESERVED[29];                /*!< (@ 0x0000014C) Reserved                                                   */
  __IOM  uint32_t  KEY0;                        /*!< (@ 0x000001C0) OSPI Decryption Key Register 0                             */
  __IOM  uint32_t  KEY1;                        /*!< (@ 0x000001C4) OSPI Decryption Key Register 1                             */
  __IOM  uint32_t  KEY2;                        /*!< (@ 0x000001C8) OSPI Decryption Key Register 2                             */
  __IOM  uint32_t  KEY3;                        /*!< (@ 0x000001CC) OSPI Decryption key Register 3                             */
  __IOM  uint32_t  IV0;                         /*!< (@ 0x000001D0) OSPI Decryption Initial Vector Register 0                  */
  __IOM  uint32_t  IV1;                         /*!< (@ 0x000001D4) OSPI Decryption Initial Vector Register 1                  */
  __IOM  uint32_t  ENC_CFG;                     /*!< (@ 0x000001D8) OSPI Decryption Configuration Register                     */
} OSPI_Type;                                    /*!< Size = 476 (0x1dc)                                                        */


/**
  * @brief I2S Controller (I2S)
  */
typedef struct {                                /*!< (@ 0x40000000) I2S0 Structure                                             */
  __IOM uint32_t  IER;                          /*!< (@ 0x00000000) This register acts as a global enable/disable
                                                                    for i2s.                                                   */
  __IOM uint32_t  IRER;                         /*!< (@ 0x00000004) This register acts as an enable/disable for the
                                                                    I2S Receiver block.                                        */
  __OM  uint32_t  ITER;                         /*!< (@ 0x00000008) This register acts as an enable/disable for the
                                                                    I2S Transmitter block.                                     */
  __IOM uint32_t  CER;                          /*!< (@ 0x0000000C) This register acts as an enable/disable for the
                                                                    I2S Clock Generation block.                                */
  __IOM  uint32_t  CCR;                          /*!< (@ 0x00000010) This register configures the ws_out and sclk_gate
                                                                    signals when I2S is a master.                              */
  __OM  uint32_t  RXFFR;                        /*!< (@ 0x00000014) This register specifies the Receiver Block FIFO
                                                                    Reset Register                                             */
  __OM  uint32_t  TXFFR;                        /*!< (@ 0x00000018) This register specifies the Transmitter Block
                                                                    FIFO Reset Register                                        */
  __IM  uint32_t  RESERVED;
  
  union {
    __IM  uint32_t LRBR;                        /*!< (@ 0x00000020) This specifies the Left Receive Buffer Register            */
    __OM  uint32_t LTHR;                        /*!< (@ 0x00000020) This specifies the Left Transmit Holding Register          */
  };
  
  union {
    __IM  uint32_t RRBR;                        /*!< (@ 0x00000024) This specifies the Right Receive Buffer Register           */
    __OM  uint32_t RTHR;                        /*!< (@ 0x00000024) This specifies the Right Transmit Holding Register         */
  };
  __IOM uint32_t  RER;                          /*!< (@ 0x00000028) This specifies the Receive Enable Register                 */
  __IOM uint32_t  TER;                          /*!< (@ 0x0000002C) This specifies the Transmit Enable Register                */
  __IOM uint32_t  RCR;                          /*!< (@ 0x00000030) This specifies the Receive Configuration Register          */
  __IOM uint32_t  TCR;                          /*!< (@ 0x00000034) This specifies the Transmit Configuration Register         */
  __IM  uint32_t  ISR;                          /*!< (@ 0x00000038) This specifies the Interrupt Status Register               */
  __IOM uint32_t  IMR;                          /*!< (@ 0x0000003C) This specifies the Interrupt Mask Register                 */
  __IM  uint32_t  ROR;                          /*!< (@ 0x00000040) This specifies the Receive Overrun Register                */
  __IM  uint32_t  TOR;                          /*!< (@ 0x00000044) This specifies the Transmit Overrun Register               */
  __IOM uint32_t  RFCR;                         /*!< (@ 0x00000048) This specifies the Receive FIFO Configuration
                                                                    Register                                                   */
  __IOM uint32_t  TFCR;                         /*!< (@ 0x0000004C) This specifies the Transmit FIFO Configuration
                                                                    Register                                                   */
  __OM  uint32_t  RFF;                          /*!< (@ 0x00000050) This specifies the Receive FIFO Flush Register             */
  __OM  uint32_t  TFF;                          /*!< (@ 0x00000054) This specifies the Transmit FIFO Flush Register            */
  __IM  uint32_t  RESERVED1[90];
  __IM  uint32_t  RXDMA;                        /*!< (@ 0x000001C0) The RXDMA register allows access to all enabled
                                                                    Receive channels via a single point.                       */
  __IM  uint32_t  RESERVED2;
  __OM  uint32_t  TXDMA;                        /*!< (@ 0x000001C8) The TXDMA register functions similar to the RXDMA
                                                                    register.                                                  */
  __IM  uint32_t  RESERVED3[13];
  __IOM uint32_t  DMACR;                        /*!< (@ 0x00000200) This register is only valid when I2S is configured
                                                                    with a set of DMA Controller interface.                    */
} I2S_Type;                                     /*!< Size = 516 (0x204)                                                        */


typedef struct
{
  __IOM uint32_t  WIN;
  __IOM uint32_t  CTRL;
  __IOM uint32_t  CLR;
  __IOM uint32_t  STS;
} WDT_Type;


/**
  * @brief Direct Memory Access Controller (DMA)
  */
typedef struct{
  __IM  uint32_t RAWTFR;
  __IM  uint32_t RESERVED;
  __IM  uint32_t RAWBLOCK;
  __IM  uint32_t RESERVED1;
  __IM  uint32_t RAWSRCTRAN;
  __IM  uint32_t RESERVED2;
  __IM  uint32_t RAWDSTTRAN;
  __IM  uint32_t RESERVED3;
  __IM  uint32_t RAWERR;
  __IM  uint32_t RESERVED4;
  __IM  uint32_t STATUSTFR;
  __IM  uint32_t RESERVED5;
  __IM  uint32_t STATUSBLOCK;
  __IM  uint32_t RESERVED6;
  __IM  uint32_t STATUSSRCTRAN;
  __IM  uint32_t RESERVED7;
  __IM  uint32_t STATUSDSTTRAN;
  __IM  uint32_t RESERVED8;
  __IM  uint32_t STATUSERR;
  __IM  uint32_t RESERVED9;
  __IOM uint32_t MASKTFR;
  __IM  uint32_t RESERVED10;
  __IOM uint32_t MASKBLOCK;
  __IM  uint32_t RESERVED11;
  __IOM uint32_t MASKSRCTRAN;
  __IM  uint32_t RESERVED12;
  __IOM uint32_t MASKDSTTRAN;
  __IM  uint32_t RESERVED13;
  __IOM uint32_t MASKERR;
  __IM  uint32_t RESERVED14;
  __OM  uint32_t CLEARTFR;
  __IM  uint32_t RESERVED15;
  __OM  uint32_t CLEARBLOCK;
  __IM  uint32_t RESERVED16;
  __OM  uint32_t CLEARSRCTRAN;
  __IM  uint32_t RESERVED17;
  __OM  uint32_t CLEARDSTTRAN;
  __IM  uint32_t RESERVED18;
  __OM  uint32_t CLEARERR;
  __IM  uint32_t RESERVED19;
  
  __IM  uint32_t RESERVED20[2];
  
  __IOM uint32_t REQSRCREG;
  __IM  uint32_t RESERVED21;
  __IOM uint32_t REQDSTREG;
  __IM  uint32_t RESERVED22;
  __IOM uint32_t SGLREQSRCREG;
  __IM  uint32_t RESERVED23;
  __IOM uint32_t SGLREQDSTREG;
  __IM  uint32_t RESERVED24;
  __IOM uint32_t LSTSRCREG;
  __IM  uint32_t RESERVED25;
  __IOM uint32_t LSTDSTREG;
  __IM  uint32_t RESERVED26;
  
  __IOM uint32_t DMACFGREG;
  __IM  uint32_t RESERVED27;
  __IOM uint32_t CHENREG;
  __IM  uint32_t RESERVED28;
} DMA_Type;

typedef struct
{
  __IOM uint32_t  SAR;
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  DAR;
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  LLP;
  __IM  uint32_t  RESERVED2;
  __IOM uint32_t  CTL[2];
  __IOM uint32_t  SSTAT;
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  DSTAT;
  __IM  uint32_t  RESERVED5;
  __IOM uint32_t  SSTATAR;
  __IM  uint32_t  RESERVED6;
  __IOM uint32_t  DSTATAR;
  __IM  uint32_t  RESERVED7;
  __IOM uint32_t  CFG[2];
  __IOM uint32_t  SGR;
  __IM  uint32_t  RESERVED8;
  __IOM uint32_t  DSR;
  __IM  uint32_t  RESERVED9;
}DMA_Channel_Type;

/**
  * @brief TIMER
  */
typedef struct
{
  __IO uint16_t CR1;
  uint16_t  RESERVED0;
  __IO uint16_t CR2;
  uint16_t  RESERVED1;
  __IO uint16_t SMCR;
  uint16_t  RESERVED2;
  __IO uint16_t DIER;
  uint16_t  RESERVED3;
  __IO uint16_t SR;
  uint16_t  RESERVED4;
  __IO uint16_t EGR;
  uint16_t  RESERVED5;
  __IO uint16_t CCMR1;
  uint16_t  RESERVED6;
  __IO uint16_t CCMR2;
  uint16_t  RESERVED7;
  __IO uint16_t CCER;
  uint16_t  RESERVED8;
  __IO uint16_t CNT;
  uint16_t  RESERVED9;
  __IO uint16_t PSC;
  uint16_t  RESERVED10;
  __IO uint16_t ARR;
  uint16_t  RESERVED11;
  __IO uint16_t RCR;
  uint16_t  RESERVED12;
  __IO uint16_t CCR1;
  uint16_t  RESERVED13;
  __IO uint16_t CCR2;
  uint16_t  RESERVED14;
  __IO uint16_t CCR3;
  uint16_t  RESERVED15;
  __IO uint16_t CCR4;
  uint16_t  RESERVED16;
  __IO uint16_t BDTR;
  uint16_t  RESERVED17;
  uint16_t  RESERVED18;
  uint16_t  RESERVED19;
  uint16_t  RESERVED20;
  uint16_t  RESERVED21;
} TMR_Type;

typedef struct
{
  __IO uint32_t MACCR;
  __IO uint32_t MACFFR;
  __IO uint32_t MACHTHR;
  __IO uint32_t MACHTLR;
  __IO uint32_t MACMIIAR;
  __IO uint32_t MACMIIDR;
  __IO uint32_t MACFCR;
  __IO uint32_t MACVLANTR;           
  uint32_t      RESERVED0[2];
  __IO uint32_t MACRWUFFR;           
  __IO uint32_t MACPMTCSR;
  uint32_t      RESERVED1[2];
  __IO uint32_t MACSR;               
  __IO uint32_t MACIMR;
  __IO uint32_t MACA0HR;
  __IO uint32_t MACA0LR;
  __IO uint32_t MACA1HR;
  __IO uint32_t MACA1LR;
  __IO uint32_t MACA2HR;
  __IO uint32_t MACA2LR;
  __IO uint32_t MACA3HR;
  __IO uint32_t MACA3LR;             
  __IO uint32_t MACA4HR;
  __IO uint32_t MACA4LR;
  __IO uint32_t MACA5HR;
  __IO uint32_t MACA5LR;
  __IO uint32_t MACA6HR;
  __IO uint32_t MACA6LR;
  __IO uint32_t MACA7HR;
  __IO uint32_t MACA7LR;        
    /*   MMC NO USE*/
  uint32_t      RESERVED2[32];  
  __IO uint32_t MMCCR;          
  __IO uint32_t MMCRIR;
  __IO uint32_t MMCTIR;
  __IO uint32_t MMCRIMR;
  __IO uint32_t MMCTIMR;        
  uint32_t      RESERVED3[14];
  __IO uint32_t MMCTGFSCCR;     
  __IO uint32_t MMCTGFMSCCR;		
  uint32_t      RESERVED4[5];
  __IO uint32_t MMCTGFCR;
  uint32_t      RESERVED5[10];
  __IO uint32_t MMCRFCECR;		
  __IO uint32_t MMCRFAECR;		
  uint32_t      RESERVED6[10];
  __IO uint32_t MMCRGUFCR;		
  uint32_t      RESERVED7[334];		
	    /*   MMC NO USE*/
  __IO uint32_t PTPTSCR;					
  __IO uint32_t PTPSSIR;		
  __IO uint32_t PTPTSHR;		
  __IO uint32_t PTPTSLR;		
  __IO uint32_t PTPTSHUR;		
  __IO uint32_t PTPTSLUR;		
  __IO uint32_t PTPTSAR;		
  __IO uint32_t PTPTTHR;		
  __IO uint32_t PTPTTLR;		
  __IO uint32_t RESERVED8;	
  __IO uint32_t PTPTSSR;		
  __IO uint32_t PTPPSCR;		
  uint32_t      RESERVED9[564];		
  __IO uint32_t DMABMR;			
  __IO uint32_t DMATPDR;		
  __IO uint32_t DMARPDR;		
  __IO uint32_t DMARDLAR;		
  __IO uint32_t DMATDLAR;		
  __IO uint32_t DMASR;			
  __IO uint32_t DMAOMR;			
  __IO uint32_t DMAIER;			
  __IO uint32_t DMAMFBOCR;	
  __IO uint32_t DMARSWTR;		
  uint32_t      RESERVED10[8];
  __IO uint32_t DMACHTDR;			
  __IO uint32_t DMACHRDR;			
  __IO uint32_t DMACHTBAR;		
  __IO uint32_t DMACHRBAR;		
	__IO uint32_t DMAHWFR;			
} ETH_TypeDef;



/** 
  * @brief DCMI
  */

typedef struct
{
  __IO uint32_t CR;       /*!< DCMI control register 1,                       Address offset: 0x00 */
  __IO uint32_t SR;       /*!< DCMI status register,                          Address offset: 0x04 */
  __IO uint32_t RISR;     /*!< DCMI raw interrupt status register,            Address offset: 0x08 */
  __IO uint32_t IER;      /*!< DCMI interrupt enable register,                Address offset: 0x0C */
  __IO uint32_t MISR;     /*!< DCMI masked interrupt status register,         Address offset: 0x10 */
  __IO uint32_t ICR;      /*!< DCMI interrupt clear register,                 Address offset: 0x14 */
  __IO uint32_t ESCR;     /*!< DCMI embedded synchronization code register,   Address offset: 0x18 */
  __IO uint32_t ESUR;     /*!< DCMI embedded synchronization unmask register, Address offset: 0x1C */
  __IO uint32_t CWSTRTR;  /*!< DCMI crop window start,                        Address offset: 0x20 */
  __IO uint32_t CWSIZER;  /*!< DCMI crop window size,                         Address offset: 0x24 */
  __IO uint32_t DR;       /*!< DCMI data register,                            Address offset: 0x28 */
} DCMI_TypeDef;


typedef struct {
  __IOM uint32_t  CTRL;                    /* 0x000 */
  __IM  uint32_t  RESERVED1[3];            /* 0x004 ~ 0x00C */
  __IM  uint32_t  BLK_MAX;                 /* 0x010 */
  __IM  uint32_t  BLK_CFG;                 /* 0x014 */
  __IOM uint32_t  BLK_IDX;                 /* 0x018 */
  __IOM uint32_t  BLK_LUT;                 /* 0x01C */
  __IM  uint32_t  INT_STAT;                /* 0x020 */
  __IO  uint32_t  INT_CLEAR;               /* 0x024 */
  __IOM uint32_t  INT_EN;                  /* 0x028 */
  __IM  uint32_t  INT_INFO1;               /* 0x02C */
  __IM  uint32_t  INT_INFO2;               /* 0x030 */
  __IO  uint32_t  INT_SET;                 /* 0x034 */
  __IM  uint32_t  RESERVED2[998];          /* 0x038 ~ 0xFCC */
  __IM  uint32_t  PIDR4;                   /* 0xFD0 */
  __IM  uint32_t  PIDR5;                   /* 0xFD4 */
  __IM  uint32_t  PIDR6;                   /* 0xFD8 */
  __IM  uint32_t  PIDR7;                   /* 0xFDC */
  __IM  uint32_t  PIDR0;                   /* 0xFE0 */
  __IM  uint32_t  PIDR1;                   /* 0xFE4 */
  __IM  uint32_t  PIDR2;                   /* 0xFE8 */
  __IM  uint32_t  PIDR3;                   /* 0xFEC */
  __IM  uint32_t  CIDR0;                   /* 0xFF0 */
  __IM  uint32_t  CIDR1;                   /* 0xFF4 */
  __IM  uint32_t  CIDR2;                   /* 0xFF8 */
  __IM  uint32_t  CIDR3;                   /* 0xFFC */
} MPC_Type;

/**
  * @brief RTC-COMPARATOR()
  */
typedef struct {                                /*!< (@ 0x40103874) Comparator Structure                                    */
  __IOM uint32_t  CMP_STS;                      /*!< (@ 0x40103874) CMP contrtol register                                   */
  __IOM uint32_t  CMP_CTRL;                     /*!< (@ 0x40103878) CMP contrtol register                                   */	
} RTC_COMP_Type;  

/**
  * @brief COMPARATOR()
  */
typedef struct {                                /*!< (@ 0x40101800) Comparator Structure                                    */
  __IOM uint32_t  CMP_CTRL;                     /*!< (@ 0x00000000) CMP contrtol register                                   */
  __IOM uint32_t  CMP_EN;                       /*!< (@ 0x00000004) CMP enable register                                     */
  __IOM uint32_t  PULSE;                        /*!< (@ 0x00000008) CMP long pulse register                                 */
  __IOM uint32_t  INT_CTRL;                     /*!< (@ 0x0000000C) CMP interrupt control register                          */
  __IOM uint32_t  INT_MODE;                     /*!< (@ 0x00000010) CMP interrupt mode  register                            */
  __IOM uint32_t  WKU_CTRL;                     /*!< (@ 0x00000014) CMP wakeup mode\source\enable register                  */
  __IOM uint32_t  INT_STATUS;                   /*!< (@ 0x00000018) CMP output\interrupt status register                    */
} COMP_Type;    

/** 
  * @brief BDMA Controller
  */
typedef struct
{
  __IO uint32_t IE;           /*!< DMA interrupt enable register,                            Address offset:0x00 */
  __IO uint32_t STS;          /*!< DMA status register,                                      Address offset:0x04 */
       uint32_t RESERVED1;    /*!< Reserved,                                                                0x08 */
       uint32_t RESERVED2;    /*!< Reserved,                                                                0x0C */
  __IO uint32_t C0CTL;        /*!< DMA channel 0 control register,                           Address offset:0x10 */
  __IO uint32_t C0SEL;        /*!< DMA channel 0 req select register,                        Address offset:0x14 */
  __IO uint32_t C0SRC;        /*!< DMA channel 0 source register,                            Address offset:0x18 */
  __IO uint32_t C0DST;        /*!< DMA channel 0 destination register,                       Address offset:0x1C */
  __IO uint32_t C0LEN;        /*!< DMA channel 0 transfer length register,                   Address offset:0x20 */
       uint32_t RESERVED3[3]; /*!< Reserved,                                                           0x24-0x2C */
  __IO uint32_t C1CTL;        /*!< DMA channel 1 control register,                           Address offset:0x30 */
  __IO uint32_t C1SEL;        /*!< DMA channel 1 req select register,                        Address offset:0x34 */
  __IO uint32_t C1SRC;        /*!< DMA channel 1 source register,                            Address offset:0x38 */
  __IO uint32_t C1DST;        /*!< DMA channel 1 destination register,                       Address offset:0x3C */
  __IO uint32_t C1LEN;        /*!< DMA channel 1 transfer length register,                   Address offset:0x40 */
       uint32_t RESERVED4[3]; /*!< Reserved,                                                           0x44-0x4C */
  __IO uint32_t C2CTL;        /*!< DMA channel 2 control register,                           Address offset:0x50 */
  __IO uint32_t C2SEL;        /*!< DMA channel 2 req select register,                        Address offset:0x54 */
  __IO uint32_t C2SRC;        /*!< DMA channel 2 source register,                            Address offset:0x58 */
  __IO uint32_t C2DST;        /*!< DMA channel 2 destination register,                       Address offset:0x5C */
  __IO uint32_t C2LEN;        /*!< DMA channel 2 transfer length register,                   Address offset:0x60 */
       uint32_t RESERVED5[3]; /*!< Reserved,                                                           0x64-0x6C */
  __IO uint32_t C3CTL;        /*!< DMA channel 3 control register,                           Address offset:0x70 */
  __IO uint32_t C3SEL;        /*!< DMA channel 3 req select register,                        Address offset:0x74 */
  __IO uint32_t C3SRC;        /*!< DMA channel 3 source register,                            Address offset:0x78 */
  __IO uint32_t C3DST;        /*!< DMA channel 3 destination register,                       Address offset:0x7C */
  __IO uint32_t C3LEN;        /*!< DMA channel 3 transfer length register,                   Address offset:0x80 */
       uint32_t RESERVED6[3]; /*!< Reserved,                                                           0x84-0x8C */
  __IO uint32_t AESCTL;       /*!< DMA AES control register,                                 Address offset:0x90 */
       uint32_t RESERVED7[3]; /*!< Reserved,                                                           0x94-0x9C */
  __IO uint32_t AESKEY0;      /*!< DMA AES key 0 register,                                   Address offset:0xA0 */
  __IO uint32_t AESKEY1;      /*!< DMA AES key 1 register,                                   Address offset:0xA4 */
  __IO uint32_t AESKEY2;      /*!< DMA AES key 2 register,                                   Address offset:0xA8 */
  __IO uint32_t AESKEY3;      /*!< DMA AES key 3 register,                                   Address offset:0xAC */
  __IO uint32_t AESKEY4;      /*!< DMA AES key 4 register,                                   Address offset:0xB0 */
  __IO uint32_t AESKEY5;      /*!< DMA AES key 5 register,                                   Address offset:0xB4 */
  __IO uint32_t AESKEY6;      /*!< DMA AES key 6 register,                                   Address offset:0xB8 */
  __IO uint32_t AESKEY7;      /*!< DMA AES key 7 register,                                   Address offset:0xBC */
} BDMA_Type;

/**
  * @brief CRYPT accelerate the sign and verify process speed of ECC. (CRYPT)
  */
typedef struct {
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000000) CRYPT control register.                                    */
  __IOM uint32_t  PTRA;                         /*!< (@ 0x00000004) CRYPT pointer A.                                           */
  __IOM uint32_t  PTRB;                         /*!< (@ 0x00000008) CRYPT pointer B.                                           */
  __IOM uint32_t  PTRO;                         /*!< (@ 0x0000000C) CRYPT pointer O.                                           */
  __IM  uint32_t  CARRY;                        /*!< (@ 0x00000010) CRYPT carry/borrow bit register.                           */
} CRYPTO_Type;

#define ADDR_SECURE(base)                ((base) + 0x10000000UL)

/* ----------------------------------------------------------------------------
   -- CM33 Peripheral Base Address
   ---------------------------------------------------------------------------- */
#define OSPI0_BASE                    (0x60000000UL)
#define OSPI0_BASE_S                   ADDR_SECURE(OSPI0_BASE)
#define OSPI1_BASE                    (0x64000000UL)
#define OSPI1_BASE_S                   ADDR_SECURE(OSPI1_BASE)
#define DMA0_Channel_BASE             (0x20201000UL)
#define DMA0_Channel_BASE_S            ADDR_SECURE(DMA0_Channel_BASE)
#define DMA0_BASE                     (DMA0_Channel_BASE   + 0x2c0)
#define DMA0_BASE_S                   (DMA0_Channel_BASE_S + 0x2c0)
#define DMA0_Channel0_BASE            (DMA0_Channel_BASE)
#define DMA0_Channel0_BASE_S          (DMA0_Channel_BASE_S)
#define DMA0_Channel1_BASE            (DMA0_Channel_BASE   + 0x58)
#define DMA0_Channel1_BASE_S          (DMA0_Channel_BASE_S + 0x58)
#define DMA0_Channel2_BASE            (DMA0_Channel_BASE   + 0xB0)
#define DMA0_Channel2_BASE_S          (DMA0_Channel_BASE_S + 0xB0)
#define DMA0_Channel3_BASE            (DMA0_Channel_BASE   + 0x108)
#define DMA0_Channel3_BASE_S          (DMA0_Channel_BASE_S + 0x108)
#define DMA0_Channel4_BASE            (DMA0_Channel_BASE   + 0x160)
#define DMA0_Channel4_BASE_S          (DMA0_Channel_BASE_S + 0x160)
#define DMA0_Channel5_BASE            (DMA0_Channel_BASE   + 0x1B8)
#define DMA0_Channel5_BASE_S          (DMA0_Channel_BASE_S + 0x1B8)
#define DMA0_Channel6_BASE            (DMA0_Channel_BASE   + 0x210)
#define DMA0_Channel6_BASE_S          (DMA0_Channel_BASE_S + 0x210)
#define DMA0_Channel7_BASE            (DMA0_Channel_BASE   + 0x268)
#define DMA0_Channel7_BASE_S          (DMA0_Channel_BASE_S + 0x268)
#define DMA1_Channel_BASE             (0x20201800UL)
#define DMA1_Channel_BASE_S            ADDR_SECURE(DMA1_Channel_BASE)
#define DMA1_BASE                     (DMA1_Channel_BASE   + 0x2c0)
#define DMA1_BASE_S                   (DMA1_Channel_BASE_S + 0x2c0)
#define DMA1_Channel0_BASE            (DMA1_Channel_BASE)
#define DMA1_Channel0_BASE_S          (DMA1_Channel_BASE_S)
#define DMA1_Channel1_BASE            (DMA1_Channel_BASE   + 0x58)
#define DMA1_Channel1_BASE_S          (DMA1_Channel_BASE_S + 0x58)
#define DMA1_Channel2_BASE            (DMA1_Channel_BASE   + 0xB0)
#define DMA1_Channel2_BASE_S          (DMA1_Channel_BASE_S + 0xB0)
#define DMA1_Channel3_BASE            (DMA1_Channel_BASE   + 0x108)
#define DMA1_Channel3_BASE_S          (DMA1_Channel_BASE_S + 0x108)
#define DMA1_Channel4_BASE            (DMA1_Channel_BASE   + 0x160)
#define DMA1_Channel4_BASE_S          (DMA1_Channel_BASE_S + 0x160)
#define DMA1_Channel5_BASE            (DMA1_Channel_BASE   + 0x1B8)
#define DMA1_Channel5_BASE_S          (DMA1_Channel_BASE_S + 0x1B8)
#define DMA1_Channel6_BASE            (DMA1_Channel_BASE   + 0x210)
#define DMA1_Channel6_BASE_S          (DMA1_Channel_BASE_S + 0x210)
#define DMA1_Channel7_BASE            (DMA1_Channel_BASE   + 0x268)
#define DMA1_Channel7_BASE_S          (DMA1_Channel_BASE_S + 0x268)
#define USB_HS_BASE                      (0x20240000UL)
#define USB_HS_BASE_S                     ADDR_SECURE(USB_HS_BASE)
#define USB_FS_BASE                      (0x20280000UL)
#define USB_FS_BASE_S                     ADDR_SECURE(USB_FS_BASE)
#define CRC_BASE                         (0x20300000UL)
#define CRC_BASE_S                        ADDR_SECURE(CRC_BASE)
#define FLEXCOMM0_BASE                   (0x40010000UL)
#define FLEXCOMM0_BASE_S                  ADDR_SECURE(FLEXCOMM0_BASE)
#define FLEXCOMM1_BASE                   (0x40010800UL)
#define FLEXCOMM1_BASE_S                  ADDR_SECURE(FLEXCOMM1_BASE)
#define FLEXCOMM2_BASE                   (0x40011000UL)
#define FLEXCOMM2_BASE_S                 ADDR_SECURE(FLEXCOMM2_BASE)
#define FLEXCOMM3_BASE                   (0x40011800UL)
#define FLEXCOMM3_BASE_S                  ADDR_SECURE(FLEXCOMM3_BASE)
#define FLEXCOMM4_BASE                   (0x40012000UL)
#define FLEXCOMM4_BASE_S                  ADDR_SECURE(FLEXCOMM4_BASE)
#define FLEXCOMM5_BASE                   (0x40012800UL)
#define FLEXCOMM5_BASE_S                  ADDR_SECURE(FLEXCOMM5_BASE)
#define FLEXCOMM6_BASE                   (0x40013000UL)
#define FLEXCOMM6_BASE_S                  ADDR_SECURE(FLEXCOMM6_BASE)
#define FLEXCOMM7_BASE                   (0x40013800UL)
#define FLEXCOMM7_BASE_S                  ADDR_SECURE(FLEXCOMM7_BASE)
#define FLEXCOMM8_BASE                   (0x40014000UL)
#define FLEXCOMM8_BASE_S                  ADDR_SECURE(FLEXCOMM8_BASE)
#define FLEXCOMM9_BASE                   (0x40014800UL)
#define FLEXCOMM9_BASE_S                  ADDR_SECURE(FLEXCOMM9_BASE)
#define FLEXCOMM10_BASE                  (0x40015000UL)
#define FLEXCOMM10_BASE_S                 ADDR_SECURE(FLEXCOMM10_BASE)
#define FLEXCOMM11_BASE                  (0x40015800UL)
#define FLEXCOMM11_BASE_S                 ADDR_SECURE(FLEXCOMM11_BASE)
#define FLEXCOMM12_BASE                  (0x40016000UL)
#define FLEXCOMM12_BASE_S                 ADDR_SECURE(FLEXCOMM12_BASE)
#define FLEXCOMM13_BASE                  (0x40016800UL)
#define FLEXCOMM13_BASE_S                 ADDR_SECURE(FLEXCOMM13_BASE)
#define ISO78160_1_BASE                  (0x40040000UL)
#define ISO78160_BASE                    (ISO78160_1_BASE + 0x00000000UL)
#define ISO78160_BASE_S                   ADDR_SECURE(ISO78160_BASE)
#define ISO78161_BASE                    (ISO78160_1_BASE + 0x00000040UL)
#define ISO78161_BASE_S                   ADDR_SECURE(ISO78161_BASE)
#define BTMR0_BASE                       (0x40050000UL)
#define BTMR0_BASE_S                      ADDR_SECURE(BTMR0_BASE)
#define BTMR1_BASE                       (0x40050020UL)
#define BTMR1_BASE_S                      ADDR_SECURE(BTMR1_BASE)
#define BTMR2_BASE                       (0x40050040UL)
#define BTMR2_BASE_S                      ADDR_SECURE(BTMR2_BASE)
#define BTMR3_BASE                       (0x40050060UL)
#define BTMR3_BASE_S                      ADDR_SECURE(BTMR3_BASE)
#define BPWM0_BASE                       (0x40050100UL)
#define BPWM0_BASE_S                      ADDR_SECURE(BPWM0_BASE)
#define BPWM1_BASE                       (0x40050120UL)
#define BPWM1_BASE_S                      ADDR_SECURE(BPWM1_BASE)
#define BPWM2_BASE                       (0x40050140UL)
#define BPWM2_BASE_S                      ADDR_SECURE(BPWM2_BASE)
#define BPWM3_BASE                       (0x40050160UL)
#define BPWM3_BASE_S                      ADDR_SECURE(BPWM3_BASE)
#define BPWM0_3_SEL_BASE                 (0x400501F0UL)
#define BPWM0_3_SEL_BASE_S                ADDR_SECURE(BPWM0_3_SEL_BASE)
#define ETMR0_BASE                        (0x40050800UL)
#define ETMR0_BASE_S                       ADDR_SECURE(ETMR0_BASE)
#define ETMR1_BASE                        (0x40051000UL)
#define ETMR1_BASE_S                       ADDR_SECURE(ETMR1_BASE)
#define GTMR0_BASE                        (0x40051800UL)
#define GTMR0_BASE_S                       ADDR_SECURE(GTMR0_BASE)
#define GTMR1_BASE                        (0x40052000UL)
#define GTMR1_BASE_S                       ADDR_SECURE(GTMR1_BASE)
#define GTMR2_BASE                        (0x40052800UL)
#define GTMR2_BASE_S                       ADDR_SECURE(GTMR2_BASE)
#define GTMR3_BASE                        (0x40053000UL)
#define GTMR3_BASE_S                       ADDR_SECURE(GTMR3_BASE)
#define RNG_BASE                         (0x40060100UL)
#define RNG_BASE_S                        ADDR_SECURE(RNG_BASE)
#define SCR_BASE                         (0x40070000UL)
#define SCR_BASE_S                        ADDR_SECURE(SCR_BASE)
#define CAN0_BASE                        (0x40080000UL)
#define CAN0_BASE_S                       ADDR_SECURE(CAN0_BASE)
#define CAN1_BASE                        (0x40080800UL)
#define CAN1_BASE_S                       ADDR_SECURE(CAN1_BASE)
#define WAVER33_BASE                     (0x40081000UL)
#define WAVER33_BASE_S                    ADDR_SECURE(WAVER33_BASE)
#define I2S0_BASE                        (0x40083000UL)
#define I2S0_BASE_S                       ADDR_SECURE(I2S0_BASE)
#define I2S1_BASE                        (0x40083800UL)
#define I2S1_BASE_S                       ADDR_SECURE(I2S1_BASE)
#define SDIO0_BASE                       (0x40084000UL)
#define SDIO0_BASE_S                      ADDR_SECURE(SDIO0_BASE)
#define SDIO1_BASE                       (0x40086000UL)
#define SDIO1_BASE_S                      ADDR_SECURE(SDIO1_BASE)
#define WDT0_BASE                        (0x40090000UL)
#define WDT0_BASE_S                       ADDR_SECURE(WDT0_BASE)
#define WDT1_BASE                        (0x40090800UL)
#define WDT1_BASE_S                       ADDR_SECURE(WDT1_BASE)
#define DAC_BASE                         (0x400A0000UL)
#define DAC_BASE_S                        ADDR_SECURE(DAC_BASE)
#define EADC_BASE                        (0x400A0800UL)
#define EADC_BASE_S                       ADDR_SECURE(EADC_BASE)
#define ADC0_BASE                        (0x400A1000UL)
#define ADC0_BASE_S                       ADDR_SECURE(ADC0_BASE)
#define ADC1_BASE                        (0x400A1100UL)
#define ADC1_BASE_S                       ADDR_SECURE(ADC1_BASE)
#define CDMA_ADC_BASE                     (0x400A1800UL)
#define CDMA_ADC_BASE_S                   ADDR_SECURE(CDMA_ADC_BASE)
#define SYSCFG0_BASE                     (0x40200000UL)
#define SYSCFG0_BASE_S                    ADDR_SECURE(SYSCFG0_BASE)
#define DCMI_BASE                        (0x40201000UL)
#define DCMI_BASE_S                       ADDR_SECURE(DCMI_BASE)
#define ETH0_BASE                        (0x40202000UL)
#define ETH0_BASE_S                       ADDR_SECURE(ETH0_BASE)
#define ETH_MAC0_BASE                    (ETH0_BASE)
#define ETH_MAC0_BASE_S                   ADDR_SECURE(ETH0_BASE)
#define ETH_MAC0_MMC_BASE                (ETH0_BASE + 0x0100)
#define ETH_MAC0_MMC_BASE_S               ADDR_SECURE(ETH0_BASE + 0x0100)
#define ETH_MAC0_PTP_BASE                (ETH0_BASE + 0x0700)
#define ETH_MAC0_PTP_BASE_S               ADDR_SECURE(ETH0_BASE + 0x0700)
#define ETH_MAC0_DMA_BASE                (ETH0_BASE + 0x1000)
#define ETH_MAC0_DMA_BASE_S               ADDR_SECURE(ETH0_BASE + 0x1000)
#define ETH1_BASE                        (0x40204000UL)
#define ETH1_BASE_S                       ADDR_SECURE(ETH1_BASE)
#define ETH_MAC1_BASE                    (ETH1_BASE)
#define ETH_MAC1_BASE_S                   ADDR_SECURE(ETH1_BASE)
#define ETH_MAC1_MMC_BASE                (ETH1_BASE + 0x0100)
#define ETH_MAC1_MMC_BASE_S               ADDR_SECURE(ETH1_BASE + 0x0100)
#define ETH_MAC1_PTP_BASE                (ETH1_BASE + 0x0700)
#define ETH_MAC1_PTP_BASE_S               ADDR_SECURE(ETH1_BASE + 0x0700)
#define ETH_MAC1_DMA_BASE                (ETH1_BASE + 0x1000)
#define ETH_MAC1_DMA_BASE_S               ADDR_SECURE(ETH1_BASE + 0x1000)
#define ENCENG_BASE                      (0x40206000UL)
#define ENCENG_BASE_S                     ADDR_SECURE(ENCENG_BASE)
#define FLASHA_CON_BASE                  (0x40208000UL)
#define FLASHA_CON_BASE_S                 ADDR_SECURE(FLASHA_CON_BASE)
#define FLASHB_CON_BASE                  (0x4020C000UL)
#define FLASHB_CON_BASE_S                 ADDR_SECURE(FLASHB_CON_BASE)
#define PMU33_BASE                       (0x40100800UL)
#define PMU33_BASE_S                      ADDR_SECURE(PMU33_BASE)
#define RETRAM33_BASE                    (0x40100000UL)
#define RETRAM33_BASE_S                   ADDR_SECURE(RETRAM33_BASE)
#define COMP33_0_BASE                    (0x40101800UL)
#define COMP33_0_BASE_S                   ADDR_SECURE(COMP33_0_BASE)
#define COMP33_1_BASE                    (0x4010181CUL)
#define COMP33_1_BASE_S                   ADDR_SECURE(COMP33_1_BASE)
#define SYSCFGLP_33_BASE                 (0x40102000UL)
#define SYSCFGLP_33_BASE_S                ADDR_SECURE(SYSCFGLP_33_BASE)
#define RTC33_ALM_BASE                   (0x40102800UL)
#define RTC33_ALM_BASE_S                  ADDR_SECURE(RTC33_ALM_BASE)
#define RTC33_BASE                       (0x40103000UL)
#define RTC33_BASE_S                      ADDR_SECURE(RTC33_BASE)
#define RTC33_ANA_CTRL_BASE              (0x40103800UL)
#define RTC33_ANA_CTRL_BASE_S             ADDR_SECURE(RTC33_ANA_CTRL_BASE)
#define RTC_COMP_BASE                    (0x40103874UL)
#define RTC_COMP_BASE_S                   ADDR_SECURE(RTC_COMP_BASE)
#define CDMA_ADC_BASE                    (0x400A1800UL)
#define CDMA_ADC_BASE_S                   ADDR_SECURE(CDMA_ADC_BASE)
#define GPIOA33_BASE                     (0x40104000UL)
#define GPIOA33_BASE_S                   ADDR_SECURE(GPIOA33_BASE)
#define GPIOB33_BASE                     (0x40104400UL)
#define GPIOB33_BASE_S                   ADDR_SECURE(GPIOB33_BASE)
#define GPIOC33_BASE                     (0x40104800UL)
#define GPIOC33_BASE_S                   ADDR_SECURE(GPIOC33_BASE)
#define GPIOD33_BASE                     (0x40104C00UL)
#define GPIOD33_BASE_S                   ADDR_SECURE(GPIOD33_BASE)
#define GPIOE33_BASE                     (0x40105000UL)
#define GPIOE33_BASE_S                   ADDR_SECURE(GPIOE33_BASE)
#define GPIOF33_BASE                     (0x40105400UL)
#define GPIOF33_BASE_S                   ADDR_SECURE(GPIOF33_BASE)
#define GPIOG33_BASE                     (0x40105800UL)
#define GPIOG33_BASE_S                   ADDR_SECURE(GPIOG33_BASE)
#define GPIOH33_BASE                     (0x40105C00UL)
#define GPIOH33_BASE_S                   ADDR_SECURE(GPIOH33_BASE)
#define GPIOI33_BASE                     (0x40106000UL)
#define GPIOI33_BASE_S                   ADDR_SECURE(GPIOI33_BASE)
#define IO_EXTI33_BASE                   (0x40106800UL)
#define IO_EXTI33_BASE_S                  ADDR_SECURE(IO_EXTI33_BASE)
#define VGIO33_BASE                      (0x40107000UL)
#define VGIO33_BASE_S                     ADDR_SECURE(VGIO33_BASE)
#define IOCTRL_BASE                      (0x40106400UL)
#define IOCTRL_BASE_S                     ADDR_SECURE(IOCTRL_BASE)
#define LPBTMR0_BASE                     (0x40108000UL)
#define LPBTMR0_BASE_S                    ADDR_SECURE(LPBTMR0_BASE)
#define LPBTMR1_BASE                     (0x40109000UL)
#define LPBTMR1_BASE_S                    ADDR_SECURE(LPBTMR1_BASE)
/* ----------------------------------------------------------------------------
   -- CM0 Peripheral Base Address
   ---------------------------------------------------------------------------- */
#define WAVER0_BASE                      (0x21014000UL)
#define WAVER0_BASE_S                     ADDR_SECURE(WAVER0_BASE)
#define HFM_BASE                         (0x21015000UL)
#define HFM_BASE_S                        ADDR_SECURE(HFM_BASE)
#define SYSCFG1_BASE                     (0x21030000UL)
#define SYSCFG1_BASE_S                    ADDR_SECURE(SYSCFG1_BASE)
#define I2C14_BASE                       (0x41010000UL)
#define I2C14_BASE_S                      ADDR_SECURE(I2C14_BASE)
#define BSPI0_BASE                      (0x41020000UL)
#define BSPI0_BASE_S                     ADDR_SECURE(BSPI0_BASE)
#define BSPI1_BASE                      (0x41020800UL)
#define BSPI1_BASE_S                     ADDR_SECURE(BSPI1_BASE)
#define BSPI2_BASE                      (0x41021000UL)
#define BSPI2_BASE_S                     ADDR_SECURE(BSPI2_BASE)
#define BSPI3_BASE                      (0x41021800UL)
#define BSPI3_BASE_S                     ADDR_SECURE(BSPI3_BASE)
#define BSPI4_BASE                      (0x41022000UL)
#define BSPI4_BASE_S                     ADDR_SECURE(BSPI4_BASE)
#define BSPI5_BASE                      (0x41022800UL)
#define BSPI5_BASE_S                     ADDR_SECURE(BSPI5_BASE)
#define UART14_BASE                     (0x41030000UL)
#define UART14_BASE_S                    ADDR_SECURE(UART14_BASE)
#define UART15_BASE                     (0x41030800UL)
#define UART15_BASE_S                    ADDR_SECURE(UART15_BASE)
#define UART16_BASE                     (0x41031000UL)
#define UART16_BASE_S                    ADDR_SECURE(UART16_BASE)
#define UART17_BASE                     (0x41031800UL)
#define UART17_BASE_S                    ADDR_SECURE(UART17_BASE)
#define UART18_BASE                     (0x41032000UL)
#define UART18_BASE_S                    ADDR_SECURE(UART18_BASE)
#define UART19_BASE                     (0x41032800UL)
#define UART19_BASE_S                    ADDR_SECURE(UART19_BASE)
#define ISO78162_3_BASE                 (0x41040000UL)
#define ISO78162_BASE                   (ISO78162_3_BASE + 0x00000000UL)
#define ISO78162_BASE_S                  ADDR_SECURE(ISO78162_BASE)
#define ISO78163_BASE                   (ISO78162_3_BASE + 0x00000040UL)
#define ISO78163_BASE_S                  ADDR_SECURE(ISO78163_BASE)
#define BTMR4_BASE                       (0x41050000UL)
#define BTMR4_BASE_S                      ADDR_SECURE(BTMR4_BASE)
#define BTMR5_BASE                       (0x41050020UL)
#define BTMR5_BASE_S                      ADDR_SECURE(BTMR5_BASE)
#define BTMR6_BASE                       (0x41050040UL)
#define BTMR6_BASE_S                      ADDR_SECURE(BTMR6_BASE)
#define BTMR7_BASE                       (0x41050060UL)
#define BTMR7_BASE_S                      ADDR_SECURE(BTMR7_BASE)
#define BPWM4_BASE                       (0x41050100UL)
#define BPWM4_BASE_S                      ADDR_SECURE(BPWM4_BASE)
#define BPWM5_BASE                       (0x41050120UL)
#define BPWM5_BASE_S                      ADDR_SECURE(BPWM5_BASE)
#define BPWM6_BASE                       (0x41050140UL)
#define BPWM6_BASE_S                      ADDR_SECURE(BPWM6_BASE)
#define BPWM7_BASE                       (0x41050160UL)
#define BPWM7_BASE_S                      ADDR_SECURE(BPWM7_BASE)
#define BPWM4_7_SEL_BASE                 (0x410501F0UL)
#define BPWM4_7_SEL_BASE_S                ADDR_SECURE(BPWM4_7_SEL_BASE)
#define BDMA_BASE                        (0x41080800UL)
#define BDMA_BASE_S                       ADDR_SECURE(BDMA_BASE)
#define FLASH0_CON_BASE                  (0x41208000UL)
#define FLASH0_CON_BASE_S                 ADDR_SECURE(FLASH0_CON_BASE)
#define CRYPTO_BASE                      (0x4120C000UL)
#define CRYPTO_BASE_S                     ADDR_SECURE(CRYPTO_BASE)
#define PMU0_BASE                        (0x41100800UL)
#define SDADC0_BASE                      (0x41101000UL)
#define SDADC0_BASE_S                     ADDR_SECURE(SDADC0_BASE)
#define COMP0_0_BASE                     (0x41101800UL)
#define COMP0_0_BASE_S                    ADDR_SECURE(COMP0_0_BASE)
#define COMP0_1_BASE                     (0x4110181CUL)
#define COMP0_1_BASE_S                    ADDR_SECURE(COMP0_1_BASE)
#define SYSCFGLP_0_BASE                  (0x41102000UL)
#define SYSCFGLP_0_BASE_S                 ADDR_SECURE(SYSCFGLP_0_BASE)
#define RTC0_ALM_BASE                    (0x41102800UL)
#define RTC0_ALM_BASE_S                   ADDR_SECURE(RTC0_ALM_BASE)
#define RTC0_BASE                        (0x41103000UL)
#define RTC0_BASE_S                       ADDR_SECURE(RTC0_BASE)
#define RTC0_ANA_CTRL_BASE               (0x41103800UL)
#define RTC0_ANA_CTRL_BASE_S              ADDR_SECURE(RTC0_ANA_CTRL_BASE)
#define RTC0_COMP_BASE                   (0x41103874UL)
#define RTC0_COMP_BASE_S                  ADDR_SECURE(RTC0_COMP_BASE)
#define GPIOA0_BASE                      (0x41104000UL)
#define GPIOA0_BASE_S                    ADDR_SECURE(GPIOA0_BASE)
#define GPIOB0_BASE                      (0x41104400UL)
#define GPIOB0_BASE_S                    ADDR_SECURE(GPIOB0_BASE)
#define GPIOC0_BASE                      (0x41104800UL)
#define GPIOC0_BASE_S                    ADDR_SECURE(GPIOC0_BASE)
#define GPIOD0_BASE                      (0x41104C00UL)
#define GPIOD0_BASE_S                    ADDR_SECURE(GPIOD0_BASE)
#define GPIOE0_BASE                      (0x41105000UL)
#define GPIOE0_BASE_S                    ADDR_SECURE(GPIOE0_BASE)
#define GPIOF0_BASE                      (0x41105400UL)
#define GPIOF0_BASE_S                    ADDR_SECURE(GPIOF0_BASE)
#define GPIOG0_BASE                      (0x41105800UL)
#define GPIOG0_BASE_S                    ADDR_SECURE(GPIOG0_BASE)
#define GPIOH0_BASE                      (0x41105C00UL)
#define GPIOH0_BASE_S                    ADDR_SECURE(GPIOH0_BASE)
#define GPIOI0_BASE                      (0x41106000UL)
#define GPIOI0_BASE_S                    ADDR_SECURE(GPIOI0_BASE)
#define IO_EXTI0_BASE                    (0x41106800UL)
#define IO_EXTI0_BASE_S                   ADDR_SECURE(IO_EXTI0_BASE)
#define VGIO0_BASE                       (0x41107000UL)
#define VGIO0_BASE_S                      ADDR_SECURE(VGIO0_BASE)
#define LPBTMR4_BASE                   (0x41108000UL)
#define LPBTMR4_BASE_S                  ADDR_SECURE(LPBTMR4_BASE)
#define LPBTMR5_BASE                   (0x41109000UL)
#define LPBTMR5_BASE_S                  ADDR_SECURE(LPBTMR5_BASE)
#define WDT2_BASE                        (0x41090000UL)
#define WDT2_BASE_S                       ADDR_SECURE(WDT2_BASE)

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

#define OSPI0                        ((OSPI_Type*)               OSPI0_BASE_S)
#define OSPI1                        ((OSPI_Type*)               OSPI1_BASE_S)
#define DMA0                        ((DMA_Type*)               DMA0_BASE_S)
#define DMA0_Channel0               ((DMA_Channel_Type *)      DMA0_Channel0_BASE_S)
#define DMA0_Channel1               ((DMA_Channel_Type *)      DMA0_Channel1_BASE_S)
#define DMA0_Channel2               ((DMA_Channel_Type *)      DMA0_Channel2_BASE_S)
#define DMA0_Channel3               ((DMA_Channel_Type *)      DMA0_Channel3_BASE_S)
#define DMA0_Channel4               ((DMA_Channel_Type *)      DMA0_Channel4_BASE_S)
#define DMA0_Channel5               ((DMA_Channel_Type *)      DMA0_Channel5_BASE_S)
#define DMA0_Channel6               ((DMA_Channel_Type *)      DMA0_Channel6_BASE_S)
#define DMA0_Channel7               ((DMA_Channel_Type *)      DMA0_Channel7_BASE_S)
#define DMA1                        ((DMA_Type*)               DMA1_BASE_S)
#define DMA1_Channel0               ((DMA_Channel_Type *)      DMA1_Channel0_BASE_S)
#define DMA1_Channel1               ((DMA_Channel_Type *)       DMA1_Channel1_BASE_S)
#define DMA1_Channel2               ((DMA_Channel_Type *)      DMA1_Channel2_BASE_S)
#define DMA1_Channel3               ((DMA_Channel_Type *)      DMA1_Channel3_BASE_S)
#define DMA1_Channel4               ((DMA_Channel_Type *)      DMA1_Channel4_BASE_S)
#define DMA1_Channel5               ((DMA_Channel_Type *)      DMA1_Channel5_BASE_S)
#define DMA1_Channel6               ((DMA_Channel_Type *)      DMA1_Channel6_BASE_S)
#define DMA1_Channel7               ((DMA_Channel_Type *)      DMA1_Channel7_BASE_S)
#define CRC                         ((CRC_Type*)               CRC_BASE_S)
#define UART0                       ((UART_Type*)              FLEXCOMM0_BASE_S)
#define UART1                       ((UART_Type*)              FLEXCOMM1_BASE_S)
#define UART2                       ((UART_Type*)              FLEXCOMM2_BASE_S)
#define UART3                       ((UART_Type*)              FLEXCOMM3_BASE_S)
#define UART4                       ((UART_Type*)              FLEXCOMM4_BASE_S)
#define UART5                       ((UART_Type*)              FLEXCOMM5_BASE_S)
#define UART6                       ((UART_Type*)              FLEXCOMM6_BASE_S)
#define UART7                       ((UART_Type*)              FLEXCOMM7_BASE_S)
#define UART8                       ((UART_Type*)              FLEXCOMM8_BASE_S)
#define UART9                       ((UART_Type*)              FLEXCOMM9_BASE_S)
#define UART10                      ((UART_Type*)              FLEXCOMM10_BASE_S)
#define UART11                      ((UART_Type*)              FLEXCOMM11_BASE_S)
#define UART12                      ((UART_Type*)              FLEXCOMM12_BASE_S)
#define UART13                      ((UART_Type*)              FLEXCOMM13_BASE_S)
#define I2C0                        ((I2C_Type*)               FLEXCOMM0_BASE_S)
#define I2C1                        ((I2C_Type*)               FLEXCOMM1_BASE_S)
#define I2C2                        ((I2C_Type*)               FLEXCOMM2_BASE_S)
#define I2C3                        ((I2C_Type*)               FLEXCOMM3_BASE_S)
#define I2C4                        ((I2C_Type*)               FLEXCOMM4_BASE_S)
#define I2C5                        ((I2C_Type*)               FLEXCOMM5_BASE_S)
#define I2C6                        ((I2C_Type*)               FLEXCOMM6_BASE_S)
#define I2C7                        ((I2C_Type*)               FLEXCOMM7_BASE_S)
#define I2C8                        ((I2C_Type*)               FLEXCOMM8_BASE_S)
#define I2C9                        ((I2C_Type*)               FLEXCOMM9_BASE_S)
#define I2C10                       ((I2C_Type*)               FLEXCOMM10_BASE_S)
#define I2C11                       ((I2C_Type*)               FLEXCOMM11_BASE_S)
#define I2C12                       ((I2C_Type*)               FLEXCOMM12_BASE_S)
#define I2C13                       ((I2C_Type*)               FLEXCOMM13_BASE_S)
#define SPI0                        ((SPI_Type*)               FLEXCOMM0_BASE_S)
#define SPI1                        ((SPI_Type*)               FLEXCOMM1_BASE_S)
#define SPI2                        ((SPI_Type*)               FLEXCOMM2_BASE_S)
#define SPI3                        ((SPI_Type*)               FLEXCOMM3_BASE_S)
#define SPI4                        ((SPI_Type*)               FLEXCOMM4_BASE_S)
#define SPI5                        ((SPI_Type*)               FLEXCOMM5_BASE_S)
#define SPI6                        ((SPI_Type*)               FLEXCOMM6_BASE_S)
#define SPI7                        ((SPI_Type*)               FLEXCOMM7_BASE_S)
#define SPI8                        ((SPI_Type*)               FLEXCOMM8_BASE_S)
#define SPI9                        ((SPI_Type*)               FLEXCOMM9_BASE_S)
#define SPI10                       ((SPI_Type*)               FLEXCOMM10_BASE_S)
#define SPI11                       ((SPI_Type*)               FLEXCOMM11_BASE_S)
#define SPI12                       ((SPI_Type*)               FLEXCOMM12_BASE_S)
#define SPI13                       ((SPI_Type*)               FLEXCOMM13_BASE_S)
#define ISO78160                       ((ISO7816_Type *)          ISO78160_BASE_S)
#define ISO78161                       ((ISO7816_Type *)          ISO78161_BASE_S)
#define BTMR0                          ((BTMR_Type *)             BTMR0_BASE_S)
#define BTMR1                          ((BTMR_Type *)             BTMR1_BASE_S)
#define BTMR2                          ((BTMR_Type *)             BTMR2_BASE_S)
#define BTMR3                          ((BTMR_Type *)             BTMR3_BASE_S)
#define BPWM0                          ((BPWM_Type *)             BPWM0_BASE_S)
#define BPWM1                          ((BPWM_Type *)             BPWM1_BASE_S)
#define BPWM2                          ((BPWM_Type *)             BPWM2_BASE_S)
#define BPWM3                          ((BPWM_Type *)             BPWM3_BASE_S)
#define BPWM0_3_SEL                    ((BPWM_SEL_Type *)         BPWM0_3_SEL_BASE)
#define ETMR0                          ((TMR_Type *)              ETMR0_BASE_S)
#define ETMR1                          ((TMR_Type *)              ETMR1_BASE_S)
#define GTMR0                          ((TMR_Type *)              GTMR0_BASE_S)
#define GTMR1                          ((TMR_Type *)              GTMR1_BASE_S)
#define GTMR2                          ((TMR_Type *)              GTMR2_BASE_S)
#define GTMR3                          ((TMR_Type *)              GTMR3_BASE_S)
#define RNG                            ((RNG_Type*)               RNG_BASE_S)
#define SCR33                          ((SCR_Type*)               SCR_BASE_S)
#define MPC_FLASHA                     ((MPC_Type *)              (SCR_BASE_S + 0x1000UL))
#define MPC_FLASHB                     ((MPC_Type *)              (SCR_BASE_S + 0x2000UL))
#define MPC_SRAM33_0                   ((MPC_Type *)              (SCR_BASE_S + 0x3000UL))
#define MPC_SRAM33_1                   ((MPC_Type *)              (SCR_BASE_S + 0x4000UL))
#define MPC_SRAM33_2                   ((MPC_Type *)              (SCR_BASE_S + 0x5000UL))
#define MPC_SRAM33_3                   ((MPC_Type *)              (SCR_BASE_S + 0x6000UL))
#define CAN0                           ((CAN_Type *)              CAN0_BASE_S)
#define CAN1                           ((CAN_Type *)              CAN1_BASE_S)
#define I2S0                           ((I2S_Type*)               I2S0_BASE_S)
#define I2S1                           ((I2S_Type*)               I2S1_BASE_S)
#define SDIO0                          ((SDIO_TypeDef *)          SDIO0_BASE_S)
#define SDIO1                          ((SDIO_TypeDef *)          SDIO1_BASE_S)
#define WDT0                           ((WDT_Type*)               WDT0_BASE_S)
#define WDT1                           ((WDT_Type*)               WDT1_BASE_S)
#define DAC                            ((DAC_Type*)               DAC_BASE_S)
#define EADC                           ((EADC_Type *)             EADC_BASE_S)
#define ADC0                           ((ADC_Type *)              ADC0_BASE_S)
#define ADC1                           ((ADC_Type *)              ADC1_BASE_S)
#define CDMA_ADC                       ((CDMA_ADC_Type *)         CDMA_ADC_BASE_S)
#define SYSCFG0                        ((SYSCFG0_Type*)          SYSCFG0_BASE_S)
#define DCMI                           ((DCMI_TypeDef *)          DCMI_BASE_S)
#define ETH0                           ((ETH_TypeDef *)           ETH0_BASE_S)
#define ETH1                           ((ETH_TypeDef *)           ETH1_BASE_S) 
#define ENCENG                         ((ENCENG_Type*)            ENCENG_BASE_S)
#define FLASHA                         ((FLASH_Type*)             FLASHA_CON_BASE_S)
#define FLASHB                         ((FLASH_Type*)             FLASHB_CON_BASE_S)
#define FLASH0                         ((FLASH_Type*)             FLASH0_CON_BASE_S)
#define PMU                            ((PMU_Type*)               PMU33_BASE_S)
#define COMP0                          ((COMP_Type *)             COMP33_0_BASE_S)
#define COMP1                          ((COMP_Type *)             COMP33_1_BASE_S)
#define SYSCFGLP                       ((SYSCFGLP_Type*)          SYSCFGLP_33_BASE_S)
#define RTCALM                         ((RTCALM_Type*)            RTC33_ALM_BASE_S)
#define RTC                            ((RTC_Type*)               RTC33_BASE_S)
#define RTCANA                         ((RTCANA_Type*)            RTC33_ANA_CTRL_BASE_S)
#define RTC_COMP                       ((RTC_COMP_Type *)         RTC_COMP_BASE_S)
#define GPIOA                          ((GPIO_Type*)              GPIOA33_BASE_S)
#define GPIOB                          ((GPIO_Type*)              GPIOB33_BASE_S)
#define GPIOC                          ((GPIO_Type*)              GPIOC33_BASE_S)
#define GPIOD                          ((GPIO_Type*)              GPIOD33_BASE_S)
#define GPIOE                          ((GPIO_Type*)              GPIOE33_BASE_S)
#define GPIOF                          ((GPIO_Type*)              GPIOF33_BASE_S)
#define GPIOG                          ((GPIO_Type*)              GPIOG33_BASE_S)
#define GPIOH                          ((GPIO_Type*)              GPIOH33_BASE_S)
#define GPIOI                          ((GPIO_Type*)              GPIOI33_BASE_S)
#define EXTI                           ((IO_EXTI_Type*)           IO_EXTI33_BASE_S)
#define IOCTRL                         ((IO_CTRL_Type*)           IOCTRL_BASE_S)
#define LPBTMR0                        ((BTMR_Type *)             LPBTMR0_BASE_S)
#define LPBTMR1                        ((BTMR_Type *)             LPBTMR1_BASE)
#define WAVER0                         ((WAVER0_Type *)           WAVER0_BASE_S)
#define HFM                            ((HFM_Type *)              HFM_BASE_S)
#define SYSCFG1                        ((SYSCFG1_Type*)           SYSCFG1_BASE_S)
#define I2C14                          ((I2C_Type*)               I2C14_BASE_S)
#define BSPI0                         ((BSPI_Type *)          BSPI0_BASE_S)
#define BSPI1                         ((BSPI_Type *)          BSPI1_BASE_S)
#define BSPI2                         ((BSPI_Type *)          BSPI2_BASE_S)
#define BSPI3                         ((BSPI_Type *)          BSPI3_BASE_S)
#define BSPI4                         ((BSPI_Type *)          BSPI4_BASE_S)
#define BSPI5                         ((BSPI_Type *)          BSPI5_BASE_S)
#define UART14                         ((UART_Type*)              UART14_BASE_S)
#define UART15                         ((UART_Type*)              UART15_BASE_S)
#define UART16                         ((UART_Type*)              UART16_BASE_S)
#define UART17                         ((UART_Type*)              UART17_BASE_S)
#define UART18                         ((UART_Type*)              UART18_BASE_S)
#define UART19                         ((UART_Type*)              UART19_BASE_S)
#define ISO78162                       ((ISO7816_Type *)          ISO78162_BASE_S)
#define ISO78163                       ((ISO7816_Type *)          ISO78163_BASE_S)
#define BTMR4                          ((BTMR_Type *)             BTMR4_BASE_S)
#define BTMR5                          ((BTMR_Type *)             BTMR5_BASE_S)
#define BTMR6                          ((BTMR_Type *)             BTMR6_BASE_S)
#define BTMR7                          ((BTMR_Type *)             BTMR7_BASE_S)
#define BPWM4                          ((BPWM_Type *)             BPWM4_BASE_S)
#define BPWM5                          ((BPWM_Type *)             BPWM5_BASE_S)
#define BPWM6                          ((BPWM_Type *)             BPWM6_BASE_S)
#define BPWM7                          ((BPWM_Type *)             BPWM7_BASE_S)
#define BPWM4_7_SEL                    ((BPWM_SEL_Type *)         BPWM4_7_SEL_BASE)
#define BDMA                           ((BDMA_Type*)              BDMA_BASE_S)
#define FLASH0                         ((FLASH_Type*)             FLASH0_CON_BASE_S)
#define CRYPTO                         ((CRYPTO_Type*)            CRYPTO_BASE_S)
#define WDT2                           ((WDT_Type*)               WDT2_BASE_S)

#else

#define OSPI0                       ((OSPI_Type*)              OSPI0_BASE)
#define OSPI1                       ((OSPI_Type*)              OSPI1_BASE)
#define DMA0                        ((DMA_Type*)               DMA0_BASE)
#define DMA0_Channel0               ((DMA_Channel_Type *)      DMA0_Channel0_BASE)
#define DMA0_Channel1               ((DMA_Channel_Type *)      DMA0_Channel1_BASE)
#define DMA0_Channel2               ((DMA_Channel_Type *)      DMA0_Channel2_BASE)
#define DMA0_Channel3               ((DMA_Channel_Type *)      DMA0_Channel3_BASE)
#define DMA0_Channel4               ((DMA_Channel_Type *)      DMA0_Channel4_BASE)
#define DMA0_Channel5               ((DMA_Channel_Type *)      DMA0_Channel5_BASE)
#define DMA0_Channel6               ((DMA_Channel_Type *)      DMA0_Channel6_BASE)
#define DMA0_Channel7               ((DMA_Channel_Type *)      DMA0_Channel7_BASE)
#define DMA1                        ((DMA_Type*)               DMA1_BASE)
#define DMA1_Channel0               ((DMA_Channel_Type *)      DMA1_Channel0_BASE)
#define DMA1_Channel1               ((DMA_Channel_Type *)      DMA1_Channel1_BASE)
#define DMA1_Channel2               ((DMA_Channel_Type *)      DMA1_Channel2_BASE)
#define DMA1_Channel3               ((DMA_Channel_Type *)      DMA1_Channel3_BASE)
#define DMA1_Channel4               ((DMA_Channel_Type *)      DMA1_Channel4_BASE)
#define DMA1_Channel5               ((DMA_Channel_Type *)      DMA1_Channel5_BASE)
#define DMA1_Channel6               ((DMA_Channel_Type *)      DMA1_Channel6_BASE)
#define DMA1_Channel7               ((DMA_Channel_Type *)      DMA1_Channel7_BASE)
#define CRC                         ((CRC_Type*)               CRC_BASE)
#define UART0                       ((UART_Type*)              FLEXCOMM0_BASE)
#define UART1                       ((UART_Type*)              FLEXCOMM1_BASE)
#define UART2                       ((UART_Type*)              FLEXCOMM2_BASE)
#define UART3                       ((UART_Type*)              FLEXCOMM3_BASE)
#define UART4                       ((UART_Type*)              FLEXCOMM4_BASE)
#define UART5                       ((UART_Type*)              FLEXCOMM5_BASE)
#define UART6                       ((UART_Type*)              FLEXCOMM6_BASE)
#define UART7                       ((UART_Type*)              FLEXCOMM7_BASE)
#define UART8                       ((UART_Type*)              FLEXCOMM8_BASE)
#define UART9                       ((UART_Type*)              FLEXCOMM9_BASE)
#define UART10                      ((UART_Type*)              FLEXCOMM10_BASE)
#define UART11                      ((UART_Type*)              FLEXCOMM11_BASE)
#define UART12                      ((UART_Type*)              FLEXCOMM12_BASE)
#define UART13                      ((UART_Type*)              FLEXCOMM13_BASE)
#define I2C0                        ((I2C_Type*)               FLEXCOMM0_BASE)
#define I2C1                        ((I2C_Type*)               FLEXCOMM1_BASE)
#define I2C2                        ((I2C_Type*)               FLEXCOMM2_BASE)
#define I2C3                        ((I2C_Type*)               FLEXCOMM3_BASE)
#define I2C4                        ((I2C_Type*)               FLEXCOMM4_BASE)
#define I2C5                        ((I2C_Type*)               FLEXCOMM5_BASE)
#define I2C6                        ((I2C_Type*)               FLEXCOMM6_BASE)
#define I2C7                        ((I2C_Type*)               FLEXCOMM7_BASE)
#define I2C8                        ((I2C_Type*)               FLEXCOMM8_BASE)
#define I2C9                        ((I2C_Type*)               FLEXCOMM9_BASE)
#define I2C10                       ((I2C_Type*)               FLEXCOMM10_BASE)
#define I2C11                       ((I2C_Type*)               FLEXCOMM11_BASE)
#define I2C12                       ((I2C_Type*)               FLEXCOMM12_BASE)
#define I2C13                       ((I2C_Type*)               FLEXCOMM13_BASE)
#define SPI0                        ((SPI_Type*)               FLEXCOMM0_BASE)
#define SPI1                        ((SPI_Type*)               FLEXCOMM1_BASE)
#define SPI2                        ((SPI_Type*)               FLEXCOMM2_BASE)
#define SPI3                        ((SPI_Type*)               FLEXCOMM3_BASE)
#define SPI4                        ((SPI_Type*)               FLEXCOMM4_BASE)
#define SPI5                        ((SPI_Type*)               FLEXCOMM5_BASE)
#define SPI6                        ((SPI_Type*)               FLEXCOMM6_BASE)
#define SPI7                        ((SPI_Type*)               FLEXCOMM7_BASE)
#define SPI8                        ((SPI_Type*)               FLEXCOMM8_BASE)
#define SPI9                        ((SPI_Type*)               FLEXCOMM9_BASE)
#define SPI10                       ((SPI_Type*)               FLEXCOMM10_BASE)
#define SPI11                       ((SPI_Type*)               FLEXCOMM11_BASE)
#define SPI12                       ((SPI_Type*)               FLEXCOMM12_BASE)
#define SPI13                       ((SPI_Type*)               FLEXCOMM13_BASE)
#define ISO78160                       ((ISO7816_Type *)          ISO78160_BASE)
#define ISO78161                       ((ISO7816_Type *)          ISO78161_BASE)
#define BTMR0                          ((BTMR_Type *)             BTMR0_BASE)
#define BTMR1                          ((BTMR_Type *)             BTMR1_BASE)
#define BTMR2                          ((BTMR_Type *)             BTMR2_BASE)
#define BTMR3                          ((BTMR_Type *)             BTMR3_BASE)
#define BPWM0                          ((BPWM_Type *)             BPWM0_BASE)
#define BPWM1                          ((BPWM_Type *)             BPWM1_BASE)
#define BPWM2                          ((BPWM_Type *)             BPWM2_BASE)
#define BPWM3                          ((BPWM_Type *)             BPWM3_BASE)
#define BPWM0_3_SEL                    ((BPWM_SEL_Type *)         BPWM0_3_SEL_BASE)
#define ETMR0                          ((TMR_Type *)              ETMR0_BASE)
#define ETMR1                          ((TMR_Type *)              ETMR1_BASE)
#define GTMR0                          ((TMR_Type *)              GTMR0_BASE)
#define GTMR1                          ((TMR_Type *)              GTMR1_BASE)
#define GTMR2                          ((TMR_Type *)              GTMR2_BASE)
#define GTMR3                          ((TMR_Type *)              GTMR3_BASE)
#define RNG                            ((RNG_Type*)               RNG_BASE)
#define SCR33                          ((SCR_Type*)               SCR_BASE)
#define MPC_FLASHA                     ((MPC_Type *)              (SCR_BASE + 0x1000UL))
#define MPC_FLASHB                     ((MPC_Type *)              (SCR_BASE + 0x2000UL))
#define MPC_SRAM33_0                   ((MPC_Type *)              (SCR_BASE + 0x3000UL))
#define MPC_SRAM33_1                   ((MPC_Type *)              (SCR_BASE + 0x4000UL))
#define MPC_SRAM33_2                   ((MPC_Type *)              (SCR_BASE + 0x5000UL))
#define MPC_SRAM33_3                   ((MPC_Type *)              (SCR_BASE + 0x6000UL))
#define CAN0                           ((CAN_Type *)              CAN0_BASE)
#define CAN1                           ((CAN_Type *)              CAN1_BASE)
#define I2S0                           ((I2S_Type*)               I2S0_BASE)
#define I2S1                           ((I2S_Type*)               I2S1_BASE)
#define SDIO0                          ((SDIO_TypeDef *)          SDIO0_BASE)
#define SDIO1                          ((SDIO_TypeDef *)          SDIO1_BASE)
#define WDT0                           ((WDT_Type*)               WDT0_BASE)
#define WDT1                           ((WDT_Type*)               WDT1_BASE)
#define DAC                            ((DAC_Type*)               DAC_BASE)
#define EADC                           ((EADC_Type *)             EADC_BASE)
#define ADC0                           ((ADC_Type *)              ADC0_BASE)
#define ADC1                           ((ADC_Type *)              ADC1_BASE)
#define SYSCFG0                       ((SYSCFG0_Type*)          SYSCFG0_BASE)
#define DCMI                           ((DCMI_TypeDef *)          DCMI_BASE)
#define ETH0                           ((ETH_TypeDef *)           ETH0_BASE)
#define ETH1                           ((ETH_TypeDef *)           ETH1_BASE) 
#define ENCENG                         ((ENCENG_Type*)            ENCENG_BASE)
#define FLASHA                         ((FLASH_Type*)             FLASHA_CON_BASE)
#define FLASHB                         ((FLASH_Type*)             FLASHB_CON_BASE)
#define FLASH0                         ((FLASH_Type*)             FLASH0_CON_BASE)
#define PMU                            ((PMU_Type*)               PMU33_BASE)
#define RETRAM                         ((RETRAM_Type*)            RETRAM33_BASE)
#define COMP0                          ((COMP_Type *)             COMP33_0_BASE)
#define COMP1                          ((COMP_Type *)             COMP33_1_BASE)
#define SYSCFGLP                       ((SYSCFGLP_Type*)          SYSCFGLP_33_BASE)
#define RTCALM                         ((RTCALM_Type*)            RTC33_ALM_BASE)
#define RTC                            ((RTC_Type*)               RTC33_BASE)
#define RTCANA                         ((RTCANA_Type*)            RTC33_ANA_CTRL_BASE)
#define RTC_COMP                       ((RTC_COMP_Type *)         RTC_COMP_BASE)
#define CDMA_ADC                       ((CDMA_ADC_Type *)         CDMA_ADC_BASE)
#define GPIOA                          ((GPIO_Type*)              GPIOA33_BASE)
#define GPIOB                          ((GPIO_Type*)              GPIOB33_BASE)
#define GPIOC                          ((GPIO_Type*)              GPIOC33_BASE)
#define GPIOD                          ((GPIO_Type*)              GPIOD33_BASE)
#define GPIOE                          ((GPIO_Type*)              GPIOE33_BASE)
#define GPIOF                          ((GPIO_Type*)              GPIOF33_BASE)
#define GPIOG                          ((GPIO_Type*)              GPIOG33_BASE)
#define GPIOH                          ((GPIO_Type*)              GPIOH33_BASE)
#define GPIOI                          ((GPIO_Type*)              GPIOI33_BASE)
#define EXTI                           ((IO_EXTI_Type*)           IO_EXTI33_BASE)
#define IOCTRL                         ((IO_CTRL_Type*)           IOCTRL_BASE)
#define LPBTMR0                        ((BTMR_Type *)             LPBTMR0_BASE)
#define LPBTMR1                        ((BTMR_Type *)             LPBTMR1_BASE)
#define WAVER0                         ((WAVER0_Type *)           WAVER0_BASE)
#define HFM                            ((HFM_Type *)              HFM_BASE)
#define SYSCFG1                        ((SYSCFG1_Type*)           SYSCFG1_BASE)
#define I2C14                          ((I2C_Type*)               I2C14_BASE)
#define BSPI0                          ((BSPI_Type *)             BSPI0_BASE)
#define BSPI1                          ((BSPI_Type *)             BSPI1_BASE)
#define BSPI2                          ((BSPI_Type *)             BSPI2_BASE)
#define BSPI3                          ((BSPI_Type *)             BSPI3_BASE)
#define BSPI4                          ((BSPI_Type *)             BSPI4_BASE)
#define BSPI5                          ((BSPI_Type *)             BSPI5_BASE)
#define UART14                         ((UART_Type*)              UART14_BASE)
#define UART15                         ((UART_Type*)              UART15_BASE)
#define UART16                         ((UART_Type*)              UART16_BASE)
#define UART17                         ((UART_Type*)              UART17_BASE)
#define UART18                         ((UART_Type*)              UART18_BASE)
#define UART19                         ((UART_Type*)              UART19_BASE)
#define ISO78162                       ((ISO7816_Type *)          ISO78162_BASE)
#define ISO78163                       ((ISO7816_Type *)          ISO78163_BASE)
#define BTMR4                          ((BTMR_Type *)             BTMR4_BASE)
#define BTMR5                          ((BTMR_Type *)             BTMR5_BASE)
#define BTMR6                          ((BTMR_Type *)             BTMR6_BASE)
#define BTMR7                          ((BTMR_Type *)             BTMR7_BASE)
#define BPWM4                          ((BPWM_Type *)             BPWM4_BASE)
#define BPWM5                          ((BPWM_Type *)             BPWM5_BASE)
#define BPWM6                          ((BPWM_Type *)             BPWM6_BASE)
#define BPWM7                          ((BPWM_Type *)             BPWM7_BASE)
#define BPWM4_7_SEL                    ((BPWM_SEL_Type *)         BPWM4_7_SEL_BASE)
#define BDMA                           ((BDMA_Type*)              BDMA_BASE)
#define FLASH0                         ((FLASH_Type*)             FLASH0_CON_BASE)
#define CRYPTO                         ((CRYPTO_Type*)            CRYPTO_BASE)
#define WDT2                           ((WDT_Type*)               WDT2_BASE)

#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/** @defgroup FLEXCOMM Type
  * @{
  */
typedef enum
{
  FLEXCOMM0 = 0,
  FLEXCOMM1 = 1,
  FLEXCOMM2 = 2,
  FLEXCOMM3 = 3,
  FLEXCOMM4 = 4,
  FLEXCOMM5 = 5,
  FLEXCOMM6 = 6,
  FLEXCOMM7 = 7,
  FLEXCOMM8 = 8,
  FLEXCOMM9 = 9,
  FLEXCOMM10 = 10,
  FLEXCOMM11 = 11,
  FLEXCOMM12 = 12,
  FLEXCOMM13 = 13,
} FLEXCOMM_Type;

#define IS_UART_ALL_INSTANCE(INSTANCE) (((INSTANCE) == UART0) ||\
                                        ((INSTANCE) == UART1) ||\
                                        ((INSTANCE) == UART2) ||\
                                        ((INSTANCE) == UART3) ||\
                                        ((INSTANCE) == UART4) ||\
                                        ((INSTANCE) == UART5) ||\
                                        ((INSTANCE) == UART6) ||\
                                        ((INSTANCE) == UART7) ||\
                                        ((INSTANCE) == UART8) ||\
                                        ((INSTANCE) == UART9) ||\
                                        ((INSTANCE) == UART10) ||\
                                        ((INSTANCE) == UART11) ||\
                                        ((INSTANCE) == UART12) ||\
                                        ((INSTANCE) == UART13) ||\
                                        ((INSTANCE) == UART14) ||\
                                        ((INSTANCE) == UART15) ||\
                                        ((INSTANCE) == UART16) ||\
                                        ((INSTANCE) == UART17) ||\
                                        ((INSTANCE) == UART18) ||\
                                        ((INSTANCE) == UART19))

#define IS_OSPI_ALL_INSTANCE(INSTANCE)     (((INSTANCE) == OSPI0) || ((INSTANCE) == OSPI1))

#define IS_I2S_ALL_INSTANCE(__INSTANCE__)  (((__INSTANCE__) == I2S0) ||\
                                            ((__INSTANCE__) == I2S1))

#define IS_SDIO_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SDIO0) || \
                                        ((INSTANCE) == SDIO1))

#define OSPI_GET_INDEX(Instance)\
(((uint32_t)(Instance) == ((uint32_t)OSPI0))? 0 : 1)

#define I2S_GET_INDEX(Instance)\
(((uint32_t)(Instance) == ((uint32_t)I2S0))? 0 : 1)

#define UART_GET_INDEX(Instance) \
(((uint32_t)(Instance) == ((uint32_t)UART0))? 0 :\
 ((uint32_t)(Instance) == ((uint32_t)UART14))? 0 :\
 ((uint32_t)(Instance) == ((uint32_t)UART1))? 1 :\
 ((uint32_t)(Instance) == ((uint32_t)UART15))? 1 :\
 ((uint32_t)(Instance) == ((uint32_t)UART2))? 2 :\
 ((uint32_t)(Instance) == ((uint32_t)UART16))? 2 :\
 ((uint32_t)(Instance) == ((uint32_t)UART3))? 3 :\
 ((uint32_t)(Instance) == ((uint32_t)UART17))? 3 :\
 ((uint32_t)(Instance) == ((uint32_t)UART4))? 4 :\
 ((uint32_t)(Instance) == ((uint32_t)UART18))? 4 :\
 ((uint32_t)(Instance) == ((uint32_t)UART5))? 5 :\
 ((uint32_t)(Instance) == ((uint32_t)UART19))? 5 :\
 ((uint32_t)(Instance) == ((uint32_t)UART6))? 6 :\
 ((uint32_t)(Instance) == ((uint32_t)UART7))? 7 :\
 ((uint32_t)(Instance) == ((uint32_t)UART8))? 8 :\
 ((uint32_t)(Instance) == ((uint32_t)UART9))? 9 :\
 ((uint32_t)(Instance) == ((uint32_t)UART10))? 10 :\
 ((uint32_t)(Instance) == ((uint32_t)UART11))? 11 :\
 ((uint32_t)(Instance) == ((uint32_t)UART12))? 12 :\
 ((uint32_t)(Instance) == ((uint32_t)UART13))? 13 :\
   14)

#define SDIO_GET_INDEX(Instance)\
(((uint32_t)(Instance) == ((uint32_t)SDIO0))? 0 : 1)


#endif /* (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1) */

#if defined (V32F20XXX_CM0_CORE)

#define WAVER0                         ((WAVER0_Type *)           WAVER0_BASE)
#define HFM                            ((HFM_Type *)              HFM_BASE)
#define SYSCFG1                        ((SYSCFG1_Type*)           SYSCFG1_BASE)
#define I2C14                          ((I2C_Type*)               I2C14_BASE)
#define BSPI0                          ((BSPI_Type *)             BSPI0_BASE)
#define BSPI1                          ((BSPI_Type *)             BSPI1_BASE)
#define BSPI2                          ((BSPI_Type *)             BSPI2_BASE)
#define BSPI3                          ((BSPI_Type *)             BSPI3_BASE)
#define BSPI4                          ((BSPI_Type *)             BSPI4_BASE)
#define BSPI5                          ((BSPI_Type *)             BSPI5_BASE)
#define UART14                         ((UART_Type*)              UART14_BASE)
#define UART15                         ((UART_Type*)              UART15_BASE)
#define UART16                         ((UART_Type*)              UART16_BASE)
#define UART17                         ((UART_Type*)              UART17_BASE)
#define UART18                         ((UART_Type*)              UART18_BASE)
#define UART19                         ((UART_Type*)              UART19_BASE)
#define ISO78162                       ((ISO7816_Type *)          ISO78162_BASE)
#define ISO78163                       ((ISO7816_Type *)          ISO78163_BASE)
#define BTMR4                          ((BTMR_Type *)             BTMR4_BASE)
#define BTMR5                          ((BTMR_Type *)             BTMR5_BASE)
#define BTMR6                          ((BTMR_Type *)             BTMR6_BASE)
#define BTMR7                          ((BTMR_Type *)             BTMR7_BASE)
#define BPWM4                          ((BPWM_Type *)             BPWM4_BASE)
#define BPWM5                          ((BPWM_Type *)             BPWM5_BASE)
#define BPWM6                          ((BPWM_Type *)             BPWM6_BASE)
#define BPWM7                          ((BPWM_Type *)             BPWM7_BASE)
#define BPWM4_7_SEL                    ((BPWM_SEL_Type *)         BPWM4_7_SEL_BASE)
#define BDMA                           ((BDMA_Type*)              BDMA_BASE)
#define FLASH0                         ((FLASH_Type*)             FLASH0_CON_BASE)
#define CRYPTO                         ((CRYPTO_Type*)            CRYPTO_BASE)
#define PMU                            ((PMU_Type*)               PMU0_BASE)
#define SYSCFGLP                       ((SYSCFGLP_Type*)          SYSCFGLP_0_BASE)
#define RTCALM                         ((RTCALM_Type*)            RTC0_ALM_BASE)
#define RTC                            ((RTC_Type*)               RTC0_BASE)
#define RTCANA                         ((RTCANA_Type*)            RTC0_ANA_CTRL_BASE)
#define RTC_COMP                       ((RTC_COMP_Type *)         RTC0_COMP_BASE)
#define GPIOA                          ((GPIO_Type*)              GPIOA0_BASE)
#define GPIOB                          ((GPIO_Type*)              GPIOB0_BASE)
#define GPIOC                          ((GPIO_Type*)              GPIOC0_BASE)
#define GPIOD                          ((GPIO_Type*)              GPIOD0_BASE)
#define GPIOE                          ((GPIO_Type*)              GPIOE0_BASE)
#define GPIOF                          ((GPIO_Type*)              GPIOF0_BASE)
#define GPIOG                          ((GPIO_Type*)              GPIOG0_BASE)
#define GPIOH                          ((GPIO_Type*)              GPIOH0_BASE)
#define GPIOI                          ((GPIO_Type*)              GPIOI0_BASE)
#define EXTI                           ((IO_EXTI_Type*)           IO_EXTI0_BASE)
#define LPBTMR0                        ((BTMR_Type *)             LPBTMR0_BASE)
#define LPBTMR1                        ((BTMR_Type *)             LPBTMR1_BASE)
#define WDT2                           ((WDT_Type*)               WDT2_BASE)

#define IS_UART_ALL_INSTANCE(INSTANCE) (((INSTANCE) == UART14) ||\
                                        ((INSTANCE) == UART15) ||\
                                        ((INSTANCE) == UART16) ||\
                                        ((INSTANCE) == UART17) ||\
                                        ((INSTANCE) == UART18) ||\
                                        ((INSTANCE) == UART19))

#define UART_GET_INDEX(Instance) \
(((uint32_t)(Instance) == ((uint32_t)UART14))? 0 :\
 ((uint32_t)(Instance) == ((uint32_t)UART15))? 1 :\
 ((uint32_t)(Instance) == ((uint32_t)UART16))? 2 :\
 ((uint32_t)(Instance) == ((uint32_t)UART17))? 3 :\
 ((uint32_t)(Instance) == ((uint32_t)UART18))? 4 :\
   5)
   
#endif /* V32F20XXX_CM0_CORE */

#define IS_UART14_19_ALL_INSTANCE(INSTANCE) (((INSTANCE) == UART14) ||\
                                         ((INSTANCE) == UART15) ||\
                                         ((INSTANCE) == UART16) ||\
                                         ((INSTANCE) == UART17) ||\
                                         ((INSTANCE) == UART18) ||\
                                         ((INSTANCE) == UART19))

#define UART14_19_GET_INDEX(Instance) \
(((uint32_t)(Instance) == ((uint32_t)UART14))? 0 :\
 ((uint32_t)(Instance) == ((uint32_t)UART15))? 1 :\
 ((uint32_t)(Instance) == ((uint32_t)UART16))? 2 :\
 ((uint32_t)(Instance) == ((uint32_t)UART17))? 3 :\
 ((uint32_t)(Instance) == ((uint32_t)UART18))? 4 :\
   5)

#include "std_def.h"

#if defined _USE_TARGET_DRIVER
 #include "lib_conf.h"
#endif


/**
  * @brief Internal RCH value
  */
#define RCH_VALUE                   (48000000UL)

/**
  * @brief External XOH value
  */
#if !defined  (XOH_VALUE)
#define XOH_VALUE                   (12000000UL)
#endif /* XOH_VALUE */

/**
  * @brief Internal RCL value
  */
#if !defined  (RCL_VALUE)
#define RCL_VALUE                   (32768UL)
#endif /* RCL_VALUE */

/**
  * @brief External XOL value
  */
#if !defined  (XOL_VALUE)
#define XOL_VALUE                   (32768UL)
#endif /* XOL_VALUE */

#ifdef __cplusplus
}
#endif

#endif /* __TARGET_H */

/*********************************** END OF FILE ******************************/
