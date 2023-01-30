#include "Lasers.h"

void setup() {
  Serial.begin(9600);
  setupLasers();
}

void loop(){
  Serial.print("Left : ");
  Serial.print(getLeft());
  Serial.print("      Right : ");
  Serial.print(getRight());
  Serial.print("      FrontUp : ");
  Serial.print(getFrontUp());
  Serial.print("      Back : ");
  Serial.print(getBack());
  Serial.print("      FrontDown : ");
  Serial.println(getFrontDown());
  delay(500);
}
