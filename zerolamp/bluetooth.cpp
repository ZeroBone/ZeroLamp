#include "bluetooth.h"
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

BluetoothSerial SerialBT;

void bluetooth_init() {
  SerialBT.begin("ZeroLamp", false, true);
  // SerialBT.deleteAllBondedDevices();

  Serial.print("ESP32 bluetooth address: ");
  Serial.println(SerialBT.getBtAddressString());

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
    SerialBT.println(bluetoothMessage);
    bluetoothMessage = "";
  }
}