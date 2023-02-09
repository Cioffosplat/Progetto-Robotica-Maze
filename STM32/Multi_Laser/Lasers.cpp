#include "Lasers.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"
Giroscopio *giro;

#define LEFT 1
#define RIGHT 2
#define BACK 3
#define FRONT_UP 4
#define FRONT_DOWN 5
#define GYRO 6

void setupGyro(){
  Wire.begin();
  Serial.begin(9600);
  giro = new Giroscopio();
}

void setupLasers(){
  
  Wire.begin();
  Serial.begin(9600);

Serial.println("Initializing Left");
  TCA9548A(LEFT);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }

  Serial.println("Initializing Right");
  TCA9548A(RIGHT);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }

Serial.println("Initializing Back");
  TCA9548A(BACK);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }

  Serial.println("Initializing Front_Up");
  TCA9548A(FRONT_UP);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }

  Serial.println("Initializing Front_Down");
  TCA9548A(FRONT_DOWN);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }
  Serial.println("Initializing Gyro");
  TCA9548A(GYRO);
  if (!sensor.init())
  {
    while (1) {}
  }
  
}

void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

uint16_t getRight(){
  TCA9548A(RIGHT);
  return sensor.readRangeSingleMillimeters();
}
uint16_t getLeft(){
  TCA9548A(LEFT);
  return (sensor.readRangeSingleMillimeters());
}
uint16_t getBack(){
  TCA9548A(BACK);
  return sensor.readRangeSingleMillimeters();
}
uint16_t getFrontUp(){
  TCA9548A(FRONT_UP);
  return sensor.readRangeSingleMillimeters();
}
uint16_t getFrontDown(){
  TCA9548A(FRONT_DOWN);
  return sensor.readRangeSingleMillimeters();
}
uint16_t getGyro(){
  float angolo;
  angolo = giro->getGradi();
  return angolo;
}
