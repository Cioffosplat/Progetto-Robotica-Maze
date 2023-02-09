#include "Wire.h"
#include "Lasers.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"

void setup() {
  Serial.begin(9600);
  setupLasers();
  setupGyro();
}

void loop(){
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
  Serial.println(getGyro());
  delay(500);
}
