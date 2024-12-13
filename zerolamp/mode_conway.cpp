#include "mode_conway.h"
#include "matrix.h"

#define GRID_INDEX(y, x) (y * grid_width + x)

void ConwayMode::enter(int logical_width, int logical_height) {

  assert(logical_width > 0 && logical_height > 0);

  grid_width = logical_width;
  grid_height = logical_height;

  grid = new bool[grid_width * grid_height];
  next_grid = new bool[grid_width * grid_height];

  set_render_interval(1000);

}

void ConwayMode::leave() {
  delete[] grid;
  delete[] next_grid;
}

void ConwayMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  assert(viewport_width <= grid_width);
  assert(viewport_height <= grid_height);

  for (int y = 0; y < viewport_height; y++) {
    for (int x = 0; x < viewport_width; x++) {

      bool grid_value = grid[GRID_INDEX(y, x)];
      CRGB color = grid_value ? CRGB::White : CRGB::Black;

      matrix_setLedColor(
        offset_y + y,
        offset_x + x,
        color
      );

    }
  }

}

CommandHandleResult ConwayMode::handle_command(String command) {
  return CommandHandleResult::NOT_HANDLED;
}

void ConwayMode::handle_event(void* event) {
  assert(false);
}