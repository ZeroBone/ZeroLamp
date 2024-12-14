#include "mode_conway.h"
#include "matrix.h"

#define GRID_INDEX(y, x) (y * grid_width + x)

void ConwayMode::enter(int logical_width, int logical_height) {

  assert(logical_width > 0 && logical_height > 0);

  grid_width = logical_width;
  grid_height = logical_height;

  int grid_size = grid_width * grid_height;

  grid = new bool[grid_size];
  next_grid = new bool[grid_size];

  for (int i = 0; i < grid_size; i++) {
    grid[i] = random8(2) == 1 ? true : false;
  }

  set_render_interval(500);

}

void ConwayMode::leave() {
  delete[] grid;
  delete[] next_grid;
}

int ConwayMode::count_neighbors(int grid_x, int grid_y) {

  int count = 0;

  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {

      if (dx == 0 && dy == 0) {
        // ignore the current cell
        continue;
      }

      // wrap around edges
      int x = (grid_x + dx + grid_width) % grid_width;
      int y = (grid_y + dy + grid_height) % grid_height;

      if (grid[GRID_INDEX(y, x)]) {
        count++;
      }

    }
  }

  return count;

}

void ConwayMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  assert(viewport_width <= grid_width);
  assert(viewport_height <= grid_height);

  // render current grid

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

  int live_cells_count = 0;

  // update grid
  for (int grid_y = 0; grid_y < grid_height; grid_y++) {
    for (int grid_x = 0; grid_x < grid_width; grid_x++) {

      int neighbor_count = count_neighbors(grid_x, grid_y);
      int grid_index = GRID_INDEX(grid_y, grid_x);
      bool grid_value = grid[grid_index];

      if (grid_value && (neighbor_count < 2 || neighbor_count > 3)) {
        // underpopulation or overpopulation
        next_grid[grid_index] = false;
      }
      else if (!grid_value && neighbor_count == 3) {
        // reproduction
        next_grid[grid_index] = true;
      }
      else {
        // no changes, just copy the old value
        next_grid[grid_index] = grid_value;
      }

      if (next_grid[grid_index]) {
        live_cells_count++;
      }

    }
  }

  // starting from which cell count do we consider the number of live cells to be small?
  int few_cells_threshold = grid_width * grid_height / 8;

  if (live_cells_count <= few_cells_threshold) {
    // there are only few live cells

    uint8_t spawn_probability = (uint8_t)map(live_cells_count, 0, few_cells_threshold, 0xff, 0);

    if (random8() <= spawn_probability) {
      for (int i = 0; i < grid_width * grid_height; i++) {
        if (next_grid[i]) {
          continue;
        }

        // spawn a new cell with probability 25%
        if (random8(4) == i % 4) {
          next_grid[i] = true;
        }
      }
    }

  }

  std::swap(grid, next_grid);

}

CommandHandleResult ConwayMode::handle_command(String command) {
  return CommandHandleResult::NOT_HANDLED;
}

void ConwayMode::handle_event(void* event) {
  assert(false);
}