#include "mode_random.h"
#include "matrix.h"

void RandomMode::enter(int logical_width, int logical_height) {
  set_render_interval(250);
}

void RandomMode::leave() {}

void RandomMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {
  for (int x = 0; x < viewport_width; x++) {
    for (int y = 0; y < viewport_height; y++) {
      matrix_setLedColor(offset_y + y, offset_x + x, CHSV(random8(), 0xff, 0xff));
    }
  }
}

CommandHandleResult RandomMode::handle_command(std::string command) {
  return CommandHandleResult::NOT_HANDLED;
}

void RandomMode::handle_event(void* event) {
  // we don't expect any events for this mode
  assert(false);
}