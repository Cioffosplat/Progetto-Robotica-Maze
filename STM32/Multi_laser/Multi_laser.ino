#include "Lasers.h"

void setup() {
  Serial.begin(9600);
}

void loop(){
  Serial.println("Right:" + getRight());
  Serial.println("Left:" + getLeft());
  Serial.println("FrontUp: " + getFrontUp());
  Serial.println("Back: " + getBack());
  Serial.println("Down: " + getFrontDown());
}
