/**
    @file    bma220.c
    @brief   BMA220 I2C Triple Axis Accelerometer
    @version 1.0
    @date    2021-12-04
    @author  Krzysztof Markiewicz <obbo.pl>


    @section LICENSE

    MIT License

    Copyright (c) 2021 Krzysztof Markiewicz

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute,
    sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "bma220.h"


static const uint8_t bma220_filter_reg[BMA220_FILTER_COUNT] = {
		BMA220_FILTER_1kHz_REG,
		BMA220_FILTER_500Hz_REG,
		BMA220_FILTER_250Hz_REG,
		BMA220_FILTER_125Hz_REG,
		BMA220_FILTER_64Hz_REG,
		BMA220_FILTER_32Hz_REG,
};
static const uint8_t bma220_filter_delay[BMA220_FILTER_COUNT] = {
		BMA220_FILTER_1kHz_DELAY,
		BMA220_FILTER_500Hz_DELAY,
		BMA220_FILTER_250Hz_DELAY,
		BMA220_FILTER_125Hz_DELAY,
		BMA220_FILTER_64Hz_DELAY,
		BMA220_FILTER_32Hz_DELAY,
};

bma220_t chip_config = {
		.int_config_bm = 0x0000,
};


bma220_err_t bma220_get_chipid(uint8_t *chipid)
{
	return bma220_i2c_read(BMA220_CHIPID, chipid, 1);
}

bma220_err_t bma220_reset()
{
	bma220_err_t result;
	uint8_t data;
	result = bma220_i2c_read(BMA220_SOFTRESET, &data, 1);
	if (result == BMA220_OK) {
		if (data != 0x00) return BMA220_ERR_INVALID_STATE;
		bma220_delay_msec(2);
		result = bma220_i2c_read(BMA220_SOFTRESET, &data, 1);
		if (result == BMA220_OK) {
			if (data != 0xff) return BMA220_ERR_INVALID_STATE;
			bma220_delay_msec(2);
		}
	}
	return result;
}

bma220_err_t bma220_reset_interrupt()
{
	uint8_t temp = (uint8_t)chip_config.int_config_bm;
	bma220_err_t result = bma220_i2c_write(BMA220_INTERRUPT_CONFIG, &temp, 1);
	if (result == BMA220_OK) {
		temp = (uint8_t)((chip_config.int_config_bm | BMA220_INTERRUPT_CONFIG_RESET_INT_bm) >> 8);
		result = bma220_i2c_write(BMA220_INTERRUPT_CONFIG + BMA220_I2C_INCREMENT_STEP, &temp, 1);
	}
	return result;
}

bma220_err_t bma220_set_interrupt_config(uint16_t config)
{
	chip_config.int_config_bm = config;
	return bma220_reset_interrupt();
}

bma220_err_t bma220_get_interrupt(uint16_t *value)
{
	return bma220_i2c_read(BMA220_INTERRUPT, (uint8_t*)value, 2);
}

bma220_err_t bma220_set_filter(bma220_filter_t value)
{
	bma220_err_t result = BMA220_OK;
	uint8_t filter = bma220_filter_reg[value] & BMA220_FILTER_MASK;
	result = bma220_i2c_write(BMA220_FILTER, &filter, 1);
	bma220_delay_msec(bma220_filter_delay[value]);
	return result;
}

bma220_err_t bma220_set_range(uint8_t value)
{
	value &= BMA220_RANGE_MASK;
	return bma220_i2c_write(BMA220_RANGE, &value, 1);
}

bma220_err_t bma220_get_acceleration(uint8_t dir, int8_t *value)
{
	bma220_err_t result = BMA220_OK;
	uint8_t temp_value;
	if ((dir == BMA220_ACCELERATION_X) || (dir == BMA220_ACCELERATION_Y) || (dir == BMA220_ACCELERATION_Z)) {
		result = bma220_i2c_read(dir, &temp_value, 1);
		if (result == BMA220_OK) *value = (int8_t)temp_value >> 2;
	} else return BMA220_ERR_INVALID_ARG;
	return result;
}

bma220_err_t bma220_get_acceleration_xyz(bma220_accel_t *value)
{
	bma220_err_t result;
	uint8_t data[3];
	result = bma220_i2c_read(BMA220_ACCELERATION, data, 3);
	if (result == BMA220_OK) {
		value->x = (int8_t)data[0] >> 2;
		value->y = (int8_t)data[1] >> 2;
		value->z = (int8_t)data[2] >> 2;
	}
	return result;
}
