/**
* @file     rn831x_rn861x_mcu.h
* @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File
*           for rn831x_rn861x_mcu CM0 Device
* @version  v1.1.3
* @note
* Copyright (C) Renergy Micro-Electronics Co.,LTD.
******************************************************************************/

#ifndef RN831X_RN861X_MCU_H
#define RN831X_RN861X_MCU_H

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup rn831x_rn861x_mcu_Definitions
     This file defines all structures and symbols for rn831x_rn861x_mcu:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - Peripheral definitions
    @{
*/

/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup rn831x_rn861x_mcu_CMSIS Device CMSIS Definitions
     Configuration of the Cortex-M0 Processor and Core Peripherals
    @{
*/

/*
* ==========================================================================
* ---------- Interrupt Number Definition -----------------------------------
* ==========================================================================
*/
typedef enum IRQn
{
    /******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn = -14, /*!<  2 Cortex-M0 Non Maskable Interrupt                  */
    HardFault_IRQn = -13,      /*!<  3 Cortex-M0 Hard Fault Interrupt                    */

    SVCall_IRQn = -5, /*!< 11 Cortex-M0 SV Call Interrupt                       */

    PendSV_IRQn = -2,  /*!< 14 Cortex-M0 Pend SV Interrupt                       */
    SysTick_IRQn = -1, /*!< 15 Cortex-M0 System Tick Interrupt                   */

    /******  rn831x_rn861x_mcu Specific Interrupt Numbers ********************************************************/
    SYSCLKCAL_IRQn = 0,      /*!<  16 SYSCLK CALC irq number                          */
    CMP_IRQn = 1,            /*!<  17 Voltage compare Interrupt                       */
    /* VCH_IRQn                     = 2,       18 Power Switch Interrupt              */
    RTC_IRQn = 3,            /*!<  19 RTC Interrupt                                   */
    D2F_IRQn = 4,            /*!<  20 D2F(v2) Interrupt                               */
    MADC_IRQn = 5,           /*!<  21 SAR Interrupt                                   */
    UART0_IRQn = 6,          /*!<  22 UART0 Interrupt                                 */
    UART1_IRQn = 7,          /*!<  23 UART1 Interrupt                                 */
    UART2_IRQn = 8,          /*!<  24 UART2 Interrupt                                 */
    UART3_IRQn = 9,          /*!<  25 UART3 Interrupt                                 */
    SPI0_IRQn = 10,          /*!<  26 SPI0 Interrupt                                  */
    I2C_IRQn = 11,           /*!<  27 IIC Interrupt                                   */
    ISO78160_IRQn = 12,      /*!<  28 ISO7816 0 or SPI3(v2) or UART6(v3) Interrupt    */
    ISO78161_IRQn = 13,      /*!<  29 ISO7816 1 or SPI2(v2) or UART7(v3) Interrupt    */
    TC0_IRQn = 14,           /*!<  30 Timer/Counter 0 Interrupt                       */
    TC1_IRQn = 15,           /*!<  31 Timer/Counter 1 (v1/v2) Interrupt               */
    UART4_IRQn = 16,         /*!<  32 UART4 Interrupt                                 */
    UART5_IRQn = 17,         /*!<  33 UART5 Interrupt                                 */
    WDT_IRQn = 18,           /*!<  34 Watch Dog Interrupt                             */
    KBI_IRQn = 19,           /*!<  35 Key Interrupt                                   */
    LCD_IRQn = 20,           /*!<  36 LCD and DSP(v2) Interrupt                       */
    CP_IRQn = 21,            /*!<  37 CP(v1) or SEA(v2) or LSRX(v3) Interrupt         */
    SPI1_IRQn = 23,          /*!<  39 SPI1(v2/v3) Interrupt                           */
    EXT0_IRQn = 24,          /*!<  40 Extern0 Interrupt(or all extern irq)            */
    EXT1_IRQn = 25,          /*!<  41 Extern1 or simp-tc0(v2/v3) Interrupt            */
    EXT2_IRQn = 26,          /*!<  42 Extern2 or simp-tc1(v2/v3) Interrupt            */
    EXT3_IRQn = 27,          /*!<  43 Extern3 or simp-tc2(v2/v3) Interrupt            */
    EXT4_IRQn = 28,          /*!<  44 Extern4 or simp-tc3(v2/v3) Interrupt            */
    EXT5_IRQn = 29,          /*!<  45 Extern5 or m2m(v2) or simp-tc4(v3) Interrupt    */
    EXT6_IRQn = 30,          /*!<  46 Extern6 Interrupt                               */
    EXT7_IRQn = 31           /*!<  47 Extern7 Interrupt                               */
} IRQn_Type;
/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT 0          /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS 2       /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig 0 /*!< Set to 1 if different SysTick Config is used     */

#if 0
#if defined(__CC_ARM)
#if defined(__TARGET_FPU_VFP)
#define __FPU_PRESENT 1 /*!< FPU present or not                               */
#else
#define __FPU_PRESENT 0 /*!< FPU present or not                               */
#endif
#else
#define __FPU_PRESENT 0 /*!< FPU present or not                               */
#endif
#endif
/*@}*/ /* end of group rn831x_rn861x_mcu_CMSIS */

#include "core_cm0.h" /* Cortex-M0 processor and core peripherals           */

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
/** @addtogroup rn831x_rn861x_mcu_Peripherals rn831x_rn861x_mcu Peripherals
     rn831x_rn861x_mcu Device Specific Peripheral registers structures
    @{
*/
/* GPIO */
typedef struct
{
    __IO uint32_t PMA;                       /* 0x0 */
    __IO uint32_t PA;                        /* 0x4 */
    __IO uint32_t PCA0;                      /* 0x8 */
    __IO uint32_t PCA1;                      /* 0xC */
    __IO uint32_t PUA;                       /* 0x10 */
    __IO uint32_t PIMA;                      /* 0x14 */
    __IO uint32_t PIEA;                      /* 0x18 */
    __IO uint32_t PMB;                       /* 0x1C */
    __IO uint32_t PB;                        /* 0x20 */
    __IO uint32_t PCB;                       /* 0x24 */
    __IO uint32_t PUB;                       /* 0x28 */
    __IO uint32_t PIMB;                      /* 0x2C */
    __IO uint32_t PIEB;                      /* 0x30 */
    __IO uint32_t PMC;                       /* 0x34 */
    __IO uint32_t PC;                        /* 0x38 */
    __IO uint32_t PCC;                       /* 0x3C */
    __IO uint32_t PUC;                       /* 0x40 */
    __IO uint32_t PIEC;                      /* 0x44 */
    __IO uint32_t PIMC;                      /* 0x48 */
    __IO uint32_t PCB2;                      /* 0x4C */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t PMD;                       /* 0x50 */
    __IO uint32_t PD;                        /* 0x54 */
    __IO uint32_t PCD;                       /* 0x58 */
    __IO uint32_t PUD;                       /* 0x5C */
#else
    __IO uint32_t RESERVED0[4];              /* 0x50 ~ 0x5C */
#endif
    __IO uint32_t PCE;                       /* 0x60 */
    __IO uint32_t PASET;                     /* 0x64 */
    __IO uint32_t PACLR;                     /* 0x68 */
    __IO uint32_t PBSET;                     /* 0x6C */
    __IO uint32_t PBCLR;                     /* 0x70 */
    __IO uint32_t PCSET;                     /* 0x74 */
    __IO uint32_t PCCLR;                     /* 0x78 */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t PDSET;                     /* 0x7C */
    __IO uint32_t PDCLR;                     /* 0x80 */
    __IO uint32_t PIED;                      /* 0x84 */
    __IO uint32_t PIMD;                      /* 0x88 */
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
    __IO uint32_t PCA2;                      /* 0x8C */
    __IO uint32_t PCA3;                      /* 0x90 */
    __IO uint32_t PCB3;                      /* 0x94 */
    __IO uint32_t PCC2;                      /* 0x98 */
    __IO uint32_t PCC3;                      /* 0x9C */
    __IO uint32_t PCC4;                      /* 0xA0 */
    __IO uint32_t PCC5;                      /* 0xA4 */
    __IO uint32_t RESERVED0[2];              /* 0xA8 ~ 0xAC */
    __IO uint32_t PIMA2;                     /* 0xB0 */
    __IO uint32_t RESERVED1;                 /* 0xB4 */
    __IO uint32_t PCB5;                      /* 0xB8 */
#endif
} GPIO_TypeDef;

/* GPIO_BB */
typedef struct
{
    __IO uint32_t BB_PMA[32];                /* 0x0000 */
    __IO uint32_t BB_PA[32];                 /* 0x0080 */
    __IO uint32_t BB_PCA0[32];               /* 0x0100 */
    __IO uint32_t BB_PCA1[32];               /* 0x0180 */
    __IO uint32_t BB_PUA[32];                /* 0x0200 */
    __IO uint32_t BB_PIMA[32];               /* 0x0280 */
    __IO uint32_t BB_PIEA[32];               /* 0x0300 */
    __IO uint32_t BB_PMB[32];                /* 0x0380 */
    __IO uint32_t BB_PB[32];                 /* 0x0400 */
    __IO uint32_t BB_PCB[32];                /* 0x0480 */
    __IO uint32_t BB_PUB[32];                /* 0x0500 */
    __IO uint32_t BB_PIMB[32];               /* 0x0580 */
    __IO uint32_t BB_PIEB[32];               /* 0x0600 */
    __IO uint32_t BB_PMC[32];                /* 0x0680 */
    __IO uint32_t BB_PC[32];                 /* 0x0700 */
    __IO uint32_t BB_PCC[32];                /* 0x0780 */
    __IO uint32_t BB_PUC[32];                /* 0x0800 */
    __IO uint32_t BB_PIEC[32];               /* 0x0880 */
    __IO uint32_t BB_PIMC[32];               /* 0x0900 */
    __IO uint32_t BB_PCB2[32];               /* 0x0980 */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t BB_PMD[32];                /* 0x0A00 */
    __IO uint32_t BB_PD[32];                 /* 0x0A80 */
    __IO uint32_t BB_PCD[32];                /* 0x0B00 */
    __IO uint32_t BB_PUD[32];                /* 0x0B80 */
#else
    __IO uint32_t BB_RESERVED0[4][32];       /* 0x0A00 ~ 0x0B80 */
#endif
    __IO uint32_t BB_PCE[32];                /* 0x0C00 */
    __IO uint32_t BB_PASET[32];              /* 0x0C80 */
    __IO uint32_t BB_PACLR[32];              /* 0x0D00 */
    __IO uint32_t BB_PBSET[32];              /* 0x0D80 */
    __IO uint32_t BB_PBCLR[32];              /* 0x0E00 */
    __IO uint32_t BB_PCSET[32];              /* 0x0E80 */
    __IO uint32_t BB_PCCLR[32];              /* 0x0F00 */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t BB_PDSET[32];              /* 0x0F80 */
    __IO uint32_t BB_PDCLR[32];              /* 0x1000 */
    __IO uint32_t BB_PIED[32];               /* 0x1080 */
    __IO uint32_t BB_PIMD[32];               /* 0x1100 */
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
    __IO uint32_t BB_PCA2[32];               /* 0x1180 */
    __IO uint32_t BB_PCA3[32];               /* 0x1200 */
    __IO uint32_t BB_PCB3[32];               /* 0x1280 */
    __IO uint32_t BB_PCC2[32];               /* 0x1300 */
    __IO uint32_t BB_PCC3[32];               /* 0x1380 */
    __IO uint32_t BB_PCC4[32];               /* 0x1400 */
    __IO uint32_t BB_PCC5[32];               /* 0x1480 */
    __IO uint32_t BB_RESERVED0[2][32];       /* 0x1500 ~ 0x1580 */
    __IO uint32_t BB_PIMA2[32];              /* 0x1600 */
    __IO uint32_t BB_RESERVED1[32];          /* 0x1680 */
    __IO uint32_t BB_PCB5[32];               /* 0x1700 */
#endif
} GPIO_BB_TypeDef;

#if !defined(RN831x_RN861x_MCU_V1)
/* IOCNT */
typedef struct
{
    __IO uint32_t IOCNT0_CFG;                /* 0x0 */
    __IO uint32_t IOCNT1_CFG;                /* 0x4 */
    __IO uint32_t IOCNT2_CFG;                /* 0x8 */
    __IO uint32_t CTRL0;                     /* 0xC */
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
    __IO uint32_t RESERVED0[4];              /* 0x10 ~ 0x1C */
    __IO uint32_t IOCNT0_OUT;                /* 0x20 */
    __IO uint32_t IOCNT1_OUT;                /* 0x24 */
    __IO uint32_t IOCNT2_OUT;                /* 0x28 */
    __IO uint32_t RESERVED1[5];              /* 0x2C ~ 0x3C */
    __IO uint32_t CHNL;                      /* 0x40 */
    __IO uint32_t CTRL1;                     /* 0x44 */
    __IO uint32_t CMD;                       /* 0x48 */
#endif
#if !defined(RN831x_RN861x_MCU_V1)
} IOCNT_TypeDef;
#endif

/* UART */
typedef struct
{
    __IO uint32_t CTRL;                      /* 0x0 */
    __IO uint32_t BAUD;                      /* 0x4 */
    __IO uint32_t STA;                       /* 0x8 */
    __IO uint32_t TXD;                       /* 0xC */
    __IO uint32_t RXD;                       /* 0x10 */
    __IO uint32_t FDIV;                      /* 0x14 */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t DMA_CTRL;                  /* 0x18 */
    __IO uint32_t DMA_TBADR;                 /* 0x1C */
    __IO uint32_t DMA_RBADR;                 /* 0x20 */
    __IO uint32_t DMA_TLEN;                  /* 0x24 */
    __IO uint32_t DMA_RLEN;                  /* 0x28 */
    __IO uint32_t DMA_TADR;                  /* 0x2C */
    __IO uint32_t DMA_RADR;                  /* 0x30 */
    __IO uint32_t DMA_IE;                    /* 0x34 */
    __IO uint32_t DMA_IF;                    /* 0x38 */
    __IO uint32_t DMA_TO;                    /* 0x3C */
#endif
} UART_TypeDef;

/* TC */
typedef struct
{
    __IO uint32_t CNT;                       /* 0x0 */
    __IO uint32_t PS;                        /* 0x4 */
    __IO uint32_t RESERVED0;                 /* 0x8 */
    __IO uint32_t DN;                        /* 0xC */
    __IO uint32_t RESERVED1;                 /* 0x10 */
    __IO uint32_t CCD0;                      /* 0x14 */
    __IO uint32_t CCD1;                      /* 0x18 */
    __IO uint32_t CCFG;                      /* 0x1C */
    __IO uint32_t CTRL;                      /* 0x20 */
    __IO uint32_t CM0;                       /* 0x24 */
    __IO uint32_t CM1;                       /* 0x28 */
    __IO uint32_t IE;                        /* 0x2C */
    __IO uint32_t STA;                       /* 0x30 */
} TC_TypeDef;

/* SPI */
typedef struct
{
    __IO uint32_t CTRL;                      /* 0x0 */
    __IO uint32_t STA;                       /* 0x4 */
    __IO uint32_t TX;                        /* 0x8 */
    __IO uint32_t RX;                        /* 0xC */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t TXDFLT;                    /* 0x10 */
    __IO uint32_t DMA_CTRL;                  /* 0x14 */
    __IO uint32_t DMA_TBADR;                 /* 0x18 */
    __IO uint32_t DMA_RBADR;                 /* 0x1C */
    __IO uint32_t DMA_TLEN;                  /* 0x20 */
    __IO uint32_t DMA_RLEN;                  /* 0x24 */
    __IO uint32_t DMA_TADR;                  /* 0x28 */
    __IO uint32_t DMA_RADR;                  /* 0x2C */
    __IO uint32_t DMA_IE;                    /* 0x30 */
    __IO uint32_t DMA_FLG;                   /* 0x34 */
#endif
} SPI_TypeDef;

/* I2C */
typedef struct
{
    __IO uint32_t CTRL;                      /* 0x0 */
    __IO uint32_t CLK;                       /* 0x4 */
    __IO uint32_t STA;                       /* 0x8 */
    __IO uint32_t ADDR;                      /* 0xC */
    __IO uint32_t DATA;                      /* 0x10 */
} I2C_TypeDef;

/* KBI */
typedef struct
{
    __IO uint32_t CTRL;                      /* 0x0 */
    __IO uint32_t SEL;                       /* 0x4 */
    __IO uint32_t DATA;                      /* 0x8 */
    __IO uint32_t MASK;                      /* 0xC */
} KBI_TypeDef;

/* WDT */
typedef struct
{
    __IO uint32_t EN;                        /* 0x0 */
} WDT_TypeDef;

/* SYSCTL */
typedef struct
{
    __IO uint32_t OSC_CTRL1;                 /* 0x0 */
    __IO uint32_t SYS_MODE;                  /* 0x4 */
    __IO uint32_t SYS_PD;                    /* 0x8 */
    __IO uint32_t RESERVED0;                 /* 0xC */
    __IO uint32_t OSC_CTRL2;                 /* 0x10 */
    __IO uint32_t SYS_RST;                   /* 0x14 */
    __IO uint32_t MAP_CTRL;                  /* 0x18 */
    __IO uint32_t MOD0_EN;                   /* 0x1C */
    __IO uint32_t MOD1_EN;                   /* 0x20 */
    __IO uint32_t INTC_EN;                   /* 0x24 */
    __IO uint32_t KBI_EN;                    /* 0x28 */
    __IO uint32_t CHIP_ID;                   /* 0x2C */
    __IO uint32_t SYS_PS;                    /* 0x30 */
    __IO uint32_t IRFR_CTRL;                 /* 0x34 */
    __IO uint32_t RESERVED1[16];             /* 0x38 ~ 0x74 */
    __IO uint32_t TRIM_CFG1;                 /* 0x78 */
    __IO uint32_t TRIM_START;                /* 0x7C */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t DMA_PRI;                   /* 0x80 */
    __IO uint32_t RESERVED2[27];             /* 0x84 ~ 0xEC */
    __IO uint32_t FAB_UID0;                  /* 0xF0 */
    __IO uint32_t FAB_UID1;                  /* 0xF4 */
#endif
#if defined(RN831x_RN861x_MCU_V3)
    __IO uint32_t RESERVED3;                 /* 0xF8 */
    __IO uint32_t DMA_PRI2;                  /* 0xFC */
#endif
} SYSCTL_TypeDef;

/* ISO7816 */
typedef struct
{
    __IO uint32_t CTRL0;                     /* 0x0 */
    __IO uint32_t CTRL1;                     /* 0x4 */
    __IO uint32_t CLK;                       /* 0x8 */
    __IO uint32_t BDDIV0;                    /* 0xC */
    __IO uint32_t BDDIV1;                    /* 0x10 */
    __IO uint32_t STA0;                      /* 0x14 */
    __IO uint32_t STA1;                      /* 0x18 */
    __IO uint32_t DATA0;                     /* 0x1C */
    __IO uint32_t DATA1;                     /* 0x20 */
} ISO7816_TypeDef;

/* RTC */
typedef struct
{
    __IO uint32_t CTRL;                      /* 0x0 */
    __IO uint32_t SC;                        /* 0x4 */
    __IO uint32_t MN;                        /* 0x8 */
    __IO uint32_t HR;                        /* 0xC */
    __IO uint32_t DT;                        /* 0x10 */
    __IO uint32_t MO;                        /* 0x14 */
    __IO uint32_t YR;                        /* 0x18 */
    __IO uint32_t DW;                        /* 0x1C */
    __IO uint32_t CNT1;                      /* 0x20 */
    __IO uint32_t CNT2;                      /* 0x24 */
    __IO uint32_t SCA;                       /* 0x28 */
    __IO uint32_t MNA;                       /* 0x2C */
    __IO uint32_t HRA;                       /* 0x30 */
    __IO uint32_t IE;                        /* 0x34 */
    __IO uint32_t IF;                        /* 0x38 */
    __IO uint32_t TEMP;                      /* 0x3C */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t PS;                        /* 0x40 */
    __IO uint32_t MODE;                      /* 0x44 */
    __IO uint32_t DOTA0;                     /* 0x48 */
    __IO uint32_t ALPHAL;                    /* 0x4C */
    __IO uint32_t ALPHAH;                    /* 0x50 */
    __IO uint32_t XT0;                       /* 0x54 */
    __IO uint32_t TADJ;                      /* 0x58 */
    __IO uint32_t RESERVED0;                 /* 0x5C */
    __IO uint32_t ZT;                        /* 0x60 */
    __IO uint32_t DOTAT;                     /* 0x64 */
    __IO uint32_t RESERVED1;                 /* 0x68 */
#endif
#if !defined(RN831x_RN861x_MCU_V3) &&  !defined(RN831x_RN861x_MCU_V2)
//    __IO uint32_t RESERVED0[11];             /* 0x40 ~ 0x68 */
#endif
    __IO uint32_t LOSC_CFG1;                 /* 0x6C */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t RESERVED2;                 /* 0x70 */
    __IO uint32_t FPTR;                      /* 0x74 */
    __IO uint32_t FDTR1S;                    /* 0x78 */
    __IO uint32_t FDTR30S;                   /* 0x7C */
    __IO uint32_t RESERVED3;                 /* 0x80 */
    __IO uint32_t FDTR120S;                  /* 0x84 */
#endif
#if !defined(RN831x_RN861x_MCU_V3) &&  !defined(RN831x_RN861x_MCU_V2)
//    __IO uint32_t RESERVED1[6];              /* 0x70 ~ 0x84 */
#endif
    __IO uint32_t IOEN;                      /* 0x88 */
    __IO uint32_t IOMODE;                    /* 0x8C */
    __IO uint32_t P44N0_TIME0;               /* 0x90 */
    __IO uint32_t P44N0_TIME1;               /* 0x94 */
    __IO uint32_t P44N0_TIME2;               /* 0x98 */
    __IO uint32_t P44P0_TIME0;               /* 0x9C */
    __IO uint32_t P44P0_TIME1;               /* 0xA0 */
    __IO uint32_t P44P0_TIME2;               /* 0xA4 */
    __IO uint32_t P44N1_TIME0;               /* 0xA8 */
    __IO uint32_t P44N1_TIME1;               /* 0xAC */
    __IO uint32_t P44N1_TIME2;               /* 0xB0 */
    __IO uint32_t P44P1_TIME0;               /* 0xB4 */
    __IO uint32_t P44P1_TIME1;               /* 0xB8 */
    __IO uint32_t P44P1_TIME2;               /* 0xBC */
#if !defined(RN831x_RN861x_MCU_V3) &&  !defined(RN831x_RN861x_MCU_V2)
//    __IO uint32_t RESERVED2[3];              /* 0xC0 ~ 0xC8 */
#endif
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t RESERVED4[3];              /* 0xC0 ~ 0xC8 */
#endif
    __IO uint32_t CALPS;                     /* 0xCC */
    __IO uint32_t CAL_T[10];                 /* 0xd0~0xF4 */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t TEMP2;                     /* 0xF8 */
    __IO uint32_t RESERVED5;                 /* 0xFC */
#endif
#if !defined(RN831x_RN861x_MCU_V3) &&  !defined(RN831x_RN861x_MCU_V2)
//    __IO uint32_t RESERVED3[2];              /* 0xF8 ~ 0xFC */
#endif
    __IO uint32_t P45N0_TIME0;               /* 0x100 */
    __IO uint32_t P45N0_TIME1;               /* 0x104 */
    __IO uint32_t P45N0_TIME2;               /* 0x108 */
    __IO uint32_t P45P0_TIME0;               /* 0x10C */
    __IO uint32_t P45P0_TIME1;               /* 0x110 */
    __IO uint32_t P45P0_TIME2;               /* 0x114 */
    __IO uint32_t P45N1_TIME0;               /* 0x118 */
    __IO uint32_t P45N1_TIME1;               /* 0x11C */
    __IO uint32_t P45N1_TIME2;               /* 0x120 */
    __IO uint32_t P45P1_TIME0;               /* 0x124 */
    __IO uint32_t P45P1_TIME1;               /* 0x128 */
    __IO uint32_t P45P1_TIME2;               /* 0x12C */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t MODE1;                     /* 0x130 */
    __IO uint32_t XT1;                       /* 0x134 */
    __IO uint32_t ALPHA;                     /* 0x138 */
    __IO uint32_t BETA;                      /* 0x13C */
    __IO uint32_t GAMMA;                     /* 0x140 */
    __IO uint32_t ZETA;                      /* 0x144 */
#endif
} RTC_TypeDef;

/* MADC */
typedef struct
{
    __IO uint32_t AD_CTRL;                   /* 0x0 */
    __IO uint32_t AD_START;                  /* 0x4 */
    __IO uint32_t AD_STAT;                   /* 0x8 */
    __IO uint32_t AD_DATA;                   /* 0xC */
    __IO uint32_t LVD_CTRL;                  /* 0x10 */
    __IO uint32_t LVD_STAT;                  /* 0x14 */
#if !defined(RN831x_RN861x_MCU_V1)
    __IO uint32_t AD_CTRL1;                  /* 0x18 */
    __IO uint32_t AD_DATA2;                  /* 0x1C */
    __IO uint32_t RESERVED0[7];              /* 0x20 ~ 0x38 */
#else
    __IO uint32_t RESERVED0[9];              /* 0x18 ~ 0x38 */
#endif
    __IO uint32_t ANA_PAD;                   /* 0x3C */
    __IO uint32_t ANA_RST;                   /* 0x40 */
} MADC_TypeDef;

/* INTC */
typedef struct
{
    __IO uint32_t CTRL;                      /* 0x0 */
    __IO uint32_t MODE;                      /* 0x4 */
    __IO uint32_t MASK;                      /* 0x8 */
    __IO uint32_t STA;                       /* 0xC */
} INTC_TypeDef;

/* LCD */
typedef struct
{
    __IO uint32_t CTRL;                      /* 0x0 */
    __IO uint32_t STA;                       /* 0x4 */
    __IO uint32_t CLKDIV;                    /* 0x8 */
    __IO uint32_t BLINK;                     /* 0xC */
    __IO uint32_t PS;                        /* 0x10 */
    __IO uint32_t RESCTL;                    /* 0x14 */
    __IO uint32_t RESERVED0[2];              /* 0x18 ~ 0x1C */
    __IO uint8_t BUF[38];                    /* 0x20 ~ 0x45 */
    __IO uint8_t RESERVED1[2];               /* 0x46 ~ 0x47 */
} LCD_TypeDef;

#if defined(RN831x_RN861x_MCU_V1)
/*--------------------- CP --------------------------------------------------*/
typedef struct {
  __IO uint32_t CTRL      ;             /* offset 0x0          CP control register            */
  __IO uint32_t IN1[6]    ;             /* offset 0x4~0x1c     CP data input register1        */
  __IO uint32_t IN2[6]    ;             /* offset 0x20~0x3c    CP data input register2        */
  __IO uint32_t RES[12]   ;             /* offset 0x0x40~0x70  CP data output register        */
} CP_TypeDef;

typedef struct {
  __IO uint32_t CTRL      ;             /* offset  0x0         AES ENC control register        */
  __IO uint32_t STAT      ;             /* offset  0x4         AES ENC status register         */
  __IO uint32_t RESERVED[2];            /* offset  0x8~0xc     RESERVED address                */
  __IO uint32_t KEY[8]    ;             /* offset  0x10~0x2c   AES ENC KEY register            */
  __IO uint32_t PT[4]     ;             /* offset  0x30~3c     AES ENC Plain Text register     */
  __IO uint32_t IV[4]     ;             /* offset  0x40~4c     AES ENC Initial Vector register */
  __IO uint32_t CT[4]     ;             /* offset  0x50~5c     AES ENC Cyper Text register     */
} AES_ENC_TypeDef;

typedef struct {
  __IO uint32_t CTRL      ;             /* offset  0x0         AES DEC control register        */
  __IO uint32_t STAT      ;             /* offset  0x4         AES DEC status register         */
  __IO uint32_t RESERVED[2];            /* offset  0x8~0xc     RESERVED address                */
  __IO uint32_t KEY[8]    ;             /* offset  0x10~0x2c   AES DEC KEY register            */
  __IO uint32_t PT[4]     ;             /* offset  0x30~3c     AES DEC Plain Text register     */
  __IO uint32_t IV[4]     ;             /* offset  0x40~4c     AES DEC Initial Vector register */
  __IO uint32_t CT[4]     ;             /* offset  0x50~5c     AES DEC Cyper Text register     */
} AES_DEC_TypeDef;

typedef struct {
  __IO uint32_t CTRL      ;             /* offset  0x0         GHASH control register          */
  __IO uint32_t STAT      ;             /* offset  0x4         GHASH status register           */
  __IO uint32_t RESERVED[2];            /* offset  0x8~0xc     RESERVED address                */
  __IO uint32_t HT[4]     ;             /* offset  0x10~0x1c   GHASH sub key register          */
  __IO uint32_t AT[4]     ;             /* offset  0x20~0x2c   GHASH initial vector register   */
  __IO uint32_t CT[4]     ;             /* offset  0x30~0x3c   GHASH input vector register     */
  __IO uint32_t RT[4]     ;             /* offset  0x40~0x4c   GHASH output vector register    */
} GHASH_TypeDef;
#endif

#if !defined(RN831x_RN861x_MCU_V1)

/* SIMP_TC */
typedef struct
{
    __IO uint32_t CTRL;                      /* 0x0 */
    __IO uint32_t LOAD;                      /* 0x4 */
    __IO uint32_t VAL;                       /* 0x8 */
} SIMP_TC_TypeDef;

/* D2F */
typedef struct
{
    __IO uint32_t HFCONST3;                  /* 0x0 */
    __IO uint32_t IE;                        /* 0x4 */
    __IO uint32_t IF;                        /* 0x8 */
    __IO uint32_t CFG;                       /* 0xC */
    __IO uint32_t D2FP[12];  /* 0x10-0x3c */
    __IO uint32_t D2FE[12];  /* 0x40-0x6c */
} D2F_TypeDef;
#endif

#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V3)
/* M2M */
typedef struct
{
    __IO uint32_t MODE;                      /* 0x0 */
    __IO uint32_t CTL;                       /* 0x4 */
    __IO uint32_t DUMMY;                     /* 0x8 */
    __IO uint32_t SADDR;                     /* 0xC */
    __IO uint32_t DADDR;                     /* 0x10 */
    __IO uint32_t ILEN;                      /* 0x14 */
    __IO uint32_t IE;                        /* 0x18 */
    __IO uint32_t IF;                        /* 0x1C */
} M2M_TypeDef;

/* DSP */
typedef struct
{
    __IO uint32_t MAC_CTL0;                  /* 0x0 */
    __IO uint32_t MAC_CTL1;                  /* 0x4 */
    __IO uint32_t MAC_CTL2;                  /* 0x8 */
    __IO uint32_t MAC_IN0;                   /* 0xC */
    __IO uint32_t MAC_IN1;                   /* 0x10 */
    __IO uint32_t MAC_IN2;                   /* 0x14 */
    __IO uint32_t MAC_IN3;                   /* 0x18 */
    __IO uint32_t MAC_IN4;                   /* 0x1C */
    __IO uint32_t MAC_IN5;                   /* 0x20 */
    __IO uint32_t MAC_OUT0;                  /* 0x24 */
    __IO uint32_t MAC_OUT1;                  /* 0x28 */
    __IO uint32_t MAC_OUT2;                  /* 0x2C */
    __IO uint32_t MAC_OUT3;                  /* 0x30 */
    __IO uint32_t DIV_IN0;                   /* 0x34 */
    __IO uint32_t DIV_IN1;                   /* 0x38 */
    __IO uint32_t DIV_OUT0;                  /* 0x3C */
    __IO uint32_t DMA_SRBADR;                /* 0x40 */
    __IO uint32_t DMA_SIBADR;                /* 0x44 */
    __IO uint32_t DMA_PRBADR;                /* 0x48 */
    __IO uint32_t DMA_PIBADR;                /* 0x4C */
    __IO uint32_t DMA_TRBADR;                /* 0x50 */
    __IO uint32_t DMA_TIBADR;                /* 0x54 */
    __IO uint32_t DMA_LEN;                   /* 0x58 */
    __IO uint32_t IE;                        /* 0x5C */
    __IO uint32_t FLG;                       /* 0x60 */
    __IO uint32_t ALU_STA0;                  /* 0x64 */
    __IO uint32_t ALU_STA1;                  /* 0x68 */
    __IO uint32_t CRD_CTL;                   /* 0x6C */
    __IO uint32_t CRD_XIN;                   /* 0x70 */
    __IO uint32_t CRD_YIN;                   /* 0x74 */
    __IO uint32_t CRD_AMP;                   /* 0x78 */
    __IO uint32_t CRD_PHASE;                 /* 0x7C */
    __IO uint32_t CRD_ANGLE;                 /* 0x80 */
    __IO uint32_t CRD_COS;                   /* 0x84 */
    __IO uint32_t CRD_SIN;                   /* 0x88 */
    __IO uint32_t CRD_IE;                    /* 0x8C */
    __IO uint32_t CRD_FLG;                   /* 0x90 */
    __IO uint32_t INTP_LEN;                  /* 0x94 */
    __IO uint32_t INTP_LOC;                  /* 0x98 */
    __IO uint32_t INTP_STEP;                 /* 0x9C */
} DSP_TypeDef;
#endif

#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
/* LSRX */
typedef struct
{
    __IO uint32_t FTOP;                      /* 0x0 */
    __IO uint32_t CFG;                       /* 0x4 */
    __IO uint32_t CTRL;                      /* 0x8 */
    __IO uint32_t PAM;                       /* 0xC */
    __IO uint32_t CAL_CFG;                   /* 0x10 */
    __IO uint32_t EN;                        /* 0x14 */
    __IO uint32_t ZX_STA;                    /* 0x18 */
    __IO uint32_t IE;                        /* 0x1C */
    __IO uint32_t IF;                        /* 0x20 */
    __IO uint32_t ZX_TIME0;                  /* 0x24 */
    __IO uint32_t ZX_TIME1;                  /* 0x28 */
    __IO uint32_t ZX_TIME2;                  /* 0x2C */
    __IO uint32_t FLA_DST0;                  /* 0x30 */
    __IO uint32_t FLA_DST1;                  /* 0x34 */
    __IO uint32_t FLA_DST2;                  /* 0x38 */
} LSRX_TypeDef;

/* SIMPTC_CFG */
typedef struct
{
    __IO uint32_t CFG;                       /* 0x0 */
} SIMPTC_CFG_TypeDef;
#endif

/*@}*/ /* end of group rn831x_rn861x_mcu_Peripherals */
/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/** @addtogroup rn831x_rn861x_mcu_MemoryMap rn831x_rn861x_mcu Memory Mapping
  @{
*/

/* base address */
#define MADC_BASE       (0x4002C000U)
#if !defined(RN831x_RN861x_MCU_V1)
#define D2F_BASE        (0x4005C000U)
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V3)
#define DSP_BASE        (0x40064000U)
#endif
#define GPIO_BASE       (0x50000000U)
#define I2C_BASE        (0x40024000U)
#define INTC_BASE       (0x40044000U)
#if !defined(RN831x_RN861x_MCU_V1)
#define IOCNT_BASE      (0x50000100U)
#endif
#define ISO7816_BASE    (0x40038000U)
#define KBI_BASE        (0x40028000U)
#define LCD_BASE        (0x40048000U)
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V3)
#define M2M_BASE        (0x40068000U)
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define LSRX_BASE       (0x40084000U)
#endif
#define RTC_BASE        (0x4003C000U)
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define SIMPTC_CFG_BASE (0x40060058U)
#endif
#if !defined(RN831x_RN861x_MCU_V1)
#define SIMP_TC0_BASE   (0x40060000U)
#define SIMP_TC1_BASE   (0x4006000CU)
#define SIMP_TC2_BASE   (0x40060018U)
#define SIMP_TC3_BASE   (0x40060024U)
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define SIMP_TC4_BASE   (0x40060030U)
#endif
#define SPI0_BASE       (0x40020000U)
#if !defined(RN831x_RN861x_MCU_V1)
#define SPI1_BASE       (0x40050000U)
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V3)
#define SPI2_BASE       (0x40054000U)
#define SPI3_BASE       (0x40058000U)
#endif
#define SYSCTL_BASE     (0x40034000U)
#define TC0_BASE        (0x40010000U)
#if !defined(RN831x_RN861x_MCU_V3)
#define TC1_BASE        (0x40014000U)
#endif
#define UART0_BASE      (0x40000000U)
#define UART1_BASE      (0x40004000U)
#define UART2_BASE      (0x40008000U)
#define UART3_BASE      (0x4000C000U)
#define UART4_BASE      (0x40018000U)
#define UART5_BASE      (0x4001C000U)
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define UART6_BASE      (0x4007C000U)
#define UART7_BASE      (0x40080000U)
#endif
#define WDT_BASE        (0x40030000U)

