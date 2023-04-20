#include "Finecorsa.h"

void setup() {
  setupCorsa();
  Serial.begin(115200);
}

void loop() {
  /*int s1 = digitalRead(PB9);
  int s2 = digitalRead(PB4);
  int s3 = digitalRead(PB8);
  int s4 = digitalRead(PA2);
  Serial.print("S1=");
  Serial.println(s1);
  Serial.print("S2=");
  Serial.println(s2);
  Serial.print("S3=");
  Serial.println(s3);
  Serial.print("S4=");
  Serial.println(s4);*/
  bool front = frontClick();
  bool back = backClick();
  Serial.print("Front");
  Serial.println(front);
  Serial.print("Back");
  Serial.println(back);
}
