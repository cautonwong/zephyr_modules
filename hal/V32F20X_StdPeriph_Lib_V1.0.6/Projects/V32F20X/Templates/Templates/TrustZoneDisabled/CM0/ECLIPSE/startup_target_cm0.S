;/**
;* @file    startup_target.s
;* @author  Application Team
;* @version V4.4.0
;* @date    2019-01-07
;* @brief   Target Devices vector table.
;******************************************************************************/

  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb

.equ __CHIPINITIAL, 1

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss


  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:

/* set stack pointer */
  ldr   r0, =_estack
  mov   sp, r0

/* Copy the data segment initializers from flash to SRAM */
  movs r1, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4

LoopCopyDataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyDataInit
  ldr r2, =_sbss
  b LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs r3, #0
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss

/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever

.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  .word  PMU_IRQHandler            //  0:  PMU
  .word  I2C14_IRQHandler          //  1:  I2C14
  .word  BDMA_IRQHandler           //  2:  BDMA
  .word  UART14_IRQHandler         //  3:  UART14
  .word  UART15_IRQHandler         //  4:  UART15
  .word  UART16_IRQHandler         //  5:  UART16
  .word  UART17_IRQHandler         //  6:  UART17
  .word  UART18_IRQHandler         //  7:  UART18
  .word  UART19_IRQHandler         //  8:  UART19
  .word  ISO78162_IRQHandler       //  9:  ISO7816 2
  .word  ISO78163_IRQHandler       // 10:  ISO7816 3
  .word  MEM_ECC_IRQHandler        // 11:  Memory ECC
  .word  BTMR4_5_IRQHandler        // 12:  BTMR4 and BTMR5
  .word  BTMR6_IRQHandler          // 13:  BTMR6
  .word  BTMR7_IRQHandler          // 14:  BTMR7
  .word  BPWM4_IRQHandler          // 15:  BPWM4
  .word  BPWM5_IRQHandler          // 16:  BPWM5
  .word  BPWM6_IRQHandler          // 17:  BPWM6
  .word  BPWM7_IRQHandler          // 18:  BPWM7
  .word  HFM_COP_IRQHandler        // 19:  HFM
  .word  BSPI0_IRQHandler          // 20:  BSPI0
  .word  BSPI1_IRQHandler          // 21:  BSPI1
  .word  BSPI2_IRQHandler          // 22:  BSPI2
  .word  BSPI3_IRQHandler          // 23:  BSPI3
  .word  BSPI4_IRQHandler          // 24:  BSPI4
  .word  BSPI5_IRQHandler          // 25:  BSPI5
  .word  FLASH0_IRQHandler         // 26:  FLASH0
  .word  RTC_RTCALM_IRQHandler     // 27:  RTC and RTC_ALM
  .word  MAILBOX_IRQHandler        // 28:  Mailbox CM0
  .word  GPIO_IRQHandler           // 29:  IO
  .word  SYSCFGLP_ANA_CMP_IRQHandler // 30:  SYSCFGLP_ANA_CMP
  .word  LPBTMR_IRQHandler          // 31:  LPBTMR

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

    .weak   PMU_IRQHandler
    .thumb_set PMU_IRQHandler,Default_Handler

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

    .weak   MEM_ECC_IRQHandler
    .thumb_set MEM_ECC_IRQHandler,Default_Handler

    .weak   BTMR4_5_IRQHandler
    .thumb_set BTMR4_5_IRQHandler,Default_Handler

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

    .weak   HFM_COP_IRQHandler
    .thumb_set HFM_COP_IRQHandler,Default_Handler

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

    .weak   FLASH0_IRQHandler
    .thumb_set FLASH0_IRQHandler,Default_Handler

    .weak   RTC_RTCALM_IRQHandler
    .thumb_set RTC_RTCALM_IRQHandler,Default_Handler

    .weak   MAILBOX_IRQHandler
    .thumb_set MAILBOX_IRQHandler,Default_Handler

    .weak   GPIO_IRQHandler
    .thumb_set GPIO_IRQHandler,Default_Handler

    .weak   SYSCFGLP_ANA_CMP_IRQHandler
    .thumb_set SYSCFGLP_ANA_CMP_IRQHandler,Default_Handler

    .weak   LPBTMR_IRQHandler
    .thumb_set LPBTMR_IRQHandler,Default_Handler

/*********************************** END OF FILE ******************************/
