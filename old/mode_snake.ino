#define SNAKE_MAX_LENGTH 128

struct Point {
  int8_t x;
  int8_t y;

  Point(int8_t x, int8_t y) : x(x), y(y) {}
  Point() {}
};

Point snake[SNAKE_MAX_LENGTH];

int snakeLength;
Point food;
int snakeMovementDirection;
CRGB foodColor;
CRGB snakeColor;

void modeSnakeInit() {
  snakeLength = 3;
  snakeColor = CHSV(random8(), 0xff, 0xff);
  snakeMovementDirection = SNAKE_DIRECTION_UP;
  
  snake[0] = Point(MATRIX_WIDTH / 2, MATRIX_HEIGHT / 2 - 1);
  snake[1] = Point(MATRIX_WIDTH / 2, MATRIX_HEIGHT / 2);
  snake[2] = Point(MATRIX_WIDTH / 2, MATRIX_HEIGHT / 2 + 1);

  spawnFood();
}

void modeSnake() {

  EVERY_N_MILLISECONDS(200) {
    modeSnakeRender();
  }

}

void modeSnakeRender() {

  moveSnake();
  
  FastLED.clear(false);

  // draw food
  leds[ledId(food.y, food.x)] = foodColor;

  // draw snake
  for (int i = 0; i < snakeLength; i++) {
    leds[ledId(snake[i].y, snake[i].x)] = snakeColor;
  }

  FastLED.show();

}

void spawnFood() {
  while (true) {
    food.x = random8(MATRIX_WIDTH);
    food.y = random8(MATRIX_HEIGHT);
    bool collisionWithSnake = false;
    for (int i = 0; i < snakeLength; i++) {
      if (snake[i].x == food.x && snake[i].y == food.y) {
        collisionWithSnake = true;
        break;
      }
    }
    if (!collisionWithSnake) break;
  }

  foodColor = CHSV(random8(), 0xff, 0xff);

}

void moveSnake() {
  Point next = snake[0];
  switch (snakeMovementDirection) {
    case SNAKE_DIRECTION_UP: next.y -= 1; break;
    case SNAKE_DIRECTION_RIGHT: next.x += 1; break;
    case SNAKE_DIRECTION_DOWN: next.y += 1; break;
    case SNAKE_DIRECTION_LEFT: next.x -= 1; break;
    default: break;
  }

  if (next.x < 0) next.x = MATRIX_WIDTH - 1;
  else if (next.x >= MATRIX_WIDTH) next.x = 0;

  if (next.y < 0) next.y = MATRIX_HEIGHT - 1;
  else if (next.y >= MATRIX_HEIGHT) next.y = 0;

  // check whether the snake collides with itself
  for (int i = 0; i < snakeLength; i++) {
    if (snake[i].x == next.x && snake[i].y == next.y) {
      // game over, restart game
      modeSnakeInit();
      return;
    }
  }

  // check whether snake collides with food
  if (next.x == food.x && next.y == food.y) {
    snakeColor = foodColor;
    if (snakeLength < SNAKE_MAX_LENGTH) {
      snakeLength++;
    }
    spawnFood();
  }

  // move the snake
  for (int i = snakeLength - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  snake[0] = next;
}