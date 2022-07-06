/* Morse code comm library */

#include <Arduino.h>

#ifndef MORSE_H_
#define MORSE_H_

void dash(int outPin);

void dot(int outPin);

void flashDashDot(int outPin, const char * morseCode);

void sendMorseCode(int outPin, char* message);

#endif