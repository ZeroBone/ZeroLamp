#include <FastLED.h>
#include <BluetoothSerial.h>

// Matrix configuration
#define CURRENT_LIMIT 2000 // maximum current in milliamps
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 19 // GPIO pin connected to WS2812B

// LED array
CRGB leds[NUM_LEDS];

// Matrix width and height
const int MATRIX_WIDTH = 16;
const int MATRIX_HEIGHT = 16;

// Bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// Modes
#define MODE_RAINBOW 0
#define MODE_FILL 1
#define MODE_FIRE 2
#define MODE_SNOW 3
#define MODE_INFO 4
#define MODE_SNAKE 5

#define MODES_COUNT 6
#define DEFAULT_MODE MODE_FILL

int currentMode = DEFAULT_MODE;

// Utility functions

int ledId(int y, int x) {
  if (x % 2 == 0) {
    // led's numbered from top to bottom
    return MATRIX_HEIGHT * x + y;
  }
  return MATRIX_HEIGHT * x + MATRIX_HEIGHT - 1 - y; // mirror along the y axis
}

void setup() {

  Serial.begin(115200);
  Serial.println("Initializing ZeroLamp...");

  // Initialize FastLED
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
  if (CURRENT_LIMIT > 0) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  }
  FastLED.setCorrection(TypicalLEDStrip);

  // initialize bluetooth
  SerialBT.begin("ZeroLamp");

  randomSeed(analogRead(0) + analogRead(1) + 0xdeadbeef);

  initCurrentMode();

  Serial.println("Initialization complete.");
}

void loop() {

  handleBluetooth();

  switch (currentMode) {
    
    case MODE_RAINBOW:
      modeRainbow();
      break;

    case MODE_FILL:
      modeFill();
      break;

    case MODE_FIRE:
      modeFire();
      break;

    case MODE_SNOW:
      modeSnow();
      break;

    case MODE_INFO:
      modeInfo();
      break;

    case MODE_SNAKE:
      modeSnake();
      break;

    default:
      break;
  }

}

// ----------------- Modes -----------------

// ----------------- Rainbow mode -----------------

uint8_t modeRainbowHue = 0;

void modeRainbow() {

  EVERY_N_MILLISECONDS(33) { // render at 30 FPS
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = 0; y < MATRIX_HEIGHT; y++) {
        leds[ledId(y, x)] = CHSV(modeRainbowHue + y * 5, 255, 255);
      }
    }

    FastLED.show();

    modeRainbowHue++;
  }

}

// ----------------- Fill mode -----------------

CRGB modeFillColor = CRGB::Red;

void modeFill() {

  EVERY_N_MILLISECONDS(500) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = 0; y < MATRIX_HEIGHT; y++) {
        leds[ledId(y, x)] = modeFillColor;
      }
    }

    FastLED.show();
  }

}

// ----------------- Fire mode -----------------

byte modeFireHeat[MATRIX_WIDTH][MATRIX_HEIGHT] = {0};

CRGB temperatureToColor(byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // Scale to red, green, and blue components based on heat level
  if (t192 <= 63) {
    return CRGB(t192 * 4, 0, 0);  // Rises from black to red
  }
  
  if (t192 <= 127) {
    return CRGB(255, (t192 - 63) * 4, 0);  // Rises from red to yellow
  }
  
  return CRGB(255, 255, (t192 - 127) * 4);  // Rises from yellow to white
}

void modeFire() {
  EVERY_N_MILLISECONDS(33) {

    // Step 1: Cool down every cell a little
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = 0; y < MATRIX_HEIGHT; y++) {
        modeFireHeat[x][y] = max(0l, modeFireHeat[x][y] - random(20, 35));
      }
    }

    // Step 2: Heat rises up, diffusing upwards and slightly sideways
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = MATRIX_HEIGHT - 1; y > 0; y--) {
        modeFireHeat[x][y] = (
          modeFireHeat[x][y - 1] + modeFireHeat[x][max(0, y - 2)] +
          modeFireHeat[max(0, x - 1)][y - 1] + 
          modeFireHeat[min(MATRIX_WIDTH - 1, x + 1)][y - 1]
        ) / 4;
      }
    }

    // Step 3: Randomly ignite new heat at the bottom row
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      if (random(0, 10) > 5) {  // Adjust the probability of ignition
        modeFireHeat[x][0] = min(255l, modeFireHeat[x][0] + random(160, 255));
      }
    }

    // Step 4: Map heat values to colors and assign them to LEDs
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = 0; y < MATRIX_HEIGHT; y++) {
        CRGB color = temperatureToColor(modeFireHeat[x][y]);
        leds[ledId(MATRIX_HEIGHT - 1 - y, x)] = color;
      }
    }

    FastLED.show();
  }
}

