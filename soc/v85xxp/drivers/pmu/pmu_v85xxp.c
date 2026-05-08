/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 *
 * V85XXP Power Management Unit (PMU) Driver
 */

#define DT_DRV_COMPAT v85xxp_pmu

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/pm/device.h>
#include <soc.h>
#include <lib_pmu.h>

#include <zephyr/drivers/misc/v85xxp_pmu.h>

struct v85xxp_pmu_config {
	uintptr_t base;
};

static int v85xxp_pmu_init(const struct device *dev)
{
	ARG_UNUSED(dev);
	return 0;
}

/* --- Power mode entry --- */

static int pmu_v85xxp_enter_sleep(const struct device *dev)
{
	ARG_UNUSED(dev);
	PMU_EnterSleepMode();
	return 0;
}

static int pmu_v85xxp_enter_deep_sleep(const struct device *dev)
{
	ARG_UNUSED(dev);
	PMU_EnterDSleepMode();
	return 0;
}

static int pmu_v85xxp_enter_idle(const struct device *dev)
{
	ARG_UNUSED(dev);
	PMU_EnterIdleMode();
	return 0;
}

static int pmu_v85xxp_enter_sleep_low_power(const struct device *dev,
					    const struct v85xxp_pmu_low_power_cfg *cfg)
{
	PMU_LowPWRTypeDef hal_cfg = {
		.CMP1Power            = cfg->cmp1_power,
		.CMP2Power            = cfg->cmp2_power,
		.TADCPower            = cfg->tadc_power,
		.BGPPower             = cfg->bgp_power,
		.AVCCPower            = cfg->avcc_power,
		.LCDPower             = cfg->lcd_power,
		.VDCINDetector        = cfg->vdcin_detector,
		.VDDDetector          = cfg->vdd_detector,
		.AHBPeriphralDisable  = cfg->ahb_periph_disable,
		.APBPeriphralDisable  = cfg->apb_periph_disable,
	};

	ARG_UNUSED(dev);
	return (int)PMU_EnterDSleep_LowPower(&hal_cfg);
}

/* --- Wakeup configuration --- */

static void pmu_v85xxp_wakeup_pin_config(const struct device *dev,
					  uint16_t io_mask, uint32_t event)
{
	ARG_UNUSED(dev);
	PMU_WakeUpPinConfig(io_mask, event);
}

static void pmu_v85xxp_sleep_wkup_ioa(const struct device *dev,
				       uint16_t io_mask, uint32_t event, uint32_t priority)
{
	ARG_UNUSED(dev);
	PMU_SleepWKUSRCConfig_IOA(io_mask, event, priority);
}

static void pmu_v85xxp_sleep_wkup_rtc(const struct device *dev,
				       uint32_t events, uint32_t priority)
{
	ARG_UNUSED(dev);
	PMU_SleepWKUSRCConfig_RTC(events, priority);
}

static void pmu_v85xxp_deep_sleep_wkup_ioa(const struct device *dev,
					    uint16_t io_mask, uint32_t event)
{
	ARG_UNUSED(dev);
	PMU_DeepSleepWKUSRCConfig_IOA(io_mask, event);
}

static void pmu_v85xxp_deep_sleep_wkup_rtc(const struct device *dev,
					    uint32_t events)
{
	ARG_UNUSED(dev);
	PMU_DeepSleepWKUSRCConfig_RTC(events);
}

/* --- Interrupts --- */

static void pmu_v85xxp_int_config(const struct device *dev, uint32_t mask, bool enable)
{
	ARG_UNUSED(dev);
	PMU_INTConfig(mask, enable ? ENABLE : DISABLE);
}

static uint8_t pmu_v85xxp_get_int_status(const struct device *dev, uint32_t mask)
{
	ARG_UNUSED(dev);
	return PMU_GetINTStatus(mask);
}

