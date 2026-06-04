/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * CMSIS USART Driver stub for Vango V32F20x
 * TF-M uses this for secure UART output (logging)
 */

#include "Driver_USART.h"

#ifndef ARG_UNUSED
#define ARG_UNUSED(arg)  ((void)arg)
#endif

#define USART_DRIVER_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0)

static const ARM_DRIVER_VERSION UsartDriverVersion = {
    ARM_USART_API_VERSION,
    USART_DRIVER_VERSION
};

static const ARM_USART_CAPABILITIES UsartDriverCapabilities = {
    .asynchronous = 1,
};

static ARM_DRIVER_VERSION GetVersion(void)       { return UsartDriverVersion; }
static ARM_USART_CAPABILITIES GetCapabilities(void) { return UsartDriverCapabilities; }

static int32_t Initialize(ARM_USART_SignalEvent_t cb)
{
    ARG_UNUSED(cb);
    /* TODO: Initialize V32F20x UART0 for TF-M secure logging */
    return ARM_DRIVER_OK;
}

static int32_t Uninitialize(void)    { return ARM_DRIVER_OK; }
static int32_t PowerControl(ARM_POWER_STATE state) { ARG_UNUSED(state); return ARM_DRIVER_OK; }

static int32_t Send(const void *data, uint32_t num)
{
    const uint8_t *p = (const uint8_t *)data;
    /* TODO: Write to V32F20x UART0 TX FIFO */
    ARG_UNUSED(p);
    ARG_UNUSED(num);
    return ARM_DRIVER_OK;
}

static int32_t Receive(void *data, uint32_t num)     { ARG_UNUSED(data); ARG_UNUSED(num); return ARM_DRIVER_OK; }
static int32_t Transfer(const void *out, void *in, uint32_t num) { ARG_UNUSED(out); ARG_UNUSED(in); ARG_UNUSED(num); return ARM_DRIVER_OK; }
static uint32_t GetTxCount(void)     { return 0; }
static uint32_t GetRxCount(void)     { return 0; }
static int32_t Control(uint32_t control, uint32_t arg) { ARG_UNUSED(control); ARG_UNUSED(arg); return ARM_DRIVER_OK; }
static ARM_USART_STATUS GetStatus(void) { ARM_USART_STATUS s = {0}; return s; }
static int32_t SetModemControl(ARM_USART_MODEM_CONTROL control) { ARG_UNUSED(control); return ARM_DRIVER_OK; }
static ARM_USART_MODEM_STATUS GetModemStatus(void) { ARM_USART_MODEM_STATUS s = {0}; return s; }

ARM_DRIVER_USART Driver_USART0 = {
    .GetVersion       = GetVersion,
    .GetCapabilities  = GetCapabilities,
    .Initialize       = Initialize,
    .Uninitialize     = Uninitialize,
    .PowerControl     = PowerControl,
    .Send             = Send,
    .Receive          = Receive,
    .Transfer         = Transfer,
    .GetTxCount       = GetTxCount,
    .GetRxCount       = GetRxCount,
    .Control          = Control,
    .GetStatus        = GetStatus,
    .SetModemControl  = SetModemControl,
    .GetModemStatus   = GetModemStatus,
};
