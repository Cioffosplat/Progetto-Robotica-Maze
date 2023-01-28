#include "Lasers.h"

#define LEFT 1
#define RIGHT 2
#define BACK 3
#define FRONT_UP 4
#define FRONT_DOWN 5

Lasers::Lasers(){
  
  Wire.begin();
  
  TCA9548A(LEFT);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }
  
  TCA9548A(RIGHT);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }

  TCA9548A(BACK);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }
  
  TCA9548A(FRONT_UP);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }
  
  TCA9548A(FRONT_DOWN);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1) {}
  }
}

void Lasers::TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

uint16_t Lasers::getRight(){
  TCA9548A(RIGHT);
  return sensor.readRangeSingleMillimeters();
}
uint16_t Lasers::getLeft(){
  TCA9548A(LEFT);
  return sensor.readRangeSingleMillimeters();
}
uint16_t Lasers::getBack(){
  TCA9548A(BACK);
  return sensor.readRangeSingleMillimeters();
}
uint16_t Lasers::getFrontUp(){
  TCA9548A(FRONT_UP);
  return sensor.readRangeSingleMillimeters();
}
uint16_t Lasers::getFrontDown(){
  TCA9548A(FRONT_DOWN);
  return sensor.readRangeSingleMillimeters();
}
