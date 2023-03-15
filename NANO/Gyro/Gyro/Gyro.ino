#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"
#include "Motori.h"

#define PIN_S1 PB3
#define PIN_S2 PA10
#define PIN_S3 PA9
#define PIN_S4 PA8

Motori *motors;
Giroscopio *giro;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  motors= new Motori(PIN_S1,PIN_S2,PIN_S3,PIN_S4);
  giro = new Giroscopio();
}

void loop() {
  float angolo;
  angolo = giro->getGradi();
  motors->destra();
  Serial.println(angolo);
}
