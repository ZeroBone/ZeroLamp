#include "program.h"
#include "bluetooth.h"
#include <FastLED.h>
#include <Arduino.h>

void ProgramExecutor::tick() {
  event_tick();
  render_tick();
}

void ProgramExecutor::event_tick() {
  // fire events if needed
  if (bg != nullptr) {
    bg->event_tick();
  }

  if (fg != nullptr) {
    fg->event_tick();
  }
}

void ProgramExecutor::render_tick() {
  // render frames

  unsigned long current_time = millis();

  bool bg_render = false; // show we render the background mode frame?
  bool fg_render = false; // show we render the foreground mode frame?

  // check whether we need to render background mode frame
  if (bg != nullptr && fg_viewport_width != MATRIX_WIDTH && current_time - bg_lastFrameRenderTime >= bg->get_render_interval()) {
    bg_render = true;
    bg_lastFrameRenderTime = current_time;
  }

  // check whether we need to render foreground mode frame
  if (fg != nullptr && fg_viewport_width != 0 && current_time - fg_lastFrameRenderTime >= fg->get_render_interval()) {
    fg_render = true;
    fg_lastFrameRenderTime = current_time;
  }

  // render frame if needed

  if (!bg_render && !fg_render) {
    // no rendering to be done
    return;
  }

  if (bg_render) {
    assert(bg != nullptr);
    assert(fg_viewport_width != MATRIX_WIDTH);

    int bg_offset_x = fg_offset_x + fg_viewport_width;
    int bg_viewport_width = MATRIX_WIDTH - fg_viewport_width;

    assert(bg_viewport_width > 0 && bg_viewport_width <= MATRIX_WIDTH);

    // clear pixels
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      for (int x = 0; x < bg_viewport_width; x++) {
        matrix_clearLed(y, bg_offset_x + x);
      }
    }

    // render frame
    bg->render_frame(
      bg_offset_x,
      0,
      bg_viewport_width,
      MATRIX_HEIGHT
    );
  }

  if (fg_render) {
    assert(fg != nullptr);
    assert(fg_viewport_width > 0);

    // clear pixels
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      for (int x = 0; x < fg_viewport_width; x++) {
        matrix_clearLed(y, fg_offset_x + x);
      }
    }

    // render frame
    fg->render_frame(
      fg_offset_x,
      0,
      fg_viewport_width,
      MATRIX_HEIGHT
    );
  }

  FastLED.show();
}

void Program::handle_command(std::string command) {

  CommandHandleResult hr;

  // prioritize the foreground mode
  if (fg != nullptr) {
    hr = fg->handle_command(command);
    if (hr == CommandHandleResult::HANDLED) {
      return;
    }
  }

  if (bg != nullptr) {
    hr = bg->handle_command(command);
    if (hr == CommandHandleResult::HANDLED) {
      return;
    }
  }

  // tell the user that they sent an unknown command
  bluetooth_serial()->println("Unknown command or invalid syntax.");

}

void ProgramExecutor::destroy() {
  if (bg != nullptr) {
    delete bg;
  }
  
  if (fg != nullptr) {
    delete fg;
  }
}