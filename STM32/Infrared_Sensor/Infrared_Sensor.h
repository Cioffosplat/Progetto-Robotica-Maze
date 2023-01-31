#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include <Wire.h>
#include <Arduino.h>

    void setupInfrared();
    int getInfrared();
    bool isSilver();

#endif INFRARED_SENSOR