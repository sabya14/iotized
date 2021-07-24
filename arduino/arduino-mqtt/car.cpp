#include "car.h"
#include <Arduino_JSON.h>


void processData(String data) {
  JSONVar carModeData = JSON.parse(data);
  Serial.println("data for car --> " + JSON.stringify(carModeData));
  
  //  {"speed":1}
  JSONVar config = JSON.parse(carModeData["config"]);
  double speed = (double) carModeData["config"]["speed"];
  
  String dir = JSON.stringify(carModeData["data"]["direction"]);
  Serial.println(dir);

  int finalSpeed = (int) (speed * 255);
  Serial.println(finalSpeed);

  if (dir == "\"forward\"") {
    motors(finalSpeed,finalSpeed);
  }
  if (dir == "\"backward\"") {
    motors(-finalSpeed,-finalSpeed);
  }
  if (dir == "\"left\"") {
    motors(-finalSpeed,finalSpeed);
  }
  if (dir == "\"right\"") {
    motors(finalSpeed,-finalSpeed);
  }
  if (dir == "\"stop\"") {
    motors(0,0);
  }

  delay(10);
  
}

void motors(int r,int l)
   {
     
     if(r>=0 && l>=0)
       { //forward @ full speed
         Serial.println(r);
          Serial.println(l);
     
          digitalWrite(12, LOW); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, l);   //Spins the motor on Channel A at full speed
          digitalWrite(13, LOW); //Establishes forward direction of Channel A
          digitalWrite(8, LOW);   //Disengage the Brake for Channel A
          analogWrite(11, r);   //Spins the motor on Channel A at full speed
       }
      else if(r<0 && l>0)
        {
          r=abs(r);
                   Serial.println(r);
          Serial.println(l);
     
          digitalWrite(12, LOW); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, l);   //Spins the motor on Channel A at full speed
          digitalWrite(13, HIGH); //Establishes forward direction of Channel A
          digitalWrite(8, LOW);   //Disengage the Brake for Channel A
          analogWrite(11, r);   //Spins the motor on Channel A at full speed
         }
      else if(l<0 && r>0)
        {
          l=abs(l);
                   Serial.println(r);
          Serial.println(l);
     
          digitalWrite(12, HIGH); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, l);   //Spins the motor on Channel A at full speed
          digitalWrite(13, LOW); //Establishes forward direction of Channel A
          digitalWrite(8, LOW);   //Disengage the Brake for Channel A
          analogWrite(11, r);   //Spins the motor on Channel A at full speed
      
    } 

    else if(l<0 && r<0)
        {
          Serial.println(r);
          Serial.println(l);
     
          digitalWrite(12, HIGH); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, abs(r));   //Spins the motor on Channel A at full speed
          digitalWrite(13, HIGH); //Establishes forward direction of Channel A
          digitalWrite(8, LOW);   //Disengage the Brake for Channel A
          analogWrite(11, abs(l));   //Spins the motor on Channel A at full speed
      
    } 
 }


 void brake(){
          digitalWrite(12, HIGH); //Establishes forward direction of Channel A
          digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
          analogWrite(3, 0);   //Spins the motor on Channel A at full speed
          digitalWrite(13, HIGH); //Establishes forward direction of Channel A
          digitalWrite(8, HIGH);   //Disengage the Brake for Channel A
          analogWrite(11, 0);   //Spins the motor on Channel A at full speed
  
  }
