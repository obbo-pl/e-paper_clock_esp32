/*
 * battery.h
 *
 * Created on: 31 sty 2022
 *     Author: Krzysztof Markiewicz <obbo.pl>
 *
 * This program is distributed under the terms of the GNU General Public License
 */

#ifndef _BATTERY_H_
#define _BATTERY_H_


#include "lvgl.h"


LV_IMG_DECLARE(battery_unknown);
LV_IMG_DECLARE(battery_charging);
LV_IMG_DECLARE(battery_empty);
LV_IMG_DECLARE(battery_quater);
LV_IMG_DECLARE(battery_half);
LV_IMG_DECLARE(battery_three_quaters);
LV_IMG_DECLARE(battery_full);


typedef enum {
	BATTERY_VOLTAGE_LEVEL_UNKNOWN,
	BATTERY_VOLTAGE_LEVEL_EMPTY,
	BATTERY_VOLTAGE_LEVEL_QUARTER,
	BATTERY_VOLTAGE_LEVEL_HALF,
	BATTERY_VOLTAGE_LEVEL_THREE_QUARTERS,
	BATTERY_VOLTAGE_LEVEL_FULL,
	BATTERY_CHARGING,
	BATTERY_ICONS_COUNT
} battery_level_t;

static const lv_img_dsc_t *battery_icons[BATTERY_ICONS_COUNT] = {
		&battery_unknown,
		&battery_empty,
		&battery_quater,
		&battery_half,
		&battery_three_quaters,
		&battery_full,
		&battery_charging
};


inline battery_level_t battery_level(int voltage, int v_min, int v_max, int charging)
{
	int hysteresis = 0.03 * v_max;
	int capacity = v_max - hysteresis - v_min;
	if (charging) voltage -= hysteresis;
	if (voltage <= 0)
		return BATTERY_VOLTAGE_LEVEL_UNKNOWN;
	else if (voltage >= (v_min + 0.9 * capacity))
		return BATTERY_VOLTAGE_LEVEL_FULL;
	else if (voltage >= (v_min + 0.63 * capacity))
		return BATTERY_VOLTAGE_LEVEL_THREE_QUARTERS;
	else if (voltage >= (v_min + 0.37 * capacity))
		return BATTERY_VOLTAGE_LEVEL_HALF;
	else if (voltage >= (v_min + 0.1 * capacity))
		return BATTERY_VOLTAGE_LEVEL_QUARTER;
	else return BATTERY_VOLTAGE_LEVEL_EMPTY;
}

#endif /* _BATTERY_H_ */
