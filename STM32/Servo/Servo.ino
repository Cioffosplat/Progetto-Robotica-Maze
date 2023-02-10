#include<Servo.h>

int servoPin = PA0;

Servo myServo;

void setup(){
  myServo.attach(servoPin);
}

void loop(){
  myServo.write(90);
  delay(1000);
  myServo.write(0);
  delay(1000);
}
