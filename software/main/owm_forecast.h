/*
 * owm_forecast.h
 *
 * Created on: 20 sty 2022
 *     Author: Krzysztof Markiewicz <obbo.pl>
 *
 * MIT License
 *
 * Copyright (c) 2021 Krzysztof Markiewicz
 */

#ifndef _OWM_FORECAST_H_
#define _OWM_FORECAST_H_


#include "esp_err.h"
#include "owm_forecast_icons.h"


#define OWM_FORECAST_MINIMALISTIC

#ifdef OWM_FORECAST_MINIMALISTIC
#define OWM_FORECAST_RECORD_MAX_COUNT		24
#else
#define OWM_FORECAST_RECORD_MAX_COUNT		40
#endif
#define OWM_FORECAST_WEATHER_MAX_COUNT		3


typedef struct {
	float temp;
	float feels_like;
#ifndef OWM_FORECAST_MINIMALISTIC
	float temp_min;
	float temp_max;
#endif
	float pressure;
#ifndef OWM_FORECAST_MINIMALISTIC
	float sea_level;
	float grnd_level;
#endif
	float humidity;
#ifndef OWM_FORECAST_MINIMALISTIC
	float temp_kf;
#endif
} owm_forecast_main_t;

typedef struct {
	int id;
#ifndef OWM_FORECAST_MINIMALISTIC
	char *main;
	char *description;
	char *icon;
#endif
} owm_forecast_wreather_t;

typedef struct {
	int all;
} owm_forecast_clouds_t;

typedef struct {
	float speed;
	int deg;
	float gust;
} owm_forecast_wind_t;

typedef struct {
	float h3;
} owm_forecast_rain_t;

typedef struct {
	float h3;
} owm_forecast_snow_t;

typedef struct {
	char pod;
} owm_forecast_sys_t;

typedef struct {
	long int dt;
	owm_forecast_main_t main;
	owm_forecast_wreather_t weather[OWM_FORECAST_WEATHER_MAX_COUNT];
#ifndef OWM_FORECAST_MINIMALISTIC
	owm_forecast_clouds_t clouds;
	owm_forecast_wind_t wind;
	int visibility;
	float pop;
	owm_forecast_rain_t rain;
	owm_forecast_snow_t snow;
#endif
	owm_forecast_sys_t sys;
#ifndef OWM_FORECAST_MINIMALISTIC
	char dt_txt[20];
#endif
} owm_forecast_record_t;

typedef struct {
	float lat;
	float lon;
} owm_forecast_coord_t;

typedef struct {
#ifndef OWM_FORECAST_MINIMALISTIC
	long int id;
	char name[50];
	owm_forecast_coord_t coord;
	char country[3];
#endif
	int timezone;
#ifndef OWM_FORECAST_MINIMALISTIC
	long int sunrise;
	long int sunset;
#endif
} owm_forecast_city_t;

typedef struct {
#ifndef OWM_FORECAST_MINIMALISTIC
	char code[5];
	int message;
	int cnt;
#endif
	owm_forecast_record_t list[OWM_FORECAST_RECORD_MAX_COUNT];
	owm_forecast_city_t city;
} owm_forecast_t;


esp_err_t owm_forecast_decode(char *json, owm_forecast_t *forecast, char *buff, int size);
esp_err_t owm_forecast_get_icon(lv_img_dsc_t **icon, int weather_id, char pod);


#endif /* _OWM_FORECAST_H_ */
