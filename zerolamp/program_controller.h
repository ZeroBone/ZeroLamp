#ifndef ZB_PROGRAM_CONTROLLER_H
#define ZB_PROGRAM_CONTROLLER_H

#include <string>

void program_controller_init();
void program_controller_handle_command(std::string command);
void program_controller_tick();

#endif