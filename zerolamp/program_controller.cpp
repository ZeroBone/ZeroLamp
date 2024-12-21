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

std::unordered_map<std::string, ProgramExecutor> programs; // programs that are currently loaded in memory and running
std::string current_program = "sort_fg";

void program_controller_init() {

  programs["sort"] = ProgramExecutor(
    new SortMode(), // background
    nullptr, // foreground
    0, // foreground offset in the x direction
    0 // foreground viewport width
  );

  programs["snowfall"] = ProgramExecutor(
    new SnowfallMode(), // background
    nullptr, // foreground
    0, // foreground offset in the x direction
    0 // foreground viewport width
  );

  programs["simplex"] = ProgramExecutor(
    new SimplexMode(), // background
    nullptr, // foreground
    0, // foreground offset in the x direction
    0 // foreground viewport width
  );

  programs["random"] = ProgramExecutor(
    new RandomMode(), // background
    nullptr, // foreground
    0, // foreground offset in the x direction
    0 // foreground viewport width
  );

  programs["rainbow"] = ProgramExecutor(
    new RainbowMode(), // background
    nullptr, // foreground
    0, // foreground offset in the x direction
    0 // foreground viewport width
  );

  programs["fire"] = ProgramExecutor(
    new FireMode(), // background
    nullptr, // foreground
    0, // foreground offset in the x direction
    0 // foreground viewport width
  );

  programs["conway"] = ProgramExecutor(
    new ConwayMode(), // background
    nullptr, // foreground
    0, // foreground offset in the x direction
    0 // foreground viewport width
  );

  // games

  programs["clock_fire"] = ProgramExecutor(
    new FireMode(), // background
    new ClockMode(), // foreground
    6, // foreground offset in the x direction
    6 // foreground viewport width
  );

  programs["snake_fire"] = ProgramExecutor(
    new SnakeMode(), // background
    new FireMode(), // foreground
    6, // foreground offset in the x direction
    6 // foreground viewport width
  );

  programs["maze_simplex"] = ProgramExecutor(
    new SimplexMode(), // background
    new MazeMode(10, 10), // foreground
    6, // foreground offset in the x direction
    6 // foreground viewport width
  );

  programs["sort_fg"] = ProgramExecutor(
    new SimplexMode(), // background
    new SortMode(), // foreground
    6, // foreground offset in the x direction
    6 // foreground viewport width
  );

}

void program_controller_handle_command(std::string command) {
  programs[current_program].handle_command(std::move(command));
}

void program_controller_tick() {
  programs[current_program].tick();
}