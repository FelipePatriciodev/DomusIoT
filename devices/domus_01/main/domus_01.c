#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "esp_wifi.h"
#include "mqtt_client.h"

#include "credentials.h"

static const char *TAG = "mqtt_example";

static EventGroupHandle_t s_wifi_event_group;
const int WIFI_CONNECTED_BIT = BIT0;

static void pub_task(void *arg);

static void log_error_if_nonzero(const char *message, int error_code) {
  if (error_code != 0) {
    ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
  }
}

// Evento Wi-Fi para monitorar conexão
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
    esp_wifi_connect();
  } else if (event_base == WIFI_EVENT &&
             event_id == WIFI_EVENT_STA_DISCONNECTED) {
    ESP_LOGI(TAG, "Disconnected. Trying to reconnect...");
    esp_wifi_connect();
    xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
  } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
    ESP_LOGI(TAG, "Got IP:" IPSTR, IP2STR(&event->ip_info.ip));
    xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
  }
}

static void wifi_init_sta(void) {
  s_wifi_event_group = xEventGroupCreate();

  ESP_ERROR_CHECK(esp_netif_init());

  ESP_ERROR_CHECK(esp_event_loop_create_default());

  esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));

  // Registra os handlers de eventos para Wi-Fi e IP
  ESP_ERROR_CHECK(esp_event_handler_instance_register(
      WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
  ESP_ERROR_CHECK(esp_event_handler_instance_register(
      IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));

  wifi_config_t wifi_config = {
      .sta =
          {
              .ssid = WIFI_SSID,
              .password = WIFI_PASS,
              .threshold.authmode = WIFI_AUTH_WPA2_PSK,
              .pmf_cfg = {.capable = true, .required = false},
          },
  };
  ESP_LOGI(TAG, "Connecting to %s...", WIFI_SSID);
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());

  // Espera até conectar
  EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT,
                                         pdFALSE, pdTRUE, portMAX_DELAY);

  if (bits & WIFI_CONNECTED_BIT) {
    ESP_LOGI(TAG, "Wi-Fi connected");
  } else {
    ESP_LOGE(TAG, "Failed to connect to Wi-Fi");
  }
}

static esp_mqtt_client_handle_t client = NULL;
static bool mqtt_connected = false;

/* MQTT event handler */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base,
                               int32_t event_id, void *event_data) {
  // ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d",
  // base,
  // event_id);
  esp_mqtt_event_handle_t event = event_data;
  client = event->client;
  switch ((esp_mqtt_event_id_t)event_id) {
  case MQTT_EVENT_CONNECTED:
    ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
    mqtt_connected = true;
    break;
  case MQTT_EVENT_DISCONNECTED:
    ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
    mqtt_connected = false;
    break;
  case MQTT_EVENT_SUBSCRIBED:
    ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
    break;
  case MQTT_EVENT_UNSUBSCRIBED:
    ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
    break;
  case MQTT_EVENT_PUBLISHED:
    ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
    break;
  case MQTT_EVENT_DATA:
    ESP_LOGI(TAG, "MQTT_EVENT_DATA");
    printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
    printf("DATA=%.*s\r\n", event->data_len, event->data);
    break;
  case MQTT_EVENT_ERROR:
    ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
    if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
      log_error_if_nonzero("esp-tls",
                           event->error_handle->esp_tls_last_esp_err);
      log_error_if_nonzero("tls stack", event->error_handle->esp_tls_stack_err);
      log_error_if_nonzero("socket errno",
                           event->error_handle->esp_transport_sock_errno);
      ESP_LOGI(TAG, "Last errno string (%s)",
               strerror(event->error_handle->esp_transport_sock_errno));
    }
    break;
  default:
    ESP_LOGI(TAG, "Other event id:%d", event->event_id);
    break;
  }
}

static void mqtt_app_start(void) {
  esp_mqtt_client_config_t mqtt_cfg = {
      .broker.address.uri = MQTT_BROKER_URI,
  };

  esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler,
                                 NULL);
  esp_mqtt_client_start(client);
}

static void pub_task(void *arg) {
  static const char *PUB_TASK_TAG = "PUB_TASK";
  int msg_id;

  while (1) {
    if (mqtt_connected && client != NULL) {
      msg_id = esp_mqtt_client_publish(client, "/device/domus_01/01",
                                       "{\"status\":\"desligado\"}", 0, 1, 0);
      ESP_LOGI(PUB_TASK_TAG, "Publish sent, msg_id=%d", msg_id);
    } else {
      ESP_LOGW(PUB_TASK_TAG, "MQTT Disconnected");
    }

    vTaskDelay(pdMS_TO_TICKS(10 * 1000));
  }
}

void app_main(void) {
  ESP_LOGI(TAG, "[APP] Starting up...");
  ESP_ERROR_CHECK(nvs_flash_init());

  wifi_init_sta();

  mqtt_app_start();

  xTaskCreate(pub_task, "pub_task", 1024 * 2, NULL, 1, NULL);
}
