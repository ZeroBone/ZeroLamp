#ifndef MODES_H
#define MODES_H

#include <Arduino.h>

// #define MODES_QUEUE_SIZE 16

void modes_init();
void modes_handle_command(String command);
void modes_tick();

#endif