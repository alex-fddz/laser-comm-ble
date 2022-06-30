/* Laser operation library */

#include <Arduino.h>

void setupLaser(int laserPin);

void blinkLaser(int laserPin);

void shootBit(int laserPin, int bit);

void laserSequence(int laserPin);