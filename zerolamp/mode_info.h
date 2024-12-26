#ifndef ZB_MODE_INFO_H
#define ZB_MODE_INFO_H

#include "mode.h"
#include <FastLED.h>

class InfoMode : public LampMode {

private:
  std::string text_line1;
  std::string text_line2;

  CRGB* line1_colors;
  CRGB* line2_colors;

  int line1_start_x;
  int line2_start_x;

public:
  InfoMode(std::string text_line1, std::string text_line2) : text_line1(text_line1), text_line2(text_line2) {}

  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(std::string command);
  void handle_event(void* event);

private:
  int count_neighbors(int grid_x, int grid_y);

};

#endif