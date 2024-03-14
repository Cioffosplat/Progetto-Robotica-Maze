#ifndef LASERS_H
#define LASERS_H
#include <Wire.h>
#include <VL53L0X.h>
#include <Arduino.h>

    void setupLasers();
    void TCA9548A(uint8_t bus);
    uint16_t getFrontL(); //0
    //uint16_t getFrontR(); //1
    //uint16_t getRightL(); //2
    uint16_t getRightR(); //3
    uint16_t getBackR(); //4
    uint16_t getBackL(); //5
    //uint16_t getLeftL(); //6
    uint16_t getLeftR(); //7
    VL53L0X sensor;

#endif
