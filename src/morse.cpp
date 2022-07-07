/* Morse code comm library */

#include <morse.h>

int dotLength = 50;
int dashLength = dotLength*3;

const char* MorseTable[] = {
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  // space, !, ", #, $, %, &, '
  NULL, "-.-.--", ".-..-.", NULL, NULL, NULL, NULL, ".----.",
  // ( ) * + , - . /
  "-.--.", "-.--.-", NULL, ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.",
  // 0 1 2 3 4 5 6 7
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
  // 8 9 : ; < = > ?
  "---..", "----.", "---...", "-.-.-.", NULL, "-...-", NULL, "..--..",
  // @ A B C D E F G
  ".--.-.", ".-0", "-...", "-.-.", "-..", ".", "..-.", "--.",
  // H I J K L M N O
  "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
  // P Q R S T U V W
  ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
  // X Y Z [ \ ] ^ _
  "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, "..--.-",
  // ' a b c d e f g
  NULL, ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
  // h i j k l m n o
  "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
  // p q r s t u v w
  ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
  // x y z { | } ~ DEL
  "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, NULL,
};

void dash(int outPin) {
  digitalWrite(outPin, HIGH);
  delay(dashLength);
  digitalWrite(outPin, LOW);
  delay(dotLength);
}

void dot(int outPin) {
  digitalWrite(outPin, HIGH);
  delay(dotLength);
  digitalWrite(outPin, LOW);
  delay(dotLength);
}

void flashDashDot(int outPin, const char * morseCode) {
  int i = 0;
  while(morseCode[i] != 0)
  {
    Serial.print(morseCode[i]);
    if(morseCode[i] == '.'){
      dot(outPin);
    } else if (morseCode[i] == '-'){
      dash(outPin);
    }
    i++;
  }
  delay(dotLength*2);
}

void sendMorseCode(int outPin, char* message) {
  char ch;
  int len = strlen(message);
  for(int i = 0; i < len; i++) {
    ch = message[i];
    flashDashDot(outPin, MorseTable[ch]);
  }
}