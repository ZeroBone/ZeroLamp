#include "mode_info.h"
#include "font.h"

void InfoMode::enter(int logical_width, int logical_height) {
  line1_start_x = logical_width;
  line2_start_x = logical_width;

  line1_colors = new CRGB[text_line1.size()];
  for (int i = 0; i < text_line1.size(); i++) {
    line1_colors[i] = CHSV(map(i, 0, text_line1.size() - 1, 0, 0xff), 0xff, 0xff);
  }

  line2_colors = new CRGB[text_line2.size()];
  for (int i = 0; i < text_line2.size(); i++) {
    line2_colors[i] = CHSV(map(i, 0, text_line2.size() - 1, 0, 0xff), 0xff, 0xff);
  }

  set_render_interval(500);
}

void InfoMode::leave() {
  delete line1_colors;
  delete line2_colors;
}

void InfoMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  assert(viewport_width > 0);

  int line1_real_width = draw_string_horizontally(
    offset_x + line1_start_x,
    offset_y + 2,
    text_line1.c_str(),
    offset_x,
    offset_x + viewport_width - 1,
    line1_colors,
    1
  );

  int line2_real_width = draw_string_horizontally(
    offset_x + line2_start_x,
    offset_y + 9,
    text_line2.c_str(),
    offset_x,
    offset_x + viewport_width - 1,
    line2_colors,
    1
  );

  line1_start_x--;
  line2_start_x--;

  if (line1_start_x < -line1_real_width) {
    line1_start_x = viewport_width;
  }

  if (line2_start_x < -line2_real_width) {
    line2_start_x = viewport_width;
  }

}

CommandHandleResult InfoMode::handle_command(std::string command) {
  return CommandHandleResult::NOT_HANDLED;
}

void InfoMode::handle_event(void* event) {}