#include "I2Cdev.h"
#include "Giroscopio.h"

Giroscopio *giro;

void setup(){
  Wire.begin();
  Serial.begin(57600);
  giro = new Giroscopio(); 
  Serial.println("READY"); 
}

void loop(){
  if(Serial.available()>0){
    float angolo = giro->getGradi();
    Serial.println(angolo);
    while(Serial.available()>0){
      Serial.read();
    }
  }
}
