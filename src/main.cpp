#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <laser.h>
#include <morse.h>


#define LASER 12 // Laser port
#define PHR 13 // Photoresistor port

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
      sendMorseCode(LASER, message);
      
      Serial.println("[OK!]");
      sendMorseCode(LASER, "\\");
      
    }
  }
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting BLE Setup...");

  // Laser setup
  setupLaserAndReceiver(LASER, PHR);

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

// Pairing sequence makes sure that the turret of the reciever is turned in the direction of the transmittor
  void pairingSequence() {
    turnLaserOn(LASER); // Laser is on
    while(1) {
      // keep laser on until phototransistor is hit and then wait 2 seconds to turn off laser
      if(checkPaired(PHR)) {
        delay(2000);
        turnLaserOff(LASER);
        // Laser is paired. Resume to loop()
        return;
      }
    }
  }

  Serial.println("Setup complete!");
}

void loop() {
  // Messages sent by bluetooth will be directly transmitted by the laser.
}
