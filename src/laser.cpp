/* Laser operation library */

#include <laser.h>

void setupLaser(int laserPin){
  pinMode(laserPin, OUTPUT);
}

void blinkLaser(int laserPin) {
  Serial.println("Laserzzz");
  digitalWrite(laserPin, HIGH);
  delay(500);
  digitalWrite(laserPin, LOW);
  delay(500);
}