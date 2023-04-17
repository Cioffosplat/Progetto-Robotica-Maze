#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Giroscopio.h"

MPU6050 mpu;

Giroscopio *giro;
void setup() {
  Wire.begin();
  Serial.begin(57600);
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
  giro = new Giroscopio();
}

void loop() {
  float angolo;
  angolo = giro->getGradi();
  Serial.println(angolo);

  // Wait for MPU6050 data ready interrupt
  while (!mpu.getIntStatus() & 0x02);

  // Get the latest DMP packet
  uint8_t fifoBuffer[64];
  mpu.getFIFOBytes(fifoBuffer, 64);
  // Get the acceleration data from the packet
  int16_t ax = ((fifoBuffer[0] << 8) | fifoBuffer[1]);

  // Map the X-axis acceleration to a range of -180 to 180 degrees
  float x_angle = map(ax, -32768, 32767, -180, 180);

  Serial.print("X-axis angle: ");
  Serial.println(x_angle);
  delay(100);
} 
