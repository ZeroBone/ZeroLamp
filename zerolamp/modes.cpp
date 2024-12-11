#include "modes.h"
#include <Arduino.h>
#include "mode.h"
// #include "queue.h"
#include "matrix.h"
#include "bg_random.h"
#include "bg_snowfall.h"
#include "fg_clock.h"

// VectorQueue<LampMode*, MODES_QUEUE_SIZE> modes_queue;

LampMode* current_mode_bg;
LampMode* current_mode_fg = nullptr;

void modes_init() {
  current_mode_bg = new SnowfallBG();
  current_mode_bg->enter(10, MATRIX_HEIGHT);
  current_mode_fg = new ClockFG();
  current_mode_fg->enter(6, MATRIX_HEIGHT);
}

unsigned long lastFrameRenderTime = 0;

void modes_tick() {

  unsigned long currentMillis = millis();

  if (currentMillis - lastFrameRenderTime < 32) {
    // no need to render frame
    return;
  }

  lastFrameRenderTime = currentMillis;

  // render frame

  FastLED.clear(false);

  current_mode_bg->render_frame(2, 0, 10, MATRIX_HEIGHT);

  if (current_mode_fg != nullptr) {
    current_mode_fg->render_frame(12, 0, 6, MATRIX_HEIGHT);
  }

  FastLED.show();

}