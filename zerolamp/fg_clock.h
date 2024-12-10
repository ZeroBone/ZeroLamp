#ifndef ZB_CLOCK_H
#define ZB_CLOCK_H

#include <cassert>
#include "font.h"
#include "wlan.h"

class ClockFG : public LampMode {

private:
  size_t logical_width;
  size_t logical_height;

  int time_position_x;

public:
  void enter(size_t logical_width, size_t logical_height) {
    this->logical_width = logical_width;
    this->logical_height = logical_height;
    time_position_x = logical_width;
  }

  void leave() {}

  void render_frame(size_t offset_x, size_t offset_y, size_t viewport_width, size_t viewport_height) {

    assert(viewport_width <= logical_width);
    assert(viewport_height <= logical_height);
    
    struct tm* cur_time = get_current_time();

    if (cur_time == nullptr) {
      draw_character(offset_x, offset_y, '?', offset_x, offset_x + viewport_width - 1, CRGB::Red);
      return;
    }

    // extract hours and minutes as strings
    char hourStr[3];  // 2 digits + null terminator
    char minuteStr[3]; // 2 digits + null terminator

    snprintf(hourStr, sizeof(hourStr), "%02d", cur_time->tm_hour);
    snprintf(minuteStr, sizeof(minuteStr), "%02d", cur_time->tm_min);

    draw_string_horizontally(offset_x + time_position_x, 0, hourStr, offset_x, offset_x + viewport_width - 1, CRGB::Green);
    draw_string_horizontally(offset_x + time_position_x, 9, minuteStr, offset_x, offset_x + viewport_width - 1, CRGB::Green);

    time_position_x--;
    if (time_position_x < -6 * 2) {
      time_position_x = logical_width; // reset position
    }

  }
};

#endif