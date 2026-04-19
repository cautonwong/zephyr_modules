/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vango_v32f20x_dma

#include <zephyr/kernel.h>
#include <zephyr/drivers/dma.h>
#include <zephyr/irq.h>
#include <soc.h>

#if defined(V32F20XXX_CM0_CORE)
#include <lib_bdma.h>
#else
#include <lib_dma.h>
#endif

#define VANGO_DMA_MAX_CHANNELS 8

struct dma_v32f20x_channel_data {
	dma_callback_t callback;
	void *user_data;
};

struct dma_v32f20x_config {
	void *regs;
	void (*irq_config)(const struct device *dev);
};

struct dma_v32f20x_data {
	struct dma_v32f20x_channel_data chan_data[VANGO_DMA_MAX_CHANNELS];
};

static int dma_v32f20x_configure(const struct device *dev, uint32_t channel,
				 struct dma_config *config)
{
	struct dma_v32f20x_data *data = dev->data;

	if (channel >= VANGO_DMA_MAX_CHANNELS) {
		return -EINVAL;
	}

#if defined(V32F20XXX_CM0_CORE)
    ARG_UNUSED(dev);
	BDMA_InitType init_struct;
	BDMA_StructInit(&init_struct);

	init_struct.SrcAddr = config->head_block->source_address;
	init_struct.DestAddr = config->head_block->dest_address;
	/* BDMA uses PackLen and FrameLen, mapping simplified for now */
	init_struct.FrameLen = (uint8_t)(config->head_block->block_size & 0xFF);

	switch (config->source_data_size) {
	case 1: init_struct.TransSize = BDMA_TRANSSIZE_BYTE; break;
	case 2: init_struct.TransSize = BDMA_TRANSSIZE_HWORD; break;
	case 4: init_struct.TransSize = BDMA_TRANSSIZE_WORD; break;
	default: return -EINVAL;
	}

	data->chan_data[channel].callback = config->dma_callback;
	data->chan_data[channel].user_data = config->user_data;

	BDMA_Init(&init_struct, channel);

	if (config->dma_callback) {
		/* BDMA_INTConfig implementation detail might vary */
		BDMA_INTConfig(BDMA_INT_C0DA << channel, ENABLE);
	}
#else
	DMA_InitType init_struct;
	DMA_Channel_Type *chan_regs;
	chan_regs = (DMA_Channel_Type *)((uintptr_t)dev_conf->regs + 0x100 + (channel * 0x58));

	DMA_StructInit(&init_struct);
	init_struct.DMA_SourceAddress = config->head_block->source_address;
	init_struct.DMA_DestinationAddress = config->head_block->dest_address;
	init_struct.DMA_TransferSize = (config->head_block->block_size & 0xFFF);

	switch (config->source_data_size) {
	case 1: init_struct.DMA_SourceTransferWidth = DMA_SourceTransferWidth_8Bit; break;
	case 2: init_struct.DMA_SourceTransferWidth = DMA_SourceTransferWidth_16Bit; break;
	case 4: init_struct.DMA_SourceTransferWidth = DMA_SourceTransferWidth_32Bit; break;
	default: return -EINVAL;
	}

	data->chan_data[channel].callback = config->dma_callback;
	data->chan_data[channel].user_data = config->user_data;

	DMA_Init(chan_regs, &init_struct);

	if (config->dma_callback) {
		DMA_ITConfig(chan_regs, DMA_CTL1_DONE, ENABLE);
	}
#endif

	return 0;
}

static int dma_v32f20x_start(const struct device *dev, uint32_t channel)
{
#if defined(V32F20XXX_CM0_CORE)
	BDMA_Cmd(channel, ENABLE);
#else
	const struct dma_v32f20x_config *dev_conf = dev->config;
	DMA_Channel_Type *chan_regs = (DMA_Channel_Type *)((uintptr_t)dev_conf->regs + 0x100 + (channel * 0x58));
	DMA_ChannelCmd(chan_regs, ENABLE);
#endif
	return 0;
}

static int dma_v32f20x_stop(const struct device *dev, uint32_t channel)
{
#if defined(V32F20XXX_CM0_CORE)
	BDMA_Cmd(channel, DISABLE);
#else
	const struct dma_v32f20x_config *dev_conf = dev->config;
	DMA_Channel_Type *chan_regs = (DMA_Channel_Type *)((uintptr_t)dev_conf->regs + 0x100 + (channel * 0x58));
	DMA_ChannelCmd(chan_regs, DISABLE);
#endif
	return 0;
}

static void dma_v32f20x_isr(const struct device *dev)
{
	struct dma_v32f20x_data *data = dev->data;

#if defined(V32F20XXX_CM0_CORE)
	for (int i = 0; i < 4; i++) { /* BDMA usually has 4 channels */
		if (BDMA_GetINTStatus(BDMA_INT_C0DA << i)) {
			BDMA_ClearINTStatus(BDMA_INT_C0DA << i);
			if (data->chan_data[i].callback) {
				data->chan_data[i].callback(dev, data->chan_data[i].user_data, i, 0);
			}
		}
	}
#else
	const struct dma_v32f20x_config *dev_conf = dev->config;
	for (int i = 0; i < VANGO_DMA_MAX_CHANNELS; i++) {
		DMA_Channel_Type *chan_regs = (DMA_Channel_Type *)((uintptr_t)dev_conf->regs + 0x100 + (i * 0x58));
		if (DMA_GetITtatus(chan_regs, DMA_CTL1_DONE)) {
			DMA_ClearITStatus(chan_regs, DMA_CTL1_DONE);
			if (data->chan_data[i].callback) {
				data->chan_data[i].callback(dev, data->chan_data[i].user_data, i, 0);
			}
		}
	}
#endif
}

static const struct dma_driver_api dma_v32f20x_driver_api = {
	.config = dma_v32f20x_configure,
	.start = dma_v32f20x_start,
	.stop = dma_v32f20x_stop,
};

static int dma_v32f20x_init(const struct device *dev)
{
	const struct dma_v32f20x_config *dev_conf = dev->config;

#if defined(V32F20XXX_CM0_CORE)
	/* BDMA initialization if needed */
#else
	DMA_Cmd((DMA_Type *)dev_conf->regs, ENABLE);
#endif
	dev_conf->irq_config(dev);

	return 0;
}

#define DMA_V32F20X_INIT(n)                                                                        \
	static void dma_v32f20x_irq_config_##n(const struct device *dev)                          \
	{                                                                                          \
		IRQ_CONNECT(DT_INST_IRQN(n), DT_INST_IRQ(n, priority),                            \
			    dma_v32f20x_isr, DEVICE_DT_INST_GET(n), 0);                          \
		irq_enable(DT_INST_IRQN(n));                                                       \
	}                                                                                          \
	static const struct dma_v32f20x_config dma_v32f20x_config_##n = {                          \
		.regs = (void *)DT_INST_REG_ADDR(n),                                               \
		.irq_config = dma_v32f20x_irq_config_##n,                                          \
	};                                                                                         \
	static struct dma_v32f20x_data dma_v32f20x_data_##n;                                       \
	DEVICE_DT_INST_DEFINE(n, dma_v32f20x_init, NULL, &dma_v32f20x_data_##n,                    \
			      &dma_v32f20x_config_##n, PRE_KERNEL_1,                              \
			      CONFIG_DMA_INIT_PRIORITY, &dma_v32f20x_driver_api);

DT_INST_FOREACH_STATUS_OKAY(DMA_V32F20X_INIT)
