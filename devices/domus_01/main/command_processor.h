#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "mqtt_manager.h"
#include "string.h"

void command_processor_init(void);
void command_processor_enqueue(mqtt_command_t cmd);

#endif // COMMAND_PROCESSOR_H
