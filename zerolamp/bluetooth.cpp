#include "bluetooth.h"
#include <NimBLEDevice.h>

BLEServer *pServer = nullptr;
BLECharacteristic *pCharacteristic = nullptr;

#define SERVICE_UUID        "550e8400-e29b-46d4-a716-446655440000"
#define CHARACTERISTIC_UUID "123e4567-e89b-10d3-a456-426614174001"

// Flag to track connection status
bool deviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Device connected");
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Device disconnected");
  }
};

void bluetooth_init() {

  NimBLEDevice::init("ZeroLamp");

  pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // NimBLEDevice::setPower(ESP_PWR_LVL_N12);

  NimBLEDevice::setSecurityAuth(false, false, false); // Bonding, MITM protection, and secure connections
  // NimBLEDevice::setSecurityPasskey(123456);
  // NimBLEDevice::setSecurityIOCap(BLE_HS_IO_DISPLAY_YESNO); // IO capability (display + confirmation)
  NimBLEDevice::setSecurityIOCap(BLE_HS_IO_NO_INPUT_OUTPUT);
  // NimBLEDevice::setSecurityInitKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);
  // NimBLEDevice::setSecurityRespKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);
  NimBLEDevice::deleteAllBonds();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
  );

  pCharacteristic->setValue("Hello from ZeroLamp!");

  pService->start();

  NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("Bluetooth server started.");
}

void bluetooth_tick() {

  if (!deviceConnected) {
    return;
  }
  
  String value = pCharacteristic->getValue().c_str();
  Serial.println("Received value: " + value);

}