@Author Filippo Schierato AKA Papaya
#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

#include <Wire.h>

class Rgb_Sensor {
public:
    int process_red_value();

    int process_blue_value();

    int process_green_value();

    bool isBlue();

    bool isBlack();

    int r;
    int g;
    int b;
};

#endif RGB_SENSOR
