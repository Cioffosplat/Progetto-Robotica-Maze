#include "Rgb_Sensor.h"

void setup(){
    setupRGB();
}

void loop() 
{
 Serial.print("IS BLUE? ");
 Serial.println(isBlue());
 Serial.print("IS BLACK? ");
 Serial.println(isBlack());
 delay(300);
}
