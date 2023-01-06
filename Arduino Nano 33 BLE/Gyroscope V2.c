//Author Filippo Schierato (CoFounder of the Robot Maze Project in collaboration with Giulio Semenzato)
//Both libraries essential 
#include <Wire.h>
#include "SparkFunLSM9DS1.h"

// Create an instance of the LSM9DS1 library called `imu` mainly used to detect the hardware
LSM9DS1 imu;

// Declare variables to store the gyroscope data
float gyroX, gyroY, gyroZ;

void setup()
{
  // Initialize the serial port
  Serial.begin(9600);
  while (!Serial);  // Wait for serial to be available

  // Initialize the IMU LSM9DS1
  if (imu.begin() == false)
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    while (1);
  }
}

void loop()
{
  // Read the gyroscope data
  imu.readGyro();

    // Convert the gyroscope data degree per second
  gyroX = imu.calcGyro(imu.gx);
  gyroY = imu.calcGyro(imu.gy);
  gyroZ = imu.calcGyro(imu.gz);

  // Convert the gyroscope data to a range of 0 to 360 degrees
  gyroX = fmod(gyroX + 360, 360);
  gyroY = fmod(gyroY + 360, 360);
  gyroZ = fmod(gyroZ + 360, 360);

  // Gyroscope data conversion from float to byte
  byte gyroXByte = (byte)gyroX;
  byte gyroYByte = (byte)gyroY;
  byte gyroZByte = (byte)gyroZ;

  // Temporary print for the date of the gyroscope
  Serial.print("Gyroscope (deg): "); //Data in degrees from 0 to 360
  Serial.print(gyroX);
  Serial.print(", ");
  Serial.print(gyroY);
  Serial.print(", ");
  Serial.println(gyroZ);
  Serial.print("Gyroscope (bytes): "); //Data in bytes converted from degrees aka float values
  Serial.print(gyroXByte);
  Serial.print(", ");
  Serial.print(gyroYByte);
  Serial.print(", ");
  Serial.println(gyroZByte);

  // Delay used to lay out the results (variable value from 1 second to anything we like)
  delay(1000);
}
