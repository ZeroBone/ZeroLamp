#ifndef ZB_MODE_SORT_H
#define ZB_MODE_SORT_H

#include <Arduino.h>
#include "mode.h"
#include "array_manipulation.h"

#define TIMEOUT_BETWEEN_ARRAY_ALGORITHMS 2000
#define ALGORIHTM_VISUALIZATION_SPEED 250

enum class SortModeState {
  SHUFFLED,
  SORTING,
  SORTED,
  SHUFFLING
};

class SortMode : public LampMode {

private:
  int array_size;
  int array_max_value;

  uint8_t* array;
  
  SortModeState state;
  ArrayManipulationAlgorithm<uint8_t>* shuffling_algorithm = nullptr;
  ArrayManipulationAlgorithm<uint8_t>* sorting_algorithm = nullptr;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(String command);
  void handle_event(void* event);

private:
  ArrayManipulationAlgorithm<uint8_t>* get_currently_running_algorithm();

};

#endif