/* bitband base address */
#define BB_OFFSET       (0x02000000U)
#define GPIO_BB_BASE     (BB_OFFSET + (GPIO_BASE     & 0xFC000000U) + ((GPIO_BASE & 0x03FFFFFFU) << 5U))
#define I2C_BB_BASE      (BB_OFFSET + (I2C_BASE      & 0xFC000000U) + ((I2C_BASE & 0x03FFFFFFU) << 5U))
#define TC0_BB_BASE      (BB_OFFSET + (TC0_BASE      & 0xFC000000U) + ((TC0_BASE & 0x03FFFFFFU) << 5U))
#if !defined(RN831x_RN861x_MCU_V3)
#define TC1_BB_BASE      (BB_OFFSET + (TC1_BASE      & 0xFC000000U) + ((TC1_BASE & 0x03FFFFFFU) << 5U))
#endif
#define UART0_BB_BASE    (BB_OFFSET + (UART0_BASE    & 0xFC000000U) + ((UART0_BASE & 0x03FFFFFFU) << 5U))
#define UART1_BB_BASE    (BB_OFFSET + (UART1_BASE    & 0xFC000000U) + ((UART1_BASE & 0x03FFFFFFU) << 5U))
#define UART2_BB_BASE    (BB_OFFSET + (UART2_BASE    & 0xFC000000U) + ((UART2_BASE & 0x03FFFFFFU) << 5U))
#define UART3_BB_BASE    (BB_OFFSET + (UART3_BASE    & 0xFC000000U) + ((UART3_BASE & 0x03FFFFFFU) << 5U))
#define UART4_BB_BASE    (BB_OFFSET + (UART4_BASE    & 0xFC000000U) + ((UART4_BASE & 0x03FFFFFFU) << 5U))
#define UART5_BB_BASE    (BB_OFFSET + (UART5_BASE    & 0xFC000000U) + ((UART5_BASE & 0x03FFFFFFU) << 5U))

