#include "mode_simplex.h"
#include "matrix.h"

void SimplexMode::enter(int logical_width, int logical_height) {

  this->logical_width = logical_width;
  this->logical_height = logical_height;

  noise = new uint8_t[logical_width * logical_height];

  simplex_x = random16();
  simplex_y = random16();
  simplex_z = random16();

  set_render_interval(33);
}

void SimplexMode::leave() {
  delete[] noise;
}

uint8_t SimplexMode::get_noise_value(int y, int x) {
  assert(y >= 0 && x >= 0);
  assert(y < logical_height && x < logical_width);
  return noise[y * logical_width + x];
}

void SimplexMode::set_noise_value(int y, int x, uint8_t value) {
  assert(y >= 0 && x >= 0);
  assert(y < logical_height && x < logical_width);
  noise[y * logical_width + x] = value;
}

void SimplexMode::update_noise() {

  for (int y = 0; y < logical_height; y++) {

    int yoffset = scale * y;

    for (int x = 0; x < logical_width; x++) {

      int xoffset = scale * x;

      set_noise_value(
        y,
        x,
        inoise8(x + yoffset, y + xoffset, simplex_z)
      );

    }

  }

  simplex_z += speed;

}

void SimplexMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  update_noise();

  for (int x = 0; x < viewport_width; x++) {
    for (int y = 0; y < viewport_height; y++) {
      matrix_setLedColor(
        offset_y + y,
        offset_x + x,
        CHSV(
          get_noise_value(y, x),
          0xff,
          0xff
        )
      );
    }
  }
}

CommandHandleResult SimplexMode::handle_command(String command) {
  return CommandHandleResult::NOT_HANDLED;
}

void SimplexMode::handle_event(void* event) {}