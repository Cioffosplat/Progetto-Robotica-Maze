#ifndef LASERS_H
#define LASERS_H
#include <Wire.h>
#include <VL53L0X.h>
#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"

    void setupLasers();
    void setupGyro();
    void TCA9548A(uint8_t bus);
    uint16_t getRight();
    uint16_t getLeft();
    uint16_t getBack();
    uint16_t getFrontUp();
    uint16_t getFrontDown();
    uint16_t getGyro();
    VL53L0X sensor;

#endif
