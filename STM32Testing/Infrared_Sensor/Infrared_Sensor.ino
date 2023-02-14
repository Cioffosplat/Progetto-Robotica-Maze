#include "Infrared_Sensor.h"

void setup() {
  Serial.begin(9600);
  setupInfrared();
}

void loop() {
 Serial.print("Infrared Value: ");
 Serial.println(getInfrared());
 delay(500);

}
