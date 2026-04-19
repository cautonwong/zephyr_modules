/******************************************************************************
 * @file     system_rn831x_rn861x_mcu.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File
 *           for the rn831x_rn861x_mcu CM0 Device
 * @note
 * Copyright (C) Renergy Micro-Electronics Co.,LTD.
 *
 ******************************************************************************/

#include <stdint.h>
#include "rn831x_rn861x_mcu.h"
#include "system_rn831x_rn861x_mcu.h"

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define HSI             (1843200UL)
#define XTAL            (1843200UL)    /* Oscillator frequency             */
#define SYS_OSC_CLK     (      HSI)    /* Main oscillator frequency        */

#define SYSTEM_CLOCK    (1UL* XTAL)

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit()    */
uint32_t SystemCoreClock = SYSTEM_CLOCK;  /*!< System Clock Frequency (Core Clock)*/


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
/* ToDo: add code to calculate the system frequency based upon the current
         register settings.
         This function can be used to retrieve the system core clock frequeny
         after user changed register sittings.                                */
  SystemCoreClock = SYSTEM_CLOCK;
  switch ((SYSCTL->OSC_CTRL1 >> 8) & 0x7U)
  {
    case 0:
      SystemCoreClock = 7372800U;
      break;
    case 1:
      SystemCoreClock = 3686400U;
      break;
    case 2:
      SystemCoreClock = 1843200U;
		  break;
    case 3:
      SystemCoreClock = 32768U;
      break;
    case 4:
      SystemCoreClock = 14745600U;
      break;
    case 5:
      SystemCoreClock = 29491200U;
      break;
		default:
			SystemCoreClock = 1843200U;
      break;
  }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
/* ToDo: add code to initialize the system
         do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards.          */
  /* SystemCoreClock = SYSTEM_CLOCK;*/

  return;
}
/* r1125 */
