#include "Gyro/Giroscopio.h"
#include "Gyro/Giroscopio.cpp"
#include "Infrared_Sensor/Infrared_Sensor.h"
#include "Motors/Motori.h"
#include "Multi_Laser/Lasers.h"
#include "Rgb_Detector/Rgb_Sensor.h"
#include <Servo.h>

#define MOTORS_PIN_1 A9
#define MOTORS_PIN_2 A10
#define MOTORS_PIN_3 A11
#define MOTORS_PIN_4 A12

#define DELTA_GYRO 3

#define SERVO_PIN PA0;

Servo myServo;
Motori myMotors;
Giroscopio *giro;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  myServo.attach(SERVO_PIN);
  myMotors = new Motori();
  giro = new Giroscopio();
  setupLasers();
}

void loop() {
  if (Serial.available() > 0) {
    //exemples of commands from rasp: "0\n"; "10\n"; "21\n"
    String data = Serial.readStringUntil('\n');
    char command = data[0];
    Serial.print("You sent me: ");
    Serial.println(data);
    commandCases(command, data);
  }
}

String commandCases(char com, String data){
  String result;
  switch (com) {

    //all sensors
    case '0':
      
      result = "1";
      break;
      
    //movement method
    case '1':
      result = moveRobot(data[1]);
      break;
      
    //medikit dropper
    case '2':
      int n;
      n = data[1]-'0';
      dropMedikit(n);
      break;
      
    case '3':
      //send only lasers
      break;
    case '4':
      //send only gyroscope
      break;
    default:
      result = "-1";
      break;
  }
  return result;
}

int robotGoBack(){

}

String robotGoFront(){
  String result = "1";
  float front = getFrontDown();
  float back = getBack();
  if(back < front){
    float startDIST = back;
    float tmp = back;
    myMotors.avanti();
    while ( tmp < startDIST + 300.0){
      if (isBlack()){
        myMotors.indietro();
        while ( tmp > startDIST){
          tmp = getBack();
        }
        myMotors.fermo();
        return "0";
      }
      tmp = getBack();
    }
    myMotors.fermo();
  }else{
    float startDIST = front;
    float tmp = front;
    myMotors.avanti();
    while ( tmp > startDIST - 300.0){
      if (isBlack()){
        myMotors.indietro();
        while ( tmp < startDIST){
          tmp = getFrontDown();
        }
        myMotors.fermo();
        return "0";
      }
      tmp = getFrontDown();
    }
    myMotors.fermo();
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
  int result;
  switch (d){
    case '0':
      result = robotGoFront();
      break;
    caso '1':
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
    myMotors.destra();
    while(!(nowG > (startG + g - DELTA_GYRO))){
      nowG = giro->getGradi();
    }
  }else{
    myMotors.sinistra();
    while(!(nowG < (startG + g + DELTA_GYRO))){
      nowG = giro->getGradi();
    }
  }
  myMotors.fermo();
}


void dropMedikit(int n){
  for(int i=0; i<n; i++){
    myServo.write(90);
    delay(1000);
    myServo.write(0);
    delay(1000);
  }
}
