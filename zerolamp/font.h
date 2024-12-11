#ifndef ZB_FONT_H
#define ZB_FONT_H

#include <FastLED.h>

int draw_character(int start_x, int start_y, char c, int x_min, int x_max, CRGB color);
int draw_string_horizontally(int start_x, int start_y, char* str, int x_min, int x_max, CRGB color, int space_between_letters);

#endif