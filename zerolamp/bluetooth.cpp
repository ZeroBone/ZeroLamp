#include "bluetooth.h"
#include <Arduino.h>
#include "programs.h"

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

String bt_message = "";

void bluetooth_tick() {

  bool reached_end = false;

  while (SerialBT.available()) {

    char c = SerialBT.read();

    if (c == '\r') {
      continue;
    }

    if (c == '\n') {
      reached_end = true;
      break;
    }
    
    bt_message += String(c);
    
  }

  if (reached_end && !bt_message.isEmpty()) {
    programs_handle_command(bt_message);
    bt_message = "";
  }
}

BluetoothSerial* bluetooth_serial() {
  return &SerialBT;
}

bool bluetooth_device_connected() {
  return SerialBT.hasClient();
}