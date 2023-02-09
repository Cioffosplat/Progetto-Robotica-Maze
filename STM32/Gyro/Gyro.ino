#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"

Giroscopio *giro;
void setup() {
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(9600);
  giro = new Giroscopio();
}

void loop() {
  float angolo;
  angolo = giro->getGradi();
  Serial.println(angolo);
}
