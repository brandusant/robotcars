/* YourDuino.com Example Software Sketch
 IR Remote Kit Test
Uses YourDuino.com IR InfraredRemote Control Kit 2
 http://arduino-direct.com/sunshop/index.php?l=product_detail&p=153
based on code byKenShirriff - http://arcfn.com
 Get Library at: https://github.com/shirriff/Arduino-IRremote
UnzipfolderintoLibraries. RENAME folderIRremote
terry@yourduino.com */
/*-----( Import neededlibraries )-----*/
#include "IRremote.h"
/*-----( Declare Constants )-----*/
int receiver = 11; // pin 1 of IR receivertoArduino digital pin 11
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'
/*-----( Declare Variables )-----*/

// Motor A, Left Side
const uint8_t pwmLeft = 9;      // ENA - Enableand PWM
const uint8_t leftForward = 7;  // IN1 - Forward Drive
const uint8_t leftReverse = 6;  // IN2 - Reverse Drive
// Motor B, Right Side
const uint8_t pwmRight = 3;     // ENB - Enableand PWM
const uint8_t rightForward = 5; // IN3 - Forward Drive
const uint8_t rightReverse = 4; // IN4 - Reverse Drive
//////////////// Start Functions //////////////////
// All Stop
void allStop() {
digitalWrite(leftForward, LOW);
digitalWrite(leftReverse, LOW);
digitalWrite(rightForward, LOW);
digitalWrite(rightReverse, LOW);
analogWrite(pwmLeft, 0);
analogWrite(pwmRight, 0);
}
void allForward() {
digitalWrite(leftForward, HIGH);
digitalWrite(leftReverse, LOW);
digitalWrite(rightForward, LOW);
digitalWrite(rightReverse, LOW);
analogWrite(pwmLeft, 255);
analogWrite(pwmRight, 255);
}
void allReverse() {
digitalWrite(leftForward, LOW);
digitalWrite(leftReverse, HIGH);
digitalWrite(rightForward, LOW);
digitalWrite(rightReverse, LOW);
analogWrite(pwmLeft, 255);
analogWrite(pwmRight, 255);
}

void skidsteerLeft() {
digitalWrite(leftForward, LOW);
digitalWrite(leftReverse, LOW);
digitalWrite(rightForward, HIGH);
digitalWrite(rightReverse, LOW);
analogWrite(pwmLeft, 255);
analogWrite(pwmRight, 255);
}

void skidsteerRight() {
digitalWrite(leftForward, LOW);
digitalWrite(leftReverse, LOW);
digitalWrite(rightForward, LOW);
digitalWrite(rightReverse, HIGH);
analogWrite(pwmLeft, 255);
analogWrite(pwmRight, 255);
}

//////////////// End Functions //////////////////
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
Serial.begin(9600);
Serial.println("IR ReceiverRaw Data + ButtonDecode Test");
irrecv.enableIRIn(); // Start thereceiver
   // Set pinsto motor driver (L298) tooutputs
pinMode(pwmLeft, OUTPUT);
pinMode(leftForward, OUTPUT);
pinMode(leftReverse, OUTPUT);
pinMode(pwmRight, OUTPUT);
pinMode(rightForward, OUTPUT);
pinMode(rightReverse, OUTPUT);
}/*--(end setup )---*/
void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
if (irrecv.decode(&results)) // havewereceived an IR signal?
  {
//    Serial.println(results.value, HEX);  UN Comment toseerawvalues
translateIR(); 
irrecv.resume(); // receivethenextvalue
  }  
}/* --(end mainloop )-- */
/*-----( Declare User-writtenFunctions )-----*/
void translateIR() // takesactionbased on IR code received
// describing Car MP3 IR codes
{
switch(results.value)
  {
  case 0xFFA25D:  
Serial.println(" CH-            "); 
    break;
  case 0xFF629D:  
Serial.println(" CH             "); 
    break;

case 0xFFE21D:  
Serial.println(" CH+            "); 
allStop();
    break;
    
case 0xFF22DD:  
Serial.println(" PREV           "); 
skidsteerLeft();  // Skidsteer spin left direction
    break;
    
case 0xFF02FD:  
Serial.println(" NEXT           "); 
skidsteerRight(); // Skidsteer spin rightdirection
    break;
    
case 0xFFC23D:  
Serial.println(" PLAY/PAUSE     "); 
allStop();  // Stop alldcmotors
    break;
    
  case 0xFFE01F:  
Serial.println(" VOL-           "); 
allReverse(); // Drive dcmotors in reverse
    break;
  case 0xFFA857: 
   
Serial.println(" VOL+           "); 
allForward(); // Drive dcmotorsforward
    break;
    
  case 0xFF906F:  
Serial.println(" EQ             "); 
    break;
    
  case 0xFF6897:  
Serial.println(" 0              "); 
skidsteerLeft();
    break;
    
  case 0xFF9867:  
Serial.println(" 100+           "); 
skidsteerRight();
    break;
    
  case 0xFFB04F:  
Serial.println(" 200+           "); 
    break;
  case 0xFF30CF:  
Serial.println(" 1              "); 
    break;
  case 0xFF18E7:  
Serial.println(" 2              "); 
allForward(); // Drive dcmotorsforward
    break;
Serial.println(" 3              "); 
    break;
case 0xFF10EF:  
Serial.println(" 4              "); 
skidsteerLeft();  // Skidsteer spin left direction
    break;
case 0xFF38C7:  
Serial.println(" 5              "); 
allStop();  // Stop alldcmotors
    break;
case 0xFF5AA5:
Serial.println(" 6              "); 
skidsteerRight(); // Skidsteer spin rightdirection
case 0xFF42BD:
    break;
Serial.println(" 7              "); 
    break;
  case 0xFF4AB5:  
Serial.println(" 8              "); 
allReverse(); // Drive dcmotors in reverse
    break;
case 0xFF52AD:
Serial.println(" 9              "); 
    break;
default: 
Serial.println(" otherbutton   ");
  }
delay(500);
} //END translateIR