// ----------------- Snow mode -----------------

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

// ----------------- Info mode -----------------

// A simple 5x7 font (ASCII characters 32-127). Each byte is a row in the 5x7 grid.
const uint8_t font5x7[][5] = {
  {0x00, 0x00, 0x00, 0x00, 0x00}, //   0x20 32
  {0x00, 0x00, 0x6f, 0x00, 0x00}, // ! 0x21 33
  {0x00, 0x07, 0x00, 0x07, 0x00}, // " 0x22 34
  {0x14, 0x7f, 0x14, 0x7f, 0x14}, // # 0x23 35
  {0x00, 0x07, 0x04, 0x1e, 0x00}, // $ 0x24 36
  {0x23, 0x13, 0x08, 0x64, 0x62}, // % 0x25 37
  {0x36, 0x49, 0x56, 0x20, 0x50}, // & 0x26 38
  {0x00, 0x00, 0x07, 0x00, 0x00}, // ' 0x27 39
  {0x00, 0x1c, 0x22, 0x41, 0x00}, // ( 0x28 40
  {0x00, 0x41, 0x22, 0x1c, 0x00}, // ) 0x29 41
  {0x14, 0x08, 0x3e, 0x08, 0x14}, // * 0x2a 42
  {0x08, 0x08, 0x3e, 0x08, 0x08}, // + 0x2b 43
  {0x00, 0x50, 0x30, 0x00, 0x00}, // , 0x2c 44
  {0x08, 0x08, 0x08, 0x08, 0x08}, // - 0x2d 45
  {0x00, 0x60, 0x60, 0x00, 0x00}, // . 0x2e 46
  {0x20, 0x10, 0x08, 0x04, 0x02}, // / 0x2f 47
  {0x3e, 0x51, 0x49, 0x45, 0x3e}, // 0 0x30 48
  {0x00, 0x42, 0x7f, 0x40, 0x00}, // 1 0x31 49
  {0x42, 0x61, 0x51, 0x49, 0x46}, // 2 0x32 50
  {0x21, 0x41, 0x45, 0x4b, 0x31}, // 3 0x33 51
  {0x18, 0x14, 0x12, 0x7f, 0x10}, // 4 0x34 52
  {0x27, 0x45, 0x45, 0x45, 0x39}, // 5 0x35 53
  {0x3c, 0x4a, 0x49, 0x49, 0x30}, // 6 0x36 54
  {0x01, 0x71, 0x09, 0x05, 0x03}, // 7 0x37 55
  {0x36, 0x49, 0x49, 0x49, 0x36}, // 8 0x38 56
  {0x06, 0x49, 0x49, 0x29, 0x1e}, // 9 0x39 57
  {0x00, 0x36, 0x36, 0x00, 0x00}, // : 0x3a 58
  {0x00, 0x56, 0x36, 0x00, 0x00}, // ; 0x3b 59
  {0x08, 0x14, 0x22, 0x41, 0x00}, // < 0x3c 60
  {0x14, 0x14, 0x14, 0x14, 0x14}, // = 0x3d 61
  {0x00, 0x41, 0x22, 0x14, 0x08}, // > 0x3e 62
  {0x02, 0x01, 0x51, 0x09, 0x06}, // ? 0x3f 63
  {0x3e, 0x41, 0x5d, 0x49, 0x4e}, // @ 0x40 64
  {0x7e, 0x09, 0x09, 0x09, 0x7e}, // A 0x41 65
  {0x7f, 0x49, 0x49, 0x49, 0x36}, // B 0x42 66
  {0x3e, 0x41, 0x41, 0x41, 0x22}, // C 0x43 67
  {0x7f, 0x41, 0x41, 0x41, 0x3e}, // D 0x44 68
  {0x7f, 0x49, 0x49, 0x49, 0x41}, // E 0x45 69
  {0x7f, 0x09, 0x09, 0x09, 0x01}, // F 0x46 70
  {0x3e, 0x41, 0x49, 0x49, 0x7a}, // G 0x47 71
  {0x7f, 0x08, 0x08, 0x08, 0x7f}, // H 0x48 72
  {0x00, 0x41, 0x7f, 0x41, 0x00}, // I 0x49 73
  {0x20, 0x40, 0x41, 0x3f, 0x01}, // J 0x4a 74
  {0x7f, 0x08, 0x14, 0x22, 0x41}, // K 0x4b 75
  {0x7f, 0x40, 0x40, 0x40, 0x40}, // L 0x4c 76
  {0x7f, 0x02, 0x0c, 0x02, 0x7f}, // M 0x4d 77
  {0x7f, 0x04, 0x08, 0x10, 0x7f}, // N 0x4e 78
  {0x3e, 0x41, 0x41, 0x41, 0x3e}, // O 0x4f 79
  {0x7f, 0x09, 0x09, 0x09, 0x06}, // P 0x50 80
  {0x3e, 0x41, 0x51, 0x21, 0x5e}, // Q 0x51 81
  {0x7f, 0x09, 0x19, 0x29, 0x46}, // R 0x52 82
  {0x46, 0x49, 0x49, 0x49, 0x31}, // S 0x53 83
  {0x01, 0x01, 0x7f, 0x01, 0x01}, // T 0x54 84
  {0x3f, 0x40, 0x40, 0x40, 0x3f}, // U 0x55 85
  {0x0f, 0x30, 0x40, 0x30, 0x0f}, // V 0x56 86
  {0x3f, 0x40, 0x30, 0x40, 0x3f}, // W 0x57 87
  {0x63, 0x14, 0x08, 0x14, 0x63}, // X 0x58 88
  {0x07, 0x08, 0x70, 0x08, 0x07}, // Y 0x59 89
  {0x61, 0x51, 0x49, 0x45, 0x43}, // Z 0x5a 90
  {0x3c, 0x4a, 0x49, 0x29, 0x1e}, // [ 0x5b 91
  {0x02, 0x04, 0x08, 0x10, 0x20}, // \ 0x5c 92
  {0x00, 0x41, 0x7f, 0x00, 0x00}, // ] 0x5d 93
  {0x04, 0x02, 0x01, 0x02, 0x04}, // ^ 0x5e 94
  {0x40, 0x40, 0x40, 0x40, 0x40}, // _ 0x5f 95
  {0x00, 0x00, 0x03, 0x04, 0x00}, // ` 0x60 96
  {0x20, 0x54, 0x54, 0x54, 0x78}, // a 0x61 97
  {0x7f, 0x48, 0x44, 0x44, 0x38}, // b 0x62 98
  {0x38, 0x44, 0x44, 0x44, 0x20}, // c 0x63 99
  {0x38, 0x44, 0x44, 0x48, 0x7f}, // d 0x64 100
  {0x38, 0x54, 0x54, 0x54, 0x18}, // e 0x65 101
  {0x08, 0x7e, 0x09, 0x01, 0x02}, // f 0x66 102
  {0x0c, 0x52, 0x52, 0x52, 0x3e}, // g 0x67 103
  {0x7f, 0x08, 0x04, 0x04, 0x78}, // h 0x68 104
  {0x00, 0x44, 0x7d, 0x40, 0x00}, // i 0x69 105
  {0x20, 0x40, 0x44, 0x3d, 0x00}, // j 0x6a 106
  {0x00, 0x7f, 0x10, 0x28, 0x44}, // k 0x6b 107
  {0x00, 0x41, 0x7f, 0x40, 0x00}, // l 0x6c 108
  {0x7c, 0x04, 0x18, 0x04, 0x78}, // m 0x6d 109
  {0x7c, 0x08, 0x04, 0x04, 0x78}, // n 0x6e 110
  {0x38, 0x44, 0x44, 0x44, 0x38}, // o 0x6f 111
  {0x7c, 0x14, 0x14, 0x14, 0x08}, // p 0x70 112
  {0x08, 0x14, 0x14, 0x18, 0x7c}, // q 0x71 113
  {0x7c, 0x08, 0x04, 0x04, 0x08}, // r 0x72 114
  {0x48, 0x54, 0x54, 0x54, 0x20}, // s 0x73 115
  {0x04, 0x3f, 0x44, 0x40, 0x20}, // t 0x74 116
  {0x3c, 0x40, 0x40, 0x20, 0x7c}, // u 0x75 117
  {0x1c, 0x20, 0x40, 0x20, 0x1c}, // v 0x76 118
  {0x3c, 0x40, 0x30, 0x40, 0x3c}, // w 0x77 119
  {0x44, 0x28, 0x10, 0x28, 0x44}, // x 0x78 120
  {0x0c, 0x50, 0x50, 0x50, 0x3c}, // y 0x79 121
  {0x44, 0x64, 0x54, 0x4c, 0x44}, // z 0x7a 122
  {0x00, 0x08, 0x36, 0x41, 0x41}, // { 0x7b 123
  {0x00, 0x00, 0x7f, 0x00, 0x00}, // | 0x7c 124
  {0x41, 0x41, 0x36, 0x08, 0x00}, // } 0x7d 125
  {0x04, 0x02, 0x04, 0x08, 0x04}, // ~ 0x7e 126
};

