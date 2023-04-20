#include "Rgb_Sensor.h"

void setup(){
    setupRGB();
}

void loop() 
{
  
  Serial.println("VALORI GREZZI");
  Serial.print("RED: ");
  Serial.println(process_red_value());
  Serial.print("BLUE: ");
  Serial.println(process_blue_value());
  Serial.print("GREEN: ");
  Serial.println(process_green_value());
  
  
 Serial.print("IS BLUE? ");
 Serial.println(isBlue());
 Serial.print("IS BLACK? ");
 Serial.println(isBlack());
 delay(300);
}
