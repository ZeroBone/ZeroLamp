#include <FastLED.h>
#include <BluetoothSerial.h>

// Matrix configuration
#define CURRENT_LIMIT 2000 // maximum current in milliamps
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 19 // GPIO pin connected to WS2812B matrix

// LED array
CRGB leds[NUM_LEDS];

// Matrix width and height
const int MATRIX_WIDTH = 16;
const int MATRIX_HEIGHT = 16;

// Modes
#define MODE_RAINBOW 0
#define MODE_FILL 1
#define MODE_FIRE 2
#define MODE_SNOW 3
#define MODE_INFO 4
#define MODE_SNAKE 5

#define MODES_COUNT 6
#define DEFAULT_MODE MODE_FIRE

#define SNAKE_DIRECTION_UP 0
#define SNAKE_DIRECTION_DOWN 1
#define SNAKE_DIRECTION_LEFT 2
#define SNAKE_DIRECTION_RIGHT 3

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
