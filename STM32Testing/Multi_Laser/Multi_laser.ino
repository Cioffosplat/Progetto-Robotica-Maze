#include "Wire.h"
#include "Lasers.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "gyro/Giroscopio.h"
#include "gyro/Giroscopio.cpp"

Giroscopio *giro;

void setup() {
  Wire.begin();
  pinMode(33, OUTPUT);
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
  digitalWrite(33,HIGH);
  delay(1000);
  digitalWrite(33,LOW);
  delay(1000);
  Serial.print("      Right : ");
  Serial.print(getRight());
  digitalWrite(33,HIGH);
  delay(1000);
  digitalWrite(33,LOW);
  delay(1000);
  Serial.print("      FrontUp : ");
  Serial.print(getFrontUp());
  digitalWrite(33,HIGH);
  delay(1000);
  digitalWrite(33,LOW);
  delay(1000);
  Serial.print("      Back : ");
  Serial.print(getBack());
  digitalWrite(33,HIGH);
  delay(1000);
  digitalWrite(33,LOW);
  delay(1000);
  Serial.print("      FrontDown : ");
  Serial.println(getFrontDown());
  digitalWrite(33,HIGH);
  delay(1000);
  digitalWrite(33,LOW);
  delay(1000);
  delay(50);
}
