#ifndef ZB_PROGRAM_H
#define ZB_PROGRAM_H

#include <Arduino.h>
#include "instruction.h"
#include "mode.h"
#include "matrix.h"

class Program {

private:
  // program
  // std::vector<Instruction> instructions;
  // size_t instruction_pointer = 0; // pointer to the next instruction to be executed

  // current state of the program
  LampMode* bg = nullptr;
  LampMode* fg = nullptr;

  unsigned long bg_lastFrameRenderTime = 0;
  unsigned long fg_lastFrameRenderTime = 0;

  int fg_offset_x = 0;
  int fg_viewport_width = 0;

public:

  Program() {}

  Program(LampMode* bg, LampMode* fg, int fg_offset_x, int fg_viewport_width) : bg(bg), fg(fg), fg_offset_x(fg_offset_x), fg_viewport_width(fg_viewport_width) {
    assert(fg_offset_x >= 0);
    assert(fg_viewport_width >= 0 && fg_viewport_width <= MATRIX_WIDTH);

    if (bg != nullptr && fg_viewport_width != MATRIX_WIDTH) {
      // if the foreground mode is not fullscreen
      bg->enter(
        MATRIX_WIDTH - fg_viewport_width, // logical width
        MATRIX_HEIGHT // logical height
      );
    }
    
    if (fg != nullptr && fg_viewport_width != 0) {
      fg->enter(
        fg_viewport_width, // logical width
        MATRIX_HEIGHT
      );
    }

  }

  ~Program() {

    // TODO
    
    /*if (bg != nullptr) {
      delete bg;
    }
    
    if (fg != nullptr) {
      delete fg;
    }*/

  }

  void tick();
  void handle_command(String command);

private:
  void event_tick();
  void render_tick();

};

#endif