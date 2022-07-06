/* Laser operation library */

#include <Arduino.h>

#ifndef LASER_H_
#define LASER_H_

void setupLaser(int laserPin);

void blinkLaser(int laserPin);

void shootBit(int laserPin, int bit);

void laserSequence(int laserPin);

#endif