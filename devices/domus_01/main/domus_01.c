#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "command_processor.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "mqtt_manager.h"
#include "ntp_manager.h"
#include "nvs_flash.h"
#include "wifi_manager.h"

static const char *TAG = "MAIN";

static const char *DOMUS_TAG = "DOMUS_TASK";

void domus_task(void *arg) {
  while (1) {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "Current date and time: %s", strftime_buf);
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

void app_main(void) {
  ESP_LOGI(TAG, "[APP] Starting up...");
  ESP_ERROR_CHECK(nvs_flash_init());

  wifi_init();

  command_processor_init();

  initialize_sntp();
  wait_sync_time();

  mqtt_manager_init();

  xTaskCreate(domus_task, DOMUS_TAG, 2048, NULL, 2, NULL);
}
