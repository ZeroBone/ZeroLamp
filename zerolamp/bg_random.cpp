#include "bg_random.h"
#include "matrix.h"

void RandomBG::enter(int logical_width, int logical_height) {
  set_render_interval(250);
}

void RandomBG::leave() {}

void RandomBG::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {
  for (int x = 0; x < viewport_width; x++) {
    for (int y = 0; y < viewport_height; y++) {
      matrix_setLedColor(offset_y + y, offset_x + x, CHSV(random8(), 0xff, 0xff));
    }
  }
}

CommandHandleResult RandomBG::handle_command(String command) {
  return CommandHandleResult::NOT_HANDLED;
}