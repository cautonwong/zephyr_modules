/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 *
 * V85XXP Power Management Unit (PMU) Driver API
 */

#ifndef ZEPHYR_DRIVERS_MISC_V85XXP_PMU_H_
#define ZEPHYR_DRIVERS_MISC_V85XXP_PMU_H_

#include <zephyr/device.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Low-power configuration passed to enter_sleep_low_power / enter_deep_sleep_low_power. */
struct v85xxp_pmu_low_power_cfg {
	uint32_t cmp1_power;
	uint32_t cmp2_power;
	uint32_t tadc_power;
	uint32_t bgp_power;
	uint32_t avcc_power;
	uint32_t lcd_power;
	uint32_t vdcin_detector;
	uint32_t vdd_detector;
	uint32_t ahb_periph_disable;
	uint32_t apb_periph_disable;
};

/** Wakeup event polarity for IOA pins. */
#define V85XXP_WAKEUP_IOA_DISABLE   IOA_DISABLE
#define V85XXP_WAKEUP_IOA_RISING    IOA_RISING
#define V85XXP_WAKEUP_IOA_FALLING   IOA_FALLING
#define V85XXP_WAKEUP_IOA_HIGH      IOA_HIGH
#define V85XXP_WAKEUP_IOA_LOW       IOA_LOW
#define V85XXP_WAKEUP_IOA_EDGE_BOTH IOA_EDGEBOTH

/** RTC wakeup event flags. */
#define V85XXP_WAKEUP_RTC_ALARM    RTC_INTSTS_INTSTS10
#define V85XXP_WAKEUP_RTC_WKUCNT   RTC_INTSTS_INTSTS6
#define V85XXP_WAKEUP_RTC_MIDNIGHT RTC_INTSTS_INTSTS5
#define V85XXP_WAKEUP_RTC_WKUHOUR  RTC_INTSTS_INTSTS4
#define V85XXP_WAKEUP_RTC_WKUMIN   RTC_INTSTS_INTSTS3
#define V85XXP_WAKEUP_RTC_WKUSEC   RTC_INTSTS_INTSTS2
#define V85XXP_WAKEUP_RTC_ITVSITV  RTC_INTSTS_INTSTS0

/** Reset source flags. */
#define V85XXP_RSTSRC_EXTRST  PMU_RSTSRC_EXTRST
#define V85XXP_RSTSRC_PORST   PMU_RSTSRC_PORST
#define V85XXP_RSTSRC_DPORST  PMU_RSTSRC_DPORST
#define V85XXP_RSTSRC_WDTRST  PMU_RSTSRC_WDTRST
#define V85XXP_RSTSRC_SFTRST  PMU_RSTSRC_SFTRST
#define V85XXP_RSTSRC_MODERST PMU_RSTSRC_MODERST

/** PMU interrupt flags. */
#define V85XXP_PMU_INT_IOA  PMU_INT_IOAEN
#define V85XXP_PMU_INT_32K  PMU_INT_32K
#define V85XXP_PMU_INT_6M   PMU_INT_6M

/** PMU interrupt status. */
#define V85XXP_PMU_STS_32K  PMU_STS_32K
#define V85XXP_PMU_STS_6M   PMU_STS_6M

/** Deep-sleep wakeup source flags. */
#define V85XXP_DSLEEP_WKU_MODE PMU_DSLEEPWKUSRC_MODE
#define V85XXP_DSLEEP_WKU_XTAL PMU_DSLEEPWKUSRC_XTAL
#define V85XXP_DSLEEP_WKU_U32K PMU_DSLEEPWKUSRC_U32K
#define V85XXP_DSLEEP_WKU_ANA  PMU_DSLEEPWKUSRC_ANA
#define V85XXP_DSLEEP_WKU_RTC  PMU_DSLEEPWKUSRC_RTC
#define V85XXP_DSLEEP_WKU_IOA  PMU_DSLEEPWKUSRC_IOA

