#include "modes.h"
#include "program.h"
#include <string>

#include "mode_sort.h"
#include "mode_snowfall.h"
#include "mode_snake.h"
#include "mode_simplex.h"
#include "mode_random.h"
#include "mode_rainbow.h"
#include "mode_maze.h"
#include "mode_fire.h"
#include "mode_fill.h"
#include "mode_conway.h"
#include "mode_clock.h"

std::unordered_map<std::string, Program> programs;
std::string current_program = "fire";

void modes_init() {

  programs["fire"] = Program(
    new FireMode(), // background
    new ClockMode(), // foreground
    6, // foreground offset in the x direction
    6 // foreground viewport width
  );

}

void modes_handle_command(String command) {
  programs[current_program].handle_command(command);
}

void modes_tick() {
  programs[current_program].tick();
}