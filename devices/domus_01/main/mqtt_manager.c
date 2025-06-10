#include "mqtt_manager.h"
#include "mqtt_client.h"

static esp_mqtt_client_handle_t client;
static QueueHandle_t mqtt_publish_queue;
static const char *TAG = "MQTT_MANAGER";

static void mqtt_event_handler(void *handler_args, esp_event_base_t base,
                               int32_t event_id, void *event_data);
static void mqtt_publish_task(void *arg);

void mqtt_manager_init(void) {
  esp_mqtt_client_config_t config = {
      .broker.address.uri = MQTT_BROKER_URI,
  };
  client = esp_mqtt_client_init(&config);
  esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler,
                                 NULL);
  esp_mqtt_client_start(client);

  mqtt_publish_queue = xQueueCreate(10, sizeof(mqtt_publish_t));
  xTaskCreate(mqtt_publish_task, "mqtt_pub", 4096, NULL, 5, NULL);
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base,
                               int32_t event_id, void *event_data) {
  esp_mqtt_event_handle_t event = event_data;

  mqtt_command_t cmd;

  switch ((esp_mqtt_event_id_t)event_id) {
  case MQTT_EVENT_CONNECTED:
    ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
    esp_mqtt_client_subscribe(client, "/domus01/downlink/01", 0);
    break;
  case MQTT_EVENT_DATA:
    snprintf(cmd.command, sizeof(cmd.command), "%.*s", event->data_len,
             event->data);
    strcpy(cmd.response_topic, "/domus01/uplink/01");
    // printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
    // printf("DATA=%s\r\n", cmd.command);
    command_processor_enqueue(cmd); // envia para a fila de comandos
    break;
  default:
    ESP_LOGI(TAG, "Other event id:%d", event->event_id);
    break;
  }
}

static void mqtt_publish_task(void *arg) {
  mqtt_publish_t msg;
  while (1) {
    if (xQueueReceive(mqtt_publish_queue, &msg, portMAX_DELAY)) {
      esp_mqtt_client_publish(client, msg.topic, msg.payload, 0, 1, 0);
    }
  }
}

void mqtt_publish(const char *topic, const char *payload) {
  mqtt_publish_t msg;
  strncpy(msg.topic, topic, sizeof(msg.topic));
  strncpy(msg.payload, payload, sizeof(msg.payload));
  xQueueSend(mqtt_publish_queue, &msg, 0);
}
