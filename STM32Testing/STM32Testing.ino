#include "I2Cdev.h"
#include "Infrared_Sensor/Infrared_Sensor.h"
#include "Infrared_Sensor/Infrared_Sensor.cpp"
#include "Motors/Motori.h"
#include "Motors/Motori.cpp"
#include "Multi_Laser/Lasers.h"
#include "Multi_Laser/Lasers.cpp"
#include "Rgb_Detector/Rgb_Sensor.h"
#include "Rgb_Detector/Rgb_Sensor.cpp"
#include "Finecorsa/Finecorsa.h"
#include "Finecorsa/Finecorsa.cpp"
#include <Servo.h>
#include "Arduino.h"

#define BAUD 115200

#define PIN_S1 PA9
#define PIN_S2 PA8
#define PIN_S3 PA10
#define PIN_S4 PB3

#define LED_PIN PB5

//#define L_frontUp 0
//#define L_frontDown 1
//#define L_right 2
//#define L_left 3
//#define L_back 4

const float BLOCK_SIZE = 300; 
const float MAX_DISTANCE = 750;


unsigned long SB_MS = 1500;
unsigned long MOVE_MS = 1000;

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
  setupCorsa();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0){
    String data = Serial.readStringUntil('\n');
    commandCases(data);
  }
}

void led_blink(){
  for(int i = 0; i < 12; i++){
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
}


void commandCases(String data){
  String result;
  char c = data.charAt(0);
  switch (c) {
    
    //send all sensors
    case '0':
    {
      led_blink();
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
  Serial.println(getFrontL());
  Serial.println(getFrontR());
  Serial.println(getRightL());
  Serial.println(getRightR());
  Serial.println(getBackR());
  Serial.println(getBackL());
  Serial.println(getLeftL());
  Serial.println(getLeftR());
}

void robotGoFront(){
  String result = "1";
  int front = getFrontR();
  int back = getBackR();
  if(back < front){
      int startDIST = back;
      int tmp = back;
      while ( tmp < startDIST + BLOCK_SIZE){
        myMotors->avanti();
        delay(100);
        if (isBlack()){
          myMotors->indietro();
          while ( tmp > startDIST){
            tmp = getBackR();
          }
          myMotors->fermo();
          Serial.println("0");
          return;
        }
        tmp = getBackR();
      }
      myMotors->fermo();
      delay(100);
  }else{
    int startDIST = front;
    int tmp = front;
      while ( tmp > startDIST - BLOCK_SIZE){
        myMotors->avanti();
        delay(50);
        if (isBlack()){
          myMotors->indietro();
          while ( tmp < startDIST){
            tmp = getFrontR();
          }
          myMotors->fermo();
          Serial.println("0");
          return;
        }
        tmp = getFrontR();
      }
      myMotors->fermo();
      delay(100);
  }
  //method to recognise blue and silver atm not needed
  if (isBlue()){
    result += "1";
  }
  /*else if (isSilver()){
    result += "2";
  }
  */
  else{
    result += "0";
  }
  Serial.println(result);
}

void wallAdjustament(bool back){
  if(back == true){
    myMotors->indietro();
    while(!backClick()){;}
    myMotors->fermo();
    int startL = getBackR();
    myMotors->avanti();
    while(getBackR() < 75){
    }
    myMotors->fermo();
  }else{
    myMotors->avanti();
    while(!frontClick()){;}
    myMotors->fermo();
    int startL = getFrontR();
    myMotors->indietro();
    while(getFrontR() < 75){
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
  while(Serial.available()==0){
    ;
  }
  myMotors->fermo();
  while(Serial.available()>0){
    Serial.read();
  }
}


void dropMedikit(){
  myServo.write(100);
  delay(1000);
  myServo.write(0);
  delay(1000);
  
}
