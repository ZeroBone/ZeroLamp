#include "mode_fill.h"
#include "matrix.h"

void FillMode::enter(int logical_width, int logical_height) {
  set_render_interval(1000);
}

void FillMode::leave() {}

void FillMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {
  for (int x = 0; x < viewport_width; x++) {
    for (int y = 0; y < viewport_height; y++) {
      matrix_setLedColor(
        offset_y + y,
        offset_x + x,
        fill_color
      );
    }
  }
}

CommandHandleResult FillMode::handle_command(String command) {
  return CommandHandleResult::NOT_HANDLED;
}

void FillMode::handle_event(void* event) {
  // we don't expect any events for this mode
  assert(false);
}