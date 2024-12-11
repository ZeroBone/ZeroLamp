#include "bg_rainbow.h"
#include "matrix.h"

void RainbowBG::enter(int logical_width, int logical_height) {
  hue = 0;
  set_render_interval(33);
}

void RainbowBG::leave() {}

void RainbowBG::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {
  for (int x = 0; x < viewport_width; x++) {
    for (int y = 0; y < viewport_height; y++) {
      matrix_setLedColor(
        offset_y + y,
        offset_x + x,
        CHSV(hue + y * 5, 0xff, 0xff)
      );
    }
  }

  hue++;
}