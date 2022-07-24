/*
 * owm_forecast.c
 *
 * Created on: 20 sty 2022
 *     Author: Krzysztof Markiewicz <obbo.pl>
 *
 * MIT License
 *
 * Copyright (c) 2021 Krzysztof Markiewicz
 */

#include "owm_forecast.h"
#include <string.h>
#include <esp_log.h>
#include "jsmn.h"


static const char *TAG = "OWM_forecast";


static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) return 0;
	return -1;
}

esp_err_t owm_forecast_get_icon(lv_img_dsc_t **icon, int weather_id, char pod)
{
	esp_err_t result = ESP_ERR_NOT_FOUND;
	for (int i = 0; i < OWM_FORECAST_WEATHER_ID_COUNT; i++) {
		if (weather_id_icon[i].id == weather_id) {
			if (pod == 'd') {
				*icon = (lv_img_dsc_t *)weather_id_icon[i].icon_day;
			} else {
				*icon = (lv_img_dsc_t *)weather_id_icon[i].icon_night;
			}
			result = ESP_OK;
			break;
		}
	}
	return result;
}

esp_err_t owm_forecast_decode(char *json, owm_forecast_t *forecast, char *buff, int size)
{
    esp_err_t result = ESP_OK;
	jsmn_parser p;
	jsmn_init(&p);

	jsmntok_t *t;
    memset(buff, 0x00, size);
	t = (jsmntok_t *)buff;
	int jsmn_token_count = (int)(size / sizeof(t[0]));

	ESP_LOGI(TAG, "JSMN buffer size: %d token(s)", jsmn_token_count);
	int r = jsmn_parse(&p, json, strlen(json), t, jsmn_token_count);
	if (r < 0) {
		switch (r) {
			case JSMN_ERROR_NOMEM:
				result = ESP_ERR_NO_MEM;
				ESP_LOGE(TAG, "Not enough tokens were provided");
				break;
			case JSMN_ERROR_INVAL:
				result = ESP_ERR_INVALID_ARG;
				ESP_LOGE(TAG, "Invalid character inside JSON string");
				break;
			case JSMN_ERROR_PART:
				result = ESP_ERR_INVALID_SIZE;
				ESP_LOGE(TAG, "The string is not a full JSON packet, more bytes expected");
				break;
			default:
				result = ESP_ERR_INVALID_RESPONSE;
				ESP_LOGE(TAG, "Unknown error code");
		}
	} else {
		ESP_LOGI(TAG, "JSMN found %d token(s)", r);
		int i = 0;
		int idx = 0;
		int w = 0;
		for (i = 1; i < r; i++) {
			if (jsoneq(json, &t[i], "list") == 0) {
				break;
			}
		}
		for (int j = i; j < r; j++) {
			if (jsoneq(json, &t[j], "dt") == 0) {
				j++;
				forecast->list[idx].dt = strtol(json + t[j].start, NULL, 10);
			} else if (jsoneq(json, &t[j], "temp") == 0) {
				j++;
				forecast->list[idx].main.temp = strtof(json + t[j].start, NULL);
			} else if (jsoneq(json, &t[j], "feels_like") == 0) {
				j++;
				forecast->list[idx].main.feels_like = strtof(json + t[j].start, NULL);
			} else if (jsoneq(json, &t[j], "pressure") == 0) {
				j++;
				forecast->list[idx].main.pressure = strtof(json + t[j].start, NULL);
			} else if (jsoneq(json, &t[j], "id") == 0) {
				j++;
				if (w < OWM_FORECAST_WEATHER_MAX_COUNT) {
					forecast->list[idx].weather[w].id = (int)strtol(json + t[j].start, NULL, 10);
					w++;
				}
			} else if (jsoneq(json, &t[j], "pod") == 0) {
				j++;
				forecast->list[idx].sys.pod = json[t[j].start];
			} else if (jsoneq(json, &t[j], "dt_txt") == 0) {
				idx++;
				w = 0;
				j++;
			}
			if (idx >= OWM_FORECAST_RECORD_MAX_COUNT) {
				i = j;
				break;
			}
		}
		for (int j = i; j < r; j++) {
			if (jsoneq(json, &t[j], "timezone") == 0) {
				j++;
				forecast->city.timezone = (int)strtol(json + t[j].start, NULL, 10);
				break;
			}
		}
	}
	return result;
}

