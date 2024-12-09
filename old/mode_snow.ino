struct Snowflake {
  uint8_t x;
  uint8_t y;
  uint8_t brightness;

  Snowflake() : x(random8(MATRIX_WIDTH)), y(random8(MATRIX_HEIGHT)), brightness(random8()) {}

  Snowflake(uint8_t y) : x(random8(MATRIX_WIDTH)), y(y), brightness(0xff) {}

  void update() {
    if (brightness == 0) return;

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

  void draw() {
    if (brightness == 0) return;
    leds[ledId(y, x)] = CHSV(160, 0, brightness);  // White color for snowflakes
  }
};

const int MAX_SNOWFLAKES = 64;
Snowflake snowflakes[MAX_SNOWFLAKES];

void modeSnowInit() {
  for (int i = 0; i < MAX_SNOWFLAKES; i++) {
    snowflakes[i] = Snowflake();
  }
}

void modeSnow() {
  EVERY_N_MILLISECONDS(33) {

    FastLED.clear(false);

    for (int i = 0; i < MAX_SNOWFLAKES; i++) {
      if (snowflakes[i].brightness <= 0) {
        snowflakes[i] = Snowflake(0);
      }
      snowflakes[i].update();
      snowflakes[i].draw();
    }

    FastLED.show();
  }
}