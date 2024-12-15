#ifndef ZB_MODES_H
#define ZB_MODES_H

#include <Arduino.h>

void modes_init();
void modes_handle_command(String command);
void modes_tick();

#endif