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