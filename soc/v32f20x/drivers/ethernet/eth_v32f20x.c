/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_eth

#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/reset.h>
#include <zephyr/net/ethernet.h>
#include <soc.h>

struct eth_v32f20x_config {
	uintptr_t base;
	const struct device *clock_dev;
	clock_control_subsys_t clock_subsys;
	const struct reset_dt_spec reset;
};

struct eth_v32f20x_data {
	struct net_if *iface;
	uint8_t mac_addr[6];
};

static int eth_v32f20x_init(const struct device *dev)
{
	const struct eth_v32f20x_config *config = dev->config;
	int ret;

	/* 1. Reset and Enable Clock */
	if (reset_is_ready_dt(&config->reset)) {
		reset_line_toggle_dt(&config->reset);
	}
	
	ret = clock_control_on(config->clock_dev, config->clock_subsys);
	if (ret < 0) return ret;

	/* 2. Basic MAC Initialization (Placeholder for full register sequence) */
	/* In a real implementation, we would set up DMA descriptors and MAC CFG here */

	return 0;
}

static const struct ethernet_api eth_v32f20x_api = {
	.iface_api.init = NULL, /* Standard Ethernet init */
};

#define ETH_V32F20X_INIT(n) \
	static const struct eth_v32f20x_config eth_v32f20x_config_##n = { \
		.base = DT_INST_REG_ADDR(n), \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)), \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, identifier), \
		.reset = RESET_DT_SPEC_INST_GET(n), \
	}; \
	static struct eth_v32f20x_data eth_v32f20x_data_##n; \
	ETH_NET_DEVICE_DT_INST_DEFINE(n, eth_v32f20x_init, NULL, \
				      &eth_v32f20x_data_##n, &eth_v32f20x_config_##n, \
				      CONFIG_ETH_INIT_PRIORITY, &eth_v32f20x_api, \
				      NET_ETH_MTU);

DT_INST_FOREACH_STATUS_OKAY(ETH_V32F20X_INIT)
