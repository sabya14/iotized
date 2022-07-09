#define sprint Serial.print
#define sprintln Serial.println
#define NUM_LEDS 4
#define LED_PIN 2

#include "FastLED.h"
#include "SoftwareSerial.h"
#include <Servo.h>
CRGB leds[NUM_LEDS];
SoftwareSerial MyBlue(5, 4); // RX | TX


char c = '1';
String rgb;
String lastRgb '';


void setup() {
  Serial.begin(9600);
  MyBlue.begin(9600);
  delay(1000);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
}




void loop() {
  if (MyBlue.available() > 0) {
      rgb = MyBlue.readStringUntil('#');
      sprintln("RGB Value Received: " + rgb);
      commandToExecute(rgb);
      lastRgb = rgb;
      MyBlue.println("Ack:" + lastRgb + "#");

  }
  else {
    sprintln("Ack: " + rgb);
    MyBlue.println("Ack:" + lastRgb + "#");
    delay(10);
  }
}

// https://stackoverflow.com/questions/9072320/split-string-into-string-array
String getValue(String data, char separator, int index, int strLengthToConsider)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = strLengthToConsider - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

boolean isValidNumber(String str) {
  for (byte i = 0; i < str.length(); i++)
  {
    if (isDigit(str.charAt(i))) return true;
  }
  return false;
}

String reverse(String str) {
  char rev[64] = {} ;
  for (int i = 0; i <= str.length() - 1; i++) {
    rev[i] = (str[str.length() - 1 - i]);
  }
  return rev;
}

int commandToExecute(String rgb) {

  String rgbReverse = reverse(rgb).substring(0, rgb.length());
  String blue = reverse(getValue(rgbReverse, ',', 0, rgb.length()));
  String green = reverse(getValue(rgbReverse, ',', 1, rgb.length()));
  String red = reverse(getValue(rgbReverse, ',', 2,  rgb.length()));
  String bright = reverse(getValue(rgbReverse, ',', 3,  rgb.length()));



  if (isValidNumber(red) && isValidNumber(green) && isValidNumber(blue) && red.length() < 4 && green.length() < 4 && blue.length() < 4) {

   sprintln("Applying new");
   sprint(red);
   sprint(':');
   sprint(green);
   sprint(':');
   sprint(blue);
   sprintln("");

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB ( red.toInt(), green.toInt(), blue.toInt());
      FastLED.show();
    }
    return 1;
  }
  return 0;
}