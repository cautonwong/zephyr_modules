/******************************************************************************
 * @file     rn831x_rn861x_mcu.h
 * @brief    CMSIS Cortex-M0 Device System Header File
 *           for rn821x_rn721x_soc Device
 * @note
 * Copyright (C) Renergy Micro-Electronics Co.,LTD.
 *
 ******************************************************************************/

#ifndef SYSTEM_RN831X_RN861X_SOC_H
#define SYSTEM_RN831X_RN861X_SOC_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_RN831X_RN861X_SOC_H */
/* r1125 */
