#include <algorithm>
#include "mode_sort.h"
#include "matrix.h"

void SortMode::enter(int logical_width, int logical_height) {

  array_size = logical_width;
  array_max_value = logical_height;

  assert(array_size > 0);
  assert(array_max_value > 0);
  assert(array_size <= 0xff);
  assert(array_max_value <= 0xff);

  assert(array_size <= array_max_value);

  // create array 1, 2, 3, ..., array_max_value
  uint8_t* temp_array = new uint8_t[array_max_value];
  for (int i = 0; i < array_max_value; i++) {
    temp_array[i] = i + 1;
  }

  // shuffle the array array using the Fisher-Yates algorithm
  for (int i = array_max_value - 1; i > 0; i--) {
    int j = random8(0, i + 1);
    std::swap(temp_array[i], temp_array[j]);
  }

  // take the first array_size elements
  array = new uint8_t[array_size];
  std::copy(temp_array, temp_array + array_size, array);

  delete[] temp_array;

  set_render_interval(500);

}

void SortMode::leave() {
  delete[] array;
  if (current_algorithm != nullptr) {
    delete current_algorithm;
  }
}

void SortMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  assert(viewport_width <= array_size);
  assert(viewport_height <= array_max_value);

  // visualize array
  for (int x = 0; x < viewport_width; x++) {

    uint8_t arr_value = array[x];
    assert(arr_value >= 1);
    assert(arr_value <= array_max_value);

    int y_bottom = viewport_height - 1;
    int y_top = y_bottom - arr_value + 1;
    if (y_top < 0) {
      y_top = 0;
    }

    CRGB arr_value_color = CHSV(
      map(arr_value, 1, array_max_value, 0, 0xff),
      0xff,
      0xff
    );

    for (int y = y_top; y <= y_bottom; y++) {
      matrix_setLedColor(
        offset_y + y,
        offset_x + x,
        arr_value_color
      );
    }

  }
}

CommandHandleResult SortMode::handle_command(String command) {
  return CommandHandleResult::NOT_HANDLED;
}

void SortMode::handle_event(void* event) {}