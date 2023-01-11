#include<Wire.h>
#include <VL53L0X.h>
#define SDA 43
#define SCL 42

VL53L0X sensor;

//Function to send data to the specified multplexer bus
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}



void setupLasers() {
  
  Serial.begin(9600);
  Wire.begin(SCL, SDA);

  sensor.setTimeout(500);
  sensor.setAddress(0x70)
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}