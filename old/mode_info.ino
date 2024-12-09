String textToShow = "ZeroBone is cool!";

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