String textToShow = "ZeroBone is cool!";

void drawChar(int xOffset, char c, CRGB color) {
  if (c < 32 || c > 126) return; // Unsupported character
  const uint8_t* charBitmap = font5x7[c - 32];
  for (int col = 0; col < 5; col++) {
    for (int row = 0; row < 7; row++) {
      if (charBitmap[col] & (1 << row)) {
        int x = xOffset + col;
        int y = row + 4; // Center vertically
        // Serial.printf("x = %2d  y = %2d\n", x, y);
        if (x >= 0 && x < MATRIX_WIDTH && y >= 0 && y < MATRIX_HEIGHT) {
          leds[ledId(y, x)] = color;
        }
      }
    }
  }
}

int textPosition = MATRIX_WIDTH;

void modeInfoInit() {
  textPosition = MATRIX_WIDTH;
}

void modeInfo() {

  EVERY_N_MILLISECONDS(100) {

    FastLED.clear(false);

    int x = textPosition;
    for (int i = 0; textToShow[i] != '\0'; i++) {
      drawChar(x, textToShow[i], CRGB::White);
      x += 6; // 5 pixels for character + 1 pixel spacing
    }

    FastLED.show();

    textPosition--;
    if (textPosition < -6 * (int)textToShow.length()) {
      textPosition = MATRIX_WIDTH; // Reset position
    }
  }

}

