#ifndef ZB_PROGRAMS_H
#define ZB_PROGRAMS_H

#include <Arduino.h>

void programs_init();
void programs_handle_command(String command);
void programs_tick();

#endif