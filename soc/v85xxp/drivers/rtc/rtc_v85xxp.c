/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_rtc

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#include <zephyr/device.h>
#include <zephyr/drivers/rtc.h>

#include <soc.h>
#include "lib_rtc.h"

struct v85xxp_rtc_config {
	RTC_Type *base;
};

struct v85xxp_rtc_data {
	bool time_valid;
#ifdef CONFIG_RTC_ALARM
	uint16_t alarm_mask;
	struct rtc_time alarm_time;
#endif
};

static uint8_t v85xxp_bin2bcd(int v)
{
	return (uint8_t)(((v / 10) << 4) | (v % 10));
}

static int v85xxp_bcd2bin(uint32_t v)
{
	return (int)(((v >> 4) * 10) + (v & 0xFU));
}

static bool v85xxp_rtc_time_is_valid(const struct rtc_time *t)
{
	if ((t->tm_sec < 0) || (t->tm_sec > 59) ||
	    (t->tm_min < 0) || (t->tm_min > 59) ||
	    (t->tm_hour < 0) || (t->tm_hour > 23) ||
	    (t->tm_mday < 1) || (t->tm_mday > 31) ||
	    (t->tm_mon < 0) || (t->tm_mon > 11) ||
	    (t->tm_wday < 0) || (t->tm_wday > 6) ||
	    (t->tm_year < 100) || (t->tm_year > 199)) {
		return false;
	}

	return true;
}

static int v85xxp_rtc_set_time(const struct device *dev, const struct rtc_time *timeptr)
{
	struct v85xxp_rtc_data *data = dev->data;
	RTC_TimeTypeDef time = {0};

	if ((timeptr == NULL) || !v85xxp_rtc_time_is_valid(timeptr)) {
		return -EINVAL;
	}

	time.Year = v85xxp_bin2bcd(timeptr->tm_year - 100);
	time.Month = v85xxp_bin2bcd(timeptr->tm_mon + 1);
	time.Date = v85xxp_bin2bcd(timeptr->tm_mday);
	time.WeekDay = (uint32_t)timeptr->tm_wday;
	time.Hours = v85xxp_bin2bcd(timeptr->tm_hour);
	time.Minutes = v85xxp_bin2bcd(timeptr->tm_min);
	time.Seconds = v85xxp_bin2bcd(timeptr->tm_sec);
	time.SubSeconds = 0;

	RTC_SetTime(&time, RTC_INACCURATE);
	data->time_valid = true;

	return 0;
}

static int v85xxp_rtc_get_time(const struct device *dev, struct rtc_time *timeptr)
{
	struct v85xxp_rtc_data *data = dev->data;
	RTC_TimeTypeDef time = {0};

	if (timeptr == NULL) {
		return -EINVAL;
	}

	if (!data->time_valid) {
		return -ENODATA;
	}

	RTC_GetTime(&time, RTC_INACCURATE);
	timeptr->tm_sec = v85xxp_bcd2bin(time.Seconds);
	timeptr->tm_min = v85xxp_bcd2bin(time.Minutes);
	timeptr->tm_hour = v85xxp_bcd2bin(time.Hours);
	timeptr->tm_mday = v85xxp_bcd2bin(time.Date);
	timeptr->tm_mon = v85xxp_bcd2bin(time.Month) - 1;
	timeptr->tm_year = 100 + v85xxp_bcd2bin(time.Year);
	timeptr->tm_wday = (int)time.WeekDay;
	timeptr->tm_yday = -1;
	timeptr->tm_isdst = -1;
	timeptr->tm_nsec = 0;

	return 0;
}

#ifdef CONFIG_RTC_ALARM
static int v85xxp_rtc_alarm_get_supported_fields(const struct device *dev, uint16_t id,
							  uint16_t *mask)
{
	ARG_UNUSED(dev);

	if ((id != 0U) || (mask == NULL)) {
		return -EINVAL;
	}

	*mask = RTC_ALARM_TIME_MASK_SECOND |
		RTC_ALARM_TIME_MASK_MINUTE |
		RTC_ALARM_TIME_MASK_HOUR;
	return 0;
}

