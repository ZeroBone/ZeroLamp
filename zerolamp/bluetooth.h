#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <BluetoothSerial.h>

void bluetooth_init();
void bluetooth_tick();
BluetoothSerial* bluetooth_serial();

#endif