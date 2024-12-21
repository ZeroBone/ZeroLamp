#include "bluetooth.h"
#include "program_controller.h"

#include <sstream>

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

void bluetooth_tick() {

  if (!SerialBT.available()) {
    return;
  }

  int read_iterations = 0;
  bool reached_end = false;
  std::ostringstream bt_stream;

  do {

    char c = SerialBT.read();
    read_iterations++;

    if (c == '\r') {
      continue;
    }

    if (c == '\n') {
      reached_end = true;
      break;
    }
    
    bt_stream.put(c);
    
  } while (SerialBT.available() && read_iterations < MAX_READ_ITERATIONS_PER_TICK);

  if (reached_end) {
    std::string bt_message = bt_stream.str();
    program_controller_handle_command(std::move(bt_message));
  }

}

BluetoothSerial* bluetooth_serial() {
  return &SerialBT;
}

bool bluetooth_device_connected() {
  return SerialBT.hasClient();
}