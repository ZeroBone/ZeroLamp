#include "bluetooth.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// ----------------- Bluetooth -----------------

String bluetoothMessage = "";

void handleBluetooth() {

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
    handleBluetoothCommand(bluetoothMessage);
    bluetoothMessage = "";
  }

}

void handleBluetoothCommand(String command) {
  if (command.equalsIgnoreCase("next")) {
    nextMode();
    return;
  }
  
  if (command.equalsIgnoreCase("prev")) {
    prevMode();
    return;
  }

  if (command.substring(0, 4).equalsIgnoreCase("fill")) {

    String remainder = command.substring(4);
    remainder.trim();

    CRGB color;

    if (remainder.isEmpty()) {
      SerialBT.println("Using random color because no color was specified.");
      color = CHSV(random8(), 0xff, 0xff);
    }
    else {
      bool success = parseColorSpec(remainder, color);
      if (!success) {
        SerialBT.printf("Error. Invalid color syntax. Using random color.\n", remainder);
        color = CHSV(random8(), 0xff, 0xff);
      }
    }

    modeFillColor = color;

    switchMode(MODE_FILL);
    return;
  }

  if (command.equalsIgnoreCase("rainbow")) {
    switchMode(MODE_RAINBOW);
    return;
  }

  if (command.equalsIgnoreCase("fire")) {
    switchMode(MODE_FIRE);
    return;
  }

  if (command.equalsIgnoreCase("snow")) {
    switchMode(MODE_SNOW);
    return;
  }

  if (command.substring(0, 4).equalsIgnoreCase("info")) {
    String remainder = command.substring(4);
    remainder.trim();

    if (!remainder.isEmpty()) {
      textToShow = remainder;
    }
    
    switchMode(MODE_INFO);
    return;
  }
  
  if (command.equalsIgnoreCase("snake")) {
    switchMode(MODE_SNAKE);
    return;
  }

  if (currentMode == MODE_SNAKE && 
        (command.equalsIgnoreCase("w") || command.equalsIgnoreCase("s") || command.equalsIgnoreCase("a") || command.equalsIgnoreCase("d"))
      ) {

    if (command.equalsIgnoreCase("w") && snakeMovementDirection != SNAKE_DIRECTION_DOWN) snakeMovementDirection = SNAKE_DIRECTION_UP;
    else if (command.equalsIgnoreCase("s") && snakeMovementDirection != SNAKE_DIRECTION_UP) snakeMovementDirection = SNAKE_DIRECTION_DOWN;
    else if (command.equalsIgnoreCase("a") && snakeMovementDirection != SNAKE_DIRECTION_RIGHT) snakeMovementDirection = SNAKE_DIRECTION_LEFT;
    else if (command.equalsIgnoreCase("d") && snakeMovementDirection != SNAKE_DIRECTION_LEFT) snakeMovementDirection = SNAKE_DIRECTION_RIGHT;

    return;
  }

  SerialBT.printf("Error. Unknown command '%s'.\n", command);
}