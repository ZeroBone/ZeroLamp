#ifndef MODE_RANDOM_H
#define MODE_RANDOM_H

#include "matrix.h"

class RandomMode : public LampMode {
  void enter() {}
  void leave() {}
  void render_frame() {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = 0; y < MATRIX_HEIGHT; y++) {
        matrix_setLedColor(y, x, CHSV(random8(), 0xff, 0xff));
      }
    }
  }
};

#endif