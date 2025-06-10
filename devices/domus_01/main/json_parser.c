#include "json_parser.h"

const char *TAG = "JSON_PARSER";

void format_uplink(char *buffer, size_t buflen, const device_state_t *state) {
  snprintf(buffer, buflen,
           "{\"device_id\":\"%s\",\"interval_min\":%d,\"output_status\":%d,"
           "\"schedules\":[",
           state->device_id, state->interval_min, state->output_status);

  size_t offset = strlen(buffer);
  for (int i = 0; i < state->schedule_count; i++) {
    char sched[64];
    snprintf(sched, sizeof(sched), "{\"hour\":%d,\"minute\":%d,\"state\":%d}%s",
             state->schedules[i].hour, state->schedules[i].minute,
             state->schedules[i].state,
             (i < state->schedule_count - 1) ? "," : "");

    strncat(buffer + offset, sched, buflen - offset - 1);
    offset = strlen(buffer);
  }

  strncat(buffer + offset, "]}", buflen - offset - 1);
}

void parse_downlink(const char *payload, device_state_t *state) {
  const char *val;

  // Parse interval_min
  val = strstr(payload, "\"interval_min\":");
  if (val) {
    int interval = 0;
    if (sscanf(val, "\"interval_min\":%d", &interval) == 1) {
      state->interval_min = interval;
      ESP_LOGI(TAG, "interval_min set to %d", interval);
    }
  }

  // Parse output_status
  val = strstr(payload, "\"output_status\":");
  if (val) {
    int status = 0;
    if (sscanf(val, "\"output_status\":%d", &status) == 1) {
      state->output_status = status;
      ESP_LOGI(TAG, "output_status set to %d", status);
    }
  }

  // Parse schedules
  val = strstr(payload, "\"schedules\":[");
  if (val) {
    val += strlen("\"schedules\":["); // move to start of array
    state->schedule_count = 0;

    while (*val && *val != ']') {
      int h = -1, m = -1, s = -1;
      const char *hptr = strstr(val, "\"hour\":");
      const char *mptr = strstr(val, "\"minute\":");
      const char *sptr = strstr(val, "\"state\":");

      if (hptr && mptr && sptr) {
        if (sscanf(hptr, "\"hour\":%d", &h) != 1)
          h = -1;
        if (sscanf(mptr, "\"minute\":%d", &m) != 1)
          m = -1;
        if (sscanf(sptr, "\"state\":%d", &s) != 1)
          s = -1;

        if (h >= 0 && m >= 0 && s >= 0 &&
            state->schedule_count < MAX_SCHEDULES) {
          state->schedules[state->schedule_count].hour = h;
          state->schedules[state->schedule_count].minute = m;
          state->schedules[state->schedule_count].state = s;
          ESP_LOGI(TAG, "schedule[%d] -> %02d:%02d state=%d",
                   state->schedule_count, h, m, s);
          state->schedule_count++;
        }
      }

      val = strchr(val, '}');
      if (val)
        val++;
      while (*val && (*val == ',' || *val == ' ' || *val == '\n'))
        val++;
    }

    ESP_LOGI(TAG, "Total schedules parsed: %d", state->schedule_count);
  }
}
