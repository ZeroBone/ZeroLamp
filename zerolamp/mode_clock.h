#ifndef ZB_MODE_CLOCK_H
#define ZB_MODE_CLOCK_H

#include "mode.h"

class ClockMode : public LampMode {

private:
  int logical_width;
  int logical_height;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(String command);

};

#endif