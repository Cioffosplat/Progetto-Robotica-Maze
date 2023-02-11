#include "Infrared_Sensor.h"
#include <Arduino.h>
#include <Wire.h>

#define IR_pin PA0    //Pin for the sensor
#define minSilver 0  //Replace value with the minimum for the Silver tile
#define maxSilver 0  //Replace value with the maximum for the Silver tile

void setupInfrared(){
    pinMode(IR_pin, INPUT);
}

int getInfrared(){
    int g = analogRead(IR_pin);
}

bool isSilver() {
  int val = getInfrared();
  if(val <= maxSilver && val >= minSilver ){
    return true;
  }else {
    return false;
  }
}
