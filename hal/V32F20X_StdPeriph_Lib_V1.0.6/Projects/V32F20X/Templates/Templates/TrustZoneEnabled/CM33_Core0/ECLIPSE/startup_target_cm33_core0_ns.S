/**
 * @file    startup_target_cm33_core0_ns.s
 * @author  Application Team
 * @version V1.0.0
 * @date    2022-05-07
 * @brief   Target Devices vector table.
******************************************************************************/
    .syntax unified
    .cpu cortex-m33
    .fpu softvfp
    .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word   _sidata
/* start address for the .data section. defined in linker script */
.word   _sdata
/* end address for the .data section. defined in linker script */
.word   _edata
/* start address for the .bss section. defined in linker script */
.word   _sbss
/* end address for the .bss section. defined in linker script */
.word   _ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section    .text.Reset_Handler
    .weak   Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack    /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b LoopCopyDataInit

CopyDataInit:
    ldr r3, =_sidata
    ldr r3, [r3, r1]
    str r3, [r0, r1]
    adds    r1, r1, #4

LoopCopyDataInit:
    ldr r0, =_sdata
    ldr r3, =_edata
    adds    r2, r0, r1
    cmp r2, r3
    bcc CopyDataInit
    ldr r2, =_sbss
    b   LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
    movs    r3, #0
    str r3, [r2], #4

LoopFillZerobss:
    ldr r3, = _ebss
    cmp r2, r3
    bcc FillZerobss

/* Call the clock system initialization function.*/
    bl  SystemInit
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
    bl  main

LoopForever:
    b LoopForever

