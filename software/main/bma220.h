/**
    @file    bma220.h
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

#ifndef _BMA220_H_
#define _BMA220_H_


#include "i2c_master.h"
#include "esp_err.h"


#define BMA220_I2C_ADDR				0x0A

// Register address (I2C)
#define BMA220_CHIPID				0x00
#define BMA220_REVISIONID			0x02
#define BMA220_ACCELERATION			0x04
#define BMA220_ACCELERATION_X		0x04
#define BMA220_ACCELERATION_Y		0x06
#define BMA220_ACCELERATION_Z		0x08
#define BMA220_FILTER				0x20
#define BMA220_FILTER_MASK			0x0F
#define BMA220_FILTER_COUNT			6
#define BMA220_FILTER_1kHz_REG 		0x0
#define BMA220_FILTER_1kHz_DELAY	2
#define BMA220_FILTER_500Hz_REG		0x1
#define BMA220_FILTER_500Hz_DELAY	2
#define BMA220_FILTER_250Hz_REG		0x2
#define BMA220_FILTER_250Hz_DELAY	3
#define BMA220_FILTER_125Hz_REG		0x3
#define BMA220_FILTER_125Hz_DELAY	5
#define BMA220_FILTER_64Hz_REG		0x4
#define BMA220_FILTER_64Hz_DELAY	9
#define BMA220_FILTER_32Hz_REG		0x5
#define BMA220_FILTER_32Hz_DELAY	17
typedef enum {
	BMA220_FILTER_1kHz,
	BMA220_FILTER_500Hz,
	BMA220_FILTER_250Hz,
	BMA220_FILTER_125Hz,
	BMA220_FILTER_64Hz,
	BMA220_FILTER_32Hz,
} bma220_filter_t;
#define BMA220_RANGE				0x22
#define BMA220_RANGE_MASK			0x03
#define BMA220_RANGE_2g				0x0
#define BMA220_RANGE_4g				0x1
#define BMA220_RANGE_8g				0x2
#define BMA220_RANGE_16g			0x3
#define BMA220_SOFTRESET			0x32

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

#define BMA220_CHIPID_VALUE			0xDD

typedef struct {
	int8_t x;
	int8_t y;
	int8_t z;
} bma220_accel_t;


typedef esp_err_t bma220_err_t;

#define BMA220_OK					ESP_OK
#define BMA220_ERR_INVALID_STATE	ESP_ERR_INVALID_STATE
#define BMA220_ERR_INVALID_ARG		ESP_ERR_INVALID_ARG

#define bma220_delay_msec(x)		do {            \
		vTaskDelay((x) / portTICK_PERIOD_MS);       \
	} while(0)

inline bma220_err_t bma220_i2c_read(uint8_t reg, uint8_t *data, uint8_t count)
{
	return (bma220_err_t)i2c_master_read_reg(I2C_PORT_NUM, BMA220_I2C_ADDR, reg, data, count);
}

inline bma220_err_t bma220_i2c_write(uint8_t reg, uint8_t *data, uint8_t count)
{
	return (bma220_err_t)i2c_master_write_reg(I2C_PORT_NUM, BMA220_I2C_ADDR, reg, data, count);
}


bma220_err_t bma220_get_chipid(uint8_t *chipid);
bma220_err_t bma220_reset();
bma220_err_t bma220_set_filter(bma220_filter_t value);
bma220_err_t bma220_set_range(uint8_t value);
bma220_err_t bma220_get_acceleration(uint8_t dir, int8_t *value);
bma220_err_t bma220_get_acceleration_xyz(bma220_accel_t *value);



#endif // _BMA220_H_
