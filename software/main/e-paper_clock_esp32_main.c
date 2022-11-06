/*
 * e-paper_clock_esp32
 *
 * Created on: 11 gru 2021
 *     Author: Krzysztof Markiewicz <obbo.pl>
 *
 * This program is distributed under the terms of the GNU General Public License
*/

#include <stdio.h>
#include <ctype.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include "soc/soc.h"
#include "soc/rtc.h"
#include <sys/time.h>
#include <esp_wifi.h>
#include <esp_sleep.h>
#include <esp_log.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_idf_version.h"
#include "driver/i2c.h"
#include "i2c_master.h"
#include "bma220.h"
#include "esp_http_client.h"
#include "esp_tls.h"
#include "owm_forecast.h"
#include "esp_err.h"
#include "esp_timer.h"
#include <inttypes.h>

#include "esp_event.h"
#include "freertos/event_groups.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "esp_sntp.h"

#include "lvgl.h"
#include "lvgl_helpers.h"
#include "epd_lut.h"
#include "font_set.h"

#include "battery.h"
#include "secrets.h"
#include "lang.h"

/*
 * Requirements:
 *	ESP IDF 4.3.1
 *	LVGL 7.x
 *	LVGL driver uc8179c (https://github.com/obbo-pl/lvgl_esp32_drivers/tree/uc8179c)
*/

#define EPCLOCK_VERSION_MAJOR      			"0"
#define EPCLOCK_VERSION_MINOR      			"9"
//#define MONITOR_FREE_SPACE
#define DISABLE_VBUS_WAKEUP

#define ADC_SAMPLES   						((int)64)
#define uS_TO_S_FACTOR 						(1000000ULL)

#define STRINGIZE_(x) 						#x
#define STRINGIZE(x) 						STRINGIZE_(x)
#ifdef CONFIG_LAYOUT_SHOW_FORECAST
#define EPCLOCK_OWM_UNIT					"metric"
#define EPCLOCK_OWM_URL 					"https://api.openweathermap.org/data/2.5/forecast" \
											"?lat=" CONFIG_OWM_FORECAST_LAT "&lon=" CONFIG_OWM_FORECAST_LON \
											"&cnt=" STRINGIZE(OWM_FORECAST_RECORD_MAX_COUNT) "&appid=" EPCLOCK_OWM_KEY \
											"&mode=json&units=" EPCLOCK_OWM_UNIT
#define EPCLOCK_OWM_BUFFER_SIZE				(CONFIG_OWM_FORECAST_BUFFER_SIZE * 1024)
#endif

#define WAKEUP_EXT1_PIN_BITMASK 			(1ULL << CONFIG_VBUS_VOLTAGE_CHECK)

#define BATTERY_VOLTAGE_MAX_MV          	(4200)
//#define BATTERY_VOLTAGE_MIN_MV        	(2500)
// ESP32 Wrover-E Recommended Power supply voltage min. (3.0V) + AP2112 Dropout Voltage (250mV)
#define BATTERY_VOLTAGE_MIN_MV          	(3250)
#define BATTERY_VOLTAGE_FACTOR				((float)2.135)
#define SENSOR_PRINT_INTERVAL				(20*uS_TO_S_FACTOR)
RTC_DATA_ATTR int battery_voltage_mv = -1;
RTC_DATA_ATTR battery_level_t battery_voltage_level = BATTERY_VOLTAGE_LEVEL_UNKNOWN;
RTC_DATA_ATTR int battery_charging_current_state = false;
RTC_DATA_ATTR int battery_charging_previous_state = false;
RTC_DATA_ATTR time_t battery_charging_start_time = 0;
RTC_DATA_ATTR bool battery_charging_change_detected = false;
int long long sensor_last_print = (-SENSOR_PRINT_INTERVAL);

RTC_DATA_ATTR owm_forecast_t forecast;

// tilt sensor
RTC_DATA_ATTR int tilt_sensor_current_state = CONFIG_TILT_SENSOR_LEVEL_OPEN;
RTC_DATA_ATTR int tilt_sensor_previous_state = CONFIG_TILT_SENSOR_LEVEL_OPEN;
RTC_DATA_ATTR int64_t tilt_sensor_last_change = 0;
uint32_t tilt_sensor_state_duration_msec = 0;
RTC_DATA_ATTR bool tilt_sensor_change_detected = false;

// USB
#define VBUS_CONNECTED   	    			(1)
RTC_DATA_ATTR int vbus_voltege_current_state = false;
RTC_DATA_ATTR int vbus_voltege_previous_state = false;
RTC_DATA_ATTR bool vbus_voltege_change_detected = false;

// wi-fi
#define WIFI_TIMEOUT_MSEC					(30000)
#define WIFI_MAXIMUM_RETRY_COUNT  			(3)
EventGroupHandle_t wifi_event_group;
#define WIFI_CONNECTED_BIT 					(BIT0)
#define WIFI_FAIL_BIT      					(BIT1)
int wifi_retry_count = 0;
bool tcpip_enabled = false;
esp_netif_t *netif_instance;

// SNTP
#define SNTP_UPDATE_INTERVAL 				(24*3600UL)
#define SNTP_UPDATE_RETRY       			(4*3600UL)
#define EPCLOCK_FIRST_SYNCHRO_RETRY			(300)
#define SNTP_TIMEOUT_SEC					(20)
RTC_DATA_ATTR time_t inet_next_connect_time = 0;
RTC_DATA_ATTR bool sntp_first_synchro_completed = false;

// LVGL
LV_IMG_DECLARE(white);
RTC_DATA_ATTR uint8_t font_style_set = 1;
#define LV_TICK_PERIOD_MS 					(10)
esp_timer_handle_t gui_periodic_timer;
bool gui_up_to_date = true;
#define EPCLOCK_COLOR_RED_HEX				(0x600000)
RTC_DATA_ATTR bool request_update_red = true;

#define GET_UP_EARLY						1	// [sec]

bool sensor_first_check_done = false;
bool gui_ready = false;

#define RETURN_ON_ERROR(x) do {                            			\
		esp_err_t result = x;                              			\
		if (result != ESP_OK) {                            			\
			ESP_LOGE(TAG, "%s", esp_err_to_name(result));  			\
			return (result);							   			\
		}                                                  			\
	} while(0)

#define GOTO_ON_ERROR(x,jump,ret) do {                     			\
		esp_err_t result = x;                              			\
		if (result != ESP_OK) {                            			\
			ESP_LOGE(TAG, "%s", esp_err_to_name(result));  			\
			ret = result;                                  			\
			goto jump;									   			\
		}                                                  			\
	} while(0)

#define LOG_ON_ERROR(func,x) do {                          			\
		esp_err_t result = x;                              			\
		if (result != ESP_OK) {                            			\
			ESP_LOGE(TAG, "%s: %s", func, esp_err_to_name(result)); \
		}                                                  			\
	} while(0)

static const adc_channel_t channel = ADC_CHANNEL_0;

