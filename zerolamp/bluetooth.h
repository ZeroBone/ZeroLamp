#ifndef ZB_BLUETOOTH_H
#define ZB_BLUETOOTH_H

#include <BluetoothSerial.h>

#define MAX_READ_ITERATIONS_PER_TICK 64

void bluetooth_init();
void bluetooth_tick();
BluetoothSerial* bluetooth_serial();
bool bluetooth_device_connected();

#endif