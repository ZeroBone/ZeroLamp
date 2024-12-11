#include "fg_clock.h"

#include <cassert>
#include "font.h"
#include "wlan.h"

void ClockFG::enter(int logical_width, int logical_height) {
  this->logical_width = logical_width;
  this->logical_height = logical_height;
}

void ClockFG::leave() {}

void ClockFG::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  assert(viewport_width <= logical_width);
  assert(viewport_height <= logical_height);
  
  struct tm* cur_time = get_current_time();

  if (cur_time == nullptr) {
    draw_character(offset_x + 1, offset_y + 4, '?', offset_x, offset_x + viewport_width - 1, CRGB::Red);
    return;
  }

  // extract hours and minutes as strings
  char hourStr[3];  // 2 digits + null terminator
  char minuteStr[3]; // 2 digits + null terminator

  snprintf(hourStr, sizeof(hourStr), "%02d", cur_time->tm_hour);
  snprintf(minuteStr, sizeof(minuteStr), "%02d", cur_time->tm_min);

  draw_string_horizontally(offset_x, 2, hourStr, offset_x, offset_x + viewport_width - 1, CRGB::Green, 0);
  draw_string_horizontally(offset_x, 9, minuteStr, offset_x, offset_x + viewport_width - 1, CRGB::Blue, 0);

}