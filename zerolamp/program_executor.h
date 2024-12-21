#ifndef ZB_PROGRAM_EXECUTOR_H
#define ZB_PROGRAM_EXECUTOR_H

#include "instruction.h"
#include "mode.h"
#include "matrix.h"

class ProgramExecutor {

private:
  // program
  // std::vector<Instruction> instructions;
  // size_t instruction_pointer = 0; // pointer to the next instruction to be executed

  // pointer to background mode currently running
  // nullptr means no background mode has been started
  // the following invariants are to be maintained
  // (IBG1) if bg != nullptr and fg_viewport_width != MATRIX_WIDTH then bg should be initialized (i.e., bg->enter() should have been called)
  LampMode* bg = nullptr;

  // the following invariants are to be maintained
  // (IFG1) if fg != nullptr and fg_viewport_width != 0 then fg should be initialized (i.e., fg->enter() should have been called)
  LampMode* fg = nullptr;

  unsigned long bg_lastFrameRenderTime = 0;
  unsigned long fg_lastFrameRenderTime = 0;

  int fg_offset_x = 0;
  int fg_viewport_width = 0;

public:

  ProgramExecutor() {}

  ProgramExecutor(LampMode* bg, LampMode* fg, int fg_offset_x, int fg_viewport_width) : bg(bg), fg(fg), fg_offset_x(fg_offset_x), fg_viewport_width(fg_viewport_width) {
    assert(fg_offset_x >= 0);
    assert(fg_viewport_width >= 0 && fg_viewport_width <= MATRIX_WIDTH);

    // establish invariant (IBG1)
    if (bg != nullptr && fg_viewport_width != MATRIX_WIDTH) {
      // if the foreground mode is not fullscreen
      bg->enter(
        MATRIX_WIDTH - fg_viewport_width, // logical width
        MATRIX_HEIGHT // logical height
      );
    }
    
    // establish invariant (IFG1)
    if (fg != nullptr && fg_viewport_width != 0) {
      fg->enter(
        fg_viewport_width, // logical width
        MATRIX_HEIGHT
      );
    }

  }

  void tick();
  void handle_command(std::string command);
  void destroy();

private:
  void event_tick();
  void render_tick();

};

#endif