static int v85xxp_rtc_alarm_set_time(const struct device *dev, uint16_t id, uint16_t mask,
					     const struct rtc_time *timeptr)
{
	struct v85xxp_rtc_data *data = dev->data;
	RTC_AlarmTypeDef alarm = {0};
	uint16_t allowed = RTC_ALARM_TIME_MASK_SECOND |
		RTC_ALARM_TIME_MASK_MINUTE |
		RTC_ALARM_TIME_MASK_HOUR;

	if (id != 0U) {
		return -EINVAL;
	}

	if (mask == 0U) {
		RTC_AlarmCmd(DISABLE);
		RTC_INTConfig(RTC_INT_ALARM, DISABLE);
		data->alarm_mask = 0U;
		return 0;
	}

	if ((mask & ~allowed) != 0U) {
		return -ENOTSUP;
	}

	if ((timeptr == NULL) || !v85xxp_rtc_time_is_valid(timeptr) || (mask != allowed)) {
		return -EINVAL;
	}

	alarm.AlarmHours = v85xxp_bin2bcd(timeptr->tm_hour);
	alarm.AlarmMinutes = v85xxp_bin2bcd(timeptr->tm_min);
	alarm.AlarmSeconds = v85xxp_bin2bcd(timeptr->tm_sec);
	RTC_SetAlarm(&alarm);
	RTC_AlarmCmd(ENABLE);
	RTC_INTConfig(RTC_INT_ALARM, ENABLE);
	RTC_ClearINTStatus(RTC_INTSTS_ALARM);

	data->alarm_mask = mask;
	data->alarm_time = *timeptr;
	return 0;
}

static int v85xxp_rtc_alarm_get_time(const struct device *dev, uint16_t id, uint16_t *mask,
					     struct rtc_time *timeptr)
{
	struct v85xxp_rtc_data *data = dev->data;

	if ((id != 0U) || (mask == NULL) || (timeptr == NULL)) {
		return -EINVAL;
	}

	*mask = data->alarm_mask;
	*timeptr = data->alarm_time;
	return 0;
}

static int v85xxp_rtc_alarm_is_pending(const struct device *dev, uint16_t id)
{
	ARG_UNUSED(dev);

	if (id != 0U) {
		return -EINVAL;
	}

	return RTC_GetINTStatus(RTC_INTSTS_ALARM) ? 1 : 0;
}

static int v85xxp_rtc_alarm_set_callback(const struct device *dev, uint16_t id,
						rtc_alarm_callback callback, void *user_data)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(id);
	ARG_UNUSED(callback);
	ARG_UNUSED(user_data);
	return -ENOTSUP;
}
#endif

static int v85xxp_rtc_init(const struct device *dev)
{
	const struct v85xxp_rtc_config *cfg = dev->config;
	struct v85xxp_rtc_data *data = dev->data;

	ARG_UNUSED(cfg);

	MISC2->PCLKEN |= MISC2_PCLKEN_RTC;
	data->time_valid = true;
#ifdef CONFIG_RTC_ALARM
	data->alarm_mask = 0U;
#endif

	return 0;
}

static DEVICE_API(rtc, v85xxp_rtc_api) = {
	.set_time = v85xxp_rtc_set_time,
	.get_time = v85xxp_rtc_get_time,
#ifdef CONFIG_RTC_ALARM
	.alarm_get_supported_fields = v85xxp_rtc_alarm_get_supported_fields,
	.alarm_set_time = v85xxp_rtc_alarm_set_time,
	.alarm_get_time = v85xxp_rtc_alarm_get_time,
	.alarm_is_pending = v85xxp_rtc_alarm_is_pending,
	.alarm_set_callback = v85xxp_rtc_alarm_set_callback,
#endif
};

#define V85XXP_RTC_INIT(inst) \
	static const struct v85xxp_rtc_config v85xxp_rtc_cfg_##inst = { \
		.base = (RTC_Type *)DT_INST_REG_ADDR(inst), \
	}; \
	static struct v85xxp_rtc_data v85xxp_rtc_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_rtc_init, NULL, \
			      &v85xxp_rtc_data_##inst, &v85xxp_rtc_cfg_##inst, \
			      PRE_KERNEL_1, CONFIG_RTC_INIT_PRIORITY, \
			      &v85xxp_rtc_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_RTC_INIT)
