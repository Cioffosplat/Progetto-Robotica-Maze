#ifndef GIROSCOPIO_H
#define GIROSCOPIO_H

#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

#define OUTPUT_READABLE_YAWPITCHROLL

#define DIRECTION_SIZE 4

enum Direction
{
    Up = 0, 
    Right = 1, 
    Down = 2, 
    Left = 3
};

class Giroscopio
{
    private:
        int actualDirection = 1;
        float angolo = 0;

        MPU6050 mpu;
        
        float ypr[3];
        bool dmpReady = false;
        uint8_t mpuIntStatus;
        Quaternion q;
        uint8_t fifoBuffer[64];
        VectorFloat gravity;

    public:

        static Direction directions[DIRECTION_SIZE];

        Giroscopio();
        
        float getGradi();

        Direction getDirection();

        void changeDirectionTowardsRight();
        void changeDirectionTowardsLeft();
};

#endif
