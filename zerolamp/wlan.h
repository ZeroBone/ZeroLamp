#ifndef WLAN_H
#define WLAN_H

#define WLAN_SSID "YODA"
#define WLAN_PASSWORD "2I9gF8FyJB27rf0ObvaVmrOGaJw5zrVh"

#define TIME_SYNC_INTERVAL 30000 // how often to syncronize time, in milliseconds

struct tm* get_current_time();
void wlan_init();
void wlan_tick();

#endif