/* Morse code comm library */

#include <Arduino.h>

#ifndef MORSE_H_
#define MORSE_H_

// Transmit
void dash(int outPin);

void dot(int outPin);

void flashDashDot(int outPin, const char * morseCode);

void sendMorseCode(int outPin, char* message);

// Recieve
void writeMsgToLCD();
void buildMsg(char inputChar);
void receiveMorseCode(int receiverPin);
void setupLCD();

#endif