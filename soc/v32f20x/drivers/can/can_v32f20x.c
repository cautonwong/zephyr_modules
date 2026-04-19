/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_can

#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/reset.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/logging/log.h>
#include <soc.h>
#include <lib_can.h>

LOG_MODULE_REGISTER(can_v32f20x, CONFIG_CAN_LOG_LEVEL);

struct can_v32f20x_config {
	CAN_Type *regs;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct reset_dt_spec reset;
	const struct pinctrl_dev_config *pincfg;
	uint32_t bus_speed;
};

struct can_v32f20x_data {
	struct k_mutex lock;
	can_tx_callback_t tx_cb;
	void *tx_cb_data;
};

static int can_v32f20x_set_mode(const struct device *dev, can_mode_t mode)
{
	const struct can_v32f20x_config *config = dev->config;

	if (mode & CAN_MODE_LOOPBACK) {
		CAN_ModeConfig(config->regs, CAN_MODE_LOOPBACK_INTERNAL);
	} else {
		CAN_ModeConfig(config->regs, CAN_MODE_NORMAL);
	}
	return 0;
}

static int can_v32f20x_set_timing(const struct device *dev,
				  const struct can_timing *timing)
{
	const struct can_v32f20x_config *config = dev->config;
	CAN_TimingType can_timing;

	can_timing.CAN_Prescaler = timing->prescaler;
	can_timing.CAN_SJW = timing->sjw;
	can_timing.CAN_BS1 = timing->prop_seg + timing->phase_seg1;
	can_timing.CAN_BS2 = timing->phase_seg2;

	CAN_SetTiming(config->regs, &can_timing);
	return 0;
}

static int can_v32f20x_send(const struct device *dev,
			    const struct can_frame *frame,
			    k_timeout_t timeout,
			    can_tx_callback_t callback,
			    void *user_data)
{
	const struct can_v32f20x_config *config = dev->config;
	struct can_v32f20x_data *data = dev->data;
	CAN_TxMsgType tx_msg;

	if (frame->flags & CAN_FRAME_FDF) {
		return -ENOTSUP;
	}

	tx_msg.ID = frame->id;
	tx_msg.IDE = (frame->flags & CAN_FRAME_IDE) ? CAN_ID_EXT : CAN_ID_STD;
	tx_msg.RTR = (frame->flags & CAN_FRAME_RTR) ? CAN_RTR_REMOTE : CAN_RTR_DATA;
	tx_msg.DLC = frame->dlc;
	memcpy(tx_msg.Data, frame->data, frame->dlc);

	k_mutex_lock(&data->lock, K_FOREVER);
	data->tx_cb = callback;
	data->tx_cb_data = user_data;

	if (CAN_Transmit(config->regs, &tx_msg) != SUCCESS) {
		k_mutex_unlock(&data->lock);
		return -EIO;
	}

	k_mutex_unlock(&data->lock);
	return 0;
}

static void can_v32f20x_isr(const struct device *dev)
{
	const struct can_v32f20x_config *config = dev->config;
	struct can_v32f20x_data *data = dev->data;

	if (CAN_GetITStatus(config->regs, CAN_IT_TX)) {
		CAN_ClearITStatus(config->regs, CAN_IT_TX);
		if (data->tx_cb) {
			data->tx_cb(dev, 0, data->tx_cb_data);
		}
	}
}

static const struct can_driver_api can_v32f20x_api = {
	.set_mode = can_v32f20x_set_mode,
	.set_timing = can_v32f20x_set_timing,
	.send = can_v32f20x_send,
	.get_capabilities = NULL, /* TODO: Add caps */
};

static int can_v32f20x_init(const struct device *dev)
{
	const struct can_v32f20x_config *config = dev->config;
	struct can_v32f20x_data *data = dev->data;
	int ret;

	k_mutex_init(&data->lock);

	ret = pinctrl_apply_state(config->pincfg, PINCTRL_STATE_DEFAULT);
	if (ret < 0) return ret;

	clock_control_on(config->clock_dev, config->clock_subsys);

	CAN_InitType init_struct;
	CAN_StructInit(&init_struct);
	CAN_Init(config->regs, &init_struct);

	return 0;
}

#define CAN_V32F20X_INIT(n)                                                    \
	PINCTRL_DT_INST_DEFINE(n);                                                 \
	static const struct can_v32f20x_config can_v32f20x_config_##n = {          \
		.regs = (CAN_Type *)DT_INST_REG_ADDR(n),                               \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),                   \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, id),    \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(n),                           \
	};                                                                         \
	static struct can_v32f20x_data can_v32f20x_data_##n;                       \
	DEVICE_DT_INST_DEFINE(n, can_v32f20x_init, NULL, &can_v32f20x_data_##n,      \
			      &can_v32f20x_config_##n, POST_KERNEL,                \
			      CONFIG_CAN_INIT_PRIORITY, &can_v32f20x_api);

DT_INST_FOREACH_STATUS_OKAY(CAN_V32F20X_INIT)
