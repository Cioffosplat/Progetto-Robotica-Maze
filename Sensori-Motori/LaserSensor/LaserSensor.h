#ifndef LASERSENSOR_H
#define LASERSENSOR_H

#include "Adafruit_VL53L0X.h"
#include "Arduino.h"

class LaserSensor 
{
    private:
        int pin;
        int lox_address;
        Adafruit_VL53L0X *lox;


    public:
        LaserSensor(int pin, int lox_address, Adafruit_VL53L0X *lox);
        ~LaserSensor();

        int getValue();
        bool isFree(int maxValue = 200);
//bool isFreeDavanti( maxValue = 100);
        void init();
        void laserLow();
        void laserHigh();
        
};

#endif