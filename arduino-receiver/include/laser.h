/* Laser operation library */

#include <Arduino.h>

#ifndef LASER_H_
#define LASER_H_

void setupLaserAndReceiver(int laserPin, int receiverPin);

void blinkLaser(int laserPin);

void shootBit(int laserPin, int bit);

void laserSequence(int laserPin);

void turnLaserOn(int laserPin);

void turnLaserOff(int laserPin);

int isReceiverOn(int receiverPin);

int checkPaired(int receiverPin);

#endif /* LASER_H_ */