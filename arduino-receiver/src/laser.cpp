/* Laser operation library */

#include <laser.h>

#define TX_SPEED 4 // bits/s
#define LO 10  // 0-bit
#define HI 255 // 1-bit

#define RECEIVER_ON_LVL 20 // 0 - 1023

int shoot_delay = 1000 / TX_SPEED;

void setupLaserAndReceiver(int laserPin, int receiverPin){
  pinMode(laserPin, OUTPUT);
  pinMode(receiverPin, INPUT);
}

void blinkLaser(int laserPin) {
  Serial.println("Laserzzz");
  analogWrite(laserPin, 50);
  delay(500);
  analogWrite(laserPin, 255);
  delay(500);
  analogWrite(laserPin, 0);
  delay(500);
}

void shootBit(int laserPin, int bit) {
  // int value = bit ? HI : LO;
  analogWrite(laserPin, bit ? HI : LO);
  delay(shoot_delay);
  analogWrite(laserPin, 0);
}

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

void turnLaserOn(int laserPin) {
  digitalWrite(laserPin, HIGH);
}

void turnLaserOff(int laserPin) {
  digitalWrite(laserPin, LOW);
}

int isReceiverOn(int receiverPin) {
  int value = analogRead(receiverPin);
  Serial.println(value);
  if (value <= RECEIVER_ON_LVL) {
    return 1;
  } else {
    return 0;
  }
}