#include <Wire.h>

Giroscopio *

void setup(){
  //indirizzo dello slave
  Wire.begin(0x69)
  Wire.onRequest(requestEvent);
}

void loop(){
  
}

void requestEvent(){
  
  
  
  Wire.write();
}
