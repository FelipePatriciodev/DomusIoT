#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#define MAX_SCHEDULES 10

#include "esp_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int hour;
  int minute;
  int state;
} schedule_t;

typedef struct {
  char device_id[32];
  int interval_min;
  int output_status;
  schedule_t schedules[MAX_SCHEDULES];
  int schedule_count;
} device_state_t;

void format_uplink(char *buffer, size_t buflen, const device_state_t *state);
void parse_downlink(const char *payload, device_state_t *state);

#endif // JSON_PARSER_H
