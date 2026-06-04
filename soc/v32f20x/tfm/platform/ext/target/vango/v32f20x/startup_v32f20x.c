/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * V32F20x (Cortex-M33) startup for TF-M Secure Firmware
 * This replaces the nRF5340-specific startup_nrf5340.c
 */

#include "cmsis.h"

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector Table (Secure)
 *----------------------------------------------------------------------------*/
extern void Reset_Handler(void);
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SecureFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

/* Default exception handlers - weak so the application can override */
void Default_Handler(void);

void __attribute__((weak, alias("Default_Handler"))) NMI_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) HardFault_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) MemManage_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) BusFault_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) UsageFault_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) SecureFault_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) SVC_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) DebugMon_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) PendSV_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) SysTick_Handler(void);

extern uint32_t __StackTop;

/* V32F20x vector table */
__attribute__((section(".vectors")))
const void * const __Vectors[] = {
    (void *)&__StackTop,       /* Initial Stack Pointer */
    (void *)Reset_Handler,     /* Reset Handler */
    (void *)NMI_Handler,
    (void *)HardFault_Handler,
    (void *)MemManage_Handler,
    (void *)BusFault_Handler,
    (void *)UsageFault_Handler,
    (void *)SecureFault_Handler,
    0, 0, 0,                   /* Reserved */
    (void *)SVC_Handler,
    (void *)DebugMon_Handler,
    0,                         /* Reserved */
    (void *)PendSV_Handler,
    (void *)SysTick_Handler,
    /* External Interrupts */
};

extern uint32_t __data_load__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

void Reset_Handler(void)
{
    /* Copy initialized data from flash to SRAM */
    uint32_t *src = &__data_load__;
    uint32_t *dest = &__data_start__;
    while (dest < &__data_end__) {
        *dest++ = *src++;
    }

    /* Zero initialize BSS */
    dest = &__bss_start__;
    while (dest < &__bss_end__) {
        *dest++ = 0;
    }

    /* Call TF-M main */
    extern void tfm_core_init(void);
    tfm_core_init();

    /* Should never return */
    while (1) {}
}

void Default_Handler(void)
{
    while (1) {}
}
