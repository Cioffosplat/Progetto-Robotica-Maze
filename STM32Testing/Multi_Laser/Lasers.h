#ifndef LASERS_H
#define LASERS_H
#include <Wire.h>
#include <VL53L0X.h>
#include <Arduino.h>

    void setupLasers();
    void TCA9548A(uint8_t bus);
    uint16_t getRightL();
    uint16_t getRightR();
    uint16_t getLeftL();
    uint16_t getLeftR();
    uint16_t getFrontL();
    uint16_t getFrontR();
    uint16_t getBackL();
    uint16_t getBackR();
    VL53L0X sensor;

#endif
