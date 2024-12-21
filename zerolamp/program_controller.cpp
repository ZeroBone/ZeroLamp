#include "program_controller.h"
#include "program_executor.h"
#include <unordered_map>

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

// std::unordered_map<std::string, Program> loaded_programs; // programs that are currently loaded in memory and running
// std::string current_program = "maze_fire";
ProgramExecutor executor;

void program_controller_init() {}

void program_controller_handle_command(std::string command) {
  executor.handle_command(std::move(command));
}

void program_controller_tick() {
  executor.tick();
}