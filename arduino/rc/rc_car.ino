#define CH4 23
#define CH2 17
#define CH5 16
#define CH6 19
#define STEER 18
#define MOTOR 5
#define sprint Serial.print
#define sprintln Serial.println

#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>



Adafruit_MPU6050 mpu;
Servo steering;  // create servo object to control a servo
Servo engine;

int steer = 0;
int motor = 0;
int gyroMultiplier = 16;
bool killOff = false;
bool turbo = false;
int throttle;
int mappedThrottle;

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

void setupGyro() {
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

}

void setupSteeringAndEngine() {
  steering.attach(STEER);
  engine.attach(MOTOR, 1000, 2000);
  pinMode(CH4, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
}

void setup() {
  Serial.begin(115200);
  setupSteeringAndEngine();
  setupGyro();

  Serial.print("Arming Test Starts in ");
  engine.writeMicroseconds(715);
  delay(5000);

}


void loop() {
  killOff = readSwitch(CH5, false);
  turbo = readSwitch(CH6, false);

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  int yaw = (g.gyro.z * 57.295779513082320876798154814105);

  if (killOff == true) {

    steer = readChannel(CH4, 29, 151, 90);
    throttle = readChannel(CH2, 0, 2000, 0);
    Serial.println("Actual throttle: ");
    Serial.println(throttle);
    mappedThrottle = 1278.789 + ((-361648700 - 1278.789)/(1 + pow((throttle/3.542685),2.515662)));
    Serial.print("Steer: ");
    Serial.print(steer);
    Serial.print("Throttle: ");
    Serial.print(throttle);

    Serial.print(" | Mapped Throttle: ");
    Serial.print(mappedThrottle);
    Serial.print(" | KillOff: ");
    Serial.print(killOff);
    Serial.print(" | Turbo: ");
    Serial.print(turbo);
    Serial.println(" ");


    steering.write(steer);
    engine.writeMicroseconds(mappedThrottle);

    delay(5);
  }
  else {
    Serial.println("Kill Switch Activated");
    steering.write(90);
    engine.writeMicroseconds(700);
    delay(1);
  }
}