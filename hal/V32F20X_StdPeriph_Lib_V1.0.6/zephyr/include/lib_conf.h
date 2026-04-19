/**
  ******************************************************************************
  * @file    lib_conf.h 
  * @brief   Driver configuration for Zephyr.
  ******************************************************************************
  */

#ifndef __LIB_CONF_H
#define __LIB_CONF_H

#include <stdint.h>

/**
  * @brief Internal RCH value
  */
#if !defined  (RCH_VALUE)
#define RCH_VALUE                   (48000000UL)
#endif /* RCH_VALUE */

/**
  * @brief External XOH value
  */
#if !defined  (XOH_VALUE)
#define XOH_VALUE                   (12000000UL)
#endif /* XOH_VALUE */

/* Assertion handling */
#define assert_parameters(expr) ((void)0U)

/* Peripheral header inclusions */
#include "lib_bpwm.h"
#include "lib_btimer.h"
#include "lib_clk.h"
#include "lib_crypt.h"
#include "lib_bdma.h"
#include "lib_flash.h"
#include "lib_gpio.h"
#include "lib_gpio_ex.h"
#include "lib_hfm.h"
#include "lib_i2c.h"
#include "lib_iso7816.h"
#include "lib_mailbox.h"
#include "lib_pmu.h"
#include "lib_rtc.h"
#include "lib_rtc_comp.h"
#include "lib_rtc_ex.h"
#include "lib_bspi.h"
#include "lib_std.h"
#include "lib_syscfg.h"
#include "lib_u32k.h"
#include "lib_uart.h"
#include "lib_wdt.h"
#include "lib_ramfunc.h"
#include "misc.h"

#endif
