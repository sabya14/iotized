#include <Arduino_JSON.h>
#include "car.h"
#include "utils.h"



void setup() {
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT); //Initiates Brake Channel A pin
  Serial.begin(115200);
  Serial3.begin(115200);
  Serial3.setTimeout(100);
}


void loop()
{
     if ( Serial3.available() )   {  
       
       String mqttData = Serial3.readString();
       
       Serial.println('\n');
       Serial.println("Data recieved..");
       Serial.println(mqttData);
       Serial.println('\n');
       Serial.println(splitString(mqttData, '\n', 1));
       String str_data = splitString(mqttData, '\n', 1);
       JSONVar data = JSON.parse(str_data);
       Serial.println(JSON.stringify(data));
       if (JSON.typeof(data) == "undefined") {
        Serial.println("Parsing input failed!");
      }
    
      String mode = JSON.stringify(data["mode"]) ;
      Serial.println("Selected mode --> " + mode);

      if (mode == "\"car\"") {
          processData(JSON.stringify(data["mode_data"]));
      } else {
          Serial.println("Invalid mode");
      } 
      
   
   }


}
