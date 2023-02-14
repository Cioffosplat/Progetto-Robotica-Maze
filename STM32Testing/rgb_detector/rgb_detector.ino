#include "Rgb_Sensor.h"

void setup(){
    setupRGB();
}

void loop() 
{
 Serial.print("Red Value: ");
 Serial.print(process_red_value());
 Serial.print("     Green Value: ");
 Serial.print(process_green_value());
 Serial.print("     Blue Value: ");
 Serial.println(process_blue_value());
 delay(500);
}