#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define UART6_BB_BASE    (BB_OFFSET + (UART6_BASE    & 0xFC000000U) + ((UART6_BASE & 0x03FFFFFFU) << 5U))
#define UART7_BB_BASE    (BB_OFFSET + (UART7_BASE    & 0xFC000000U) + ((UART7_BASE & 0x03FFFFFFU) << 5U))
#endif

#if defined(RN831x_RN861x_MCU_V1)
#define HS_PERIPH_BASE (0x50000000U)
#define HSP_BASE     (HS_PERIPH_BASE)
#define CP_BASE      (HSP_BASE + 0xC000U)
#define AES_ENC_BASE (HSP_BASE + 0xD000U)
#define AES_DEC_BASE (HSP_BASE + 0xE000U)
#define GHASH_BASE   (HSP_BASE + 0xF000U)
#endif


/* #endif */
/*@}*/ /* end of group rn831x_rn861x_mcu_MemoryMap */

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define MADC       ((MADC_TypeDef *)     MADC_BASE)
#if !defined(RN831x_RN861x_MCU_V1)
#define D2F        ((D2F_TypeDef *)      D2F_BASE)
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V3)
#define DSP        ((DSP_TypeDef *)      DSP_BASE)
#endif
#define GPIO       ((GPIO_TypeDef *)     GPIO_BASE)
#define I2C        ((I2C_TypeDef *)      I2C_BASE)
#define INTC       ((INTC_TypeDef *)     INTC_BASE)
#if !defined(RN831x_RN861x_MCU_V1)
#define IOCNT      ((IOCNT_TypeDef *)    IOCNT_BASE)
#endif
#define ISO7816    ((ISO7816_TypeDef *)  ISO7816_BASE)
#define KBI        ((KBI_TypeDef *)      KBI_BASE)
#define LCD        ((LCD_TypeDef *)      LCD_BASE)
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V3)
#define M2M        ((M2M_TypeDef *)      M2M_BASE)
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define LSRX       ((LSRX_TypeDef *)     LSRX_BASE)
#endif
#define RTC        ((RTC_TypeDef *)      RTC_BASE)
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define SIMPTC_CFG ((SIMPTC_CFG_TypeDef *)SIMPTC_CFG_BASE)
#endif
#if !defined(RN831x_RN861x_MCU_V1)
#define SIMP_TC0   ((SIMP_TC_TypeDef *)  SIMP_TC0_BASE)
#define SIMP_TC1   ((SIMP_TC_TypeDef *)  SIMP_TC1_BASE)
#define SIMP_TC2   ((SIMP_TC_TypeDef *)  SIMP_TC2_BASE)
#define SIMP_TC3   ((SIMP_TC_TypeDef *)  SIMP_TC3_BASE)
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define SIMP_TC4   ((SIMP_TC_TypeDef *)  SIMP_TC4_BASE)
#endif
#define SPI        ((SPI_TypeDef *)      SPI0_BASE)
#if !defined(RN831x_RN861x_MCU_V1)
#define SPI1       ((SPI_TypeDef *)      SPI1_BASE)
#endif
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V3)
#define SPI2       ((SPI_TypeDef *)      SPI2_BASE)
#define SPI3       ((SPI_TypeDef *)      SPI3_BASE)
#endif
#define SYSCTL     ((SYSCTL_TypeDef *)   SYSCTL_BASE)
#define TC0        ((TC_TypeDef *)       TC0_BASE)
#if !defined(RN831x_RN861x_MCU_V3)
#define TC1        ((TC_TypeDef *)       TC1_BASE)
#endif
#define UART0      ((UART_TypeDef *)     UART0_BASE)
#define UART1      ((UART_TypeDef *)     UART1_BASE)
#define UART2      ((UART_TypeDef *)     UART2_BASE)
#define UART3      ((UART_TypeDef *)     UART3_BASE)
#define UART4      ((UART_TypeDef *)     UART4_BASE)
#define UART5      ((UART_TypeDef *)     UART5_BASE)
#if !defined(RN831x_RN861x_MCU_V1) && !defined(RN831x_RN861x_MCU_V2)
#define UART6      ((UART_TypeDef *)     UART6_BASE)
#define UART7      ((UART_TypeDef *)     UART7_BASE)
#endif
#define WDT        ((WDT_TypeDef *)      WDT_BASE)

