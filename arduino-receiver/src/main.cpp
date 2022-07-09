#include <Arduino.h>

#include <SerialLCD.h>
#include <SoftwareSerial.h> 
#include <Servo.h>

#include <morse.h>
#include <laser.h>

#define MOTOR 9
#define LASER 13
#define PHR A0

int rcv;
int count = 0;

Servo servo;

// Laser pairing sequence (w/ servo)
void pairLasers() {
  int angleWait = 500;
  turnLaserOn(LASER);
  // Slowly turn the motors from 0 to 90 degrees,
  //  until they find each other.
  while (1) {
    for (int angle = 0; angle < 90; angle++) {
      servo.write(angle);
      delay(angleWait);
      // see if other laser is received
      if(checkPaired(PHR)) {
        // Paired!
        delay(2000);
        turnLaserOff(LASER);
        return;
      }
    }
    // then to the other side
    for (int angle = 90; angle > 0; angle--) {
      servo.write(angle);
      delay(angleWait);
      // see if other laser is received
      if(checkPaired(PHR)) {
        // Paired!
        delay(2000);
        turnLaserOff(LASER);
        return;
      }
    }
  }
}

void setup() {
  setupLCD();
  Serial.begin(115200);

  setupLaserAndReceiver(LASER, PHR);

  servo.attach(MOTOR);
  servo.write(0);
  delay(1000);

  Serial.println("Pairing...");
  pairLasers();
  Serial.print("OK!");
  servo.detach();
}

void loop() {
  receiveMorseCode(PHR);
}
