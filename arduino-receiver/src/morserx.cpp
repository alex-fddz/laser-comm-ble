/* 
 * Morse code receiving library
 *
 * Morse Code Binary Tree
 * Left child at 2n+1
 * Right child at 2n+2
 *         <.|->
 *      .E       -T
 *    .I  -A   .N  -M
 *
*/

#include <morserx.h>


const char MorseTree[] = {'\0','E', 'T', 'I', 'A', 'N', 'M', 'S',
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
int val = 0; // A Variable to Store the Light Value from the LDR
int ctrHigh = 0;
int ctrLow = 0;
int codePtr = 0;
int dotLen = 400; //400

void receiveMorseCode()
{
  val = analogRead(0);
  if (val <= 10) //(val >= 10)
  {
    ctrHigh++;
    ctrLow = 0;
    //digitalWrite(13, HIGH);
    //tone(9, 1000);
  } else {
    ctrLow++;
    //Serial.print(ctrLow);
    if ((ctrHigh >= dotLen) && (ctrHigh < dotLen*2)) {
      Serial.print(".");
      codePtr = (2*codePtr) + 1;
    } else if (ctrHigh >= dotLen * 2) {
      Serial.print("-");
      codePtr = (2*codePtr) + 2;
    } else {
      if(ctrLow == dotLen*2 && codePtr != 0){
        Serial.print(MorseTree[codePtr]);
        codePtr = 0;
      }
    }
    ctrHigh = 0;
    //digitalWrite(13, LOW);
    //noTone(9);
  }
}