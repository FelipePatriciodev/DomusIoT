#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include "credentials.h"
#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "mqtt_client.h"
#include "string.h"

typedef struct {
  char command[512];
  char response_topic[64];
} mqtt_command_t;

typedef struct {
  char payload[512];
  char topic[64];
} mqtt_publish_t;

void mqtt_manager_init(void);
void mqtt_publish(const char *topic, const char *payload);

extern void command_processor_enqueue(mqtt_command_t cmd);

#endif // MQTT_MANAGER_H
