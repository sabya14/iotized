#define CH4 9
#define CH2 10
#define CH5 13
#define CH6 12

#define STEER 14
#define MOTOR 27
#include <ESP32Servo.h>
#include <Wire.h>


Servo steering;  // create servo object to control a servo
Servo engine;

int steer = 0;
int motor = 0;
bool killOff = false;
bool reverse = false;
bool forward = true;
int throttle;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 200) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


void setupSteeringAndEngine() {
  steering.attach(STEER);
  engine.attach(MOTOR, 1000, 2000);
  engine.writeMicroseconds(1500);
  delay(5000);
  pinMode(CH4, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
}

void setup() {
  Serial.begin(115200);
  setupSteeringAndEngine();
  delay(1000);
}


void loop() {
  killOff = readSwitch(CH5, false);
  reverse = readSwitch(CH6, false);

  if (reverse == true && forward== true) {
      Serial.print("Chagning direction to reverse: ");
      engine.writeMicroseconds(1350);
      delay(50);
      engine.writeMicroseconds(1600);
      delay(50);
      engine.writeMicroseconds(1350);
      delay(50);
      forward = false;
  }

  if (reverse == false && forward == false) {
      Serial.print("Chagning direction to forward: ");
      engine.writeMicroseconds(1350);
      delay(50);
      engine.writeMicroseconds(1600);
      forward = true;
  }



  if (killOff == true) {
    steer = readChannel(CH4, 55, 125, 90);
    throttle = readChannel(CH2, 1000, 2000, 1500);
    int throttleDiff = (throttle-1500);
    int mappedThrottle = (-3.322505382374*(pow(10,-6))*(pow(throttleDiff, 2))) + (0.896498*throttleDiff) + 1500.63;


    Serial.print("Steer: ");
    Serial.print(steer);
    Serial.print("Throttle: ");
    Serial.print(throttle);
    Serial.print("Throttle diff: ");
    Serial.print(throttleDiff);
    Serial.print("Mapped Throttle: ");
    Serial.print(mappedThrottle);

    Serial.print(" | KillOff: ");
    Serial.print(killOff);
    Serial.print(" | reverse: ");
    Serial.print(reverse);
    Serial.println(" ");
    steering.write(steer);
    engine.writeMicroseconds(throttle);
    delay(1);
  }
  else {
    Serial.println("Kill Switch Activated");
    steering.write(90);
    engine.writeMicroseconds(1500);
    delay(2);
  }
}