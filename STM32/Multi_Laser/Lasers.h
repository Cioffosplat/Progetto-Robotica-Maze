#ifndef LASERS_H
#define LASERS_H
#include <Wire.h>
#include <VL53L0X.h>
#include <Arduino.h>

    void setupLasers();
    void TCA9548A(uint8_t bus);
    uint16_t getRight();
    uint16_t getLeft();
    uint16_t getBack();
    uint16_t getFrontUp();
    uint16_t getFrontDown();
    VL53L0X sensor;

#endif
