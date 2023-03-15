#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"

Giroscopio *giro;
<<<<<<< HEAD
  
=======

float angolo;

>>>>>>> 6d2cf53d9af8d581071a71f990d9107a22e138af
void setup() {
  Wire.begin();
  Serial.begin(115200);
  giro = new Giroscopio();
}

void loop() {
  angolo = giro->getGradi();
<<<<<<< HEAD
  Serial.print("ZAngle is;");
  Serial.println(angolo);
  delay(100);
=======
  if(Serial.available()>0){
    while(Serial.available()>0){
      Serial.read();
    }
    Serial.println(angolo);
  }
>>>>>>> 6d2cf53d9af8d581071a71f990d9107a22e138af
}
