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

  state = SortModeState::SHUFFLED;

  set_render_interval(ALGORIHTM_VISUALIZATION_SPEED);

  schedule_event(TIMEOUT_BETWEEN_ARRAY_ALGORITHMS, nullptr);

}

void SortMode::leave() {
  delete[] array;

  if (shuffling_algorithm != nullptr) {
    delete shuffling_algorithm;
  }

  if (sorting_algorithm != nullptr) {
    delete sorting_algorithm;
  }

}

ArrayManipulationAlgorithm<uint8_t>* SortMode::get_currently_running_algorithm() {

  switch (state) {

    case SortModeState::SORTING:
      return sorting_algorithm;

    case SortModeState::SHUFFLING:
      return shuffling_algorithm;

    default:
      break;

  }

  return nullptr;

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

  // run the current array manipulation algorithm
  ArrayManipulationAlgorithm<uint8_t>* current_algorithm = get_currently_running_algorithm();

  if (current_algorithm == nullptr) {
    return;
  }

  if (current_algorithm->is_completed()) {

    switch (state) {

      case SortModeState::SORTING:
        state = SortModeState::SORTED;
        break;

      case SortModeState::SHUFFLING:
        state = SortModeState::SHUFFLED;
        break;

      default:
        assert(false);
        break;

    }

    schedule_event(TIMEOUT_BETWEEN_ARRAY_ALGORITHMS, nullptr);
    return;
  }

  current_algorithm->step(array);

}

CommandHandleResult SortMode::handle_command(String command) {
  return CommandHandleResult::NOT_HANDLED;
}

void SortMode::handle_event(void* event) {

  assert(event == nullptr); // no other events are known

  switch (state) {

    case SortModeState::SHUFFLED: {
      // start a sorting algorithm
      sorting_algorithm = new BubbleSortAlgorithm<uint8_t>(array_size);
      state = SortModeState::SORTING;
      break;
    }

    case SortModeState::SORTED: {
      // verify the array is indeed sorted
      uint8_t previous_value = array[0];

      for (int i = 1; i < array_size; i++) {
        uint8_t cur_value = array[i];
        assert(previous_value <= cur_value);
        previous_value = cur_value;
      }

      // start a shuffling algorithm
      shuffling_algorithm = new FisherYatesShuffleAlgorithm<uint8_t>(array_size);
      state = SortModeState::SHUFFLING;
      break;
    }

    default:
      assert(false);
      break;

  }

  request_immediate_rendering();

}