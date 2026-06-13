/*
 * Copyright (c) 2024, Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * V32F20X TF-M Peripherals Definition
 */

#ifndef __TFM_PERIPHERALS_DEF_H__
#define __TFM_PERIPHERALS_DEF_H__

/* V32F20X HAL includes for IRQ numbers */
#include "v32f20x.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Default IRQ priority for platform peripherals */
#define DEFAULT_IRQ_PRIORITY    (1UL << (__NVIC_PRIO_BITS - 2))

/* Platform peripherals used by TF-M partitions */
#define TFM_PERIPHERAL_UART1_IRQ    (FLEXCOMM1_IRQn)
#define TFM_PERIPHERAL_FLASH_IRQ    (FLASH0_IRQn)
#define TFM_PERIPHERAL_RNG_IRQ      (RNG_IRQn)

struct platform_data_t;

extern struct platform_data_t tfm_peripheral_uart1;
extern struct platform_data_t tfm_peripheral_flash;

#define TFM_PERIPHERAL_STD_UART  (&tfm_peripheral_uart1)
#define TFM_PERIPHERAL_FLASH0    (&tfm_peripheral_flash)

#ifdef __cplusplus
}
#endif

#endif /* __TFM_PERIPHERALS_DEF_H__ */