// ----------------- Snake game mode -----------------

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

#define SNAKE_DIRECTION_UP 0
#define SNAKE_DIRECTION_DOWN 1
#define SNAKE_DIRECTION_LEFT 2
#define SNAKE_DIRECTION_RIGHT 3

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

// ----------------- Bluetooth -----------------

String bluetoothMessage = "";

void handleBluetooth() {

  bool reachedEndOfMessage = false;

  while (SerialBT.available()) {

    char c = SerialBT.read();

    if (c == '\r') {
      continue;
    }

    if (c == '\n') {
      reachedEndOfMessage = true;
      break;
    }
    
    bluetoothMessage += String(c);
    
  }

  if (reachedEndOfMessage && !bluetoothMessage.isEmpty()) {
    handleBluetoothCommand(bluetoothMessage);
    bluetoothMessage = "";
  }

}

void handleBluetoothCommand(String command) {
  if (command.equalsIgnoreCase("next")) {
    nextMode();
    return;
  }
  
  if (command.equalsIgnoreCase("prev")) {
    prevMode();
    return;
  }

  if (command.substring(0, 4).equalsIgnoreCase("fill")) {

    String remainder = command.substring(4);
    remainder.trim();

    CRGB color;

    if (remainder.isEmpty()) {
      SerialBT.println("Using random color because no color was specified.");
      color = CHSV(random8(), 0xff, 0xff);
    }
    else {
      bool success = parseColorSpec(remainder, color);
      if (!success) {
        SerialBT.printf("Error. Invalid color syntax. Using random color.\n", remainder);
        color = CHSV(random8(), 0xff, 0xff);
      }
    }

    modeFillColor = color;

    switchMode(MODE_FILL);
    return;
  }

  if (command.equalsIgnoreCase("rainbow")) {
    switchMode(MODE_RAINBOW);
    return;
  }

  if (command.equalsIgnoreCase("fire")) {
    switchMode(MODE_FIRE);
    return;
  }

  if (command.equalsIgnoreCase("snow")) {
    switchMode(MODE_SNOW);
    return;
  }

  if (command.substring(0, 4).equalsIgnoreCase("info")) {
    String remainder = command.substring(4);
    remainder.trim();

    if (!remainder.isEmpty()) {
      textToShow = remainder;
    }
    
    switchMode(MODE_INFO);
    return;
  }
  
  if (command.equalsIgnoreCase("snake")) {
    switchMode(MODE_SNAKE);
    return;
  }

  if (currentMode == MODE_SNAKE && 
        (command.equalsIgnoreCase("w") || command.equalsIgnoreCase("s") || command.equalsIgnoreCase("a") || command.equalsIgnoreCase("d"))
      ) {

    if (command.equalsIgnoreCase("w") && snakeMovementDirection != SNAKE_DIRECTION_DOWN) snakeMovementDirection = SNAKE_DIRECTION_UP;
    else if (command.equalsIgnoreCase("s") && snakeMovementDirection != SNAKE_DIRECTION_UP) snakeMovementDirection = SNAKE_DIRECTION_DOWN;
    else if (command.equalsIgnoreCase("a") && snakeMovementDirection != SNAKE_DIRECTION_RIGHT) snakeMovementDirection = SNAKE_DIRECTION_LEFT;
    else if (command.equalsIgnoreCase("d") && snakeMovementDirection != SNAKE_DIRECTION_LEFT) snakeMovementDirection = SNAKE_DIRECTION_RIGHT;

    return;
  }

  SerialBT.printf("Error. Unknown command '%s'.\n", command);
}

