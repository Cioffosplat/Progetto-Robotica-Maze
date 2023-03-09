#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"

Giroscopio *giro;

float angolo;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  giro = new Giroscopio();
}

void loop() {
  angolo = giro->getGradi();
  if(Serial.available()>0){
    while(Serial.available()>0){
      Serial.read();
    }
    Serial.println(angolo);
  }
}
