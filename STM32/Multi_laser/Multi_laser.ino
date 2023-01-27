#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

//Function to send data to the specified multplexer bus
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}



void setup() {

  
  Serial.begin(9600);
  Wire.begin();
  
  TCA9548A(1);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 2!");
    while (1) {}
  }
  
  TCA9548A(2);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 5!");
    while (1) {}
  }

  TCA9548A(3);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 5!");
    while (1) {}
  }
  TCA9548A(4);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 5!");
    while (1) {}
  }
  TCA9548A(5);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 5!");
    while (1) {}
  }
}

void loop(){
  
    TCA9548A(1);
    Serial.print("Sensore 1: ");
    Serial.print(sensor.readRangeSingleMillimeters());
    if (sensor.timeoutOccurred()) {
      Serial.print(" TIMEOUT"); 
    }
    Serial.println();
    
    TCA9548A(2);
    Serial.print("Sensore 2: ");
    Serial.print(sensor.readRangeSingleMillimeters());
    if (sensor.timeoutOccurred()) {
      Serial.print(" TIMEOUT"); 
    }
    Serial.println();

    TCA9548A(3);
    Serial.print("Sensore 3: ");
    Serial.print(sensor.readRangeSingleMillimeters());
    if (sensor.timeoutOccurred()) {
      Serial.print(" TIMEOUT");
    }
    Serial.println();
    
    TCA9548A(4);
    Serial.print("Sensore 4: ");
    Serial.print(sensor.readRangeSingleMillimeters());
    if (sensor.timeoutOccurred()) {
      Serial.print(" TIMEOUT"); 
    }
    Serial.println();

    TCA9548A(5);
    Serial.print("Sensore 5: ");
    Serial.print(sensor.readRangeSingleMillimeters());
    if (sensor.timeoutOccurred()) {
      Serial.print(" TIMEOUT"); 
    }
    Serial.println();
    delay(3000);
}
