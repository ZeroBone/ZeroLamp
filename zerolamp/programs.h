#ifndef ZB_PROGRAMS_H
#define ZB_PROGRAMS_H

#include <string>

void programs_init();
void programs_handle_command(std::string command);
void programs_tick();

#endif