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
    motors(0,finalSpeed);
  }
  if (dir == "\"right\"") {
    motors(finalSpeed,0);
  }
  if (dir == "\"stop\"") {
    motors(0,0);
  }
  
}

void motors(int r,int l)
   {
     
     if(r>=0 && l>=0)
       { //forward @ full speed
          digitalWrite(12, HIGH); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, l);   //Spins the motor on Channel A at full speed
          //forward @ full speed
          digitalWrite(13, HIGH); //Establishes forward direction of Channel A
          digitalWrite(8, LOW);   //Disengage the Brake for Channel A
          analogWrite(11, r);   //Spins the motor on Channel A at full speed
       }
      else if(r<0 && l>0)
        {
          r=abs(r);
          digitalWrite(12, LOW); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, l);   //Spins the motor on Channel A at full speed
          //forward @ full speed
          digitalWrite(13, HIGH); //Establishes forward direction of Channel A
          digitalWrite(8, LOW);   //Disengage the Brake for Channel A
          analogWrite(11, r);   //Spins the motor on Channel A at full speed
         }
      else if(l<0 && r>0)
        {
          l=abs(l);
          digitalWrite(12, HIGH); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, l);   //Spins the motor on Channel A at full speed
          //forward @ full speed
          digitalWrite(13, LOW); //Establishes forward direction of Channel A
          digitalWrite(8, LOW);   //Disengage the Brake for Channel A
          analogWrite(11, r);   //Spins the motor on Channel A at full speed
      
    } 

    else if(l<0 && r<0)
        {
          l=abs(l);
          digitalWrite(12, LOW); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, l);   //Spins the motor on Channel A at full speed
          //forward @ full speed
          digitalWrite(13, LOW); //Establishes forward direction of Channel A
          digitalWrite(8, LOW);   //Disengage the Brake for Channel A
          analogWrite(11, r);   //Spins the motor on Channel A at full speed
      
    } 
 }
