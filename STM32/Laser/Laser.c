/*
@Author Giulio Semenzato
This is a program that tests the funcionality of the TCA9548A i2c multisim
with 5 VL53L0X laser sensors 
*/

#include <Wire.h>		//library for i2c comunication
#include <VL53L0X.h>	//library for laser sensor comunication

VL53L0X sensor;		//laser sensor declaration

//Function to send data to the specified multplexer bus
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}



void setup() {
  Serial.begin(9600);	//initializing the serial port
  Wire.begin();			//initializing the i2c comunication

  /*
  This commands are used for setting every laser sensor connected to
  the TCA9548A multisim by using the "TCA9548A()" function to select
  every laser connected to the various bus of the multisim 
  */
  TCA9548A(0);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 1!");
    while (1) {}
  }
  
  
  sensor.setMeasurementTimingBudget(200000);	
  /*
    this method gives 200ms to the laser 
    to take the measures
    so it gets more accurate 
  */
  
  TCA9548A(1);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 2!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(200000);	
  TCA9548A(2);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 3!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(200000);
  
  TCA9548A(3);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 4!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(200000);
  
  TCA9548A(4);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 5!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(200000);
  
}

void loop(){
  for(int i = 0; i<5; i++){
    TCA9548A(i);
    Serial.println((i+1));
    Serial.println(sensor.readRangeSingleMillimeters());
    if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
    Serial.println();
  }
}
