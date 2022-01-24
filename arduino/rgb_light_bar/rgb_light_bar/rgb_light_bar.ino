#define sprint Serial.print
#define sprintln Serial.println
#include "FastLED.h"
#define NUM_LEDS 26
#include "SoftwareSerial.h"
#include <Servo.h>
#define LED_PIN 5

CRGB leds[NUM_LEDS];
SoftwareSerial MyBlue(11, 12); // RX | TX
char c = '1';
int pos = 0;    // variable to store the servo position


void setup() {
  Serial.begin(9600);
  MyBlue.begin(9600);  //Baud Rate for AT-command Mode.
  delay(1000);

}

void loop() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  if (MyBlue.available() > 0) {
    String rgb = MyBlue.readStringUntil('!');
    commandToExecute(rgb);
  } else {
    MyBlue.println("Alive");
    delay(10);
  }
}

// https://stackoverflow.com/questions/9072320/split-string-into-string-array
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void commandToExecute(String rgb) {
  sprintln(rgb);
  String red = getValue(rgb, ',', 0);
  String green = getValue(rgb, ',', 1);
  String blue = getValue(rgb, ',', 2);
  sprintln(red);
  sprintln(green);
  sprintln(blue);

  for (int i = 0; i <= 26; i++) {
    leds[i] = CRGB ( red.toInt(), green.toInt(), blue.toInt());
    FastLED.show();
    delay(2);
  }
  
  delay(2);
}
