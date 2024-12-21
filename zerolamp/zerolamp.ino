#include "matrix.h"
#include "wlan.h"
#include "bluetooth.h"
#include "program_controller.h"

#include <FastLED.h>

void setup() {

  Serial.begin(115200);

  Serial.println("Initializing ZeroLamp...");

  unsigned long seed = (analogRead(0) + analogRead(1)) ^ 0xdeadbeef;
  randomSeed(seed);
  random16_set_seed(~seed);

  bluetooth_init();
  matrix_init();
  wlan_init();
  program_controller_init();
  
  Serial.println("ZeroLamp successfully initialized.");

}

void loop() {

  bluetooth_tick();
  wlan_tick();
  program_controller_tick();

  // add 16-bit entropy from the slower random number generator to the faster one
  random16_add_entropy(random(0x10000));

}
