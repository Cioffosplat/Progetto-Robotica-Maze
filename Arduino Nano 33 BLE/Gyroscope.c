/*
  Arduino LSM9DS1 - Simple Gyroscope

  This example reads the gyroscope values from the LSM9DS1
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Nano 33 BLE Sense
*/

#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600); //Serial Begin per il monitor seriale, modda come vuoi
  while (!Serial);
  Serial.println("Started");

//Codice di controllo di errore
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
//Dati del giroscopio
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;
  
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
  }
}
