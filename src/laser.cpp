/* Laser operation library */

#include <laser.h>

// CONFIGS (*)
#define RECEIVER_ON_LVL 1000 // 0 - 1023

#define TX_SPEED 4 // bits/s (*)
#define LO 10  // 0-bit (*)
#define HI 255 // 1-bit (*)

int shoot_delay = 1000 / TX_SPEED; // (*)

// Setup laser pin as output and receiver pin as input
void setupLaserAndReceiver(int laserPin, int receiverPin){
  pinMode(laserPin, OUTPUT);
  pinMode(receiverPin, INPUT);
}

// Just actuate the laser (for testing)
void blinkLaser(int laserPin) {
  Serial.println("Laserzzz");
  analogWrite(laserPin, 50);
  delay(500);
  analogWrite(laserPin, 255);
  delay(500);
  analogWrite(laserPin, 0);
  delay(500);
}

// Shoot a bit value (*)
void shootBit(int laserPin, int bit) {
  // int value = bit ? HI : LO;
  analogWrite(laserPin, bit ? HI : LO);
  delay(shoot_delay);
  analogWrite(laserPin, 0);
}

// Shoot some bits (*)
void laserSequence(int laserPin) {
  //int seq = 0b1101u; //sequence;
  int n_bits = 4u;
  int seq[n_bits] = {1,1,0,1};
  
  for (int bitnum = 0; bitnum < n_bits; bitnum++) {
    int bit = seq[bitnum];
    Serial.println(bit);
    shootBit(laserPin, bit);
  }
}

// Turn on the laser
void turnLaserOn(int laserPin) {
  digitalWrite(laserPin, HIGH);
}

// Turn off the laser
void turnLaserOff(int laserPin) {
  digitalWrite(laserPin, LOW);
}

// Check whether receiver is sensing the laser
int isReceiverOn(int receiverPin) {
  int value = analogRead(receiverPin);
  Serial.println(value);
  if (value <= RECEIVER_ON_LVL) {
    return 1;
  } else {
    return 0;
  }
}

// Check whether receiver is consistently sensing the laser
int checkPaired(int receiverPin) {
  if(isReceiverOn(receiverPin)) {
    delay(1000); // Stop for 1s and check again
    if(isReceiverOn(receiverPin)) {
      // Lasers are paired.
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

// (*): Deprecated funcionality