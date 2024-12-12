#include "mode.h"

unsigned long LampMode::get_render_interval() {

  if (immediate_rendering_requested) {
    immediate_rendering_requested = false;
    return 0;
  }

  return render_interval;
}

void LampMode::set_render_interval(unsigned long new_render_interval) {
  render_interval = new_render_interval;
}

void LampMode::request_immediate_rendering() {
  immediate_rendering_requested = true;
}