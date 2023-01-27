#ifndef LASERSENSOR_H
#define LASERSENSOR_H

#include "Adafruit_VL53L0X.h"
#include "Arduino.h"

// ================== Costanti sensori =================

#define SHT_LOX1 43
#define SHT_LOX2 39
#define SHT_LOX3 45
#define SHT_LOX4 41

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;


void initLaserSensors()
{
// all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot 1 VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot 2 VL53L0X"));
    while(1);
  }

  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // initing LOX3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot 3 VL53L0X"));
    while(1);
  }

  // activating LOX4
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  // initing LOX4
  if(!lox4.begin(LOX4_ADDRESS)) {
    Serial.println(F("Failed to boot 4 VL53L0X"));
    while(1);
  }
}

int getFrontSensorValue()
{
    int value = -1;

    lox1.rangingTest(&measure1, false);

    if (measure1.RangeStatus != 4)
    { 
        value = measure1.RangeMilliMeter;
    }
    else{
        value=8000;
    }

    return value;
}

int getRightSensorValue()
{
    int value = -1;

    lox2.rangingTest(&measure2, false);

    if (measure2.RangeStatus != 4)
    { 
        value = measure2.RangeMilliMeter;
    }

    return value;
}

int getBackSensorValue()
{
    int value = -1;

    lox3.rangingTest(&measure3, false);

    if (measure3.RangeStatus != 4)
    { 
        value = measure3.RangeMilliMeter;
    }

    return value;
}

int getLeftSensorValue()
{
    int value = -1;

    lox4.rangingTest(&measure4, false);

    if (measure4.RangeStatus != 4)
    { 
        value = measure4.RangeMilliMeter;
    }

    return value;
}

#endif
