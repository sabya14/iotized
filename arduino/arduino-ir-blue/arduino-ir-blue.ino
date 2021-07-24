#define sprint Serial.print
#define sprintln Serial.println
#include <IRremote.h>
#include <SoftwareSerial.h> 
SoftwareSerial HC06(8, 9); // RX | TX 
int flag = 0; 
int LED = 8; 

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;
IRsend irsend;

decode_results results;
const uint8_t NEC_KHZ = 38;
void setup() {
  Serial.begin(9600);
  HC06.begin(38400); 
}

void loop() {
  if (HC06.available()) {
   Serial.write(HC06.read());
  }
//  recvWithEndMarker();
//  showNewData();
}


void recvWithEndMarker() {

  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  // if (Serial.available() > 0) {
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("This just in ... ");
    Serial.println(receivedChars);
    newData = false;
  }
}

void commandToExecute(int command) {
  switch (command) {
    case 1: //Keypad button "5"
      const uint8_t irSignalOn[] PROGMEM = {
        67, 65, 9, 24, 9, 7, 9, 24, 9, 24, 9, 8, 8, 8, 9, 24, 8, 8, 9, 24, 9, 7, 9, 24, 9, 8, 9, 23, 9, 24, 9, 24, 9, 8, 8, 8, 9, 24, 9, 7, 9, 8, 8, 25, 9, 23, 9, 8, 8, 25, 9, 23, 9, 8, 9, 7, 9, 24, 9, 8, 8, 8, 9, 7, 9, 24, 9, 24, 9, 24, 9, 24, 8, 25, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 24, 9, 7, 9, 24, 9, 8, 8, 8, 9, 8, 9, 24, 8, 24, 9, 24, 9, 8, 8, 8, 9, 24, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 8, 8, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 8, 8, 8, 9, 7, 9, 7, 9, 8, 9, 8, 8, 8, 9, 7, 9, 8, 8, 8, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 24, 9, 8, 9, 7, 9, 7, 9, 8, 9, 8, 8, 24, 9, 24, 9, 8, 8, 24, 9, 8, 9, 7, 9, 8, 9
      };

      sprintln("calling  On");
      irsend.sendRaw(irSignalOn, sizeof(irSignalOn) / sizeof(irSignalOn[0]), NEC_KHZ);


    case 2:
      const uint8_t irSignalOff[] PROGMEM = {
        66, 65, 10, 23, 9, 8, 8, 24, 9, 25, 8, 8, 8, 8, 9, 24, 9, 8, 8, 24, 9, 8, 8, 25, 8, 8, 9, 24, 9, 24, 8, 24, 9, 8, 9, 7, 9, 24, 9, 7, 9, 8, 9, 24, 9, 23, 9, 8, 9, 24, 9, 24, 9, 7, 9, 8, 9, 23, 9, 8, 9, 7, 9, 8, 9, 23, 9, 25, 8, 24, 9, 24, 9, 24, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 7, 9, 24, 9, 8, 9, 23, 9, 8, 9, 8, 9, 7, 9, 24, 8, 25, 9, 23, 10, 7, 9, 7, 9, 24, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 8, 9, 7, 9, 7, 10, 7, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 9, 8, 9, 7, 9, 8, 8, 8, 9, 7, 9, 8, 9, 7, 9, 8, 8, 8, 8, 8, 9, 24, 9, 24, 9, 7, 9, 8, 9, 8, 8, 8, 8, 8, 9, 24, 9, 8, 8, 24, 9, 24, 9, 8, 8, 8, 9, 7, 9
      };
      sprintln("calling  Off");
      irsend.sendRaw(irSignalOff, sizeof(irSignalOff) / sizeof(irSignalOff[0]), NEC_KHZ);
  }
  delay(1000);

}
