#include "Lasers.h"

Lasers l = Lasers();

void setup() {
  Serial.begin(9600);
}

void loop(){
  Serial.println(l.getRight());
}
