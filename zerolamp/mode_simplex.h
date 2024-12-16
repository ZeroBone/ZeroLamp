#ifndef ZB_MODE_SIMPLEX_H
#define ZB_MODE_SIMPLEX_H

#include <Arduino.h>
#include "mode.h"

class SimplexMode : public LampMode {

private:
  int logical_width;
  int logical_height;
  
  uint8_t* noise;

  uint16_t simplex_x;
  uint16_t simplex_y;
  uint16_t simplex_z;

  uint16_t speed = 20;
  uint16_t scale = 311;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(std::string command);
  void handle_event(void* event);

private:
  uint8_t get_noise_value(int y, int x);
  void set_noise_value(int y, int x, uint8_t value);
  void update_noise();
  
};

#endif