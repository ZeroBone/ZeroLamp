#ifndef ZB_PROGRAM_EXECUTOR_H
#define ZB_PROGRAM_EXECUTOR_H

#include "instruction.h"
#include "mode.h"
#include "matrix.h"
#include "program.h"

class ProgramExecutor {

private:
  // program
  Program program;

  // pointer to background mode currently running
  // nullptr means no background mode has been started
  // the following invariants are to be maintained
  // (IBG1) if bg != nullptr and fg_viewport_width != MATRIX_WIDTH then bg should be initialized (i.e., bg->enter() should have been called)
  LampMode* bg = nullptr;
  int bg_logical_width; // the logical width used to initialize bg, garbage if bg is nullptr

  // the following invariants are to be maintained
  // (IFG1) if fg != nullptr and fg_viewport_width != 0 then fg should be initialized (i.e., fg->enter() should have been called)
  LampMode* fg = nullptr;
  int fg_logical_width; // the logical width used to initialize fg, garbage if bg is nullptr

  unsigned long bg_lastFrameRenderTime = 0;
  unsigned long fg_lastFrameRenderTime = 0;

  int fg_offset_x = 5;
  int fg_viewport_width = 0;

private:
  inline void establish_ibg1() {
    // establish invariant (IBG1)
    if (bg != nullptr && fg_viewport_width != MATRIX_WIDTH) {
      // if the foreground mode is not fullscreen
      bg->enter(
        MATRIX_WIDTH - fg_viewport_width, // logical width
        MATRIX_HEIGHT // logical height
      );
      bg_logical_width = MATRIX_WIDTH - fg_viewport_width;
    }
  }

  inline void establish_ifg1() {
    // establish invariant (IFG1)
    if (fg != nullptr && fg_viewport_width != 0) {
      fg->enter(
        fg_viewport_width, // logical width
        MATRIX_HEIGHT
      );
      fg_logical_width = fg_viewport_width;
    }
  }

public:

  ProgramExecutor() {}

  ProgramExecutor(LampMode* bg, LampMode* fg, int fg_offset_x, int fg_viewport_width) : bg(bg), fg(fg), fg_offset_x(fg_offset_x), fg_viewport_width(fg_viewport_width) {
    assert(fg_offset_x >= 0);
    assert(fg_viewport_width >= 0 && fg_viewport_width <= MATRIX_WIDTH);

    establish_ibg1();
    establish_ifg1();
  }

  inline int get_foreground_viewport_width() {
    return fg_viewport_width;
  }

  void set_background(LampMode* new_bg);
  void set_foreground(LampMode* new_fg);
  void set_foreground_viewport_width(int new_fg_viewport_width);

  void tick();
  void handle_command(std::string command);
  void destroy();

private:
  void event_tick();
  void render_tick();

};

#endif