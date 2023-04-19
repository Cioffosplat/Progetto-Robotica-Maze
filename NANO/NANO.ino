#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"

Giroscopio *giro;

void setup(){
  Wire.begin();
  Serial.begin(57600);
  giro = new Giroscopio(); 
}

void loop(){
  if(Serial.available()>0){
    String data = Serial.readStringUntil('\n');
    char c = data.charAt(0);
  switch (c) {
    case '0':
    {
      float angolo = giro->getGradi();
      Serial.println(angolo);
      break;
    } 
    case '1':
    {
      break;
    } 
    
  }
  }
}
