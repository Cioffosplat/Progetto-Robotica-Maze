#include "Wire.h"
#include "Lasers.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "gyro/Giroscopio.h"
#include "gyro/Giroscopio.cpp"

Giroscopio *giro;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  giro = new Giroscopio();
  setupLasers();
}

void loop(){
  float angolo;
  angolo = giro->getGradi();
  Serial.print("Angle : ");
  Serial.println(angolo);
  Serial.print("Left : ");
  Serial.print(getLeft());
  Serial.print("      Right : ");
  Serial.print(getRight());
  Serial.print("      FrontUp : ");
  Serial.print(getFrontUp());
  Serial.print("      Back : ");
  Serial.print(getBack());
  Serial.print("      FrontDown : ");
  Serial.println(getFrontDown());
  delay(50);
}
