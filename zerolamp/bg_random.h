#ifndef ZB_RANDOM_H
#define ZB_RANDOM_H

#include "matrix.h"

class RandomBG : public LampMode {

public:
  void enter(size_t logical_width, size_t logical_height) {}

  void leave() {}

  void render_frame(size_t offset_x, size_t offset_y, size_t viewport_width, size_t viewport_height) {
    for (size_t x = 0; x < viewport_width; x++) {
      for (size_t y = 0; y < viewport_height; y++) {
        matrix_setLedColor(offset_y + y, offset_x + x, CHSV(random8(), 0xff, 0xff));
      }
    }
  }

};

#endif