// accelerometer
bma220_accel_t acceleration = {.x = 0, .y = 0, .z = 0};
bool accelerometer_present = false;
time_t accelerometer_int_event_time = 0;
#define BMA220_TRIGGER_LEVEL				(6)
#define ACCELERATION_SHAKE_BREAK_LENGTH		(40)
#define ACCELERATION_SHAKE_LENGTH 			(6)
#define ACCELERATION_TILT_LEFT	 			(-1)
#define ACCELERATION_TILT_NOT	 			(0)
#define ACCELERATION_TILT_RIGHT	 			(1)


lv_color_t* buf1;
char *http_response_buffer;
size_t dispaly_buffer_size;

esp_sleep_wakeup_cause_t wakeup_reason;

enum {
	EPCLOCK_DISPLAY_LUT_DEFAULT,
	EPCLOCK_DISPLAY_LUT_FULL_RED,
	EPCLOCK_DISPLAY_LUT_NO_RED,
};

int epclock_dispay_current_lut = EPCLOCK_DISPLAY_LUT_DEFAULT;
#define EPCLOCK_DISPALY_REFRESH_TIMEOUT		(30)
#define EPCLOCK_GUI_READY_TIMEOUT			(2)

#define EPCLOCK_OWM_FORECAST_COUNT			(8)
lv_obj_t *label_time;
#ifdef CONFIG_LAYOUT_SHOW_DATE
lv_obj_t *label_weekday;
lv_obj_t *label_date;
#endif
lv_obj_t *icon_battery;
lv_obj_t *icon_charging;
#ifdef CONFIG_LAYOUT_SHOW_FORECAST
lv_obj_t *cont_forecast[EPCLOCK_OWM_FORECAST_COUNT];
lv_obj_t *label_forecast_time[EPCLOCK_OWM_FORECAST_COUNT];
lv_obj_t *icon_forecast[EPCLOCK_OWM_FORECAST_COUNT];
lv_obj_t *label_forecast_temp[EPCLOCK_OWM_FORECAST_COUNT];
#endif

lv_style_t st_time;
lv_style_t st_day;
lv_style_t st_date;
lv_style_t st_forecast1;
lv_style_t st_forecast2;
lv_style_t st_container;

QueueHandle_t update_red_evt_queue = NULL;
QueueHandle_t acceleration_evt_queue = NULL;
SemaphoreHandle_t xSemaphore_gui;
SemaphoreHandle_t xSemaphore_sensor;


// function prototype
void IRAM_ATTR gpio_isr_handler(void* arg);
void print_welcome();
void print_wakeup_reason(esp_sleep_wakeup_cause_t reason);
void set_epaper_power(bool enable);
int read_battery_voltage();
void check_tilt_sensor();
void check_battery_charging();
void check_vbus_voltege();
void set_dispaly_lut(int lut);
esp_err_t sync_time();
esp_err_t update_forecast();
esp_err_t connect_inet();
esp_err_t init_wifi_sta();
esp_err_t timeout_sec(bool *condition, uint16_t delay_sec);
void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
esp_err_t http_event_handler(esp_http_client_event_t *evt);
void lv_tick_task(void *arg);
void init_gui_layout();
void guiTask(void *pvParameter);
void sensorTask(void *pvParameter);
void set_font_style_set(uint8_t style_set);
void gui_refresh_ready();
void set_style_set_color(lv_style_t *style, lv_color_t color_text, lv_color_t color_background);


static const char *TAG = "e-paper clock";

void app_main(void)
{
	esp_err_t err;
	gpio_config_t io_conf;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE ;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE ;
    io_conf.intr_type = GPIO_INTR_DISABLE ;
#if defined(CONFIG_HAVE_EPAPER_PWR) && (CONFIG_HAVE_EPAPER_PWR >= 0)
    io_conf.mode = GPIO_MODE_OUTPUT ;
    io_conf.pin_bit_mask = (1ULL << CONFIG_EPAPER_PWR);
    gpio_config(&io_conf);
    set_epaper_power(true);
#endif
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_0) | (1ULL << GPIO_NUM_2) | (1ULL << CONFIG_BATTERY_CHARGING_STATUS);
    gpio_config(&io_conf);
    lv_init();
    lvgl_driver_init();
    uc8179c_set_flush_ready_cb(gui_refresh_ready);
    uc8179c_set_palette(LV_COLOR_BLACK, lv_color_hex(EPCLOCK_COLOR_RED_HEX));
#if defined(CONFIG_HAVE_SENSOR_TILT) && (CONFIG_SENSOR_TILT >= 0)
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pin_bit_mask = (1ULL << CONFIG_SENSOR_TILT);
    gpio_config(&io_conf);
#endif
    io_conf.pin_bit_mask = (1ULL << CONFIG_VBUS_VOLTAGE_CHECK);
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpio_config(&io_conf);
#ifdef CONFIG_HAVE_SENSOR_ACCELERATION
    io_conf.pin_bit_mask = (1ULL << CONFIG_ACCELERATION_SENSOR_INTERRUPT);
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    gpio_config(&io_conf);
#endif
    gpio_install_isr_service(0);
    wakeup_reason = esp_sleep_get_wakeup_cause();
    gpio_isr_handler_add(CONFIG_ACCELERATION_SENSOR_INTERRUPT, gpio_isr_handler, (void*)CONFIG_ACCELERATION_SENSOR_INTERRUPT);
#if (3 * EPCLOCK_OWM_BUFFER_SIZE < DISP_BUF_SIZE)
    dispaly_buffer_size = DISP_BUF_SIZE;
#else
    dispaly_buffer_size = 3 * EPCLOCK_OWM_BUFFER_SIZE;
#endif
    buf1 = heap_caps_malloc(dispaly_buffer_size, MALLOC_CAP_DMA);
    memset(buf1, 0x00, dispaly_buffer_size);
    http_response_buffer = (char *)buf1;
    assert(buf1 != NULL);
    if ((wakeup_reason == ESP_SLEEP_WAKEUP_UNDEFINED) || (wakeup_reason == ESP_SLEEP_WAKEUP_ALL)) {
        print_welcome();
    }
    setenv("TZ", CONFIG_TIME_ZONE, 1);
    tzset();
    print_wakeup_reason(wakeup_reason);
    if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
        tilt_sensor_change_detected = true;
        tilt_sensor_current_state = CONFIG_TILT_SENSOR_LEVEL_CLOSE;
        tilt_sensor_previous_state = CONFIG_TILT_SENSOR_LEVEL_CLOSE;
    }
#if defined(CONFIG_HAVE_SENSOR_TILT) && (CONFIG_SENSOR_TILT >= 0)
    esp_sleep_enable_ext0_wakeup(CONFIG_SENSOR_TILT, CONFIG_TILT_SENSOR_LEVEL_CLOSE);
#endif
#ifndef DISABLE_VBUS_WAKEUP
    esp_sleep_enable_ext1_wakeup(WAKEUP_EXT1_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);
