/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Target Configuration for Vango V32F20x - TF-M Platform Init
 */

#include "cmsis.h"
#include "target_cfg.h"
#include "tfm_plat_defs.h"

enum tfm_plat_err_t enable_fault_handlers(void)
{
    /*
     * Enable UsageFault, BusFault, MemManageFault, SecureFault
     * on Cortex-M33 SCB->SHCSR
     */
    SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
                | SCB_SHCSR_BUSFAULTENA_Msk
                | SCB_SHCSR_MEMFAULTENA_Msk
                | SCB_SHCSR_SECUREFAULTENA_Msk;

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t system_reset_cfg(void)
{
    /* Enable SYSRESETREQ for both secure and non-secure resets */
    SCB->AIRCR = (SCB->AIRCR & ~SCB_AIRCR_VECTKEY_Msk)
                 | (0x05FAUL << SCB_AIRCR_VECTKEY_Pos)
                 | SCB_AIRCR_SYSRESETREQ_Msk;
    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t nvic_interrupt_target_state_cfg(void)
{
    /*
     * Route V32F20x IRQs: by default all go to Secure.
     * Non-secure interrupts (e.g. application UART) to be marked NS
     * as needed during hardware bring-up.
     */
    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t nvic_interrupt_enable(void)
{
    /* Enable any Secure-domain interrupts needed by TF-M partitions */
    return TFM_PLAT_ERR_SUCCESS;
}
