#include <Encoder.h>
#include <Bounce2.h>
#include "HID-Project.h"
//Keypad buttons
int R1 = 4;
int R2 = 5;
int R3 = 6;
int R4 = 7;
const byte ROWS = 4;

byte rowPins[ROWS] = {R1, R2, R3, R4};

int lastDebounceTime = 0;
const int debounceDelay = 200;
//Encoder
int SW = 15;
int DT = 14;
int CLK = 16;
Encoder volumeKnob(DT, CLK);
Bounce encoderButton = Bounce(SW, 80);
int timeLimit = 500;
long oldPosition = -999;
int previousButtonState = HIGH;
int buttonState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(CLK, INPUT_PULLUP);

  Keyboard.begin();
  Consumer.begin();

  for (int i = 4; i < 8; i++) {
    pinMode(i, INPUT_PULLUP);
    digitalWrite(i, HIGH);
  }
  Serial.print("Ready");
}


void loop() {
  for (int i = 4; i < 8; i++) {
    buttonState = digitalRead(i);
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (buttonState == LOW ) {
        Serial.println(i);
        switch (i) {
            
          case 4:
            Keyboard.write('4');
            break;
          case 5:
            // Desk light off
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('O');
            break;
          case 6:
            // Lock Screen
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press('Q');
            break;
          case 7:
            // Main bulb off
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('P');
            break;
        }
        Keyboard.releaseAll();
        lastDebounceTime = millis();
        digitalWrite(i, HIGH);
      }

    }
    // save the the last state


  }


  //check the encoder button
  if (encoderButton.update()) {
    if (encoderButton.fallingEdge()) {
      int fall = millis();
      while (!encoderButton.update()) {}
      if (encoderButton.risingEdge()) {
        int rise = millis();
        //Serial.println(rise - fall);
        if (rise - fall > timeLimit) {
          Consumer.write(MEDIA_NEXT);
          Serial.print("Next");
        } else {
          Consumer.write(MEDIA_PLAY_PAUSE);
          Serial.print("Play/Pause");
        }
      }
      Keyboard.releaseAll();
    }
  }

  //check encoder rotation
  long newPosition = volumeKnob.read();
  if (newPosition != oldPosition) {
    Serial.println(newPosition);
    Serial.println(oldPosition);

    if ((newPosition - oldPosition) > 0) {
      //volumeup
      Serial.println("volume up");
      Consumer.write(MEDIA_VOLUME_UP);
    }
    if ((newPosition - oldPosition) < 0 ) {
      //volumedown
      Serial.println("volume down");
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    oldPosition = newPosition;
    Keyboard.releaseAll();
    delay(10); //a delay of 200 seems to be the sweet spot for this encoder.
  }
}