#endif
    if (esp_netif_init() == ESP_OK) {
    	tcpip_enabled = true;
    } else {
    	ESP_LOGE(TAG, "TCP/IP initialization has failed");
    }
    err = esp_event_loop_create_default();
    if (err != ESP_OK) ESP_LOGE(TAG, "Creating an event loop has failed ");
    acceleration_evt_queue = xQueueCreate(1, sizeof(uint8_t));
    update_red_evt_queue = xQueueCreate(1, sizeof(bool));
    TaskHandle_t sensorTask_handle;
    xTaskCreatePinnedToCore(sensorTask, "sensor", 2048, NULL, 0, &sensorTask_handle, 1);
    if ((wakeup_reason == ESP_SLEEP_WAKEUP_UNDEFINED) || (wakeup_reason == ESP_SLEEP_WAKEUP_ALL)) {
    	uc8179c_clear_screen();
    }
    TaskHandle_t guiTask_handle;
    xTaskCreatePinnedToCore(guiTask, "gui", 3072, NULL, 0, &guiTask_handle, 1);
    vTaskDelay(20 / portTICK_PERIOD_MS);
    uint32_t timeout_count = 50;
    while (((xSemaphore_sensor == NULL) || (xSemaphore_gui == NULL)) && timeout_count) {
    	vTaskDelay(10 / portTICK_PERIOD_MS);
    	timeout_count--;
    }
    if ((xSemaphore_sensor == NULL) || (xSemaphore_gui == NULL)) ESP_LOGE(TAG, "At least one semaphore creation has failed");
    uint32_t sleep_duration;
    bool sleep_long = false;
    bool sleep_skip;
    while (1)
    {
        sleep_skip = false;
        if (!sntp_first_synchro_completed) connect_inet();
        if (sntp_first_synchro_completed) {
			ESP_LOGI(TAG, "Waiting for GUI ready");
			LOG_ON_ERROR("gui ready", timeout_sec(&gui_ready, EPCLOCK_GUI_READY_TIMEOUT));
			if (gui_ready) {
				time_t now;
				struct tm timeinfo;
				time(&now);
				localtime_r(&now, &timeinfo);
				while (1) {
					time(&now);
					localtime_r(&now, &timeinfo);
#if ((GET_UP_EARLY + EPCLOCK_DISPALY_REFRESH_TIMEOUT) >= 59)
#error (GET_UP_EARLY + EPCLOCK_DISPALY_REFRESH_TIMEOUT) should be less than 59
#endif
					if (timeinfo.tm_sec < (59 - (GET_UP_EARLY + EPCLOCK_DISPALY_REFRESH_TIMEOUT))) break;
					vTaskDelay(50 / portTICK_PERIOD_MS);
				};
				char str_buf[64];
				strftime(str_buf, sizeof(str_buf), "%c", &timeinfo);
				ESP_LOGI(TAG, "The current date/time is: %s", str_buf);
				if (pdTRUE == xSemaphoreTake(xSemaphore_sensor, 200 / portTICK_PERIOD_MS )) {
#if defined(CONFIG_HAVE_SENSOR_TILT)
					if ((tilt_sensor_current_state == CONFIG_TILT_SENSOR_LEVEL_CLOSE) && (tilt_sensor_state_duration_msec > 3000)) {
#endif
#if defined(CONFIG_HAVE_SENSOR_ACCELERATION)
						// tilt to the left
						if (acceleration.x > BMA220_TRIGGER_LEVEL) {
							font_style_set++;
							if (font_style_set >= FONT_STYLE_COUNT) font_style_set = 0;
						}
						// tilt to the right
						if (acceleration.x < -BMA220_TRIGGER_LEVEL) {
							if (font_style_set == 0) font_style_set = FONT_STYLE_COUNT;
							font_style_set--;
						}
						set_font_style_set(font_style_set);
#else
						font_style_set++;
						if (font_style_set >= FONT_STYLE_COUNT) font_style_set = 0;
						set_font_style_set(font_style_set);
#endif
#if defined(CONFIG_HAVE_SENSOR_TILT)
					}
#endif
					xSemaphoreGive(xSemaphore_sensor);
				}
				sprintf(str_buf, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
				lv_label_set_text(label_time, str_buf);
#ifdef CONFIG_LAYOUT_SHOW_DATE
				lv_label_set_text(label_weekday, day_name[timeinfo.tm_wday]);
				sprintf(str_buf, "%d %s, ", timeinfo.tm_mday, month_name[timeinfo.tm_mon]);
				lv_label_set_text(label_date, str_buf);
				if (timeinfo.tm_wday == 0) {
					set_style_set_color(&st_day, lv_color_hex(EPCLOCK_COLOR_RED_HEX), LV_COLOR_WHITE);
					request_update_red = true;
				}
#endif
				if ((vbus_voltege_current_state == VBUS_CONNECTED) || (battery_voltage_level == BATTERY_VOLTAGE_LEVEL_EMPTY)) {
					lv_img_set_src(icon_battery, battery_icons[battery_voltage_level]);
				} else {
					lv_img_set_src(icon_battery, &white);
				}
				if (battery_charging_current_state) {
					lv_img_set_src(icon_charging, battery_icons[BATTERY_CHARGING]);
				} else {
					lv_img_set_src(icon_charging, &white);
				}
#ifdef CONFIG_LAYOUT_SHOW_FORECAST
				int wf = 0;
				for (int i = 0; i < OWM_FORECAST_RECORD_MAX_COUNT; i++) {
					if (forecast.list[i].dt >= now) {
						time_t local_dt = forecast.list[i].dt + forecast.city.timezone;
						int h = (int)((local_dt % 86400) / 3600);
						int m = (int)((local_dt % 3600) / 60);
						sprintf(str_buf, "%d:%02d", h, m);
						lv_label_set_text(label_forecast_time[wf], str_buf);
						lv_img_dsc_t *icon = NULL;
						err = owm_forecast_get_icon(&icon, forecast.list[i].weather[0].id, forecast.list[i].sys.pod);
						if (err == ESP_OK) {
							lv_img_set_src(icon_forecast[wf], icon);
						} else {
							lv_img_set_src(icon_forecast[wf], &white);
						}
						sprintf(str_buf, "%d%c%cC", (int)forecast.list[i].main.temp, 0xC2, 0xB0);
						lv_label_set_text(label_forecast_temp[wf], str_buf);
						wf ++;
						if (wf >= EPCLOCK_OWM_FORECAST_COUNT) break;
					}
				}
#endif
#ifdef MONITOR_FREE_SPACE
			    lv_mem_monitor_t mon;
			    lv_mem_monitor(&mon);
			    ESP_LOGI(TAG, "LVGL mem used: %d (%d %%), frag: %d %%, biggest free: %d",
			    		(int)mon.total_size - mon.free_size,
			            mon.used_pct,
			            mon.frag_pct,
			            (int)mon.free_biggest_size);
#endif
				if (update_red_evt_queue != 0) xQueueReceive(update_red_evt_queue, &request_update_red, 0);
				if ((timeinfo.tm_hour != 3)) {
					if (request_update_red) {
						set_dispaly_lut(EPCLOCK_DISPLAY_LUT_FULL_RED);
						request_update_red = false;
					} else {
						set_dispaly_lut(EPCLOCK_DISPLAY_LUT_NO_RED);
					}
				} else {
					set_dispaly_lut(EPCLOCK_DISPLAY_LUT_DEFAULT);
				}
				gui_up_to_date = false;
				ESP_LOGI(TAG, "New job fired");
			}
			time_t refresh_display_start = time(NULL);
			if (inet_next_connect_time < time(NULL)) connect_inet();
			if (gui_ready) {
				ESP_LOGI(TAG, "Waiting for GUI refresh");
				LOG_ON_ERROR("gui up-to-date", timeout_sec(&gui_up_to_date, EPCLOCK_DISPALY_REFRESH_TIMEOUT));
			}
			if (gui_up_to_date) ESP_LOGI(TAG, "GUI refreshed in %lds", time(NULL) - refresh_display_start);
        }
		LOG_ON_ERROR("sensor check", timeout_sec(&sensor_first_check_done, 1));
#if defined(CONFIG_HAVE_SENSOR_ACCELERATION)
		// X.shake
		uint32_t acceleration_shake = 0;
		xQueueReceive(acceleration_evt_queue, &acceleration_shake, 0);
		if (acceleration_shake) {
			inet_next_connect_time = time(NULL);
		}
		// interrupt
		if (gpio_get_level(CONFIG_ACCELERATION_SENSOR_INTERRUPT)) {
			if (((esp_timer_get_time() - accelerometer_int_event_time) / 1000) > 3000){
				// forward tilt
				if (acceleration.y > BMA220_TRIGGER_LEVEL) {
					sleep_long = true;
				}
				// tilting backwards
				if (acceleration.y < -BMA220_TRIGGER_LEVEL) {
					// TODO add an action, change the layout
				}
			} else {
				sleep_skip = true;
			}
		}
#endif
#ifndef DISABLE_VBUS_WAKEUP
        if ((tilt_sensor_current_state == CONFIG_TILT_SENSOR_LEVEL_CLOSE) || (vbus_voltege_current_state == VBUS_CONNECTED)) {
#else
        if (tilt_sensor_current_state == CONFIG_TILT_SENSOR_LEVEL_CLOSE) {
#endif
        	sleep_skip = true;
        }
#ifdef MONITOR_FREE_SPACE
		ESP_LOGI(TAG, "GUI: free stack space %u byte(s)", uxTaskGetStackHighWaterMark(guiTask_handle));
		ESP_LOGI(TAG, "Sensor: free stack space %u byte(s)", uxTaskGetStackHighWaterMark(sensorTask_handle));
#endif
        if (sleep_skip) {
			sleep_duration = 60 - time(NULL)%60;
			if (sleep_duration > GET_UP_EARLY) sleep_duration -= GET_UP_EARLY;
			ESP_LOGI(TAG, "Waiting %us for a minute change", sleep_duration);
			wakeup_reason = ESP_SLEEP_WAKEUP_TIMER;
			sleep_long = false;
			vTaskDelay(1000 * sleep_duration / portTICK_PERIOD_MS);
        } else {
			goto go_sleep;
        }
    }
go_sleep:
	if (sleep_long) {
		sleep_duration = 0xFFFFFFFF;
		uc8179c_clear_screen();
	} else if (!sntp_first_synchro_completed) {
       	sleep_duration = EPCLOCK_FIRST_SYNCHRO_RETRY;
    } else {
		sleep_duration = 60 - time(NULL)%60;
		if (sleep_duration > GET_UP_EARLY) sleep_duration -= GET_UP_EARLY;
    }
	if (pdTRUE == xSemaphoreTake(xSemaphore_gui, 1000 * EPCLOCK_DISPALY_REFRESH_TIMEOUT / portTICK_PERIOD_MS )) {}
	set_epaper_power(false);
	if (esp_timer_is_active(gui_periodic_timer)) esp_timer_stop(gui_periodic_timer);
	if (guiTask_handle != NULL) vTaskDelete(guiTask_handle);
	if (pdTRUE == xSemaphoreTake(xSemaphore_sensor, 200 / portTICK_PERIOD_MS )) {}
	if (sensorTask_handle != NULL) vTaskDelete(sensorTask_handle);
	if (update_red_evt_queue != 0) xQueueReceive(update_red_evt_queue, &request_update_red, 0);
	ESP_LOGI(TAG, "Going to sleep for %us", sleep_duration);
    esp_sleep_enable_timer_wakeup(sleep_duration * uS_TO_S_FACTOR);
	esp_deep_sleep_start();
}

void IRAM_ATTR gpio_isr_handler(void* arg)
{
	accelerometer_int_event_time = esp_timer_get_time();
}

esp_err_t timeout_sec(bool *condition, uint16_t delay_sec)
{
	uint16_t tic_to_sec = 20;
	uint32_t timeout_count = tic_to_sec * delay_sec;
	while (!(*condition) && timeout_count) {
		vTaskDelay((1000 / tic_to_sec) / portTICK_PERIOD_MS);
		timeout_count--;
	}
	return ((*condition) ? ESP_OK : ESP_ERR_TIMEOUT);
}

void sensorTask(void *pvParameter)
{
	(void) pvParameter;
	static const char *TAG = "sensors";
	ESP_LOGI(TAG, "Running sensors task");
	xSemaphore_sensor = xSemaphoreCreateMutex();
	int acceleration_shake_prev = ACCELERATION_TILT_NOT;
	uint8_t acceleration_shake_count = 0;
	uint8_t acceleration_shake_break = 0;
	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

#ifdef CONFIG_HAVE_SENSOR_ACCELERATION
	i2c_master_init();
	vTaskDelay(2 / portTICK_PERIOD_MS); // BMA220 start-up time = 1.5ms
	LOG_ON_ERROR("BMA220 reset", bma220_reset());
	uint8_t chipid;
	if (bma220_get_chipid(&chipid) == ESP_OK) {
		if (chipid == BMA220_CHIPID_VALUE) {
			accelerometer_present = true;
			ESP_LOGI(TAG, "BMA220 acceleration sensor detected");
			LOG_ON_ERROR("BMA220 set range", bma220_set_range(BMA220_RANGE_2g));
			LOG_ON_ERROR("BMA220 set filter", bma220_set_filter(BMA220_FILTER_250Hz));
			LOG_ON_ERROR("BMA220 set interrupt", bma220_set_interrupt_config(
					BMA220_INTERRUPT_CONFIG_LAT_PERMANENTLY_bm |
					BMA220_INTERRUPT_CONFIG_ORIENT_EN_bm));
		}
	}
#endif
	while(1) {
		if (pdTRUE == xSemaphoreTake(xSemaphore_sensor, portMAX_DELAY)) {
#ifdef CONFIG_HAVE_SENSOR_TILT
			// check tilt
			check_tilt_sensor();
			if (tilt_sensor_change_detected) {
				if (tilt_sensor_current_state == CONFIG_TILT_SENSOR_LEVEL_CLOSE) {
					ESP_LOGI(TAG, "Tilt sensor: closed");
				} else {
					ESP_LOGI(TAG, "Tilt sensor: open");
				}
				tilt_sensor_change_detected = false;
			}
#endif
			// check USB supply
			check_vbus_voltege();
			if (vbus_voltege_change_detected) {
				if (vbus_voltege_current_state == VBUS_CONNECTED) {
					ESP_LOGI(TAG, "VBUS connected");
				} else {
					ESP_LOGI(TAG, "VBUS disconnected");
				}
				vbus_voltege_change_detected = false;
			}
			// battery voltage
			battery_voltage_mv = read_battery_voltage();
			battery_voltage_level = battery_level(battery_voltage_mv, BATTERY_VOLTAGE_MIN_MV, BATTERY_VOLTAGE_MAX_MV, battery_charging_current_state);
			// charging state
			check_battery_charging();
			if ((battery_charging_current_state) && (update_red_evt_queue != 0)) {
				xQueueSend(update_red_evt_queue, &battery_charging_current_state, 0);
			}
			if (battery_charging_change_detected) {
				if (battery_charging_current_state) {
					ESP_LOGI(TAG, "The battery is charging");
				} else {
					ESP_LOGI(TAG, "The battery is not charging");
				}
				battery_charging_change_detected = false;
			}
			// BMA220 acceleration sensor
			if (accelerometer_present) {
				LOG_ON_ERROR("BMA220 get acceleration", bma220_get_acceleration_xyz(&acceleration));
				if ((acceleration.x < BMA220_TRIGGER_LEVEL) && (acceleration.x > -BMA220_TRIGGER_LEVEL)) {
					acceleration_shake_break++;
					if (acceleration_shake_break > ACCELERATION_SHAKE_BREAK_LENGTH) {
						acceleration_shake_count = 0;
						acceleration_shake_prev = ACCELERATION_TILT_NOT;
					}
				}
				if (uxQueueMessagesWaiting(acceleration_evt_queue) == 0) {
					if ((acceleration.x > BMA220_TRIGGER_LEVEL) && (acceleration_shake_prev != ACCELERATION_TILT_LEFT)) {
						acceleration_shake_count++;
						acceleration_shake_prev = ACCELERATION_TILT_LEFT;
						acceleration_shake_break = 0;
					}
					if ((acceleration.x < -BMA220_TRIGGER_LEVEL) && (acceleration_shake_prev != ACCELERATION_TILT_RIGHT)) {
						acceleration_shake_count++;
						acceleration_shake_prev = ACCELERATION_TILT_RIGHT;
						acceleration_shake_break = 0;
					}
					if (acceleration_shake_count >= ACCELERATION_SHAKE_LENGTH) {
						xQueueSend(acceleration_evt_queue, &acceleration_shake_count, 0);
						acceleration_shake_count = 0;
						acceleration_shake_prev = ACCELERATION_TILT_NOT;
						ESP_LOGI(TAG, "Shake detected");
					}
				}
			}
			sensor_first_check_done = true;
			// print summary
			if (((esp_timer_get_time() - sensor_last_print) > SENSOR_PRINT_INTERVAL)) {
				if (battery_voltage_level == BATTERY_VOLTAGE_LEVEL_UNKNOWN) {
					ESP_LOGW(TAG, "Battery voltage: unknown");
				} else if (battery_voltage_level == BATTERY_VOLTAGE_LEVEL_EMPTY) {
					ESP_LOGW(TAG, "Battery voltage: %dmV, is charging: %s", battery_voltage_mv, (battery_charging_current_state) ? "yes" : "no");
				} else {
					ESP_LOGI(TAG, "Battery voltage: %dmV, is charging: %s", battery_voltage_mv, (battery_charging_current_state) ? "yes" : "no");
				}
				if (sntp_first_synchro_completed) {
					if (battery_charging_current_state) ESP_LOGI(TAG, "Charging duration: %llis", (long long int)(time(NULL) - battery_charging_start_time));
				}
				if (accelerometer_present) ESP_LOGI(TAG, "BMA220 x=%i, y=%i, z=%i", acceleration.x, acceleration.y, acceleration.z);
				sensor_last_print = esp_timer_get_time();
			}
		}
		xSemaphoreGive(xSemaphore_sensor);
		vTaskDelay(50 / portTICK_PERIOD_MS);
	}
}

void set_epaper_power(bool enable)
{
#if defined(CONFIG_HAVE_EPAPER_PWR) && (CONFIG_HAVE_EPAPER_PWR >= 0)
    if (enable) {
    	gpio_set_level(CONFIG_EPAPER_PWR, 0);
    } else {
    	gpio_set_level(CONFIG_EPAPER_PWR, 1);
    }
#endif
}

int read_battery_voltage()
{
	int long adc_raw = 0;
    for (int i = 0; i < ADC_SAMPLES; i++) {
            adc_raw += adc1_get_raw((adc1_channel_t)channel);
    }
    adc_raw /= ADC_SAMPLES;
    return (int)(BATTERY_VOLTAGE_FACTOR * (3.3 * adc_raw / 4.095));
}

void check_battery_charging()
{
	battery_charging_current_state = !gpio_get_level(CONFIG_BATTERY_CHARGING_STATUS);
    if (battery_charging_current_state != battery_charging_previous_state) {
    	battery_charging_change_detected = true;
    	battery_charging_previous_state = battery_charging_current_state;
    }
    if (!battery_charging_current_state) {
    	battery_charging_start_time = 0;
    } else if (sntp_first_synchro_completed && battery_charging_start_time == 0) {
    	battery_charging_start_time = time(NULL);
    }
}

void check_tilt_sensor()
{
#if defined(CONFIG_HAVE_SENSOR_TILT) && (CONFIG_SENSOR_TILT >= 0)
    tilt_sensor_current_state = gpio_get_level(CONFIG_SENSOR_TILT);
    if (tilt_sensor_current_state != tilt_sensor_previous_state) {
        tilt_sensor_last_change = esp_timer_get_time();
        tilt_sensor_change_detected = true;
        tilt_sensor_previous_state = tilt_sensor_current_state;
    }
    tilt_sensor_state_duration_msec = (uint32_t)((esp_timer_get_time() - tilt_sensor_last_change) / 1000);
#endif
}

void check_vbus_voltege()
{
	vbus_voltege_current_state = gpio_get_level(CONFIG_VBUS_VOLTAGE_CHECK);
    if (vbus_voltege_current_state != vbus_voltege_previous_state) {
    	vbus_voltege_change_detected = true;
    	vbus_voltege_previous_state = vbus_voltege_current_state;
    }
}

void print_wakeup_reason(esp_sleep_wakeup_cause_t reason)
{
    switch(reason) {
        case ESP_SLEEP_WAKEUP_ALL       : ESP_LOGI(TAG, "Not a wakeup cause"); break;
        case ESP_SLEEP_WAKEUP_EXT0      : ESP_LOGI(TAG, "Wakeup caused by external signal using RTC_IO"); break;
        case ESP_SLEEP_WAKEUP_EXT1      : ESP_LOGI(TAG, "Wakeup caused by external signal using RTC_CNTL"); break;
        case ESP_SLEEP_WAKEUP_TIMER     : ESP_LOGI(TAG, "Wakeup caused by timer"); break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD  : ESP_LOGI(TAG, "Wakeup caused by touchpad"); break;
        case ESP_SLEEP_WAKEUP_ULP       : ESP_LOGI(TAG, "Wakeup caused by ULP program"); break;
        case ESP_SLEEP_WAKEUP_GPIO      : ESP_LOGI(TAG, "Wakeup caused by GPIO"); break;
        case ESP_SLEEP_WAKEUP_UART      : ESP_LOGI(TAG, "Wakeup caused by UART"); break;
        default                         : ESP_LOGI(TAG, "Wakeup was not caused by deep sleep"); break; // ESP_SLEEP_WAKEUP_UNDEFINED
    }
}

void print_welcome()
{
	unsigned char mac[6] = {0};
	esp_read_mac(mac, ESP_MAC_WIFI_STA);
	printf("\n");
	printf("*********************************************************** \n");
	printf("  obbo.pl e-paper clock %s.%s \n", EPCLOCK_VERSION_MAJOR, EPCLOCK_VERSION_MINOR);
	printf("  ESP-IDF v%u.%u.%u \n", ESP_IDF_VERSION_MAJOR, ESP_IDF_VERSION_MINOR, ESP_IDF_VERSION_PATCH);
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    static const char *chip_model;
    switch (chip_info.model) {
		case CHIP_ESP32:
			chip_model = "ESP32";
			break;
		case CHIP_ESP32S2:
			chip_model = "ESP32-S2";
			break;
		case CHIP_ESP32S3:
			chip_model = "ESP32-S3";
			break;
		case CHIP_ESP32C3:
			chip_model = "ESP32-C3";
			break;
		default:
			chip_model = "Unknown chip";
    }
    printf("  %s with %d CPU core(s), %s%s%s\x8, revision %d \n",
    		chip_model,
			chip_info.cores,
			(chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
            (chip_info.features & CHIP_FEATURE_BT) ? "BT/" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "BLE/" : "",
            chip_info.revision);
    printf("  %dMB %s flash \n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    printf("  Minimum free heap size: %d bytes \n", esp_get_minimum_free_heap_size());
	printf("  Main XTAL frequency: %uMHz \n", rtc_clk_xtal_freq_get());
    rtc_cpu_freq_config_t freq_conf;
    rtc_clk_cpu_freq_get_config(&freq_conf);
    printf("  CPU frequency: %uMHz \n", freq_conf.freq_mhz);
	if (rtc_clk_32k_enabled()) printf("  RTC 32k XTAL oscillator has been enabled \n");
	printf("  Base MAC address: %02X:%02X:%02X:%02X:%02X:%02X \n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    printf("  Waveshare e-Paper %s %ux%upx \n", "UC8179C", LV_HOR_RES_MAX, LV_VER_RES_MAX);
#ifdef LV_DRIVER_SUPPORT_READ_DATA
	uint8_t rev[7];
    uc8179c_get_revision(rev);
    printf("  Revision: %02X%02X%02X-%02X%02X%02X-%02X \n", rev[0], rev[1], rev[2], rev[3], rev[4], rev[5], rev[6]);
    printf("  Temperature: %d%c%cC \n", uc8179c_get_temperature_raw(), 0xC2, 0xB0);
#endif
    nvs_stats_t nvs_stats;
    if (nvs_get_stats(NULL, &nvs_stats) == ESP_OK) {
    	printf("  NVS total: %d, used: %d \n", nvs_stats.total_entries, nvs_stats.used_entries );
    }
    printf("*********************************************************** \n");
}

esp_err_t connect_inet()
{
	esp_err_t result = ESP_OK;
	if (tcpip_enabled) {
		esp_err_t result = init_wifi_sta();
		if (result == ESP_OK) {
			esp_err_t err;
			err = sync_time();
			if (err != ESP_OK) result = err;
			err = update_forecast();
			if (err != ESP_OK) result = err;
		}
		LOG_ON_ERROR("wifi disconnect", esp_wifi_disconnect());
		LOG_ON_ERROR("wifi stop", esp_wifi_stop());
	    esp_netif_destroy(netif_instance);
	    vEventGroupDelete(wifi_event_group);
	} else result = ESP_ERR_ESP_NETIF_IF_NOT_READY;
	time_t current_time = time(NULL);
	if (result == ESP_OK) {
		inet_next_connect_time = current_time + SNTP_UPDATE_INTERVAL;
	} else inet_next_connect_time = time(NULL) + SNTP_UPDATE_RETRY;
	return result;
}

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
	static const char *TAG = "wifi event";
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (wifi_retry_count < WIFI_MAXIMUM_RETRY_COUNT) {
            ESP_LOGI(TAG, "Retry to connect to the AP");
            wifi_retry_count++;
            esp_wifi_connect();
        } else {
            ESP_LOGW(TAG,"Connect to the AP fail");
            xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "Got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        wifi_retry_count = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

esp_err_t init_wifi_sta()
{
	esp_err_t result = ESP_OK;
	static const char *TAG = "wifi sta";
    ESP_LOGI(TAG, "Initializing STA...");

    wifi_event_group = xEventGroupCreate();
    if (wifi_event_group == NULL) return ESP_FAIL;

    netif_instance = esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    GOTO_ON_ERROR(esp_wifi_init(&cfg), err, result);
    GOTO_ON_ERROR(esp_wifi_set_storage(WIFI_STORAGE_RAM), err, result);
    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    GOTO_ON_ERROR(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &instance_any_id), err, result);
    GOTO_ON_ERROR(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &instance_got_ip), err, result);
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = ESP_WIFI_SSID,
            .password = ESP_WIFI_PASS,
 	        .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                .capable = true,
                .required = false
            },
        },
    };
    GOTO_ON_ERROR(esp_wifi_set_mode(WIFI_MODE_STA), err, result);
    GOTO_ON_ERROR(esp_wifi_set_config(WIFI_IF_STA, &wifi_config), err, result);
    GOTO_ON_ERROR(esp_wifi_start(), err, result);
    ESP_LOGI(TAG, "Initialization STA finished.");
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group,
    		WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, (WIFI_TIMEOUT_MSEC / portTICK_PERIOD_MS));
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "Connected to AP SSID:%s", ESP_WIFI_SSID);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGW(TAG, "Failed to connect to SSID:%s", ESP_WIFI_SSID);
        result = ESP_ERR_WIFI_NOT_CONNECT;
    } else {
        ESP_LOGE(TAG, "Operation timed out");
        result = ESP_ERR_WIFI_TIMEOUT;
    }
