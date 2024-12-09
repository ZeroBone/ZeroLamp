#include <FastLED.h>
#include "matrix.h"
#include "wlan.h"
#include "bluetooth.h"

void setup() {

  Serial.begin(115200);
  Serial.println("Initializing ZeroLamp...");

  randomSeed((analogRead(0) + analogRead(1)) ^ 0xdeadbeef);

  bluetooth_init();
  matrix_init();
  wlan_init();
  
  Serial.println("ZeroLamp successfully initialized.");
}

void loop() {

  bluetooth_tick();
  wlan_tick();

  EVERY_N_MILLISECONDS(500) {

    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = 0; y < MATRIX_HEIGHT; y++) {
        matrix_setLedColor(y, x, CHSV(random8(), 0xff, 0xff));
      }
    }

    matrix_render();

    struct tm* cur_time = get_current_time();
    if (cur_time == nullptr) {
      Serial.println("Time: unknown");
    }
    else {
      Serial.println(cur_time, "Time: %A, %B %d %Y %H:%M:%S");
    }

  }

}
