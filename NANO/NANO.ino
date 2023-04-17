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
    String data = Serial.readStringUntil('\n');
     if (data == "0"){
        float angolo = giro->getGradi();
        Serial.println(angolo);
    }
    Serial.flush();
  }
}
