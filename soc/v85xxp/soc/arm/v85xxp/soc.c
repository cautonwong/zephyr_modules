/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <soc.h>

static void v85xxp_clock_init(void)
{
	/*
	 * Follow the vendor clock driver's documented safe fallback path:
	 * power up the bandgap and internal 6.5536 MHz RC clock, then make
	 * that RC oscillator the AHB/PCLK source with divide-by-1.
	 */
	ANA->REG3 &= ~(ANA_REG3_BGPPD | ANA_REG3_RCHPD);
	MISC2->CLKSEL = MISC2_CLKSEL_CLKSEL_RCOH;
	MISC2->CLKDIVH = 0U;
	MISC2->CLKDIVP = 0U;
	MISC2->HCLKEN |= MISC2_HCLKEN_GPIO;
}

void z_arm_platform_init(void)
{
	v85xxp_clock_init();
}

static int v85xxp_init(void)
{
	return 0;
}

SYS_INIT(v85xxp_init, PRE_KERNEL_1, 0);
