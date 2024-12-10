#include "matrix.h"
#include "wlan.h"
#include "bluetooth.h"
#include "modes.h"

#include <FastLED.h>

void setup() {

  Serial.begin(115200);

  Serial.println("Initializing ZeroLamp...");

  randomSeed((analogRead(0) + analogRead(1)) ^ 0xdeadbeef);

  bluetooth_init();
  matrix_init();
  wlan_init();
  modes_init();
  
  Serial.println("ZeroLamp successfully initialized.");
}

void loop() {

  bluetooth_tick();
  wlan_tick();
  modes_tick();

  /*EVERY_N_MILLISECONDS(500) {

    struct tm* cur_time = get_current_time();
    if (cur_time == nullptr) {
      Serial.println("Time: unknown");
    }
    else {
      Serial.println(cur_time, "Time: %A, %B %d %Y %H:%M:%S");
    }

  }*/

}
