// clytle 2013
// Thanks to bcreighton for debugging help
//
// Tested on a Roomba 4150 (manufacture date July 15 2007)
// using an Arduino Duemilanove & Arduino Leonardo. 
//
// Roomba docs at http://www.irobot.com/images/consumer/hacker/Roomba_SCI_Spec_Manual.pdf
//
// Wiring:
// Connect Arduino pin 5 to Roomba pin 4
// Connect Arduino pin 6 to Roomba pin 3
// Connect Arduino pin 7 to Roomba pin 5
// Connect Arduino GND pin to Roomba pin 6 or 7

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6); //rx,tx
int ddPin = 7;
int now;

void setup() {
  pinMode(ddPin,  OUTPUT);
  mySerial.begin(57600);
  //Use Device Detect to wake Roomba
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);
  //Initialize Roomba SCI
  // Start SCI
  mySerial.write(128);
  delay(100);
  // Enable control
  mySerial.write(130);  
  delay(100);
  // Enable full control, no safety, all commands (optional)
  mySerial.write(132);
  delay(100);
  //Drop whatever operations you wish to run into the array below.
  //This example will play 3 distinct 1 second long tones.
  int a[] = {140, 1, 3, 69, 64, 71, 64, 72, 64, 141, 1};
  opcodes(a, (sizeof(a)/sizeof(int)));
}

void loop() {
}

// This little function takes an array of opcodes (and the array's length) and runs them all.
void opcodes(int *bytes, int len) {
  for (now = 0; now < len; now++) {
    mySerial.write((byte)(bytes[now]));
    delay(100);
  }
}
