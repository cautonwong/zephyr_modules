/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_i2c

#include <errno.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/pinctrl.h>

#include <soc.h>
#include "lib_i2c.h"
#include "lib_clk.h"

struct v85xxp_i2c_config {
	I2C_Type *base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct pinctrl_dev_config *pincfg;
};

struct v85xxp_i2c_data {
	uint32_t dev_config;
};

static uint32_t v85xxp_i2c_clksel_from_bitrate(uint32_t bitrate)
{
	if (bitrate >= I2C_BITRATE_FAST) {
		return I2C_CLOCKSOURCE_APBD60;
	}
	return I2C_CLOCKSOURCE_APBD120;
}

static int v85xxp_i2c_configure(const struct device *dev, uint32_t dev_config)
{
	struct v85xxp_i2c_data *data = dev->data;
	I2C_InitType init;

	if (I2C_ADDR_10_BITS & dev_config) {
		return -ENOTSUP;
	}
	if ((dev_config & I2C_MODE_CONTROLLER) == 0U) {
		return -ENOTSUP;
	}

	I2C_StructInit(&init);
	init.SlaveAddr = 0;
	init.ClockSource = v85xxp_i2c_clksel_from_bitrate(I2C_SPEED_GET(dev_config));
	I2C_Init(&init);

	data->dev_config = dev_config;
	return 0;
}

static int v85xxp_i2c_transfer(const struct device *dev,
			       struct i2c_msg *msgs,
			       uint8_t num_msgs,
			       uint16_t addr)
{
	if ((msgs == NULL) || (num_msgs == 0U)) {
		return -EINVAL;
	}

	if (num_msgs == 1U) {
		I2C_WRType wr = {
			.SlaveAddr = (uint16_t)(addr << 1),
			.SubAddrType = I2C_SUBADDR_OTHER,
			.PageRange = 256U,
			.SubAddress = 0U,
			.pBuffer = msgs[0].buf,
			.Length = msgs[0].len,
		};
		if ((msgs[0].flags & I2C_MSG_READ) != 0U) {
			return (I2C_MasterReadBytes(&wr) == 0U) ? 0 : -EIO;
		}
		return (I2C_MasterWriteBytes(&wr) == 0U) ? 0 : -EIO;
	}

	if (num_msgs == 2U && (msgs[0].flags & I2C_MSG_READ) == 0U && msgs[0].len == 1U) {
		I2C_WRType wr = {
			.SlaveAddr = (uint16_t)(addr << 1),
			.SubAddrType = I2C_SUBADDR_1BYTE,
			.PageRange = 256U,
			.SubAddress = msgs[0].buf[0],
			.pBuffer = msgs[1].buf,
			.Length = msgs[1].len,
		};
		if ((msgs[1].flags & I2C_MSG_READ) != 0U) {
			return (I2C_MasterReadBytes(&wr) == 0U) ? 0 : -EIO;
		}
		return (I2C_MasterWriteBytes(&wr) == 0U) ? 0 : -EIO;
	}

	return -ENOTSUP;
}

static int v85xxp_i2c_init(const struct device *dev)
{
	const struct v85xxp_i2c_config *cfg = dev->config;
	int ret;

	ret = clock_control_on(cfg->clock_dev, cfg->clock_subsys);
	if (ret != 0) return ret;

	ret = pinctrl_apply_state(cfg->pincfg, PINCTRL_STATE_DEFAULT);
	if (ret < 0 && ret != -ENOENT) return ret;

	I2C_DeInit(0U);
	return v85xxp_i2c_configure(dev, I2C_MODE_CONTROLLER | I2C_SPEED_SET(I2C_SPEED_STANDARD));
}

static DEVICE_API(i2c, v85xxp_i2c_api) = {
	.configure = v85xxp_i2c_configure,
	.transfer = v85xxp_i2c_transfer,
	.get_config = (int (*)(const struct device *, uint32_t *))NULL,
};

#define V85XXP_I2C_INIT(inst) \
	PINCTRL_DT_INST_DEFINE(inst); \
	static const struct v85xxp_i2c_config v85xxp_i2c_cfg_##inst = { \
		.base = (I2C_Type *)DT_INST_REG_ADDR(inst), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(inst)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(inst, identifier), \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(inst), \
	}; \
	static struct v85xxp_i2c_data v85xxp_i2c_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_i2c_init, NULL, \
			      &v85xxp_i2c_data_##inst, &v85xxp_i2c_cfg_##inst, \
			      PRE_KERNEL_1, CONFIG_I2C_INIT_PRIORITY, \
			      &v85xxp_i2c_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_I2C_INIT)
