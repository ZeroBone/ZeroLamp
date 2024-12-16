#ifndef ZB_MODE_RAINBOW_H
#define ZB_MODE_RAINBOW_H

#include <Arduino.h>
#include "mode.h"

class RainbowMode : public LampMode {

private:
  uint8_t hue;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(std::string command);
  void handle_event(void* event);

};

#endif