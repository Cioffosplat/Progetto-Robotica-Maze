#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>

class Motori
{
private:
    int d1;
    int d2;
    int motored_b;
    int d3;
    int d4;
    int motored_a;
    int s1;
    int s2; 
    int motores_a;
    int motores_b;
    int s3;
    int s4;
    int defaultSpeed;

    int chooseSpeed(int speed);
public:

    Motori(
        int d1,
        int d2,
        int motored_b,
        int d3,
        int d4,
        int motored_a,
        int s1,
        int s2,
        int motores_a,
        int motores_b,
        int s3,
        int s4,
        int defaultSpeed
    );
    void avanti(int speed = -1);
    void indietro(int speed = -1);
    void destra(int speed = -1);
    void sinistra(int speed = -1);
    void fermo();
}; 

#endif