/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/timer/system_timer.h>
#include <zephyr/sys_clock.h>
#include <zephyr/spinlock.h>
#include <soc.h>
#include "lib_tmr.h"
#include "lib_clk.h"

/* V85XXP TMR is a 32-bit down counter */
#define COUNTER_MAX 0xFFFFFFFFU

static struct k_spinlock lock;
static uint32_t last_load;
static uint32_t cycle_count;

static void tmr_isr(const void *arg)
{
	ARG_UNUSED(arg);
	k_spinlock_key_t key = k_spin_lock(&lock);

	TMR_ClearINTStatus(TMR0);
	cycle_count += last_load;

	k_spin_unlock(&lock, key);
	sys_clock_announce(1);
}

int sys_clock_driver_init(void)
{
	TMR_InitType init;
	uint32_t pclk = 6553600; // Default PCLK for V85XXP

	last_load = pclk / CONFIG_SYS_CLOCK_TICKS_PER_SEC;

	TMR_DeInit(TMR0);
	TMR_StructInit(&init);
	init.Period = last_load;
	init.ClockSource = TMR_CLKSRC_INTERNAL;
	TMR_Init(TMR0, &init);

	IRQ_CONNECT(TMR0_IRQn, 0, tmr_isr, NULL, 0);
	irq_enable(TMR0_IRQn);

	TMR_INTConfig(TMR0, ENABLE);
	TMR_Cmd(TMR0, ENABLE);

	return 0;
}

uint32_t sys_clock_elapsed(void)
{
	return 0;
}

uint32_t sys_clock_cycle_get_32(void)
{
	k_spinlock_key_t key = k_spin_lock(&lock);
	uint32_t val = cycle_count + (last_load - TMR_GetCurrentValue(TMR0));
	k_spin_unlock(&lock, key);
	return val;
}
