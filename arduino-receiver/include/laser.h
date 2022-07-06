/* Laser operation library */

#include <Arduino.h>

void setupLaserAndReceiver(int laserPin, int receiverPin);

void blinkLaser(int laserPin);

void shootBit(int laserPin, int bit);

void laserSequence(int laserPin);

void turnLaserOn(int laserPin);

void turnLaserOff(int laserPin);

int isReceiverOn(int receiverPin);