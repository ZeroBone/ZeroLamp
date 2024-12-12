#ifndef ZB_MODE_SNAKE_H
#define ZB_MODE_SNAKE_H

#include <FastLED.h>
#include <Arduino.h>
#include "mode.h"

enum class SnakeDirection {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct SnakePoint {
  uint8_t x;
  uint8_t y;

  SnakePoint(uint8_t x, uint8_t y) : x(x), y(y) {}
  SnakePoint() {}
};

class SnakeMode : public LampMode {

private:
  int logical_width;
  int logical_height;

  int snake_length;
  int snake_max_length;

  CRGB snake_color;

  SnakeDirection movement_direction;
  SnakePoint* snake;

  SnakePoint food;
  CRGB food_color;

public:
  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(String command);
  void handle_event(void* event);

private:
  void move_snake();
  void spawn_food();

};

#endif