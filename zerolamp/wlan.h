#ifndef ZB_WLAN_H
#define ZB_WLAN_H

#define WLAN_SSID "YODA"
#define WLAN_PASSWORD "2I9gF8FyJB27rf0ObvaVmrOGaJw5zrVh"

// #define WLAN_SSID "NikitaNet_VPN_2.4"
// #define WLAN_PASSWORD "63430356"

#define TIME_SYNC_INTERVAL 30000 // how often to syncronize time, in milliseconds

struct tm* get_current_time();
void wlan_init();
void wlan_tick();

#endif