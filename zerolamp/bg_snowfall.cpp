#include "bg_snowfall.h"
#include "matrix.h"

#include <FastLED.h>

void Snowflake::update() {

  if (brightness == 0) {
    return;
  }

  if (random8(4) != 3) {
    // Randomly make the snowflake move left, right, or straight down
    if (random8(4) == 3) {
      uint8_t shiftX = random8(2);
      if (shiftX == 0 && x != 0) {
        x--;
      }
      else if (shiftX == 1 && x != MATRIX_WIDTH - 1) {
        x++;
      }
    }
    if (random8(2) == 1) {
      y++;
    }
    
    if (y == MATRIX_HEIGHT) y = MATRIX_HEIGHT - 1;
  }

  // Fade out as it reaches the bottom
  uint8_t brightnessDecrease = random8(3, 6);
  if (brightness >= brightnessDecrease) {
    brightness -= brightnessDecrease;
  }
  else {
    brightness = 0;
  }
}

void Snowflake::draw(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  if (brightness == 0) {
    return;
  }

  CRGB snowflake_color = CHSV(160, 0, brightness);

  if (x >= viewport_width || y >= viewport_height) {
    // out of bounds
    return;
  }

  matrix_setLedColor(offset_y + y, offset_x + x, snowflake_color);

}

void SnowfallBG::enter(int logical_width, int logical_height) {

  set_render_interval(32);

  this->logical_width = logical_width;
  this->logical_height = logical_height;

  for (int i = 0; i < MAX_SNOWFLAKES; i++) {
    snowflakes[i] = Snowflake(
      random8(logical_width), // x
      random8(logical_height), // y
      random8() // brightness
    );
  }

}

void SnowfallBG::leave() {}

void SnowfallBG::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  assert(viewport_width <= logical_width);
  assert(viewport_height <= logical_height);

  for (int i = 0; i < MAX_SNOWFLAKES; i++) {

    if (snowflakes[i].brightness == 0) {
      snowflakes[i] = Snowflake(
        random8(logical_width), // x
        0, // y
        0xff // brightness
      );
    }

    snowflakes[i].update();
    snowflakes[i].draw(offset_x, offset_y, viewport_width, viewport_height);

  }

}