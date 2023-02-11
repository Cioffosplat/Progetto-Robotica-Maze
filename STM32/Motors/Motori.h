#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>

// ALL of the commentated methods inside of the class are used to connect
// the enable pins and regulate the motor's speed and rpm

class Motori
{
private:
    int d1;
    int d2;
    //int motored_b;
    int d3;
    int d4;
    //int motored_a;
    //int defaultSpeed;

    //int chooseSpeed(int speed);
public:

    Motori(int d1, int d2, int d3, int d4);
    void avanti(/*int speed = -1*/);
    void indietro(/*int speed = -1*/);
    void destra(/*int speed = -1*/);
    void sinistra(/*int speed = -1*/);
    void fermo();
}; 

#endif