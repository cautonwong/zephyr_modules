;/**
;* @file    startup_target.s
;* @author  Application Team
;* @version V4.4.0
;* @date    2019-01-07
;* @brief   Target Devices vector table.
;******************************************************************************/

  .syntax unified
  .cpu cortex-m33
 // .fpu fpv5-sp-d16
   .fpu softvfp
  .thumb



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
  .word          _estack              // Top of Stack
  .word          Reset_Handler             // Reset Handler
  .word          NMI_Handler               // NMI Handler
  .word          HardFault_Handler         // Hard Fault Handler
  .word          MemManage_Handler         // MPU Fault Handler
  .word          BusFault_Handler          // Bus Fault Handler
  .word          UsageFault_Handler        // Usage Fault Handler
  .word          SecureFault_Handler       // Secure Fault Handler
  .word          0                         // Reserved
  .word          0                         // Reserved
  .word          0                         // Reserved
  .word          SVC_Handler               // SVCall Handler
  .word          DebugMon_Handler          // Debug Monitor Handler
  .word          0                         // Reserved
  .word          PendSV_Handler            // PendSV Handler
  .word          SysTick_Handler           // SysTick Handler

                // External Interrupts
  .word          CM33_MAILBOX_IRQHandler
  .word          CM0_MAILBOX_IRQHandler
  .word          0
  .word          0
  .word          I2S0_IRQHandle
  .word          I2S1_IRQHandler
  .word          USB_HS_IRQHandler
  .word          USB_FS_IRQHandler
  .word          SSI_0_IRQHandler
  .word          SSI_1_IRQHandler
  .word          FLASHA_IRQHandler
  .word          FLASHB_IRQHandler
  .word          ISO781633_0_1_IRQHandler
  .word          MEM_ECC_IRQHandler
  .word          BTMR33_0_IRQHandler
  .word          BTMR33_1_IRQHandler
  .word          BTMR33_2_IRQHandler
  .word          BTMR33_3_IRQHandler
  .word          PWM33_0_IRQHandler
  .word          PWM33_1_IRQHandler
  .word          PWM33_2_IRQHandler
  .word          PWM33_3_IRQHandler
  .word          SDIO_0_IRQHandler
  .word          SDIO_1_IRQHandler
  .word          RNG_IRQHandler
  .word          EADC_IRQHandler
  .word          SCR_IRQHandler
  .word          CAN_0_IRQHandler
  .word          CAN_1_IRQHandler
  .word          TIM1_UP_IRQHandler
  .word          TIM1_BRK_IRQHandler
  .word          TIM1_CC_IRQHandler
  .word          TIM1_TRG_COM_IRQHandler
  .word          TIM2_UP_IRQHandler
  .word          TIM2_BRK_IRQHandler
  .word          TIM2_CC_IRQHandler
  .word          TIM2_TRG_COM_IRQHandler
  .word          TMR3_UP_BRK_CC_TRG_IRQHandler
  .word          TMR4_UP_BRK_CC_TRG_IRQHandler
  .word          TMR5_UP_BRK_CC_TRG_IRQHandler
  .word          TMR6_UP_BRK_CC_TRG_IRQHandler
  .word          DMA0_CH0_IRQHandler
  .word          DMA0_CH1_IRQHandler
  .word          DMA0_CH2_IRQHandler
  .word          DMA0_CH3_IRQHandler
  .word          DMA0_CH4_IRQHandler
  .word          DMA0_CH5_IRQHandler
  .word          DMA0_CH6_IRQHandler
  .word          DMA0_CH7_IRQHandler
  .word          0                         // Reserved
  .word          0                         // Reserved
  .word          ADC1_IRQHandler
  .word          ADC2_IRQHandler
  .word          ENCENG_IRQHandler
  .word          MAC0_SBD_IRQHandler
  .word          MAC0_PMT_IRQHandler
  .word          MAC1_SBD_IRQHandler
  .word          MAC1_PMT_IRQHandler
  .word          DCMI_IRQHandler
  .word          CDMA_ADC_IRQHandler
  .word          FLEXCOMM0_IRQHandler
  .word          FLEXCOMM1_IRQHandler
  .word          FLEXCOMM2_IRQHandler
  .word          FLEXCOMM3_IRQHandler
  .word          FLEXCOMM4_IRQHandler
  .word          FLEXCOMM5_IRQHandler
  .word          FLEXCOMM6_IRQHandler
  .word          FLEXCOMM7_IRQHandler
  .word          FLEXCOMM8_IRQHandler
  .word          FLEXCOMM9_IRQHandler
  .word          FLEXCOMM10_IRQHandler
  .word          FLEXCOMM11_IRQHandler
  .word          FLEXCOMM12_IRQHandler
  .word          FLEXCOMM13_IRQHandler
  .word          DMA1_CH0_IRQHandler
  .word          DMA1_CH1_IRQHandler
  .word          DMA1_CH2_IRQHandler
  .word          DMA1_CH3_IRQHandler
  .word          DMA1_CH4_IRQHandler
  .word          DMA1_CH5_IRQHandler
  .word          DMA1_CH6_IRQHandler
  .word          DMA1_CH7_IRQHandler
  .word          IO_EXTI0_IRQHandler
  .word          IO_EXTI1_IRQHandler
  .word          IO_EXTI2_IRQHandler
  .word          IO_EXTI3_IRQHandler
  .word          IO_EXTI4_IRQHandler
  .word          IO_EXTI5_IRQHandler
  .word          IO_EXTI6_IRQHandler
  .word          IO_EXTI7_IRQHandler
  .word          IO_EXTI8_IRQHandler
  .word          IO_EXTI9_IRQHandler
  .word          IO_EXTI10_IRQHandler
  .word          IO_EXTI11_IRQHandler
  .word          IO_EXTI12_IRQHandler
  .word          IO_EXTI13_IRQHandler
  .word          IO_EXTI14_IRQHandler
  .word          IO_EXTI15_IRQHandler
  .word          I2C0_0_IRQHandler       //98
  .word          DMA0_IRQHandler         //99
  .word          UART0_0_IRQHandler      //100
  .word          UART0_1_IRQHandler      //101
  .word          UART0_2_IRQHandler      //102
  .word          UART0_3_IRQHandler      //103
  .word          UART0_4_IRQHandler      //104
  .word          UART0_5_IRQHandler      //105
  .word          ISO78160_0_IRQHandler   //106
  .word          ISO78160_1_IRQHandler   //107
  .word          TMR0_0_IRQHandler       //108
  .word          TMR0_1_IRQHandler       //109
  .word          TMR0_2_IRQHandler       //110
  .word          TMR0_3_IRQHandler       //111
  .word          PWM0_0_IRQHandler       //112
  .word          PWM0_1_IRQHandler       //113
  .word          PWM0_2_IRQHandler       //114
  .word          PWM0_3_IRQHandler       //115
  .word          FLASH0_IRQHandler       //116
  .word          SPI0_0_IRQHandler       //117
  .word          SPI0_1_IRQHandler       //118
  .word          SPI0_2_IRQHandler       //119
  .word          SPI0_3_IRQHandler       //120
  .word          SPI0_4_IRQHandler       //121
  .word          SPI0_5_IRQHandler       //122
  .word          HFM_COP_IRQHandler      //123
  .word          RTC_IRQHandler          //124
  .word          PMU_IRQHandler          //125
  .word          RTC_ALM_IRQHandler      //126
  .word          SYSCON_LP_ANA_IRQHandler//127
  .word          TIMER_LP_IRQHandler     //128
  .word          0                       //129
  .word          MPMU_CMP_IRQHandler     //130
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
  .weak      MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler
  .weak      BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler
  .weak      UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler
  .weak      SecureFault_Handler
  .thumb_set SecureFault_Handler,Default_Handler
  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler
  .weak      DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler
  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler
  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      	CM33_MAILBOX_IRQHandler
  .thumb_set 	 	CM33_MAILBOX_IRQHandler	,Default_Handler
  .weak      	CM0_MAILBOX_IRQHandler
  .thumb_set 	 	CM0_MAILBOX_IRQHandler	,Default_Handler
  .weak      	I2S0_IRQHandle
  .thumb_set 	 	I2S0_IRQHandle	,Default_Handler
  .weak      	I2S1_IRQHandler
  .thumb_set 	 	I2S1_IRQHandler	,Default_Handler
  .weak      	USB_HS_IRQHandler
  .thumb_set 	 	USB_HS_IRQHandler	,Default_Handler
  .weak      	USB_FS_IRQHandler
  .thumb_set 	 	USB_FS_IRQHandler	,Default_Handler
  .weak      	SSI_0_IRQHandler
  .thumb_set 	 	SSI_0_IRQHandler	,Default_Handler
  .weak      	SSI_1_IRQHandler
  .thumb_set 	 	SSI_1_IRQHandler	,Default_Handler
  .weak      	FLASHA_IRQHandler
  .thumb_set 	 	FLASHA_IRQHandler	,Default_Handler
  .weak      	FLASHB_IRQHandler
  .thumb_set 	 	FLASHB_IRQHandler	,Default_Handler
  .weak      	ISO781633_0_1_IRQHandler
  .thumb_set 	 	ISO781633_0_1_IRQHandler	,Default_Handler
  .weak      	MEM_ECC_IRQHandler
  .thumb_set 	 	MEM_ECC_IRQHandler	,Default_Handler
  .weak      	BTMR33_0_IRQHandler
  .thumb_set 	 	BTMR33_0_IRQHandler	,Default_Handler
  .weak      	BTMR33_1_IRQHandler
  .thumb_set 	 	BTMR33_1_IRQHandler	,Default_Handler
  .weak      	BTMR33_2_IRQHandler
  .thumb_set 	 	BTMR33_2_IRQHandler	,Default_Handler
  .weak      	BTMR33_3_IRQHandler
  .thumb_set 	 	BTMR33_3_IRQHandler	,Default_Handler
  .weak      	PWM33_0_IRQHandler
  .thumb_set 	 	PWM33_0_IRQHandler	,Default_Handler
  .weak      	PWM33_1_IRQHandler
  .thumb_set 	 	PWM33_1_IRQHandler	,Default_Handler
  .weak      	PWM33_2_IRQHandler
  .thumb_set 	 	PWM33_2_IRQHandler	,Default_Handler
  .weak      	PWM33_3_IRQHandler
  .thumb_set 	 	PWM33_3_IRQHandler	,Default_Handler
  .weak      	SDIO_0_IRQHandler
  .thumb_set 	 	SDIO_0_IRQHandler	,Default_Handler
  .weak      	SDIO_1_IRQHandler
  .thumb_set 	 	SDIO_1_IRQHandler	,Default_Handler
  .weak      	RNG_IRQHandler
  .thumb_set 	 	RNG_IRQHandler	,Default_Handler
  .weak      	EADC_IRQHandler
  .thumb_set 	 	EADC_IRQHandler	,Default_Handler
  .weak      	SCR_IRQHandler
  .thumb_set 	 	SCR_IRQHandler	,Default_Handler
  .weak      	CAN_0_IRQHandler
  .thumb_set 	 	CAN_0_IRQHandler	,Default_Handler
  .weak      	CAN_1_IRQHandler
  .thumb_set 	 	CAN_1_IRQHandler	,Default_Handler
  .weak      	TIM1_UP_IRQHandler
  .thumb_set 	 	TIM1_UP_IRQHandler	,Default_Handler
  .weak      	TIM1_BRK_IRQHandler
  .thumb_set 	 	TIM1_BRK_IRQHandler	,Default_Handler
  .weak      	TIM1_CC_IRQHandler
  .thumb_set 	 	TIM1_CC_IRQHandler	,Default_Handler
  .weak      	TIM1_TRG_COM_IRQHandler
  .thumb_set 	 	TIM1_TRG_COM_IRQHandler	,Default_Handler
  .weak      	TIM2_UP_IRQHandler
  .thumb_set 	 	TIM2_UP_IRQHandler	,Default_Handler
  .weak      	TIM2_BRK_IRQHandler
  .thumb_set 	 	TIM2_BRK_IRQHandler	,Default_Handler
  .weak      	TIM2_CC_IRQHandler
  .thumb_set 	 	TIM2_CC_IRQHandler	,Default_Handler
  .weak      	TIM2_TRG_COM_IRQHandler
  .thumb_set 	 	TIM2_TRG_COM_IRQHandler	,Default_Handler
  .weak      	TMR3_UP_BRK_CC_TRG_IRQHandler
  .thumb_set 	 	TMR3_UP_BRK_CC_TRG_IRQHandler	,Default_Handler
  .weak      	TMR4_UP_BRK_CC_TRG_IRQHandler
  .thumb_set 	 	TMR4_UP_BRK_CC_TRG_IRQHandler	,Default_Handler
  .weak      	TMR5_UP_BRK_CC_TRG_IRQHandler
  .thumb_set 	 	TMR5_UP_BRK_CC_TRG_IRQHandler	,Default_Handler
  .weak      	TMR6_UP_BRK_CC_TRG_IRQHandler
  .thumb_set 	 	TMR6_UP_BRK_CC_TRG_IRQHandler	,Default_Handler
  .weak      	DMA0_CH0_IRQHandler
  .thumb_set 	 	DMA0_CH0_IRQHandler	,Default_Handler
  .weak      	DMA0_CH1_IRQHandler
  .thumb_set 	 	DMA0_CH1_IRQHandler	,Default_Handler
  .weak      	DMA0_CH2_IRQHandler
  .thumb_set 	 	DMA0_CH2_IRQHandler	,Default_Handler
  .weak      	DMA0_CH3_IRQHandler
  .thumb_set 	 	DMA0_CH3_IRQHandler	,Default_Handler
  .weak      	DMA0_CH4_IRQHandler
  .thumb_set 	 	DMA0_CH4_IRQHandler	,Default_Handler
  .weak      	DMA0_CH5_IRQHandler
  .thumb_set 	 	DMA0_CH5_IRQHandler	,Default_Handler
  .weak      	DMA0_CH6_IRQHandler
  .thumb_set 	 	DMA0_CH6_IRQHandler	,Default_Handler
  .weak      	DMA0_CH7_IRQHandler
  .thumb_set 	 	DMA0_CH7_IRQHandler	,Default_Handler
  .weak      	ADC1_IRQHandler
  .thumb_set 	 	ADC1_IRQHandler	,Default_Handler
  .weak      	ADC2_IRQHandler
  .thumb_set 	 	ADC2_IRQHandler	,Default_Handler
  .weak      	ENCENG_IRQHandler
  .thumb_set 	 	ENCENG_IRQHandler	,Default_Handler
  .weak      	MAC0_SBD_IRQHandler
  .thumb_set 	 	MAC0_SBD_IRQHandler	,Default_Handler
  .weak      	MAC0_PMT_IRQHandler
  .thumb_set 	 	MAC0_PMT_IRQHandler	,Default_Handler
  .weak      	MAC1_SBD_IRQHandler
  .thumb_set 	 	MAC1_SBD_IRQHandler	,Default_Handler
  .weak      	MAC1_PMT_IRQHandler
  .thumb_set 	 	MAC1_PMT_IRQHandler	,Default_Handler
  .weak      	DCMI_IRQHandler
  .thumb_set 	 	DCMI_IRQHandler	,Default_Handler
  .weak      	CDMA_ADC_IRQHandler
  .thumb_set 	 	CDMA_ADC_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM0_IRQHandler
  .thumb_set 	 	FLEXCOMM0_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM1_IRQHandler
  .thumb_set 	 	FLEXCOMM1_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM2_IRQHandler
  .thumb_set 	 	FLEXCOMM2_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM3_IRQHandler
  .thumb_set 	 	FLEXCOMM3_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM4_IRQHandler
  .thumb_set 	 	FLEXCOMM4_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM5_IRQHandler
  .thumb_set 	 	FLEXCOMM5_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM6_IRQHandler
  .thumb_set 	 	FLEXCOMM6_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM7_IRQHandler
  .thumb_set 	 	FLEXCOMM7_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM8_IRQHandler
  .thumb_set 	 	FLEXCOMM8_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM9_IRQHandler
  .thumb_set 	 	FLEXCOMM9_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM10_IRQHandler
  .thumb_set 	 	FLEXCOMM10_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM11_IRQHandler
  .thumb_set 	 	FLEXCOMM11_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM12_IRQHandler
  .thumb_set 	 	FLEXCOMM12_IRQHandler	,Default_Handler
  .weak      	FLEXCOMM13_IRQHandler
  .thumb_set 	 	FLEXCOMM13_IRQHandler	,Default_Handler
  .weak      	DMA1_CH0_IRQHandler
  .thumb_set 	 	DMA1_CH0_IRQHandler	,Default_Handler
  .weak      	DMA1_CH1_IRQHandler
  .thumb_set 	 	DMA1_CH1_IRQHandler	,Default_Handler
  .weak      	DMA1_CH2_IRQHandler
  .thumb_set 	 	DMA1_CH2_IRQHandler	,Default_Handler
  .weak      	DMA1_CH3_IRQHandler
  .thumb_set 	 	DMA1_CH3_IRQHandler	,Default_Handler
  .weak      	DMA1_CH4_IRQHandler
  .thumb_set 	 	DMA1_CH4_IRQHandler	,Default_Handler
  .weak      	DMA1_CH5_IRQHandler
  .thumb_set 	 	DMA1_CH5_IRQHandler	,Default_Handler
  .weak      	DMA1_CH6_IRQHandler
  .thumb_set 	 	DMA1_CH6_IRQHandler	,Default_Handler
  .weak      	DMA1_CH7_IRQHandler
  .thumb_set 	 	DMA1_CH7_IRQHandler	,Default_Handler
  .weak      	IO_EXTI0_IRQHandler
  .thumb_set 	 	IO_EXTI0_IRQHandler	,Default_Handler
  .weak      	IO_EXTI1_IRQHandler
  .thumb_set 	 	IO_EXTI1_IRQHandler	,Default_Handler
  .weak      	IO_EXTI2_IRQHandler
  .thumb_set 	 	IO_EXTI2_IRQHandler	,Default_Handler
  .weak      	IO_EXTI3_IRQHandler
  .thumb_set 	 	IO_EXTI3_IRQHandler	,Default_Handler
  .weak      	IO_EXTI4_IRQHandler
  .thumb_set 	 	IO_EXTI4_IRQHandler	,Default_Handler
  .weak      	IO_EXTI5_IRQHandler
  .thumb_set 	 	IO_EXTI5_IRQHandler	,Default_Handler
  .weak      	IO_EXTI6_IRQHandler
  .thumb_set 	 	IO_EXTI6_IRQHandler	,Default_Handler
  .weak      	IO_EXTI7_IRQHandler
  .thumb_set 	 	IO_EXTI7_IRQHandler	,Default_Handler
  .weak      	IO_EXTI8_IRQHandler
  .thumb_set 	 	IO_EXTI8_IRQHandler	,Default_Handler
  .weak      	IO_EXTI9_IRQHandler
  .thumb_set 	 	IO_EXTI9_IRQHandler	,Default_Handler
  .weak      	IO_EXTI10_IRQHandler
  .thumb_set 	 	IO_EXTI10_IRQHandler	,Default_Handler
  .weak      	IO_EXTI11_IRQHandler
  .thumb_set 	 	IO_EXTI11_IRQHandler	,Default_Handler
  .weak      	IO_EXTI12_IRQHandler
  .thumb_set 	 	IO_EXTI12_IRQHandler	,Default_Handler
  .weak      	IO_EXTI13_IRQHandler
  .thumb_set 	 	IO_EXTI13_IRQHandler	,Default_Handler
  .weak      	IO_EXTI14_IRQHandler
  .thumb_set 	 	IO_EXTI14_IRQHandler	,Default_Handler
  .weak      	IO_EXTI15_IRQHandler
  .thumb_set 	 	IO_EXTI15_IRQHandler	,Default_Handler
  .weak      	I2C0_0_IRQHandler
  .thumb_set 	 	I2C0_0_IRQHandler	,Default_Handler
  .weak      	DMA0_IRQHandler
  .thumb_set 	 	DMA0_IRQHandler	,Default_Handler
  .weak      	UART0_0_IRQHandler
  .thumb_set 	 	UART0_0_IRQHandler	,Default_Handler
  .weak      	UART0_1_IRQHandler
  .thumb_set 	 	UART0_1_IRQHandler	,Default_Handler
  .weak      	UART0_2_IRQHandler
  .thumb_set 	 	UART0_2_IRQHandler	,Default_Handler
  .weak      	UART0_3_IRQHandler
  .thumb_set 	 	UART0_3_IRQHandler	,Default_Handler
  .weak      	UART0_4_IRQHandler
  .thumb_set 	 	UART0_4_IRQHandler	,Default_Handler
  .weak      	UART0_5_IRQHandler
  .thumb_set 	 	UART0_5_IRQHandler	,Default_Handler
  .weak      	ISO78160_0_IRQHandler
  .thumb_set 	 	ISO78160_0_IRQHandler	,Default_Handler
  .weak      	ISO78160_1_IRQHandler
  .thumb_set 	 	ISO78160_1_IRQHandler	,Default_Handler
  .weak      	TMR0_0_IRQHandler
  .thumb_set 	 	TMR0_0_IRQHandler	,Default_Handler
  .weak      	TMR0_1_IRQHandler
  .thumb_set 	 	TMR0_1_IRQHandler	,Default_Handler
  .weak      	TMR0_2_IRQHandler
  .thumb_set 	 	TMR0_2_IRQHandler	,Default_Handler
  .weak      	TMR0_3_IRQHandler
  .thumb_set 	 	TMR0_3_IRQHandler	,Default_Handler
  .weak      	PWM0_0_IRQHandler
  .thumb_set 	 	PWM0_0_IRQHandler	,Default_Handler
  .weak      	PWM0_1_IRQHandler
  .thumb_set 	 	PWM0_1_IRQHandler	,Default_Handler
  .weak      	PWM0_2_IRQHandler
  .thumb_set 	 	PWM0_2_IRQHandler	,Default_Handler
  .weak      	PWM0_3_IRQHandler
  .thumb_set 	 	PWM0_3_IRQHandler	,Default_Handler
  .weak      	FLASH0_IRQHandler
  .thumb_set 	 	FLASH0_IRQHandler	,Default_Handler
  .weak      	SPI0_0_IRQHandler
  .thumb_set 	 	SPI0_0_IRQHandler	,Default_Handler
  .weak      	SPI0_1_IRQHandler
  .thumb_set 	 	SPI0_1_IRQHandler	,Default_Handler
  .weak      	SPI0_2_IRQHandler
  .thumb_set 	 	SPI0_2_IRQHandler	,Default_Handler
  .weak      	SPI0_3_IRQHandler
  .thumb_set 	 	SPI0_3_IRQHandler	,Default_Handler
  .weak      	SPI0_4_IRQHandler
  .thumb_set 	 	SPI0_4_IRQHandler	,Default_Handler
  .weak      	SPI0_5_IRQHandler
  .thumb_set 	 	SPI0_5_IRQHandler	,Default_Handler
  .weak      	HFM_COP_IRQHandler
  .thumb_set 	 	HFM_COP_IRQHandler	,Default_Handler
  .weak      	RTC_IRQHandler
  .thumb_set 	 	RTC_IRQHandler	,Default_Handler
  .weak      	PMU_IRQHandler
  .thumb_set 	 	PMU_IRQHandler	,Default_Handler
  .weak      	RTC_ALM_IRQHandler
  .thumb_set 	 	RTC_ALM_IRQHandler	,Default_Handler
  .weak      	SYSCON_LP_ANA_IRQHandler
  .thumb_set 	 	SYSCON_LP_ANA_IRQHandler	,Default_Handler
  .weak      	TIMER_LP_IRQHandler
  .thumb_set 	 	TIMER_LP_IRQHandler	,Default_Handler
  .weak      	MPMU_CMP_IRQHandler
  .thumb_set 	 	MPMU_CMP_IRQHandler	,Default_Handler