// ----------------- Utility functions -----------------

bool parseColorSpec(String colorSpec, CRGB &result) {
  colorSpec.trim();

  if (colorSpec.startsWith("#")) {
    // Hex color code
    
    if (colorSpec.length() == 7) {
      // #RRGGBB
      uint8_t r = strtol(colorSpec.substring(1, 3).c_str(), nullptr, 16);
      uint8_t g = strtol(colorSpec.substring(3, 5).c_str(), nullptr, 16);
      uint8_t b = strtol(colorSpec.substring(5, 7).c_str(), nullptr, 16);
      result = CRGB(r, g, b);
      return true;
    }
    
    if (colorSpec.length() == 4) {
      // #RGB (shorthand)
      uint8_t r = strtol(colorSpec.substring(1, 2).c_str(), nullptr, 16) * 17; // Scale to 0-255
      uint8_t g = strtol(colorSpec.substring(2, 3).c_str(), nullptr, 16) * 17;
      uint8_t b = strtol(colorSpec.substring(3, 4).c_str(), nullptr, 16) * 17;
      result = CRGB(r, g, b);
      return true;
    }

    return false; // invalid syntax
  }
  
  if (colorSpec.equalsIgnoreCase("red")) {
    result = CRGB::Red;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("green")) {
    result = CRGB::Green;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("blue")) {
    result = CRGB::Blue;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("black")) {
    result = CRGB::Black;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("white")) {
    result = CRGB::White;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("yellow")) {
    result = CRGB::Yellow;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("cyan")) {
    result = CRGB::Cyan;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("magenta")) {
    result = CRGB::Magenta;
    return true;
  }
  if (colorSpec.equalsIgnoreCase("orange")) {
    result = CRGB(255, 165, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("purple")) {
    result = CRGB(128, 0, 128);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("pink")) {
    result = CRGB(255, 192, 203);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("brown")) {
    result = CRGB(165, 42, 42);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("lime")) {
    result = CRGB(0, 255, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("indigo")) {
    result = CRGB(75, 0, 130);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("violet")) {
    result = CRGB(238, 130, 238);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("gold")) {
    result = CRGB(255, 215, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("silver")) {
    result = CRGB(192, 192, 192);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("gray") || colorSpec.equalsIgnoreCase("grey")) {
    result = CRGB(128, 128, 128);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("navy")) {
    result = CRGB(0, 0, 128);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("teal")) {
    result = CRGB(0, 128, 128);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("olive")) {
    result = CRGB(128, 128, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("maroon")) {
    result = CRGB(128, 0, 0);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("aqua")) {
    result = CRGB(0, 255, 255);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("beige")) {
    result = CRGB(245, 245, 220);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("coral")) {
    result = CRGB(255, 127, 80);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("chocolate")) {
    result = CRGB(210, 105, 30);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("khaki")) {
    result = CRGB(240, 230, 140);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("salmon")) {
    result = CRGB(250, 128, 114);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("orchid")) {
    result = CRGB(218, 112, 214);
    return true;
  }
  if (colorSpec.equalsIgnoreCase("turquoise")) {
    result = CRGB(64, 224, 208);
    return true;
  }

  // parsing failed
  return false;
}

void initCurrentMode() {
  switch (currentMode) {
    case MODE_SNOW:
      modeSnowInit();
      break;

    case MODE_INFO:
      modeInfoInit();
      break;

    case MODE_SNAKE:
      modeSnakeInit();
      break;

    default:
      break;
  }
}

void switchMode(int newMode) {
  FastLED.clear(false);
  currentMode = newMode;
  initCurrentMode();
}

void nextMode() {
  int newMode = (currentMode + 1) % MODES_COUNT;
  switchMode(newMode);
}

void prevMode() {
  int newMode;
  if (currentMode == 0) newMode = MODES_COUNT - 1;
  else newMode = currentMode - 1;
  switchMode(newMode);
}
