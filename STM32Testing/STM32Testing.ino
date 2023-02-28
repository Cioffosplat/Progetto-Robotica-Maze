#include "I2Cdev.h"
//#include "MPU6050_6Axis_MotionApps20.h"
//#include "Gyro/Giroscopio.h"
//#include "Gyro/Giroscopio.cpp"
#include "Infrared_Sensor/Infrared_Sensor.h"
#include "Infrared_Sensor/Infrared_Sensor.cpp"
#include "Motors/Motori.h"
#include "Motors/Motori.cpp"
#include "Multi_Laser/Lasers.h"
#include "Multi_Laser/Lasers.cpp"
#include "Rgb_Detector/Rgb_Sensor.h"
#include "Rgb_Detector/Rgb_Sensor.cpp"
#include <Servo.h>
#include "Arduino.h"

#define BAUD 115200

#define PIN_S1 PA9
#define PIN_S2 PA8
#define PIN_S3 PA10
#define PIN_S4 PB3

#define L_frontUp 0
#define L_frontDown 1
#define L_right 2
#define L_left 3
#define L_back 4

const float WALL_MAX = 300.00; 
const float BLOCK_SIZE = 300.00; 

unsigned long ROTATION_MILLIS = 1000;
unsigned long SB_MS = 1500;

#define DELTA_GYRO 3

#define SERVO_PIN PB1

//servo motor
Servo myServo;
//Motors on h bridge
Motori *myMotors;


void setup() {
  //both usb and raspberry serial on pins a3 and a2
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);
  myServo.write(0);
  myMotors = new Motori(PIN_S1,PIN_S2,PIN_S3,PIN_S4);
  setupLasers();
  setupRGB();
}

void loop() {
  if (Serial.available() > 0){
    String data = Serial.readStringUntil('\n');
    commandCases(data);
  }
}

void commandCases(String data){
  String result;
  char c = data.charAt(0);
  switch (c) {
    
    //send all sensors
    case '0':
    {
      lasersString();
      break;
    } 
    
    //movement method
    case '1':
    {
      if (data == "10"){
        robotGoFront();
      }
      if (data == "12"){
        rotateRobot(true);
      }
      if (data == "13"){
        rotateRobot(false);
      }
      if (data == "14"){
        goUntillSerial();
      }
      if (data == "15"){
        wallAdjustament(true);
      }
      if (data == "16"){
        wallAdjustament(false);
      }
      break;
    }

     
    //medikit dropper
    case '2':
    {
      dropMedikit();
      break;
    }

    
    //send only lasers
    case '3':
    {
      lasersString();    
      break;
    } 

    default:
    {
      result = "X";
      break;
    }
  }
}

void goUntillSerial(){
  myMotors->avanti();
  while(true){
    if(Serial.available()>0){
      myMotors->fermo();
      String tmp= Serial.readStringUntil('\n');
      break;
    }
  }
}

void lasersString(){
  Serial.println(getFrontUp());
  Serial.println(getFrontDown());
  Serial.println(getRight());
  Serial.println(getLeft());
  Serial.println(getBack());
}

void robotGoFront(){
  String result = "1";
  int front = getFrontDown();
  int back = getBack();
  if(back < front){
    int startDIST = back;
    int tmp = back;
    while ( tmp < startDIST + BLOCK_SIZE){
      myMotors->avanti();
      delay(100);
      /*
      if (isBlack()){
        myMotors->indietro();
        while ( tmp > startDIST){
          tmp = getBack();
        }
        myMotors->fermo();
        return "0";
      }
      */
      tmp = getBack();
    }
    myMotors->fermo();
    delay(100);
  }else{
    int startDIST = front;
    int tmp = front;
    while ( tmp > startDIST - BLOCK_SIZE){
      myMotors->avanti();
      delay(100);
      /*
      if (isBlack()){
        myMotors->indietro();
        while ( tmp < startDIST){
          tmp = getFrontDown();
        }
        myMotors->fermo();
        return "0";
      }
      */
      tmp = getFrontDown();
    }
    myMotors->fermo();
    delay(100);
  }
  /*method to recognise blue and silver atm not needed
  if (isBlue()){
    result += "1";
  }
  else if (isSilver()){
    result += "2";
  }
  else{
    result += "0";
  }*/
  result += "0";
  Serial.println(result);
}

void wallAdjustament(bool back){
  if(back == true){
    myMotors->indietro();
    delay(SB_MS);
    myMotors->fermo();
    int startL = getBack();
    myMotors->avanti();
    while(getBack() < (startL + 40)){
    }
    myMotors->fermo();
  }else{
    myMotors->avanti();
    delay(SB_MS);
    myMotors->fermo();
    int startL = getFrontDown();
    myMotors->indietro();
    while(getFrontDown() < (startL + 40)){
    }
    myMotors->fermo();
  }
}

void rotateRobot(bool d){
  if(d==true){
    myMotors->destra();
  }else{
    myMotors->sinistra();
  }
  delay(ROTATION_MILLIS);
  myMotors->fermo();
}


void dropMedikit(){
  for (int i = 0; i < 100; i++){
    myServo.write(i);
    delay(100);
  }
  for (int i = 100; i >= 0; i--){
    myServo.write(i);
    delay(100);
  }
}