.size   Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section    .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b   Infinite_Loop
    .size   Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex-M33.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
    .section    .isr_vector,"a",%progbits
    .type   g_pfnVectors, %object
    .size   g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
    .word   _estack
    .word   Reset_Handler
    .word   NMI_Handler
    .word   HardFault_Handler
    .word   MemManage_Handler
    .word   BusFault_Handler
    .word   UsageFault_Handler
    .word   SecureFault_Handler
    .word   0
    .word   0
    .word   0
    .word   SVC_Handler
    .word   DebugMon_Handler
    .word   0
    .word   PendSV_Handler
    .word   SysTick_Handler
   // Cortex-M33 External Interrupts (#0~97)
    .word   CM33_MAILBOX_IRQHandler   // CM33_MAILBOX global interrupts
    .word   CM0_MAILBOX_IRQHandler    // CM0_MAILBOX global interrupts
    .word   0                         // Reserved
    .word   0                         // Reserved
    .word   I2S0_IRQHandler           // I2S0
    .word   I2S1_IRQHandler           // I2S1
    .word   USB_HS_IRQHandler         // USB HS
    .word   USB_FS_IRQHandler         // USB FS
    .word   OSPI0_IRQHandler          // OSPI0
    .word   OSPI1_IRQHandler          // OSPI1
    .word   FLASHA_IRQHandler         // FLASHA
    .word   FLASHB_IRQHandler         // FLASHB
    .word   ISO78160_1_IRQHandler     // ISO7816 0/1
    .word   MEM_ECC_IRQHandler        // Memory ECC global interrupts
    .word   BTMR0_IRQHandler          // BTMR0
    .word   BTMR1_IRQHandler          // BTMR1
    .word   BTMR2_IRQHandler          // BTMR2
    .word   BTMR3_IRQHandler          // BTMR3
    .word   BPWM0_IRQHandler          // BPWM0
    .word   BPWM1_IRQHandler          // BPWM1
    .word   BPWM2_IRQHandler          // BPWM2
    .word   BPWM3_IRQHandler          // BPWM3
    .word   SDIO0_IRQHandler          // SDIO0
    .word   SDIO1_IRQHandler          // SDIO1
    .word   RNG_IRQHandler            // RNG
    .word   EADC_IRQHandler           // EADC
    .word   SCR_IRQHandler            // SCR global interrupts
    .word   CAN0_IRQHandler           // CAN0
    .word   CAN1_IRQHandler           // CAN1
    .word   ETMR0_UP_IRQHandler        // ETMR0 Update
    .word   ETMR0_BRK_IRQHandler       // ETMR0 Break
    .word   ETMR0_CC_IRQHandler        // ETMR0 Capture Compare
    .word   ETMR0_TRG_COM_IRQHandler   // ETMR0 Trigger and Commutation
    .word   ETMR1_UP_IRQHandler        // ETMR1 Update
    .word   ETMR1_BRK_IRQHandler       // ETMR1 Break
    .word   ETMR1_CC_IRQHandler        // ETMR1 Capture Compare
    .word   ETMR1_TRG_COM_IRQHandler   // ETMR1 Trigger and Commutation
    .word   GTMR0_IRQHandler           // GTMR0
    .word   GTMR1_IRQHandler           // GTMR1
    .word   GTMR2_IRQHandler           // GTMR2
    .word   GTMR3_IRQHandler           // GTMR3
    .word   DMA0_CH0_IRQHandler       // DMA0 Channel 0
    .word   DMA0_CH1_IRQHandler       // DMA0 Channel 1
    .word   DMA0_CH2_IRQHandler       // DMA0 Channel 2
    .word   DMA0_CH3_IRQHandler       // DMA0 Channel 3
    .word   DMA0_CH4_IRQHandler       // DMA0 Channel 4
    .word   DMA0_CH5_IRQHandler       // DMA0 Channel 5
    .word   DMA0_CH6_IRQHandler       // DMA0 Channel 6
    .word   DMA0_CH7_IRQHandler       // DMA0 Channel 7
    .word   0                         // Reserved
    .word   0                         // Reserved
    .word   ADC0_IRQHandler           // ADC1
    .word   ADC1_IRQHandler           // ADC2
    .word   ENCENG_IRQHandler         // ENCENG
    .word   MAC0_SBD_IRQHandler       // MAC0 SBD
    .word   MAC0_PMT_IRQHandler       // MAC0 PMT
    .word   MAC1_SBD_IRQHandler       // MAC1 SBD
    .word   MAC1_PMT_IRQHandler       // MAC1 PMT
    .word   DCMI_IRQHandler           // DCMI
    .word   CDMA_ADC_IRQHandler         // DSMADC
    .word   FLEXCOMM0_IRQHandler      // FLEXCOMM0
    .word   FLEXCOMM1_IRQHandler      // FLEXCOMM1
    .word   FLEXCOMM2_IRQHandler      // FLEXCOMM2
    .word   FLEXCOMM3_IRQHandler      // FLEXCOMM3
    .word   FLEXCOMM4_IRQHandler      // FLEXCOMM4
    .word   FLEXCOMM5_IRQHandler      // FLEXCOMM5
    .word   FLEXCOMM6_IRQHandler      // FLEXCOMM6
    .word   FLEXCOMM7_IRQHandler      // FLEXCOMM7
    .word   FLEXCOMM8_IRQHandler      // FLEXCOMM8
    .word   FLEXCOMM9_IRQHandler      // FLEXCOMM9
    .word   FLEXCOMM10_IRQHandler     // FLEXCOMM10
    .word   FLEXCOMM11_IRQHandler     // FLEXCOMM11
    .word   FLEXCOMM12_IRQHandler     // FLEXCOMM12
    .word   FLEXCOMM13_IRQHandler     // FLEXCOMM13
    .word   DMA1_CH0_IRQHandler       // DMA1 Channel 0
    .word   DMA1_CH1_IRQHandler       // DMA1 Channel 1
    .word   DMA1_CH2_IRQHandler       // DMA1 Channel 2
    .word   DMA1_CH3_IRQHandler       // DMA1 Channel 3
    .word   DMA1_CH4_IRQHandler       // DMA1 Channel 4
    .word   DMA1_CH5_IRQHandler       // DMA1 Channel 5
    .word   DMA1_CH6_IRQHandler       // DMA1 Channel 6
    .word   DMA1_CH7_IRQHandler       // DMA1 Channel 7
    .word   EXTI0_IRQHandler          // EXTI Line0
    .word   EXTI1_IRQHandler          // EXTI Line1
    .word   EXTI2_IRQHandler          // EXTI Line2
    .word   EXTI3_IRQHandler          // EXTI Line3
    .word   EXTI4_IRQHandler          // EXTI Line4
    .word   EXTI5_IRQHandler          // EXTI Line5
    .word   EXTI6_IRQHandler          // EXTI Line6
    .word   EXTI7_IRQHandler          // EXTI Line7
    .word   EXTI8_IRQHandler          // EXTI Line8
    .word   EXTI9_IRQHandler          // EXTI Line9
    .word   EXTI10_IRQHandler         // EXTI Line10
    .word   EXTI11_IRQHandler         // EXTI Line11
    .word   EXTI12_IRQHandler         // EXTI Line12
    .word   EXTI13_IRQHandler         // EXTI Line13
    .word   EXTI14_IRQHandler         // EXTI Line14
    .word   EXTI15_IRQHandler         // EXTI Line15
    .word   I2C14_IRQHandler          // I2C0
    .word   BDMA_IRQHandler           // DMA
    .word   UART14_IRQHandler         // UART14
    .word   UART15_IRQHandler         // UART15
    .word   UART16_IRQHandler         // UART16
    .word   UART17_IRQHandler         // UART17
    .word   UART18_IRQHandler         // UART18
    .word   UART19_IRQHandler         // UART19
    .word   ISO78162_IRQHandler       // ISO78162
    .word   ISO78163_IRQHandler       // ISO78163
    .word   BTMR4_IRQHandler          // BTMR0
    .word   BTMR5_IRQHandler          // BTMR1
    .word   BTMR6_IRQHandler          // BTMR2
    .word   BTMR7_IRQHandler          // BTMR3
    .word   BPWM4_IRQHandler          // BPWM0
    .word   BPWM5_IRQHandler          // BPWM1
    .word   BPWM6_IRQHandler          // BPWM2
    .word   BPWM7_IRQHandler          // BPWM3
    .word   FLASH0_IRQHandler         // FLASH0
    .word   BSPI0_IRQHandler          // BSPI0
    .word   BSPI1_IRQHandler          // BSPI1
    .word   BSPI2_IRQHandler          // BSPI2
    .word   BSPI3_IRQHandler          // BSPI3
    .word   BSPI4_IRQHandler          // BSPI4
    .word   BSPI5_IRQHandler          // BSPI5
    .word   HFM_COP_IRQHandler        // HFM & COP
    .word   RTC_IRQHandler            // RTC global interrupts
    .word   PMU_IRQHandler            // PMU global interrupts
    .word   RTC_ALM_IRQHandler        // RTC Alarm
    .word   SYSCFGLP_ANA_IRQHandler  // SYSCFGLP & Analog global interrupts
    .word   LPBTMR_IRQHandler         // LPBTMR
    .word   0                         // Reserved
    .word   COMP_IRQHandler           // Comparator
                
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0


