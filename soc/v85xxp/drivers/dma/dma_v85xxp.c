/*
 * Copyright (c) 2026
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT v85xxp_dma

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <zephyr/device.h>
#include <zephyr/drivers/dma.h>
#include <zephyr/irq.h>

#include <soc.h>
#include "lib_dma.h"

#define V85XXP_DMA_MAX_CHANNELS 4U

struct v85xxp_dma_channel_state {
	bool configured;
	bool busy;
	struct dma_config cfg;
	struct dma_block_config block;
	DMA_InitType hal_cfg;
};

struct v85xxp_dma_config {
	DMA_Type *base;
	uint32_t channels;
	void (*irq_config_func)(const struct device *dev);
};

struct v85xxp_dma_data {
	struct v85xxp_dma_channel_state ch[V85XXP_DMA_MAX_CHANNELS];
};

static uint32_t v85xxp_dma_done_mask(uint32_t ch)
{
	switch (ch) {
	case 0: return DMA_INTSTS_C0DA;
	case 1: return DMA_INTSTS_C1DA;
	case 2: return DMA_INTSTS_C2DA;
	case 3: return DMA_INTSTS_C3DA;
	default: return 0U;
	}
}

static uint32_t v85xxp_dma_err_mask(uint32_t ch)
{
	switch (ch) {
	case 0: return DMA_INTSTS_C0FE | DMA_INTSTS_C0PE;
	case 1: return DMA_INTSTS_C1FE | DMA_INTSTS_C1PE;
	case 2: return DMA_INTSTS_C2FE | DMA_INTSTS_C2PE;
	case 3: return DMA_INTSTS_C3FE | DMA_INTSTS_C3PE;
	default: return 0U;
	}
}

static uint32_t v85xxp_dma_busy_mask(uint32_t ch)
{
	switch (ch) {
	case 0: return DMA_INTSTS_C0BUSY;
	case 1: return DMA_INTSTS_C1BUSY;
	case 2: return DMA_INTSTS_C2BUSY;
	case 3: return DMA_INTSTS_C3BUSY;
	default: return 0U;
	}
}

static uint32_t v85xxp_dma_done_ie_mask(uint32_t ch)
{
	switch (ch) {
	case 0: return DMA_INT_C0DA;
	case 1: return DMA_INT_C1DA;
	case 2: return DMA_INT_C2DA;
	case 3: return DMA_INT_C3DA;
	default: return 0U;
	}
}

static uint32_t v85xxp_dma_err_ie_mask(uint32_t ch)
{
	switch (ch) {
	case 0: return DMA_INT_C0FE | DMA_INT_C0PE;
	case 1: return DMA_INT_C1FE | DMA_INT_C1PE;
	case 2: return DMA_INT_C2FE | DMA_INT_C2PE;
	case 3: return DMA_INT_C3FE | DMA_INT_C3PE;
	default: return 0U;
	}
}

static int v85xxp_dma_transsize_from_width(uint32_t width)
{
	switch (width) {
	case 1U:
		return DMA_TRANSSIZE_BYTE;
	case 2U:
		return DMA_TRANSSIZE_HWORD;
	case 4U:
		return DMA_TRANSSIZE_WORD;
	default:
		return -EINVAL;
	}
}

static int v85xxp_dma_addrmode_from_adj(uint16_t adj)
{
	switch (adj) {
	case DMA_ADDR_ADJ_INCREMENT:
		return DMA_DESTADDRMODE_PEND;
	case DMA_ADDR_ADJ_NO_CHANGE:
		return DMA_DESTADDRMODE_FIX;
	default:
		return -ENOTSUP;
	}
}

static int v85xxp_dma_compute_lengths(uint32_t elems, uint8_t *frame_len,
				      uint8_t *pack_len, uint32_t *trans_mode)
{
	uint32_t d;

	if ((elems == 0U) || (frame_len == NULL) || (pack_len == NULL) || (trans_mode == NULL)) {
		return -EINVAL;
	}

	if (elems <= 256U) {
		*frame_len = (uint8_t)(elems - 1U);
		*pack_len = 0U;
		*trans_mode = DMA_TRANSMODE_SINGLE;
		return 0;
	}

	for (d = 256U; d >= 1U; d--) {
		if ((elems % d) == 0U) {
			uint32_t f = elems / d;
			if (f <= 256U) {
				*frame_len = (uint8_t)(f - 1U);
				*pack_len = (uint8_t)(d - 1U);
				*trans_mode = DMA_TRANSMODE_PACK;
				return 0;
			}
		}
	}

	return -ENOTSUP;
}

static int v85xxp_dma_fill_hal_cfg(const struct dma_config *cfg, DMA_InitType *hal)
{
	const struct dma_block_config *b;
	uint32_t width;
	uint32_t elems;
	uint8_t flen;
	uint8_t plen;
	int tsize;
	int dmode;
	int smode;
	int rc;

	if ((cfg == NULL) || (hal == NULL) || (cfg->head_block == NULL) || (cfg->block_count != 1U)) {
		return -EINVAL;
	}

	b = cfg->head_block;
	if (b->next_block != NULL) {
		return -ENOTSUP;
	}

	if (cfg->channel_direction != MEMORY_TO_MEMORY &&
	    cfg->channel_direction != MEMORY_TO_PERIPHERAL &&
	    cfg->channel_direction != PERIPHERAL_TO_MEMORY) {
		return -ENOTSUP;
	}

	if (b->source_gather_en || b->dest_scatter_en || b->source_reload_en || b->dest_reload_en) {
		return -ENOTSUP;
	}

	if ((cfg->source_data_size == 0U) || (cfg->source_data_size != cfg->dest_data_size)) {
		return -ENOTSUP;
	}

	width = cfg->source_data_size;
	if ((b->block_size == 0U) || ((b->block_size % width) != 0U)) {
		return -EINVAL;
	}

	elems = b->block_size / width;
	rc = v85xxp_dma_compute_lengths(elems, &flen, &plen, &hal->TransMode);
	if (rc != 0) {
		return rc;
	}

	tsize = v85xxp_dma_transsize_from_width(width);
	if (tsize < 0) {
		return tsize;
	}

	dmode = v85xxp_dma_addrmode_from_adj(b->dest_addr_adj);
	smode = v85xxp_dma_addrmode_from_adj(b->source_addr_adj);
	if ((dmode < 0) || (smode < 0)) {
		return -ENOTSUP;
	}

	DMA_StructInit(hal);
	hal->DestAddr = b->dest_address;
	hal->SrcAddr = b->source_address;
	hal->FrameLen = flen;
	hal->PackLen = plen;
	hal->ContMode = cfg->cyclic ? DMA_CONTMODE_ENABLE : DMA_CONTMODE_DISABLE;
	hal->ReqSrc = (cfg->dma_slot & 0x1FU) << DMA_CCTL_DMASEL_Pos;
	hal->DestAddrMode = (uint32_t)dmode;
	hal->SrcAddrMode = (uint32_t)smode;
	hal->TransSize = (uint32_t)tsize;

	return 0;
}

static int v85xxp_dma_config(const struct device *dev, uint32_t channel, struct dma_config *cfg)
{
	const struct v85xxp_dma_config *config = dev->config;
	struct v85xxp_dma_data *data = dev->data;
	struct v85xxp_dma_channel_state *st;
	int rc;

	if ((cfg == NULL) || (channel >= config->channels)) {
		return -EINVAL;
	}

	st = &data->ch[channel];
	rc = v85xxp_dma_fill_hal_cfg(cfg, &st->hal_cfg);
	if (rc != 0) {
		return rc;
	}

	st->cfg = *cfg;
	st->block = *cfg->head_block;
	st->cfg.head_block = &st->block;
	st->configured = true;
	st->busy = false;

	DMA_DeInit(channel);
	DMA_Init(&st->hal_cfg, channel);

	if (cfg->dma_callback != NULL) {
		DMA_INTConfig(v85xxp_dma_done_ie_mask(channel), ENABLE);
		if (!cfg->error_callback_dis) {
			DMA_INTConfig(v85xxp_dma_err_ie_mask(channel), ENABLE);
		}
	}

	return 0;
}

#ifdef CONFIG_DMA_64BIT
static int v85xxp_dma_reload(const struct device *dev, uint32_t channel,
			     uint64_t src, uint64_t dst, size_t size)
#else
static int v85xxp_dma_reload(const struct device *dev, uint32_t channel,
			     uint32_t src, uint32_t dst, size_t size)
#endif
{
	const struct v85xxp_dma_config *config = dev->config;
	struct v85xxp_dma_data *data = dev->data;
	struct v85xxp_dma_channel_state *st;

	if (channel >= config->channels) {
		return -EINVAL;
	}

	st = &data->ch[channel];
	if (!st->configured) {
		return -EINVAL;
	}

	st->block.source_address = (uint32_t)src;
	st->block.dest_address = (uint32_t)dst;
	st->block.block_size = size;
	st->cfg.head_block = &st->block;

	if (v85xxp_dma_fill_hal_cfg(&st->cfg, &st->hal_cfg) != 0) {
		return -EINVAL;
	}

	DMA_Cmd(channel, DISABLE);
	DMA_Init(&st->hal_cfg, channel);
	return 0;
}

static int v85xxp_dma_start(const struct device *dev, uint32_t channel)
{
	const struct v85xxp_dma_config *config = dev->config;
	struct v85xxp_dma_data *data = dev->data;

	if (channel >= config->channels) {
		return -EINVAL;
	}

	if (!data->ch[channel].configured) {
		return -EINVAL;
	}

	DMA_ClearINTStatus(v85xxp_dma_done_mask(channel) | v85xxp_dma_err_mask(channel));
	DMA_Cmd(channel, ENABLE);
	data->ch[channel].busy = true;
	return 0;
}

static int v85xxp_dma_stop(const struct device *dev, uint32_t channel)
{
	const struct v85xxp_dma_config *config = dev->config;
	struct v85xxp_dma_data *data = dev->data;

	if (channel >= config->channels) {
		return -EINVAL;
	}

	DMA_StopTransmit(channel, ENABLE);
	DMA_Cmd(channel, DISABLE);
	DMA_StopTransmit(channel, DISABLE);
	data->ch[channel].busy = false;
	return 0;
}

static int v85xxp_dma_suspend(const struct device *dev, uint32_t channel)
{
	return v85xxp_dma_stop(dev, channel);
}

static int v85xxp_dma_resume(const struct device *dev, uint32_t channel)
{
	return v85xxp_dma_start(dev, channel);
}

static int v85xxp_dma_get_status(const struct device *dev, uint32_t channel,
				 struct dma_status *stat)
{
	const struct v85xxp_dma_config *config = dev->config;
	struct v85xxp_dma_data *data = dev->data;

	if ((channel >= config->channels) || (stat == NULL)) {
		return -EINVAL;
	}

	memset(stat, 0, sizeof(*stat));
	stat->busy = (DMA_GetINTStatus(v85xxp_dma_busy_mask(channel)) != 0U) || data->ch[channel].busy;
	stat->dir = (enum dma_channel_direction)data->ch[channel].cfg.channel_direction;
	return 0;
}

static int v85xxp_dma_get_attribute(const struct device *dev, uint32_t type, uint32_t *value)
{
	ARG_UNUSED(dev);

	if (value == NULL) {
		return -EINVAL;
	}

	switch (type) {
	case DMA_ATTR_BUFFER_ADDRESS_ALIGNMENT:
	case DMA_ATTR_BUFFER_SIZE_ALIGNMENT:
	case DMA_ATTR_COPY_ALIGNMENT:
		*value = 1U;
		return 0;
	case DMA_ATTR_MAX_BLOCK_COUNT:
		*value = 1U;
		return 0;
	default:
		return -EINVAL;
	}
}

static void v85xxp_dma_isr(const struct device *dev)
{
	const struct v85xxp_dma_config *config = dev->config;
	struct v85xxp_dma_data *data = dev->data;
	uint32_t ch;

	for (ch = 0U; ch < config->channels; ch++) {
		uint32_t done = v85xxp_dma_done_mask(ch);
		uint32_t err = v85xxp_dma_err_mask(ch);
		int status = 0;
		bool hit = false;

		if (DMA_GetINTStatus(err) != 0U) {
			status = -EIO;
			DMA_ClearINTStatus(err);
			hit = true;
		}

		if (DMA_GetINTStatus(done) != 0U) {
			DMA_ClearINTStatus(done);
			status = DMA_STATUS_COMPLETE;
			hit = true;
		}

		if (hit) {
			if (!data->ch[ch].cfg.cyclic) {
				data->ch[ch].busy = false;
			}

			if (data->ch[ch].cfg.dma_callback != NULL) {
				data->ch[ch].cfg.dma_callback(dev, data->ch[ch].cfg.user_data,
							  ch, status);
			}
		}
	}
}

static int v85xxp_dma_init(const struct device *dev)
{
	const struct v85xxp_dma_config *config = dev->config;

	DMA_DeInit(DMA_CHANNEL_0);
	DMA_DeInit(DMA_CHANNEL_1);
	DMA_DeInit(DMA_CHANNEL_2);
	DMA_DeInit(DMA_CHANNEL_3);
	config->irq_config_func(dev);
	return 0;
}

static DEVICE_API(dma, v85xxp_dma_api) = {
	.config = v85xxp_dma_config,
	.reload = v85xxp_dma_reload,
	.start = v85xxp_dma_start,
	.stop = v85xxp_dma_stop,
	.suspend = v85xxp_dma_suspend,
	.resume = v85xxp_dma_resume,
	.get_status = v85xxp_dma_get_status,
	.get_attribute = v85xxp_dma_get_attribute,
};

#define V85XXP_DMA_IRQ_CONFIG(inst) \
	static void v85xxp_dma_irq_config_##inst(const struct device *dev) \
	{ \
		ARG_UNUSED(dev); \
		IRQ_CONNECT(DT_INST_IRQN(inst), DT_INST_IRQ(inst, priority), \
			    v85xxp_dma_isr, DEVICE_DT_INST_GET(inst), 0); \
		irq_enable(DT_INST_IRQN(inst)); \
	}

#define V85XXP_DMA_INIT(inst) \
	V85XXP_DMA_IRQ_CONFIG(inst) \
	static const struct v85xxp_dma_config v85xxp_dma_cfg_##inst = { \
		.base = (DMA_Type *)DT_INST_REG_ADDR(inst), \
		.channels = DT_INST_PROP_OR(inst, dma_channels, V85XXP_DMA_MAX_CHANNELS), \
		.irq_config_func = v85xxp_dma_irq_config_##inst, \
	}; \
	static struct v85xxp_dma_data v85xxp_dma_data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, v85xxp_dma_init, NULL, \
			      &v85xxp_dma_data_##inst, &v85xxp_dma_cfg_##inst, \
			      POST_KERNEL, CONFIG_DMA_INIT_PRIORITY, \
			      &v85xxp_dma_api);

DT_INST_FOREACH_STATUS_OKAY(V85XXP_DMA_INIT)
