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