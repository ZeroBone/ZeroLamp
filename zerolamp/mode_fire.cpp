#include "mode_fire.h"
#include "matrix.h"

#include <cassert>

int FireMode::get_temperature(int x, int y) {

  if (y < 0) {
    y = 0;
  }

  if (x < 0) {
    x += logical_width;
    assert(x >= 0);
  }
  else if (x >= logical_width) {
    x = x - logical_width;
    assert(x < logical_width);
  }
  
  assert(y < logical_height);

  return temperature[y * logical_width + x];
}

void FireMode::set_temperature(int x, int y, int new_temperature) {
  assert(x >= 0);
  assert(y >= 0);
  assert(x < logical_width);
  assert(y < logical_height);

  if (new_temperature > 0xff) {
    new_temperature = 0xff;
  }

  if (new_temperature < 0) {
    new_temperature = 0;
  }

  temperature[y * logical_width + x] = (uint8_t)new_temperature;
}

void FireMode::enter(int logical_width, int logical_height) {

  assert(logical_width >= 1);
  assert(logical_height >= 1);

  this->logical_width = logical_width;
  this->logical_height = logical_height;

  temperature = new uint8_t[logical_width * logical_height](); // initialize all temperature values to 0

  set_render_interval(33);
}

void FireMode::leave() {
  if (temperature != nullptr) {
    delete[] temperature;
  }
}

CRGB visualize_temperature(uint8_t temperature) {
  // scale 'heat' down from 0-255 to 0-191
  uint8_t t192 = round((temperature / 255.0) * 191);

  // scale to red, green, and blue components based on heat level
  if (t192 <= 63) {
    return CRGB(t192 * 4, 0, 0); // rises from black to red
  }
  
  if (t192 <= 127) {
    return CRGB(0xff, (t192 - 63) * 4, 0); // rises from red to yellow
  }
  
  return CRGB(0xff, 0xff, (t192 - 127) * 4); // rises from yellow to white
}

void FireMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  assert(viewport_width <= logical_width);
  assert(viewport_height <= logical_height);

  // step 1: cool down every cell a little
  for (int x = 0; x < logical_width; x++) {
    for (int y = 0; y < logical_height; y++) {
      set_temperature(
        x, y,
        get_temperature(x, y) - random(20, 35)
      );
    }
  }

  // step 2: heat rises up, diffusing upwards and slightly sideways
  for (int x = 0; x < logical_width; x++) {
    for (int y = logical_height - 1; y > 0; y--) {
      set_temperature(
        x, y,
        (
          get_temperature(x, y - 1) +
          get_temperature(x, y - 2) +
          get_temperature(x - 1, y - 1) +
          get_temperature(x + 1, y - 1)
        ) / 4
      );
    }
  }

  // step 3: randomly ignite new heat at the bottom row
  for (int x = 0; x < logical_width; x++) {
    if (random(0, 10) > 5) {
      // ignite the bottom cell
      set_temperature(
        x, 0,
        get_temperature(x, 0) + random(160, 255)
      );
    }
  }

  // step 4: map heat values to colors and assign them to LEDs
  for (int x = 0; x < viewport_width; x++) {
    for (int y = 0; y < viewport_height; y++) {
      uint8_t current_temperature = get_temperature(x, logical_height - 1 - y);
      CRGB color = visualize_temperature(current_temperature);
      matrix_setLedColor(offset_y + y, offset_x + x, color);
    }
  }

}

CommandHandleResult FireMode::handle_command(String command) {
  return CommandHandleResult::NOT_HANDLED;
}