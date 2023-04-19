#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>

class Motori
{
private:
    int d1;
    int d2;
    int d3;
    int d4;

public:

    Motori(
        int d1,
        int d2,
        int d3,
        int d4
        );
    void avanti();
    void indietro();
    void destra();
    void sinistra();
    void fermo();
}; 

#endif