#if defined(RN831x_RN861x_MCU_V1)
#define CP ((CP_TypeDef*) CP_BASE)
#define AES_ENC ((AES_ENC_TypeDef *) AES_ENC_BASE       )
#define AES_DEC ((AES_DEC_TypeDef *) AES_DEC_BASE       )
#define GHASH   ((GHASH_TypeDef   *) GHASH_BASE         )
#define DMA     ((DMA_TypeDef     *) DMA_BASE           )
#endif

/* bitband declaration */
#define GPIO_BB    ((GPIO_BB_TypeDef *)  GPIO_BB_BASE)

/* bit operations */
#define REG32(addr) (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr) (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr) (*(volatile uint8_t *)(uint32_t)(addr))
#define BIT(x) ((uint32_t)((uint32_t)0x01U << (x)))
#define BITS(start, end)  (((0xFFFFFFFFUL >> start) << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))
#define GET_BITS(regval, start, end) (((regval)&BITS((start), (end))) >> (start))

/*@}*/ /* end of group rn831x_rn861x_mcu_Definitions */


#define GPIO_OFFSET                      0x50000000
#define GPIO_PMA                        (GPIO_OFFSET+0x00)
#define GPIO_PA                         (GPIO_OFFSET+0x04)
#define GPIO_PCA0                       (GPIO_OFFSET+0x08)
#define GPIO_PCA1                       (GPIO_OFFSET+0x0C)
#define GPIO_PUA                        (GPIO_OFFSET+0x10)
#define GPIO_PIMA                       (GPIO_OFFSET+0x14)
#define GPIO_PIEA                       (GPIO_OFFSET+0x18)

