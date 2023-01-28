#include "Lasers.h"

Lasers l = Lasers();

void setup() {
  Serial.begin(9600);
}

void loop(){
  Serial.println("Right:" + l.getRight());
  /*Serial.println("Left:" + l.getLeft());
  Serial.println("FrontUp: " + l.getFrontUp());
  Serial.println("Back: " + l.getBack());
  Serial.println("Down: " + l.getFrontDown());*/
}
