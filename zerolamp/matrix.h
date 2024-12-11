#ifndef MATRIX_H
#define MATRIX_H

#include <FastLED.h>

#define CURRENT_LIMIT 2000 // maximum current in milliamps
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 19 // GPIO pin connected to WS2812B matrix

const int MATRIX_WIDTH = 16;
const int MATRIX_HEIGHT = 16;

void matrix_init();
void matrix_setLedColor(int y, int x, CRGB color);
void matrix_clearLed(int y, int x);

#endif