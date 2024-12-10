#include "modes.h"
#include <Arduino.h>
#include "mode.h"
// #include "queue.h"
#include "matrix.h"
#include "mode_random.h"

// VectorQueue<LampMode*, MODES_QUEUE_SIZE> modes_queue;

LampMode* current_mode = nullptr;

void modes_init() {
  current_mode = new RandomMode();
}

unsigned long lastFrameRenderTime = 0;

void modes_tick() {

  unsigned long currentMillis = millis();

  if (currentMillis - lastFrameRenderTime < 500) {
    // no need to render frame
    return;
  }

  lastFrameRenderTime = currentMillis;

  current_mode->render_frame();

  matrix_render();

}