#ifndef ZB_MODE_SORT_H
#define ZB_MODE_SORT_H

#include "mode.h"

class ArrayManipulationAlgorithm {

public:

  virtual void step(uint8_t* array) = 0;

  virtual bool is_completed() = 0;

  virtual ~ArrayManipulationAlgorithm() {}

};

class SortMode : public LampMode {

private:
  int array_size;
  int array_max_value;

  uint8_t* array;
  ArrayManipulationAlgorithm* current_algorithm = nullptr;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(String command);
  void handle_event(void* event);

};

#endif