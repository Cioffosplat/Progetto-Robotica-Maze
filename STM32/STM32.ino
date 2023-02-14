#include "Gyro/Giroscopio.h"
#include "Gyro/Giroscopio.cpp"
#include "Infrared_Sensor/Infrared_Sensor.h"
#include "Infrared_Sensor/Infrared_Sensor.cpp"
#include "Motors/Motori.h"
#include "Motors/Motori.cpp"
#include "Multi_Laser/Lasers.h"
#include "Multi_Laser/Lasers.cpp"
#include "Rgb_Detector/Rgb_Sensor.h"
#include "Rgb_Detector/Rgb_Sensor.cpp"
#include <Servo.h>

#define MOTORS_PIN_1 PA8
#define MOTORS_PIN_2 PA9
#define MOTORS_PIN_3 PA10
#define MOTORS_PIN_4 PA11

#define DELTA_GYRO 3

#define SERVO_PIN B1

Servo myServo;
Motori *myMotors;
Giroscopio *giro;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  myServo.attach(SERVO_PIN);
  myMotors = new Motori(MOTORS_PIN_1, MOTORS_PIN_2, MOTORS_PIN_3, MOTORS_PIN_4);
  giro = new Giroscopio();
  setupLasers();
}

void loop() {
  if (Serial.available() > 0){
    //examples of commands from rasp: "0\n"; "10\n"; "21\n"
    String data = Serial.readStringUntil('\n');
    char command = data.charAt(0);
    String result = commandCases(command, data);
    Serial.print(result + '\n');
  }
}

String commandCases(char com, String data){
  String result;
  switch (com) {


    //send all sensors
    case '0':
    {
      String s = gyroString() + ";" + lasersString();
      break;
    } 

    
    //movement method
    case '1':
    {
      result = moveRobot(data[1]);
      break;
    }

     
    //medikit dropper
    case '2':
    {
      int n;
      n = data.charAt(1) - '0';
      dropMedikit(n);
      result = "1";
      break;
    }

    
    //send only lasers
    case '3':
    {
      result = lasersString();    
      break;
    } 


    //only gyro
    case '4':
    {
      result = gyroString();
      break;
    }

    
    default:
    {
      result = "X";
      break;
    }

    
  }
  return result;
}


String gyroString(){
  float angle = giro->getGradi();
  String sAngle = String(angle, 2);
  return sAngle;  
}


String lasersString(){
  String las = "";
  las += getFrontUp() + ';';
  las += getFrontDown() + ";" ;
  las += getRight() + ";" ;
  las += getLeft() + ";";
  las += getBack();
  return las;
}

String robotGoBack(){
  String result = "1";
  float front = getFrontDown();
  float back = getBack();
  if(back < front){
    float startDIST = back;
    float tmp = back;
    myMotors->indietro();
    while ( tmp > startDIST - 300.0){
      if (isBlack()){
        myMotors->avanti();
        while ( tmp < startDIST){
          tmp = getBack();
        }
        myMotors->fermo();
        return "0";
      }
      tmp = getBack();
    }
    myMotors->fermo();
  }else{
    float startDIST = front;
    float tmp = front;
    myMotors->indietro();
    while ( tmp < startDIST + 300.0){
      if (isBlack()){
        myMotors->avanti();
        while ( tmp > startDIST){
          tmp = getFrontDown();
        }
        myMotors->fermo();
        return "0";
      }
      tmp = getFrontDown();
    }
    myMotors->fermo();
  }
  if (isBlue()){
    result += "1";
  }
  else if (isSilver()){
    result += "2";
  }
  else{
    result += "0";
  }
  return result;
}

String robotGoFront(){
  String result = "1";
  float front = getFrontDown();
  float back = getBack();
  if(back < front){
    float startDIST = back;
    float tmp = back;
    myMotors->avanti();
    while ( tmp < startDIST + 300.0){
      if (isBlack()){
        myMotors->indietro();
        while ( tmp > startDIST){
          tmp = getBack();
        }
        myMotors->fermo();
        return "0";
      }
      tmp = getBack();
    }
    myMotors->fermo();
  }else{
    float startDIST = front;
    float tmp = front;
    myMotors->avanti();
    while ( tmp > startDIST - 300.0){
      if (isBlack()){
        myMotors->indietro();
        while ( tmp < startDIST){
          tmp = getFrontDown();
        }
        myMotors->fermo();
        return "0";
      }
      tmp = getFrontDown();
    }
    myMotors->fermo();
  }
  if (isBlue()){
    result += "1";
  }
  else if (isSilver()){
    result += "2";
  }
  else{
    result += "0";
  }
  return result;
}

String moveRobot(char d){
  String result;
  switch (d){
    case '0':
      result = robotGoFront();
      break;
    case '1':
      result = robotGoBack();
      break;
    case '2':
      rotateRobot(90.0);
      result = robotGoFront();
      break;
    case '3':
      rotateRobot(-90.0);
      result = robotGoFront();
      break;
  }
  return result;
}


void rotateRobot(float g){
  float startG; 
  float nowG;
  startG = giro->getGradi();
  nowG = giro->getGradi();
  if(g>0){
    myMotors->destra();
    while(!(nowG > (startG + g - DELTA_GYRO))){
      nowG = giro->getGradi();
    }
  }else{
    myMotors->sinistra();
    while(!(nowG < (startG + g + DELTA_GYRO))){
      nowG = giro->getGradi();
    }
  }
  myMotors->fermo();
}


void dropMedikit(int n){
  for(int i=0; i<n; i++){
    myServo.write(90);
    delay(1000);
    myServo.write(0);
    delay(1000);
  }
}