#define GPIO_PMB                        (GPIO_OFFSET+0x1C)
#define GPIO_PB                         (GPIO_OFFSET+0x20)
#define GPIO_PCB                        (GPIO_OFFSET+0x24)
#define GPIO_PUB                        (GPIO_OFFSET+0x28)
#define GPIO_PIMB                       (GPIO_OFFSET+0x2C)
#define GPIO_PIEB                       (GPIO_OFFSET+0x30)

#define GPIO_PMC                        (GPIO_OFFSET+0x34)
#define GPIO_PC                         (GPIO_OFFSET+0x38)
#define GPIO_PCC                        (GPIO_OFFSET+0x3C)
#define GPIO_PUC                        (GPIO_OFFSET+0x40)
#define GPIO_PIEC                       (GPIO_OFFSET+0x44)
#define GPIO_PIMC                       (GPIO_OFFSET+0x48)
#define GPIO_PCB2                       (GPIO_OFFSET+0x4C)

/* PCA0 */
#define  UART2_SEL    BIT30
#define  SWD_SEL      BIT29
#define  PC267_IO     0
#define  PC267_UART3        BIT28
#define  PC245_IO     0
#define  PC245_UART2        BIT27
#define  PC223_IO     0
#define  PC223_UART1        BIT26
#define  PC201_IO     0
#define  PC201_UART0        BIT25
#define  PC17_IO      0
#define  PC17_KEY     BIT23
#define  PC17_TC_OUT  BIT24
#define  PC17_TC_IN   (BIT23+BIT24)
#define  PC16_IO      0
#define  PC16_KEY     BIT21
#define  PC16_TC_OUT  BIT22
#define  PC16_TC_IN   (BIT21+BIT22)
#define  PC15_IO      0
#define  PC15_KEY     BIT19
#define  PC15_TC_OUT  BIT20
#define  PC15_TC_IN   (BIT19+BIT20)
#define  PC14_IO      0
#define  PC14_KEY     BIT17
#define  PC14_TC_OUT  BIT18
#define  PC14_TC_IN   (BIT17+BIT18)
#define  PC13_IO      0
#define  PC13_KEY     BIT15
#define  PC13_TC_OUT  BIT16
#define  PC13_TC_IN   (BIT15+BIT16)
#define  PC12_IO      0
#define  PC12_KEY     BIT13
#define  PC12_TC_OUT  BIT14
#define  PC12_TC_IN   (BIT13+BIT14)
#define  PC11_IO      0
#define  PC11_KEY     BIT11
#define  PC11_TC_OUT  BIT12
#define  PC11_TC_IN   (BIT11+BIT12)
#define  PC10_IO      0
#define  PC10_KEY     BIT9
#define  PC10_TC_OUT  BIT10
#define  PC10_TC_IN   (BIT9+BIT10)
#define  KEY4_SEL     BIT8
#define  PC04_AIN         BIT6
#define  PC03_AIN         BIT5
#define  PC02_AIN         BIT4
#define  PC01_IO      0
#define  PC01_AIN     BIT2
#define  PC01_KEY3    BIT3
#define  PC01_TX2     (BIT2+BIT3)
#define  PC00_IO      0
#define  PC00_AIN     BIT0
#define  PC00_KEY2    BIT1
#define  PC00_RX2     (BIT0+BIT1)
/* PCA1 */
#define  PC37_IO       0
#define  PC37_INT7     BIT14
#define  PC37_POSCI    BIT15

