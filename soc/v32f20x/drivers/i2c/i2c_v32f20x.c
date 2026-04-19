/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_i2c

#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/reset.h>
#include <zephyr/drivers/pinctrl.h>
#include <soc.h>
#include <lib_i2c.h>

struct i2c_v32f20x_config {
	I2C_Type *regs;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct reset_dt_spec reset;
	const struct pinctrl_dev_config *pincfg;
	uint32_t bitrate;
};

struct i2c_v32f20x_data {
	struct k_sem lock;
};

static int i2c_v32f20x_transfer(const struct device *dev, struct i2c_msg *msgs,
				 uint8_t num_msgs, uint16_t addr)
{
	const struct i2c_v32f20x_config *config = dev->config;
	struct i2c_v32f20x_data *data = dev->data;
	int ret = 0;

	k_sem_take(&data->lock, K_FOREVER);

	for (uint8_t i = 0; i < num_msgs; i++) {
		struct i2c_msg *msg = &msgs[i];
		I2C_TransferType transfer;

		transfer.I2C_Address = addr;
		transfer.I2C_Buffer = msg->buf;
		transfer.I2C_Length = msg->len;
		
		/* Map flags to HAL */
		if (msg->flags & I2C_MSG_READ) {
			ret = I2C_MasterReceive(config->regs, &transfer);
		} else {
			ret = I2C_MasterTransmit(config->regs, &transfer);
		}

		if (ret != SUCCESS) {
			ret = -EIO;
			break;
		}

		ret = 0;
	}

	k_sem_give(&data->lock);
	return ret;
}

static int i2c_v32f20x_configure(const struct device *dev, uint32_t dev_config)
{
	const struct i2c_v32f20x_config *config = dev->config;
	uint32_t clock_rate;
	I2C_InitType init_struct;

	if (!(dev_config & I2C_MODE_CONTROLLER)) {
		return -ENOTSUP;
	}

	if (clock_control_get_rate(config->clock_dev, config->clock_subsys, &clock_rate) != 0) {
		return -EIO;
	}

	I2C_StructInit(&init_struct);
	
	switch (I2C_SPEED_GET(dev_config)) {
	case I2C_SPEED_STANDARD: init_struct.I2C_ClockSpeed = 100000; break;
	case I2C_SPEED_FAST:     init_struct.I2C_ClockSpeed = 400000; break;
	default: return -ENOTSUP;
	}

	init_struct.I2C_BusClock = clock_rate;
	I2C_Init(config->regs, &init_struct);

	return 0;
}

static const struct i2c_driver_api i2c_v32f20x_driver_api = {
	.configure = i2c_v32f20x_configure,
	.transfer = i2c_v32f20x_transfer,
};

static int i2c_v32f20x_init(const struct device *dev)
{
	const struct i2c_v32f20x_config *config = dev->config;
	struct i2c_v32f20x_data *data = dev->data;
	int ret;

	k_sem_init(&data->lock, 1, 1);

	ret = pinctrl_apply_state(config->pincfg, PINCTRL_STATE_DEFAULT);
	if (ret < 0) return ret;

	if (config->reset.dev != NULL) {
		reset_line_toggle(config->reset.dev, config->reset.id);
	}

	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	return i2c_v32f20x_configure(dev, I2C_MODE_CONTROLLER | i2c_map_dt_bitrate(config->bitrate));
}

#define I2C_V32F20X_INIT(n)                                                    \
	PINCTRL_DT_INST_DEFINE(n);                                                 \
	static const struct i2c_v32f20x_config i2c_v32f20x_config_##n = {          \
		.regs = (I2C_Type *)DT_INST_REG_ADDR(n),                               \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),                   \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, id),    \
		.reset = RESET_DT_SPEC_INST_GET_OR(n, {0}),                            \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(n),                           \
		.bitrate = DT_INST_PROP_OR(n, clock_frequency, 100000),                \
	};                                                                         \
	static struct i2c_v32f20x_data i2c_v32f20x_data_##n;                       \
	DEVICE_DT_INST_DEFINE(n, i2c_v32f20x_init, NULL, &i2c_v32f20x_data_##n,      \
			      &i2c_v32f20x_config_##n, POST_KERNEL,                \
			      CONFIG_I2C_INIT_PRIORITY, &i2c_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(I2C_V32F20X_INIT)
