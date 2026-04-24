/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_rtc

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#include <zephyr/device.h>
#include <zephyr/drivers/rtc.h>
#include <zephyr/drivers/clock_control.h>

#include <soc.h>
#include "lib_rtc.h"
#include "lib_clk.h"

struct v85xxp_rtc_config {
	RTC_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
};

struct v85xxp_rtc_data {
	bool time_valid;
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
	time.WeekDay = (uint32_t)(timeptr->tm_wday >= 0 ? timeptr->tm_wday : 0);
	time.Hours = v85xxp_bin2bcd(timeptr->tm_hour);
	time.Minutes = v85xxp_bin2bcd(timeptr->tm_min);
	time.Seconds = v85xxp_bin2bcd(timeptr->tm_sec);

	RTC_SetTime(&time, RTC_INACCURATE);
	data->time_valid = true;
	return 0;
}

static int v85xxp_rtc_get_time(const struct device *dev, struct rtc_time *timeptr)
{
	struct v85xxp_rtc_data *data = dev->data;
	RTC_TimeTypeDef time = {0};

	if (timeptr == NULL) return -EINVAL;
	if (!data->time_valid) return -ENODATA;

	RTC_GetTime(&time, RTC_INACCURATE);
	timeptr->tm_sec = v85xxp_bcd2bin(time.Seconds);
	timeptr->tm_min = v85xxp_bcd2bin(time.Minutes);
	timeptr->tm_hour = v85xxp_bcd2bin(time.Hours);
	timeptr->tm_mday = v85xxp_bcd2bin(time.Date);
	timeptr->tm_mon = v85xxp_bcd2bin(time.Month) - 1;
	timeptr->tm_year = 100 + v85xxp_bcd2bin(time.Year);
	timeptr->tm_wday = (int)time.WeekDay;
	timeptr->tm_nsec = 0;
	return 0;
}

static int v85xxp_rtc_init(const struct device *dev)
{
	const struct v85xxp_rtc_config *cfg = dev->config;
	struct v85xxp_rtc_data *data = dev->data;

	if (clock_control_on(cfg->clock_dev, cfg->clock_subsys) != 0) return -EIO;
	data->time_valid = true;
	return 0;
}

static DEVICE_API(rtc, v85xxp_rtc_api) = {
	.set_time = v85xxp_rtc_set_time,
	.get_time = v85xxp_rtc_get_time,
};

#define V85XXP_RTC_INIT(inst) \
	static const struct v85xxp_rtc_config v85xxp_rtc_cfg_##inst = { \
		.base = (RTC_Type *)DT_INST_REG_ADDR(inst), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
	}; \
	static struct v85xxp_rtc_data v85xxp_rtc_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_rtc_init, NULL, \
			      &v85xxp_rtc_data_##inst, &v85xxp_rtc_cfg_##inst, \
			      PRE_KERNEL_1, CONFIG_RTC_INIT_PRIORITY, \
			      &v85xxp_rtc_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_RTC_INIT)
