#include "bluetooth.h"
#include <BluetoothSerial.h>
// #include <NimBLEDevice.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

BluetoothSerial SerialBT;

void bluetooth_init() {
  SerialBT.begin("ZeroLamp");
}

String bluetoothMessage = "";

void bluetooth_tick() {
  bool reachedEndOfMessage = false;

  while (SerialBT.available()) {

    char c = SerialBT.read();

    if (c == '\r') {
      continue;
    }

    if (c == '\n') {
      reachedEndOfMessage = true;
      break;
    }
    
    bluetoothMessage += String(c);
    
  }

  if (reachedEndOfMessage && !bluetoothMessage.isEmpty()) {
    // TODO: handle bluetooth message here
    Serial.println(bluetoothMessage);
    bluetoothMessage = "";
  }
}