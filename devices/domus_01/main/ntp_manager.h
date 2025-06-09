#ifndef NTP_MANAGER_H
#define NTP_MANAGER_H

#include "esp_log.h"
#include "esp_netif_sntp.h"
#include "esp_sntp.h"
#include <time.h>

void initialize_sntp(void);
void wait_sync_time(void);

#endif // NTP_MANAGER_H
