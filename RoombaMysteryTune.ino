// clytle 2013
// Thanks to bcreighton for debugging help
// Thanks to Marc Moesse for transcribbing music to opcodes
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
  // Each single letter array is a bar of music.
  // Each double letter array is play command for the corresponding music.
  int e[] = {140, 5, 14, 65, 8, 67, 8, 70, 8, 67, 8, 74, 24, 74, 24, 72, 48, 65, 8, 67, 8, 70, 8, 67, 8, 72, 24, 72, 24, 70, 48};
  int f[] = {140, 6, 11, 65, 8, 67, 8, 70, 8, 67, 8, 70, 32, 72, 16, 69, 32, 65, 32, 65, 16, 72, 32, 70, 64};
  int g[] = {140, 7, 14, 65, 8, 67, 8, 70, 8, 67, 8, 74, 24, 74, 24, 72, 48, 65, 8, 67, 8, 70, 8, 67, 8, 77, 32, 69, 16, 70, 48};
  int h[] = {140, 8, 10, 65, 8, 67, 8, 70, 8, 67, 8, 70, 32, 72, 16, 69, 64, 65, 16, 72, 32, 70, 64};
  int ee[] = {141, 5};
  int ff[] = {141, 6};
  int gg[] = {141, 7};
  int hh[] = {141, 8};
  // Load the songs to the Roomba
  opcodes(e, (sizeof(e)/sizeof(int)));
  opcodes(f, (sizeof(f)/sizeof(int)));
  opcodes(g, (sizeof(g)/sizeof(int)));
  opcodes(h, (sizeof(h)/sizeof(int)));
  // Play the songs. Pauses must be included while the music plays.
  opcodes(ee, (sizeof(ee)/sizeof(int)));
  delay(4000);
  opcodes(ff, (sizeof(ff)/sizeof(int)));
  delay(4000);
  opcodes(gg, (sizeof(gg)/sizeof(int)));
  delay(4000);
  opcodes(hh, (sizeof(hh)/sizeof(int)));
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
