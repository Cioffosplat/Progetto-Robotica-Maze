#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

#include <Wire.h>
    void setupRGB();
    int process_red_value();
    int process_blue_value();
    int process_green_value();
    bool isBlue();
    bool isBlack();


#endif RGB_SENSOR
