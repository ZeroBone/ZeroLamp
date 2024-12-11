#include "mode.h"

unsigned long LampMode::get_render_interval() {
  return render_interval;
}

void LampMode::set_render_interval(unsigned long new_render_interval) {
  render_interval = new_render_interval;
}