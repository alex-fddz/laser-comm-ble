/* Morse code comm library */

#include <Arduino.h>

#ifndef MORSE_H_
#define MORSE_H_

void dash(int outPin);

void dot(int outPin);

void flashDashDot(int outPin, const char * morseCode);

void sendMorseCode(int outPin, char* message);

void receiveMorseCode(int receiverPin);

// Acknowledge functions
void setAcknowledgeFlag(bool setting);
bool getAcknowledgeFlag();
void receiveAck(int receiverPin);

#endif