err:
	ESP_LOGI(TAG, "Leaving STA");
    RETURN_ON_ERROR(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
    RETURN_ON_ERROR(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
    return result;
}

esp_err_t sync_time()
{
	esp_err_t result = ESP_OK;
	static const char *TAG = "sntp";
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, CONFIG_NTP_SERVER);
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_init();
    uint16_t tic_to_sec = 5;
    sntp_sync_status_t sync_status;
    uint16_t check_count = tic_to_sec * SNTP_TIMEOUT_SEC;
    do {
        if (check_count%tic_to_sec == 0) ESP_LOGI(TAG, "Waiting for system time to be set... (%ds)", (check_count / tic_to_sec));
        vTaskDelay((1000 / tic_to_sec) / portTICK_PERIOD_MS);
        check_count--;
        sync_status = sntp_get_sync_status();
    } while (sync_status != SNTP_SYNC_STATUS_COMPLETED && check_count);
    if (sync_status) {
    	ESP_LOGI(TAG, "SNTP synchronization completed");
    	sntp_first_synchro_completed = true;
    } else {
    	ESP_LOGW(TAG, "SNTP synchronization timeout");
    	result = ESP_ERR_TIMEOUT;
    }
    sntp_stop();
    return result;
}

esp_err_t update_forecast()
{
	esp_err_t result = ESP_OK;
#ifdef CONFIG_LAYOUT_SHOW_FORECAST
	memset(http_response_buffer, 0x00, EPCLOCK_OWM_BUFFER_SIZE);
	int content_length;
	esp_http_client_config_t http_config = {
			.url = EPCLOCK_OWM_URL,
		    .auth_type = HTTP_AUTH_TYPE_NONE,
			.event_handler = http_event_handler,
			.user_data = http_response_buffer,
			.disable_auto_redirect = true,
			.timeout_ms=4000,
	};
	esp_http_client_handle_t http_client = esp_http_client_init(&http_config);
	if (http_client != NULL) {
	    ESP_LOGI(TAG, "HTTP response buffer size = %d", EPCLOCK_OWM_BUFFER_SIZE);
		esp_http_client_set_method(http_client, HTTP_METHOD_GET);
	    esp_err_t err = esp_http_client_open(http_client, 0);
	    if (err != ESP_OK) {
	        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
	        result = ESP_ERR_HTTP_CONNECT;
	    } else {
	    	content_length = esp_http_client_fetch_headers(http_client);
	        if (content_length < 0) {
	            ESP_LOGE(TAG, "HTTP client fetch headers failed");
	            result = ESP_ERR_HTTP_FETCH_HEADER;
	        } else if (content_length >= EPCLOCK_OWM_BUFFER_SIZE){
	        	ESP_LOGE(TAG, "HTTP buffer is too small");
	        	result = ESP_ERR_INVALID_SIZE;
	        } else {
	        	int data_read = esp_http_client_read_response(http_client, http_response_buffer, EPCLOCK_OWM_BUFFER_SIZE);
				if (data_read >= 0) {
					ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
					esp_http_client_get_status_code(http_client),
					esp_http_client_get_content_length(http_client));
					result = owm_forecast_decode(http_response_buffer,
							&forecast, http_response_buffer + EPCLOCK_OWM_BUFFER_SIZE,
							dispaly_buffer_size - EPCLOCK_OWM_BUFFER_SIZE);
				} else {
					ESP_LOGE(TAG, "Failed to read response");
					result = ESP_ERR_INVALID_SIZE;
				}
	        }
        }
	    esp_http_client_close(http_client);
	} else result = ESP_FAIL;

	esp_http_client_cleanup(http_client);
