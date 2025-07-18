#include "command_processor.h"
#include "json_parser.h"
#include <stdio.h>
#include <string.h>

#define LED_GPIO GPIO_NUM_2

static const char *LED_CMD = "\"LED\":";

static QueueHandle_t command_queue;

static void command_processor_task(void *arg);

static void init_gpio(void) {
  gpio_config_t io_conf = {.pin_bit_mask = (1ULL << LED_GPIO),
                           .mode = GPIO_MODE_OUTPUT,
                           .pull_up_en = 0,
                           .pull_down_en = 0,
                           .intr_type = GPIO_INTR_DISABLE};
  gpio_config(&io_conf);
}

void command_processor_init(void) {
  command_queue = xQueueCreate(10, sizeof(mqtt_command_t));
  xTaskCreate(command_processor_task, "cmd_proc", 4096, NULL, 6, NULL);
}

void command_processor_enqueue(mqtt_command_t cmd) {
  xQueueSend(command_queue, &cmd, 0);
}

static void command_processor_task(void *arg) {
  mqtt_command_t cmd;

  init_gpio();

  char *cptr = NULL;
  int value = 0;

  device_state_t device = {.device_id = "esp32-001",
                           .interval_min = 10,
                           .output_status = 1,
                           .schedule_count = 2,
                           .schedules = {{6, 30, 1}, {22, 0, 0}}};

  while (1) {
    if (xQueueReceive(command_queue, &cmd, portMAX_DELAY)) {
      char response[512];
      // if ((cptr = strstr(cmd.command, LED_CMD)) != NULL) {
      //   cptr += strlen(LED_CMD);
      //   sscanf(cptr, "%d", &value);
      //   gpio_set_level(LED_GPIO, value);
      //   strcpy(response, "\"result\":true");
      // } else {
      //   strcpy(response, "\"result\":false");
      // }
      parse_downlink(cmd.command, &device);
      format_uplink(response, sizeof(response), &device);
      mqtt_publish(cmd.response_topic, response);
    }
  }
}