/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

    .weak   NMI_Handler
    .thumb_set NMI_Handler,Default_Handler

    .weak   HardFault_Handler
    .thumb_set HardFault_Handler,Default_Handler

    .weak   MemManage_Handler
    .thumb_set MemManage_Handler,Default_Handler

    .weak   BusFault_Handler
    .thumb_set BusFault_Handler,Default_Handler

    .weak   UsageFault_Handler
    .thumb_set UsageFault_Handler,Default_Handler

    .weak   SecureFault_Handler
    .thumb_set SecureFault_Handler,Default_Handler

    .weak   SVC_Handler
    .thumb_set SVC_Handler,Default_Handler

    .weak   DebugMon_Handler
    .thumb_set DebugMon_Handler,Default_Handler

    .weak   PendSV_Handler
    .thumb_set PendSV_Handler,Default_Handler

    .weak   SysTick_Handler
    .thumb_set SysTick_Handler,Default_Handler

    .weak   CM33_MAILBOX_IRQHandler
    .thumb_set CM33_MAILBOX_IRQHandler,Default_Handler

    .weak   CM0_MAILBOX_IRQHandler
    .thumb_set CM0_MAILBOX_IRQHandler,Default_Handler

    .weak   I2S0_IRQHandler
    .thumb_set I2S0_IRQHandler,Default_Handler

    .weak   I2S1_IRQHandler
    .thumb_set I2S1_IRQHandler,Default_Handler

    .weak   USB_HS_IRQHandler
    .thumb_set USB_HS_IRQHandler,Default_Handler

    .weak   USB_FS_IRQHandler
    .thumb_set USB_FS_IRQHandler,Default_Handler

    .weak   OSPI0_IRQHandler
    .thumb_set OSPI0_IRQHandler,Default_Handler

    .weak   OSPI1_IRQHandler
    .thumb_set OSPI1_IRQHandler,Default_Handler

    .weak   FLASHA_IRQHandler
    .thumb_set FLASHA_IRQHandler,Default_Handler

    .weak   FLASHB_IRQHandler
    .thumb_set FLASHB_IRQHandler,Default_Handler

    .weak   ISO78160_1_IRQHandler
    .thumb_set ISO78160_1_IRQHandler,Default_Handler

    .weak   MEM_ECC_IRQHandler
    .thumb_set MEM_ECC_IRQHandler,Default_Handler

    .weak   BTMR0_IRQHandler
    .thumb_set BTMR0_IRQHandler,Default_Handler

    .weak   BTMR1_IRQHandler
    .thumb_set BTMR1_IRQHandler,Default_Handler

    .weak   BTMR2_IRQHandler
    .thumb_set BTMR2_IRQHandler,Default_Handler

    .weak   BTMR3_IRQHandler
    .thumb_set BTMR3_IRQHandler,Default_Handler

    .weak   BPWM0_IRQHandler
    .thumb_set BPWM0_IRQHandler,Default_Handler

    .weak   BPWM1_IRQHandler
    .thumb_set BPWM1_IRQHandler,Default_Handler

    .weak   BPWM2_IRQHandler
    .thumb_set BPWM2_IRQHandler,Default_Handler

    .weak   BPWM3_IRQHandler
    .thumb_set BPWM3_IRQHandler,Default_Handler

    .weak   SDIO0_IRQHandler
    .thumb_set SDIO0_IRQHandler,Default_Handler

    .weak   SDIO1_IRQHandler
    .thumb_set SDIO1_IRQHandler,Default_Handler

    .weak   RNG_IRQHandler
    .thumb_set RNG_IRQHandler,Default_Handler

    .weak   EADC_IRQHandler
    .thumb_set EADC_IRQHandler,Default_Handler

    .weak   SCR_IRQHandler
    .thumb_set SCR_IRQHandler,Default_Handler

    .weak   CAN0_IRQHandler
    .thumb_set CAN0_IRQHandler,Default_Handler

    .weak   CAN1_IRQHandler
    .thumb_set CAN1_IRQHandler,Default_Handler

    .weak   ETMR0_UP_IRQHandler
    .thumb_set ETMR0_UP_IRQHandler,Default_Handler

    .weak   ETMR0_BRK_IRQHandler
    .thumb_set ETMR0_BRK_IRQHandler,Default_Handler

    .weak   ETMR0_CC_IRQHandler
    .thumb_set ETMR0_CC_IRQHandler,Default_Handler

    .weak   ETMR0_TRG_COM_IRQHandler
    .thumb_set ETMR0_TRG_COM_IRQHandler,Default_Handler

    .weak   ETMR1_UP_IRQHandler
    .thumb_set ETMR1_UP_IRQHandler,Default_Handler

    .weak   ETMR1_BRK_IRQHandler
    .thumb_set ETMR1_BRK_IRQHandler,Default_Handler

    .weak   ETMR1_CC_IRQHandler
    .thumb_set ETMR1_CC_IRQHandler,Default_Handler

    .weak   ETMR1_TRG_COM_IRQHandler
    .thumb_set ETMR1_TRG_COM_IRQHandler,Default_Handler

    .weak   GTMR0_IRQHandler
    .thumb_set GTMR0_IRQHandler,Default_Handler

    .weak   GTMR1_IRQHandler
    .thumb_set GTMR1_IRQHandler,Default_Handler

    .weak   GTMR2_IRQHandler
    .thumb_set GTMR2_IRQHandler,Default_Handler

    .weak   GTMR3_IRQHandler
    .thumb_set GTMR3_IRQHandler,Default_Handler

    .weak   DMA0_CH0_IRQHandler
    .thumb_set DMA0_CH0_IRQHandler,Default_Handler

    .weak   DMA0_CH1_IRQHandler
    .thumb_set DMA0_CH1_IRQHandler,Default_Handler

    .weak   DMA0_CH2_IRQHandler
    .thumb_set DMA0_CH2_IRQHandler,Default_Handler

    .weak   DMA0_CH3_IRQHandler
    .thumb_set DMA0_CH3_IRQHandler,Default_Handler

    .weak   DMA0_CH4_IRQHandler
    .thumb_set DMA0_CH4_IRQHandler,Default_Handler

    .weak   DMA0_CH5_IRQHandler
    .thumb_set DMA0_CH5_IRQHandler,Default_Handler

    .weak   DMA0_CH6_IRQHandler
    .thumb_set DMA0_CH6_IRQHandler,Default_Handler

    .weak   DMA0_CH7_IRQHandler
    .thumb_set DMA0_CH7_IRQHandler,Default_Handler

    .weak   ADC0_IRQHandler
    .thumb_set ADC0_IRQHandler,Default_Handler

    .weak   ADC1_IRQHandler
    .thumb_set ADC1_IRQHandler,Default_Handler

    .weak   ENCENG_IRQHandler
    .thumb_set ENCENG_IRQHandler,Default_Handler

    .weak   MAC0_SBD_IRQHandler
    .thumb_set MAC0_SBD_IRQHandler,Default_Handler

    .weak   MAC0_PMT_IRQHandler
    .thumb_set MAC0_PMT_IRQHandler,Default_Handler

    .weak   MAC1_SBD_IRQHandler
    .thumb_set MAC1_SBD_IRQHandler,Default_Handler

    .weak   MAC1_PMT_IRQHandler
    .thumb_set MAC1_PMT_IRQHandler,Default_Handler

    .weak   DCMI_IRQHandler
    .thumb_set DCMI_IRQHandler,Default_Handler
    
    .weak   CDMA_ADC_IRQHandler
    .thumb_set CDMA_ADC_IRQHandler,Default_Handler

    .weak   FLEXCOMM0_IRQHandler
    .thumb_set FLEXCOMM0_IRQHandler,Default_Handler

    .weak   FLEXCOMM1_IRQHandler
    .thumb_set FLEXCOMM1_IRQHandler,Default_Handler

    .weak   FLEXCOMM2_IRQHandler
    .thumb_set FLEXCOMM2_IRQHandler,Default_Handler

    .weak   FLEXCOMM3_IRQHandler
    .thumb_set FLEXCOMM3_IRQHandler,Default_Handler

    .weak   FLEXCOMM4_IRQHandler
    .thumb_set FLEXCOMM4_IRQHandler,Default_Handler

    .weak   FLEXCOMM5_IRQHandler
    .thumb_set FLEXCOMM5_IRQHandler,Default_Handler

    .weak   FLEXCOMM6_IRQHandler
    .thumb_set FLEXCOMM6_IRQHandler,Default_Handler

    .weak   FLEXCOMM7_IRQHandler
    .thumb_set FLEXCOMM7_IRQHandler,Default_Handler

    .weak   FLEXCOMM8_IRQHandler
    .thumb_set FLEXCOMM8_IRQHandler,Default_Handler

    .weak   FLEXCOMM9_IRQHandler
    .thumb_set FLEXCOMM9_IRQHandler,Default_Handler

    .weak   FLEXCOMM10_IRQHandler
    .thumb_set FLEXCOMM10_IRQHandler,Default_Handler

    .weak   FLEXCOMM11_IRQHandler
    .thumb_set FLEXCOMM11_IRQHandler,Default_Handler

    .weak   FLEXCOMM12_IRQHandler
    .thumb_set FLEXCOMM12_IRQHandler,Default_Handler

    .weak   FLEXCOMM13_IRQHandler
    .thumb_set FLEXCOMM13_IRQHandler,Default_Handler

    .weak   DMA1_CH0_IRQHandler
    .thumb_set DMA1_CH0_IRQHandler,Default_Handler

    .weak   DMA1_CH1_IRQHandler
    .thumb_set DMA1_CH1_IRQHandler,Default_Handler

    .weak   DMA1_CH2_IRQHandler
    .thumb_set DMA1_CH2_IRQHandler,Default_Handler

    .weak   DMA1_CH3_IRQHandler
    .thumb_set DMA1_CH3_IRQHandler,Default_Handler

    .weak   DMA1_CH4_IRQHandler
    .thumb_set DMA1_CH4_IRQHandler,Default_Handler

    .weak   DMA1_CH5_IRQHandler
    .thumb_set DMA1_CH5_IRQHandler,Default_Handler

    .weak   DMA1_CH6_IRQHandler
    .thumb_set DMA1_CH6_IRQHandler,Default_Handler

    .weak   DMA1_CH7_IRQHandler
    .thumb_set DMA1_CH7_IRQHandler,Default_Handler

    .weak   EXTI0_IRQHandler
    .thumb_set EXTI0_IRQHandler,Default_Handler

    .weak   EXTI1_IRQHandler
    .thumb_set EXTI1_IRQHandler,Default_Handler

    .weak   EXTI2_IRQHandler
    .thumb_set EXTI2_IRQHandler,Default_Handler

    .weak   EXTI3_IRQHandler
    .thumb_set EXTI3_IRQHandler,Default_Handler

    .weak   EXTI4_IRQHandler
    .thumb_set EXTI4_IRQHandler,Default_Handler

    .weak   EXTI5_IRQHandler
    .thumb_set EXTI5_IRQHandler,Default_Handler

    .weak   EXTI6_IRQHandler
    .thumb_set EXTI6_IRQHandler,Default_Handler

    .weak   EXTI7_IRQHandler
    .thumb_set EXTI7_IRQHandler,Default_Handler

    .weak   EXTI8_IRQHandler
    .thumb_set EXTI8_IRQHandler,Default_Handler

    .weak   EXTI9_IRQHandler
    .thumb_set EXTI9_IRQHandler,Default_Handler

    .weak   EXTI10_IRQHandler
    .thumb_set EXTI10_IRQHandler,Default_Handler

    .weak   EXTI11_IRQHandler
    .thumb_set EXTI11_IRQHandler,Default_Handler

    .weak   EXTI12_IRQHandler
    .thumb_set EXTI12_IRQHandler,Default_Handler

    .weak   EXTI13_IRQHandler
    .thumb_set EXTI13_IRQHandler,Default_Handler

    .weak   EXTI14_IRQHandler
    .thumb_set EXTI14_IRQHandler,Default_Handler

    .weak   EXTI15_IRQHandler
    .thumb_set EXTI15_IRQHandler,Default_Handler

    .weak   I2C14_IRQHandler
    .thumb_set I2C14_IRQHandler,Default_Handler

    .weak   BDMA_IRQHandler
    .thumb_set BDMA_IRQHandler,Default_Handler

    .weak   UART14_IRQHandler
    .thumb_set UART14_IRQHandler,Default_Handler

    .weak   UART15_IRQHandler
    .thumb_set UART15_IRQHandler,Default_Handler

    .weak   UART16_IRQHandler
    .thumb_set UART16_IRQHandler,Default_Handler

    .weak   UART17_IRQHandler
    .thumb_set UART17_IRQHandler,Default_Handler

    .weak   UART18_IRQHandler
    .thumb_set UART18_IRQHandler,Default_Handler

    .weak   UART19_IRQHandler
    .thumb_set UART19_IRQHandler,Default_Handler

    .weak   ISO78162_IRQHandler
    .thumb_set ISO78162_IRQHandler,Default_Handler
    
    .weak   ISO78163_IRQHandler
    .thumb_set ISO78163_IRQHandler,Default_Handler

    .weak   BTMR4_IRQHandler
    .thumb_set BTMR4_IRQHandler,Default_Handler

    .weak   BTMR5_IRQHandler
    .thumb_set BTMR5_IRQHandler,Default_Handler

    .weak   BTMR6_IRQHandler
    .thumb_set BTMR6_IRQHandler,Default_Handler

    .weak   BTMR7_IRQHandler
    .thumb_set BTMR7_IRQHandler,Default_Handler

    .weak   BPWM4_IRQHandler
    .thumb_set BPWM4_IRQHandler,Default_Handler

    .weak   BPWM5_IRQHandler
    .thumb_set BPWM5_IRQHandler,Default_Handler

    .weak   BPWM6_IRQHandler
    .thumb_set BPWM6_IRQHandler,Default_Handler

    .weak   BPWM7_IRQHandler
    .thumb_set BPWM7_IRQHandler,Default_Handler

    .weak   FLASH0_IRQHandler
    .thumb_set FLASH0_IRQHandler,Default_Handler

    .weak   BSPI0_IRQHandler
    .thumb_set BSPI0_IRQHandler,Default_Handler

    .weak   BSPI1_IRQHandler
    .thumb_set BSPI1_IRQHandler,Default_Handler

    .weak   BSPI2_IRQHandler
    .thumb_set BSPI2_IRQHandler,Default_Handler

    .weak   BSPI3_IRQHandler
    .thumb_set BSPI3_IRQHandler,Default_Handler

    .weak   BSPI4_IRQHandler
    .thumb_set BSPI4_IRQHandler,Default_Handler

    .weak   BSPI5_IRQHandler
    .thumb_set BSPI5_IRQHandler,Default_Handler

    .weak   HFM_COP_IRQHandler
    .thumb_set HFM_COP_IRQHandler,Default_Handler

    .weak   RTC_IRQHandler
    .thumb_set RTC_IRQHandler,Default_Handler

    .weak   PMU_IRQHandler
    .thumb_set PMU_IRQHandler,Default_Handler

    .weak   RTC_ALM_IRQHandler
    .thumb_set RTC_ALM_IRQHandler,Default_Handler

    .weak   SYSCFGLP_ANA_IRQHandler
    .thumb_set SYSCFGLP_ANA_IRQHandler,Default_Handler

    .weak   LPBTMR_IRQHandler
    .thumb_set LPBTMR_IRQHandler,Default_Handler

    .weak   COMP_IRQHandler
    .thumb_set COMP_IRQHandler,Default_Handler


/*********************************** END OF FILE ******************************/
