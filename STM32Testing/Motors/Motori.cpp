#include "Motori.h"

Motori::Motori(int d1, int d2, int d3, int d4)
{
    this->d1=d1;
    this->d2=d2;
    this->d3=d3;
    this->d4=d4;

    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(d3, OUTPUT);
    pinMode(d4, OUTPUT);

}


void Motori::avanti()
{
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);
    analogWrite(d1, 127);
    analogWrite(d2, 0);
}
    
void Motori::indietro()
{
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);
    analogWrite(d1, 0);
    analogWrite(d2, 127);
}
    
void Motori::destra()
{
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);
    analogWrite(d1, 127);
    analogWrite(d2, 0);

}

void Motori::sinistra()
{

    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);
    analogWrite(d1, 0);
    analogWrite(d2, 127);

}
 
void Motori::fermo()
{
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
    analogWrite(d1, 0);
    analogWrite(d2, 0);
}
