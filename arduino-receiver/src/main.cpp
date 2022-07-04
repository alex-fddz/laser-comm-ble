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

#define LASER 13

#define MOTOR 9

Servo servo;

// initialize the library
SerialLCD slcd(11,12);//this is a must, assign soft serial pins
// (11 and 12 will be lcd's tx and rx respectively)

void setup() {
  // set up
  slcd.begin();
  // Print a message to the LCD.
  slcd.print("DON'T");
  slcd.setCursor(0, 1);
  slcd.print("PANIC !");

  setupLaser(LASER);
  turnLaserOn(LASER);

  servo.attach(MOTOR);
  servo.write(0);
}

void loop() {
  servo.write(45);
  delay(1000);
  servo.write(90);
  delay(1000);

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // slcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // slcd.print(millis()/1000);
}
