#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <laser.h>

#define LASER_PIN 12

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "6d1cacdf-7aa8-4adf-9d7a-c76c9967ad8c"
#define CHARACTERISTIC_UUID "8a0fc0a3-2a2d-46ca-9a69-b2ba8e52db74"

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onStatus(BLECharacteristic* pCharacteristic, Status s, uint32_t code)
  {
    Serial.println(pCharacteristic->getValue().c_str());
    Serial.println(s);
    Serial.println(code);
  }

  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0)
    {
      // Convert string to char array
      int msg_size = value.length();
      char message[msg_size+1];
      for (int i = 0; i < msg_size; i++) {
        message[i] = value[i];
      }
      message[msg_size] = '\0';
      
      Serial.print("> ");
      Serial.println(message);

      // doSomething(message);
    }
  }
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting BLE Setup...");

  // Laser setup
  setupLaser(LASER_PIN);

  // BLE setup:
  BLEDevice::init("DM_AJ");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID, 
    BLECharacteristic::PROPERTY_READ | 
    BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello World");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  Serial.println("Setup complete!");
}

void loop() {
  // put your main code here, to run repeatedly:
  laserSequence(LASER_PIN);
  delay(2000);
}