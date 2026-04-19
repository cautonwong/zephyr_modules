/**
  ******************************************************************************
  * @file    lib_conf.h 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Dirver configuration.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_CONF_H
#define __LIB_CONF_H

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

/**
  * @brief This is the HAL system configuration section
  */
#define TICK_INT_PRIORITY  ((1UL<<__NVIC_PRIO_BITS) - 1UL)  /*!< tick interrupt priority (lowest by default) */

//*** <<< Use Configuration Wizard in Context Menu >>> ***

// <c1> Enable parametres assert
// <i> Enable parametres assert
#define ASSERT_ENABLED
// </c>

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file 
  */
#include "lib_adc.h"
#include "lib_bpwm.h"
#include "lib_btimer.h"
#include "lib_can.h"
#include "lib_clk.h"
#include "lib_comp.h"
#include "lib_crc.h"
#include "lib_dac.h"
#include "lib_dcmi.h"
#include "lib_dma.h"
#include "lib_eadc.h"
#include "lib_enceng.h"
#include "lib_flash.h"
#include "lib_gpio.h"
#include "lib_gpio_ex.h"
#include "lib_i2c.h"
#include "lib_i2s.h"
#include "lib_iso7816.h"
#include "lib_mailbox.h"
#include "lib_pmu.h"
#include "lib_rng.h"
#include "lib_rtc.h"
#include "lib_rtc_comp.h"
#include "lib_rtc_ex.h"
#include "lib_sdio.h"
#include "lib_spi.h"
#include "lib_ospi.h"
#include "lib_std.h"
#include "lib_syscfg.h"
#include "lib_timer.h"
#include "lib_u32k.h"
#include "lib_uart.h"
#include "lib_wdt.h"
#include "lib_ramfunc.h"
#include "lib_bdma.h"
#include "lib_bspi.h"
#include "lib_crypt.h"
#include "lib_hfm.h"
#include "misc.h"
#ifdef  ASSERT_ENABLED
  #define assert_parameters(expr) ((expr) ? (void)0U : assert_errhandler((uint8_t *)__FILE__, __LINE__))
  void assert_errhandler(uint8_t* file, uint32_t line);
#else
  #define assert_parameters(expr) ((void)0U)
#endif /* ASSERT_NDEBUG */ 

#endif

/*********************************** END OF FILE ******************************/