#define  PC36_IO       0
#define  PC36_INT6     BIT12
#define  PC36_POSCO    BIT13

#define  PC35_IO       0
#define  PC35_INT5     BIT10
#define  PC35_TC_IN    BIT11

#define  PC34_IO       0
#define  PC34_INT4     BIT8
#define  PC34_SF_OUT   BIT9

#define  PC33_IO       0
#define  PC33_INT3     BIT6
#define  PC33_TC_IN    BIT7

#define  PC32_IO       0
#define  PC32_INT2     BIT4
#define  PC32_RTC_OUT  BIT5

#define  PC31_IO       0
#define  PC31_INT1     BIT2
#define  PC31_TC_IN    BIT3
#define  PC31_RX4      (BIT2+BIT3)

#define  PC30_IO       0
#define  PC30_INT0     BIT0
#define  PC30_TC_IN    BIT1


/* PCB */
#define  PC77_LCD      BIT31
#define  PC76_LCD      BIT30
#define  PC75_LCD      BIT29
#define  PC74_LCD      BIT28
#define  PC73_LCD      BIT27
#define  PC72_LCD      BIT26
#define  PC71_LCD      BIT25
#define  PC70_LCD      BIT24

#define  PC67_LCD      BIT23
#define  PC66_LCD      BIT22
#define  PC65_LCD      BIT21
#define  PC64_LCD      BIT20
#define  PC63_LCD      BIT19
#define  PC62_LCD      BIT18
#define  PC61_LCD      BIT17
#define  PC60_LCD      BIT16

