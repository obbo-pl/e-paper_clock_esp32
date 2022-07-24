/*
 * font_set.h
 *
 * Created on: 31 sty 2022
 *     Author: Krzysztof Markiewicz <obbo.pl>
 *
 * This program is distributed under the terms of the GNU General Public License
 */

#ifndef _FONT_SET_H_
#define _FONT_SET_H_


#include "lvgl.h"


LV_FONT_DECLARE(opensansb16px);
LV_FONT_DECLARE(opensansb20px);

LV_FONT_DECLARE(Ribeye230px);
LV_FONT_DECLARE(Ribeye260px);
LV_FONT_DECLARE(Ribeye48px);
LV_FONT_DECLARE(NewtSerif260px);
LV_FONT_DECLARE(NewtSerif300px);
LV_FONT_DECLARE(NewtSerif54px);
LV_FONT_DECLARE(TitilliumWeb230px);
LV_FONT_DECLARE(TitilliumWeb260px);
LV_FONT_DECLARE(TitilliumWeb48px);
LV_FONT_DECLARE(Yrsa280px);
LV_FONT_DECLARE(Yrsa330px);
LV_FONT_DECLARE(Yrsa48px);


#define FONT_STYLE_COUNT			4

enum {
	FONT_PURPOSE_TIME1,
	FONT_PURPOSE_TIME2,
	FONT_PURPOSE_DATE,
	FONT_PURPOSE_COUNT
};

lv_font_t *font_style[FONT_STYLE_COUNT][FONT_PURPOSE_COUNT] = {
	{&Ribeye230px, &Ribeye260px, &Ribeye48px},
	{&NewtSerif260px, &NewtSerif300px, &NewtSerif54px},
	{&TitilliumWeb230px, &TitilliumWeb260px, &TitilliumWeb48px},
	{&Yrsa280px, &Yrsa330px, &Yrsa48px}
};



#endif /* _FONT_SET_H_ */
