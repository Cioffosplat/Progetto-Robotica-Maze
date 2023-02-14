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

#define PIN_S1 PA11
#define PIN_S2 PA10
#define PIN_S3 PA8
#define PIN_S4 PA9

#define DELTA_GYRO 3

#define SERVO_PIN B1

//raspberry serial on pins a3 and a2, need to use Serial.write to pass the values to raspberry
HardwareSerial Serial2(PA3, PA2);
//servo motor
Servo myServo;
//Motors on h bridge
Motori *myMotors;
//gyroscope object
Giroscopio *giro;





void setup() {
  //both usb and raspberry serial on pins a3 and a2
  Serial.begin(9600);
  Serial2.begin(115200); 
  while (!Serial) {
    ;
  }
  myServo.attach(SERVO_PIN);
  myMotors = new Motori(PIN_S1,PIN_S2,PIN_S3,PIN_S4);
  giro = new Giroscopio();
  setupLasers();
  setupRGB();
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
      gyroString();
      lasersString();
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
      lasersString();    
      break;
    } 


    //only gyro
    case '4':
    {
      gyroString();
      break;
    }

    case '5':
    {
      rotateRobot(90.00);
      result ="1";
      break;
    }

    case '6':
    {
      myMotors->avanti();
      delay(1000);
      result = "1";
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


void gyroString(){
  //possible error in the conversion 
  float angle = giro->getGradi();
  String sAngle = String(angle, 2);
  Serial.println(sAngle);  
}


void lasersString(){
  Serial.println(getFrontUp());
  Serial.println(getFrontDown());
  Serial.println(getRight());
  Serial.println(getLeft());
  Serial.println(getBack());
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
      /*if (isBlack()){
        myMotors->avanti();
        while ( tmp < startDIST){
          tmp = getBack();
        }
        myMotors->fermo();
        return "0";
      }
      */
      tmp = getBack();
    }
    myMotors->fermo();
  }else{
    float startDIST = front;
    float tmp = front;
    myMotors->indietro();
    while ( tmp < startDIST + 300.0){
      /*if (isBlack()){
        myMotors->avanti();
        while ( tmp > startDIST){
          tmp = getFrontDown();
        }
        myMotors->fermo();
        return "0";
      }
      */
      tmp = getFrontDown();
    }
    myMotors->fermo();
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
  }else{
    float startDIST = front;
    float tmp = front;
    myMotors->avanti();
    while ( tmp > startDIST - 300.0){
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
    while(nowG < (startG + g)){
      delay(100);
      nowG = giro->getGradi();
    }
  }else{
    myMotors->sinistra();
    while(nowG > (startG + g)){
      delay(100);
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
