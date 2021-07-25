#define sprint Serial.print
#define sprintln Serial.println
#include <IRremote.h>
#include "SoftwareSerial.h"
SoftwareSerial MyBlue(11, 12); // RX | TX

IRsend irsend;
const uint8_t NEC_KHZ = 38;
char c = '1';

void setup() {
  Serial.begin(9600);
  MyBlue.begin(9600);  //Baud Rate for AT-command Mode.
  delay(1000);
}

void loop() {
  if (MyBlue.available()) {
    commandToExecute(MyBlue.read());
  }

}





void commandToExecute(char c) {
  Serial.println(c);
  const uint8_t irSignalOff[] PROGMEM = {
    67, 65, 9, 24, 9, 7, 9, 24, 9, 24, 9, 8, 8, 8, 9, 24, 8, 8, 9, 24, 9, 7, 9, 24, 9, 8, 9, 23, 9, 24, 9, 24, 9, 8, 8, 8, 9, 24, 9, 7, 9, 8, 8, 25, 9, 23, 9, 8, 8, 25, 9, 23, 9, 8, 9, 7, 9, 24, 9, 8, 8, 8, 9, 7, 9, 24, 9, 24, 9, 24, 9, 24, 8, 25, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 24, 9, 7, 9, 24, 9, 8, 8, 8, 9, 8, 9, 24, 8, 24, 9, 24, 9, 8, 8, 8, 9, 24, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 8, 8, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 8, 8, 8, 9, 7, 9, 7, 9, 8, 9, 8, 8, 8, 9, 7, 9, 8, 8, 8, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 24, 9, 8, 9, 7, 9, 7, 9, 8, 9, 8, 8, 24, 9, 24, 9, 8, 8, 24, 9, 8, 9, 7, 9, 8, 9
  };
  const uint8_t irSignalOn[] PROGMEM = {
    66, 65, 10, 23, 9, 8, 8, 24, 9, 25, 8, 8, 8, 8, 9, 24, 9, 8, 8, 24, 9, 8, 8, 25, 8, 8, 9, 24, 9, 24, 8, 24, 9, 8, 9, 7, 9, 24, 9, 7, 9, 8, 9, 24, 9, 23, 9, 8, 9, 24, 9, 24, 9, 7, 9, 8, 9, 23, 9, 8, 9, 7, 9, 8, 9, 23, 9, 25, 8, 24, 9, 24, 9, 24, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 7, 9, 24, 9, 8, 9, 23, 9, 8, 9, 8, 9, 7, 9, 24, 8, 25, 9, 23, 10, 7, 9, 7, 9, 24, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 7, 10, 7, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 8, 8, 9, 24, 9, 24, 9, 7, 9, 8, 9, 8, 8, 8, 8, 8, 9, 24, 9, 8, 8, 24, 9, 24, 9, 8, 8, 8, 9, 7, 9
  };

  switch (c) {
    case '1':
      sprintln("calling  On");
      irsend.sendRaw(irSignalOn, sizeof(irSignalOff) / sizeof(irSignalOn[0]), NEC_KHZ);
      delay(1000);
      break;
    case '2':
      sprintln("calling  Off");
      irsend.sendRaw(irSignalOff, sizeof(irSignalOn) / sizeof(irSignalOff[0]), NEC_KHZ);
      irsend.sendRaw(irSignalOff, sizeof(irSignalOn) / sizeof(irSignalOff[0]), NEC_KHZ);
      delay(1000);
      break;
  }
  
}
