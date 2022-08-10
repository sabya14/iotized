#define CH4 23
#define CH2 22
#define CH5 21
#define CH6 19

#define STEER 18
#define MOTOR 5

#define Z_YAW 17
#define Y_PITCH 16

#include <ESP32Servo.h>
#define sprint Serial.print
#define sprintln Serial.println

Servo steering;  // create servo object to control a servo
Servo engine;


int steer = 0;
int motor = 0;
bool killOff = false;
bool turbo = false;
int throttle;
int mappedThrottle;
 
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 200) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
 
void setup(){
  Serial.begin(115200);
  steering.attach(STEER);
  engine.attach(MOTOR, 1000, 2000);
  pinMode(CH4, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  Serial.print("Arming Test Starts in ");
  engine.writeMicroseconds(715);
  delay(5000);
  
}


void loop() {
  killOff = readSwitch(CH5, false);
  turbo = readSwitch(CH6, false);

   if (killOff == true) {
    // Get values for each channel
    steer = readChannel(CH4, 29, 151, 90);
    throttle = readChannel(CH2, 0, 2000, 0);
    Serial.println("Actual throttle: ");
    Serial.println(throttle);
    mappedThrottle = 1278.789 + ((-361648700 - 1278.789)/(1 + pow((throttle/3.542685),2.515662)));
    Serial.print("Steer: ");
    Serial.print(steer);
    Serial.print(" | Throttle: ");
    Serial.print(mappedThrottle);
    Serial.print(" | KillOff: ");
    Serial.print(killOff);
    Serial.print(" | Turbo: ");
    Serial.print(turbo);
    Serial.println(" ");
    steering.write(steer);
    
    engine.writeMicroseconds(mappedthrottle);
    delay(1);
  }
  else {
   Serial.println("Kill Switch Activated");
   steering.write(90);
   engine.writeMicroseconds(700);  
  }
}