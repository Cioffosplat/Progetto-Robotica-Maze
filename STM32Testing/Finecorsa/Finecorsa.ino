#include "Finecorsa.h"

void setup() {
  setupCorsa();
  Serial.begin(9600);
}

void loop() {
  bool front = backClick();
  bool back = backClick();
  Serial.println(front);
  Serial.println(back);
}
