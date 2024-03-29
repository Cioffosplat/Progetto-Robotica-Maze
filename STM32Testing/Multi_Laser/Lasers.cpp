#include "Lasers.h"

//0,3,4,5,7

#define FRONT_L 0
//#define FRONT_R 1
//#define RIGHT_L 2
#define RIGHT_R 3
#define BACK_R 4
#define BACK_L 5
//#define LEFT_L 6
#define LEFT_R 7


void setupLasers() {

    
    TCA9548A(FRONT_L);
    sensor.setTimeout(500);
    if (!sensor.init()) {
        while (1) {}
    }

    /*TCA9548A(FRONT_R);
    sensor.setTimeout(500);
    if (!sensor.init()) {
        while (1) {}
    }*/

    TCA9548A(RIGHT_R);
    sensor.setTimeout(500);
    if (!sensor.init()) {
        while (1) {}
    }
    
    TCA9548A(BACK_R);
    sensor.setTimeout(500);
    if (!sensor.init()) {
        while (1) {}
    }
    
    TCA9548A(BACK_L);
    sensor.setTimeout(500);
    if (!sensor.init()) {
        while (1) {}
    }
    TCA9548A(LEFT_R);
    sensor.setTimeout(500);
    if (!sensor.init()) {
        while (1) {}
    }
}

void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
    
    uint16_t getFrontL(){
        TCA9548A(FRONT_L);
        return sensor.readRangeSingleMillimeters();
    }
    
    /*uint16_t getFrontR(){
        TCA9548A(FRONT_R);
        return sensor.readRangeSingleMillimeters();
    }*/
    uint16_t getRightR(){
        TCA9548A(RIGHT_R);
        return sensor.readRangeSingleMillimeters();
    }
    uint16_t getBackR(){
        TCA9548A(BACK_R);
        return sensor.readRangeSingleMillimeters();
    }
    uint16_t getBackL(){
        TCA9548A(BACK_L);
        return sensor.readRangeSingleMillimeters();
    }
    uint16_t getLeftR(){
        TCA9548A(LEFT_R);
        return sensor.readRangeSingleMillimeters();
    }
    
