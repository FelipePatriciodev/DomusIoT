#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "credentials.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

void wifi_init(void);

#endif // WIFI_MANAGER_H
