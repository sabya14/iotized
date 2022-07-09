#define sprint Serial.print
#define sprintln Serial.println

#include "SoftwareSerial.h"
#include <Servo.h>
SoftwareSerial MyBlue(11, 12); // RX | TX
char c = '1';


Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position


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
    delay(400);
  }
}


void commandToExecute(char comm) {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  if (comm == '0') {
    for (pos = 0; pos <= 75; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }
  if (comm == '1') {
    for (pos = 75; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }
  myservo.detach();  // attaches the servo on pin 9 to the servo object

}
