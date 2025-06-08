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
#include "nvs_flash.h"
#include "wifi_manager.h"

static const char *TAG = "MAIN";

void app_main(void) {
  ESP_LOGI(TAG, "[APP] Starting up...");
  ESP_ERROR_CHECK(nvs_flash_init());

  wifi_init();
  command_processor_init();
  mqtt_manager_init();
}
