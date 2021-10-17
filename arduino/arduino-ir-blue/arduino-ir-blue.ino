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
  if (MyBlue.available() > 0) {
    Serial.println("Here");
    char com = MyBlue.read();
    Serial.println(com);
    commandToExecute(com);
  } else {
    Serial.println("Sending health probe");
    MyBlue.println("Alive");
    delay(1000);
  }
}





void commandToExecute(char comm) {
  Serial.println(comm);
  if (comm == '0') {
    const uint8_t irSignalOff[] = {
      67, 65, 9, 24, 9, 7, 9, 24, 9, 24, 9, 8, 8, 8, 9, 24, 8, 8, 9, 24, 9, 7, 9, 24, 9, 8, 9, 23, 9, 24, 9, 24, 9, 8, 8, 8, 9, 24, 9, 7, 9, 8, 8, 25, 9, 23, 9, 8, 8, 25, 9, 23, 9, 8, 9, 7, 9, 24, 9, 8, 8, 8, 9, 7, 9, 24, 9, 24, 9, 24, 9, 24, 8, 25, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 24, 9, 7, 9, 24, 9, 8, 8, 8, 9, 8, 9, 24, 8, 24, 9, 24, 9, 8, 8, 8, 9, 24, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 8, 8, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 8, 8, 8, 9, 7, 9, 7, 9, 8, 9, 8, 8, 8, 9, 7, 9, 8, 8, 8, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 24, 9, 8, 9, 7, 9, 7, 9, 8, 9, 8, 8, 24, 9, 24, 9, 8, 8, 24, 9, 8, 9, 7, 9, 8, 9
    };
    Serial.println("Switching off");
    irsend.sendRaw(irSignalOff, sizeof(irSignalOff) / sizeof(irSignalOff[0]), NEC_KHZ);
    delay(1000);
  }
  if (comm == '1') {
    const uint8_t irSignalOn[] = {
      66, 65, 10, 23, 9, 8, 8, 24, 9, 25, 8, 8, 8, 8, 9, 24, 9, 8, 8, 24, 9, 8, 8, 25, 8, 8, 9, 24, 9, 24, 8, 24, 9, 8, 9, 7, 9, 24, 9, 7, 9, 8, 9, 24, 9, 23, 9, 8, 9, 24, 9, 24, 9, 7, 9, 8, 9, 23, 9, 8, 9, 7, 9, 8, 9, 23, 9, 25, 8, 24, 9, 24, 9, 24, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 7, 9, 24, 9, 8, 9, 23, 9, 8, 9, 8, 9, 7, 9, 24, 8, 25, 9, 23, 10, 7, 9, 7, 9, 24, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 7, 10, 7, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 8, 8, 9, 24, 9, 24, 9, 7, 9, 8, 9, 8, 8, 8, 8, 8, 9, 24, 9, 8, 8, 24, 9, 24, 9, 8, 8, 8, 9, 7, 9
    };
    Serial.println("Switching on");
    irsend.sendRaw(irSignalOn, sizeof(irSignalOn) / sizeof(irSignalOn[0]), NEC_KHZ);
    delay(1000);
    irsend.sendRaw(irSignalOn, sizeof(irSignalOn) / sizeof(irSignalOn[0]), NEC_KHZ);
    delay(1000);

  }
}