struct v85xxp_pmu_driver_api {
	int (*enter_sleep)(const struct device *dev);
	int (*enter_deep_sleep)(const struct device *dev);
	int (*enter_idle)(const struct device *dev);
	int (*enter_sleep_low_power)(const struct device *dev,
				     const struct v85xxp_pmu_low_power_cfg *cfg);
	void (*wakeup_pin_config)(const struct device *dev, uint16_t io_mask, uint32_t event);
	void (*sleep_wkup_ioa)(const struct device *dev, uint16_t io_mask, uint32_t event, uint32_t priority);
	void (*sleep_wkup_rtc)(const struct device *dev, uint32_t events, uint32_t priority);
	void (*deep_sleep_wkup_ioa)(const struct device *dev, uint16_t io_mask, uint32_t event);
	void (*deep_sleep_wkup_rtc)(const struct device *dev, uint32_t events);
	void (*int_config)(const struct device *dev, uint32_t mask, bool enable);
	uint8_t (*get_int_status)(const struct device *dev, uint32_t mask);
	void (*clear_int_status)(const struct device *dev, uint32_t mask);
	uint32_t (*get_reset_source)(const struct device *dev);
	void (*clear_reset_source)(const struct device *dev, uint32_t mask);
	void (*bgp_cmd)(const struct device *dev, bool enable);
	void (*vdd_alarm_threshold)(const struct device *dev, uint32_t threshold);
	void (*vdd_detector_cmd)(const struct device *dev, uint32_t state);
	uint8_t (*get_mode_status)(const struct device *dev);
};

/* Inline wrappers — see v85xxp_lcd.h for the pattern. */

static inline int v85xxp_pmu_enter_sleep(const struct device *dev)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	return api->enter_sleep(dev);
}

static inline int v85xxp_pmu_enter_deep_sleep(const struct device *dev)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	return api->enter_deep_sleep(dev);
}

static inline int v85xxp_pmu_enter_idle(const struct device *dev)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	return api->enter_idle(dev);
}

static inline int v85xxp_pmu_enter_sleep_low_power(const struct device *dev,
						    const struct v85xxp_pmu_low_power_cfg *cfg)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	return api->enter_sleep_low_power(dev, cfg);
}

static inline void v85xxp_pmu_wakeup_pin_config(const struct device *dev,
						 uint16_t io_mask, uint32_t event)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->wakeup_pin_config(dev, io_mask, event);
}

static inline void v85xxp_pmu_sleep_wkup_ioa(const struct device *dev,
					      uint16_t io_mask, uint32_t event, uint32_t prio)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->sleep_wkup_ioa(dev, io_mask, event, prio);
}

static inline void v85xxp_pmu_sleep_wkup_rtc(const struct device *dev,
					      uint32_t events, uint32_t prio)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->sleep_wkup_rtc(dev, events, prio);
}

static inline void v85xxp_pmu_deep_sleep_wkup_ioa(const struct device *dev,
						   uint16_t io_mask, uint32_t event)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->deep_sleep_wkup_ioa(dev, io_mask, event);
}

static inline void v85xxp_pmu_deep_sleep_wkup_rtc(const struct device *dev,
						   uint32_t events)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->deep_sleep_wkup_rtc(dev, events);
}

static inline void v85xxp_pmu_int_config(const struct device *dev,
					  uint32_t mask, bool enable)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->int_config(dev, mask, enable);
}

static inline uint8_t v85xxp_pmu_get_int_status(const struct device *dev, uint32_t mask)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	return api->get_int_status(dev, mask);
}

static inline void v85xxp_pmu_clear_int_status(const struct device *dev, uint32_t mask)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->clear_int_status(dev, mask);
}

static inline uint32_t v85xxp_pmu_get_reset_source(const struct device *dev)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	return api->get_reset_source(dev);
}

static inline void v85xxp_pmu_clear_reset_source(const struct device *dev, uint32_t mask)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->clear_reset_source(dev, mask);
}

static inline void v85xxp_pmu_bgp_cmd(const struct device *dev, bool enable)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->bgp_cmd(dev, enable);
}

static inline void v85xxp_pmu_vdd_alarm_threshold(const struct device *dev, uint32_t threshold)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->vdd_alarm_threshold(dev, threshold);
}

static inline void v85xxp_pmu_vdd_detector_cmd(const struct device *dev, uint32_t state)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	api->vdd_detector_cmd(dev, state);
}

static inline uint8_t v85xxp_pmu_get_mode_status(const struct device *dev)
{
	const struct v85xxp_pmu_driver_api *api =
		(const struct v85xxp_pmu_driver_api *)dev->api;
	return api->get_mode_status(dev);
}

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_DRIVERS_MISC_V85XXP_PMU_H_ */
