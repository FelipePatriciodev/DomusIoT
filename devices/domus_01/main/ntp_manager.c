#include "ntp_manager.h"

static const char *TAG = "NTP_MANAGER";

void initialize_sntp(void) {
  esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
  config.sync_cb = NULL;
  esp_netif_sntp_init(&config);
  ESP_LOGI(TAG, "SNTP started");
}

void wait_sync_time(void) {
  time_t now = 0;
  struct tm timeinfo = {0};

  int retry = 0;
  const int retry_count = 15;

  while (timeinfo.tm_year < (2023 - 1900) && ++retry < retry_count) {
    ESP_LOGI(TAG, "Waiting for time synchronization... (%d/%d)", retry,
             retry_count);
    vTaskDelay(pdMS_TO_TICKS(2000));
    time(&now);
    localtime_r(&now, &timeinfo);
  }

  if (timeinfo.tm_year >= (2023 - 1900)) {
    setenv("TZ", "BRT3", 1);
    tzset();
    ESP_LOGI(TAG, "Time synchronized successfully");
  } else {
    ESP_LOGW(TAG, "Failed to synchronize time via SNTP");
  }
}
