/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_V85XXP_CLOCK_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_V85XXP_CLOCK_H_

/* AHB Peripheral Clocks (Bit 0-31) */
#define V85XXP_AHB_DMA      (1 << 0)
#define V85XXP_AHB_GPIO     (1 << 1)
#define V85XXP_AHB_LCD      (1 << 2)
#define V85XXP_AHB_CRYPT    (1 << 3)

/* APB Peripheral Clocks (Bit 31 set to distinguish from AHB) */
#define V85XXP_APB_FLAG     (1 << 31)
#define V85XXP_APB_DMA      (V85XXP_APB_FLAG | (1 << 0))
#define V85XXP_APB_I2C      (V85XXP_APB_FLAG | (1 << 1))
#define V85XXP_APB_SPI1     (V85XXP_APB_FLAG | (1 << 2))
#define V85XXP_APB_UART0    (V85XXP_APB_FLAG | (1 << 3))
#define V85XXP_APB_UART1    (V85XXP_APB_FLAG | (1 << 4))
#define V85XXP_APB_UART2    (V85XXP_APB_FLAG | (1 << 5))
#define V85XXP_APB_UART3    (V85XXP_APB_FLAG | (1 << 6))
#define V85XXP_APB_UART4    (V85XXP_APB_FLAG | (1 << 7))
#define V85XXP_APB_UART5    (V85XXP_APB_FLAG | (1 << 8))
#define V85XXP_APB_ISO0     (V85XXP_APB_FLAG | (1 << 9))
#define V85XXP_APB_ISO1     (V85XXP_APB_FLAG | (1 << 10))
#define V85XXP_APB_TMR      (V85XXP_APB_FLAG | (1 << 11))
#define V85XXP_APB_MISC1    (V85XXP_APB_FLAG | (1 << 12))
#define V85XXP_APB_MISC2    (V85XXP_APB_FLAG | (1 << 13))
#define V85XXP_APB_PMU      (V85XXP_APB_FLAG | (1 << 14))
#define V85XXP_APB_RTC      (V85XXP_APB_FLAG | (1 << 15))
#define V85XXP_APB_ANA      (V85XXP_APB_FLAG | (1 << 16))
#define V85XXP_APB_U32K0    (V85XXP_APB_FLAG | (1 << 17))
#define V85XXP_APB_U32K1    (V85XXP_APB_FLAG | (1 << 18))
#define V85XXP_APB_SPI2     (V85XXP_APB_FLAG | (1 << 19))
#define V85XXP_APB_SPI3     (V85XXP_APB_FLAG | (1 << 20))

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_V85XXP_CLOCK_H_ */
