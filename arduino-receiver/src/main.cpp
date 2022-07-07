#include <Arduino.h>
/*
  SerialLCD Library - Hello World
 
 Demonstrates the use a 16x2 LCD SerialLCD driver from Seeedstudio.
 
 This sketch prints "Hello, Seeeduino!" to the LCD
 and shows the time.
 
 Library originally added 16 Dec. 2010
 by Jimbo.we 
 http://www.seeedstudio.com
 */

// include the library code:
#include <SerialLCD.h>
#include <SoftwareSerial.h> //this is a must

#include <laser.h>

#include <Servo.h>

#include <morse.h>

#define LASER 13
#define PHR A0

#define MOTOR 9

Servo servo;

int rcv;
int count = 0;

// initialize the library
// SerialLCD slcd(11,12);//this is a must, assign soft serial pins
// (11 and 12 will be lcd's tx and rx respectively)

// Laser pairing sequence (w/ servo)
void pairLasers() {
  turnLaserOn(LASER);
  // Slowly turn the motors from 0 to 90 degrees,
  //  until they find each other.
  while (1) {
    for (int angle = 0; angle < 90; angle++) {
      servo.write(angle);
      delay(250);
      // see if other laser is received
      if(checkPaired(PHR)) {
        // Paired!
        turnLaserOff(LASER);
        return;
      }
    }
    // then to the other side
    for (int angle = 90; angle > 0; angle--) {
      servo.write(angle);
      delay(250);
      // see if other laser is received
      if(checkPaired(PHR)) {
        return;
      }
    }
  }
}

void setup() {
  // set up
  setupLCD();
  //slcd.begin();
  Serial.begin(115200);
  // Print a message to the LCD.
  //slcd.print("DON'T PANIC!");
  //slcd.setCursor(0, 1);

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
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // slcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // slcd.print(millis()/1000);
}
