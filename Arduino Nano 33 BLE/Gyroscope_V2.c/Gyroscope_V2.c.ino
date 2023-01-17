//Author Filippo Schierato (CoFounder of the Robot Maze Project in collaboration with Giulio Semenzato)
//Both libraries essential 
#include <Arduino_LSM9DS1.h>

// Declare variables to store the gyroscope and accelerometer data
float Gx, Gy, Gz;
float Ax, Ay, Az;

// Declare local variables of a byte array for the serial comunication of x,y and z values 
byte byteArray[4] = {NULL,NULL,NULL,NULL};

void setup() {
  // Initialize the serial port
  Serial.begin(9600);
  while (!Serial);// Wait for serial to be available
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    Serial.println("Double-check wiring.");
    while (1);
  }
}

void loop() {

  // Read and Prepear the gyroscope data
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(Gx, Gy, Gz);
  }

// Print of the current action
  if( Gx > 10){
    Serial.println("Going Up");
  } else if( Gx < -10){
    Serial.println("Going Down");
  }
  if( Gy > 10 ){
    Serial.println("Going Left");
  } else if( Gy < -10){
    Serial.println("Going Right");
  }
  
  // Print the gyro's x, y, and z values to the serial monitor
  Serial.print("Gx: ");
  Serial.print(Gx);
  Serial.print("  Gy: ");
  Serial.print(Gy);
  Serial.print("  Gz: ");
  Serial.println(Gz);
/*
  // Gyroscope data conversion from float to byte
    byte gyroXByte = (byte)x;
    byte gyroYByte = (byte)y;
    byte gyroZByte = (byte)z;

  // Print the gyro's x, y, and z values into byte conversion
  Serial.print("byteX: ");
  Serial.print(gyroXByte);
  Serial.print("  byteY: ");
  Serial.print(gyroYByte);
  Serial.print("  byteZ: ");
  Serial.println(gyroZByte); 
  */

  //Delay for examinating purpouse
  delay(500);
}
