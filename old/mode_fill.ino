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