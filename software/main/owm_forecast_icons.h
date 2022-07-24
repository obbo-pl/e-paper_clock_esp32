/*
 * owm_forecast_icons.h
 *
 * Created on: 29 sty 2022
 *     Author: Krzysztof Markiewicz <obbo.pl>
 *
 * MIT License
 *
 * Copyright (c) 2021 Krzysztof Markiewicz
 */

#ifndef _OWM_FORECAST_ICONS_H_
#define _OWM_FORECAST_ICONS_H_


#include "lvgl.h"

LV_IMG_DECLARE(d01);
LV_IMG_DECLARE(d02);
LV_IMG_DECLARE(d03);
LV_IMG_DECLARE(d04);
LV_IMG_DECLARE(d09);
LV_IMG_DECLARE(d10);
LV_IMG_DECLARE(d11);
LV_IMG_DECLARE(d13);
LV_IMG_DECLARE(d50);
LV_IMG_DECLARE(n01);
LV_IMG_DECLARE(n02);
LV_IMG_DECLARE(n03);
LV_IMG_DECLARE(n04);
LV_IMG_DECLARE(n09);
LV_IMG_DECLARE(n10);
LV_IMG_DECLARE(n11);
LV_IMG_DECLARE(n13);
LV_IMG_DECLARE(n50);


/*
01d.c, 01n.c - clear sky
02d.c, 02n.c - few clouds
03d.c, 03n.c - scattered clouds
04d.c, 04n.c - broken clouds
09d.c, 09n.c - shower rain
10d.c, 10n.c - rain
11d.c, 11n.c - thunderstorm
13d.c, 13n.c - snow
50d.c, 50n.c - mist
*/


#define OWM_FORECAST_WEATHER_ID_COUNT			55


typedef struct {
	int id;
	const lv_img_dsc_t *icon_day;
	const lv_img_dsc_t *icon_night;
} owm_weather_id_t;


static const owm_weather_id_t weather_id_icon[OWM_FORECAST_WEATHER_ID_COUNT] = {
		// Thunderstorm
		{.id = 200, .icon_day = &d11, .icon_night = &n11},
		{.id = 201, .icon_day = &d11, .icon_night = &n11},
		{.id = 202, .icon_day = &d11, .icon_night = &n11},
		{.id = 210, .icon_day = &d11, .icon_night = &n11},
		{.id = 211, .icon_day = &d11, .icon_night = &n11},
		{.id = 212, .icon_day = &d11, .icon_night = &n11},
		{.id = 221, .icon_day = &d11, .icon_night = &n11},
		{.id = 230, .icon_day = &d11, .icon_night = &n11},
		{.id = 231, .icon_day = &d11, .icon_night = &n11},
		{.id = 232, .icon_day = &d11, .icon_night = &n11},
		// Drizzle
		{.id = 300, .icon_day = &d09, .icon_night = &n09},
		{.id = 301, .icon_day = &d09, .icon_night = &n09},
		{.id = 302, .icon_day = &d09, .icon_night = &n09},
		{.id = 310, .icon_day = &d09, .icon_night = &n09},
		{.id = 311, .icon_day = &d09, .icon_night = &n09},
		{.id = 312, .icon_day = &d09, .icon_night = &n09},
		{.id = 313, .icon_day = &d09, .icon_night = &n09},
		{.id = 314, .icon_day = &d09, .icon_night = &n09},
		{.id = 321, .icon_day = &d09, .icon_night = &n09},
		// Rain
		{.id = 500, .icon_day = &d10, .icon_night = &n10},
		{.id = 501, .icon_day = &d10, .icon_night = &n10},
		{.id = 502, .icon_day = &d10, .icon_night = &n10},
		{.id = 503, .icon_day = &d10, .icon_night = &n10},
		{.id = 504, .icon_day = &d10, .icon_night = &n10},
		{.id = 511, .icon_day = &d13, .icon_night = &n13},
		{.id = 520, .icon_day = &d09, .icon_night = &n09},
		{.id = 521, .icon_day = &d09, .icon_night = &n09},
		{.id = 522, .icon_day = &d09, .icon_night = &n09},
		{.id = 531, .icon_day = &d09, .icon_night = &n09},
		// Snow
		{.id = 600, .icon_day = &d13, .icon_night = &n13},
		{.id = 601, .icon_day = &d13, .icon_night = &n13},
		{.id = 602, .icon_day = &d13, .icon_night = &n13},
		{.id = 611, .icon_day = &d13, .icon_night = &n13},
		{.id = 612, .icon_day = &d13, .icon_night = &n13},
		{.id = 613, .icon_day = &d13, .icon_night = &n13},
		{.id = 615, .icon_day = &d13, .icon_night = &n13},
		{.id = 616, .icon_day = &d13, .icon_night = &n13},
		{.id = 620, .icon_day = &d13, .icon_night = &n13},
		{.id = 621, .icon_day = &d13, .icon_night = &n13},
		{.id = 622, .icon_day = &d13, .icon_night = &n13},
		// Atmosphere
		{.id = 700, .icon_day = &d50, .icon_night = &n50},
		{.id = 701, .icon_day = &d50, .icon_night = &n50},
		{.id = 702, .icon_day = &d50, .icon_night = &n50},
		{.id = 703, .icon_day = &d50, .icon_night = &n50},
		{.id = 704, .icon_day = &d50, .icon_night = &n50},
		{.id = 711, .icon_day = &d50, .icon_night = &n50},
		{.id = 720, .icon_day = &d50, .icon_night = &n50},
		{.id = 721, .icon_day = &d50, .icon_night = &n50},
		{.id = 722, .icon_day = &d50, .icon_night = &n50},
		{.id = 731, .icon_day = &d50, .icon_night = &n50},
		// Clear
		{.id = 800, .icon_day = &d01, .icon_night = &n01},
		// Clouds
		{.id = 801, .icon_day = &d02, .icon_night = &n02},
		{.id = 802, .icon_day = &d03, .icon_night = &n03},
		{.id = 803, .icon_day = &d04, .icon_night = &n04},
		{.id = 804, .icon_day = &d04, .icon_night = &n04}
};



#endif /* _OWM_FORECAST_ICONS_H_ */
