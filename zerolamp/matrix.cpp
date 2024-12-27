#include "matrix.h"
#include <cassert>

CRGB leds[NUM_LEDS];

void matrix_init() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
  if (CURRENT_LIMIT > 0) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  }
  FastLED.setCorrection(TypicalLEDStrip);

  // optional: clear all led's to ensure that they don't continue representing the state after the firmware stopped or crashed
  FastLED.clear(true);
}

inline int ledId(int y, int x) {
  if (x % 2 == 0) {
    // led's numbered from top to bottom
    return MATRIX_HEIGHT * x + y;
  }
  return MATRIX_HEIGHT * x + MATRIX_HEIGHT - 1 - y; // mirror along the y axis
}

void matrix_setLedColor(int y, int x, CRGB color) {
  assert(y >= 0);
  assert(y < MATRIX_HEIGHT);
  assert(x >= 0);
  leds[ledId(y, x % MATRIX_WIDTH)] = color;
}

void matrix_clearLed(int y, int x) {
  matrix_setLedColor(y, x, CRGB::Black);
}