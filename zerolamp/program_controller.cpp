#include "program_controller.h"
#include "program_executor.h"
#include "bluetooth.h"
// #include <unordered_map>
#include "lexer.h"
#include "parser.h"

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
#include "mode_info.h"

// std::unordered_map<std::string, Program> loaded_programs; // programs that are currently loaded in memory and running
// std::string current_program = "maze_fire";
ProgramExecutor executor;

void program_controller_init() {

  LampMode* bg;

  uint8_t r = random8(7);

  switch (r) {
    case 0: bg = new SortMode(); break;
    case 1: bg = new SnowfallMode(); break;
    case 2: bg = new SimplexMode(); break;
    case 3: bg = new RandomMode(); break;
    case 4: bg = new RainbowMode(); break;
    case 5: bg = new FireMode(); break;
    case 6: bg = new ConwayMode(); break;
    default:
      assert(false);
      break;
  }

  executor.set_background(bg);

  executor.set_foreground(new ClockMode());
  executor.set_foreground_viewport_width(6);

}

LampMode* initialize_mode(std::string mode_name) {

  if (mode_name == "sort") {
    return new SortMode();
  }

  if (mode_name == "snowfall") {
    return new SnowfallMode();
  }

  if (mode_name == "simplex") {
    return new SimplexMode();
  }

  if (mode_name == "random") {
    return new RandomMode();
  }

  if (mode_name == "rainbow") {
    return new RainbowMode();
  }

  if (mode_name == "fire") {
    return new FireMode();
  }

  if (mode_name == "conway") {
    return new ConwayMode();
  }

  if (mode_name == "clock") {
    return new ClockMode();
  }

  if (mode_name == "snake") {
    return new SnakeMode();
  }

  if (mode_name == "maze") {
    return new MazeMode(10, 10);
  }

  if (mode_name == "fill") {
    return new FillMode();
  }

  return nullptr;

}

bool on = true;

void program_controller_handle_command(std::string command) {

  Lexer lexer(command);
  Parser parser;

  if (parser.successfullyParsed()) {
    bluetooth_serial()->println("Success.");
  }
  else {
    bluetooth_serial()->println("Error.");
  }

  // TODO: remove old controller

  if (command == "on" && !on) {
    on = true;
    bluetooth_serial()->println("Turned lamp on.");
    return;
  }
  else if (command == "off" && on) {
    on = false;
    FastLED.clear(true);
    bluetooth_serial()->println("Turned lamp off.");
    return;
  }

  if (command == "bg") {
    executor.set_background(nullptr);
    return;
  }

  if (command.starts_with("bg ")) {

    std::string mode_name = command.substr(3);
    
    LampMode* new_background = initialize_mode(mode_name);

    if (new_background == nullptr) {
      bluetooth_serial()->printf("Unknown mode '%s'.", mode_name.c_str());
      return;
    }

    executor.set_background(new_background);

    bluetooth_serial()->printf("Changed background to '%s'.", mode_name.c_str());

    return;
  }

  if (command == "fg") {
    executor.set_foreground(nullptr);
    return;
  }
  
  if (command.starts_with("fg ")) {

    std::string mode_name = command.substr(3);

    int input_number = 0;
    bool is_number = true;
    for (char c : mode_name) {
      if (c >= '0' && c <= '9') {
        input_number *= 10;
        input_number += c - '0';
      }
      else {
        is_number = false;
        break;
      }
    }

    if (is_number) {

      if (input_number < 3) {
        bluetooth_serial()->printf("Error. The specified width (%d) is too small.", input_number);
        return;
      }

      if (input_number > MATRIX_WIDTH) {
        bluetooth_serial()->printf("Error. The specified width (%d) exceeds the matrix width.", input_number);
        return;
      }

      executor.set_foreground_viewport_width(input_number);

      return;
    }
    
    LampMode* new_foreground = initialize_mode(mode_name);

    if (new_foreground == nullptr) {
      bluetooth_serial()->printf("Unknown mode '%s'.", mode_name.c_str());
      return;
    }

    executor.set_foreground(new_foreground);

    if (executor.get_foreground_viewport_width() == 0) {
      executor.set_foreground_viewport_width(6);
    }

    bluetooth_serial()->printf("Changed foreground to '%s'.", mode_name.c_str());

    return;
  }

  if (command.starts_with("w ")) {
    std::string message = command.substr(2);

    bool msg_valid = true;
    for (char c : message) {
      if (c < 32 || c > 126) {
        msg_valid = false;
      }
    }

    if (!msg_valid) {
      bluetooth_serial()->println("The message contains character(s) that are not yet supported. Please try again.");
      return;
    }

    executor.set_foreground(new InfoMode(message, "Happy Birthday!"));

    if (executor.get_foreground_viewport_width() == 0) {
      executor.set_foreground_viewport_width(6);
    }

    return;
  }

  executor.handle_command(std::move(command));
}

void program_controller_tick() {
  if (!on) {
    return;
  }
  executor.tick();
}