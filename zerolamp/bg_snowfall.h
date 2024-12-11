#ifndef ZB_BG_SNOWFALL_H
#define ZB_BG_SNOWFALL_H

#include <Arduino.h>
#include "mode.h"

#define MAX_SNOWFLAKES 64

struct Snowflake {
  uint8_t x;
  uint8_t y;
  uint8_t brightness;

  Snowflake() {}
  Snowflake(uint8_t x, uint8_t y, uint8_t brightness) : x(x), y(y), brightness(brightness) {}

  void update();
  void draw(int offset_x, int offset_y, int viewport_width, int viewport_height);
};

class SnowfallBG : public LampMode {

private:
  int logical_width;
  int logical_height;
  Snowflake snowflakes[MAX_SNOWFLAKES];

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(String command);

};

#endif