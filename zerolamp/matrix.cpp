#include "matrix.h"

CRGB leds[NUM_LEDS];

void matrix_init() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
  if (CURRENT_LIMIT > 0) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  }
  FastLED.setCorrection(TypicalLEDStrip);
}

inline int ledId(int y, int x) {
  if (x % 2 == 0) {
    // led's numbered from top to bottom
    return MATRIX_HEIGHT * x + y;
  }
  return MATRIX_HEIGHT * x + MATRIX_HEIGHT - 1 - y; // mirror along the y axis
}

void matrix_setLedColor(int y, int x, CRGB color) {
  leds[ledId(y, x)] = color;
}

void matrix_render() {
  FastLED.show();
}