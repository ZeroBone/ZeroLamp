#ifndef ZB_BG_FIRE_H
#define ZB_BG_FIRE_H

#include <Arduino.h>
#include "mode.h"

class FireBG : public LampMode {

private:
  int logical_width;
  int logical_height;

  uint8_t* temperature = nullptr;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(String command);

private:
  int get_temperature(int x, int y);
  void set_temperature(int x, int y, int new_temperature);

};

#endif