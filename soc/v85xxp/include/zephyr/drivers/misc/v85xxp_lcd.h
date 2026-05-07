/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: Apache-2.0
 *
 * V85XXP Segment LCD Driver API
 */

#ifndef ZEPHYR_DRIVERS_MISC_V85XXP_LCD_H_
#define ZEPHYR_DRIVERS_MISC_V85XXP_LCD_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief V85XXP segment LCD driver API.
 *
 * The V85XXP LCD controller drives static segment LCD glass with
 * 4/6/8 COM multiplexing. Data registers DATA0..DATA15 map to
 * segment pins SEG0..SEG(32*N-1).
 */
struct v85xxp_lcd_driver_api {
	void (*update_data)(const struct device *dev, uint8_t idx, uint32_t data);
	void (*clear)(const struct device *dev);
	uint32_t (*get_data)(const struct device *dev, uint8_t idx);
	int (*enable)(const struct device *dev, bool enable);
};

/**
 * @brief Write a 32-bit segment pattern to a data register.
 *
 * @param dev LCD device instance
 * @param idx Data register index (0..15)
 * @param data Segment bitmask to write
 */
static inline void v85xxp_lcd_update_data(const struct device *dev,
					   uint8_t idx, uint32_t data)
{
	const struct v85xxp_lcd_driver_api *api =
		(const struct v85xxp_lcd_driver_api *)dev->api;
	api->update_data(dev, idx, data);
}

/**
 * @brief Clear all 16 data registers to zero.
 *
 * @param dev LCD device instance
 */
static inline void v85xxp_lcd_clear(const struct device *dev)
{
	const struct v85xxp_lcd_driver_api *api =
		(const struct v85xxp_lcd_driver_api *)dev->api;
	api->clear(dev);
}

/**
 * @brief Read the current value of a data register.
 *
 * @param dev LCD device instance
 * @param idx Data register index (0..15)
 * @return Current segment bitmask
 */
static inline uint32_t v85xxp_lcd_get_data(const struct device *dev, uint8_t idx)
{
	const struct v85xxp_lcd_driver_api *api =
		(const struct v85xxp_lcd_driver_api *)dev->api;
	return api->get_data(dev, idx);
}

/**
 * @brief Enable or disable the LCD controller.
 *
 * @param dev LCD device instance
 * @param enable true to enable, false to disable
 * @return 0 on success, negative on error
 */
static inline int v85xxp_lcd_enable(const struct device *dev, bool enable)
{
	const struct v85xxp_lcd_driver_api *api =
		(const struct v85xxp_lcd_driver_api *)dev->api;
	return api->enable(dev, enable);
}

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_DRIVERS_MISC_V85XXP_LCD_H_ */
