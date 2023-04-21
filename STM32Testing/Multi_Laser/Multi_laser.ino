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
  Serial.print("0: ");
  Serial.println(getFrontR());
  Serial.print("1: ");
  Serial.println(getFrontL());
  Serial.print("2: ");
  Serial.println(getLeftL());
  Serial.print("3: ");
  Serial.println(getBackL());
  Serial.print("4: ");
  Serial.println(getBackR());
  Serial.print("5: ");
  Serial.println(getRightR());
  delay(200);
}
