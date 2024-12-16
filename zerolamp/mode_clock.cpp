#include "mode_clock.h"

#include <cassert>
#include "font.h"
#include "wlan.h"

void ClockMode::enter(int logical_width, int logical_height) {
  this->logical_width = logical_width;
  this->logical_height = logical_height;

  set_render_interval(500);
}

void ClockMode::leave() {}

void ClockMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  assert(viewport_width <= logical_width);
  assert(viewport_height <= logical_height);

  // extract hours and minutes as strings
  char hourStr[3];  // 2 digits + null terminator
  char minuteStr[3]; // 2 digits + null terminator

  struct tm* cur_time = get_current_time();

  if (cur_time == nullptr) {
    // time is not available at the moment
    hourStr[0] = '?';
    hourStr[1] = '?';
    hourStr[2] = '\0';
    minuteStr[0] = '?';
    minuteStr[1] = '?';
    minuteStr[2] = '\0';
  }
  else {
    snprintf(hourStr, sizeof(hourStr), "%02d", cur_time->tm_hour);
    snprintf(minuteStr, sizeof(minuteStr), "%02d", cur_time->tm_min);
  }

  CRGB hour_color[] = {CRGB::Green, CRGB::Yellow};
  CRGB minute_color[] = {CRGB::Red, CRGB::Blue};

  draw_string_horizontally(offset_x, 2, hourStr, offset_x, offset_x + viewport_width - 1, hour_color, 0);
  draw_string_horizontally(offset_x, 9, minuteStr, offset_x, offset_x + viewport_width - 1, minute_color, 0);

}

CommandHandleResult ClockMode::handle_command(std::string command) {
  return CommandHandleResult::NOT_HANDLED;
}

void ClockMode::handle_event(void* event) {
  // we don't expect any events for this mode
  assert(false);
}