#endif
    return result;

}

esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    static char *output_buffer;
    static int output_len;
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                if (evt->user_data) {
                    memcpy(evt->user_data + output_len, evt->data, evt->data_len);
                } else {
                    if (output_buffer == NULL) {
                        output_buffer = (char *) malloc(esp_http_client_get_content_length(evt->client));
                        output_len = 0;
                        if (output_buffer == NULL) {
                            ESP_LOGE(TAG, "Failed to allocate memory for output buffer");
                            return ESP_FAIL;
                        }
                    }
                    memcpy(output_buffer + output_len, evt->data, evt->data_len);
                }
                output_len += evt->data_len;
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            if (output_buffer != NULL) {
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

void set_dispaly_lut(int lut)
{
	if (lut != epclock_dispay_current_lut) {
	    bool lut_ready = false;
		if (pdTRUE == xSemaphoreTake(xSemaphore_gui, 2000 / portTICK_PERIOD_MS )) {
			switch (lut) {
				case EPCLOCK_DISPLAY_LUT_FULL_RED:
					uc8179c_set_lut_from_reg(epd_lut_vcom_data, NULL, epd_lut_r_data, epd_lut_w_data, epd_lut_k_data, NULL);
					break;
				case EPCLOCK_DISPLAY_LUT_NO_RED:
					uc8179c_set_lut_from_reg(epd_lut_vcom_data, NULL, epd_lut_r_data_no_red, epd_lut_w_data, epd_lut_k_data, NULL);
					break;
				default:
					uc8179c_set_lut_from_otp();
					lut = EPCLOCK_DISPLAY_LUT_DEFAULT;
			}
			epclock_dispay_current_lut = lut;
			lut_ready = true;
			ESP_LOGI(TAG, "The LUT swap is done");
			xSemaphoreGive(xSemaphore_gui);
		}
	    if (!lut_ready) ESP_LOGW(TAG, "LUT update timed out, display is too busy");
	}
}

void guiTask(void *pvParameter)
{
    (void) pvParameter;
	static const char *TAG = "gui";
	ESP_LOGI(TAG, "Running GUI task");
    xSemaphore_gui = xSemaphoreCreateMutex();

    static lv_color_t *buf2 = NULL;
    static lv_disp_buf_t disp_buf;
#if defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820         \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A    \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D     \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306     \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8179C
    /* Actual size in pixels, not bytes. */
#if LV_COLOR_DEPTH == 1
    uint32_t size_in_px = 8 * DISP_BUF_SIZE;
#else
    uint32_t size_in_px = 4 * DISP_BUF_SIZE;
#endif
#endif
    lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.rounder_cb = disp_driver_rounder;
    disp_drv.set_px_cb = disp_driver_set_px;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);
   	init_gui_layout();
   	ESP_LOGI(TAG, "Create GUI timer");
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &gui_periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(gui_periodic_timer, LV_TICK_PERIOD_MS * 1000));
    gui_ready = true;

   	while (gui_up_to_date) {
   		vTaskDelay(10 / portTICK_PERIOD_MS);
   	}
    ESP_LOGI(TAG, "Start GUI loop");
    while (1) {
    	if (pdTRUE == xSemaphoreTake(xSemaphore_gui, portMAX_DELAY)) {
    		lv_task_handler();
            xSemaphoreGive(xSemaphore_gui);
    	}
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void gui_refresh_ready()
{
	gui_up_to_date = true;
}

void set_font_style_set(uint8_t style_set)
{
#ifdef CONFIG_LAYOUT_SHOW_FORECAST
    lv_style_set_text_font(&st_time, LV_STATE_DEFAULT, font_style[style_set][FONT_PURPOSE_TIME1]);
#else
    lv_style_set_text_font(&st_time, LV_STATE_DEFAULT, font_style[style_set][FONT_PURPOSE_TIME2]);
#endif
    lv_style_set_text_font(&st_day, LV_STATE_DEFAULT, font_style[style_set][FONT_PURPOSE_DATE]);
    lv_style_set_text_font(&st_date, LV_STATE_DEFAULT, font_style[style_set][FONT_PURPOSE_DATE]);
}

void set_style_set_color(lv_style_t *style, lv_color_t color_text, lv_color_t color_background)
{
	lv_style_set_text_color(style, LV_STATE_DEFAULT, color_text);
	lv_style_set_bg_color(style, LV_STATE_DEFAULT, color_background);
}

void init_gui_layout()
{
	static const char *TAG = "gui";
	ESP_LOGI(TAG, "Create GUI layout");

	const int cont_forecast_y_size = 82;
	int cont_time_y_top = 0;
	int cont_time_y_size = LV_VER_RES_MAX;
#ifdef CONFIG_LAYOUT_SHOW_FORECAST
	const int cont_date_y_size = (int)(LV_VER_RES_MAX / 6);
#else
#ifdef CONFIG_LAYOUT_SHOW_DATE
	const int cont_date_y_size = (int)(LV_VER_RES_MAX / 5);
#endif
#endif
	lv_style_init(&st_time);
	lv_style_init(&st_day);
	lv_style_init(&st_date);
	lv_style_init(&st_container);
	lv_style_init(&st_forecast1);
	lv_style_init(&st_forecast2);

	set_style_set_color(&st_time, LV_COLOR_BLACK, LV_COLOR_WHITE);
	set_style_set_color(&st_day, LV_COLOR_BLACK, LV_COLOR_WHITE);
	set_style_set_color(&st_date, LV_COLOR_BLACK, LV_COLOR_WHITE);
	set_style_set_color(&st_forecast1, LV_COLOR_BLACK, LV_COLOR_WHITE);
	set_style_set_color(&st_forecast2, LV_COLOR_BLACK, LV_COLOR_WHITE);
    set_font_style_set(font_style_set);
    lv_style_set_text_font(&st_forecast1, LV_STATE_DEFAULT, &opensansb16px);
    lv_style_set_text_font(&st_forecast2, LV_STATE_DEFAULT, &opensansb20px);
    lv_style_set_pad_inner(&st_container, LV_STATE_DEFAULT, 2);

    lv_obj_t *scr = lv_disp_get_scr_act(NULL);

#ifdef CONFIG_LAYOUT_SHOW_FORECAST
    cont_time_y_top += cont_forecast_y_size;
    cont_time_y_size -= cont_forecast_y_size;
    for (int i = 0; i < EPCLOCK_OWM_FORECAST_COUNT; i++) {
    	cont_forecast[i] = lv_cont_create(scr, NULL);
    	lv_obj_add_style(cont_forecast[i], LV_LABEL_PART_MAIN, &st_container);
        lv_obj_set_pos(cont_forecast[i], (int)(i * (LV_HOR_RES_MAX / EPCLOCK_OWM_FORECAST_COUNT)), 0);
        lv_obj_set_size(cont_forecast[i], (int)(LV_HOR_RES_MAX / EPCLOCK_OWM_FORECAST_COUNT), cont_forecast_y_size);
        lv_cont_set_layout(cont_forecast[i], LV_LAYOUT_CENTER);

		label_forecast_time[i] = lv_label_create(cont_forecast[i], NULL);
		lv_obj_add_style(label_forecast_time[i], LV_LABEL_PART_MAIN, &st_forecast1);
		lv_label_set_text(label_forecast_time[i], "");

		icon_forecast[i] = lv_img_create(cont_forecast[i], NULL);
		lv_img_set_src(icon_forecast[i], &white);

		label_forecast_temp[i] = lv_label_create(cont_forecast[i], NULL);
		lv_obj_add_style(label_forecast_temp[i], LV_LABEL_PART_MAIN, &st_forecast2);
		lv_label_set_text(label_forecast_temp[i], "");
   }
#else
#ifdef CONFIG_LAYOUT_SHOW_DATE
    cont_time_y_top += (cont_forecast_y_size / 2);
    cont_time_y_size -= (cont_forecast_y_size / 2);
#endif
#endif

#ifdef CONFIG_LAYOUT_SHOW_DATE
    lv_obj_t *cont_date;
    cont_time_y_size -= cont_date_y_size;
    cont_date = lv_cont_create(scr, NULL);
    lv_obj_set_pos(cont_date, 0, cont_time_y_top + cont_time_y_size);
    lv_obj_set_size(cont_date, LV_HOR_RES_MAX, cont_date_y_size);
	lv_obj_add_style(cont_date, LV_LABEL_PART_MAIN, &st_container);
	lv_cont_set_fit(cont_date, LV_FIT_NONE);
    lv_cont_set_layout(cont_date, LV_LAYOUT_CENTER);

    lv_obj_t *cont_date_grid;
    cont_date_grid = lv_cont_create(cont_date, NULL);
	lv_obj_add_style(cont_date_grid, LV_LABEL_PART_MAIN, &st_container);
	lv_cont_set_fit(cont_date_grid, LV_FIT_TIGHT);
    lv_cont_set_layout(cont_date_grid, LV_LAYOUT_ROW_TOP);
#endif
    lv_obj_t *cont_time;
    cont_time = lv_cont_create(scr, NULL);
    lv_obj_set_pos(cont_time, 0, cont_time_y_top);
    lv_obj_set_size(cont_time, LV_HOR_RES_MAX, cont_time_y_size);
	lv_obj_add_style(cont_time, LV_LABEL_PART_MAIN, &st_container);
    lv_cont_set_layout(cont_time, LV_LAYOUT_CENTER);

    label_time = lv_label_create(cont_time, NULL);
    lv_obj_add_style(label_time, LV_LABEL_PART_MAIN, &st_time);
    lv_label_set_text(label_time, "00:00");

#ifdef CONFIG_LAYOUT_SHOW_DATE
	label_date = lv_label_create(cont_date_grid, NULL);
    lv_obj_add_style(label_date, LV_LABEL_PART_MAIN, &st_date);
    lv_label_set_text(label_date, "date");

	label_weekday = lv_label_create(cont_date_grid, NULL);
    lv_obj_add_style(label_weekday, LV_LABEL_PART_MAIN, &st_day);
    lv_label_set_text(label_weekday, "day of week");
#endif

    icon_charging = lv_img_create(scr, NULL);
    lv_obj_set_pos(icon_charging, 10, LV_VER_RES_MAX - 104);
    lv_img_set_src(icon_charging, &white);
    icon_battery = lv_img_create(scr, NULL);
    lv_obj_set_pos(icon_battery, 10, LV_VER_RES_MAX - 64);
    lv_img_set_src(icon_battery, &white);
}

void lv_tick_task(void *arg) {
    (void) arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

