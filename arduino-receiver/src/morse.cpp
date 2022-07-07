/* Morse code comm library */

#include <morse.h>

#define PRINT_MORSE_CODE_FLAG false

int dotLength = 50;
int dashLength = dotLength*3;

int val = 0; // A Variable to Store the Light Value from the LDR
int ctrHigh = 0;
int ctrLow = 0;
int codePtr = 0;
int dotLen = 400;

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

/*
 * Morse Code Binary Tree
 * Left child at 2n+1
 * Right child at 2n+2
 *         <.|->
 *      .E       -T
 *    .I  -A   .N  -M
*/
const char MorseTree[] = {
  '\0','E', 'T', 'I', 'A', 'N', 'M', 'S',
  'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H',
  'V', 'F', 'U', 'L', 'A', 'P', 'J', 'B',
  'X', 'C', 'Y', 'Z', 'Q', '\0','\0','5',
  '4', '\0','3', '\0','\0','\0','2', '\0',
  '\0','+', '\0','\0','\0','\0','1', '6',
  '=', '/', '\0','\0','\0','(', '\0','7',
  '\0','\0','\0','8', '\0','9', '0', '\0',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0','\0','?', '_', '\0','\0','\0',
  '\0','"', '\0','\0','.', '\0','\0','\0',
  '\0','@', '\0','\0','\0','\0','\0','\0',
  '-', '\0','\0','\0','\0','\0','\0','\0',
  '\0',';', '!', '\0',')', '\0','\0','\0',
  '\0','\0',',', '\0','\0','\0','\0',':',
  '\0','\0','\0','\0','\0','\0','\0'
};

char Message[32];
int MsgPos = 0;

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

void writeMsgToLCD() {
  slcd.setCursot(0,0);
  slcd.print(Message);
}

void buildMsg(char inputChar) {
  if (inputChar == '\\' || MsgPos >= 32) {
    writeMsgToLCD(Message);
    MsgPos = 0;
    return;
  }
  Message[MsgPos] = inputChar;
  MsgPos++;
  return;
}

void receiveMorseCode(int receiverPin) {
  val = analogRead(receiverPin);
  if (val <= 10) {
    ctrHigh++;
    ctrLow = 0;
  } else {
    ctrLow++;
    if ((ctrHigh >= dotLen) && (ctrHigh < dotLen*2)) {
      #if PRINT_MORSE_CODE_FLAG
      Serial.print(".");
      #endif
      codePtr = (2*codePtr) + 1;
    } else if (ctrHigh >= dotLen * 2) {
      #if PRINT_MORSE_CODE_FLAG
      Serial.print("-");
      #endif
      codePtr = (2*codePtr) + 2;
    } else {
      if(ctrLow == dotLen*2 && codePtr != 0){
        Serial.print(MorseTree[codePtr]);
        buildMsg(MorseTree[codePtr]);
        codePtr = 0;
      }
    }
    ctrHigh = 0;
  }
}

void buildAndPrintMsg() {

}