/* Morse code comm library */

#include <Arduino.h>

void dash(int outPin);

void dot(int outPin);

void flashDashDot(int outPin, const char * morseCode);