#define  PC57_IO       0
#define  PC56_IO       0
#define  PC55_IO       0
#define  PC54_IO       0
#define  PC53_IO       0
#define  PC52_IO       0
#define  PC51_IO       0
#define  PC50_IO       0

#define  PC55_TX5      BIT13
#define  PC54_RX5      BIT12
#define  PC53_SDA      BIT11
#define  PC52_SCL      BIT10
#define  PC51_INT2_QF  BIT9
#define  PC50_INT0_PF  BIT8

#define  PC47_IO       0
#define  PC46_IO       0
#define  PC45_IO       0
#define  PC44_IO       0
#define  PC43_IO       0
#define  PC42_IO       0
#define  PC41_IO       0
#define  PC40_IO       0

#define  PC47_SPI      BIT7
#define  PC46_SPI      BIT6
#define  PC45_SPI      BIT5
#define  PC44_SPI      BIT4
#define  PC43_7816     BIT3
#define  PC42_7816     BIT2
#define  PC41_7816     BIT1
#define  PC40_7816     BIT0

/* PCB2 */
#define  PC57_2_TCIN    BIT30
#define  PC57_2_TC1_P1  BIT31
#define  PC56_2_TCIN    BIT28
#define  PC56_2_TC1_N1  BIT29
#define  PC55_2_TCIN    BIT26
#define  PC55_2_TC1_P0  BIT27
#define  PC54_2_TCIN    BIT24
#define  PC54_2_TC1_N0  BIT25
#define  PC53_2_TCIN    BIT22
#define  PC53_2_TC0P1   BIT23
#define  PC52_2_TCIN    BIT20
#define  PC52_2_TC0N1   BIT21
#define  PC51_2_RTC_OUT BIT18
#define  PC51_2_SPI_CLK BIT19
#define  PC51_2_INT7_SF2  (BIT19+BIT18)
#define  PC50_2_RTC_OUT BIT16
#define  PC50_2_SPI_SCSN  BIT17
#define  PC50_2_INT6_SF1  (BIT16+BIT17)
#define  PC47_2_TX4       BIT14
#define  PC46_2_RX4       BIT12
#define  PC45_2_KEY7      BIT10 /** PC17 youxianjigao */
#define  PC45_2_AIN6      BIT11 
#define  PC44_2_KEY6      BIT8  /** PC16 youxianjigao */
#define  PC44_2_AIN5      BIT9  
#define  PC43_2_INT5      BIT6  /** PC35 youxianjigao */
#define  PC42_2_INT4      BIT4  /** PC34 youxianjigao */
#define  PC41_2_INT3      BIT2  /** PC33 youxianjigao */
#define  PC40_2_INT1      BIT0  /** PC31 youxianjigao */

/* PCC */
#define  SPI_MUX_P11      BIT28
#define  PC113_SPI        BIT27
#define  PC112_SPI        BIT26
#define  PC111_SPI        BIT25
#define  PC110_SPI        BIT24

#define  PC103_LCD        BIT19
#define  PC102_LCD        BIT18
#define  PC101_LCD        BIT17
#define  PC100_LCD        BIT16

#define  PC97_LCD         BIT15
#define  PC96_LCD         BIT14
#define  PC95_LCD         BIT13
#define  PC94_LCD         BIT12
#define  PC93_LCD         BIT11
#define  PC92_LCD         BIT10
#define  PC91_LCD         BIT9
#define  PC90_LCD         BIT8 

#define  PC87_LCD         BIT7
#define  PC86_LCD         BIT6
#define  PC85_LCD         BIT5
#define  PC84_LCD         BIT4
#define  PC83_LCD         BIT3
#define  PC82_LCD         BIT2
#define  PC81_LCD         BIT1
#define  PC80_LCD         BIT0

/* PCE */
#define  COM7             BIT3
#define  COM6             BIT2
#define  COM5             BIT1
#define  COM4             BIT0

/* PMA */
#define  PM37_IN          BIT31
#define  PM37_OUT         0
#define  PM36_IN          BIT30
#define  PM36_OUT         0
#define  PM35_IN          BIT29
#define  PM35_OUT         0
#define  PM34_IN          BIT28
#define  PM34_OUT         0
#define  PM33_IN          BIT27
#define  PM33_OUT         0
#define  PM32_IN          BIT26
#define  PM32_OUT         0
#define  PM31_IN          BIT25
#define  PM31_OUT         0
#define  PM30_IN          BIT24
#define  PM30_OUT         0

