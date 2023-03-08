#include "Wire.h"
#include "Lasers.h"
#include "I2Cdev.h"

void setup() {
  Wire.begin();
  setupLasers();
}

void loop(){
  Serial.print("Left : ");
  Serial.print(getLeft());
  delay(1000);
  Serial.print("      Right : ");
  Serial.print(getRight());
  delay(1000);
  Serial.print("      FrontUp : ");
  Serial.print(getFrontUp());
  delay(1000);
  Serial.print("      Back : ");
  Serial.print(getBack());
  delay(1000);
  Serial.print("      FrontDown : ");
  Serial.println(getFrontDown());
  delay(1000);
}
