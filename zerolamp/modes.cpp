#include "modes.h"
#include <Arduino.h>
#include "mode.h"
// #include "queue.h"
#include "matrix.h"
#include "bg_random.h"
#include "fg_clock.h"

// VectorQueue<LampMode*, MODES_QUEUE_SIZE> modes_queue;

LampMode* current_mode_bg;
LampMode* current_mode_fg = nullptr;

void modes_init() {
  current_mode_bg = new RandomBG();
  current_mode_bg->enter(11, MATRIX_HEIGHT);
  current_mode_fg = new ClockFG();
  current_mode_fg->enter(5, MATRIX_HEIGHT);
}

unsigned long lastFrameRenderTime = 0;

void modes_tick() {

  unsigned long currentMillis = millis();

  if (currentMillis - lastFrameRenderTime < 250) {
    // no need to render frame
    return;
  }

  lastFrameRenderTime = currentMillis;

  // render frame

  FastLED.clear(false);

  current_mode_bg->render_frame(0, 0, 11, MATRIX_HEIGHT);

  if (current_mode_fg != nullptr) {
    current_mode_fg->render_frame(11, 0, 5, MATRIX_HEIGHT);
  }

  FastLED.show();

}