#define  PM27_IN          BIT23
#define  PM27_OUT         0
#define  PM26_IN          BIT22
#define  PM26_OUT         0
#define  PM25_IN          BIT21
#define  PM25_OUT         0
#define  PM24_IN          BIT20
#define  PM24_OUT         0
#define  PM23_IN          BIT19
#define  PM23_OUT         0
#define  PM22_IN          BIT18
#define  PM22_OUT         0
#define  PM21_IN          BIT17
#define  PM21_OUT         0
#define  PM20_IN          BIT16
#define  PM20_OUT         0

#define  PM17_IN          BIT15
#define  PM17_OUT         0
#define  PM16_IN          BIT14
#define  PM16_OUT         0
#define  PM15_IN          BIT13
#define  PM15_OUT         0
#define  PM14_IN          BIT12
#define  PM14_OUT         0
#define  PM13_IN          BIT11
#define  PM13_OUT         0
#define  PM12_IN          BIT10
#define  PM12_OUT         0
#define  PM11_IN          BIT9
#define  PM11_OUT         0
#define  PM10_IN          BIT8
#define  PM10_OUT         0

#define  PM04_IN          BIT4
#define  PM04_OUT         0
#define  PM03_IN          BIT3
#define  PM03_OUT         0
#define  PM02_IN          BIT2
#define  PM02_OUT         0
#define  PM01_IN          BIT1
#define  PM01_OUT         0
#define  PM00_IN          BIT0
#define  PM00_OUT         0

#define  PM77_IN          BIT31
#define  PM77_OUT         0
#define  PM76_IN          BIT30
#define  PM76_OUT         0
#define  PM75_IN          BIT29
#define  PM75_OUT         0
#define  PM74_IN          BIT28
#define  PM74_OUT         0
#define  PM73_IN          BIT27
#define  PM73_OUT         0
#define  PM72_IN          BIT26
#define  PM72_OUT         0
#define  PM71_IN          BIT25
#define  PM71_OUT         0
#define  PM70_IN          BIT24
#define  PM70_OUT         0

#define  PM67_IN          BIT23
#define  PM67_OUT         0
#define  PM66_IN          BIT22
#define  PM66_OUT         0
#define  PM65_IN          BIT21
#define  PM65_OUT         0
#define  PM64_IN          BIT20
#define  PM64_OUT         0
#define  PM63_IN          BIT19
#define  PM63_OUT         0
#define  PM62_IN          BIT18
#define  PM62_OUT         0
#define  PM61_IN          BIT17
#define  PM61_OUT         0
#define  PM60_IN          BIT16
#define  PM60_OUT         0

#define  PM57_IN          BIT15
#define  PM57_OUT         0
#define  PM56_IN          BIT14
#define  PM56_OUT         0
#define  PM55_IN          BIT13
#define  PM55_OUT         0
#define  PM54_IN          BIT12
#define  PM54_OUT         0
#define  PM53_IN          BIT11
#define  PM53_OUT         0
#define  PM52_IN          BIT10
#define  PM52_OUT         0
#define  PM51_IN          BIT9
#define  PM51_OUT         0
#define  PM50_IN          BIT8
#define  PM50_OUT         0

#define  PM47_IN          BIT7
#define  PM47_OUT         0
#define  PM46_IN          BIT6
#define  PM46_OUT         0
#define  PM45_IN          BIT5
#define  PM45_OUT         0
#define  PM44_IN          BIT4
#define  PM44_OUT         0
#define  PM43_IN          BIT3
#define  PM43_OUT         0
#define  PM42_IN          BIT2
#define  PM42_OUT         0
#define  PM41_IN          BIT1
#define  PM41_OUT         0
#define  PM40_IN          BIT0
#define  PM40_OUT         0

/* PC */

#define  PM117_IN          BIT31
#define  PM117_OUT         0
#define  PM116_IN          BIT30
#define  PM116_OUT         0
#define  PM115_IN          BIT29
#define  PM115_OUT         0
#define  PM114_IN          BIT28
#define  PM114_OUT         0
#define  PM113_IN          BIT27
#define  PM113_OUT         0
#define  PM112_IN          BIT26
#define  PM112_OUT         0
#define  PM111_IN          BIT25
#define  PM111_OUT         0
#define  PM110_IN          BIT24
#define  PM110_OUT         0

#define  PM107_IN          BIT23
#define  PM107_OUT         0
#define  PM106_IN          BIT22
#define  PM106_OUT         0
#define  PM105_IN          BIT21
#define  PM105_OUT         0
#define  PM104_IN          BIT20
#define  PM104_OUT         0
#define  PM103_IN          BIT19
#define  PM103_OUT         0
#define  PM102_IN          BIT18
#define  PM102_OUT         0
#define  PM101_IN          BIT17
#define  PM101_OUT         0
#define  PM100_IN          BIT16
#define  PM100_OUT         0

#define  PM97_IN          BIT15
#define  PM97_OUT         0
#define  PM96_IN          BIT14
#define  PM96_OUT         0
#define  PM95_IN          BIT13
#define  PM95_OUT         0
#define  PM94_IN          BIT12
#define  PM94_OUT         0
#define  PM93_IN          BIT11
#define  PM93_OUT         0
#define  PM92_IN          BIT10
#define  PM92_OUT         0
#define  PM91_IN          BIT9
#define  PM91_OUT         0
#define  PM90_IN          BIT8
#define  PM90_OUT         0

#define  PM87_IN          BIT7
#define  PM87_OUT         0
#define  PM86_IN          BIT6
#define  PM86_OUT         0
#define  PM85_IN          BIT5
#define  PM85_OUT         0
#define  PM84_IN          BIT4
#define  PM84_OUT         0
#define  PM83_IN          BIT3
#define  PM83_OUT         0
#define  PM82_IN          BIT2
#define  PM82_OUT         0
#define  PM81_IN          BIT1
#define  PM81_OUT         0
#define  PM80_IN          BIT0
#define  PM80_OUT         0


#define  EN_EXT_INT(X)    (SYSCTL->INTC_EN   |=   (0x01 << X))
#define  DIS_EXT_INT(X)   (SYSCTL->INTC_EN   &=   ~(0x01 << X))

/* INTC_MODE */
#define  INT7_RISE_MODE    0
#define  INT7_FALL_MODE    BIT14
#define  INT7_BOTH_MODE    BIT15

#define  INT6_RISE_MODE    0
#define  INT6_FALL_MODE    BIT12
#define  INT6_BOTH_MODE    BIT13

#define  INT5_RISE_MODE    0
#define  INT5_FALL_MODE    BIT10
#define  INT5_BOTH_MODE    BIT11

#define  INT4_RISE_MODE    0
#define  INT4_FALL_MODE    BIT8
#define  INT4_BOTH_MODE    BIT9

#define  INT3_RISE_MODE    0
#define  INT3_FALL_MODE    BIT6
#define  INT3_BOTH_MODE    BIT7

#define  INT2_RISE_MODE    0
#define  INT2_FALL_MODE    BIT4
#define  INT2_BOTH_MODE    BIT5

#define  INT1_RISE_MODE    0
#define  INT1_FALL_MODE    BIT2
#define  INT1_BOTH_MODE    BIT3

#define  INT0_RISE_MODE    0
#define  INT0_FALL_MODE    BIT0
#define  INT0_BOTH_MODE    BIT1



#define SPI_EN          (0x00000001 << 15)
#define IIC_EN          (0x00000001 << 14)
#define ISO7816_EN      (0x00000001 << 13)
#define UART38K_EN      (0x00000001 << 12)
#define UART3_EN        (0x00000001 << 11)
#define UART2_EN        (0x00000001 << 10)
#define UART1_EN        (0x00000001 << 9)
#define UART0_EN        (0x00000001 << 8)
#define UART5_EN        (0x00000001 << 7)
#define UART4_EN        (0x00000001 << 6)
#define TC1_EN          (0x00000001 << 5)
#define TC0_EN          (0x00000001 << 4)

#ifdef __cplusplus
}
#endif

#endif /* RN831X_RN861X_MCU_H */
/* r1974 */
