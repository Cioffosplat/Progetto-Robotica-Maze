//#include "Giroscopio.h"
//#include "Infrared_Sensor.h"
//#include "Motori.h"
//#include "Lasers.h"
//#include "Rgb_Sensor.h"
//#include "Medikit.h"


void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}


void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    char command = data[0];
    commandCases(command, data);
    Serial.print("You sent me: ");
    Serial.println(data);
  }
}

void commandCases(char com, String data){
  switch (com) {
    case '0':
      //send all data from sensors
      break;
    case '1':
      //metodo move(data[1]);
      break;
    case '2':
      //metodo cagaMattone();
      break;
    default:
      //richiedi di nuovo il comando seriale da raspberry 
      break;
  }
}
