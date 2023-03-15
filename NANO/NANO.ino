#include "I2Cdev.h"
#include "Giroscopio.h"

Giroscopio *giro;

void setup(){
  Wire.begin();
  Serial.begin(115200);
  giro = new Giroscopio(); 
  Serial.println("READY"); 
}

void loop(){
  if(Serial.available()>0){
    while(Serial.available()>0){
      Serial.read();
      delay(1);
    }
    float angolo = giro->getGradi();
    Serial.println(angolo);
  }
}
