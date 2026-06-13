/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Vector table and startup for TF-M BL2 and Secure Firmware.
 */

#include "cmsis.h"

extern const uint32_t Image$$ARM_LIB_STACK$$ZI$$Limit[];

/* Reset Handler and standard exception handlers */
void Reset_Handler(void) __attribute__((noreturn));
void Default_Handler(void) __attribute__((noreturn));

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

__attribute__((section(".vectors")))
const void * const __Vectors[] = {
    (void *)&Image$$ARM_LIB_STACK$$ZI$$Limit,  /* Initial Stack Pointer */
    (void *)Reset_Handler,                     /* Reset Handler */
    (void *)NMI_Handler,
    (void *)HardFault_Handler,
    (void *)MemManage_Handler,
    (void *)BusFault_Handler,
    (void *)UsageFault_Handler,
    (void *)SecureFault_Handler,
    0, 0, 0,                                   /* Reserved */
    (void *)SVC_Handler,
    (void *)DebugMon_Handler,
    0,                                         /* Reserved */
    (void *)PendSV_Handler,
    (void *)SysTick_Handler,
};

#ifdef BL2
extern void __PROGRAM_START(void) __attribute__((noreturn));

void Reset_Handler(void)
{
    __PROGRAM_START();
}
#else
extern void tfm_core_init(void);

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

    tfm_core_init();

    while (1) {}
}
#endif

void Default_Handler(void)
{
    while (1) {}
}