static void pmu_v85xxp_clear_int_status(const struct device *dev, uint32_t mask)
{
	ARG_UNUSED(dev);
	PMU_ClearINTStatus(mask);
}

/* --- Reset source --- */

static uint32_t pmu_v85xxp_get_reset_source(const struct device *dev)
{
	ARG_UNUSED(dev);
	return PMU_GetAllResetSource();
}

static void pmu_v85xxp_clear_reset_source(const struct device *dev, uint32_t mask)
{
	ARG_UNUSED(dev);
	PMU_ClearResetSource(mask);
}

/* --- Detectors --- */

static void pmu_v85xxp_bgp_cmd(const struct device *dev, bool enable)
{
	ARG_UNUSED(dev);
	PMU_BGPCmd(enable ? ENABLE : DISABLE);
}

static void pmu_v85xxp_vdd_alarm_threshold(const struct device *dev, uint32_t threshold)
{
	ARG_UNUSED(dev);
	PMU_VDDAlarmTHConfig(threshold);
}

static void pmu_v85xxp_vdd_detector_cmd(const struct device *dev, uint32_t state)
{
	ARG_UNUSED(dev);
	PMU_VDDDetectorCmd(state);
}

/* --- Status --- */

static uint8_t pmu_v85xxp_get_mode_status(const struct device *dev)
{
	ARG_UNUSED(dev);
	return PMU_GetModeStatus();
}

#ifdef CONFIG_PM_DEVICE
static int pmu_v85xxp_pm_action(const struct device *dev,
				enum pm_device_action action)
{
	ARG_UNUSED(dev);
	switch (action) {
	case PM_DEVICE_ACTION_SUSPEND:
	case PM_DEVICE_ACTION_RESUME:
		return 0;
	default:
		return -ENOTSUP;
	}
}
#endif

static const struct v85xxp_pmu_driver_api v85xxp_pmu_api = {
	.enter_sleep              = pmu_v85xxp_enter_sleep,
	.enter_deep_sleep         = pmu_v85xxp_enter_deep_sleep,
	.enter_idle               = pmu_v85xxp_enter_idle,
	.enter_sleep_low_power    = pmu_v85xxp_enter_sleep_low_power,
	.wakeup_pin_config        = pmu_v85xxp_wakeup_pin_config,
	.sleep_wkup_ioa           = pmu_v85xxp_sleep_wkup_ioa,
	.sleep_wkup_rtc           = pmu_v85xxp_sleep_wkup_rtc,
	.deep_sleep_wkup_ioa      = pmu_v85xxp_deep_sleep_wkup_ioa,
	.deep_sleep_wkup_rtc      = pmu_v85xxp_deep_sleep_wkup_rtc,
	.int_config               = pmu_v85xxp_int_config,
	.get_int_status           = pmu_v85xxp_get_int_status,
	.clear_int_status         = pmu_v85xxp_clear_int_status,
	.get_reset_source         = pmu_v85xxp_get_reset_source,
	.clear_reset_source       = pmu_v85xxp_clear_reset_source,
	.bgp_cmd                  = pmu_v85xxp_bgp_cmd,
	.vdd_alarm_threshold      = pmu_v85xxp_vdd_alarm_threshold,
	.vdd_detector_cmd         = pmu_v85xxp_vdd_detector_cmd,
	.get_mode_status          = pmu_v85xxp_get_mode_status,
};

#define V85XXP_PMU_INIT(inst) \
	static const struct v85xxp_pmu_config v85xxp_pmu_cfg_##inst = { \
		.base = DT_INST_REG_ADDR(inst), \
	}; \
	PM_DEVICE_DT_INST_DEFINE(inst, pmu_v85xxp_pm_action); \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_pmu_init, \
			      PM_DEVICE_DT_INST_GET(inst), \
			      NULL, &v85xxp_pmu_cfg_##inst, \
			      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, \
			      &v85xxp_pmu_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_PMU_INIT)
