#include "wlan.h"
#include <WiFi.h>
// #include <ESPAsyncWiFiManager.h>
#include <Arduino.h>

// NTP Server
const char* ntpServer = "pool.ntp.org";
// Offset for your timezone in seconds (e.g., -5*60*60 for UTC-5)
const long gmtOffset_sec = 60*60;
// Daylight saving time offset in seconds (usually 0 or 3600)
const int daylightOffset_sec = 0;

void wlan_init() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

unsigned long lastAttemptToSyncTime = 0;
unsigned long lastSuccessfulTimeSync = 0;

struct tm current_time_info;

struct tm* get_current_time() {
  if (getLocalTime(&current_time_info, 35)) {
    return &current_time_info;
  }

  return nullptr; // error
}

void _sync_time() {

  unsigned long currentMillis = millis();

  if (currentMillis - lastAttemptToSyncTime < TIME_SYNC_INTERVAL) {
    return;
  }

  lastAttemptToSyncTime = currentMillis;

  // it is time to synchronize time with the NTP server
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Error. WiFi is not connected. Unable to synchronize time.");
    return;
  }

  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeInfo;

  if (!getLocalTime(&timeInfo, 1000)) {
    Serial.println("Error. Failed to sync time.");
    return;
  }

  lastSuccessfulTimeSync = millis();

  Serial.println(&timeInfo, "Time synchronized: %A, %B %d %Y %H:%M:%S");

}

void wlan_tick() {
  _sync_time();
}