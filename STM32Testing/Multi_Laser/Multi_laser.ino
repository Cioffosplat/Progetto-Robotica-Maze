#include "Wire.h"
#include "Lasers.h"
#include "I2Cdev.h"

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Started setup");
  Wire.begin();
  setupLasers();
}

void loop(){
  //Serial.print("0: ");
  //Serial.println(getFrontR());
  Serial.print("0: ");
  Serial.println(getFrontL());
  Serial.print("2: ");
  Serial.println(getLeftR());
  Serial.print("3: ");
  Serial.println(getLeftL());
  //Serial.print("4: ");
  //Serial.println(getBackR());
  Serial.print("4: ");
  Serial.println(getBackR());
  Serial.print("6: ");
  Serial.println(getRightR());
  Serial.print("7: ");
  Serial.println(getRightL());
  delay(200);
}
