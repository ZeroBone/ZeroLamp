#ifndef ZB_MODE_CONWAY_H
#define ZB_MODE_CONWAY_H

#include "mode.h"

class ConwayMode : public LampMode {

private:
  int grid_width;
  int grid_height;

  bool* grid;
  bool* next_grid;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(String command);
  void handle_event(void* event);

private:
  int count_neighbors(int grid_x, int grid_y);

};

#endif