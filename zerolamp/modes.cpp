#include "modes.h"
#include "mode.h"
#include "matrix.h"
#include "mode_fire.h"
#include "mode_maze.h"

// VectorQueue<LampMode*, MODES_QUEUE_SIZE> modes_queue;

LampMode* current_mode_bg;
LampMode* current_mode_fg = nullptr;

unsigned long current_mode_bg_lastFrameRenderTime = 0;
unsigned long current_mode_fg_lastFrameRenderTime = 0;

int current_mode_fg_offset_x = 12;
int current_mode_fg_viewport_width = 6;

void modes_init() {
  current_mode_bg = new FireMode();
  current_mode_bg->enter(10, MATRIX_HEIGHT);
  current_mode_fg = new MazeMode(10, 10);
  current_mode_fg->enter(6, MATRIX_HEIGHT);
}

void modes_handle_command(String command) {

  CommandHandleResult hr;

  if (current_mode_fg != nullptr) {
    hr = current_mode_fg->handle_command(command);
    if (hr == CommandHandleResult::HANDLED) {
      return;
    }
  }

  hr = current_mode_bg->handle_command(command);
  if (hr == CommandHandleResult::HANDLED) {
    return;
  }

  // TODO: tell the user that they sent an unknown command

}

void modes_tick() {

  unsigned long current_time = millis();

  bool bg_render = false; // show we render the background mode frame?
  bool fg_render = false; // show we render the foreground mode frame?

  // check whether we need to render background mode frame
  if (current_time - current_mode_bg_lastFrameRenderTime >= current_mode_bg->get_render_interval()) {
    bg_render = true;
    current_mode_bg_lastFrameRenderTime = current_time;
  }

  // check whether we need to render foreground mode frame
  if (current_mode_fg != nullptr && current_time - current_mode_fg_lastFrameRenderTime >= current_mode_fg->get_render_interval()) {
    fg_render = true;
    current_mode_fg_lastFrameRenderTime = current_time;
  }

  // render frame if needed

  if (!bg_render && !fg_render) {
    // no rendering to be done
    return;
  }

  if (bg_render) {

    int bg_offset_x = current_mode_fg_offset_x + current_mode_fg_viewport_width;
    int bg_viewport_width = MATRIX_WIDTH - current_mode_fg_viewport_width;

    // clear pixels
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      for (int x = 0; x < bg_viewport_width; x++) {
        matrix_clearLed(y, bg_offset_x + x);
      }
    }

    // render frame
    current_mode_bg->render_frame(
      bg_offset_x,
      0,
      bg_viewport_width,
      MATRIX_HEIGHT
    );
  }

  if (fg_render) {
    assert(current_mode_fg != nullptr);

    // clear pixels
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      for (int x = 0; x < current_mode_fg_viewport_width; x++) {
        matrix_clearLed(y, current_mode_fg_offset_x + x);
      }
    }

    // render frame
    current_mode_fg->render_frame(current_mode_fg_offset_x, 0, current_mode_fg_viewport_width, MATRIX_HEIGHT);
  }

  FastLED.show();

}