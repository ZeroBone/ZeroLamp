#include "fg_snake_game.h"
#include "matrix.h"
#include <cassert>
#include "bluetooth.h"

SnakeDirection get_random_snake_direction() {

  uint8_t r = random8(4);

  switch (r) {
    case 0: return SnakeDirection::UP;
    case 1: return SnakeDirection::DOWN;
    case 2: return SnakeDirection::LEFT;
    case 3: return SnakeDirection::RIGHT;
    default:
      break;
  }

  assert(false);

}

void SnakeGameFG::enter(int logical_width, int logical_height) {

  assert(logical_width >= 3);
  assert(logical_height >= 3);

  this->logical_width = logical_width;
  this->logical_height = logical_height;

  snake_length = 3;

  snake_max_length = (logical_width * logical_height) >> 1;
  assert(snake_max_length >= 4);

  snake_color = CHSV(random8(), 0xff, 0xff);
  movement_direction = get_random_snake_direction();

  snake = new SnakePoint[snake_max_length];

  int center_x = logical_width >> 1;
  int center_y = logical_height >> 1;

  switch (movement_direction) {

    case SnakeDirection::UP:
      snake[0] = SnakePoint(center_x, center_y - 1);
      snake[1] = SnakePoint(center_x, center_y);
      snake[2] = SnakePoint(center_x, center_y + 1);
      break;

    case SnakeDirection::DOWN:
      snake[0] = SnakePoint(center_x, center_y + 1);
      snake[1] = SnakePoint(center_x, center_y);
      snake[2] = SnakePoint(center_x, center_y - 1);
      break;

    case SnakeDirection::LEFT:
      snake[0] = SnakePoint(center_x - 1, center_y);
      snake[1] = SnakePoint(center_x, center_y);
      snake[2] = SnakePoint(center_x + 1, center_y);
      break;

    case SnakeDirection::RIGHT:
      snake[0] = SnakePoint(center_x + 1, center_y);
      snake[1] = SnakePoint(center_x, center_y);
      snake[2] = SnakePoint(center_x - 1, center_y);
      break;

    default:
      assert(false);
      break;

  }

  spawn_food();

  set_render_interval(200);
}

void SnakeGameFG::leave() {
  if (snake != nullptr) {
    delete[] snake;
  }
}

void SnakeGameFG::move_snake() {
  
  SnakePoint next = snake[0];

  assert(next.x < logical_width);
  assert(next.y < logical_height);

  switch (movement_direction) {

    case SnakeDirection::UP:
      if (next.y == 0) {
        next.y = logical_height - 1;
      }
      else {
        next.y--;
      }
      break;

    case SnakeDirection::DOWN:
      if (next.y == logical_height - 1) {
        next.y = 0;
      }
      else {
        next.y++;
      }
      break;

    case SnakeDirection::LEFT:
      if (next.x == 0) {
        next.x = logical_width - 1;
      }
      else {
        next.x--;
      }
      break;

    case SnakeDirection::RIGHT:
      if (next.x == logical_width - 1) {
        next.x = 0;
      }
      else {
        next.x++;
      }
      break;

    default:
      assert(false);
      break;

  }

  // check whether the snake collides with itself
  for (int i = 0; i < snake_length; i++) {
    if (snake[i].x == next.x && snake[i].y == next.y) {
      // game over, restart game
      leave();
      enter(logical_width, logical_height);
      return;
    }
  }

  // check whether snake collides with food
  if (next.x == food.x && next.y == food.y) {
    snake_color = food_color;

    if (snake_length < snake_max_length) {
      snake_length++;
    }

    spawn_food();
  }

  // move the snake
  for (int i = snake_length - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }

  snake[0] = next;

}

void SnakeGameFG::spawn_food() {

  while (true) {

    food.x = random8(logical_width);
    food.y = random8(logical_height);

    bool collision_with_snake = false;

    for (int i = 0; i < snake_length; i++) {
      if (snake[i].x == food.x && snake[i].y == food.y) {
        collision_with_snake = true;
        break;
      }
    }

    if (!collision_with_snake) {
      break;
    }

  }

  food_color = CHSV(random8(), 0xff, 0xff);

}

void SnakeGameFG::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  move_snake();

  // draw food
  if (food.x < viewport_width && food.y < viewport_height) {
    matrix_setLedColor(offset_y + food.y, offset_x + food.x, food_color);
  }

  // draw snake
  for (int i = 0; i < snake_length; i++) {
    int x = snake[i].x;
    int y = snake[i].y;

    assert(x >= 0);
    assert(y >= 0);

    if (x >= viewport_width || y >= viewport_height) {
      // out of bounds
      continue;
    }

    matrix_setLedColor(offset_y + y, offset_x + x, snake_color);

  }

}

CommandHandleResult SnakeGameFG::handle_command(String command) {

  if (command.equalsIgnoreCase("w")) {
    if (movement_direction != SnakeDirection::DOWN) {
      bluetooth_serial()->println("Snake moves up.");
      movement_direction = SnakeDirection::UP;
    }
    else {
      bluetooth_serial()->println("Can't move up.");
    }
    return CommandHandleResult::HANDLED;
  }

  if (command.equalsIgnoreCase("s")) {
    if (movement_direction != SnakeDirection::UP) {
      bluetooth_serial()->println("Snake moves down.");
      movement_direction = SnakeDirection::DOWN;
    }
    else {
      bluetooth_serial()->println("Can't move down.");
    }
    return CommandHandleResult::HANDLED;
  }

  if (command.equalsIgnoreCase("a")) {
    if (movement_direction != SnakeDirection::RIGHT) {
      bluetooth_serial()->println("Snake moves left.");
      movement_direction = SnakeDirection::LEFT;
    }
    else {
      bluetooth_serial()->println("Can't move left.");
    }
    return CommandHandleResult::HANDLED;
  }

  if (command.equalsIgnoreCase("d")) {
    if (movement_direction != SnakeDirection::LEFT) {
      bluetooth_serial()->println("Snake moves right.");
      movement_direction = SnakeDirection::RIGHT;
    }
    else {
      bluetooth_serial()->println("Can't move right.");
    }
    return CommandHandleResult::HANDLED;
  }

  return CommandHandleResult::NOT_HANDLED;
}