#include <string>
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

std::vector<uint8_t> incoming_bytes;

void bluetooth_tick() {

  if (!SerialBT.available()) {
    return;
  }

  int read_iterations = 0;
  bool reached_end = false;

  do {

    uint8_t byte = SerialBT.read();
    read_iterations++;

    if (byte == '\r') {
      continue;
    }

    if (byte == '\n') {
      reached_end = true;
      break;
    }

    incoming_bytes.emplace_back(byte);
    
  } while (SerialBT.available() && read_iterations < MAX_READ_ITERATIONS_PER_TICK);

  if (reached_end) {

    std::string incoming_string(incoming_bytes.begin(), incoming_bytes.end());

    incoming_bytes.clear();

    program_controller_handle_command(std::move(incoming_string));

  }

}

BluetoothSerial* bluetooth_serial() {
  return &SerialBT;
}

bool bluetooth_device_connected() {
  return SerialBT.hasClient();
}