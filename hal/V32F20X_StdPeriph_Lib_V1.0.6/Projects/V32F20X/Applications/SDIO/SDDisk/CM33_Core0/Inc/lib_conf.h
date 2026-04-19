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

//
// <h> Include module's header file 
//
// <c1> Miscellaneous (MISC)
// <i> Use misc library
#include "misc.h"
#include "lib_uart.h"

#include "lib_gpio.h"
#include "lib_clk.h"
#include "lib_syscfg.h"
#include "misc.h"
#include "lib_std.h"
// </c>

#define BIT0        0x00000001
#define BIT1        0x00000002
#define BIT2        0x00000004
#define BIT3        0x00000008
#define BIT4        0x00000010
#define BIT5        0x00000020
#define BIT6        0x00000040
#define BIT7        0x00000080
#define BIT8        0x00000100
#define BIT9        0x00000200
#define BIT10       0x00000400
#define BIT11       0x00000800
#define BIT12       0x00001000
#define BIT13       0x00002000
#define BIT14       0x00004000
#define BIT15       0x00008000
#define BIT16       0x00010000
#define BIT17       0x00020000
#define BIT18       0x00040000
#define BIT19       0x00080000
#define BIT20       0x00100000
#define BIT21       0x00200000
#define BIT22       0x00400000
#define BIT23       0x00800000
#define BIT24       0x01000000
#define BIT25       0x02000000
#define BIT26       0x04000000
#define BIT27       0x08000000
#define BIT28       0x10000000
#define BIT29       0x20000000
#define BIT30       0x40000000
#define BIT31       0x80000000

#ifdef  ASSERT_ENABLED
  #define assert_parameters(expr) ((expr) ? (void)0U : assert_errhandler((uint8_t *)__FILE__, __LINE__))
  void assert_errhandler(uint8_t* file, uint32_t line);
#else
  #define assert_parameters(expr) ((void)0U)
#endif /* ASSERT_NDEBUG */ 

#endif

/*********************************** END OF FILE ******************************/
