/* Morse code comm library */

#include <morse.h>
#include <SerialLCD.h>

#define PRINT_MORSE_CODE_FLAG false // Flag to decide if to print message to serial monitor
#define MESSAGE_LENGTH 16 // Length of a message sent to LCD
SerialLCD slcd(11,12); // LCD ports

int dotLength = 50;
int dashLength = dotLength*3;

int val = 0; // A Variable to Store the Light Value from the LDR
int ctrHigh = 0; // To check how long the input of phototransistor was on high
int ctrLow = 0; // To check how long the input of the phototransistor was on low
int codePtr = 0; // To keep track of where we are in the morse tree
int dotLen = 400; // How many cycles it takes to recieve a dot

// Table of morse code for sending. Each code is at the place that corresponds to the byte value of the character
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
  "-..-", "-.--", "--..", NULL, "..-.-", NULL, NULL, "..--.-",
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

char Message[MESSAGE_LENGTH]; // Char array to store the message
int MsgPos = 0; // To keep track of where to write on the LCD screen

// Send a dash via laser
void dash(int outPin) {
  digitalWrite(outPin, HIGH);
  delay(dashLength);
  digitalWrite(outPin, LOW);
  delay(dotLength);
}

// Send a dot via laser
void dot(int outPin) {
  digitalWrite(outPin, HIGH);
  delay(dotLength);
  digitalWrite(outPin, LOW);
  delay(dotLength);
}

// Sends a char array of dots and dashes
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

// Sends a message as morse code using the morse table
void sendMorseCode(int outPin, char* message) {
  char ch;
  int len = strlen(message);
  for(int i = 0; i < len; i++) {
    ch = message[i];
    flashDashDot(outPin, MorseTable[ch]);
  }
}

// Write to LCD
void writeMsgToLCD() {
  slcd.clear();
  slcd.setCursor(0,0);
  slcd.print("Message recieved:");
  slcd.setCursor(0,1);
  slcd.print(Message);
}

// Builds the message that gets written to the LCD
void buildMsg(char inputChar) {
  if (inputChar == '\0' || MsgPos >= MESSAGE_LENGTH) {
    writeMsgToLCD();
    MsgPos = 0;
    return;
  }
  Message[MsgPos] = inputChar;
  MsgPos++;
  return;
}

// Recieves morse code. Decides if dot or dash by counting cycles and converts to char with the morse tree
void receiveMorseCode(int receiverPin) {
  val = analogRead(receiverPin);
  // Check if laser received is on
  if (val <= 10) {
    ctrHigh++; // Add to laser high count
    ctrLow = 0; // Reset laser low count
    // Else laser received is off
  } else {
    ctrLow++; // Add to laser low count
    // If laser was high for dotLen to dotLen*2 print dot
    if ((ctrHigh >= dotLen) && (ctrHigh < dotLen*2)) {
      #if PRINT_MORSE_CODE_FLAG
      Serial.print(".");
      #endif
      codePtr = (2*codePtr) + 1; // Dot received. Move pointer accordingly
    // Else if laser was high for longer than dotLen*2 print dash
    } else if (ctrHigh >= dotLen * 2) {
      #if PRINT_MORSE_CODE_FLAG
      Serial.print("-");
      #endif
      codePtr = (2*codePtr) + 2;// Dash received. Move pointer accordingly
    // Else check if pause was long enough and check which letter was send with morse tree
    } else {
      if(ctrLow == dotLen*2 && codePtr != 0){
        Serial.print(MorseTree[codePtr]);
        buildMsg(MorseTree[codePtr]); // Message gets built for LCD screen
        codePtr = 0; // Reset morse code pointer
      }
    }
    ctrHigh = 0; // Reset laser high count
  }
}

// Set up the LCD and print "Awaiting Msg..."
void setupLCD() {
  slcd.begin();
  slcd.print("Awaiting Msg...");
}